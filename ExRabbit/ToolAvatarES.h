#pragma once


// CToolAvatarES �Ի���

class CToolAvatarES : public CDialogEx
{
	DECLARE_DYNAMIC(CToolAvatarES)

public:
	CToolAvatarES(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolAvatarES();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_ES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString partID[10];
	int type;
	afx_msg void OnBnClickedOk();
};
