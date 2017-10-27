#include "Func.h"
#include "stdafx.h"

#include "../KoishiEx/KoishiBase.cpp"
#include "../KoishiEx/Koishidata.cpp"
#include "../KoishiEx/Koishifactory.cpp"
#include "../KoishiEx/sha256.cpp"
#include "../KoishiEx/dds.cpp"
#include "goodlistctrl.cpp"

void CStrToStr(CString cstr,str &str1)  
{  
    int n = cstr.GetLength(); //按字符计算，str的长度  
    int len = WideCharToMultiByte(CP_ACP,0,cstr,n,NULL,0,NULL,NULL);//按Byte计算str长度  
    char *pChStr = new char[len+1];//按字节为单位  
    WideCharToMultiByte(CP_ACP,0,cstr,n,pChStr,len,NULL,NULL);//宽字节转换为多字节编码  
    pChStr[len] = '\0';//不要忽略末尾结束标志  
  
    str1 = pChStr;  
    delete []pChStr;  
}
CString StrToCStr(str str1){
	return CString(str1.c_str());
}
CString NumToCStr(int n){
	CString s;
	s.Format(L"%d",n);
	return s;
}
CString shorten(CString str1, char split){
	CString s;
	int i = str1.ReverseFind(split);
	s = str1.Right(str1.GetLength()-i-1);
	return s;
}
CString to_(CString str1){
	str1.Replace(L"/", L"_");
	str1.Replace(L":", L"");
	str1.Replace(L"\\", L"_");
	return str1;
}
str to_(str str1){
	str str2;
	CString cstr1 = StrToCStr(str1);
	CString cstr2 = to_(cstr1);
	CStrToStr(cstr2, str2);
	return str2;
}
CString PtToCStr(point pt){
	CString s;
	s.Format(L"(%d，%d)",pt.get_X(), pt.get_Y());
	return s;
}
CString SzToCStr(size pt){
	CString s;
	s.Format(L"%d×%d",pt.get_W(), pt.get_H());
	return s;
}
CString ClrToCStr(color clr){
	CString s;
	s.Format(L"%02X%02X%02X%02X",clr.get_R(),clr.get_G(),clr.get_B(),clr.get_A());
	return s;
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
		if(iv == V2 || iv == V5){
			s = L"ARGB1555";
		}else{
			s = L"索引颜色";
		}
		break;
	case LINK:
		s = L"指向帧号";
		break;
	case DDS_DXT1:
		s = L"DDS_DXT1";
		break;
	case DDS_DXT3:
		s = L"DDS_DXT3";
		break;
	case DDS_DXT5:
		s = L"DDS_DXT5";
		break;
	default:
		s = L"暂未定义";
		break;
	}
	return s;
}
CString getCurDir(){
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
CString getOutPutDir(CString subFolderName){
	TCHAR strCurDrt[500];  
	int nLen = ::GetCurrentDirectory(500,strCurDrt);  
	if( strCurDrt[nLen]!='\\' )  
	{  
		strCurDrt[nLen++] = '\\';  
		strCurDrt[nLen] = '\0';  
	}  
	CString savePathStr = strCurDrt;
	savePathStr += L"output";
	::CreateDirectory(savePathStr, NULL);
	if(subFolderName != L""){
		savePathStr += L"\\"+subFolderName;
		::CreateDirectory(savePathStr, NULL);
	}
	return savePathStr+L"\\";
}