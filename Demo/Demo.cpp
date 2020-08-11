// Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiBase.cpp"
#include "../KoishiEx/Koishidata.cpp"
#include "../KoishiEx/Koishifactory.cpp"
#include "../KoishiEx/sha256.cpp"
#include "TestFunc.h"
#include "../KoishiEx/KoishiImageTool.cpp"
#include "../KoishiEx/KoishiAudioTool.cpp"
#include "../KoishiEx/avatar.cpp"
#include "../KoishiEx/KoishiExpand.cpp"
#include <string>
#include <iostream>
#include <fstream> 
#include <exception>
#include <time.h>
#include <stdlib.h>
#include <io.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#include <locale.h>
#include <thread>

using namespace Koishi;
using namespace KoishiAudioTool;

#define RANGE LONG_MAX
#define PLAY 1


int _tmain(int argc, _TCHAR* argv[]){
	IMGobject io;
	image im;
	io.loadFile("E:\\Source\\KoishiEx_Test\\font.IMG");
	
	return 0;
}
