#ifndef KOISHI_EX_LIB
#define KOISHI_EX_LIB

#pragma once

#include <vector>
#include <string>
#include <math.h>
#pragma warning(disable:4018)			//�޷������������ֱ�ӽ��в���
#pragma warning(disable:4244)			//��ͬ��������֮���ǿ��ת��
#pragma warning(disable:4390)			//���ڿյ��ܿ����
#pragma warning(disable:4996)			//����ȫ�ĺ��������


#define KOISHI_EX_VER		(double)1.1

#define MAX_UNCOMPRESSED_DATA_LENGTH	0x1000000

#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define DEF_GETSET(_type, _member) public:_type _member;public:inline _type get_##_member() const{return _member;}inline _type*getPtr_##_member(){return &_member;}inline void set_##_member(_type val){_member=val;}

namespace Koishi{
	//�����������
	typedef std::string	str;
	typedef unsigned char uchar;
	typedef unsigned short word;
	typedef unsigned long dword;
	typedef long long longex;
	typedef std::vector<long> queue;
	typedef std::vector<longex> queueex;

	//IMG�汾��
	enum IMGversion:dword{V1 = 1, V2 = 2, V4 = 4, V5 = 5, V6 = 6, VUDEF = 0};
	//������
	enum compressType:dword{COMP_NONE = 5, COMP_ZLIB = 6, COMP_ZLIB_DUAL = 7, COMP_UDEF = 0};
	//��ɫ��ʽ
	enum colorFormat:dword{ARGB8888 = 0x10, ARGB4444 = 0x0F, ARGB1555 = 0x0E, LINK = 0x11, DDS_DXT1 = 0x12, DDS_DXT3 = 0x13, DDS_DXT5 = 0x14, COLOR_UDEF = 0, INDEX_FMT_PALETTE};
	//���ģʽ
	enum colorMethod{LAY, DARKEN, MULTIPLY, COLORBURN, LINEARBURN, LIGHTEN, SCREEN, COLORDODGE, LINEARDODGE, OVERLAY, HARDLIGHT, SOFTLIGHT, VIVIDLIGHT, LINEARLIGHT, PINLIGHT, HARDMIX, DIFFER, EXCLUSION};
	//���޸�ͼƬ����������
	enum picChangablePara{LINKTO, BASEX, BASEY, FRAMEW, FRAMEH};
	//��ɫ���� ͸���ȡ���ɫ����ɫ����ɫ���Ҷȡ�ɫ�������Ͷȡ�����
	enum colorProperty{COLOR_ALPHA, COLOR_CHANNEL_RED, COLOR_CHANNEL_GREEN, COLOR_CHANNEL_BLUE, COLOR_GRAYSCALE, COLOR_HUE, COLOR_SATURATION, COLOR_VALUE};

	class stream;
	class color;
	class point;
	class size;
	class matrix;
	class palette;

	typedef std::vector<color> colorList;
	typedef std::vector<colorList> colorTable;
	///////////////////////////////////////
	//������:������
	///////////////////////////////////////
	class stream{
	public:
		stream();
		stream(longex _len);
		stream(const stream &_s);
		~stream();
		stream& operator = (const stream &_s);
	public:
		//����ռ�
		void allocate(longex _len);
		void reallocate(longex _len);
		void release();
	public:
		//�±꺯��
		uchar& operator[] (longex pos) const;
		uchar getBit(longex pos, long bitCount = 1) const;
		uchar getRBit(longex pos, long bitCount = 1) const;
		operator str();
		longex getLen() const;
		longex getMaxLen() const;
		longex getPtPos() const;
		longex ptMoveTo(longex pos);
		longex ptMove(longex dist);
	public:
		void clear(bool makeZero = false);
		//��������
		uchar push(uchar d);
		uchar push(word d);
		uchar push(dword d);
		uchar push(longex d);
		uchar push(long i);
		//��ȡ�α괦����
		uchar read(uchar &d);
		uchar read(word &d);
		uchar read(dword &d);
		uchar read(longex &d);
		uchar read(long &i);
		uchar read(void *dest, longex l);
		//�����ַ���
		uchar pushString(str s);
		//��ȡ�ַ���
		str readString(dword l);
		//������һ��������
		uchar pushStream(const stream &s, longex l);
		//���α괦��ȡl���ֽڵ�dest
		void readStream(stream &dest, longex l);
		//�м�λ�ò�����һ��������
		void insertStream(const stream &s, longex l, longex pos);
		//ɾ��������
		void deleteStream(longex pos, longex l);
		//����ָ��λ�õ�һ���ֽ�
		bool modify(longex pos, uchar d);
		//����ָ��λ�õ�һ������
		bool modify(longex pos, long i);
		//�滻����
		longex replace(const uchar &whos, const uchar &to);
	public:
		//���������洢���ļ�
		bool makeFile(str fileName);
		//��ȡ�ļ���������
		bool loadFile(str fileName);
	public:
		void nameMask();
		int compressData(stream &dest, compressType type);
		int uncompressData(stream &dest, compressType type, longex tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
		void getSHA256(stream &dest);
		void getSHA256(stream &dest, const stream &added);
	public:
		//����������һ��������
		longex findStream(const stream &s, longex startPos = 0);
		longex splitStream(const stream &s, queueex &posList, queueex &lenList);
		int BZcompress(stream &dest);
		int BZuncompress(stream &dest);
		int ZLIBcompress(stream &dest);
		int ZLIBuncompress(stream &dest, longex tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
	public:
		uchar *data;
		longex len,maxLen,pt;
	};
	///////////////////////////////////////
	//������:��ɫ��HSV��Ϣ
	///////////////////////////////////////
	typedef struct colorHSV{
		long H;
		double S;
		double V;
	}colorHSV;
	///////////////////////////////////////
	//������:��ɫ��RGB��Ϣ
	///////////////////////////////////////
	class color{
	public:
		uchar A,R,G,B;
	public:
		color();
		color(dword colorDt, colorFormat clrFmt = ARGB8888);
		color(uchar r, uchar g, uchar b);
		color(uchar a, uchar r, uchar g, uchar b);
		void set(dword colorDt, colorFormat clrFmt = ARGB8888);
		void make(dword &colorDt, colorFormat clrFmt = ARGB8888);
		operator dword() const;
	public:
		//�Ҷ�
		color gray() const;
		double getProperty(colorProperty theProperty) const;
		//��ɫ���
		double mixMethod(double a,double b, colorMethod _method);
		uchar mixMethod(uchar a,uchar b, colorMethod _method);
		void mixWith(const color &_clr2, colorMethod _method = LAY);
		color mix(const color &_clr1, const color &_clr2, colorMethod _method = LAY);
	public:
		//HSV����
		void getHSV(colorHSV &hsv) const;
		void useHSV(const colorHSV &hsv);
		void moveHto(long newH);
		void moveSto(double newS);
		void moveVto(double newV);
		void moveRto(uchar newR);
		void moveGto(uchar newG);
		void moveBto(uchar newB);
		void moveH(long delta);
		void moveS(double delta);
		void moveV(double delta);
		void moveR(short delta);
		void moveG(short delta);
		void moveB(short delta);
		void moveA(short delta);
	public:
		//����������ɫ��ŷ�Ͼ����ƽ��
		static int EuclideanDistanceSquareOf(const color &a, const color &b);
		//ƽ����ɫ�ռ�������ɫ
		static color lose(const color &c, uchar part);
		static color loseBit(const color &c, uchar bit);
		//٤��任
		static color loseBlack(const color &c, uchar gamma);
	};
	///////////////////////////////////////
	//������:����㡤�ߴ�
	///////////////////////////////////////
	class point{
	public:
		long X, Y;
	public:
		point();
		point(long x, long y);
		void set(long x, long y);
		void moveHonz(long dist);
		void moveVert(long dist);
		void move(long honzDist, long vertDist);
		void move(size sz);
		point oppo() const;

		point operator + (const point &delta) const;
		point operator - (const point &delta) const;
		point operator + (const size &sz) const;
		point operator - (const size &sz) const;
		point operator + () const;
		point operator - () const;
		point operator * (double mult) const;
		point operator / (double mult) const;
		point operator ~ () const;
	};
	class size{
	public:
		long W,H;
	public:
		size();
		size(long w, long h);
		void set(long w, long h);
		long area() const;
	};
	///////////////////////////////////////
	//������:���󣬵�R=G=B=0ʱ��������������������
	///////////////////////////////////////
	class matrix{
	public:
		matrix();
		matrix(dword _row, dword _column);
		matrix(const size &_sz);
		matrix(const matrix &_mat);
		~matrix();
		matrix& operator = (const matrix &_mat);

	public:
		//�ڴ����
		bool valid();
		void create(dword _row, dword _column);
		void create(const size &_sz);
		void destory();
		void fill(color clr);
		void push(color clr);									//�α괦��ɫ��ֵ����1
		longex push(const stream &_s, colorFormat cf = ARGB8888);	//������䣬��cfΪINDEX_FMT_PALEETEʱ��Ϊ����������
		longex make(stream &s, colorFormat cf = ARGB8888) const;	//��������������cfΪINDEX_FMT_PALEETEʱ��Ϊ����������
	public:
		//ȡֵ/����
		color* operator[] (dword _i) const;		//��д˫�±꺯��
		long getHeight() const;
		long getWidth() const;
		long getElemCount() const;
		//Ԫ��ͳ��
		void setElem(dword r, dword c, const color &clr);
		void setElem(dword id, const color &clr);
		color getElem(dword r, dword c) const;			//ȡ���ص�
		color getElem(dword id) const;						//ȡ���ص�
		long getElemCountNzero() const;						//ͳ��ʵ�����ظ���
		long getElemCountWhos(const color &whos) const;		//ͳ����ɫֵ����whos�����ظ���
		void getElemCountList(colorList &getColorList) const;			//ͳ�����г��ֵ���ɫ
		void getElemHonzBound(dword &lower, dword &upper) const;	//ͳ�ƴ���ʵ�����ص�ˮƽ�߽�
		void getElemVertBound(dword &lower, dword &upper) const;	//ͳ�ƴ���ʵ�����صĴ�ֱ�߽�
	public:
		//��������
		long moveHonz(long dist, const color &surplus = color(0,0,0,0));		//��0Ԫ��ˮƽ�ƶ�
		long moveVert(long dist, const color &surplus = color(0,0,0,0));		//��0Ԫ�ش�ֱ�ƶ�
		long replace(const color &whos, const color &to);//��ָ����ɫ���������ر��ΪĿ����ɫ
		void putFore(const matrix &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//�Դ˾���Ϊ�ײ㣬����Ŀ�����
		void putBack(const matrix &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//�Դ˾���Ϊ���㣬������»���Ŀ�����
	public:
		//�Դ˾���Ϊ��׼������������
		void clip(matrix &dest, dword rowStart, dword rowEnd, dword columnStart, dword columnEnd) const;//�ü�
		void expand(matrix &dest, dword toTop, dword toBottom, dword toLeft, dword toRight) const;		//����
		void zoom(matrix &dest, double ratio) const;			//����
		void zoom(matrix &dest, double honzRatio, double vertRatio) const;	//����

		void clip(dword rowStart, dword rowEnd, dword columnStart, dword columnEnd);
		void expand(dword toTop, dword toBottom, dword toLeft, dword toRight);		//����
		void zoom(double ratio);			//����
		void zoom(double honzRatio, double vertRatio);	//����
	public:
		//��ɫ����
		void lose(uchar fine); //��ͨ��
		void loseBit(uchar bit); //��λ
		void loseBlack(uchar gamma); //ȥ�ڵ�
		void turnShield();			//��ʵɫɫ���ֱ�Ϊ1/2͸���İ�ɫ
	public:
		//���Ʋ���
		void line(point p1, point p2, const color &clr);
		void rectangle(point p1, point p2, const color &clr);
		void filledRectangle(point p1, point p2, const color &clr);
		void filledLattice(point p1, point p2, const color &clr1, const color &clr2, long size);
	public:
		//bool loadPNG(str fileName);
		//bool makePNG(str fileName);
	protected:
		color *data;
		dword column, row, pt;
	};
	//��ɫ��
	class palette{
	public:
		palette();
		~palette();
	public:
		colorList &operator[] (long i);
		void clear();
		void push(const colorList &list);
		void remove(long paletteID);
		long getCount() const;
		long getTotalColorCount() const;
	public:
		//�Ե�����ɫ�����
		long getColorCount(long paletteID = 0) const;
		long findColor(color goalColor, long paletteID = 0) const;
		long matchColor(color goalColor, long paletteID = 0) const;
		long matchColor(color goalColor, long paletteID, long &nearestDistance) const;
		bool joinWith(const colorList &list, long paletteID = 0);
	public:
		bool tinyMake(stream &s, long paletteID = 0);
		bool bigMake(stream &s);
	public:
		static bool makeACT(str fileName, const colorList &list);
		static bool loadACT(str fileName, colorList &list);
		static bool makeCID(str fileName, const colorList &list);
		static bool loadCID(str fileName, colorList &list);
		static colorList palette2();
		static colorList palette16();
		static colorList palette64();
		static colorList palette256();
	protected:
		colorTable table;
	};
	//////������////////////////////////
	class NPKobject;		//����NPK��
	class IMGobject;		//IMG��
	//////�ṹ��//////////////////////
	class IMGindex;			//IMG��������
	class PICinfo;			//PIC����
	class TEXinfo;			//DDS����
	typedef std::vector<IMGindex> IMGcontent;
	typedef std::vector<PICinfo> PIClist;
	typedef std::vector<TEXinfo> TEXlist;
	///////////////////////////////////
	class IMGindex{
		//IMG��������
	public:
		dword imgoffset, imgsize;
		str imgname;
	public:
		IMGindex();
	};
	class PICinfo{
		//ͼ����Ϣ
		DEF_GETSET(colorFormat,format);
		DEF_GETSET(compressType,comp);
		DEF_GETSET(dword,dataSize);
		DEF_GETSET(point,basePt);
		DEF_GETSET(size,picSize);
		DEF_GETSET(size,frmSize);
		DEF_GETSET(long,linkTo);
		//˫����ģʽ
		DEF_GETSET(dword,TEXusing);
		DEF_GETSET(point,TEXpointLT);
		DEF_GETSET(point,TEXpointRB);
	public:
		PICinfo();
	};
	class TEXinfo{
		//������Ϣ
		DEF_GETSET(colorFormat,format);
		DEF_GETSET(dword,ID);
		DEF_GETSET(dword,compressedLength);
		DEF_GETSET(dword,dataLength);
		DEF_GETSET(dword,width);
		DEF_GETSET(dword,height);
		DEF_GETSET(dword,reserved);
	public:
		TEXinfo();
	};
	class NPKobject{
	public:
		NPKobject();
		NPKobject(const stream &s);
		NPKobject(const str &fileName);
		bool load(const stream &s);
		bool make(stream &s);
		bool loadFile(const str &fileName);
		bool saveFile(const str &fileName);
		bool create();
		bool release();
		bool loadIndex(const str &fileName, std::vector<IMGversion> &versionList);	//����ȡ�汾
		long getVersion(long pos);
		long getPaletteCount(long pos);
	public:
		bool IMGpush(IMGobject &obj, const str &imgName);
		bool IMGinsert(long pos, IMGobject &obj, const str &imgName);
		bool IMGremove(long pos);
		bool IMGreplace(long pos, IMGobject &obj);
		bool IMGrename(long pos, const str &newName);
	public:
		stream *getData(uchar part);
		longex getSize() const;
		bool IMGextract(dword pos, IMGobject &obj);
		bool IMGfind(const str &keyword, dword &pos);
		bool IMGfind(const str &keyword, const str &nonkeyword, dword &pos);
		bool randomExtract(long pos, str fileName);
		bool randomPush(stream s, const str &imgName);
		bool randomExtract(dword pos, stream &s);
	public:
		bool IMGpushLink(long linkPos, const str &otherName);
		bool IMGremoveLink(long pos);
		bool IMGmodifyLink(long pos, long newLinkPos);
		long IMGcheckLink(long pos);
	public:
		dword count;
		IMGcontent content;
	protected:
		//Data���ĸ������ļ�ͷ��IMG������У��λ��IMG�ļ�
		stream dataHeader;
		stream dataIndex;
		stream dataCheckCode;
		stream dataMain;
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
		IMGindex *derived;

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
			void extract(int pos, Koishi::stream &s);
			void extractTrueStream(Koishi::stream &s);
			void makeNPK(Koishi::str NPKfileName);
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
			bool load(const Koishi::str &fileName);
			bool getImagePack2(LSTfolder &lf);
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
			bool load(Koishi::str fileName);
			bool release();
			bool makeNPK(Koishi::str NPKfileName);
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
			bool load(const Koishi::str &fileName);
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
		bool load(Koishi::stream &s);
		bool load(const Koishi::str &fileName);
		bool make(Koishi::IMGobject &io);
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
	namespace KoishiAudioTool{
		typedef struct WAVinfo{
			dword magic;
			dword dataSize;
			dword format;
		}WAVinfo;
		typedef struct WAVheader{
			dword magic;
			dword blockSize;
			word audioFormat;
			word countChannels;
			dword sampleRate;
			dword byteRate;
			word blockAlign;
			word bitsPerSample;
		}WAVheader;
		typedef struct WAVfact{
			dword magic;
			dword dw1;
			dword dw2;
		}WAVfact;
	}
}

namespace KoishiAvatar{
	using namespace Koishi;
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
#endif