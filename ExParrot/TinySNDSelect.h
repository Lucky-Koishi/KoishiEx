#pragma once


// TinyIMGSelect 对话框

class TinySNDSelect : public CDialogEx
{
	DECLARE_DYNAMIC(TinySNDSelect)

public:
	TinySNDSelect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinySNDSelect();

// 对话框数据
	enum { IDD = IDD_TINY_SND_SELECT };

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
