#pragma once


// CDlgInsertIMG �Ի���

class CDlgInsertIMG : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsertIMG)

public:
	CDlgInsertIMG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInsertIMG();

// �Ի�������
	enum { IDD = IDD_INSERT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_btn1;
	CButton m_btn7;
	CButton m_ch1;
	CButton m_ch2;
	CButton m_ch3;
	CComboBox m_c1;
	CComboBox m_c3;
	CComboBox m_c4;
	CEdit m_e1;
	CEdit m_e2;
	CEdit m_e3;
	CEdit m_e6;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton7();
};
