// TinyAddMark.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyAddMark.h"
#include "afxdialogex.h"


// TinyAddMark 对话框

IMPLEMENT_DYNAMIC(TinyAddMark, CDialogEx)

TinyAddMark::TinyAddMark(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyAddMark::IDD, pParent)
{

}

TinyAddMark::~TinyAddMark()
{
}

void TinyAddMark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyAddMark, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinyAddMark::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyAddMark 消息处理程序


void TinyAddMark::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(str);
	text = CStrToStr(str);
	CDialogEx::OnOK();
}
