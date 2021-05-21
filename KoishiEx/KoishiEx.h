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


#define KOISHI_EX_VER		(double)2.0

#define MAX_UNCOMPRESSED_DATA_LENGTH	0x1000000

#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
namespace Koishi{
	//定义基础数据
	typedef std::string	str;
	typedef unsigned char uchar;
	typedef unsigned short word;
	typedef unsigned long dword;
	typedef long long longex;
	typedef unsigned long long ulongex;
	class complex;
	typedef std::vector<long> queue;
	typedef std::vector<double> sequence;
	typedef std::vector<longex> queueex;
	typedef std::vector<complex> compsequence;
	enum colorFormat:dword{
		ARGB8888 = 0x10, ARGB4444 = 0x0F, ARGB1555 = 0x0E, LINK = 0x11, 
		DDS_DXT1 = 0x12, DDS_DXT3 = 0x13, DDS_DXT5 = 0x14, COLOR_UDEF = 0, INDEX_FMT_PALETTE
	};
	enum colorMethod{
		//颜色运算 覆盖·变暗·正片叠底·颜色加深·线性加深·变亮·滤色·颜色减淡·线性减淡·叠加·强光·柔光·亮光·线性光·点光·实色混合·插值·排除
		LAY, DARKEN, MULTIPLY, COLORBURN, LINEARBURN, LIGHTEN, SCREEN, COLORDODGE, LINEARDODGE, OVERLAY, HARDLIGHT, SOFTLIGHT, VIVIDLIGHT, LINEARLIGHT, PINLIGHT, HARDMIX, DIFFER, EXCLUSION, REPLACE
	};
	enum colorProperty{
		//颜色属性 透明度·红色·绿色·蓝色·灰度·色调·饱和度·明度
		COLOR_ALPHA, COLOR_CHANNEL_RED, COLOR_CHANNEL_GREEN, COLOR_CHANNEL_BLUE, COLOR_GRAYSCALE, COLOR_HUE, COLOR_SATURATION, COLOR_VALUE
	};
	class stream;
	class color;
	class point;
	class size;
	class image;
	class palette;

	typedef std::vector<color> colorList;
	typedef std::vector<colorList> colorTable;
	///////////////////////////////////////
	//基本类:数据流
	///////////////////////////////////////
	class stream{
	public:
		stream();
		stream(longex newLen);
		//复制构造函数和复制构造运算符会重置浮标
		stream(const stream &sSource);	
		stream& operator = (const stream &sSource);
		~stream();
	private:
		uchar *data;
	public:
		longex length;
		longex storage;
	public:
		//分配空间
		void allocate(longex newLen);
		void reallocate(longex newLen);
		void release();
		void clear();
	public:
		//取值函数
		uchar& operator[] (longex pos) const;
		uchar getBit(longex pos, long bitCount = 1) const;	//低位先
		uchar getRBit(longex pos, long bitCount = 1) const;	//高位先
		void *begin(longex pos = 0) const;
		void *end(longex pos = 0) const;
	private:
		//游标控制
		longex position;		//两种游标
	public:
		longex getPosition() const;
		longex resetPosition();
		longex movePosition(longex dist);
		longex setPosition(longex dist);
	public:
		//按字节插入数据（仅限往后）
		void push(const void *sour, longex len);
		bool pushByte(uchar d);
		bool pushWord(word d);
		bool pushDWord(dword d);
		bool pushInt64(longex d);
		bool pushInt(long i);
		bool pushString(str s);
		void pushStream(const stream &addedStream, longex len);
		//读取游标处数据
		bool readByte(uchar&);
		bool readWord(word&);
		bool readDWord(dword&);
		bool readInt64(longex&);
		bool readInt(long&);
		str readString(dword l);
		longex readStream(stream &dest, longex l);
		longex read(void *dest, longex l);
		//穿插其他字节流
		void insertStream(const stream &s, longex l, longex pos);
		void deleteStream(longex pos, longex l);
		//更改指定的数据
		bool modifyByte(longex pos, uchar d);
		bool modifyDWord(longex pos, dword d);
		bool modifyInt(longex pos, long i);
		longex replace(const uchar &whos, const uchar &to);
		//其他常用操作
		longex findStream(const stream &s, longex startPos = 0);
		longex splitStream(const stream &s, queueex &posList, queueex &lenList);
	public:
		//输入输出
		bool makeFile(str fileName);
		bool loadFile(str fileName);
	public:
		//变换和加密
		void nameMask();
		void SHA256code(stream &dest);
		int BZcompress(stream &dest);
		int BZuncompress(stream &dest);
		int ZLIBcompress(stream &dest);
		int ZLIBuncompress(stream &dest, longex tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
		///////////////////////////////////////////////////
		//位运算/不带LF是右端（低位就是低位）起////////////
		///////////////////////////////////////////////////
	private:
		//位游标控制
		longex bitPosition;		//位游标
	public:
		void bitAlignPosition();					//将位游标与字节游标对齐
		void alignBitPosition();					//将字节游标调整到位游标(向后取整)
		void bitResetPosition();					//重置位游标
		longex bitGetPosition();					//设置位游标
		void bitSetPosition(longex bitPos);			//设置位游标
	public:
		uchar bitGet(longex bitPos);				//获得指定位是高电平还是低电平
		bool bitSet(longex bitPos, uchar value);	//修改单个位，value取值为零（低电平）或非零（高电平）
		bool bitPush(const void *sour, longex bitLen);
		bool bitPush(dword value, longex bitLen);	//一次性压入最多32位数值
		bool bitRead(void *dest, longex bitLen);
		bool bitRead(dword &value, longex bitLen);	//一次性读取最多32位数值
		//左端First位运算
	public:
		uchar LFbitGet(longex bitPos);
		bool LFbitSet(longex bitPos, uchar value);
		bool LFbitPush(const void *sour, longex bitLen);
		bool LFbitPush(dword value, longex bitLen);
		bool LFbitRead(void *dest, longex bitLen);
		bool LFbitRead(dword &value, longex bitLen);
	};
	///////////////////////////////////////
	//基本类:复数
	///////////////////////////////////////
	class complex{
	public:
		complex(double a = 0, double b = 0);
		double real, img;
		complex operator +() const;
		complex operator -() const;
		double operator *() const;	//取地址被认为是求模
		complex operator ~() const; //共轭
		complex operator +(const complex &c) const;
		complex operator -(const complex &c) const;
		complex operator *(const complex &c) const;
		complex operator /(const complex &c) const;
		complex operator *(const double &m) const;
		complex operator /(const double &m) const;
		double radius() const;
		double angle() const;
	};
	///////////////////////////////////////
	//基本类:颜色信息
	///////////////////////////////////////
	typedef struct colorHSV{
		long H;
		double S;
		double V;
	}colorHSV;
	class color{
	public:
		union{
			uchar alpha;
			uchar index;
		};
		uchar R,G,B;
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
		//颜色变换
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
		static int distance_2(const color &a, const color &b);
		static color lose(const color &c, uchar part);
		static color loseBit(const color &c, uchar bit);
		static color loseBlack(const color &c, uchar gamma);
		static color getBrighten(const color &c);
		static color getDarken(const color &c);
	};
	///////////////////////////////////////
	//基本类:坐标点·尺寸·矩形
	///////////////////////////////////////
	class point{
	public:
		long X, Y;
	public:
		point();
		point(long x, long y);
		point operator + (const point &delta) const;
		point operator - (const point &delta) const;
		point operator + (const size &sz) const;
		point operator - (const size &sz) const;
		point operator + () const;
		point operator - () const;
		point operator * (double mult) const;
		point operator / (double mult) const;
		point operator ~ () const;
		char operator == (const point &other) const;
	};
	class size{
	public:
		long W,H;
	public:
		size();
		size(long w, long h);
		long area() const;
	};
	class rectangle {
	public:
		long X1, Y1, X2, Y2;
	public:
		rectangle();
		rectangle(point lt, point rb);
		rectangle(point lt, size sz);
		rectangle(long x1, long y1, long x2, long y2);
		char operator == (const rectangle &other) const;
		long getWidth() const;
		long getHeight() const;
	public:
		void shrink(long distance);
		void expand(long distance);
		void splitHroz2(rectangle &x1, rectangle &x2, int ratioLeft, int ratioRight, int gap = 0);
		void splitVert2(rectangle &x1, rectangle &x2, int ratioTop, int ratioBottom, int gap = 0);
		void splitHrozN(std::vector<rectangle> xn, queue ratioList, int gap = 0);
		void splitVertN(std::vector<rectangle> xn, queue ratioList, int gap = 0);
	};
	///////////////////////////////////////
	//基本类:图像，当R=G=B=0时，可以用做索引矩阵用
	///////////////////////////////////////
	class image{
	public:
		image();
		image(dword _row, dword _column);
		image(const size &_sz);
		image(const image &_mat);
		~image();
		image& operator = (const image &_mat);
	public:
		union{
			dword column, width;
		};
		union{
			dword row, height;
		};
	protected:
		color *data;
		//dword pt;
	public:
		//内存分配
		bool valid();
		void create(dword _row, dword _column);
		void create(const size &_sz);
		void destory();
		void fill(color clr);
		//void push(color clr);									//游标处颜色赋值并加1
		longex load(const stream &_s, colorFormat cf = ARGB8888);	//以流填充，当cf为INDEX_FMT_PALEETE时作为索引矩阵处理
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
		void setElem(point pt, const color &clr);
		color getElem(dword r, dword c) const;			//取像素点
		color getElem(dword id) const;						//取像素点
		color getElem(point pt) const;
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
		void putFore(const image &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//以此矩阵为底层，画上目标矩阵
		void putBack(const image &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//以此矩阵为顶层，在其底下画上目标矩阵
	public:
		//以此矩阵为基准计算其他矩阵
		void clip(image &dest, dword rowStart, dword rowEnd, dword columnStart, dword columnEnd) const;//裁剪
		void expand(image &dest, dword toTop, dword toBottom, dword toLeft, dword toRight, color filledClr = color(0,0,0,0)) const;		//扩充
		void zoom(image &dest, double ratio) const;			//缩放
		void zoom(image &dest, double honzRatio, double vertRatio) const;	//缩放

		void clip(dword rowStart, dword rowEnd, dword columnStart, dword columnEnd);
		void expand(dword toTop, dword toBottom, dword toLeft, dword toRight, color filledClr = color(0,0,0,0));		//扩充
		void zoom(double ratio);			//缩放
		void zoom(double honzRatio, double vertRatio);	//缩放
	public:
		//颜色操作
		void lose(uchar fine); //扔通道
		void loseBit(uchar bit); //扔位
		void loseBlack(uchar gamma); //去黑底
		void turnGray();
		void turnShield();			//将实色色部分变为1/2透明的白色
		void getBrighten();
		void getDarken();
		void getTransparented();
	public:
		//绘制操作
		void line(point p1, point p2, const color &clr);
		void rectangle(point p1, point p2, const color &clr);
		void filledRectangle(point p1, point p2, const color &clr);
		void filledLattice(point p1, point p2, const color &clr1, const color &clr2, long size);
		void fill(point seedPt, const color &clr);
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
	public:
		//为IMG对象创建调色板数据
		bool tinyMake(stream &s, long paletteID = 0);
		bool bigMake(stream &s);
	public:
		//对调色板文件的导入导出
		static bool makeACT(str fileName, const colorList &list);
		static bool loadACT(str fileName, colorList &list);
		static bool makeCID(str fileName, const colorList &list);
		static bool loadCID(str fileName, colorList &list);
		//默认调色板
		static colorList palette2();
		static colorList palette16();
		static colorList palette64();
		static colorList palette256();
	protected:
		colorTable table;
	};
	//音频采样点
	typedef union sample{
	public:
		sample();
		sample(short a1);
		sample(short a1, short a2);
	public:
		short value[2];
		dword data;
	public:
		short &operator [](int i);
		sample operator + (const sample &delta) const;	//增加
		sample operator - (const sample &delta) const;	//减少
		sample operator + () const;						//正向
		sample operator - () const;						//反向
		sample operator * (double mult) const;			//数乘
		sample operator / (double mult) const;			//数除
		sample operator ~ () const;						//交换左右
	private:
		static short shortPlus(short a, short b);		//a+b然后限制在范围内
		static short shortMult(short a, double b);		//数乘然后限制在范围内
	}sample;
	class audio{
	public:
		audio();
		audio(const longex &newLen, int ch = 1, int newSample = 44100);
		audio(const audio &sour);
		~audio();
		audio(const stream &PCM, int ch = 1, int newSample = 44100);			//输入
		audio& operator = (const audio &sour);
	public:
		int channel;
		int sampleRate;								//采样频率单位HZ
		longex length;
	protected:
		longex pt;
		sample *data;
	public:
		void create(longex newLen);
		void create(const stream &PCM, int ch = 1, int newSample = 44100);
		void destory();
		void fill(const sample &sp);
		void make(stream &s);						//输出的声道数为channel
		void make2(stream &s);						//输出的肯定是双声道的（1个声道置0）
	public:
		sample &operator[](longex i) const;
		longex getLastTime() const;					//获得持续时间，单位毫秒
		longex getPos(longex minisec) const;		//真实时间 - 时域转换
		longex getTime(longex pos) const;			//真实时间 - 时域转换
		sample *begin(longex pos) const;
		sample *end(longex pos) const;
	public:
		void expand(audio &ad, longex newLen);
		void clip(audio &ad, longex left, longex right);
		void clipToBegin(audio &ad, longex right);
		void clipToEnd(audio &ad, longex left);
		void reverse(audio &ad);
		void mult(audio &ad, double value);
		void multCurve(audio &ad, double(*f)(double)); //curve: 定义域为0 - 1的曲线，范围随意
		void applayFadeIn(audio &ad, longex last);
		void applayFadeOut(audio &ad, longex last);
		void zoom(audio &ad, double rate);
		void swapChannel(audio &ad);
		void echo(audio &ad, int times, int offset, double attenuation = 0.5f);
	public:
		void expand(longex newLen);
		void clip(longex left, longex right);
		void clipToBegin(longex right);
		void clipToEnd(longex left);
		void reverse();
		void mult(double value);
		void multCurve(double(*f)(double));
		void applayFadeIn(longex last);
		void applayFadeOut(longex last);
		void zoom(double rate);
		void swapChannel();
		void echo(int times, int offset, double attenuation = 0.5f);
	public:	
		void cat(const audio &ad);	//拼接
		void mixWith(const audio &ad, double percent = 1, longex offset = 0);		//混音
		void doubleChannel();
		void getChannel(audio &ad, int ch) const;
	public:
		//平滑曲线 d为0-1之间
		static double slope_up(double d);
		static double slope_down(double d);
	public:
		void slow(audio &ad, int blockSize, int gapSize);		//gapSize不得超过blockSize的一半，减慢的速度不能小于50%，否则需要多次调用
		void fast(audio &ad, int blockSize, int overlapSize);	//overlapSize不得超过blockSize的一半，加快速度不能超过2倍，否则需要多次调用
		void slow(int blockSize, int gapSize);	
		void fast(int blockSize, int overlapSize);
		void adjustSpeed(audio &ad, double rate);				//变速 rate>1是加速
		void adjustPitch(audio &ad, double rate);				//变调 rate>1是升调
		void adjustSpeed(double rate);
		void adjustPitch(double rate);
	};
}

#endif