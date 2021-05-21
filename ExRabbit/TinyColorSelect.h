#pragma once


// TinyColorSelect 对话框

class TinyColorSelect : public CDialogEx
{
	DECLARE_DYNAMIC(TinyColorSelect)

public:
	TinyColorSelect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyColorSelect();

// 对话框数据
	enum { IDD = IDD_TINY_COLOR_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	colorList in;	//颜色
	int selection;	//选择的
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
