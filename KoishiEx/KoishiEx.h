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

#define MIN(a,b) ((a)>(b)?b:a)
#define MAX(a,b) ((a)>(b)?a:b)

#define DEF_GETSET(_type, _member) protected:_type _member;public:inline _type get_##_member() const{return _member;}inline _type*getPtr_##_member(){return &_member;}inline void set_##_member(_type val){_member=val;}


namespace Koishi{
	//���ֶ���
	typedef std::string				str;
	typedef float					fl1;
	typedef double					fl2;
	typedef unsigned char			b8,			*pb8;
	typedef unsigned short			b16,		*pb16;
	typedef unsigned long			b32,		*pb32;
	typedef unsigned long long		b64,		*pb64;
	typedef signed char				i8,			*pi8;
	typedef short					i16,		*pi16;
	typedef long					i32,		*pi32;
	typedef long long				i64,		*pi64;
	typedef std::vector<b8>			lb8;
	typedef std::vector<b16>		lb16;
	typedef std::vector<b32>		lb32;
	typedef std::vector<b64>		lb64;
	typedef std::vector<i8>			li8;
	typedef std::vector<i16>		li16;
	typedef std::vector<i32>		li32;
	typedef std::vector<i64>		li64;
	extern str NPKheaderStr;
	extern str IMGheaderStr;
	extern str IMGheaderStr2;
	extern str NPKext;
	extern str IMGext;
	extern str IMGnameMask;
	//IMG�汾��
	enum IMGversion{V1 = 1, V2 = 2, V4 = 4, V5 = 5, V6 = 6, OGG = -1, VUDEF = 0};
	//ѹ����ʽ
	enum compressType{COMP_NONE = 5, COMP_ZLIB = 6, COMP_ZLIB2 = 7, COMP_UDEF = 0};
	//��ɫ��ʽ
	enum colorFormat{ARGB8888 = 0x10, ARGB4444 = 0x0F, ARGB1555 = 0x0E, LINK = 0x11, DDS_DXT1 = 0x12, DDS_DXT3 = 0x13, DDS_DXT5 = 0x14, COLOR_UDEF = 0, INDEX_FMT_PALETTE, RGB565};
	//���ģʽ
	enum colorMethod{LAY, DARKEN, MULTIPLY, COLORBURN, LINEARBURN, LIGHTEN, SCREEN, COLORDODGE, LINEARDODGE, OVERLAY, HARDLIGHT, SOFTLIGHT, VIVIDLIGHT, LINEARLIGHT, PINLIGHT, HARDMIX, DIFFER, EXCLUSION};
	//���޸�ͼƬ����������
	enum picChangablePara{LINKTO, BASEX, BASEY, FRAMEW, FRAMEH};
	//��ɫͨ��
	enum channelFlag{FA = 0x01, FR = 0x02, FG = 0x04, FB = 0x08};
	//ͼ����ŷ�ʽ
	enum layerMethod{UPPER, LOWER};
	class stream;
	class color;
	class point;
	class size;
	class matrix;
	class palette;
	typedef stream *pstream;
	typedef color *pcolor;
	typedef point *ppoint;
	typedef size *psize;
	typedef std::vector<color> lcolor;
	typedef std::vector<lcolor> llcolor;
	///////////////////////////////////////
	//������:������
	///////////////////////////////////////
	class stream{
	public:
		stream();
		stream(b64 _len);
		stream(const stream &_s);
		~stream();
		stream& operator = (const stream &_s);
	public:
		//����ռ�
		void allocate(b64 _len);
		//���·���ռ�
		void reallocate(b64 _len);
		//�ͷſռ�
		void release();
	public:
		//�±꺯��
		b8& operator[] (b64 _i) const;
		//ת��Ϊ�ַ���
		operator str();
		//�����Ч���ݳ���
		b64 getLen() const;
		//��÷��䳤��
		b64 getMaxLen() const;
		//����α�λ��
		b64 ptPos() const;
		//�α��ƶ�������
		b64 ptMoveTo(i64 pos);
		//�α��ƶ�
		b64 ptMove(i64 dist);
	public:
		//��Ч���ݳ������㣬�����ͷſռ�
		void clear();
		//��������
		b8 push(b8 d);
		b8 push(b16 d);
		b8 push(b32 d);
		b8 push(b64 d);
		b8 push(i32 i);
		//��ȡ�α괦����
		b8 read(b8 &d);
		b8 read(b16 &d);
		b8 read(b32 &d);
		b8 read(b64 &d);
		b8 read(i32 &i);
		//�����ַ���
		b8 pushString(str s);
		//��ȡ�ַ���
		str readString(b32 l);
		//������һ��������
		b8 pushStream(const stream &s, b64 l);
		//���α괦��ȡl���ֽڵ�dest
		void readStream(stream &dest, b64 l);
		//�м�λ�ò�����һ��������
		void insertStream(const stream &s, b64 l, b64 pos);
		//ɾ��������
		void deleteStream(b64 pos, b64 l);
		//����ָ��λ�õ�һ���ֽ�
		bool modify(b64 pos, b8 d);
		//����ָ��λ�õ�һ������
		bool modify(b64 pos, i32 i);
		//�滻����
		b64 replace(const b8 &whos, const b8 &to);
	public:
		//���������洢���ļ�
		bool makeFile(str fileName);
		//��ȡ�ļ���������
		bool loadFile(str fileName);
	public:
		//NPK�����ļ�����
		void nameMask();
		//������������type��ʾѹ�������洢��dest��
		i8 compressData(stream &dest, compressType type);
		//������������type��ʾ��ѹ�����洢��dest�У��ɹ�����0�����ݴ��󷵻�-3��tryLength��������-5
		i8 uncompressData(stream &dest, compressType type, b64 tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
		//������������SHA256���ܣ�����32�ֽ����洢��dest��
		void getSHA256(stream &dest);
		//��������׷����һ��������������Ϊ17����������������SHA256���ܣ�ΪNPK׼����
		void getSHA256(stream &dest, const stream &added);
	public:
		//����������һ��������
		i64 findStream(const stream &s, b64 startPos = 0);
		//��ȡ��ָ���������ָ���ַ�������ʼλ�úͳ��ȣ����طָ���������Ҳ�㣩
		b64 splitStream(const stream &s, lb64 &posList, lb64 &lenList);
		//����BZ2ѹ��
		i8 BZcompress(stream &dest);
		//����BZ2��ѹ
		i8 BZdecompress(stream &dest);

	public:
		pb8 data;
		b64 len,maxLen,pt;
	};
	///////////////////////////////////////
	//������:��ɫ��HSV��Ϣ
	///////////////////////////////////////
	typedef struct colorHSV{
		i32 H;
		fl2 S;
		fl2 V;
	}colorHSV;
	///////////////////////////////////////
	//������:��ɫ��RGB��Ϣ
	///////////////////////////////////////
	class color{
		DEF_GETSET(b8,A);
		DEF_GETSET(b8,R);
		DEF_GETSET(b8,G);
		DEF_GETSET(b8,B);
	public:
		color();
		color(b32 colorDt, colorFormat clrFmt = ARGB8888);
		color(b8 r, b8 g, b8 b);
		color(b8 a, b8 r, b8 g, b8 b);
		void set(b32 colorDt, colorFormat clrFmt = ARGB8888);
		void make(b32 &colorDt, colorFormat clrFmt = ARGB8888);
		operator b32() const;
	public:
		//��ɫͨ��
		color getChannel(b8 _chn) const;
		//��ɫ���
		fl2 mixMethod(fl2 a,fl2 b, colorMethod _method);
		b8 mixMethod(b8 a,b8 b, colorMethod _method);
		void mixWith(const color &_clr2, colorMethod _method = LAY);
		color mix(const color &_clr1, const color &_clr2, colorMethod _method = LAY);
	public:
		//HSV����
		void getHSV(colorHSV &hsv) const;
		void useHSV(const colorHSV &hsv);
		void moveHto(i32 newH);
		void moveSto(fl2 newS);
		void moveVto(fl2 newV);
		void moveH(i32 delta);
		void moveS(fl2 delta);
		void moveV(fl2 delta);
		void moveRto(b8 newR);
		void moveGto(b8 newG);
		void moveBto(b8 newB);
		void moveR(i16 delta);
		void moveG(i16 delta);
		void moveB(i16 delta);
		void moveA(i16 delta);
	public:
		//����������ɫ��ŷ�Ͼ����ƽ��
		static int EuclideanDistanceSquareOf(const color &a, const color &b);
		//ƽ����ɫ�ռ�������ɫ
		static color lose(const color &c, b8 part);
		static color loseBit(const color &c, b8 bit);
		//٤��任
		static color loseBlack(const color &c, b8 gamma);
	};
	///////////////////////////////////////
	//������:�����
	///////////////////////////////////////
	class point{
		DEF_GETSET(i32,X);
		DEF_GETSET(i32,Y);
	public:
		point();
		point(i32 x, i32 y);
		void set(i32 x, i32 y);
		void moveHonz(i32 dist);
		void moveVert(i32 dist);
		void move(i32 honzDist, i32 vertDist);
		void move(size sz);
	};
	///////////////////////////////////////
	//������:�ߴ�
	///////////////////////////////////////
	class size{
		DEF_GETSET(i32,W);
		DEF_GETSET(i32,H);
	public:
		size();
		size(i32 w, i32 h);
		void set(i32 w, i32 h);
		i32 area() const;
	};
	///////////////////////////////////////
	//������:��ɫ����
	//��R=G=B=0ʱ��������������������
	///////////////////////////////////////
	class matrix{
	public:
		matrix();
		matrix(b32 _row, b32 _column);
		matrix(const size &_sz);
		matrix(const matrix &_mat);
		~matrix();
		matrix& operator = (const matrix &_mat);

	public:
		//�ڴ����
		bool valid();
		void allocate(b32 _row, b32 _column);
		void allocate(const size &_sz);
		void release();
		void fill(color clr);
		void push(color clr);									//�α괦��ɫ��ֵ����1
		b64 push(const stream &_s, colorFormat cf = ARGB8888);	//������䣬��cfΪINDEX_FMT_PALEETEʱ��Ϊ����������
		b64 make(stream &s, colorFormat cf = ARGB8888) const;	//��������������cfΪINDEX_FMT_PALEETEʱ��Ϊ����������
	public:
		//ȡֵ/����
		pcolor operator[] (b32 _i) const;		//��д˫�±꺯��
		b32 getRowCount() const;
		b32 getColumnCount() const;
		b32 getElemCount() const;
		//ȡ����
		void getSubMatrix(matrix &dest, b32 rowStart, b32 rowEnd, b32 columnStart, b32 columnEnd) const;
		void getChannelMatrix(matrix &dest, b8 _chn = FA) const;
		//�������
		void expandMatrix(matrix &dest, b32 toTop, b32 toBottom, b32 toLeft, b32 toRight) const;
		//Ԫ��ͳ��
		void setElem(b32 r, b32 c, const color &clr);
		void setElem(b32 id, const color &clr);
		color getElem(b32 r, b32 c) const;			//ȡ���ص�
		color getElem(b32 id) const;						//ȡ���ص�
		b32 getElemCountNzero() const;						//ͳ��ʵ�����ظ���
		b32 getElemCountWhos(const color &whos) const;		//ͳ����ɫֵ����whos�����ظ���
		void getElemCountList(lcolor &colorList) const;			//ͳ�����г��ֵ���ɫ
		void getElemHonzBound(b32 &lower, b32 &upper) const;	//ͳ�ƴ���ʵ�����ص�ˮƽ�߽�
		void getElemVertBound(b32 &lower, b32 &upper) const;	//ͳ�ƴ���ʵ�����صĴ�ֱ�߽�
	public:
		//��������
		i32 elemMoveHonz(i32 dist);							//��0Ԫ��ˮƽ�ƶ�
		i32 elemMoveVert(i32 dist);							//��0Ԫ�ش�ֱ�ƶ�
		i32 elemReplace(const color &whos, const color &to);//��ָ����ɫ���������ر��ΪĿ����ɫ
		void putFore(const matrix &layer, colorMethod _met = LAY);	//��ǰ��
		void putBack(const matrix &layer, colorMethod _met = LAY);	//�̱���
		void lose(b8 fine); //��ͨ��
		void loseBit(b8 bit); //��λ
		void loseBlack(b8 gamma); //ȥ�ڵ�
	public:
		bool loadPNG(str fileName);
		bool makePNG(str fileName);
	protected:
		pcolor data;
		b32 column, row, pt;
	};
	//��ɫ��
	class palette{
	public:
		palette();
		~palette();
	public:
		lcolor& operator[] (i32 i);
		void clear();
		void push(lcolor colorList);
		i32 getCount() const;
		i32 getTotalColorCount() const;
	public:
		//�Ե�����ɫ�����
		i32 getColorCount(i32 paletteID = 0) const;
		i32 findColor(color goalColor, i32 paletteID = 0) const;
		bool joinWith(const lcolor &colorList, i32 paletteID = 0);
	public:
		bool tinyMake(stream &s, i32 paletteID = 0);
		bool bigMake(stream &s);
	public:
		static bool makeACT(str fileName, const lcolor &lc);
		static bool loadACT(str fileName, lcolor &lc);
	protected:
		llcolor table;
	};
	//////������////////////////////////
	class NPKobject;		//����NPK��
	class IMGobject;		//IMG��
	//////�ṹ��//////////////////////
	class IMGindex;			//IMG��������
	class PICinfo;			//PIC����
	class TEXinfo;			//DDS����
	typedef std::vector<IMGindex> IMGcontent;
	typedef std::vector<IMGobject> IMGlist;
	typedef std::vector<PICinfo> PIClist;
	typedef std::vector<TEXinfo> TEXlist;
	///////////////////////////////////
	class IMGindex{
		//IMG��������
		DEF_GETSET(b32,imgoffset);		//�׵�ַƫ����
		DEF_GETSET(b32,imgsize);		//IMG��С
		DEF_GETSET(str,imgname);		//IMG·����
	public:
		IMGindex();
	};
	class PICinfo{
		//ͼ����Ϣ
		DEF_GETSET(colorFormat,format);
		DEF_GETSET(compressType,comp);
		DEF_GETSET(b32,dataSize);
		DEF_GETSET(point,basePt);
		DEF_GETSET(size,picSize);
		DEF_GETSET(size,frmSize);
		DEF_GETSET(i32,linkTo);
		//˫����ģʽ
		DEF_GETSET(b32,TEXusing);
		DEF_GETSET(point,TEXpointLT);
		DEF_GETSET(point,TEXpointRB);
	public:
		PICinfo();
	};
	class TEXinfo{
		//������Ϣ
		DEF_GETSET(colorFormat,format);
		DEF_GETSET(b32,ID);
		DEF_GETSET(b32,compressedLength);
		DEF_GETSET(b32,dataLength);
		DEF_GETSET(b32,width);
		DEF_GETSET(b32,height);
		DEF_GETSET(b32,reserved);
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
		i32 getVersion(i32 pos);
	public:
		bool IMGpush(IMGobject &obj, const str &imgName);
		bool IMGinsert(i32 pos, IMGobject &obj, const str &imgName);
		bool IMGremove(i32 pos);
		bool IMGreplace(i32 pos, IMGobject &obj);
		bool IMGrename(i32 pos, const str &newName);
	public:
		stream *getData(b8 part);
		b64 getSize() const;
		bool IMGextract(b32 pos, IMGobject &obj);
		bool IMGfind(const str &keyword, b32 &pos);
		bool IMGfind(const str &keyword, const str &nonkeyword, b32 &pos);
		bool extractIMGFile(i32 pos, str fileName);
	public:
		b32 count;
		IMGcontent content;
	protected:
		//Data���ĸ������ļ�ͷ��IMG������У��λ��IMG�ļ�
		stream data1;
		stream data2;
		stream data3;
		stream data4;
	};
	/////////////////////////////////////
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
		bool PICgetInfo(i32 pos, PICinfo &info);		//��ȡ��������Ϣ
		bool PICgetInfoOffset(i32 pos, b64 &off);		//��ȡ������ƫ����
		bool PICgetData(i32 pos, stream &s);			//��ȡͼƬ������
		bool PICgetDataOffset(i32 pos, b64 &off);		//��ȡͼƬ������ƫ����
		bool PICpush(const PICinfo &info, const stream &s);				//����ͼƬ
		bool PICinsert(i32 pos, const PICinfo &info, const stream &s);	//����ͼƬ������
		bool PICremove(i32 pos);										//ɾ��ͼƬ
		bool PICreplace(i32 pos, const PICinfo &info, const stream &s);	//�滻ͼƬ
		bool PICextract(i32 pos, matrix &mat, i32 paletteID = 0);		//��ȡͼƬ
		bool PICpreprocess(const matrix &mat, stream &s, PICinfo &info, colorFormat cf = COLOR_UDEF);//Ԥ����ͼƬ
		bool PICextractIndexMatrix(i32 pos, matrix &mat);										//��ȡ�ľ�������������
		bool PICpreprocessIndexMatrix(const matrix &mat, stream &s, PICinfo &info);			//�����������ݵľ����IMG����Ԥ����
		bool PICempty(stream &s, PICinfo &info);						//�Կ�֡Ԥ����ͼƬ
		bool PICsetInfoPara(i32 pos, i32 term, void *pval);		//������������Ϣ
		//��������
		bool TEXgetInfo(i32 pos, TEXinfo &info);		//��ȡ������������Ϣ
		bool TEXgetInfoOffset(i32 pos, b64 &off);		//��ȡ����������ƫ����
		bool TEXgetData(i32 pos, stream &s);			//��ȡ��������
		bool TEXgetDataOffset(i32 pos, b64 &off);		//��ȡ��������ƫ����
		
		bool TEXpush(const TEXinfo &info, const stream &s);
		bool TEXinsert(i32 pos, const TEXinfo &info, const stream &s);
		bool TEXremove(i32 pos);
		bool TEXreplace(i32 pos, const TEXinfo &info, const stream &s);
		bool TEXextract(i32 pos, matrix &mat);
		bool TEXpreprocess(const matrix &mat, stream &s, TEXinfo &info, colorFormat cf = COLOR_UDEF);
		//��ɫ����
		bool CLRpush(const color &clr, i32 paletteID = 0);
		bool CLRinsert(i32 pos, const color &clr, i32 paletteID = 0);
		bool CLRremove(i32 pos, i32 paletteID = 0);
		bool CLRreplace(i32 pos, const color &clr, i32 paletteID = 0);
		bool CLRnewPalette();
		//ת��
		bool convertTo(
			IMGobject &newIO,				//ת����IMG������
			IMGversion newVersion,			//ת����IMG�İ汾
			colorFormat cf = COLOR_UDEF,	//��ɫ��ʽ
			i32 palettedID = 0,				//ԭIMGΪV6ʱ��ȡ��ɫ�����
			b8 indexPara = 0,				//ת��Ϊ����ͼ��ʱ��������ɫ��������
			bool makeTexture = false		//ת��ΪV5ʱ���Ƿ���������
		);
		//��������
		i32 linkFind(b32 pos, b32 depth = 5);		//��������֡����ָ��depthΪ��ȣ�
		b64 getSize() const;
	public:
		IMGindex *derived;

		IMGversion version;
		b32 indexCount, indexSize;
		b32 V5_TEXCount;
		b32 V5_totalLength;

		palette paletteData;
		TEXlist TEXcontent;
		PIClist PICcontent;
	protected:
		stream *getData(b8 _part);
		stream data1;		//�ļ�ͷ��V2,V4,V6Ϊһ��,V5Ϊһ�飩
		stream data2;		//��ɫ������
		stream data3;		//DDS��Ϣ��V5֮����Ч
		stream data4;		//ͼ����Ϣ
		stream data5;		//DDSͼ�����ݣ�V5֮����Ч
		stream data6;		//ͼ������
	};
}

namespace KoishiExpand{
	//��չ����
	//ʱװ���
	extern void CharMat(char p, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern void StrMat(std::string str, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern void CharMat2(char p, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern void StrMat2(std::string str, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern bool AvatarMarking(std::string avatarNPKfileName);
	extern bool AvatarBatchMarking(std::string avatarNPKfileListName);
	//����NPK���(�Ҳ����IMG·������֡��)
	extern bool IMGMarking(Koishi::IMGobject &io, std::string customMark = "", bool usingCustom = false, bool addedFrameID = true);
	extern bool NPKMarking(std::string NPKfileName);
	//ǿ��ת����ͼ��
	class Indexing{
	public:
		Indexing();
		void input(const Koishi::IMGobject &in);
		void input(const std::string imgName);
		void output(Koishi::IMGobject &out);
		void output(const std::string imgName);
		volatile int millages;		//ǧ��֮����
	private:
		void deal(Koishi::IMGobject &goal, int colorCount = 0xFF);
		Koishi::IMGobject io;
	};
	/////////////////////////////////////////////////////
	//�������ļ�SPK����
	/////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////
	//�������ļ��б�LST����
	/////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////
	//��������ļ�TCT����
	/////////////////////////////////////////////////////
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
	class LSTfile2{
	public:
		unsigned char name[256];
		unsigned char lenStr[32];
		unsigned char hash[32];
		LSTfile2();
	};
	class LSTobject2{
	public:
		std::vector<LSTfile2>  list;
		bool load(const Koishi::str &fileName);
	};
	/////////////////////////////////////////////////////////
	//�ɰ�IMG(V1�汾)ת��
	/////////////////////////////////////////////////////////
	class OldIMGobject{
	protected:
		Koishi::PIClist PICcontent;
		Koishi::lb64 posList, lenList;
		Koishi::stream data;
	public:
		bool load(Koishi::stream &s);
		bool load(const Koishi::str &fileName);
		bool make(Koishi::IMGobject &io);
		bool release();
	};
	namespace KoishiImageTool{
		//��ɫ�ݶ�
		class gradient{
		public:
			gradient(unsigned int newRange = 0xFFFF);
		public:
			void setRange(unsigned int newRange = 0xFFFF);
			void addKey(Koishi::color newKeyColor, unsigned int situ);
			void deleteKey(unsigned int id);
			Koishi::color pick(unsigned int situ) const;
		protected:
			Koishi::lcolor keyColorList;
			std::vector<unsigned int> keyColorSection;
			unsigned int range;
		};
	}
}

#endif
