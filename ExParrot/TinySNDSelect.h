#pragma once


// TinyIMGSelect �Ի���

class TinySNDSelect : public CDialogEx
{
	DECLARE_DYNAMIC(TinySNDSelect)

public:
	TinySNDSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinySNDSelect();

// �Ի�������
	enum { IDD = IDD_TINY_SND_SELECT };

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
