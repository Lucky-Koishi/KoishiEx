#include "StdAfx.h"
#include "avatar.h"

using namespace KoishiTitle;

avatar::avatar(void)
{
}


avatar::~avatar(void)
{
}

bool avatar::useName(str fileName){
	str numstr = "";
	b8 p;
	i32 i;
	if(fileName.find("(tn)") == str::npos){
		isTN = false;
	}else{
		isTN = true;
	}
	if(fileName.find("_mask1") == str::npos){
		isMask1 = false;
		i = fileName.size()-5;
	}else{
		isMask1 = true;
		i = fileName.size()-11;
	}
	bool spc;//分两种情况进行讨论：mg_pants2000.img和mg_pants2000a2.img
	if(spc = isnum(p = fileName[i])){
		subPartID = atoi((const char*)&p);
		i --;
	}else{
		subPartID = 0;
	}
	switch(fileName[i]){
	case 'a':
		subPart = sp_a;
		i--;
		break;
	case 'b':
		subPart = sp_b;
		i--;
		break;
	case 'c':
		subPart = sp_c;
		i--;
		break;
	case 'd':
		subPart = sp_d;
		i--;
		break;
	case 'e':
		subPart = sp_e;
		i--;
		break;
	case 'f':
		subPart = sp_f;
		i--;
		break;
	case 'g':
		subPart = sp_g;
		i--;
		break;
	case 'h':
		subPart = sp_h;
		i--;
		break;
	case 'x':
		subPart = sp_x;
		i--;
		break;
	default:
		subPart = sp_udef;
		if(spc)
			i++;
		break;
	}
	while(isnum(p = fileName[i--])){
		numstr.push_back(p);
	}
	if(numstr.length() == 0)
		return false;
	std::reverse(numstr.begin(), numstr.end());
	mainPartID = std::stoi(numstr);
	if(fileName.find("coat") != str::npos){
		mainPart = mp_coat;
	}else if(fileName.find("pants") != str::npos){
		mainPart = mp_pants; 
	}else if(fileName.find("cap") != str::npos){
		mainPart = mp_cap;
	}else if(fileName.find("hair") != str::npos){
		mainPart = mp_hair;
	}else if(fileName.find("face") != str::npos){
		mainPart = mp_face;
	}else if(fileName.find("neck") != str::npos){
		mainPart = mp_neck;
	}else if(fileName.find("shoes") != str::npos){
		mainPart = mp_shoes;
	}else if(fileName.find("belt") != str::npos){
		mainPart = mp_belt;
	}else if(fileName.find("skin") != str::npos){
		mainPart = mp_skin;
	}else{
		mainPart = mp_weapon;
	}
	numstr = "";
	i = 0;
	if(isTN){
		i = 4;
	}
	numstr.push_back(fileName[i]);
	numstr.push_back(fileName[i+1]);
	if(numstr == "sm"){
		chars = ch_sm;
	}else if(numstr == "sg"){
		chars = ch_sg;
	}else if(numstr == "ft"){
		chars = ch_ft;
	}else if(numstr == "fm"){
		chars = ch_fm;
	}else if(numstr == "gn"){
		chars = ch_gn;
	}else if(numstr == "gg"){
		chars = ch_gg;
	}else if(numstr == "mg"){
		chars = ch_mg;
	}else if(numstr == "mm"){
		chars = ch_mm;
	}else if(numstr == "pr"){
		chars = ch_pr;
	}else if(numstr == "pg"){
		chars = ch_pg;
	}else if(numstr == "th"){
		chars = ch_th;
	}else if(numstr == "kn"){
		chars = ch_kn;
	}else if(numstr == "dl"){
		chars = ch_dl;
	}
	return true;
}

bool KoishiTitle::isnum(b8 chars){
	return chars >= '0' && chars <= '9';
}

str KoishiTitle::shorten(const str &path){
	str path1,path2;
	str::size_type st;
	st = path.find_last_of('\\');
	if(st != str::npos){
		path1 = path.substr(st+1);
	}else{
		path1 = path;
	}
	st = path1.find_last_of('/');
	if(st != str::npos){
		path2 = path1.substr(st+1);
	}else{
		path2 = path1;
	}
	return path2;
}
str KoishiTitle::replaceAll(const str &oldStr, const str &oldChar, const str &newChar){
	str newStr = oldStr;
	str::size_type pos;
	while(true){
		pos = newStr.find_last_of(oldChar);
		if(pos != str::npos){
			newStr.replace(pos, oldChar.length(), newChar);
		}else{
			break;
		}
	}
	return newStr;
}
str KoishiTitle::fileUnslash(const str &filePath){
	str newStr = replaceAll(filePath, "\\", "_");
	newStr = replaceAll(newStr, "/", "_");
	newStr = replaceAll(newStr, ":", "");
	return newStr;
}
str KoishiTitle::imgUnslash(const str &imgPath){
	return replaceAll(imgPath, "/", "_");
}
str KoishiTitle::imgSlash(const str &imgPath){
	return replaceAll(imgPath, "_", "/");
}
str KoishiTitle::imgAddV4Num(const str &imgName, i32 num){
	str newName = imgName;
	i32 i1 = num % 10;	//个位数
	i32 i2 = num / 10 % 10;	//十位数
	b8 c1 = '0'+i1;
	b8 c2 = '0'+i2;
	str::size_type pos = imgName.find_last_of('0');
	if(pos != str::npos){
		newName[pos] = c1;
		newName[pos-1] = c2;
	}
	return newName;
}

i32 KoishiTitle::avatar::getWeight() const{
	if(mainPart == mp_shoes && subPart == sp_f)
		return 2880;
	if(mainPart == mp_belt && subPart == sp_f )
		return 2870;
	if(mainPart == mp_pants && subPart == sp_f )
		return 2860;
	if(mainPart == mp_coat && subPart == sp_f )
		return 2850;
	if(mainPart == mp_neck && subPart == sp_f )
		return 2840;
	if(mainPart == mp_face && subPart == sp_f )
		return 2830;
	if(mainPart == mp_cap && subPart == sp_f )
		return 2810;
	if(mainPart == mp_face && subPart == sp_g )
		return 2750;
	if(mainPart == mp_face && subPart == sp_a )
		return 2700;
	if(mainPart == mp_weapon && subPart == sp_c)
		return 2600 + subPartID;
	if(mainPart == mp_cap && subPart == sp_c )
		return 2500;
	if(mainPart == mp_hair && subPart == sp_c )
		return 2400;
	if(mainPart == mp_neck && subPart == sp_e )
		return 2350;
	if(mainPart == mp_coat && subPart == sp_c )
		return 2300;
	if(mainPart == mp_neck && subPart == sp_g )
		return 2251;
	if(mainPart == mp_neck && subPart == sp_c )
		return 2200;
	if(mainPart == mp_weapon && subPart == sp_a)
		return 2150 + subPartID;
	if(mainPart == mp_cap && subPart == sp_g )
		return 2125;
	if(mainPart == mp_cap && subPart == sp_a )
		return 2100;
	if(mainPart == mp_hair && subPart == sp_a )
		return 2000;
	if(mainPart == mp_neck && subPart == sp_x )
		return 1975;
	if(mainPart == mp_belt && subPart == sp_g )
		return 1951;
	if(mainPart == mp_belt && subPart == sp_c )
		return 1950;
	if(mainPart == mp_face && subPart == sp_c )
		return 1925;
	if(mainPart == mp_neck && subPart == sp_a )
		return 1900;
	if(mainPart == mp_coat && subPart == sp_g )
		return 1850;
	if(mainPart == mp_coat && subPart == sp_a )
		return 1800;
	if(mainPart == mp_belt && subPart == sp_a )
		return 1700;
	if(mainPart == mp_shoes && subPart == sp_c )
		return 1600;
	if(mainPart == mp_pants && subPart == sp_g )
		return 1501;
	if(mainPart == mp_pants && subPart == sp_a )
		return 1500;
	if(mainPart == mp_shoes && subPart == sp_g )
		return 1450;
	if(mainPart == mp_shoes && subPart == sp_a )
		return 1400;
	if(mainPart == mp_pants && subPart == sp_b )
		return 1300;
	if(mainPart == mp_shoes && subPart == sp_h )
		return 1250;
	if(mainPart == mp_shoes && subPart == sp_b )
		return 1200;
	if(mainPart == mp_pants && subPart == sp_h )
		return 1151;
	if(mainPart == mp_pants && subPart == sp_d )
		return 1150;
	if(mainPart == mp_belt && subPart == sp_b )
		return 1100;
	if(mainPart == mp_neck && subPart == sp_b )
		return 1000;
	if(mainPart == mp_coat && subPart == sp_h )
		return 925;
	if(mainPart == mp_coat && subPart == sp_b )
		return 900;
	if(mainPart == mp_belt && subPart == sp_d )
		return 850;
	if(mainPart == mp_hair && subPart == sp_b )
		return 800;
	if(mainPart == mp_cap && subPart == sp_h )
		return 750;
	if(mainPart == mp_cap && subPart == sp_b )
		return 700;
	if(mainPart == mp_weapon && subPart == sp_b)
		return 650 + subPartID;
	if(mainPart == mp_neck && subPart == sp_d )
		return 600;
	if(mainPart == mp_neck && subPart == sp_h )
		return 550;
	if(mainPart == mp_coat && subPart == sp_d )
		return 500;
	if(mainPart == mp_hair && subPart == sp_d )
		return 400;
	if(mainPart == mp_cap && subPart == sp_d )
		return 300;
	if(mainPart == mp_weapon && subPart == sp_d)
		return 200 + subPartID;
	if(mainPart == mp_face && subPart == sp_b )
		return 100;
	if(mainPart == mp_skin)
		return 50;
	return 0;
}

str KoishiTitle::avaFmt(int i){
	str s = "";
	if(i>9999)
		s.push_back('0'+i/10000);
	s.push_back('0'+(i/1000)%10);
	s.push_back('0'+(i/100)%10);
	s.push_back('0'+(i/10)%10);
	s.push_back('0'+i%10);
	return s;
}

KoishiTitle::mixSeqElem KoishiTitle::mixSeqList[55] = {
	{mp_shoes, sp_f},
	{mp_belt, sp_f},
	{mp_pants, sp_f},
	{mp_coat, sp_f},
	{mp_neck, sp_f},
	{mp_face, sp_f},
	{mp_cap, sp_f},
	{mp_face, sp_g},
	{mp_face, sp_a},
	{mp_weapon, sp_c},
	{mp_cap, sp_c},
	{mp_hair, sp_c},
	{mp_neck, sp_e},
	{mp_coat, sp_c},
	{mp_neck, sp_g},
	{mp_neck, sp_c},
	{mp_weapon, sp_a},
	{mp_cap, sp_g},
	{mp_cap, sp_a},
	{mp_hair, sp_a},
	{mp_neck, sp_x},
	{mp_belt, sp_g},
	{mp_belt, sp_c},
	{mp_face, sp_c},
	{mp_neck, sp_a},
	{mp_coat, sp_g},
	{mp_coat, sp_a},
	{mp_belt, sp_a},
	{mp_shoes, sp_c},
	{mp_pants, sp_g},
	{mp_pants, sp_a},
	{mp_shoes, sp_g},
	{mp_shoes, sp_a},
	{mp_pants, sp_b},
	{mp_shoes, sp_h},
	{mp_shoes, sp_b},
	{mp_pants, sp_h},
	{mp_pants, sp_d},
	{mp_belt, sp_b},
	{mp_neck, sp_b},
	{mp_coat, sp_h},
	{mp_coat, sp_b},
	{mp_belt, sp_d},
	{mp_hair, sp_b},
	{mp_cap, sp_h},
	{mp_cap, sp_b},
	{mp_weapon, sp_b},
	{mp_neck, sp_d},
	{mp_neck, sp_h},
	{mp_coat, sp_d},
	{mp_hair, sp_d},
	{mp_cap, sp_d},
	{mp_weapon, sp_d},
	{mp_face, sp_b},
	{mp_skin, sp_udef}
};