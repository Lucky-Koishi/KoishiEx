// Demo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiBase.cpp"
#include "../KoishiEx/Koishidata.cpp"
#include "../KoishiEx/Koishifactory.cpp"
#include "../KoishiEx/sha256.cpp"
#include "TestFunc.h"
#include "../KoishiEx//DDS.cpp"
#include "../KoishiEx//avatar.cpp"
#include "../KoishiEx//KoishiExpand.cpp"
#include <string>
#include <iostream>
#include <fstream> 
#include <exception>
#include <time.h>
#include <stdlib.h>
#include <io.h>
using namespace Koishi;
using namespace KoishiAvatar;
using namespace KoishiExpand::KoishiImageTool;
using namespace KoishiExpand;

uchar deal(uchar p){
	//ȡ����ѭ������
	uchar rp = ~p;
	uchar res = rp << 5;
	res |= rp >> 3;
	return res;
}
int _tmain(int argc, _TCHAR* argv[]){
	BMPobject bo;
	matrix mat;
	mat.loadPNG("1.png");
	makeBMP(mat, "�������.bmp");
	//while(1);
	return 0;
}
