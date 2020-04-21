// ToolAvatarIO.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarIO.h"
#include "afxdialogex.h"


// ToolAvatarIO �Ի���

IMPLEMENT_DYNAMIC(ToolAvatarIO, CDialogEx)

ToolAvatarIO::ToolAvatarIO(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarIO::IDD, pParent)
{

}

ToolAvatarIO::~ToolAvatarIO()
{
}

void ToolAvatarIO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarIO, CDialogEx)
	ON_BN_CLICKED(IDOK, &ToolAvatarIO::OnBnClickedOk)
END_MESSAGE_MAP()


// ToolAvatarIO ��Ϣ�������


BOOL ToolAvatarIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(style == AVA_IMPORT){
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"�����������빲���롣");
	}else{
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(content);
		GET_CTRL(CEdit, IDC_EDIT1)->SetReadOnly(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ToolAvatarIO::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(style == AVA_IMPORT){
		GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(content);
	}
	CDialogEx::OnOK();
}
