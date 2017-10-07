// ScanDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DemoEx.h"
#include "ScanDialog.h"
#include "afxdialogex.h"
#include "DemoExDlg.h"

// CScanDialog 对话框

IMPLEMENT_DYNAMIC(CScanDialog, CDialogEx)

CScanDialog::CScanDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScanDialog::IDD, pParent)
{

}

CScanDialog::~CScanDialog()
{
}

void CScanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_SPIN1, m_sp1);
	DDX_Control(pDX, IDC_SPIN2, m_sp2);
	DDX_Control(pDX, IDC_COMBO1, m_c1);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
}


BEGIN_MESSAGE_MAP(CScanDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScanDialog::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CScanDialog::OnBnClickedButton1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CScanDialog::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CScanDialog::OnDeltaposSpin2)
	ON_BN_CLICKED(IDC_CHECK1, &CScanDialog::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CScanDialog 消息处理程序
extern CString NumToCStr(int n);

void CScanDialog::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDemoExDlg* dlg = (CDemoExDlg*)para;
	dlg->draw();
}


void CScanDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDemoExDlg* dlg = (CDemoExDlg*)para;
	int row = dlg->m_l2.GetSelectionMark();
	if(row<0)
		return;
	dlg->base.set_X(-dlg->io.content[row].get_basePt().get_X());
	dlg->base.set_Y(-dlg->io.content[row].get_basePt().get_Y());
	m_e1.SetWindowText(NumToCStr(dlg->base.get_X()));
	m_e2.SetWindowText(NumToCStr(dlg->base.get_Y()));
	dlg->draw();
}


void CScanDialog::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CDemoExDlg* dlg = (CDemoExDlg*)para;
	dlg->base.set_X(dlg->base.get_X()+pNMUpDown->iDelta);
	m_e1.SetWindowText(NumToCStr(dlg->base.get_X()));
	dlg->draw();
	*pResult = 0;
}


void CScanDialog::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CDemoExDlg* dlg = (CDemoExDlg*)para;
	dlg->base.set_Y(dlg->base.get_Y()+pNMUpDown->iDelta);
	m_e2.SetWindowText(NumToCStr(dlg->base.get_Y()));
	dlg->draw();
	*pResult = 0;
}


void CScanDialog::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDemoExDlg* dlg = (CDemoExDlg*)para;
	dlg->draw();
}
