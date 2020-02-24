// TinyAdjustVolume.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyAdjustVolume.h"
#include "afxdialogex.h"


// TinyAdjustVolume �Ի���

IMPLEMENT_DYNAMIC(TinyAdjustVolume, CDialogEx)

TinyAdjustVolume::TinyAdjustVolume(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyAdjustVolume::IDD, pParent)
{

}

TinyAdjustVolume::~TinyAdjustVolume()
{
}

void TinyAdjustVolume::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyAdjustVolume, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &TinyAdjustVolume::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &TinyAdjustVolume::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyAdjustVolume ��Ϣ�������


void TinyAdjustVolume::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString val;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(val);
	rate = _ttof(val);
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(maxEnergy/32768.f));
	double modifyEnergy = abs(rate)*maxEnergy;
	if(modifyEnergy >= 32768){
		modifyEnergy = 32768;
		GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(L"���������");
	}else{
		GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(L"û�����");
	}
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(modifyEnergy/32768.f));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void TinyAdjustVolume::OnBnClickedOk(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


BOOL TinyAdjustVolume::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"1.00");
	rate = 1.f;
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(DoubleToCStr(maxEnergy/32768.f));
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(DoubleToCStr(maxEnergy/32768.f));
	GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(L"û�����");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
