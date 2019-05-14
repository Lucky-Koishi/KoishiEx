// ModalImageHide.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalImageHide.h"
#include "afxdialogex.h"


// ModalImageHide �Ի���

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


// ModalImageHide ��Ϣ�������


BOOL ModalImageHide::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(FALSE);
	out.operate = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
