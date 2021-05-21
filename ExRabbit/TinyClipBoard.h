#pragma once


// TinyClipBoard 对话框

class TinyClipBoard : public CDialogEx
{
	DECLARE_DYNAMIC(TinyClipBoard)

public:
	TinyClipBoard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyClipBoard();

// 对话框数据
	enum { IDD = IDD_TINY_CLIPBOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonRemoveall();

public:
	NPKobject *ptrClipNo;
	int selectID;
	afx_msg void OnBnClickedOk();
};
