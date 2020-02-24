#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//像素格式
using namespace Koishi;

namespace KoishiNeoplePack{
	enum IMGversion:dword{
		V1 = 1, V2 = 2, V4 = 4, V5 = 5, V6 = 6, VUDEF = 0, VUKNOWN = 0xFFFFFFFF, 
		VSOUND = 0xFFFFFFFE
	};
	enum SNDversion:dword{
		VWAVE, VVORBIS, VMP3, VIMAGE, VSNDUKNOWN
	};
	enum IMGcomp:dword{
		COMP_NONE =	5, COMP_ZLIB = 6, COMP_ZLIB_DUAL = 7, COMP_UDEF = 0
	};
	//////工厂类////////////////////////
	class NPKobject;		//NPK对象
	class IMGobject;		//IMG对象
	////////////////////////////
	class NPKentry{
	public:
		NPKentry(const str pathName, int blockID);
		NPKentry();
	public:
		str comment;	//路径名
		int link;		//映射到的数据块
	};
	class NPKobject{
	public:
		NPKobject();
		NPKobject(const stream &in);
		NPKobject(const str &fileName);
	public:
		dword count;
		std::vector<NPKentry> entry;
		std::vector<stream> block;
	public:
		bool load(const stream &in);
		bool make(stream &out);
		bool loadFile(const str &fileName);
		bool saveFile(const str &fileName);
		bool create();
		bool release();
		longex getSize() const;
	public:
		//数据流接口
		bool extract(long pos, stream &dest);
		bool push(const stream &sour, const str &pathName);
		bool insert(long pos, const stream &sour, const str &pathName);
		bool remove(long pos);
		
		bool replace(long pos, const stream &sour);		//将直接修改缓存里的数据·同引用的IMG将一同被修改
		bool replace2(long pos, const stream &sour);			//将新数据插入缓存，同引用的其他IMG将不会修改，占空间
		//映射操作
		bool pushLink(long linkPos, const str &pathName);
		bool insertLink(long pos, long linkPos, const str &pathName);
		bool modifyLink(long pos, long newLinkPos);
		bool delink(long pos);
		long checkLink(long pos) const;							//查找第一个与pos相同映射的条目
		//条目名操作
		bool rename(long pos, const str &newPathName);
		bool find(const str &keyword, dword &pos, long startPos = 0);
		bool find(const str &keyword, const str &nonkeyword, dword &pos, long startPos = 0);
	public:
		//其他接口
		bool extract(long pos, const str &fileName);
		bool push(const str &fileName, const str &pathName);
		bool insert(long pos, const str &fileName, const str &pathName);
		bool replace(long pos, const str &fileName);
		//IMG对象的接口
		bool IMGextract(dword pos, IMGobject &obj);
		bool IMGpush(IMGobject &obj, const str &imgName);
		bool IMGinsert(long pos, IMGobject &obj, const str &imgName);
		bool IMGremove(long pos);
		bool IMGreplace(long pos, IMGobject &obj);
		bool IMGrename(long pos, const str &newName);
		long IMGgetVersion(long pos);
		long IMGgetPaletteCount(long pos);
		//音效接口
		long SNDgetVersion(long pos);
	};
	class PICinfo;			//IMG内部帧数据
	class TEXinfo;			//IMG内部纹理集数据
	typedef std::vector<PICinfo> PIClist;
	typedef std::vector<TEXinfo> TEXlist;

	class PICinfo{
	public:
		colorFormat format;
		IMGcomp comp;
		dword dataSize;
		point basePt;
		size picSize;
		size frmSize;
		long linkTo;
		//双索引模式有效
		dword TEXusing;
		point TEXpointLT;
		point TEXpointRB;
	public:
		PICinfo();
	};
	class TEXinfo{
	public:
		colorFormat format;
		dword ID;
		dword compressedLength;
		dword dataLength;
		dword width;
		dword height;
		dword reserved;
	public:
		TEXinfo();
	};
	class IMGobject{
	public:
		IMGobject();
		IMGobject(stream &s);
		IMGobject(const str &fileName);
		~IMGobject();
		bool loadFile(str fileName);			//从文件中读取
		bool saveFile(str fileName);			//保存文件
		bool load(stream &s);
		bool make(stream &s);
		bool create(IMGversion ver);
		bool release();
		//贴图操作
		bool PICgetInfo(long pos, PICinfo &info);		//获取索引项信息
		bool PICgetInfoOffset(long pos, longex &off);		//获取索引项偏移量
		bool PICgetBound(long pos, long &left, long &right, long &top, long &bottom);
		bool PICgetTotalBound(long &left, long &right, long &top, long &bottom);
		bool PICgetData(long pos, stream &s);			//获取图片型数据
		bool PICgetDataOffset(long pos, longex &off);		//获取图片型数据偏移量
		bool PICpush(const PICinfo &info, const stream &s);				//插入图片
		bool PICinsert(long pos, const PICinfo &info, const stream &s);	//插入图片索引项
		bool PICremove(long pos);										//删除图片
		bool PICreplace(long pos, const PICinfo &info, const stream &s);//替换图片
		bool PICextract(long pos, matrix &mat, long paletteID = 0);		//提取图片
		bool PICpreprocess(const matrix &mat, stream &s, PICinfo &info, colorFormat cf = COLOR_UDEF, long paletteID = 0);//预处理图片
		bool PICextractIndexMatrix(long pos, matrix &mat);									//提取的矩阵是索引数据
		bool PICpreprocessIndexMatrix(const matrix &mat, stream &s, PICinfo &info);			//根据索引数据的矩阵对IMG进行预处理
		bool PICempty(stream &s, PICinfo &info);						//以空帧预处理图片
		bool PICsetInfoPara(long pos, long term, void *pval);		//设置索引项信息
		//纹理集操作
		bool TEXgetInfo(long pos, TEXinfo &info);		//获取纹理集索引项信息
		bool TEXgetInfoOffset(long pos, longex &off);		//获取纹理集索引项偏移量
		bool TEXgetData(long pos, stream &s);			//获取纹理集数据
		bool TEXgetDataOffset(long pos, longex &off);		//获取纹理集数据偏移量
		
		bool TEXpush(const TEXinfo &info, const stream &s);
		bool TEXinsert(long pos, const TEXinfo &info, const stream &s);
		bool TEXremove(long pos);
		bool TEXreplace(long pos, const TEXinfo &info, const stream &s);
		bool TEXextract(long pos, matrix &mat);
		bool TEXpreprocess(const matrix &mat, stream &s, TEXinfo &info, colorFormat cf = COLOR_UDEF);
		//颜色操作
		bool CLRpush(const color &clr, long paletteID = 0);
		bool CLRinsert(long pos, const color &clr, long paletteID = 0);
		bool CLRremove(long pos, long paletteID = 0);
		bool CLRreplace(long pos, const color &clr, long paletteID = 0);
		bool CLRnewPalette();
		bool CLRdeletePalette(long paletteID);
		//转换操作
		bool convertToV2(std::vector<IMGobject> &newIOList, colorFormat cf = ARGB8888);
		bool convertToV4(std::vector<IMGobject> &newIOList, colorList useColorPalette, bool useOriginPalette = true);
		bool convertToV5(std::vector<IMGobject> &newIOList, colorFormat cf, colorList useColorPalette, bool makeTexture);
		bool convertToV6(std::vector<IMGobject> &newIOList, colorTable useColorPaletteList, bool useOriginPalette = true);
		
		
		//其他操作
		long linkFind(dword pos, dword depth = 5);		//查找索引帧最终指向（depth为深度）
		longex getSize() const;
		bool empty();
		static void makeEmpty(IMGobject &newIO, int frameCount);
		static bool checkIsOld(stream &s);
	public:
		NPKentry *derived;

		IMGversion version;
		dword indexCount, indexSize;
		dword V5_TEXCount;
		dword V5_totalLength;

		palette paletteData;
		TEXlist TEXcontent;
		PIClist PICcontent;
	protected:
		stream *getData(uchar _part);
		stream dataHeader;		//文件头（V2,V4,V6为一组,V5为一组）
		stream dataPalette;		//调色板数据
		stream dataIndexTexture;//DDS信息，V5之外无效
		stream dataIndexPicture;//图像信息
		stream dataTexture;		//DDS图像数据，V5之外无效
		stream dataPicture;		//图像数据
	};
}

namespace KoishiExpand{
	using namespace KoishiNeoplePack;
	using namespace Koishi;
	//扩展功能
	namespace KoishiMarkTool{
		//图片内字体工具
		extern void CharMat(char p, matrix &mat, color clr = color(0xff,0,0,0));
		extern void StrMat(str s, matrix &mat, color clr = color(0xff,0,0,0));
		extern void CharMatLarge(char p, matrix &mat, color clr = color(0xff,0,0,0));
		extern void StrMatLarge(str s, matrix &mat, color clr = color(0xff,0,0,0));
		extern bool MatrixMarking(const matrix &sourceMatrix, matrix &destMatrix, str codeString, point deltaPoint, color textColor);
		//PS画布风格
		extern bool MatrixPSstyle(const matrix &sourceMatrix, matrix &destMatrix, color clrBound = color(0xFF, 0, 0, 0), color clrBG1 = color(0xFF, 0xFF, 0xFF, 0xFF), color clrBG2 = color(0xFF, 0xDD, 0xDD, 0xDD));
	}
	namespace KoishiDownloadTool{
		class SPKblock{
		public:
			unsigned long bzlib;		//第一个双字，若采用BZ压缩则为1
			unsigned long len;			//第二个双字，数据块长度，不包含数据块头的48字节
			unsigned long bzlib_r;		//第三个双字，第一双字反码
			unsigned long len_r;		//第四个双字，第二双字反码
			unsigned char hash[32];		//哈希32字节，再往后就是真实数据了

			unsigned long startPos;		//在原SPK文件的起始位置
			unsigned long mainStartPos;	//真实数据在原SPK文件的起始位置，配合len可以取出完整数据
		};
		typedef std::vector<SPKblock> SPKlist;
		class SPKobject{
		public:
			//头部
			unsigned long magic;			//应该是标识，均为0x1B111
			unsigned char name[260];			//文件名
			unsigned long reserve1;			//所有SPK文件内此双字均为0xC8
			unsigned long decompressed_len;	//压缩后文件大小
			unsigned char hash[32];			//哈希32字节
			unsigned long maxBlockSize;		//最大数据块中真实数据长度，似乎都是0xE1000（900K）
			unsigned long indexCount;		//数据块数目
			std::vector<unsigned long> listLen;	//数据块的长度
			//之后就是各种数据块了
			SPKlist list;
			Koishi::stream  data;
			bool load(Koishi::str fileName);
			void release();
			//提取单个数据块
			void extract(int pos, stream &s);
			void extractTrueStream(stream &s);
			void makeNPK(str NPKfileName);
		};
		class LSTfile{
		public:
			unsigned long nameLen;
			unsigned char name[256];
			unsigned long fileLen;
			unsigned long compLen;
			unsigned long hashLen;
			unsigned char hash[32];
			LSTfile();
		};
		class LSTfolder{
		public:
			unsigned long nameLen;
			unsigned char name[256];
			unsigned long fileCount;
			unsigned long subFolderCount;
			std::vector<LSTfile> list;
			LSTfolder();
		};
		class LSTobject{
		public:
			unsigned char hash[32];
			unsigned long magic;
			unsigned long reserve;
			unsigned long reserve2;
			std::vector<LSTfolder> list;
			void load(Koishi::stream &s);
			bool load(const str &fileName);
			bool getImagePack2(LSTfolder &lf);
			bool getSoundPack(LSTfolder &lf);
		};
		class TCTobject{
		public:
			unsigned char name[256];
			unsigned char ex[256];
			unsigned long magic;
			unsigned short minVersion;
			unsigned short GTBF;
			unsigned short compMethod;
			unsigned short lastTime;
			unsigned short lastDate;
			unsigned long CRC32;
			unsigned long comSize;
			unsigned long uncomSize;
			unsigned short nmSize;
			unsigned short exSize;
			unsigned long dtStartPos;
			Koishi::stream  data;
			bool load(str fileName);
			bool release();
			bool makeNPK(str NPKfileName);
		};
		class LSTfileGF{
		public:
			unsigned char name[256];
			unsigned char lenStr[32];
			unsigned char hash[32];
			LSTfileGF();
		};
		class LSTobjectGF{
		public:
			std::vector<LSTfileGF>  list;
			bool load(const str &fileName);
			bool load2(const str &fileName);
		};
	}
	class IMGobjectV1{
	//旧版本IMGV1
	protected:
		PIClist PICcontent;
		queueex posList;
		queueex lenList;
		stream data;
	public:
		bool load(stream &s);
		bool load(const str &fileName);
		bool make(IMGobject &io);
		bool release();
	};
	class exhibit{
	//多图展示
	public:
		exhibit();
	public:
		void clear();
		void create(int width, int height);
		bool putMatrix(const matrix &newMat, bool expanded = false);
	public:
		matrix canvas;		//大画布
	public:
		//摆放方式1·先按行摆放，每行摆放完毕后·另起一行，新行的坐标为上一行坐标的下限
		queue hList;				//每行的起始坐标(每行第一张图的y坐标)
		std::vector<queue> rList;	//指定行中每列的起始坐标(单行中每一张图的x坐标)
		int hMaxPerRow;				//当前放入行的图的最大高度，用于计算另起一行时的新y坐标
	};
	class authorLock{
	public:
		//返回0口令错误 返回1口令正确 返回2无锁 返回3无此文件或文件长度不够
		static int checkLock(str fileName, str password);
		static bool addLock(str fileName, str password);
	};
	class textDisplay{
	public:
		static void binary(const stream &in, stream &out);		//以二进制输出字节流，低位在前高位在后
		static void binaryFile(const stream &in, str fileName);	//输出文件
		static void binaryCompareFile(const stream &in1, const stream &in2, str fileName);	//输出文件
	};
	//////////////////////////////////////////////////////////////////////////////////////
}

namespace KoishiAvatar{
	using namespace Koishi;
	using namespace KoishiNeoplePack;
	enum avatarCareer{ACAREER_UD, ACAREER_SM, ACAREER_SG, ACAREER_FT, ACAREER_FM, ACAREER_GN, ACAREER_GG, ACAREER_MG, ACAREER_MM, ACAREER_PR, ACAREER_PG, ACAREER_TH, ACAREER_KN, ACAREER_DL, ACAREER_GB, ACAREER_MAXCOUNT};
	enum avatarPart{APART_UD, APART_CAP, APART_HAIR, APART_FACE, APART_NECK, APART_COAT, APART_PANTS, APART_BELT, APART_SHOES, APART_BODY, APART_MAXCOUNT, APART_WEAPON};
	enum avatarLayer{ALAYER_UD, ALAYER_A, ALAYER_A1, ALAYER_A2, ALAYER_B, ALAYER_B1, ALAYER_B2, ALAYER_C, ALAYER_C1, ALAYER_C2, ALAYER_D, ALAYER_D1, ALAYER_D2,	ALAYER_E, ALAYER_E1, ALAYER_E2,	ALAYER_F, ALAYER_F1, ALAYER_F2,	ALAYER_G, ALAYER_G1, ALAYER_G2,	ALAYER_H, ALAYER_H1, ALAYER_H2, ALAYER_K, ALAYER_K1, ALAYER_K2, ALAYER_X, ALAYER_X1, ALAYER_X2, ALAYER_MAXCOUNT};
	enum {TOTAL_LAYER_COUNT = 64};
	extern bool isnum(uchar chars);
	extern str shorten(const str &path);					//缩短路径名至最后一个节点
	extern str imgAddV4Num(const str &imgName, long num);	//V6变成V4时使用
	extern str getAvatarIDString(int i);					//将时装ID转为数字
	extern str getCareerNPKName(avatarCareer cr);			//NPK文件名职业部分(gunner_at)
	extern str getCareerIMGName(avatarCareer cr);			//IMG路径名职业部分(gg_)
	extern str getAvatarPartNPKName(avatarPart pt);			//NPK文件名部件部分(skin)
	extern str getAvatarPartIMGName(avatarPart pt);			//IMG路径名部件部分(body)
	extern str getAvatarLayerName(avatarLayer ly);			//IMG路径名图层部分(a1,a2等)
	extern str getAvatarNPKName(avatarCareer ch, avatarPart pt); //完整的NPK文件名
	extern str getAvatarIMGName(avatarCareer ch, avatarPart pt); //IMG路径名的大部分(gg_body)
	extern color getCareerColor(avatarCareer cr);						//获得职业的代表色
	extern point getAvatarModelOffset(avatarCareer cr, avatarPart pt);	//获得展现职业部件的最佳中心点偏移量
	extern long getCareerRepresentativeFrame(avatarCareer cr);			//代表帧
	extern str getIconNPKName(avatarCareer cr);							//获得图标NPK
	extern std::vector<str> getIconIMGName(avatarCareer cr, avatarPart pt);			//获得图标IMG
	class avatar;
	extern bool parseAvatarName(const str &avatarName, avatar &av, avatarLayer &al);
	extern str makeAvatarName(avatar av, avatarLayer al);
	//拼合相关数据
	extern void getMQData(int order, avatarPart &part, avatarLayer &layer);
	extern avatarPart getMQPart(int order);
	extern avatarLayer getMQLayer(int order);
	class avatar{
	public:
		avatar();
	public:
		//原数据
		avatarCareer carrer;
		avatarPart part;
		long ID;
		bool isTN;
	public:
		//辅助数据
		int v6palette;
		bool layer[ALAYER_MAXCOUNT];
	};
	typedef struct avatarBigram{
		long ID;			//ID
		bool isTN;			//TN
		long paletteID;		//调色板ID
		long originPos;		//对应的装扮在原Album中的位置
	}avatarBigram;//装扮二元组(ID + 调色板ID)以及一些必要的信息
	class avatarAlbum{
	public:
		bool valid;
		avatarCareer career;
		avatarPart part;
		str resoucePath;
		NPKobject sourceNPK;
		std::vector<avatar> avatarList;						 //存储装扮信息
		std::vector<std::vector<long>> avatarPos;			 //存储装扮对应的图层IMG在NPK中的位置
		std::vector<std::vector<long>> avatarPosAtBigramList;//按照调色板进行全排列时，每个装扮所在的位置
		std::vector<avatarBigram> bigramList;				 //按照调色板进行全排列序列
	public:
		int selected;							//当前选择
		int selectedPalette;					//当前选择色板
		int selectedFrame;						//当前选择帧
		IMGobject layerIMG[ALAYER_MAXCOUNT];	//图层IMG
		str layerIMGpath[ALAYER_MAXCOUNT];		//图层IMG路径列表
		int layerIMGpos[ALAYER_MAXCOUNT];		//图层IMG在NPK中的位置，若-1则不存在
		matrix layerMatrix[ALAYER_MAXCOUNT];	//图层IMG的矩阵
	public:
		avatarAlbum();
		void clear();
		bool loadNPK();
		bool changeIMG(long selected);
		bool changeIMGByID(long avatarID, bool isTN = false);
		long findPosByID(long avatarID, bool isTN = false);
		bool changePalette(long paletteID);
		bool changeFrame(long frame);
		bool updateMatrix();
		bool getBasePoint(avatarLayer al, point &pt);
		bool getMatrix(avatarLayer al, matrix &mat);
	};
	class avatarFactory{
	public:
		str resoucePath;			//导入文件路径
		avatarCareer career;		//当前处理的角色
		avatarAlbum partAlbum[APART_MAXCOUNT];
		//设置
		void clear();
		void setPath(str pathStr);
		void setCarrer(avatarCareer ac);
		//操作NPK
		bool loadNPK(avatarPart ap);
		bool changeFrame(int newFrame);
		bool changeIMG(avatarPart ap, long selected);
		long changeIMGByID(avatarPart ap, long ID, bool isTN = false);	//ID个位数有余数则匹配V6格式的目标IMG，找不到返回-1
		void updateMatrix(avatarPart ap);
		//显示当前效果
		void makeMatrix(point leftTopPos, size displaySize, matrix &mat);
		void makeNPK(NPKobject &no);			//将当前选择的IMG都放入一个NPK里，且排好序
		//其他
		void makeModel(matrix &outputMat, color baseColor, size modelSize, avatarPart ap, int selected, int paletteID, point offsetPos, int frame, PICinfo *ptrModelPI, matrix *ptrModelMat);
		void makeButton(matrix &outputMat, color baseColor, size modelSize, int iconCtrl);
	};
}