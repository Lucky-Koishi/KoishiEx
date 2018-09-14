#pragma once


// CDialogAbout 对话框

class CDialogAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAbout)

public:
	CDialogAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogAbout();

// 对话框数据
	enum { IDD = IDD_ABOUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_QR;

public:
	CBitmap m_QRbmp;
	afx_msg void OnBnClickedOk();
};
