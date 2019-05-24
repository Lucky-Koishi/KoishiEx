#include "StdAfx.h"
#include "KoishiEx.h"
#include <fstream> 

using namespace Koishi;
using namespace KoishiAvatar;
using namespace KoishiExpand::KoishiMarkTool;
using namespace KoishiExpand::KoishiDownloadTool;
void KoishiExpand::KoishiMarkTool::CharMat(char p, matrix &mat, color clr){
	if(p>='a'&& p <= 'z'){
		p = p-'a'+'A';
	}
	unsigned long charCode[0xFF];
	charCode['0'] = 0x0E9D72E;
	charCode['1'] = 0x0E210C4;
	charCode['2'] = 0x1F1322E;
	charCode['3'] = 0x0E8B22E;
	charCode['4'] = 0x08FA54C;
	charCode['5'] = 0x0F83C3F;
	charCode['6'] = 0x0E8BC3E;
	charCode['7'] = 0x022221F;
	charCode['8'] = 0x0E8BA2E;
	charCode['9'] = 0x0C87A2E;
	charCode['A'] = 0x118FE2E;
	charCode['B'] = 0xF8BE2F;
	charCode['C'] = 0x1E0843E;
	charCode['D'] = 0xF8C62F;
	charCode['E'] = 0x1F0BC3F;
	charCode['F'] = 0x10BC3F;
	charCode['G'] = 0x1E8F43E;

	int b[43][25]={
		{0,1,1,1,0,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1,0,1,1,1,0},
		{0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0},
		{0,1,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,1,1,1,1},
		{0,1,1,1,0,1,0,0,0,1,0,0,1,1,0,1,0,0,0,1,0,1,1,1,0},
		{0,0,1,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,0},//4
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0},
		{0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,0},
		{1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},//7
		{0,1,1,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,0},
		{0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,1,0,0,1,1,0},
		{0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1},//A
		{1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0},
		{0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1},//E
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1},//G
		{1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1},
		{0,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0},
		{0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,0,1,1,1,0},
		{1,0,0,0,1,1,0,0,1,0,1,1,1,0,0,1,0,0,1,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1},
		{1,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,1},
		{1,0,0,0,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,0,0,0,1},
		{0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},
		{1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0},
		{0,1,1,1,0,1,0,0,0,1,1,0,1,0,1,1,0,0,1,0,0,1,1,0,1},
		{1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1},
		{0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0},
		{1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
		{1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},
		{1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0},
		{1,0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0},
		{1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
		{1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0},
		{0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0},
		{0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,
		 0,0,0,1,1,
		 1,1,1,0,1,
		 1,0,1,0,0,
		 1,1,1,0,0},
		{0,0,1,1,1,
		 0,0,1,0,1,
		 1,0,1,1,1,
		 0,1,0,0,0,
		 1,0,1,0,0}
	};
	int situ = 0;
	if(p >= 'A' && p <= 'Z'){
		situ = p - 'A' + 10;
	}else if(p >= '0' && p<= '9'){
		situ = p - '0';
	}else if(p == '.'){
		situ = 36;
	}else if(p == '_'){
		situ = 37;
	}else if(p == '('){
		situ = 38;
	}else if(p == ')'){
		situ = 39;
	}else if(p == '&'){
		//男性
		situ = 41;
	}else if(p == '*'){
		//女性
		situ = 42;
	}else{
		situ = 40;
	}
	mat.create(5,5);
	int i;
	for(i=0;i<25;i++){
		mat.push(b[situ][i]?clr:color(0,0,0,0));
	}
}
void KoishiExpand::KoishiMarkTool::StrMat(str s, matrix &mat, color clr){
	char p;
	if(s.size() == 0){
		s = " ";
	}
	matrix subMat;
	mat.create(5,6*s.size()-1);
	mat.fill(0);
	for(int i = 0;i<s.size();i++){
		p = s[s.size()-i-1];
		CharMat(p, subMat, clr);
		mat.putFore(subMat);
		if(i != s.size()-1){
			mat.moveHonz(6);
		}
		subMat.destory();
	}
}
void KoishiExpand::KoishiMarkTool::CharMatLarge(char p, Koishi::matrix &mat, Koishi::color clr){
	if(p>='a'&& p <= 'z'){
		p = p-'a'+'A';
	}
	int b[44][100]={
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,1,1,
		 1,1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
		 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,1,1,0,0,0,0,1,1,0,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,0,0,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 0,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,0,0,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,0,0,0,0,0,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,1,1,1,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,0,0,0,
		 1,1,1,1,1,1,1,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,0,0,0,
		 1,1,1,1,1,1,1,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,1,1,1,1,
		 1,1,0,0,0,0,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1},
		{0,0,0,1,1,1,1,0,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,1,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,1,1,1,
		 0,0,0,0,0,0,0,1,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 0,1,1,1,1,1,1,1,1,0,
		 0,0,1,1,1,1,1,1,0,0},
		{1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,1,1,0,
		 1,1,0,0,0,0,1,1,0,0,
		 1,1,0,0,0,1,1,0,0,0,
		 1,1,1,1,1,1,0,0,0,0,
		 1,1,1,1,1,1,0,0,0,0,
		 1,1,0,0,0,1,1,0,0,0,
		 1,1,0,0,0,0,1,1,0,0,
		 1,1,0,0,0,0,0,1,1,0,
		 1,1,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,1,1,
		 1,1,1,0,0,0,0,1,1,1,
		 1,1,1,1,0,0,1,1,1,1,
		 1,1,0,1,1,1,1,0,1,1,
		 1,1,0,0,1,1,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,1,1,
		 1,1,1,0,0,0,0,0,1,1,
		 1,1,1,1,0,0,0,0,1,1,
		 1,1,0,1,1,0,0,0,1,1,
		 1,1,0,0,1,1,0,0,1,1,
		 1,1,0,0,1,1,0,0,1,1,
		 1,1,0,0,0,1,1,0,1,1,
		 1,1,0,0,0,0,1,1,1,1,
		 1,1,0,0,0,0,0,1,1,1,
		 1,1,0,0,0,0,0,0,1,1},
		{0,1,1,1,1,1,1,1,1,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,1,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,0,0,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,1,1,1,1,1,1,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,1,1,1,1,
		 1,1,0,0,0,0,1,1,1,0,
		 1,1,1,1,1,1,1,1,1,1,
		 0,1,1,1,1,1,1,0,1,1},
		{1,1,1,1,1,1,1,1,0,0,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,0,
		 1,1,1,1,1,1,1,1,0,0,
		 1,1,0,0,0,1,1,0,0,0,
		 1,1,0,0,0,0,1,1,0,0,
		 1,1,0,0,0,0,0,1,1,0,
		 1,1,0,0,0,0,0,0,1,1},
		{0,0,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,0,0,
		 0,0,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,1,1,1,1,1,1,1,1,0},
		{1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 0,1,1,0,0,0,0,1,1,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,1,1,0,0,1,1,
		 1,1,0,1,1,1,1,0,1,1,
		 1,1,1,1,0,0,1,1,1,1,
		 1,1,1,0,0,0,0,1,1,1,
		 1,1,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,1,1,
		 0,1,1,0,0,0,0,1,1,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,1,1,0,0,0,0,1,1,0,
		 1,1,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,1,1,
		 0,1,1,0,0,0,0,1,1,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,
		 0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		 {0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,1,1,0,1,1,0,1,1,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,0,1,1,1,1,0,0,0},
		 {0,0,0,1,1,1,1,0,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,0,0,1,1,0,0,0,0},
		 {1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 0,0,0,0,1,1,1,1,1,1,
		 0,0,0,0,1,1,1,1,1,1,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0}
	};
	int situ = 0;
	if(p >= 'A' && p <= 'Z'){
		situ = p - 'A' + 10;
	}else if(p >= '0' && p<= '9'){
		situ = p - '0';
	}else if(p == '.'){
		situ = 36;
	}else if(p == '_'){
		situ = 37;
	}else if(p == '('){
		situ = 38;
	}else if(p == ')'){
		situ = 39;
	}else if(p == '&'){
		//男性
		situ = 41;
	}else if(p == '*'){
		//女性
		situ = 42;
	}else if(p == '?'){
		situ = 43;
	}else{
		situ = 40;
	}
	mat.create(10,10);
	int i;
	for(i=0;i<100;i++){
		mat.push(b[situ][i]?clr:color(0,0,0,0));
	}
}
void KoishiExpand::KoishiMarkTool::StrMatLarge(str s, Koishi::matrix &mat, Koishi::color clr){
	char p;
	if(s.size() == 0){
		s = " ";
	}
	matrix subMat;
	mat.create(10,11*s.size()-1);
	mat.fill(0);
	for(int i = 0;i<s.size();i++){
		p = s[s.size()-i-1];
		CharMatLarge(p, subMat, clr);
		mat.putFore(subMat);
		if(i != s.size()-1){
			mat.moveHonz(11);
		}
		subMat.destory();
	}
}
bool KoishiExpand::KoishiMarkTool::MatrixMarking(const matrix &sourceMatrix, matrix &destMatrix, str codeString, point deltaPoint, color textColor){
	matrix strMatrix;
	StrMatLarge(codeString, strMatrix, textColor);
	long topEx = 0;
	long leftEx = 0;
	long rightEx = 0;
	long bottomEx = 0;
	if(deltaPoint.Y < 0){
		topEx = -deltaPoint.Y;
	}
	if(deltaPoint.X < 0){
		leftEx = -deltaPoint.X;
	}
	if(deltaPoint.X + strMatrix.getWidth() > sourceMatrix.getWidth()){
		rightEx = deltaPoint.X + strMatrix.getWidth() - sourceMatrix.getWidth();
	}
	if(deltaPoint.Y + strMatrix.getHeight() > sourceMatrix.getHeight()){
		bottomEx = deltaPoint.Y + strMatrix.getHeight() - sourceMatrix.getHeight();
	}
	sourceMatrix.expand(destMatrix, topEx, bottomEx, leftEx, rightEx);
	strMatrix.expand(deltaPoint.Y > 0 ? deltaPoint.Y:0, 0, deltaPoint.X > 0 ? deltaPoint.X:0, 0); 
	destMatrix.putBack(strMatrix);
	return true;

}
bool KoishiExpand::KoishiMarkTool::MatrixPSstyle(const matrix &sourceMatrix, matrix &destMatrix, color clrBound, color clrBG1, color clrBG2){
	long i, j;
	destMatrix.create(sourceMatrix.getHeight(), sourceMatrix.getWidth());
	for(i = 0;i<destMatrix.getWidth();i++){
		for(j = 0;j<destMatrix.getHeight();j++){
			destMatrix.setElem(j, i, (i%10<5&&j%10<5||i%10>=5&&j%10>=5)?clrBG1:clrBG2);
			if(i==0||j==0||i==destMatrix.getWidth()-1||j==destMatrix.getHeight()-1){
				destMatrix.setElem(j,i,clrBound);
			}
		}
	}
	destMatrix.putFore(sourceMatrix);
	return true;
}

/////////////////////////////////////////////////////////////
bool SPKobject::load(str fileName){
	int i,j;
	unsigned long dw;
	if(!data.loadFile(fileName)){
		return false;
	}
	data.read(magic);
	if(magic != 0x1B111){
		data.release();
		return false;
	}
	for(i=0;i<260;i++){
		data.read(name[i]);
	}
	data.read(reserve1);
	data.read(decompressed_len);
	for(i=0;i<32;i++){
		data.read(hash[i]);
	}
	data.read(maxBlockSize);
	data.read(indexCount);
	listLen.clear();
	for(i=0;i<indexCount;i++){
		data.read(dw);
		listLen.push_back(dw);
	}
	for(i=0;i<indexCount;i++){
		SPKblock sb;
		sb.startPos = data.getPtPos();
		data.read(sb.bzlib);
		data.read(sb.len);
		data.read(sb.bzlib_r);
		data.read(sb.len_r);
		for(j=0;j<32;j++){
			data.read(sb.hash[j]);
		}
		sb.mainStartPos = data.getPtPos();
		data.ptMove(sb.len);
		list.push_back(sb);
	}
	return true;
}

void SPKobject::release(){
	data.release();
}

void SPKobject::extract(int pos, stream &s){
	data.ptMoveTo(list[pos].mainStartPos);
	data.readStream(s, list[pos].len);
}

void SPKobject::extractTrueStream(stream &s){
	s.allocate(decompressed_len*2);
	s.clear();
	stream s1,s2;
	for(int i = 0;i<indexCount;i++){
		extract(i, s1);
		if(list[i].bzlib){
			s1.BZuncompress(s2);
			s.pushStream(s2,s2.getLen());
		}else{
			s.pushStream(s1,s1.getLen());
		}
	}
}

void SPKobject::makeNPK(str NPKfileName){
	stream s;
	extractTrueStream(s);
	s.makeFile(NPKfileName);
}

LSTfile::LSTfile(){
	int i = 0;
	nameLen = 0;
	for(i=0;i<256;i++){
		name[i] = 0;
	}
	fileLen = 0;
	compLen = 0;
	hashLen = 0;
	for(i=0;i<32;i++){
		hash[i] = 0;
	}
}

LSTfolder::LSTfolder(){
	int i = 0;
	nameLen = 0;
	for(i=0;i<256;i++){
		name[i] = 0;
	}
	fileCount = 0;
	subFolderCount = 0;
	list.clear();
}
void LSTobject::load(Koishi::stream &s){
	int i,j;
	for(i=0;i<32;i++){
		s.read(hash[i]);
	}
	s.read(magic);
	s.read(reserve);
	s.read(reserve2);
	list.clear();
	while(true){
		LSTfolder lf;
		if(!s.read(lf.nameLen)){
			break;
		}
		for(i=0;i<lf.nameLen;i++){
			s.read(lf.name[i]);
		}
		s.read(lf.fileCount);
		lf.list.clear();
		for(j=0;j<lf.fileCount;j++){
			LSTfile lfl;
			s.read(lfl.nameLen);
			for(i=0;i<lfl.nameLen;i++){
				s.read(lfl.name[i]);
			}
			s.read(lfl.compLen);
			s.read(lfl.fileLen);
			s.read(lfl.hashLen);
			for(i=0;i<lfl.hashLen;i++){
				s.read(lfl.hash[i]);
			}
			lf.list.push_back(lfl);
		}
		s.read(lf.subFolderCount);
		list.push_back(lf);
	}
}
bool LSTobject::load(const str &fileName){
	int i,j;
	stream s;
	if(!s.loadFile(fileName))
		return false;
	for(i=0;i<32;i++){
		s.read(hash[i]);
	}
	s.read(magic);
	if(magic != 0x54534C){
		return false;
	}
	s.read(reserve);
	s.read(reserve2);
	list.clear();
	while(true){
		LSTfolder lf;
		if(!s.read(lf.nameLen)){
			break;
		}
		for(i=0;i<lf.nameLen;i++){
			s.read(lf.name[i]);
		}
		s.read(lf.fileCount);
		lf.list.clear();
		for(j=0;j<lf.fileCount;j++){
			LSTfile lfl;
			s.read(lfl.nameLen);
			for(i=0;i<lfl.nameLen;i++){
				s.read(lfl.name[i]);
			}
			s.read(lfl.compLen);
			s.read(lfl.fileLen);
			s.read(lfl.hashLen);
			for(i=0;i<lfl.hashLen;i++){
				s.read(lfl.hash[i]);
			}
			lf.list.push_back(lfl);
		}
		s.read(lf.subFolderCount);
		list.push_back(lf);
	}
	return true;
}

bool LSTobject::getImagePack2(LSTfolder &lf){
	int i;
	for(i=0;i<list.size();i++){
		str s1((char*)list[i].name);
		str s2 = "ImagePacks2";
		if(s1 == s2){
			lf = list[i];
			return true;
		}
	}
	return false;
}

bool TCTobject::load(Koishi::str fileName){
	int i;
	if(!data.loadFile(fileName)){
		return false;
	}
	data.read(magic);
	if(magic != 0x04034b50){
		return false;
	}
	data.read(minVersion);
	data.read(GTBF);
	data.read(compMethod);
	data.read(lastTime);
	data.read(lastDate);
	data.read(CRC32);
	data.read(comSize);
	data.read(uncomSize);
	data.read(nmSize);
	data.read(exSize);
	for(i=0;i<256;i++){
		 name[i] = 0;
		 if(i<nmSize){
			 data.read(name[i]);
		 }
	}
	for(i=0;i<256;i++){
		 ex[i] = 0;
		 if(i<exSize){
			 data.read(ex[i]);
		 }
	}
	dtStartPos = data.getPtPos();
	return true;
}
bool TCTobject::release(){
	data.release();
	return true;
}
bool TCTobject::makeNPK(Koishi::str NPKfileName){
	stream s, s1, sHead,sOut;
	data.ptMoveTo(dtStartPos);
	data.readStream(s, comSize);
	sHead.allocate(2);
	sHead.push((word)0x9C78);
	s.insertStream(sHead, 2, 0);
	s.ZLIBuncompress(s1, uncomSize);
	s1.readStream(sOut, uncomSize);
	sOut.makeFile(NPKfileName);
	s.release();
	s1.release();
	sOut.release();
	sHead.release();
	return true;
}
LSTfileGF::LSTfileGF(){
	int i;
	for(i=0;i<256;i++){
		name[i] = 0;		
	}
	for(i=0;i<32;i++){
		lenStr[i] = 0;
		hash[i] = 0;	
	}
}
bool LSTobjectGF::load(const Koishi::str &fileName){
	int i,j;
	unsigned char n;
	stream s,sSplit;
	queueex pos, len;
	s.loadFile(fileName);
	sSplit.allocate(20);
	sSplit.pushString("ImagePacks2\\");
	s.splitStream(sSplit, pos, len);
	sSplit.release();
	list.clear();
	for(i=1;i<pos.size();i++){
		s.ptMoveTo(pos[i]);
		LSTfileGF lf;
		j = 0;
		while(true){
			s.read(n);
			if(n == 0x22){
				break;
			}else{
				lf.name[j++] = n;
			}
		}
		s.read(n);
		j = 0;
		while(true){
			s.read(n);
			if(n == 0x20){
				break;
			}else{
				lf.hash[j++] = n;
			}
		}
		j = 0;
		while(true){
			s.read(n);
			if(n == 0x0D){
				break;
			}else{
				lf.lenStr[j++] = n;
			}
		}
		list.push_back(lf);
	}
	return true;
}
/////////////旧版本IMG///////////////////
bool KoishiExpand::IMGobjectV1::load(const Koishi::str &fileName){
	stream s;
	if(!s.loadFile(fileName))
		return false;
	return load(s);
}

bool KoishiExpand::IMGobjectV1::load(Koishi::stream &s){
	data = s;
	//开始读取
	int i;
	unsigned long dwTemp;
	unsigned long dwVersion;
	unsigned long dwIndexCount;
	s.ptMoveTo(0);
	Koishi::str sz = s.readString(20);
	if(sz != "Neople Image File")
		return false;
	s.read(dwTemp);	//保留位
	s.read(dwVersion); //版本
	if(dwVersion != (unsigned long)Koishi::V1){
		return false;
	}
	s.read(dwIndexCount);	//INDEX数
	PICcontent.clear();
	posList.clear();

	for(i=0;i<dwIndexCount;i++){
		PICinfo pi;
		s.read(dwTemp);
		pi.set_format((Koishi::colorFormat)dwTemp);
		s.read(dwTemp);
		pi.set_comp((Koishi::compressType)dwTemp);
		s.read(dwTemp);
		pi.picSize.W = (long)dwTemp;
		s.read(dwTemp);
		pi.picSize.H = (long)dwTemp;
		s.read(dwTemp);
		pi.set_dataSize(dwTemp);
		s.read(dwTemp);
		pi.basePt.X = (long)dwTemp;
		s.read(dwTemp);
		pi.basePt.Y = (long)dwTemp;
		s.read(dwTemp);
		pi.frmSize.W = (long)dwTemp;
		s.read(dwTemp);
		pi.frmSize.H = (long)dwTemp;
		PICcontent.push_back(pi);
		posList.push_back(s.getPtPos());
		lenList.push_back(pi.get_dataSize());
		s.ptMove(pi.get_dataSize());
	}
	return true;
}
bool KoishiExpand::IMGobjectV1::make(Koishi::IMGobject &io){
	io.create(V2);
	stream s;
	int i;
	for(i=0;i<PICcontent.size();i++){
		data.ptMoveTo(posList[i]);
		data.readStream(s, lenList[i]);
		io.PICpush(PICcontent[i], s);
		s.release();
	}
	return true;
}
bool KoishiExpand::IMGobjectV1::release(){
	data.release();
	posList.clear();
	lenList.clear();
	return true;
}

///////////全帧展示////////////////////////

KoishiExpand::exhibit::exhibit(){
	clear();
}
void KoishiExpand::exhibit::clear(){
	hMaxPerRow = 0;
	hList.clear();
	rList.clear();
	hList.push_back(0);
	queue zero;
	zero.push_back(0);
	rList.push_back(zero);
	canvas.destory();
}
void KoishiExpand::exhibit::create(int width, int height){
	canvas.create(height, width);
}
//全帧显示
//1.首先计算新放置缩略图的位置的顶部坐标和左边坐标
//2.根据左边坐标到画布右侧的距离与缩略图宽度做比较，如果不够放，则另起一行（转至3）；否则转至4。
//3.另起一行时，若上一行的最大高度超过了画布下册，则返回失败0；否则转至4。
//4.放置图像，坐标以及最大高度更新，返回成功1。

bool KoishiExpand::exhibit::putMatrix(const matrix &newMat, bool expanded){
	int currentRow = hList.size()-1;	//当前已经达成的行
	int top = hList[currentRow];		//顶部坐标
	int current = rList[currentRow].size()-1;	//当前行中已插入的个数
	int left = rList[currentRow][current];		//左边坐标

	bool needNewLine = false;
	if(newMat.getWidth() + left > canvas.getWidth()){
		needNewLine = true;
	}
	if(needNewLine){
		//计算上一栏的最低层
		currentRow ++;
		top += hMaxPerRow;
		current = 0;
		left = 0;
		if(top >= canvas.getHeight() && !expanded){
			return false;
		}
		hMaxPerRow = 0;
		queue zero;
		zero.push_back(0);
		rList.push_back(zero);
		hList.push_back(top);
	}
	matrix offset;
	newMat.expand(offset, top, 0, left, 0);
	if(expanded){
		if(canvas.getHeight()<offset.getHeight()){
			int hDelta = offset.getHeight() - canvas.getHeight();
			matrix tempCanvas(canvas);
			canvas.destory();
			tempCanvas.expand(canvas, 0, hDelta, 0, 0);
			tempCanvas.destory();
		}
	}
	canvas.putFore(offset);
	if(newMat.getHeight()>hMaxPerRow){
		hMaxPerRow = newMat.getHeight();
	}
	rList[currentRow].push_back(left + newMat.getWidth());
	return true;
}

/////////////////////////////////////////////////////
int KoishiExpand::authorLock::checkLock(str fileName, str password){
	stream s, sStr, sSHA1, sSHA2;
	sStr.allocate(password.size());
	sStr.pushString(password);
	sStr.getSHA256(sSHA1);
	//没能打开文件
	if(!s.loadFile(fileName))
		return 3;
	//长度不够，不可能含有锁
	if(s.len < 38)
		return 3;
	s.ptMoveTo(s.len - 6);
	//未加锁
	if("XYZZY" != s.readString(6))
		return 2;
	//已经加锁
	s.ptMoveTo(s.len - 38);
	s.readStream(sSHA2, 32);
	for(int i = 0;i<32;i++){
		if(sSHA1[i] != sSHA2[i])
			return 0;
	}	
	return 1;

}
bool KoishiExpand::authorLock::addLock(str fileName, str password){
	stream s, sStr, sSHA1;
	sStr.allocate(password.size());
	sStr.pushString(password);
	sStr.getSHA256(sSHA1);
	if(checkLock(fileName, password) < 2)
		return false;	//已经有锁所以不能加锁
	if(!s.loadFile(fileName))
		return false;	//无法读取文件
	s.pushStream(sSHA1, 32);
	s.pushString("XYZZY");
	s.push(uchar(0));
	s.makeFile(fileName);
	return true;
}
//////////////////////////////////////////////////////////////////////////////
void KoishiExpand::textDisplay::binary(const stream &in, stream &out){
	out.release();
	out.allocate(in.len*10);
	for(longex i = 0;i<in.len;i++){
		if(i % 16 == 0){
			char s[10];
			itoa(i, s, 16);
			out.pushString(str(s));
			out.push((uchar)' ');
		}
		uchar mask = 1;
		for(uchar j = 0;j<8;j++){
			if(in[i] & mask){
				out.push((uchar)'1');
			}else{
				out.push((uchar)'0');
			}
			mask <<= 1;
		}
		
		out.push((uchar)' ');
		if(i % 16 == 15){
			out.push((uchar)'\r');
			out.push((uchar)'\n');
		}
	}
}
void KoishiExpand::textDisplay::binaryFile(const stream &in, str fileName){
	stream out;
	binary(in, out);
	out.makeFile(fileName);
}
void KoishiExpand::textDisplay::binaryCompareFile(const stream &in1, const stream &in2, str fileName){
	stream out;
	longex maxLen =MAX(in1.len, in2.len);
	out.allocate(maxLen*40);
	for(longex i = 0;i<maxLen;i+=16){
		//head:
		char s[10];
		itoa(i, s, 16);
		out.pushString(str(s));
		out.push((uchar)':');
		out.push((uchar)' ');
		for(uchar j = 0;j<16;j++){
			uchar mask = 1;
			for(uchar k = 0;k<8;k++){
				if(i+j>=in1.len){
					out.push((uchar)' ');
				}else if(in1[i+j] & mask){
					out.push((uchar)'1');
				}else{
					out.push((uchar)'0');
				}
				mask <<= 1;
			}
			out.push((uchar)' ');
		}
		out.push((uchar)'\r');
		out.push((uchar)'\n');
		out.pushString(str(s));
		out.push((uchar)':');
		out.push((uchar)' ');
		for(uchar j = 0;j<16;j++){
			uchar mask = 1;
			for(uchar k = 0;k<8;k++){
				if(i+j>=in2.len){
					out.push((uchar)' ');
				}else if(in2[i+j] & mask){
					out.push((uchar)'1');
				}else{
					out.push((uchar)'0');
				}
				mask <<= 1;
			}
			out.push((uchar)' ');
		}
		out.push((uchar)'\r');
		out.push((uchar)'\n');
		out.push((uchar)'\r');
		out.push((uchar)'\n');
	}
	out.makeFile(fileName);
}