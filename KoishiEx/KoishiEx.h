#ifndef KOISHI_EX_LIB
#define KOISHI_EX_LIB

#pragma once

#include <vector>
#include <string>
#include <math.h>
#pragma warning(disable:4018)			//无符号数与符号数直接进行操作
#pragma warning(disable:4244)			//不同类型数据之间的强制转换
#pragma warning(disable:4390)			//存在空的受控语句
#pragma warning(disable:4996)			//不安全的函数或变量


#define KOISHI_EX_VER		(double)1.1

#define MAX_UNCOMPRESSED_DATA_LENGTH	0x1000000

#define MIN(a,b) ((a)>(b)?b:a)
#define MAX(a,b) ((a)>(b)?a:b)

#define DEF_GETSET(_type, _member) public:_type _member;public:inline _type get_##_member() const{return _member;}inline _type*getPtr_##_member(){return &_member;}inline void set_##_member(_type val){_member=val;}


namespace Koishi{
	//定义基础数据
	typedef std::string	str;
	typedef unsigned char uchar;
	typedef unsigned short word;
	typedef unsigned long dword;
	typedef long long longex;
	typedef std::vector<long> queue;
	typedef std::vector<longex> queueex;

	//IMG版本号
	enum IMGversion{V1 = 1, V2 = 2, V4 = 4, V5 = 5, V6 = 6, OGG = -1, VUDEF = 0};
	//压缩格式
	enum compressType{COMP_NONE = 5, COMP_ZLIB = 6, COMP_ZLIB2 = 7, COMP_UDEF = 0};
	//颜色格式
	enum colorFormat{ARGB8888 = 0x10, ARGB4444 = 0x0F, ARGB1555 = 0x0E, LINK = 0x11, DDS_DXT1 = 0x12, DDS_DXT3 = 0x13, DDS_DXT5 = 0x14, COLOR_UDEF = 0, INDEX_FMT_PALETTE, RGB565};
	//混合模式
	enum colorMethod{LAY, DARKEN, MULTIPLY, COLORBURN, LINEARBURN, LIGHTEN, SCREEN, COLORDODGE, LINEARDODGE, OVERLAY, HARDLIGHT, SOFTLIGHT, VIVIDLIGHT, LINEARLIGHT, PINLIGHT, HARDMIX, DIFFER, EXCLUSION};
	//可修改图片索引项数据
	enum picChangablePara{LINKTO, BASEX, BASEY, FRAMEW, FRAMEH};
	//颜色属性 透明度·红色·绿色·蓝色·灰度·色调·饱和度·明度
	enum colorProperty{COLOR_ALPHA, COLOR_CHANNEL_RED, COLOR_CHANNEL_GREEN, COLOR_CHANNEL_BLUE, COLOR_GRAYSCALE, COLOR_HUE, COLOR_SATURATION, COLOR_VALUE};
	//图层叠放方式
	enum layerMethod{UPPER, LOWER};

	class stream;
	class color;
	class point;
	class size;
	class matrix;
	class palette;

	typedef std::vector<color> colorList;
	typedef std::vector<colorList> colorTable;
	///////////////////////////////////////
	//基本类:数据流
	///////////////////////////////////////
	class stream{
	public:
		stream();
		stream(longex _len);
		stream(const stream &_s);
		~stream();
		stream& operator = (const stream &_s);
	public:
		//分配空间
		void allocate(longex _len);
		void reallocate(longex _len);
		void release();
	public:
		//下标函数
		uchar& operator[] (longex _i) const;
		operator str();
		longex getLen() const;
		longex getMaxLen() const;
		longex getPtPos() const;
		longex ptMoveTo(longex pos);
		longex ptMove(longex dist);
	public:
		void clear();
		//插入数据
		uchar push(uchar d);
		uchar push(word d);
		uchar push(dword d);
		uchar push(longex d);
		uchar push(long i);
		//读取游标处数据
		uchar read(uchar &d);
		uchar read(word &d);
		uchar read(dword &d);
		uchar read(longex &d);
		uchar read(long &i);
		//插入字符串
		uchar pushString(str s);
		//读取字符串
		str readString(dword l);
		//插入另一个数据流
		uchar pushStream(const stream &s, longex l);
		//从游标处读取l个字节到dest
		void readStream(stream &dest, longex l);
		//中间位置插入另一个数据流
		void insertStream(const stream &s, longex l, longex pos);
		//删除数据流
		void deleteStream(longex pos, longex l);
		//更改指定位置的一个字节
		bool modify(longex pos, uchar d);
		//更改指定位置的一个整型
		bool modify(longex pos, long i);
		//替换数据
		longex replace(const uchar &whos, const uchar &to);
	public:
		//将数据流存储成文件
		bool makeFile(str fileName);
		//读取文件到数据流
		bool loadFile(str fileName);
	public:
		//NPK名字文件掩码
		void nameMask();
		//对数据流进行type所示压缩，并存储到dest中
		int compressData(stream &dest, compressType type);
		//对数据流进行type所示解压，并存储到dest中，成功返回0，数据错误返回-3，tryLength不够返回-5
		int uncompressData(stream &dest, compressType type, longex tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
		//对数据流进行SHA256加密，并将32字节数存储到dest中
		void getSHA256(stream &dest);
		//对数据流追加另一段数据流后修正为17的整数倍，并进行SHA256加密（为NPK准备）
		void getSHA256(stream &dest, const stream &added);
	public:
		//查找相连的一串数据流
		longex findStream(const stream &s, longex startPos = 0);
		//获取被指定数据流分割的字符串的起始位置和长度，返回分割数（空流也算）
		longex splitStream(const stream &s, queueex &posList, queueex &lenList);
		//进行BZ2压缩
		int BZcompress(stream &dest);
		//进行BZ2解压
		int BZdecompress(stream &dest);

	public:
		uchar *data;
		longex len,maxLen,pt;
	};
	///////////////////////////////////////
	//基本类:颜色的HSV信息
	///////////////////////////////////////
	typedef struct colorHSV{
		long H;
		double S;
		double V;
	}colorHSV;
	///////////////////////////////////////
	//基本类:颜色的RGB信息
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
		//灰度
		color gray() const;
		double getProperty(colorProperty theProperty) const;
		//颜色混合
		double mixMethod(double a,double b, colorMethod _method);
		uchar mixMethod(uchar a,uchar b, colorMethod _method);
		void mixWith(const color &_clr2, colorMethod _method = LAY);
		color mix(const color &_clr1, const color &_clr2, colorMethod _method = LAY);
	public:
		//HSV操作
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
		//计算两个颜色的欧氏距离的平方
		static int EuclideanDistanceSquareOf(const color &a, const color &b);
		//平分颜色空间后计算颜色
		static color lose(const color &c, uchar part);
		static color loseBit(const color &c, uchar bit);
		//伽马变换
		static color loseBlack(const color &c, uchar gamma);
	};
	///////////////////////////////////////
	//基本类:坐标点·尺寸
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
	//基本类:矩阵，当R=G=B=0时，可以用做索引矩阵用
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
		//内存分配
		bool valid();
		void create(dword _row, dword _column);
		void create(const size &_sz);
		void destory();
		void fill(color clr);
		void push(color clr);									//游标处颜色赋值并加1
		longex push(const stream &_s, colorFormat cf = ARGB8888);	//以流填充，当cf为INDEX_FMT_PALEETE时作为索引矩阵处理
		longex make(stream &s, colorFormat cf = ARGB8888) const;	//制作数据流，当cf为INDEX_FMT_PALEETE时作为索引矩阵处理
	public:
		//取值/行列
		color* operator[] (dword _i) const;		//重写双下标函数
		long getHeight() const;
		long getWidth() const;
		long getElemCount() const;
		//元素统计
		void setElem(dword r, dword c, const color &clr);
		void setElem(dword id, const color &clr);
		color getElem(dword r, dword c) const;			//取像素点
		color getElem(dword id) const;						//取像素点
		long getElemCountNzero() const;						//统计实体像素个数
		long getElemCountWhos(const color &whos) const;		//统计颜色值等于whos的像素个数
		void getElemCountList(colorList &getColorList) const;			//统计所有出现的颜色
		void getElemHonzBound(dword &lower, dword &upper) const;	//统计带有实体像素的水平边界
		void getElemVertBound(dword &lower, dword &upper) const;	//统计带有实体像素的垂直边界
	public:
		//操作矩阵
		long moveHonz(long dist, const color &surplus = color(0,0,0,0));		//非0元素水平移动
		long moveVert(long dist, const color &surplus = color(0,0,0,0));		//非0元素垂直移动
		long replace(const color &whos, const color &to);//将指定颜色的所有像素变更为目标颜色
		void putFore(const matrix &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//以此矩阵为底层，画上目标矩阵
		void putBack(const matrix &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//以此矩阵为顶层，在其底下画上目标矩阵
	public:
		//以此矩阵为基准计算其他矩阵
		void clip(matrix &dest, dword rowStart, dword rowEnd, dword columnStart, dword columnEnd) const;//裁剪
		void expand(matrix &dest, dword toTop, dword toBottom, dword toLeft, dword toRight) const;		//扩充
		void zoom(matrix &dest, double ratio) const;			//缩放
		void zoom(matrix &dest, double honzRatio, double vertRatio) const;	//缩放

		void clip(dword rowStart, dword rowEnd, dword columnStart, dword columnEnd);
		void expand(dword toTop, dword toBottom, dword toLeft, dword toRight);		//扩充
		void zoom(double ratio);			//缩放
		void zoom(double honzRatio, double vertRatio);	//缩放
	public:
		//颜色操作
		void lose(uchar fine); //扔通道
		void loseBit(uchar bit); //扔位
		void loseBlack(uchar gamma); //去黑底
		void turnShield();			//将实色色部分变为1/2透明的白色
	public:
		//绘制操作
		void line(point p1, point p2, const color &clr);
		void rectangle(point p1, point p2, const color &clr);
		void filledRectangle(point p1, point p2, const color &clr);
		void filledLattice(point p1, point p2, const color &clr1, const color &clr2, long size);
	public:
		bool loadPNG(str fileName);
		bool makePNG(str fileName);
	protected:
		color *data;
		dword column, row, pt;
	};
	//调色板
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
		//对单个调色板操作
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
	//////工厂类////////////////////////
	class NPKobject;		//整个NPK块
	class IMGobject;		//IMG块
	//////结构体//////////////////////
	class IMGindex;			//IMG的索引项
	class PICinfo;			//PIC数据
	class TEXinfo;			//DDS数据
	typedef std::vector<IMGindex> IMGcontent;
	typedef std::vector<PICinfo> PIClist;
	typedef std::vector<TEXinfo> TEXlist;
	///////////////////////////////////
	class IMGindex{
		//IMG索引数据
	public:
		dword imgoffset, imgsize;
		str imgname;
	public:
		IMGindex();
	};
	class PICinfo{
		//图像信息
		DEF_GETSET(colorFormat,format);
		DEF_GETSET(compressType,comp);
		DEF_GETSET(dword,dataSize);
		DEF_GETSET(point,basePt);
		DEF_GETSET(size,picSize);
		DEF_GETSET(size,frmSize);
		DEF_GETSET(long,linkTo);
		//双索引模式
		DEF_GETSET(dword,TEXusing);
		DEF_GETSET(point,TEXpointLT);
		DEF_GETSET(point,TEXpointRB);
	public:
		PICinfo();
	};
	class TEXinfo{
		//纹理集信息
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
		bool loadIndex(const str &fileName, std::vector<IMGversion> &versionList);	//仅读取版本
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
		bool extractIMGFile(long pos, str fileName);
	public:
		dword count;
		IMGcontent content;
	protected:
		//Data分四个区域：文件头、IMG索引表、校验位、IMG文件
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
		stream dataHeader;		//文件头（V2,V4,V6为一组,V5为一组）
		stream dataPalette;		//调色板数据
		stream dataIndexTexture;//DDS信息，V5之外无效
		stream dataIndexPicture;//图像信息
		stream dataTexture;		//DDS图像数据，V5之外无效
		stream dataPicture;		//图像数据
	};
}

namespace KoishiExpand{
	using namespace Koishi;
	//扩展功能
	namespace KoishiMarkTool{
		//字体点阵
		extern void CharMat(char p, matrix &mat, color clr = color(0xff,0,0,0));
		extern void StrMat(str s, matrix &mat, color clr = color(0xff,0,0,0));
		extern void CharMatLarge(char p, matrix &mat, color clr = color(0xff,0,0,0));
		extern void StrMatLarge(str s, matrix &mat, color clr = color(0xff,0,0,0));
		//旧时装打标器·会自动选择打标地点
		extern bool AvatarMarking(str avatarNPKfileName);
		extern bool AvatarBatchMarking(str avatarNPKfileListName);
		//对任意图片打标，situ = 1 上方外侧；situ = 2 右方外侧
		extern bool MatrixMarking(const matrix &sourceMatrix, matrix &destMatrix, str codeString, int situ);
		extern bool MatrixMarking(const matrix &sourceMatrix, matrix &destMatrix, str codeString, point deltaPoint, color textColor);
		extern bool MatrixShowcasing(const matrix &sourceMatrix, matrix &destMatrix, int num, int size = 100);
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
	class Indexing{
	//索引化
	public:
		Indexing();
		void input(const Koishi::IMGobject &in);
		void input(const str imgName);
		void output(Koishi::IMGobject &out);
		void output(const str imgName);
		volatile int millages;		//千分之……
	private:
		void deal(Koishi::IMGobject &goal, int colorCount = 0xFF);
		Koishi::IMGobject io;
	};
	class IMGobjectV1{
	//旧版本IMGV1
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
	namespace KoishiImageTool{
		//extern colorList pickColor(const matrix &mat);				//提取颜色
		//extern colorList joinColor(const colorList &otherList);		//融合颜色
		//extern colorList sortColor(const colorList &otherList);		//排序算法
		//extern int EuclideanDistance(const color &clr1, const color &clr2);	//欧氏距离
		//extern void indexing(const matrix &source, matrix &indexed, const colorList &paletteColor);	//匹配算法
		extern color gradient(const color &sourceColor, const colorList &keyColorList, Koishi::colorProperty cp);			//根据颜色性质
	}
}

namespace KoishiAvatar{
	using namespace Koishi;
	enum avatarCareer{ACAREER_UD, ACAREER_SM, ACAREER_SG, ACAREER_FT, ACAREER_FM, ACAREER_GN, ACAREER_GG, ACAREER_MG, ACAREER_MM, ACAREER_PR, ACAREER_PG, ACAREER_TH, ACAREER_KN, ACAREER_DL, ACAREER_GB, ACAREER_MAXCOUNT};
	enum avatarPart{APART_UD, APART_CAP, APART_HAIR, APART_FACE, APART_NECK, APART_COAT, APART_PANTS, APART_BELT, APART_SHOES, APART_BODY, APART_MAXCOUNT, APART_WEAPON};
	enum avatarLayer{ALAYER_UD, ALAYER_A, ALAYER_A1, ALAYER_A2, ALAYER_B, ALAYER_B1, ALAYER_B2, ALAYER_C, ALAYER_C1, ALAYER_C2, ALAYER_D, ALAYER_D1, ALAYER_D2,	ALAYER_E, ALAYER_E1, ALAYER_E2,	ALAYER_F, ALAYER_F1, ALAYER_F2,	ALAYER_G, ALAYER_G1, ALAYER_G2,	ALAYER_H, ALAYER_H1, ALAYER_H2, ALAYER_X, ALAYER_X1, ALAYER_X2, ALAYER_MAXCOUNT};
	enum {TOTAL_LAYER_COUNT = 63};
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
		str resoucePath;
		avatarCareer career;
		avatarPart part;
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
#endif