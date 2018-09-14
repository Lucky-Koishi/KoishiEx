
// ExKittyDlg.h : 头文件
//
#include "../KoishiEx/koishiex.h"
#pragma once


// CExKittyDlg 对话框
class CExKittyDlg : public CDialogEx
{
// 构造
public:
	CExKittyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXKITTY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	bool avatarEnableDisplay[10];
	CBitmap avatarIconEnable[10];
	CBitmap avatarIconDisable[10];

public:
	Koishi::NPKobject no;
	Koishi::IMGobject io;
public:
	void Initial();
	void DrawUI();
	void DrawIconButton();
	void DrawPalette();
	afx_msg void OnBnClickedButtonMenu1();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnBnClickedButtonMenu4();
	afx_msg void OnBnClickedButtonMenu5();
};
