// TinyEcho.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyEcho.h"
#include "afxdialogex.h"


// TinyEcho 对话框

IMPLEMENT_DYNAMIC(TinyEcho, CDialogEx)

TinyEcho::TinyEcho(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyEcho::IDD, pParent)
{

}

TinyEcho::~TinyEcho()
{
}

void TinyEcho::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyEcho, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &TinyEcho::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &TinyEcho::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &TinyEcho::OnEnChangeEdit3)
	ON_BN_CLICKED(IDOK, &TinyEcho::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyEcho 消息处理程序


BOOL TinyEcho::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowTextW(L"5");
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowTextW(L"500");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowTextW(L"0.8");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void TinyEcho::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString val;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowTextW(val);
	times = abs(_ttoi(val));
	// TODO:  在此添加控件通知处理程序代码
}


void TinyEcho::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString val;
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowTextW(val);
	offset = abs(_ttoi(val));
	// TODO:  在此添加控件通知处理程序代码
}


void TinyEcho::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString val;
	GET_CTRL(CEdit, IDC_EDIT3)->GetWindowTextW(val);
	attenu = abs(_ttof(val));
	// TODO:  在此添加控件通知处理程序代码
}


void TinyEcho::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
