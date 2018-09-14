#pragma once


// DlgLoseBlack 对话框

class CDlgLoseBlack : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLoseBlack)

public:
	CDlgLoseBlack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLoseBlack();

// 对话框数据
	enum { IDD = IDD_LOSEBLACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_eGamma;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
