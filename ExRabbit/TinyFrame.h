#pragma once


// TinyFrame �Ի���

class TinyFrame : public CDialogEx
{
	DECLARE_DYNAMIC(TinyFrame)

public:
	TinyFrame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyFrame();

// �Ի�������
	enum { IDD = IDD_TINY_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	int min, cur, max;
	int output;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
