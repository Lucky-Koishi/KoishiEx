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
	return obj.Load(temps);
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
			getData(1)->allocate(264*count);
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
			getData(1)->release();
			getData(1)->allocate(count*400);
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
			_io.Make(_s);
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
			getData(1)->release();
			getData(1)->allocate(count*400);
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
			_io.Make(_s);
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
			getData(1)->release();
			getData(1)->allocate(count*400);
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
			getData(1)->release();
			getData(1)->allocate(count*400);
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
			_io.Make(_s);
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

IMGobject::IMGobject(){
	Release();
}
IMGobject::IMGobject(stream &s){
	Release();
	Load(s);
}
IMGobject::IMGobject(const str &fileName){
	Release();
	LoadFile(fileName);
}
IMGobject::~IMGobject(){
	Release();
}
bool IMGobject::LoadFile(str fileName){
	bool result = true;
	stream s;
	result &= s.loadFile(fileName);
	result &= Load(s);
	s.release();
	return result;
}
bool IMGobject::SaveFile(str fileName){
	bool result = true;
	stream s;
	result &= Make(s);
	result &= s.makeFile(fileName);
	s.release();
	return result;
}
bool IMGobject::Load(stream &s){
	bool result = true;
	////////////////////////////////////////////
	str sz;
	i32 num1,num2;
	b32 dword, i, j;
	b64 ptStart, ptEnd;
	ptStart = 0;
	s.ptMoveTo(0);
	sz = s.readString(20);
	if(sz == "Neople Img File"){
		s.ptMove(-4);
		s.read(dword);
		indexSize = dword;
	}else if(sz == "Neople Image File"){
		indexSize = -1;
	}else{
		return false;
	}
	s.ptMove(4);
	s.read(dword);
	version = (IMGversion)dword;
	if(version != V2 && version != V4 && version != V5 && version != V6)
		return false;
	s.read(dword);
	indexCount = dword;
	if(version == V5){
		s.read(dword);
		V5_DDSCount = dword;
		s.read(dword);
		V5_totalLength = dword;
	}
	ptEnd = s.ptPos();
	s.ptMoveTo(ptStart);
	getData(1)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(1), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	//////////////////////////////////////////
	b32 clrCount = 0;
	b32 pleCount = 0;
	lcolor clrList;
	if(version == V4 || version == V5){
		s.read(clrCount);
		clrList.clear();
		for(i=0;i<clrCount;i++){
			s.read(dword);
			clrList.push_back(color(dword,V4_FMT));
		}
		paletteData.clear();
		paletteData.push(clrList);
	}
	if(version == V6){
		s.read(pleCount);
		for(i=0;i<pleCount;i++){
			s.read(clrCount);
			clrList.clear();
			for(j=0;j<clrCount;j++){
				s.read(dword);
				clrList.push_back(color(dword, V4_FMT));
			}
			paletteData.push(clrList);
		}
	}
	ptEnd = s.ptPos();
	s.ptMoveTo(ptStart);
	getData(2)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(2), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	//////////////////////////////////////
	DDSinfo di;
	DDScontent.clear();
	if(version == V5){
		for(i=0;i<V5_DDSCount;i++){
			s.read(dword);
			di.set_reserved(dword);
			s.read(dword);
			di.set_fourCCID((DDSPixelFormatID)dword);
			s.read(dword);
			di.set_DDSID(dword);
			s.read(dword);
			di.set_lengthOfCompressed(dword);
			s.read(dword);
			di.set_lengthOfDDS(dword);
			s.read(dword);
			di.set_width(dword);
			s.read(dword);
			di.set_height(dword);
			DDScontent.push_back(di);
		}
	}
	ptEnd = s.ptPos();
	s.ptMoveTo(ptStart);
	getData(3)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(3), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	///////////////////////////////////////
	PICinfo pi;
	PICcontent.clear();
	if(version != V1){
		for(i=0;i<indexCount;i++){
			s.read(dword);
			pi.set_format((colorFormat)dword);
			if(dword == LINK){
				s.read(num1);
				pi.set_linkTo(num1);

				pi.set_comp((compressType)0);
				pi.set_picSize(size(0,0));
				pi.set_dataSize(0);
				pi.set_basePt(point(0,0));
				pi.set_frmSize(size(0,0));
						
				pi.set_DDSIDused(0);
				pi.set_DDSpointLT(point(0,0));
				pi.set_DDSpointRB(point(0,0));
			}else if(dword<LINK){
				pi.set_linkTo(-1);

				s.read(dword);
				pi.set_comp((compressType)dword);
				s.read(num1);
				s.read(num2);
				pi.set_picSize(size(num1, num2));
				s.read(dword);
				pi.set_dataSize(dword);
				s.read(num1);
				s.read(num2);
				pi.set_basePt(point(num1, num2));
				s.read(num1);
				s.read(num2);
				pi.set_frmSize(size(num1, num2));

				pi.set_DDSIDused(0);
				pi.set_DDSpointLT(point(0,0));
				pi.set_DDSpointRB(point(0,0));
			}else{
				pi.set_linkTo(-1);

				s.read(dword);
				pi.set_comp((compressType)dword);
				s.read(num1);
				s.read(num2);
				pi.set_picSize(size(num1, num2));
				s.read(dword);
				pi.set_dataSize(dword);
				s.read(num1);
				s.read(num2);
				pi.set_basePt(point(num1, num2));
				s.read(num1);
				s.read(num2);
				pi.set_frmSize(size(num1, num2));
				s.read(dword);
				s.read(dword);
				pi.set_DDSIDused(dword);
				s.read(num1);
				s.read(num2);
				pi.set_DDSpointLT(point(num1,num2));
				s.read(num1);
				s.read(num2);
				pi.set_DDSpointRB(point(num1,num2));
				s.read(dword);
			}
			PICcontent.push_back(pi);
		}
	}
	ptEnd = s.ptPos();
	s.ptMoveTo(ptStart);
	getData(4)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(4), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	///////////////////////////////////////
	b64 fsize = 0;
	for(i=0;i<DDScontent.size();i++){
		fsize += DDScontent[i].get_lengthOfCompressed();
	}
	getData(5)->allocate(s.getLen());
	s.readStream(*getData(5), fsize);
	///////////////////////////////////////
	getData(6)->allocate(s.getLen());
	s.readStream(*getData(6), s.getLen());
	return result;
}
bool IMGobject::Make(stream &s){
	b64 len1 = getData(1)->getLen();
	b64 len2 = getData(2)->getLen();
	b64 len3 = getData(3)->getLen();
	b64 len4 = getData(4)->getLen();
	b64 len5 = getData(5)->getLen();
	b64 len6 = getData(6)->getLen();
	s.allocate(len1 + len2 + len3 + len4 + len5 + len6 + 1000);
	s.pushStream(*getData(1), len1);
	s.pushStream(*getData(2), len2);
	s.pushStream(*getData(3), len3);
	s.pushStream(*getData(4), len4);
	s.pushStream(*getData(5), len5);
	s.pushStream(*getData(6), len6);
	return true;
}
bool IMGobject::Create(IMGversion ver){
	if(ver != V2 && ver != V4 && ver != V5 && ver != V6)
		return false;
	Release();
	version = ver;
	if(ver == V4 || ver == V5){
		lcolor clrList;
		clrList.clear();
		paletteData.push(clrList);
	}
	getData(1)->allocate(1024);
	getData(1)->pushString("Neople Img File");
	getData(1)->push((b8)0);
	getData(1)->push((b32)(indexSize));
	getData(1)->push((b32)0);
	getData(1)->push((b32)(ver));
	getData(1)->push((b32)(indexCount));
	if(ver == V5){
		V5_totalLength = 44;
		getData(1)->push(V5_DDSCount);
		getData(1)->push(V5_totalLength);
	}
	getData(2)->allocate(1024);
	if(ver == V4 || ver == V5 || ver == V6){
		getData(2)->push((b32)0);
	}
	getData(3)->allocate(1024);
	getData(4)->allocate(1024);
	getData(5)->allocate(1024);
	getData(6)->allocate(1024);
	return true;
}
bool IMGobject::Release(){
	data1.release();
	data2.release();
	data3.release();
	data4.release();
	data5.release();
	data6.release();
	derived = NULL;
	version = VUDEF;
	indexCount = 0;
	indexSize = 0;
	V5_DDSCount = 0;
	V5_totalLength = 0;
	paletteData.clear();
	DDScontent.clear();
	PICcontent.clear();
	return true;
}
bool IMGobject::GetPICInfo(i32 pos, PICinfo &info){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	info = PICcontent[pos];
	return true;
}
bool IMGobject::GetPICInfoOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	off = 0;
	for(i32 i=0;i<pos;i++){
		if(PICcontent[i].get_format() == LINK){
			off += 8;
		}else if(PICcontent[i].get_format() < LINK){
			off += 36;
		}else{
			off += 64;
		}
	}
	return true;
}
bool IMGobject::GetPICData(i32 pos, stream &s){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	b64 size = (b64)PICcontent[pos].get_dataSize();
	b64 offset;
	if(size == 0)
		return false;
	if(!GetPICDataOffset(pos, offset))
		return false;
	data6.ptMoveTo(offset);
	data6.readStream(s, size);
	return false;
}
bool IMGobject::GetPICDataOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	i32 i;
	off = 0;
	for(i=0;i<pos;i++){
		if(PICcontent[i].get_format() < LINK){
			off += (b64)PICcontent[i].get_dataSize();
		}
	}
	return true;
}
bool IMGobject::GetDDSInfo(i32 pos, DDSinfo &info){
	if(pos<0)
		return false;
	if(pos>=V5_DDSCount)
		return false;
	info = DDScontent[pos];
	return true;
}
bool IMGobject::GetDDSInfoOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=V5_DDSCount)
		return false;
	off = 0;
	for(i32 i=0;i<pos;i++){
		off += 28;
	}
	return true;
}
bool IMGobject::GetDDSData(i32 pos, stream &s){
	if(pos<0)
		return false;
	if(pos>=V5_DDSCount)
		return false;
	b64 offset;
	b64 size = (b64)DDScontent[pos].get_lengthOfCompressed();
	if(size == 0)
		return false;
	if(!GetDDSDataOffset(pos, offset))
		return false;
	getData(5)->ptMoveTo(offset);
	getData(5)->readStream(s, size);
	return true;
}
bool IMGobject::GetDDSDataOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=V5_DDSCount)
		return false;
	i32 i;
	off = 0;
	for(i=0;i<pos;i++){
		off += (b64)DDScontent[i].get_lengthOfCompressed();
	}
	return true;
}
bool IMGobject::SetPICInfoPara(i32 pos, i32 term, void *pval){
	//Term: 0. linkTo 1. basePoint 2.frameSize 3.DDSID 4.pointLT, 5.pointRB
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	i32 i = *(i32*)pval;
	size sz = *(size*)pval;
	point pt = *(point*)pval;
	PICinfo pi;
	DDSinfo di;
	b64 off;
	GetPICInfo(pos, pi);
	GetPICInfoOffset(pos, off);
	if(pi.get_format() == LINK){
		switch(term){
		case 0:
			if(i<0 || i>indexCount-1)
				return false;
			if(PICcontent[i].get_format() == LINK)
				return false;
			PICcontent[pos].set_linkTo(i);
			getData(4)->modify(off+4, i);
			return true;
		default:
			return false;
		}
	}else if(pi.get_format() < LINK){
		switch(term){
		case 1:
			PICcontent[pos].set_basePt(pt);
			getData(4)->modify(off+20, pt.get_X());
			getData(4)->modify(off+24, pt.get_Y());
			return true;
		case 2:
			PICcontent[pos].set_frmSize(sz);
			getData(4)->modify(off+28, sz.get_W());
			getData(4)->modify(off+32, sz.get_H());
			return true;
		default:
			return false;
		}
	}else/*if(_pi.get_format() > LINK)*/{
		GetDDSInfo(pi.get_DDSIDused(), di);
		switch(term){
		case 1:
			PICcontent[pos].set_basePt(pt);
			getData(4)->modify(off+20, pt.get_X());
			getData(4)->modify(off+24, pt.get_Y());
			return true;
		case 2:
			PICcontent[pos].set_frmSize(sz);
			getData(4)->modify(off+28, sz.get_W());
			getData(4)->modify(off+32, sz.get_H());
			return true;
		case 3:
			if(i<0 || i>=DDScontent.size())
				return false;
			PICcontent[pos].set_DDSIDused(i);
			getData(4)->modify(off+40, i);
			return true;
		case 4:
			if(pt.get_X()<0 || pt.get_X()>pi.get_DDSpointRB().get_X()){
				return false;
			}
			if(pt.get_Y()<0 || pt.get_Y()>pi.get_DDSpointRB().get_Y()){
				return false;
			}
			sz = size(pi.get_DDSpointRB().get_X()-pt.get_X(),
				pi.get_DDSpointRB().get_Y()-pt.get_Y());
			PICcontent[pos].set_DDSpointLT(pt);
			PICcontent[pos].set_picSize(sz);
			getData(4)->modify(off+8,  sz.get_W());
			getData(4)->modify(off+12, sz.get_H());
			getData(4)->modify(off+44, pt.get_X());
			getData(4)->modify(off+48, pt.get_Y());
			return true;
		case 5:
			if(pt.get_X()>di.get_width()-1 || pt.get_X()<pi.get_DDSpointLT().get_X()){
				return false;
			}
			if(pt.get_Y()>di.get_height()-1 || pt.get_Y()<pi.get_DDSpointLT().get_Y()){
				return false;
			}
			sz = size(pt.get_X()-pi.get_DDSpointLT().get_X(),
				pt.get_Y()-pi.get_DDSpointLT().get_Y());
			PICcontent[pos].set_DDSpointRB(pt);
			PICcontent[pos].set_picSize(sz);
			getData(4)->modify(off+8, sz.get_W());
			getData(4)->modify(off+12,sz.get_H());
			getData(4)->modify(off+52, pt.get_X());
			getData(4)->modify(off+56, pt.get_Y());
			return true;
		default:
			return false;
		}
	}
	return true;
}
bool IMGobject::PICpush(const PICinfo &info, const stream &s){
	PICcontent.push_back(info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push((b32)info.get_format());
	if(info.get_format() == LINK){
		sTemp.push(info.get_linkTo());
		getData(4)->pushStream(sTemp, 8);
	}else if(info.get_format() < LINK){
		sTemp.push((b32)info.get_comp());
		sTemp.push(info.get_picSize().get_W());
		sTemp.push(info.get_picSize().get_H());
		sTemp.push(info.get_dataSize());
		sTemp.push(info.get_basePt().get_X());
		sTemp.push(info.get_basePt().get_Y());
		sTemp.push(info.get_frmSize().get_W());
		sTemp.push(info.get_frmSize().get_H());
		getData(4)->pushStream(sTemp, 36);
		getData(6)->pushStream(s, info.get_dataSize());
	}else{
		sTemp.push((b32)info.get_comp());
		sTemp.push(info.get_picSize().get_W());
		sTemp.push(info.get_picSize().get_H());
		sTemp.push((b32)0);
		sTemp.push(info.get_basePt().get_X());
		sTemp.push(info.get_basePt().get_Y());
		sTemp.push(info.get_frmSize().get_W());
		sTemp.push(info.get_frmSize().get_H());
		sTemp.push((b32)0);
		sTemp.push(info.get_DDSIDused());
		sTemp.push(info.get_DDSpointLT().get_X());
		sTemp.push(info.get_DDSpointLT().get_Y());
		sTemp.push(info.get_DDSpointRB().get_X());
		sTemp.push(info.get_DDSpointRB().get_Y());
		sTemp.push((b32)0);
		getData(4)->pushStream(sTemp, 64);
	}
	//////////////////////////////////////////////////////////////////
	indexCount ++;
	indexSize = getData(4)->getLen();
	V5_totalLength = getSize();
	getData(1)->modify(16, (i32)indexSize);
	getData(1)->modify(28, (i32)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (i32)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICinsert(i32 pos, const PICinfo &info, const stream &s){
	if(pos<0)
		pos += (indexCount + 1);
	if(pos<0)
		return false;
	if(pos>indexCount)
		return false;
	if(pos == indexCount)
		return PICpush(info, s);
	b64 off1, off2;
	GetPICInfoOffset(pos, off1);
	GetPICDataOffset(pos, off2);
	PICcontent.insert(PICcontent.begin()+pos, info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push((b32)info.get_format());
	if(info.get_format() == LINK){
		sTemp.push(info.get_linkTo());
		getData(4)->insertStream(sTemp, 8, off1);
	}else if(info.get_format() < LINK){
		sTemp.push((b32)info.get_comp());
		sTemp.push(info.get_picSize().get_W());
		sTemp.push(info.get_picSize().get_H());
		sTemp.push(info.get_dataSize());
		sTemp.push(info.get_basePt().get_X());
		sTemp.push(info.get_basePt().get_Y());
		sTemp.push(info.get_frmSize().get_W());
		sTemp.push(info.get_frmSize().get_H());
		getData(4)->insertStream(sTemp, 36, off1);
		getData(6)->insertStream(s, info.get_dataSize(), off2);
	}else{
		sTemp.push((b32)info.get_comp());
		sTemp.push(info.get_picSize().get_W());
		sTemp.push(info.get_picSize().get_H());
		sTemp.push((b32)0);
		sTemp.push(info.get_basePt().get_X());
		sTemp.push(info.get_basePt().get_Y());
		sTemp.push(info.get_frmSize().get_W());
		sTemp.push(info.get_frmSize().get_H());
		sTemp.push((b32)0);
		sTemp.push(info.get_DDSIDused());
		sTemp.push(info.get_DDSpointLT().get_X());
		sTemp.push(info.get_DDSpointLT().get_Y());
		sTemp.push(info.get_DDSpointRB().get_X());
		sTemp.push(info.get_DDSpointRB().get_Y());
		sTemp.push((b32)0);
		getData(4)->insertStream(sTemp, 64, off1);
	}
	//////////////////////////////////////////////////////////////////
	indexCount ++;
	indexSize = getData(4)->getLen();
	V5_totalLength = getSize();
	getData(1)->modify(16, (i32)indexSize);
	getData(1)->modify(28, (i32)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (i32)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICremove(i32 pos){
	if(pos<0)
		pos += indexCount;
	if(pos<0)
		return false;
	if(pos>indexCount - 1)
		return false;
	PICinfo pi;
	b64 off1,off2;
	GetPICInfo(pos, pi);
	GetPICInfoOffset(pos, off1);
	GetPICDataOffset(pos, off2);
	PICcontent.erase(PICcontent.begin()+pos);
	if(pi.get_format() == LINK){
		getData(4)->deleteStream(off1, 8);
	}else if(pi.get_format() < LINK){
		getData(4)->deleteStream(off1, 36);
		getData(6)->deleteStream(off2, pi.get_dataSize());
	}else{
		getData(4)->deleteStream(off1, 64);
	}
	//////////////////////////////////////////////////////////////////
	indexCount --;
	indexSize = getData(4)->getLen();
	V5_totalLength = getSize();
	getData(1)->modify(16, (i32)indexSize);
	getData(1)->modify(28, (i32)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (i32)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICreplace(i32 pos, const PICinfo &info, const stream &s){
	if(pos<0)
		pos += indexCount;
	if(pos<0)
		return false;
	if(pos>indexCount - 1)
		return false;
	PICinfo pi;			//旧PICinfo
	b64 off1,off2;
	GetPICInfo(pos, pi);
	GetPICInfoOffset(pos, off1);
	GetPICDataOffset(pos, off2);
	PICcontent[pos] = info;
	///////////////////////
	if(pi.get_format() == LINK){
		getData(4)->deleteStream(off1, 8);
	}else if(pi.get_format() < LINK){
		getData(4)->deleteStream(off1, 36);
		getData(6)->deleteStream(off2, pi.get_dataSize());
	}else{
		getData(4)->deleteStream(off1, 64);
	}
	///////////////////////
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push((b32)info.get_format());
	if(info.get_format() == LINK){
		sTemp.push(info.get_linkTo());
		getData(4)->insertStream(sTemp, 8, off1);
	}else if(info.get_format() < LINK){
		sTemp.push((b32)info.get_comp());
		sTemp.push(info.get_picSize().get_W());
		sTemp.push(info.get_picSize().get_H());
		sTemp.push(info.get_dataSize());
		sTemp.push(info.get_basePt().get_X());
		sTemp.push(info.get_basePt().get_Y());
		sTemp.push(info.get_frmSize().get_W());
		sTemp.push(info.get_frmSize().get_H());
		getData(4)->insertStream(sTemp, 36, off1);
		getData(6)->insertStream(s, info.get_dataSize(), off2);
	}else{
		sTemp.push((b32)info.get_comp());
		sTemp.push(info.get_picSize().get_W());
		sTemp.push(info.get_picSize().get_H());
		sTemp.push((b32)0);
		sTemp.push(info.get_basePt().get_X());
		sTemp.push(info.get_basePt().get_Y());
		sTemp.push(info.get_frmSize().get_W());
		sTemp.push(info.get_frmSize().get_H());
		sTemp.push((b32)0);
		sTemp.push(info.get_DDSIDused());
		sTemp.push(info.get_DDSpointLT().get_X());
		sTemp.push(info.get_DDSpointLT().get_Y());
		sTemp.push(info.get_DDSpointRB().get_X());
		sTemp.push(info.get_DDSpointRB().get_Y());
		sTemp.push((b32)0);
		getData(4)->insertStream(sTemp, 64, off1);
	}
	///////////////////////////////////////////
	indexSize = getData(4)->getLen();
	V5_totalLength = getSize();
	getData(1)->modify(16, (i32)indexSize);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (i32)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICextract(i32 pos, matrix &mat, i32 paletteID){
	if(pos<0)
		pos += indexCount;
	if(pos<0)
		return false;
	if(pos>indexCount - 1)
		return false;
	if(version == V4 && paletteData[0].size() == 0)
		return false;
	if(version == V6 && (paletteID < 0 || paletteID >= paletteData.getCount()))
		return false;
	i32 i;
	PICinfo pi;
	DDSinfo di;
	stream sMid, sPic;
	GetPICInfo(pos, pi);
	if(pi.get_format() == LINK){
		pos = linkFind(pos);
	}
	GetPICInfo(pos, pi);
	if(pi.get_format()<LINK){
		GetPICData(pos, sMid);
		sMid.uncompressData(sPic, pi.get_comp());
		switch(version){
		case V2:
			mat.allocate(pi.get_picSize());
			mat.push(sPic, pi.get_format());
			break;
		case V4:
			mat.allocate(pi.get_picSize());
			for(i=0;i<sPic.getLen();i++){
				if(sPic[i]>=paletteData[0].size())
					sPic[i] = 0;
				mat.push(paletteData[0][sPic[i]]);
			}
			break;
		case V5:
			mat.allocate(pi.get_picSize());
			mat.push(sPic, pi.get_format());
			break;
		case V6:
			mat.allocate(pi.get_picSize());
			for(i=0;i<sPic.getLen();i++){
				if(sPic[i]>=paletteData[paletteID].size())
					sPic[i] = 0;
				mat.push(paletteData[paletteID][sPic[i]]);
			}
			break;
		}
	}else if(pi.get_format()>LINK){
		if(pi.get_DDSIDused()>=V5_DDSCount){
			return false;
		}
		GetDDSInfo(pi.get_DDSIDused(), di);
		GetDDSData(pi.get_DDSIDused(), sMid);
		sMid.uncompressData(sPic, pi.get_comp());
		matrix mTemp;
		KoishiDDS::DDS d(sPic);
		d.uncompress(mTemp);
		mTemp.getSubMatrix(mat,
			pi.get_DDSpointLT().get_Y(),
			pi.get_DDSpointRB().get_Y(),
			pi.get_DDSpointLT().get_X(),
			pi.get_DDSpointRB().get_X()
		);
	}
	return true;
}
bool IMGobject::PICpreprocess(const matrix &mat, stream &s, PICinfo &info){
	if(version == V2){
		stream sTemp;
		mat.make(sTemp);
		sTemp.compressData(s, COMP_ZLIB);
		info.set_comp(COMP_ZLIB);
		info.set_format(ARGB8888);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
		return true;
	}
	if(version == V4){
		i32 i;
		lcolor clrList;
		stream sTemp;
		mat.getElemCountList(clrList);
		if(!paletteData.joinWith(clrList)){
			return false;
		}
		getData(2)->release();
		paletteData.tinyMake(*getData(2));
		sTemp.allocate(mat.getElemCount());
		for(i=0;i<mat.getElemCount();i++){
			sTemp.push((b8)paletteData.findColor(mat.getElem(i)));
		}
		sTemp.compressData(s, COMP_ZLIB);
		sTemp.release();
		info.set_comp(COMP_ZLIB);
		info.set_format(ARGB1555);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
		return true;
	}
	if(version == V5){
		stream sTemp;
		DDSinfo di;
		DDSpreprocess(mat, sTemp, di);
		di.set_DDSID(V5_DDSCount);
		DDSpush(di, sTemp);
		info.set_comp(COMP_ZLIB2);
		info.set_format(DDS_DXT5);
		info.set_dataSize(0);
		info.set_linkTo(-1);
		info.set_picSize(size(di.get_width(), di.get_height()));
		info.set_DDSIDused(di.get_DDSID());
		info.set_DDSpointLT(point(0,0));
		info.set_DDSpointRB(point(di.get_width(),di.get_height()));
		return true;
	}
	return false;
}
bool IMGobject::PICempty(stream &s, PICinfo &info){
	switch(version){
	case V2:
		s.allocate(4);
		s.push((b32)0);
		info.set_comp(COMP_NONE);
		info.set_format(ARGB8888);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
		return true;
	case V4:
		s.allocate(1);
		s.push((b8)0);
		info.set_comp(COMP_NONE);
		info.set_format(ARGB1555);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
		return true;
	case V5:
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
		info.set_DDSpointRB(point(
			info.get_DDSpointLT().get_X()+1,
			info.get_DDSpointLT().get_Y()+1
		));
		return true;
	case V6:
		s.allocate(1);
		s.push((b8)0);
		info.set_comp(COMP_NONE);
		info.set_format(ARGB1555);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
		return true;
	}
	return false;
}
bool IMGobject::DDSpush(const DDSinfo &info, const stream &s){
	if(version != V5)
		return false;
	DDScontent.push_back(info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((b32)info.get_fourCCID());
	sTemp.push(info.get_DDSID());
	sTemp.push(info.get_lengthOfCompressed());
	sTemp.push(info.get_lengthOfDDS());
	sTemp.push(info.get_height());
	sTemp.push(info.get_width());
	getData(3)->pushStream(sTemp, 28);
	getData(5)->pushStream(s, info.get_lengthOfCompressed());
	//////////////////////////////////////////////////////////////////
	V5_DDSCount ++;
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_DDSCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::DDSinsert(i32 pos, const DDSinfo &info, const stream &s){
	if(version != V5)
		return false;
	if(pos<0)
		pos += (V5_DDSCount + 1);
	if(pos<0)
		return false;
	if(pos>V5_DDSCount)
		return false;
	if(pos == V5_DDSCount)
		return DDSpush(info, s);
	b64 off1, off2;
	GetDDSInfoOffset(pos, off1);
	GetDDSDataOffset(pos, off2);
	DDScontent.insert(DDScontent.begin()+pos, info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((b32)info.get_fourCCID());
	sTemp.push(info.get_DDSID());
	sTemp.push(info.get_lengthOfCompressed());
	sTemp.push(info.get_lengthOfDDS());
	sTemp.push(info.get_height());
	sTemp.push(info.get_width());
	getData(3)->insertStream(sTemp, 28, off1);
	getData(5)->insertStream(s, info.get_lengthOfCompressed(), off2);
	//////////////////////////////////////////////////////////////////
	V5_DDSCount ++;
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_DDSCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::DDSremove(i32 pos){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_DDSCount;
	if(pos<0)
		return false;
	if(pos>V5_DDSCount-1)
		return false;
	DDSinfo di;
	b64 off1,off2;
	GetDDSInfo(pos, di);
	GetDDSInfoOffset(pos, off1);
	GetDDSInfoOffset(pos, off2);
	DDScontent.erase(DDScontent.begin()+pos);
	getData(3)->deleteStream(off1, 28);
	getData(5)->deleteStream(off2, di.get_lengthOfCompressed());
	//////////////////////////////////////////////////////////////////
	V5_DDSCount --;
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_DDSCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::DDSreplace(i32 pos, const DDSinfo &info, const stream &s){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_DDSCount;
	if(pos<0)
		return false;
	if(pos>V5_DDSCount-1)
		return false;
	DDSinfo di;
	b64 off1,off2;
	GetDDSInfo(pos, di);
	GetDDSInfoOffset(pos, off1);
	GetDDSInfoOffset(pos, off2);
	DDScontent[pos] = info;
	getData(3)->deleteStream(off1, 28);
	getData(5)->deleteStream(off2, di.get_lengthOfCompressed());
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((b32)info.get_fourCCID());
	sTemp.push(info.get_DDSID());
	sTemp.push(info.get_lengthOfCompressed());
	sTemp.push(info.get_lengthOfDDS());
	sTemp.push(info.get_height());
	sTemp.push(info.get_width());
	getData(3)->insertStream(sTemp, 28, off1);
	getData(5)->insertStream(s, info.get_lengthOfCompressed(), off2);
	////////////////////////////////////////
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_DDSCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::DDSextract(i32 pos, matrix &mat){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_DDSCount;
	if(pos<0)
		return false;
	if(pos>V5_DDSCount - 1)
		return false;
	i32 i;
	DDSinfo di;
	stream sMid, sPic;
	GetDDSInfo(pos, di);
	GetDDSData(pos, sMid);
	sMid.uncompressData(sPic, COMP_ZLIB);
	KoishiDDS::DDS d(sPic);
	d.uncompress(mat);
	return true;
}
bool IMGobject::DDSpreprocess(const matrix &mat, stream &s, DDSinfo &info){
	if(version != V5)
		return false;
	stream sTemp;
	KoishiDDS::DDS d;
	d.compress(mat);
	d.make(sTemp);
	sTemp.compressData(s, COMP_ZLIB);
	info.set_reserved(1);
	info.set_fourCCID(DXT5);
	info.set_lengthOfDDS(sTemp.getLen());
	info.set_lengthOfCompressed(s.getLen());
	info.set_width(d.getHeader()->width);
	info.set_height(d.getHeader()->height);
	return true;
}
bool IMGobject::CLRpush(const color &clr, i32 paletteID){
	if(version != V4 && version != V5 && version != V6)
		return false;
	if(version == V6 && (paletteID < 0 || paletteID >= paletteData.getCount()))
		return false;
	if(version != V6)
		paletteID = 0;
	paletteData[paletteID].push_back(clr);
	getData(2)->release();
	if(version != V6)
		paletteData.tinyMake(*getData(2), 0);
	if(version == V6)
		paletteData.bigMake(*getData(2));
	return true;
}
bool IMGobject::CLRinsert(i32 pos, const color &clr, i32 paletteID){
	if(version != V4 && version != V5 && version != V6)
		return false;
	if(version == V6 && (paletteID < 0 || paletteID >= paletteData.getCount()))
		return false;
	if(version != V6)
		paletteID = 0;
	paletteData[paletteID].insert(paletteData[paletteID].begin()+pos, clr);
	getData(2)->release();
	if(version != V6)
		paletteData.tinyMake(*getData(2), 0);
	if(version == V6)
		paletteData.bigMake(*getData(2));
	return true;
}
bool IMGobject::CLRremove(i32 pos, i32 paletteID){
	if(version != V4 && version != V5 && version != V6)
		return false;
	if(version == V6 && (paletteID < 0 || paletteID >= paletteData.getCount()))
		return false;
	if(version != V6)
		paletteID = 0;
	paletteData[paletteID].erase(paletteData[paletteID].begin()+pos);
	getData(2)->release();
	if(version != V6)
		paletteData.tinyMake(*getData(2), 0);
	if(version == V6)
		paletteData.bigMake(*getData(2));
	return true;
}
bool IMGobject::CLRreplace(i32 pos, const color &clr, i32 paletteID){
	if(version != V4 && version != V5 && version != V6)
		return false;
	if(version == V6 && (paletteID < 0 || paletteID >= paletteData.getCount()))
		return false;
	if(version != V6)
		paletteID = 0;
	paletteData[paletteID][pos] = clr;
	getData(2)->release();
	if(version != V6)
		paletteData.tinyMake(*getData(2), 0);
	if(version == V6)
		paletteData.bigMake(*getData(2));
	return true;
}
bool IMGobject::CLRnewPalette(){
	if(version != V6){
		return false;
	}
	lcolor clrList;
	clrList.clear();
	paletteData.push(clrList);
	paletteData.bigMake(*getData(2));
	return true;
}
bool IMGobject::ConvertTo(IMGobject &newIO, IMGversion newVersion, i32 paletteID){
	i32 i;
	PICinfo pi;
	bool result = true;
	matrix mat;
	stream s;
	newIO.Create(newVersion);
	if(version == newVersion){
		newIO = *this;
		return true;
	}else if(version == V4 && newVersion == V6){
		for(i=0;i<indexCount;i++){
			GetPICInfo(i,pi);
			if(pi.get_format() == LINK){
				result &= newIO.PICpush(pi,NULL);
			}else{
				result &= GetPICData(i, s);
				result &= newIO.PICpush(pi, s);
				s.release();
			}
		}
		newIO.paletteData.clear();
		newIO.paletteData.push(paletteData[0]);
		newIO.getData(2)->release();
		newIO.paletteData.bigMake(*(newIO.getData(2)));
		return result;
	}else if(version == V6 && newVersion == V4){
		for(i=0;i<indexCount;i++){
			GetPICInfo(i,pi);
			if(pi.get_format() == LINK){
				result &= newIO.PICpush(pi,NULL);
			}else{
				result &= GetPICData(i, s);
				result &= newIO.PICpush(pi, s);
				s.release();
			}
		}
		newIO.paletteData.clear();
		newIO.paletteData.push(paletteData[paletteID]);
		newIO.getData(2)->release();
		newIO.paletteData.tinyMake(*(newIO.getData(2)));
		return result;
	}else if(newVersion == V6){
		IMGobject midIO;
		result &= ConvertTo(midIO, V4);
		if(!result)
			return false;
		result &= midIO.ConvertTo(newIO, V6);
		return result;
	}else{
		for(i=0;i<indexCount;i++){
			GetPICInfo(i, pi);
			if(pi.get_format() == LINK){
				result &= newIO.PICpush(pi, NULL);
			}else{
				result &= PICextract(i, mat, paletteID);
				result &= newIO.PICpreprocess(mat, s, pi);
				if(!result)
					return false;
				result &= newIO.PICpush(pi, s);
				mat.release();
				s.release();
			}
		}
		return true;
	}
	return false;
}

i32 IMGobject::linkFind(b32 pos, b32 depth){
	PICinfo pi;
	GetPICInfo(pos, pi);
	if(depth == 0){
		return -1;
	}else if(pi.get_format() == LINK){
		return linkFind(pi.get_linkTo(), depth-1);
	}else{
		return pos;
	}
}
stream *IMGobject::getData(b8 _part){
	stream *sList[] = {NULL, &data1, &data2, &data3, &data4, &data5, &data6};
	return sList[_part%7];
}
b64 IMGobject::getSize() const{
	return data1.getLen()+data2.getLen()+data3.getLen()+data4.getLen()+data5.getLen()+data6.getLen();
}
