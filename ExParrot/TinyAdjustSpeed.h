#pragma once


// TinyAdjustSpeed 对话框

class TinyAdjustSpeed : public CDialogEx
{
	DECLARE_DYNAMIC(TinyAdjustSpeed)

public:
	TinyAdjustSpeed(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyAdjustSpeed();

// 对话框数据
	enum { IDD = IDD_TINY_ADJUST_SPEED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	enum {
		ADJUST_SPEED, ADJUST_PITCH
	};
	int type;
	double rate;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
