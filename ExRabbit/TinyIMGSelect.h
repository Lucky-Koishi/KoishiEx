#pragma once


// TinyIMGSelect 对话框

class TinyIMGSelect : public CDialogEx
{
	DECLARE_DYNAMIC(TinyIMGSelect)

public:
	TinyIMGSelect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyIMGSelect();

// 对话框数据
	enum { IDD = IDD_TINY_IMG_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	std::vector<str> listStr;
	int defaultSelected;
	int selected;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
