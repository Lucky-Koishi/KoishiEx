// ModalSaveWarning.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalSaveWarning.h"
#include "afxdialogex.h"


// ModalSaveWarning �Ի���

IMPLEMENT_DYNAMIC(ModalSaveWarning, CDialogEx)

ModalSaveWarning::ModalSaveWarning(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalSaveWarning::IDD, pParent){

}
ModalSaveWarning::~ModalSaveWarning(){
}

void ModalSaveWarning::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalSaveWarning, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVELEFT, &ModalSaveWarning::OnBnClickedButtonSaveleft)
	ON_BN_CLICKED(IDC_BUTTON_SAVERIGHT, &ModalSaveWarning::OnBnClickedButtonSaveright)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &ModalSaveWarning::OnBnClickedButtonContinue)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &ModalSaveWarning::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// ModalSaveWarning ��Ϣ�������


BOOL ModalSaveWarning::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	switch(alertType) {
	case MODIFIED_IMG:
		GET_CTRL(CStatic, IDC_STATIC_INFO)->SetWindowText(L"��ǰ���ڱ༭��IMG����\r\n��û�б�ȷ���޸�����\r\n\r\n�Ƿ�ȷ�������޸ļ�¼����");
		GET_CTRL(CButton, IDC_BUTTON_CANCEL)->SetWindowText(L"ȡ��");
		GET_CTRL(CButton, IDC_BUTTON_CONTINUE)->SetWindowText(L"���޸�");
		GET_CTRL(CButton, IDC_BUTTON_SAVERIGHT)->SetWindowText(L"ȷ���޸ģ�");
		GET_CTRL(CButton, IDC_BUTTON_SAVELEFT)->ShowWindow(SW_HIDE);
		break;
	case MODIFIED_NPK:
		GET_CTRL(CStatic, IDC_STATIC_INFO)->SetWindowText(L"��ǰ���ڴ򿪵�NPK�ļ���\r\n��û�б���������\r\n\r\n�Ƿ񱣴������޸ļ�¼����");
		GET_CTRL(CButton, IDC_BUTTON_CANCEL)->SetWindowText(L"ȡ��");
		GET_CTRL(CButton, IDC_BUTTON_CONTINUE)->SetWindowText(L"������");
		GET_CTRL(CButton, IDC_BUTTON_SAVERIGHT)->SetWindowText(L"���棡");
		GET_CTRL(CButton, IDC_BUTTON_SAVELEFT)->ShowWindow(SW_HIDE);
		break;
	case MODIFIED_IMG_NPK:
		GET_CTRL(CStatic, IDC_STATIC_INFO)->SetWindowText(L"��ǰ�򿪵�NPK�ļ��У�\r\n�������ڱ��༭��IMG����\r\n\r\n�Ƿ񱣴������޸ļ�¼����");
		GET_CTRL(CButton, IDC_BUTTON_CANCEL)->SetWindowText(L"ȡ��");
		GET_CTRL(CButton, IDC_BUTTON_CONTINUE)->SetWindowText(L"������NPK");
		GET_CTRL(CButton, IDC_BUTTON_SAVERIGHT)->SetWindowText(L"���޸�IMG������NPK");
		GET_CTRL(CButton, IDC_BUTTON_SAVELEFT)->SetWindowText(L"�޸�IMG������NPK");
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ModalSaveWarning::OnBnClickedButtonSaveleft() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	returnType = RETURN_ALL_SAVE;
	OnOK();
}


void ModalSaveWarning::OnBnClickedButtonSaveright() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	returnType = RETURN_SAVE;
	OnOK();
}


void ModalSaveWarning::OnBnClickedButtonContinue() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	returnType = RETURN_NO_SAVE;
	OnOK();
}


void ModalSaveWarning::OnBnClickedButtonCancel() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	returnType = RETURN_CANCEL;
	OnCancel();
}
