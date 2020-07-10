// TinyFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyFrame.h"
#include "afxdialogex.h"


// TinyFrame 对话框

IMPLEMENT_DYNAMIC(TinyFrame, CDialogEx)

TinyFrame::TinyFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyFrame::IDD, pParent)
{

}

TinyFrame::~TinyFrame()
{
}

void TinyFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyFrame, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinyFrame::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyFrame 消息处理程序


BOOL TinyFrame::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"范围:" + NumToCStr(min) + L"-" + NumToCStr(max));
	GetDlgItem(IDC_EDIT2)->SetWindowText(NumToCStr(cur));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void TinyFrame::OnBnClickedOk() {
	// TODO:  在此添加控件通知处理程序代码
	CString ss;
	GetDlgItem(IDC_EDIT2)->GetWindowText(ss);
	output = _ttoi(ss);
	if(output < min || output > max) {
		MessageBox(L"请输入范围以内的帧号喵！", L"提示");
		return;
	}
	CDialogEx::OnOK();
}
