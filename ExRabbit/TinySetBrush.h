#pragma once


// TinySetBrush 对话框

class TinySetBrush : public CDialogEx
{
	DECLARE_DYNAMIC(TinySetBrush)

public:
	TinySetBrush(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinySetBrush();

// 对话框数据
	enum { IDD = IDD_TINY_SET_BRUSH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedOk();

	int shape;
	int size;
};
