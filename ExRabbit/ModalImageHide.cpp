// ModalImageHide.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalImageHide.h"
#include "afxdialogex.h"


// ModalImageHide 对话框

IMPLEMENT_DYNAMIC(ModalImageHide, CDialogEx)

ModalImageHide::ModalImageHide(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalImageHide::IDD, pParent){

}

ModalImageHide::~ModalImageHide(){
}

void ModalImageHide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalImageHide, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalImageHide::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalImageHide::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalImageHide::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDOK, &ModalImageHide::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalImageHide 消息处理程序


BOOL ModalImageHide::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(FALSE);
	out.operate = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ModalImageHide::OnBnClickedRadioOperate1(){
	out.operate = 1;
}


void ModalImageHide::OnBnClickedRadioOperate2(){
	out.operate = 2;
}


void ModalImageHide::OnBnClickedRadioOperate3(){
	out.operate = 3;
}


void ModalImageHide::OnBnClickedOk(){
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
