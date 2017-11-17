#pragma once
#include "stdafx.h"

// CDlgColor 对话框

class CDlgColor : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgColor)

public:
	CDlgColor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgColor();

// 对话框数据
	enum { IDD = IDD_COLOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	bool chosenClr[256];
	lcolor *plc;
	lcolor basePlc;
	void setClr(lcolor *lclr);
	void draw();
	int ptToIndex(const CPoint &pt);
	CPoint indexToPt(int i);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	CComboBox m_c1;
	CSliderCtrl m_s1;
	CSliderCtrl m_s2;
	CSliderCtrl m_s3;
	CStatic m_st1;
	CStatic m_st3;
	CStatic m_st2;
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_e1;
	CEdit m_e2;
	CEdit m_e3;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCtAll();
	afx_msg void OnCtUnall();
	afx_msg void OnCtRev();
	afx_msg void OnCtImportAct();
	afx_msg void OnCtImportCid();
	afx_msg void OnCtExportAct();
	afx_msg void OnCtExportCid();
};
