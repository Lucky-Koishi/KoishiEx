// TinySetBrush.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinySetBrush.h"
#include "afxdialogex.h"


// TinySetBrush �Ի���

IMPLEMENT_DYNAMIC(TinySetBrush, CDialogEx)

TinySetBrush::TinySetBrush(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinySetBrush::IDD, pParent)
{

}

TinySetBrush::~TinySetBrush()
{
}

void TinySetBrush::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinySetBrush, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &TinySetBrush::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &TinySetBrush::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &TinySetBrush::OnBnClickedOk)
END_MESSAGE_MAP()


// TinySetBrush ��Ϣ�������


BOOL TinySetBrush::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(shape == 1){
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(TRUE);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(FALSE);
	}
	if(shape == 2){
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(FALSE);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(TRUE);
	}
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(NumToCStr(size));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void TinySetBrush::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(FALSE);
}


void TinySetBrush::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(TRUE);
}


void TinySetBrush::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(GET_CTRL(CButton, IDC_CHECK1)->GetCheck() == TRUE){
		shape = 1;
	}else{
		shape = 2;
	}
	CString s;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(s);
	if(_ttoi(s)<=0 || _ttoi(s)>10){
		MessageBox(L"������1-10֮�����������");
		return;
	}
	size = _ttoi(s);
	CDialogEx::OnOK();
}
