// ModalSaveWarning.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalSaveWarning.h"
#include "afxdialogex.h"


// ModalSaveWarning 对话框

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


// ModalSaveWarning 消息处理程序


BOOL ModalSaveWarning::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	switch(alertType) {
	case MODIFIED_IMG:
		GET_CTRL(CStatic, IDC_STATIC_INFO)->SetWindowText(L"当前正在编辑的IMG对象，\r\n还没有被确认修改喵。\r\n\r\n是否确认您的修改记录喵？");
		GET_CTRL(CButton, IDC_BUTTON_CANCEL)->SetWindowText(L"取消");
		GET_CTRL(CButton, IDC_BUTTON_CONTINUE)->SetWindowText(L"不修改");
		GET_CTRL(CButton, IDC_BUTTON_SAVERIGHT)->SetWindowText(L"确认修改！");
		GET_CTRL(CButton, IDC_BUTTON_SAVELEFT)->ShowWindow(SW_HIDE);
		break;
	case MODIFIED_NPK:
		GET_CTRL(CStatic, IDC_STATIC_INFO)->SetWindowText(L"当前正在打开的NPK文件，\r\n还没有被保存喵。\r\n\r\n是否保存您的修改记录喵？");
		GET_CTRL(CButton, IDC_BUTTON_CANCEL)->SetWindowText(L"取消");
		GET_CTRL(CButton, IDC_BUTTON_CONTINUE)->SetWindowText(L"不保存");
		GET_CTRL(CButton, IDC_BUTTON_SAVERIGHT)->SetWindowText(L"保存！");
		GET_CTRL(CButton, IDC_BUTTON_SAVELEFT)->ShowWindow(SW_HIDE);
		break;
	case MODIFIED_IMG_NPK:
		GET_CTRL(CStatic, IDC_STATIC_INFO)->SetWindowText(L"当前打开的NPK文件中，\r\n还有正在被编辑的IMG对象。\r\n\r\n是否保存您的修改记录喵？");
		GET_CTRL(CButton, IDC_BUTTON_CANCEL)->SetWindowText(L"取消");
		GET_CTRL(CButton, IDC_BUTTON_CONTINUE)->SetWindowText(L"不保存NPK");
		GET_CTRL(CButton, IDC_BUTTON_SAVERIGHT)->SetWindowText(L"不修改IMG并保存NPK");
		GET_CTRL(CButton, IDC_BUTTON_SAVELEFT)->SetWindowText(L"修改IMG并保存NPK");
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ModalSaveWarning::OnBnClickedButtonSaveleft() {
	// TODO:  在此添加控件通知处理程序代码
	returnType = RETURN_ALL_SAVE;
	OnOK();
}


void ModalSaveWarning::OnBnClickedButtonSaveright() {
	// TODO:  在此添加控件通知处理程序代码
	returnType = RETURN_SAVE;
	OnOK();
}


void ModalSaveWarning::OnBnClickedButtonContinue() {
	// TODO:  在此添加控件通知处理程序代码
	returnType = RETURN_NO_SAVE;
	OnOK();
}


void ModalSaveWarning::OnBnClickedButtonCancel() {
	// TODO:  在此添加控件通知处理程序代码
	returnType = RETURN_CANCEL;
	OnCancel();
}
