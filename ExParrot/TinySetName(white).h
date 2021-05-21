#pragma once


// TinySetName 对话框

class TinySetName : public CDialogEx
{
	DECLARE_DYNAMIC(TinySetName)

public:
	TinySetName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinySetName();

// 对话框数据
	enum { IDD = IDD_TINY_SET_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CString name;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
