
// ExKitty.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExKittyApp:
// �йش����ʵ�֣������ ExKitty.cpp
//

class CExKittyApp : public CWinApp
{
public:
	CExKittyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExKittyApp theApp;