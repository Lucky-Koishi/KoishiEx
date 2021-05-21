#include "Func.h"
#include "stdafx.h"

#include "../KoishiEx/KoishiBase.cpp"
#include "../KoishiEx/Koishidata.cpp"
#include "../KoishiEx/Koishifactory.cpp"
#include "../KoishiEx/koishiexpand.cpp"
#include "../KoishiEx/sha256.cpp"
#include "../KoishiEx/KoishiImageTool.cpp"
#include "../KoishiEx/KoishiAudioTool.cpp"
#include "../KoishiEx/avatar.cpp"

#include <afxinet.h> 
#include <cstring>

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
#if 1
	return CString(str1.c_str());
#else
	//以下代码由网友m=0提供，可以解决显示乱码问题。
	int size = MultiByteToWideChar(CP_UTF8, 0, str1.c_str(), -1, NULL, 0);
	TCHAR *buffer = new TCHAR[size+1];
	memset(buffer, 0, sizeof(TCHAR)*(size + 1));
	MultiByteToWideChar(CP_UTF8, 0, str1.c_str(), -1, buffer, size);
	CString temp(buffer);
	delete[] buffer;
	return temp;
#endif
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
	s.Format(L"%02X%02X%02X%02X",clr.R,clr.G,clr.B,clr.alpha);
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
CString FmtToCStr(const PICinfo &pi, IMGversion iv){
	CString s;
	switch(pi.format){
	case ARGB8888:
		s = L"ARGB8888";
		break;
	case ARGB4444:
		if(iv == V4 || iv == V6){
			s = L"索引颜色(改)";
		}else{
			s = L"ARGB4444";
		}
		break;
	case ARGB1555:
		if(iv == V2){
			s = L"ARGB1555";
		}else{
			if(pi.comp == COMP_NONE && pi.dataSize == 2 * pi.picSize.area()){
				s = L"ARGB1555";
			}else{
				s = L"索引颜色";
			}
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
	//CString pusheenStr;
	//pusheenStr.Format(L"%02X%02X", pi.format, pi.comp);
	//s += L"(" + pusheenStr + L")";
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
void GetFile(CString folderName, std::vector<CString> &fileList, std::vector<CString> &pathList) {
	CFileFind ff;
	BOOL ret = ff.FindFile(folderName);
	while(ret) {
		ret = ff.FindNextFile();
		if(ff.IsDots())
			continue;
		if(ff.IsDirectory()) {
			GetFile(ff.GetFilePath() + L"\\*.*", fileList, pathList);
		} else {
			fileList.push_back(ff.GetFileName());
			pathList.push_back(ff.GetFilePath());
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//以下代码来源：https://blog.csdn.net/charlessimonyi/article/details/8666108
//用于在网上下载文件到本地//////////////////////////////////////////////////
INT GetInternetFile(CString strUrl, CString strSavePath) {
#ifndef DISABLE_TEST
	if(strUrl.IsEmpty())
		return -5;
	if(strSavePath.IsEmpty())
		return -6;

	unsigned short nPort;       //用于保存目标HTTP服务端口  
	CString strServer, strObject;   //strServer用于保存服务器地址，strObject用于保存文件对象名称  
	DWORD dwServiceType, dwRet;      //dwServiceType用于保存服务类型，dwRet用于保存提交GET请求返回的状态号  

	//解析URL，获取信息  
	if(!AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort)) {
		//解析失败，该Url不正确  
		return -1;
	}
	//创建网络连接对象，HTTP连接对象指针和用于该连接的HttpFile文件对象指针，注意delete  
	CInternetSession intsess;
	CHttpFile *pHtFile = NULL;
	//建立网络连接  
	CHttpConnection *pHtCon = intsess.GetHttpConnection(strServer, nPort);
	if(pHtCon == NULL) {
		//建立网络连接失败  
		intsess.Close();
		return -2;
	}
	//发起GET请求  
	pHtFile = pHtCon->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
	if(pHtFile == NULL) {
		//发起GET请求失败  
		intsess.Close();
		delete pHtCon; pHtCon = NULL;
		return -3;
	}
	//提交请求
	try {
		pHtFile->SendRequest();
	} catch(CException *) {
		intsess.Close();
		delete pHtCon; pHtCon = NULL;
		delete pHtFile; pHtFile = NULL;
		return -8;
	}
	//获取服务器返回的状态号  
	pHtFile->QueryInfoStatusCode(dwRet);
	if(dwRet != HTTP_STATUS_OK) {
		//服务器不接受请求  
		intsess.Close();
		delete pHtCon; pHtCon = NULL;
		delete pHtFile; pHtFile = NULL;
		return -4;
	}
	//获取文件大小  
	UINT nFileLen = (UINT)pHtFile->GetLength();
	DWORD dwRead = 1;       //用于标识读了多少，为1是为了进入循环  
	//创建缓冲区  
	CHAR *szBuffer = new CHAR[nFileLen + 1];
	TRY
	{
		//创建文件  
		CFile PicFile(strSavePath, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		while(dwRead>0) {
			//清空缓冲区  
			memset(szBuffer, 0, (size_t)(nFileLen + 1));
			//读取到缓冲区  
			dwRead = pHtFile->Read(szBuffer, nFileLen);
			//写入到文件  
			PicFile.Write(szBuffer, dwRead);
		}
		//关闭文件  
		PicFile.Close();
		//释放内存  
		delete[]szBuffer;
		delete pHtFile;
		delete pHtCon;
		//关闭网络连接  
		intsess.Close();
	}
		CATCH(CFileException, e) {
		//释放内存  
		delete[]szBuffer;
		delete pHtFile;
		delete pHtCon;
		//关闭网络连接  
		intsess.Close();
		return -7;          //读写文件异常  
	}
	END_CATCH
#endif
		return 0;

}
//转载END/////////////////////////////////////////////////////////////////
