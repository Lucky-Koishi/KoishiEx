#pragma once


// CToolForceEx �Ի���

class CToolForceEx : public CDialogEx
{
	DECLARE_DYNAMIC(CToolForceEx)

public:
	CToolForceEx(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolForceEx();

// �Ի�������
	enum { IDD = IDD_TOOL_FORCEEXTRACT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_eNPK;
	CEdit m_eOK;
	CEdit m_eProc;
	CProgressCtrl m_pProc;
	CString fileName;
	static UINT extractIMGthread(PVOID para);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
};
