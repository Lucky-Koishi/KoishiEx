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
#include "../koishiEx/bz2.cpp"
#include <afxinet.h> 
#include <cstring>

void CStrToStr(CString cstr,str &str1)  
{  
    int n = cstr.GetLength();										//���ַ����㣬str�ĳ���  
    int len = WideCharToMultiByte(CP_ACP,0,cstr,n,NULL,0,NULL,NULL);//��Byte����str����  
    char *pChStr = new char[len+1];									//���ֽ�Ϊ��λ  
    WideCharToMultiByte(CP_ACP,0,cstr,n,pChStr,len,NULL,NULL);		//���ֽ�ת��Ϊ���ֽڱ���  
    pChStr[len] = '\0';												//��Ҫ����ĩβ������־  
  
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
	//���´���������m=0�ṩ�����Խ����ʾ�������⡣
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
	s.Format(L"(%d��%d)",pt.X, pt.Y);
	return s;
}
CString SzToCStr(size pt){
	CString s;
	s.Format(L"%d��%d",pt.W, pt.H);
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
			s = L"������ɫ(��)";
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
				s = L"������ɫ";
			}
		}
		break;
	case LINK:
		s = L"ָ��֡��";
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
		s = L"��δ����";
		break;
	}
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
			s = L"������ɫ";
		}
		break;
	case LINK:
		s = L"ָ��֡��";
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
		s = L"��δ����";
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
//���´�����Դ��https://blog.csdn.net/charlessimonyi/article/details/8666108
//���������������ļ�������//////////////////////////////////////////////////
INT GetInternetFile(CString strUrl, CString strSavePath) {
#ifndef DISABLE_TEST
	if(strUrl.IsEmpty())
		return -5;
	if(strSavePath.IsEmpty())
		return -6;

	unsigned short nPort;       //���ڱ���Ŀ��HTTP����˿�  
	CString strServer, strObject;   //strServer���ڱ����������ַ��strObject���ڱ����ļ���������  
	DWORD dwServiceType, dwRet;      //dwServiceType���ڱ���������ͣ�dwRet���ڱ����ύGET���󷵻ص�״̬��  

	//����URL����ȡ��Ϣ  
	if(!AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort)) {
		//����ʧ�ܣ���Url����ȷ  
		return -1;
	}
	//�����������Ӷ���HTTP���Ӷ���ָ������ڸ����ӵ�HttpFile�ļ�����ָ�룬ע��delete  
	CInternetSession intsess;
	CHttpFile *pHtFile = NULL;
	//������������  
	CHttpConnection *pHtCon = intsess.GetHttpConnection(strServer, nPort);
	if(pHtCon == NULL) {
		//������������ʧ��  
		intsess.Close();
		return -2;
	}
	//����GET����  
	pHtFile = pHtCon->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
	if(pHtFile == NULL) {
		//����GET����ʧ��  
		intsess.Close();
		delete pHtCon; pHtCon = NULL;
		return -3;
	}
	//�ύ����
	try {
		pHtFile->SendRequest();
	} catch(CException *) {
		intsess.Close();
		delete pHtCon; pHtCon = NULL;
		delete pHtFile; pHtFile = NULL;
		return -8;
	}
	//��ȡ���������ص�״̬��  
	pHtFile->QueryInfoStatusCode(dwRet);
	if(dwRet != HTTP_STATUS_OK) {
		//����������������  
		intsess.Close();
		delete pHtCon; pHtCon = NULL;
		delete pHtFile; pHtFile = NULL;
		return -4;
	}
	//��ȡ�ļ���С  
	UINT nFileLen = (UINT)pHtFile->GetLength();
	DWORD dwRead = 1;       //���ڱ�ʶ���˶��٣�Ϊ1��Ϊ�˽���ѭ��  
	//����������  
	CHAR *szBuffer = new CHAR[nFileLen + 1];
	TRY
	{
		//�����ļ�  
		CFile PicFile(strSavePath, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		while(dwRead>0) {
			//��ջ�����  
			memset(szBuffer, 0, (size_t)(nFileLen + 1));
			//��ȡ��������  
			dwRead = pHtFile->Read(szBuffer, nFileLen);
			//д�뵽�ļ�  
			PicFile.Write(szBuffer, dwRead);
		}
		//�ر��ļ�  
		PicFile.Close();
		//�ͷ��ڴ�  
		delete[]szBuffer;
		delete pHtFile;
		delete pHtCon;
		//�ر���������  
		intsess.Close();
	}
		CATCH(CFileException, e) {
		//�ͷ��ڴ�  
		delete[]szBuffer;
		delete pHtFile;
		delete pHtCon;
		//�ر���������  
		intsess.Close();
		return -7;          //��д�ļ��쳣  
	}
	END_CATCH
#endif
		return 0;

}
//ת��END/////////////////////////////////////////////////////////////////
