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


#define KOISHI_EX_VER		(double)2.0

#define MAX_UNCOMPRESSED_DATA_LENGTH	0x1000000

#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)>(b)?(a):(b))

namespace Koishi{
	//�����������
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
		ARGB8888 = 0x10, ARGB4444 = 0x0F, ARGB1555 = 0x0E, LINK = 0x11, DDS_DXT1 = 0x12, DDS_DXT3 = 0x13, DDS_DXT5 = 0x14, COLOR_UDEF = 0, INDEX_FMT_PALETTE
	};
	enum colorMethod{
		//��ɫ���� ���ǡ��䰵����Ƭ���ס���ɫ������Լ����������ɫ����ɫ���������Լ��������ӡ�ǿ�⡤��⡤���⡤���Թ⡤��⡤ʵɫ��ϡ���ֵ���ų�
		LAY, DARKEN, MULTIPLY, COLORBURN, LINEARBURN, LIGHTEN, SCREEN, COLORDODGE, LINEARDODGE, OVERLAY, HARDLIGHT, SOFTLIGHT, VIVIDLIGHT, LINEARLIGHT, PINLIGHT, HARDMIX, DIFFER, EXCLUSION, REPLACE
	};
	enum colorProperty{
		//��ɫ���� ͸���ȡ���ɫ����ɫ����ɫ���Ҷȡ�ɫ�������Ͷȡ�����
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
	//������:������
	///////////////////////////////////////
	class stream{
	public:
		stream();
		stream(longex newLen);
		//���ƹ��캯���͸��ƹ�������������ø���
		stream(const stream &sSource);	
		stream& operator = (const stream &sSource);
		~stream();
	private:
		uchar *data;
	public:
		longex length;
		longex storage;
	public:
		//����ռ�
		void allocate(longex newLen);
		void reallocate(longex newLen);
		void release();
		void clear();
	public:
		//ȡֵ����
		uchar& operator[] (longex pos) const;
		uchar getBit(longex pos, long bitCount = 1) const;	//��λ��
		uchar getRBit(longex pos, long bitCount = 1) const;	//��λ��
		void *begin(longex pos = 0) const;
		void *end(longex pos = 0) const;
	private:
		//�α����
		longex position;		//�����α�
	public:
		longex getPosition() const;
		longex resetPosition();
		longex movePosition(longex dist);
		longex setPosition(longex dist);
	public:
		//���ֽڲ������ݣ���������
		void push(const void *sour, longex len);
		bool pushByte(uchar d);
		bool pushWord(word d);
		bool pushDWord(dword d);
		bool pushInt64(longex d);
		bool pushInt(long i);
		bool pushString(str s);
		void pushStream(const stream &addedStream, longex len);
		//��ȡ�α괦����
		bool readByte(uchar&);
		bool readWord(word&);
		bool readDWord(dword&);
		bool readInt64(longex&);
		bool readInt(long&);
		str readString(dword l);
		longex readStream(stream &dest, longex l);
		longex read(void *dest, longex l);
		//���������ֽ���
		void insertStream(const stream &s, longex l, longex pos);
		void deleteStream(longex pos, longex l);
		//����ָ��������
		bool modifyByte(longex pos, uchar d);
		bool modifyDWord(longex pos, dword d);
		bool modifyInt(longex pos, long i);
		longex replace(const uchar &whos, const uchar &to);
		//�������ò���
		longex findStream(const stream &s, longex startPos = 0);
		longex splitStream(const stream &s, queueex &posList, queueex &lenList);
	public:
		//�������
		bool makeFile(str fileName);
		bool loadFile(str fileName);
	public:
		//�任�ͼ���
		void nameMask();
		void SHA256code(stream &dest);
		int BZcompress(stream &dest);
		int BZuncompress(stream &dest);
		int ZLIBcompress(stream &dest);
		int ZLIBuncompress(stream &dest, longex tryLength = MAX_UNCOMPRESSED_DATA_LENGTH);
		///////////////////////////////////////////////////
		//λ����/����LF���Ҷˣ���λ���ǵ�λ����////////////
		///////////////////////////////////////////////////
	private:
		//λ�α����
		longex bitPosition;		//λ�α�
	public:
		void bitAlignPosition();					//��λ�α����ֽ��α����
		void alignBitPosition();					//���ֽ��α������λ�α�(���ȡ��)
		void bitResetPosition();					//����λ�α�
		longex bitGetPosition();					//����λ�α�
		void bitSetPosition(longex bitPos);			//����λ�α�
	public:
		uchar bitGet(longex bitPos);				//���ָ��λ�Ǹߵ�ƽ���ǵ͵�ƽ
		bool bitSet(longex bitPos, uchar value);	//�޸ĵ���λ��valueȡֵΪ�㣨�͵�ƽ������㣨�ߵ�ƽ��
		bool bitPush(const void *sour, longex bitLen);
		bool bitPush(dword value, longex bitLen);	//һ����ѹ�����32λ��ֵ
		bool bitRead(void *dest, longex bitLen);
		bool bitRead(dword &value, longex bitLen);	//һ���Զ�ȡ���32λ��ֵ
		//���Firstλ����
	public:
		uchar LFbitGet(longex bitPos);
		bool LFbitSet(longex bitPos, uchar value);
		bool LFbitPush(const void *sour, longex bitLen);
		bool LFbitPush(dword value, longex bitLen);
		bool LFbitRead(void *dest, longex bitLen);
		bool LFbitRead(dword &value, longex bitLen);
	};
	///////////////////////////////////////
	//������:����
	///////////////////////////////////////
	class complex{
	public:
		complex(double a = 0, double b = 0);
		double real, img;
		complex operator +() const;
		complex operator -() const;
		double operator *() const;	//ȡ��ַ����Ϊ����ģ
		complex operator ~() const; //����
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
	//������:��ɫ��Ϣ
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
		//�Ҷ�
		color gray() const;
		double getProperty(colorProperty theProperty) const;
		//��ɫ���
		double mixMethod(double a,double b, colorMethod _method);
		uchar mixMethod(uchar a,uchar b, colorMethod _method);
		void mixWith(const color &_clr2, colorMethod _method = LAY);
		color mix(const color &_clr1, const color &_clr2, colorMethod _method = LAY);
	public:
		//��ɫ�任
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
	//������:����㡤�ߴ�
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
	};
	class size{
	public:
		long W,H;
	public:
		size();
		size(long w, long h);
		long area() const;
	};
	///////////////////////////////////////
	//������:���󣬵�R=G=B=0ʱ��������������������
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
		dword pt;
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
		void putFore(const image &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//�Դ˾���Ϊ�ײ㣬����Ŀ�����
		void putBack(const image &layer, colorMethod _met = LAY, point basePoint = point(0,0));	//�Դ˾���Ϊ���㣬������»���Ŀ�����
	public:
		//�Դ˾���Ϊ��׼������������
		void clip(image &dest, dword rowStart, dword rowEnd, dword columnStart, dword columnEnd) const;//�ü�
		void expand(image &dest, dword toTop, dword toBottom, dword toLeft, dword toRight, color filledClr = color(0,0,0,0)) const;		//����
		void zoom(image &dest, double ratio) const;			//����
		void zoom(image &dest, double honzRatio, double vertRatio) const;	//����

		void clip(dword rowStart, dword rowEnd, dword columnStart, dword columnEnd);
		void expand(dword toTop, dword toBottom, dword toLeft, dword toRight, color filledClr = color(0,0,0,0));		//����
		void zoom(double ratio);			//����
		void zoom(double honzRatio, double vertRatio);	//����
	public:
		//��ɫ����
		void lose(uchar fine); //��ͨ��
		void loseBit(uchar bit); //��λ
		void loseBlack(uchar gamma); //ȥ�ڵ�
		void turnShield();			//��ʵɫɫ���ֱ�Ϊ1/2͸���İ�ɫ
		void getBrighten();
		void getDarken();
	public:
		//���Ʋ���
		void line(point p1, point p2, const color &clr);
		void rectangle(point p1, point p2, const color &clr);
		void filledRectangle(point p1, point p2, const color &clr);
		void filledLattice(point p1, point p2, const color &clr1, const color &clr2, long size);
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
	public:
		//ΪIMG���󴴽���ɫ������
		bool tinyMake(stream &s, long paletteID = 0);
		bool bigMake(stream &s);
	public:
		//�Ե�ɫ���ļ��ĵ��뵼��
		static bool makeACT(str fileName, const colorList &list);
		static bool loadACT(str fileName, colorList &list);
		static bool makeCID(str fileName, const colorList &list);
		static bool loadCID(str fileName, colorList &list);
		//Ĭ�ϵ�ɫ��
		static colorList palette2();
		static colorList palette16();
		static colorList palette64();
		static colorList palette256();
	protected:
		colorTable table;
	};
	//��Ƶ������
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
		sample operator + (const sample &delta) const;	//����
		sample operator - (const sample &delta) const;	//����
		sample operator + () const;						//����
		sample operator - () const;						//����
		sample operator * (double mult) const;			//����
		sample operator / (double mult) const;			//����
		sample operator ~ () const;						//��������
	private:
		static short shortPlus(short a, short b);		//a+bȻ�������ڷ�Χ��
		static short shortMult(short a, double b);		//����Ȼ�������ڷ�Χ��
	}sample;
	class audio{
	public:
		audio();
		audio(const longex &newLen, int ch = 1, int newSample = 44100);
		audio(const audio &sour);
		~audio();
		audio(const stream &PCM, int ch = 1, int newSample = 44100);			//����
		audio& operator = (const audio &sour);
	public:
		int channel;
		int sampleRate;								//����Ƶ�ʵ�λHZ
		longex length;
	protected:
		longex pt;
		sample *data;
	public:
		void create(longex newLen);
		void create(const stream &PCM, int ch = 1, int newSample = 44100);
		void destory();
		void fill(const sample &sp);
		void make(stream &s);						//�����������Ϊchannel
		void make2(stream &s);						//����Ŀ϶���˫�����ģ�1��������0��
	public:
		sample &operator[](longex i) const;
		longex getLastTime() const;					//��ó���ʱ�䣬��λ����
		longex getPos(longex minisec) const;		//��ʵʱ�� - ʱ��ת��
		longex getTime(longex pos) const;			//��ʵʱ�� - ʱ��ת��
		sample *begin(longex pos) const;
		sample *end(longex pos) const;
	public:
		void expand(audio &ad, longex newLen);
		void clip(audio &ad, longex left, longex right);
		void clipToBegin(audio &ad, longex right);
		void clipToEnd(audio &ad, longex left);
		void reverse(audio &ad);
		void mult(audio &ad, double value);
		void multCurve(audio &ad, double(*f)(double)); //curve: ������Ϊ0 - 1�����ߣ���Χ����
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
		void cat(const audio &ad);	//ƴ��
		void mixWith(const audio &ad, double percent = 1, longex offset = 0);		//����
		void doubleChannel();
		void getChannel(audio &ad, int ch) const;
	public:
		//ƽ������ dΪ0-1֮��
		static double slope_up(double d);
		static double slope_down(double d);
	public:
		void slow(audio &ad, int blockSize, int gapSize);		//gapSize���ó���blockSize��һ�룬�������ٶȲ���С��50%��������Ҫ��ε���
		void fast(audio &ad, int blockSize, int overlapSize);	//overlapSize���ó���blockSize��һ�룬�ӿ��ٶȲ��ܳ���2����������Ҫ��ε���
		void slow(int blockSize, int gapSize);	
		void fast(int blockSize, int overlapSize);
		void adjustSpeed(audio &ad, double rate);				//���� rate>1�Ǽ���
		void adjustPitch(audio &ad, double rate);				//��� rate>1������
		void adjustSpeed(double rate);
		void adjustPitch(double rate);
	};
}

#endif