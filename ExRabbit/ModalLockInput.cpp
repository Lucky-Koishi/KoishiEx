// ModalLockInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalLockInput.h"
#include "afxdialogex.h"


// ModalLockInput �Ի���

IMPLEMENT_DYNAMIC(ModalLockInput, CDialogEx)

ModalLockInput::ModalLockInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalLockInput::IDD, pParent)
{
	restTime = 3;
}

ModalLockInput::~ModalLockInput()
{
}

void ModalLockInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalLockInput, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModalLockInput::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalLockInput ��Ϣ�������


void ModalLockInput::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString password;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(password);
	if(KoishiExpand::authorLock::checkLock(CStrToStr(fileCheckName), CStrToStr(password)) > 0){
		CDialogEx::OnOK();
	}else{
		restTime --;
		if(restTime > 0){
			CString tryString;
			tryString.Format(L"���������������%d�λ�������", restTime);
			MessageBox(tryString, L"��ʾ��");
		}else{
			remove(CStrToStr(fileCheckName).c_str());
			MessageBox(L"�����������ΪҪ�ͷ������Խ��ļ�ɾ��������", L"��ʾ��");
			CDialogEx::OnCancel();
		}
	}
}
