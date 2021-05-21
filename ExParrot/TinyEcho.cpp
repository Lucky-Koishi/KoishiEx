// TinyEcho.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyEcho.h"
#include "afxdialogex.h"


// TinyEcho �Ի���

IMPLEMENT_DYNAMIC(TinyEcho, CDialogEx)

TinyEcho::TinyEcho(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyEcho::IDD, pParent)
{

}

TinyEcho::~TinyEcho()
{
}

void TinyEcho::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyEcho, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &TinyEcho::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &TinyEcho::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &TinyEcho::OnEnChangeEdit3)
	ON_BN_CLICKED(IDOK, &TinyEcho::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyEcho ��Ϣ�������


BOOL TinyEcho::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowTextW(L"5");
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowTextW(L"500");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowTextW(L"0.8");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void TinyEcho::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString val;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowTextW(val);
	times = abs(_ttoi(val));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void TinyEcho::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString val;
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowTextW(val);
	offset = abs(_ttoi(val));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void TinyEcho::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString val;
	GET_CTRL(CEdit, IDC_EDIT3)->GetWindowTextW(val);
	attenu = abs(_ttof(val));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void TinyEcho::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
