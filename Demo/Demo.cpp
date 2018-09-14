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
using namespace KoishiTitle;
using namespace KoishiExpand;

int _tmain(int argc, _TCHAR* argv[]){
	matrix mat;
	mat.loadPNG("13.png");
	mat.loseBlack(1);
	mat.makePNG("131.png");
	return 0;
}
