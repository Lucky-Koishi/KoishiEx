#pragma once


// CDlgCanvas 对话框

class CDlgCanvas : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCanvas)

public:
	CDlgCanvas(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCanvas();

// 对话框数据
	enum { IDD = IDD_CANVAS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
