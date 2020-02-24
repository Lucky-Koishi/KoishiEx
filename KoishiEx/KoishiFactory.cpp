#include "StdAfx.h"
#include "KoishiEx.h"
#include "KoishiImageTool.h"
#include "KoishiNeoplePack.h"
#include <assert.h>

#define NEW_NPK_METHOD 1

using namespace Koishi;
using namespace KoishiNeoplePack;
using KoishiImageTool::DDS::DDSobject;
/////////有用的结构体的初始化////////////////////////////////////////////////////////
NPKentry::NPKentry(){
	comment = "";
	link = -1;
}
NPKentry::NPKentry(const str pathName, int blockID){
	comment = pathName;
	link = blockID;
}
NPKobject::NPKobject(){
	release();
}
NPKobject::NPKobject(const stream &in){
	load(in);
}
NPKobject::NPKobject(const str &fileName){
	loadFile(fileName);
}
//////////////////////////////////////////////////////////////////////////////////////
//Main Factory
//////////////////////////////////////////////////////////////////////////////////////
bool NPKobject::load(const stream &in){
	stream data(in);
	data.resetPosition();
	if(data.length < 20)
		return false;
	if(data.readString(16) != "NeoplePack_Bill")
		return false;
	data.readDWord(count);
	if(data.length < count*264 + 52)
		return false;
	queue offsetInEntry, sizeInEntry;
	queue offsetInBlock, sizeInBlock;
	entry.clear();
	block.clear();
	entry.reserve(count);
	block.reserve(count);
	offsetInEntry.reserve(count);
	offsetInBlock.reserve(count);
	sizeInEntry.reserve(count);
	sizeInBlock.reserve(count);
	for(int i = 0;i<count;i++){
		stream sPath(0x100);
		long num;
		data.readInt(num);
		offsetInEntry.push_back(num);
		data.readInt(num);
		sizeInEntry.push_back(num);
		data.readStream(sPath, 0x100);
		sPath.nameMask();
		entry.push_back(NPKentry((char*)sPath.begin(), -1));
	}
	if(true){
		stream checkCode;
		data.readStream(checkCode, 32);
	}
	for(int i = 0;i<count;i++){
		int findBlock = -1;
		for(int j = 0;j<block.size();j++){
			if(sizeInBlock[j] == sizeInEntry[i] && offsetInBlock[j] == offsetInEntry[i]){
				findBlock = j;
				break;
			}
		}
		if(findBlock >= 0){
			entry[i].link = findBlock;
		}else{
			stream blockData;
			offsetInBlock.push_back(offsetInEntry[i]);
			sizeInBlock.push_back(sizeInEntry[i]);
			data.setPosition(offsetInEntry[i]);
			data.readStream(blockData, sizeInEntry[i]);
			block.push_back(blockData);
			entry[i].link = block.size()-1;
		}
	}
	return true;
}
bool NPKobject::make(stream &out){
	longex preLen = 0;		//数据段预计大小
	long coff = 0;		//偏移量
	for(int i = 0;i<block.size();i++){
		preLen += block[i].length;
	}
	stream data;
	data.allocate(1000 + preLen);
	out.allocate(count * 264 + 1000 + preLen);
	out.pushString("NeoplePack_Bill");
	out.pushByte(0);
	out.pushDWord(count);
	coff = count * 264 + 52;
	queue offsetInEntry, sizeInEntry;
	offsetInEntry.reserve(count);
	sizeInEntry.reserve(count);
	for(int i = 0;i<count;i++){
		long lfs = checkLink(i);
		if(lfs == i){
			offsetInEntry.push_back(coff);
			sizeInEntry.push_back(block[entry[i].link].length);
			data.pushStream(block[entry[i].link], block[entry[i].link].length);
			coff += block[entry[i].link].length;
		}else{
			offsetInEntry.push_back(offsetInEntry[lfs]);
			sizeInEntry.push_back(sizeInEntry[lfs]);
		}
		stream sPath(512);
		sPath.pushString(entry[i].comment);
		while(sPath.length < 256)
			sPath.pushByte(0);
		sPath.nameMask();
		out.pushInt(offsetInEntry[i]);
		out.pushInt(sizeInEntry[i]);
		out.pushStream(sPath, 256);
	}
	stream checkCode, head(count * 264 + 52);
	head.pushStream(out, out.length / 17 * 17);
	head.SHA256code(checkCode);
	out.pushStream(checkCode, 32);
	out.pushStream(data, data.length);
	return true;
}
bool NPKobject::loadFile(const str &fileName){
	stream data;
	if(!data.loadFile(fileName))
		return false;
	if(!load(data))
		return false;
	return true;
}
bool NPKobject::saveFile(const str &fileName){
	stream data;
	if(!make(data))
		return false;
	if(!data.makeFile(fileName))
		return false;
	return true;
}
bool NPKobject::create(){
	count = 0;
	block.clear();
	entry.clear();
	return true;
}
bool NPKobject::release(){
	count = 0;
	block.clear();
	entry.clear();
	return true;
}
longex NPKobject::getSize() const{
	longex preLen = 0;
	for(int i = 0;i<block.size();i++){
		preLen += block[i].length;
	}
	return count * 264 + 52 + preLen;
}
//数据流接口
bool NPKobject::extract(long pos, stream &dest){
	if(pos < 0 || pos >= count)
		return false;
	dest = block[entry[pos].link];
	return true;
}
bool NPKobject::push(const stream &sour, const str &imgName){
	block.push_back(sour);
	entry.push_back(NPKentry(imgName, block.size()-1));
	count ++;
	return true;
}
bool NPKobject::insert(long pos, const stream &sour, const str &imgName){
	if(pos < 0 || pos > count)
		return false;
	if(pos == count)
		return push(sour, imgName);
	block.push_back(sour);
	entry.insert(entry.begin() + pos, NPKentry(imgName, block.size()-1));
	count ++;
	return true;
}
bool NPKobject::remove(long pos){
	if(pos < 0 || pos >= count)
		return false;
	entry.erase(entry.begin() + pos);
	count --;
	return true;
}
bool NPKobject::replace2(long pos, const stream &sour){
	if(pos < 0 || pos >= count)
		return false;
	block.push_back(sour);
	entry[pos].link = block.size()-1;
	return true;
}
bool NPKobject::replace(long pos, const stream &sour){
	if(pos < 0 || pos >= count)
		return false;
	block[entry[pos].link].release();
	block[entry[pos].link] = sour;
	return true;
}
bool NPKobject::pushLink(long linkPos, const str &pathName){
	if(linkPos < 0 || linkPos >= count)
		return false;
	entry.push_back(NPKentry(pathName, entry[linkPos].link));
	count ++;
	return true;
}
bool NPKobject::insertLink(long pos, long linkPos, const str &pathName){
	if(linkPos < 0 || linkPos >= count || pos < 0 || pos >= count)
		return false;
	if(pos == count)
		return pushLink(linkPos, pathName);
	entry.insert(entry.begin()+pos, NPKentry(pathName, entry[linkPos].link));
	count ++;
	return true;
}
bool NPKobject::modifyLink(long pos, long newLinkPos){
	if(newLinkPos < 0 || newLinkPos >= count || pos < 0 || pos >= count)
		return false;
	entry[pos].link = newLinkPos;
	return true;
}
bool NPKobject::delink(long pos){
	if(pos < 0 || pos >= count)
		return false;
	replace2(pos, block[entry[pos].link]);
	return true;
}
long NPKobject::checkLink(long pos) const{
	//检查在其前的Entry是否有与其映射到同一数据块
	for(int i = 0;i<count;i++){
		if(entry[pos].link == entry[i].link){
			return i;
		}
	}
	return pos;
}
bool NPKobject::rename(long pos, const str& newName){
	if(pos < 0 || pos >= count)
		return false;
	entry[pos].comment = newName;
	return true;
}
bool NPKobject::find(const str &keyword, dword &pos, long startPos){
	for(long i = startPos;i<count;i++){
		if(entry[i].comment.find(keyword) != str::npos){
			pos = i;
			return true;
		}
	}
	return false;
}
bool NPKobject::find(const str &keyword, const str &nonkeyword, dword &pos, long startPos){
	for(long i = startPos;i<count;i++){
		if(entry[i].comment.find(keyword) != str::npos && entry[i].comment.find(nonkeyword) == str::npos){
			pos = i;
			return true;
		}
	}
	return false;
}
//文件接口
bool NPKobject::extract(long pos, const str &fileName){
	stream fs;
	if(!extract(pos, fs))
		return false;
	return fs.makeFile(fileName);
}
bool NPKobject::push(const str &fileName, const str &pathName){
	stream fs;
	if(!fs.loadFile(fileName))
		return false;
	return push(fs, pathName);
}
bool NPKobject::insert(long pos, const str &fileName, const str &pathName){
	stream fs;
	if(!fs.loadFile(fileName))
		return false;
	return insert(pos, fs, pathName);
}
bool NPKobject::replace(long pos, const str &fileName){
	stream fs;
	if(!fs.loadFile(fileName))
		return false;
	return replace(pos, fs);
}
//IMG对象的接口
bool NPKobject::IMGextract(dword pos, IMGobject &io){
	if(pos<0 || pos >= count)
		return false;
	stream dataIO;
	if(!extract(pos, dataIO))
		return false;
	if(!io.load(dataIO))
		return false;
	io.derived = &entry[pos];
	return true;
}
bool NPKobject::IMGpush(IMGobject &io, const str &imgName){
	stream dataIO;
	io.make(dataIO);
	return push(dataIO, imgName);
}
bool NPKobject::IMGinsert(long pos, IMGobject &io, const str &imgName){
	stream dataIO;
	io.make(dataIO);
	return insert(pos, dataIO, imgName);
}
bool NPKobject::IMGremove(long pos){
	return remove(pos);
}
bool NPKobject::IMGreplace(long pos, IMGobject &io){
	stream dataIO;
	io.make(dataIO);
	return replace(pos, dataIO);
}
bool NPKobject::IMGrename(long pos, const str& newName){
	return rename(pos, newName);
}
long NPKobject::IMGgetVersion(long pos){
	long r;
	stream &s = block[entry[pos].link];
	s.resetPosition();
	s.readInt(r);
	if(r == 0x706F654E){
		s.movePosition(20);
		s.readInt(r);
		if(r == 1 || r == 2 || r == 4 || r == 5 || r == 6){
			return r;
		}
		return VUKNOWN;
	}else if(r == 0x5367674F){
		return VSOUND;//OggS
	}else if(r == 0x46464952){
		return VSOUND;//RIFF
	}else if((r & 0xFFFFFF) == 0x334449 || (r & 0xF0FF) == 0xF0FF){
		return VSOUND;//MP3
	}
	return VUDEF;		//根本就不是支持的文件
}
long NPKobject::IMGgetPaletteCount(long pos){
	long r;
	stream &s = block[entry[pos].link];
	s.resetPosition();
	s.readInt(r);
	if(r != 0x706F654E)
		return 0;
	s.movePosition(20);
	s.readInt(r);
	if(r != 6)
		return 0;
	s.movePosition(4);
	s.readInt(r);
	return r;
}
long NPKobject::SNDgetVersion(long pos){
	long r;
	stream &s = block[entry[pos].link];
	s.resetPosition();
	s.readInt(r);
	if(r == 0x706F654E){
		return VIMAGE;
	}else if(r == 0x5367674F){
		return VVORBIS;//OggS
	}else if(r == 0x46464952){
		return VWAVE;//RIFF
	}else if((r & 0xFFFFFF) == 0x334449 || (r & 0xF0FF) == 0xF0FF){
		return VMP3;//MP3
	}
	return VSNDUKNOWN;		//根本就不是支持的文件
}
//////////////////////////////////////////////////////////////////////////////////////
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
	dword i, j;
	longex ptStart, ptEnd;
	ptStart = 0;
	s.resetPosition();
	if(s.readString(16) != "Neople Img File")
		return false;
	s.readDWord(indexSize);
	s.movePosition(4);
	s.read(&version, 4);
	s.readDWord(indexCount);
	//if(version != V2 && version != V4 && version != V5 && version != V6)
	//	return false;
	if(version == V5){
		s.readDWord(V5_TEXCount);
		s.readDWord(V5_totalLength);
	}
	ptEnd = s.getPosition();
	s.setPosition(ptStart);
	getData(1)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(1), ptEnd - ptStart);
	s.setPosition(ptStart = ptEnd);
	//////////////////////////////////////////
	dword clrCount = 0;
	dword pleCount = 0;
	colorList clrList;
	if(version == V4 || version == V5){
		s.readDWord(clrCount);
		clrList.clear();
		for(i=0;i<clrCount;i++){
			dword dwTemp;
			s.readDWord(dwTemp);
			clrList.push_back(color(dwTemp,INDEX_FMT_PALETTE));
		}
		paletteData.clear();
		paletteData.push(clrList);
	}
	if(version == V6){
		s.readDWord(pleCount);
		for(i=0;i<pleCount;i++){
			s.readDWord(clrCount);
			clrList.clear();
			for(j=0;j<clrCount;j++){
				dword dwTemp;
				s.readDWord(dwTemp);
				clrList.push_back(color(dwTemp, INDEX_FMT_PALETTE));
			}
			paletteData.push(clrList);
		}
	}
	ptEnd = s.getPosition();
	s.setPosition(ptStart);
	getData(2)->allocate(1000 + ptEnd - ptStart);
	s.readStream(*getData(2), ptEnd - ptStart);
	s.setPosition(ptStart = ptEnd);
	//////////////////////////////////////
	TEXinfo di;
	TEXcontent.clear();
	if(version == V5){
		for(i=0;i<V5_TEXCount;i++){
			s.readDWord(di.reserved);
			s.read(&di.format, 4);
			s.readDWord(di.ID);
			s.readDWord(di.compressedLength);
			s.readDWord(di.dataLength);
			s.readDWord(di.width);
			s.readDWord(di.height);
			di.width &= 0xFFFF;
			di.height &= 0xFFFF;
			TEXcontent.push_back(di);
		}
	}
	ptEnd = s.getPosition();
	s.setPosition(ptStart);
	getData(3)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(3), ptEnd - ptStart);
	s.setPosition(ptStart = ptEnd);
	///////////////////////////////////////
	PICinfo pi;
	PICcontent.clear();
	if(version != V1){
		for(i=0;i<indexCount;i++){
			s.read(&pi.format, 4);
			if(pi.format == LINK){
				s.readInt(pi.linkTo);
			}else{
				s.read(&pi.comp, 4);
				if(pi.comp == 0x05 || pi.comp == 0x06){
					s.readInt(pi.picSize.W);
					s.readInt(pi.picSize.H);
					s.readDWord(pi.dataSize);
					s.readInt(pi.basePt.X);
					s.readInt(pi.basePt.Y);
					s.readInt(pi.frmSize.W);
					s.readInt(pi.frmSize.H);
				}else if(pi.comp == 0x07){
					s.readInt(pi.picSize.W);
					s.readInt(pi.picSize.H);
					pi.picSize.W &= 0xFFFF;
					pi.picSize.H &= 0xFFFF;
					s.readDWord(pi.dataSize);
					s.readInt(pi.basePt.X);
					s.readInt(pi.basePt.Y);
					s.readInt(pi.frmSize.W);
					s.readInt(pi.frmSize.H);
					s.movePosition(4);
					s.readDWord(pi.TEXusing);
					s.readInt(pi.TEXpointLT.X);
					s.readInt(pi.TEXpointLT.Y);
					s.readInt(pi.TEXpointRB.X);
					s.readInt(pi.TEXpointRB.Y);
					pi.TEXpointLT.X &= 0xFFFF;
					pi.TEXpointLT.Y &= 0xFFFF;
					pi.TEXpointRB.X &= 0xFFFF;
					pi.TEXpointRB.Y &= 0xFFFF;
					s.movePosition(4);
				}else{
					//NODEF
				}
			}
			PICcontent.push_back(pi);
		}
	}
	ptEnd = s.getPosition();
	s.setPosition(ptStart);
	getData(4)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(4), ptEnd - ptStart);
	if(ptEnd - ptStart >= indexSize){
		//真实索引表大小>给定索引表大小
		s.setPosition(ptStart = ptEnd);
	}else{
		//真实索引表大小<给定索引表大小
		s.setPosition(ptStart = ptStart + indexSize);
	}
	///////////////////////////////////////
	longex fsize = 0;
	for(i=0;i<TEXcontent.size();i++){
		fsize += TEXcontent[i].compressedLength;
	}
	getData(5)->allocate(s.length);
	s.readStream(*getData(5), fsize);
	///////////////////////////////////////
	getData(6)->allocate(s.length);
	s.readStream(*getData(6), s.length);
	return result;
}
bool IMGobject::make(stream &s){
	longex len1 = getData(1)->length;
	longex len2 = getData(2)->length;
	longex len3 = getData(3)->length;
	longex len4 = getData(4)->length;
	longex len5 = getData(5)->length;
	longex len6 = getData(6)->length;
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
	getData(1)->pushByte((uchar)0);
	getData(1)->pushDWord((dword)(indexSize));
	getData(1)->pushDWord((dword)0);
	getData(1)->pushDWord((dword)(ver));
	getData(1)->pushDWord((dword)(indexCount));
	if(ver == V5){
		V5_totalLength = 44;
		getData(1)->pushDWord(V5_TEXCount);
		getData(1)->pushDWord(V5_totalLength);
	}
	//调色板数据
	getData(2)->allocate(1024);
	if(ver == V6){
		getData(2)->pushDWord((dword)1);
	}
	if(ver == V4 || ver == V5 || ver == V6){
		getData(2)->pushDWord((dword)0);
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
	dataPicture.setPosition(offset);
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
	getData(5)->setPosition(offset);
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
		off += (longex)TEXcontent[i].compressedLength;
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
	if(pi.format == LINK){
		switch(term){
		case 0:
			if(i<0 || i>indexCount-1)
				return false;
			if(PICcontent[i].format == LINK)
				return false;
			PICcontent[pos].linkTo = i;
			getData(4)->modifyInt(off+4, i);
			return true;
		default:
			return false;
		}
	}else if(pi.comp <= COMP_ZLIB){
		switch(term){
		case 1:
			PICcontent[pos].basePt = pt;
			getData(4)->modifyInt(off+20, pt.X);
			getData(4)->modifyInt(off+24, pt.Y);
			return true;
		case 2:
			PICcontent[pos].frmSize = sz;
			getData(4)->modifyInt(off+28, sz.W);
			getData(4)->modifyInt(off+32, sz.H);
			return true;
		default:
			return false;
		}
	}else/*if(pi.comp > COMP_ZLIB)*/{
		TEXgetInfo(pi.TEXusing, di);
		switch(term){
		case 1:
			PICcontent[pos].basePt = pt;
			getData(4)->modifyInt(off+20, pt.X);
			getData(4)->modifyInt(off+24, pt.Y);
			return true;
		case 2:
			PICcontent[pos].frmSize = sz;
			getData(4)->modifyInt(off+28, sz.W);
			getData(4)->modifyInt(off+32, sz.H);
			return true;
		case 3:
			if(i<0 || i>=TEXcontent.size())
				return false;
			PICcontent[pos].TEXusing = i;
			getData(4)->modifyInt(off+40, i);
			return true;
		case 4:
			if(pt.X<0 || pt.X>pi.TEXpointLT.X){
				return false;
			}
			if(pt.Y<0 || pt.Y>pi.TEXpointRB.Y){
				return false;
			}
			sz = size(pi.TEXpointRB.X-pt.X,
				pi.TEXpointRB.Y-pt.Y);
			PICcontent[pos].TEXpointLT = pt;
			PICcontent[pos].picSize = sz;
			getData(4)->modifyInt(off+8,  sz.W);
			getData(4)->modifyInt(off+12, sz.H);
			getData(4)->modifyInt(off+44, pt.X);
			getData(4)->modifyInt(off+48, pt.Y);
			return true;
		case 5:
			if(pt.X>di.width-1 || pt.X<pi.TEXpointLT.X){
				return false;
			}
			if(pt.Y>di.height-1 || pt.Y<pi.TEXpointLT.Y){
				return false;
			}
			sz = size(pt.X-pi.TEXpointLT.X,
				pt.Y-pi.TEXpointLT.Y);
			PICcontent[pos].TEXpointRB = pt;
			PICcontent[pos].picSize = sz;
			getData(4)->modifyInt(off+8, sz.W);
			getData(4)->modifyInt(off+12,sz.H);
			getData(4)->modifyInt(off+52, pt.X);
			getData(4)->modifyInt(off+56, pt.Y);
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
	sTemp.pushDWord(info.format);
	if(info.format == LINK){
		sTemp.pushDWord(info.linkTo);
		getData(4)->pushStream(sTemp, 8);
	}else if(info.comp <= COMP_ZLIB){
		sTemp.pushDWord(info.comp);
		sTemp.pushInt(info.picSize.W);
		sTemp.pushInt(info.picSize.H);
		sTemp.pushDWord(info.dataSize);
		sTemp.pushInt(info.basePt.X);
		sTemp.pushInt(info.basePt.Y);
		sTemp.pushInt(info.frmSize.W);
		sTemp.pushInt(info.frmSize.H);
		getData(4)->pushStream(sTemp, 36);
		getData(6)->pushStream(s, info.dataSize);
	}else{
		sTemp.pushDWord(info.comp);
		sTemp.pushInt(info.picSize.W);
		sTemp.pushInt(info.picSize.H);
		sTemp.pushDWord(0);
		sTemp.pushInt(info.basePt.X);
		sTemp.pushInt(info.basePt.Y);
		sTemp.pushInt(info.frmSize.W);
		sTemp.pushInt(info.frmSize.H);
		sTemp.pushDWord(0);
		sTemp.pushDWord(info.TEXusing);
		sTemp.pushInt(info.TEXpointLT.X);
		sTemp.pushInt(info.TEXpointLT.Y);
		sTemp.pushInt(info.TEXpointRB.X);
		sTemp.pushInt(info.TEXpointRB.Y);
		sTemp.pushDWord(0);
		getData(4)->pushStream(sTemp, 64);
	}
	//////////////////////////////////////////////////////////////////
	indexCount ++;
	indexSize = getData(4)->length;
	V5_totalLength = getSize();
	getData(1)->modifyInt(16, (long)indexSize);
	getData(1)->modifyInt(28, (long)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modifyInt(36, (long)V5_totalLength);
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
	sTemp.pushDWord(info.format);
	if(info.format == LINK){
		sTemp.pushDWord(info.linkTo);
		getData(4)->insertStream(sTemp, 8, off1);
	}else if(info.comp <= COMP_ZLIB){
		sTemp.pushDWord(info.comp);
		sTemp.pushInt(info.picSize.W);
		sTemp.pushInt(info.picSize.H);
		sTemp.pushDWord(info.dataSize);
		sTemp.pushInt(info.basePt.X);
		sTemp.pushInt(info.basePt.Y);
		sTemp.pushInt(info.frmSize.W);
		sTemp.pushInt(info.frmSize.H);
		getData(4)->insertStream(sTemp, 36, off1);
		getData(6)->insertStream(s, info.dataSize, off2);
	}else{
		sTemp.pushDWord(info.comp);
		sTemp.pushInt(info.picSize.W);
		sTemp.pushInt(info.picSize.H);
		sTemp.pushDWord(0);
		sTemp.pushInt(info.basePt.X);
		sTemp.pushInt(info.basePt.Y);
		sTemp.pushInt(info.frmSize.W);
		sTemp.pushInt(info.frmSize.H);
		sTemp.pushDWord(0);
		sTemp.pushDWord(info.TEXusing);
		sTemp.pushInt(info.TEXpointLT.X);
		sTemp.pushInt(info.TEXpointLT.Y);
		sTemp.pushInt(info.TEXpointRB.X);
		sTemp.pushInt(info.TEXpointRB.Y);
		sTemp.pushDWord(0);
		getData(4)->insertStream(sTemp, 64, off1);
	}
	//////////////////////////////////////////////////////////////////
	indexCount ++;
	indexSize = getData(4)->length;
	V5_totalLength = getSize();
	getData(1)->modifyInt(16, (long)indexSize);
	getData(1)->modifyInt(28, (long)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modifyInt(36, (long)V5_totalLength);
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
	if(pi.format == LINK){
		getData(4)->deleteStream(off1, 8);
	}else if(pi.comp <= COMP_ZLIB){
		getData(4)->deleteStream(off1, 36);
		getData(6)->deleteStream(off2, pi.dataSize);
	}else{
		getData(4)->deleteStream(off1, 64);
	}
	//////////////////////////////////////////////////////////////////
	indexCount --;
	indexSize = getData(4)->length;
	V5_totalLength = getSize();
	getData(1)->modifyInt(16, (long)indexSize);
	getData(1)->modifyInt(28, (long)indexCount);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modifyInt(36, (long)V5_totalLength);
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
	if(pi.format == LINK){
		getData(4)->deleteStream(off1, 8);
	}else if(pi.comp <= COMP_ZLIB){
		getData(4)->deleteStream(off1, 36);
		getData(6)->deleteStream(off2, pi.dataSize);
	}else{
		getData(4)->deleteStream(off1, 64);
	}
	///////////////////////
	stream sTemp;
	sTemp.allocate(100);
	sTemp.pushDWord(info.format);
	if(info.format == LINK){
		sTemp.pushDWord(info.linkTo);
		getData(4)->insertStream(sTemp, 8, off1);
	}else if(info.comp <= COMP_ZLIB){
		sTemp.pushDWord(info.comp);
		sTemp.pushInt(info.picSize.W);
		sTemp.pushInt(info.picSize.H);
		sTemp.pushDWord(info.dataSize);
		sTemp.pushInt(info.basePt.X);
		sTemp.pushInt(info.basePt.Y);
		sTemp.pushInt(info.frmSize.W);
		sTemp.pushInt(info.frmSize.H);
		getData(4)->insertStream(sTemp, 36, off1);
		getData(6)->insertStream(s, info.dataSize, off2);
	}else{
		sTemp.pushDWord(info.comp);
		sTemp.pushInt(info.picSize.W);
		sTemp.pushInt(info.picSize.H);
		sTemp.pushDWord(0);
		sTemp.pushInt(info.basePt.X);
		sTemp.pushInt(info.basePt.Y);
		sTemp.pushInt(info.frmSize.W);
		sTemp.pushInt(info.frmSize.H);
		sTemp.pushDWord(0);
		sTemp.pushDWord(info.TEXusing);
		sTemp.pushInt(info.TEXpointLT.X);
		sTemp.pushInt(info.TEXpointLT.Y);
		sTemp.pushInt(info.TEXpointRB.X);
		sTemp.pushInt(info.TEXpointRB.Y);
		sTemp.pushDWord(0);
		getData(4)->insertStream(sTemp, 64, off1);
	}
	///////////////////////////////////////////
	indexSize = getData(4)->length;
	V5_totalLength = getSize();
	getData(1)->modifyInt(16, (long)indexSize);
	if(version == V5){
		V5_totalLength = getSize();
		getData(1)->modifyInt(36, (long)V5_totalLength);
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
	if(pi.format == LINK){
		pos = linkFind(pos);
	}
	PICgetInfo(pos, pi);
	if(pi.format != LINK){
		if(pi.comp <= 0X06){
			PICgetData(pos, sMid);
			if(pi.comp == COMP_ZLIB){
				sMid.ZLIBuncompress(sPic, 4*pi.picSize.area());
			}else{
				sPic = sMid;
			}
			switch(version){
			case V2:
				mat.create(pi.picSize);
				mat.push(sPic, pi.format);
				break;
			case V4:
				if(sPic.length == pi.picSize.area()){
					//索引形式
					mat.create(pi.picSize);
					for(i=0;i<sPic.length;i++){
						if(sPic[i]>=paletteData[0].size())
							sPic[i] = 0;
						mat.push(paletteData[0][sPic[i]]);
					}
				}else{
					//非索引形式
					mat.create(pi.picSize);
					mat.push(sPic, pi.format);
				}
				break;
			case V5:
				if(sPic.length == pi.picSize.area()){
					//索引形式
					mat.create(pi.picSize);
					for(i=0;i<sPic.length;i++){
						if(sPic[i]>=paletteData[0].size())
							sPic[i] = 0;
						mat.push(paletteData[0][sPic[i]]);
					}
				}else{
					//非索引形式
					mat.create(pi.picSize);
					mat.push(sPic, pi.format);
				}
				break;
			case V6:
				mat.create(pi.picSize);
				for(i=0;i<sPic.length;i++){
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
		}else/*if(pi.comp == 0X07)*/{
			if(pi.TEXusing>=V5_TEXCount){
				return false;
			}
			matrix mTemp;
			TEXextract(pi.TEXusing,mTemp);
			mTemp.clip(mat,
				pi.TEXpointLT.Y,
				pi.TEXpointRB.Y,
				pi.TEXpointLT.X,
				pi.TEXpointRB.X
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
		sTemp.ZLIBcompress(s);
		sTemp.release();
		info.comp = (COMP_ZLIB);
		info.format = (ARGB8888);
		info.dataSize = (s.length);
		info.linkTo = (-1);
		info.picSize = (size(mat.getWidth(), mat.getHeight()));
		return true;
	}
	if(cf == ARGB4444){
		stream sTemp;
		mat.make(sTemp, ARGB4444);
		sTemp.ZLIBcompress(s);
		sTemp.release();
		info.comp = (COMP_ZLIB);
		info.format = (ARGB4444);
		info.dataSize = (s.length);
		info.linkTo = (-1);
		info.picSize = (size(mat.getWidth(), mat.getHeight()));
		return true;
	}
	if(cf == ARGB1555){
		stream sTemp;
		mat.make(sTemp, ARGB1555);
		sTemp.ZLIBcompress(s);
		sTemp.release();
		info.comp = (COMP_ZLIB);
		info.format = (ARGB1555);
		info.dataSize = (s.length);
		info.linkTo = (-1);
		info.picSize = (size(mat.getWidth(), mat.getHeight()));
		return true;
	}
	if(cf == INDEX_FMT_PALETTE){
		stream sTemp;
		sTemp.allocate(mat.getElemCount());
		for(long i = 0;i<mat.getElemCount();i++){
			if(paletteID >= paletteData.getCount() || paletteData[paletteID].size() == 0){
				sTemp.pushByte((uchar)0);
				continue;
			}
			sTemp.pushByte((uchar)paletteData.matchColor(mat.getElem(i)));
		}
		sTemp.ZLIBcompress(s);
		sTemp.release();
		info.comp = (COMP_ZLIB);
		info.format = (ARGB1555);
		info.dataSize = (s.length);
		info.linkTo = (-1);
		info.picSize = (size(mat.getWidth(), mat.getHeight()));
		return true;
	}
	if(cf == DDS_DXT5){
		//效果很差
		stream sTemp;
		DDSobject d;
		d.compress(mat);
		d.make(sTemp);
		sTemp.ZLIBcompress(s);
		sTemp.release();
		info.format = (DDS_DXT5);
		info.comp = (COMP_ZLIB);
		info.dataSize = (s.length);
		info.linkTo = (-1);
		info.picSize = (size(d.getHeader()->width,d.getHeader()->height));
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
	if(pi.format == LINK){
		pos = linkFind(pos);
	}
	PICgetInfo(pos, pi);
	if(pi.format == ARGB1555){
		PICgetData(pos, sMid);
		if(pi.comp == COMP_ZLIB){
			sMid.ZLIBuncompress(sPic, 4*pi.picSize.area());
		}else{
			sPic = sMid;
		}
		//解压后索引矩阵的长度与宽×高必须一致
		if(sPic.length == pi.picSize.area()){
			mat.create(pi.picSize);
			for(i=0;i<sPic.length;i++){
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
		sTemp.pushByte(mat.getElem(i).index);
	}
	sTemp.ZLIBcompress(s);
	sTemp.release();
	info.comp = (COMP_ZLIB);
	info.format = (ARGB1555);
	info.dataSize = (s.length);
	info.linkTo = (-1);
	info.picSize = (size(mat.getWidth(), mat.getHeight()));
	return true;
}
bool IMGobject::PICempty(stream &s, PICinfo &info){
	switch(version){
	case V2:
		s.allocate(4);
		s.pushDWord(0);
		info.comp = COMP_NONE;
		info.format = ARGB8888;
		info.dataSize = s.length;
		info.linkTo = -1;
		info.picSize = size(1,1);
		return true;
	case V4:
		s.allocate(1);
		s.pushByte(0);
		info.comp = COMP_NONE;
		info.format = ARGB1555;
		info.dataSize = s.length;
		info.linkTo = -1;
		info.picSize = size(1,1);
		return true;
	case V5:
		s.allocate(4);
		s.pushDWord(0);
		info.comp = COMP_NONE;
		info.format = ARGB8888;
		info.dataSize = s.length;
		info.linkTo = -1;
		info.picSize = size(1,1);
		return true;
	case V6:
		s.allocate(1);
		s.pushByte(0);
		info.comp = COMP_NONE;
		info.format = ARGB1555;
		info.dataSize = s.length;
		info.linkTo = -1;
		info.picSize = size(1,1);
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
	sTemp.pushDWord(info.reserved);
	sTemp.pushDWord(info.format);
	sTemp.pushDWord(info.ID);
	sTemp.pushDWord(info.compressedLength);
	sTemp.pushDWord(info.dataLength);
	sTemp.pushInt(info.width);
	sTemp.pushInt(info.height);
	getData(3)->pushStream(sTemp, 28);
	getData(5)->pushStream(s, info.compressedLength);
	//////////////////////////////////////////////////////////////////
	V5_TEXCount ++;
	V5_totalLength = getSize();
	getData(1)->modifyInt(32, (long)V5_TEXCount);
	getData(1)->modifyInt(36, (long)V5_totalLength);
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
	sTemp.pushDWord(info.reserved);
	sTemp.pushDWord(info.format);
	sTemp.pushDWord(info.ID);
	sTemp.pushDWord(info.compressedLength);
	sTemp.pushDWord(info.dataLength);
	sTemp.pushInt(info.width);
	sTemp.pushInt(info.height);
	getData(3)->insertStream(sTemp, 28, off1);
	getData(5)->insertStream(s, info.compressedLength, off2);
	//////////////////////////////////////////////////////////////////
	V5_TEXCount ++;
	V5_totalLength = getSize();
	getData(1)->modifyInt(32, (long)V5_TEXCount);
	getData(1)->modifyInt(36, (long)V5_totalLength);
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
	getData(5)->deleteStream(off2, di.compressedLength);
	//////////////////////////////////////////////////////////////////
	V5_TEXCount --;
	V5_totalLength = getSize();
	getData(1)->modifyInt(32, (long)V5_TEXCount);
	getData(1)->modifyInt(36, (long)V5_totalLength);
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
	getData(5)->deleteStream(off2, di.compressedLength);
	stream sTemp;
	sTemp.allocate(100);
	sTemp.pushDWord(info.reserved);
	sTemp.pushDWord(info.format);
	sTemp.pushDWord(info.ID);
	sTemp.pushDWord(info.compressedLength);
	sTemp.pushDWord(info.dataLength);
	sTemp.pushInt(info.height);
	sTemp.pushInt(info.width);
	getData(3)->insertStream(sTemp, 28, off1);
	getData(5)->insertStream(s, info.compressedLength, off2);
	////////////////////////////////////////
	V5_totalLength = getSize();
	getData(1)->modifyInt(32, (long)V5_TEXCount);
	getData(1)->modifyInt(36, (long)V5_totalLength);
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
	sMid.ZLIBuncompress(sPic, di.dataLength + 1000);
	if(di.format > LINK){
		DDSobject d(sPic);
		d.uncompress(mat);
	}else{
		if(sPic.length == di.height*di.width){
			//索引形式
			mat.create(di.height, di.width);
			for(int i=0;i<sPic.length;i++){
				if(sPic[i]>=paletteData[0].size()){
					sPic[i] = 0;
				}
				mat.push(paletteData[0][sPic[i]]);
			}
		}else{
			mat.create(di.height, di.width);
			mat.push(sPic, di.format);
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
		DDSobject d;
		d.compress(mat);
		d.make(sTemp);
		sTemp.ZLIBcompress(s);
		info.reserved = 1;
		info.format = DDS_DXT5;
		info.dataLength = sTemp.length;
		info.compressedLength = s.length;
		info.width = d.getHeader()->width;
		info.height = d.getHeader()->height;
		info.ID = V5_TEXCount;
		sTemp.release();
		return true;
	}
	if(cf == ARGB8888){
		stream sTemp;
		mat.make(sTemp, ARGB8888);
		sTemp.ZLIBcompress(s);
		info.reserved = 1;
		info.format = ARGB8888;
		info.dataLength = sTemp.length;
		info.compressedLength = s.length;
		info.width = mat.getWidth();
		info.height = mat.getHeight();
		info.ID = V5_TEXCount;
		sTemp.release();
		return true;
	}
	if(cf == ARGB4444){
		stream sTemp;
		mat.make(sTemp, ARGB4444);
		sTemp.ZLIBcompress(s);
		info.reserved = 1;
		info.format = ARGB4444;
		info.dataLength = sTemp.length;
		info.compressedLength = s.length;
		info.width = mat.getWidth();
		info.height = mat.getHeight();
		info.ID = V5_TEXCount;
		sTemp.release();
		return true;
	}
	if(cf == ARGB1555){
		stream sTemp;
		mat.make(sTemp, ARGB1555);
		sTemp.ZLIBcompress(s);
		info.reserved = 1;
		info.format = ARGB1555;
		info.dataLength = sTemp.length;
		info.compressedLength = s.length;
		info.width = mat.getWidth();
		info.height = mat.getHeight();
		info.ID = V5_TEXCount;
		sTemp.release();
		return true;
	}
	if(cf == INDEX_FMT_PALETTE){
		stream sTemp;
		sTemp.allocate(mat.getElemCount());
		for(long i = 0;i<mat.getElemCount();i++){
			if(paletteData.getCount() == 0 || paletteData[0].size() == 0){
				sTemp.pushByte(0);
				continue;
			}
			sTemp.pushByte(paletteData.matchColor(mat.getElem(i)));
		}
		sTemp.ZLIBcompress(s);
		info.reserved = 1;
		info.format = ARGB1555;
		info.dataLength = sTemp.length;
		info.compressedLength = s.length;
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
					pi.comp = COMP_ZLIB_DUAL;
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
	}else if(pi.format == LINK){
		return linkFind(pi.linkTo, depth-1);
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
		pi.format = LINK;
		pi.linkTo = 0;
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
	s.pushWord(0);
	newIO.PICpush(pi, s);
	pi.format = LINK;
	pi.linkTo = 0;
	for(int i = 0;i<frameCount;i++){
		newIO.PICpush(pi, s);
	}
	s.release();
}
bool IMGobject::checkIsOld(stream &s){
	s.resetPosition();
	if(s.readString(20) != "Neople Image File")
		return false;
	dword dwTemp, dwVersion;
	s.readDWord(dwTemp);	//保留位
	s.readDWord(dwVersion); //版本
	if(dwVersion != V1)
		return false;
	return true;
}
stream *IMGobject::getData(uchar _part){
	stream *sList[] = {NULL, &dataHeader, &dataPalette, &dataIndexTexture, &dataIndexPicture, &dataTexture, &dataPicture};
	return sList[_part%7];
}
longex IMGobject::getSize() const{
	return dataHeader.length+dataPalette.length+dataIndexTexture.length+dataIndexPicture.length+dataTexture.length+dataPicture.length;
}
