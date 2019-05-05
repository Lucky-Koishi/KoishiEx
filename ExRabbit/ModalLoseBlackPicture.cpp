// ModalLoseBlackPicture.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalLoseBlackPicture.h"
#include "afxdialogex.h"


// ModalLoseBlackPicture �Ի���

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


// ModalLoseBlackPicture ��Ϣ�������


void ModalLoseBlackPicture::OnBnClickedRadioTarget1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 1;
}


void ModalLoseBlackPicture::OnBnClickedRadioTarget2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 2;
}


void ModalLoseBlackPicture::OnBnClickedRadioTarget3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 3;
}


BOOL ModalLoseBlackPicture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalLoseBlackPicture::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString numStr;
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->GetWindowText(numStr);
	out.gamma = _ttoi(numStr);
	CDialogEx::OnOK();
}
