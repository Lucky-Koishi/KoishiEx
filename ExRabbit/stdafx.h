
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include <afxsock.h>            // MFC �׽�����չ

#define GET_CTRL(theClass, theID) (( theClass * )GetDlgItem( theID ))
#define GET_DLG_CTRL(theClass, theID) (( theClass * )dlg->GetDlgItem( theID ))
#define ENABLE_CTRL(theID, newStatus) (GetDlgItem( theID )->EnableWindow(newStatus))
#define CHECK_CTRL(theID, newStatus) (GET_CTRL(CButton, theID)->SetCheck(newStatus))
#define SET_CTRL(theClass, theID, left, top, right, bottom) GET_CTRL(theClass, theID)->SetWindowPos(NULL,left,top,(right)-(left),(bottom)-(top),SWP_NOZORDER)

#define MOVEW(x) CRect rect;GetClientRect(&rect);ClientToScreen(&rect);x.SetWindowPos(this, rect.left+100, rect.top+100, 0, 0 , SWP_NOSIZE)
#define CREATEW(x,y) x.Create(y,this);x.ShowWindow(SW_HIDE)

#define CHECK_VALID(x)				if(!(x)){return;}			
#define CHECK_VALID_RETURN(x)		if(!(x)){return 0;}
#define CHECK_VALID_CONTINUE(x)		if(!(x)){continue;}
#define CHECK_VALID_BREAK(x)		if(!(x)){break;}

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include "../General/Func.h"
#include "../General/GoodListCtrl.h"
#include "../General/Profile.h"