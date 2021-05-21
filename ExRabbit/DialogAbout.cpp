// DialogAbout.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DialogAbout.h"
#include "afxdialogex.h"


// CDialogAbout 对话框

IMPLEMENT_DYNAMIC(CDialogAbout, CDialogEx)

CDialogAbout::CDialogAbout(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogAbout::IDD, pParent)
{

}

CDialogAbout::~CDialogAbout()
{
}

void CDialogAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_QR, m_QR);
}


BEGIN_MESSAGE_MAP(CDialogAbout, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogAbout::OnBnClickedOk)
	ON_COMMAND(ID_GOTO_COLG, &CDialogAbout::OnGoToColg)
	ON_COMMAND(ID_GOTO_EXNPK, &CDialogAbout::OnGoToExNpk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogAbout::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialogAbout 消息处理程序


BOOL CDialogAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_QRbmp.LoadBitmap(IDB_BITMAP2);
	m_QR.SetBitmap(m_QRbmp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDialogAbout::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}


void CDialogAbout::OnGoToColg()
{
	// TODO: 在此添加命令处理程序代码
	ShellExecute(NULL, L"open",L"https://bbs.colg.cn/thread-7571180-1-1.html", NULL, NULL, SW_MAXIMIZE); 
}


void CDialogAbout::OnGoToExNpk()
{
	// TODO: 在此添加命令处理程序代码
	ShellExecute(NULL, L"open",L"http://bbs.exnpk.com/thread-51457-1-1.html", NULL, NULL, SW_MAXIMIZE); 
}


void CDialogAbout::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(2); 
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}
