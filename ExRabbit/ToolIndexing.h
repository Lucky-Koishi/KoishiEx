#pragma once


// CToolIndexing �Ի���

class CToolIndexing : public CDialogEx
{
	DECLARE_DYNAMIC(CToolIndexing)

public:
	CToolIndexing(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolIndexing();

// �Ի�������
	enum { IDD = IDD_TOOL_INDEXING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_c1;
	CButton m_c2;
	CEdit m_e1;
	CEdit m_e2;
	CProgressCtrl m_p;
	CString fileName;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	static UINT PH(PVOID para);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCancel();
};
