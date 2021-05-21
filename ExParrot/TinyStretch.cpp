// TinyStretch.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyStretch.h"
#include "afxdialogex.h"


// TinyStretch 对话框

IMPLEMENT_DYNAMIC(TinyStretch, CDialogEx)

TinyStretch::TinyStretch(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyStretch::IDD, pParent)
{

}

TinyStretch::~TinyStretch()
{
}

void TinyStretch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyStretch, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &TinyStretch::OnEnChangeEdit1)
END_MESSAGE_MAP()


// TinyStretch 消息处理程序


void TinyStretch::OnEnChangeEdit1(){
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString val;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(val);
	rate =  abs(_ttof(val));
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(1000.f * originLen / sampleRate));
	double modifyLen = rate * originLen;
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(1000.f * modifyLen / sampleRate));
	// TODO:  在此添加控件通知处理程序代码
}


BOOL TinyStretch::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"1.00");
	rate = 1.f;
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(1000.f * originLen / sampleRate));
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(1000.f * originLen / sampleRate));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
