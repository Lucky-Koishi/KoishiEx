// TinyFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyFrame.h"
#include "afxdialogex.h"


// TinyFrame �Ի���

IMPLEMENT_DYNAMIC(TinyFrame, CDialogEx)

TinyFrame::TinyFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyFrame::IDD, pParent)
{

}

TinyFrame::~TinyFrame()
{
}

void TinyFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyFrame, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinyFrame::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyFrame ��Ϣ�������


BOOL TinyFrame::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"��Χ:" + NumToCStr(min) + L"-" + NumToCStr(max));
	GetDlgItem(IDC_EDIT2)->SetWindowText(NumToCStr(cur));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void TinyFrame::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString ss;
	GetDlgItem(IDC_EDIT2)->GetWindowText(ss);
	output = _ttoi(ss);
	if(output < min || output > max) {
		MessageBox(L"�����뷶Χ���ڵ�֡������", L"��ʾ");
		return;
	}
	CDialogEx::OnOK();
}
