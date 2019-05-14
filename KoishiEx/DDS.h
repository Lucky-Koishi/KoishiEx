#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//���ظ�ʽ

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
