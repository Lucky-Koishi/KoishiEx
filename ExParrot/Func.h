#pragma once
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiNeoplePack.h"
#include "../KoishiEx/KoishiImageTool.h"
#include "../KoishiEx//KoishiAudioTool.h"
//////////////////////////////////////////////////////
//Ö§³Ö
//////////////////////////////////////////////////////
using namespace Koishi;
using namespace KoishiNeoplePack;
using namespace KoishiImageTool;
using KoishiImageTool::DDS::DDSobject;
void CStrToStr(CString cstr,str &str1);
str CStrToStr(CString cstr);
CString StrToCStr(str str1);
CString NumToCStr(int n);
CString DoubleToCStr(double n);
CString GetTail(CString str1);
CString Underlining(CString str1);
CString Slashing(CString str1);
CString PtToCStr(point pt);
CString SzToCStr(size pt);
CString ClrToCStr(color clr);
CString FmtToCStr(colorFormat cf, IMGversion iv);
CString GetCurDir();
int B16CStrToNum(CString b16cstr);