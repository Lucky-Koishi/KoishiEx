#pragma once

// CToolDict 对话框

class CToolDict : public CDialogEx
{
	DECLARE_DYNAMIC(CToolDict)

public:
	CToolDict(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CToolDict();

// 对话框数据
	enum { IDD = IDD_TOOL_DICT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_e1;
	CEdit m_e2;
	CGoodListCtrl m_l1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	CProgressCtrl m_p1;
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CEdit m_e3;
	CString contentDir;
	CString resourceDir;
	afx_msg void OnBnClickedButton17();
};

UINT ThreadToolDictLoadDict(PVOID para);
UINT ThreadToolDictSearchDict(PVOID para);