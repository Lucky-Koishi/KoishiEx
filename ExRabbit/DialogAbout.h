#pragma once


// CDialogAbout �Ի���

class CDialogAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAbout)

public:
	CDialogAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogAbout();

// �Ի�������
	enum { IDD = IDD_ABOUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_QR;

public:
	CBitmap m_QRbmp;
	afx_msg void OnBnClickedOk();
};
