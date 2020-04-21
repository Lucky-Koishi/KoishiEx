// ModalCopyReplace.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalCopyReplace.h"
#include "afxdialogex.h"
#include "GoodListCtrl.h"

// ModalCopyReplace 对话框

IMPLEMENT_DYNAMIC(ModalCopyReplace, CDialogEx)

ModalCopyReplace::ModalCopyReplace(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalCopyReplace::IDD, pParent)
{

}

ModalCopyReplace::~ModalCopyReplace()
{
}

void ModalCopyReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalCopyReplace, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalCopyReplace::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalCopyReplace::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalCopyReplace::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_INPUT1, &ModalCopyReplace::OnBnClickedRadioInput1)
	ON_BN_CLICKED(IDC_RADIO_INPUT2, &ModalCopyReplace::OnBnClickedRadioInput2)
	ON_BN_CLICKED(IDOK, &ModalCopyReplace::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalCopyReplace 消息处理程序


void ModalCopyReplace::OnBnClickedRadioOperate1(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(0);
	out.operate = 1;
}


void ModalCopyReplace::OnBnClickedRadioOperate2(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(0);
	out.operate = 2;
}


void ModalCopyReplace::OnBnClickedRadioOperate3(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(1);
	out.operate = 3;
}


void ModalCopyReplace::OnBnClickedRadioInput1(){
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(0);
	out.type = 1;
}


void ModalCopyReplace::OnBnClickedRadioInput2(){
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(1);
	out.type = 2;
}


void ModalCopyReplace::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = GET_CTRL(CGoodListCtrl, IDC_LIST1)->GetSelectionMark();
	if(i == -1){
		MessageBox(L"尚未选择IMG。",L"提示");
		return;
	}
	out.selectID = i;
	CDialogEx::OnOK();
}


BOOL ModalCopyReplace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertColumn(L"请选择目标IMG,200");
	for(int i = 0;i<in.ptrNo->count;i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertItem(GetTail(StrToCStr(in.ptrNo->entry[i].comment)));
	OnBnClickedRadioOperate1();
	OnBnClickedRadioOperate2();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
