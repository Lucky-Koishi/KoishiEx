#pragma once


// ModalLock 对话框

class ModalLock : public CDialogEx
{
	DECLARE_DYNAMIC(ModalLock)

public:
	ModalLock(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalLock();

// 对话框数据
	enum { IDD = IDD_MODAL_LOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnToolsNPKLock();
};
