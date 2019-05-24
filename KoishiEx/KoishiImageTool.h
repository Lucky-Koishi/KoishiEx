#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//���ظ�ʽ
using namespace Koishi;
namespace KoishiImageTool{
	/////////////////////////////////////////////
	//��ɫ�㷨
	extern color gradient(const color &sourceColor, const colorList &keyColorList, Koishi::colorProperty cp);
	extern colorList rainbowSort(const colorList &originList);
	extern colorList nearbySort(const colorList &originList);
	//////////////////////////////////////////
	//BMP�㷨
	extern void makeBMP(const matrix &mat, str fileName);
	extern bool loadBMP(matrix &mat, str fileName);
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
		void output(matrix &mat);
		void input(const matrix &mat);
	};
	/////////////////////////////////
	//PNG�㷨
	extern void makePNG(const matrix &mat, str fileName);
	extern void makePNG(const colorList &clrList, str fileName);
	extern bool loadPNG(matrix &mat, str fileName);
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
		char chunkType[5];		//�ֿ�����
		dword chunkDataSize;	//�����ֶεĳ���(������Ҫ������)
		dword chunkDataOffset;	//�����ֶε�ƫ����(�����ֿ��ƫ��������8)
		dword chunkDataCRC;		//�ֿ�����+�����ֶε�CRCУ��(������Ҫ������)
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
		bool output(matrix &mat);
		void input(const matrix &mat);
	private:
		//�˲�������
		static uchar filter(uchar filterType, uchar curByte, uchar lefByte, uchar upByte, uchar lefUpByte);
		static uchar reconstruction(uchar filterType, uchar curByte, uchar lefByte, uchar upByte, uchar lefUpByte);
	};
///////////////////////////////////////////////////////////////////////////////////////
	namespace GIF{
		typedef struct LZWnode{
			uchar content;
			word current, parent, firstChild, nextBrother;
		}LZWnode;
		class LZW{
		private:
			static const word MAX_COUNT = 0X1000;
			uchar minCodeSize;
			word ID_NOEXIST, ID_CLEAR, ID_EOF;
			word nodeCount, rootCount;
			LZWnode node[MAX_COUNT];
		private:
			void init(uchar LWZminCodeSize = 0);		//0Ϊ���������ã�һ������ΪGIF�ڲ�����ͷ��LZWminCode�Ĵ�С���ձ�Ϊ8��
			void add(word parentID, uchar content);
			word find(const stream &s);
			bool get(word ID, stream &s);
		private:
			static int LZWgetBitLen(uchar cMinCodeSize, word cNodeCount);	//���ݵ�ǰ�ڵ����Ŀ����СLZW����λ����õ�ǰLZW����λ�� 
			static void LZWwriteWord(stream &res, longex &startBitPos, int bitCount, word w);	//LZWʽд������λ��ʼ��
			static word LZWreadWord(const stream &res, longex &startBitPos, int bitCount);		//LZWʽ��������λ��ʼ��
		public:
			void compress(const stream &in, stream &out, uchar LWZminCodeSize, bool elongated = true);
			bool uncompress(const stream &in, stream &out, uchar LWZminCodeSize, bool elongated = true);
		};
		//����GIF�ļ��ṹ
		typedef struct GIFinfo{
			str version;
			word width, height;
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
			std::vector<GIFimage> image;
			std::vector<GIFexpand> expand;
			std::vector<GIFcontrol> controller;
			std::vector<GIFappData> appData;
		public:
			bool load(stream &s);
			bool loadFile(const str &fileName);
			bool output(matrix &mat, int frame = 0);
			void input(const matrix &mat);
			void input(const matrix &mat, const colorList &usePalette);
			void input(const std::vector<matrix> &matList, int delayTime);
			void input(const std::vector<matrix> &matList, int delayTime, const str &imgPath, const std::vector<int> &frameID);
			void input(const std::vector<matrix> &matList, const colorList &usePalette, int delayTime);
			void input(const std::vector<matrix> &matList, const colorList &usePalette, int delayTime, const str &imgPath, const std::vector<int> &frameID);
			void make(stream &s);
			void makeFile(const str &fileName);
		};
	};
	
///////////////////////////////////////////////////////////////////////////////////////
	
}
namespace KoishiDDS{
	typedef struct DDSPixelFormat{
		unsigned int size;				//���ظ�ʽ���ݴ�С���̶�Ϊ32(0x20)
		unsigned int flags;				//��־λ��DNF��һ����DDPF_FOURCC��0x04��
		unsigned int fourCC;			//DXT��ʽ��flag����DDPF_FOURCC��Ч��DNF��һ��Ϊ�ַ���DXT1-5��0x31545844 - 0x35545844��
		unsigned int rgbBitCount;		//һ��RGB(A)������λ����flag����DDPF_RGB��DDPF_YUV��DDPF_LUMINANCE��Ч��DNF��һ����Ч
		unsigned int rBitMask;			//Rͨ��(Yͨ��������ͨ��)���룬DNF�ò���
		unsigned int gBitMask;			//Gͨ��(Uͨ��)���룬DNF�ò���
		unsigned int bBitMask;			//Bͨ��(Vͨ��)���룬DNF�ò���
		unsigned int aBitMask;			//Aͨ�����룬DNF�ò���
	}DDSPixelFormat;
	//����ͷ
	typedef struct DDSHeader{
		unsigned int magic;				//��ʶ"DDS "���̶�Ϊ542327876��0x20534444��
		unsigned int headSize;			//�ײ���С���̶�Ϊ124��0x7C��
		unsigned int flags;				//��־λ����DDSHeaderFlags����DNF�ﾭ�����õ��ǡ�ѹ��������һ��Ϊ0x81007
		unsigned int height;			//�߶�
		unsigned int width;				//���
		unsigned int pitchOrLinearSize;	//���
		unsigned int depth;				//DNF��û�ã���־λDDSD_DEPTH��Чʱ����
		unsigned int mipMapCount;		//DNF��û�ã���־λDDSD_MIPMAPCOUNT��Чʱ����
		unsigned int reserved1[11];		//����λ��DNF���ʮ˫��һ��Ϊ"NVTT"��0x5454564E������ʮһ˫��һ��Ϊ0x20008������Ϊ��
		DDSPixelFormat pixelFormat;		//���ظ�ʽ���ݣ�������
		unsigned int caps1;				//����ĸ����ԣ���DDSCaps����DNF��һ��Ϊ0x1000
		unsigned int caps2;				//�����������Ϣ����Ҫ����ά�ԣ���DNF�ﲻ�ã�Ϊ��
		unsigned int caps3;				//Ĭ����
		unsigned int caps4;				//Ĭ����
		unsigned int reserved2; 		//Ĭ����
	}DDSHeader;
	//ö��
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
	class DDS{
	public:
		DDS(void);
		DDS(const stream &s);
		DDS(const str &DDSfileName);
		~DDS(void);
	protected:
		DDSHeader header;
		stream data;
	public:
		bool load(const stream &s);
		bool loadFile(const str &DDSfileName);
		bool make(stream &s);
		bool makeFile(const str &DDSfileName);
		bool uncompress(matrix &mat);
		bool uncompressMipmap(std::vector<matrix> &matList);
		bool compress(const matrix &mat);
		DDSHeader *getHeader();
	public:
		word RGB8888TO565(Koishi::color c8888);
		Koishi::color RGB565TO8888(word c565);
		void DXT1_uncompress(const stream &udata, colorList &clist);
		void DXT1_uncompress(matrix &mat);
		void DXT3_uncompress(const stream &udata, colorList &clist);
		void DXT3_uncompress(matrix &mat);
		void DXT5_uncompress(const stream &udata, colorList &clist);
		void DXT5_uncompress(matrix &mat);
		void DXT5_compress(const colorList &clist, stream &dest);
		void DXT5_compress(const matrix &mat);
	};
}
