#pragma once

// ModalPreference2 对话框

class ModalPreference2 : public CDialogEx
{
	DECLARE_DYNAMIC(ModalPreference2)

public:
	ModalPreference2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalPreference2();

// 对话框数据
	enum { IDD = IDD_MODAL_PREFERENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPreference1();
	afx_msg void OnBnClickedButtonPreference2();
	afx_msg void OnBnClickedButtonPreference3();
	afx_msg void OnBnClickedButtonPreference4();
	afx_msg void OnBnClickedButtonPreference5();
	afx_msg void OnBnClickedButtonPreference6();
	afx_msg void OnBnClickedButtonPreference7();
	afx_msg void OnBnClickedButtonPreference8();
	afx_msg void OnBnClickedButtonPreference9();
	afx_msg void OnBnClickedButtonSetpic1();
	afx_msg void OnBnClickedButtonSetpic2();
	afx_msg void OnBnClickedOk();
	Profile modifiedProfile;
	afx_msg void OnBnClickedButtonPreference10();
	afx_msg void OnBnClickedButtonPreference11();
	virtual BOOL OnInitDialog();
};
