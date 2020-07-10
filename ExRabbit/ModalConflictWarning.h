#pragma once


// ModalConflictWarning 对话框

class ModalConflictWarning : public CDialogEx
{
	DECLARE_DYNAMIC(ModalConflictWarning)

public:
	ModalConflictWarning(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalConflictWarning();

// 对话框数据
	enum { IDD = IDD_MODAL_CONFLICT_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString conflictName;
	int method;
	BOOL noAlarm;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedIgnore();
	afx_msg void OnBnClickedRemain();
	afx_msg void OnBnClickedRename();
};
