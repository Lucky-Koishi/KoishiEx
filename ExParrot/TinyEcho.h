#pragma once


// TinyEcho 对话框

class TinyEcho : public CDialogEx
{
	DECLARE_DYNAMIC(TinyEcho)

public:
	TinyEcho(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyEcho();

// 对话框数据
	enum { IDD = IDD_TINY_ECHO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	double attenu;
	int times;
	int offset;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedOk();
};
