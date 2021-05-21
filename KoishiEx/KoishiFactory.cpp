#include "StdAfx.h"
#include "KoishiEx.h"
#include "KoishiImageTool.h"
#include "KoishiAudioTool.h"
#include "KoishiNeoplePack.h"
#include <assert.h>

#define NEW_NPK_METHOD 1

using namespace Koishi;
using namespace KoishiNeoplePack;
using KoishiImageTool::DDS::DDSobject;
/////////���õĽṹ��ĳ�ʼ��////////////////////////////////////////////////////////
NPKentry::NPKentry(){
	comment = "";
	link = -1;
}
NPKentry::NPKentry(const str newComment, long blockID) {
	comment = newComment;
	link = blockID;
}
NPKblock::NPKblock() {
	start = 0;
	length = 0;
}
NPKblock::~NPKblock() {
	destroy();
}
void NPKblock::load(const stream &sourceStream) {
	start = 0;
	length = sourceStream.length;
	data.allocate(length);
	memcpy(data.begin(), sourceStream.begin(), sourceStream.length);
}
void NPKblock::destroy() {
	data.release();
}
dword NPKblock::checkMagic() {
	dword value = 0;
	for(char i = 0; i < 4; i++) {
		if(i<length)value |= data[i] << (i << 3);
	}
	return value;
}
dword NPKblock::checkData(long pos) {
	dword value = 0;
	for(char i = 0; i < 4; i++) {
		if(i + pos<length)value |= data[i + pos] << (i << 3);
	}
	return value;
}
NPKobject::NPKobject(){
	//release();
}
bool NPKobject::loadEntry(const str &fileName) {
	FILE *file = fopen(fileName.c_str(), "rb+");
	if(!file)
		return false;
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	if(length < 20) {
		fclose(file);
		return false;
	}
	fseek(file, 0, SEEK_SET);
	char magic[17] = {0};
	fread(magic, sizeof(char), 16, file);
	if(str(magic) != "NeoplePack_Bill") {
		fclose(file);
		return false;
	}
	dword count;
	fread(&count, sizeof(dword), 1, file);
	if(length < count * 264 + 52) {
		fclose(file);
		return false;
	}
	//�����ж�����ʼ����
	for(int i = 0; i < count; i++) {
		NPKblock thisBlock;
		NPKentry thisEntry;
		char pathBuf[256] = {0};
		fread(&thisBlock.start, sizeof(long), 1, file);
		fread(&thisBlock.length, sizeof(long), 1, file);
		fread(pathBuf, sizeof(char), 256, file);
		nameMask(pathBuf);
		thisEntry.comment = str(pathBuf);
		thisEntry.link = -1;
		content.push_back(thisEntry);
	}
	fclose(file);
	return true;
}
bool NPKobject::loadFile(const str &fileName) {
	FILE *file = fopen(fileName.c_str(), "rb+");
	if(!file)
		return false;
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	if(length < 20) {
		fclose(file);
		return false;
	}
	fseek(file, 0, SEEK_SET);
	char magic[17] = {0};
	fread(magic, sizeof(char), 16, file);
	if(str(magic) != "NeoplePack_Bill") {
		fclose(file);
		return false;
	}
	dword count;
	fread(&count, sizeof(dword), 1, file);
	if(length < count * 264 + 52) {
		fclose(file);
		return false;
	}
	//�����ж�����ʼ����
	for(int i = 0; i < count; i++) {
		NPKblock thisBlock;
		NPKentry thisEntry;
		char pathBuf[256] = {0};
		fread(&thisBlock.start, sizeof(long), 1, file);
		fread(&thisBlock.length, sizeof(long), 1, file);
		fread(pathBuf, sizeof(char), 256, file);
		nameMask(pathBuf);
		thisEntry.comment = str(pathBuf);
		thisEntry.link = -1;
		//����ȷ�����block�ǲ����µģ���������µľ������ö���
		long thisBlockID = -1;
		for(int b = 0; b < block.size(); b++) {
			if(block[b].start == thisBlock.start && block[b].length == thisBlock.length) {
				thisBlockID = b;
				break;
			}
		}
		if(thisBlockID == -1) {
			//�µģ�����block��entry��linkΪ����block
			block.push_back(thisBlock);
			thisEntry.link = block.size() - 1;
			content.push_back(thisEntry);
		} else {
			thisEntry.link = thisBlockID;
			content.push_back(thisEntry);
		}
	}
	for(int i = 0; i < block.size(); i++) {
		auto &thisBlock = block[i];
		thisBlock.data.allocate(thisBlock.length);
		fseek(file, thisBlock.start, SEEK_SET);
		fread(thisBlock.data.begin(), sizeof(char), thisBlock.length, file);
	}
	fclose(file);
	return true;
}
bool NPKobject::saveFile(const str &fileName) {
	//һ���д
	FILE *file = fopen(fileName.c_str(), "wb+");
	if(!file)
		return false;
	//�ļ�ͷ
	stream headHelper(52 + content.size() * 264), headTrun(52 + content.size() * 264), checkCode;//����SHA256�õ�
	char magic[16] = "NeoplePack_Bill";
	fwrite(magic, sizeof(char), 16, file);
	headHelper.push(magic, 16);
	long count = content.size();
	fwrite(&count, sizeof(long), 1, file);
	headHelper.push(&count, 4);
	//������Ŀ��������block��˳��blockҪ���ţ�
	std::vector<long> newBlockSeq;	//block��˳��
	//���ж���Щ��������
	for(int i = 0; i < content.size(); i++) {
		const auto &entry = content[i];
		long isQuote = -1;
		for(int k = 0; k < i; k++) {
			if(content[k].link == entry.link) {
				isQuote = k;
				break;
			}
		}
		if(isQuote == -1) {
			newBlockSeq.push_back(entry.link);
		}
	}
	//����block������ʼλ��
	long start_pos = 52 + 264 * content.size();
	for(int i = 0; i < newBlockSeq.size(); i++) {
		block[newBlockSeq[i]].start = start_pos;
		start_pos += block[newBlockSeq[i]].length;
	}
	//������Ŀ����
	for(int i = 0; i < content.size(); i++) {
		const auto &entry = content[i];
		long offset = block[entry.link].start;
		long length = block[entry.link].length;
		char pathName[256] = {0};
		memcpy(pathName, entry.comment.c_str(), entry.comment.size());
		nameMask(pathName);
		fwrite(&offset, sizeof(long), 1, file);
		fwrite(&length, sizeof(long), 1, file);
		fwrite(pathName, sizeof(char), 256, file);
		
		
		headHelper.push(&offset, 4);
		headHelper.push(&length, 4);
		headHelper.push(pathName, 256);
	}
	headTrun.pushStream(headHelper, headHelper.length / 17 * 17);
	headTrun.SHA256code(checkCode);
	fwrite(checkCode.begin(), sizeof(char), 32, file);
	for(int i = 0; i < newBlockSeq.size(); i++) {
		const auto &bk = block[newBlockSeq[i]];
		fwrite(bk.data.begin(), sizeof(char), bk.length, file);
	}
	fclose(file);
	return true;
}
bool NPKobject::create() {
	block.clear();
	content.clear();
	return false;
}
bool NPKobject::release() {
	block.clear();
	content.clear();
	return false;
}
void NPKobject::addBlock(const stream &newStream) {
	NPKblock newBlock;
	block.push_back(newBlock);	//�����˸��ƹ��캯��(���block���·���ռ���ô��������á�����
	NPKblock &lastBlock = block[block.size() - 1];
	lastBlock.load(newStream);
}
bool NPKobject::push(const str &path, const stream &newStream) {
	addBlock(newStream);
	content.push_back(NPKentry(path, block.size() - 1));
	return true;
}
bool NPKobject::pushFile(const str &path, str fileName) {
	stream newStream;
	if(!newStream.loadFile(fileName))
		return false;
	if(!push(path, newStream))
		return false;
	return true;
}
bool NPKobject::pushCopy(const str &path, long quotePos) {
	stream newStream;
	if(!checkEntryRange(quotePos))
		return false;
	if(!extract(quotePos, newStream))
		return false;
	if(!push(path, newStream))
		return false;
	return true;
}
bool NPKobject::pushQuote(const str &path, long quotePos) {
	if(!checkEntryRange(quotePos))
		return false;
	if(!checkBlockRange(content[quotePos].link))
		return false;
	content.push_back(NPKentry(path, content[quotePos].link));
	return true;
}
bool NPKobject::insert(long pos, const str &path, const stream &newStream) {
	if(!checkEntryRangeEx(pos))
		return false;
	if(pos == content.size())
		return push(path, newStream);
	addBlock(newStream);
	content.insert(content.begin() + pos, NPKentry(path, block.size() - 1));
	return true;
}
bool NPKobject::insertFile(long pos, const str &path, str fileName) {
	stream newStream;
	if(!newStream.loadFile(fileName))
		return false;
	if(!insert(pos, path, newStream))
		return false;
	return true;
}
bool NPKobject::insertCopy(long pos, const str &path, long sourcePos) {
	stream newStream;
	if(!checkEntryRange(sourcePos))
		return false;
	if(!extract(sourcePos, newStream))
		return false;
	if(!insert(pos, path, newStream))
		return false;
	return true;
}
bool NPKobject::insertQuote(long pos, const str &path, long sourcePos) {
	if(!checkEntryRangeEx(pos))
		return false;
	if(!checkEntryRange(sourcePos))
		return false;
	if(!checkBlockRange(content[sourcePos].link))
		return false;
	content.insert(content.begin() + pos, NPKentry(path, content[sourcePos].link));
	return true;
}
//��ȡ��Ŀ(��ȡ��Ŀ���������Ϊ�ļ���
bool NPKobject::extract(long pos, stream &dest) {
	if(!checkEntryRange(pos))
		return false;
	if(!checkBlockRange(content[pos].link))
		return false;
	const auto &bk = block[content[pos].link];
	dest.allocate(bk.length);
	dest.push(bk.data.begin(), bk.length);
	return true;
}
bool NPKobject::extractFile(long pos, const str &fileName) {
	stream newStream;
	if(!extract(pos, newStream))
		return false;
	if(!newStream.makeFile(fileName))
		return false;
	return true;
}
//ɾ����Ŀ
bool NPKobject::remove(long pos) {
	if(!checkEntryRange(pos))
		return false;
	content.erase(content.begin() + pos);
	return true;
}
//��������Ŀ
bool NPKobject::rename(long pos, str newPathName) {
	if(!checkEntryRange(pos))
		return false;
	if(newPathName.size() >= 256)
		return false;
	content[pos].comment = newPathName;
	return true;
}
//������Ŀ
bool NPKobject::find(const str &keyword, long &pos, long startPos){
	for(long i = startPos;i<content.size();i++){
		if(content[i].comment.find(keyword) != str::npos){
			pos = i;
			return true;
		}
	}
	pos = -1;
	return false;
}
//�滻��Ŀ
bool NPKobject::replace(long pos, const stream &newStream) {
	if(!checkEntryRange(pos))
		return false;
	if(!checkBlockRange(content[pos].link))
		return false;
	auto &bk = block[content[pos].link];
	bk.destroy();
	bk.load(newStream);
	return true;
}
bool NPKobject::replaceFile(long pos, const str &fileName) {
	if(!checkEntryRange(pos))
		return false;
	if(!checkBlockRange(content[pos].link))
		return false;
	stream newStream;
	if(!newStream.loadFile(fileName))
		return false;
	if(!replace(pos, newStream))
		return false;
	return true;
}
bool NPKobject::replaceCopy(long pos, long sourcePos) {
	if(!checkEntryRange(pos))
		return false;
	if(!checkBlockRange(content[pos].link))
		return false;
	stream newStream;
	if(!extract(sourcePos, newStream))
		return false;
	if(!replace(pos, newStream))
		return false;
	return true;
}
bool NPKobject::replaceQuote(long pos, long sourcePos) {
	if(!checkEntryRange(pos))
		return false;
	if(!checkEntryRange(sourcePos))
		return false;
	if(!checkBlockRange(content[sourcePos].link))
		return false;
	content[pos].link = content[sourcePos].link;
	return true;
}
bool NPKobject::subscribe(long pos, stream newStream) {
	if(!checkEntryRange(pos))
		return false;
	addBlock(newStream);
	content[pos].link = block.size() - 1;
	return true;
}
bool NPKobject::subscribeFile(long pos, const str &fileName) {
	if(!checkEntryRange(pos))
		return false;
	stream newStream;
	if(!newStream.loadFile(fileName))
		return false;
	if(!subscribe(pos, newStream))
		return false;
	return true;
}
bool NPKobject::subscribeCopy(long pos, long sourcePos) {
	if(!checkEntryRange(pos))
		return false;
	stream newStream;
	if(!extract(sourcePos, newStream))
		return false;
	if(!subscribe(pos, newStream))
		return false;
	return true;
}
//������
bool NPKobject::dequote(long pos) {
	if(!checkEntryRange(pos))
		return false;
	if(pos == checkQuote(pos))
		return false;
	if(!subscribeCopy(pos, pos))
		return false;
	return true;
}
//������ã��������ã���������
long NPKobject::checkQuote(long pos) {
	for(int i = 0; i<pos; i++) {
		if(content[pos].link == content[i].link) {
			return i;
		}
	}
	return pos;
}
//IMG����Ľӿ�
bool NPKobject::IMGextract(long pos, IMGobject &io){
	stream dataIO;
	if(!extract(pos, dataIO))
		return false;
	if(!io.load(dataIO))
		return false;
	io.derived = &content[pos];
	return true;
}
bool NPKobject::IMGpush(const str &newPath, IMGobject &io){
	stream dataIO;
	if(!io.make(dataIO))
		return false;
	if(!push(newPath, dataIO))
		return false;
	return true;
}
bool NPKobject::IMGinsert(long pos, const str &newPath, IMGobject &io) {
	stream dataIO;
	if(!io.make(dataIO))
		return false;
	if(!insert(pos, newPath, dataIO))
		return false;
	return true;
}
bool NPKobject::IMGremove(long pos){
	if(!remove(pos))
		return false;
	return true;
}
bool NPKobject::IMGreplace(long pos, IMGobject &io){
	stream dataIO;
	if(!io.make(dataIO))
		return false;
	if(!replace(pos, dataIO))
		return false;
	return true;
}
bool NPKobject::IMGrename(long pos, const str& newName){
	if(!rename(pos, newName))
		return false;
	return true;
}
IMGversion NPKobject::IMGgetVersion(long pos) {
	if(!checkEntryRange(pos))
		return VUDEF;
	if(!checkBlockRange(content[pos].link))
		return VUDEF;
	auto &bk = block[content[pos].link];
	dword magic = bk.checkMagic();
	if(0x706F654E == magic) {
		dword version = bk.checkData(24);
		if(version == 1) {
			return V1;
		} else if(version == 2) {
			return V2;
		} else if(version == 4) {
			return V4;
		} else if(version == 5) {
			return V5;
		} else if(version == 6) {
			return V6;
		} else {
			return VUKNOWN;
		}
	} else if(0x46464952 == magic) {
		return VSOUND; /*riff*/
	} else if(0x5367674F == magic) {
		return VSOUND; /*ogg*/
	} else if((magic & 0xFFFFFF) == 0x334449 || (magic & 0xF0FF) == 0xF0FF) {
		return VSOUND; /*mp3*/
	}
	return VUDEF;
}
IMGversion NPKobject::IMGgetVersionEx(long pos) {
	if(!checkEntryRange(pos))
		return VUDEF;
	if(!checkBlockRange(content[pos].link))
		return VUDEF;
	if(checkQuote(pos) < pos)
		return VQUOTE;
	return IMGgetVersion(pos);
}
long NPKobject::IMGgetPaletteCount(long pos){
	if(!checkEntryRange(pos))
		return 0;
	if(!checkBlockRange(content[pos].link))
		return 0;
	auto &bk = block[content[pos].link];
	dword magic = bk.checkMagic();
	if(0x706F654E != magic)
		return 0;
	dword version = bk.checkData(24);
	if(6 != version)
		return 0;
	dword count = bk.checkData(32);
	return count;
}
SNDversion NPKobject::SNDgetVersion(long pos) {
	if(!checkEntryRange(pos))
		return VSNDUDEF;
	if(!checkBlockRange(content[pos].link))
		return VSNDUDEF;
	auto &bk = block[content[pos].link];
	dword magic = bk.checkMagic();
	if(0x46464952 == magic) {
		return VWAVE; /*riff*/
	} else if(0x5367674F == magic) {
		return VVORBIS; /*ogg*/
	} else if((magic & 0xFFFFFF) == 0x334449 || (magic & 0xF0FF) == 0xF0FF) {
		return VMP3; /*mp3*/
	} else if(0x706F654E == magic) {
		return VIMAGE;
	}
	return VSNDUDEF;
}
SNDversion NPKobject::SNDgetVersionEx(long pos) {
	if(!checkEntryRange(pos))
		return VSNDUDEF;
	if(!checkBlockRange(content[pos].link))
		return VSNDUDEF;
	if(checkQuote(pos) < pos)
		return VSNDQUOTE;
	return SNDgetVersion(pos);
}
void NPKobject::nameMask(void*data) {
	str IMGnameMask = "puchikon@neople dungeon and fighter DNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNF";
	for(long i = 0; i<255; i++)
		((char*)data)[i] ^= IMGnameMask[i];
}
bool NPKobject::checkEntryRange(long pos) {
	return pos >= 0 && pos < content.size();
}
bool NPKobject::checkEntryRangeEx(long pos) {
	return pos >= 0 && pos <= content.size();
}
bool NPKobject::checkBlockRange(long pos) {
	return pos >= 0 && pos < block.size();
}
long NPKobject::getCount() const {
	return content.size();
}
long NPKobject::getSize() const {
	long sz = 52 + content.size() * 264;
	for(const auto &bk : block) {
		sz += bk.length;
	}
	return sz;
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
			//����һ�������ڽ��ϰ汾V2��˵��δѹ����1555��4444��ʽ�����ݴ�С��ʾ����ת��Ϊ8888������ݴ�С�����Ҫ����Ϊ1555��4444�Ĵ�С
			if(version == V2 && pi.comp == COMP_NONE && (pi.format == ARGB1555 || pi.format == ARGB4444))
				pi.dataSize = pi.picSize.area() << 1;
			PICcontent.push_back(pi);
		}
	}
	ptEnd = s.getPosition();
	s.setPosition(ptStart);
	getData(4)->allocate(100 + ptEnd - ptStart);
	s.readStream(*getData(4), ptEnd - ptStart);
	if(ptEnd - ptStart >= indexSize){
		//��ʵ�������С>�����������С
		s.setPosition(ptStart = ptEnd);
	}else{
		//��ʵ�������С<�����������С
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
	//��ɫ������
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
			//������ģʽ
			off += 36;
		}else{
			//˫����ģʽ
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
	PICinfo pi;			//��PICinfo
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
bool IMGobject::PICextract(long pos, image &mat, long paletteID){
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
				sMid.ZLIBuncompress(sPic, 5*pi.picSize.area());
			}else{
				sPic = sMid;
			}
			switch(version){
			case V2:
				mat.create(pi.picSize);
				mat.load(sPic, pi.format);
				break;
			case V4:
				if(sPic.length == pi.picSize.area()){
					//������ʽ
					mat.create(pi.picSize);
					for(i=0;i<sPic.length;i++){
						if(sPic[i]>=paletteData[0].size())
							sPic[i] = 0;
						mat.setElem(i, paletteData[0][sPic[i]]);
					}
				}else{
					//��������ʽ
					mat.create(pi.picSize);
					mat.load(sPic, pi.format);
				}
				break;
			case V5:
				if(sPic.length == pi.picSize.area()){
					//������ʽ
					mat.create(pi.picSize);
					for(i=0;i<sPic.length;i++){
						if(sPic[i]>=paletteData[0].size())
							sPic[i] = 0;
						mat.setElem(i, paletteData[0][sPic[i]]);
					}
				}else{
					//��������ʽ
					mat.create(pi.picSize);
					mat.load(sPic, pi.format);
				}
				break;
			case V6:
				mat.create(pi.picSize);
				for(i=0;i<sPic.length;i++){
					if(sPic[i]>=paletteData[paletteID].size()){
						sPic[i] = 0;
					}
					if(paletteData[paletteID].size()>0){
						if(pi.format == ARGB4444){
							//������ɫ
							color c1 = paletteData[paletteID][sPic[i]];
							color c2 = color(
								(c1.alpha == 0xFF ? 0x8F:0x00) | c1.R >> 1, 
								0x0F | c1.R >> 3 << 6 | c1.G >> 2, 
								0x0F | c1.G >> 3 << 5 | c1.B >> 3, 
								0x0F | c1.B << 1);
							mat.setElem(i, c2);
						}else{
							mat.setElem(i, paletteData[paletteID][sPic[i]]);
						}
					}else{
						mat.setElem(i, color(0));
					}
				}
				break;
			}
		}else/*if(pi.comp == 0X07)*/{
			if(pi.TEXusing>=V5_TEXCount){
				return false;
			}
			image  mTemp;
			TEXextract(pi.TEXusing,mTemp);
			mTemp.clip(mat,
				pi.TEXpointLT.Y,
				pi.TEXpointRB.Y,
				pi.TEXpointLT.X,
				pi.TEXpointRB.X
			);
			if(pi.picSize.H != pi.picSize.W && pi.picSize.H == pi.TEXpointRB.X - pi.TEXpointLT.X) {
				//���ͼƬ���Ƿ��γߴ磬�������������ܿ����ͼ��ߣ����������ÿ����ͼƬ����෴��ʱ��ͼ��Ӧ����˳ʱ����ת90�ȵ�
				//Ӧ��mTemp��ʱ����ת90������ȡ
				image imRotated;
				imRotated.create(mat.width, mat.height);
				for(int xp = 0; xp < mat.column; xp++) {
					for(int yp = 0; yp < mat.row; yp++) {
						imRotated[xp][yp] = mat[yp][mat.column - xp - 1];
					}
				}
				mat.destory();
				mat = imRotated;
			}
		}
	}
	return true;
}
///////////////////////////////////////////
bool IMGobject::PICpreprocess(const image &mat, stream &s, PICinfo &info, colorFormat cf, long paletteID){
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
		//Ч���ܲ�
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
bool IMGobject::PICextractIndexImage(long pos, image &mat){
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
			sMid.ZLIBuncompress(sPic, 5*pi.picSize.area());
		}else{
			sPic = sMid;
		}
		//��ѹ����������ĳ��������߱���һ��
		if(sPic.length == pi.picSize.area()){
			mat.create(pi.picSize);
			for(i=0;i<sPic.length;i++){
				mat.setElem(i, color(sPic[i],0,0,0));
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
bool IMGobject::PICpreprocessIndexImage(const image &mat, stream &s, PICinfo &info){
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
bool IMGobject::TEXextract(long pos, image &mat){
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
	sMid.ZLIBuncompress(sPic, MAX(di.height * di.width * 5, di.dataLength + 1000));
	if(di.format > LINK){
		DDSobject d(sPic);
		d.uncompress(mat);
	}else{
		if(sPic.length == di.height*di.width){
			//������ʽ
			mat.create(di.height, di.width);
			for(int i=0;i<sPic.length;i++){
				if(sPic[i]>=paletteData[0].size()){
					sPic[i] = 0;
				}
				mat.setElem(i, paletteData[0][sPic[i]]);
			}
		}else{
			mat.create(di.height, di.width);
			mat.load(sPic, di.format);
		}
	}
	return true;
}
bool IMGobject::TEXpreprocess(const image &mat, stream &s, TEXinfo &info, colorFormat cf){
	if(version != V5)
		return false;
	if(cf == DDS_DXT5){
		//Ч���ܲ�
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
//ת�汾2����
//���ȶ���ͼ��ȫ��ȡ������Ȼ��ת��ARGB1555/4444/8888��ʽ
//��ԭ�汾Ϊ6����ֲ�����ɣ�����newIOList
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
				image mPic;
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
//ת�汾4����
//��ԭ�汾Ϊ4��6���������ɫ����Ч(��������useOriginPaletteΪfalse)
//��ԭ�汾Ϊ4�������������ɫ��ֱ�ӽ�ԭIMG����newIOList
//��ԭ�汾Ϊ6�������������ɫ�壬����ԭ�汾��ɫ��ֲ�󣬱�����ͼ���ݣ�����newIOList
//��ԭ�汾Ϊ�����汾������ȡ������Ȼ����������ɫ��ƥ�䣬����newIOList
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
			//������ͼ����
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
			//������תV4��ʹ�üȶ���ɫ��
			newIO.create(V4);
			newIO.paletteData.clear();
			newIO.paletteData.push(useColorPalette);
			newIO.getData(2)->release();
			newIO.paletteData.tinyMake(*(newIO.getData(2)));
			//����ͼ�������ɫ��Ƚ�ƥ��
			for(long i = 0;i<indexCount;i++){
				PICinfo pi;
				PICgetInfo(i, pi);
				if(pi.format == LINK){
					newIO.PICpush(pi, NULL);
				}else{
					image mPic;
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
//ת�汾5����
//�������ɫ����Ϊ�µ�V5��ɫ��
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
				//V5�ĵ�ɫ�壬ʹ�üȶ���ɫ��
				newIO.paletteData.clear();
				newIO.paletteData.push(useColorPalette);
				newIO.getData(2)->release();
				newIO.paletteData.tinyMake(*(newIO.getData(2)));
				//��ͼ����
				if(makeTexture){
					//��������
					TEXinfo ti;
					image mPic;
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
					image mPic;
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
	//ԭ�汾V6 & ����ԭ��ɫ�壺����
	if(version == V6 && useOriginPalette){
		IMGobject newIO;
		newIO = *this;
		newIOList.push_back(newIO);
		return true;
	}
	//ԭ�汾V4 & ����ԭ��ɫ�� ��ֱ�ӱ��V6
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
	//��������ɫ�壺ʹ�üȶ���ɫ�壬������һ����ɫ�������ɫƥ�䣬ԭ�汾ΪV6��������
	long paletteCount = 1;
	if(version == V6)
		paletteCount = paletteData.getCount();
	for(long paletteID = 0;paletteID < paletteCount; paletteID ++){
		IMGobject newIO;
		//������תV6��ʹ�üȶ���ɫ��
		newIO.create(V6);
		newIO.paletteData.clear();
		for(long i = 0;i<useColorPaletteList.size();i++){
			newIO.paletteData.push(useColorPaletteList[i]);
		}
		newIO.getData(2)->release();
		newIO.paletteData.bigMake(*(newIO.getData(2)));
		//����ͼ�������ɫ��Ƚ�ƥ��
		for(long i = 0;i<indexCount;i++){
			PICinfo pi;
			PICgetInfo(i, pi);
			if(pi.format == LINK){
				newIO.PICpush(pi, NULL);
			}else{
				image mPic;
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
	s.readDWord(dwTemp);	//����λ
	s.readDWord(dwVersion); //�汾
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
