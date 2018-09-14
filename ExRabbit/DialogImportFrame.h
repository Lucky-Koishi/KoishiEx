#pragma once


// CDialogImportFrame 对话框

class CDialogImportFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImportFrame)

public:
	CDialogImportFrame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogImportFrame();

// 对话框数据
	enum { IDD = IDD_IMPORT_PNG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_c1;
	CComboBox m_c3;
	CEdit m_e1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
