#pragma once


// CDlgTrasform �Ի���

class CDlgTrasform : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTrasform)

public:
	CDlgTrasform(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTrasform();

// �Ի�������
	enum { IDD = IDD_TRASFORM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ch1;
	CButton m_ch2;
	CButton m_ch3;
	CButton m_ch4;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	CComboBox m_c1;
	CComboBox m_c2;
	CButton m_ch5;
	CEdit m_e1;
	CEdit m_e2;
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo3();
	CButton m_s1;
};
