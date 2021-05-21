// ModalClearPicture.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalClearPicture.h"
#include "afxdialogex.h"


// ModalClearPicture �Ի���

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


// ModalClearPicture ��Ϣ�������


void ModalClearPicture::OnBnClickedRadioTarget1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 1;
}


void ModalClearPicture::OnBnClickedRadioTarget2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 2;
}


void ModalClearPicture::OnBnClickedRadioTarget3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 3;
}


void ModalClearPicture::OnBnClickedRadioOperate1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 1;
}


void ModalClearPicture::OnBnClickedRadioOperate2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 2;
}

BOOL ModalClearPicture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	out.target = 1;
	out.operate = 1;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalClearPicture::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
