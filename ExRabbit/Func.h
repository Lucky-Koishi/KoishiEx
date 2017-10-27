#pragma once
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/DDS.h"
//////////////////////////////////////////////////////
//Ö§³Ö
//////////////////////////////////////////////////////
using namespace Koishi;
void CStrToStr(CString cstr,str &str1);
CString StrToCStr(str str1);
CString NumToCStr(int n);
CString shorten(CString str1, char split);
CString to_(CString str1);
str to_(str str1);
CString PtToCStr(point pt);
CString SzToCStr(size pt);
CString ClrToCStr(color clr);
CString FmtToCStr(colorFormat cf, IMGversion iv);
CString getCurDir();
CString getOutPutDir(CString subFolderName);