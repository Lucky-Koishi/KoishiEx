#pragma once


// TinyClipBoard �Ի���

class TinyClipBoard : public CDialogEx
{
	DECLARE_DYNAMIC(TinyClipBoard)

public:
	TinyClipBoard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyClipBoard();

// �Ի�������
	enum { IDD = IDD_TINY_CLIPBOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonRemoveall();

public:
	NPKobject *ptrClipNo;
	int selectID;
	afx_msg void OnBnClickedOk();
};
