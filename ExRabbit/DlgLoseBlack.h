#pragma once


// DlgLoseBlack �Ի���

class CDlgLoseBlack : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLoseBlack)

public:
	CDlgLoseBlack(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLoseBlack();

// �Ի�������
	enum { IDD = IDD_LOSEBLACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_eGamma;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
