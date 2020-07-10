// TinySetName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinySetName(white).h"
#include "afxdialogex.h"


// TinySetName �Ի���

IMPLEMENT_DYNAMIC(TinySetName, CDialogEx)

TinySetName::TinySetName(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinySetName::IDD, pParent)
{

}

TinySetName::~TinySetName()
{
}

void TinySetName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinySetName, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinySetName::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TinySetName::OnBnClickedCancel)
END_MESSAGE_MAP()


// TinySetName ��Ϣ�������


BOOL TinySetName::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(name);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void TinySetName::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(name);
	CDialogEx::OnOK();
}


void TinySetName::OnBnClickedCancel() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(name);
	CDialogEx::OnCancel();
}
