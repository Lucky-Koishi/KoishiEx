#include "stdafx.h"
#pragma once


// ToolPatch �Ի���

class ToolPatch : public CDialogEx
{
	DECLARE_DYNAMIC(ToolPatch)

public:
	ToolPatch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolPatch();

// �Ի�������
	enum { IDD = IDD_TOOL_PATCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedStop();

	ProfileBlack *p;
	void getPNG();
	void getGIF();
	void transToV2();
	static unsigned go(void*context);
};
