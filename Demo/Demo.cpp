// Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiBase.cpp"
#include "../KoishiEx/Koishidata.cpp"
#include "../KoishiEx/Koishifactory.cpp"
#include "../KoishiEx/sha256.cpp"
#include "TestFunc.h"
#include "../KoishiEx//KoishiImageTool.cpp"
#include "../KoishiEx///KoishiAudioTool.cpp"
#include "../KoishiEx//avatar.cpp"
#include "../KoishiEx//KoishiExpand.cpp"
#include <string>
#include <iostream>
#include <fstream> 
#include <exception>
#include <time.h>
#include <stdlib.h>
#include <io.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#include "../KoishiEx//BZ2.cpp"
using namespace Koishi;
using namespace KoishiAudioTool;

#define BUILD 1
#define PLAY 1

#define _2_13 1.05946309436f
int _tmain(int argc, _TCHAR* argv[]){
	PCMdevice pd;
	pd.initFormat(2, 16, 44100, 88200, 4, 0);
	pd.record();
	Sleep(15000);
	stream s;
	pd.getData(s);
	audio ad;
	ad.create(s, 2, 44100);
	makeWAV(ad, "t.wav");
	
	pd.stop();
	s.release();
	ad.destory();

	pd.record();
	Sleep(10000);
	pd.getData(s);
	ad.create(s, 2, 44100);
	makeWAV(ad, "t2.wav");
	//stream s;
	//double d;
	//::OGGeasyDecode("F:\\KoishiEx\\test\\sounds_char_wizard_wz_dmg_03.ogg", s, d);
	////s.loadFile("TEST.pcm");
	//audio a(s, 1, 44100);
	//audio a1[13];
	//sequence seqh, seqb;
	//double av1 = 1;
	//double bv1 = 2;	
	//for(int i = 0;i<=12;i++){
	//	seqh.push_back(av1);
	//	seqb.push_back(bv1);
	//	av1 /= 1.05946309436f;
	//	bv1 /= 1.05946309436f;
	//	a.zoom(a1[i], seqh[i]);
	//	a.zoom(a1[i], seqb[i]);
	//}
	//int spum[64] = {
	//	3,	3,	0,	3,	0,	1,	3,	0,	5,	0,	0,	0,	-5,	0,	0,	0,
	//	1,0,0,-5,0,0,-3,0,-6,0,0,-7,0,-b7,6,0
	//};

	//audio t(4100*64, 1, 44100);
	//for(int i = 0;i<64;i++){
	//	if(spum[i]){
	//		t.mixWith(a1[spum[i]-1], 1, i*4100);
	//	}
	//}
	//::makeWAV(t, "1.wav");
	//printf("playing..\n");
	//TIC;
	//play(t);
	//TOC;
	//system("pause");
	return 0;
}
