// DlgMix.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgMix.h"
#include "afxdialogex.h"


// CDlgMix 对话框

IMPLEMENT_DYNAMIC(CDlgMix, CDialogEx)

CDlgMix::CDlgMix(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMix::IDD, pParent)
{

}

CDlgMix::~CDlgMix()
{
}

void CDlgMix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_LIST1, m_l1);
}


BEGIN_MESSAGE_MAP(CDlgMix, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgMix::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgMix::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgMix 消息处理程序


BOOL CDlgMix::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgMix::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgMix::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
