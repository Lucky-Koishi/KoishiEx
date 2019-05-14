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
	dword dword;
	long i;
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
		ii.imgoffset = dword;
		data.read(dword);
		ii.imgsize = dword;
		sPath.allocate(256);
		data.readStream(sPath, 256);
		sPath.nameMask();
		ii.imgname = (str)sPath;
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
	dword len1 = getData(1)->getLen();
	dword len2 = getData(2)->getLen();
	dword len3 = getData(3)->getLen();
	dword len4 = getData(4)->getLen();
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
	getData(1)->push((uchar)0);
	getData(1)->push((dword)0);
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
	dword dwTemp;
	long i;
	ii.imgname = imgName;
	ii.imgoffset = getSize();
	ii.imgsize = io.getSize();
	content.push_back(ii);
	for(i=0;i<content.size();i++){
		dwTemp = content[i].imgoffset;
		content[i].imgoffset = dwTemp+264;
	}
	//////////////////////////////////////////////
	count++;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((uchar)0);
	getData(1)->push(count);
	//////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
bool NPKobject::IMGpushLink(long linkPos, const str &otherName){
	if(linkPos<0 || linkPos>=count){
		return false;
	}
	stream s;
	IMGindex ii;
	dword dwTemp;
	long i;
	ii.imgname = otherName;
	ii.imgoffset = content[linkPos].imgoffset;
	ii.imgsize = content[linkPos].imgsize;
	content.push_back(ii);
	for(i=0;i<content.size();i++){
		dwTemp = content[i].imgoffset;
		content[i].imgoffset = dwTemp+264;
	}
	//////////////////////////////////////////////
	count++;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((uchar)0);
	getData(1)->push(count);
	//////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
	return true;
}
bool NPKobject::IMGremoveLink(long pos){
	if(IMGcheckLink(pos) < 0){
		return false;
	}
	long i;
	stream s;
	dword dwTemp;
	content.erase(content.begin() + pos);
	for(i=0;i<content.size();i++){
		dwTemp = content[i].imgoffset - 264;
		content[i].imgoffset = dwTemp;
	}
	/////////////////////////////////////////////////////
	count --;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((uchar)0);
	getData(1)->push(count);
	/////////////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
	return true;
}
bool NPKobject::IMGmodifyLink(long pos, long newLinkPos){
	if(IMGcheckLink(pos) < 0){
		return false;
	}
	if(newLinkPos < 0 && newLinkPos >= pos){
		return false;
	}
	long i;
	stream s;
	content[pos].imgoffset = content[newLinkPos].imgoffset;
	content[pos].imgsize = content[newLinkPos].imgsize;
	/////////////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
	return true;
}

long NPKobject::IMGcheckLink(long pos){
	if(pos<0 || pos>=count){
		return -2;
	}
	for(int i = 0;i<pos;i++){
		if(content[i].imgoffset == content[pos].imgoffset){
			return i;
		}
	}
	return -1;
}
bool NPKobject::randomExtract(dword pos, stream &s){
	if(pos<0 || pos>=count){
		return false;
	}
	stream temps;
	getData(4)->ptMoveTo(content[pos].imgoffset-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->readStream(s, (longex)(content[pos].imgsize));
	return true;
}
bool NPKobject::randomPush(stream randomStream, const str &imgName){
	stream s;
	IMGindex ii;
	dword dwTemp;
	long i;
	ii.imgname = imgName;
	ii.imgoffset = getSize();
	ii.imgsize = randomStream.getLen();
	content.push_back(ii);
	for(i=0;i<content.size();i++){
		dwTemp = content[i].imgoffset;
		content[i].imgoffset = dwTemp+264;
	}
	//////////////////////////////////////////////
	count++;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((uchar)0);
	getData(1)->push(count);
	//////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
	getData(4)->pushStream(randomStream, randomStream.getLen());
	return true;
}
bool NPKobject::IMGinsert(long pos, IMGobject &io, const str &imgName){
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
	long i;
	stream s;
	IMGindex ii;
	dword dwTemp;
	longex offset = content[pos].imgoffset - getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen();
	ii.imgname = imgName;
	ii.imgoffset = content[pos].imgoffset;
	ii.imgsize = io.getSize();
	content.insert(content.begin()+pos, ii);
	for(i=0;i<content.size();i++){
		dwTemp = content[i].imgoffset;
		dwTemp += 264;
		if(i>pos){
			dwTemp += io.getSize();
		}
		content[i].imgoffset = dwTemp;
	}
	//////////////////////////////////////////////
	count++;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((uchar)0);
	getData(1)->push(count);
	//////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
bool NPKobject::IMGremove(long pos){
	if(pos<0){
		pos += count;
	}
	if(pos<0){
		pos = 0;
	}
	if(pos>count-1){
		pos = count-1;
	}
	long i;
	//////////////////////////////////////////////
	//先确定是否有其他东西指向它
	//////////////////////////////////////////////
	for(i = count - 1;i>pos;i--){
		if(IMGcheckLink(i) == pos){
			IMGremoveLink(i);
		}
	}
	//////////////////////////////////////////////
	stream s;
	IMGindex ii;
	dword dwTemp;
	ii = content[pos];
	longex offset = content[pos].imgoffset - getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen();
	content.erase(content.begin() + pos);
	for(i=0;i<content.size();i++){
		dwTemp = content[i].imgoffset;
		dwTemp -= 264;
		if(i>=pos){
			dwTemp -= ii.imgsize;
		}
		content[i].imgoffset = dwTemp;
	}
	/////////////////////////////////////////////////////
	count --;
	getData(1)->clear();
	getData(1)->pushString("NeoplePack_Bill");
	getData(1)->push((uchar)0);
	getData(1)->push(count);
	/////////////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
	getData(4)->deleteStream(offset, ii.imgsize);
	return true;
}
bool NPKobject::IMGreplace(long pos, IMGobject &io){
	if(pos<0){
		pos += count;
	}
	if(pos<0){
		pos = 0;
	}
	if(pos>count){
		pos = count - 1;
	}
	long i;
	stream s;
	IMGindex ii;
	dword dwTemp;
	longex offset = content[pos].imgoffset - getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen();
	ii = content[pos];
	content[pos].imgsize = io.getSize();
	for(i=0;i<content.size();i++){
		if(i>pos){
			dwTemp = content[i].imgoffset;
			dwTemp -= ii.imgsize;
			dwTemp += io.getSize();
			content[i].imgoffset = dwTemp;
		}
	}
	//////////////////////////////////////////////////
	getData(2)->release();
	getData(2)->allocate(count*400);
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
	getData(4)->deleteStream(offset, ii.imgsize);
	getData(4)->insertStream(s, s.getLen(), offset);
	return true;
}
bool NPKobject::IMGrename(long pos, const str& newName){
	if(pos<0){
		pos += count;
	}
	if(pos<0){
		pos = 0;
	}
	if(pos>count){
		pos = count - 1;
	}
	long i;
	stream s;
	content[pos].imgname = newName;
	///////////////////////////////////////////////////////
	getData(2)->clear();
	for(i=0;i<count;i++){
		getData(2)->push(content[i].imgoffset);
		getData(2)->push(content[i].imgsize);
		s.allocate(512);
		s.pushString(content[i].imgname);
		while(s.getLen()<256){
			s.push((uchar)0);
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
stream *NPKobject::getData(uchar _part){
	stream *sList[] = {NULL, &dataHeader, &dataIndex, &dataCheckCode, &dataMain};
	return sList[_part%5];
}
longex NPKobject::getSize() const{
	return dataHeader.getLen()+dataIndex.getLen()+dataCheckCode.getLen()+dataMain.getLen();
}
bool NPKobject::IMGextract(dword pos, IMGobject &obj){
	if(pos<0 || pos>=count){
		return false;
	}
	stream temps;
	obj.derived = &content[pos];
	getData(4)->ptMoveTo(content[pos].imgoffset-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->readStream(temps, (longex)(content[pos].imgsize));
	return obj.load(temps);
}
bool NPKobject::IMGfind(const str &keyword, dword &pos){
	long i = 0;
	for(i=0;i<count;i++){
		if(content[i].imgname.find(keyword) != str::npos){
			pos = i;
			return true;
		}
	}
	return false;
}
bool NPKobject::IMGfind(const str &keyword, const str &nonkeyword, dword &pos){
	long i = 0;
	for(i=0;i<count;i++){
		if(content[i].imgname.find(keyword) != str::npos && content[i].imgname.find(nonkeyword) == str::npos){
			pos = i;
			return true;
		}
	}
	return false;
}
bool NPKobject::randomExtract(long pos, str fileName){
	if(pos<0 || pos>=count){
		return false;
	}
	stream temps;
	getData(4)->ptMoveTo(content[pos].imgoffset-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->readStream(temps, (longex)(content[pos].imgsize));
	return temps.makeFile(fileName);
}
long NPKobject::getVersion(long pos){
	long r;
	getData(4)->ptMoveTo(content[pos].imgoffset-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->ptMove(24);
	getData(4)->read(r);
	return r;
}
long NPKobject::getPaletteCount(long pos){
	if(getVersion(pos) != 6){
		return 0;
	}
	long r;
	getData(4)->ptMoveTo(content[pos].imgoffset-getData(1)->getLen() - getData(2)->getLen() - getData(3) -> getLen());
	getData(4)->ptMove(32);
	getData(4)->read(r);
	return r;
}
bool NPKobject::loadIndex(const str &fileName, std::vector<IMGversion> &versionList){
	stream data;
	stream s;
	if(!data.loadFile(fileName))
		return false;
	dword dword;
	long i;
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
		ii.imgoffset = dword;
		data.read(dword);
		ii.imgsize = dword;
		s.allocate(256);
		data.readStream(s, 256);
		s.nameMask();
		ii.imgname = (str)s;
		s.release();
		content.push_back(ii);
	}
	versionList.clear();
	for(i=0;i<count;i++){
		data.ptMoveTo(content[i].imgoffset);
		data.read(dword);
		if(dword == 0x706f654e){
			data.ptMoveTo(content[i].imgoffset+24);
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
	long num1,num2;
	dword dwTemp, i, j;
	longex ptStart, ptEnd;
	ptStart = 0;
	s.ptMoveTo(0);
	sz = s.readString(20);
	if(sz != "Neople Img File")
		return false;
	s.ptMoveTo(16);
	s.read(dwTemp);
	indexSize = dwTemp;
	s.read(dwTemp);
	s.read(dwTemp);
	version = (IMGversion)dwTemp;
	if(version != V2 && version != V4 && version != V5 && version != V6)
		return false;
	s.read(dwTemp);
	indexCount = dwTemp;
	if(version == V5){
		s.read(dwTemp);
		V5_TEXCount = dwTemp;
		s.read(dwTemp);
		V5_totalLength = dwTemp;
	}
	ptEnd = s.getPtPos();
	s.ptMoveTo(ptStart);
	getData(1)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(1), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	//////////////////////////////////////////
	dword clrCount = 0;
	dword pleCount = 0;
	colorList clrList;
	if(version == V4 || version == V5){
		s.read(clrCount);
		clrList.clear();
		for(i=0;i<clrCount;i++){
			s.read(dwTemp);
			clrList.push_back(color(dwTemp,INDEX_FMT_PALETTE));
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
				s.read(dwTemp);
				clrList.push_back(color(dwTemp, INDEX_FMT_PALETTE));
			}
			paletteData.push(clrList);
		}
	}
	ptEnd = s.getPtPos();
	s.ptMoveTo(ptStart);
	getData(2)->allocate(1000 + ptEnd - ptStart);
	s.readStream(*getData(2), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	//////////////////////////////////////
	TEXinfo di;
	TEXcontent.clear();
	if(version == V5){
		for(i=0;i<V5_TEXCount;i++){
			s.read(dwTemp);
			di.set_reserved(dwTemp);
			s.read(dwTemp);
			di.set_format((colorFormat)dwTemp);
			s.read(dwTemp);
			di.set_ID(dwTemp);
			s.read(dwTemp);
			di.set_compressedLength(dwTemp);
			s.read(dwTemp);
			di.set_dataLength(dwTemp);
			s.read(dwTemp);
			di.set_width(dwTemp & 0xFFFF);
			s.read(dwTemp);
			di.set_height(dwTemp & 0xFFFF);
			TEXcontent.push_back(di);
		}
	}
	ptEnd = s.getPtPos();
	s.ptMoveTo(ptStart);
	getData(3)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(3), ptEnd - ptStart);
	s.ptMoveTo(ptStart = ptEnd);
	///////////////////////////////////////
	PICinfo pi;
	PICcontent.clear();
	if(version != V1){
		for(i=0;i<indexCount;i++){
			s.read(dwTemp);
			pi.set_format((colorFormat)dwTemp);
			if(dwTemp == LINK){
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
				s.read(dwTemp);
				pi.set_comp((compressType)dwTemp);
				if(dwTemp == 0x05 || dwTemp == 0x06){
					s.read(num1);
					s.read(num2);
					pi.set_picSize(size(num1 & 0xFFFF, num2 & 0xFFFF));
					s.read(dwTemp);
					pi.set_dataSize(dwTemp);
					s.read(num1);
					s.read(num2);
					pi.set_basePt(point(num1, num2));
					s.read(num1);
					s.read(num2);
					pi.set_frmSize(size(num1, num2));

					pi.set_TEXusing(0);
					pi.set_TEXpointLT(point(0,0));
					pi.set_TEXpointRB(point(0,0));
				}else if(dwTemp == 0x07){
					s.read(num1);
					s.read(num2);
					pi.set_picSize(size(num1 & 0xFFFF, num2 & 0xFFFF));
					s.read(dwTemp);
					pi.set_dataSize(dwTemp);
					s.read(num1);
					s.read(num2);
					pi.set_basePt(point(num1, num2));
					s.read(num1);
					s.read(num2);
					pi.set_frmSize(size(num1, num2));
					s.read(dwTemp);
					s.read(dwTemp);
					pi.set_TEXusing(dwTemp);
					s.read(num1);
					s.read(num2);
					pi.set_TEXpointLT(point(num1 & 0xFFFF,num2 & 0xFFFF));
					s.read(num1);
					s.read(num2);
					pi.set_TEXpointRB(point(num1 & 0xFFFF,num2 & 0xFFFF));
					s.read(dwTemp);
				}else{
					//NODEF
				}
			}
			PICcontent.push_back(pi);
		}
	}
	ptEnd = s.getPtPos();
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
	longex fsize = 0;
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
	longex len1 = getData(1)->getLen();
	longex len2 = getData(2)->getLen();
	longex len3 = getData(3)->getLen();
	longex len4 = getData(4)->getLen();
	longex len5 = getData(5)->getLen();
	longex len6 = getData(6)->getLen();
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
		colorList clrList;
		clrList.clear();
		paletteData.push(clrList);
	}
	getData(1)->allocate(1024);
	getData(1)->pushString("Neople Img File");
	getData(1)->push((uchar)0);
	getData(1)->push((dword)(indexSize));
	getData(1)->push((dword)0);
	getData(1)->push((dword)(ver));
	getData(1)->push((dword)(indexCount));
	if(ver == V5){
		V5_totalLength = 44;
		getData(1)->push(V5_TEXCount);
		getData(1)->push(V5_totalLength);
	}
	//调色板数据
	getData(2)->allocate(1024);
	if(ver == V6){
		getData(2)->push((dword)1);
	}
	if(ver == V4 || ver == V5 || ver == V6){
		getData(2)->push((dword)0);
	}
	getData(3)->allocate(1024);
	getData(4)->allocate(1024);
	getData(5)->allocate(1024);
	getData(6)->allocate(1024);
	return true;
}
bool IMGobject::release(){
	dataHeader.release();
	dataPalette.release();
	dataIndexTexture.release();
	dataIndexPicture.release();
	dataTexture.release();
	dataPicture.release();
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
bool IMGobject::PICgetInfo(long pos, PICinfo &info){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	info = PICcontent[pos];
	return true;
}
bool IMGobject::PICgetBound(long pos, long &left, long &right, long &top, long &bottom){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	PICinfo info = PICcontent[pos];
	left = info.basePt.X;
	right = left + info.picSize.W - 1;
	top = info.basePt.Y;
	bottom = top + info.picSize.H - 1;
	return true;
}
bool IMGobject::PICgetTotalBound(long &left, long &right, long &top, long &bottom){
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
	bool origin = true;
	for(long i = 0;i<indexCount;i++){
		PICinfo pi;
		PICgetInfo(i, pi);
		if(pi.format != LINK && pi.picSize.area() != 1){
			if(origin){
				left = pi.basePt.X;
				right = left + pi.picSize.W-1;
				top = pi.basePt.Y;
				bottom = top + pi.picSize.H-1;
				origin = false;
			}else{
				if(pi.basePt.X < left){
					left = pi.basePt.X;
				}
				if(pi.basePt.X + pi.picSize.W - 1 > right){
					right = pi.basePt.X + pi.picSize.W - 1;
				}
				if(pi.basePt.Y < top){
					top = pi.basePt.Y;
				}
				if(pi.basePt.Y + pi.picSize.H - 1 > bottom){
					bottom = pi.basePt.Y + pi.picSize.H - 1;
				}
			}
			
		}
	}
	return !origin;
}
bool IMGobject::PICgetInfoOffset(long pos, longex &off){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	off = 0;
	for(long i=0;i<pos;i++){
		if(PICcontent[i].format == LINK){
			off += 8;
		}else if(PICcontent[i].comp <= COMP_ZLIB){
			//单索引模式
			off += 36;
		}else{
			//双索引模式
			off += 64;
		}
	}
	return true;
}
bool IMGobject::PICgetData(long pos, stream &s){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	longex size = (longex)PICcontent[pos].dataSize;
	longex offset;
	if(size == 0)
		return false;
	if(!PICgetDataOffset(pos, offset))
		return false;
	dataPicture.ptMoveTo(offset);
	dataPicture.readStream(s, size);
	return true;
}
bool IMGobject::PICgetDataOffset(long pos, longex &off){
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	long i;
	off = 0;
	for(i=0;i<pos;i++){
		if(PICcontent[i].format != LINK && PICcontent[i].comp <= COMP_ZLIB){
			off += (longex)PICcontent[i].dataSize;
		}
	}
	return true;
}
bool IMGobject::TEXgetInfo(long pos, TEXinfo &info){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	info = TEXcontent[pos];
	return true;
}
bool IMGobject::TEXgetInfoOffset(long pos, longex &off){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	off = 0;
	for(long i=0;i<pos;i++){
		off += 28;
	}
	return true;
}
bool IMGobject::TEXgetData(long pos, stream &s){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	longex offset;
	longex size = (longex)TEXcontent[pos].compressedLength;
	if(size == 0)
		return false;
	if(!TEXgetDataOffset(pos, offset))
		return false;
	getData(5)->ptMoveTo(offset);
	getData(5)->readStream(s, size);
	return true;
}
bool IMGobject::TEXgetDataOffset(long pos, longex &off){
	if(pos<0)
		return false;
	if(pos>=V5_TEXCount)
		return false;
	long i;
	off = 0;
	for(i=0;i<pos;i++){
		off += (longex)TEXcontent[i].get_compressedLength();
	}
	return true;
}
bool IMGobject::PICsetInfoPara(long pos, long term, void *pval){
	//Term: 0. linkTo 1. basePoint 2.frameSize 3.DDSID 4.pointLT, 5.pointRB
	if(pos<0)
		return false;
	if(pos>=indexCount)
		return false;
	long i = *(long*)pval;
	size sz = *(size*)pval;
	point pt = *(point*)pval;
	PICinfo pi;
	TEXinfo di;
	longex off;
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
			getData(4)->modify(off+20, pt.X);
			getData(4)->modify(off+24, pt.Y);
			return true;
		case 2:
			PICcontent[pos].set_frmSize(sz);
			getData(4)->modify(off+28, sz.W);
			getData(4)->modify(off+32, sz.H);
			return true;
		default:
			return false;
		}
	}else/*if(pi.get_comp() > COMP_ZLIB)*/{
		TEXgetInfo(pi.get_TEXusing(), di);
		switch(term){
		case 1:
			PICcontent[pos].set_basePt(pt);
			getData(4)->modify(off+20, pt.X);
			getData(4)->modify(off+24, pt.Y);
			return true;
		case 2:
			PICcontent[pos].set_frmSize(sz);
			getData(4)->modify(off+28, sz.W);
			getData(4)->modify(off+32, sz.H);
			return true;
		case 3:
			if(i<0 || i>=TEXcontent.size())
				return false;
			PICcontent[pos].set_TEXusing(i);
			getData(4)->modify(off+40, i);
			return true;
		case 4:
			if(pt.X<0 || pt.X>pi.get_TEXpointLT().X){
				return false;
			}
			if(pt.Y<0 || pt.Y>pi.get_TEXpointRB().Y){
				return false;
			}
			sz = size(pi.get_TEXpointRB().X-pt.X,
				pi.get_TEXpointRB().Y-pt.Y);
			PICcontent[pos].set_TEXpointLT(pt);
			PICcontent[pos].set_picSize(sz);
			getData(4)->modify(off+8,  sz.W);
			getData(4)->modify(off+12, sz.H);
			getData(4)->modify(off+44, pt.X);
			getData(4)->modify(off+48, pt.Y);
			return true;
		case 5:
			if(pt.X>di.get_width()-1 || pt.X<pi.get_TEXpointLT().X){
				return false;
			}
			if(pt.Y>di.get_height()-1 || pt.Y<pi.get_TEXpointLT().Y){
				return false;
			}
			sz = size(pt.X-pi.get_TEXpointLT().X,
				pt.Y-pi.get_TEXpointLT().Y);
			PICcontent[pos].set_TEXpointRB(pt);
			PICcontent[pos].set_picSize(sz);
			getData(4)->modify(off+8, sz.W);
			getData(4)->modify(off+12,sz.H);
			getData(4)->modify(off+52, pt.X);
			getData(4)->modify(off+56, pt.Y);
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
	sTemp.push((dword)info.get_format());
	if(info.get_format() == LINK){
		sTemp.push(info.get_linkTo());
		getData(4)->pushStream(sTemp, 8);
	}else if(info.get_comp() <= COMP_ZLIB){
		sTemp.push((dword)info.get_comp());
		sTemp.push(info.get_picSize().W);
		sTemp.push(info.get_picSize().H);
		sTemp.push(info.get_dataSize());
		sTemp.push(info.get_basePt().X);
		sTemp.push(info.get_basePt().Y);
		sTemp.push(info.get_frmSize().W);
		sTemp.push(info.get_frmSize().H);
		getData(4)->pushStream(sTemp, 36);
		getData(6)->pushStream(s, info.get_dataSize());
	}else{
		sTemp.push((dword)info.get_comp());
		sTemp.push(info.get_picSize().W);
		sTemp.push(info.get_picSize().H);
		sTemp.push((dword)0);
		sTemp.push(info.get_basePt().X);
		sTemp.push(info.get_basePt().Y);
		sTemp.push(info.get_frmSize().W);
		sTemp.push(info.get_frmSize().H);
		sTemp.push((dword)0);
		sTemp.push(info.get_TEXusing());
		sTemp.push(info.get_TEXpointLT().X);
		sTemp.push(info.get_TEXpointLT().Y);
		sTemp.push(info.get_TEXpointRB().X);
		sTemp.push(info.get_TEXpointRB().Y);
		sTemp.push((dword)0);
		getData(4)->pushStream(sTemp, 64);
	}
	//////////////////////////////////////////////////////////////////
	indexCount ++;
	indexSize = getData(4)->getLen();
	V5_totalLength = getSize();
	getData(1)->modify(16, (long)indexSize);
	getData(1)->modify(28, (long)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (long)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICinsert(long pos, const PICinfo &info, const stream &s){
	if(pos<0)
		pos += (indexCount + 1);
	if(pos<0)
		return false;
	if(pos>indexCount)
		return false;
	if(pos == indexCount)
		return PICpush(info, s);
	longex off1, off2;
	PICgetInfoOffset(pos, off1);
	PICgetDataOffset(pos, off2);
	PICcontent.insert(PICcontent.begin()+pos, info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push((dword)info.get_format());
	if(info.get_format() == LINK){
		sTemp.push(info.get_linkTo());
		getData(4)->insertStream(sTemp, 8, off1);
	}else if(info.get_comp() <= COMP_ZLIB){
		sTemp.push((dword)info.get_comp());
		sTemp.push(info.get_picSize().W);
		sTemp.push(info.get_picSize().H);
		sTemp.push(info.get_dataSize());
		sTemp.push(info.get_basePt().X);
		sTemp.push(info.get_basePt().Y);
		sTemp.push(info.get_frmSize().W);
		sTemp.push(info.get_frmSize().H);
		getData(4)->insertStream(sTemp, 36, off1);
		getData(6)->insertStream(s, info.get_dataSize(), off2);
	}else{
		sTemp.push((dword)info.get_comp());
		sTemp.push(info.get_picSize().W);
		sTemp.push(info.get_picSize().H);
		sTemp.push((dword)0);
		sTemp.push(info.get_basePt().X);
		sTemp.push(info.get_basePt().Y);
		sTemp.push(info.get_frmSize().W);
		sTemp.push(info.get_frmSize().H);
		sTemp.push((dword)0);
		sTemp.push(info.get_TEXusing());
		sTemp.push(info.get_TEXpointLT().X);
		sTemp.push(info.get_TEXpointLT().Y);
		sTemp.push(info.get_TEXpointRB().X);
		sTemp.push(info.get_TEXpointRB().Y);
		sTemp.push((dword)0);
		getData(4)->insertStream(sTemp, 64, off1);
	}
	//////////////////////////////////////////////////////////////////
	indexCount ++;
	indexSize = getData(4)->getLen();
	V5_totalLength = getSize();
	getData(1)->modify(16, (long)indexSize);
	getData(1)->modify(28, (long)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (long)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICremove(long pos){
	if(pos<0)
		pos += indexCount;
	if(pos<0)
		return false;
	if(pos>indexCount - 1)
		return false;
	PICinfo pi;
	longex off1,off2;
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
	getData(1)->modify(16, (long)indexSize);
	getData(1)->modify(28, (long)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (long)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICreplace(long pos, const PICinfo &info, const stream &s){
	if(pos<0)
		pos += indexCount;
	if(pos<0)
		return false;
	if(pos>indexCount - 1)
		return false;
	PICinfo pi;			//旧PICinfo
	longex off1,off2;
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
	sTemp.push((dword)info.get_format());
	if(info.get_format() == LINK){
		sTemp.push(info.get_linkTo());
		getData(4)->insertStream(sTemp, 8, off1);
	}else if(info.get_comp() <= COMP_ZLIB){
		sTemp.push((dword)info.get_comp());
		sTemp.push(info.get_picSize().W);
		sTemp.push(info.get_picSize().H);
		sTemp.push(info.get_dataSize());
		sTemp.push(info.get_basePt().X);
		sTemp.push(info.get_basePt().Y);
		sTemp.push(info.get_frmSize().W);
		sTemp.push(info.get_frmSize().H);
		getData(4)->insertStream(sTemp, 36, off1);
		getData(6)->insertStream(s, info.get_dataSize(), off2);
	}else{
		sTemp.push((dword)info.get_comp());
		sTemp.push(info.get_picSize().W);
		sTemp.push(info.get_picSize().H);
		sTemp.push((dword)0);
		sTemp.push(info.get_basePt().X);
		sTemp.push(info.get_basePt().Y);
		sTemp.push(info.get_frmSize().W);
		sTemp.push(info.get_frmSize().H);
		sTemp.push((dword)0);
		sTemp.push(info.get_TEXusing());
		sTemp.push(info.get_TEXpointLT().X);
		sTemp.push(info.get_TEXpointLT().Y);
		sTemp.push(info.get_TEXpointRB().X);
		sTemp.push(info.get_TEXpointRB().Y);
		sTemp.push((dword)0);
		getData(4)->insertStream(sTemp, 64, off1);
	}
	///////////////////////////////////////////
	indexSize = getData(4)->getLen();
	V5_totalLength = getSize();
	getData(1)->modify(16, (long)indexSize);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modify(36, (long)V5_totalLength);
	}
	return true;
}
bool IMGobject::PICextract(long pos, matrix &mat, long paletteID){
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
	long i;
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
				mat.create(pi.get_picSize());
				mat.push(sPic, pi.get_format());
				break;
			case V4:
				/*mat.create(pi.get_picSize());
				for(i=0;i<sPic.getLen();i++){
					if(sPic[i]>=paletteData[0].size())
						sPic[i] = 0;
					mat.push(paletteData[0][sPic[i]]);
				}*/
				if(sPic.getLen() == pi.get_picSize().area()){
					//索引形式
					mat.create(pi.get_picSize());
					for(i=0;i<sPic.getLen();i++){
						if(sPic[i]>=paletteData[0].size())
							sPic[i] = 0;
						mat.push(paletteData[0][sPic[i]]);
					}
				}else{
					//非索引形式
					mat.create(pi.get_picSize());
					mat.push(sPic, pi.get_format());
				}
				break;
			case V5:
				if(sPic.getLen() == pi.get_picSize().area()){
					//索引形式
					mat.create(pi.get_picSize());
					for(i=0;i<sPic.getLen();i++){
						if(sPic[i]>=paletteData[0].size())
							sPic[i] = 0;
						mat.push(paletteData[0][sPic[i]]);
					}
				}else{
					//非索引形式
					mat.create(pi.get_picSize());
					mat.push(sPic, pi.get_format());
				}
				break;
			case V6:
				mat.create(pi.get_picSize());
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
			mTemp.clip(mat,
				pi.get_TEXpointLT().Y,
				pi.get_TEXpointRB().Y,
				pi.get_TEXpointLT().X,
				pi.get_TEXpointRB().X
			);
		}
	}
	return true;
}
///////////////////////////////////////////
bool IMGobject::PICpreprocess(const matrix &mat, stream &s, PICinfo &info, colorFormat cf, long paletteID){
	if(cf == COLOR_UDEF){
		if(version == V2 || version == V5){
			cf = ARGB8888;
		}
		if(version == V4 || version == V6){
			cf = INDEX_FMT_PALETTE;
		}
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
		info.set_picSize(size(mat.getWidth(), mat.getHeight()));
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
		info.set_picSize(size(mat.getWidth(), mat.getHeight()));
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
		info.set_picSize(size(mat.getWidth(), mat.getHeight()));
		return true;
	}
	if(cf == INDEX_FMT_PALETTE){
		stream sTemp;
		sTemp.allocate(mat.getElemCount());
		for(long i = 0;i<mat.getElemCount();i++){
			if(paletteID >= paletteData.getCount() || paletteData[paletteID].size() == 0){
				sTemp.push((uchar)0);
				continue;
			}
			sTemp.push((uchar)paletteData.matchColor(mat.getElem(i)));
		}
		sTemp.compressData(s, COMP_ZLIB);
		sTemp.release();
		info.set_comp(COMP_ZLIB);
		info.set_format(ARGB1555);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(mat.getWidth(), mat.getHeight()));
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
bool IMGobject::PICextractIndexMatrix(long pos, matrix &mat){
	if(pos<0)
		pos += indexCount;
	if(pos<0)
		return false;
	if(pos>indexCount - 1)
		return false;
	if(version != V4 && version != V5 && version != V6)
		return false;
	long i;
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
			mat.create(pi.get_picSize());
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
	long i;
	stream sTemp;
	sTemp.allocate(mat.getElemCount());
	for(i=0;i<mat.getElemCount();i++){
		sTemp.push(mat.getElem(i).A);
	}
	sTemp.compressData(s, COMP_ZLIB);
	sTemp.release();
	info.set_comp(COMP_ZLIB);
	info.set_format(ARGB1555);
	info.set_dataSize(s.getLen());
	info.set_linkTo(-1);
	info.set_picSize(size(mat.getWidth(), mat.getHeight()));
	return true;
}
bool IMGobject::PICempty(stream &s, PICinfo &info){
	switch(version){
	case V2:
		s.allocate(4);
		s.push((dword)0);
		info.set_comp(COMP_NONE);
		info.set_format(ARGB8888);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
		return true;
	case V4:
		s.allocate(1);
		s.push((uchar)0);
		info.set_comp(COMP_NONE);
		info.set_format(ARGB1555);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
		return true;
	case V5:
		s.allocate(4);
		s.push((dword)0);
		info.set_comp(COMP_NONE);
		info.set_format(ARGB8888);
		info.set_dataSize(s.getLen());
		info.set_linkTo(-1);
		info.set_picSize(size(1,1));
		return true;
	case V6:
		s.allocate(1);
		s.push((uchar)0);
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
	sTemp.push((dword)info.get_format());
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
	getData(1)->modify(32, (long)V5_TEXCount);
	getData(1)->modify(36, (long)V5_totalLength);
	return true;
}
bool IMGobject::TEXinsert(long pos, const TEXinfo &info, const stream &s){
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
	longex off1, off2;
	TEXgetInfoOffset(pos, off1);
	TEXgetDataOffset(pos, off2);
	TEXcontent.insert(TEXcontent.begin()+pos, info);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((dword)info.get_format());
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
	getData(1)->modify(32, (long)V5_TEXCount);
	getData(1)->modify(36, (long)V5_totalLength);
	return true;
}
bool IMGobject::TEXremove(long pos){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_TEXCount;
	if(pos<0)
		return false;
	if(pos>V5_TEXCount-1)
		return false;
	TEXinfo di;
	longex off1,off2;
	TEXgetInfo(pos, di);
	TEXgetInfoOffset(pos, off1);
	TEXgetDataOffset(pos, off2);
	TEXcontent.erase(TEXcontent.begin()+pos);
	getData(3)->deleteStream(off1, 28);
	getData(5)->deleteStream(off2, di.get_compressedLength());
	//////////////////////////////////////////////////////////////////
	V5_TEXCount --;
	V5_totalLength = getSize();
	getData(1)->modify(32, (long)V5_TEXCount);
	getData(1)->modify(36, (long)V5_totalLength);
	return true;
}
bool IMGobject::TEXreplace(long pos, const TEXinfo &info, const stream &s){
	if(version != V5)
		return false;
	if(pos<0)
		pos += V5_TEXCount;
	if(pos<0)
		return false;
	if(pos>V5_TEXCount-1)
		return false;
	TEXinfo di;
	longex off1,off2;
	TEXgetInfo(pos, di);
	TEXgetInfoOffset(pos, off1);
	TEXgetDataOffset(pos, off2);
	TEXcontent[pos] = info;
	getData(3)->deleteStream(off1, 28);
	getData(5)->deleteStream(off2, di.get_compressedLength());
	stream sTemp;
	sTemp.allocate(100);
	sTemp.push(info.get_reserved());
	sTemp.push((dword)info.get_format());
	sTemp.push(info.get_ID());
	sTemp.push(info.get_compressedLength());
	sTemp.push(info.get_dataLength());
	sTemp.push(info.get_height());
	sTemp.push(info.get_width());
	getData(3)->insertStream(sTemp, 28, off1);
	getData(5)->insertStream(s, info.get_compressedLength(), off2);
	////////////////////////////////////////
	V5_totalLength = getSize();
	getData(1)->modify(32, (long)V5_TEXCount);
	getData(1)->modify(36, (long)V5_totalLength);
	return true;
}
bool IMGobject::TEXextract(long pos, matrix &mat){
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
			mat.create(di.get_height(), di.get_width());
			for(int i=0;i<sPic.getLen();i++){
				if(sPic[i]>=paletteData[0].size()){
					sPic[i] = 0;
				}
				mat.push(paletteData[0][sPic[i]]);
			}
		}else{
			mat.create(di.get_height(), di.get_width());
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
		info.set_width(mat.getWidth());
		info.set_height(mat.getHeight());
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
		info.set_width(mat.getWidth());
		info.set_height(mat.getHeight());
		info.set_ID(V5_TEXCount);
		sTemp.release();
		return true;
	}
	if(cf == ARGB1555){
		stream sTemp;
		mat.make(sTemp, ARGB1555);
		sTemp.compressData(s, COMP_ZLIB);
		info.reserved = 1;
		info.format = ARGB1555;
		info.dataLength = sTemp.getLen();
		info.compressedLength = s.getLen();
		info.set_width(mat.getWidth());
		info.set_height(mat.getHeight());
		info.set_ID(V5_TEXCount);
		sTemp.release();
		return true;
	}
	if(cf == INDEX_FMT_PALETTE){
		stream sTemp;
		sTemp.allocate(mat.getElemCount());
		for(long i = 0;i<mat.getElemCount();i++){
			if(paletteData.getCount() == 0 || paletteData[0].size() == 0){
				sTemp.push((uchar)0);
				continue;
			}
			sTemp.push((uchar)paletteData.matchColor(mat.getElem(i)));
		}
		sTemp.compressData(s, COMP_ZLIB);
		info.reserved = 1;
		info.format = ARGB1555;
		info.dataLength = sTemp.getLen();
		info.compressedLength = s.getLen();
		info.width = mat.getWidth();
		info.height = mat.getHeight();
		info.ID = V5_TEXCount;
		sTemp.release();
		return true;
	}
	return false;
}
bool IMGobject::CLRpush(const color &clr, long paletteID){
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
bool IMGobject::CLRinsert(long pos, const color &clr, long paletteID){
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
bool IMGobject::CLRremove(long pos, long paletteID){
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
	if(paletteData[paletteID].size() == 0)
		return false;
	paletteData[paletteID].erase(paletteData[paletteID].begin()+pos);
	getData(2)->release();
	if(version != V6)
		paletteData.tinyMake(*getData(2), 0);
	if(version == V6)
		paletteData.bigMake(*getData(2));
	return true;
}
bool IMGobject::CLRreplace(long pos, const color &clr, long paletteID){
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
	colorList clrList;
	clrList.clear();
	paletteData.push(clrList);
	getData(2)->release();
	paletteData.bigMake(*getData(2));
	return true;
}
bool IMGobject::CLRdeletePalette(long paletteID){
	if(version != V6){
		return false;
	}
	if(paletteID >= paletteData.getCount() || paletteID < 0){
		return false;
	}
	paletteData.remove(paletteID);
	getData(2)->release();
	paletteData.bigMake(*getData(2));
	return true;
}
//转版本2方案
//将既定贴图完全提取出矩阵，然后转成ARGB1555/4444/8888形式
//若原版本为6，则分拆成若干，存入newIOList
bool IMGobject::convertToV2(std::vector<IMGobject> &newIOList, colorFormat cf){
	newIOList.clear();
	long paletteCount = 1;
	if(version == V6)
		paletteCount = paletteData.getCount();
	for(long paletteID = 0;paletteID < paletteCount; paletteID ++){
		IMGobject newIO;
		newIO.create(V2);
		for(long i = 0;i<indexCount;i++){
			PICinfo pi;
			PICgetInfo(i, pi);
			if(pi.format == LINK){
				newIO.PICpush(pi, NULL);
			}else{
				matrix mPic;
				stream sPic;
				PICextract(i, mPic, paletteID);
				newIO.PICpreprocess(mPic, sPic, pi, cf);
				newIO.PICpush(pi, sPic);
				mPic.destory();
				sPic.release();
			}
		}
		newIOList.push_back(newIO);
		newIO.release();
	}
	return true;
}
//转版本4方案
//若原版本为4或6，则输入调色板无效(除非设置useOriginPalette为false)
//若原版本为4，则无视输入调色板直接将原IMG存入newIOList
//若原版本为6，则无视输入调色板，并将原版本调色板分拆后，保留贴图数据，存入newIOList
//若原版本为其他版本，则提取出矩阵，然后与输入颜色版匹配，存入newIOList
bool IMGobject::convertToV4(std::vector<IMGobject> &newIOList, colorList useColorPalette, bool useOriginPalette){
	newIOList.clear();
	long paletteCount = 1;
	if(version == V6)
		paletteCount = paletteData.getCount();
	for(long paletteID = 0;paletteID < paletteCount; paletteID ++){
		IMGobject newIO;
		if(useOriginPalette && version == V4){
			newIO =*this;
		}else if(useOriginPalette && version == V6){
			newIO.create(V4);
			newIO.paletteData.clear();
			newIO.paletteData.push(paletteData[paletteID]);
			newIO.getData(2)->release();
			newIO.paletteData.tinyMake(*(newIO.getData(2)));
			//复制贴图内容
			for(long i = 0;i<indexCount;i++){
				PICinfo pi;
				PICgetInfo(i, pi);
				if(pi.format == LINK){
					newIO.PICpush(pi, NULL);
				}else{
					stream sPic;
					PICgetData(i, sPic);
					newIO.PICpush(pi, sPic);
					sPic.release();
				}
			}
		}else{
			//非索引转V4，使用既定调色板
			newIO.create(V4);
			newIO.paletteData.clear();
			newIO.paletteData.push(useColorPalette);
			newIO.getData(2)->release();
			newIO.paletteData.tinyMake(*(newIO.getData(2)));
			//将贴图内容与调色板比较匹配
			for(long i = 0;i<indexCount;i++){
				PICinfo pi;
				PICgetInfo(i, pi);
				if(pi.format == LINK){
					newIO.PICpush(pi, NULL);
				}else{
					matrix mPic;
					stream sPic;
					PICextract(i, mPic, paletteID);
					newIO.PICpreprocess(mPic, sPic, pi);
					newIO.PICpush(pi, sPic);
					mPic.destory();
					sPic.release();
				}
			}
		}
		newIOList.push_back(newIO);
		newIO.release();
	}
	return true;
}
//转版本5方案
//将输入调色板作为新的V5调色板
bool IMGobject::convertToV5(std::vector<IMGobject> &newIOList, colorFormat cf, colorList useColorPalette, bool makeTexture){
	newIOList.clear();
	long paletteCount = 1;
	if(version == V6)
		paletteCount = paletteData.getCount();
	for(long paletteID = 0;paletteID < paletteCount; paletteID ++){
		IMGobject newIO;
		newIO.create(V5);
		for(long i = 0;i<indexCount;i++){
			PICinfo pi;
			PICgetInfo(i, pi);
			if(pi.format == LINK){
				newIO.PICpush(pi, NULL);
			}else{
				//V5的调色板，使用既定调色板
				newIO.paletteData.clear();
				newIO.paletteData.push(useColorPalette);
				newIO.getData(2)->release();
				newIO.paletteData.tinyMake(*(newIO.getData(2)));
				//贴图处理
				if(makeTexture){
					//制作纹理集
					TEXinfo ti;
					matrix mPic;
					stream sPic;
					PICextract(i, mPic, paletteID);
					newIO.TEXpreprocess(mPic, sPic, ti, cf);
					newIO.TEXpush(ti, sPic);
					mPic.destory();
					sPic.release();
					pi.format = ti.format;
					pi.comp = COMP_ZLIB2;
					pi.dataSize = 0;
					pi.picSize = size(ti.width, ti.height);
					pi.TEXusing = newIO.V5_TEXCount - 1;
					pi.TEXpointLT = point(0, 0);
					pi.TEXpointRB = point(ti.width, ti.height);
					newIO.PICpush(pi, NULL);
				}else{
					matrix mPic;
					stream sPic;
					PICextract(i, mPic, paletteID);
					newIO.PICpreprocess(mPic, sPic, pi, cf);
					newIO.PICpush(pi, sPic);
					mPic.destory();
					sPic.release();
				}
			}
		}
		newIOList.push_back(newIO);
		newIO.release();
	}
	return true;
}
//
bool IMGobject::convertToV6(std::vector<IMGobject> &newIOList, colorTable useColorPaletteList, bool useOriginPalette){
	newIOList.clear();
	//原版本V6 & 保留原调色板：不变
	if(version == V6 && useOriginPalette){
		IMGobject newIO;
		newIO = *this;
		newIOList.push_back(newIO);
		return true;
	}
	//原版本V4 & 保留原调色板 ：直接变成V6
	if(version == V4 && useOriginPalette){
		IMGobject newIO;
		newIO.create(V6);
		newIO.paletteData.clear();
		newIO.paletteData.push(paletteData[0]);
		newIO.getData(2)->release();
		newIO.paletteData.bigMake(*(newIO.getData(2)));
		for(long i = 0;i<indexCount;i++){
			PICinfo pi;
			PICgetInfo(i, pi);
			if(pi.format == LINK){
				newIO.PICpush(pi, NULL);
			}else{
				stream sPic;
				PICgetData(i, sPic);
				newIO.PICpush(pi, sPic);
				sPic.release();
			}
		}
		newIOList.push_back(newIO);
		return true;
	}
	//不保留调色板：使用既定调色板，并按第一个调色板进行颜色匹配，原版本为V6则拆成若干
	long paletteCount = 1;
	if(version == V6)
		paletteCount = paletteData.getCount();
	for(long paletteID = 0;paletteID < paletteCount; paletteID ++){
		IMGobject newIO;
		//非索引转V6，使用既定调色板
		newIO.create(V6);
		newIO.paletteData.clear();
		for(long i = 0;i<useColorPaletteList.size();i++){
			newIO.paletteData.push(useColorPaletteList[i]);
		}
		newIO.getData(2)->release();
		newIO.paletteData.bigMake(*(newIO.getData(2)));
		//将贴图内容与调色板比较匹配
		for(long i = 0;i<indexCount;i++){
			PICinfo pi;
			PICgetInfo(i, pi);
			if(pi.format == LINK){
				newIO.PICpush(pi, NULL);
			}else{
				matrix mPic;
				stream sPic;
				PICextract(i, mPic, paletteID);
				newIO.PICpreprocess(mPic, sPic, pi);
				newIO.PICpush(pi, sPic);
				mPic.destory();
				sPic.release();
			}
		}
		newIOList.push_back(newIO);
		newIO.release();
	}
	return true;
}

long IMGobject::linkFind(dword pos, dword depth){
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
bool IMGobject::empty(){
	long count = indexCount;
	IMGversion iv = version;
	release();
	create(iv);
	////////////////////////
	PICinfo pi;
	stream s;
	PICempty(s, pi);
	PICpush(pi, s);
	for(long i = 1;i<count;i++){
		pi.set_format(LINK);
		pi.set_linkTo(0);
		PICpush(pi, s);
	}
	s.release();
	return true;
}
void IMGobject::makeEmpty(IMGobject &newIO, int frameCount){
	newIO.create(V2);
	PICinfo pi;
	pi.basePt = point(0,0);
	pi.comp = COMP_NONE;
	pi.dataSize = 2;
	pi.format = ARGB4444;
	pi.frmSize = size(1, 1);
	pi.picSize = size(1, 1);
	stream s;
	s.allocate(2);
	s.push((word)0);
	newIO.PICpush(pi, s);
	pi.format = LINK;
	pi.linkTo = 0;
	for(int i = 0;i<frameCount;i++){
		newIO.PICpush(pi, s);
	}
	s.release();
}
bool IMGobject::checkIsOld(stream &s){
	s.ptMoveTo(0);
	str sz = s.readString(20);
	if(sz != "Neople Image File")
		return false;
	dword dwTemp, dwVersion;
	s.read(dwTemp);	//保留位
	s.read(dwVersion); //版本
	if(dwVersion != V1)
		return false;
	return true;
}
stream *IMGobject::getData(uchar _part){
	stream *sList[] = {NULL, &dataHeader, &dataPalette, &dataIndexTexture, &dataIndexPicture, &dataTexture, &dataPicture};
	return sList[_part%7];
}
longex IMGobject::getSize() const{
	return dataHeader.getLen()+dataPalette.getLen()+dataIndexTexture.getLen()+dataIndexPicture.getLen()+dataTexture.getLen()+dataPicture.getLen();
}
