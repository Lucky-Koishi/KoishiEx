#pragma once


// CToolAvatarES 对话框

class CToolAvatarES : public CDialogEx
{
	DECLARE_DYNAMIC(CToolAvatarES)

public:
	CToolAvatarES(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CToolAvatarES();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_ES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString partID[10];
	int type;
	afx_msg void OnBnClickedOk();
};
