#pragma once


// TinyAddMark 对话框

class TinyAddMark : public CDialogEx
{
	DECLARE_DYNAMIC(TinyAddMark)

public:
	TinyAddMark(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyAddMark();

// 对话框数据
	enum { IDD = IDD_TINY_ADD_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

public:
	str text;
};
