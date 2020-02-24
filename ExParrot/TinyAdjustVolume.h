#pragma once


// TinyAdjustVolume 对话框

class TinyAdjustVolume : public CDialogEx
{
	DECLARE_DYNAMIC(TinyAdjustVolume)

public:
	TinyAdjustVolume(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyAdjustVolume();

// 对话框数据
	enum { IDD = IDD_TINY_ADJUST_VOLUME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();

public:
	int maxEnergy;		//输入量
	double rate;		//输出比值
	virtual BOOL OnInitDialog();
};
