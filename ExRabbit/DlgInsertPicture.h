#pragma once


// CDlgInsertPicture 对话框

class CDlgInsertPicture : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsertPicture)

public:
	CDlgInsertPicture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInsertPicture();

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
	int iORr;
	CButton m_b1;
	CComboBox m_cb2;
	CEdit m_e14;
	CEdit m_e15;
	CEdit m_e16;
	CEdit m_e17;
	CComboBox m_cb3;
	afx_msg void OnCbnSelchangeCombo8();
};
