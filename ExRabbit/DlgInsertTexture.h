#pragma once


// CDlgInsertTexture �Ի���

class CDlgInsertTexture : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsertTexture)

public:
	CDlgInsertTexture(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInsertTexture();

// �Ի�������
	enum { IDD = IDD_INSERT3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_c1;
	CButton m_c2;
	CButton m_c3;
	CComboBox m_cb1;
	CEdit m_ed1;
	enum{__INSERT, __REPLACE};
	int iORr;
	IMGversion ver;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CComboBox m_cb2;
};
