#pragma once


// TinyStretch 对话框

class TinyStretch : public CDialogEx
{
	DECLARE_DYNAMIC(TinyStretch)

public:
	TinyStretch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyStretch();

// 对话框数据
	enum { IDD = IDD_TINY_STRETCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
public:
	int sampleRate;
	longex originLen;		//输入量
	double rate;		//输出比值
};
