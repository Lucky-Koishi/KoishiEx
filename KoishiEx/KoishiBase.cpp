#include "StdAfx.h"
#include "KoishiEx.h"
#include <math.h>

#define MIN(a,b) ((a)>(b)?b:a)
#define MAX(a,b) ((a)>(b)?a:b)

#pragma comment(lib, "libpng15.lib")
#include "png.h"

using namespace Koishi;


str Koishi::NPKheaderStr = "NeoplePack_Bill";
str Koishi::IMGheaderStr = "Neople Img File";
str Koishi::IMGheaderStr2 = "Neople Image File";
str Koishi::NPKext = ".npk";
str Koishi::IMGext = ".img";
str Koishi::IMGnameMask = "puchikon@neople dungeon and fighter DNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNFDNF";

//////////////////////////////////////////////////////////////
//color
color::color(){
	set(0);
}
color::color(b32 colorDt, colorFormat clrFmt){
	set(colorDt, clrFmt);
}
color::color(b8 r, b8 g, b8 b){
	set(0xff000000|(r<<16)|(g<<8)|b);
}
color::color(b8 a, b8 r, b8 g, b8 b){
	set((a<<24)|(r<<16)|(g<<8)|b);
}
void color::set(b32 colorDt, colorFormat clrFmt){
	switch(clrFmt){
		//////////////////////////////////////////////////////////////////////////
		/////////////////////////////////ARGB8888/////////////////////////////////
		//1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //
		//|      A      |   |      R      |   |      G      |   |      B      | //
		//////////////////////////////////////////////////////////////////////////
	case ARGB8888:
		set_A((colorDt & 0xff000000) >> 24);
		set_R((colorDt & 0x00ff0000) >> 16);
		set_G((colorDt & 0x0000ff00) >> 8);
		set_B((colorDt & 0x000000ff) >> 0);
		break;
		//////////////////////////////////////
		///////////////ARGB4444///////////////
		//1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //
		//|  A  | |  R  |   |  G  | |  B  | //
		//////////////////////////////////////
	case ARGB4444:
		set_A(((colorDt & 0xf000) >> 12) * 0x11);
		set_R((colorDt & 0x0f00) >> 8 << 4);
		set_G((colorDt & 0x00f0) >> 4 << 4);
		set_B((colorDt & 0x000f) >> 0 << 4);
		break;
		//////////////////////////////////////
		///////////////ARGB1555///////////////
		//1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //
		//A |   R   | |     G   | |   B   | //
		//////////////////////////////////////
	case ARGB1555:
		set_A(((colorDt & 0x8000) >> 15) * 0xff);
		set_R((colorDt & 0x7c00) >> 10 << 3);
		set_G((colorDt & 0x03e0) >> 5 << 3);
		set_B((colorDt & 0x001f) >> 0 << 3);
		break;
		////////////
		///V4专用///
		//ABGR8888//
		////////////
	case V4_FMT:
		set_A((colorDt & 0xff000000) >> 24);
		set_R((colorDt & 0x000000ff) >> 0);
		set_G((colorDt & 0x0000ff00) >> 8);
		set_B((colorDt & 0x00ff0000) >> 16);
		break;
	case RGB565:
		//////////////////////////////////////
		///////////////ARGB1555///////////////
		//1 1 1 1 1 1 1 1 //1 1 1 1 1 1 1 1 //
		//|   R   | |     G     | |   B   | //
		//////////////////////////////////////
		set_A(0xff);
		set_R((colorDt & 0xf800) >> 11 << 3);
		set_G((colorDt & 0x07e0) >> 5 << 2);
		set_B((colorDt & 0x001f) >> 0 << 3);
		break;
	default:
		set(colorDt);
		break;
	}
}
color color::getChannel(b8 _chn) const{
	color _clr;
	if((_chn & FA) != 0)
		_clr.set_A(A);
	if((_chn & FR) != 0)
		_clr.set_R(R);
	if((_chn & FG) != 0)
		_clr.set_G(G);
	if((_chn & FB) != 0)
		_clr.set_B(B);
	return _clr;
}
color::operator b32() const{
	return (b32)(A<<24)|(R<<16)|(G<<8)|B;
}
fl2 color::mixMethod(fl2 a, fl2 b, colorMethod _method){
	fl2 c;
	switch(_method){
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
b8 color::mixMethod(b8 a, b8 b, colorMethod _method){
	i32 C,B,A;
	B = b;
	A = a;
	switch(_method){
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
	return (b16)C;
}
void color::mixWith(const color &_clr2, colorMethod _method){
	fl2 a1 = (fl2)get_A()/255;
	fl2 r1 = (fl2)get_R()/255;
	fl2 g1 = (fl2)get_G()/255;
	fl2 b1 = (fl2)get_B()/255;
	fl2 a2 = (fl2)_clr2.get_A()/255;
	fl2 r2 = (fl2)_clr2.get_R()/255;
	fl2 g2 = (fl2)_clr2.get_G()/255;
	fl2 b2 = (fl2)_clr2.get_B()/255;
	fl2 a = a1 + a2 - a1*a2;
	fl2 r,g,b;
	if(_method == LAY){
		r = r1*a1+r2*(1-a1);
		g = g1*a1+g2*(1-a1);
		b = b1*a1+b2*(1-a1);
	}else{
		r = mixMethod(r1,r2,_method);
		g = mixMethod(g1,g2,_method);
		b = mixMethod(b1,b2,_method);
	}
	set_A(a*255);
	set_R(r*255);
	set_G(g*255);
	set_B(b*255);
}
color color::mix(const color &_clr1, const color &_clr2, colorMethod _method){
	color _clr3 = _clr1;
	_clr3.mixWith(_clr2, _method);
	return _clr3;
}

void color::getHSV(colorHSV &hsv) const{
	fl2 r = (fl2)R/255;
	fl2 g = (fl2)G/255;
	fl2 b = (fl2)B/255;
	fl2 maxclr, minclr;
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
	i32 h = hsv.H/60;
	fl2 f = (fl2)hsv.H/60 - h;
	fl2 v = hsv.V;
	fl2 p = hsv.V*(1-hsv.S);
	fl2 q = hsv.V*(1-f*hsv.S);
	fl2 t = hsv.V*(1-(1-f)*hsv.S);
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
void color::moveHto(i32 newH){
	colorHSV hsv;
	getHSV(hsv);
	hsv.H = newH;
	hsv.H %= 360;
	useHSV(hsv);
}
void color::moveSto(fl2 newS){
	colorHSV hsv;
	getHSV(hsv);
	hsv.S = newS;
	if(hsv.S >= 1)
		hsv.S = 1;
	if(hsv.S <= 0)
		hsv.S = 0;
	useHSV(hsv);
}
void color::moveVto(fl2 newV){
	colorHSV hsv;
	getHSV(hsv);
	hsv.V = newV;
	if(hsv.V >= 1)
		hsv.V = 1;
	if(hsv.V <= 0)
		hsv.V = 0;
	useHSV(hsv);
}
void color::moveH(i32 delta){
	colorHSV hsv;
	getHSV(hsv);
	hsv.H += 360 + delta;
	hsv.H %= 360;
	useHSV(hsv);
}
void color::moveS(fl2 delta){
	colorHSV hsv;
	getHSV(hsv);
	hsv.S += delta;
	if(hsv.S >= 1)
		hsv.S = 1;
	if(hsv.S <= 0)
		hsv.S = 0;
	useHSV(hsv);
}
void color::moveV(fl2 delta){
	colorHSV hsv;
	getHSV(hsv);
	hsv.V += delta;
	if(hsv.V >= 1)
		hsv.V = 1;
	if(hsv.V <= 0)
		hsv.V = 0;
	useHSV(hsv);
}
void color::moveRto(b8 newR){
	R = newR;
}
void color::moveGto(b8 newG){
	G = newG;
}
void color::moveBto(b8 newB){
	B = newB;
}
void color::moveR(i16 delta){
	if(R + delta>255){
		R = 255;
	}else if(R + delta<0){
		R = 0;
	}else{
		R += delta;
	}
}
void color::moveG(i16 delta){
	if(G + delta>255){
		G = 255;
	}else if(G + delta<0){
		G = 0;
	}else{
		G += delta;
	}
}
void color::moveB(i16 delta){
	if(B + delta>255){
		B = 255;
	}else if(B + delta<0){
		B = 0;
	}else{
		B += delta;
	}
}
void color::moveA(i16 delta){
	if(A + delta>255){
		A = 255;
	}else if(A + delta<0){
		A = 0;
	}else{
		A += delta;
	}
}
///////////////////////////////////////////////////////////////
//point & size
point::point(){
	set(0,0);
}
point::point(i32 x, i32 y){
	set(x,y);
}
void point::set(i32 x, i32 y){
	set_X(x);
	set_Y(y);
}
void point::moveHonz(i32 dist){
	set_X(X+dist);
}
void point::moveVert(i32 dist){
	set_Y(Y+dist);
}
void point::move(i32 honzDist, i32 vertDist){
	set(X+honzDist, Y+vertDist);
}
void point::move(size sz){
	set(X+sz.get_W(), Y+sz.get_H());
}
size::size(){
	set(0,0);
}
size::size(i32 w, i32 h){
	set(w,h);
}
void size::set(i32 w, i32 h){
	set_W(w);
	set_H(h);
}
i32 size::area() const{
	return get_W()*get_H();
}
matrix::matrix(){
	column = 0;
	row = 0;
	pt = 0;
	data = NULL;
}
matrix::matrix(b32 _row, b32 _column){
	column = _column;
	row = _row;
	pt = 0;
	data = new color[column*row+1000];
	fill(0);
}
matrix::matrix(const size &_sz){
	column = _sz.get_W();
	row = _sz.get_H();
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
	release();
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

void matrix::allocate(b32 _row, b32 _column){
	if(!data){
		row  = _row;
		column = _column;
		data = new color[row*column+1000];
		pt = 0;
		fill(0);
	}
}
void matrix::allocate(const size &_sz){
	if(!data){
		row  = _sz.get_H();
		column = _sz.get_W();
		data = new color[row*column+1000];
		pt = 0;
		fill(0);
	}
}
void matrix::release(){
	if(data){
		delete[] data;
		data = NULL;
		column = 0;
		row = 0;
		pt = 0;
	}
}

void matrix::fill(color _clr){
	for(b32 i = 0; i< column*row ; i++)
		data[i] = _clr;
}

void matrix::push(color _clr){
	data[pt] = _clr;
	if(pt != column*row - 1)
		pt++;
}

b64 matrix::push(const stream &_s, colorFormat cf){
	b32 len = _s.getLen();
	b32 i = 0;
	switch(cf){
		case ARGB4444:
		while(i+1<len){
			//一个字节一个字节读的话是B/G/R/A
			push(color(_s[i+1]<<8 | _s[i+0], ARGB4444));
			i+=2;
		}
		break;
		case ARGB1555:
		while(i+1<len){
			//一个字节一个字节读的话是B/G/R/A
			push(color(_s[i+1]<<8 | _s[i+0], ARGB1555));
			i+=2;
		}
		break;
		default:
		while(i+3<len){
			//一个字节一个字节读的话是B/G/R/A
			push(color(_s[i+3], _s[i+2], _s[i+1], _s[i+0]));
			i+=4;
		}
		break;
	}
	return i;
}

b64 matrix::make(stream &_s) const{
	_s.allocate(4*column*row);
	for(b32 i = 0; i< column*row; i++){
		_s.push(data[i].get_B());
		_s.push(data[i].get_G());
		_s.push(data[i].get_R());
		_s.push(data[i].get_A());
	}
	return _s.ptPos();
}

pcolor matrix::operator[] (b32 _i) const{
	return data + _i*column;
}

b32 matrix::getRowCount() const{
	return row;
}
b32 matrix::getColumnCount() const{
	return column;
}
b32 matrix::getElemCount() const{
	return row*column;
}	
//取子阵
void matrix::getSubMatrix(matrix &dest, b32 rowStart, b32 rowEnd, b32 columnStart, b32 columnEnd) const{
	if(rowEnd>row)
		rowEnd = row;
	if(rowStart>rowEnd)
		rowStart = rowEnd;
	if(columnEnd>column)
		columnEnd = column;
	if(columnStart>columnEnd)
		columnStart = columnEnd;
	dest.allocate(rowEnd-rowStart, columnEnd-columnStart);
	b32 i,j;
	for(i=0;i<rowEnd-rowStart;i++){
		for(j=0;j<columnEnd-columnStart;j++){
			dest.push(data[columnStart+j+(rowStart+i)*column]);
		}
	}
}
void matrix::getChannelMatrix(matrix &dest, b8 _chn) const{
	dest.allocate(row, column);
	for(b32 i = 0;i<getElemCount();i++){
		dest.push(data[i].getChannel(_chn));
	}
}
void matrix::expandMatrix(matrix &dest, b32 toTop, b32 toBottom, b32 toLeft, b32 toRight) const{
	dest.allocate(row+toTop+toBottom, column+toLeft+toRight);
	b32 i,j;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			dest.setElem(i+toTop, j+toLeft, getElem(i,j));
		}
	}
}
//元素统计
void matrix::setElem(b32 _id, const color &_clr){
	data[_id] = _clr;
}
void matrix::setElem(b32 _row, b32 _column, const color &_clr){
	data[_row*column+_column] = _clr;
}
color matrix::getElem(b32 _id) const{
	return data[_id];
}
color matrix::getElem(b32 _row, b32 _column) const{
	return data[_row*column+_column];
}
b32 matrix::getElemCountNzero() const{
	b32 total = 0;
	for(b32 i = 0;i<getElemCount();i++){
		if(data[i] != (color)0){
			total ++;
		}
	}
	return total;
}
b32 matrix::getElemCountWhos(const color &whos) const{
	b32 total = 0;
	for(b32 i = 0;i<getElemCount();i++){
		if(data[i] == whos){
			total ++;
		}
	}
	return total;
}
void matrix::getElemCountList(lcolor &colorList) const{
	colorList.clear();
	color temp;
	b32 i,j,k;
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
void matrix::getElemHonzBound(b32 &lower, b32 &upper) const{
	lower = column - 1;
	upper = 0;
	b32 i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			if(getElem(i, j).get_A() != 0){
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
void matrix::getElemVertBound(b32 &lower, b32 &upper) const{
	lower = row - 1;
	upper = 0;
	b32 i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			if(getElem(i, j).get_A() != 0){
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
i32 matrix::elemMoveHonz(i32 dist){
	i32 i,j;
	color _clr;
	for(i = 0;i<row;i++){
		if(dist>0){
			for(j = column -1;j>=0;j--){
				if(j>dist-1){
					_clr = getElem(i, j-dist);
					setElem(i, j, _clr);
				}else{
					setElem(i, j, (color)0);
				}
			}
		}else{
			for(j = 0;j<column;j++){
				if(j<column+dist){
					_clr = getElem(i, j-dist);
					setElem(i,j,_clr);
				}else{
					setElem(i,j,(color)0);
				}
			}
		}
	}
	return 1;
}
i32 matrix::elemMoveVert(i32 dist){
	i32 i,j;
	color _clr;
	for(j = 0;j<column;j++){
		if(dist>0){
			for(i = row -1;i>=0;i--){
				if(i>dist-1){
					_clr = getElem(i-dist, j);
					setElem(i, j, _clr);
				}else{
					setElem(i, j, (color)0);
				}
			}
		}else{
			for(i = 0;i<row;i++){
				if(i<row+dist){
					_clr = getElem(i-dist, j);
					setElem(i,j,_clr);
				}else{
					setElem(i,j,(color)0);
				}
			}
		}
	}
	return 1;
}
i32 matrix::elemReplace(const color &whos, const color &to){
	b32 i,j;
	for(i = 0;i<row;i++){
		for(j = 0;j<column;j++){
			if(getElem(i, j) == whos){
				setElem(i, j ,to);
			}
		}
	}
	return 1;
}


void matrix::putFore(const matrix &layer, colorMethod _met){
	b32 i,j;
	color _clr;
	for(i=0;i<MIN(row, layer.row);i++){
		for(j=0;j<MIN(column, layer.column);j++){
			_clr = layer[i][j];
			_clr.mixWith(getElem(i,j), _met);
			setElem(i,j,_clr);
		}
	}
}
void matrix::putBack(const matrix &layer, colorMethod _met){
	b32 i,j;
	color _clr;
	for(i=0;i<MIN(row, layer.row);i++){
		for(j=0;j<MIN(column, layer.column);j++){
			_clr = getElem(i,j);
			_clr.mixWith(layer[i][j], _met);
			setElem(i,j,_clr);
		}
	}
}
//#ifdef USE_PNG
bool matrix::loadPNG(str fileName){
	FILE *fp;  
	png_structp png_ptr;  
	png_infop info_ptr;  
	png_bytep* row_pointers;  
	b8 buf[4];  
	i32 w, h, x, y, temp, color_type;
	fp = fopen( fileName.c_str(), "rb" );  
	if(!fp) {
		return false;  
	}  
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0 );  
	info_ptr = png_create_info_struct(png_ptr);  
	setjmp(png_jmpbuf(png_ptr));   
	//读取4个字节，检查是不是PNG
	temp = fread(buf, 1, 4, fp);  
	if( temp < 4 ) {  
		fclose(fp);  
		png_destroy_read_struct( &png_ptr, &info_ptr, 0);  
		return false;  
	}  
	temp = png_sig_cmp( (png_bytep)buf, (png_size_t)0, 4 );  
	if(temp != 0) {  
		fclose(fp);  
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);  
		return false;  
	}  
	rewind(fp);  
	//是PNG，读取文件
	png_init_io(png_ptr, fp );   
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);  
	color_type = png_get_color_type( png_ptr, info_ptr );  
	w = png_get_image_width( png_ptr, info_ptr );  
	h = png_get_image_height( png_ptr, info_ptr ); 
	row_pointers = png_get_rows( png_ptr, info_ptr );  
	switch( color_type ) {  
	case PNG_COLOR_TYPE_RGB_ALPHA:  
		data = new color[w*h];
		temp = 0;
		for( y=0; y<h; ++y ) {  
			for( x=0; x<w*4; ) {  
				/* 以下是RGBA数据，需要自己补充代码，保存RGBA数据 */  
				data[temp].set_R(row_pointers[y][x++]); // red  
				data[temp].set_G(row_pointers[y][x++]); // green  
				data[temp].set_B(row_pointers[y][x++]); // blue
				data[temp].set_A(row_pointers[y][x++]);   
				temp ++;
			}  
		}  
		break;  
	case PNG_COLOR_TYPE_RGB:  
		data = new color[w*h];
		temp = 0;
		for(y=0; y<h; ++y) {  
			for(x=0; x<w*3;) {  
				data[temp].set_A(0XFF); // alpha  
				data[temp].set_R(row_pointers[y][x++]); // red  
				data[temp].set_G(row_pointers[y][x++]); // green  
				data[temp].set_B(row_pointers[y][x++]); // blue  
				temp ++;
			}  
		}  
		break;  
	default:  
		fclose(fp);  
		png_destroy_read_struct( &png_ptr, &info_ptr, 0);  
		return false;  
	}  
	png_destroy_read_struct( &png_ptr, &info_ptr, 0);
	column = w;
	row = h;
	return true;
}
bool  matrix::makePNG(str fileName){
	i32 j, i, temp, pos,pos1;    
	png_structp png_ptr;  
	png_infop info_ptr;   
	png_bytep * row_pointers;  
	FILE *fp = fopen(fileName.c_str(), "wb");  
	if (!fp){  
		return false;  
	}  
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);  
	info_ptr = png_create_info_struct(png_ptr);  
	setjmp(png_jmpbuf(png_ptr));
	png_init_io(png_ptr, fp);  
	png_set_IHDR(png_ptr, info_ptr, column, row, 8, PNG_COLOR_TYPE_RGB_ALPHA, 0,0, 0);  
	png_write_info(png_ptr, info_ptr);  
	temp = 4 * column;  
	pos = 0;  
	pos1 = 0;
	row_pointers = new png_bytep[row];
	for(i = 0; i < row; i++)  
	{  
		row_pointers[i] = new unsigned char[temp];
		for(j = 0; j < temp; j += 4)  
		{  
			row_pointers[i][j]   = data[pos1].get_R(); // red  
			row_pointers[i][j+1] = data[pos1].get_G(); // green  
			row_pointers[i][j+2] = data[pos1].get_B(); // blue  
			row_pointers[i][j+3] = data[pos1].get_A(); // alpha
			pos1++;
			++pos;  
		}  
	}  
	png_write_image(png_ptr, row_pointers);  
	png_write_end(png_ptr, NULL);  

	for (j=0; j<row; j++)  
		delete[] row_pointers[j];  
	delete[] row_pointers;  
	fclose(fp);  
	return true;
}

palette::palette(){
	clear();
}

palette::~palette(){
}
lcolor& palette::operator[] (i32 i){
	return table[i];
}
void palette::clear(){
	table.clear();
}
void palette::push(lcolor colorList){
	table.push_back(colorList);
}
i32 palette::getCount() const{
	return table.size();
}
i32 palette::getTotalColorCount() const{
	i32 total = 0;
	for(i32 i = 0;i<table.size();i++){
		total += table[i].size();
	}
	return total;
}
i32 palette::getColorCount(i32 paletteID) const{
	if(paletteID >= getCount()){
		return -1;
	}
	return table[paletteID].size();
}
i32 palette::findColor(color goalColor, i32 paletteID) const{
	if(paletteID >= getCount()){
		return -2;
	}
	lcolor colorList = table[paletteID];
	for(i32 i = 0;i<colorList.size();i++){
		if(colorList[i] == goalColor){
			return i;
		}
	}
	return -1;
}
bool palette::joinWith(const lcolor &colorList, i32 paletteID){
	if(paletteID >= getCount()){
		return false;
	}
	lcolor colorList2;
	colorList2.clear();
	i32 i;
	for(i = 0;i<colorList.size();i++){
		if(findColor(colorList[i], paletteID) < 0){
			colorList2.push_back(colorList[i]);
		}
	}
	if(getColorCount(paletteID)+colorList2.size() > 256){
		return false;
	}
	for(i = 0;i<colorList2.size();i++){
		table[paletteID].push_back(colorList2[i]);
	}
	return true;
}
bool palette::tinyMake(stream &s, i32 paletteID){
	if(paletteID >= getCount()){
		return false;
	}
	i32 i;
	lcolor colorList = table[paletteID];
	s.allocate(sizeof(color)*(10+colorList.size()));
	s.push((i32)colorList.size());
	for(i = 0;i<colorList.size();i++){
		s.push((b8)colorList[i].get_R());
		s.push((b8)colorList[i].get_G());
		s.push((b8)colorList[i].get_B());
		s.push((b8)colorList[i].get_A());
	}
	return false;
}
bool palette::bigMake(stream &s){
	i32 i,j;
	lcolor colorList;
	s.allocate(sizeof(color)*(1000+getCount()+getTotalColorCount()));
	s.push((i32)getCount());
	for(j=0;j<getCount();j++){
		colorList = table[j];
		s.push((i32)colorList.size());
		for(i = 0;i<colorList.size();i++){
			s.push((b8)colorList[i].get_R());
			s.push((b8)colorList[i].get_G());
			s.push((b8)colorList[i].get_B());
			s.push((b8)colorList[i].get_A());
		}
	}
	return false;
}

bool palette::makeACT(str fileName, const lcolor &lc){
	stream s;
	s.allocate(772);
	i32 alIndex = 0;
	for(i32 i = 0;i<256;i++){
		if(i<lc.size()){
			if(lc[i].get_A() == 0){
				alIndex = i;
			}
			s.push(lc[i].get_R());
			s.push(lc[i].get_G());
			s.push(lc[i].get_B());
		}else{
			s.push((b8)0);
			s.push((b8)0);
			s.push((b8)0);
		}
	}
	s.push((b8)(lc.size() >> 8));
	s.push((b8)(lc.size() & 0xff));
	s.push((b8)0);
	s.push((b8)(alIndex & 0xff));
	s.makeFile(fileName);
	s.release();
	return true;
}
bool palette::loadACT(str fileName, lcolor &lc){
	stream s;
	s.loadFile(fileName);
	if(s.getLen() != 772)
		return false;
	i32 clrCount = s[768]*256+s[769];
	if(clrCount >= 256)
		return false;
	i32 alIndex = s[771];
	if(alIndex >= clrCount)
		return false;
	lc.clear();
	for(i32 i = 0;i<clrCount;i++){
		lc.push_back(color(0xFF, s[3*i], s[3*i+1], s[3*i+2]));
	}
	lc[alIndex].set(0);
	s.release();
	return true;
}