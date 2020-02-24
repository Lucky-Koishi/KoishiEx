#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//���ظ�ʽ
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
	//////������////////////////////////
	class NPKobject;		//NPK����
	class IMGobject;		//IMG����
	////////////////////////////
	class NPKentry{
	public:
		NPKentry(const str pathName, int blockID);
		NPKentry();
	public:
		str comment;	//·����
		int link;		//ӳ�䵽�����ݿ�
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
		//�������ӿ�
		bool extract(long pos, stream &dest);
		bool push(const stream &sour, const str &pathName);
		bool insert(long pos, const stream &sour, const str &pathName);
		bool remove(long pos);
		
		bool replace(long pos, const stream &sour);		//��ֱ���޸Ļ���������ݡ�ͬ���õ�IMG��һͬ���޸�
		bool replace2(long pos, const stream &sour);			//�������ݲ��뻺�棬ͬ���õ�����IMG�������޸ģ�ռ�ռ�
		//ӳ�����
		bool pushLink(long linkPos, const str &pathName);
		bool insertLink(long pos, long linkPos, const str &pathName);
		bool modifyLink(long pos, long newLinkPos);
		bool delink(long pos);
		long checkLink(long pos) const;							//���ҵ�һ����pos��ͬӳ�����Ŀ
		//��Ŀ������
		bool rename(long pos, const str &newPathName);
		bool find(const str &keyword, dword &pos, long startPos = 0);
		bool find(const str &keyword, const str &nonkeyword, dword &pos, long startPos = 0);
	public:
		//�����ӿ�
		bool extract(long pos, const str &fileName);
		bool push(const str &fileName, const str &pathName);
		bool insert(long pos, const str &fileName, const str &pathName);
		bool replace(long pos, const str &fileName);
		//IMG����Ľӿ�
		bool IMGextract(dword pos, IMGobject &obj);
		bool IMGpush(IMGobject &obj, const str &imgName);
		bool IMGinsert(long pos, IMGobject &obj, const str &imgName);
		bool IMGremove(long pos);
		bool IMGreplace(long pos, IMGobject &obj);
		bool IMGrename(long pos, const str &newName);
		long IMGgetVersion(long pos);
		long IMGgetPaletteCount(long pos);
		//��Ч�ӿ�
		long SNDgetVersion(long pos);
	};
	class PICinfo;			//IMG�ڲ�֡����
	class TEXinfo;			//IMG�ڲ���������
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
		//˫����ģʽ��Ч
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
		bool loadFile(str fileName);			//���ļ��ж�ȡ
		bool saveFile(str fileName);			//�����ļ�
		bool load(stream &s);
		bool make(stream &s);
		bool create(IMGversion ver);
		bool release();
		//��ͼ����
		bool PICgetInfo(long pos, PICinfo &info);		//��ȡ��������Ϣ
		bool PICgetInfoOffset(long pos, longex &off);		//��ȡ������ƫ����
		bool PICgetBound(long pos, long &left, long &right, long &top, long &bottom);
		bool PICgetTotalBound(long &left, long &right, long &top, long &bottom);
		bool PICgetData(long pos, stream &s);			//��ȡͼƬ������
		bool PICgetDataOffset(long pos, longex &off);		//��ȡͼƬ������ƫ����
		bool PICpush(const PICinfo &info, const stream &s);				//����ͼƬ
		bool PICinsert(long pos, const PICinfo &info, const stream &s);	//����ͼƬ������
		bool PICremove(long pos);										//ɾ��ͼƬ
		bool PICreplace(long pos, const PICinfo &info, const stream &s);//�滻ͼƬ
		bool PICextract(long pos, matrix &mat, long paletteID = 0);		//��ȡͼƬ
		bool PICpreprocess(const matrix &mat, stream &s, PICinfo &info, colorFormat cf = COLOR_UDEF, long paletteID = 0);//Ԥ����ͼƬ
		bool PICextractIndexMatrix(long pos, matrix &mat);									//��ȡ�ľ�������������
		bool PICpreprocessIndexMatrix(const matrix &mat, stream &s, PICinfo &info);			//�����������ݵľ����IMG����Ԥ����
		bool PICempty(stream &s, PICinfo &info);						//�Կ�֡Ԥ����ͼƬ
		bool PICsetInfoPara(long pos, long term, void *pval);		//������������Ϣ
		//��������
		bool TEXgetInfo(long pos, TEXinfo &info);		//��ȡ������������Ϣ
		bool TEXgetInfoOffset(long pos, longex &off);		//��ȡ����������ƫ����
		bool TEXgetData(long pos, stream &s);			//��ȡ��������
		bool TEXgetDataOffset(long pos, longex &off);		//��ȡ��������ƫ����
		
		bool TEXpush(const TEXinfo &info, const stream &s);
		bool TEXinsert(long pos, const TEXinfo &info, const stream &s);
		bool TEXremove(long pos);
		bool TEXreplace(long pos, const TEXinfo &info, const stream &s);
		bool TEXextract(long pos, matrix &mat);
		bool TEXpreprocess(const matrix &mat, stream &s, TEXinfo &info, colorFormat cf = COLOR_UDEF);
		//��ɫ����
		bool CLRpush(const color &clr, long paletteID = 0);
		bool CLRinsert(long pos, const color &clr, long paletteID = 0);
		bool CLRremove(long pos, long paletteID = 0);
		bool CLRreplace(long pos, const color &clr, long paletteID = 0);
		bool CLRnewPalette();
		bool CLRdeletePalette(long paletteID);
		//ת������
		bool convertToV2(std::vector<IMGobject> &newIOList, colorFormat cf = ARGB8888);
		bool convertToV4(std::vector<IMGobject> &newIOList, colorList useColorPalette, bool useOriginPalette = true);
		bool convertToV5(std::vector<IMGobject> &newIOList, colorFormat cf, colorList useColorPalette, bool makeTexture);
		bool convertToV6(std::vector<IMGobject> &newIOList, colorTable useColorPaletteList, bool useOriginPalette = true);
		
		
		//��������
		long linkFind(dword pos, dword depth = 5);		//��������֡����ָ��depthΪ��ȣ�
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
		stream dataHeader;		//�ļ�ͷ��V2,V4,V6Ϊһ��,V5Ϊһ�飩
		stream dataPalette;		//��ɫ������
		stream dataIndexTexture;//DDS��Ϣ��V5֮����Ч
		stream dataIndexPicture;//ͼ����Ϣ
		stream dataTexture;		//DDSͼ�����ݣ�V5֮����Ч
		stream dataPicture;		//ͼ������
	};
}

namespace KoishiExpand{
	using namespace KoishiNeoplePack;
	using namespace Koishi;
	//��չ����
	namespace KoishiMarkTool{
		//ͼƬ�����幤��
		extern void CharMat(char p, matrix &mat, color clr = color(0xff,0,0,0));
		extern void StrMat(str s, matrix &mat, color clr = color(0xff,0,0,0));
		extern void CharMatLarge(char p, matrix &mat, color clr = color(0xff,0,0,0));
		extern void StrMatLarge(str s, matrix &mat, color clr = color(0xff,0,0,0));
		extern bool MatrixMarking(const matrix &sourceMatrix, matrix &destMatrix, str codeString, point deltaPoint, color textColor);
		//PS�������
		extern bool MatrixPSstyle(const matrix &sourceMatrix, matrix &destMatrix, color clrBound = color(0xFF, 0, 0, 0), color clrBG1 = color(0xFF, 0xFF, 0xFF, 0xFF), color clrBG2 = color(0xFF, 0xDD, 0xDD, 0xDD));
	}
	namespace KoishiDownloadTool{
		class SPKblock{
		public:
			unsigned long bzlib;		//��һ��˫�֣�������BZѹ����Ϊ1
			unsigned long len;			//�ڶ���˫�֣����ݿ鳤�ȣ����������ݿ�ͷ��48�ֽ�
			unsigned long bzlib_r;		//������˫�֣���һ˫�ַ���
			unsigned long len_r;		//���ĸ�˫�֣��ڶ�˫�ַ���
			unsigned char hash[32];		//��ϣ32�ֽڣ������������ʵ������

			unsigned long startPos;		//��ԭSPK�ļ�����ʼλ��
			unsigned long mainStartPos;	//��ʵ������ԭSPK�ļ�����ʼλ�ã����len����ȡ����������
		};
		typedef std::vector<SPKblock> SPKlist;
		class SPKobject{
		public:
			//ͷ��
			unsigned long magic;			//Ӧ���Ǳ�ʶ����Ϊ0x1B111
			unsigned char name[260];			//�ļ���
			unsigned long reserve1;			//����SPK�ļ��ڴ�˫�־�Ϊ0xC8
			unsigned long decompressed_len;	//ѹ�����ļ���С
			unsigned char hash[32];			//��ϣ32�ֽ�
			unsigned long maxBlockSize;		//������ݿ�����ʵ���ݳ��ȣ��ƺ�����0xE1000��900K��
			unsigned long indexCount;		//���ݿ���Ŀ
			std::vector<unsigned long> listLen;	//���ݿ�ĳ���
			//֮����Ǹ������ݿ���
			SPKlist list;
			Koishi::stream  data;
			bool load(Koishi::str fileName);
			void release();
			//��ȡ�������ݿ�
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
	//�ɰ汾IMGV1
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
	//��ͼչʾ
	public:
		exhibit();
	public:
		void clear();
		void create(int width, int height);
		bool putMatrix(const matrix &newMat, bool expanded = false);
	public:
		matrix canvas;		//�󻭲�
	public:
		//�ڷŷ�ʽ1���Ȱ��аڷţ�ÿ�аڷ���Ϻ�����һ�У����е�����Ϊ��һ�����������
		queue hList;				//ÿ�е���ʼ����(ÿ�е�һ��ͼ��y����)
		std::vector<queue> rList;	//ָ������ÿ�е���ʼ����(������ÿһ��ͼ��x����)
		int hMaxPerRow;				//��ǰ�����е�ͼ�����߶ȣ����ڼ�������һ��ʱ����y����
	};
	class authorLock{
	public:
		//����0������� ����1������ȷ ����2���� ����3�޴��ļ����ļ����Ȳ���
		static int checkLock(str fileName, str password);
		static bool addLock(str fileName, str password);
	};
	class textDisplay{
	public:
		static void binary(const stream &in, stream &out);		//�Զ���������ֽ�������λ��ǰ��λ�ں�
		static void binaryFile(const stream &in, str fileName);	//����ļ�
		static void binaryCompareFile(const stream &in1, const stream &in2, str fileName);	//����ļ�
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
	extern str shorten(const str &path);					//����·���������һ���ڵ�
	extern str imgAddV4Num(const str &imgName, long num);	//V6���V4ʱʹ��
	extern str getAvatarIDString(int i);					//��ʱװIDתΪ����
	extern str getCareerNPKName(avatarCareer cr);			//NPK�ļ���ְҵ����(gunner_at)
	extern str getCareerIMGName(avatarCareer cr);			//IMG·����ְҵ����(gg_)
	extern str getAvatarPartNPKName(avatarPart pt);			//NPK�ļ�����������(skin)
	extern str getAvatarPartIMGName(avatarPart pt);			//IMG·������������(body)
	extern str getAvatarLayerName(avatarLayer ly);			//IMG·����ͼ�㲿��(a1,a2��)
	extern str getAvatarNPKName(avatarCareer ch, avatarPart pt); //������NPK�ļ���
	extern str getAvatarIMGName(avatarCareer ch, avatarPart pt); //IMG·�����Ĵ󲿷�(gg_body)
	extern color getCareerColor(avatarCareer cr);						//���ְҵ�Ĵ���ɫ
	extern point getAvatarModelOffset(avatarCareer cr, avatarPart pt);	//���չ��ְҵ������������ĵ�ƫ����
	extern long getCareerRepresentativeFrame(avatarCareer cr);			//����֡
	extern str getIconNPKName(avatarCareer cr);							//���ͼ��NPK
	extern std::vector<str> getIconIMGName(avatarCareer cr, avatarPart pt);			//���ͼ��IMG
	class avatar;
	extern bool parseAvatarName(const str &avatarName, avatar &av, avatarLayer &al);
	extern str makeAvatarName(avatar av, avatarLayer al);
	//ƴ���������
	extern void getMQData(int order, avatarPart &part, avatarLayer &layer);
	extern avatarPart getMQPart(int order);
	extern avatarLayer getMQLayer(int order);
	class avatar{
	public:
		avatar();
	public:
		//ԭ����
		avatarCareer carrer;
		avatarPart part;
		long ID;
		bool isTN;
	public:
		//��������
		int v6palette;
		bool layer[ALAYER_MAXCOUNT];
	};
	typedef struct avatarBigram{
		long ID;			//ID
		bool isTN;			//TN
		long paletteID;		//��ɫ��ID
		long originPos;		//��Ӧ��װ����ԭAlbum�е�λ��
	}avatarBigram;//װ���Ԫ��(ID + ��ɫ��ID)�Լ�һЩ��Ҫ����Ϣ
	class avatarAlbum{
	public:
		bool valid;
		avatarCareer career;
		avatarPart part;
		str resoucePath;
		NPKobject sourceNPK;
		std::vector<avatar> avatarList;						 //�洢װ����Ϣ
		std::vector<std::vector<long>> avatarPos;			 //�洢װ���Ӧ��ͼ��IMG��NPK�е�λ��
		std::vector<std::vector<long>> avatarPosAtBigramList;//���յ�ɫ�����ȫ����ʱ��ÿ��װ�����ڵ�λ��
		std::vector<avatarBigram> bigramList;				 //���յ�ɫ�����ȫ��������
	public:
		int selected;							//��ǰѡ��
		int selectedPalette;					//��ǰѡ��ɫ��
		int selectedFrame;						//��ǰѡ��֡
		IMGobject layerIMG[ALAYER_MAXCOUNT];	//ͼ��IMG
		str layerIMGpath[ALAYER_MAXCOUNT];		//ͼ��IMG·���б�
		int layerIMGpos[ALAYER_MAXCOUNT];		//ͼ��IMG��NPK�е�λ�ã���-1�򲻴���
		matrix layerMatrix[ALAYER_MAXCOUNT];	//ͼ��IMG�ľ���
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
		str resoucePath;			//�����ļ�·��
		avatarCareer career;		//��ǰ����Ľ�ɫ
		avatarAlbum partAlbum[APART_MAXCOUNT];
		//����
		void clear();
		void setPath(str pathStr);
		void setCarrer(avatarCareer ac);
		//����NPK
		bool loadNPK(avatarPart ap);
		bool changeFrame(int newFrame);
		bool changeIMG(avatarPart ap, long selected);
		long changeIMGByID(avatarPart ap, long ID, bool isTN = false);	//ID��λ����������ƥ��V6��ʽ��Ŀ��IMG���Ҳ�������-1
		void updateMatrix(avatarPart ap);
		//��ʾ��ǰЧ��
		void makeMatrix(point leftTopPos, size displaySize, matrix &mat);
		void makeNPK(NPKobject &no);			//����ǰѡ���IMG������һ��NPK����ź���
		//����
		void makeModel(matrix &outputMat, color baseColor, size modelSize, avatarPart ap, int selected, int paletteID, point offsetPos, int frame, PICinfo *ptrModelPI, matrix *ptrModelMat);
		void makeButton(matrix &outputMat, color baseColor, size modelSize, int iconCtrl);
	};
}