#pragma once


// ModalRename 对话框

class ModalRename : public CDialogEx
{
	DECLARE_DYNAMIC(ModalRename)

public:
	ModalRename(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalRename();

// 对话框数据
	enum { IDD = IDD_MODAL_SOUND_RENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString oldName;
	CString newName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
