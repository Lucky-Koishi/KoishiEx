// DlgTrasform.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgTrasform.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgTrasform 对话框

IMPLEMENT_DYNAMIC(CDlgTrasform, CDialogEx)

CDlgTrasform::CDlgTrasform(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTrasform::IDD, pParent)
{

}

CDlgTrasform::~CDlgTrasform()
{
}

void CDlgTrasform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
	DDX_Control(pDX, IDC_CHECK2, m_ch2);
	DDX_Control(pDX, IDC_CHECK3, m_ch3);
	DDX_Control(pDX, IDC_CHECK4, m_ch4);
}


BEGIN_MESSAGE_MAP(CDlgTrasform, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTrasform::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgTrasform::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgTrasform::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgTrasform::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgTrasform::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgTrasform::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CDlgTrasform 消息处理程序


BOOL CDlgTrasform::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ch1.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgTrasform::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	if(m_ch1.GetCheck()){
		dlg->transform(V2);
	}else if(m_ch2.GetCheck()){
		dlg->transform(V4);
	}else if(m_ch3.GetCheck()){
		dlg->transform(V5);
	}else if(m_ch4.GetCheck()){
		dlg->transform(V6);
	}
	ShowWindow(SW_HIDE);
}


void CDlgTrasform::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CDlgTrasform::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
	m_ch4.SetCheck(0);
}


void CDlgTrasform::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
	m_ch4.SetCheck(0);
}


void CDlgTrasform::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
	m_ch4.SetCheck(0);
}


void CDlgTrasform::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
	m_ch4.SetCheck(1);
}
