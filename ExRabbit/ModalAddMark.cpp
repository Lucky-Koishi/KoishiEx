// ModalAddMark.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAddMark.h"
#include "afxdialogex.h"
#include "TinyColorSelect.h"

// ModalAddMark 对话框

IMPLEMENT_DYNAMIC(ModalAddMark, CDialogEx)

ModalAddMark::ModalAddMark(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalAddMark::IDD, pParent)
{

}

ModalAddMark::~ModalAddMark()
{
}

void ModalAddMark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalAddMark, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalAddMark::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalAddMark::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalAddMark::OnBnClickedRadioTarget3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalAddMark::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalAddMark::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalAddMark::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE4, &ModalAddMark::OnBnClickedRadioOperate4)
	ON_BN_CLICKED(IDC_RADIO_OPERATE5, &ModalAddMark::OnBnClickedRadioOperate5)
	ON_BN_CLICKED(IDOK, &ModalAddMark::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &ModalAddMark::OnBnClickedButtonColor)
END_MESSAGE_MAP()


// ModalAddMark 消息处理程序


BOOL ModalAddMark::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	out.target = 1;
	out.operate = 1;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_TEXT)->SetWindowText(L"FRAME_[F] [I]");
	if(in.version == V2){
		GET_CTRL(CEdit, IDC_EDIT_COLOR)->SetWindowText(L"000000");
		out.useColor = color(0xff, 0, 0, 0);
	}else{
		GET_CTRL(CEdit, IDC_EDIT_COLOR)->SetWindowText(L"第1项喵");
		out.useColorID = 1;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ModalAddMark::OnBnClickedRadioTarget1(){
	// TODO: 在此添加控件通知处理程序代码
	out.target = 1;
}

void ModalAddMark::OnBnClickedRadioTarget2(){
	// TODO: 在此添加控件通知处理程序代码
	out.target = 2;
}

void ModalAddMark::OnBnClickedRadioTarget3(){
	// TODO: 在此添加控件通知处理程序代码
	out.target = 3;
}

void ModalAddMark::OnBnClickedRadioOperate1(){
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 1;
}

void ModalAddMark::OnBnClickedRadioOperate2(){
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 2;
}

void ModalAddMark::OnBnClickedRadioOperate3(){
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 3;
}

void ModalAddMark::OnBnClickedRadioOperate4(){
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 4;
}

void ModalAddMark::OnBnClickedRadioOperate5(){
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 5;
}

void ModalAddMark::OnBnClickedOk(){
	// TODO: 在此添加控件通知处理程序代码
	CString numStr;
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->GetWindowText(numStr);
	out.xDelta = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->GetWindowText(numStr);
	out.yDelta = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_TEXT)->GetWindowText(numStr);
	out.text = numStr;
	CDialogEx::OnOK();
}


void ModalAddMark::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	if(in.version == V2){
		CString colorStr;
		GET_CTRL(CEdit, IDC_EDIT_COLOR)->GetWindowText(colorStr);
		int colorValue = B16CStrToNum(colorStr);
		COLORREF sclr = RGB(colorValue >> 16, colorValue >> 8, colorValue);
		CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
		if(cdlg.DoModal() == IDOK){
			sclr = cdlg.GetColor();
			colorStr.Format(L"%02X%02X%02X", GetRValue(sclr),
				GetGValue(sclr), GetBValue(sclr));
			out.useColor = color(0xFF, GetRValue(sclr),
				GetGValue(sclr), GetBValue(sclr));
			GET_CTRL(CEdit, IDC_EDIT_COLOR)->SetWindowText(colorStr);
		}
	}else{
		TinyColorSelect dlg;
		dlg.in = in.list;
		if(IDOK == dlg.DoModal()){
			out.useColorID = dlg.selection;
			CString colorStr;
			colorStr.Format(L"第%d项喵", out.useColorID);
			GET_CTRL(CEdit, IDC_EDIT_COLOR)->SetWindowText(colorStr);
		}
	}
}
