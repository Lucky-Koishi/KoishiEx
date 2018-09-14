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

#define DEF_GETSET(_type, _member) protected:_type _member;public:inline _type get_##_member() const{return _member;}inline _type*getPtr_##_member(){return &_member;}inline void set_##_member(_type val){_member=val;}


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
	//颜色通道
	enum channelFlag{FA = 0x01, FR = 0x02, FG = 0x04, FB = 0x08};
	//图层叠放方式
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
	//基本类:数据流
	///////////////////////////////////////
	class stream{
	public:
		stream();
		stream(b64 _len);
		stream(const stream &_s);
		~stream();
		stream& operator = (const stream &_s);
	public:
		//分配空间
		void allocate(b64 _len);
		//重新分配空间
		void reallocate(b64 _len);
		//释放空间
		void release();
	public:
		//下标函数
		b8& operator[] (b64 _i) const;
		//转化为字符串
		operator str();
		//获得有效数据长度
		b64 getLen() const;
		//获得分配长度
		b64 getMaxLen() const;
		//获得游标位置
		b64 ptPos() const;
		//游标移动至……
		b64 ptMoveTo(i64 pos);
		//游标移动
		b64 ptMove(i64 dist);
	public:
		//有效数据长度清零，并不释放空间
		void clear();
		//插入数据
		b8 push(b8 d);
		b8 push(b16 d);
		b8 push(b32 d);
		b8 push(b64 d);
		b8 push(i32 i);
		//读取游标处数据
		b8 read(b8 &d);
		b8 read(b16 &d);
		b8 read(b32 &d);
		b8 read(b64 &d);
		b8 read(i32 &i);
		//插入字符串
		b8 pushString(str s);
		//读取字符串
		str readString(b32 l);
		//插入另一个数据流
		b8 pushStream(const stream &s, b64 l);
		//从游标处读取l个字节到dest
		void readStream(stream &dest, b64 l);
		//中间位置插入另一个数据流
		void insertStream(const stream &s, b64 l, b64 pos);
		//删除数据流
		void deleteStream(b64 pos, b64 l);
		//更改指定位置的一个字节
		bool modify(b64 pos, b8 d);
		//更改指定位置的一个整型
		bool modify(b64 pos, i32 i);
		//替换数据
		b64 replace(const b8 &whos, const b8 &to);
	public:
		//将数据流存储成文件
		bool makeFile(str fileName);
		//读取文件到数据流
		bool loadFile(str fileName);
	public:
		//NPK名字文件掩码
		void nameMask();
		//对数据流进行type所示压缩，并存储到dest中
		i8 compressData(stream &dest, compressType type);
		//对数据流进行type所示解压，并存储到dest中，成功返回0，数据错误返回-3，tryLength不够返回-5
		i8 uncompressData(stream &dest, compressType type, b64 tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
		//对数据流进行SHA256加密，并将32字节数存储到dest中
		void getSHA256(stream &dest);
		//对数据流追加另一段数据流后修正为17的整数倍，并进行SHA256加密（为NPK准备）
		void getSHA256(stream &dest, const stream &added);
	public:
		//查找相连的一串数据流
		i64 findStream(const stream &s, b64 startPos = 0);
		//获取被指定数据流分割的字符串的起始位置和长度，返回分割数（空流也算）
		b64 splitStream(const stream &s, lb64 &posList, lb64 &lenList);
		//进行BZ2压缩
		i8 BZcompress(stream &dest);
		//进行BZ2解压
		i8 BZdecompress(stream &dest);

	public:
		pb8 data;
		b64 len,maxLen,pt;
	};
	///////////////////////////////////////
	//基本类:颜色的HSV信息
	///////////////////////////////////////
	typedef struct colorHSV{
		i32 H;
		fl2 S;
		fl2 V;
	}colorHSV;
	///////////////////////////////////////
	//基本类:颜色的RGB信息
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
		//颜色通道
		color getChannel(b8 _chn) const;
		//颜色混合
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
	public:
		//计算两个颜色的欧氏距离的平方
		static int EuclideanDistanceSquareOf(const color &a, const color &b);
		//平分颜色空间后计算颜色
		static color lose(const color &c, b8 part);
		static color loseBit(const color &c, b8 bit);
		//伽马变换
		static color loseBlack(const color &c, b8 gamma);
	};
	///////////////////////////////////////
	//基本类:坐标点
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
	//基本类:尺寸
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
	//基本类:颜色矩阵
	//令R=G=B=0时，可以用做索引矩阵用
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
		//内存分配
		bool valid();
		void allocate(b32 _row, b32 _column);
		void allocate(const size &_sz);
		void release();
		void fill(color clr);
		void push(color clr);									//游标处颜色赋值并加1
		b64 push(const stream &_s, colorFormat cf = ARGB8888);	//以流填充，当cf为INDEX_FMT_PALEETE时作为索引矩阵处理
		b64 make(stream &s, colorFormat cf = ARGB8888) const;	//制作数据流，当cf为INDEX_FMT_PALEETE时作为索引矩阵处理
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
		void setElem(b32 r, b32 c, const color &clr);
		void setElem(b32 id, const color &clr);
		color getElem(b32 r, b32 c) const;			//取像素点
		color getElem(b32 id) const;						//取像素点
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
		void lose(b8 fine); //扔通道
		void loseBit(b8 bit); //扔位
		void loseBlack(b8 gamma); //去黑底
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
	class TEXinfo;			//DDS数据
	typedef std::vector<IMGindex> IMGcontent;
	typedef std::vector<IMGobject> IMGlist;
	typedef std::vector<PICinfo> PIClist;
	typedef std::vector<TEXinfo> TEXlist;
	///////////////////////////////////
	class IMGindex{
		//IMG索引数据
		DEF_GETSET(b32,imgoffset);		//首地址偏移量
		DEF_GETSET(b32,imgsize);		//IMG大小
		DEF_GETSET(str,imgname);		//IMG路径名
	public:
		IMGindex();
	};
	class PICinfo{
		//图像信息
		DEF_GETSET(colorFormat,format);
		DEF_GETSET(compressType,comp);
		DEF_GETSET(b32,dataSize);
		DEF_GETSET(point,basePt);
		DEF_GETSET(size,picSize);
		DEF_GETSET(size,frmSize);
		DEF_GETSET(i32,linkTo);
		//双索引模式
		DEF_GETSET(b32,TEXusing);
		DEF_GETSET(point,TEXpointLT);
		DEF_GETSET(point,TEXpointRB);
	public:
		PICinfo();
	};
	class TEXinfo{
		//纹理集信息
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
		bool loadIndex(const str &fileName, std::vector<IMGversion> &versionList);	//仅读取版本
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
		//Data分四个区域：文件头、IMG索引表、校验位、IMG文件
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
		bool loadFile(str fileName);			//从文件中读取
		bool saveFile(str fileName);			//保存文件
		bool load(stream &s);
		bool make(stream &s);
		bool create(IMGversion ver);
		bool release();
		//贴图操作
		bool PICgetInfo(i32 pos, PICinfo &info);		//获取索引项信息
		bool PICgetInfoOffset(i32 pos, b64 &off);		//获取索引项偏移量
		bool PICgetData(i32 pos, stream &s);			//获取图片型数据
		bool PICgetDataOffset(i32 pos, b64 &off);		//获取图片型数据偏移量
		bool PICpush(const PICinfo &info, const stream &s);				//插入图片
		bool PICinsert(i32 pos, const PICinfo &info, const stream &s);	//插入图片索引项
		bool PICremove(i32 pos);										//删除图片
		bool PICreplace(i32 pos, const PICinfo &info, const stream &s);	//替换图片
		bool PICextract(i32 pos, matrix &mat, i32 paletteID = 0);		//提取图片
		bool PICpreprocess(const matrix &mat, stream &s, PICinfo &info, colorFormat cf = COLOR_UDEF);//预处理图片
		bool PICextractIndexMatrix(i32 pos, matrix &mat);										//提取的矩阵是索引数据
		bool PICpreprocessIndexMatrix(const matrix &mat, stream &s, PICinfo &info);			//根据索引数据的矩阵对IMG进行预处理
		bool PICempty(stream &s, PICinfo &info);						//以空帧预处理图片
		bool PICsetInfoPara(i32 pos, i32 term, void *pval);		//设置索引项信息
		//纹理集操作
		bool TEXgetInfo(i32 pos, TEXinfo &info);		//获取纹理集索引项信息
		bool TEXgetInfoOffset(i32 pos, b64 &off);		//获取纹理集索引项偏移量
		bool TEXgetData(i32 pos, stream &s);			//获取纹理集数据
		bool TEXgetDataOffset(i32 pos, b64 &off);		//获取纹理集数据偏移量
		
		bool TEXpush(const TEXinfo &info, const stream &s);
		bool TEXinsert(i32 pos, const TEXinfo &info, const stream &s);
		bool TEXremove(i32 pos);
		bool TEXreplace(i32 pos, const TEXinfo &info, const stream &s);
		bool TEXextract(i32 pos, matrix &mat);
		bool TEXpreprocess(const matrix &mat, stream &s, TEXinfo &info, colorFormat cf = COLOR_UDEF);
		//颜色操作
		bool CLRpush(const color &clr, i32 paletteID = 0);
		bool CLRinsert(i32 pos, const color &clr, i32 paletteID = 0);
		bool CLRremove(i32 pos, i32 paletteID = 0);
		bool CLRreplace(i32 pos, const color &clr, i32 paletteID = 0);
		bool CLRnewPalette();
		//转换
		bool convertTo(
			IMGobject &newIO,				//转化后IMG的引用
			IMGversion newVersion,			//转化后IMG的版本
			colorFormat cf = COLOR_UDEF,	//颜色格式
			i32 palettedID = 0,				//原IMG为V6时，取调色板参数
			b8 indexPara = 0,				//转化为索引图像时，矩阵颜色量化参数
			bool makeTexture = false		//转化为V5时，是否制作纹理集
		);
		//其他操作
		i32 linkFind(b32 pos, b32 depth = 5);		//查找索引帧最终指向（depth为深度）
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
		stream data1;		//文件头（V2,V4,V6为一组,V5为一组）
		stream data2;		//调色板数据
		stream data3;		//DDS信息，V5之外无效
		stream data4;		//图像信息
		stream data5;		//DDS图像数据，V5之外无效
		stream data6;		//图像数据
	};
}

namespace KoishiExpand{
	//扩展功能
	//时装打标
	extern void CharMat(char p, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern void StrMat(std::string str, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern void CharMat2(char p, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern void StrMat2(std::string str, Koishi::matrix &mat, Koishi::color clr = Koishi::color(0xff,0,0,0));
	extern bool AvatarMarking(std::string avatarNPKfileName);
	extern bool AvatarBatchMarking(std::string avatarNPKfileListName);
	//任意NPK打标(右侧添加IMG路径名：帧号)
	extern bool IMGMarking(Koishi::IMGobject &io, std::string customMark = "", bool usingCustom = false, bool addedFrameID = true);
	extern bool NPKMarking(std::string NPKfileName);
	//强制转索引图像
	class Indexing{
	public:
		Indexing();
		void input(const Koishi::IMGobject &in);
		void input(const std::string imgName);
		void output(Koishi::IMGobject &out);
		void output(const std::string imgName);
		volatile int millages;		//千分之……
	private:
		void deal(Koishi::IMGobject &goal, int colorCount = 0xFF);
		Koishi::IMGobject io;
	};
	/////////////////////////////////////////////////////
	//外服解包文件SPK功能
	/////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////
	//外服解包文件列表LST功能
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
	//国服解包文件TCT功能
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
	//旧版IMG(V1版本)转换
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
		//颜色梯度
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
