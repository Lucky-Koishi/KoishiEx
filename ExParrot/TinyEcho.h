#pragma once


// TinyEcho �Ի���

class TinyEcho : public CDialogEx
{
	DECLARE_DYNAMIC(TinyEcho)

public:
	TinyEcho(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyEcho();

// �Ի�������
	enum { IDD = IDD_TINY_ECHO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	double attenu;
	int times;
	int offset;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedOk();
};
