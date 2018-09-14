// DlgInsert.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsertIMG.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"


// CDlgInsertIMG 对话框

IMPLEMENT_DYNAMIC(CDlgInsertIMG, CDialogEx)

CDlgInsertIMG::CDlgInsertIMG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInsertIMG::IDD, pParent)
{

}

CDlgInsertIMG::~CDlgInsertIMG()
{
}

void CDlgInsertIMG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON7, m_btn7);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
	DDX_Control(pDX, IDC_CHECK2, m_ch2);
	DDX_Control(pDX, IDC_CHECK3, m_ch3);
	DDX_Control(pDX, IDC_COMBO1, m_c1);
	DDX_Control(pDX, IDC_COMBO3, m_c3);
	DDX_Control(pDX, IDC_COMBO4, m_c4);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_EDIT3, m_e3);
	DDX_Control(pDX, IDC_EDIT6, m_e6);
}


BEGIN_MESSAGE_MAP(CDlgInsertIMG, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgInsertIMG::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgInsertIMG::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgInsertIMG::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInsertIMG::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgInsertIMG::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgInsertIMG::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgInsertIMG::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgInsertIMG::OnBnClickedButton7)
END_MESSAGE_MAP()


// CDlgInsertIMG 消息处理程序


BOOL CDlgInsertIMG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_c1.ResetContent();
	m_c1.AddString(L"空IMG对象");
	m_c1.AddString(L"从外部IMG文件导入");
	m_c1.AddString(L"从外部NPK文件导入");
	m_c1.SetCurSel(0);
	m_c3.ResetContent();
	m_c3.AddString(L"V2");
	m_c3.AddString(L"V4");
	m_c3.AddString(L"V5");
	m_c3.AddString(L"V6");
	m_c3.SetCurSel(0);
	m_c4.ResetContent();
	m_c4.AddString(L"不进行检测，允许冲突");
	m_c4.AddString(L"NPK内存在相同路径名的IMG时跳过");
	m_c4.AddString(L"NPK内存在相同路径名的IMG时替换");
	m_c4.SetCurSel(0);
	m_ch1.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgInsertIMG::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
}


void CDlgInsertIMG::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
}


void CDlgInsertIMG::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
}

void CDlgInsertIMG::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_e2.SetWindowText(fileName);
		m_e3.SetWindowText(toSl(shorten(fileName)));
	}
}


void CDlgInsertIMG::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_e6.SetWindowText(fileName);
	}
}


void CDlgInsertIMG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos;
	if(m_ch1.GetCheck()){
		pos = dlg->crtIMGid;
	}else if(m_ch2.GetCheck()){
		pos = dlg->crtIMGid+1;
	}else{
		pos = dlg->no.count;
	}
	CString fileName;
	str fn;
	IMGversion iv[4] = {V2,V4,V5,V6};
	IMGobject io;
	switch(m_c1.GetCurSel()){
	case 0:
		m_e1.GetWindowText(fileName);
		CStrToStr(fileName, fn);
		io.create(iv[m_c3.GetCurSel()]);
		dlg->no.IMGinsert(pos, io, fn);
		dlg->m_lIMG.InsertItem(pos,shorten(fileName),dlg->getIconIMG(io.version));
		io.release();
		break;
	case 1:
		m_e2.GetWindowText(fileName);
		CStrToStr(fileName, fn);
		io.loadFile(fn);
		m_e3.GetWindowText(fileName);
		CStrToStr(fileName, fn);
		dlg->no.IMGinsert(pos, io, fn);
		dlg->m_lIMG.InsertItem(pos,shorten(fileName),dlg->getIconIMG(io.version));
		break;
	case 2:
		m_e6.GetWindowText(fileName);
		CStrToStr(fileName,fn);
		dlg->importNPKPara.fileName = fn;
		dlg->importNPKPara.conflictPara = m_c4.GetCurSel();
		::AfxBeginThread(CExRabbitDlg::threadImportNPK, (PVOID)GetParent());
		break;
	}
	dlg->updateNPKInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsertIMG::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CDlgInsertIMG::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c3.EnableWindow(false);
	m_e1.EnableWindow(false);
	m_e2.EnableWindow(false);
	m_e3.EnableWindow(false);
	m_btn1.EnableWindow(false);
	m_e6.EnableWindow(false);
	m_btn7.EnableWindow(false);
	m_c4.EnableWindow(false);
	m_ch1.EnableWindow(true);
	m_ch2.EnableWindow(true);
	m_ch3.EnableWindow(true);
	switch(m_c1.GetCurSel()){
	case 0:
		m_c3.EnableWindow(true);
		m_e1.EnableWindow(true);
		break;
	case 1:
		m_e2.EnableWindow(true);
		m_e3.EnableWindow(true);
		m_btn1.EnableWindow(true);
		break;
	case 2:
		m_e6.EnableWindow(true);
		m_btn7.EnableWindow(true);
		m_c4.EnableWindow(true);
		m_ch1.EnableWindow(false);
		m_ch2.EnableWindow(false);
		m_ch3.EnableWindow(false);
		m_ch1.SetCheck(0);
		m_ch2.SetCheck(0);
		m_ch3.SetCheck(1);
		break;
	}
}
