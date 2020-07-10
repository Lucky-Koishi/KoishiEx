
// ExToolDlg.h : 头文件
//

#pragma once
#include <string>
#include "../KoishiEx//KoishiAudioTool.h"

// CExToolDlg 对话框
class CExToolDlg : public CDialogEx
{
// 构造
public:
	CExToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXTOOL_DIALOG };

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

protected:
	void fun();
	static unsigned funThread(void*p){
		((CExToolDlg*)p)->fun();
		return 0U;
	}
public:
	afx_msg void OnBnClickedOk(){
		AfxBeginThread(funThread, this);
	}
	void setPos1(int pos){
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetPos(pos);
	}
	void setPos2(int pos){
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS2))->SetPos(pos);
	}
	void printf(const CString &ss){
		GetDlgItem(IDC_EDIT1)->SetWindowText(ss);
	}
	CString CStr(int n){
		CString nstr;
		nstr.Format(L"%d",n);
		return nstr;
	}
	CString CStr(std::string n){
		return CString(n.c_str());
	}
	afx_msg void OnBnClickedButton1();

public:
	static void fun20(void*para) {
		((CExToolDlg*)para)->fun2();
	}
	static void fun30(void*para) {
		((CExToolDlg*)para)->fun3();
	}
	//NPK分析工具
	//按版本号统计NPK下所包含的IMG的个数（并举例）
	//针对不同版本统计帧PIC格式（即前两个双字）的个数（并举例）
	void fun2();	//NPK分析工具 
	//装扮统计工具
	//以装扮名称格式解析，并按职业区分装扮包含的各图层（并举例）
	void fun3();
	afx_msg void OnBnClickedButton2();
};
