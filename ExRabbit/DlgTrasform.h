#pragma once


// CDlgTrasform 对话框

class CDlgTrasform : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTrasform)

public:
	CDlgTrasform(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTrasform();

// 对话框数据
	enum { IDD = IDD_TRASFORM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ch1;
	CButton m_ch2;
	CButton m_ch3;
	CButton m_ch4;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
};
