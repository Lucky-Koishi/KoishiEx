#pragma once


// TinySetName �Ի���

class TinySetName : public CDialogEx
{
	DECLARE_DYNAMIC(TinySetName)

public:
	TinySetName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinySetName();

// �Ի�������
	enum { IDD = IDD_TINY_SET_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CString name;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
