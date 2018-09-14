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
	TEXusing = 0;
};
TEXinfo::TEXinfo(){
	ID = 0;
	format = COLOR_UDEF;
	height = 0;
	compressedLength = 0;
	dataLength = 0;
	reserved = 1;
	width = 0;
}
NPKobject::NPKobject(){
	release();
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

bool NPKobject::load(const stream &s){
	stream data(s);
	b32 dword;
	i32 i;
	IMGindex ii;
	stream sPath;
	getData(1)->reallocate(24);
	data.ptMoveTo(0);
	data.readStream(*(getData(1)), 20);
	data.ptMoveTo(0);
	if(data.readString(16) != "NeoplePack_Bill"){
		return false;
	}
	data.read(dword);
	count = dword;
	getData(2)->allocate(264*count);
	data.readStream(*(getData(2)), 264*count);
	data.ptMoveTo(20);
	for(i=0;i<count;i++){
		data.read(dword);
		ii.set_imgoffset(dword);
		data.read(dword);
		ii.set_imgsize(dword);
		sPath.allocate(256);
		data.readStream(sPath, 256);
		sPath.nameMask();
		ii.set_imgname((str)sPath);
		sPath.release();
		content.push_back(ii);
	}
	getData(3)->reallocate(32);
	data.readStream(*(getData(3)), 32);
	getData(4)->reallocate(data.getLen());
	data.readStream(*(getData(4)), data.getLen());
	return true;
}
bool NPKobject::make(stream &s){
	b32 len1 = getData(1)->getLen();
	b32 len2 = getData(2)->getLen();
	b32 len3 = getData(3)->getLen();
	b32 len4 = getData(4)->getLen();
	s.allocate(len1 + len2 + len3 +len4 + 100);
	s.pushStream(*getData(1), len1);
	s.pushStream(*getData(2), len2);
	s.pushStream(*getData(3), len3);
	s.pushStream(*getData(4), len4);
	return true;
}
bool NPKobject::create(){
	count = 0;
	content.clear();
	getData(1)->allocate(64);
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((b8)0);
	getData(1)->push((b32)0);
	getData(2)->allocate(64);
	stream s;
	getData(1)->getSHA256(s,*getData(2));
	getData(3)->allocate(64);
	getData(3)->pushStream(s, 32);
	getData(4)->allocate(64);
	return true;
}
bool NPKobject::release(){
	count = 0;
	content.clear();
	getData(1)->release();
	getData(2)->release();
	getData(3)->release();
	getData(4)->release();
	return true;
}
bool NPKobject::loadFile(const str &fileName){
	stream data;
	bool ret1 = data.loadFile(fileName);
	bool ret2 = false;
	if(ret1){
		ret2 = load(data);
	}
	data.release();
	return ret1 && ret2;
}
bool NPKobject::saveFile(const str &fileName){
	stream data;
	bool ret1 = make(data);
	bool ret2 = false;
	if(ret1){
		ret2 = data.makeFile(fileName);
	}
	data.release();
	return ret1 && ret2;
}
bool NPKobject::IMGpush(IMGobject &io, const str &imgName){
	stream s;
	IMGindex ii;
	b32 _dword;
	i32 i;
	ii.set_imgname(imgName);
	ii.set_imgoffset(getSize());
	ii.set_imgsize(io.getSize());
	content.push_back(ii);
	for(i=0;i<content.size();i++){
		_dword = content[i].get_imgoffset();
		content[i].set_imgoffset(_dword+264);
	}
	//////////////////////////////////////////////
	count++;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((b8)0);
	getData(1)->push(count);
	//////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].get_imgoffset());
		getData(2)->push(content[i].get_imgsize());
		s.allocate(512);
		s.pushString(content[i].get_imgname());
		while(s.getLen()<256){
			s.push((b8)0);
		}
		s.nameMask();
		getData(2)->pushStream(s, 256);
		s.release();
	}
	//////////////////////////////////////////////
	getData(1)->getSHA256(s,*getData(2));
	getData(3)->clear();
	getData(3)->pushStream(s, 32);
	s.release();
	//////////////////////////////////////////////
	io.make(s);
	getData(4)->pushStream(s, s.getLen());
	return true;
}
bool NPKobject::IMGinsert(i32 pos, IMGobject &io, const str &imgName){
	if(pos<0){
		pos += (count + 1);
	}
	if(pos<0){
		pos = 0;
	}
	if(pos>count){
		pos = count;
	}
	if(pos == count){
		return IMGpush(io, imgName);
	}
	i32 i;
	stream s;
	IMGindex ii;
	b32 dword;
	b64 offset = content[pos].get_imgoffset() - getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen();
	ii.set_imgname(imgName);
	ii.set_imgoffset(content[pos].get_imgoffset());
	ii.set_imgsize(io.getSize());
	content.insert(content.begin()+pos, ii);
	for(i=0;i<content.size();i++){
		dword = content[i].get_imgoffset();
		dword += 264;
		if(i>pos){
			dword += io.getSize();
		}
		content[i].set_imgoffset(dword);
	}
	//////////////////////////////////////////////
	count++;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((b8)0);
	getData(1)->push(count);
	//////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].get_imgoffset());
		getData(2)->push(content[i].get_imgsize());
		s.allocate(512);
		s.pushString(content[i].get_imgname());
		while(s.getLen()<256){
			s.push((b8)0);
		}
		s.nameMask();
		getData(2)->pushStream(s, 256);
		s.release();
	}
	//////////////////////////////////////////////
	getData(1)->getSHA256(s,*getData(2));
	getData(3)->clear();
	getData(3)->pushStream(s, 32);
	s.release();
	//////////////////////////////////////////////
	io.make(s);
	getData(4)->insertStream(s, s.getLen(),offset);
	return true;
}
bool NPKobject::IMGremove(i32 pos){
	if(pos<0){
		pos += count;
	}
	if(pos<0){
		pos = 0;
	}
	if(pos>count-1){
		pos = count-1;
	}
	i32 i;
	stream s;
	IMGindex ii;
	b32 dword;
	ii = content[pos];
	b64 offset = content[pos].get_imgoffset() - getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen();
	content.erase(content.begin() + pos);
	for(i=0;i<content.size();i++){
		dword = content[i].get_imgoffset();
		dword -= 264;
		if(i>=pos){
			dword -= ii.get_imgsize();
		}
		content[i].set_imgoffset(dword);
	}
	/////////////////////////////////////////////////////
	count --;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((b8)0);
	getData(1)->push(count);
	/////////////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].get_imgoffset());
		getData(2)->push(content[i].get_imgsize());
		s.allocate(512);
		s.pushString(content[i].get_imgname());
		while(s.getLen()<256){
			s.push((b8)0);
		}
		s.nameMask();
		getData(2)->pushStream(s, 256);
		s.release();
	}
	//////////////////////////////////////////////
	getData(1)->getSHA256(s,*getData(2));
	getData(3)->clear();
	getData(3)->pushStream(s, 32);
	s.release();
	//////////////////////////////////////////////
	getData(4)->deleteStream(offset, ii.get_imgsize());
	return true;
}
bool NPKobject::IMGreplace(i32 pos, IMGobject &io){
	if(pos<0){
		pos += count;
	}
	if(pos<0){
		pos = 0;
	}
	if(pos>count){
		pos = count - 1;
	}
	i32 i;
	stream s;
	IMGindex ii;
	b32 dword;
	b64 offset = content[pos].get_imgoffset() - getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen();
	ii = content[pos];
	content[pos].set_imgsize(io.getSize());
	for(i=0;i<content.size();i++){
		if(i>pos){
			dword = content[i].get_imgoffset();
			dword -= ii.get_imgsize();
			dword += io.getSize();
			content[i].set_imgoffset(dword);
		}
	}
	//////////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].get_imgoffset());
		getData(2)->push(content[i].get_imgsize());
		s.allocate(512);
		s.pushString(content[i].get_imgname());
		while(s.getLen()<256){
			s.push((b8)0);
		}
		s.nameMask();
		getData(2)->pushStream(s, 256);
		s.release();
	}
	//////////////////////////////////////////////
	getData(1)->getSHA256(s,*getData(2));
	getData(3)->clear();
	getData(3)->pushStream(s, 32);
	s.release();
	//////////////////////////////////////////////
	io.make(s);
	getData(4)->deleteStream(offset, ii.get_imgsize());
	getData(4)->insertStream(s, s.getLen(), offset);
	return true;
}
bool NPKobject::IMGrename(i32 pos, const str& newName){
	if(pos<0){
		pos += count;
	}
	if(pos<0){
		pos = 0;
	}
	if(pos>count){
		pos = count - 1;
	}
	i32 i;
	stream s;
	content[pos].set_imgname(newName);
	///////////////////////////////////////////////////////
	getData(2)->clear();
	for(i=0;i<count;i++){
		getData(2)->push(content[i].get_imgoffset());
		getData(2)->push(content[i].get_imgsize());
		s.allocate(512);
		s.pushString(content[i].get_imgname());
		while(s.getLen()<256){
			s.push((b8)0);
		}
		s.nameMask();
		getData(2)->pushStream(s, 256);
		s.release();
	}
	//////////////////////////////////////////////
	getData(1)->getSHA256(s,*getData(2));
	getData(3)->clear();
	getData(3)->pushStream(s, 32);
	s.release();
	///////////////////////////////////////////////
	return true;
}
stream *NPKobject::getData(b8 _part){
	stream *sList[] = {NULL, &data1, &data2, &data3, &data4};
	return sList[_part%5];
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
	getData(4)->ptMoveTo(content[pos].get_imgoffset()-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->readStream(temps, (b64)(content[pos].get_imgsize()));
	return obj.load(temps);
}
bool NPKobject::IMGfind(const str &keyword, b32 &pos){
	i32 i = 0;
	for(i=0;i<count;i++){
		if(content[i].get_imgname().find(keyword) != str::npos){
			pos = i;
			return true;
		}
	}
	return false;
}
bool NPKobject::IMGfind(const str &keyword, const str &nonkeyword, b32 &pos){
	i32 i = 0;
	for(i=0;i<count;i++){
		if(content[i].get_imgname().find(keyword) != str::npos && content[i].get_imgname().find(nonkeyword) == str::npos){
			pos = i;
			return true;
		}
	}
	return false;
}
bool NPKobject::extractIMGFile(i32 pos, str fileName){
	if(pos<0 || pos>=count){
		return false;
	}
	stream temps;
	getData(4)->ptMoveTo(content[pos].get_imgoffset()-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->readStream(temps, (b64)(content[pos].get_imgsize()));
	return temps.makeFile(fileName);
}
i32 NPKobject::getVersion(i32 pos){
	i32 r;
	getData(4)->ptMoveTo(content[pos].get_imgoffset()-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->ptMove(24);
	getData(4)->read(r);
	return r;
}
bool NPKobject::loadIndex(const str &fileName, std::vector<IMGversion> &versionList){
	stream data;
	stream s;
	if(!data.loadFile(fileName))
		return false;
	b32 dword;
	i32 i;
	IMGindex ii;
	data.ptMoveTo(0);
	if(data.readString(16) != "NeoplePack_Bill"){
		return false;
	}
	data.read(dword);
	count = dword;
	content.clear();
	for(i=0;i<count;i++){
		data.read(dword);
		ii.set_imgoffset(dword);
		data.read(dword);
		ii.set_imgsize(dword);
		s.allocate(256);
		data.readStream(s, 256);
		s.nameMask();
		ii.set_imgname((str)s);
		s.release();
		content.push_back(ii);
	}
	versionList.clear();
	for(i=0;i<count;i++){
		data.ptMoveTo(content[i].get_imgoffset());
		data.read(dword);
		if(dword == 0x706f654e){
			data.ptMoveTo(content[i].get_imgoffset()+24);
			data.read(dword);
			versionList.push_back(IMGversion(dword));
		}else{
			versionList.push_back(IMGversion(0));
		}
	}
	data.release();
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////

IMGobject::IMGobject(){
	release();
}
IMGobject::IMGobject(stream &s){
	release();
	load(s);
}
IMGobject::IMGobject(const str &fileName){
	release();
	loadFile(fileName);
}
IMGobject::~IMGobject(){
	release();
}
bool IMGobject::loadFile(str fileName){
	bool result = true;
	stream s;
	result &= s.loadFile(fileName);
	result &= load(s);
	s.release();
	return result;
}
bool IMGobject::saveFile(str fileName){
	bool result = true;
	stream s;
	result &= make(s);
	result &= s.makeFile(fileName);
	s.release();
	return result;
}
bool IMGobject::load(stream &s){
	bool result = true;
	////////////////////////////////////////////
	str sz;
	i32 num1,num2;
	b32 dword, i, j;
	b64 ptStart, ptEnd;
	ptStart = 0;
	s.ptMoveTo(0);
	sz = s.readString(20);
	//if(sz == "Neople Image File"){
	//	KoishiExpand::OldIMGobject oio;
	//	if(!oio.load(s)){
	//		return false;
	//	}
	//	oio.make(*this);
	//	oio.release();
	//	return true;
	//}
	if(sz != "Neople Img File")
		return false;
	s.ptMoveTo(16);
	s.read(dword);
	indexSize = dword;
	s.read(dword);
	s.read(dword);
	version = (IMGversion)dword;
	if(version != V2 && version != V4 && version != V5 && version != V6)
		return false;
	s.read(dword);
	indexCount = dword;
	if(version == V5){
		s.read(dword);
		V5_TEXCount = dword;
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
			clrList.push_back(color(dword,INDEX_FMT_PALETTE));
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
				clrList.push_back(color(dword, INDEX_FMT_PALETTE));
			}
			paletteData.push(clrList);
		}
	}
	ptEnd = s.ptPos();
	s.ptMoveTo(ptStart);
	getData(2)->allocate(1000 + ptEnd - ptStart);
	s.readStream(*getData(2), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	//////////////////////////////////////
	TEXinfo di;
	TEXcontent.clear();
	if(version == V5){
		for(i=0;i<V5_TEXCount;i++){
			s.read(dword);
			di.set_reserved(dword);
			s.read(dword);
			di.set_format((colorFormat)dword);
			s.read(dword);
			di.set_ID(dword);
			s.read(dword);
			di.set_compressedLength(dword);
			s.read(dword);
			di.set_dataLength(dword);
			s.read(dword);
			di.set_width(dword & 0xFFFF);
			s.read(dword);
			di.set_height(dword & 0xFFFF);
			TEXcontent.push_back(di);
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
						
				pi.set_TEXusing(0);
				pi.set_TEXpointLT(point(0,0));
				pi.set_TEXpointRB(point(0,0));
			}else{
				pi.set_linkTo(-1);
				s.read(dword);
				pi.set_comp((compressType)dword);
				if(dword == 0x05 || dword == 0x06){
					s.read(num1);
					s.read(num2);
					pi.set_picSize(size(num1 & 0xFFFF, num2 & 0xFFFF));
					s.read(dword);
					pi.set_dataSize(dword);
					s.read(num1);
					s.read(num2);
					pi.set_basePt(point(num1 & 0xFFFF, num2 & 0xFFFF));
					s.read(num1);
					s.read(num2);
					pi.set_frmSize(size(num1 & 0xFFFF, num2 & 0xFFFF));

					pi.set_TEXusing(0);
					pi.set_TEXpointLT(point(0,0));
					pi.set_TEXpointRB(point(0,0));
				}else if(dword == 0x07){
					s.read(num1);
					s.read(num2);
					pi.set_picSize(size(num1 & 0xFFFF, num2 & 0xFFFF));
					s.read(dword);
					pi.set_dataSize(dword);
					s.read(num1);
					s.read(num2);
					pi.set_basePt(point(num1 & 0xFFFF, num2 & 0xFFFF));
					s.read(num1);
					s.read(num2);
					pi.set_frmSize(size(num1 & 0xFFFF, num2 & 0xFFFF));
					s.read(dword);
					s.read(dword);
					pi.set_TEXusing(dword);
					s.read(num1);
					s.read(num2);
					pi.set_TEXpointLT(point(num1 & 0xFFFF,num2 & 0xFFFF));
					s.read(num1);
					s.read(num2);
					pi.set_TEXpointRB(point(num1 & 0xFFFF,num2 & 0xFFFF));
					s.read(dword);
				}else{
					//NODEF
				}
			}
			PICcontent.push_back(pi);
		}
	}
	ptEnd = s.ptPos();
	s.ptMoveTo(ptStart);
	getData(4)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(4), ptEnd - ptStart);
	if(ptEnd - ptStart >= indexSize){
		//真实索引表大小>给定索引表大小
		s.ptMoveTo(ptStart = ptEnd);
	}else{
		//真实索引表大小<给定索引表大小
		s.ptMoveTo(ptStart = ptStart + indexSize);
	}
	///////////////////////////////////////
	b64 fsize = 0;
	for(i=0;i<TEXcontent.size();i++){
		fsize += TEXcontent[i].get_compressedLength();
	}
	getData(5)->allocate(s.getLen());
	s.readStream(*getData(5), fsize);
	///////////////////////////////////////
	getData(6)->allocate(s.getLen());
	s.readStream(*getData(6), s.getLen());
	return result;
}
bool IMGobject::make(stream &s){
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
bool IMGobject::create(IMGversion ver){
	if(ver != V2 && ver != V4 && ver != V5 && ver != V6)
		return false;
	release();
	version = ver;
	if(ver == V4 || ver == V5 || ver == V6){
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
		getData(1)->push(V5_TEXCount);
		getData(1)->push(V5_totalLength);
	}
	//调色板数据
	getData(2)->allocate(1024);
	if(ver == V6){
		getData(2)->push((b32)1);
	}
	if(ver == V4 || ver == V5 || ver == V6){
		getData(2)->push((b32)0);
	}
	getData(3)->allocate(1024);
	getData(4)->allocate(1024);
	getData(5)->allocate(1024);
	getData(6)->allocate(1024);
	return true;
}
bool IMGobject::release(){
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
	V5_TEXCount = 0;
	V5_totalLength = 0;
	paletteData.clear();
	TEXcontent.clear();
	PICcontent.clear();
	return true;
}
bool IMGobject::PICgetInfo(i32 pos, PICinfo &info){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	info = PICcontent[pos];
	return true;
}
bool IMGobject::PICgetInfoOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	off = 0;
	for(i32 i=0;i<pos;i++){
		if(PICcontent[i].get_format() == LINK){
			off += 8;
		}else if(PICcontent[i].get_comp() <= COMP_ZLIB){
			//单索引模式
			off += 36;
		}else{
			//双索引模式
			off += 64;
		}
	}
	return true;
}
bool IMGobject::PICgetData(i32 pos, stream &s){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	b64 size = (b64)PICcontent[pos].get_dataSize();
	b64 offset;
	if(size == 0)
		return false;
	if(!PICgetDataOffset(pos, offset))
		return false;
	data6.ptMoveTo(offset);
	data6.readStream(s, size);
	return true;
}
bool IMGobject::PICgetDataOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	i32 i;
	off = 0;
	for(i=0;i<pos;i++){
		if(PICcontent[i].get_format() != LINK && PICcontent[i].get_comp() <= COMP_ZLIB){
			off += (b64)PICcontent[i].get_dataSize();
		}
	}
	return true;
}
bool IMGobject::TEXgetInfo(i32 pos, TEXinfo &info){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	info = TEXcontent[pos];
	return true;
}
bool IMGobject::TEXgetInfoOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	off = 0;
	for(i32 i=0;i<pos;i++){
		off += 28;
	}
	return true;
}
bool IMGobject::TEXgetData(i32 pos, stream &s){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	b64 offset;
	b64 size = (b64)TEXcontent[pos].get_compressedLength();
	if(size == 0)
		return false;
	if(!TEXgetDataOffset(pos, offset))
		return false;
	getData(5)->ptMoveTo(offset);
	getData(5)->readStream(s, size);
	return true;
}
bool IMGobject::TEXgetDataOffset(i32 pos, b64 &off){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	i32 i;
	off = 0;
	for(i=0;i<pos;i++){
		off += (b64)TEXcontent[i].get_compressedLength();
	}
	return true;
}
bool IMGobject::PICsetInfoPara(i32 pos, i32 term, void *pval){
	//Term: 0. linkTo 1. basePoint 2.frameSize 3.DDSID 4.pointLT, 5.pointRB
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	i32 i = *(i32*)pval;
	size sz = *(size*)pval;
	point pt = *(point*)pval;
	PICinfo pi;
	TEXinfo di;
	b64 off;
	PICgetInfo(pos, pi);
	PICgetInfoOffset(pos, off);
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
	}else if(pi.get_comp() <= COMP_ZLIB){
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
	}else/*if(pi.get_comp() > COMP_ZLIB)*/{
		TEXgetInfo(pi.get_TEXusing(), di);
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
			if(i<0 || i>=TEXcontent.size())
				return false;
			PICcontent[pos].set_TEXusing(i);
			getData(4)->modify(off+40, i);
			return true;
		case 4:
			if(pt.get_X()<0 || pt.get_X()>pi.get_TEXpointLT().get_X()){
				return false;
			}
			if(pt.get_Y()<0 || pt.get_Y()>pi.get_TEXpointRB().get_Y()){
				return false;
			}
			sz = size(pi.get_TEXpointRB().get_X()-pt.get_X(),
				pi.get_TEXpointRB().get_Y()-pt.get_Y());
			PICcontent[pos].set_TEXpointLT(pt);
			PICcontent[pos].set_picSize(sz);
			getData(4)->modify(off+8,  sz.get_W());
			getData(4)->modify(off+12, sz.get_H());
			getData(4)->modify(off+44, pt.get_X());
			getData(4)->modify(off+48, pt.get_Y());
			return true;
		case 5:
			if(pt.get_X()>di.get_width()-1 || pt.get_X()<pi.get_TEXpointLT().get_X()){
				return false;
			}
			if(pt.get_Y()>di.get_height()-1 || pt.get_Y()<pi.get_TEXpointLT().get_Y()){
				return false;
			}
			sz = size(pt.get_X()-pi.get_TEXpointLT().get_X(),
				pt.get_Y()-pi.get_TEXpointLT().get_Y());
			PICcontent[pos].set_TEXpointRB(pt);
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
	}else if(info.get_comp() <= COMP_ZLIB){
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
		sTemp.push(info.get_TEXusing());
		sTemp.push(info.get_TEXpointLT().get_X());
		sTemp.push(info.get_TEXpointLT().get_Y());
		sTemp.push(info.get_TEXpointRB().get_X());
		sTemp.push(info.get_TEXpointRB().get_Y());
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
	PICgetInfoOffset(pos, off1);
	PICgetDataOffset(pos, off2);
	PICcontent.insert(PICcontent.begin()+pos, info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push((b32)info.get_format());
	if(info.get_format() == LINK){
		sTemp.push(info.get_linkTo());
		getData(4)->insertStream(sTemp, 8, off1);
	}else if(info.get_comp() <= COMP_ZLIB){
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
		sTemp.push(info.get_TEXusing());
		sTemp.push(info.get_TEXpointLT().get_X());
		sTemp.push(info.get_TEXpointLT().get_Y());
		sTemp.push(info.get_TEXpointRB().get_X());
		sTemp.push(info.get_TEXpointRB().get_Y());
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
	PICgetInfo(pos, pi);
	PICgetInfoOffset(pos, off1);
	PICgetDataOffset(pos, off2);
	PICcontent.erase(PICcontent.begin()+pos);
	if(pi.get_format() == LINK){
		getData(4)->deleteStream(off1, 8);
	}else if(pi.get_comp() <= COMP_ZLIB){
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
	PICgetInfo(pos, pi);
	PICgetInfoOffset(pos, off1);
	PICgetDataOffset(pos, off2);
	PICcontent[pos] = info;
	///////////////////////
	if(pi.get_format() == LINK){
		getData(4)->deleteStream(off1, 8);
	}else if(pi.get_comp() <= COMP_ZLIB){
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
	}else if(info.get_comp() <= COMP_ZLIB){
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
		sTemp.push(info.get_TEXusing());
		sTemp.push(info.get_TEXpointLT().get_X());
		sTemp.push(info.get_TEXpointLT().get_Y());
		sTemp.push(info.get_TEXpointRB().get_X());
		sTemp.push(info.get_TEXpointRB().get_Y());
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
	TEXinfo di;
	stream sMid, sPic;
	PICgetInfo(pos, pi);
	if(pi.get_format() == LINK){
		pos = linkFind(pos);
	}
	PICgetInfo(pos, pi);
	if(pi.get_format() != LINK){
		if(pi.get_comp()<= 0X06){
			PICgetData(pos, sMid);
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
				if(sPic.getLen() == pi.get_picSize().area()){
					//索引形式
					mat.allocate(pi.get_picSize());
					for(i=0;i<sPic.getLen();i++){
						if(sPic[i]>=paletteData[0].size())
							sPic[i] = 0;
						mat.push(paletteData[0][sPic[i]]);
					}
				}else{
					//非索引形式
					mat.allocate(pi.get_picSize());
					mat.push(sPic, pi.get_format());
				}
				break;
			case V6:
				mat.allocate(pi.get_picSize());
				for(i=0;i<sPic.getLen();i++){
					if(sPic[i]>=paletteData[paletteID].size()){
						sPic[i] = 0;
					}
					if(paletteData[paletteID].size()>0){
						mat.push(paletteData[paletteID][sPic[i]]);
					}else{
						mat.push(color(0));
					}
				}
				break;
			}
		}else/*if(pi.get_comp() == 0X07)*/{
			if(pi.get_TEXusing()>=V5_TEXCount){
				return false;
			}
			matrix mTemp;
			TEXextract(pi.get_TEXusing(),mTemp);
			/*
			TEXgetInfo(pi.get_TEXusing(), di);
			TEXgetData(pi.get_TEXusing(), sMid);
			sMid.uncompressData(sPic, pi.get_comp());
			
			if(di.get_format() > LINK){
				KoishiDDS::DDS d(sPic);
				d.uncompress(mTemp);
			}else{
				mTemp.allocate(di.get_height(), di.get_width());
				mTemp.push(sPic, di.get_format());
			}*/
			mTemp.getSubMatrix(mat,
				pi.get_TEXpointLT().get_Y(),
				pi.get_TEXpointRB().get_Y(),
				pi.get_TEXpointLT().get_X(),
				pi.get_TEXpointRB().get_X()
			);
		}
	}
	return true;
}
///////////////////////////////////////////
//
//
//		大改！！！！！！！！！
//
//
///////////////////////////////////////////
bool IMGobject::PICpreprocess(const matrix &mat, stream &s, PICinfo &info, colorFormat cf){
	//依然不支持V6
	if(version == V2){
		if(cf == COLOR_UDEF){
			cf = ARGB8888;
		}
		if(cf == ARGB8888){
			stream sTemp;
			mat.make(sTemp, ARGB8888);
			sTemp.compressData(s, COMP_ZLIB);
			sTemp.release();
			info.set_comp(COMP_ZLIB);
			info.set_format(ARGB8888);
			info.set_dataSize(s.getLen());
			info.set_linkTo(-1);
			info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
			return true;
		}
		if(cf == ARGB4444){
			stream sTemp;
			mat.make(sTemp, ARGB4444);
			sTemp.compressData(s, COMP_ZLIB);
			sTemp.release();
			info.set_comp(COMP_ZLIB);
			info.set_format(ARGB4444);
			info.set_dataSize(s.getLen());
			info.set_linkTo(-1);
			info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
			return true;
		}
		if(cf == ARGB1555){
			stream sTemp;
			mat.make(sTemp, ARGB1555);
			sTemp.compressData(s, COMP_ZLIB);
			sTemp.release();
			info.set_comp(COMP_ZLIB);
			info.set_format(ARGB1555);
			info.set_dataSize(s.getLen());
			info.set_linkTo(-1);
			info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
			return true;
		}
		return false;
	}
	if(version == V4){
		if(cf == COLOR_UDEF){
			cf = INDEX_FMT_PALETTE;
		}
		if(cf == INDEX_FMT_PALETTE){
			i32 i;
			lcolor clrList;
			stream sTemp;
			mat.getElemCountList(clrList);
			if(!paletteData.joinWith(clrList)){
				//调色板溢出
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
		return false;
	}
	if(version == V5){
		if(cf == COLOR_UDEF){
			cf = ARGB8888;
		}
		if(cf == ARGB8888){
			stream sTemp;
			mat.make(sTemp, ARGB8888);
			sTemp.compressData(s, COMP_ZLIB);
			sTemp.release();
			info.set_comp(COMP_ZLIB);
			info.set_format(ARGB8888);
			info.set_dataSize(s.getLen());
			info.set_linkTo(-1);
			info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
			return true;
		}
		if(cf == ARGB4444){
			stream sTemp;
			mat.make(sTemp, ARGB4444);
			sTemp.compressData(s, COMP_ZLIB);
			sTemp.release();
			info.set_comp(COMP_ZLIB);
			info.set_format(ARGB4444);
			info.set_dataSize(s.getLen());
			info.set_linkTo(-1);
			info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
			return true;
		}
		if(cf == ARGB1555){
			stream sTemp;
			mat.make(sTemp, ARGB1555);
			sTemp.compressData(s, COMP_ZLIB);
			sTemp.release();
			info.set_comp(COMP_ZLIB);
			info.set_format(ARGB1555);
			info.set_dataSize(s.getLen());
			info.set_linkTo(-1);
			info.set_picSize(size(mat.getColumnCount(), mat.getRowCount()));
			return true;
		}
		if(cf == INDEX_FMT_PALETTE){
			i32 i;
			lcolor clrList;
			stream sTemp;
			mat.getElemCountList(clrList);
			if(!paletteData.joinWith(clrList)){
				//调色板溢出
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
		if(cf == DDS_DXT5){
			//效果很差
			stream sTemp;
			KoishiDDS::DDS d;
			d.compress(mat);
			d.make(sTemp);
			sTemp.compressData(s, COMP_ZLIB);
			sTemp.release();
			info.set_format(DDS_DXT5);
			info.set_comp(COMP_ZLIB);
			info.set_dataSize(s.getLen());
			info.set_linkTo(-1);
			info.set_picSize(size(d.getHeader()->width,d.getHeader()->height));
			sTemp.release();
			return true;
		}
		return false;
	}
	return false;
}
bool IMGobject::PICextractIndexMatrix(i32 pos, matrix &mat){
	if(pos<0)
		pos += indexCount;
	if(pos<0)
		return false;
	if(pos>indexCount - 1)
		return false;
	if(version == V2)
		return false;
	i32 i;
	PICinfo pi;
	stream sMid, sPic;
	PICgetInfo(pos, pi);
	if(pi.get_format() == LINK){
		pos = linkFind(pos);
	}
	PICgetInfo(pos, pi);
	if(pi.get_format() == ARGB1555){
		PICgetData(pos, sMid);
		sMid.uncompressData(sPic, pi.get_comp());
		//解压后索引矩阵的长度与宽×高必须一致
		if(sPic.getLen() == pi.get_picSize().area()){
			mat.allocate(pi.get_picSize());
			for(i=0;i<sPic.getLen();i++){
				mat.push(color(sPic[i],0,0,0));
			}
			sMid.release();
			sPic.release();
			return true;
		}else{
			sMid.release();
			sPic.release();
			return false;
		}
	}else{
		return false;
	}
	return true;
}
bool IMGobject::PICpreprocessIndexMatrix(const matrix &mat, stream &s, PICinfo &info){
	i32 i;
	stream sTemp;
	sTemp.allocate(mat.getElemCount());
	for(i=0;i<mat.getElemCount();i++){
		sTemp.push(mat.getElem(i).get_A());
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
		s.allocate(4);
		s.push((b32)0);
		info.set_comp(COMP_NONE);
		info.set_format(ARGB8888);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
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
bool IMGobject::TEXpush(const TEXinfo &info, const stream &s){
	if(version != V5)
		return false;
	TEXcontent.push_back(info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((b32)info.get_format());
	sTemp.push(info.get_ID());
	sTemp.push(info.get_compressedLength());
	sTemp.push(info.get_dataLength());
	sTemp.push(info.get_width());
	sTemp.push(info.get_height());
	getData(3)->pushStream(sTemp, 28);
	getData(5)->pushStream(s, info.get_compressedLength());
	//////////////////////////////////////////////////////////////////
	V5_TEXCount ++;
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_TEXCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::TEXinsert(i32 pos, const TEXinfo &info, const stream &s){
	if(version != V5)
		return false;
	if(pos<0)
		pos += (V5_TEXCount + 1);
	if(pos<0)
		return false;
	if(pos>V5_TEXCount)
		return false;
	if(pos == V5_TEXCount)
		return TEXpush(info, s);
	b64 off1, off2;
	TEXgetInfoOffset(pos, off1);
	TEXgetDataOffset(pos, off2);
	TEXcontent.insert(TEXcontent.begin()+pos, info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((b32)info.get_format());
	sTemp.push(info.get_ID());
	sTemp.push(info.get_compressedLength());
	sTemp.push(info.get_dataLength());
	sTemp.push(info.get_width());
	sTemp.push(info.get_height());
	getData(3)->insertStream(sTemp, 28, off1);
	getData(5)->insertStream(s, info.get_compressedLength(), off2);
	//////////////////////////////////////////////////////////////////
	V5_TEXCount ++;
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_TEXCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::TEXremove(i32 pos){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_TEXCount;
	if(pos<0)
		return false;
	if(pos>V5_TEXCount-1)
		return false;
	TEXinfo di;
	b64 off1,off2;
	TEXgetInfo(pos, di);
	TEXgetInfoOffset(pos, off1);
	TEXgetDataOffset(pos, off2);
	TEXcontent.erase(TEXcontent.begin()+pos);
	getData(3)->deleteStream(off1, 28);
	getData(5)->deleteStream(off2, di.get_compressedLength());
	//////////////////////////////////////////////////////////////////
	V5_TEXCount --;
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_TEXCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::TEXreplace(i32 pos, const TEXinfo &info, const stream &s){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_TEXCount;
	if(pos<0)
		return false;
	if(pos>V5_TEXCount-1)
		return false;
	TEXinfo di;
	b64 off1,off2;
	TEXgetInfo(pos, di);
	TEXgetInfoOffset(pos, off1);
	TEXgetDataOffset(pos, off2);
	TEXcontent[pos] = info;
	getData(3)->deleteStream(off1, 28);
	getData(5)->deleteStream(off2, di.get_compressedLength());
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((b32)info.get_format());
	sTemp.push(info.get_ID());
	sTemp.push(info.get_compressedLength());
	sTemp.push(info.get_dataLength());
	sTemp.push(info.get_height());
	sTemp.push(info.get_width());
	getData(3)->insertStream(sTemp, 28, off1);
	getData(5)->insertStream(s, info.get_compressedLength(), off2);
	////////////////////////////////////////
	V5_totalLength = getSize();
	getData(1)->modify(32, (i32)V5_TEXCount);
	getData(1)->modify(36, (i32)V5_totalLength);
	return true;
}
bool IMGobject::TEXextract(i32 pos, matrix &mat){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_TEXCount;
	if(pos<0)
		return false;
	if(pos>V5_TEXCount - 1)
		return false;
	TEXinfo di;
	stream sMid, sPic;
	TEXgetInfo(pos, di);
	TEXgetData(pos, sMid);
	sMid.uncompressData(sPic, COMP_ZLIB);
	if(di.get_format() > LINK){
		KoishiDDS::DDS d(sPic);
		d.uncompress(mat);
	}else{
		if(sPic.getLen() == di.get_height()*di.get_width()){
			//索引形式
			mat.allocate(di.get_height(), di.get_width());
			for(int i=0;i<sPic.getLen();i++){
				if(sPic[i]>=paletteData[0].size()){
					sPic[i] = 0;
				}
				mat.push(paletteData[0][sPic[i]]);
			}
		}else{
			mat.allocate(di.get_height(), di.get_width());
			mat.push(sPic, di.get_format());
		}
	}
	return true;
}
bool IMGobject::TEXpreprocess(const matrix &mat, stream &s, TEXinfo &info, colorFormat cf){
	if(version != V5)
		return false;
	if(cf == DDS_DXT5){
		//效果很差
		stream sTemp;
		KoishiDDS::DDS d;
		d.compress(mat);
		d.make(sTemp);
		sTemp.compressData(s, COMP_ZLIB);
		info.set_reserved(1);
		info.set_format(DDS_DXT5);
		info.set_dataLength(sTemp.getLen());
		info.set_compressedLength(s.getLen());
		info.set_width(d.getHeader()->width);
		info.set_height(d.getHeader()->height);
		info.set_ID(V5_TEXCount);
		sTemp.release();
		return true;
	}
	if(cf == ARGB8888){
		stream sTemp;
		mat.make(sTemp, ARGB8888);
		sTemp.compressData(s, COMP_ZLIB);
		info.set_reserved(1);
		info.set_format(ARGB8888);
		info.set_dataLength(sTemp.getLen());
		info.set_compressedLength(s.getLen());
		info.set_width(mat.getColumnCount());
		info.set_height(mat.getRowCount());
		info.set_ID(V5_TEXCount);
		sTemp.release();
		return true;
	}
	if(cf == ARGB4444){
		stream sTemp;
		mat.make(sTemp, ARGB4444);
		sTemp.compressData(s, COMP_ZLIB);
		info.set_reserved(1);
		info.set_format(ARGB4444);
		info.set_dataLength(sTemp.getLen());
		info.set_compressedLength(s.getLen());
		info.set_width(mat.getColumnCount());
		info.set_height(mat.getRowCount());
		info.set_ID(V5_TEXCount);
		sTemp.release();
		return true;
	}
	if(cf == ARGB1555){
		stream sTemp;
		mat.make(sTemp, ARGB1555);
		sTemp.compressData(s, COMP_ZLIB);
		info.set_reserved(1);
		info.set_format(ARGB1555);
		info.set_dataLength(sTemp.getLen());
		info.set_compressedLength(s.getLen());
		info.set_width(mat.getColumnCount());
		info.set_height(mat.getRowCount());
		info.set_ID(V5_TEXCount);
		sTemp.release();
		return true;
	}
	if(cf == INDEX_FMT_PALETTE){
		i32 i;
		lcolor clrList;
		stream sTemp;
		mat.getElemCountList(clrList);
		if(!paletteData.joinWith(clrList)){
			//调色板溢出
			return false;
		}
		getData(2)->release();
		paletteData.tinyMake(*getData(2));
		sTemp.allocate(mat.getElemCount());
		for(i=0;i<mat.getElemCount();i++){
			sTemp.push((b8)paletteData.findColor(mat.getElem(i)));
		}
		sTemp.compressData(s, COMP_ZLIB);
		info.set_reserved(1);
		info.set_format(ARGB1555);
		info.set_dataLength(sTemp.getLen());
		info.set_compressedLength(s.getLen());
		info.set_width(mat.getColumnCount());
		info.set_height(mat.getRowCount());
		info.set_ID(V5_TEXCount);
		sTemp.release();
		return true;
	}
	return false;
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
	if(pos<0)
		pos += paletteData[paletteID].size()+1;
	if(pos<0)
		return false;
	if(pos>paletteData[paletteID].size())
		return false;
	if(pos==paletteData[paletteID].size())
		return CLRpush(clr, paletteID);
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
	if(pos<0)
		pos += paletteData[paletteID].size();
	if(pos<0)
		return false;
	if(pos>paletteData[paletteID].size() - 1)
		return false;
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
	getData(2)->release();
	paletteData.bigMake(*getData(2));
	return true;
}
//newIO: 新IO的引用
//newVersion: 新版本
//cf: 新格式
//paletteID: 原IO为V6时，转换为哪个调色板
//indexPara: 量化参数，最高位为1时采用位量化，否则采用平均量化，低7位为量化级别，为0时不采用量化
bool IMGobject::convertTo(IMGobject &newIO, IMGversion newVersion, colorFormat cf, i32 paletteID, b8 indexPara, bool makeTexture){
	i32 i;
	PICinfo pi;
	TEXinfo di;
	bool result = true;
	matrix mat;
	stream s;
	newIO.create(newVersion);
	if(version == newVersion){
		newIO = *this;
		return true;
	}else if(version == V4 && newVersion == V6){
		for(i=0;i<indexCount;i++){
			PICgetInfo(i,pi);
			if(pi.get_format() == LINK){
				result &= newIO.PICpush(pi,NULL);
			}else{
				result &= PICgetData(i, s);
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
			PICgetInfo(i,pi);
			if(pi.get_format() == LINK){
				result &= newIO.PICpush(pi,NULL);
			}else{
				result &= PICgetData(i, s);
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
		result &= convertTo(midIO, V4, cf);
		if(!result)
			return false;
		result &= midIO.convertTo(newIO, V6, cf);
		return result;
	}else{
		for(i=0;i<indexCount;i++){
			PICgetInfo(i, pi);
			if(pi.get_format() == LINK){
				result &= newIO.PICpush(pi, NULL);
			}else{
				result &= PICextract(i, mat, paletteID);
				if(indexPara != 0){
					if(indexPara > 0x7f){
						mat.loseBit(indexPara & 0x07);
					}else{
						mat.lose(indexPara & 0x7f);
					}
				}
				if(!makeTexture || newVersion != V5){
					//对非V5也是不能使用纹理集
					result &= newIO.PICpreprocess(mat, s, pi, cf);
					if(!result)
						return false;
					result &= newIO.PICpush(pi, s);
					mat.release();
					s.release();
				}else{
					result &= newIO.TEXpreprocess(mat, s, di, cf);
					if(!result)
						return false;
					result &= newIO.TEXpush(di, s);
					mat.release();
					s.release();
					pi.set_format(di.get_format());
					pi.set_comp(COMP_ZLIB2);
					pi.set_dataSize(0);
					pi.set_picSize(size(di.get_width(),di.get_height()));
					pi.set_TEXusing(newIO.V5_TEXCount-1);
					pi.set_TEXpointLT(point(0,0));
					pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
					result &= newIO.PICpush(pi,NULL);
				}
			}
		}
		return true;
	}
	return false;
}

i32 IMGobject::linkFind(b32 pos, b32 depth){
	PICinfo pi;
	PICgetInfo(pos, pi);
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
