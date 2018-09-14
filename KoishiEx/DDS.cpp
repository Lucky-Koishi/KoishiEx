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
	data1.release();
	data2.release();
}
DDSHeader *DDS::getHeader(){
	return &header;
}
bool DDS::load(const stream &s){
	stream _s(s);
	bool b = true;
	b32 _v;
	i32 i;
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
	data1.allocate(header.pitchOrLinearSize + 1000);
	_s.readStream(data1, header.pitchOrLinearSize);
	data2.allocate(header.pitchOrLinearSize + 1000);
	_s.readStream(data2, header.pitchOrLinearSize);
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
	s.allocate(128+data1.getLen()+data2.getLen()+2000);

	s.push((b32)header.magic);
	s.push((b32)header.headSize);
	s.push((b32)header.flags);
	s.push((b32)header.height);
	s.push((b32)header.width);
	s.push((b32)header.pitchOrLinearSize);
	s.push((b32)header.depth);
	s.push((b32)header.mipMapCount);
	s.push((b32)header.reserved1[0]);
	s.push((b32)header.reserved1[1]);
	s.push((b32)header.reserved1[2]);
	s.push((b32)header.reserved1[3]);
	s.push((b32)header.reserved1[4]);
	s.push((b32)header.reserved1[5]);
	s.push((b32)header.reserved1[6]);
	s.push((b32)header.reserved1[7]);
	s.push((b32)header.reserved1[8]);
	s.push((b32)header.reserved1[9]);
	s.push((b32)header.reserved1[10]);
	s.push((b32)header.pixelFormat.size);
	s.push((b32)header.pixelFormat.flags);
	s.push((b32)header.pixelFormat.fourCC);
	s.push((b32)header.pixelFormat.rgbBitCount);
	s.push((b32)header.pixelFormat.rBitMask);
	s.push((b32)header.pixelFormat.gBitMask);
	s.push((b32)header.pixelFormat.bBitMask);
	s.push((b32)header.pixelFormat.aBitMask);
	s.push((b32)header.caps1);
	s.push((b32)header.caps2);
	s.push((b32)header.caps3);
	s.push((b32)header.caps4);
	s.push((b32)header.reserved2);
	s.pushStream(data1,data1.getLen());
	s.pushStream(data2,data2.getLen());
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
bool DDS::compress(const matrix &mat){
	DXT5_compress(mat);
	//设置头
	header.magic = 0x20534444;
	header.headSize = 0x7c;
	header.flags = 0x81007;
	header.height = (mat.getRowCount()+3)/4*4;
	header.width = (mat.getColumnCount()+3)/4*4;
	header.pitchOrLinearSize = data1.getLen();
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
b16 DDS::RGB8888TO565(color c8888){
	b16 c565 = 0;
	c565 |= (c8888.get_B() >> 3 << 11);
	c565 |= (c8888.get_G() >> 2 << 5);
	c565 |= (c8888.get_R() >> 3);
	return c565;
}
color DDS::RGB565TO8888(b16 c565){
	color c8888(0);
	c8888.set_A(0xFF);
	c8888.set_R((c565 & 0xf800)>>8);
	c8888.set_G((c565 & 0x07e0)>>3);
	c8888.set_B((c565 & 0x001f)<<3);
	return c8888;
}
void DDS::DXT1_uncompress(const stream &udata, lcolor &clist){
	i16 i;
	b32 clrPart = udata[0] | (udata[1]<<8) | (udata[2]<<16) | (udata[3]<<24);
	b32 idxPart = udata[4] | (udata[5]<<8) | (udata[6]<<16) | (udata[7]<<24);
	b16 uc1 = clrPart & 0xffff;
	b16 uc2 = clrPart >> 16;
	color cTempList[4];
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	if(uc1<=uc2){
		cTempList[2].set_A(0xff);
		cTempList[2].set_B((cTempList[0].get_B()+cTempList[1].get_B())/2);
		cTempList[2].set_R((cTempList[0].get_R()+cTempList[1].get_R())/2);
		cTempList[2].set_G((cTempList[0].get_G()+cTempList[1].get_G())/2);
		cTempList[3].set_A(0x00);
	}else{
		cTempList[2].set_A(0xff);
		cTempList[2].set_B((2*cTempList[0].get_B()+cTempList[1].get_B())/3);
		cTempList[2].set_R((2*cTempList[0].get_R()+cTempList[1].get_R())/3);
		cTempList[2].set_G((2*cTempList[0].get_G()+cTempList[1].get_G())/3);
		cTempList[3].set_A(0xff);
		cTempList[3].set_B((cTempList[0].get_B()+2*cTempList[1].get_B())/3);
		cTempList[3].set_R((cTempList[0].get_R()+2*cTempList[1].get_R())/3);
		cTempList[3].set_G((cTempList[0].get_G()+2*cTempList[1].get_G())/3);
	}
	b16 iTempList[16];
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
	mat.allocate(header.height, header.width);
	b32 blockrow = mat.getRowCount()/4;
	b32 blockcol = mat.getColumnCount()/4;
	i32 i,j;
	lcolor _cl;
	stream s;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			data1.readStream(s, 8);
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
void DDS::DXT3_uncompress(const stream &udata, lcolor &clist){
	i16 i;
	b32 clrPart = udata[8] | (udata[9]<<8) | (udata[10]<<16) | (udata[11]<<24);
	b32 idxPart = udata[12] | (udata[13]<<8) | (udata[14]<<16) | (udata[15]<<24);
	//颜色提取
	b16 uc1 = clrPart & 0xffff;	//关键颜色1
	b16 uc2 = clrPart >> 16;	//关键颜色2
	color cTempList[4];			//四种颜色计算
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	cTempList[2].set_A(0xff);	//透明度先缺省
	cTempList[2].set_B((2*cTempList[0].get_B()+cTempList[1].get_B())/3);
	cTempList[2].set_R((2*cTempList[0].get_R()+cTempList[1].get_R())/3);
	cTempList[2].set_G((2*cTempList[0].get_G()+cTempList[1].get_G())/3);
	cTempList[3].set_A(0xff);	//透明度先缺省
	cTempList[3].set_B((cTempList[0].get_B()+2*cTempList[1].get_B())/3);
	cTempList[3].set_R((cTempList[0].get_R()+2*cTempList[1].get_R())/3);
	cTempList[3].set_G((cTempList[0].get_G()+2*cTempList[1].get_G())/3);
	//颜色索引
	b16 iTempList1[16];
	for(i = 0;i<16;i++){
		iTempList1[i] = idxPart & 0x0003;
		idxPart >>= 2;
	}
	//透明提取
	b16 iTempList2[16];
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
		cTemp.set_A(iTempList2[i]);
		clist.push_back(cTemp);
	}
}
void DDS::DXT3_uncompress(matrix &mat){
	mat.allocate(header.height, header.width);
	b32 blockrow = mat.getRowCount()/4;
	b32 blockcol = mat.getColumnCount()/4;
	i32 i,j;
	lcolor _cl;
	stream s;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			data1.readStream(s, 16);
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
void DDS::DXT5_uncompress(const stream &udata, lcolor &clist){
	i16 i;
	b32 clrPart = udata[8] | (udata[9]<<8) | (udata[10]<<16) | (udata[11]<<24);
	b32 idxPart = udata[12] | (udata[13]<<8) | (udata[14]<<16) | (udata[15]<<24);
	//颜色提取
	b16 uc1 = clrPart & 0xffff;	//关键颜色1
	b16 uc2 = clrPart >> 16;	//关键颜色2
	color cTempList[4];			//四种颜色计算
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	cTempList[2].set_A(0xff);	//透明度先缺省
	cTempList[2].set_B((2*cTempList[0].get_B()+cTempList[1].get_B())/3);
	cTempList[2].set_R((2*cTempList[0].get_R()+cTempList[1].get_R())/3);
	cTempList[2].set_G((2*cTempList[0].get_G()+cTempList[1].get_G())/3);
	cTempList[3].set_A(0xff);	//透明度先缺省
	cTempList[3].set_B((cTempList[0].get_B()+2*cTempList[1].get_B())/3);
	cTempList[3].set_R((cTempList[0].get_R()+2*cTempList[1].get_R())/3);
	cTempList[3].set_G((cTempList[0].get_G()+2*cTempList[1].get_G())/3);
	//颜色索引
	b16 iTempList1[16];
	for(i = 0;i<16;i++){
		iTempList1[i] = idxPart & 0x0003;
		idxPart >>= 2;
	}
	//透明提取
	b8 ua1 = udata[0];	//关键透明度1
	b8 ua2 = udata[1];	//关键透明度2
	b8 aTempList[8];
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
	b16 iTempList2[16];
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
		cTemp.set_A(aTempList[iTempList2[i]]);
		clist.push_back(cTemp);
	}
}
void DDS::DXT5_uncompress(matrix &mat){
	mat.allocate(header.height, header.width);
	b32 blockrow = mat.getRowCount()/4;
	b32 blockcol = mat.getColumnCount()/4;
	i32 i,j;
	lcolor _cl;
	stream s;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			data1.readStream(s, 16);
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
void DDS::DXT5_uncompress2(matrix &mat){
	mat.allocate(header.height*5/4, header.width*5/4);
	b32 blockrow = header.height/4;
	b32 blockcol = header.width/4;
	i32 i,j;
	lcolor _cl;
	stream s;
	for(j=0;j<blockrow;j++){
		for(i=0;i<blockcol;i++){
			data1.readStream(s, 16);
			DXT5_uncompress(s, _cl);
			mat[5*j+0][5*i+0] = _cl[0];
			mat[5*j+0][5*i+1] = _cl[1];
			mat[5*j+0][5*i+2] = _cl[2];
			mat[5*j+0][5*i+3] = _cl[3];
			mat[5*j+0][5*i+4] = 0;
			mat[5*j+1][5*i+0] = _cl[4];
			mat[5*j+1][5*i+1] = _cl[5];
			mat[5*j+1][5*i+2] = _cl[6];
			mat[5*j+1][5*i+3] = _cl[7];
			mat[5*j+1][5*i+4] = 0;
			mat[5*j+2][5*i+0] = _cl[8];
			mat[5*j+2][5*i+1] = _cl[9];
			mat[5*j+2][5*i+2] = _cl[10];
			mat[5*j+2][5*i+3] =	_cl[11];
			mat[5*j+2][5*i+4] = 0;
			mat[5*j+3][5*i+0] = _cl[12];
			mat[5*j+3][5*i+1] = _cl[13];
			mat[5*j+3][5*i+2] = _cl[14];
			mat[5*j+3][5*i+3] = _cl[15];
			mat[5*j+3][5*i+4] = 0;
			mat[5*j+4][5*i+4] = 0;
			mat[5*j+4][5*i+4] = 0;
			mat[5*j+4][5*i+4] = 0;
			mat[5*j+4][5*i+4] = 0;
			mat[5*j+4][5*i+4] = 0;
			s.release();
		}
	}
}
void DDS::DXT5_compress(const lcolor &clist, stream &dest){
	i16 i;
	b8 iTempList[16];		//存储透明度索引
	b8 cTempList[16];		//存储颜色索引
	dest.allocate(16);
	//透明度处理
	//确定是否使用alpha7=0,alph8=0xff
	bool flUseBound = false;
	for(i=0;i<16;i++){
		if(clist[i].get_A() == 0 || clist[i].get_A() == 0xff){
			flUseBound = true;
			break;
		}
	}
	if(flUseBound){
		//ua1需要小于等于ua2，分5份
		b8 ua1 = 0xff;	//非零最小值初始化
		b8 ua2 = 0;		//非FF最大值初始化
		b8 uTemp;
		for(i=0;i<16;i++){
			uTemp = clist[i].get_A();
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
		b16 uTempb;
		b16 uab1 = ua1 << 8;
		b16 uab2 = ua2 << 8;
		b16 uad1 = uab1/2;
		b16 uad2 = (uab2-uab1)/10;
		b16 uad3 = (0xffff-uab2)/2;
		for(i=0;i<16;i++){
			uTempb = clist[i].get_A()<<8;
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
		dest.push((b8)((iTempList[0]>>0)|(iTempList[1]<<3)|(iTempList[2]<<6)));
		dest.push((b8)((iTempList[2]>>2)|(iTempList[3]<<1)|(iTempList[4]<<4)|(iTempList[5]<<7)));
		dest.push((b8)((iTempList[5]>>1)|(iTempList[6]<<2)|(iTempList[7]<<5)));
		dest.push((b8)((iTempList[8]>>0)|(iTempList[9]<<3)|(iTempList[10]<<6)));
		dest.push((b8)((iTempList[10]>>2)|(iTempList[11]<<1)|(iTempList[12]<<4)|(iTempList[13]<<7)));
		dest.push((b8)((iTempList[13]>>1)|(iTempList[14]<<2)|(iTempList[15]<<5)));
	}else{
		//ua1需要大于ua2，分7份
		b8 ua1 = 0;		//最大值初始化
		b8 ua2 = 0xff;	//最小值初始化
		b8 uTemp;
		for(i=0;i<16;i++){
			uTemp = clist[i].get_A();
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
		b16 uTempb;
		b16 uab1 = ua1 << 8;
		b16 uab2 = ua2 << 8;
		b16 uad = (uab2-uab1)/14;
		for(i=0;i<16;i++){
			uTempb = clist[i].get_A()<<8;
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
		dest.push((b8)((iTempList[0]>>0)|(iTempList[1]<<3)|(iTempList[2]<<6)));
		dest.push((b8)((iTempList[2]>>2)|(iTempList[3]<<1)|(iTempList[4]<<4)|(iTempList[5]<<7)));
		dest.push((b8)((iTempList[5]>>1)|(iTempList[6]<<2)|(iTempList[7]<<5)));
		dest.push((b8)((iTempList[8]>>0)|(iTempList[9]<<3)|(iTempList[10]<<6)));
		dest.push((b8)((iTempList[10]>>2)|(iTempList[11]<<1)|(iTempList[12]<<4)|(iTempList[13]<<7)));
		dest.push((b8)((iTempList[13]>>1)|(iTempList[14]<<2)|(iTempList[15]<<5)));
	}
	//颜色处理
	//不同于DXT1，无需考虑两个关键颜色谁大谁小，默认uc1<=uc2，但采用alpha7=0,alph8=0xff时不应该考虑alpha=7或8的时候的情形
	b32 ucb1 = 0xffffff;	//小关键颜色 高位R 中位G 低位B
	b32 ucb2 = 0;			//大关键颜色
	for(i=0;i<16;i++){
		b64 tempClr = clist[i].get_R() | clist[i].get_G() << 8 | clist[i].get_B() <<16; 
		//若使用边界透明度，则不能考虑透明度为0的情形
		if(flUseBound){
			if(clist[i].get_A() != 0){
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
	b32 ucdb = (ucb2-ucb1)/6;
	for(i=0;i<16;i++){
		b32 tempClr = clist[i].get_R() | clist[i].get_G() << 8 | clist[i].get_B() << 16; 
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
	dest.push((b8)((cTempList[0]>>0)|(cTempList[1]<<2)|(cTempList[2]<<4)|(cTempList[3]<<6)));
	dest.push((b8)((cTempList[4]>>0)|(cTempList[5]<<2)|(cTempList[6]<<4)|(cTempList[7]<<6)));
	dest.push((b8)((cTempList[8]>>0)|(cTempList[9]<<2)|(cTempList[10]<<4)|(cTempList[11]<<6)));
	dest.push((b8)((cTempList[12]>>0)|(cTempList[13]<<2)|(cTempList[14]<<4)|(cTempList[15]<<6)));
}

void DDS::DXT5_compress(const matrix &mat){
	matrix mat1;
	b32 blockrow = (mat.getRowCount()+3)/4;
	b32 blockcol = (mat.getColumnCount()+3)/4;
	data1.reallocate(blockrow*blockcol*16);
	mat.expandMatrix(mat1, 0, 4*blockrow-mat.getRowCount(), 0, 4*blockcol-mat.getColumnCount());
	b32 i,j;
	stream s;
	lcolor clrList;
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
			data1.pushStream(s,16);
			s.release();
		}
	}
}