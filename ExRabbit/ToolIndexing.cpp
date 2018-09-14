// ToolIndexing.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolIndexing.h"
#include "afxdialogex.h"
#include "ExRabbitdlg.h"

// CToolIndexing 对话框

IMPLEMENT_DYNAMIC(CToolIndexing, CDialogEx)

CToolIndexing::CToolIndexing(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolIndexing::IDD, pParent)
{

}

CToolIndexing::~CToolIndexing()
{
}

void CToolIndexing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_c1);
	DDX_Control(pDX, IDC_CHECK2, m_c2);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_PROGRESS1, m_p);
}


BEGIN_MESSAGE_MAP(CToolIndexing, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolIndexing::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CToolIndexing::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CToolIndexing::OnBnClickedCheck2)
	ON_BN_CLICKED(IDCANCEL, &CToolIndexing::OnBnClickedCancel)
END_MESSAGE_MAP()


// CToolIndexing 消息处理程序


void CToolIndexing::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_c2.GetCheck()){
		m_e1.SetWindowText(L"开始转换");
		AfxBeginThread(indexingThread, (PVOID)GetParent());
		AfxBeginThread(indexingProcessThread, (PVOID)GetParent());
	}else{
		m_e1.SetWindowText(L"开始转换外部文件");
		AfxBeginThread(indexingExternThread, (PVOID)GetParent());
		AfxBeginThread(indexingProcessThread, (PVOID)GetParent());
	}
	//AfxBeginThread(PH, (PVOID)this);
}


UINT CToolIndexing::PH(PVOID para){
	//CToolIndexing* dlg = (CToolIndexing*)para;
	//while(dlg->ii.millages < 1000){
	//	dlg->m_p.SetPos(dlg->ii.millages);
	//	if(dlg->ii.millages > 0 && dlg->ii.millages < 500){
	//		dlg->m_e1.SetWindowText(L"正在重建颜色表……");
	//	}
	//	if(dlg->ii.millages > 500 && dlg->ii.millages < 1000){
	//		dlg->m_e1.SetWindowText(L"正在填充索引……");
	//	}
	//	Sleep(5);
	//}
	//dlg->m_e1.SetWindowText(L"转换完毕。");
	return 0;
}
BOOL CToolIndexing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_e1.SetWindowText(L"等待");
	m_e2.SetWindowText(L"将外部IMG文件或EX中选定的IMG文件转化为V4版本(索引图像)。与EX内置的IMG转换相比，这个方法采用基于颜色统计与最短颜色欧氏距离匹配的方式构造颜色表和设定索引，因而能在保持较低失真率的前提下，突破颜色数超过255的限制。注意：半透明像素将会被忽略。");
	m_p.SetRange32(0,1000);
	m_c2.SetCheck(1);
	m_c1.SetCheck(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CToolIndexing::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_e1.SetWindowText(L"准备转换"+shorten(fileName));
		m_c1.SetCheck(1);
		m_c2.SetCheck(0);
	}else{
		m_c1.SetCheck(0);
		m_c2.SetCheck(1);
	}
}


void CToolIndexing::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(0);
	m_c2.SetCheck(1);
}


void CToolIndexing::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
