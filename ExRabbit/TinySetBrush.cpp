// TinySetBrush.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinySetBrush.h"
#include "afxdialogex.h"


// TinySetBrush 对话框

IMPLEMENT_DYNAMIC(TinySetBrush, CDialogEx)

TinySetBrush::TinySetBrush(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinySetBrush::IDD, pParent)
{

}

TinySetBrush::~TinySetBrush()
{
}

void TinySetBrush::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinySetBrush, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &TinySetBrush::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &TinySetBrush::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &TinySetBrush::OnBnClickedOk)
END_MESSAGE_MAP()


// TinySetBrush 消息处理程序


BOOL TinySetBrush::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(shape == 1){
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(TRUE);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(FALSE);
	}
	if(shape == 2){
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(FALSE);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(TRUE);
	}
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(NumToCStr(size));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void TinySetBrush::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(FALSE);
}


void TinySetBrush::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(TRUE);
}


void TinySetBrush::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(GET_CTRL(CButton, IDC_CHECK1)->GetCheck() == TRUE){
		shape = 1;
	}else{
		shape = 2;
	}
	CString s;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(s);
	if(_ttoi(s)<=0 || _ttoi(s)>10){
		MessageBox(L"请输入1-10之间的整数喵！");
		return;
	}
	size = _ttoi(s);
	CDialogEx::OnOK();
}
