#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//像素格式

namespace KoishiDDS{
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
	using namespace Koishi;
	class DDS
	{
	public:
		DDS(void);
		DDS(const stream &s);
		DDS(const str &DDSfileName);
		~DDS(void);
	protected:
		DDSHeader header;
		stream data1, data2;
	public:
		bool load(const stream &s);
		bool loadFile(const str &DDSfileName);
		bool make(stream &s);
		bool makeFile(const str &DDSfileName);
		bool uncompress(matrix &mat);
	private:
		b16 RGB8888TO565(Koishi::color c8888);
		Koishi::color RGB565TO8888(b16 c565);
		void DXT1_uncompress(const stream &udata, lcolor &clist);
		void DXT1_uncompress(matrix &mat);
		void DXT3_uncompress(const stream &udata, lcolor &clist);
		void DXT3_uncompress(matrix &mat);
		void DXT5_uncompress(const stream &udata, lcolor &clist);
		void DXT5_uncompress(matrix &mat);
	};
}
