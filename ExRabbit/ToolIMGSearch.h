#pragma once

// CToolIMGSearch �Ի���

class CToolIMGSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CToolIMGSearch)

public:
	CToolIMGSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolIMGSearch();

// �Ի�������
	enum { IDD = IDD_TOOL_IMGSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_e1;
	CEdit m_e2;
	CGoodListCtrl m_list;
	CButton m_b2;
	CButton m_b3;
	CProgressCtrl m_p1;
	CButton m_b5;
	CButton m_b10;
	CButton m_b11;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton6();
	volatile bool stopSign;
	CButton m_b6;
};
UINT ThreadToolIMGSearchOutput(PVOID para);
UINT ThreadToolIMGSearch(PVOID para);