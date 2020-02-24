// ModalSoundHide.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ModalSoundHide.h"
#include "afxdialogex.h"


// ModalSoundHide �Ի���

IMPLEMENT_DYNAMIC(ModalSoundHide, CDialogEx)

ModalSoundHide::ModalSoundHide(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalSoundHide::IDD, pParent)
{

}

ModalSoundHide::~ModalSoundHide()
{
}

void ModalSoundHide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalSoundHide, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalSoundHide::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalSoundHide::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalSoundHide::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDOK, &ModalSoundHide::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalSoundHide ��Ϣ�������

BOOL ModalSoundHide::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(FALSE);
	out.operate = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalSoundHide::OnBnClickedRadioOperate1(){
	out.operate = 1;
}


void ModalSoundHide::OnBnClickedRadioOperate2(){
	out.operate = 2;
}


void ModalSoundHide::OnBnClickedRadioOperate3(){
	out.operate = 3;
}


void ModalSoundHide::OnBnClickedOk(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
