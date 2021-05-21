// TinyStretch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyStretch.h"
#include "afxdialogex.h"


// TinyStretch �Ի���

IMPLEMENT_DYNAMIC(TinyStretch, CDialogEx)

TinyStretch::TinyStretch(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyStretch::IDD, pParent)
{

}

TinyStretch::~TinyStretch()
{
}

void TinyStretch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyStretch, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &TinyStretch::OnEnChangeEdit1)
END_MESSAGE_MAP()


// TinyStretch ��Ϣ�������


void TinyStretch::OnEnChangeEdit1(){
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString val;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(val);
	rate =  abs(_ttof(val));
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(1000.f * originLen / sampleRate));
	double modifyLen = rate * originLen;
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(1000.f * modifyLen / sampleRate));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL TinyStretch::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"1.00");
	rate = 1.f;
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(1000.f * originLen / sampleRate));
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(1000.f * originLen / sampleRate));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
