// ModalRename.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ModalRename(white).h"
#include "afxdialogex.h"


// ModalRename 对话框

IMPLEMENT_DYNAMIC(ModalRename, CDialogEx)

ModalRename::ModalRename(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalRename::IDD, pParent)
{

}

ModalRename::~ModalRename()
{
}

void ModalRename::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalRename, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModalRename::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalRename 消息处理程序

BOOL ModalRename::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(oldName);
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(oldName);
	newName = oldName;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ModalRename::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(newName);
	CDialogEx::OnOK();
}
