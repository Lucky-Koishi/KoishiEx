#pragma once


// TinyIMGSelect �Ի���

class TinyIMGSelect : public CDialogEx
{
	DECLARE_DYNAMIC(TinyIMGSelect)

public:
	TinyIMGSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyIMGSelect();

// �Ի�������
	enum { IDD = IDD_TINY_IMG_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	std::vector<str> listStr;
	int defaultSelected;
	int selected;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
