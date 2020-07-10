// TinyAdjustSpeed.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyAdjustSpeed.h"
#include "afxdialogex.h"


// TinyAdjustSpeed �Ի���

IMPLEMENT_DYNAMIC(TinyAdjustSpeed, CDialogEx)

TinyAdjustSpeed::TinyAdjustSpeed(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyAdjustSpeed::IDD, pParent)
{

}

TinyAdjustSpeed::~TinyAdjustSpeed()
{
}

void TinyAdjustSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyAdjustSpeed, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinyAdjustSpeed::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TinyAdjustSpeed::OnBnClickedCancel)
END_MESSAGE_MAP()


// TinyAdjustSpeed ��Ϣ�������


BOOL TinyAdjustSpeed::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(type ? L"��������" : L"�����ٶ�");
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"1.00");
	rate = 1.f;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void TinyAdjustSpeed::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString ss;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(ss);
	rate = _ttof(ss);
	if(rate < 0.5) {
		MessageBox(L"�������ֱ���Ҫ���ڵ���0.5��", L"��ʾ��");
		return;
	}
	CDialogEx::OnOK();
}


void TinyAdjustSpeed::OnBnClickedCancel() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
