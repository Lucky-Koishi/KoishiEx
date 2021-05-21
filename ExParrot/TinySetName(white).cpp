// TinySetName.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinySetName(white).h"
#include "afxdialogex.h"


// TinySetName 对话框

IMPLEMENT_DYNAMIC(TinySetName, CDialogEx)

TinySetName::TinySetName(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinySetName::IDD, pParent)
{

}

TinySetName::~TinySetName()
{
}

void TinySetName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinySetName, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinySetName::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TinySetName::OnBnClickedCancel)
END_MESSAGE_MAP()


// TinySetName 消息处理程序


BOOL TinySetName::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(name);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void TinySetName::OnBnClickedOk() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(name);
	CDialogEx::OnOK();
}


void TinySetName::OnBnClickedCancel() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(name);
	CDialogEx::OnCancel();
}
