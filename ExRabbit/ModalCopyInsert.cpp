// ModalCopyInsert.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalCopyInsert.h"
#include "afxdialogex.h"


// ModalCopyInsert �Ի���

IMPLEMENT_DYNAMIC(ModalCopyInsert, CDialogEx)

ModalCopyInsert::ModalCopyInsert(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalCopyInsert::IDD, pParent)
{

}

ModalCopyInsert::~ModalCopyInsert()
{
}

void ModalCopyInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalCopyInsert, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalCopyInsert::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalCopyInsert::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_INPUT1, &ModalCopyInsert::OnBnClickedRadioInput1)
	ON_BN_CLICKED(IDC_RADIO_INPUT2, &ModalCopyInsert::OnBnClickedRadioInput2)
	ON_BN_CLICKED(IDOK, &ModalCopyInsert::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalCopyInsert ��Ϣ�������


void ModalCopyInsert::OnBnClickedRadioOperate1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(0);
	out.operate = 1;
}


void ModalCopyInsert::OnBnClickedRadioOperate2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(1);
	out.operate = 2;
}


void ModalCopyInsert::OnBnClickedRadioInput1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(0);
	out.type = 1;
}


void ModalCopyInsert::OnBnClickedRadioInput2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(1);
	out.type = 2;
}


BOOL ModalCopyInsert::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	OnBnClickedRadioOperate1();
	OnBnClickedRadioInput1();
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(in.pathName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalCopyInsert::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(out.pathName);
	CDialogEx::OnOK();
}
