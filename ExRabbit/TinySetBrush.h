#pragma once


// TinySetBrush �Ի���

class TinySetBrush : public CDialogEx
{
	DECLARE_DYNAMIC(TinySetBrush)

public:
	TinySetBrush(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinySetBrush();

// �Ի�������
	enum { IDD = IDD_TINY_SET_BRUSH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedOk();

	int shape;
	int size;
};
