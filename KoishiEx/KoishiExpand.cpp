#include "StdAfx.h"
#include "KoishiEx.h"
#include "avatar.h"
#include <fstream> 

using namespace Koishi;

void KoishiExpand::CharMat(char p, Koishi::matrix &mat, Koishi::color clr){
	if(p>='a'&& p <= 'z'){
		p = p-'a'+'A';
	}
	int b[41][25]={
		{0,1,1,1,0,
		 1,0,0,1,1,
		 1,0,1,0,1,
		 1,1,0,0,1,
		 0,1,1,1,0},
		{0,0,1,0,0,
		 0,1,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,1,1,1,0},
		{0,1,1,1,0,
		 1,0,0,0,1,
		 0,0,1,1,0,
		 0,1,0,0,0,
		 1,1,1,1,1},
		{0,1,1,1,0,
		 1,0,0,0,1,
		 0,0,1,1,0,
		 1,0,0,0,1,
		 0,1,1,1,0},
		{0,0,1,1,0,
		 0,1,0,1,0,
		 1,0,0,1,0,
		 1,1,1,1,1,
		 0,0,0,1,0},
		{1,1,1,1,1,
		 1,0,0,0,0,
		 1,1,1,1,0,
		 0,0,0,0,1,
		 1,1,1,1,0},
		{0,1,1,1,1,
		 1,0,0,0,0,
		 1,1,1,1,0,
		 1,0,0,0,1,
		 0,1,1,1,0},
		{1,1,1,1,1,
		 0,0,0,0,1,
		 0,0,0,1,0,
		 0,0,1,0,0,
		 0,1,0,0,0},
		{0,1,1,1,0,
		 1,0,0,0,1,
		 0,1,1,1,0,
		 1,0,0,0,1,
		 0,1,1,1,0},
		{0,1,1,1,0,
		 1,0,0,0,1,
		 0,1,1,1,1,
		 0,0,0,0,1,
		 0,0,1,1,0},
		{0,1,1,1,0,
		 1,0,0,0,1,
		 1,1,1,1,1,
		 1,0,0,0,1,
		 1,0,0,0,1},
		{1,1,1,1,0,
		 1,0,0,0,1,
		 1,1,1,1,0,
		 1,0,0,0,1,
		 1,1,1,1,0},
		{0,1,1,1,1,
		 1,0,0,0,0,
		 1,0,0,0,0,
		 1,0,0,0,0,
		 0,1,1,1,1},
		{1,1,1,1,0,
		 1,0,0,0,1,
		 1,0,0,0,1,
		 1,0,0,0,1,
		 1,1,1,1,0},
		{1,1,1,1,1,
		 1,0,0,0,0,
		 1,1,1,1,0,
		 1,0,0,0,0,
		 1,1,1,1,1},
		{1,1,1,1,1,
		 1,0,0,0,0,
		 1,1,1,1,0,
		 1,0,0,0,0,
		 1,0,0,0,0},
		{0,1,1,1,1,
		 1,0,0,0,0,
		 1,0,1,1,1,
		 1,0,0,0,1,
		 0,1,1,1,1},
		{1,0,0,0,1,
		 1,0,0,0,1,
		 1,1,1,1,1,
		 1,0,0,0,1,
		 1,0,0,0,1},
		{0,1,1,1,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,1,1,1,0},
		{0,0,0,0,1,
		 0,0,0,0,1,
		 0,0,0,0,1,
		 1,0,0,0,1,
		 0,1,1,1,0},
		{1,0,0,0,1,
		 1,0,0,1,0,
		 1,1,1,0,0,
		 1,0,0,1,0,
		 1,0,0,0,1},
		{1,0,0,0,0,
		 1,0,0,0,0,
		 1,0,0,0,0,
		 1,0,0,0,0,
		 1,1,1,1,1},
		{1,0,0,0,1,
		 1,1,0,1,1,
		 1,0,1,0,1,
		 1,0,0,0,1,
		 1,0,0,0,1},
		{1,0,0,0,1,
		 1,1,0,0,1,
		 1,0,1,0,1,
		 1,0,0,1,1,
		 1,0,0,0,1},
		{0,1,1,1,0,
		 1,0,0,0,1,
		 1,0,0,0,1,
		 1,0,0,0,1,
		 0,1,1,1,0},
		{1,1,1,1,0,
		 1,0,0,0,1,
		 1,1,1,1,0,
		 1,0,0,0,0,
		 1,0,0,0,0},
		{0,1,1,1,0,
		 1,0,0,0,1,
		 1,0,1,0,1,
		 1,0,0,1,0,
		 0,1,1,0,1},
		{1,1,1,1,0,
		 1,0,0,0,1,
		 1,1,1,1,0,
		 1,0,0,0,1,
		 1,0,0,0,1},
		{0,1,1,1,1,
		 1,0,0,0,0,
		 0,1,1,1,0,
		 0,0,0,0,1,
		 1,1,1,1,0},
		{1,1,1,1,1,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0},
		{1,0,0,0,1,
		 1,0,0,0,1,
		 1,0,0,0,1,
		 1,0,0,0,1,
		 0,1,1,1,0},
		{1,0,0,0,1,
		 1,0,0,0,1,
		 1,0,0,0,1,
		 0,1,0,1,0,
		 0,0,1,0,0},
		{1,0,0,0,1,
		 1,0,0,0,1,
		 1,0,1,0,1,
		 1,0,1,0,1,
		 0,1,0,1,0},
		{1,0,0,0,1,
		 0,1,0,1,0,
		 0,0,1,0,0,
		 0,1,0,1,0,
		 1,0,0,0,1},
		{1,0,0,0,1,
		 0,1,0,1,0,
		 0,0,1,0,0,
		 0,0,1,0,0,
		 0,0,1,0,0},
		{1,1,1,1,1,
		 0,0,0,1,0,
		 0,0,1,0,0,
		 0,1,0,0,0,
		 1,1,1,1,1},
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,1,0,0,
		 0,0,0,0,0},
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,1,1,1,0},
		{0,0,1,0,0,
		 0,1,0,0,0,
		 0,1,0,0,0,
		 0,1,0,0,0,
		 0,0,1,0,0},
		{0,0,1,0,0,
		 0,0,0,1,0,
		 0,0,0,1,0,
		 0,0,0,1,0,
		 0,0,1,0,0},
		{0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0,
		 0,0,0,0,0}
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
	}else{
		situ = 40;
	}
	mat.allocate(5,5);
	int i;
	for(i=0;i<25;i++){
		mat.push(b[situ][i]?clr:color(0,0,0,0));
	}
}
void KoishiExpand::StrMat(std::string str, Koishi::matrix &mat, Koishi::color clr){
	char p;
	matrix subMat;
	mat.allocate(5,6*str.size()+6);
	mat.fill(0);
	for(int i = 0;i<str.size();i++){
		p = str[str.size()-i-1];
		KoishiExpand::CharMat(p, subMat, clr);
		mat.putFore(subMat);
		mat.elemMoveHonz(6);
		subMat.release();
	}
}
void KoishiExpand::CharMat2(char p, Koishi::matrix &mat, Koishi::color clr){
	if(p>='a'&& p <= 'z'){
		p = p-'a'+'A';
	}
	int b[41][100]={
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,1,1,1,1,
		 1,1,0,0,0,1,0,0,1,1,
		 1,1,0,0,1,0,0,0,1,1,
		 1,1,1,1,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,1,1,0,0,0,0,
		 0,0,0,1,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,1,1,1,1,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,1,1,1,0,0,
		 0,0,0,0,1,1,1,1,0,0,
		 0,0,0,1,1,0,1,1,0,0,
		 0,0,1,1,0,0,1,1,0,0,
		 0,1,1,0,0,0,1,1,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,1,1,0,0,
		 0,0,0,0,0,0,1,1,0,0,
		 0,0,0,0,0,0,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 0,0,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,0,0,0,0,0,0,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,1,1,0,
		 0,0,0,0,0,0,1,1,0,0,
		 0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0},
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
		{1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,0,0,1,1,0,
		 0,0,0,0,0,0,1,1,0,0,
		 0,0,0,0,1,1,1,0,0,0,
		 0,0,0,1,1,1,0,0,0,0,
		 0,0,1,1,0,0,0,0,0,0,
		 0,1,1,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,
		 1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,1,1,1,1,1,1,0,0},
		{0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,0,1,1,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,0,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0}
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
	}else{
		situ = 40;
	}
	mat.allocate(10,10);
	int i;
	for(i=0;i<100;i++){
		mat.push(b[situ][i]?clr:color(0,0,0,0));
	}
}
void KoishiExpand::StrMat2(std::string str, Koishi::matrix &mat, Koishi::color clr){
	char p;
	matrix subMat;
	mat.allocate(10,11*str.size()+11);
	mat.fill(0);
	for(int i = 0;i<str.size();i++){
		p = str[str.size()-i-1];
		KoishiExpand::CharMat2(p, subMat, clr);
		mat.putFore(subMat);
		mat.elemMoveHonz(11);
		subMat.release();
	}
}

bool KoishiExpand::AvatarMarking(std::string avatarNPKfileName){
	int i, j, k;
	NPKobject inputNo;
	NPKobject outputNo;
	IMGobject io;

	if(!inputNo.loadFile(avatarNPKfileName)){
		//printf("No good npk files...\n");
		return false;
	}
	outputNo.create();
	////////////////////////////////////////////////////////////////////
	//第一步：寻找需要打标的IMG文件
	std::vector<int> imgSitList;
	std::vector<int> imgIDList;
	std::vector<int> imgPartList;
	KoishiTitle::avatar av;

	imgSitList.clear();
	imgIDList.clear();
	imgPartList.clear();
	//printf("Calculating marking imgs...\n");
	for(i=0;i<inputNo.count;i++){
		av.useName(KoishiTitle::shorten(inputNo.content[i].get_imgname()));
		if(imgIDList.size() == 0 || imgIDList[imgIDList.size()-1] != av.mainPartID){
			inputNo.IMGextract(i, io);
			if(io.PICcontent[0].get_dataSize()>2){
				imgIDList.push_back(av.mainPartID);
				imgSitList.push_back(i);
				imgPartList.push_back((int)av.mainPart);
			}
			io.release();
		}
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
		//i=14;
		situ = imgSitList[i];
		inputNo.IMGextract(situ, io);
		inputNo.IMGextract(situ, ioTemp);
		imgName = inputNo.content[situ].get_imgname();
		//printf("Marking ");
		//printf(KoishiTitle::shorten(imgName).c_str());
		//printf("(%d/%d):\n",1+i, imgSitList.size());
		if(io.version == V6 && io.paletteData.getCount()<=0){
			io.release();
			//printf("No palettes...\n");
			continue;
		}
		if(io.version != V2 && io.paletteData[0].size()<=1){
			io.release();
			//printf("Palette color lacking...\n");
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
					x1 = MIN(20, pi.get_basePt().get_X());
					y1 = MIN(180, pi.get_basePt().get_Y());
					x2 = pi.get_basePt().get_X()+pi.get_picSize().get_W();
					y2 = pi.get_basePt().get_Y()+pi.get_picSize().get_H();
					mat.allocate(y2-y1, x2-x1);
					io.PICextract(k, orginMat);
					mat.putFore(orginMat);
					mat.elemMoveHonz(pi.get_basePt().get_X()-x1);
					mat.elemMoveVert(pi.get_basePt().get_Y()-y1);
					KoishiExpand::StrMat2(KoishiTitle::shorten(imgName), markMat);
					markMoved.allocate((markMat.getRowCount()+1)*13, markMat.getColumnCount()+100);
					markMoved.putFore(markMat);
					markMoved.elemMoveHonz(20-x1);
					markMoved.elemMoveVert(180-y1+(markMat.getRowCount()+1)*imgPartList[i]);
					mat.putFore(markMoved);
					io.PICpreprocess(mat, s, pi);
					pi.set_basePt(point(x1,y1));
					ioTemp.PICreplace(k, pi, s);
					mat.release();
					markMat.release();
					markMoved.release();
					orginMat.release();
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
						if(io.paletteData[0][j].get_A() == 0){
							alphaIndex = j;
							break;
						}
					}
					x1 = MIN(20, pi.get_basePt().get_X());
					y1 = MIN(180, pi.get_basePt().get_Y());
					x2 = pi.get_basePt().get_X()+pi.get_picSize().get_W();
					y2 = pi.get_basePt().get_Y()+pi.get_picSize().get_H();

					mat.allocate(y2-y1, x2-x1);
					io.PICextractIndexMatrix(k, orginMat);
					mat.putFore(orginMat);
					mat.elemMoveHonz(pi.get_basePt().get_X()-x1);
					mat.elemMoveVert(pi.get_basePt().get_Y()-y1);
					KoishiExpand::StrMat2(KoishiTitle::shorten(imgName), markMat, color((alphaIndex==1)?2:1,0,0,0));
					markMoved.allocate((markMat.getRowCount()+1)*13, markMat.getColumnCount()+100);
					markMoved.putFore(markMat);
					markMoved.elemMoveHonz(20-x1);
					markMoved.elemMoveVert(180-y1+(markMat.getRowCount()+1)*imgPartList[i]);
					mat.putFore(markMoved);

					for(m1=0;m1<mat.getRowCount();m1++){
						for(m2=0;m2<mat.getColumnCount();m2++){
							if((m1<pi.get_basePt().get_Y()-y1 || m2<pi.get_basePt().get_X()-x1) && mat[m1][m2] == color(0,0,0,0)){
								mat.setElem(m1,m2,color(alphaIndex,0,0,0));
							}
						}
					}
					io.PICpreprocessIndexMatrix(mat, s, pi);
					pi.set_basePt(point(x1,y1));
					ioTemp.PICreplace(k, pi, s);
					mat.release();
					markMat.release();
					markMoved.release();
					orginMat.release();
					s.release();
				}
			}
		}
		outputNo.IMGpush(ioTemp, imgName);
		io.release();
		ioTemp.release();
		//printf("Done.\n");
	}
	outputNo.saveFile("(marked)"+avatarNPKfileName);
	inputNo.release();
	outputNo.release();
	return true;
}
bool KoishiExpand::AvatarBatchMarking(std::string avatarNPKfileListName){
	std::ifstream myfile(avatarNPKfileListName); 
	if(!myfile.is_open()){
		//printf("No NPK list file exists");
		//system("pause");
		return false;
	}
	str temp;
	while(getline(myfile,temp)){
		//printf("Now dealing ");
		//printf(temp.c_str());
		//printf("...\n");
		AvatarMarking(temp);
	}
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
	lcolor lc;
	li32 li;
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
			if(c.get_A()<=0x7F)
				continue;
			c.set_A(0xFF);
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
		mat.release();
		millages = 500*i/io.indexCount;
	}
	lc = pl[0];
	//取出数目最多的若干个颜色
	lcolor lc2; //这个就是新的色表
	li32 li2;
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
			if(c.get_A()<=0x7F){
				s.push((b8)0);
			}else{
				c.set_A(0xFF);
				int lowdist = 0x7FFFFFFF;
				int lowID = -1;
				for(k=0;k<lc2.size();k++){
					int dist = Koishi::color::EuclideanDistanceSquareOf(c,lc2[k]);
					if(dist<=lowdist){
						lowID = k;						//最短颜色欧氏距离匹配
						lowdist = dist;
					}
				}
				s.push((b8)(1+lowID));
			}
		}
		s.compressData(s1, COMP_ZLIB);
		pi.set_format(ARGB1555);
		pi.set_comp(COMP_ZLIB);
		pi.set_dataSize(s1.getLen());
		goal.PICpush(pi, s1);
		s.release();
		s1.release();
		mat.release();
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

bool KoishiExpand::SPKobject::load(str fileName){
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
		sb.startPos = data.ptPos();
		data.read(sb.bzlib);
		data.read(sb.len);
		data.read(sb.bzlib_r);
		data.read(sb.len_r);
		for(j=0;j<32;j++){
			data.read(sb.hash[j]);
		}
		sb.mainStartPos = data.ptPos();
		data.ptMove(sb.len);
		list.push_back(sb);
	}
	return true;
}

void KoishiExpand::SPKobject::release(){
	data.release();
}

void KoishiExpand::SPKobject::extract(int pos, stream &s){
	data.ptMoveTo(list[pos].mainStartPos);
	data.readStream(s, list[pos].len);
}

void KoishiExpand::SPKobject::extractTrueStream(stream &s){
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

void KoishiExpand::SPKobject::makeNPK(str NPKfileName){
	stream s;
	extractTrueStream(s);
	s.makeFile(NPKfileName);
}

KoishiExpand::LSTfile::LSTfile(){
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

KoishiExpand::LSTfolder::LSTfolder(){
	int i = 0;
	nameLen = 0;
	for(i=0;i<256;i++){
		name[i] = 0;
	}
	fileCount = 0;
	subFolderCount = 0;
	list.clear();
}
void KoishiExpand::LSTobject::load(Koishi::stream &s){
	int i,j;
	unsigned long temp;
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
bool KoishiExpand::LSTobject::load(const str &fileName){
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

bool KoishiExpand::LSTobject::getImagePack2(LSTfolder &lf){
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

bool KoishiExpand::TCTobject::load(Koishi::str fileName){
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
	dtStartPos = data.ptPos();
	return true;
}
bool KoishiExpand::TCTobject::release(){
	data.release();
	return true;
}
bool KoishiExpand::TCTobject::makeNPK(Koishi::str NPKfileName){
	stream s, s1, sHead,sOut;
	data.ptMoveTo(dtStartPos);
	data.readStream(s, comSize);
	sHead.allocate(2);
	sHead.push((b16)0x9C78);
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
KoishiExpand::LSTfile2::LSTfile2(){
	int i;
	for(i=0;i<256;i++){
		name[i] = 0;		
	}
	for(i=0;i<32;i++){
		lenStr[i] = 0;
		hash[i] = 0;	
	}
}
bool KoishiExpand::LSTobject2::load(const Koishi::str &fileName){
	int i,j;
	unsigned char n;
	stream s,sSplit;
	lb64 pos, len;
	s.loadFile(fileName);
	sSplit.allocate(20);
	sSplit.pushString("ImagePacks2\\");
	s.splitStream(sSplit, pos, len);
	sSplit.release();
	list.clear();
	for(i=1;i<pos.size();i++){
		s.ptMoveTo(pos[i]);
		LSTfile2 lf2;
		j = 0;
		while(true){
			s.read(n);
			if(n == 0x22){
				break;
			}else{
				lf2.name[j++] = n;
			}
		}
		s.read(n);
		j = 0;
		while(true){
			s.read(n);
			if(n == 0x20){
				break;
			}else{
				lf2.hash[j++] = n;
			}
		}
		j = 0;
		while(true){
			s.read(n);
			if(n == 0x0D){
				break;
			}else{
				lf2.lenStr[j++] = n;
			}
		}
		list.push_back(lf2);
	}
	return true;
}
/////////////旧版本IMG///////////////////
bool KoishiExpand::OldIMGobject::load(const Koishi::str &fileName){
	stream s;
	if(!s.loadFile(fileName))
		return false;
	return load(s);
}

bool KoishiExpand::OldIMGobject::load(Koishi::stream &s){
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
	if(dwVersion != (unsigned long)Koishi::IMGversion::V1){
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
		pi.getPtr_picSize()->set_W((long)dwTemp);
		s.read(dwTemp);
		pi.getPtr_picSize()->set_H((long)dwTemp);
		s.read(dwTemp);
		pi.set_dataSize(dwTemp);
		s.read(dwTemp);
		pi.getPtr_basePt()->set_X((long)dwTemp);
		s.read(dwTemp);
		pi.getPtr_basePt()->set_Y((long)dwTemp);
		s.read(dwTemp);
		pi.getPtr_frmSize()->set_W((long)dwTemp);
		s.read(dwTemp);
		pi.getPtr_frmSize()->set_H((long)dwTemp);
		PICcontent.push_back(pi);
		posList.push_back(s.ptPos());
		lenList.push_back(pi.get_dataSize());
		s.ptMove(pi.get_dataSize());
	}
	return true;
}
bool KoishiExpand::OldIMGobject::make(Koishi::IMGobject &io){
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
bool KoishiExpand::OldIMGobject::release(){
	data.release();
	posList.clear();
	lenList.clear();
	return true;
}
/////////////图像工具////////////////////
KoishiExpand::KoishiImageTool::gradient::gradient(unsigned int newRange){
	range = newRange;
	keyColorList.clear();
	keyColorSection.clear();
}
void KoishiExpand::KoishiImageTool::gradient::setRange(unsigned int newRange){
	unsigned int oldRange = range;
	range = newRange;
	int i;
	for(i=0;i<keyColorSection.size();i++){
		keyColorSection[i] *= newRange;
		keyColorSection[i] /= oldRange;
	}
}
void KoishiExpand::KoishiImageTool::gradient::addKey(Koishi::color newKeyColor, unsigned int situ){
	if(situ > range)
		return;
	int i;
	if(keyColorSection.size() == 0){
		keyColorList.push_back(newKeyColor);
		keyColorSection.push_back(situ);
	}else{
		if(situ < keyColorSection[0]){
			keyColorList.insert(keyColorList.begin(), newKeyColor);
			keyColorSection.insert(keyColorSection.begin(), situ);
		}else if(situ > keyColorSection[keyColorSection.size()-1]){
			keyColorList.push_back(newKeyColor);
			keyColorSection.push_back(situ);
		}else{
			for(i=0;i<keyColorSection.size()-1;i++){
				if(situ >= keyColorSection[i] && situ <keyColorSection[i+1]){
					keyColorList.insert(keyColorList.begin()+i, newKeyColor);
					keyColorSection.insert(keyColorSection.begin()+i, situ);
					break;
				}
			}
		}
	}
}
void KoishiExpand::KoishiImageTool::gradient::deleteKey(unsigned int id){
	if(id >= keyColorSection.size())
		return;
	keyColorList.erase(keyColorList.begin()+id);
	keyColorSection.erase(keyColorSection.begin()+id);
}
Koishi::color KoishiExpand::KoishiImageTool::gradient::pick(unsigned int situ) const{
	if(keyColorSection.size() == 0){
		return Koishi::color(0);
	}
	if(situ <= keyColorSection[0]){
		return keyColorList[0];
	}else if(situ >= keyColorSection[keyColorSection.size()-1]){
		return keyColorList[keyColorSection.size()-1];
	}else{
		int i;
		for(i=0;i<keyColorSection.size()-1;i++){
			if(situ >= keyColorSection[i] && situ <keyColorSection[i+1]){
				Koishi::color color1 = keyColorList[i];
				Koishi::color color2 = keyColorList[i+1];
				Koishi::color colorn;

				break;
			}
		}
	}
	return Koishi::color(0);
}