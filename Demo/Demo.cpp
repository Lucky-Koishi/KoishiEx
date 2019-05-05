// Demo.cpp : 定义控制台应用程序的入口点。
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
using namespace KoishiExpand::KoishiMarkTool;
using namespace KoishiExpand;
int _tmain(int argc, _TCHAR* argv[]){
	NPKobject no("I:\\ImagePacks2\\sprite_item_avatar_mage.NPK");
	std::vector<matrix> mat1;
	KoishiExpand::exhibit ex;
	ex.create(2800, 2800);
	for(int i = 0;i<no.count;i++){
		IMGobject io;
		no.IMGextract(i, io);
		for(int j = 0;j<io.indexCount;j++){
			matrix mat;
			io.PICextract(j, mat);
			mat1.push_back(mat);
			ex.putMatrix(mat, true);
			printf("_");
		}
		printf("|");
	}
	ex.canvas.makePNG("1.png");
	while(1);
	return 0;
}
