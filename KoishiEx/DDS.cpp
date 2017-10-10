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
	if(_v != 0x81007)
		b = false;
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
	b &= load(s);
	s.release();
	return b;
}
bool DDS::make(stream &s){
	return false;
}
bool DDS::makeFile(const str &DDSfileName){
	return false;
}
bool DDS::uncompress(matrix &mat){
	switch(header.pixelFormat.fourCC){
	case 0x31545844:
		DXT1_uncompress(mat);
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

b16 DDS::RGB8888TO565(color c8888){
	b16 c565 = 0;
	c565 |= (c8888.get_R() >> 3 << 11);
	c565 |= (c8888.get_G() >> 2 << 5);
	c565 |= (c8888.get_B() >> 3);
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
	i32 i,j,k;
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
	i32 i,j,k;
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