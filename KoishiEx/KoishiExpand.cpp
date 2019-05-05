#include "StdAfx.h"
#include "KoishiEx.h"
#include <fstream> 

using namespace Koishi;
using namespace KoishiAvatar;
using namespace KoishiExpand::KoishiMarkTool;
void KoishiExpand::KoishiMarkTool::CharMat(char p, matrix &mat, color clr){
	if(p>='a'&& p <= 'z'){
		p = p-'a'+'A';
	}
	int b[43][25]={
		{0,1,1,1,0,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1,0,1,1,1,0},
		{0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0},
		{0,1,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,1,1,1,1},
		{0,1,1,1,0,1,0,0,0,1,0,0,1,1,0,1,0,0,0,1,0,1,1,1,0},
		{0,0,1,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0},
		{0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,0},
		{1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
		{0,1,1,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,0},
		{0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,1,0,0,1,1,0},
		{0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1},
		{1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0},
		{0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0},
		{0,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1},
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

bool KoishiExpand::KoishiMarkTool::AvatarMarking(std::string avatarNPKfileName){
	int i, j, k;
	NPKobject inputNo;
	NPKobject outputNo;
	IMGobject io;


	if(!inputNo.loadFile(avatarNPKfileName)){
		printf("No good npk files...\n");
		return false;
	}
	outputNo.create();
	////////////////////////////////////////////////////////////////////
	//第一步：寻找需要打标的IMG文件
	std::vector<int> imgSitList;
	std::vector<int> imgIDList;
	std::vector<int> imgPartList;
	//avatarName av;

	imgSitList.clear();
	imgIDList.clear();
	imgPartList.clear();
	printf("Calculating marking imgs...\n");
	for(i=0;i<inputNo.count;i++){
		//av.parse(KoishiAvatar::shorten(inputNo.content[i].get_imgname()));
		/*if(imgIDList.size() == 0 || imgIDList[imgIDList.size()-1] != av.ID){
			inputNo.IMGextract(i, io);
			if(io.PICcontent[0].get_dataSize()>2){
				imgIDList.push_back(av.ID);
				imgSitList.push_back(i);
				imgPartList.push_back((int)av.part);
			}
			io.release();
		}*/
	}
	////////////////////////////////////////////////////////////////////
	//第二步：打标
	int situ;
	str imgName;
	IMGobject ioTemp;
	point allPt1, allPt2;	//画布左上、右下点
	matrix mat;				//原图像矩阵
	matrix markMat,orginMat;
	matrix markMoved,orginedMoved;
	stream s;
	PICinfo pi;
	for(i=0;i<imgSitList.size();i++){
		situ = imgSitList[i];
		inputNo.IMGextract(situ, io);
		inputNo.IMGextract(situ, ioTemp);
		imgName = inputNo.content[situ].imgname;
		printf("Marking ");
		printf(KoishiAvatar::shorten(imgName).c_str());
		printf("(%d/%d):\n",1+i, imgSitList.size());
		if(io.version == V6 && io.paletteData.getCount()<=0){
			io.release();
			printf("No palettes...\n");
			continue;
		}
		if(io.version != V2 && io.paletteData[0].size()<=1){
			io.release();
			printf("Palette color lacking...\n");
			continue;
		}
		if(io.version == V2){
			for(k=0;k<io.indexCount;k++){
				io.PICgetInfo(k, pi);
				if(pi.get_format() != LINK){
					if(pi.get_dataSize() <= 2){
						//continue;
					}
					int x1,y1,x2,y2;
					int alphaIndex = 0;
					x1 = MIN(20, pi.get_basePt().X);
					y1 = MIN(180, pi.get_basePt().Y);
					x2 = pi.get_basePt().X+pi.get_picSize().W;
					y2 = pi.get_basePt().Y+pi.get_picSize().H;
					mat.create(y2-y1, x2-x1);
					io.PICextract(k, orginMat);
					mat.putFore(orginMat);
					mat.moveHonz(pi.get_basePt().X-x1);
					mat.moveVert(pi.get_basePt().Y-y1);
					StrMatLarge(KoishiAvatar::shorten(imgName), markMat);
					markMoved.create((markMat.getHeight()+1)*13, markMat.getWidth()+100);
					markMoved.putFore(markMat);
					markMoved.moveHonz(20-x1);
					markMoved.moveVert(180-y1+(markMat.getHeight()+1)*imgPartList[i]);
					mat.putFore(markMoved);
					io.PICpreprocess(mat, s, pi);
					pi.set_basePt(point(x1,y1));
					ioTemp.PICreplace(k, pi, s);
					mat.destory();
					markMat.destory();
					markMoved.destory();
					orginMat.destory();
					s.release();
				}
			}
		}else{
			for(k=0;k<io.indexCount;k++){
				io.PICgetInfo(k, pi);
				if(pi.get_format() != LINK){
					if(pi.get_dataSize() <= 2){
						//continue;
					}
					int m1,m2;
					int x1,y1,x2,y2;
					int alphaIndex = 0;
					for(j=0;j<io.paletteData[0].size();j++){
						if(io.paletteData[0][j].A == 0){
							alphaIndex = j;
							break;
						}
					}
					x1 = MIN(20, pi.get_basePt().X);
					y1 = MIN(180, pi.get_basePt().Y);
					x2 = pi.get_basePt().X+pi.get_picSize().W;
					y2 = pi.get_basePt().Y+pi.get_picSize().H;

					mat.create(y2-y1, x2-x1);
					io.PICextractIndexMatrix(k, orginMat);
					mat.putFore(orginMat);
					mat.moveHonz(pi.get_basePt().X-x1);
					mat.moveVert(pi.get_basePt().Y-y1);
					StrMatLarge(KoishiAvatar::shorten(imgName), markMat, color((alphaIndex==1)?2:1,0,0,0));
					markMoved.create((markMat.getHeight()+1)*13, markMat.getWidth()+100);
					markMoved.putFore(markMat);
					markMoved.moveHonz(20-x1);
					markMoved.moveVert(180-y1+(markMat.getHeight()+1)*imgPartList[i]);
					mat.putFore(markMoved);

					for(m1=0;m1<mat.getHeight();m1++){
						for(m2=0;m2<mat.getWidth();m2++){
							if((m1<pi.get_basePt().Y-y1 || m2<pi.get_basePt().X-x1) && mat[m1][m2] == color(0,0,0,0)){
								mat.setElem(m1,m2,color(alphaIndex,0,0,0));
							}
						}
					}
					io.PICpreprocessIndexMatrix(mat, s, pi);
					pi.set_basePt(point(x1,y1));
					ioTemp.PICreplace(k, pi, s);
					mat.destory();
					markMat.destory();
					markMoved.destory();
					orginMat.destory();
					s.release();
				}
			}
		}
		outputNo.IMGpush(ioTemp, imgName);
		io.release();
		ioTemp.release();
		printf("Done.\n");
	}
	outputNo.saveFile("(marked)"+avatarNPKfileName);
	inputNo.release();
	outputNo.release();
	return true;
}
bool KoishiExpand::KoishiMarkTool::AvatarBatchMarking(std::string avatarNPKfileListName){
	std::ifstream myfile(avatarNPKfileListName); 
	if(!myfile.is_open()){
		printf("No NPK list file exists");
		system("pause");
		return false;
	}
	str temp;
	while(getline(myfile,temp)){
		printf("Now dealing ");
		printf(temp.c_str());
		printf("...\n");
		AvatarMarking(temp);
	}
	return true;
}
bool KoishiExpand::KoishiMarkTool::MatrixMarking(const matrix &sourceMatrix, matrix &destMatrix, str codeString, int situ){
	matrix strMatrix;
	StrMatLarge(codeString, strMatrix);
	switch(situ){
	case 1:
		//上方外侧
		strMatrix.expand(0,sourceMatrix.getHeight()+1, 0, 0);
		sourceMatrix.expand(destMatrix, strMatrix.getHeight()+1, 0, 0, sourceMatrix.getWidth() > strMatrix.getWidth() ? 0 : strMatrix.getWidth());
		destMatrix.putBack(strMatrix);
		break;
	case 2:
		//右方外侧
		strMatrix.expand(0, 0, sourceMatrix.getWidth()+1, 0);
		sourceMatrix.expand(destMatrix, 0, sourceMatrix.getHeight() > strMatrix.getHeight() ? 0 : strMatrix.getHeight(), 0, strMatrix.getWidth()+1);
		destMatrix.putBack(strMatrix);
		break;
	default:
		return false;
		break;
	}
	return true;
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
bool KoishiExpand::KoishiMarkTool::MatrixShowcasing(const matrix &sourceMatrix, matrix &destMatrix, int num, int size){
	matrix strMatrix, showcaseMatrix;
	matrix cutMatrix;
	if(size<8){
		size = 8;
	}
	destMatrix.create(size+20, size);
	//绘制框架
	showcaseMatrix.create(size+20, size);
	color cList[4] = {color(0,0,0), color(0xFF, 0x33, 0x00),color(0xFF, 0x66, 0x33),color(0xFF, 0x99, 0x66)};
	showcaseMatrix.fill(cList[2]);
	showcaseMatrix.rectangle(point(0,0), point(size-1,size+19), cList[0]);
	showcaseMatrix.rectangle(point(1,1), point(size-2,size+18), cList[0]);
	showcaseMatrix.line(point(2,2), point(2,size+17), cList[3]);
	showcaseMatrix.line(point(2,2), point(size-3,2), cList[3]);
	showcaseMatrix.line(point(3,3), point(3,size+16), cList[3]);
	showcaseMatrix.line(point(3,3), point(size-4,3), cList[3]);
	showcaseMatrix.line(point(size-3,size+17), point(3,size+17), cList[1]);
	showcaseMatrix.line(point(size-3,size+17), point(size-3,3), cList[1]);
	showcaseMatrix.line(point(size-4,size+16), point(4,size+16), cList[1]);
	showcaseMatrix.line(point(size-4,size+16), point(size-4,4), cList[1]);
	showcaseMatrix.line(point(5,5), point(size-6,5), cList[1]);
	showcaseMatrix.line(point(5,5), point(5,size-6), cList[1]);
	showcaseMatrix.line(point(size-6,5), point(size-6,size-6), cList[3]);
	showcaseMatrix.line(point(5,size-6), point(size-6,size-6), cList[3]);
	//绘制数字
	StrMatLarge(KoishiAvatar::getAvatarIDString(num), strMatrix);
	strMatrix.expand(size + 8 - strMatrix.getHeight()/2, 0, size / 2 - strMatrix.getWidth()/2, 0);
	//裁切Matrix
	long left = 0;
	long right = sourceMatrix.getWidth();
	long top = 0;
	long bottom = sourceMatrix.getHeight();
	if(sourceMatrix.getWidth() > size - 12){
		left = (sourceMatrix.getWidth() - size + 12) / 2;
		right -= left;
	}if(sourceMatrix.getHeight() > size - 12){
		top = (sourceMatrix.getHeight() - size + 12) / 2;
		bottom -= top;
	}
	sourceMatrix.clip(cutMatrix, top, bottom, left, right);
	cutMatrix.expand( size/2 - cutMatrix.getHeight()/2, 0, size/2 - cutMatrix.getWidth()/2, 0);
	destMatrix.putFore(showcaseMatrix);
	destMatrix.putFore(strMatrix);
	destMatrix.putFore(cutMatrix);
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
KoishiExpand::Indexing::Indexing(){
	millages = 0;
}
void KoishiExpand::Indexing::input(const IMGobject &in){
	io = in;
}
void KoishiExpand::Indexing::input(const std::string imgName){
	io.release();
	io.loadFile(imgName);
}
void KoishiExpand::Indexing::deal(IMGobject &goal, int colorCount){
	millages = 0;
	if(colorCount>0xff){
		colorCount = 0xff;
	}
	PICinfo pi;
	matrix mat;
	stream s,s1;
	palette pl;
	colorList lc;
	queue li;
	int i,j,k;
	lc.clear();
	li.clear();
	pl.push(lc);
	//统计颜色
	for(i=0;i<io.indexCount;i++){
		io.PICextract(i, mat);
		//提取矩阵
		for(j=0;j<mat.getElemCount();j++){
			color c = mat.getElem(j);
			if(c.A<=0x7F)
				continue;
			c.A = 0xFF;
			int count = pl.findColor(c,0);
			if(count==-1){
				pl[0].push_back(c);
				li.push_back(1);
			}else{
				li[count]++;
			}
			if(j % 10000 == 0){
				int aabb = 0;
			}
		}
		mat.destory();
		millages = 500*i/io.indexCount;
	}
	lc = pl[0];
	//取出数目最多的若干个颜色
	colorList lc2; //这个就是新的色表
	queue li2;
	lc2.clear();
	li2.clear();
	if(colorCount>lc.size()){
		colorCount = lc.size();
	}
	for(i=0;i<colorCount;i++){
		int maximum = 0;
		int maximumId = -1;
		for(j=0;j<lc.size();j++){
			if(li[j]>maximum){
				maximum = li[j];
				maximumId = j;
			}
		}
		lc2.push_back(lc[maximumId]);
		li2.push_back(li[maximumId]);
		li.erase(li.begin()+maximumId);
		lc.erase(lc.begin()+maximumId);
	}
	//开始转换
	millages = 500;
	goal.create(V4);
	//导入色表
	goal.CLRpush(color(0,0,0,0));
	for(i=0;i<lc2.size();i++){
		goal.CLRpush(lc2[i]);
	}
	//插入索引数据
	for(i=0;i<io.indexCount;i++){
		io.PICgetInfo(i,pi);
		if(pi.get_format() == LINK){
			goal.PICpush(pi, NULL);
			continue;
		}
		io.PICextract(i, mat);
		s.allocate(pi.get_picSize().area()+100);		//直接分配内存
		for(j=0;j<mat.getElemCount();j++){
			color c = mat.getElem(j);
			if(c.A <= 0x7F){
				s.push((Koishi::uchar)0);
			}else{
				c.A = 0xFF;
				int lowdist = 0x7FFFFFFF;
				int lowID = -1;
				for(k=0;k<lc2.size();k++){
					int dist = Koishi::color::EuclideanDistanceSquareOf(c,lc2[k]);
					if(dist<=lowdist){
						lowID = k;						//最短颜色欧氏距离匹配
						lowdist = dist;
					}
				}
				s.push((uchar)(1+lowID));
			}
		}
		s.compressData(s1, COMP_ZLIB);
		pi.set_format(ARGB1555);
		pi.set_comp(COMP_ZLIB);
		pi.set_dataSize(s1.getLen());
		goal.PICpush(pi, s1);
		s.release();
		s1.release();
		mat.destory();
		millages = 500+500*i/io.indexCount;
	}
	millages = 1000;
}
void KoishiExpand::Indexing::output(IMGobject &out){
	deal(out);
}
void KoishiExpand::Indexing::output(const std::string imgName){
	IMGobject out;
	deal(out);
	out.saveFile(imgName);
}

/////////////////////////////////////////////////////////////
using namespace KoishiExpand::KoishiDownloadTool;
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
			s1.BZdecompress(s2);
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
	s.uncompressData(s1, COMP_ZLIB, uncomSize);
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
/////////////图像工具////////////////////
color KoishiExpand::KoishiImageTool::gradient(const color &sourceColor, const colorList &keyColorList, Koishi::colorProperty cp){
	if(keyColorList.size() == 0){
		return sourceColor;
	}
	if(keyColorList.size() == 1){
		return keyColorList[0];
	}
	double theProp = sourceColor.getProperty(cp);
	double delta = 1.0/(keyColorList.size()-1);		//步长
	int step = (int)(theProp / delta);
	if(step >= keyColorList.size() - 1){
		step = keyColorList.size() - 2;
	}
	return color(
		(uchar)(theProp*keyColorList[step].A) + (uchar)((1-theProp)*keyColorList[step+1].A),
		(uchar)(theProp*keyColorList[step].R) + (uchar)((1-theProp)*keyColorList[step+1].R),
		(uchar)(theProp*keyColorList[step].G) + (uchar)((1-theProp)*keyColorList[step+1].G),
		(uchar)(theProp*keyColorList[step].B) + (uchar)((1-theProp)*keyColorList[step+1].B)
	);
}
////////////////////////////////////////////////

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
//放置缩略图的算法
/*
1.首先计算新放置缩略图的位置的顶部坐标和左边坐标
2.根据左边坐标到画布右侧的距离与缩略图宽度做比较，如果不够放，则另起一行（转至3）；否则转至4。
3.另起一行时，若上一行的最大高度超过了画布下册，则返回失败0；否则转至4。
4.放置图像，坐标以及最大高度更新，返回成功1。
*/
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
