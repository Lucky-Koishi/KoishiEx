// ModalPictureStretch.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalPictureStretch.h"
#include "afxdialogex.h"


// ModalPictureStretch 对话框

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


// ModalPictureStretch 消息处理程序


BOOL ModalPictureStretch::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"向左(px)");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"向上(px)");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"向右(px)");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"向下(px)");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(
		L"当前帧的对角坐标：\r\n(" + NumToCStr(in.curX1) + L"," + NumToCStr(in.curY1) + L")至(" + NumToCStr(in.curX2) + L"," + NumToCStr(in.curY2) + L")\r\n" +
		L"IMG文件的对角坐标：\r\n(" + NumToCStr(in.imgX1) + L"," + NumToCStr(in.imgY1) + L")至(" + NumToCStr(in.imgX2) + L"," + NumToCStr(in.imgY2) + L")"
		);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ModalPictureStretch::OnBnClickedRadioTarget1() {
	// TODO:  在此添加控件通知处理程序代码
	out.target = SINGLE_SELECT;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_TARGET2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(FALSE);
}


void ModalPictureStretch::OnBnClickedRadioTarget2() {
	// TODO:  在此添加控件通知处理程序代码
	out.target = MULTI_SELECT;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET2)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(FALSE);
}


void ModalPictureStretch::OnBnClickedRadioTarget3() {
	// TODO:  在此添加控件通知处理程序代码
	out.target = ALL_SELECT;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(TRUE);
}


void ModalPictureStretch::OnBnClickedRadioOperate1() {
	// TODO:  在此添加控件通知处理程序代码
	out.mode = PIXEL_MODE;
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"向左(px)");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"向上(px)");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"向右(px)");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"向下(px)");
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
	// TODO:  在此添加控件通知处理程序代码
	out.mode = RATIO_MODE;
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"向左(%)");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"向上(%)");
	GET_CTRL(CButton, IDC_CHECK3)->SetWindowText(L"向右(%)");
	GET_CTRL(CButton, IDC_CHECK4)->SetWindowText(L"向下(%)");
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
	// TODO:  在此添加控件通知处理程序代码
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
