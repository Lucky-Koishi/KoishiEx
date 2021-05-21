// ModalRename.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalRename.h"
#include "afxdialogex.h"


// ModalRename �Ի���

IMPLEMENT_DYNAMIC(ModalRename, CDialogEx)

ModalRename::ModalRename(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalRename::IDD, pParent)
{

}

ModalRename::~ModalRename()
{
}

void ModalRename::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalRename, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModalRename::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalRename ��Ϣ�������


BOOL ModalRename::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(oldName);
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(oldName);
	newName = oldName;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalRename::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(newName);
	CDialogEx::OnOK();
}
