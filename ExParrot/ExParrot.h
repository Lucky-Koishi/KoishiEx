
// ExParrot.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExParrotApp:
// �йش����ʵ�֣������ ExParrot.cpp
//

class CExParrotApp : public CWinApp
{
public:
	CExParrotApp();

// ��д
public:
	virtual BOOL InitInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExParrotApp theApp;