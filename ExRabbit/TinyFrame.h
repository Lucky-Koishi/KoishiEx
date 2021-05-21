#pragma once


// TinyFrame 对话框

class TinyFrame : public CDialogEx
{
	DECLARE_DYNAMIC(TinyFrame)

public:
	TinyFrame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyFrame();

// 对话框数据
	enum { IDD = IDD_TINY_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int min, cur, max;
	int output;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
