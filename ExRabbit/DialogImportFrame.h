#pragma once


// CDialogImportFrame �Ի���

class CDialogImportFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImportFrame)

public:
	CDialogImportFrame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogImportFrame();

// �Ի�������
	enum { IDD = IDD_IMPORT_PNG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_c1;
	CComboBox m_c3;
	CEdit m_e1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
