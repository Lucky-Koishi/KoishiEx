#pragma once


// CDlgSetXY 对话框

class CDlgSetXY : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetXY)

public:
	CDlgSetXY(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetXY();

// 对话框数据
	enum { IDD = IDD_SERXY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedCancel();
	CEdit m_e1;
};
