// ModalLoseBlackPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalLoseBlackPicture.h"
#include "afxdialogex.h"


// ModalLoseBlackPicture 对话框

IMPLEMENT_DYNAMIC(ModalLoseBlackPicture, CDialogEx)

ModalLoseBlackPicture::ModalLoseBlackPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalLoseBlackPicture::IDD, pParent)
{

}

ModalLoseBlackPicture::~ModalLoseBlackPicture()
{
}

void ModalLoseBlackPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalLoseBlackPicture, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalLoseBlackPicture::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalLoseBlackPicture::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalLoseBlackPicture::OnBnClickedRadioTarget3)
	ON_BN_CLICKED(IDOK, &ModalLoseBlackPicture::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalLoseBlackPicture 消息处理程序


void ModalLoseBlackPicture::OnBnClickedRadioTarget1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 1;
}


void ModalLoseBlackPicture::OnBnClickedRadioTarget2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 2;
}


void ModalLoseBlackPicture::OnBnClickedRadioTarget3()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 3;
}


BOOL ModalLoseBlackPicture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	out.target = 1;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	if(in.version == V4 || in.version == V6){
		out.target = 3;
		GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(1);
		GET_CTRL(CButton, IDC_RADIO_TARGET1)->EnableWindow(0);
		GET_CTRL(CButton, IDC_RADIO_TARGET2)->EnableWindow(0);
	}
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"3");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ModalLoseBlackPicture::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString numStr;
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->GetWindowText(numStr);
	out.gamma = _ttoi(numStr);
	CDialogEx::OnOK();
}
