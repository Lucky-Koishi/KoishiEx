// TinyAddMark.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyAddMark.h"
#include "afxdialogex.h"


// TinyAddMark �Ի���

IMPLEMENT_DYNAMIC(TinyAddMark, CDialogEx)

TinyAddMark::TinyAddMark(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyAddMark::IDD, pParent)
{

}

TinyAddMark::~TinyAddMark()
{
}

void TinyAddMark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyAddMark, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinyAddMark::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyAddMark ��Ϣ�������


void TinyAddMark::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(str);
	text = CStrToStr(str);
	CDialogEx::OnOK();
}
