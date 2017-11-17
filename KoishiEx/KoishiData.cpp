#include "StdAfx.h"
#include "KoishiEx.h"
#include "sha256.h"

#pragma comment(lib, "zlib.lib")
#include "zlib.h"

using namespace Koishi;

//class stream
stream::stream(){
	maxLen = 0;
	len = 0;
	data = NULL;
	pt = 0;
}
stream::stream(b64 _len){
	maxLen = _len;
	len = 0;
	pt = 0;
	data = new b8[maxLen];
}
stream::stream(const stream& _s){
	maxLen = _s.maxLen;
	len = _s.len;
	pt = 0;
	data = new b8[maxLen];
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
	data = new b8[maxLen];
	if(data)
		memcpy(data, _s.data, maxLen);
	return *this;
}
void stream::allocate(b64 _len){
	if(!data){
		len = 0;
		pt = 0;
		maxLen = _len;
		data = new b8[maxLen];
		for(b32 i = 0;i<maxLen;i++){
			data[i] = 0;
		}
	}
}
void stream::reallocate(b64 _len){
	if(_len<maxLen){
		return;
	}
	pb8 buff = new b8[len];
	b64 buffLen = len;
	memcpy(buff, data, buffLen);
	release();
	allocate(_len);
	for(b64 i = 0;i<buffLen;i++){
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
b8& stream::operator[] (b64 _i) const{
	return data[_i];
}
stream::operator str(){
	return (char*)data;
}
void stream::clear(){
	len = 0;
}
b8 stream::push(b8 _d){
	data[len++] = _d;
	return 1;
}
b8 stream::push(b16 _d){
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	return 1;
}
b8 stream::push(b32 _d){
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	_d >>= 8;
	data[len++] = _d & 0xFF;
	return 1;
}
b8 stream::push(b64 _d){
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
b8 stream::push(i32 _i){
	return push((b32)_i);
}
b8 stream::pushString(str _s){
	for(b64 i = 0;i<_s.size();i++)
		data[len++] = (b8)_s[i];
	return 1;
}
b64 stream::replace(const b8 &whos, const b8 &to){
	b64 count = 0;
	for(b64 i = 0;i<len;i++){
		if(data[i]==whos){
			count ++;
			data[i] = to;
		}
	}
	return count;
}
b8 stream::pushStream(const stream &_s, b64 _len){
	if(getLen() + _len > getMaxLen()){
		reallocate(getLen() + _len * 5);
	}
	for(b64 i = 0;i<_len;i++)
		data[len++] = _s.data[i];
	return 1;
}
b64 stream::getLen() const{
	return len;
}
b64 stream::getMaxLen() const{
	return maxLen;
}
b64 stream::ptPos() const{
	return pt;
}
b64 stream::ptMove(i64 dist){
	i64 now = (i64)pt;
	i64 goa = now + dist;
	if(goa<0){
		pt = 0;
	}else if((b64)goa>len){
		pt = len;
	}else{
		pt = (b64)goa;
	}
	return pt;
}
b64 stream::ptMoveTo(i64 pos){
	if(pos<0)
		pos = 0;
	if(pos>len)
		pos = len;
	pt = (b64)pos;
	return pt;
}
b8 stream::read(b8 &_d){
	if(pt > len - 1){
		return 0;
	}
	_d = data[pt];
	ptMove(sizeof(b8));
	return 1;
}
b8 stream::read(b16 &_d){
	if(pt > len -2){
		return 0;
	}
	_d = data[pt] | data[pt+1]<<8;
	ptMove(sizeof(b16));
	return 1;
}
b8 stream::read(b32 &_d){
	if(pt > len -4){
		return 0;
	}
	_d = data[pt] | data[pt+1]<<8 | data[pt+2]<<16 | data[pt+3]<<24;
	ptMove(sizeof(b32));
	return 1;
}
b8 stream::read(b64 &_d){
	if(pt > len -8){
		return 0;
	}
	_d = data[pt] | data[pt+1]<<8 | data[pt+2]<<16 | data[pt+3]<<24 | ((b64)(data[pt+4] | data[pt+5]<<8 | data[pt+6]<<16 | data[pt+7]<<24)<<32);
	ptMove(sizeof(64));
	return 1;
}
b8 stream::read(i32 &_i){
	b32 bresult;
	read(bresult);
	_i = (i32)bresult;
	return 1;
}
str stream::readString(b32 _len){
	if(pt > len -_len){
		return "";
	}
	stream _s(_len+1);
	readStream(_s, _len);
	_s.push((b8)0);
	return (char*)_s.data;
}
void stream::readStream(stream &dest, b64 _len){
	if(pt > len -_len){
		_len = len - pt;
	}
	dest.reallocate(_len);
	dest.clear();
	for(b64 i = 0; i<_len;i++){
		dest.push(data[pt+i]);
	}
	pt += _len;
}
void stream::insertStream(const stream &_s, b64 _len, b64 _pos){
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
	b64 i;
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
void stream::deleteStream(b64 _pos, b64 _len){
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
	b64 i;
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
bool stream::modify(b64 _pos, b8 _d){
	if(_pos<getLen() || _pos>=0){
		data[_pos] = _d;
		return true;
	}
	return false;
}
bool stream::modify(b64 _pos, i32 _i){
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
	b64 sz = ftell(fl);
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
	for(i32 i = 0;i<255;i++){
		data[i]^= IMGnameMask[i];
	}
}

void stream::getSHA256(stream &dest){
	pb8 buf = new b8[32];
	b64 len = getLen();
	KoishiSHA256::SHA256 sha;
	sha.reset();
	sha.add(data, len);
	sha.getHash(buf);
	i32 i;
	dest.allocate(32);
	for(i=0;i<32;i++){
		dest.push(buf[i]);
	}
	delete[] buf;
}

void stream::getSHA256(stream &dest, const stream &added){
	stream s(*this);
	s.pushStream(added, added.getLen());
	pb8 buf = new b8[32];
	b64 len = s.getLen()/17*17;
	KoishiSHA256::SHA256 sha;
	sha.reset();
	sha.add(s.data, len);
	sha.getHash(buf);
	i32 i;
	dest.allocate(32);
	for(i=0;i<32;i++){
		dest.push(buf[i]);
	}
	delete[] buf;
}
i8 stream::compressData(stream &dest, compressType type){
	switch(type){
	case COMP_ZLIB:
		{
			b64 tryLength = getLen()+1000; 
			dest.allocate(tryLength);
			i8 i = (i8)compress(dest.data, (b32*)&tryLength, data, getLen());
			dest.len = tryLength;
			return i;
		}
		break;
	case COMP_NONE:
		{
			dest = *this;
			return 0;
		}
		break;
	default:
		{
			dest = *this;
			return 0;
		}
		break;
	}
 }
i8 stream::uncompressData(stream &dest, compressType type, b64 tryLength){
	switch(type){
	case COMP_ZLIB:
		{
			 dest.allocate(tryLength);
			 i8 i = (i8)uncompress(dest.data, (b32*)&tryLength, data, getLen());
			 dest.len = tryLength;
			 return i;
		}
		break;
	case COMP_ZLIB2:
		{
			 dest.allocate(tryLength);
			 i8 i = (i8)uncompress(dest.data, (b32*)&tryLength, data, getLen());
			 dest.len = tryLength;
			 return i;
		}
		break;
	case COMP_NONE:
		{
			dest = *this;
			return 0;
		}
		break;
	default:
		{
			dest = *this;
			return 0;
		}
		break;
	}
 }