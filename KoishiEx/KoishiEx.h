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

#define unclared
#define declare_basefun(_member,_type) protected:_type _member;public:inline _type get_##_member() const{return _member;}inline _type*getPtr_##_member(){return &_member;}inline void set_##_member(_type val){_member=val;}


namespace Koishi{
	//各种定义
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
	enum IMGversion{V1 = 1, V2 = 2, V4 = 4, V5 = 5, V6 = 6, OGG = -1, VUDEF = 0};
	enum command{CREATE, LOAD, MAKE, RELEASE,PUSH, INSERT,REMOVE, REPLACE,RENAME};
	enum compressType{COMP_NONE = 5, COMP_ZLIB = 6, COMP_ZLIB2 = 7, COMP_UDEF = 0};
	enum DDSPixelFormatID{DXT1 = 0x12, DXT3=0x13, DXT5=0x14, DPF_UDF = 0};
	enum colorFormat{ARGB8888 = 0x10, ARGB4444 = 0x0F, ARGB1555 = 0x0E, LINK = 0x11, DDS_DXT1 = 0x12, DDS_DXT3 = 0x13, DDS_DXT5 = 0x14, COLOR_UDEF = 0, V4_FMT, RGB565};
	enum colorMethod{LAY, DARKEN, MULTIPLY, COLORBURN, LINEARBURN, LIGHTEN, SCREEN, COLORDODGE, LINEARDODGE, OVERLAY, HARDLIGHT, SOFTLIGHT, VIVIDLIGHT, LINEARLIGHT, PINLIGHT, HARDMIX, DIFFER, EXCLUSION};
	enum picChangablePara{LINKTO, BASEX, BASEY, FRAMEW, FRAMEH};
	enum channelFlag{FA = 0x01, FR = 0x02, FG = 0x04, FB = 0x08};
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
	//基本类
	///////////////////////////////////////
	class stream{
	public:
		stream();
		stream(b64 _len);
		stream(const stream &_s);
		~stream();
		stream& operator = (const stream &_s);
	public:
		void allocate(b64 _len);
		void reallocate(b64 _len);
		void release();
	public:
		b8& operator[] (b64 _i) const;
		operator str();
		b64 getLen() const;
		b64 getMaxLen() const;
		b64 ptPos() const;
		b64 ptMoveTo(i64 pos);
		b64 ptMove(i64 dist);
	public:
		//清除所有内容，并不释放空间
		void clear();
		b8 push(b8 _d);
		b8 push(b16 _d);
		b8 push(b32 _d);
		b8 push(b64 _d);
		b8 push(i32 _i);
		b8 read(b8 &_d);
		b8 read(b16 &_d);
		b8 read(b32 &_d);
		b8 read(b64 &_d);
		b8 read(i32 &_i);
		b8 pushString(str _s);
		str readString(b32 _len);
		b8 pushStream(const stream &_s, b64 _len);
		void readStream(stream &dest, b64 _len);
		void insertStream(const stream &_s, b64 _len, b64 _pos);
		void deleteStream(b64 _pos, b64 _len);
		bool modify(b64 _pos, b8 _d);
		bool modify(b64 _pos, i32 _i);
		b64 replace(const b8 &whos, const b8 &to);	//返回替换了多少个
	public:
		//将数据流存储成文件
		bool makeFile(str fileName);
		bool loadFile(str fileName);
	public:
		//NPK名字文件掩码
		void nameMask();
		//对数据流进行type所示压缩，并存储到dest中
		i8 compressData(stream &dest, compressType type);
		//对数据流进行type所示解压，并存储到dest中，成功返回0，数据错误返回-3，tryLength不够返回-5
		i8 uncompressData(stream &dest, compressType type, b64 tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
		//对数据流进行MD5加密，并将16字节数据存储到dest中
		unclared void getMD5(stream &dest);
		//对数据流进行SHA256加密，并将32字节数存储到dest中
		void getSHA256(stream &dest);
		void getSHA256(stream &dest, const stream &added);
	protected:
		pb8 data;
		b64 len,maxLen,pt;
	};
	/////////////////////////////////////
	typedef struct colorHSV{
		i32 H;
		fl2 S;
		fl2 V;
	}colorHSV;
	class color{
		declare_basefun(A,b8);
		declare_basefun(R,b8);
		declare_basefun(G,b8);
		declare_basefun(B,b8);
	public:
		color();
		color(b32 colorDt, colorFormat clrFmt = ARGB8888);
		color(b8 r, b8 g, b8 b);
		color(b8 a, b8 r, b8 g, b8 b);
		void set(b32 colorDt, colorFormat clrFmt = ARGB8888);
	public:
		color getChannel(b8 _chn) const;
		operator b32() const;
		fl2 mixMethod(fl2 a,fl2 b, colorMethod _method);
		b8 mixMethod(b8 a,b8 b, colorMethod _method);
		void mixWith(const color &_clr2, colorMethod _method = LAY);
		color mix(const color &_clr1, const color &_clr2, colorMethod _method = LAY);
	public:
		//HSV操作
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
	};
	////////////////////////////////////
	class point{
		declare_basefun(X,i32);
		declare_basefun(Y,i32);
	public:
		point();
		point(i32 x, i32 y);
		void set(i32 x, i32 y);
		void moveHonz(i32 dist);
		void moveVert(i32 dist);
		void move(i32 honzDist, i32 vertDist);
		void move(size sz);
	};
	class size{
		declare_basefun(W,i32);
		declare_basefun(H,i32);
	public:
		size();
		size(i32 w, i32 h);
		void set(i32 w, i32 h);
		i32 area() const;
	};
	//////////////////////////////////
	//static size operator - (const point& pt1, const point& pt2);
	//static point operator + (const point& pt1, const size& sz);
	//static point operator - (const point& pt1, const size& sz);
	/////////////////////////////////////
	class matrix{
	public:
		matrix();
		matrix(b32 _row, b32 _column);
		matrix(const size &_sz);
		matrix(const matrix &_mat);
		~matrix();
		matrix& operator = (const matrix &_mat);
	public:
		//内存分配
		void allocate(b32 _row, b32 _column);
		void allocate(const size &_sz);
		void release();
		void fill(color _clr);
		void push(color _clr);							//游标处颜色赋值并加1
		b64 push(const stream &_s, colorFormat cf = ARGB8888);		//以流填充
		b64 make(stream &_s) const;							//制作成ARGB8888流
	public:
		//取值/行列
		pcolor operator[] (b32 _i) const;		//重写双下标函数
		b32 getRowCount() const;
		b32 getColumnCount() const;
		b32 getElemCount() const;
		//取子阵
		void getSubMatrix(matrix &dest, b32 rowStart, b32 rowEnd, b32 columnStart, b32 columnEnd) const;
		void getChannelMatrix(matrix &dest, b8 _chn = FA) const;
		//扩充矩阵
		void expandMatrix(matrix &dest, b32 toTop, b32 toBottom, b32 toLeft, b32 toRight) const;
		//元素统计
		void setElem(b32 _row, b32 _column, const color &_clr);
		void setElem(b32 _id, const color &_clr);
		color getElem(b32 _row, b32 _column) const;			//取像素点
		color getElem(b32 _id) const;						//取像素点
		b32 getElemCountNzero() const;						//统计实体像素个数
		b32 getElemCountWhos(const color &whos) const;		//统计颜色值等于whos的像素个数
		void getElemCountList(lcolor &colorList) const;			//统计所有出现的颜色
		void getElemHonzBound(b32 &lower, b32 &upper) const;	//统计带有实体像素的水平边界
		void getElemVertBound(b32 &lower, b32 &upper) const;	//统计带有实体像素的垂直边界
	public:
		//操作矩阵
		i32 elemMoveHonz(i32 dist);							//非0元素水平移动
		i32 elemMoveVert(i32 dist);							//非0元素垂直移动
		i32 elemReplace(const color &whos, const color &to);//将指定颜色的所有像素变更为目标颜色
		void putFore(const matrix &layer, colorMethod _met = LAY);	//铺前景
		void putBack(const matrix &layer, colorMethod _met = LAY);	//铺背景
	public:
		bool loadPNG(str fileName);
		bool makePNG(str fileName);
	protected:
		pcolor data;
		b32 column, row, pt;
	};
	//调色板
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
		//对单个调色板操作
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
	//////工厂类////////////////////////
	class NPKobject;		//整个NPK块
	class IMGobject;		//IMG块
	//////结构体//////////////////////
	class IMGindex;			//IMG的索引项
	class PICinfo;			//PIC数据
	class DDSinfo;			//DDS数据
	typedef std::vector<IMGindex> IMGcontent;
	typedef std::vector<IMGobject> IMGlist;
	typedef std::vector<PICinfo> PIClist;
	typedef std::vector<DDSinfo> DDSlist;
	///////////////////////////////////
	class IMGindex{
		//IMG索引数据
		declare_basefun(imgoffset,b32);
		declare_basefun(imgsize,b32);
		declare_basefun(imgname,str);
	public:
		IMGindex();
	};
	class PICinfo{
		//图像信息
		declare_basefun(format, colorFormat);
		declare_basefun(comp, compressType);
		declare_basefun(dataSize, b32);
		declare_basefun(basePt, point);
		declare_basefun(picSize, size);
		declare_basefun(frmSize, size);
		declare_basefun(linkTo, i32);
		//V5独有
		declare_basefun(DDSIDused, b32);
		declare_basefun(DDSpointLT, point);
		declare_basefun(DDSpointRB, point);
	public:
		PICinfo();
	};
	class DDSinfo{
		declare_basefun(fourCCID, DDSPixelFormatID);
		declare_basefun(DDSID, b32);
		declare_basefun(lengthOfCompressed, b32);
		declare_basefun(lengthOfDDS, b32);
		declare_basefun(width, b32);
		declare_basefun(height, b32);
		declare_basefun(reserved, b32);
	public:
		DDSinfo();
	};
	class NPKobject{
	public:
		NPKobject();
		NPKobject(const stream &_s);
		NPKobject(const str &fileName);
		bool load(const stream &_s);
		bool make(stream &_s);
		bool loadFile(const str &fileName);
		bool saveFile(const str &fileName);
		bool create();
		bool release();
		bool loadIndex(const str &fileName, std::vector<IMGversion> &versionList);
	public:
		bool IMGpush(const IMGobject &obj, const str &imgName);
		bool IMGinsert(i32 pos, const IMGobject &obj, const str &imgName);
		bool IMGremove(i32 pos);
		bool IMGreplace(i32 pos, const IMGobject &obj);
		bool IMGrename(i32 pos, const str& newName);
	public:
		pstream getData(b8 part);
		b64 getSize() const;
		bool IMGextract(b32 pos, IMGobject &obj);
		bool IMGfind(const str &keyword, b32 &pos);
		bool extractIMGFile(i32 pos, str fileName);
	public:
		b32 count;
		IMGcontent content;
	protected:
		//Data分四个区域：文件头、IMG索引表、校验位、IMG文件
		stream data1, data2, data3, data4;
		bool invoke(b16 command, void *para1 = NULL, void *para2 = NULL, void *para3 = NULL);
	
	};
	/////////////////////////////////////
	class IMGobject{
	public:
		IMGobject();
		IMGobject(stream &s);
		IMGobject(const str &fileName);
		~IMGobject();
		bool LoadFile(str fileName);			//从文件中读取
		bool SaveFile(str fileName);			//保存文件
		bool Load(stream &s);
		bool Make(stream &s);
		bool Create(IMGversion ver);
		bool Release();
		bool GetPICInfo(i32 pos, PICinfo &info);		//
		bool GetPICInfoOffset(i32 pos, b64 &off);
		bool GetPICData(i32 pos, stream &s);
		bool GetPICDataOffset(i32 pos, b64 &off);
		bool GetDDSInfo(i32 pos, DDSinfo &info);
		bool GetDDSInfoOffset(i32 pos, b64 &off);
		bool GetDDSData(i32 pos, stream &s);
		bool GetDDSDataOffset(i32 pos, b64 &off);
		bool SetPICInfoPara(i32 pos, i32 term, void *pval);
		bool PICpush(const PICinfo &info, const stream &s);
		bool PICinsert(i32 pos, const PICinfo &info, const stream &s);
		bool PICremove(i32 pos);
		bool PICreplace(i32 pos, const PICinfo &info, const stream &s);
		bool PICextract(i32 pos, matrix &mat, i32 paletteID = 0);
		bool PICpreprocess(const matrix &mat, stream &s, PICinfo &info);
		bool PICempty(stream &s, PICinfo &info);
		bool DDSpush(const DDSinfo &info, const stream &s);
		bool DDSinsert(i32 pos, const DDSinfo &info, const stream &s);
		bool DDSremove(i32 pos);
		bool DDSreplace(i32 pos, const DDSinfo &info, const stream &s);
		bool DDSextract(i32 pos, matrix &mat);
		bool DDSpreprocess(const matrix &mat, stream &s, DDSinfo &info);
		bool CLRpush(const color &clr, i32 paletteID = 0);
		bool CLRinsert(i32 pos, const color &clr, i32 paletteID = 0);
		bool CLRremove(i32 pos, i32 paletteID = 0);
		bool CLRreplace(i32 pos, const color &clr, i32 paletteID = 0);
		bool CLRnewPalette();
		bool ConvertTo(IMGobject &newIO, IMGversion newVersion, i32 palettedID = 0);
	public:
		i32 linkFind(b32 pos, b32 depth = 5);		//查找索引帧最终指向（depth为深度）
		b64 getSize() const;
	protected:
		stream *getData(b8 _part);
		stream data1;		//文件头（V2,V4,V6为一组,V5为一组）
		stream data2;		//调色板数据
		stream data3;		//DDS信息，V5之外无效
		stream data4;		//图像信息
		stream data5;		//DDS图像数据，V5之外无效
		stream data6;		//图像数据
	public:
		IMGindex *derived;

		IMGversion version;
		b32 indexCount, indexSize;
		b32 V5_DDSCount;
		b32 V5_totalLength;

		palette paletteData;
		DDSlist DDScontent;
		PIClist PICcontent;
	};
}


#endif
