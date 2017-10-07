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

#define MAX_UNCOMPRESSED_DATA_LENGTH	0x100000

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
	typedef char					i8,			*pi8;
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
	enum compressType{COMP_NONE = 5, COMP_ZLIB = 6, COMP_UDEF = 0};
	enum colorFormat{ARGB8888 = 0x10, ARGB4444 = 0x0F, ARGB1555 = 0x0E, LINK = 0x11, COLOR_UDEF = 0, V4_FMT};
	enum colorMethod{LAY, DARKEN, MULTIPLY, COLORBURN, LINEARBURN, LIGHTEN, SCREEN, COLORDODGE, LINEARDODGE, OVERLAY, HARDLIGHT, SOFTLIGHT, VIVIDLIGHT, LINEARLIGHT, PINLIGHT, HARDMIX, DIFFER, EXCLUSION};
	enum command{CREATE, LOAD, MAKE, RELEASE, PUSH, INSERT, REMOVE, REPLACE, RENAME, SETPARA, EXTRACT, PREPROCESS, CONVERT};
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
	static size operator - (const point& pt1, const point& pt2);
	static point operator + (const point& pt1, const size& sz);
	static point operator - (const point& pt1, const size& sz);
	/////////////////////////////////////
	class matrix{
	public:
		matrix();
		matrix(b32 _row, b32 _column);
		matrix(const matrix &_mat);
		~matrix();
		matrix& operator = (const matrix &_mat);
	public:
		//内存分配
		void allocate(b32 _row, b32 _column);
		void reallocate(b32 _row, b32 _column);
		void release();
		void fill(color _clr);
		void push(color _clr);					//游标处颜色赋值并加1
		b64 push(const stream &_s);				//以流填充
		b64 make(stream &_s);					//制作成流
	public:
		//取值/行列
		pcolor operator[] (b32 _i) const;		//重写双下标函数
		b32 getRowCount() const;
		b32 getColumnCount() const;
		b32 getElemCount() const;
		//取子阵
		void getSubMatrix(matrix &dest, b32 &_rst, b32 &_red, b32 &_cst, b32 &_ced) const;
		void getChannelMatrix(matrix &dest, b8 _chn = FA) const;
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
	protected:
		llcolor table;
	};
	//////工厂类////////////////////////
	class NPKobject;		//整个NPK块
	class IMGobject;		//IMG块
	//////结构体//////////////////////
	class IMGindex;			//IMG的索引项
	class PICinfo;			//PIC数据
	typedef std::vector<IMGindex> IMGcontent;
	typedef std::vector<IMGobject> IMGlist;
	typedef std::vector<PICinfo> PIClist;
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
	public:
		//图像信息
		declare_basefun(format, colorFormat);
		declare_basefun(comp, compressType);
		declare_basefun(dataSize, b32);
		declare_basefun(basePt, point);
		declare_basefun(picSize, size);
		declare_basefun(frmSize, size);
		declare_basefun(linkTo, i32);
	public:
		PICinfo();
	};
	///////////////////////////////////
	class NPKobject{
	public:
		NPKobject();
		bool load(const stream &_s);
		bool make(const stream &_s);
		bool loadFile(str fileName);
		bool saveFile(str fileName);
		bool create();
		bool release();
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
		~IMGobject();
		bool loadFile(str fileName);			//从文件中读取
		bool saveFile(str fileName);			//保存文
	public:
		bool create(IMGversion ver = V2);
		bool load(const stream &_s);
		bool make(stream& _s);
		bool release();
		bool PICparaModify(i32 pos, i32 term, i32 val);
		bool PICpush(const PICinfo &obj, const stream &_s);
		bool PICinsert(i32 pos, const PICinfo &obj, const stream &_s);
		bool PICremove(i32 pos);
		bool PICreplace(i32 pos, const PICinfo &obj, const stream &_s);
		bool PICextract(i32 pos, matrix &mat, i32 paletteID = 0);
		bool PICpreprocess(const matrix &mat, stream &s, PICinfo &obj);
		bool colorExtract(lcolor &list);
		bool convertTo(IMGversion newVer, IMGobject &imgObj, i32 paletteID = 0);
	public:
		pstream getData(b8 _part);
		b64 getSize() const;
		bool PICInfo(b32 pos, PICinfo &obj);
		bool PICData(b32 pos, stream &data);
		bool PICInfoOffset(b32 pos, b64 &off);		//计算目标字节流在数据块3内的存储位置
		bool PICDataOffset(b32 pos, b64 &off);		//计算目标字节流在数据块4内的存储位置
		i32 linkFind(b32 pos, b32 depth = 5);		//查找索引帧最终指向（depth为深度）
	public:
		//通用属性
		IMGversion version;
		b32 count, indexSize;
		IMGindex *derived;
		PIClist content;
	public:
		//V4,V6使用的调色板
		palette paletteData;
	protected:
		//Data分为四个区域：文件头、IMG功能区、图像信息区、图像数据区
		stream data1, data2, data3, data4;
		bool invoke(b16 command, void *para1 = NULL, void *para2 = NULL, void *para3 = NULL);
	};
}


#endif
