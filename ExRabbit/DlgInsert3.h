#pragma once


// CDlgInsert3 对话框

class CDlgInsert3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsert3)

public:
	CDlgInsert3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInsert3();

// 对话框数据
	enum { IDD = IDD_INSERT3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_c1;
	CButton m_c2;
	CButton m_c3;
	CComboBox m_cb1;
	CEdit m_ed1;
	enum{__INSERT, __REPLACE};
	int iORr;
	int mode;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
