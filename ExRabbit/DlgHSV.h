#pragma once


// CDlgHSV 对话框

class CDlgHSV : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHSV)

public:
	CDlgHSV(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHSV();

// 对话框数据
	enum { IDD = IDD_HSV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chHSV;
	CButton m_chRGB;
	CEdit m_e1;
	CEdit m_e2;
	CEdit m_e3;
	CListBox m_list;
	CSliderCtrl m_s1;
	CSliderCtrl m_s2;
	CSliderCtrl m_s3;
	lcolor oldClrList;
	lcolor midClrList;
	lcolor newClrList;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeList1();
	void draw();
	int firstpos;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
};
