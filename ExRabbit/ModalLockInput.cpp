// ModalLockInput.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalLockInput.h"
#include "afxdialogex.h"


// ModalLockInput 对话框

IMPLEMENT_DYNAMIC(ModalLockInput, CDialogEx)

ModalLockInput::ModalLockInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalLockInput::IDD, pParent)
{
	restTime = 3;
}

ModalLockInput::~ModalLockInput()
{
}

void ModalLockInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalLockInput, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModalLockInput::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalLockInput 消息处理程序


void ModalLockInput::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString password;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(password);
	if(KoishiExpand::authorLock::checkLock(CStrToStr(fileCheckName), CStrToStr(password)) > 0){
		CDialogEx::OnOK();
	}else{
		restTime --;
		if(restTime > 0){
			CString tryString;
			tryString.Format(L"口令不对喵！您还有%d次机会喵！", restTime);
			MessageBox(tryString, L"提示喵");
		}else{
			remove(CStrToStr(fileCheckName).c_str());
			MessageBox(L"口令不对喵！因为要惩罚你所以将文件删除了喵！", L"提示喵");
			CDialogEx::OnCancel();
		}
	}
}
