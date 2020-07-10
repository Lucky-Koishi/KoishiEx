#pragma once
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiNeoplePack.h"
#include "../KoishiEx/KoishiImageTool.h"

//////////////////////////////////////////////////////
//֧��
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
CString FmtToCStr(const PICinfo &pi, IMGversion iv);
CString GetCurDir();
int B16CStrToNum(CString b16cstr);
void GetFile(CString folderName, std::vector<CString> &fileList, std::vector<CString> &pathList);
///////////////////////////////////////////////////////
//����
///////////////////////////////////////////////////////
int GetInternetFile(CString strUrl, CString strSavePath);
///////////////////////////////////////////////////////
//�������ú�
///////////////////////////////////////////////////////
#define CHS_LOCALE_START {\
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));\
	setlocale(LC_CTYPE, "chs");
#define CHS_LOCALE_END \
	setlocale(LC_CTYPE, old_locale);\
	free(old_locale);\
}
///////////////////////////////////////////////////////
//�ؼ�����ǿ��ת����
///////////////////////////////////////////////////////
#define GET_CTRL(theClass, theID) \
	(( theClass * )GetDlgItem( theID ))
#define GET_DLG_CTRL(theClass, theID) \
	(( theClass * )dlg->GetDlgItem( theID ))
#define ENABLE_CTRL(theID, newStatus) \
	(GetDlgItem( theID )->EnableWindow(newStatus))
#define CHECK_CTRL(theID, newStatus) \
	(GET_CTRL(CButton, theID)->SetCheck(newStatus))
#define SET_CTRL(theClass, theID, left, top, right, bottom) \
	GET_CTRL(theClass, theID)->SetWindowPos(NULL,left,top,(right)-(left),(bottom)-(top),SWP_NOZORDER)
#define MOVEW(x) \
	CRect rect;\
	GetClientRect(&rect);\
	ClientToScreen(&rect);\
	x.SetWindowPos(this, rect.left+100, rect.top+100, 0, 0 , SWP_NOSIZE)
#define CREATEW(x,y) \
	x.Create(y,this);\
	x.ShowWindow(SW_HIDE)
///////////////////////////////////////////////////////
//��ⷵ�غ�
///////////////////////////////////////////////////////
#define CHECK_VALID(x)				if(!(x)){return;}			
#define CHECK_VALID_RETURN(x)		if(!(x)){return 0;}
#define CHECK_VALID_CONTINUE(x)		if(!(x)){continue;}
#define CHECK_VALID_BREAK(x)		if(!(x)){break;}
///////////////////////////////////////////////////////
//�̺߳���������
///////////////////////////////////////////////////////
#define DeclareThreadFunc(funName, argType) \
	void funName(argType);\
	static void THREAD_##funName(void*, argType);
///////////////////////////////////////////////////////
//�̺߳��������
///////////////////////////////////////////////////////
#define DefineThreadFunc(theClass, funName, argType)\
	void theClass::THREAD_##funName(void*context, argType para){\
		((theClass*)context)->funName(para);\
	}\
	void theClass::funName(argType para)
///////////////////////////////////////////////////////
//�̺߳������ú�
///////////////////////////////////////////////////////
#define StartThreadFunc(funName, argPara)\
	std::thread(THREAD_##funName, this, argPara).detach();
///////////////////////////////////////////////////////
//�ļ���ѡ��Ի����
///////////////////////////////////////////////////////
#define CALL_FOLDER_DIALOG(cstrPara, title, errorMsgTitle, errorMsg) {\
	HWND hwnd= GetSafeHwnd();\
	CString GET_FOLDER_NAME = L"";\
	LPMALLOC pMalloc;\
	if(::SHGetMalloc(&pMalloc) == NOERROR) {\
		BROWSEINFO bi;\
		TCHAR pszBuffer[MAX_PATH];\
		LPITEMIDLIST pidl;\
		bi.hwndOwner = hwnd;\
		bi.pidlRoot = NULL;\
		bi.pszDisplayName = pszBuffer;\
		bi.lpszTitle = (title);\
		bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;\
		bi.lpfn = NULL;\
		bi.lParam = 0;\
		bi.iImage = 0;\
		if((pidl = ::SHBrowseForFolder(&bi)) != NULL) {\
			if(::SHGetPathFromIDList(pidl, pszBuffer)) {\
				GET_FOLDER_NAME = pszBuffer;\
			}\
			pMalloc->Free(pidl);\
			if(GET_FOLDER_NAME.GetLength() <= 1) {\
				MessageBox(errorMsg, errorMsgTitle);\
			} else {\
				cstrPara = GET_FOLDER_NAME;}}}\
	pMalloc->Release();\
}