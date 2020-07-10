// ModalCopyReplace.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalCopyReplace.h"
#include "afxdialogex.h"

// ModalCopyReplace �Ի���

IMPLEMENT_DYNAMIC(ModalCopyReplace, CDialogEx)

ModalCopyReplace::ModalCopyReplace(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalCopyReplace::IDD, pParent)
{

}

ModalCopyReplace::~ModalCopyReplace()
{
}

void ModalCopyReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalCopyReplace, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalCopyReplace::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalCopyReplace::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalCopyReplace::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_INPUT1, &ModalCopyReplace::OnBnClickedRadioInput1)
	ON_BN_CLICKED(IDC_RADIO_INPUT2, &ModalCopyReplace::OnBnClickedRadioInput2)
	ON_BN_CLICKED(IDOK, &ModalCopyReplace::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalCopyReplace ��Ϣ�������


void ModalCopyReplace::OnBnClickedRadioOperate1(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(out.type == 1);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(out.type == 2);
	out.operate = 1;
}


void ModalCopyReplace::OnBnClickedRadioOperate2(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(out.type == 1);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(out.type == 2);
	out.operate = 2;
}


void ModalCopyReplace::OnBnClickedRadioOperate3(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(out.type == 1);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(out.type == 2);
	out.operate = 3;
}


void ModalCopyReplace::OnBnClickedRadioInput1(){
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(out.operate == 1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(out.operate == 2);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(out.operate == 3);
	out.type = 1;
}


void ModalCopyReplace::OnBnClickedRadioInput2(){
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(0);
	GET_CTRL(CButton, IDC_RADIO_INPUT2)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(out.operate == 1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(out.operate == 2);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(out.operate == 3);
	out.type = 2;
}


void ModalCopyReplace::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = GET_CTRL(CGoodListCtrl, IDC_LIST1)->GetSelectionMark();
	if(i == -1){
		MessageBox(L"��δѡ��IMG��",L"��ʾ");
		return;
	}
	out.selectID = i;
	CDialogEx::OnOK();
}


BOOL ModalCopyReplace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertColumn(L"��ѡ��Ŀ��IMG,200");
	for(int i = 0;i<in.ptrNo->count;i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertItem(GetTail(StrToCStr(in.ptrNo->entry[i].comment)));
	OnBnClickedRadioOperate1();
	OnBnClickedRadioInput2();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
