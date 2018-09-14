#pragma once
#include "stdafx.h"

// CDlgColor �Ի���

class CDlgColor : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgColor)

public:
	CDlgColor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgColor();

// �Ի�������
	enum { IDD = IDD_COLOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	afx_msg void OnNMreleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMreleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMreleasedcaptureSlider3(NMHDR *pNMHDR, LRESULT *pResult);
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
