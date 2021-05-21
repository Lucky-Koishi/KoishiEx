// ModalPictureParameter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalPictureParameter.h"
#include "afxdialogex.h"


// ModalPictureParameter �Ի���

IMPLEMENT_DYNAMIC(ModalPictureParameter, CDialogEx)

ModalPictureParameter::ModalPictureParameter(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalPictureParameter::IDD, pParent)
{

}

ModalPictureParameter::~ModalPictureParameter()
{
}

void ModalPictureParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalPictureParameter, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalPictureParameter::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalPictureParameter::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalPictureParameter::OnBnClickedRadioTarget3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalPictureParameter::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalPictureParameter::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalPictureParameter::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDOK, &ModalPictureParameter::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalPictureParameter ��Ϣ�������


BOOL ModalPictureParameter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	out.target = 1;
	out.operate = 1;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(
		L"��ǰ֡�Ļ�׼�����꣺\r\n("+NumToCStr(in.curBX)+L","+NumToCStr(in.curBY)+L")\r\n"+
		L"��ǰ֡��֡���ߣ�\r\n("+NumToCStr(in.curFW)+L","+NumToCStr(in.curFH)+L")"
	);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalPictureParameter::OnBnClickedRadioTarget1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 1;
}


void ModalPictureParameter::OnBnClickedRadioTarget2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 2;
}


void ModalPictureParameter::OnBnClickedRadioTarget3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 3;
}


void ModalPictureParameter::OnBnClickedRadioOperate1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 1;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"ˮƽ�ƶ�");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"��ֱ�ƶ�");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
}


void ModalPictureParameter::OnBnClickedRadioOperate2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 2;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"X����");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"Y����");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(NumToCStr(in.curBX));
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(NumToCStr(in.curBY));
}


void ModalPictureParameter::OnBnClickedRadioOperate3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 3;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"֡����");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"֡��߶�");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(NumToCStr(in.curFW));
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(NumToCStr(in.curFH));
}


void ModalPictureParameter::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString numStr;
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->GetWindowText(numStr);
	out.para[0] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->GetWindowText(numStr);
	out.para[1] = _ttoi(numStr);
	out.enable[0] = GET_CTRL(CButton, IDC_CHECK1)->GetCheck() == 1;
	out.enable[1] = GET_CTRL(CButton, IDC_CHECK2)->GetCheck() == 1;
	CDialogEx::OnOK();
}
