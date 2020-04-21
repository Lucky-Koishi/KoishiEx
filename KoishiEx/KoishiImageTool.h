#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//像素格式
using namespace Koishi;
namespace KoishiImageTool{
	/////////////////////////////////////////////
	//颜色算法
	extern color gradient(const color &sourceColor, const colorList &keyColorList, Koishi::colorProperty cp);
	extern colorList rainbowSort(const colorList &originList);
	extern colorList nearbySort(const colorList &originList);
	//////////////////////////////////////////
	//BMP算法
	extern void makeBMP(const image &mat, str fileName);
	extern bool loadBMP(image &mat, str fileName);
	namespace BMP{
		typedef struct BMPheader{
			word magic;
			dword fileSize;
			dword reserved;
			dword dataOffset;
		}BMPheader;
		typedef struct BMPinfo{
			dword infoSize;
			dword width;
			dword height;
			word planes;
			word bitCount;
			dword compression;
			dword dataSize;
			dword xPixelsPerMeter;
			dword yPixelsPerMeter;
			dword colorUsed;
			dword colorImportant;
		}BMPinfo;
		class BMPobject{
			stream data;
		public:
			BMPheader header;
			BMPinfo info;
			colorList paletteColor;
		public:
			bool load(stream s);
			bool loadFile(str fileName);
			void make(stream &s);
			void makeFile(str fileName);
			void output(image &mat);
			void input(const image &mat);
		};
	}
	/////////////////////////////////
	//PNG算法
	extern void makePNG(const image &mat, str fileName);
	extern void makePNG(const colorList &clrList, str fileName);
	extern bool loadPNG(image &mat, str fileName);
	namespace PNG{
		extern word PNGword(word originWord);
		extern dword PNGdword(dword originDword);
		extern uchar PNGpaeth(uchar a, uchar b, uchar c);
		extern uchar PNGaverage(uchar a, uchar b);
		extern dword PNGcodeCRC(uchar *dest, longex len);
		typedef enum PNGcolorType:uchar{
			PNG_GRAY = 0,
			PNG_TRUE = 2,
			PNG_INDEXED = 3,
			PNG_AGRAY = 4,
			PNG_ATRUE = 6
		}PNGformat;
		typedef struct PNGheader{
			dword magic1;
			dword magic2;
		}PNGheader;
		typedef struct PNGinfo{
			dword width;
			dword height;
			uchar depth;
			PNGformat colorType;
			uchar compress;
			uchar filter;
			uchar interlace;
		}PNGinfo;
		typedef uchar PNGalpha;
		typedef struct PNGcolor{
			uchar R, G, B;
		}PNGcolor;
		typedef struct PNGblockInfo{
			char chunkType[5];		//分块类型
			dword chunkDataSize;	//数据字段的长度(解析后要反着来)
			dword chunkDataOffset;	//数据字段的偏移量(整个分块的偏移量加上8)
			dword chunkDataCRC;		//分块类型+数据字段的CRC校验(解析后要反着来)
		}PNGblock;
		class PNGobject{
			stream data;
		public:
			PNGheader header;
			std::vector<PNGblock> chunkList;
			PNGinfo info;
			std::vector<PNGcolor> paletteColor;
			std::vector<PNGalpha> paletteAlpha;
		public:
			bool load(const stream &s);
			bool loadFile(str fileName);
			void make(stream &s);
			void makeFile(str fileName);
			bool output(image &mat);
			void input(const image &mat);
		private:
			//滤波器计算
			static uchar filter(uchar filterType, uchar curByte, uchar lefByte, uchar upByte, uchar lefUpByte);
			static uchar reconstruction(uchar filterType, uchar curByte, uchar lefByte, uchar upByte, uchar lefUpByte);
		};
	}
///////////////////////////////////////////////////////////////////////////////////////
	namespace GIF{
		typedef struct LZWnode{
			uchar content;
			word current;
			word parent;
			word firstChild;
			word nextBrother;
		}LZWnode;
		class LZW{
		private:
			static const word MAX_COUNT = 0X1000;
			uchar minCodeSize;
			word ID_NOEXIST;
			word ID_CLEAR;
			word ID_EOF;
			word nodeCount;
			word rootCount;
			LZWnode node[MAX_COUNT];
		private:
			void LZWinit(uchar LWZminCodeSize = 0);		//0为不重新设置，一般设置为GIF内部数据头的LZWminCode的大小（普遍为8）
			void LZWadd(word parentID, uchar content);
			word LZWfind(const stream &s);
			bool LZWget(word ID, stream &s);
			int LZWgetBitLen(uchar cMinCodeSize, word wNodeCount);			//根据当前节点的数目和最小LZW编码位数获得当前LZW编码位数 
		public:
			//LZW压缩和解压方式
			//参数为输入，输出流的引用，最小码数长度，是否采用变长存储
			void compress(stream &in, stream &out, uchar LWZminCodeSize, bool elongated = true);
			bool uncompress(stream &in, stream &out, uchar LWZminCodeSize, bool elongated = true);
		};
		//解析GIF文件结构
		typedef struct GIFinfo{
			str version;
			word width;
			word height;
			bool globalColorValid;
			bool globalColorSort;
			word globalColorCount;
			word globalColorDepth;
			uchar bkColorID;
			uchar aspectRatio;
			colorList globalPalette;
		}GIFinfo;
		typedef enum GIFexpandType:uchar{
			GIFET_PLAIN_TEXT = 1,
			GIFET_CONTROL = 0xF9,
			GIFET_COMMENT = 0xFE,
			GIFET_APPLICATION = 0xFF
		}GIFexpandType;
		typedef struct GIFexpandBlock{
			GIFexpandType type;
			stream dataDisposed;
		}GIFexpand;
		typedef struct GIFimageBlock{
			word xOffset, yOffset;
			word width, height;
			word localColorCount;
			bool localColorValid;
			bool localColorSort;
			bool localInterlace;
			colorList localPalette;
			uchar LZWminCodeSize;
			stream dataDisposed;
		}GIFimage;
		typedef struct GIFcontrolBlock{
			bool alphaValid;
			bool userInputValid;
			uchar dealMethod;
			uchar alphaIndex;
			int delayTime;
		}GIFcontrol;
		typedef struct GIFappBlock{
			char appName[9];
			char appVer[4];
			stream appData;
		}GIFappData;
		class GIFobject{
		public:
			GIFinfo info;
			std::vector<GIFimage> frame;
			std::vector<GIFexpand> expand;
			std::vector<GIFcontrol> controller;
			std::vector<GIFappData> appData;
		public:
			bool load(stream &s);
			bool loadFile(const str &fileName);
			bool output(image &mat, int frameID = 0);
			void input(const image &mat);
			void input(const image &mat, const colorList &usePalette);
			void input(const std::vector<image> &matList, int delayTime);
			void input(const std::vector<image> &matList, int delayTime, const str &imgPath, const std::vector<int> &frameID);
			void input(const std::vector<image> &matList, const colorList &usePalette, int delayTime);
			void input(const std::vector<image> &matList, const colorList &usePalette, int delayTime, const str &imgPath, const std::vector<int> &frameID);
			void make(stream &s);
			void makeFile(const str &fileName);
		};
	};
	
///////////////////////////////////////////////////////////////////////////////////////
	namespace DDS{
		typedef struct DDSPixelFormat{
			unsigned int size;				//像素格式数据大小，固定为32(0x20)
			unsigned int flags;				//标志位，DNF里一般用DDPF_FOURCC（0x04）
			unsigned int fourCC;			//DXT格式，flag里有DDPF_FOURCC有效，DNF里一般为字符串DXT1-5（0x31545844 - 0x35545844）
			unsigned int rgbBitCount;		//一个RGB(A)包含的位数，flag里有DDPF_RGB、DDPF_YUV、DDPF_LUMINANCE有效，DNF里一般无效
			unsigned int rBitMask;			//R通道(Y通道或亮度通道)掩码，DNF用不上
			unsigned int gBitMask;			//G通道(U通道)掩码，DNF用不上
			unsigned int bBitMask;			//B通道(V通道)掩码，DNF用不上
			unsigned int aBitMask;			//A通道掩码，DNF用不上
		}DDSPixelFormat;
		//像素头
		typedef struct DDSHeader{
			unsigned int magic;				//标识"DDS "，固定为542327876（0x20534444）
			unsigned int headSize;			//首部大小，固定为124（0x7C）
			unsigned int flags;				//标志位（见DDSHeaderFlags），DNF里经常采用的是“压缩纹理”，一般为0x81007
			unsigned int height;			//高度
			unsigned int width;				//宽度
			unsigned int pitchOrLinearSize;	//间距
			unsigned int depth;				//DNF里没用，标志位DDSD_DEPTH有效时有用
			unsigned int mipMapCount;		//DNF里没用，标志位DDSD_MIPMAPCOUNT有效时有用
			unsigned int reserved1[11];		//保留位，DNF里第十双字一般为"NVTT"（0x5454564E），第十一双字一般为0x20008，其他为零
			DDSPixelFormat pixelFormat;		//像素格式数据，见上文
			unsigned int caps1;				//曲面的复杂性（见DDSCaps），DNF里一般为0x1000
			unsigned int caps2;				//曲面的其他信息（主要是三维性），DNF里不用，为零
			unsigned int caps3;				//默认零
			unsigned int caps4;				//默认零
			unsigned int reserved2; 		//默认零
		}DDSHeader;
		//枚举
		typedef enum DDSHeaderFlag{
			DDSD_CAPS			=0x00000001U,//Required in every .dds file.
			DDSD_HEIGHT			=0x00000002U,//Required in every .dds file.
			DDSD_WIDTH			=0x00000004U,//Required in every .dds file.
			DDSD_PITCH			=0x00000008U,//Required when pitch is provided for an uncompressed texture.
			DDSD_PIXELFORMAT	=0x00001000U,//Required in every .dds file.
			DDSD_MIPMAPCOUNT	=0x00020000U,//Required in a mipmapped texture.
			DDSD_LINEARSIZE		=0x00080000U,//Required when pitch is provided for a compressed texture.
			DDSD_DEPTH			=0x00800000U //Required in a depth texture.
		}DDSHeaderFlag;
		typedef enum DDSCap{
			DDSCAPS_COMPLEX		=0x00000008U,//Optional; must be used on any file that contains more than one surface (a mipmap, a cubic environment map, or mipmapped volume texture).
			DDSCAPS_MIPMAP		=0x00400000U,//Optional; should be used for a mipmap.
			DDSCAPS_TEXTURE		=0x00001000U,//Required
		}DDSCap;
		typedef enum DDSCap2{
			DDSCAPS2_CUBEMAP			= 0x00000200U,
			DDSCAPS2_CUBEMAP_POSITIVEX	= 0x00000400U,
			DDSCAPS2_CUBEMAP_NEGATIVEX	= 0x00000800U,
			DDSCAPS2_CUBEMAP_POSITIVEY	= 0x00001000U,
			DDSCAPS2_CUBEMAP_NEGATIVEY	= 0x00002000U,
			DDSCAPS2_CUBEMAP_POSITIVEZ	= 0x00004000U,
			DDSCAPS2_CUBEMAP_NEGATIVEZ	= 0x00008000U,
			DDSCAPS2_VOLUME				= 0x00200000U
		}DDSCap2;
		typedef enum DDSPixelFormatFlag{
			DDPF_ALPHAPIXELS	= 0x00000001U,
			DDPF_ALPHA			= 0x00000002U,
			DDPF_FOURCC			= 0x00000004U,
			DDPF_RGB			= 0x00000040U,
			DDPF_YUV			= 0x00000200U,
			DDPF_LUMINANCE		= 0x00002000U
		}DDSPixelFormatFlag;
		class DDSobject{
		public:
			DDSobject(void);
			DDSobject(const stream &s);
			DDSobject(const str &DDSfileName);
			~DDSobject(void);
		protected:
			DDSHeader header;
			stream data;
		public:
			bool load(const stream &s);
			bool loadFile(const str &DDSfileName);
			bool make(stream &s);
			bool makeFile(const str &DDSfileName);
			bool uncompress(image &mat);
			bool uncompressMipmap(std::vector<image> &matList);
			bool compress(const image &mat);
			DDSHeader *getHeader();
		public:
			word RGB8888TO565(Koishi::color c8888);
			Koishi::color RGB565TO8888(word c565);
			void DXT1_uncompress(const stream &udata, colorList &clist);
			void DXT1_uncompress(image &mat);
			void DXT3_uncompress(const stream &udata, colorList &clist);
			void DXT3_uncompress(image &mat);
			void DXT5_uncompress(const stream &udata, colorList &clist);
			void DXT5_uncompress(image &mat);
			void DXT5_compress(const colorList &clist, stream &dest);
			void DXT5_compress(const image &mat);
		};
	}
	namespace JFIF{
		enum JFIFtag:uchar{
			JFIF_UD,	JFIF_COMM,	JFIF_JPG13,	JFIF_JPG12,
			JFIF_JPG11,	JFIF_JPG10,	JFIF_JPG9,	JFIF_JPG8,
			JFIF_JPG7,	JFIF_JPG6,	JFIF_JPG5,	JFIF_JPG4,
			JFIF_JPG3,	JFIF_JPG2,	JFIF_JPG1,	JFIF_JPG0,
			JFIF_APP15,	JFIF_APP14,	JFIF_APP13,	JFIF_APP12,
			JFIF_APP11,	JFIF_APP10,	JFIF_APP9,	JFIF_APP8,
			JFIF_APP7,	JFIF_APP6,	JFIF_APP5,	JFIF_APP4,
			JFIF_APP3,	JFIF_APP2,	JFIF_APP1,	JFIF_APP,
			JFIF_EXP,	JFIF_DHP,	JFIF_DRI,	JFIF_DNL,
			JFIF_DQT,	JFIF_SOS,	JFIF_EOI,	JFIF_SOI,
			JFIF_RST7,	JFIF_RST6,	JFIF_RST5,	JFIF_RST4,
			JFIF_RST3,	JFIF_RST2,	JFIF_RST1,	JFIF_RST0,
			JFIF_SOF15,	JFIF_SOF14,	JFIF_SOF13, JFIF_DAC,
			JFIF_SOF11,	JFIF_SOF10,	JFIF_SOF9,	JFIF_JPG,
			JFIF_SOF7,	JFIF_SOF6,	JFIF_SOF5,	JFIF_DHT,
			JFIF_SOF3,	JFIF_SOF2,	JFIF_SOF1,	JFIF_SOF0
		};
		extern JFIFtag parseTag(const word &tagWord);
		extern word JFIFword(const word &originWord);
		struct JFIFblock{
			JFIFtag tag;
			dword len;
			stream data;
		};
		struct JFIFthumbnail{
			word width;
			word height;
			stream data;
		};	//位于JFIFinfo中，一般都没有
		struct JFIFinfo{
			word mainVersion;
			word subVersion;
			word unitDensity;
			dword horizontalDensity;
			dword verticalDensity;
			JFIFthumbnail thumbnail;
		};	//从APP块解析
		struct JFIFquantizeInfo{
			word precision;
			word ID;
			word term[64];
		};	//DQT块解析，可以有多个
		struct JFIFstartFrame0{
			word bitPerSample;
			dword height;
			dword width;
			word colorDim;
			struct{
				word ID;
				word horizontalSampleFactor;
				word verticalSampleFactor;
				word useQuantizeTableID;
			}colorInfo[3];
		};	//SOF块信息
		struct JFIFhuffmanInfo{
			word huffmanType;		//DC还是AC
			word huffmanID;
			uchar lenList[16];
			stream data;
		};	//DHT块信息
		struct JFIFhuffmanEntry{
			word code;
			word value;
			word bitLen;
		};	//哈夫曼映射（一项），一个表可以解析出多项
		typedef std::vector<JFIFhuffmanEntry> JFIFhuffmanMap; //哈夫曼映射表
		struct JFIFdiffResetInfo{
			word interval;
		};	//DRI块信息
		struct JFIFstartScan{
			word colorDim;
			struct{
				word ID;
				word DChuffmanID;
				word AChuffmanID;
			}colorInfo[3];
		};	//SOS块信息
		class JFIFobject{
		public:
			std::vector<JFIFblock> blockList;
			stream imageData;
		public:
			bool load(const stream &sour);
			bool loadFile(const str &fileName);
		public:
			JFIFinfo appInfo;
			std::vector<JFIFquantizeInfo> quantizInfo;
			JFIFstartFrame0 frameInfo;
			std::vector<JFIFhuffmanInfo> huffmanACinfo;
			std::vector<JFIFhuffmanInfo> huffmanDCinfo;
			JFIFdiffResetInfo diffInfo;
			JFIFstartScan scanInfo;
		public:
			void initDecoder();
			void decodeHuffman();
			void decodeQuantiz();
		public:
			std::vector<JFIFhuffmanMap> huffmanAC;	//交流映射表
			std::vector<JFIFhuffmanMap> huffmanDC;	//直流映射表
		};
	}
}

