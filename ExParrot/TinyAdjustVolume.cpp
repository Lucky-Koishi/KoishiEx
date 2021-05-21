// TinyAdjustVolume.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyAdjustVolume.h"
#include "afxdialogex.h"


// TinyAdjustVolume 对话框

IMPLEMENT_DYNAMIC(TinyAdjustVolume, CDialogEx)

TinyAdjustVolume::TinyAdjustVolume(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyAdjustVolume::IDD, pParent)
{

}

TinyAdjustVolume::~TinyAdjustVolume()
{
}

void TinyAdjustVolume::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyAdjustVolume, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &TinyAdjustVolume::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &TinyAdjustVolume::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyAdjustVolume 消息处理程序


void TinyAdjustVolume::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString val;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(val);
	rate = _ttof(val);
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(maxEnergy/32768.f));
	double modifyEnergy = abs(rate)*maxEnergy;
	if(modifyEnergy >= 32768){
		modifyEnergy = 32768;
		GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(L"出现溢出！");
	}else{
		GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(L"没有溢出");
	}
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(modifyEnergy/32768.f));
	// TODO:  在此添加控件通知处理程序代码
}


void TinyAdjustVolume::OnBnClickedOk(){
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL TinyAdjustVolume::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"1.00");
	rate = 1.f;
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(maxEnergy/32768.f));
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(maxEnergy/32768.f));
	GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(L"没有溢出");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
