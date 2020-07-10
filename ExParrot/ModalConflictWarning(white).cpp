// ModalConflictWarning.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ModalConflictWarning(white).h"
#include "afxdialogex.h"


// ModalConflictWarning 对话框

IMPLEMENT_DYNAMIC(ModalConflictWarning, CDialogEx)

ModalConflictWarning::ModalConflictWarning(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalConflictWarning::IDD, pParent)
{

}

ModalConflictWarning::~ModalConflictWarning()
{
}

void ModalConflictWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalConflictWarning, CDialogEx)
	ON_BN_CLICKED(ID_REPLACE, &ModalConflictWarning::OnBnClickedReplace)
	ON_BN_CLICKED(ID_IGNORE, &ModalConflictWarning::OnBnClickedIgnore)
	ON_BN_CLICKED(ID_REMAIN, &ModalConflictWarning::OnBnClickedRemain)
	ON_BN_CLICKED(ID_RENAME, &ModalConflictWarning::OnBnClickedRename)
END_MESSAGE_MAP()


// ModalConflictWarning 消息处理程序


BOOL ModalConflictWarning::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CStatic, IDC_STATIC1)->SetWindowText(
		L"发现此对象与现有NPK中某对象的路径名相同：\r\n" +
		conflictName + 
		L"要怎么办喵？"
		);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ModalConflictWarning::OnBnClickedReplace() {
	// TODO:  在此添加控件通知处理程序代码
	method = 0;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}


void ModalConflictWarning::OnBnClickedIgnore() {
	// TODO:  在此添加控件通知处理程序代码
	method = 1;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}


void ModalConflictWarning::OnBnClickedRemain() {
	// TODO:  在此添加控件通知处理程序代码
	method = 2;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}


void ModalConflictWarning::OnBnClickedRename() {
	// TODO:  在此添加控件通知处理程序代码
	method = 3;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}
