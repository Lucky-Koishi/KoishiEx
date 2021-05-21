// ModalPictureParameter.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalPictureParameter.h"
#include "afxdialogex.h"


// ModalPictureParameter 对话框

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


// ModalPictureParameter 消息处理程序


BOOL ModalPictureParameter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	out.target = 1;
	out.operate = 1;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(
		L"当前帧的基准点坐标：\r\n("+NumToCStr(in.curBX)+L","+NumToCStr(in.curBY)+L")\r\n"+
		L"当前帧的帧域宽高：\r\n("+NumToCStr(in.curFW)+L","+NumToCStr(in.curFH)+L")"
	);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ModalPictureParameter::OnBnClickedRadioTarget1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 1;
}


void ModalPictureParameter::OnBnClickedRadioTarget2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 2;
}


void ModalPictureParameter::OnBnClickedRadioTarget3()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 3;
}


void ModalPictureParameter::OnBnClickedRadioOperate1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 1;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"水平移动");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"垂直移动");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(L"0");
}


void ModalPictureParameter::OnBnClickedRadioOperate2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 2;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"X坐标");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"Y坐标");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(NumToCStr(in.curBX));
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(NumToCStr(in.curBY));
}


void ModalPictureParameter::OnBnClickedRadioOperate3()
{
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 3;
	GET_CTRL(CButton, IDC_CHECK1)->SetWindowText(L"帧域宽度");
	GET_CTRL(CButton, IDC_CHECK2)->SetWindowText(L"帧域高度");
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(NumToCStr(in.curFW));
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(NumToCStr(in.curFH));
}


void ModalPictureParameter::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString numStr;
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->GetWindowText(numStr);
	out.para[0] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->GetWindowText(numStr);
	out.para[1] = _ttoi(numStr);
	out.enable[0] = GET_CTRL(CButton, IDC_CHECK1)->GetCheck() == 1;
	out.enable[1] = GET_CTRL(CButton, IDC_CHECK2)->GetCheck() == 1;
	CDialogEx::OnOK();
}
