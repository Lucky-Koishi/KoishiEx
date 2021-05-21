// ModalClearPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalClearPicture.h"
#include "afxdialogex.h"


// ModalClearPicture 对话框

IMPLEMENT_DYNAMIC(ModalClearPicture, CDialogEx)

ModalClearPicture::ModalClearPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalClearPicture::IDD, pParent)
{

}

ModalClearPicture::~ModalClearPicture()
{
}

void ModalClearPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalClearPicture, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalClearPicture::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalClearPicture::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalClearPicture::OnBnClickedRadioTarget3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalClearPicture::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalClearPicture::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDOK, &ModalClearPicture::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalClearPicture 消息处理程序


void ModalClearPicture::OnBnClickedRadioTarget1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 1;
}


void ModalClearPicture::OnBnClickedRadioTarget2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 2;
}


void ModalClearPicture::OnBnClickedRadioTarget3()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 3;
}


void ModalClearPicture::OnBnClickedRadioOperate1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 1;
}


void ModalClearPicture::OnBnClickedRadioOperate2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 2;
}

BOOL ModalClearPicture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	out.target = 1;
	out.operate = 1;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ModalClearPicture::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
