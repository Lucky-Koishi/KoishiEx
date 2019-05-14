#include "StdAfx.h"
#include "DDS.h"

using namespace Koishi;
using namespace KoishiDDS;
DDS::DDS(void){
}
DDS::DDS(const stream &s){
	load(s);
}
DDS::DDS(const str &DDSfileName){
	loadFile(DDSfileName);
}
DDS::~DDS(void){
	data.release();
}
DDSHeader *DDS::getHeader(){
	return &header;
}
bool DDS::load(const stream &s){
	stream _s(s);
	bool b = true;
	dword _v;
	long i;
	_s.read(_v);
	header.magic = _v;
	if(_v != 0x20534444)
		b = false;
	_s.read(_v);
	header.headSize	= _v;
	if(_v != 0x7C)
		b = false;
	_s.read(_v);
	header.flags = _v;
	if(_v != 0x81007){
	//	b = false;
	}
	_s.read(_v);
	header.height = _v;
	_s.read(_v);
	header.width = _v;
	_s.read(_v);
	header.pitchOrLinearSize = _v;
	_s.read(_v);
	header.depth = _v;
	_s.read(_v);
	header.mipMapCount = _v;
	for(i=0;i<11;i++){
		_s.read(_v);
		header.reserved1[i] = _v;
	}
	_s.read(_v);
	header.pixelFormat.size = _v;
	_s.read(_v);
	header.pixelFormat.flags = _v;
	_s.read(_v);
	header.pixelFormat.fourCC = _v;
	_s.read(_v);
	header.pixelFormat.rgbBitCount = _v;
	_s.read(_v);
	header.pixelFormat.rBitMask = _v;
	_s.read(_v);
	header.pixelFormat.gBitMask = _v;
	_s.read(_v);
	header.pixelFormat.bBitMask = _v;
	_s.read(_v);
	header.pixelFormat.aBitMask = _v;
	_s.read(_v);
	header.caps1 = _v;
	_s.read(_v);
	header.caps2 = _v;
	_s.read(_v);
	header.caps3 = _v;
	_s.read(_v);
	header.caps4 = _v;
	_s.read(_v);
	header.reserved2 = _v;
	if(header.flags & DDSD_MIPMAPCOUNT){
		//mipmap格式
		if(header.mipMapCount >= 15){
		return false;
		}
		long len = 0;
		long originWidth = header.width;
		long originHeight = header.height;
		for(int i = 0 ;i<header.mipMapCount;i++){
			len += MAX(1,((originWidth+3)/4))*MAX(1,((originHeight+3)/4))*((header.pixelFormat.fourCC == 0x31545844)?8:16);
			originWidth /= 2;
			originHeight /= 2;
		}
		data.allocate(len + 1000);
		_s.readStream(data, len);
	}else{
		data.allocate(header.pitchOrLinearSize + 1000);
		_s.readStream(data, header.pitchOrLinearSize);
	}
	return b;
}
bool DDS::loadFile(const str &DDSfileName){
	stream s;
	bool b = true;
	b &= s.loadFile(DDSfileName);
	if(!b){
		s.release();
		return b;
	}
	b &= load(s);
	s.release();
	return b;
}
bool DDS::make(stream &s){
	s.allocate(128+data.getLen()+2000);

	s.push((dword)header.magic);
	s.push((dword)header.headSize);
	s.push((dword)header.flags);
	s.push((dword)header.height);
	s.push((dword)header.width);
	s.push((dword)header.pitchOrLinearSize);
	s.push((dword)header.depth);
	s.push((dword)header.mipMapCount);
	s.push((dword)header.reserved1[0]);
	s.push((dword)header.reserved1[1]);
	s.push((dword)header.reserved1[2]);
	s.push((dword)header.reserved1[3]);
	s.push((dword)header.reserved1[4]);
	s.push((dword)header.reserved1[5]);
	s.push((dword)header.reserved1[6]);
	s.push((dword)header.reserved1[7]);
	s.push((dword)header.reserved1[8]);
	s.push((dword)header.reserved1[9]);
	s.push((dword)header.reserved1[10]);
	s.push((dword)header.pixelFormat.size);
	s.push((dword)header.pixelFormat.flags);
	s.push((dword)header.pixelFormat.fourCC);
	s.push((dword)header.pixelFormat.rgbBitCount);
	s.push((dword)header.pixelFormat.rBitMask);
	s.push((dword)header.pixelFormat.gBitMask);
	s.push((dword)header.pixelFormat.bBitMask);
	s.push((dword)header.pixelFormat.aBitMask);
	s.push((dword)header.caps1);
	s.push((dword)header.caps2);
	s.push((dword)header.caps3);
	s.push((dword)header.caps4);
	s.push((dword)header.reserved2);
	s.pushStream(data,data.getLen());
	return false;
}
bool DDS::makeFile(const str &DDSfileName){
	stream s;
	bool b = true;
	b &= make(s);
	b &= s.makeFile(DDSfileName);
	s.release();
	return false;
}
bool DDS::uncompress(matrix &mat){
	switch(header.pixelFormat.fourCC){
	case 0x31545844:
		DXT1_uncompress(mat);
		return true;
		break;
	case 0x33545844:
		DXT3_uncompress(mat);
		return true;
		break;
	case 0x35545844:
		DXT5_uncompress(mat);
		return true;
		break;
	default:
		return false;
	}
}
bool DDS::uncompressMipmap(std::vector<matrix> &matList){
	return false;
}
bool DDS::compress(const matrix &mat){
	DXT5_compress(mat);
	//设置头
	header.magic = 0x20534444;
	header.headSize = 0x7c;
	header.flags = 0x81007;
	header.height = (mat.getHeight()+3)/4*4;
	header.width = (mat.getWidth()+3)/4*4;
	header.pitchOrLinearSize = data.getLen();
	header.depth = 0;
	header.mipMapCount = 0;
	header.reserved1[0] = 0;
	header.reserved1[1] = 0;
	header.reserved1[2] = 0;
	header.reserved1[3] = 0;
	header.reserved1[4] = 0;
	header.reserved1[5] = 0;
	header.reserved1[6] = 0;
	header.reserved1[7] = 0;
	header.reserved1[8] = 0;
	header.reserved1[9] = 0x5454564e;
	header.reserved1[10] = 0x20008;
	header.pixelFormat.size = 0x20;
	header.pixelFormat.flags = 0x04;
	header.pixelFormat.fourCC = 0x35545844;
	header.pixelFormat.rgbBitCount = 0;
	header.pixelFormat.rBitMask = 0;
	header.pixelFormat.gBitMask = 0;
	header.pixelFormat.bBitMask = 0;
	header.pixelFormat.aBitMask = 0;
	header.caps1 = 0x1000;
	header.caps2 = 0;
	header.caps3 = 0;
	header.caps4 = 0;
	header.reserved2 = 0;
	return true;
}
word DDS::RGB8888TO565(color c8888){
	word c565 = 0;
	c565 |= (c8888.B >> 3 << 11);
	c565 |= (c8888.G >> 2 << 5);
	c565 |= (c8888.R >> 3);
	return c565;
}
color DDS::RGB565TO8888(word c565){
	color c8888(0);
	c8888.A = (0xFF);
	c8888.R = ((c565 & 0xf800)>>8);
	c8888.G = ((c565 & 0x07e0)>>3);
	c8888.B = ((c565 & 0x001f)<<3);
	return c8888;
}
void DDS::DXT1_uncompress(const stream &udata, colorList &clist){
	int i;
	dword clrPart = udata[0] | (udata[1]<<8) | (udata[2]<<16) | (udata[3]<<24);
	dword idxPart = udata[4] | (udata[5]<<8) | (udata[6]<<16) | (udata[7]<<24);
	word uc1 = clrPart & 0xffff;
	word uc2 = clrPart >> 16;
	color cTempList[4];
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	if(uc1<=uc2){
		cTempList[2].A = (0xff);
		cTempList[2].B = ((cTempList[0].B+cTempList[1].B)/2);
		cTempList[2].R = ((cTempList[0].R+cTempList[1].R)/2);
		cTempList[2].G = ((cTempList[0].G+cTempList[1].G)/2);
		cTempList[3].A = (0x00);
	}else{
		cTempList[2].A = (0xff);
		cTempList[2].B = ((2*cTempList[0].B+cTempList[1].B)/3);
		cTempList[2].R = ((2*cTempList[0].R+cTempList[1].R)/3);
		cTempList[2].G = ((2*cTempList[0].G+cTempList[1].G)/3);
		cTempList[3].A = (0xff);
		cTempList[3].B = ((cTempList[0].B+2*cTempList[1].B)/3);
		cTempList[3].R = ((cTempList[0].R+2*cTempList[1].R)/3);
		cTempList[3].G = ((cTempList[0].G+2*cTempList[1].G)/3);
	}
	word iTempList[16];
	for(i = 0;i<16;i++){
		iTempList[i] = idxPart & 0x0003;
		idxPart >>= 2;
	}
	clist.clear();
	for(i = 0;i<16;i++){
		clist.push_back(cTempList[iTempList[i]]);
	}
}
void DDS::DXT1_uncompress(matrix &mat){
	mat.create(header.height, header.width);
	dword blockrow = mat.getHeight()/4;
	dword blockcol = mat.getWidth()/4;
	long i,j;
	colorList _cl;
	stream s;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			data.readStream(s, 8);
			DXT1_uncompress(s, _cl);
			mat[4*j+0][4*i+0] = _cl[0];
			mat[4*j+0][4*i+1] = _cl[1];
			mat[4*j+0][4*i+2] = _cl[2];
			mat[4*j+0][4*i+3] = _cl[3];
			mat[4*j+1][4*i+0] = _cl[4];
			mat[4*j+1][4*i+1] = _cl[5];
			mat[4*j+1][4*i+2] = _cl[6];
			mat[4*j+1][4*i+3] = _cl[7];
			mat[4*j+2][4*i+0] = _cl[8];
			mat[4*j+2][4*i+1] = _cl[9];
			mat[4*j+2][4*i+2] = _cl[10];
			mat[4*j+2][4*i+3] =	_cl[11];
			mat[4*j+3][4*i+0] = _cl[12];
			mat[4*j+3][4*i+1] = _cl[13];
			mat[4*j+3][4*i+2] = _cl[14];
			mat[4*j+3][4*i+3] = _cl[15];
			s.release();
		}
	}
}
void DDS::DXT3_uncompress(const stream &udata, colorList &clist){
	int i;
	dword clrPart = udata[8] | (udata[9]<<8) | (udata[10]<<16) | (udata[11]<<24);
	dword idxPart = udata[12] | (udata[13]<<8) | (udata[14]<<16) | (udata[15]<<24);
	//颜色提取
	word uc1 = clrPart & 0xffff;	//关键颜色1
	word uc2 = clrPart >> 16;	//关键颜色2
	color cTempList[4];			//四种颜色计算
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	cTempList[2].A = (0xff);	//透明度先缺省
	cTempList[2].B = ((2*cTempList[0].B+cTempList[1].B)/3);
	cTempList[2].R = ((2*cTempList[0].R+cTempList[1].R)/3);
	cTempList[2].G = ((2*cTempList[0].G+cTempList[1].G)/3);
	cTempList[3].A = (0xff);	//透明度先缺省
	cTempList[3].B = ((cTempList[0].B+2*cTempList[1].B)/3);
	cTempList[3].R = ((cTempList[0].R+2*cTempList[1].R)/3);
	cTempList[3].G = ((cTempList[0].G+2*cTempList[1].G)/3);
	//颜色索引
	word iTempList1[16];
	for(i = 0;i<16;i++){
		iTempList1[i] = idxPart & 0x0003;
		idxPart >>= 2;
	}
	//透明提取
	word iTempList2[16];
	iTempList2[0] = (udata[0] & 0xf) * 0x11;
	iTempList2[1] = (udata[0] >>  4) * 0x11;
	iTempList2[2] = (udata[1] & 0xf) * 0x11;
	iTempList2[3] = (udata[1] >>  4) * 0x11;
	iTempList2[4] = (udata[2] & 0xf) * 0x11;
	iTempList2[5] = (udata[2] >>  4) * 0x11;
	iTempList2[6] = (udata[3] & 0xf) * 0x11;
	iTempList2[7] = (udata[3] >>  4) * 0x11;
	iTempList2[8] = (udata[4] & 0xf) * 0x11;
	iTempList2[9] = (udata[4] >>  4) * 0x11;
	iTempList2[10] = (udata[5] & 0xf) * 0x11;
	iTempList2[11] = (udata[5] >>  4) * 0x11;
	iTempList2[12] = (udata[6] & 0xf) * 0x11;
	iTempList2[13] = (udata[6] >>  4) * 0x11;
	iTempList2[14] = (udata[7] & 0xf) * 0x11;
	iTempList2[15] = (udata[7] >>  4) * 0x11;
	clist.clear();
	color cTemp;
	for(i = 0;i<16;i++){
		cTemp = cTempList[iTempList1[i]];
		cTemp.A = (iTempList2[i]);
		clist.push_back(cTemp);
	}
}
void DDS::DXT3_uncompress(matrix &mat){
	mat.create(header.height, header.width);
	dword blockrow = mat.getHeight()/4;
	dword blockcol = mat.getWidth()/4;
	long i,j;
	colorList _cl;
	stream s;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			data.readStream(s, 16);
			DXT3_uncompress(s, _cl);
			mat[4*j+0][4*i+0] = _cl[0];
			mat[4*j+0][4*i+1] = _cl[1];
			mat[4*j+0][4*i+2] = _cl[2];
			mat[4*j+0][4*i+3] = _cl[3];
			mat[4*j+1][4*i+0] = _cl[4];
			mat[4*j+1][4*i+1] = _cl[5];
			mat[4*j+1][4*i+2] = _cl[6];
			mat[4*j+1][4*i+3] = _cl[7];
			mat[4*j+2][4*i+0] = _cl[8];
			mat[4*j+2][4*i+1] = _cl[9];
			mat[4*j+2][4*i+2] = _cl[10];
			mat[4*j+2][4*i+3] =	_cl[11];
			mat[4*j+3][4*i+0] = _cl[12];
			mat[4*j+3][4*i+1] = _cl[13];
			mat[4*j+3][4*i+2] = _cl[14];
			mat[4*j+3][4*i+3] = _cl[15];
			s.release();
		}
	}
}
void DDS::DXT5_uncompress(const stream &udata, colorList &clist){
	int i;
	dword clrPart = udata[8] | (udata[9]<<8) | (udata[10]<<16) | (udata[11]<<24);
	dword idxPart = udata[12] | (udata[13]<<8) | (udata[14]<<16) | (udata[15]<<24);
	//颜色提取
	word uc1 = clrPart & 0xffff;	//关键颜色1
	word uc2 = clrPart >> 16;	//关键颜色2
	color cTempList[4];			//四种颜色计算
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	cTempList[2].A = (0xff);	//透明度先缺省
	cTempList[2].B = ((2*cTempList[0].B+cTempList[1].B)/3);
	cTempList[2].R = ((2*cTempList[0].R+cTempList[1].R)/3);
	cTempList[2].G = ((2*cTempList[0].G+cTempList[1].G)/3);
	cTempList[3].A = (0xff);	//透明度先缺省
	cTempList[3].B = ((cTempList[0].B+2*cTempList[1].B)/3);
	cTempList[3].R = ((cTempList[0].R+2*cTempList[1].R)/3);
	cTempList[3].G = ((cTempList[0].G+2*cTempList[1].G)/3);
	//颜色索引
	word iTempList1[16];
	for(i = 0;i<16;i++){
		iTempList1[i] = idxPart & 0x0003;
		idxPart >>= 2;
	}
	//透明提取
	Koishi::uchar ua1 = udata[0];	//关键透明度1
	Koishi::uchar ua2 = udata[1];	//关键透明度2
	Koishi::uchar aTempList[8];
	aTempList[0] = ua1;
	aTempList[1] = ua2;
	if(ua1<=ua2){
		aTempList[2] = (4*ua1 + 1*ua2)/5;
		aTempList[3] = (3*ua1 + 2*ua2)/5;
		aTempList[4] = (2*ua1 + 3*ua2)/5;
		aTempList[5] = (1*ua1 + 4*ua2)/5;
		aTempList[6] = 0;
		aTempList[7] = 0xff;
	}else{
		aTempList[2] = (6*ua1 + 1*ua2)/7;
		aTempList[3] = (5*ua1 + 2*ua2)/7;
		aTempList[4] = (4*ua1 + 3*ua2)/7;
		aTempList[5] = (3*ua1 + 4*ua2)/7;
		aTempList[6] = (2*ua1 + 5*ua2)/7;
		aTempList[7] = (1*ua1 + 6*ua2)/7;
	}
	//透明度索引
	word iTempList2[16];
	iTempList2[0] = ((udata[2] & 0x07) >> 0);
	iTempList2[1] = ((udata[2] & 0x38) >> 3);
	iTempList2[2] = ((udata[2] & 0xC0) >> 6) | ((udata[3] & 0x01) << 2);
	iTempList2[3] = ((udata[3] & 0x0E) >> 1);
	iTempList2[4] = ((udata[3] & 0x70) >> 4);
	iTempList2[5] = ((udata[3] & 0x80) >> 7) | ((udata[4] & 0x03) << 1);
	iTempList2[6] = ((udata[4] & 0x1C) >> 2);
	iTempList2[7] = ((udata[4] & 0xE0) >> 5);
	iTempList2[8] = ((udata[5] & 0x07) >> 0);
	iTempList2[9] = ((udata[5] & 0x38) >> 3);
	iTempList2[10] = ((udata[5] & 0xC0) >> 6) | ((udata[6] & 0x01) << 2);
	iTempList2[11] = ((udata[6] & 0x0E) >> 1);
	iTempList2[12] = ((udata[6] & 0x70) >> 4);
	iTempList2[13] = ((udata[6] & 0x80) >> 7) | ((udata[7] & 0x03) << 1);
	iTempList2[14] = ((udata[7] & 0x1C) >> 2);
	iTempList2[15] = ((udata[7] & 0xE0) >> 5);
	clist.clear();
	color cTemp;
	for(i = 0;i<16;i++){
		cTemp = cTempList[iTempList1[i]];
		cTemp.A = (aTempList[iTempList2[i]]);
		clist.push_back(cTemp);
	}
}
void DDS::DXT5_uncompress(matrix &mat){
	mat.create(header.height, header.width);
	dword blockrow = mat.getHeight()/4;
	dword blockcol = mat.getWidth()/4;
	long i,j;
	colorList _cl;
	stream s;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			data.readStream(s, 16);
			DXT5_uncompress(s, _cl);
			mat[4*j+0][4*i+0] = _cl[0];
			mat[4*j+0][4*i+1] = _cl[1];
			mat[4*j+0][4*i+2] = _cl[2];
			mat[4*j+0][4*i+3] = _cl[3];
			mat[4*j+1][4*i+0] = _cl[4];
			mat[4*j+1][4*i+1] = _cl[5];
			mat[4*j+1][4*i+2] = _cl[6];
			mat[4*j+1][4*i+3] = _cl[7];
			mat[4*j+2][4*i+0] = _cl[8];
			mat[4*j+2][4*i+1] = _cl[9];
			mat[4*j+2][4*i+2] = _cl[10];
			mat[4*j+2][4*i+3] =	_cl[11];
			mat[4*j+3][4*i+0] = _cl[12];
			mat[4*j+3][4*i+1] = _cl[13];
			mat[4*j+3][4*i+2] = _cl[14];
			mat[4*j+3][4*i+3] = _cl[15];
			s.release();
		}
	}
}
void DDS::DXT5_compress(const colorList &clist, stream &dest){
	int i;
	Koishi::uchar iTempList[16];		//存储透明度索引
	Koishi::uchar cTempList[16];		//存储颜色索引
	dest.allocate(16);
	//透明度处理
	//确定是否使用alpha7=0,alph8=0xff
	bool flUseBound = false;
	for(i=0;i<16;i++){
		if(clist[i].A == 0 || clist[i].A == 0xff){
			flUseBound = true;
			break;
		}
	}
	if(flUseBound){
		//ua1需要小于等于ua2，分5份
		Koishi::uchar ua1 = 0xff;	//非零最小值初始化
		Koishi::uchar ua2 = 0;		//非FF最大值初始化
		Koishi::uchar uTemp;
		for(i=0;i<16;i++){
			uTemp = clist[i].A;
			if(uTemp != 0 && uTemp<ua1){
				ua1 = uTemp;
			}
			if(uTemp != 0xff && uTemp>ua2){
				ua2 = uTemp;
			}
		}
		if(ua1>ua2){
			ua1 = 0;
			ua2 = 0xff;
		}
		//计算落在哪个区间里
		//(a7)0____|____(a1)___|___(a3)___|___(a4)___|___(a5)___|___(a6)___|___(a2)_______|_______0xff(a8)
		//扩充8位，以便除法运算更为精确
		word uTempb;
		word uab1 = ua1 << 8;
		word uab2 = ua2 << 8;
		word uad1 = uab1/2;
		word uad2 = (uab2-uab1)/10;
		word uad3 = (0xffff-uab2)/2;
		for(i=0;i<16;i++){
			uTempb = clist[i].A<<8;
			if(uTempb <uad1){
				iTempList[i] = 6;
			}else if(uTempb < uab1+uad2){
				iTempList[i] = 0;
			}else if(uTempb < uab1+uad2*3){
				iTempList[i] = 2;
			}else if(uTempb < uab1+uad2*5){
				iTempList[i] = 3;
			}else if(uTempb < uab2-uad2*3){
				iTempList[i] = 4;
			}else if(uTempb < uab2-uad2){
				iTempList[i] = 5;
			}else if(uTempb < uab2+uad3){
				iTempList[i] = 1;
			}else{
				iTempList[i] = 7;
			}
		}
		dest.push(ua1);
		dest.push(ua2);
		dest.push((Koishi::uchar)((iTempList[0]>>0)|(iTempList[1]<<3)|(iTempList[2]<<6)));
		dest.push((Koishi::uchar)((iTempList[2]>>2)|(iTempList[3]<<1)|(iTempList[4]<<4)|(iTempList[5]<<7)));
		dest.push((Koishi::uchar)((iTempList[5]>>1)|(iTempList[6]<<2)|(iTempList[7]<<5)));
		dest.push((Koishi::uchar)((iTempList[8]>>0)|(iTempList[9]<<3)|(iTempList[10]<<6)));
		dest.push((Koishi::uchar)((iTempList[10]>>2)|(iTempList[11]<<1)|(iTempList[12]<<4)|(iTempList[13]<<7)));
		dest.push((Koishi::uchar)((iTempList[13]>>1)|(iTempList[14]<<2)|(iTempList[15]<<5)));
	}else{
		//ua1需要大于ua2，分7份
		Koishi::uchar ua1 = 0;		//最大值初始化
		Koishi::uchar ua2 = 0xff;	//最小值初始化
		Koishi::uchar uTemp;
		for(i=0;i<16;i++){
			uTemp = clist[i].A;
			if(uTemp>ua1){
				ua1 = uTemp;
			}
			if(uTemp<ua2){
				ua2 = uTemp;
			}
		}
		//计算落在哪个区间里
		//...__(a2)__|__(a8)__|__(a7)__|__(a6)__|__(a5)__|__(a4)__|__(a3)__|__(a1)__...
		//扩充8位，以便除法运算更为精确
		word uTempb;
		word uab1 = ua1 << 8;
		word uab2 = ua2 << 8;
		word uad = (uab2-uab1)/14;
		for(i=0;i<16;i++){
			uTempb = clist[i].A<<8;
			if(uTempb <uab2+uad){
				iTempList[i] = 1;
			}else if(uTempb < uab2+3*uad){
				iTempList[i] = 7;
			}else if(uTempb < uab2+5*uad){
				iTempList[i] = 6;
			}else if(uTempb < uab2+7*uad){
				iTempList[i] = 5;
			}else if(uTempb < uab1-5*uad){
				iTempList[i] = 4;
			}else if(uTempb < uab1-3*uad){
				iTempList[i] = 3;
			}else if(uTempb < uab1-uad){
				iTempList[i] = 2;
			}else{
				iTempList[i] = 0;
			}
		}
		dest.push(ua1);
		dest.push(ua2);
		dest.push((Koishi::uchar)((iTempList[0]>>0)|(iTempList[1]<<3)|(iTempList[2]<<6)));
		dest.push((Koishi::uchar)((iTempList[2]>>2)|(iTempList[3]<<1)|(iTempList[4]<<4)|(iTempList[5]<<7)));
		dest.push((Koishi::uchar)((iTempList[5]>>1)|(iTempList[6]<<2)|(iTempList[7]<<5)));
		dest.push((Koishi::uchar)((iTempList[8]>>0)|(iTempList[9]<<3)|(iTempList[10]<<6)));
		dest.push((Koishi::uchar)((iTempList[10]>>2)|(iTempList[11]<<1)|(iTempList[12]<<4)|(iTempList[13]<<7)));
		dest.push((Koishi::uchar)((iTempList[13]>>1)|(iTempList[14]<<2)|(iTempList[15]<<5)));
	}
	//颜色处理
	//不同于DXT1，无需考虑两个关键颜色谁大谁小，默认uc1<=uc2，但采用alpha7=0,alph8=0xff时不应该考虑alpha=7或8的时候的情形
	dword ucb1 = 0xffffff;	//小关键颜色 高位R 中位G 低位B
	dword ucb2 = 0;			//大关键颜色
	for(i=0;i<16;i++){
		longex tempClr = clist[i].R | clist[i].G << 8 | clist[i].B <<16; 
		//若使用边界透明度，则不能考虑透明度为0的情形
		if(flUseBound){
			if(clist[i].A != 0){
				if(tempClr>ucb2){
					ucb2 = tempClr;
				}
				if(tempClr<ucb1){
					ucb1 = tempClr;
				}
			}
		}else{
			if(tempClr>ucb2){
				ucb2 = tempClr;
			}
			if(tempClr<ucb1){
				ucb1 = tempClr;
			}
		}
	}
	//计算落在哪个区间里
	//...__(a1)__|__(a3)__|__(a4)__|__(a2)__...
	dword ucdb = (ucb2-ucb1)/6;
	for(i=0;i<16;i++){
		dword tempClr = clist[i].R | clist[i].G << 8 | clist[i].B << 16; 
		if(tempClr <ucb1+ucdb){
			cTempList[i] = 0;
		}else if(tempClr < ucb1+ucdb*3){
			cTempList[i] = 2;
		}else if(tempClr < ucb2-ucdb){
			cTempList[i] = 3;
		}else{
			cTempList[i] = 1;
		}
	}
	dest.push(RGB8888TO565(color(ucb1 >> 16, ucb1 >> 8 & 0xff, ucb1 & 0xff)));
	dest.push(RGB8888TO565(color(ucb2 >> 16, ucb2 >> 8 & 0xff, ucb2 & 0xff)));
	dest.push((Koishi::uchar)((cTempList[0]>>0)|(cTempList[1]<<2)|(cTempList[2]<<4)|(cTempList[3]<<6)));
	dest.push((Koishi::uchar)((cTempList[4]>>0)|(cTempList[5]<<2)|(cTempList[6]<<4)|(cTempList[7]<<6)));
	dest.push((Koishi::uchar)((cTempList[8]>>0)|(cTempList[9]<<2)|(cTempList[10]<<4)|(cTempList[11]<<6)));
	dest.push((Koishi::uchar)((cTempList[12]>>0)|(cTempList[13]<<2)|(cTempList[14]<<4)|(cTempList[15]<<6)));
}

void DDS::DXT5_compress(const matrix &mat){
	matrix mat1;
	dword blockrow = (mat.getHeight()+3)/4;
	dword blockcol = (mat.getWidth()+3)/4;
	data.reallocate(blockrow*blockcol*16);
	mat.expand(mat1, 0, 4*blockrow-mat.getHeight(), 0, 4*blockcol-mat.getWidth());
	dword i,j;
	stream s;
	colorList clrList;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			clrList.clear();
			clrList.push_back(mat1[4*j+0][4*i+0]);
			clrList.push_back(mat1[4*j+0][4*i+1]);
			clrList.push_back(mat1[4*j+0][4*i+2]);
			clrList.push_back(mat1[4*j+0][4*i+3]);
			clrList.push_back(mat1[4*j+1][4*i+0]);
			clrList.push_back(mat1[4*j+1][4*i+1]);
			clrList.push_back(mat1[4*j+1][4*i+2]);
			clrList.push_back(mat1[4*j+1][4*i+3]);
			clrList.push_back(mat1[4*j+2][4*i+0]);
			clrList.push_back(mat1[4*j+2][4*i+1]);
			clrList.push_back(mat1[4*j+2][4*i+2]);
			clrList.push_back(mat1[4*j+2][4*i+3]);
			clrList.push_back(mat1[4*j+3][4*i+0]);
			clrList.push_back(mat1[4*j+3][4*i+1]);
			clrList.push_back(mat1[4*j+3][4*i+2]);
			clrList.push_back(mat1[4*j+3][4*i+3]);
			DXT5_compress(clrList, s);
			data.pushStream(s,16);
			s.release();
		}
	}
}