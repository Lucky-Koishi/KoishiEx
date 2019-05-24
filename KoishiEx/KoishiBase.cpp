#include "StdAfx.h"
#include "KoishiEx.h"
#include <math.h>

using namespace Koishi;

//////////////////////////////////////////////////////////////
//color
color::color(){
	set(0);
}
color::color(dword colorDt, colorFormat clrFmt){
	set(colorDt, clrFmt);
}
color::color(uchar r, uchar g, uchar b){
	set(0xff000000|(r<<16)|(g<<8)|b);
}
color::color(uchar a, uchar r, uchar g, uchar b){
	set((a<<24)|(r<<16)|(g<<8)|b);
}
void color::set(dword colorDt, colorFormat clrFmt){
	switch(clrFmt){
		//////////////////////////////////////////////////////////////////////////
		/////////////////////////////////ARGB8888/////////////////////////////////
		//1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //
		//|      A      |   |      R      |   |      G      |   |      B      | //
		//////////////////////////////////////////////////////////////////////////
	case ARGB8888:
		A = ((colorDt & 0xff000000) >> 24);
		R = ((colorDt & 0x00ff0000) >> 16);
		G = ((colorDt & 0x0000ff00) >> 8);
		B = ((colorDt & 0x000000ff) >> 0);
		break;
		//////////////////////////////////////
		///////////////ARGB4444///////////////
		//1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //
		//|  A  | |  R  |   |  G  | |  B  | //
		//////////////////////////////////////
	case ARGB4444:
		A = (((colorDt & 0xf000) >> 12) * 0x11);
		R = ((colorDt & 0x0f00) >> 8 << 4);
		G = ((colorDt & 0x00f0) >> 4 << 4);
		B = ((colorDt & 0x000f) >> 0 << 4);
		break;
		//////////////////////////////////////
		///////////////ARGB1555///////////////
		//1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //
		//A |   R   | |     G   | |   B   | //
		//////////////////////////////////////
	case ARGB1555:
		A = (((colorDt & 0x8000) >> 15) * 0xff);
		R = ((colorDt & 0x7c00) >> 10 << 3);
		G = ((colorDt & 0x03e0) >> 5 << 3);
		B = ((colorDt & 0x001f) >> 0 << 3);
		break;
		//////////////////
		//索引颜色调色板//
		/////ABGR8888/////
		//////////////////
	case INDEX_FMT_PALETTE:
		A = ((colorDt & 0xff000000) >> 24);
		R = ((colorDt & 0x000000ff) >> 0);
		G = ((colorDt & 0x0000ff00) >> 8);
		B = ((colorDt & 0x00ff0000) >> 16);
		break;
	default:
		set(colorDt, ARGB8888);
		break;
	}
}
void color::make(dword &colorDt, colorFormat clrFmt){
	switch(clrFmt){
	case ARGB8888:
		colorDt = (A<<24)|(R<<16)|(G<<8)|B;
		break;
	case ARGB4444:
		colorDt = (A>>4<<12)|(R>>4<<8)|(G>>4<<4)|(B>>4);
		break;
	case ARGB1555:
		colorDt = (A>>7<<15)|(R>>3<<10)|(G>>3<<5)|(B>>3);
		break;
	case INDEX_FMT_PALETTE:
		colorDt = (A<<24)|R|(G<<8)|(B<<16);
		break;
	default:
		colorDt = (A<<24)|(R<<16)|(G<<8)|B;
		break;
	}
}
color color::gray() const{
	 uchar gray = ((word)R*38 + (word)G*75 + (word)B*15) >> 7;
	 return color(0xFF, gray, gray, gray);
}
double color::getProperty(colorProperty theProperty) const{
	colorHSV theHSV;
	switch(theProperty){
	case COLOR_ALPHA:
		return (double)A/255;
	case COLOR_CHANNEL_BLUE:
		return (double)B/255;
	case COLOR_CHANNEL_GREEN:
		return (double)G/255;
	case COLOR_CHANNEL_RED:
		return (double)R/255;
	case COLOR_GRAYSCALE:
		return (double)(((word)R*38 + (word)G*75 + (word)B*15) >> 7 )/255;
	case COLOR_HUE:
		getHSV(theHSV);
		return (double)theHSV.H/360;
	case COLOR_SATURATION:
		getHSV(theHSV);
		return theHSV.S;
	case COLOR_VALUE:
		getHSV(theHSV);
		return theHSV.V;
	default:
		return 0;
	}
}
color::operator dword() const{
	return (dword)(A<<24)|(R<<16)|(G<<8)|B;
}
double color::mixMethod(double a, double b, colorMethod method){
	double c;
	switch(method){
	case LAY://覆盖
		c = a;
		break;
	case DARKEN://变暗
		c = MIN(a,b);
		break;
	case MULTIPLY://正片叠底
		c = a*b;
		break;
	case COLORBURN://颜色加深
		c = (a+b-1)/b;
		break;
	case LINEARBURN://线性加深
		c = a+b-1;
		break;
	case LIGHTEN://变亮
		c = MAX(a,b);
		break;
	case SCREEN://滤色
		c = a+b-a*b;
		break;
	case COLORDODGE://颜色减淡
		c = a/(1-b);
		break;
	case LINEARDODGE://线性减淡
		c = a+b;
		break;
	case OVERLAY://叠加
		c = (a<0.5)?(2*a*b):(2*(a+b-a*b)-1);
		break;
	case HARDLIGHT://强光
		c = (b<0.5)?(2*a*b):(2*(a+b-a*b)-1);
		break;
	case SOFTLIGHT://柔光
		c = (b<0.5)?(2*a*b+a*a*(1-2*b)):(2*a*(1-b)+sqrt(a)*(2*b-1));
		break;
	case VIVIDLIGHT://亮光
		c = (b<0.5)?((a-1)/2/b+1):(a/2/(1-b));
		break;
	case LINEARLIGHT://线性光
		c = a+2*b-1;
		break;
	case PINLIGHT://点光
		c = (b<0.5)?(MIN(a,2*b)):(MIN(a,2*b-1));
		break;
	case HARDMIX://实色混合
		c = (a+b>1)?1:0;
		break;
	case DIFFER://差值
		c = (a>b)?(a-b):(b-a);
		break;
	case EXCLUSION://排除
		c = a+b-a*b;
		break;
	default://缺省
		c=a;
		break;
	}
	if(c>1){
		c = 1;
	}
	if(c<0){
		c = 0;
	}
	return c;
}
uchar color::mixMethod(uchar a, uchar b, colorMethod method){
	long C,B,A;
	B = b;
	A = a;
	switch(method){
	case LAY://覆盖
		C = A;
		break;
	case DARKEN://变暗
		C = MIN(A,B);
		break;
	case MULTIPLY://正片叠底
		C = A*B/255;
		break;
	case COLORBURN://颜色加深
		C = A-(255-A)*(255-B)/B;
		break;
	case LINEARBURN://线性加深
		C = A+B-255;
		break;
	case LIGHTEN://变亮
		C = MAX(A,B);
		break;
	case SCREEN://滤色
		C = 255-(255-A)*(255-B)/255;
		break;
	case COLORDODGE://颜色减淡
		C = A+A*B/(255-B);
		break;
	case LINEARDODGE://线性减淡
		C = A+B;
		break;
	case OVERLAY://叠加
		C = (A<=128)?(A*B/128):(255-(255-A)*(255-B)/128);
		break;
	case HARDLIGHT://强光
		C = (B<=128)?(A*B/128):(255-(255-A)*(255-B)/128);
		break;
	case SOFTLIGHT://柔光
		C = (B<=128)?(A*B/128+A*A*(255-B)/255/255):(A*(255-B)/128+sqrt((double)(A/255))*(2*B-255));
		break;
	case VIVIDLIGHT://亮光
		C = (B<=128)?(A-(255-A)*(255-2*B)/2/B):(A+A*(B*2-255)/(255-B)/2);
		break;
	case LINEARLIGHT://线性光
		C = A+B*2-255;
		break;
	case PINLIGHT://点光
		C = (B<=128)?(MIN(A,2*B)):(MIN(A,2*B-1));
		break;
	case HARDMIX://实色混合
		C = (A+B>255)?255:0;
		break;
	case DIFFER://差值
		C = (A>B)?(A-B):(B-A);
		break;
	case EXCLUSION://排除
		C = A+B-A*B/255;
		break;
	default://缺省
		C=A;
		break;
	}
	if(C>255){
		C = 255;
	}
	if(C<0){
		C = 0;
	}
	return (word)C;
}
void color::mixWith(const color &clr2, colorMethod method){
	double a1 = (double)A/255;
	double r1 = (double)R/255;
	double g1 = (double)G/255;
	double b1 = (double)B/255;
	double a2 = (double)clr2.A/255;
	double r2 = (double)clr2.R/255;
	double g2 = (double)clr2.G/255;
	double b2 = (double)clr2.B/255;
	double a = a1 + a2 - a1*a2;
	double r,g,b;
	if(method == LAY){
		r = r1*a1+r2*(1-a1);
		g = g1*a1+g2*(1-a1);
		b = b1*a1+b2*(1-a1);
	}else{
		r = mixMethod(r1,r2,method);
		g = mixMethod(g1,g2,method);
		b = mixMethod(b1,b2,method);
	}
	A = a*255;
	R = r*255;
	G = g*255;
	B = b*255;
}
color color::mix(const color &clr1, const color &clr2, colorMethod method){
	color clr3 = clr1;
	clr3.mixWith(clr2, method);
	return clr3;
}

void color::getHSV(colorHSV &hsv) const{
	double r = (double)R/255;
	double g = (double)G/255;
	double b = (double)B/255;
	double maxclr, minclr;
	if(r>=g && r>=b)
		maxclr = r;
	if(b>=g && b>=r)
		maxclr = b;
	if(g>=b && g>=r)
		maxclr = g;
	if(r>=g && b>=g)
		minclr = g;
	if(b>=r && g>=r)
		minclr = r;
	if(g>=b && r>=b)
		minclr = b;
	hsv.V = maxclr;
	if(hsv.V==0){
		hsv.S = 0;
	}else{
		hsv.S = (maxclr-minclr)/maxclr;
	}
	if(hsv.S == 0){
		hsv.H = 0;
	}else{
		if(maxclr == r)
			hsv.H = 60*(g-b)/(maxclr-minclr);
		if(maxclr == g)
			hsv.H = 120+60*(b-r)/(maxclr-minclr);
		if(maxclr == b)
			hsv.H = 240+60*(r-g)/(maxclr-minclr);
		if(hsv.H<0)
			hsv.H += 360;
	}
}
void color::useHSV(const colorHSV &hsv){
	long h = hsv.H/60;
	double f = (double)hsv.H/60 - h;
	double v = hsv.V;
	double p = hsv.V*(1-hsv.S);
	double q = hsv.V*(1-f*hsv.S);
	double t = hsv.V*(1-(1-f)*hsv.S);
	switch(h){
	case 0:
		R = v*255;
		G = t*255;
		B = p*255;
		break;
	case 1:
		R = q*255;
		G = v*255;
		B = p*255;
		break;
	case 2:
		R = p*255;
		G = v*255;
		B = t*255;
		break;
	case 3:
		R = p*255;
		G = q*255;
		B = v*255;
		break;
	case 4:
		R = t*255;
		G = p*255;
		B = v*255;
		break;
	case 5:
		R = v*255;
		G = p*255;
		B = q*255;
		break;
	}
}
void color::moveHto(long newH){
	colorHSV hsv;
	getHSV(hsv);
	hsv.H = newH;
	hsv.H %= 360;
	useHSV(hsv);
}
void color::moveSto(double newS){
	colorHSV hsv;
	getHSV(hsv);
	hsv.S = newS;
	if(hsv.S >= 1)
		hsv.S = 1;
	if(hsv.S <= 0)
		hsv.S = 0;
	useHSV(hsv);
}
void color::moveVto(double newV){
	colorHSV hsv;
	getHSV(hsv);
	hsv.V = newV;
	if(hsv.V >= 1)
		hsv.V = 1;
	if(hsv.V <= 0)
		hsv.V = 0;
	useHSV(hsv);
}
void color::moveH(long delta){
	colorHSV hsv;
	getHSV(hsv);
	hsv.H += 360 + delta;
	hsv.H %= 360;
	useHSV(hsv);
}
void color::moveS(double delta){
	colorHSV hsv;
	getHSV(hsv);
	hsv.S += delta;
	if(hsv.S >= 1)
		hsv.S = 1;
	if(hsv.S <= 0)
		hsv.S = 0;
	useHSV(hsv);
}
void color::moveV(double delta){
	colorHSV hsv;
	getHSV(hsv);
	hsv.V += delta;
	if(hsv.V >= 1)
		hsv.V = 1;
	if(hsv.V <= 0)
		hsv.V = 0;
	useHSV(hsv);
}
void color::moveRto(uchar newR){
	R = newR;
}
void color::moveGto(uchar newG){
	G = newG;
}
void color::moveBto(uchar newB){
	B = newB;
}
void color::moveR(short delta){
	if(R + delta>255){
		R = 255;
	}else if(R + delta<0){
		R = 0;
	}else{
		R += delta;
	}
}
void color::moveG(short delta){
	if(G + delta>255){
		G = 255;
	}else if(G + delta<0){
		G = 0;
	}else{
		G += delta;
	}
}
void color::moveB(short delta){
	if(B + delta>255){
		B = 255;
	}else if(B + delta<0){
		B = 0;
	}else{
		B += delta;
	}
}
void color::moveA(short delta){
	if(A + delta>255){
		A = 255;
	}else if(A + delta<0){
		A = 0;
	}else{
		A += delta;
	}
}
int color::EuclideanDistanceSquareOf(const color &a, const color &b){
	return (int)(a.R-b.R)*(a.R-b.R)+(a.G-b.G)*(a.G-b.G)+(a.B-b.B)*(a.B-b.B);
}
color color::lose(const color &c, uchar part){
	return color(c.A, c.R/part*part, c.G/part*part, c.B/part*part);
}
color color::loseBit(const color &c, uchar bit){
	return color(c.A, c.R>>bit<<bit, c.G>>bit<<bit, c.B>>bit<<bit);
}
color color::loseBlack(const color &c, uchar gamma){
	uchar newR = c.R;
	uchar newG = c.G;
	uchar newB = c.B;
	uchar newA = 255 - (255 - newR)  * (255 - newG)  * (255 - newB)/ 255/ 255;
	double gm = pow((double)newA/255, gamma);
	newA = gm*255;
	return color(c.A*newA/255, newR, newG, newB);
}
///////////////////////////////////////////////////////////////
//point & size
point::point(){
	set(0,0);
}
point::point(long x, long y){
	set(x,y);
}
void point::set(long x, long y){
	X = x;
	Y = y;
}
void point::moveHonz(long dist){
	X += dist;
}
void point::moveVert(long dist){
	Y += dist;
}
void point::move(long honzDist, long vertDist){
	set(X+honzDist, Y+vertDist);
}
void point::move(size sz){
	set(X+sz.W, Y+sz.H);
}
point point::oppo() const{
	return point(-X, -Y);
}
point point::operator + (const point &delta) const{
	return point(X + delta.X, Y + delta.Y);
}
point point::operator - (const point &delta) const{
	return point(X - delta.X, Y - delta.Y);
}
point point::operator + (const size &sz) const{
	return point(X + sz.W, Y + sz.H);
}
point point::operator - (const size &sz) const{
	return point(X - sz.W, Y - sz.H);
}
point point::operator + () const{
	return point(X, Y);
}
point point::operator - () const{
	return point(-X, -Y);
}
point point::operator * (const double mult) const{
	return point(X*mult, Y*mult);
}
point point::operator / (const double mult) const{
	return point(X/mult, Y/mult);
}
point point::operator ~ () const{
	return point(Y, X);
}
size::size(){
	set(0,0);
}
size::size(long w, long h){
	set(w,h);
}
void size::set(long w, long h){
	W = w;
	H = h;
}
long size::area() const{
	return W*H;
}
matrix::matrix(){
	column = 0;
	row = 0;
	pt = 0;
	data = NULL;
}
matrix::matrix(dword _row, dword _column){
	column = _column;
	row = _row;
	pt = 0;
	data = new color[column*row+1000];
	fill(0);
}
matrix::matrix(const size &_sz){
	column = _sz.W;
	row = _sz.H;
	pt = 0;
	data = new color[column*row+1000];
	fill(0);
}
matrix::matrix(const matrix &_mat){
	column = _mat.column;
	row = _mat.row;
	pt = 0;
	data = new color[column*row+1000];
	if(data)
		memcpy(data, _mat.data, 4*column*row+1000);
}
matrix::~matrix(){
	destory();
}
matrix& matrix::operator = (const matrix &_mat){
	if(this == &_mat)
		return *this;
	if(data)
		delete[] data;
	column = _mat.column;
	row = _mat.row;
	data = new color[column*row+1000];
	pt = 0;
	if(data)
		memcpy(data, _mat.data, 4*column*row+1000);
	return *this;
}

bool matrix::valid(){
	return !(data == NULL);
}
void matrix::create(dword _row, dword _column){
	if(!data){
		row  = _row;
		column = _column;
		data = new color[row*column+1000];
		pt = 0;
		fill(0);
	}
}
void matrix::create(const size &_sz){
	if(!data){
		row  = _sz.H;
		column = _sz.W;
		data = new color[row*column+1000];
		pt = 0;
		fill(0);
	}
}
void matrix::destory(){
	if(data){
		delete[] data;
		data = NULL;
		column = 0;
		row = 0;
		pt = 0;
	}
}

void matrix::fill(color _clr){
	for(dword i = 0; i< column*row ; i++)
		data[i] = _clr;
}

void matrix::push(color _clr){
	data[pt] = _clr;
	if(pt != column*row - 1)
		pt++;
}

longex matrix::push(const stream &s, colorFormat cf){
	dword len = s.getLen();
	dword i = 0;
	switch(cf){
	case ARGB8888:
		while(i+3<len){
			push(color(s[i+3], s[i+2], s[i+1], s[i+0]));
			i+=4;
		}
		break;
	case ARGB4444:
		while(i+1<len){
			push(color(s[i+1]<<8 | s[i+0], ARGB4444));
			i+=2;
		}
		break;
	case ARGB1555:
		while(i+1<len){
			push(color(s[i+1]<<8 | s[i+0], ARGB1555));
			i+=2;
		}
		break;
	case INDEX_FMT_PALETTE:
		while(i<len){
			push(color(s[i], 0, 0, 0));
			i++;
		}
		break;
	default:
		return push(s, ARGB8888);
		break;
	}
	return i;
}

longex matrix::make(stream &s, colorFormat cf) const{
	dword i = 0;
	dword colorData;
	switch(cf){
	case ARGB8888:
		s.allocate(4*column*row);
		for(i = 0; i< column*row; i++){
			data[i].make(colorData,ARGB8888);
			s.push(colorData);
		}
		break;
	case ARGB4444:
		s.allocate(2*column*row);
		for(i = 0; i< column*row; i++){
			data[i].make(colorData,ARGB4444);
			s.push((word)(colorData & 0xFFFF));
		}
		break;
	case ARGB1555:
		s.allocate(2*column*row);
		for(i = 0; i< column*row; i++){
			data[i].make(colorData,ARGB1555);
			s.push((word)(colorData & 0xFFFF));
		}
		break;
	case INDEX_FMT_PALETTE:
		s.allocate(column*row);
		for(i = 0; i< column*row; i++){
			s.push((uchar)data[i].A);
		}
		break;
	}
	return s.getPtPos();
}

color *matrix::operator[] (dword _i) const{
	return data + _i*column;
}
long matrix::getHeight() const{
	return row;
}
long matrix::getWidth() const{
	return column;
}
long matrix::getElemCount() const{
	return row*column;
}	
//取子阵
void matrix::clip(matrix &dest, dword rowStart, dword rowEnd, dword columnStart, dword columnEnd) const{
	if(rowEnd>row)
		rowEnd = row;
	if(rowStart>rowEnd)
		rowStart = rowEnd;
	if(columnEnd>column)
		columnEnd = column;
	if(columnStart>columnEnd)
		columnStart = columnEnd;
	dest.create(rowEnd-rowStart, columnEnd-columnStart);
	dword i,j;
	for(i=0;i<rowEnd-rowStart;i++){
		for(j=0;j<columnEnd-columnStart;j++){
			dest.push(data[columnStart+j+(rowStart+i)*column]);
		}
	}
}
void matrix::expand(matrix &dest, dword toTop, dword toBottom, dword toLeft, dword toRight) const{
	dest.create(row+toTop+toBottom, column+toLeft+toRight);
	dword i,j;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			dest.setElem(i+toTop, j+toLeft, getElem(i,j));
		}
	}
}
void matrix::zoom(matrix &dest, double ratio) const{
	dest.create(row*ratio, column*ratio);
	dword i,j;
	for(i=0;i<row*ratio;i++){
		for(j=0;j<column*ratio;j++){
			dest.setElem(i, j, getElem(i/ratio,j/ratio));
		}
	}
}
void matrix::zoom(matrix &dest, double honzRatio, double vertRatio) const{
	dest.create(row*vertRatio, column*honzRatio);
	dword i,j;
	for(i=0;i<row*vertRatio;i++){
		for(j=0;j<column*honzRatio;j++){
			dest.setElem(i, j, getElem(i/vertRatio,j/honzRatio));
		}
	}
}
void matrix::clip(dword rowStart, dword rowEnd, dword columnStart, dword columnEnd){
	matrix dest;
	clip(dest, rowStart, rowEnd, columnStart, columnEnd);
	destory();
	*this = dest;
	dest.destory();
}
void matrix::expand(dword toTop, dword toBottom, dword toLeft, dword toRight){
	matrix dest;
	expand(dest, toTop, toBottom, toLeft, toRight);
	destory();
	*this = dest;
	dest.destory();
}
void matrix::zoom(double ratio){
	matrix dest;
	zoom(dest, ratio);
	*this = dest;
	dest.destory();
}
void matrix::zoom(double honzRatio, double vertRatio){
	matrix dest;
	zoom(dest, honzRatio, vertRatio);
	destory();
	*this = dest;
	dest.destory();
}
//元素统计
void matrix::setElem(dword _id, const color &_clr){
	data[_id] = _clr;
}
void matrix::setElem(dword _row, dword _column, const color &_clr){
	if(_row > row - 1 || _column > column - 1){
		return;
	}
	data[_row*column+_column] = _clr;
}
color matrix::getElem(dword _id) const{
	return data[_id];
}
color matrix::getElem(dword _row, dword _column) const{
	return data[_row*column+_column];
}
long matrix::getElemCountNzero() const{
	dword total = 0;
	for(dword i = 0;i<getElemCount();i++){
		if(data[i] != (color)0){
			total ++;
		}
	}
	return total;
}
long matrix::getElemCountWhos(const color &whos) const{
	dword total = 0;
	for(dword i = 0;i<getElemCount();i++){
		if(data[i] == whos){
			total ++;
		}
	}
	return total;
}
void matrix::getElemCountList(colorList &colorList) const{
	colorList.clear();
	color temp;
	dword i,j,k;
	bool flag;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			temp = getElem(i, j);
			flag = false;
			for(k=0;k<colorList.size();k++){
				if(colorList[k] == temp){
					flag = true;
					break;
				}
			}
			if(!flag){
				colorList.push_back(temp);
			}
		}
	}
}
void matrix::getElemHonzBound(dword &lower, dword &upper) const{
	lower = column - 1;
	upper = 0;
	dword i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			if(getElem(i, j).A != 0){
				if(lower>j){
					lower = j;
				}
				if(upper<j){
					upper = j;
				}
			}
		}
	}
}
void matrix::getElemVertBound(dword &lower, dword &upper) const{
	lower = row - 1;
	upper = 0;
	dword i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			if(getElem(i, j).A != 0){
				if(lower>i){
					lower = i;
				}
				if(upper<i){
					upper = i;
				}
			}
		}
	}
}
//操作矩阵
long matrix::moveHonz(long dist, const color &surplus){
	long i,j;
	color _clr;
	for(i = 0;i<row;i++){
		if(dist>0){
			for(j = column -1;j>=0;j--){
				if(j>dist-1){
					_clr = getElem(i, j-dist);
					setElem(i, j, _clr);
				}else{
					setElem(i, j, surplus);
				}
			}
		}else{
			for(j = 0;j<column;j++){
				if(j<column+dist){
					_clr = getElem(i, j-dist);
					setElem(i,j,_clr);
				}else{
					setElem(i,j, surplus);
				}
			}
		}
	}
	return 1;
}
long matrix::moveVert(long dist, const color &surplus){
	long i,j;
	color _clr;
	for(j = 0;j<column;j++){
		if(dist>0){
			for(i = row -1;i>=0;i--){
				if(i>dist-1){
					_clr = getElem(i-dist, j);
					setElem(i, j, _clr);
				}else{
					setElem(i, j, surplus);
				}
			}
		}else{
			for(i = 0;i<row;i++){
				if(i<row+dist){
					_clr = getElem(i-dist, j);
					setElem(i,j,_clr);
				}else{
					setElem(i,j,surplus);
				}
			}
		}
	}
	return 1;
}
long matrix::replace(const color &whos, const color &to){
	dword i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			if(getElem(i, j) == whos){
				setElem(i, j ,to);
			}
		}
	}
	return 1;
}


void matrix::putFore(const matrix &layer, colorMethod met, point basePoint){
	dword i,j, tx, ty;
	color clr;
	for(i=0;i<layer.getWidth();i++){
		for(j=0;j<layer.getHeight();j++){
			tx = i + basePoint.X;
			ty = j + basePoint.Y;
			if(tx >= 0 && tx < getWidth() && ty >= 0 && ty < getHeight()){
				clr = layer[j][i];
				clr.mixWith(getElem(ty,tx), met);
				setElem(ty,tx,clr);
			}
		}
	}
}
void matrix::putBack(const matrix &layer, colorMethod met, point basePoint){
	dword i,j, tx, ty;
	color clr;
	for(i=0;i<layer.getWidth();i++){
		for(j=0;j<layer.getHeight();j++){
			tx = i + basePoint.X;
			ty = j + basePoint.Y;
			if(tx >= 0 && tx < getWidth() && ty >= 0 && ty < getHeight()){
				clr = getElem(ty,tx);
				clr.mixWith(layer[j][i], met);
				setElem(ty,tx,clr);
			}
		}
	}
}

void matrix::lose(uchar fine){
	dword i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			setElem(i, j ,Koishi::color::lose(getElem(i,j),fine));
		}
	}
}
void matrix::loseBit(uchar bit){
	dword i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			setElem(i, j ,Koishi::color::loseBit(getElem(i,j),bit));
		}
	}
}
void matrix::loseBlack(uchar gamma){
	dword i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			setElem(i, j ,Koishi::color::loseBlack(getElem(i,j),gamma));
		}
	}
}
void matrix::turnShield(){
	dword i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			color clr = getElem(i, j);
			clr.R = 0xFF;
			clr.G = 0xFF;
			clr.B = 0xFF;
			clr.A /= 2;
			setElem(i, j ,clr);
		}
	}
}
void matrix::line(point p1, point p2, const color &clr){
	//数值微分法画线
	long dx = p2.X - p1.X;
	long dy = p2.Y - p1.Y;
	long n = MAX(abs(dx), abs(dy));
	double xdelta = (double)dx/n;
	double ydelta = (double)dy/n;
	double x = p1.X;
	double y = p1.Y;
	for(long i=0;i<=n;i++){
		setElem((long)(y+0.5), (long)(x+0.5), clr);
		x += xdelta;
		y += ydelta;
	}
}
void matrix::rectangle(point p1, point p2, const color &clr){
	//画矩形
	long x1 = MIN(p1.X, p2.X);
	long x2 = MAX(p1.X, p2.X);
	long y1 = MIN(p1.Y, p2.Y);
	long y2 = MAX(p1.Y, p2.Y);
	for(long i = x1;i<=x2;i++){
		setElem(y1,i,clr);
		setElem(y2,i,clr);
	}
	for(long i = y1;i<=y2;i++){
		setElem(i,x1,clr);
		setElem(i,x2,clr);
	}
}
void matrix::filledRectangle(point p1, point p2, const color &clr){
	long x1 = MIN(p1.X, p2.X);
	long x2 = MAX(p1.X, p2.X);
	long y1 = MIN(p1.Y, p2.Y);
	long y2 = MAX(p1.Y, p2.Y);
	for(long i = x1;i<=x2;i++){
		for(long j = y1;j<=y2;j++){
			setElem(j,i,clr);
		}
	}
}
void matrix::filledLattice(point p1, point p2, const color &clr1, const color &clr2, long size){
	long x1 = MIN(p1.X, p2.X);
	long x2 = MAX(p1.X, p2.X);
	long y1 = MIN(p1.Y, p2.Y);
	long y2 = MAX(p1.Y, p2.Y);
	for(long i = x1;i<=x2;i++){
		for(long j = y1;j<=y2;j++){
			if(i % size < size/2 && j % size < size/2 || i % size >= size/2 && j % size >= size/2){
				setElem(j,i,clr1);
			}else{
				setElem(j,i,clr2);
			}
		}
	}
}

palette::palette(){
	clear();
}
palette::~palette(){
}
colorList& palette::operator[] (long i){
	return table[i];
}
void palette::clear(){
	table.clear();
}
void palette::push(const colorList &list){
	table.push_back(list);
}
void palette::remove(long paletteID){
	table.erase(table.begin() + paletteID);
}
long palette::getCount() const{
	return table.size();
}
long palette::getTotalColorCount() const{
	long total = 0;
	for(long i = 0;i<table.size();i++){
		total += table[i].size();
	}
	return total;
}
long palette::getColorCount(long paletteID) const{
	if(paletteID >= getCount()){
		return -1;
	}
	return table[paletteID].size();
}
long palette::findColor(color goalColor, long paletteID) const{
	if(paletteID >= getCount()){
		return -2;
	}
	colorList colorList = table[paletteID];
	for(long i = 0;i<colorList.size();i++){
		if(colorList[i] == goalColor){
			return i;
		}
	}
	return -1;
}
long palette::matchColor(color goalColor, long paletteID) const{
	long nearest;
	return matchColor(goalColor, paletteID, nearest);
}
//匹配规则：
//首先如果同为透明颜色则直接为匹配透明颜色·匹配距离为零
//如果本身不是透明颜色，则按RGB最短欧氏距离匹配
//如果本身不是透明颜色，但第一次匹配到的颜色是透明颜色，也以此匹配，等后续更新；若无更新则匹配距离依然为MAX
long palette::matchColor(color goalColor, long paletteID, long &nearestDistance) const{
	if(paletteID >= getCount())
		return -2;
	colorList colorList = table[paletteID];
	if(colorList.size() == 0)
		return 0;
	long nearestID = -1;
	nearestDistance = 3 * 0x100 * 0x100;
	for(long i = 0;i<colorList.size();i++){
		if(colorList[i].A == 0 && goalColor.A <= 0x7F){
			//匹配透明颜色
			nearestDistance = 0;
			return i;
		}else if(colorList[i].A == 0){
			//加此步是为了防止非透明颜色与透明颜色进行匹配
			continue;
		}else{
			//匹配普通颜色
			long newNearest = color::EuclideanDistanceSquareOf(colorList[i], goalColor);
			if(newNearest < nearestDistance){
				nearestDistance = newNearest;
				nearestID = i;
			}
		}
	}
	if(nearestID == -1){
		//找不到的话返回0
		nearestID = 0;
	}
	return nearestID;
}
bool palette::joinWith(const colorList &list, long paletteID){
	if(paletteID >= getCount()){
		return false;
	}
	colorList list2;
	list2.clear();
	long i;
	for(i = 0;i<list.size();i++){
		if(findColor(list[i], paletteID) < 0){
			list2.push_back(list[i]);
		}
	}
	if(getColorCount(paletteID)+list2.size() > 256){
		return false;
	}
	for(i = 0;i<list2.size();i++){
		table[paletteID].push_back(list2[i]);
	}
	return true;
}
bool palette::tinyMake(stream &s, long paletteID){
	if(paletteID >= getCount()){
		return false;
	}
	long i;
	colorList list = table[paletteID];
	s.allocate(sizeof(color)*(10+list.size()));
	s.push((long)list.size());
	for(i = 0;i<list.size();i++){
		s.push((uchar)list[i].R);
		s.push((uchar)list[i].G);
		s.push((uchar)list[i].B);
		s.push((uchar)list[i].A);
	}
	return false;
}
bool palette::bigMake(stream &s){
	long i,j;
	colorList list;
	s.allocate(sizeof(color)*(1000+getCount()+getTotalColorCount()));
	s.push((long)getCount());
	for(j=0;j<getCount();j++){
		list = table[j];
		s.push((long)list.size());
		for(i = 0;i<list.size();i++){
			s.push((uchar)list[i].R);
			s.push((uchar)list[i].G);
			s.push((uchar)list[i].B);
			s.push((uchar)list[i].A);
		}
	}
	return false;
}

bool palette::makeACT(str fileName, const colorList &lc){
	stream s;
	s.allocate(772);
	long alphaIndex = 0;
	for(long i = 0;i<256;i++){
		if(i<lc.size()){
			if(lc[i].A == 0){
				alphaIndex = i;
			}
			s.push(lc[i].R);
			s.push(lc[i].G);
			s.push(lc[i].B);
		}else{
			s.push((uchar)0);
			s.push((uchar)0);
			s.push((uchar)0);
		}
	}
	s.push((uchar)(lc.size() >> 8));
	s.push((uchar)(lc.size() & 0xff));
	s.push((uchar)0);
	s.push((uchar)(alphaIndex & 0xff));
	s.makeFile(fileName);
	s.release();
	return true;
}
bool palette::loadACT(str fileName, colorList &lc){
	stream s;
	s.loadFile(fileName);
	long len = s.getLen();
	if(len == 768){
		lc.clear();
		for(long i = 0;i<256;i++){
			lc.push_back(color(0xFF, s[3*i], s[3*i+1], s[3*i+2]));
		}
		return true;
	}else if(len == 772){
		long alphaIndex = s[771] | s[770] << 8;
		long clrCount = s[768] << 8 | s[769];
		if(clrCount >= 256){
			clrCount = 256;
		}
		lc.clear();
		for(long i = 0;i<clrCount;i++){
			lc.push_back(color(0xFF, s[3*i], s[3*i+1], s[3*i+2]));
		}
		if(alphaIndex < 256){
			lc[alphaIndex] = color(0, 0, 0, 0);
		}
		return true;
	}
	s.release();
	return false;
}
bool palette::makeCID(str fileName, const colorList &lc){
	stream s;
	s.allocate(lc.size()*4 + 100);
	s.pushString("KoishiColor");
	s.push((uchar)0);
	s.push((dword)lc.size());
	for(int i = 0;i<lc.size();i++){
		s.push((uchar)lc[i].A);
		s.push((uchar)lc[i].R);
		s.push((uchar)lc[i].G);
		s.push((uchar)lc[i].B);
	}
	s.makeFile(fileName);
	s.release();
	return true;
}
bool palette::loadCID(str fileName, colorList &lc){
	stream s;
	s.loadFile(fileName);
	s.ptMoveTo(12);
	dword clrCount;
	s.read(clrCount);
	for(int i = 0;i<clrCount;i++){
		uchar p;
		color clr;
		s.read(p);
		clr.A = p;
		s.read(p);
		clr.R = p;
		s.read(p);
		clr.G = p;
		s.read(p);
		clr.B = p;
	}
	s.release();
	return true;
}
colorList palette::palette2(){
	colorList cl;
	cl.push_back(color(0,0,0,0));
	cl.push_back(color(0xFF, 0xFF, 0xFF, 0xFF));
	cl.push_back(color(0xFF, 0x00, 0x00, 0x00));
	return cl;
}
colorList palette::palette16(){
	colorList cl;
	cl.push_back(color(0,0,0,0));
	cl.push_back(color(0xFF, 0xFF, 0xFF, 0xFF));
	cl.push_back(color(0xFF, 0xC0, 0xC0, 0xC0));
	cl.push_back(color(0xFF, 0xFF, 0x00, 0x00));
	cl.push_back(color(0xFF, 0xFF, 0xFF, 0x00));
	cl.push_back(color(0xFF, 0x00, 0xFF, 0x00));
	cl.push_back(color(0xFF, 0x00, 0xFF, 0xFF));
	cl.push_back(color(0xFF, 0x00, 0x00, 0xFF));
	cl.push_back(color(0xFF, 0xFF, 0x00, 0xFF));
	cl.push_back(color(0xFF, 0x00, 0x00, 0x00));
	cl.push_back(color(0xFF, 0x80, 0x80, 0x80));
	cl.push_back(color(0xFF, 0x80, 0x00, 0x00));
	cl.push_back(color(0xFF, 0x80, 0x80, 0x00));
	cl.push_back(color(0xFF, 0x00, 0x80, 0x00));
	cl.push_back(color(0xFF, 0x00, 0x80, 0x80));
	cl.push_back(color(0xFF, 0x00, 0x00, 0x80));
	cl.push_back(color(0xFF, 0x80, 0x00, 0x80));
	return cl;
}
colorList palette::palette64(){
	//rgb222
	colorList cl;
	uchar p[4] = {0, 0x55, 0xAA, 0xFF};
	cl.push_back(color(0,0,0,0));
	for(int i = 0;i<4;i++){
		for(int j = 0;j<4;j++){
			for(int k = 0;k<4;k++){
				if(i == 0 && j == 0 && k == 1)
					continue;
				cl.push_back(color(0xFF, p[i], p[j], p[k]));
			}
		}
	}
	return cl;
}
colorList palette::palette256(){
	//rgb332
	colorList cl;
	uchar rg3[8]  = {0, 0x24, 0x48, 0x6D, 0x91, 0xB5, 0xDA, 0xFF};
	uchar b2[4]  = {0, 0x55, 0xAA, 0xFF};
	cl.push_back(color(0,0,0,0));
	for(long i = 0;i<8;i++){
		for(long j = 0;j<8;j++){
			for(long k = 0;k<4;k++){
				if(i == 0 && j == 0 && k == 1)
					continue;
				cl.push_back(color(0xFF, rg3[i], rg3[j], b2[k]));
			}
		}
	}
	return cl;
}