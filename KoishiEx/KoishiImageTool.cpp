#include "StdAfx.h"
#include "KoishiImageTool.h"
#include "KoishiNeoplePack.h"

using namespace Koishi;
using namespace KoishiImageTool;
using namespace KoishiImageTool::BMP;
using namespace KoishiImageTool::PNG;
using namespace KoishiImageTool::GIF;
using namespace KoishiImageTool::DDS;
using namespace KoishiImageTool::JFIF;
/////////////图像工具////////////////////
color KoishiImageTool::gradient(const color &sourceColor, const colorList &keyColorList, Koishi::colorProperty cp){
	if(keyColorList.size() == 0){
		return sourceColor;
	}
	if(keyColorList.size() == 1){
		return keyColorList[0];
	}
	double theProp = sourceColor.getProperty(cp);
	double delta = 1.0/(keyColorList.size()-1);		//步长
	int step = (int)(theProp / delta);
	if(step >= keyColorList.size() - 1){
		step = keyColorList.size() - 2;
	}
	return color(
		(uchar)(theProp*keyColorList[step].alpha) + (uchar)((1-theProp)*keyColorList[step+1].alpha),
		(uchar)(theProp*keyColorList[step].R) + (uchar)((1-theProp)*keyColorList[step+1].R),
		(uchar)(theProp*keyColorList[step].G) + (uchar)((1-theProp)*keyColorList[step+1].G),
		(uchar)(theProp*keyColorList[step].B) + (uchar)((1-theProp)*keyColorList[step+1].B)
	);
}
colorList KoishiImageTool::rainbowSort(const colorList &originList){
	colorList oldColorList = originList;
	colorList newColorList;
	for(int i = 0;i<originList.size();i++){
		int minValue = 36100;
		int minID = -1;
		for(int j = 0;j<oldColorList.size();j++){
			colorHSV hsv;
			oldColorList[j].getHSV(hsv);
			int value = 100*hsv.H + 100 * hsv.V+ 10 * hsv.S;
			if(value < minValue){
				minID = j;
				minValue = value;
			}
		}
		newColorList.push_back(oldColorList[minID]);
		oldColorList.erase(oldColorList.begin() + minID);
	}
	return newColorList;
}
colorList KoishiImageTool::nearbySort(const colorList &originList){
	colorList oldColorList = originList;
	colorList newColorList;
	for(int i = 0;i<originList.size();i++){
		if(i == 0){
			newColorList.push_back(oldColorList[0]);
			oldColorList.erase(oldColorList.begin());
			continue;
		}
		int minDist = 196608;
		int minID = -1;
		for(int j = 0;j<oldColorList.size();j++){
			int dist = color::distance_2(newColorList[i-1], oldColorList[j]);
			if(dist < minDist){
				minID = j;
				minDist = dist;
			}
		}
		newColorList.push_back(oldColorList[minID]);
		oldColorList.erase(oldColorList.begin() + minID);
	}
	return newColorList;
}
///////////BMP//////////////////
void KoishiImageTool::makeBMP(const image &mat, str fileName){
	BMPobject bo;
	bo.input(mat);
	bo.makeFile(fileName);
}
bool KoishiImageTool::loadBMP(image &mat, str fileName){
	BMPobject bo;
	if(bo.loadFile(fileName)){
		bo.output(mat);
		return true;
	}
	return false;
}
bool BMPobject::load(stream s){
	s.resetPosition();
	s.readWord(header.magic);
	if(header.magic != 0x4D42)
		return false;
	s.readDWord(header.fileSize);
	s.readDWord(header.reserved);
	s.readDWord(header.dataOffset);
	s.readDWord(info.infoSize);
	s.readDWord(info.width);
	s.readDWord(info.height);
	s.readWord(info.planes);
	s.readWord(info.bitCount);
	s.readDWord(info.compression);
	s.readDWord(info.dataSize);
	s.readDWord(info.xPixelsPerMeter);
	s.readDWord(info.yPixelsPerMeter);
	s.readDWord(info.colorUsed);
	s.readDWord(info.colorImportant);
	paletteColor.clear();
	if(info.bitCount <= 8){
		for(int i = 0;i<(1<<info.bitCount);i++){
			color clr;
			s.readByte(clr.B);
			s.readByte(clr.G);
			s.readByte(clr.R);
			s.readByte(clr.alpha);
			clr.alpha = 0xFF;
			paletteColor.push_back(clr);
		}
	}
	s.readStream(data, header.fileSize - header.dataOffset);
	return true;
}
bool BMPobject::loadFile(str fileName){
	stream s;
	s.loadFile(fileName);
	return load(s);
}
void BMPobject::make(stream &s){
	s.release();
	s.allocate(header.dataOffset + data.length);
	s.pushWord(header.magic);
	s.pushDWord(header.fileSize);
	s.pushDWord(header.reserved);
	s.pushDWord(header.dataOffset);
	s.pushDWord(info.infoSize);
	s.pushDWord(info.width);
	s.pushDWord(info.height);
	s.pushWord(info.planes);
	s.pushWord(info.bitCount);
	s.pushDWord(info.compression);
	s.pushDWord(info.dataSize);
	s.pushDWord(info.xPixelsPerMeter);
	s.pushDWord(info.yPixelsPerMeter);
	s.pushDWord(info.colorUsed);
	s.pushDWord(info.colorImportant);
	for(long i = 0;i<paletteColor.size();i++){
		s.pushByte(paletteColor[i].B);
		s.pushByte(paletteColor[i].G);
		s.pushByte(paletteColor[i].R);
		s.pushByte(0);
	}
	s.pushStream(data, data.length);
}
void BMPobject::makeFile(str fileName){
	stream s;
	make(s);
	s.makeFile(fileName);
}
void BMPobject::output(image &mat){
	long bitPerRow = info.width * info.bitCount;
	long dwPerRow = bitPerRow / 32;
	if(bitPerRow & 0x1F){
		dwPerRow ++;	//补零
	}
	data.resetPosition();
	stream lineStream;
	mat.create(size(info.width, info.height));
	for(long i = 0;i<info.height;i++){
		data.readStream(lineStream, 4 * dwPerRow);
		for(long id = 0;id < info.width ;id++){
			if(info.bitCount <= 8){
				//一个字节里对应好几个像素值
				uchar colorID = lineStream.getRBit(id, info.bitCount);
				mat[info.height - i - 1][id] = paletteColor[colorID];
			}else if(info.bitCount == 16){
				//采用RGB555格式
				word currentWord = lineStream[2*id] | lineStream[2*id + 1] << 8;
				uchar mask = 0x1F;
				uchar bValue = currentWord & mask;
				uchar gValue = currentWord >> 5 & mask;
				uchar rValue = currentWord >> 10 & mask;
				mat[info.height - i - 1][id] = color(rValue, gValue, bValue);
			}else if(info.bitCount == 24){
				//采用RGB888格式
				uchar bValue = lineStream[3*id];
				uchar gValue = lineStream[3*id+1];
				uchar rValue = lineStream[3*id+2];
				mat[info.height - i - 1][id] = color(rValue, gValue, bValue);
			}else if(info.bitCount == 32){
				//Alpha位并没有用
				uchar bValue = lineStream[4*id];
				uchar gValue = lineStream[4*id+1];
				uchar rValue = lineStream[4*id+2];
				mat[info.height - i - 1][id] = color(rValue, gValue, bValue);
			}else{
				return;
			}
		}
	}
}
void BMPobject::input(const image &mat){
	paletteColor.clear();
	data.release();
	data.allocate(mat.getElemCount() * 3 + mat.getHeight() * 3 + 1000); //加上高度×3是为补齐4字节预留
	for(long i = mat.getHeight() - 1;i >= 0;i--){
		for(long j = 0;j<mat.getWidth();j++){
			data.pushByte(mat[i][j].B);
			data.pushByte(mat[i][j].G);
			data.pushByte(mat[i][j].R);
		}
		long addZeroCount = data.length % 4;
		for(long j = 0;j<addZeroCount;j++){
			data.pushByte(0);
		}
	}
	header.magic = 0x4D42;
	header.fileSize = 54 + data.length;
	header.reserved = 0;
	header.dataOffset = 54;
	info.infoSize = 40;
	info.width = mat.getWidth();
	info.height = mat.getHeight();
	info.planes = 1;
	info.bitCount = 24;
	info.compression = 0;
	info.dataSize = data.length;
	info.xPixelsPerMeter = 0;
	info.yPixelsPerMeter = 0;
	info.colorUsed = 0;
	info.colorImportant = 0;
}
////PNG/////////////////////
void KoishiImageTool::makePNG(const image &mat, str fileName){
	PNGobject po;
	po.input(mat);
	po.makeFile(fileName);
}
void KoishiImageTool::makePNG(const colorList &clrList, str fileName){
	image mat(20*clrList.size(), 200);
	mat.filledLattice(point(0, 0), point(199, 20*clrList.size()-1), color(0xFF, 0xFF, 0xFF), color(0xCC, 0xCC, 0xCC), 8);
	for(int i = 0;i<clrList.size();i++){
		image mat1(20, 200);
		mat1.fill(clrList[i]);
		mat.putFore(mat1, LAY, point(0, i*20));
		mat1.destory();
	}
	makePNG(mat, fileName);
}
extern bool KoishiImageTool::loadPNG(image &mat, str fileName){
	PNGobject po;
	if(po.loadFile(fileName)){
		po.output(mat);
		return true;
	}
	return false;
}
extern word KoishiImageTool::PNG::PNGword(word originWord){
	return (originWord & 0xFF) << 8 | (originWord & 0xFF00) >> 8; 
}
extern dword KoishiImageTool::PNG::PNGdword(dword originDword){
	return (originDword & 0xFF) << 24 | (originDword & 0xFF00) << 8 | (originDword & 0xFF0000) >> 8 | (originDword & 0xFF000000) >> 24;
}
extern uchar KoishiImageTool::PNG::PNGpaeth(uchar a, uchar b, uchar c){
	short wa = (short)a;
	short wb = (short)b;
	short wc = (short)c;
	short wp = wa + wb - wc;
	short pa = (wp - wa >= 0) ? (wp - wa):(wa - wp);
	short pb = (wp - wb >= 0) ? (wp - wb):(wb - wp);
	short pc = (wp - wc >= 0) ? (wp - wc):(wc - wp);
	if(pa <= pb && pa <= pc)
		return a;
	if(pb <= pc)
		return b;
	return c;
}
extern uchar KoishiImageTool::PNG::PNGaverage(uchar a, uchar b){
	word wa = (word)a;
	word wb = (word)b;
	word wc = (wa + wb) >> 1;
	return (uchar)wc;
}
extern dword KoishiImageTool::PNG::PNGcodeCRC(uchar *dest, longex len){
	dword crc_table[256];
	for(long n = 0;n<256;n++){
		dword c = (dword)n;
		for(long k = 0;k<8;k++){
			if(c & 1)
				c = 0xEDB88320L^(c >> 1);
			else
				c >>= 1;
		}
		crc_table[n] = c;
	}
	dword result = 0xFFFFFFFFL;
	for(long n = 0;n<len;n++){
		result = crc_table[(result^dest[n])&0xFF]^(result >> 8);
	}
	return result^0xFFFFFFFFL;
}
bool PNGobject::loadFile(str fileName){
	stream s;
	s.loadFile(fileName);
	return load(s);
}
bool PNGobject::load(const stream &s){
	data = stream(s);
	data.resetPosition();
	if(!data.read(&header, 8))
		return false;
	if(header.magic1 != 0x474E5089)
		return false;
	if(header.magic2 != 0x0A1A0A0D)
		return false;
	bool haveIHDR = false;
	bool haveIEND = false;
	bool haveIDAT = false;
	paletteColor.clear();
	paletteAlpha.clear();
	chunkList.clear();
	while(true){
		PNGblock pb;
		data.readDWord(pb.chunkDataSize);
		data.read(pb.chunkType, 4);
		pb.chunkDataSize = PNGdword(pb.chunkDataSize);
		pb.chunkType[4] = 0; 
		pb.chunkDataOffset = data.getPosition();
		data.movePosition(pb.chunkDataSize);
		data.readDWord(pb.chunkDataCRC);
		pb.chunkDataCRC = PNGdword(pb.chunkDataCRC);
		chunkList.push_back(pb);
		longex endPos = data.getPosition();
		if(str(pb.chunkType) == "IHDR" ){
			data.setPosition(pb.chunkDataOffset);
			data.read(&info, 13);
			info.width = PNGdword(info.width);
			info.height = PNGdword(info.height);
			haveIHDR = true;
		}
		if(str(pb.chunkType) == "PLTE" ){
			data.setPosition(pb.chunkDataOffset);
			for(long i = 0;i<pb.chunkDataSize / 3;i++){
				PNGcolor pc;
				data.read(&pc, 3);
				paletteColor.push_back(pc);
			}
		}
		if(str(pb.chunkType) == "tRNS" ){
			data.setPosition(pb.chunkDataOffset);
			for(long i = 0;i<pb.chunkDataSize;i++){
				PNGalpha pa;
				data.read(&pa, 1);
				paletteAlpha.push_back(pa);
			}
		}
		if(str(pb.chunkType) == "IDAT" ){
			haveIDAT = true;
		}
		if(str(pb.chunkType) == "IEND" ){
			haveIEND = true;
			break;
		}
		data.setPosition(endPos);
	}
	return haveIEND && haveIDAT && haveIHDR;
}
void PNGobject::make(stream &s){
	s = data;
}
void PNGobject::makeFile(str fileName){
	stream s;
	make(s);
	s.makeFile(fileName);
}
bool PNGobject::output(image &mat){
	stream sCompressed, sFiltered;
	sCompressed.allocate(info.width * info.height * 5);
	long bitPerPixel, bytePerPixel, bytePerLine;
	switch(info.colorType){
	case PNG_GRAY:
		bitPerPixel = info.depth;
		break;
	case PNG_TRUE:
		bitPerPixel = info.depth * 3;
		break;
	case PNG_INDEXED:
		bitPerPixel = info.depth;
		break;
	case PNG_AGRAY:
		bitPerPixel = info.depth * 2;
		break;
	case PNG_ATRUE:
		bitPerPixel = info.depth * 4;
		break;
	default:
		return false;
	}
	bytePerPixel = bitPerPixel / 8;	//小于8位无效
	bytePerLine = info.width * bitPerPixel / 8;
	for(long i = 0;i<chunkList.size();i++){
		if(str(chunkList[i].chunkType) != "IDAT")
			continue;
		stream sTemp;
		data.setPosition(chunkList[i].chunkDataOffset);
		data.readStream(sTemp, chunkList[i].chunkDataSize);
		sCompressed.pushStream(sTemp, sTemp.length);
	}
	mat.create(info.height, info.width);
	if(info.interlace == 0){
		//普通算法
		sCompressed.ZLIBuncompress(sFiltered, info.width * info.height * 5);
		stream sFilteredScanline, sScanline, sPriorScanline;
		sPriorScanline.allocate(bytePerLine);
		sScanline.allocate(bytePerLine);
		for(long h = 0;h<info.height;h++){
			if(h != 0)
				sPriorScanline = sScanline;
			sScanline.clear();
			sFiltered.readStream(sFilteredScanline, bytePerLine + 1);
			uchar filterType = sFilteredScanline[0];
			for(long j = 0;j<bytePerLine;j++){
				//去滤波
				uchar curByte = sFilteredScanline[1 + j], lByte, uByte, luByte;
				if(info.depth < 8){
					//位深度小于8取前一个字节
					lByte = (j != 0) ? sScanline[j-1] : 0;
					uByte = (h != 0) ? sPriorScanline[j] : 0;
					luByte = (h != 0 && j != 0) ? sPriorScanline[j-1]:0;
				}else{
					//位深度大于等于8取前一个像素中对应的字节
					lByte = (j >= bytePerPixel) ? sScanline[j-bytePerPixel] : 0;
					uByte = (h != 0) ? sPriorScanline[j] : 0;
					luByte = (h != 0 && j >= bytePerPixel) ? sPriorScanline[j-bytePerPixel]:0;
				}
				sScanline.pushByte(reconstruction(filterType, curByte, lByte, uByte, luByte));
			}
			//填充矩阵·处理单个像素
			for(int i = 0;i<info.width;i++){
				switch(info.colorType){
				case PNG_GRAY:
					//灰度，支持1，2，4，8，16位（1字节的8421和2字节），16位中的地位会被舍去
					if(info.depth <= 8){
						uchar colorID = sScanline.getBit(i, info.depth);
						mat[h][i] = color(colorID<<(8-info.depth), colorID<<(8-info.depth), colorID<<(8-info.depth));
					}else{
						mat[h][i] = color(sScanline[2*i], sScanline[2*i], sScanline[2*i]);
					}
					break;
				case PNG_AGRAY:
					//灰度A，支持8，16位（2、4字节)，但16位中低位会被舍去
					switch(info.depth){
					case 8:
						mat[h][i] = color(sScanline[2*i+1], sScanline[2*i], sScanline[2*i], sScanline[2*i]);
						break;
					case 16:
						mat[h][i] = color(sScanline[4*i+3], sScanline[4*i], sScanline[4*i], sScanline[4*i]);
						break;
					default:
						return false;
					}
					break;
				case PNG_INDEXED:
					//索引模式，支持1，2，4，8位（1字节8421)，必须有PLTE支持，有没有tRNS无所谓
					if(info.depth <= 8){
						uchar colorId = sScanline.getBit(i, info.depth);
						mat[h][i] = color(
							colorId < paletteAlpha.size() ? paletteAlpha[colorId] : 0xFF,
							colorId < paletteColor.size() ? paletteColor[colorId].R : 0,
							colorId < paletteColor.size() ? paletteColor[colorId].G : 0,
							colorId < paletteColor.size() ? paletteColor[colorId].B : 0
						);
					}else{
						return false;
					}
					break;
				case PNG_TRUE:
					//真彩，支持8，16位（3、6字节)，但16位中低位会被舍去
					switch(info.depth){
					case 8:
						mat[h][i] = color(sScanline[3*i], sScanline[3*i+1], sScanline[3*i+2]);
						break;
					case 16:
						mat[h][i] = color(sScanline[6*i], sScanline[6*i+2], sScanline[6*i+4]);
						break;
					default:
						return false;
					}
					break;
				case PNG_ATRUE:
					//真彩A，支持8，16位（4、8字节)，但16位中低位会被舍去
					switch(info.depth){
					case 8:
						mat[h][i] = color(sScanline[4*i+3], sScanline[4*i], sScanline[4*i+1], sScanline[4*i+2]);
						break;
					case 16:
						mat[h][i] = color(sScanline[8*i+6], sScanline[8*i], sScanline[8*i+2], sScanline[8*i+4]);
						break;
					default:
						return false;
					}
					break;
				default:
					return false;
				}
			}
		}
	}else{
		//Adam7隔行扫描算法
		stream sInterlaced;
		sCompressed.ZLIBuncompress(sInterlaced, info.width * info.height * 5);
		stream sFilteredScanline, sScanline, sPriorScanline;
		sPriorScanline.allocate(bytePerLine);
		sScanline.allocate(bytePerLine);
		long liXorigin[7] = {0, 4, 0, 2, 0, 1, 0};
		long liYorigin[7] = {0, 0, 4, 0, 2, 0, 1};
		long liXdelta[7] = {8, 8, 4, 4, 2, 2, 1};
		long liYdelta[7] = {8, 8, 8, 4, 4, 2, 2};
		long liWidth[7];
		long liHeight[7];
		liWidth[6] = info.width;
		liHeight[6] = info.height / 2;
		liWidth[5] = liWidth[6] / 2;
		liHeight[5] = info.height - liHeight[6];
		liWidth[4] = liWidth[6] - liWidth[5];
		liHeight[4] = liHeight[5] / 2;
		liWidth[3] = liWidth[4] / 2;
		liHeight[3] = liHeight[5]  - liHeight[4];
		liWidth[2] = liWidth[4] - liWidth[3];
		liHeight[2] = liHeight[3] / 2;
		liWidth[1] = liWidth[2] / 2;
		liHeight[1] = liHeight[3]  - liHeight[2];
		liWidth[0] = liWidth[2] - liWidth[1];
		liHeight[0] = liHeight[1];
		for(int sub = 0;sub<7;sub ++){
			if(liWidth[sub]*liHeight[sub] != 0){
				for(long h = 0;h<liHeight[sub];h++){
					if(h != 0)
						sPriorScanline = sScanline;
					sScanline.clear();
					bytePerLine = liWidth[sub] * bitPerPixel / 8;
					sInterlaced.readStream(sFilteredScanline, bytePerLine + 1);
					uchar filterType = sFilteredScanline[0];
					//去滤波
					for(long j = 0;j<bytePerLine;j++){
						uchar curByte = sFilteredScanline[1 + j], lByte, uByte, luByte;
						if(info.depth < 8){
							//位深度小于8取前一个字节
							lByte = (j != 0) ? sScanline[j-1] : 0;
							uByte = (h != 0) ? sPriorScanline[j] : 0;
							luByte = (h != 0 && j != 0) ? sPriorScanline[j-1]:0;
						}else{
							//位深度大于等于8取前一个像素中对应的字节
							lByte = (j >= bytePerPixel) ? sScanline[j-bytePerPixel] : 0;
							uByte = (h != 0) ? sPriorScanline[j] : 0;
							luByte = (h != 0 && j >= bytePerPixel) ? sPriorScanline[j-bytePerPixel]:0;
						}
						sScanline.pushByte(reconstruction(filterType, curByte, lByte, uByte, luByte));
					}
					sScanline;
					//填充矩阵·处理单个像素
					for(int i = 0;i<liWidth[sub];i++){
						switch(info.colorType){
						case PNG_GRAY:
							//灰度，支持1，2，4，8，16位（1字节的8421和2字节），16位中的地位会被舍去
							if(info.depth <= 8){
								uchar colorID = sScanline.getBit(i, info.depth);
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(colorID<<(8-info.depth), colorID<<(8-info.depth), colorID<<(8-info.depth));
							}else{
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(sScanline[2*i], sScanline[2*i], sScanline[2*i]);
							}
							break;
						case PNG_AGRAY:
							//灰度A，支持8，16位（2、4字节)，但16位中低位会被舍去
							switch(info.depth){
							case 8:
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(sScanline[2*i+1], sScanline[2*i], sScanline[2*i], sScanline[2*i]);
								break;
							case 16:
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(sScanline[4*i+3], sScanline[4*i], sScanline[4*i], sScanline[4*i]);
								break;
							default:
								return false;
							}
							break;
						case PNG_INDEXED:
							//索引模式，支持1，2，4，8位（1字节8421)，必须有PLTE支持，有没有tRNS无所谓
							if(info.depth <= 8){
								uchar colorId = sScanline.getBit(i, info.depth);
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(
									colorId < paletteAlpha.size() ? paletteAlpha[colorId] : 0xFF,
									colorId < paletteColor.size() ? paletteColor[colorId].R : 0,
									colorId < paletteColor.size() ? paletteColor[colorId].G : 0,
									colorId < paletteColor.size() ? paletteColor[colorId].B : 0
								);
							}else{
								return false;
							}
							break;
						case PNG_TRUE:
							//真彩，支持8，16位（3、6字节)，但16位中低位会被舍去
							switch(info.depth){
							case 8:
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(sScanline[3*i], sScanline[3*i+1], sScanline[3*i+2]);
								break;
							case 16:
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(sScanline[6*i], sScanline[6*i+2], sScanline[6*i+4]);
								break;
							default:
								return false;
							}
							break;
						case PNG_ATRUE:
							//真彩A，支持8，16位（4、8字节)，但16位中低位会被舍去
							switch(info.depth){
							case 8:
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(sScanline[4*i+3], sScanline[4*i], sScanline[4*i+1], sScanline[4*i+2]);
								break;
							case 16:
								mat[liYorigin[sub]+h*liYdelta[sub]][liXorigin[sub]+i*liXdelta[sub]] = color(sScanline[8*i+6], sScanline[8*i], sScanline[8*i+2], sScanline[8*i+4]);
								break;
							default:
								return false;
							}
							break;
						default:
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}
void PNGobject::input(const image &mat){
	stream sBlock, sCompressed, sOrigin, sScanline;
	header.magic1 = 0x474E5089;
	header.magic2 = 0x0A1A0A0D;
	info.colorType = PNG_ATRUE;
	info.compress = 0;
	info.depth = 8;
	info.filter = 0;
	info.height = mat.getHeight();
	info.width = mat.getWidth();
	info.interlace = 0;
	////////////////////////////////////////
	longex pt;
	data.release();
	data.allocate(100 + info.width * info.height * 5);
	data.pushDWord(header.magic1);
	data.pushDWord(header.magic2);
	////////////////////////////////////////
	//插入IHDR
	data.pushDWord(PNGdword(13));
	pt = data.length;
	data.pushString("IHDR");
	data.pushDWord(PNGdword(info.width));
	data.pushDWord(PNGdword(info.height));
	data.pushByte(info.depth);
	data.pushByte((uchar)info.colorType);
	data.pushByte(info.compress);
	data.pushByte(info.filter);
	data.pushByte(info.interlace);
	data.pushDWord(PNGdword(PNGcodeCRC((uchar*)data.begin() + pt, 17)));
	////////////////////////////////////////
	//插入tEXt
	data.pushDWord(PNGdword(44));
	pt = data.length;
	data.pushString("tEXt");
	data.pushString("Software");
	data.pushByte(0);
	data.pushString("Koishi's Extractor Blackcat Version");
	data.pushDWord(PNGdword(PNGcodeCRC((uchar*)data.begin() + pt, 48)));
	////////////////////////////////////////
	//插入图像数据
	//生成Origin和Compressed
	long bytePerLine = info.width * 4 + 1;
	sCompressed.allocate(info.width * info.height * 5);
	sOrigin.allocate(info.width * info.height * 5);
	sScanline.allocate(bytePerLine);
	for(long h = 0;h<info.height;h++){
		sScanline.clear();
		sScanline.pushByte(1);
		//插入元素
		for(long e = 0;e<info.width;e++){
			//RGBA的顺序
			if(e == 0){
				sScanline.pushByte(mat[h][e].R);
				sScanline.pushByte(mat[h][e].G);
				sScanline.pushByte(mat[h][e].B);
				sScanline.pushByte(mat[h][e].alpha);
			}else{
				sScanline.pushByte(mat[h][e].R - mat[h][e-1].R);
				sScanline.pushByte(mat[h][e].G - mat[h][e-1].G);
				sScanline.pushByte(mat[h][e].B - mat[h][e-1].B);
				sScanline.pushByte(mat[h][e].alpha - mat[h][e-1].alpha);
			}
		}
		sOrigin.pushStream(sScanline, bytePerLine);
	}
	sOrigin.ZLIBcompress(sCompressed);
	////////////////////////////////////////
	//分块
	longex blockSize = 4096;
	longex remainLen = sCompressed.length;
	while(remainLen > 0){
		if(remainLen <= blockSize){
			////////////////////////////////////////
			//插入IDAT
			data.pushDWord(PNGdword(remainLen));
			pt = data.length;
			data.pushString("IDAT");
			data.pushStream(sCompressed, remainLen);
			data.pushDWord(PNGdword(PNGcodeCRC((uchar*)data.begin() + pt, remainLen + 4)));
			break;
			////////////////////////////////////////
		}else{
			////////////////////////////////////////
			//插入IDAT
			data.pushDWord(PNGdword(blockSize));
			pt = data.length;
			data.pushString("IDAT");
			data.pushStream(sCompressed, blockSize);
			sCompressed.deleteStream(0, blockSize);
			data.pushDWord(PNGdword(PNGcodeCRC((uchar*)data.begin() + pt, blockSize+4)));
			remainLen = sCompressed.length;
			////////////////////////////////////////
		}
	}
	////////////////////////////////////////
	//插入IEND
	data.pushDWord(PNGdword(0));
	data.pushString("IEND");
	data.pushDWord(0x826042AE);
}
uchar PNGobject::filter(uchar filterType, uchar curByte, uchar lefByte, uchar upByte, uchar lefUpByte){
	switch(filterType){
	case 1:
		//前向减法
		return uchar(curByte - lefByte);
	case 2:
		//向上
		return uchar(curByte - upByte);
	case 3:
		//中值滤波
		return uchar(curByte - PNGaverage(lefByte, upByte));
	case 4:
		//线性滤波
		return uchar(curByte - PNGpaeth(lefByte, upByte, lefUpByte));
	default:
		return curByte;
	}
}
uchar PNGobject::reconstruction(uchar filterType, uchar curByte, uchar lefByte, uchar upByte, uchar lefUpByte){
	switch(filterType){
	case 1:
		//前向减法
		return uchar(curByte + lefByte);
	case 2:
		//向上
		return uchar(curByte + upByte);
	case 3:
		//中值滤波
		return uchar(curByte + PNGaverage(lefByte, upByte));
	case 4:
		//线性滤波
		return uchar(curByte + PNGpaeth(lefByte, upByte, lefUpByte));
	default:
		return curByte;
	}
}
//////////////////////////////////////////////////////////////////
void GIF::LZW::LZWinit(uchar LZWminCodeSize){
	if(LZWminCodeSize > 0){
		rootCount = 1 << LZWminCodeSize;		//根数
		minCodeSize = LZWminCodeSize;
		ID_CLEAR = rootCount;
		ID_EOF = rootCount + 1;
		ID_NOEXIST = 0xFFFF;
	}
	nodeCount = rootCount + 2;
	for(word i = 0;i<MAX_COUNT;i++){
		if(i<nodeCount){
			node[i].content = i;
			node[i].current = i;
			node[i].parent = ID_NOEXIST;
			node[i].firstChild = ID_NOEXIST;
			node[i].nextBrother = i+1;
		}else{
			node[i].content = 0;
			node[i].current = ID_NOEXIST;
			node[i].parent = ID_NOEXIST;
			node[i].firstChild = ID_NOEXIST;
			node[i].nextBrother = ID_NOEXIST;
		}
	}
}
void GIF::LZW::LZWadd(word parentID, uchar content){
	if(nodeCount >= MAX_COUNT)
		return;
	if(parentID >= nodeCount)
		return;
	node[nodeCount].content = content;
	node[nodeCount].current = nodeCount;
	node[nodeCount].firstChild = ID_NOEXIST;
	node[nodeCount].nextBrother = ID_NOEXIST;
	node[nodeCount].parent = parentID;
	if(node[node[nodeCount].parent].firstChild == ID_NOEXIST){
		//为继承方添加一个子节点
		node[node[nodeCount].parent].firstChild = nodeCount;
	}else{
		//为继承方的最后一个子节点添加一个旁节点
			word id = node[node[nodeCount].parent].firstChild;
			word lastBrother = id;
			while(id < nodeCount){
				lastBrother = id;
				id = node[id].nextBrother;
			}
			node[lastBrother].nextBrother = nodeCount;
		}
		nodeCount ++;
}
word GIF::LZW::LZWfind(const stream &s){
	longex pt = 0;
	word id = 0;
	while(pt<s.length){
		if(id >= nodeCount)
			return ID_NOEXIST;	//没找到
		if(node[id].content == s[pt]){
			pt ++;
			if(pt < s.length){
				id = node[id].firstChild;
			}else{
				return id;
			}
		}else{
			id = node[id].nextBrother;
		}
	}
	return id;
}
bool GIF::LZW::LZWget(word ID, stream &s){
	stream temp(2048);
	if(ID >= nodeCount)
		return false;
	while(ID != ID_NOEXIST){
		uchar content = node[ID].content;
		temp.pushByte(content);
		ID = node[ID].parent;
	}
	s.release();
	s.allocate(temp.length + 2048);
	for(longex i = 0;i<temp.length;i++){
		s.pushByte(temp[temp.length - 1 - i]);
	}
	return true;
}
int GIF::LZW::LZWgetBitLen(uchar cMinCodeSize, word cNodeCount){
	int p = cMinCodeSize;
	short baseCodeSize = 1 << cMinCodeSize;
	while(cNodeCount > baseCodeSize){
		p ++;
		baseCodeSize <<= 1;
	}
	if(p>12)
		p = 12;
	return p;
}

void GIF::LZW::compress(stream &in, stream &out, uchar LWZminCodeSize, bool elongated){
	if(in.length == 0)
		return;
	out.release();
	out.allocate(2*in.length + 100);
	out.bitResetPosition();
	in.resetPosition();
	longex bitPos = 0;				//out内的pos的位置
	longex pos = 0;					//in内的pos的位置
	stream prefix;
	uchar suffix;
	LZWinit(LWZminCodeSize);
	int bitLen = LZWgetBitLen(minCodeSize, nodeCount);	//当前每个编码
	prefix.allocate(2048);
	while(true){
		if(in.getPosition() == 0){						
			//第一步·写入一个ID_CLEAR
			out.bitPush(ID_CLEAR, elongated ? bitLen : 16);
			in.readByte(suffix);
			prefix.clear();
			prefix.pushByte(suffix);
		}else if(in.getPosition() < in.length){
			word prefixID = LZWfind(prefix);	//这步肯定能找到
			in.readByte(suffix);
			prefix.pushByte(suffix);
			word findID = LZWfind(prefix);
			if(ID_NOEXIST == findID){
				//未命中，输出前缀输出码，扩充辞典，前置要重置为当前的后缀
				bitLen = LZWgetBitLen(minCodeSize, nodeCount);	//重新确定编码长度
				out.bitPush(prefixID, elongated ? bitLen : 16);
				prefix.clear();
				prefix.pushByte(suffix);
				LZWadd(prefixID, suffix);
				if(nodeCount > MAX_COUNT){
					//辞典满了要重置，先写入一个ID_CLEAR
					out.bitPush(ID_CLEAR, elongated ? bitLen : 16);
					LZWinit();
				}
				
			}
		}else{
			word prefixID = LZWfind(prefix);
			out.bitPush(prefixID, elongated ? bitLen : 16);
			out.bitPush(ID_EOF, elongated ? bitLen : 16);
			break;
		}
	}
}
bool GIF::LZW::uncompress(stream &in, stream &out, uchar LWZminCodeSize, bool elongated){
	if(in.length == 0)
		return false;
	LZWinit(LWZminCodeSize);
	out.allocate(65536);
	stream previousStr;
	stream currentStr;
	word previousID = 0xFFFF;
	word currentID = 0xFFFF;
	in.bitResetPosition();
	out.resetPosition();
	int bitLen = LZWgetBitLen(minCodeSize, nodeCount);
	previousStr.allocate(2048);
	currentStr.allocate(2048);
	while(in.bitGetPosition() <= 8 * in.length){
		previousID = currentID;
		bitLen = LZWgetBitLen(minCodeSize, nodeCount+1);	//重新确定编码长度，因为解压是要预知的，所以要以nodeCount+1检测
		currentID = 0;
		in.bitRead(&currentID, elongated ? bitLen : 16);
		if(currentID == ID_EOF)
			return true;
		if(currentID == ID_CLEAR){
			LZWinit();
			previousID = 0xFFFF;
			currentID = 0xFFFF;
			continue;
		}
		LZWget(previousID, previousStr);
		if(currentID < nodeCount){
			//能查到
			LZWget(currentID, currentStr);
			out.pushStream(currentStr, currentStr.length);
			LZWadd(previousID, currentStr[0]);
		}else{
			//查不到
			previousStr.pushByte(previousStr[0]);
			out.pushStream(previousStr, previousStr.length);
			LZWadd(previousID, previousStr[0]);
		}
	}
	//没查到EOF，直接查到结束
	return false;
}
//////////////////////////////////////////////////////////////////
bool GIF::GIFobject::load(stream &s){
	frame.clear();
	expand.clear();
	appData.clear();
	controller.clear();
	s.resetPosition();
	//读取头
	uchar fieldChar;
	uchar version[7];
	s.read(version, 6);
	version[6] = 0;
	info.version = str((char*)version);
	s.readWord(info.width);
	s.readWord(info.height);
	s.readByte(fieldChar);
	info.globalColorCount = 2 << (fieldChar & 0x07);
	info.globalColorSort = (fieldChar & 0x08) == 0x08;
	info.globalColorDepth = 1 + ((fieldChar & 0x70) >> 4);
	info.globalColorValid = (fieldChar & 0x80) == 0x80;
	s.readByte(info.bkColorID);
	s.readByte(info.aspectRatio);
	info.globalPalette.clear();
	if(info.globalColorValid){
		for(int i = 0;i<info.globalColorCount;i++){
			color cl;
			cl.alpha = 0xFF;
			s.readByte(cl.R);
			s.readByte(cl.G);
			s.readByte(cl.B);
			info.globalPalette.push_back(cl);
		}
	}
	uchar flag;
	while(true){
		if(!s.readByte(flag))
			return false;
		switch(flag){
		case ',':
			{
				GIFimage gi;
				s.readWord(gi.xOffset);
				s.readWord(gi.yOffset);
				s.readWord(gi.width);
				s.readWord(gi.height);
				gi.dataDisposed.allocate(gi.width * gi.height * info.globalColorDepth);
				s.readByte(fieldChar);
				gi.localColorCount = 2 <<(fieldChar & 0x07);
				gi.localColorSort = (fieldChar & 0x20) == 0x20;
				gi.localInterlace = (fieldChar & 0x40) == 0x40;
				gi.localColorValid = (fieldChar & 0x80) == 0x80;
				gi.localPalette.clear();
				if(gi.localColorValid){
					for(int i = 0;i<gi.localColorCount;i++){
						color cl;
						cl.alpha = 0xFF;
						s.readByte(cl.R);
						s.readByte(cl.G);
						s.readByte(cl.B);
						gi.localPalette.push_back(cl);
					}
				}
				s.readByte(gi.LZWminCodeSize);
				while(true){
					uchar len;
					s.readByte(len);
					if(len == 0){
						break;
					}
					stream originStream;
					s.readStream(originStream, len);
					gi.dataDisposed.pushStream(originStream, len);
				}
				frame.push_back(gi);
			}
			break;
		case '!':
			{
				GIFexpand ge;
				s.read(&ge.type, 1);
				while(true){
					uchar len;
					s.readByte(len);
					if(len == 0){
						break;
					}
					stream originStream;
					s.readStream(originStream, len);
					ge.dataDisposed.pushStream(originStream, len);
				}
				expand.push_back(ge);
				if(ge.type == GIFET_CONTROL && ge.dataDisposed.length >= 4){
					GIFcontrol gc;
					fieldChar = ge.dataDisposed[0];
					gc.alphaValid = (fieldChar & 0x01) == 0x01;
					gc.userInputValid = (fieldChar & 0x02) == 0x2;
					gc.dealMethod = (fieldChar & 0x1C) >> 2;
					gc.delayTime = 10*(ge.dataDisposed[1] | ge.dataDisposed[2] << 8);
					gc.alphaIndex = ge.dataDisposed[3];
					controller.push_back(gc);
				}
				if(ge.type == GIFET_APPLICATION && ge.dataDisposed.length >= 11){
					GIFappData ga;
					ge.dataDisposed.resetPosition();
					ge.dataDisposed.read(ga.appName, 8);
					ga.appName[8] = 0;
					ge.dataDisposed.read(ga.appVer, 3);
					ga.appVer[3] = 0;
					if(ge.dataDisposed.length > 11){
						ge.dataDisposed.readStream(ga.appData, ge.dataDisposed.length - 11);	
					}
					appData.push_back(ga);
				}
			}
			break;
		case ';':
			{
			 }
			return true;
		default:
			return false;
		}
	}
}
bool GIF::GIFobject::loadFile(const str &fileName){
	stream s;
	s.loadFile(fileName);
	return load(s);
}
bool GIF::GIFobject::output(image &mat, int frameID){
	LZW l;
	if(frame.size() <= frameID)
		return false;
	stream out;
	l.uncompress(frame[frameID].dataDisposed, out, frame[frameID].LZWminCodeSize);
	mat.create(frame[frameID].height, frame[frameID].width);
	colorList cl;
	color bkColor;
	if(frame[frameID].localColorValid){
		cl = frame[frameID].localPalette;
		bkColor = color(0xFF,0xFF,0xFF);
	}else if(info.globalColorValid){
		cl = info.globalPalette;
		bkColor = cl[info.bkColorID];
	}else{
		return false;
	}
	if(frameID < controller.size() && controller[frameID].alphaValid){
		cl[controller[frameID].alphaIndex].alpha = 0;
	}
	for(int i = 0;i<mat.getElemCount();i++){
		if(i < out.length){
			mat.setElem(i, cl[out[i]]);
		}
	}
	return true;
}
void GIF::GIFobject::input(const image &mat){
	//提取调色板
	palette pal;			//寻找用的调色板
	colorList clrList;		//颜色列表
	queue clrCount;			//颜色个数
	pal.push(clrList);
	for(int i = 0;i<mat.getElemCount();i++){
		color clr = mat.getElem(i);
		clr.alpha = 0xFF;
		long clrPos = pal.findColor(clr,0);
		if(clrPos == -1){
			pal[0].push_back(clr);
			clrCount.push_back(1);
		}else{
			clrCount[clrPos] ++;
		}
	}
	clrList = pal[0];
	uchar finalColorCount = MIN(0xFE, pal.getColorCount(0));
	colorList finalColorList;
	for(int i = 0;i<finalColorCount; i++){
		long maxCount = 0;
		long maxID = -1;
		for(int j = 0;j<clrCount.size();j++){
			if(clrCount[j] > maxCount){
				maxCount =clrCount[j];
				maxID = j;
			}
		}
		finalColorList.push_back(clrList[maxID]);
		clrList.erase(clrList.begin() + maxID);
		clrCount.erase(clrCount.begin() + maxID);
	}
	finalColorList = KoishiImageTool::nearbySort(finalColorList);
	finalColorList.insert(finalColorList.begin(), color(0,0,0,0));
	input(mat, finalColorList);
	////////////////////////////////////
	appData.clear();
	GIFappData ga;
	char an[9] = "KoishiEx";
	memcpy(ga.appName, an, 9);
	char av[4] = "CAT";
	memcpy(ga.appVer, av, 4);
	ga.appData.allocate(5);
	ga.appData.pushDWord(1);
	ga.appData.pushByte(0);
	appData.push_back(ga);
}
void GIF::GIFobject::input(const image &mat, const colorList &usePalette){
	//更新头
	info.version = "GIF89a";
	info.globalColorValid = true;
	info.globalColorSort = false;
	info.globalColorDepth = 8;
	info.globalColorCount = 256;
	info.aspectRatio = 0;
	info.bkColorID = 0;
	info.globalPalette.clear();
	info.height = mat.getHeight();
	info.width = mat.getWidth();
	for(int i = 0;i<256;i++){
		if(i<usePalette.size()){
			info.globalPalette.push_back(usePalette[i]);
		}else{
			info.globalPalette.push_back(color(0));
		}
	}
	//更新这个帧的控制域
	controller.clear();
	GIFcontrol gc;
	gc.alphaIndex = 0xFF;
	for(int i = 0;i<usePalette.size();i++){
		if(usePalette[i].alpha == 0){
			gc.alphaIndex = i;
		}
	}
	if(gc.alphaIndex == 0xFF){
		gc.alphaIndex = 0;
		gc.alphaValid = false;
	}else{
		gc.alphaValid = true;
	}
	gc.dealMethod = 2;
	gc.delayTime = 100;
	gc.userInputValid = false;
	controller.push_back(gc);
	//更新这个帧的应用域
	appData.clear();
	GIFappData ga;
	char an[9] = "KoishiEx";
	memcpy(ga.appName, an, 8);
	char av[4] = "CAT";
	memcpy(ga.appVer, av, 3);
	ga.appData.allocate(5);
	ga.appData.pushDWord(2);
	ga.appData.pushByte(0);
	appData.push_back(ga);
	//更新这个帧的图像域
	frame.clear();
	GIFimage gi;
	gi.xOffset = 0;
	gi.yOffset = 0;
	gi.height = info.height;
	gi.width = info.width;
	gi.localColorCount = 0;
	gi.localColorSort = false;
	gi.localColorValid = false;
	gi.localInterlace = false;
	gi.localPalette.clear();
	gi.LZWminCodeSize = 8;
	stream rawData(1000 + gi.height * gi.width);
	palette pl;
	pl.push(usePalette);
	for(int i = 0;i<gi.height * gi.width;i++){
		uchar id = pl.matchColor(mat.getElem(i));
		rawData.pushByte(id);
	}
	LZW l;
	l.compress(rawData, gi.dataDisposed, gi.LZWminCodeSize);
	frame.push_back(gi);
}
void GIF::GIFobject::input(const std::vector<image> &matList, int delayTime){
	//尝试生成多帧的图像
	if(matList.size() == 0)
		return;
	info.version = "GIF89a";
	info.globalColorValid = false;
	info.globalColorSort = false;
	info.globalColorDepth = 0;
	info.globalColorCount = 0;
	info.aspectRatio = 0;
	info.bkColorID = 0;
	info.globalPalette.clear();
	info.height = matList[0].getHeight();
	info.width = matList[0].getWidth();
	//更新这个帧的控制域
	controller.clear();
	appData.clear();
	frame.clear();
	for(int id = 0;id<matList.size();id ++){
		GIFcontrol gc;
		gc.alphaIndex = 0;
		gc.alphaValid = true;
		gc.dealMethod = 2;
		gc.delayTime = delayTime;
		gc.userInputValid = false;
		controller.push_back(gc);
		if(id == 0){
			GIFappData ga;
			char an[9] = "NETSCAPE";
			memcpy(ga.appName, an, 9);
			char av[4] = "2.0";
			memcpy(ga.appVer, av, 4);
			ga.appData.allocate(3);
			ga.appData.pushWord(1);
			ga.appData.pushByte(0);
			appData.push_back(ga);
		}
		//更新这个帧的应用域
		GIFappData ga;
		char an[9] = "KoishiEx";
		memcpy(ga.appName, an, 9);
		char av[4] = "CAT";
		memcpy(ga.appVer, av, 4);
		ga.appData.allocate(5);
		ga.appData.pushDWord(3);
		ga.appData.pushByte(0);
		appData.push_back(ga);
		//更新这个帧的图像域
		GIFimage gi;
		gi.xOffset = 0;
		gi.yOffset = 0;
		gi.height = info.height;
		gi.width = info.width;
		gi.localColorCount = 256;
		gi.localColorSort = false;
		gi.localColorValid = true;
		gi.localInterlace = false;
		gi.localPalette.clear();
		//重新生成localPalette
		palette pal;			//寻找用的调色板
		colorList clrList;		//颜色列表
		queue clrCount;			//颜色个数
		pal.push(clrList);
		for(int i = 0;i<matList[id].getElemCount();i++){
			color clr = matList[id].getElem(i);
			clr.alpha = 0xFF;
			long clrPos = pal.findColor(clr,0);
			if(clrPos == -1){
				pal[0].push_back(clr);
				clrCount.push_back(1);
			}else{
				clrCount[clrPos] ++;
			}
		}
		clrList = pal[0];
		uchar finalColorCount = MIN(0xFE, pal.getColorCount(0));
		colorList finalColorList;
		for(int i = 0;i<finalColorCount; i++){
			long maxCount = 0;
			long maxID = -1;
			for(int j = 0;j<clrCount.size();j++){
				if(clrCount[j] > maxCount){
					maxCount =clrCount[j];
					maxID = j;
				}
			}
			finalColorList.push_back(clrList[maxID]);
			clrList.erase(clrList.begin() + maxID);
			clrCount.erase(clrCount.begin() + maxID);
		}
		finalColorList = KoishiImageTool::nearbySort(finalColorList);
		finalColorList.insert(finalColorList.begin(), color(0,0,0,0));
		for(int i = 0;i<256;i++){
			if(i<finalColorList.size()){
				gi.localPalette.push_back(finalColorList[i]);
			}else{
				gi.localPalette.push_back(color(0,0,0,0));
			}
		}
		//生成图像数据
		gi.LZWminCodeSize = 8;
		stream rawData(1000 + gi.height * gi.width);
		palette pl;
		pl.push(finalColorList);
		for(int i = 0;i<gi.height * gi.width;i++){
			uchar idx = pl.matchColor(matList[id].getElem(i));
			rawData.pushByte(idx);
		}
		LZW l;
		l.compress(rawData, gi.dataDisposed, gi.LZWminCodeSize);
		frame.push_back(gi);
	}
}
void GIF::GIFobject::input(const std::vector<image> &matList, int delayTime, const str &imgPath, const std::vector<int> &frameID){
	//更新头
	if(matList.size() == 0)
		return;
	info.version = "GIF89a";
	info.globalColorValid = false;
	info.globalColorSort = false;
	info.globalColorDepth = 0;
	info.globalColorCount = 0;
	info.aspectRatio = 0;
	info.bkColorID = 0;
	info.globalPalette.clear();
	info.height = matList[0].getHeight();
	info.width = matList[0].getWidth();
	//更新这个帧的控制域
	controller.clear();
	appData.clear();
	frame.clear();
	for(int id = 0;id<matList.size();id ++){
		GIFcontrol gc;
		gc.alphaIndex = 0;
		gc.alphaValid = true;
		gc.dealMethod = 2;
		gc.delayTime = delayTime;
		gc.userInputValid = false;
		controller.push_back(gc);
		if(id == 0){
			GIFappData ga;
			char an[9] = "NETSCAPE";
			memcpy(ga.appName, an, 9);
			char av[4] = "2.0";
			memcpy(ga.appVer, av, 4);
			ga.appData.allocate(3);
			ga.appData.pushWord(1);
			ga.appData.pushByte(0);
			appData.push_back(ga);
		}
		//更新这个帧的应用域
		GIFappData ga;
		char an[9] = "KoishiEx";
		memcpy(ga.appName, an, 9);
		char av[4] = "CAT";
		memcpy(ga.appVer, av, 4);
		ga.appData.allocate(512);
		ga.appData.pushDWord(4);
		if(id < imgPath.size() && id < frameID.size()){
			ga.appData.pushDWord(imgPath.size());
			ga.appData.pushString(imgPath);
			ga.appData.pushDWord(frameID[id]);
		}
		ga.appData.pushByte(0);
		appData.push_back(ga);
		//更新这个帧的图像域
		GIFimage gi;
		gi.xOffset = 0;
		gi.yOffset = 0;
		gi.height = info.height;
		gi.width = info.width;
		gi.localColorCount = 256;
		gi.localColorSort = false;
		gi.localColorValid = true;
		gi.localInterlace = false;
		gi.localPalette.clear();
		//重新生成localPalette
		palette pal;			//寻找用的调色板
		colorList clrList;		//颜色列表
		queue clrCount;			//颜色个数
		pal.push(clrList);
		for(int i = 0;i<matList[id].getElemCount();i++){
			color clr = matList[id].getElem(i);
			clr.alpha = 0xFF;
			long clrPos = pal.findColor(clr,0);
			if(clrPos == -1){
				pal[0].push_back(clr);
				clrCount.push_back(1);
			}else{
				clrCount[clrPos] ++;
			}
		}
		clrList = pal[0];
		uchar finalColorCount = MIN(0xFE, pal.getColorCount(0));
		colorList finalColorList;
		for(int i = 0;i<finalColorCount; i++){
			long maxCount = 0;
			long maxID = -1;
			for(int j = 0;j<clrCount.size();j++){
				if(clrCount[j] > maxCount){
					maxCount =clrCount[j];
					maxID = j;
				}
			}
			finalColorList.push_back(clrList[maxID]);
			clrList.erase(clrList.begin() + maxID);
			clrCount.erase(clrCount.begin() + maxID);
		}
		finalColorList = KoishiImageTool::nearbySort(finalColorList);
		finalColorList.insert(finalColorList.begin(), color(0,0,0,0));
		for(int i = 0;i<256;i++){
			if(i<finalColorList.size()){
				gi.localPalette.push_back(finalColorList[i]);
			}else{
				gi.localPalette.push_back(color(0,0,0,0));
			}
		}
		//生成图像数据
		gi.LZWminCodeSize = 8;
		stream rawData(1000 + gi.height * gi.width);
		palette pl;
		pl.push(finalColorList);
		for(int i = 0;i<gi.height * gi.width;i++){
			uchar idx = pl.matchColor(matList[id].getElem(i));
			rawData.pushByte(idx);
		}
		LZW l;
		l.compress(rawData, gi.dataDisposed, gi.LZWminCodeSize);
		frame.push_back(gi);
	}
}
void GIF::GIFobject::input(const std::vector<image> &matList, const colorList &usePalette, int delayTime){
	//更新头
	if(matList.size() == 0)
		return;
	info.version = "GIF89a";
	info.globalColorValid = true;
	info.globalColorSort = false;
	info.globalColorDepth = 8;
	info.globalColorCount = 256;
	info.aspectRatio = 0;
	info.bkColorID = 0;
	info.globalPalette.clear();
	info.height = matList[0].getHeight();
	info.width = matList[0].getWidth();
	for(int i = 0;i<256;i++){
		if(i<usePalette.size()){
			info.globalPalette.push_back(usePalette[i]);
		}else{
			info.globalPalette.push_back(color(0));
		}
	}
	//更新这个帧的控制域
	controller.clear();
	appData.clear();
	frame.clear();
	for(int id = 0;id<matList.size();id ++){
		GIFcontrol gc;
		gc.alphaIndex = 0xFF;
		for(int i = 0;i<usePalette.size();i++){
			if(usePalette[i].alpha == 0){
				gc.alphaIndex = i;
			}
		}
		if(gc.alphaIndex == 0xFF){
			gc.alphaIndex = 0;
			gc.alphaValid = false;
		}else{
			gc.alphaValid = true;
		}
		gc.dealMethod = 2;
		gc.delayTime = delayTime;
		gc.userInputValid = false;
		controller.push_back(gc);
		if(id == 0){
			GIFappData ga;
			char an[9] = "NETSCAPE";
			memcpy(ga.appName, an, 9);
			char av[4] = "2.0";
			memcpy(ga.appVer, av, 4);
			ga.appData.allocate(3);
			ga.appData.pushWord(1);
			ga.appData.pushByte(0);
			appData.push_back(ga);
		}
		//更新这个帧的应用域
	
		GIFappData ga;
		char an[9] = "KoishiEx";
		memcpy(ga.appName, an, 9);
		char av[4] = "CAT";
		memcpy(ga.appVer, av, 4);
		ga.appData.allocate(5);
		ga.appData.pushDWord(4);
		ga.appData.pushByte(0);
		appData.push_back(ga);
		//更新这个帧的图像域
	
		GIFimage gi;
		gi.xOffset = 0;
		gi.yOffset = 0;
		gi.height = info.height;
		gi.width = info.width;
		gi.localColorCount = 0;
		gi.localColorSort = false;
		gi.localColorValid = false;
		gi.localInterlace = false;
		gi.localPalette.clear();
		gi.LZWminCodeSize = 8;
		stream rawData(1000 + gi.height * gi.width);
		palette pl;
		pl.push(usePalette);
		for(int i = 0;i<gi.height * gi.width;i++){
			uchar idx = pl.matchColor(matList[id].getElem(i));
			rawData.pushByte(idx);
		}
		LZW l;
		l.compress(rawData, gi.dataDisposed, gi.LZWminCodeSize);
		frame.push_back(gi);
	}
}
void GIF::GIFobject::input(const std::vector<image> &matList, const colorList &usePalette, int delayTime, const str &imgPath, const std::vector<int> &frameID){
	//更新头
	if(matList.size() == 0)
		return;
	info.version = "GIF89a";
	info.globalColorValid = true;
	info.globalColorSort = false;
	info.globalColorDepth = 8;
	info.globalColorCount = 256;
	info.aspectRatio = 0;
	info.bkColorID = 0;
	info.globalPalette.clear();
	info.height = matList[0].getHeight();
	info.width = matList[0].getWidth();
	for(int i = 0;i<256;i++){
		if(i<usePalette.size()){
			info.globalPalette.push_back(usePalette[i]);
		}else{
			info.globalPalette.push_back(color(0));
		}
	}
	//更新这个帧的控制域
	controller.clear();
	appData.clear();
	frame.clear();
	for(int id = 0;id<matList.size();id ++){
		GIFcontrol gc;
		gc.alphaIndex = 0xFF;
		for(int i = 0;i<usePalette.size();i++){
			if(usePalette[i].alpha == 0){
				gc.alphaIndex = i;
			}
		}
		if(gc.alphaIndex == 0xFF){
			gc.alphaIndex = 0;
			gc.alphaValid = false;
		}else{
			gc.alphaValid = true;
		}
		gc.dealMethod = 2;
		gc.delayTime = delayTime;
		gc.userInputValid = false;
		controller.push_back(gc);
		if(id == 0){
			GIFappData ga;
			char an[9] = "NETSCAPE";
			memcpy(ga.appName, an, 9);
			char av[4] = "2.0";
			memcpy(ga.appVer, av, 4);
			ga.appData.allocate(3);
			ga.appData.pushWord(1);
			ga.appData.pushByte(0);
			appData.push_back(ga);
		}
		//更新这个帧的应用域
	
		GIFappData ga;
		char an[9] = "KoishiEx";
		memcpy(ga.appName, an, 9);
		char av[4] = "CAT";
		memcpy(ga.appVer, av, 4);
		ga.appData.allocate(512);
		ga.appData.pushDWord(4);
		if(id < imgPath.size() && id < frameID.size()){
			ga.appData.pushDWord(imgPath.size());
			ga.appData.pushString(imgPath);
			ga.appData.pushDWord(frameID[id]);
		}
		ga.appData.pushByte(0);
		appData.push_back(ga);
		//更新这个帧的图像域
	
		GIFimage gi;
		gi.xOffset = 0;
		gi.yOffset = 0;
		gi.height = info.height;
		gi.width = info.width;
		gi.localColorCount = 0;
		gi.localColorSort = false;
		gi.localColorValid = false;
		gi.localInterlace = false;
		gi.localPalette.clear();
		gi.LZWminCodeSize = 8;
		stream rawData(1000 + gi.height * gi.width);
		palette pl;
		pl.push(usePalette);
		for(int i = 0;i<gi.height * gi.width;i++){
			uchar idx = pl.matchColor(matList[id].getElem(i));
			rawData.pushByte(idx);
		}
		LZW l;
		l.compress(rawData, gi.dataDisposed, gi.LZWminCodeSize);
		frame.push_back(gi);
	}
}
void GIF::GIFobject::make(stream &s){
	longex estimateLen = 13;	//估算所需空间
	estimateLen += 1000;		//给全局调色板留的空间
	estimateLen += frame.size() * (1000 + info.height * info.width);		//给图像数据留的空间
	estimateLen += controller.size() * 20;				//给控制数据留的空间
	estimateLen += appData.size() * 1000;				//给应用数据留的空间，这些足够了
	s.allocate(estimateLen);
	s.pushString(info.version);
	s.pushWord(info.width);
	s.pushWord(info.height);
	uchar fieldChar = 0;
	if(info.globalColorValid){
		fieldChar |= 0x80;
		fieldChar |= (info.globalColorDepth - 1) << 4;
		if(info.globalColorSort)
			fieldChar |= 0x8;
		if(info.globalColorCount > 128){
			fieldChar |= 0x7;
		}else if(info.globalColorCount > 64){
			fieldChar |= 0x6;
		}else if(info.globalColorCount > 32){
			fieldChar |= 0x5;
		}else if(info.globalColorCount > 16){
			fieldChar |= 0x4;
		}else if(info.globalColorCount > 8){
			fieldChar |= 0x3;
		}else if(info.globalColorCount > 4){
			fieldChar |= 0x2;
		}else if(info.globalColorCount > 2){
			fieldChar |= 0x1;
		}
	}
	s.pushByte(fieldChar);
	s.pushByte(info.bkColorID);
	s.pushByte(info.aspectRatio);
	if(info.globalColorValid){
		for(int i = 0;i<info.globalColorCount;i++){
			s.pushByte(info.globalPalette[i].R);
			s.pushByte(info.globalPalette[i].G);
			s.pushByte(info.globalPalette[i].B);
		}
	}
	//插入各块：按照控制块，NET应用块（如果单帧则无此块），KOISHIEX应用块，图像块顺序插入
	for(int id = 0;id < frame.size(); id++){
		//插入控制块
		s.pushByte('!');
		s.pushByte(GIFET_CONTROL);
		s.pushByte(4);
		fieldChar = 0;
		if(controller[id].alphaValid)
			fieldChar |= 1;
		if(controller[id].userInputValid)
			fieldChar |= 2;
		fieldChar |= (controller[id].dealMethod << 2);
		s.pushByte(fieldChar);
		s.pushWord((word)(controller[id].delayTime / 10));
		s.pushByte(controller[id].alphaIndex);
		s.pushByte(0);
		//插入NET应用快
		if(appData.size() > 0 && frame.size() > 1 && id == 0){
			s.pushByte('!');
			s.pushByte(GIFET_APPLICATION);
			s.pushByte(11);
			s.pushString(str(appData[0].appName));
			s.pushString(str(appData[0].appVer));
			s.pushByte(appData[0].appData.length);
			s.pushStream(appData[0].appData, appData[0].appData.length);
			s.pushByte(0);
		}
		//插入KOISHI应用块
		int appId = (frame.size() == 1) ? id :(id + 1);
		if(appId < appData.size()){
			s.pushByte('!');
			s.pushByte(GIFET_APPLICATION);
			s.pushByte(11);
			s.pushString(str(appData[appId].appName));
			s.pushString(str(appData[appId].appVer));
			//剩下的分块写
			int restLen = appData[appId].appData.length;
			int pos = 0;
			while(true){
				if(restLen > 0xFE){
					s.pushByte(0xFE);
					for(int i = 0;i<0xFE;i++){
						s.pushByte(appData[appId].appData[pos+i]);
					}
					pos += 0xFE;
					restLen -= 0xFE;
				}else{
					s.pushByte(restLen);
					for(int i = 0;i<restLen;i++){
						s.pushByte(appData[appId].appData[pos+i]);
					}
					break;
				}
			}
			s.pushByte(0);
		}
		//插入图像块
		s.pushByte(',');
		s.pushWord(frame[id].xOffset);
		s.pushWord(frame[id].yOffset);
		s.pushWord(frame[id].width);
		s.pushWord(frame[id].height);
		fieldChar = 0;
		if(frame[id].localColorValid){
			fieldChar |= 0x80;
			if(frame[id].localInterlace)
				fieldChar |= 0x40;
			if(frame[id].localColorSort)
				fieldChar |= 0x20;
			if(frame[id].localColorCount > 128){
				fieldChar |= 0x7;
			}else if(frame[id].localColorCount > 64){
				fieldChar |= 0x6;
			}else if(frame[id].localColorCount > 32){
				fieldChar |= 0x5;
			}else if(frame[id].localColorCount > 16){
				fieldChar |= 0x4;
			}else if(frame[id].localColorCount > 8){
				fieldChar |= 0x3;
			}else if(frame[id].localColorCount > 4){
				fieldChar |= 0x2;
			}else if(frame[id].localColorCount > 2){
				fieldChar |= 0x1;
			}
		}
		s.pushByte(fieldChar);
		if(frame[id].localColorValid){
			for(int i = 0;i<frame[id].localColorCount;i++){
				s.pushByte(frame[id].localPalette[i].R);
				s.pushByte(frame[id].localPalette[i].G);
				s.pushByte(frame[id].localPalette[i].B);
			}
		}
		s.pushByte(frame[id].LZWminCodeSize);
		//剩下的分块写
		int restLen = frame[id].dataDisposed.length;
		int pos = 0;
		while(true){
			if(restLen > 0xFE){
				s.pushByte(0xFE);
				for(int i = 0;i<0xFE;i++){
					s.pushByte(frame[id].dataDisposed[pos+i]);
				}
				pos += 0xFE;
				restLen -= 0xFE;
			}else{
				s.pushByte(restLen);
				for(int i = 0;i<restLen;i++){
					s.pushByte(frame[id].dataDisposed[pos+i]);
				}
				break;
			}
		}
		s.pushByte(0);
	}
	s.pushByte(';');
}
void GIF::GIFobject::makeFile(const str &fileName){
	stream s;
	make(s);
	s.makeFile(fileName);
}
//////////////////////////////////////////////////////////////////
DDSobject::DDSobject(void){
}
DDSobject::DDSobject(const stream &s){
	load(s);
}
DDSobject::DDSobject(const str &DDSfileName){
	loadFile(DDSfileName);
}
DDSobject::~DDSobject(void){
	data.release();
}
DDSHeader *DDSobject::getHeader(){
	return &header;
}
bool DDSobject::load(const stream &s){
	stream _s(s);
	bool b = true;
	dword _v;
	long i;
	_s.readDWord(_v);
	header.magic = _v;
	if(_v != 0x20534444)
		return false;
	_s.readDWord(_v);
	header.headSize	= _v;
	if(_v != 0x7C)
		return false;
	_s.readDWord(_v);
	header.flags = _v;
	if(_v != 0x81007){
	//	b = false;
	}
	_s.readDWord(_v);
	header.height = _v;
	_s.readDWord(_v);
	header.width = _v;
	_s.readDWord(_v);
	header.pitchOrLinearSize = _v;
	_s.readDWord(_v);
	header.depth = _v;
	_s.readDWord(_v);
	header.mipMapCount = _v;
	for(i=0;i<11;i++){
		_s.readDWord(_v);
		header.reserved1[i] = _v;
	}
	_s.readDWord(_v);
	header.pixelFormat.size = _v;
	_s.readDWord(_v);
	header.pixelFormat.flags = _v;
	_s.readDWord(_v);
	header.pixelFormat.fourCC = _v;
	_s.readDWord(_v);
	header.pixelFormat.rgbBitCount = _v;
	_s.readDWord(_v);
	header.pixelFormat.rBitMask = _v;
	_s.readDWord(_v);
	header.pixelFormat.gBitMask = _v;
	_s.readDWord(_v);
	header.pixelFormat.bBitMask = _v;
	_s.readDWord(_v);
	header.pixelFormat.aBitMask = _v;
	_s.readDWord(_v);
	header.caps1 = _v;
	_s.readDWord(_v);
	header.caps2 = _v;
	_s.readDWord(_v);
	header.caps3 = _v;
	_s.readDWord(_v);
	header.caps4 = _v;
	_s.readDWord(_v);
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
bool DDSobject::loadFile(const str &DDSfileName){
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
bool DDSobject::make(stream &s){
	s.allocate(128+data.length+2000);

	s.pushDWord((dword)header.magic);
	s.pushDWord((dword)header.headSize);
	s.pushDWord((dword)header.flags);
	s.pushDWord((dword)header.height);
	s.pushDWord((dword)header.width);
	s.pushDWord((dword)header.pitchOrLinearSize);
	s.pushDWord((dword)header.depth);
	s.pushDWord((dword)header.mipMapCount);
	s.pushDWord((dword)header.reserved1[0]);
	s.pushDWord((dword)header.reserved1[1]);
	s.pushDWord((dword)header.reserved1[2]);
	s.pushDWord((dword)header.reserved1[3]);
	s.pushDWord((dword)header.reserved1[4]);
	s.pushDWord((dword)header.reserved1[5]);
	s.pushDWord((dword)header.reserved1[6]);
	s.pushDWord((dword)header.reserved1[7]);
	s.pushDWord((dword)header.reserved1[8]);
	s.pushDWord((dword)header.reserved1[9]);
	s.pushDWord((dword)header.reserved1[10]);
	s.pushDWord((dword)header.pixelFormat.size);
	s.pushDWord((dword)header.pixelFormat.flags);
	s.pushDWord((dword)header.pixelFormat.fourCC);
	s.pushDWord((dword)header.pixelFormat.rgbBitCount);
	s.pushDWord((dword)header.pixelFormat.rBitMask);
	s.pushDWord((dword)header.pixelFormat.gBitMask);
	s.pushDWord((dword)header.pixelFormat.bBitMask);
	s.pushDWord((dword)header.pixelFormat.aBitMask);
	s.pushDWord((dword)header.caps1);
	s.pushDWord((dword)header.caps2);
	s.pushDWord((dword)header.caps3);
	s.pushDWord((dword)header.caps4);
	s.pushDWord((dword)header.reserved2);
	s.pushStream(data,data.length);
	return false;
}
bool DDSobject::makeFile(const str &DDSfileName){
	stream s;
	bool b = true;
	b &= make(s);
	b &= s.makeFile(DDSfileName);
	s.release();
	return false;
}
bool DDSobject::uncompress(image &mat){
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
bool DDSobject::uncompressMipmap(std::vector<image> &matList){
	return false;
}
bool DDSobject::compress(const image &mat){
	DXT5_compress(mat);
	//设置头
	header.magic = 0x20534444;
	header.headSize = 0x7c;
	header.flags = 0x81007;
	header.height = (mat.getHeight()+3)/4*4;
	header.width = (mat.getWidth()+3)/4*4;
	header.pitchOrLinearSize = data.length;
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
word DDSobject::RGB8888TO565(color c8888){
	word c565 = 0;
	c565 |= (c8888.B >> 3 << 11);
	c565 |= (c8888.G >> 2 << 5);
	c565 |= (c8888.R >> 3);
	return c565;
}
color DDSobject::RGB565TO8888(word c565){
	color c8888(0);
	c8888.alpha = (0xFF);
	c8888.R = ((c565 & 0xf800)>>8);
	c8888.G = ((c565 & 0x07e0)>>3);
	c8888.B = ((c565 & 0x001f)<<3);
	return c8888;
}
void DDSobject::DXT1_uncompress(const stream &udata, colorList &clist){
	int i;
	dword clrPart = udata[0] | (udata[1]<<8) | (udata[2]<<16) | (udata[3]<<24);
	dword idxPart = udata[4] | (udata[5]<<8) | (udata[6]<<16) | (udata[7]<<24);
	word uc1 = clrPart & 0xffff;
	word uc2 = clrPart >> 16;
	color cTempList[4];
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	if(uc1<=uc2){
		cTempList[2].alpha = (0xff);
		cTempList[2].B = ((cTempList[0].B+cTempList[1].B)/2);
		cTempList[2].R = ((cTempList[0].R+cTempList[1].R)/2);
		cTempList[2].G = ((cTempList[0].G+cTempList[1].G)/2);
		cTempList[3].alpha = (0x00);
	}else{
		cTempList[2].alpha = (0xff);
		cTempList[2].B = ((2*cTempList[0].B+cTempList[1].B)/3);
		cTempList[2].R = ((2*cTempList[0].R+cTempList[1].R)/3);
		cTempList[2].G = ((2*cTempList[0].G+cTempList[1].G)/3);
		cTempList[3].alpha = (0xff);
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
void DDSobject::DXT1_uncompress(image &mat){
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
void DDSobject::DXT3_uncompress(const stream &udata, colorList &clist){
	int i;
	dword clrPart = udata[8] | (udata[9]<<8) | (udata[10]<<16) | (udata[11]<<24);
	dword idxPart = udata[12] | (udata[13]<<8) | (udata[14]<<16) | (udata[15]<<24);
	//颜色提取
	word uc1 = clrPart & 0xffff;	//关键颜色1
	word uc2 = clrPart >> 16;	//关键颜色2
	color cTempList[4];			//四种颜色计算
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	cTempList[2].alpha = (0xff);	//透明度先缺省
	cTempList[2].B = ((2*cTempList[0].B+cTempList[1].B)/3);
	cTempList[2].R = ((2*cTempList[0].R+cTempList[1].R)/3);
	cTempList[2].G = ((2*cTempList[0].G+cTempList[1].G)/3);
	cTempList[3].alpha = (0xff);	//透明度先缺省
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
		cTemp.alpha = (iTempList2[i]);
		clist.push_back(cTemp);
	}
}
void DDSobject::DXT3_uncompress(image &mat){
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
void DDSobject::DXT5_uncompress(const stream &udata, colorList &clist){
	int i;
	dword clrPart = udata[8] | (udata[9]<<8) | (udata[10]<<16) | (udata[11]<<24);
	dword idxPart = udata[12] | (udata[13]<<8) | (udata[14]<<16) | (udata[15]<<24);
	//颜色提取
	word uc1 = clrPart & 0xffff;	//关键颜色1
	word uc2 = clrPart >> 16;	//关键颜色2
	color cTempList[4];			//四种颜色计算
	cTempList[0] = RGB565TO8888(uc1);
	cTempList[1] = RGB565TO8888(uc2);
	cTempList[2].alpha = (0xff);	//透明度先缺省
	cTempList[2].B = ((2*cTempList[0].B+cTempList[1].B)/3);
	cTempList[2].R = ((2*cTempList[0].R+cTempList[1].R)/3);
	cTempList[2].G = ((2*cTempList[0].G+cTempList[1].G)/3);
	cTempList[3].alpha = (0xff);	//透明度先缺省
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
		cTemp.alpha = (aTempList[iTempList2[i]]);
		clist.push_back(cTemp);
	}
}
void DDSobject::DXT5_uncompress(image &mat){
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
void DDSobject::DXT5_compress(const colorList &clist, stream &dest){
	int i;
	Koishi::uchar iTempList[16];		//存储透明度索引
	Koishi::uchar cTempList[16];		//存储颜色索引
	dest.allocate(16);
	//透明度处理
	//确定是否使用alpha7=0,alph8=0xff
	bool flUseBound = false;
	for(i=0;i<16;i++){
		if(clist[i].alpha == 0 || clist[i].alpha == 0xff){
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
			uTemp = clist[i].alpha;
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
			uTempb = clist[i].alpha<<8;
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
		dest.pushByte(ua1);
		dest.pushByte(ua2);
		dest.pushByte((Koishi::uchar)((iTempList[0]>>0)|(iTempList[1]<<3)|(iTempList[2]<<6)));
		dest.pushByte((Koishi::uchar)((iTempList[2]>>2)|(iTempList[3]<<1)|(iTempList[4]<<4)|(iTempList[5]<<7)));
		dest.pushByte((Koishi::uchar)((iTempList[5]>>1)|(iTempList[6]<<2)|(iTempList[7]<<5)));
		dest.pushByte((Koishi::uchar)((iTempList[8]>>0)|(iTempList[9]<<3)|(iTempList[10]<<6)));
		dest.pushByte((Koishi::uchar)((iTempList[10]>>2)|(iTempList[11]<<1)|(iTempList[12]<<4)|(iTempList[13]<<7)));
		dest.pushByte((Koishi::uchar)((iTempList[13]>>1)|(iTempList[14]<<2)|(iTempList[15]<<5)));
	}else{
		//ua1需要大于ua2，分7份
		Koishi::uchar ua1 = 0;		//最大值初始化
		Koishi::uchar ua2 = 0xff;	//最小值初始化
		Koishi::uchar uTemp;
		for(i=0;i<16;i++){
			uTemp = clist[i].alpha;
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
			uTempb = clist[i].alpha<<8;
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
		dest.pushByte(ua1);
		dest.pushByte(ua2);
		dest.pushByte((Koishi::uchar)((iTempList[0]>>0)|(iTempList[1]<<3)|(iTempList[2]<<6)));
		dest.pushByte((Koishi::uchar)((iTempList[2]>>2)|(iTempList[3]<<1)|(iTempList[4]<<4)|(iTempList[5]<<7)));
		dest.pushByte((Koishi::uchar)((iTempList[5]>>1)|(iTempList[6]<<2)|(iTempList[7]<<5)));
		dest.pushByte((Koishi::uchar)((iTempList[8]>>0)|(iTempList[9]<<3)|(iTempList[10]<<6)));
		dest.pushByte((Koishi::uchar)((iTempList[10]>>2)|(iTempList[11]<<1)|(iTempList[12]<<4)|(iTempList[13]<<7)));
		dest.pushByte((Koishi::uchar)((iTempList[13]>>1)|(iTempList[14]<<2)|(iTempList[15]<<5)));
	}
	//颜色处理
	//不同于DXT1，无需考虑两个关键颜色谁大谁小，默认uc1<=uc2，但采用alpha7=0,alph8=0xff时不应该考虑alpha=7或8的时候的情形
	dword ucb1 = 0xffffff;	//小关键颜色 高位R 中位G 低位B
	dword ucb2 = 0;			//大关键颜色
	for(i=0;i<16;i++){
		longex tempClr = clist[i].R | clist[i].G << 8 | clist[i].B <<16; 
		//若使用边界透明度，则不能考虑透明度为0的情形
		if(flUseBound){
			if(clist[i].alpha != 0){
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
	dest.pushWord(RGB8888TO565(color(ucb1 >> 16, ucb1 >> 8 & 0xff, ucb1 & 0xff)));
	dest.pushWord(RGB8888TO565(color(ucb2 >> 16, ucb2 >> 8 & 0xff, ucb2 & 0xff)));
	dest.pushByte((Koishi::uchar)((cTempList[0]>>0)|(cTempList[1]<<2)|(cTempList[2]<<4)|(cTempList[3]<<6)));
	dest.pushByte((Koishi::uchar)((cTempList[4]>>0)|(cTempList[5]<<2)|(cTempList[6]<<4)|(cTempList[7]<<6)));
	dest.pushByte((Koishi::uchar)((cTempList[8]>>0)|(cTempList[9]<<2)|(cTempList[10]<<4)|(cTempList[11]<<6)));
	dest.pushByte((Koishi::uchar)((cTempList[12]>>0)|(cTempList[13]<<2)|(cTempList[14]<<4)|(cTempList[15]<<6)));
}

void DDSobject::DXT5_compress(const image &mat){
	image mat1;
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
//////////////////////////////////////////////////////////////
//  TAG列表  
////////////////////////////////////////////////
//帧开始标记
//FFC0			SOF0		非层次Huffman编码·基线DCT
//FFC1			SOF1		非层次Huffman编码·扩展顺序DCT
//FFC2			SOF2		非层次Huffman编码·递进DCT
//FFC3			SOF3		非层次Huffman编码·空间顺序无损
//FFC5			SOF5		层次Huffman编码·差分DCT
//FFC6			SOF6		层次Huffman编码·差分层次DCT
//FFC7			SOF7		层次Huffman编码·差分空间无损
//FFC8			JPG			非层次算术编码·保留
//FFC9			SOF9		非层次算术编码·扩展顺序DCT
//FFCA			SOF10		非层次算术编码·递进DCT
//FFCB			SOF11		非层次算术编码·空间顺序无损
//FFCD			SOF13		层次算术编码·差分DCT
//FFCE			SOF14		层次算术编码·差分层次DCT
//FFCF			SOF15		层次算术编码·差分空间无损
//////////////////////////////////////////////////
//FFC4			DHT			Huffman树表
//FFCC			DAC			算术编码表
//////////////////////////////////////////////////
//FFD0-7		RST0-7		差分编码累积复位，8个
//FFD8			SOI			图像开始
//FFD9			EOI			图像结束
//FFDA			SOS			开始扫描（之后接图像数据）
//FFDB			DQT			量化表
//FFDC			DNL			线数
//FFDD			DRI			差分编码累积复位的间隔
//FFDE			DHP			层次级数
//FFDF			EXP			展开参考图像
//FFE0-E		APP0-15		APP数据
//FFF0-D		JPG0-14		保留，没卵用
//FFFE			COM			注释
//FF**			XXX			等价于**			
extern JFIFtag KoishiImageTool::JFIF::parseTag(const word &tagWord){
	uchar id = (tagWord ^ 0xFFFF) >> 8;
	return id <= 63 ? (JFIFtag)id : JFIF_UD;
}
extern word KoishiImageTool::JFIF::JFIFword(const word &lenWord){
	return  (lenWord & 0xFF) << 8 | lenWord >> 8;
}
bool JFIFobject::load(const stream &sour){
	//如果检测到SOS前，标志为SOI只记录标记，标志为其他记录标记后要解析长度和携带数据
	//如果检测到SOS后，一切均变为图像数据，但检测到EOI，RES0 - RES7时也会记录标记
	//图像数据中0xFF与其他数据联合解析部分由解码进行，不在解析文件结构时进行。
	stream s = sour;
	word wTemp;
	blockList.clear();
	while(s.getPosition() < s.length){
		JFIFblock block;
		s.read(&wTemp, 2);
		block.tag = parseTag(wTemp);
		if(!(block.tag == JFIF_UD || block.tag == JFIF_SOI|| block.tag == JFIF_EOI)){
			s.read(&wTemp, 2);
			block.len = JFIFword(wTemp);
			s.readStream(block.data, block.len - 2);
		}else{
			block.len = 0;
		}
		blockList.push_back(block);
		if(block.tag == JFIF_SOS)
			break;
	}
	imageData.clear();
	imageData.allocate(100 + s.length - s.getPosition());
	uchar u;
	while(s.getPosition() < s.length){
		s.readByte(u);
		imageData.pushByte(u);
		if(u == 0xFF && s.getPosition() < s.length){
			uchar u2;
			s.readByte(u2);
			imageData.pushByte(u2);
			if(u2 >= 0xD0 && u2 <= 0xD9){
				JFIFblock block;
				block.tag = parseTag(0xFF | u2 << 8);
				block.len = 0;
				blockList.push_back(block);
				if(block.tag == JFIF_EOI){
					return true;
				}
			}
		}
	}
	return false;
}
bool JFIFobject::loadFile(const str &fileName){
	stream s;
	s.loadFile(fileName);
	return load(s);
}
void JFIFobject::initDecoder(){
	int i, j;
	memset(&appInfo, 0, sizeof(appInfo));
	memset(&frameInfo, 0, sizeof(frameInfo));
	memset(&diffInfo, 0, sizeof(diffInfo));
	memset(&scanInfo, 0, sizeof(scanInfo));
	quantizInfo.clear();
	huffmanACinfo.clear();
	huffmanDCinfo.clear();
	stream *pData;
	uchar c = 0;
	for(i = 0;i<blockList.size();i++){
		pData = &blockList[i].data;
		JFIFquantizeInfo qTable;
		JFIFhuffmanInfo hTable;
		switch(blockList[i].tag){
		case JFIF_APP:
			pData -> resetPosition();
			pData -> movePosition(5);	//跳过"JFIF/0"
			pData -> read(&appInfo.mainVersion, 1);
			pData -> read(&appInfo.subVersion, 1);
			pData -> read(&appInfo.unitDensity, 1);
			pData -> read(&appInfo.horizontalDensity, 2);
			pData -> read(&appInfo.verticalDensity, 2);
			pData -> read(&appInfo.thumbnail.width, 1);
			pData -> read(&appInfo.thumbnail.height, 1);
			pData -> readStream(appInfo.thumbnail.data, 3 * appInfo.thumbnail.width * appInfo.thumbnail.height);
			appInfo.horizontalDensity = JFIFword(appInfo.horizontalDensity);
			appInfo.verticalDensity = JFIFword(appInfo.verticalDensity);
			break;
		case JFIF_DQT:
			memset(&qTable, 0, sizeof(JFIFquantizeInfo));
			pData -> resetPosition();
			pData -> readByte(c);
			qTable.ID = c & 0xF;
			qTable.precision = (c & 0xF0) ? 16 : 8;
			for(j = 0;j < 64;j++)
				pData -> read(qTable.term + j, (c & 0xF0) ? 2 : 1);
			quantizInfo.push_back(qTable);
			break;
		case JFIF_DHT:
			memset(&hTable, 0, sizeof(JFIFhuffmanInfo));
			pData -> resetPosition();
			pData -> readByte(c);
			hTable.huffmanID = c & 0xF;
			hTable.huffmanType = (c & 0xF0) ? 1 : 0;
			pData -> read(hTable.lenList, 16);
			pData -> readStream(hTable.data, pData->length - pData->getPosition());
			if(c & 0xF0){
				huffmanACinfo.push_back(hTable);
			}else{
				huffmanDCinfo.push_back(hTable);
			}
			break;
		case JFIF_DRI:
			pData->resetPosition();
			pData->read(&diffInfo.interval, 2);
			diffInfo.interval = JFIFword(diffInfo.interval);
			break;
		case JFIF_SOF0:
			pData -> resetPosition();
			pData -> read(&frameInfo.bitPerSample, 1);
			pData -> read(&frameInfo.height, 2);
			pData -> read(&frameInfo.width, 2);
			pData -> read(&frameInfo.colorDim, 1);
			for(j = 0;j<frameInfo.colorDim;j++){
				pData -> read(&frameInfo.colorInfo[j].ID, 1);
				pData -> readByte(c);
				pData ->read(&frameInfo.colorInfo[j].useQuantizeTableID, 1);
				frameInfo.colorInfo[j].horizontalSampleFactor = c >> 4;
				frameInfo.colorInfo[j].verticalSampleFactor = c & 0xF;
			}
			frameInfo.height = JFIFword(frameInfo.height);
			frameInfo.width = JFIFword(frameInfo.width);
			break;
		case JFIF_SOS:
			pData -> resetPosition();
			pData -> read(&scanInfo.colorDim, 1);
			for(j = 0;j<scanInfo.colorDim;j++){
				pData -> read(&scanInfo.colorInfo[j].ID, 1);
				pData -> readByte(c);
				scanInfo.colorInfo[j].AChuffmanID = c >> 4;
				scanInfo.colorInfo[j].DChuffmanID = c & 0xF;
			}
			break;
		}
	}
}

void JFIFobject::decodeHuffman(){
	//解析AC
	int i, j, k;
	huffmanAC.clear();
	huffmanDC.clear();
	for(i=0;i<huffmanACinfo.size();i++){
		JFIFhuffmanInfo &huffmanInfo = huffmanACinfo[i];
		int entryCount = 0;
		for(j = 0;j<16;j++){
			entryCount += huffmanInfo.lenList[i];
		}
		JFIFhuffmanMap map;
		JFIFhuffmanEntry prevEntry = {0xFFFF, 0, 0};
		map.reserve(entryCount);
		huffmanInfo.data.resetPosition();
		for(j = 0;j<16;j++){
			for(k = 0;k<huffmanInfo.lenList[j];k++){
				JFIFhuffmanEntry entry = {prevEntry.code + 1, 0, j + 1};
				huffmanInfo.data.read(&entry.value, 1);
				if(entry.bitLen > prevEntry.bitLen){
					entry.code <<= entry.bitLen - prevEntry.bitLen;
				}
				map.push_back(entry);
				prevEntry = entry;
			}
		}
		huffmanAC.push_back(map);
	}
	for(i=0;i<huffmanDCinfo.size();i++){
		JFIFhuffmanInfo &huffmanInfo = huffmanDCinfo[i];
		int entryCount = 0;
		for(j = 0;j<16;j++){
			entryCount += huffmanInfo.lenList[i];
		}
		JFIFhuffmanMap map;
		JFIFhuffmanEntry prevEntry = {0xFFFF, 0, 0};
		map.reserve(entryCount);
		huffmanInfo.data.resetPosition();
		for(j = 0;j<16;j++){
			for(k = 0;k<huffmanInfo.lenList[j];k++){
				JFIFhuffmanEntry entry = {prevEntry.code + 1, 0, j + 1};
				huffmanInfo.data.read(&entry.value, 1);
				if(entry.bitLen > prevEntry.bitLen){
					entry.code <<= entry.bitLen - prevEntry.bitLen;
				}
				map.push_back(entry);
				prevEntry = entry;
			}
		}
		huffmanDC.push_back(map);
	}
}