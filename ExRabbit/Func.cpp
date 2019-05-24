#include "Func.h"
#include "stdafx.h"

#include "../KoishiEx/KoishiBase.cpp"
#include "../KoishiEx/Koishidata.cpp"
#include "../KoishiEx/Koishifactory.cpp"
#include "../KoishiEx/koishiexpand.cpp"
#include "../KoishiEx/sha256.cpp"
#include "../KoishiEx/KoishiImageTool.cpp"
#include "../KoishiEx/avatar.cpp"
#include "goodlistctrl.cpp"

void CStrToStr(CString cstr,str &str1)  
{  
    int n = cstr.GetLength();										//按字符计算，str的长度  
    int len = WideCharToMultiByte(CP_ACP,0,cstr,n,NULL,0,NULL,NULL);//按Byte计算str长度  
    char *pChStr = new char[len+1];									//按字节为单位  
    WideCharToMultiByte(CP_ACP,0,cstr,n,pChStr,len,NULL,NULL);		//宽字节转换为多字节编码  
    pChStr[len] = '\0';												//不要忽略末尾结束标志  
  
    str1 = pChStr;  
    delete []pChStr;  
}
str CStrToStr(CString cstr){
	str p;
	CStrToStr(cstr, p);
	return p;
}
CString StrToCStr(str str1){
	return CString(str1.c_str());
}
CString NumToCStr(int n){
	CString s;
	s.Format(L"%d",n);
	return s;
}
CString DoubleToCStr(double n){
	CString s;
	s.Format(L"%.3lf",n);
	return s;
}
CString GetTail(CString str1){
	CString s;
	int i = str1.ReverseFind('\\');
	s = str1.Right(str1.GetLength()-i-1);
	i = str1.ReverseFind('/');
	s = str1.Right(s.GetLength()-i-1);
	return s;
}
CString Underlining(CString str1){
	str1.Replace(L"/", L"_");
	str1.Replace(L":", L"");
	str1.Replace(L"\\", L"_");
	return str1;
}
CString Slashing(CString str1){
	str1.Replace(L"_", L"/");
	return str1;
}
CString PtToCStr(point pt){
	CString s;
	s.Format(L"(%d，%d)",pt.X, pt.Y);
	return s;
}
CString SzToCStr(size pt){
	CString s;
	s.Format(L"%d×%d",pt.W, pt.H);
	return s;
}
CString ClrToCStr(color clr){
	CString s;
	s.Format(L"%02X%02X%02X%02X",clr.R,clr.G,clr.B,clr.A);
	return s;
}
int B16CStrToNum(CString b16cstr){
	if(b16cstr.GetLength() == 0){
		return 0;
	}
	if(b16cstr.GetLength() == 1){
		CString ABC[16] = {L"0",L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"A",L"B",L"C",L"D",L"E",L"F"};
		CString abc[16] = {L"0",L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"a",L"b",L"c",L"d",L"e",L"f"};
		for(int i = 0;i<16;i++){
			if(ABC[i] == b16cstr || abc[i] == b16cstr)
				return i;
		}
		return 0;
	}
	CString tail = b16cstr.Right(1);
	CString remain = b16cstr.Left(b16cstr.GetLength()-1);
	return B16CStrToNum(remain)*16 + B16CStrToNum(tail);
}
CString FmtToCStr(colorFormat cf, IMGversion iv){
	CString s;
	switch(cf){
	case ARGB8888:
		s = L"ARGB8888";
		break;
	case ARGB4444:
		s = L"ARGB4444";
		break;
	case ARGB1555:
		if(iv == V2){
			s = L"ARGB1555";
		}else{
			s = L"索引颜色";
		}
		break;
	case LINK:
		s = L"指向帧号";
		break;
	case DDS_DXT1:
		s = L"DXT1";
		break;
	case DDS_DXT3:
		s = L"DXT3";
		break;
	case DDS_DXT5:
		s = L"DXT5";
		break;
	default:
		s = L"暂未定义";
		break;
	}
	return s;
}
CString GetCurDir(){
	TCHAR strCurDrt[500];  
	int nLen = ::GetCurrentDirectory(500,strCurDrt);  
	if( strCurDrt[nLen]!='\\' )  
	{  
		strCurDrt[nLen++] = '\\';  
		strCurDrt[nLen] = '\0';  
	}  
	CString savePathStr = strCurDrt;
	return savePathStr;
}