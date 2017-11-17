// DlgInsert.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsert.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"


// CDlgInsert 对话框

IMPLEMENT_DYNAMIC(CDlgInsert, CDialogEx)

CDlgInsert::CDlgInsert(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInsert::IDD, pParent)
{

}

CDlgInsert::~CDlgInsert()
{
}

void CDlgInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
	DDX_Control(pDX, IDC_CHECK2, m_ch2);
	DDX_Control(pDX, IDC_CHECK3, m_ch3);
	DDX_Control(pDX, IDC_CHECK4, m_ch4);
	DDX_Control(pDX, IDC_CHECK5, m_ch5);
	DDX_Control(pDX, IDC_CHECK6, m_ch6);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	DDX_Control(pDX, IDC_EDIT1, m_ed1);
	DDX_Control(pDX, IDC_EDIT2, m_ed2);
	DDX_Control(pDX, IDC_EDIT3, m_ed3);
}


BEGIN_MESSAGE_MAP(CDlgInsert, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK5, &CDlgInsert::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CDlgInsert::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgInsert::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgInsert::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgInsert::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgInsert::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInsert::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgInsert::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgInsert::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgInsert 消息处理程序


BOOL CDlgInsert::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cb1.ResetContent();
	m_cb1.AddString(L"IMGV2");
	m_cb1.AddString(L"IMGV4");
	m_cb1.AddString(L"IMGV5");
	m_cb1.AddString(L"IMGV6");
	m_cb1.SetCurSel(0);
	m_ch5.SetCheck(1);
	m_ch1.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgInsert::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch5.SetCheck(1);
	m_ch6.SetCheck(0);
	m_cb1.EnableWindow(true);
	m_ed1.EnableWindow(false);
	m_btn1.EnableWindow(false);
}


void CDlgInsert::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch5.SetCheck(0);
	m_ch6.SetCheck(1);
	m_cb1.EnableWindow(false);
	m_ed1.EnableWindow(true);
	m_btn1.EnableWindow(true);
}


void CDlgInsert::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
	m_ch4.SetCheck(0);
	m_ed2.EnableWindow(false);
}


void CDlgInsert::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
	m_ch4.SetCheck(0);
	m_ed2.EnableWindow(false);
}


void CDlgInsert::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
	m_ch4.SetCheck(0);
	m_ed2.EnableWindow(false);
}


void CDlgInsert::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
	m_ch4.SetCheck(1);
	m_ed2.EnableWindow(true);
}


void CDlgInsert::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_ed1.SetWindowText(fileName);
		m_ed3.SetWindowText(toSl(shorten(fileName)));
	}
}


void CDlgInsert::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos;
	if(m_ch1.GetCheck()){
		pos = dlg->crtIMGid;
	}else if(m_ch2.GetCheck()){
		pos = dlg->crtIMGid+1;
	}else if(m_ch3.GetCheck()){
		pos = dlg->no.count;
	}else if(m_ch4.GetCheck()){
		CString posStr;
		m_ed2.GetWindowText(posStr);
		pos = _ttoi(posStr);
	}
	CString fileName;
	str fn;
	if(m_ch6.GetCheck()){
		m_ed1.GetWindowText(fileName);
		CStrToStr(fileName, fn);
		IMGobject io(fn);
		m_ed3.GetWindowText(fileName);
		CStrToStr(fileName, fn);
		if(dlg->no.IMGinsert(pos, io, fn)){
			MessageBox(L"插入完毕！");
		}else{
			MessageBox(L"插入失败！");
		}
	}else if(m_ch5.GetCheck()){
		IMGversion ivl[4] = {V2,V4,V5,V6};
		IMGversion iv = ivl[m_cb1.GetCurSel()];
		IMGobject io;
		io.Create(iv);
		m_ed3.GetWindowText(fileName);
		CStrToStr(fileName, fn);
		if(dlg->no.IMGinsert(pos, io, fn)){
			MessageBox(L"插入完毕！");
		}else{
			MessageBox(L"插入失败！");
		}
	}
	//dlg->updateIMGlist();
	{
		dlg->m_lIMG.InsertItem(pos, shorten(fileName));
	}
	dlg->updateNPKInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsert::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
