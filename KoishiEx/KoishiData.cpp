#include "StdAfx.h"
#include "KoishiEx.h"
#include "sha256.h"

#pragma comment(lib, "zlib.lib")
#include "zlib.h"
#include "bz2.h"

using namespace Koishi;

//#define sdebug
#ifdef sdebug
	#define vprintf(x, y) printf(x, y)
#else
	#define vprintf(x, y)
#endif
//stream类
stream::stream(){
	data = NULL;
	length = 0;
	storage = 0;
	position = 0;
	bitPosition = 0;
}
stream::stream(longex newLen){
	if(newLen == 0){
		data = NULL;
	}else{
		data = new uchar[newLen];
		vprintf("Allocate %d bytes.\n", newLen);
		memset(data, 0, newLen);
	}
	length = 0;
	storage = newLen;
	position = 0;
	bitPosition = 0;
}
stream::stream(const stream& sSource){
	if(sSource.storage == 0){
		data = NULL;
	}else{
		data = new uchar[sSource.storage];
		vprintf("Allocate %d bytes.\n", sSource.storage);
		memcpy(data, sSource.data, sSource.storage);
	}
	length = sSource.length;
	storage = sSource.storage;
	position = 0;
	bitPosition = 0;
}
stream& stream::operator = (const stream &sSource){
	if(this == &sSource)
		return *this;
	if(data){
		delete[] data;
		vprintf("Release %d bytes.\n", sSource.storage);
	}
	if(sSource.storage == 0){
		data = NULL;
	}else{
		data = new uchar[sSource.storage];
		vprintf("Allocate %d bytes.\n", sSource.storage);
		memcpy(data, sSource.data, sSource.storage);
	}
	length = sSource.length;
	storage = sSource.storage;
	position = 0;
	bitPosition = 0;
	return *this;
}
stream::~stream(){
	release();
}
void stream::allocate(longex newLen){
	release();
	if(newLen == 0){
		return;
	}
	if(!data){
		length = 0;
		position = 0;
		bitPosition = 0;
		storage = newLen;
		data = new uchar[storage];
		vprintf("Allocate %d bytes.\n", storage);
		memset(data, 0, storage);
	}
}
void stream::reallocate(longex newLen){
	if(newLen<storage){
		//不用重新分配了
		return;
	}
	uchar *buff = new uchar[length];
	longex buffLen = length;
	memcpy(buff, data, buffLen);
	release();
	allocate(newLen);
	memcpy(data, buff, buffLen);
	length = buffLen;
	delete[] buff;
}
void stream::release(){
	if(data){
		delete[] data;
		vprintf("Release %d bytes.\n", storage);
		data = NULL;
		length = 0;
		storage = 0;
		position = 0;
	}
}
void stream::clear(){
	memset(data, 0, storage);
	length = 0;
}
uchar& stream::operator[] (longex pos) const{
	return data[pos];
}
uchar stream::getBit(longex pos, long bitCount) const{
	longex atByte;
	long inByte;
	switch(bitCount){
	case 1:
		atByte = pos / 8;
		inByte = pos % 8;
		return (data[atByte] & (1 << inByte)) >> inByte;
	case 2:
		atByte = pos / 4;
		inByte = pos % 4;
		return (data[atByte] & (3 << (inByte << 1))) >> (inByte << 1);
	case 4:
		atByte = pos / 2;
		inByte = pos % 2;
		return (data[atByte] & (15 << (inByte << 2))) >> (inByte << 2);
	}
	return data[pos];
}
uchar stream::getRBit(longex pos, long bitCount) const{
	//将字节流按1位/2位/4位分段
	longex atByte;
	long inByte;
	switch(bitCount){
	case 1:
		atByte = pos / 8;
		inByte = 7 - pos % 8;
		return (data[atByte] & (1 << inByte)) >> inByte;
	case 2:
		atByte = pos / 4;
		inByte = 3 - pos % 4;
		return (data[atByte] & (3 << (inByte << 1))) >> (inByte << 1);
	case 4:
		atByte = pos / 2;
		inByte = 1 - pos % 2;
		return (data[atByte] & (15 << (inByte << 2))) >> (inByte << 2);
	}
	return data[pos];
}
void *stream::begin(longex pos) const{
	return data + pos;
}
void *stream::end(longex pos) const{
	return data + length - pos;
}
/////////////////////////////////////////////////
longex stream::getPosition() const{
	return position;
}
longex stream::resetPosition(){
	position = 0;
	return 0;
}
longex stream::movePosition(longex dist){
	longex now = position;
	longex goal = now + dist;
	if(goal<0){
		position = 0;
	}else if(goal>length){
		position = length;
	}else{
		position = goal;
	}
	return position;
}
longex stream::setPosition(longex pos){
	if(pos<0)
		pos = 0;
	if(pos>length)
		pos = length;
	position = pos;
	return position;
}
/////////////////////////////////

bool stream::pushByte(uchar d){
	if(length < storage){
		data[length++] = d;
		return true;
	}else{
		return false;
	}
}
bool stream::pushWord(word d){
	if(length + 1< storage){
		memcpy(data + length, &d, 2);
		length += 2;
		return true;
	}else{
		return false;
	}
}
bool stream::pushDWord(dword d){
	if(length + 3< storage){
		memcpy(data + length, &d, 4);
		length += 4;
		return true;
	}else{
		return false;
	}
}
bool stream::pushInt64(longex d){
	if(length + 7< storage){
		memcpy(data + length, &d, 4);
		length += 4;
		return true;
	}else{
		return false;
	}
}
bool stream::pushInt(long i){
	if(length + 3< storage){
		memcpy(data + length, &i, 4);
		length += 4;
		return true;
	}else{
		return false;
	}
}
bool stream::pushString(str s){
	if(length + s.size() <= storage){
		for(longex i = 0;i<s.size();i++)
			data[length++] = s[i];
		return true;
	}else{
		return false;
	}
}
void stream::pushStream(const stream &addedStream, longex len){
	if(length + len > storage){
		reallocate((length + len) * 2);
	}
	for(longex i = 0;i<MIN(len, addedStream.length);i++)
		data[length++] = addedStream[i];
}
void stream::push(const void *sour, longex len){
	if(length + len > storage){
		reallocate((length + len) * 2);
	}
	for(longex i = 0;i<len;i++)
		data[length++] = *((char*)sour+i);
}
bool stream::readByte(uchar& d){
	if(position > length - 1)
		return false;
	d = data[position];
	movePosition(1);
	return true;
}
bool stream::readWord(word& d){
	if(position > length -2)
		return false;
	d = data[position] | data[position+1]<<8;
	movePosition(2);
	return true;
}
bool stream::readDWord(dword& d){
	if(position > length -4){
		return false;
	}
	d = data[position] | data[position+1]<<8 | data[position+2]<<16 | data[position+3] << 24;
	movePosition(4);
	return true;
}
bool stream::readInt64(longex& d){
	if(position > length -8){
		return false;
	}
	dword i1 = data[position] | data[position+1]<<8 | data[position+2]<<16 | data[position+3]<<24;
	dword i2 = data[position+4] | data[position+5]<<8 | data[position+6]<<16 | data[position+7]<<24;
	movePosition(8);
	d = (longex)(((unsigned long long)i2 << 32) | i1);
	return true;
}
bool stream::readInt(long& d){
	dword dw;
	bool b;
	b = readDWord(dw);
	d = (long)dw;
	return b;
}
str stream::readString(dword len){
	if(position > length - len){
		return "";
	}
	stream s(len+1);
	readStream(s, len);
	s.pushByte(0);
	return (char*)s.data;
}
longex stream::read(void *dest, longex len){
	if(position > length - len)
		len = length - position;
	for(longex i = 0;i<len; i++){
		*((uchar*)dest+i) = data[position++];
	}
	return len;
}
longex stream::readStream(stream &dest, longex len){
	if(position > length -len){
		len = length - position;
	}
	dest.allocate(len*2);
	for(longex i = 0; i<len;i++){
		dest.pushByte(data[position+i]);
	}
	position += len;
	return len;
}
void stream::insertStream(const stream &insertStream, longex len, longex pos){
	if(len > insertStream.length)
		len = insertStream.length;
	if(len + length > storage)
		reallocate((length + len)*2);
	if(pos > length)
		pos = length;
	//开始处理
	stream prefix;
	stream suffix;
	longex i;
	prefix.allocate(pos);
	for(i = 0;i<pos;i++)
		prefix.pushByte(data[i]);
	suffix.allocate(length-pos);
	for(i = 0;i<length-pos;i++)
		suffix.pushByte(data[pos+i]);
	clear();
	pushStream(prefix, prefix.length);
	pushStream(insertStream, len);
	pushStream(suffix, suffix.length);
	prefix.release();
	suffix.release();
}
void stream::deleteStream(longex pos, longex len){
	if(pos > length)
		pos = length;
	if(len+pos > length)
		len = length - pos;
	if(len <= 0)
		return;
	//开始处理
	stream prefix;
	stream suffix;
	prefix.allocate(pos);
	for(longex i = 0;i<pos;i++)
		prefix.pushByte(data[i]);
	suffix.allocate(length-pos-len);
	for(longex i = 0;i<length -pos-len;i++)
		suffix.pushByte(data[pos+len+i]);
	clear();
	pushStream(prefix, prefix.length);
	pushStream(suffix, suffix.length);
	prefix.release();
	suffix.release();
}
bool stream::modifyByte(longex pos, uchar d){
	if(pos<length || pos>=0){
		data[pos] = d;
		return true;
	}
	return false;
}
bool stream::modifyDWord(longex pos, dword d){
	if(pos<length-4 || pos>=0){
		data[pos] = (d & 0xff);
		data[pos+1] = ((d >> 8) & 0xff);
		data[pos+2] = ((d >> 16) & 0xff);
		data[pos+3] = ((d >> 24) & 0xff);
		return true;
	}
	return false;
}
bool stream::modifyInt(longex pos, long i){
	if(pos<length-4 || pos>=0){
		data[pos] = (i & 0xff);
		data[pos+1] = ((i >> 8) & 0xff);
		data[pos+2] = ((i >> 16) & 0xff);
		data[pos+3] = ((i >> 24) & 0xff);
		return true;
	}
	return false;
}
longex stream::replace(const uchar &whos, const uchar &to){
	longex count = 0;
	for(longex i = 0;i<length;i++){
		if(data[i]==whos){
			count ++;
			data[i] = to;
		}
	}
	return count;
}
bool stream::makeFile(str fileName){
	FILE *fl = fopen(fileName.c_str(), "wb");
	if(!fl)
		return false;
	fwrite(data, 1, length, fl);
	fclose(fl);
	return true;
}
bool stream::loadFile(str fileName){
	FILE *fl = fopen(fileName.c_str(), "rb");
	if(!fl)
		return false;
	fseek(fl, 0, SEEK_END);
	longex sz = ftell(fl);
	reallocate(sz+1);
	fseek(fl, 0, SEEK_SET);
	length = fread((void*)data, 1, sz, fl);
	fclose(fl);
	return true;
}

void stream::nameMask(){
	if(length < 256)
		return;
	str IMGnameMask = "puchikon@neople dungeon and fighter DNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNF";
	for(long i = 0;i<255;i++)
		data[i]^= IMGnameMask[i];
}

void stream::SHA256code(stream &dest){
	uchar *buff = new uchar[32];
	longex len = length;
	KoishiSHA256::SHA256 sha;
	sha.reset();
	sha.add(data, len);
	sha.getHash(buff);
	dest.allocate(32);
	dest.push(buff, 32);
	delete[] buff;
}

longex stream::findStream(const stream &s,longex startPos){
	int fLine = s.length;
	int i;
	while(startPos + fLine <= length){
		bool isOK = true;
		for(i=0;i<fLine;i++){
			if(data[startPos+i] != s[i]){
				isOK = false;
				break;
			}
		}
		if(isOK){
			return startPos;
		}else{
			startPos ++;
		}
	}
	return -1;
}

longex stream::splitStream(const stream &s, queueex &posList, queueex &lenList){
	longex startPos = 0;
	longex fLine = s.length;
	posList.clear();
	lenList.clear();
	posList.push_back(0);
	while(true){
		longex p = findStream(s, startPos);
		if(p == -1){
			lenList.push_back(length-startPos);
			break;
		}else{
			lenList.push_back(p-startPos);
			posList.push_back(p+fLine);
			startPos = p + fLine;
		}
	}
	return posList.size();
}

//进行BZ2压缩
int stream::BZcompress(stream &dest){
	unsigned int len = 10*length;
	dest.allocate(len);
	int i = BZ2_bzBuffToBuffCompress((char*)dest.data, &len, (char*)data, length, 1, 0, 0);
	dest.length = len;
	return i;
}
//进行BZ2解压
int stream::BZuncompress(stream &dest){
	unsigned int len = 1000*length;
	dest.allocate(len);
	int i = BZ2_bzBuffToBuffDecompress((char*)dest.data, &len, (char*)data, length, 0, 0);
	dest.length = len;
	return i;
}

int stream::ZLIBcompress(stream &dest){
	longex tryLength = length+1000; 
	dest.allocate(tryLength);
	int i = (int)compress(dest.data, (dword*)&tryLength, data, length);
	dest.length = tryLength;
	return i;
}
int stream::ZLIBuncompress(stream &dest, longex tryLength){
	dest.allocate(tryLength);
	int i = (int)uncompress(dest.data, (dword*)&tryLength, data, length);
	dest.length = tryLength;
	return i;
}