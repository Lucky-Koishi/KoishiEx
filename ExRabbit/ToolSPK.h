#pragma once
#include "GoodListCtrl.h"

// CToolSPK 对话框
using namespace KoishiExpand::KoishiDownloadTool;

class CToolSPK : public CDialogEx
{
	DECLARE_DYNAMIC(CToolSPK)

public:
	CToolSPK(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CToolSPK();

// 对话框数据
	enum { IDD = IDD_TOOL_SPK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int serverChoose;
	CComboBox m_cRec;
	CGoodListCtrl m_lSPK;
	CEdit m_eURL;
	CEdit m_eDownloadSPK;
	CEdit m_eSPK;
	CEdit m_eConvertToNPK;
	CString URLaddr;
	CString localAddr;
	CString localAddrFileName;
	void loadPackage();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedCancel();

	static UINT threadDownloadPackageList(PVOID para);
	static UINT threadDownloadSPK(PVOID para);

	static INT GetInternetFile(const CString strUrl,const CString strSavePath);
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton22();
	CEdit m_eKeyWord;

	str stringInfo[7];
};
