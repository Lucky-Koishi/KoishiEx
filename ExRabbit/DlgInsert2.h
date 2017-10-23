#pragma once


// CDlgInsert2 对话框

class CDlgInsert2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsert2)

public:
	CDlgInsert2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInsert2();

// 对话框数据
	enum { IDD = IDD_INSERT2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	CButton m_ch1;
	CButton m_ch2;
	CButton m_ch3;
	CComboBox m_cb1;
	CEdit m_ed1;
	CEdit m_ed2;
	CEdit m_ed4;
	CEdit m_ed5;
	CEdit m_ed6;
	CEdit m_ed7;
	CEdit m_ed8;
	CEdit m_ed9;
	CEdit m_ed10;
	CEdit m_ed11;
	CEdit m_ed12;
	enum{__INSERT, __REPLACE};
	IMGversion ver;
	int mode;
	int iORr;
	CButton m_b1;
};
