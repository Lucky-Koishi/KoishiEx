
// ExRabbit.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExRabbitApp:
// �йش����ʵ�֣������ ExRabbit.cpp
//

class CExRabbitApp : public CWinApp
{
public:
	CExRabbitApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuImageClipboardCopy();
};

extern CExRabbitApp theApp;