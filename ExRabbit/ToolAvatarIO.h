#pragma once


// ToolAvatarIO �Ի���

class ToolAvatarIO : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarIO)

public:
	ToolAvatarIO(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarIO();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	enum{AVA_IMPORT, AVA_EXPORT} style;
	CString content;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
