#pragma once


// TinyAddMark �Ի���

class TinyAddMark : public CDialogEx
{
	DECLARE_DYNAMIC(TinyAddMark)

public:
	TinyAddMark(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyAddMark();

// �Ի�������
	enum { IDD = IDD_TINY_ADD_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

public:
	str text;
};
