#pragma once


// CDlgInsert4 对话框

class CDlgInsert4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsert4)

public:
	CDlgInsert4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInsert4();

// 对话框数据
	enum { IDD = IDD_INSERT4_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	void draw();
	enum{__INSERT, __REPLACE};
	int iORr;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool getting;
};
