// ModalConflictWarning.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ModalConflictWarning(white).h"
#include "afxdialogex.h"


// ModalConflictWarning �Ի���

IMPLEMENT_DYNAMIC(ModalConflictWarning, CDialogEx)

ModalConflictWarning::ModalConflictWarning(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalConflictWarning::IDD, pParent)
{

}

ModalConflictWarning::~ModalConflictWarning()
{
}

void ModalConflictWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalConflictWarning, CDialogEx)
	ON_BN_CLICKED(ID_REPLACE, &ModalConflictWarning::OnBnClickedReplace)
	ON_BN_CLICKED(ID_IGNORE, &ModalConflictWarning::OnBnClickedIgnore)
	ON_BN_CLICKED(ID_REMAIN, &ModalConflictWarning::OnBnClickedRemain)
	ON_BN_CLICKED(ID_RENAME, &ModalConflictWarning::OnBnClickedRename)
END_MESSAGE_MAP()


// ModalConflictWarning ��Ϣ�������


BOOL ModalConflictWarning::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CStatic, IDC_STATIC1)->SetWindowText(
		L"���ִ˶���������NPK��ĳ�����·������ͬ��\r\n" +
		conflictName + 
		L"Ҫ��ô������"
		);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ModalConflictWarning::OnBnClickedReplace() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	method = 0;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}


void ModalConflictWarning::OnBnClickedIgnore() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	method = 1;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}


void ModalConflictWarning::OnBnClickedRemain() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	method = 2;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}


void ModalConflictWarning::OnBnClickedRename() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	method = 3;
	noAlarm = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	OnOK();
}
