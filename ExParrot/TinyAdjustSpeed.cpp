// TinyAdjustSpeed.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyAdjustSpeed.h"
#include "afxdialogex.h"


// TinyAdjustSpeed 对话框

IMPLEMENT_DYNAMIC(TinyAdjustSpeed, CDialogEx)

TinyAdjustSpeed::TinyAdjustSpeed(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyAdjustSpeed::IDD, pParent)
{

}

TinyAdjustSpeed::~TinyAdjustSpeed()
{
}

void TinyAdjustSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyAdjustSpeed, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinyAdjustSpeed::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TinyAdjustSpeed::OnBnClickedCancel)
END_MESSAGE_MAP()


// TinyAdjustSpeed 消息处理程序


BOOL TinyAdjustSpeed::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(type ? L"调节音调" : L"调节速度");
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"1.00");
	rate = 1.f;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void TinyAdjustSpeed::OnBnClickedOk() {
	// TODO:  在此添加控件通知处理程序代码
	CString ss;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(ss);
	rate = _ttof(ss);
	if(rate < 0.5) {
		MessageBox(L"输入数字必须要大于等于0.5！", L"提示喵");
		return;
	}
	CDialogEx::OnOK();
}


void TinyAdjustSpeed::OnBnClickedCancel() {
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
