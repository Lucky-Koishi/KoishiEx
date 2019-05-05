// ModalAdjustCanvas.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAdjustCanvas.h"
#include "afxdialogex.h"


// ModalAdjustCanvas �Ի���

IMPLEMENT_DYNAMIC(ModalAdjustCanvas, CDialogEx)

ModalAdjustCanvas::ModalAdjustCanvas(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalAdjustCanvas::IDD, pParent)
{

}

ModalAdjustCanvas::~ModalAdjustCanvas()
{
}

void ModalAdjustCanvas::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalAdjustCanvas, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalAdjustCanvas::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalAdjustCanvas::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalAdjustCanvas::OnBnClickedRadioTarget3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalAdjustCanvas::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalAdjustCanvas::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalAdjustCanvas::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE4, &ModalAdjustCanvas::OnBnClickedRadioOperate4)
	ON_BN_CLICKED(IDOK, &ModalAdjustCanvas::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalAdjustCanvas ��Ϣ�������


BOOL ModalAdjustCanvas::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	out.target = 1;
	out.operate = 1;
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
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(
		L"��ǰ֡�ĶԽ����꣺\r\n("+NumToCStr(in.curX1)+L","+NumToCStr(in.curY1)+L")��("+NumToCStr(in.curX2)+L","+NumToCStr(in.curY2)+L")\r\n"+
		L"IMG�ļ��ĶԽ����꣺\r\n("+NumToCStr(in.imgX1)+L","+NumToCStr(in.imgY1)+L")��("+NumToCStr(in.imgX2)+L","+NumToCStr(in.imgY2)+L")"
	);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalAdjustCanvas::OnBnClickedRadioTarget1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 1;
}


void ModalAdjustCanvas::OnBnClickedRadioTarget2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 2;
}


void ModalAdjustCanvas::OnBnClickedRadioTarget3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 3;
}


void ModalAdjustCanvas::OnBnClickedRadioOperate1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 1;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"��������");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"��������");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"��������");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"��������");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(L"0");
}


void ModalAdjustCanvas::OnBnClickedRadioOperate2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 2;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"��߲���");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"�ϱ߲���");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"�ұ߲���");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"�±߲���");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(L"0");
}


void ModalAdjustCanvas::OnBnClickedRadioOperate3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 3;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"������ֵ");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"������ֵ");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"������ֵ");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"������ֵ");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(NumToCStr(in.imgX1));
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(NumToCStr(in.imgY1));
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(NumToCStr(in.imgX2));
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(NumToCStr(in.imgY2));
}


void ModalAdjustCanvas::OnBnClickedRadioOperate4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 4;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"�������");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"�����ϱ�");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"�����ұ�");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"�����±�");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"-");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"-");
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(L"-");
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(L"-");
}


void ModalAdjustCanvas::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
