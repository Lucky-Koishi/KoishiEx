#pragma once


// CDlgSetpara 对话框

class CDlgSetpara : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetpara)

public:
	CDlgSetpara(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetpara();

// 对话框数据
	enum { IDD = IDD_SERPARA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_c1;
	CButton m_c2;
	CButton m_c3;
	CEdit m_e1;
	CEdit m_e2;
	CEdit m_e3;
	CEdit m_e4;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck4();
	CButton m_c4;
};
