#pragma once


// CDlgRename 对话框

class CDlgRename : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRename)

public:
	CDlgRename(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRename();

// 对话框数据
	enum { IDD = IDD_RENAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ed1;
	CEdit m_ed2;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
