// ModalPictureStretch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalPictureStretch.h"
#include "afxdialogex.h"


// ModalPictureStretch �Ի���

IMPLEMENT_DYNAMIC(ModalPictureStretch, CDialogEx)

ModalPictureStretch::ModalPictureStretch(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalPictureStretch::IDD, pParent)
{

}

ModalPictureStretch::~ModalPictureStretch()
{
}

void ModalPictureStretch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalPictureStretch, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalPictureStretch::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalPictureStretch::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalPictureStretch::OnBnClickedRadioTarget3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalPictureStretch::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalPictureStretch::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDOK, &ModalPictureStretch::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalPictureStretch ��Ϣ�������


BOOL ModalPictureStretch::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	out.target = SINGLE_SELECT;
	out.mode = PIXEL_MODE;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK4)->SetCheck(1);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(L"0");
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"����(px)");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"����(px)");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"����(px)");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"����(px)");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(
		L"��ǰ֡�ĶԽ����꣺\r\n(" + NumToCStr(in.curX1) + L"," + NumToCStr(in.curY1) + L")��(" + NumToCStr(in.curX2) + L"," + NumToCStr(in.curY2) + L")\r\n" +
		L"IMG�ļ��ĶԽ����꣺\r\n(" + NumToCStr(in.imgX1) + L"," + NumToCStr(in.imgY1) + L")��(" + NumToCStr(in.imgX2) + L"," + NumToCStr(in.imgY2) + L")"
		);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ModalPictureStretch::OnBnClickedRadioTarget1() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	out.target = SINGLE_SELECT;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_TARGET2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(FALSE);
}


void ModalPictureStretch::OnBnClickedRadioTarget2() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	out.target = MULTI_SELECT;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET2)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(FALSE);
}


void ModalPictureStretch::OnBnClickedRadioTarget3() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	out.target = ALL_SELECT;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(TRUE);
}


void ModalPictureStretch::OnBnClickedRadioOperate1() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	out.mode = PIXEL_MODE;
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"����(px)");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"����(px)");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"����(px)");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"����(px)");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(L"0");
}


void ModalPictureStretch::OnBnClickedRadioOperate2() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	out.mode = RATIO_MODE;
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"����(%)");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"����(%)");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"����(%)");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"����(%)");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(L"0");
}


void ModalPictureStretch::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString numStr;
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->GetWindowText(numStr);
	out.para[0] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->GetWindowText(numStr);
	out.para[1] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->GetWindowText(numStr);
	out.para[2] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->GetWindowText(numStr);
	out.para[3] = _ttoi(numStr);
	out.enable[0] = GET_CTRL(CButton, IDC_CHECK1)->GetCheck() == 1;
	out.enable[1] = GET_CTRL(CButton, IDC_CHECK2)->GetCheck() == 1;
	out.enable[2] = GET_CTRL(CButton, IDC_CHECK3)->GetCheck() == 1;
	out.enable[3] = GET_CTRL(CButton, IDC_CHECK4)->GetCheck() == 1;
	CDialogEx::OnOK();
}
