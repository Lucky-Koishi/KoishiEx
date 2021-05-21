#pragma once


// ToolAvatarIO 对话框

class ToolAvatarIO : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarIO)

public:
	ToolAvatarIO(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatarIO();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	enum{AVA_IMPORT, AVA_EXPORT} style;
	CString content;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
