#pragma once
#include "GoodListCtrl.h"

// CDlgMix 对话框

class CDlgMix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMix)

public:
	CDlgMix(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMix();

// 对话框数据
	enum { IDD = IDD_MIX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_e1;
	CGoodListCtrl m_l1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
};
