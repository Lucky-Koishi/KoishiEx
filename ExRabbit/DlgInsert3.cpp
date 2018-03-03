// DlgInsert3.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsert3.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgInsert3 对话框

IMPLEMENT_DYNAMIC(CDlgInsert3, CDialogEx)

CDlgInsert3::CDlgInsert3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInsert3::IDD, pParent)
{

}

CDlgInsert3::~CDlgInsert3()
{
}

void CDlgInsert3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_c1);
	DDX_Control(pDX, IDC_CHECK2, m_c2);
	DDX_Control(pDX, IDC_CHECK3, m_c3);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	DDX_Control(pDX, IDC_EDIT1, m_ed1);
}


BEGIN_MESSAGE_MAP(CDlgInsert3, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgInsert3::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgInsert3::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgInsert3::OnBnClickedCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgInsert3::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInsert3::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgInsert3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgInsert3::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgInsert3 消息处理程序


void CDlgInsert3::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(1);
	m_c2.SetCheck(0);
	m_c3.SetCheck(0);
}


void CDlgInsert3::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(0);
	m_c2.SetCheck(1);
	m_c3.SetCheck(0);
}


void CDlgInsert3::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(0);
	m_c2.SetCheck(0);
	m_c3.SetCheck(1);
}


void CDlgInsert3::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	mode = m_cb1.GetCurSel();
}


void CDlgInsert3::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString listExt[2] = {
		_T("dds图像(*.dds)|*.dds"),
		_T("png图像(*.png)|*.png")
	}; 
	listExt[0].LoadStringW(IDS_STRING_DDSTYPE);
	listExt[1].LoadStringW(IDS_STRING_PNGTYPE);
	CString defExt = listExt[mode];
	CString extFilter = listExt[mode] + L"||";
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_ed1.SetWindowText(fileName);
	}
}


void CDlgInsert3::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	CString info, title;
	int pos = 0;
	if(m_c1.GetCheck()){
		pos = dlg->m_lDDS.GetSelectionMark();
	}else if(m_c2.GetCheck()){
		pos = dlg->m_lDDS.GetSelectionMark()+1;
	}else if(m_c3.GetCheck()){
		pos = dlg->io.V5_DDSCount;
	}
	DDSinfo di;
	stream s,s1;
	KoishiDDS::DDS d;
	CString cstr;
	str fn;
	matrix mat;
	switch(mode){
	case 0:
		//dds
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		if(!s1.loadFile(fn)){
			info.LoadStringW(IDS_STRING_FAILEDTOREADFILE);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"无法打开文件喵！",L"提示喵");
			return;
		}
		if(!d.load(s1)){
			info.LoadStringW(IDS_STRING_DDSFILEINVALID);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"DDS文件无效喵！",L"提示喵");
			return;
		}
		s1.compressData(s, COMP_ZLIB);
		di.set_reserved(1);
		switch(d.getHeader()->pixelFormat.fourCC){
		case 0x31545844:
			di.set_fourCCID(DXT1);
			break;
		case 0x33545844:
			di.set_fourCCID(DXT3);
			break;
		case 0x35545844:
			di.set_fourCCID(DXT5);
			break;
		default:
			info.LoadStringW(IDS_STRING_DDSNOTSUPPORTED);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"DDS格式不支持喵！只支持DX1、DXT3和DXT5喵！",L"提示喵");
			return;
		}
		di.set_lengthOfDDS(s1.getLen());
		di.set_lengthOfCompressed(s.getLen());
		di.set_width(d.getHeader()->width);
		di.set_height(d.getHeader()->height);
		if(iORr == __INSERT){
			dlg->io.DDSinsert(pos, di, s);
			info.LoadStringW(IDS_STRING_INSERTDDSFINISHED);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"插入DDS贴图成功喵！",L"提示喵");
		}else{
			dlg->io.DDSreplace(pos, di, s);
			info.LoadStringW(IDS_STRING_REPLACEDDSFINISHED);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"替换DDS贴图成功喵！",L"提示喵");
		}
		break;
	case 1:
		//png
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		if(!mat.loadPNG(fn)){
			info.LoadStringW(IDS_STRING_FAILEDTOREADPNGFILE);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"读取PNG文件失败喵！",L"提示喵");
			return;
		}
		if(!dlg->io.DDSpreprocess(mat, s, di)){
			info.LoadStringW(IDS_STRING_FAILEDTOCONVERTTODDS);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"转换为DDS失败！",L"提示喵");
			return;
		}
		if(iORr == __INSERT){
			dlg->io.DDSinsert(pos, di, s);
			info.LoadStringW(IDS_STRING_INSERTDDSFINISHED);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"插入DDS贴图成功喵！",L"提示喵");
		}else{
			dlg->io.DDSreplace(pos, di, s);
			info.LoadStringW(IDS_STRING_REPLACEDDSFINISHED);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"替换DDS贴图成功喵！",L"提示喵");
		}
		break;
	}
	dlg->updateDDSlist();
	dlg->updateNPKInfo();
	dlg->updateIMGInfo();
	dlg->updatePICInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsert3::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
