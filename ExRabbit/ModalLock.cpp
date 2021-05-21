// ModalLock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalLock.h"
#include "afxdialogex.h"


// ModalLock �Ի���

IMPLEMENT_DYNAMIC(ModalLock, CDialogEx)

ModalLock::ModalLock(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalLock::IDD, pParent)
{

}

ModalLock::~ModalLock()
{
}

void ModalLock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalLock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ModalLock::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &ModalLock::OnBnClickedOk)
	ON_COMMAND(ID_TOOLS_NPK_LOCK, &ModalLock::OnToolsNPKLock)
END_MESSAGE_MAP()


// ModalLock ��Ϣ�������


void ModalLock::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(fileName);
	}
}


void ModalLock::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString fileName, passWord;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(fileName);
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(passWord);
	KoishiExpand::authorLock::addLock(CStrToStr(fileName), CStrToStr(passWord));
	MessageBox(L"�ѽ���NPK������������",L"��ʾ��");
	CDialogEx::OnOK();
}


void ModalLock::OnToolsNPKLock()
{
	// TODO: �ڴ���������������
}
