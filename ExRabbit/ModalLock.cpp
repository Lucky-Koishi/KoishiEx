// ModalLock.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalLock.h"
#include "afxdialogex.h"


// ModalLock 对话框

IMPLEMENT_DYNAMIC(ModalLock, CDialogEx)

ModalLock::ModalLock(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalLock::IDD, pParent)
{

}

ModalLock::~ModalLock()
{
}

void ModalLock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalLock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ModalLock::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &ModalLock::OnBnClickedOk)
	ON_COMMAND(ID_TOOLS_NPK_LOCK, &ModalLock::OnToolsNPKLock)
END_MESSAGE_MAP()


// ModalLock 消息处理程序


void ModalLock::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(fileName);
	}
}


void ModalLock::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName, passWord;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(fileName);
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(passWord);
	KoishiExpand::authorLock::addLock(CStrToStr(fileName), CStrToStr(passWord));
	MessageBox(L"已将该NPK进行锁定喵！",L"提示喵");
	CDialogEx::OnOK();
}


void ModalLock::OnToolsNPKLock()
{
	// TODO: 在此添加命令处理程序代码
}
