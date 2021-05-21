// ToolAvatarIO.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarIO.h"
#include "afxdialogex.h"


// ToolAvatarIO 对话框

IMPLEMENT_DYNAMIC(ToolAvatarIO, CDialogEx)

ToolAvatarIO::ToolAvatarIO(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarIO::IDD, pParent)
{

}

ToolAvatarIO::~ToolAvatarIO()
{
}

void ToolAvatarIO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarIO, CDialogEx)
	ON_BN_CLICKED(IDOK, &ToolAvatarIO::OnBnClickedOk)
END_MESSAGE_MAP()


// ToolAvatarIO 消息处理程序


BOOL ToolAvatarIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(style == AVA_IMPORT){
		SetWindowText(L"请输入共享码喵！");
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"请在这里输入共享码。");
	}else{
		SetWindowText(L"请将文本框的内容复制给他人喵！");
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(content);
		GET_CTRL(CEdit, IDC_EDIT1)->SetReadOnly(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ToolAvatarIO::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(style == AVA_IMPORT){
		GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(content);
	}
	CDialogEx::OnOK();
}
