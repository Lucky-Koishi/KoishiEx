// ModalImageRemove.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalImageRemove.h"
#include "afxdialogex.h"


// ModalImageRemove �Ի���

IMPLEMENT_DYNAMIC(ModalImageRemove, CDialogEx)

ModalImageRemove::ModalImageRemove(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalImageRemove::IDD, pParent)
{

}

ModalImageRemove::~ModalImageRemove()
{
}

void ModalImageRemove::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalImageRemove, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalImageRemove::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalImageRemove::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalImageRemove::OnBnClickedRadioOperate3)
END_MESSAGE_MAP()


// ModalImageRemove ��Ϣ�������


void ModalImageRemove::OnBnClickedRadioOperate1(){
	out.operate = 1;
}


void ModalImageRemove::OnBnClickedRadioOperate2(){
	out.operate = 2;
}


void ModalImageRemove::OnBnClickedRadioOperate3(){
	out.operate = 3;
}


BOOL ModalImageRemove::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(FALSE);
	out.operate = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
