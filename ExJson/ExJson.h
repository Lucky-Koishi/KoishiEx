
// ExJson.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExJsonApp:
// �йش����ʵ�֣������ ExJson.cpp
//

class CExJsonApp : public CWinApp
{
public:
	CExJsonApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExJsonApp theApp;