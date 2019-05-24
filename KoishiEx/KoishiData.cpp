#include "StdAfx.h"
#include "KoishiEx.h"
#include "sha256.h"

#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "libbz2.lib")
#include "zlib.h"
#include "bzlib.h"

using namespace Koishi;

//class stream
stream::stream(){
	maxLen = 0;
	len = 0;
	data = NULL;
	pt = 0;
}
stream::stream(longex _len){
	maxLen = _len;
	len = 0;
	pt = 0;
	data = new uchar[maxLen];
}
stream::stream(const stream& _s){
	maxLen = _s.maxLen;
	len = _s.len;
	pt = 0;
	data = new uchar[maxLen];
	if(data)
		memcpy(data, _s.data, maxLen);
}
stream::~stream(){
	release();
}
stream& stream::operator = (const stream &_s){
	if(this == &_s)
		return *this;
	if(data)
		delete[] data;
	maxLen = _s.maxLen;
	len = _s.len;
	data = new uchar[maxLen];
	if(data)
		memcpy(data, _s.data, maxLen);
	return *this;
}
void stream::allocate(longex _len){
	if(!data){
		len = 0;
		pt = 0;
		maxLen = _len;
		data = new uchar[maxLen];
		for(dword i = 0;i<maxLen;i++){
			data[i] = 0;
		}
	}
}
void stream::reallocate(longex _len){
	if(_len<maxLen){
		return;
	}
	uchar *buff = new uchar[len];
	longex buffLen = len;
	memcpy(buff, data, buffLen);
	release();
	allocate(_len);
	for(longex i = 0;i<buffLen;i++){
		push(buff[i]);
	}
	delete[] buff;
}
void stream::release(){
	if(data){
		delete[] data;
		data = NULL;
		maxLen = 0;
		len = 0;
	}
}
uchar& stream::operator[] (longex pos) const{
	return data[pos];
}
stream::operator str(){
	return (char*)data;
}
uchar stream::getBit(longex pos, long bitCount) const{
	//将字节流按1位/2位/4位分段
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
void stream::clear(bool makeZero){
	if(makeZero){
		for(longex i = 0 ;i<maxLen;i++)
			data[i] = 0;
	}
	len = 0;
}
uchar stream::push(uchar _d){
	data[len++] = _d;
	return 1;
}
uchar stream::push(word _d){
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	return 1;
}
uchar stream::push(dword _d){
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	return 1;
}
uchar stream::push(longex _d){
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	return 1;
}
uchar stream::push(long _i){
	return push((dword)_i);
}
uchar stream::pushString(str _s){
	for(longex i = 0;i<_s.size();i++)
		data[len++] = (uchar)_s[i];
	return 1;
}
longex stream::replace(const uchar &whos, const uchar &to){
	longex count = 0;
	for(longex i = 0;i<len;i++){
		if(data[i]==whos){
			count ++;
			data[i] = to;
		}
	}
	return count;
}
uchar stream::pushStream(const stream &_s, longex _len){
	if(getLen() + _len > getMaxLen()){
		reallocate(getLen() + _len * 5);
	}
	for(longex i = 0;i<_len;i++)
		data[len++] = _s.data[i];
	return 1;
}
longex stream::getLen() const{
	return len;
}
longex stream::getMaxLen() const{
	return maxLen;
}
longex stream::getPtPos() const{
	return pt;
}
longex stream::ptMove(longex dist){
	longex now = (longex)pt;
	longex goa = now + dist;
	if(goa<0){
		pt = 0;
	}else if((longex)goa>len){
		pt = len;
	}else{
		pt = (longex)goa;
	}
	return pt;
}
longex stream::ptMoveTo(longex pos){
	if(pos<0)
		pos = 0;
	if(pos>len)
		pos = len;
	pt = (longex)pos;
	return pt;
}
uchar stream::read(uchar &_d){
	if(pt > len - 1){
		return 0;
	}
	_d = data[pt];
	ptMove(sizeof(uchar));
	return 1;
}
uchar stream::read(word &_d){
	if(pt > len -2){
		return 0;
	}
	_d = data[pt] | data[pt+1]<<8;
	ptMove(sizeof(word));
	return 1;
}
uchar stream::read(dword &_d){
	if(pt > len -4){
		return 0;
	}
	_d = data[pt] | data[pt+1]<<8 | data[pt+2]<<16 | data[pt+3]<<24;
	ptMove(sizeof(dword));
	return 1;
}
uchar stream::read(longex &_d){
	if(pt > len -8){
		return 0;
	}
	_d = data[pt] | data[pt+1]<<8 | data[pt+2]<<16 | data[pt+3]<<24 | ((longex)(data[pt+4] | data[pt+5]<<8 | data[pt+6]<<16 | data[pt+7]<<24)<<32);
	ptMove(sizeof(64));
	return 1;
}
uchar stream::read(long &_i){
	dword bresult;
	read(bresult);
	_i = (long)bresult;
	return 1;
}
uchar stream::read(void *dest, longex l){
	if(pt > len - l)
		return 0;
	for(longex i = 0;i<l; i++){
		*((uchar*)dest+i) = data[pt++];
	}
	return 1;
}
str stream::readString(dword _len){
	if(pt > len -_len){
		return "";
	}
	stream _s(_len+1);
	readStream(_s, _len);
	_s.push((uchar)0);
	return (char*)_s.data;
}
void stream::readStream(stream &dest, longex _len){
	if(pt > len -_len){
		_len = len - pt;
	}
	dest.reallocate(_len);
	dest.clear();
	for(longex i = 0; i<_len;i++){
		dest.push(data[pt+i]);
	}
	pt += _len;
}
void stream::insertStream(const stream &_s, longex _len, longex _pos){
	//len超过s的长度
	if(_len > _s.getLen()){
		_len = _s.getLen();
	}
	//超过最大长度时重新分配
	if(_len + getLen() > getMaxLen()){
		reallocate(getLen() + _len*5);
	}
	//插入点超过全长默认在最后追加
	if(_pos > getLen()){
		_pos = getLen();
	}
	//开始处理
	stream prefix, suffix;
	longex i;
	//首部时prefix无效
	if(_pos>0){
		prefix.allocate(_pos);
		for(i = 0;i<_pos;i++){
			prefix.push(data[i]);
		}
	}
	if(_pos < getLen()){
		suffix.allocate(getLen()-_pos);
		for(i = 0;i<getLen()-_pos;i++){
			suffix.push(data[_pos+i]);
		}
	}
	clear();
	if(prefix.getLen()>0){
		pushStream(prefix, prefix.getLen());
	}
	pushStream(_s, _len);
	if(suffix.getLen()>0){
		pushStream(suffix, suffix.getLen());
	}
	prefix.release();
	suffix.release();
}
void stream::deleteStream(longex _pos, longex _len){
	//
	if(_pos > getLen()){
		_pos = getLen();
	}
	//删除长度的结尾超过总长
	if(_len+_pos> getLen()){
		_len = getLen() - _pos;
	}
	if(_len <= 0)
		return;
	//开始处理
	stream prefix, suffix;
	longex i;
	//首部时prefix无效
	if(_pos>0){
		prefix.allocate(_pos);
		for(i = 0;i<_pos;i++){
			prefix.push(data[i]);
		}
	}
	if(_pos + _len< getLen()){
		suffix.allocate(getLen()-_pos-_len);
		for(i = 0;i<getLen()-_pos-_len;i++){
			suffix.push(data[_pos+_len+i]);
		}
	}
	clear();
	if(prefix.getLen()>0){
		pushStream(prefix, prefix.getLen());
	}
	if(suffix.getLen()>0){
		pushStream(suffix, suffix.getLen());
	}
	prefix.release();
	suffix.release();
}
bool stream::modify(longex _pos, uchar _d){
	if(_pos<getLen() || _pos>=0){
		data[_pos] = _d;
		return true;
	}
	return false;
}
bool stream::modify(longex _pos, long _i){
	if(_pos<getLen()-4 || _pos>=0){
		data[_pos] = (_i & 0xff);
		data[_pos+1] = ((_i >> 8) & 0xff);
		data[_pos+2] = ((_i >> 16) & 0xff);
		data[_pos+3] = ((_i >> 24) & 0xff);
		return true;
	}
	return false;
}
bool stream::makeFile(str fileName){
	FILE *fl = fopen(fileName.c_str(), "wb");
	if(!fl)
		return false;
	fwrite(data, 1, len, fl);
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
	len = fread((void*)data, 1, sz, fl);
	fclose(fl);
	return true;
}

void stream::nameMask(){
	if(len < 256){
		return;
	}
	str IMGnameMask = "puchikon@neople dungeon and fighter DNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNF";
	for(long i = 0;i<255;i++){
		data[i]^= IMGnameMask[i];
	}
}

void stream::getSHA256(stream &dest){
	uchar *buff = new uchar[32];
	longex len = getLen();
	KoishiSHA256::SHA256 sha;
	sha.reset();
	sha.add(data, len);
	sha.getHash(buff);
	long i;
	dest.allocate(32);
	for(i=0;i<32;i++){
		dest.push(buff[i]);
	}
	delete[] buff;
}

void stream::getSHA256(stream &dest, const stream &added){
	stream s(*this);
	s.pushStream(added, added.getLen());
	uchar *buff = new uchar[32];
	longex len = s.getLen()/17*17;
	KoishiSHA256::SHA256 sha;
	sha.reset();
	sha.add(s.data, len);
	sha.getHash(buff);
	long i;
	dest.allocate(32);
	for(i=0;i<32;i++){
		dest.push(buff[i]);
	}
	delete[] buff;
}
int stream::compressData(stream &dest, compressType type){
	switch(type){
	case COMP_ZLIB:
	case COMP_ZLIB_DUAL:
		return ZLIBcompress(dest);
	default:
		dest = *this;
		return 0;
	}
 }
int stream::uncompressData(stream &dest, compressType type, longex tryLength){
	switch(type){
	case COMP_ZLIB:
	case COMP_ZLIB_DUAL:
		return ZLIBuncompress(dest, tryLength);
	default:
		dest = *this;
		return 0;
	}
 }

longex stream::findStream(const stream &s,longex startPos){
	int fLine = s.getLen();
	int i;
	while(startPos + fLine <= getLen()){
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
	longex fLine = s.getLen();
	posList.clear();
	lenList.clear();
	posList.push_back(0);
	while(true){
		longex p = findStream(s, startPos);
		if(p == -1){
			lenList.push_back(getLen()-startPos);
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
	unsigned int len = 10*getLen();
	dest.allocate(len);
	int i = BZ2_bzBuffToBuffCompress((char*)dest.data, &len, (char*)data, getLen(), 1, 0, 0);
	dest.len = len;
	return i;
}
//进行BZ2解压
int stream::BZuncompress(stream &dest){
	unsigned int len = 100*getLen();
	dest.allocate(len);
	int i = BZ2_bzBuffToBuffDecompress((char*)dest.data, &len, (char*)data, getLen(), 0, 0);
	dest.len = len;
	return i;
}

int stream::ZLIBcompress(stream &dest){
	longex tryLength = getLen()+1000; 
	dest.allocate(tryLength);
	int i = (int)compress(dest.data, (dword*)&tryLength, data, getLen());
	dest.len = tryLength;
	return i;
}
int stream::ZLIBuncompress(stream &dest, longex tryLength){
	dest.allocate(tryLength);
	int i = (int)uncompress(dest.data, (dword*)&tryLength, data, getLen());
	dest.len = tryLength;
	return i;
}