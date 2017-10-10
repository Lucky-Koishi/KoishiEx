#include "StdAfx.h"
#include "KoishiEx.h"
#include "DDS.h"
#include <assert.h>

using namespace Koishi;

/////////有用的结构体的初始化////////////////////////////////////////////////////////
IMGindex::IMGindex(){
	imgoffset = 0;
	imgsize = 0;
	imgname = "";
};
PICinfo::PICinfo(){
	format = COLOR_UDEF;
	comp = COMP_UDEF;
	linkTo = -1;
	dataSize = 0;
	DDSIDused = 0;
};
DDSinfo::DDSinfo(){
	DDSID = 0;
	fourCCID = DPF_UDF;
	height = 0;
	lengthOfCompressed = 0;
	lengthOfDDS = 0;
	reserved = 1;
	width = 0;
}
NPKobject::NPKobject(){
	count = 0;
}
NPKobject::NPKobject(const stream &_s){
	load(_s);
}
NPKobject::NPKobject(const str &fileName){
	loadFile(fileName);
}
IMGobject::IMGobject(){
	//普通属性
	count = 0;
	derived = NULL;
	content.clear();
	indexSize = 0;
	version = VUDEF;
}
IMGobject::IMGobject(const stream &_s){
	load(_s);
}
IMGobject::IMGobject(const str &fileName){
	loadFile(fileName);
}
//////////////////////////////////////////////////////////////////////////////////////
//Main Factory
//////////////////////////////////////////////////////////////////////////////////////

bool NPKobject::load(const stream &_s){
	return invoke(LOAD, (void*)&_s);
}
bool NPKobject::make(stream &_s){
	return invoke(MAKE, (void*)&_s);
}
bool NPKobject::create(){
	return invoke(CREATE);
}
bool NPKobject::release(){
	return invoke(RELEASE);
}
bool NPKobject::loadFile(const str &fileName){
	stream _data;
	bool ret1 = _data.loadFile(fileName);
	bool ret2 = false;
	if(ret1){
		ret2 = load(_data);
	}
	_data.release();
	return ret1 && ret2;
}
bool NPKobject::saveFile(const str &fileName){
	stream _data;
	bool ret1 = make(_data);
	bool ret2 = false;
	if(ret1){
		ret2 = _data.makeFile(fileName);
	}
	_data.release();
	return ret1 && ret2;
}
bool NPKobject::IMGpush(const IMGobject &obj, const str &imgName){
	return invoke(PUSH, (void*)&obj, (void*)&imgName);
}
bool NPKobject::IMGinsert(i32 pos, const IMGobject &obj, const str &imgName){
	return invoke(INSERT, (void*)&pos, (void*)&obj, (void*)&imgName);
}
bool NPKobject::IMGremove(i32 pos){
	return invoke(REMOVE, (void*)&pos);
}
bool NPKobject::IMGreplace(i32 pos, const IMGobject &obj){
	return invoke(REPLACE, (void*)&pos, (void*)&obj);
}
bool NPKobject::IMGrename(i32 pos, const str& newName){
	return invoke(RENAME, (void*)&pos, (void*)&newName);
}
pstream NPKobject::getData(b8 _part){
	switch(_part){
	case 0:
		return &data1;
	case 1:
		return &data2;
	case 2:
		return &data3;
	case 3:
		return &data4;
	default:
		return &data1;
	}
}
b64 NPKobject::getSize() const{
	return data1.getLen()+data2.getLen()+data3.getLen()+data4.getLen();
}
bool NPKobject::IMGextract(b32 pos, IMGobject &obj){
	if(pos<0 || pos>=count){
		return false;
	}
	stream temps;
	obj.derived = &content[pos];
	getData(3)->ptMoveTo(content[pos].get_imgoffset()-getData(0)->getLen() - getData(1)->getLen() - getData(2) -> getLen());
	getData(3)->readStream(temps, (b64)(content[pos].get_imgsize()));
	return obj.load(temps);
}
bool NPKobject::extractIMGFile(i32 pos, str fileName){
	if(pos<0 || pos>=count){
		return false;
	}
	stream temps;
	getData(3)->ptMoveTo(content[pos].get_imgoffset()-getData(0)->getLen() - getData(1)->getLen() - getData(2) -> getLen());
	getData(3)->readStream(temps, (b64)(content[pos].get_imgsize()));
	return temps.makeFile(fileName);
}
bool NPKobject::invoke(b16 command, void *para1, void *para2, void *para3){
	switch(command){
	case CREATE:
		////////////////////////////////////////////////
		//创建空的数据
		//para1:无意义
		//para2:无意义
		//para3:无意义
		////////////////////////////////////////////////
		{
			count = 0;
			content.clear();
			getData(0)->allocate(64);
			getData(0)->pushString("NeoplePack_Bill");
			getData(0)->push((b8)0);
			getData(0)->push((b32)0);
			getData(1)->allocate(64);
			stream _s;
			getData(0)->getSHA256(_s,*getData(1));
			getData(2)->allocate(64);
			getData(2)->pushStream(_s, 32);
			getData(3)->allocate(64);
			return true;
		}
		break;
	case LOAD:
		////////////////////////////////////////////////
		//读取数据
		//para1:(stream*)数据流
		//para2:无意义
		//para3:无意义
		////////////////////////////////////////////////
		{
			stream _data(*(stream*)para1);
			b32 _dword;
			i32 i;
			IMGindex _ii;
			stream _s;
			getData(0)->reallocate(24);
			_data.ptMoveTo(0);
			_data.readStream(*(getData(0)), 20);
			_data.ptMoveTo(0);
			if(_data.readString(16) != "NeoplePack_Bill"){
				return false;
			}
			_data.read(_dword);
			count = _dword;
			getData(1)->reallocate(264*(count+10));
			_data.readStream(*(getData(1)), 264*count);
			_data.ptMoveTo(20);
			for(i=0;i<count;i++){
				_data.read(_dword);
				_ii.set_imgoffset(_dword);
				_data.read(_dword);
				_ii.set_imgsize(_dword);
				_s.allocate(256);
				_data.readStream(_s, 256);
				_s.nameMask();
				_ii.set_imgname((str)_s);
				_s.release();
				content.push_back(_ii);
			}
			getData(2)->reallocate(32);
			_data.readStream(*(getData(2)), 32);
			getData(3)->reallocate(_data.getLen());
			_data.readStream(*(getData(3)), _data.getLen());
			return true;
		}
		break;
	case MAKE:
		////////////////////////////////////////////////
		//制造数据
		//para1:(stream*)数据流
		//para2:无意义
		//para3:无意义
		////////////////////////////////////////////////
		{
			stream *_ps = (stream*)para1;
			b32 len1 = getData(0)->getLen();
			b32 len2 = getData(1)->getLen();
			b32 len3 = getData(2)->getLen();
			b32 len4 = getData(3)->getLen();
			_ps->allocate(len1 + len2 + len3 +len4 + 100);
			_ps->pushStream(*getData(0), len1);
			_ps->pushStream(*getData(1), len2);
			_ps->pushStream(*getData(2), len3);
			_ps->pushStream(*getData(3), len4);
			return true;
		}
		break;
	case RELEASE:
		////////////////////////////////////////////////
		//释放数据
		//para1:无意义
		//para2:无意义
		//para3:无意义
		////////////////////////////////////////////////
		{
			count = 0;
			content.clear();
			getData(0)->release();
			getData(1)->release();
			getData(2)->release();
			getData(3)->release();
			return true;
		}
		break;
	case PUSH:
		//////////////////////////////////////////////////
		//末端插入IMG文件
		//para1:const IMGobject &
		//para2:const str &
		//para3:无意义
		//////////////////////////////////////////////////
		{
			IMGobject _io = *(IMGobject*)para1;
			str _str = *(str*)para2;
			stream _s;
			IMGindex _ii;
			b32 _dword;
			i32 i;
			_ii.set_imgname(_str);
			_ii.set_imgoffset(getSize());
			_ii.set_imgsize(_io.getSize());
			content.push_back(_ii);
			for(i=0;i<content.size();i++){
				_dword = content[i].get_imgoffset();
				content[i].set_imgoffset(_dword+264);
			}
			//////////////////////////////////////////////
			count++;
			getData(0)->clear();
			getData(0)->pushString("NeoplePack_Bill");
			getData(0)->push((b8)0);
			getData(0)->push(count);
			//////////////////////////////////////////////
			getData(1)->clear();
			for(i=0;i<count;i++){
				getData(1)->push(content[i].get_imgoffset());
				getData(1)->push(content[i].get_imgsize());
				_s.allocate(512);
				_s.pushString(content[i].get_imgname());
				while(_s.getLen()<256){
					_s.push((b8)0);
				}
				_s.nameMask();
				getData(1)->pushStream(_s, 256);
				_s.release();
			}
			//////////////////////////////////////////////
			getData(0)->getSHA256(_s,*getData(1));
			getData(2)->clear();
			getData(2)->pushStream(_s, 32);
			_s.release();
			//////////////////////////////////////////////
			_io.make(_s);
			getData(3)->pushStream(_s, _s.getLen());
			return true;
		}
		break;
	case INSERT:
		//////////////////////////////////////////////////
		//插入IMG文件
		//para1:i32
		//para2:const IMGobject &
		//para3:const str &
		//////////////////////////////////////////////////
		{
			i32 _pos = *(i32*)para1;
			if(_pos<0){
				_pos += (count + 1);
			}
			if(_pos<0){
				_pos = 0;
			}
			if(_pos>count){
				_pos = count;
			}
			if(_pos == count){
				return invoke(PUSH, para2, para3);
			}
			IMGobject _io = *(IMGobject*)para2;
			str _str = *(str*)para3;
			i32 i;
			stream _s;
			IMGindex _ii;
			b32 _dword;
			b64 _offset = content[_pos].get_imgoffset() - getData(0)->getLen() - getData(1)->getLen() - getData(2) -> getLen();
			_ii.set_imgname(_str);
			_ii.set_imgoffset(content[_pos].get_imgoffset());
			_ii.set_imgsize(_io.getSize());
			content.insert(content.begin()+_pos, _ii);
			for(i=0;i<content.size();i++){
				_dword = content[i].get_imgoffset();
				_dword += 264;
				if(i>_pos){
					_dword += _io.getSize();
				}
				content[i].set_imgoffset(_dword);
			}
			//////////////////////////////////////////////
			count++;
			getData(0)->clear();
			getData(0)->pushString("NeoplePack_Bill");
			getData(0)->push((b8)0);
			getData(0)->push(count);
			//////////////////////////////////////////////
			getData(1)->clear();
			for(i=0;i<count;i++){
				getData(1)->push(content[i].get_imgoffset());
				getData(1)->push(content[i].get_imgsize());
				_s.allocate(512);
				_s.pushString(content[i].get_imgname());
				while(_s.getLen()<256){
					_s.push((b8)0);
				}
				_s.nameMask();
				getData(1)->pushStream(_s, 256);
				_s.release();
			}
			//////////////////////////////////////////////
			getData(0)->getSHA256(_s,*getData(1));
			getData(2)->clear();
			getData(2)->pushStream(_s, 32);
			_s.release();
			//////////////////////////////////////////////
			_io.make(_s);
			getData(3)->insertStream(_s, _s.getLen(),_offset);
			return true;
		}
		break;
	case REMOVE:
		//////////////////////////////////////////////////
		//删除IMG文件
		//para1:i32
		//para2:无意义
		//para3:无意义
		//////////////////////////////////////////////////
		{
			i32 _pos = *(i32*)para1;
			if(_pos<0){
				_pos += count;
			}
			if(_pos<0){
				_pos = 0;
			}
			if(_pos>count-1){
				_pos = count-1;
			}
			i32 i;
			stream _s;
			IMGindex _ii;
			b32 _dword;
			_ii = content[_pos];
			b64 _offset = content[_pos].get_imgoffset() - getData(0)->getLen() - getData(1)->getLen() - getData(2) -> getLen();
			content.erase(content.begin() + _pos);
			for(i=0;i<content.size();i++){
				_dword = content[i].get_imgoffset();
				_dword -= 264;
				if(i>=_pos){
					_dword -= _ii.get_imgsize();
				}
				content[i].set_imgoffset(_dword);
			}
			/////////////////////////////////////////////////////
			count --;
			getData(0)->clear();
			getData(0)->pushString("NeoplePack_Bill");
			getData(0)->push((b8)0);
			getData(0)->push(count);
			/////////////////////////////////////////////////////
			getData(1)->clear();
			for(i=0;i<count;i++){
				getData(1)->push(content[i].get_imgoffset());
				getData(1)->push(content[i].get_imgsize());
				_s.allocate(512);
				_s.pushString(content[i].get_imgname());
				while(_s.getLen()<256){
					_s.push((b8)0);
				}
				_s.nameMask();
				getData(1)->pushStream(_s, 256);
				_s.release();
			}
			//////////////////////////////////////////////
			getData(0)->getSHA256(_s,*getData(1));
			getData(2)->clear();
			getData(2)->pushStream(_s, 32);
			_s.release();
			//////////////////////////////////////////////
			getData(3)->deleteStream(_offset, _ii.get_imgsize());
			return true;
		}
		break;
	case REPLACE:
		//////////////////////////////////////////////////
		//将已知IMG文件替换成其他的IMG文件（不改名）
		//para1:i32
		//para2:const IMGobject &
		//para3:无意义
		//////////////////////////////////////////////////
		{
			i32 _pos = *(i32*)para1;
			if(_pos<0){
				_pos += count;
			}
			if(_pos<0){
				_pos = 0;
			}
			if(_pos>count){
				_pos = count - 1;
			}
			IMGobject _io = *(IMGobject*)para2;
			i32 i;
			stream _s;
			IMGindex _ii;
			b32 _dword;
			b64 _offset = content[_pos].get_imgoffset() - getData(0)->getLen() - getData(1)->getLen() - getData(2) -> getLen();
			_ii = content[_pos];
			content[_pos].set_imgsize(_io.getSize());
			for(i=0;i<content.size();i++){
				if(i>_pos){
					_dword = content[i].get_imgoffset();
					_dword -= _ii.get_imgsize();
					_dword += _io.getSize();
					content[i].set_imgoffset(_dword);
				}
			}
			//////////////////////////////////////////////////
			getData(1)->clear();
			for(i=0;i<count;i++){
				getData(1)->push(content[i].get_imgoffset());
				getData(1)->push(content[i].get_imgsize());
				_s.allocate(512);
				_s.pushString(content[i].get_imgname());
				while(_s.getLen()<256){
					_s.push((b8)0);
				}
				_s.nameMask();
				getData(1)->pushStream(_s, 256);
				_s.release();
			}
			//////////////////////////////////////////////
			getData(0)->getSHA256(_s,*getData(1));
			getData(2)->clear();
			getData(2)->pushStream(_s, 32);
			_s.release();
			//////////////////////////////////////////////
			_io.make(_s);
			getData(3)->deleteStream(_offset, _ii.get_imgsize());
			getData(3)->insertStream(_s, _s.getLen(), _offset);
			return true;
		}
		break;
	case RENAME:
		//////////////////////////////////////////////////
		//重命名已知的IMG文件
		//para1:i32
		//para2:const str &
		//para3:无意义
		//////////////////////////////////////////////////
		{
			i32 _pos = *(i32*)para1;
			if(_pos<0){
				_pos += count;
			}
			if(_pos<0){
				_pos = 0;
			}
			if(_pos>count){
				_pos = count - 1;
			}
			str _str = *(str*)para2;
			i32 i;
			stream _s;
			content[_pos].set_imgname(_str);
			///////////////////////////////////////////////////////
			getData(1)->clear();
			for(i=0;i<count;i++){
				getData(1)->push(content[i].get_imgoffset());
				getData(1)->push(content[i].get_imgsize());
				_s.allocate(512);
				_s.pushString(content[i].get_imgname());
				while(_s.getLen()<256){
					_s.push((b8)0);
				}
				_s.nameMask();
				getData(1)->pushStream(_s, 256);
				_s.release();
			}
			//////////////////////////////////////////////
			getData(0)->getSHA256(_s,*getData(1));
			getData(2)->clear();
			getData(2)->pushStream(_s, 32);
			_s.release();
			///////////////////////////////////////////////
			return true;
		}
		break;
	default:
		//////////////////////////////////////////////////
		//缺省
		//////////////////////////////////////////////////
		{
			return false;
		}
		break;
	}
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
IMGobject::~IMGobject(){
	data1.release();
	data2.release();
	data3.release();
	data4.release();
}
bool IMGobject::create(IMGversion ver){
	return invoke(CREATE, (void*)&ver);
}
bool IMGobject::load(const stream &_s){
	return invoke(LOAD, (void*)&_s);
}
bool IMGobject::make(stream &_s){
	return invoke(MAKE, (void*)&_s);
}
bool IMGobject::release(){
	return invoke(RELEASE);
}
bool IMGobject::PICparaModify(i32 pos, i32 term, i32 val){
	return invoke(SETPARA, (void*)&pos, (void*)&term, (void*)&val);
}
bool IMGobject::PICpush(const PICinfo &obj, const stream &_s){
	return invoke(PUSH, (void*)&obj, (void*)&_s);
}
bool IMGobject::PICinsert(i32 pos, const PICinfo &obj, const stream &_s){
	return invoke(INSERT, (void*)&pos, (void*)&obj, (void*)&_s);
}
bool IMGobject::PICremove(i32 pos){
	return invoke(REMOVE, (void*)&pos);
}
bool IMGobject::PICreplace(i32 pos, const PICinfo &obj, const stream &_s){
	return invoke(REPLACE, (void*)&pos, (void*)&obj, (void*)&_s);
}
bool IMGobject::PICextract(i32 pos, matrix &mat, i32 clrPos){
	return invoke(EXTRACT, (void*)&pos, (void*)&mat, (void*)&clrPos);
}
bool IMGobject::PICpreprocess(const matrix &mat, stream &s, PICinfo &obj){
	return invoke(PREPROCESS, (void*)&mat, (void*)&s, (void*)&obj);
}
bool IMGobject::convertTo(IMGversion newVer, IMGobject &imgObj, i32 paletteID){
	return invoke(CONVERT, (void*)&newVer, (void*)&imgObj, (void*)&paletteID);
}
bool IMGobject::loadFile(str fileName){
	stream _data;
	_data.loadFile(fileName);
	load(_data);
	_data.release();
	return 1;
}
bool IMGobject::saveFile(str fileName){
	stream _data;
	make(_data);
	_data.makeFile(fileName);
	_data.release();
	return 1;
}
b64 IMGobject::getSize() const{
	return data1.getLen()+data2.getLen()+data3.getLen()+data4.getLen();
}
pstream IMGobject::getData(b8 _part){
	switch(_part){
	case 0:
		return &data1;
	case 1:
		return &data2;
	case 2:
		return &data3;
	case 3:
		return &data4;
	default:
		return &data1;
	}
}
bool IMGobject::PICInfo(b32 pos, PICinfo& obj){
	if(pos>=count)
		return false;
	obj = content[pos];
	return true;
}
bool IMGobject::PICData(b32 pos, stream& data){
	if(pos>=count)
		return false;
	b64 offset = 0;
	b64 size = (b64)content[pos].get_dataSize();
	if(size == 0)
		return false;
	if(!PICDataOffset(pos, offset))
		return false;
	data4.ptMoveTo(offset);
	data4.readStream(data, size);
	return true;
}
bool IMGobject::PICInfoOffset(b32 pos, b64 &off){
	if(pos>=count)
		return false;
	off = 0;
	for(i32 i=0;i<pos;i++){
		if(content[i].get_format() == LINK){
			off += 8;
		}else if(content[i].get_format() < LINK){
			off += 36;
		}else{
			//V5的某些特例
			off += 64;
		}
	}
	return true;
}
bool IMGobject::PICDataOffset(b32 pos, b64 &off){
	if(pos>=count)
		return false;
	off = 0;
	i32 i;
	if(version == V5){
		for(i=0;i<DDScontent.size();i++){
			off += DDScontent[i].get_lengthOfCompressed();
		}
	}
	for(i=0;i<pos;i++){
		if(content[i].get_format() < LINK){
			off += content[i].get_dataSize();
		}
	}
	return true;
}
bool IMGobject::DDSInfo(b32 pos, DDSinfo& obj){
	if(version != V5)
		return false;
	if(pos>=count)
		return false;
	obj = DDScontent[pos];
	return true;
}
bool IMGobject::DDSData(b32 pos, stream& data){
	if(version != V5)
		return false;
	if(pos>=count)
		return false;
	b64 offset = 0;
	b64 size = (b64)DDScontent[pos].get_lengthOfCompressed();
	if(!DDSDataOffset(pos, offset))
		return false;
	data4.ptMoveTo(offset);
	data4.readStream(data, size);
	return true;
}
bool IMGobject::DDSInfoOffset(b32 pos, b64 &off){
	if(version != V5)
		return false;
	if(pos>=count)
		return false;
	return 3+pos*7;
}
bool IMGobject::DDSDataOffset(b32 pos, b64 &off){
	if(version != V5)
		return false;
	if(pos>=count)
		return false;
	off = 0;
	for(i32 i=0;i<pos;i++){
		off += DDScontent[i].get_lengthOfCompressed();
	}
	return true;
}
i32 IMGobject::linkFind(b32 pos, b32 depth){
	PICinfo pi;
	PICInfo(pos, pi);
	if(depth == 0){
		return -1;
	}else{
		if(pi.get_format() == LINK){
			return linkFind(pi.get_linkTo(), depth-1);
		}else{
			return pos;
		}
	}
}
bool IMGobject::invoke(b16 cmdcode, void *para1, void *para2, void *para3){
	IMGversion ver = IMGversion(cmdcode >> 8);
	b8 cmd = cmdcode & 0xFF;
	switch(ver){
		////////////////////////////////////////////////////
		//缺省版本替换
		////////////////////////////////////////////////////
	case VUDEF:
		switch(cmd){
		case CREATE:
			{
				IMGversion _ver = *(IMGversion*)para1;
				if(_ver != V1 && _ver != V2 && _ver != V4 && _ver != V5 && _ver != V6 && _ver != OGG)
					return false;
				return invoke(CREATE | _ver<<8, para1, para2, para3);
			}
			break;
		case LOAD:
			{
				stream _data(*(stream*)para1);
				b32 _dword;
				getData(0)->reallocate(64);
				_data.ptMoveTo(0);
				_data.readStream(*(getData(0)), 32);
				_data.ptMoveTo(0);
				str sz = _data.readString(20);
				if(sz == "Neople Img File"){
					_data.ptMove(-4);
					_data.read(_dword);
					indexSize = _dword;
				}else if(sz == "Neople Image File"){
					indexSize = -1;
				}else{
					return false;
				}
				_data.ptMove(4);
				_data.read(_dword);
				version = (IMGversion)_dword;
				_data.read(_dword);
				count = _dword;
				/////////////////////////////////////////////////////
				//切换到有ver定义的情形
				/////////////////////////////////////////////////////
				b16 newcmd = (b16)cmd;
				b8 newver = (b8)(version);
				return invoke((newver<<8) | newcmd, para1, para2, para3);
			}
			break;
		default:
			{
				b16 newcmd = (b16)cmd;
				b8 newver = (b8)(version);
				if(newver == 0)
					return false;
				return invoke((newver<<8) | newcmd, para1, para2, para3);
			}
			break;
		}
		break;
		///////////////////////////////////////////
		//IMG version 2
		///////////////////////////////////////////
	case V2:
		switch(cmd){
		case CREATE:
			////////////////////////////////////////////////
			//创建空的数据
			//para1:版本，已在缺省模式下定义为2，因此无意义
			//para2:无意义
			//para3:无意义
			////////////////////////////////////////////////
			{
				indexSize = 0;
				version = V2;
				count = 0;
				content.clear();
				getData(0)->allocate(64);
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				getData(2)->allocate(10);
				getData(3)->allocate(10);
				return true;
			}
			break;
		case LOAD:
			////////////////////////////////////////////////
			//读取数据
			//para1:(stream*)数据流
			//para2:无意义
			//para3:无意义
			////////////////////////////////////////////////
			{
				stream _data(*(stream*)para1);			//源数据
				b32 _dword;								//暂存无符号整型
				i32 _int,_int1,_int2,i;					//暂存有符号整型
				PICinfo _po;							//暂存图片信息
				_data.ptMoveTo(32);
				getData(2)->reallocate(36*(count+10));
				_data.readStream(*(getData(2)), indexSize);
				getData(3)->reallocate(_data.getLen());
				_data.readStream(*(getData(3)), _data.getLen());
				_data.ptMoveTo(32);
				content.clear();
				for(i=0;i<count;i++){
					_data.read(_dword);
					_po.set_format((colorFormat)_dword);
					if(_dword == LINK){
						_data.read(_int);
						_po.set_linkTo(_int);
						_po.set_comp((compressType)0);
						_po.set_picSize(size(0,0));
						_po.set_dataSize(0);
						_po.set_basePt(point(0,0));
						_po.set_frmSize(size(0,0));
					}else{
						_po.set_linkTo(-1);
						_data.read(_dword);
						_po.set_comp((compressType)_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_picSize(size(_int1, _int2));
						_data.read(_dword);
						_po.set_dataSize(_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_basePt(point(_int1, _int2));
						_data.read(_int1);
						_data.read(_int2);
						_po.set_frmSize(size(_int1, _int2));
					}
					content.push_back(_po);
				}
				return true;
			}//load
			break;
		case MAKE:
			////////////////////////////////////////////////
			//转换成流
			//para1: stream & 存储流
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				stream *_ps = (stream*)para1;
				b32 len1 = getData(0)->getLen();
				b32 len3 = getData(2)->getLen();
				b32 len4 = getData(3)->getLen();
				_ps->allocate(len1 + len3 +len4 + 100);
				_ps->pushStream(*getData(0), len1);
				_ps->pushStream(*getData(2), len3);
				_ps->pushStream(*getData(3), len4);
				return true;
			}//make
			break;
		case PUSH:
			////////////////////////////////////////////////
			//插入数据
			//para1: const PICinfo & 图像信息结构
			//para2: const stream & 图像数据
			//para3: 无意义
			////////////////////////////////////////////////
			{
				PICinfo _po = *(PICinfo*)para1;
				stream _data;
				if(para2){
					_data = (*(stream*)para2);
				}
				stream _s;
				content.push_back(_po);
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->pushStream(_s, 8);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->pushStream(_s, 36);
					getData(3)->pushStream(_data, _po.get_dataSize());
				}
				count ++;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//push
			break;
		case RELEASE:
			////////////////////////////////////////////////
			//释放
			//para1: 无意义
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				derived = NULL;
				version = VUDEF;
				count = 0;
				indexSize = 0;
				paletteData.clear();
				content.clear();
				getData(0)->release();
				getData(2)->release();
				getData(3)->release();
				return true;
			}
			break;
		case SETPARA:
			////////////////////////////////////////////////
			//设置INDEX的参数
			//para1: i32 位置，-1则为结尾处
			//para2: i32 要设置的参数：0.LINK_TO，1.基准X坐标，2.基准Y坐标，3.帧域宽，4.帧域高
			//para3: const i32 & 设置成……
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				i32 _term = *(i32*)para2;
				i32 _val = *(i32*)para3;
				b64 _off;
				PICinfo _po;
				PICInfo(_pos, _po);
				PICInfoOffset(_pos, _off);
				if(_po.get_format() == LINK){
					if(_term != 0){
						return false;
					}else if(_val <0 || _val >_count - 1 || content[_val].get_format() == LINK){
						return false;
					}else{
						content[_pos].set_linkTo(_val);
						getData(2)->modify(_off+4, _val);
						return true;
					}
				}else{
					switch(_term){
					case 1:
						content[_pos].set_basePt(point(_val, _po.get_basePt().get_Y()));
						getData(2)->modify(_off+20, _val);
						return true;
						break;
					case 2:
						content[_pos].set_basePt(point(_po.get_basePt().get_X(), _val));
						getData(2)->modify(_off+24, _val);
						return true;
						break;
					case 3:
						content[_pos].set_frmSize(size(_val, _po.get_frmSize().get_H()));
						getData(2)->modify(_off+28, _val);
						return true;
						break;
					case 4:
						content[_pos].set_frmSize(size(_po.get_frmSize().get_W(), _val));
						getData(2)->modify(_off+32, _val);
						return true;
						break;
					default:
						return false;
						break;
					}
				}
				return false;
			}
		case INSERT:
			////////////////////////////////////////////////
			//插入数据
			//para1: i32 位置，-1则为结尾处
			//para2: const PICinfo & 图像信息结构
			//para3: const stream & 图像数据
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += (_count + 1);
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count){
					return false;
				}
				if(_pos == _count){
					return invoke(PUSH, para2, para3);
				}
				PICinfo _po = *(PICinfo*)para2;
				stream _data;
				if(para3){
					_data = (*(stream*)para3);
				}
				content.insert(content.begin() + _pos, _po);
				stream _s;
				b64 _offset;
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				//处理INDEX
				PICInfoOffset(_pos, _offset);
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->insertStream(_s, 8, _offset);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->insertStream(_s, 36, _offset);
				}
				//处理图像数据
				PICDataOffset(_pos, _offset);
				if(_po.get_format() != LINK){
					getData(3)->insertStream(_data, _po.get_dataSize(), _offset);
				}
				count ++;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//insert
			break;
		case REMOVE:
			////////////////////////////////////////////////
			//删除数据
			//para1: i32 位置，-1则为结尾处
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _po = content[_pos];
				content.erase(content.begin() + _pos);
				b64 _offset;
				//处理INDEX
				PICInfoOffset(_pos, _offset);
				if(_po.get_format() == LINK){
					getData(2)->deleteStream(_offset, 8);
				}else{
					getData(2)->deleteStream(_offset, 36);
				}
				//处理图像数据
				PICDataOffset(_pos, _offset);
				if(_po.get_format() != LINK){
					getData(3)->deleteStream(_offset, _po.get_dataSize());
				}
				count --;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//REMOVE
			break;
		case REPLACE:
			////////////////////////////////////////////////
			//替换数据
			//para1: i32 位置，-1则为结尾处
			//para2: const PICinfo & 图像信息结构
			//para3: const stream & 图像数据
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _po = *(PICinfo*)para2;			//待添加的PIC对象
				PICinfo _po2 = content[_pos];			//待删除的PIC对象
				content[_pos] = _po;
				stream _data;
				if(para3){
					_data = (*(stream*)para3);
				}
				stream _s;
				b64 _offset;
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				PICInfoOffset(_pos, _offset);
				if(_po2.get_format() == LINK){
					getData(2)->deleteStream(_offset, 8);
				}else{
					getData(2)->deleteStream(_offset, 36);
				}
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->insertStream(_s, 8, _offset);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->insertStream(_s, 36, _offset);
				}
				PICDataOffset(_pos, _offset);
				if(_po2.get_format() != LINK){
					getData(3)->deleteStream(_offset, _po2.get_dataSize());
				}
				if(_po.get_format() != LINK){
					getData(3)->insertStream(_data, _po.get_dataSize(), _offset);
				}
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//replace
			break;
		case EXTRACT:
			////////////////////////////////////////////////
			//替换数据
			//para1: i32 位置，-1则为结尾处
			//para2: matrix & 像素矩阵
			//para3: 无意义
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _pi;
				stream _s, _s1;
				PICInfo(_pos, _pi);
				if(_pi.get_format() == LINK){
					_pos = linkFind(_pos);
				}
				PICData(_pos, _s);
				_s.uncompressData(_s1, _pi.get_comp());
				matrix *_pmat = (matrix *)para2;
				_pmat->allocate(_pi.get_picSize().get_H(), _pi.get_picSize().get_W()); 
				_pmat->push(_s1, _pi.get_format());
				return true;
			}
			break;
		case PREPROCESS:
			////////////////////////////////////////////////
			//para1: const matrix & 输入矩阵
			//para2: stream & 输出流
			//para3: PICinfo & 输出PIC结构
			////////////////////////////////////////////////
			{
				matrix _mat = *(matrix*)para1;
				stream* _s = (stream*)para2;
				PICinfo* _obj = (PICinfo*)para3;
				stream s1;
				_mat.make(s1);
				s1.compressData(*_s, COMP_ZLIB);
				_obj->set_comp(COMP_ZLIB);
				_obj->set_format(ARGB8888);
				_obj->set_dataSize(_s->getLen());
				_obj->set_linkTo(-1);
				_obj->set_picSize(size(_mat.getColumnCount(), _mat.getRowCount()));
				return true;
			}//preprocess
			break;
		case CONVERT:
			////////////////////////////////////////////////
			//para1: IMGversion 要转换的版本
			//para2: IMGobject & 待存储的IMG数据结构，要未初始化的
			//para3: i32 调色板内的颜色表项ID，V4里无用
			//IMGversion newVer, IMGobject &imgObj, i32 paletteID
			////////////////////////////////////////////////
			{
				IMGversion _ver = *(IMGversion*)para1;
				IMGobject* _obj = (IMGobject*)para2;
				switch(_ver){
				case V2:
					{
						bool ret = true;
						i32 i,j;
						stream _s;
						matrix _mat;
						PICinfo _pi;
						ret &= _obj->create(_ver);
						for(i=0;i<count;i++){
							ret &= PICInfo(i,_pi);
							if(_pi.get_format() == LINK){
								ret &= _obj->PICpush(_pi,NULL);
							}else{
								ret &= PICextract(i, _mat);
								ret &= _obj->PICpreprocess(_mat, _s, _pi);
								ret &= _obj->PICpush(_pi,_s);
								_mat.release();
								_s.release();
							}
						}
						return ret;
					}
					break;
				case V4:
					{
						bool ret = true;
						i32 i,j;
						stream _s;
						matrix _mat;
						PICinfo _pi;
						ret &=  _obj->create(_ver);
						for(i=0;i<count;i++){
							ret &=  PICInfo(i,_pi);
							if(_pi.get_format() == LINK){
								ret &=  _obj->PICpush(_pi,NULL);
							}else{
								ret &=  PICextract(i, _mat);
								ret &=  _obj->PICpreprocess(_mat, _s, _pi);
								ret &=  _obj->PICpush(_pi,_s);
								_mat.release();
								_s.release();
							}
						}
						return ret;
					}
				default:
					return false;
					break;
				}
				return true;
			}
			break;
		default:
			////////////////////////////////////////////////
			//para1: 无意义
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				return false;
			}//default
			break;
		}//switch(cmd)
		break;
	case V4:
		switch(cmd){
		case CREATE:
			////////////////////////////////////////////////
			//创建空的数据
			//para1:版本，已在缺省模式下定义为4，因此无意义
			//para2:无意义
			//para3:无意义
			////////////////////////////////////////////////
			{
				indexSize = 0;
				version = V4;
				count = 0;
				content.clear();
				//色表
				lcolor _colorList;	
				paletteData.clear();
				_colorList.clear();
				paletteData.push(_colorList);
				getData(0)->allocate(64);
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				getData(1)->allocate(10);
				getData(1)->push((b32)0);
				getData(2)->allocate(10);
				getData(3)->allocate(10);
				return true;
			}
			break;
		case LOAD:
			////////////////////////////////////////////////
			//读取数据
			//para1:(stream*)数据流
			//para2:无意义
			//para3:无意义
			////////////////////////////////////////////////
			{
				stream _data(*(stream*)para1);			//源数据
				b32 _dword;								//暂存无符号整型
				i32 _int,_int1,_int2,i,_byteCount;		//暂存有符号整型
				PICinfo _po;							//暂存图片信息
				i32 _colorCount;						//颜色数目
				lcolor _colorList;						//调色板
				paletteData.clear();
				_data.ptMoveTo(32);
				_data.read(_dword);
				_colorCount = _dword;
				_colorList.clear();
				for(i=0;i<_colorCount;i++){
					_data.read(_dword);
					_colorList.push_back(color(_dword, V4_FMT));
				}
				paletteData.push(_colorList);
				_byteCount = _data.ptPos()-32;
				_data.ptMoveTo(32);
				getData(1)->reallocate(_byteCount+1000);
				_data.readStream(*(getData(1)),_byteCount);
				getData(2)->reallocate(36*(count+10));
				_data.readStream(*(getData(2)), indexSize);
				getData(3)->reallocate(_data.getLen());
				_data.readStream(*(getData(3)), _data.getLen());
				_data.ptMoveTo(32+_byteCount);
				content.clear();
				for(i=0;i<count;i++){
					_data.read(_dword);
					_po.set_format((colorFormat)_dword);
					if(_dword == LINK){
						_data.read(_int);
						_po.set_linkTo(_int);
						_po.set_comp((compressType)0);
						_po.set_picSize(size(0,0));
						_po.set_dataSize(0);
						_po.set_basePt(point(0,0));
						_po.set_frmSize(size(0,0));
					}else{
						_po.set_linkTo(-1);
						_data.read(_dword);
						_po.set_comp((compressType)_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_picSize(size(_int1, _int2));
						_data.read(_dword);
						_po.set_dataSize(_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_basePt(point(_int1, _int2));
						_data.read(_int1);
						_data.read(_int2);
						_po.set_frmSize(size(_int1, _int2));
					}
					content.push_back(_po);
				}
				return true;
			}//load
			break;
		case MAKE:
			////////////////////////////////////////////////
			//转换成流
			//para1: stream & 存储流
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				stream *_ps = (stream*)para1;
				b32 len1 = getData(0)->getLen();
				b32 len2 = getData(1)->getLen();
				b32 len3 = getData(2)->getLen();
				b32 len4 = getData(3)->getLen();
				_ps->allocate(len1 + len2 + len3 +len4 + 100);
				_ps->pushStream(*getData(0), len1);
				_ps->pushStream(*getData(1), len2);
				_ps->pushStream(*getData(2), len3);
				_ps->pushStream(*getData(3), len4);
				return true;
			}//make
			break;
		case RELEASE:
			////////////////////////////////////////////////
			//释放
			//para1: 无意义
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				derived = NULL;
				version = VUDEF;
				count = 0;
				indexSize = 0;
				paletteData.clear();
				content.clear();
				getData(0)->release();
				getData(1)->release();
				getData(2)->release();
				getData(3)->release();
				return true;
			}
			break;
		case SETPARA:
			////////////////////////////////////////////////
			//设置INDEX的参数
			//para1: i32 位置，-1则为结尾处
			//para2: i32 要设置的参数：0.LINK_TO，1.基准X坐标，2.基准Y坐标，3.帧域宽，4.帧域高
			//para3: const i32 & 设置成……
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				i32 _term = *(i32*)para2;
				i32 _val = *(i32*)para3;
				b64 _off;
				PICinfo _po;
				PICInfo(_pos, _po);
				PICInfoOffset(_pos, _off);
				if(_po.get_format() == LINK){
					if(_term != 0){
						return false;
					}else if(_val <0 || _val >_count - 1 || content[_val].get_format() == LINK){
						return false;
					}else{
						content[_pos].set_linkTo(_val);
						getData(2)->modify(_off+4, _val);
						return true;
					}
				}else{
					switch(_term){
					case 1:
						content[_pos].set_basePt(point(_val, _po.get_basePt().get_Y()));
						getData(2)->modify(_off+20, _val);
						return true;
						break;
					case 2:
						content[_pos].set_basePt(point(_po.get_basePt().get_X(), _val));
						getData(2)->modify(_off+24, _val);
						return true;
						break;
					case 3:
						content[_pos].set_frmSize(size(_val, _po.get_frmSize().get_H()));
						getData(2)->modify(_off+28, _val);
						return true;
						break;
					case 4:
						content[_pos].set_frmSize(size(_po.get_frmSize().get_W(), _val));
						getData(2)->modify(_off+32, _val);
						return true;
						break;
					default:
						return false;
						break;
					}
				}
				return false;
			}
		case PUSH:
			////////////////////////////////////////////////
			//插入数据
			//para1: const PICinfo & 图像信息结构
			//para2: const stream & 图像数据
			//para3: 无意义
			////////////////////////////////////////////////
			{
				PICinfo _po = *(PICinfo*)para1;
				stream _data;
				if(para2){
					_data = (*(stream*)para2);
				}
				stream _s;
				content.push_back(_po);
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->pushStream(_s, 8);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->pushStream(_s, 36);
					getData(3)->pushStream(_data, _po.get_dataSize());
				}
				count ++;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//push
			break;
		case INSERT:
			////////////////////////////////////////////////
			//插入数据
			//para1: i32 位置，-1则为结尾处
			//para2: const PICinfo & 图像信息结构
			//para3: const stream & 图像数据
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += (_count + 1);
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count){
					return false;
				}
				if(_pos == _count){
					return invoke(PUSH, para2, para3);
				}
				PICinfo _po = *(PICinfo*)para2;
				stream _data;
				if(para3){
					_data = (*(stream*)para3);
				}
				content.insert(content.begin() + _pos, _po);
				stream _s;
				b64 _offset;
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				//处理INDEX
				PICInfoOffset(_pos, _offset);
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->insertStream(_s, 8, _offset);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->insertStream(_s, 36, _offset);
				}
				//处理图像数据
				PICDataOffset(_pos, _offset);
				if(_po.get_format() != LINK){
					getData(3)->insertStream(_data, _po.get_dataSize(), _offset);
				}
				count ++;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//insert
			break;
		case REMOVE:
			////////////////////////////////////////////////
			//删除数据
			//para1: i32 位置，-1则为结尾处
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _po = content[_pos];
				content.erase(content.begin() + _pos);
				b64 _offset;
				//处理INDEX
				PICInfoOffset(_pos, _offset);
				if(_po.get_format() == LINK){
					getData(2)->deleteStream(_offset, 8);
				}else{
					getData(2)->deleteStream(_offset, 36);
				}
				//处理图像数据
				PICDataOffset(_pos, _offset);
				if(_po.get_format() != LINK){
					getData(3)->deleteStream(_offset, _po.get_dataSize());
				}
				count --;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//REMOVE
			break;
		case REPLACE:
			////////////////////////////////////////////////
			//替换数据
			//para1: i32 位置，-1则为结尾处
			//para2: const PICinfo & 图像信息结构
			//para3: const stream & 图像数据
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _po = *(PICinfo*)para2;				//待添加的PIC对象
				PICinfo _po2 = content[_pos];			//待删除的PIC对象
				content[_pos] = _po;
				stream _data;
				if(para3){
					_data = (*(stream*)para3);
				}
				stream _s;
				b64 _offset;
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				PICInfoOffset(_pos, _offset);
				if(_po2.get_format() == LINK){
					getData(2)->deleteStream(_offset, 8);
				}else{
					getData(2)->deleteStream(_offset, 36);
				}
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->insertStream(_s, 8, _offset);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->insertStream(_s, 36, _offset);
				}
				PICDataOffset(_pos, _offset);
				if(_po2.get_format() != LINK){
					getData(3)->deleteStream(_offset, _po2.get_dataSize());
				}
				if(_po.get_format() != LINK){
					getData(3)->insertStream(_data, _po.get_dataSize(), _offset);
				}
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//replace
			break;
		case EXTRACT:
			////////////////////////////////////////////////
			//替换数据
			//para1: i32 位置，-1则为结尾处
			//para2: matrix & 像素矩阵
			//para3: 无意义
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				i32 i;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _pi;
				stream _s, _s1;
				PICInfo(_pos, _pi);
				if(_pi.get_format() == LINK){
					_pos = linkFind(_pos);
				}
				PICInfo(_pos, _pi);
				PICData(_pos, _s);
				_s.uncompressData(_s1, _pi.get_comp());
				matrix *_pmat = (matrix *)para2;
				_pmat->allocate(_pi.get_picSize().get_H(), _pi.get_picSize().get_W());
				for(i=0;i<_s1.getLen();i++){
					_pmat->push(paletteData[0][_s1[i]]);
				}
				return true;
			}
			break;
		case PREPROCESS:
			////////////////////////////////////////////////
			//para1: const matrix & 输入矩阵
			//para2: stream & 输出流
			//para3: PICinfo & 输出PIC结构
			////////////////////////////////////////////////
			{
				matrix _mat = *(matrix*)para1;
				stream* _s = (stream*)para2;
				PICinfo* _obj = (PICinfo*)para3;
				//先扩充调色板
				lcolor _cl;
				i32 i;
				_mat.getElemCountList(_cl);
				if(!paletteData.joinWith(_cl)){
					//调色板信息已满
					return false;
				}
				getData(1)->release();
				paletteData.tinyMake(*getData(1));
				stream s1(_mat.getElemCount()+100);
				for(i=0;i<_mat.getElemCount();i++){
					s1.push((b8)paletteData.findColor(_mat.getElem(i)));
				}
				s1.compressData(*_s, COMP_ZLIB);
				_obj->set_comp(COMP_ZLIB);
				_obj->set_format(ARGB1555);//其实是0x0E，在V4里表示的并不是ARGB1555，但是暂时借用了。
				_obj->set_dataSize(_s->getLen());
				_obj->set_linkTo(-1);
				_obj->set_picSize(size(_mat.getColumnCount(), _mat.getRowCount()));
				return true;
			}//preprocess
		case CONVERT:
			////////////////////////////////////////////////
			//para1: IMGversion 要转换的版本
			//para2: IMGobject & 待存储的IMG数据结构，要未初始化的
			//para3: i32 调色板内的颜色表项ID，V4里无用
			//IMGversion newVer, IMGobject &imgObj, i32 paletteID
			////////////////////////////////////////////////
			{
				IMGversion _ver = *(IMGversion*)para1;
				IMGobject* _obj = (IMGobject*)para2;
				switch(_ver){
				case V2:
					{
						bool ret = true;
						i32 i,j;
						stream _s;
						matrix _mat;
						PICinfo _pi;
						ret &= _obj->create(_ver);
						for(i=0;i<count;i++){
							ret &= PICInfo(i,_pi);
							if(_pi.get_format() == LINK){
								ret &= _obj->PICpush(_pi,NULL);
							}else{
								ret &= PICextract(i, _mat);
								ret &= _obj->PICpreprocess(_mat, _s, _pi);
								ret &= _obj->PICpush(_pi,_s);
								_mat.release();
								_s.release();
							}
						}
						return ret;
					}
					break;
				case V4:
					{
						bool ret = true;
						i32 i,j;
						stream _s;
						matrix _mat;
						PICinfo _pi;
						ret &=  _obj->create(_ver);
						for(i=0;i<count;i++){
							ret &=  PICInfo(i,_pi);
							if(_pi.get_format() == LINK){
								ret &=  _obj->PICpush(_pi,NULL);
							}else{
								ret &=  PICextract(i, _mat);
								ret &=  _obj->PICpreprocess(_mat, _s, _pi);
								ret &=  _obj->PICpush(_pi,_s);
								_mat.release();
								_s.release();
							}
						}
						return ret;
					}
				default:
					return false;
					break;
				}
				return true;
			}
			break;
		default:
			////////////////////////////////////////////////
			//预留
			//para1: 无意义
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				return false;
			}//default
			break;
		}//switch(cmd)
		break;
	case V5:
		switch(cmd){
		case LOAD:
			////////////////////////////////////////////////
			//读取数据
			//para1:(stream*)数据流
			//para2:无意义
			//para3:无意义
			////////////////////////////////////////////////
			{
				stream _data(*(stream*)para1);			//源数据
				b32 _dword;								//暂存无符号整型
				i32 _int,_int1,_int2,i,j;				//暂存有符号整型
				i32 _byteCount,_byteCount2;				//暂存有符号整型2
				PICinfo _po;							//暂存图片信息
				DDSinfo _di;							//暂存DDS信息
				i32 _ddsCount;							//DDS数目
				i32 _clrCount;
				lcolor _colorList;
				paletteData.clear();
				_data.ptMoveTo(32);
				/////////////////////////////////////////////////////////
				//V5专用
				_data.read(_dword);
				_ddsCount = _dword;						//V5专用：DDS图片个数
				_data.read(_dword);
				totalLength_usedByV5 = _dword;			//数值上等于IMG的总长度
				_data.read(_dword);
				_clrCount = _dword;						//颜色表数据
				_colorList.clear();
				for(i=0;i<_clrCount;i++){
					_data.read(_dword);
					_colorList.push_back(color(_dword, V4_FMT));
				}
				paletteData.push(_colorList);
				/////////////////////////////////////////////////////////
				//第一组不明意义的表
				DDScontent.clear();
				for(i=0;i<_ddsCount;i++){		//不知道是与V5DATA.COUNT有关还是INDEX数目有关，先尝试
					_data.read(_dword);
					_di.set_reserved(_dword);
					_data.read(_dword);
					_di.set_fourCCID((DDSPixelFormatID)_dword);
					_data.read(_dword);
					_di.set_DDSID(_dword);
					_data.read(_dword);
					_di.set_lengthOfCompressed(_dword);
					_data.read(_dword);
					_di.set_lengthOfDDS(_dword);
					_data.read(_dword);
					_di.set_width(_dword);
					_data.read(_dword);
					_di.set_height(_dword);
					DDScontent.push_back(_di);
				}
				_byteCount = _data.ptPos()-32;		//功能区字节数
				_data.ptMoveTo(32);
				getData(1)->reallocate(_byteCount+1000);
				_data.readStream(*(getData(1)),_byteCount);
				/////////////////////////////////////////////////////
				//此处才是INDEX开始，但是INDEX与V2V4V6格式不是很相同
				//必须使用第一字节进行区分，
				//第一字节小于LINK的话，与V2V4V6的图片帧INDEX相同，都是36字节
				//第一字节等于LINK还是2字节
				//第一字节大于LINK则是V5特有的INDEX格式，为64字节
				//V5特有的INDEX格式比V2V4V6少了个图片数据长度（4字节）、
				//多了个参数（据说与DDS有关）以及两个坐标点（总计20字节）、
				//还有12个空字节，所以是36-4+20+12=64字节
				_data.ptMoveTo(32+_byteCount);
				content.clear();
				for(i=0;i<count;i++){
					_data.read(_dword);
					_po.set_format((colorFormat)_dword);
					if(_dword == LINK){
						_data.read(_int);
						_po.set_linkTo(_int);

						_po.set_comp((compressType)0);
						_po.set_picSize(size(0,0));
						_po.set_dataSize(0);
						_po.set_basePt(point(0,0));
						_po.set_frmSize(size(0,0));
						
						_po.set_DDSIDused(0);
						_po.set_DDSpointLT(point(0,0));
						_po.set_DDSpointRB(point(0,0));
					}else if(_dword<LINK){
						_po.set_linkTo(-1);

						_data.read(_dword);
						_po.set_comp((compressType)_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_picSize(size(_int1, _int2));
						_data.read(_dword);
						_po.set_dataSize(_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_basePt(point(_int1, _int2));
						_data.read(_int1);
						_data.read(_int2);
						_po.set_frmSize(size(_int1, _int2));

						_po.set_DDSIDused(0);
						_po.set_DDSpointLT(point(0,0));
						_po.set_DDSpointRB(point(0,0));
					}else{
						_po.set_linkTo(-1);

						_data.read(_dword);
						_po.set_comp((compressType)_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_picSize(size(_int1, _int2));
						_data.read(_dword);
						_po.set_dataSize(_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_basePt(point(_int1, _int2));
						_data.read(_int1);
						_data.read(_int2);
						_po.set_frmSize(size(_int1, _int2));
						_data.read(_dword);
						_data.read(_dword);
						_po.set_DDSIDused(_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_DDSpointLT(point(_int1,_int2));
						_data.read(_int1);
						_data.read(_int2);
						_po.set_DDSpointRB(point(_int1,_int2));
						_data.read(_dword);
					}
					content.push_back(_po);
				}
				_byteCount2 = _data.ptPos()-32-_byteCount;		//功能区字节数
				_data.ptMoveTo(32+_byteCount);
				getData(2)->reallocate(_byteCount2+1000);
				_data.readStream(*(getData(2)), _byteCount2);
				//////////////////////////////////////////////////////
				//数据区
				getData(3)->reallocate(_data.getLen());
				_data.readStream(*(getData(3)), _data.getLen());
				return true;
			}//load
			break;
		case EXTRACT:
			////////////////////////////////////////////////
			//提取数据
			//para1: i32 位置，-1则为结尾处
			//para2: matrix & 像素矩阵
			//para3: 无意义
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				matrix *_pmat = (matrix *)para2;
				b32 _count = count;
				i32 i;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _pi;
				DDSinfo _di;
				stream _s, _s1;
				matrix _mat;
				PICInfo(_pos, _pi);
				if(_pi.get_format() == LINK){
					_pos = linkFind(_pos);
				}
				PICInfo(_pos, _pi);
				if(_pi.get_format() > LINK){
					DDSInfo(_pi.get_DDSIDused(), _di);
					DDSData(_pi.get_DDSIDused(), _s);
					_s.uncompressData(_s1, COMP_ZLIB);
					KoishiDDS::DDS _d(_s1);
					_d.uncompress(_mat);
					b32 _it = _pi.get_DDSpointLT().get_Y();
					b32 _ib = _pi.get_DDSpointRB().get_Y()-1;
					b32 _il = _pi.get_DDSpointLT().get_X();
					b32 _ir = _pi.get_DDSpointRB().get_X()-1;
					_mat.getSubMatrix(*_pmat, _it, _ib, _il, _ir);
				}else{
					PICData(_pos, _s);
					_s.uncompressData(_s1, _pi.get_comp());
					_pmat->allocate(_pi.get_picSize().get_H(), _pi.get_picSize().get_W()); 
					_pmat->push(_s1, _pi.get_format());
				}
				return true;
			}//extract
			break;
		default:
			////////////////////////////////////////////////
			//预留
			//para1: 无意义
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				return false;
			}//default
			break;
		}
		break;
	case V1:
		break;
	case V6:
		switch(cmd){
		case CREATE:
			////////////////////////////////////////////////
			//创建空的数据
			//para1:版本，已在缺省模式下定义为4，因此无意义
			//para2:无意义
			//para3:无意义
			////////////////////////////////////////////////
			{
				indexSize = 0;
				version = V6;
				count = 0;
				content.clear();
				//色表
				lcolor _colorList;	
				paletteData.clear();
				getData(0)->allocate(64);
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				getData(1)->allocate(10);
				getData(1)->push((b32)0);
				getData(2)->allocate(10);
				getData(3)->allocate(10);
				return true;
			}
			break;
		case LOAD:
			////////////////////////////////////////////////
			//读取数据
			//para1:(stream*)数据流
			//para2:无意义
			//para3:无意义
			////////////////////////////////////////////////
			{
				stream _data(*(stream*)para1);			//源数据
				b32 _dword;								//暂存无符号整型
				i32 _int,_int1,_int2,i,j,_byteCount;	//暂存有符号整型
				PICinfo _po;							//暂存图片信息
				i32 _colorListCount,_subCount;			//暂存颜色表数和颜色数
				lcolor _colorList;						//调色板
				paletteData.clear();
				_data.ptMoveTo(32);
				_data.read(_dword);
				_colorListCount = _dword;
				for(i=0;i<_colorListCount;i++){
					_data.read(_dword);
					_subCount = _dword;
					_colorList.clear();
					for(j=0;j<_subCount;j++){
						_data.read(_dword);
						_colorList.push_back(color(_dword, V4_FMT));
					}
					paletteData.push(_colorList);
				}
				_byteCount = _data.ptPos() - 32;
				_data.ptMoveTo(32);
				getData(1)->reallocate(sizeof(b32)*100+_byteCount);
				_data.readStream(*(getData(1)),_byteCount);
				getData(2)->reallocate(36*(count+10));
				_data.readStream(*(getData(2)), indexSize);
				getData(3)->reallocate(_data.getLen());
				_data.readStream(*(getData(3)), _data.getLen());
				_data.ptMoveTo(32+_byteCount);
				content.clear();
				for(i=0;i<count;i++){
					_data.read(_dword);
					_po.set_format((colorFormat)_dword);
					if(_dword == LINK){
						_data.read(_int);
						_po.set_linkTo(_int);
						_po.set_comp((compressType)0);
						_po.set_picSize(size(0,0));
						_po.set_dataSize(0);
						_po.set_basePt(point(0,0));
						_po.set_frmSize(size(0,0));
					}else{
						_po.set_linkTo(-1);
						_data.read(_dword);
						_po.set_comp((compressType)_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_picSize(size(_int1, _int2));
						_data.read(_dword);
						_po.set_dataSize(_dword);
						_data.read(_int1);
						_data.read(_int2);
						_po.set_basePt(point(_int1, _int2));
						_data.read(_int1);
						_data.read(_int2);
						_po.set_frmSize(size(_int1, _int2));
					}
					content.push_back(_po);
				}
				return true;
			}//load
			break;
		case MAKE:
			////////////////////////////////////////////////
			//转换成流
			//para1: stream & 存储流
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				stream *_ps = (stream*)para1;
				b32 len1 = getData(0)->getLen();
				b32 len2 = getData(1)->getLen();
				b32 len3 = getData(2)->getLen();
				b32 len4 = getData(3)->getLen();
				_ps->allocate(len1 + len2 + len3 +len4 + 100);
				_ps->pushStream(*getData(0), len1);
				_ps->pushStream(*getData(1), len2);
				_ps->pushStream(*getData(2), len3);
				_ps->pushStream(*getData(3), len4);
				return true;
			}//make
			break;
		case RELEASE:
			////////////////////////////////////////////////
			//释放
			//para1: 无意义
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				derived = NULL;
				version = VUDEF;
				count = 0;
				indexSize = 0;
				paletteData.clear();
				content.clear();
				getData(0)->release();
				getData(1)->release();
				getData(2)->release();
				getData(3)->release();
				return true;
			}
			break;
		case SETPARA:
			////////////////////////////////////////////////
			//设置INDEX的参数
			//para1: i32 位置，-1则为结尾处
			//para2: i32 要设置的参数：0.LINK_TO，1.基准X坐标，2.基准Y坐标，3.帧域宽，4.帧域高
			//para3: const i32 & 设置成……
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				i32 _term = *(i32*)para2;
				i32 _val = *(i32*)para3;
				b64 _off;
				PICinfo _po;
				PICInfo(_pos, _po);
				PICInfoOffset(_pos, _off);
				if(_po.get_format() == LINK){
					if(_term != 0){
						return false;
					}else if(_val <0 || _val >_count - 1 || content[_val].get_format() == LINK){
						return false;
					}else{
						content[_pos].set_linkTo(_val);
						getData(2)->modify(_off+4, _val);
						return true;
					}
				}else{
					switch(_term){
					case 1:
						content[_pos].set_basePt(point(_val, _po.get_basePt().get_Y()));
						getData(2)->modify(_off+20, _val);
						return true;
						break;
					case 2:
						content[_pos].set_basePt(point(_po.get_basePt().get_X(), _val));
						getData(2)->modify(_off+24, _val);
						return true;
						break;
					case 3:
						content[_pos].set_frmSize(size(_val, _po.get_frmSize().get_H()));
						getData(2)->modify(_off+28, _val);
						return true;
						break;
					case 4:
						content[_pos].set_frmSize(size(_po.get_frmSize().get_W(), _val));
						getData(2)->modify(_off+32, _val);
						return true;
						break;
					default:
						return false;
						break;
					}
				}
				return false;
			}
		case PUSH:
			////////////////////////////////////////////////
			//插入数据
			//para1: const PICinfo & 图像信息结构
			//para2: const stream & 图像数据
			//para3: 无意义
			////////////////////////////////////////////////
			{
				PICinfo _po = *(PICinfo*)para1;
				stream _data;
				if(para2){
					_data = (*(stream*)para2);
				}
				stream _s;
				content.push_back(_po);
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->pushStream(_s, 8);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->pushStream(_s, 36);
					getData(3)->pushStream(_data, _po.get_dataSize());
				}
				count ++;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//push
			break;
		case INSERT:
			////////////////////////////////////////////////
			//插入数据
			//para1: i32 位置，-1则为结尾处
			//para2: const PICinfo & 图像信息结构
			//para3: const stream & 图像数据
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += (_count + 1);
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count){
					return false;
				}
				if(_pos == _count){
					return invoke(PUSH, para2, para3);
				}
				PICinfo _po = *(PICinfo*)para2;
				stream _data;
				if(para3){
					_data = (*(stream*)para3);
				}
				content.insert(content.begin() + _pos, _po);
				stream _s;
				b64 _offset;
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				//处理INDEX
				PICInfoOffset(_pos, _offset);
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->insertStream(_s, 8, _offset);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->insertStream(_s, 36, _offset);
				}
				//处理图像数据
				PICDataOffset(_pos, _offset);
				if(_po.get_format() != LINK){
					getData(3)->insertStream(_data, _po.get_dataSize(), _offset);
				}
				count ++;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//insert
			break;
		case REMOVE:
			////////////////////////////////////////////////
			//删除数据
			//para1: i32 位置，-1则为结尾处
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _po = content[_pos];
				content.erase(content.begin() + _pos);
				b64 _offset;
				//处理INDEX
				PICInfoOffset(_pos, _offset);
				if(_po.get_format() == LINK){
					getData(2)->deleteStream(_offset, 8);
				}else{
					getData(2)->deleteStream(_offset, 36);
				}
				//处理图像数据
				PICDataOffset(_pos, _offset);
				if(_po.get_format() != LINK){
					getData(3)->deleteStream(_offset, _po.get_dataSize());
				}
				count --;
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//REMOVE
			break;
		case REPLACE:
			////////////////////////////////////////////////
			//替换数据
			//para1: i32 位置，-1则为结尾处
			//para2: const PICinfo & 图像信息结构
			//para3: const stream & 图像数据
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				b32 _count = count;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				PICinfo _po = *(PICinfo*)para2;				//待添加的PIC对象
				PICinfo _po2 = content[_pos];			//待删除的PIC对象
				content[_pos] = _po;
				stream _data;
				if(para3){
					_data = (*(stream*)para3);
				}
				stream _s;
				b64 _offset;
				_s.allocate(50);
				_s.push((b32)_po.get_format());
				PICInfoOffset(_pos, _offset);
				if(_po2.get_format() == LINK){
					getData(2)->deleteStream(_offset, 8);
				}else{
					getData(2)->deleteStream(_offset, 36);
				}
				if(_po.get_format() == LINK){
					_s.push(_po.get_linkTo());
					getData(2)->insertStream(_s, 8, _offset);
				}else{
					_s.push((b32)_po.get_comp());
					_s.push(_po.get_picSize().get_W());
					_s.push(_po.get_picSize().get_H());
					if(_po.get_dataSize()>_data.getLen()){
						_po.set_dataSize(_data.getLen());
					}
					_s.push(_po.get_dataSize());
					_s.push(_po.get_basePt().get_X());
					_s.push(_po.get_basePt().get_Y());
					_s.push(_po.get_frmSize().get_W());
					_s.push(_po.get_frmSize().get_H());
					getData(2)->insertStream(_s, 36, _offset);
				}
				PICDataOffset(_pos, _offset);
				if(_po2.get_format() != LINK){
					getData(3)->deleteStream(_offset, _po2.get_dataSize());
				}
				if(_po.get_format() != LINK){
					getData(3)->insertStream(_data, _po.get_dataSize(), _offset);
				}
				indexSize = getData(2)->getLen();
				getData(0)->clear();
				getData(0)->pushString("Neople Img File");
				getData(0)->push((b8)0);
				getData(0)->push((b32)(indexSize));
				getData(0)->push((b32)0);
				getData(0)->push((b32)(version));
				getData(0)->push((b32)(count));
				return true;
			}//replace
			break;
		case EXTRACT:
			////////////////////////////////////////////////
			//替换数据
			//para1: i32 位置，-1则为结尾处
			//para2: matrix & 像素矩阵
			//para3: i32 clrPos 调色板位置
			////////////////////////////////////////////////
			{
				i32 _pos = *(i32*)para1;
				i32 _clrPos;
				if(!para3){
					_clrPos = 0;
				}else{
					_clrPos = *(i32*)para3;
				}
				b32 _count = count;
				i32 i;
				if(_pos<0){
					_pos += _count;
				}
				if(_pos<0){
					return false;
				}
				if(_pos>_count - 1){
					return false;
				}
				if(_clrPos<0){
					return false;
				}
				if(_clrPos>=paletteData.getCount()){
					return false;
				}
				PICinfo _pi;
				stream _s, _s1;
				PICInfo(_pos, _pi);
				if(_pi.get_format() == LINK){
					_pos = linkFind(_pos);
				}
				PICInfo(_pos, _pi);
				PICData(_pos, _s);
				_s.uncompressData(_s1, _pi.get_comp());
				matrix *_pmat = (matrix *)para2;
				_pmat->allocate(_pi.get_picSize().get_H(), _pi.get_picSize().get_W());
				for(i=0;i<_s1.getLen();i++){
					_pmat->push(paletteData[_clrPos][_s1[i]]);
				}
				return true;
			}
			break;
		case CONVERT:
			////////////////////////////////////////////////
			//转换数据
			//para1: version 转换后版本
			//para2: IMGlist & 转换后的IMG对象序列
			//para3: 颜色方案
			////////////////////////////////////////////////
			{
				IMGversion _ver = *(IMGversion*)para1;
				IMGobject* _obj = (IMGobject*)para2;
				i32 _cp = *(i32*)para3;
				switch(_ver){
				case V2:
					{
						bool ret = true;
						i32 i,j;
						stream _s;
						matrix _mat;
						PICinfo _pi;
						ret &= _obj->create(_ver);
						for(i=0;i<count;i++){
							ret &= PICInfo(i,_pi);
							if(_pi.get_format() == LINK){
								ret &= _obj->PICpush(_pi,NULL);
							}else{
								ret &= PICextract(i, _mat, _cp);
								ret &= _obj->PICpreprocess(_mat, _s, _pi);
								ret &= _obj->PICpush(_pi,_s);
								_mat.release();
								_s.release();
							}
						}
						return ret;
					}
					break;
				case V4:
					{
						bool ret = true;
						i32 i,j;
						stream _s;
						PICinfo _pi;
						ret &=  _obj->create(_ver);
						for(i=0;i<count;i++){
							ret &=  PICInfo(i,_pi);
							if(_pi.get_format() == LINK){
								ret &= _obj->PICpush(_pi,NULL);
							}else{
								ret &= PICData(i, _s);
								ret &= _obj->PICpush(_pi, _s);
								_s.release();
							}
						}
						_obj->paletteData.clear();
						_obj->paletteData.push(paletteData[_cp]);
						_obj->getData(1)->release();
						_obj->paletteData.tinyMake(*(_obj->getData(1)));
						return ret;
					}
				default:
					return false;
					break;
				}
				return true;
			}
			break;
		default:
			////////////////////////////////////////////////
			//预留
			//para1: 无意义
			//para2: 无意义
			//para3: 无意义
			////////////////////////////////////////////////
			{
				return false;
			}//default
			break;
		}//switch(cmd)
		break;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////