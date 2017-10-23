#pragma once


// CDialogNew 对话框

class CDialogNew : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogNew)

public:
	CDialogNew(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNew();

// 对话框数据
	enum { IDD = IDD_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ch1;
	CButton m_ch2;
	CButton m_ch3;
	CButton m_ch4;
	CButton m_ch5;
	CButton m_ch6;
	CEdit m_ed1;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
