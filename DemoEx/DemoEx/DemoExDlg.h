#include "stdafx.h"
#include "../../KoishiEx/koishiex.h"
#include "GoodListCtrl.h"
#include "ScanDialog.h"
#include "renamedialog.h"
using namespace Koishi;
// DemoExDlg.h : 头文件
//

#pragma once


// CDemoExDlg 对话框
class CDemoExDlg : public CDialogEx
{
// 构造
public:
	CDemoExDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DEMOEX_DIALOG };

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
	
public:
	CEdit m_e1;
	CEdit m_e2;
	CEdit m_e3;
	CGoodListCtrl m_l1;
	CGoodListCtrl m_l2;
	CScanDialog csd;
	renamedialog rd;
	afx_msg void OnBnClickedCancel13();
	afx_msg void OnBnClickedCancel8();
	afx_msg void OnBnClickedCancel7();
	afx_msg void OnBnClickedCancel4();
	afx_msg void OnBnClickedCancel5();
	afx_msg void OnBnClickedCancel6();
	afx_msg void OnBnClickedCancel3();
	afx_msg void OnBnClickedCancel14();
	afx_msg void OnBnClickedCancel15();
	afx_msg void OnBnClickedCancel16();
	afx_msg void OnBnClickedCancel12();
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnBnClickedCancel9();
	afx_msg void OnBnClickedCancel10();
	afx_msg void OnBnClickedCancel11();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);

	void update1();
	void update2();
	void update3();
public:
	void draw();
	point base;
	NPKobject no;
	IMGobject io;
	matrix mat;
	CEdit m_e4;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};
