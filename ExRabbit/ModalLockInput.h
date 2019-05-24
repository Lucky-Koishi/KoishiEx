#pragma once


// ModalLockInput 对话框

class ModalLockInput : public CDialogEx
{
	DECLARE_DYNAMIC(ModalLockInput)

public:
	ModalLockInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalLockInput();

// 对话框数据
	enum { IDD = IDD_MODAL_LOCK_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString fileCheckName;
	int restTime;
	afx_msg void OnBnClickedOk();
};
