// DlgLoseBlack.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgLoseBlack.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// DlgLoseBlack 对话框

IMPLEMENT_DYNAMIC(CDlgLoseBlack, CDialogEx)

CDlgLoseBlack::CDlgLoseBlack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLoseBlack::IDD, pParent)
{

}

CDlgLoseBlack::~CDlgLoseBlack()
{
}

void CDlgLoseBlack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eGamma);
}


BEGIN_MESSAGE_MAP(CDlgLoseBlack, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLoseBlack::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgLoseBlack::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgLoseBlack 消息处理程序


void CDlgLoseBlack::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	CString gammaStr;
	m_eGamma.GetWindowText(gammaStr);
	dlg->loseBlackPara.gamma = _ttoi(gammaStr);
	AfxBeginThread(dlg->threadLoseBlack, (void*)GetParent());
	ShowWindow(SW_HIDE);
}


void CDlgLoseBlack::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
