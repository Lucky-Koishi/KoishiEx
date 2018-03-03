// DialogNew.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DialogNew.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDialogNew 对话框

IMPLEMENT_DYNAMIC(CDialogNew, CDialogEx)

CDialogNew::CDialogNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogNew::IDD, pParent)
{

}

CDialogNew::~CDialogNew()
{
}

void CDialogNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
	DDX_Control(pDX, IDC_CHECK2, m_ch2);
	DDX_Control(pDX, IDC_CHECK3, m_ch3);
	DDX_Control(pDX, IDC_CHECK4, m_ch4);
	DDX_Control(pDX, IDC_CHECK7, m_ch5);
	DDX_Control(pDX, IDC_CHECK8, m_ch6);
	DDX_Control(pDX, IDC_EDIT1, m_ed1);
}


BEGIN_MESSAGE_MAP(CDialogNew, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CDialogNew::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDialogNew::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDialogNew::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CDialogNew::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK7, &CDialogNew::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CDialogNew::OnBnClickedCheck8)
	ON_BN_CLICKED(IDOK, &CDialogNew::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogNew::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialogNew 消息处理程序


void CDialogNew::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(true);
	m_ch2.SetCheck(false);
	m_ch3.SetCheck(false);
	m_ch4.SetCheck(false);
	m_ch5.SetCheck(false);
	m_ch6.SetCheck(false);
	CString info = L"新建一个NPK文件。\r\n";
	info += L"新建一个不含有任何IMG的NPK文件，您需要自行添加所需要的外部IMG文件。";
	info.LoadStringW(IDS_STRING_CREATENPKINFO);
	m_ed1.SetWindowText(info);
}


void CDialogNew::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(false);
	m_ch2.SetCheck(true);
	m_ch3.SetCheck(false);
	m_ch4.SetCheck(false);
	m_ch5.SetCheck(false);
	m_ch6.SetCheck(false);
	CString info = L"新建一个拼合方案。\r\n";
	info += L"拼合方案是类似于NPK的一种结构，不同的是，系统将视其内部IMG为图层，从而按照IMG顺序显示所有贴图。\r\n";
	info += L"您可以像IMG那样调整每个图层的信息，然后通过浏览来确定最后拼合的效果。\r\n";
	info.LoadStringW(IDS_STRING_CREATEMERGEINFO);
	m_ed1.SetWindowText(info);
}


void CDialogNew::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(false);
	m_ch2.SetCheck(false);
	m_ch3.SetCheck(true);
	m_ch4.SetCheck(false);
	m_ch5.SetCheck(false);
	m_ch6.SetCheck(false);
	CString info = L"新建一个版本号为2的IMG文件。\r\n";
	info += L"V2是适用程度最广的IMG文件，可以存储任意类型的图片，但占空间较大。\r\n";
	info += L"您可以使用V2进行图像添加、替换、拼合等操作，并且除非是计算机环境或软件自身因素导致，执行是一定成功的。\r\n";
	info += L"您即将建立一个V2的IMG文件，您需要自行添加贴图文件。";
	info.LoadStringW(IDS_STRING_CREATEV2IMG);
	m_ed1.SetWindowText(info);
}


void CDialogNew::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(false);
	m_ch2.SetCheck(false);
	m_ch3.SetCheck(false);
	m_ch4.SetCheck(true);
	m_ch5.SetCheck(false);
	m_ch6.SetCheck(false);
	CString info = L"新建一个版本号为4的IMG文件。\r\n";
	info += L"V4是时装适用的IMG文件，以调色板索引方式存储图像。\r\n";
	info += L"您可以使用V4进行颜色编辑等操作，添加贴图操作也同样支持，但插入贴图颜色过多的话则会执行失败。\r\n";
	info += L"您即将建立一个V4的IMG文件，您需要自行添加贴图文件和调色板信息，我们建议您使用索引方式添加贴图。";
	info.LoadStringW(IDS_STRING_CREATEV4IMG);
	m_ed1.SetWindowText(info);
}


void CDialogNew::OnBnClickedCheck7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(false);
	m_ch2.SetCheck(false);
	m_ch3.SetCheck(false);
	m_ch4.SetCheck(false);
	m_ch5.SetCheck(true);
	m_ch6.SetCheck(false);
	CString info = L"新建一个版本号为5的IMG文件。\r\n";
	info += L"V5是大部分技能特效适用的IMG文件，以DDS格式存储大图像并且以区域引用方式转换成每个图片帧的小图像。\r\n";
	info += L"您可以使用V5文件进行DDS操作，建议您使用现成的DDS贴图进行添加、替换操作，本作支持将PNG贴图转化为DDS但会严重失真，应慎用。\r\n";
	info += L"您即将建立一个V5的IMG文件，您需要自行添加DDS贴图，并通过设置引用DDS标号以及范围来创建普通的帧贴图。";
	info.LoadStringW(IDS_STRING_CREATEV5IMG);
	m_ed1.SetWindowText(info);
}


void CDialogNew::OnBnClickedCheck8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(false);
	m_ch2.SetCheck(false);
	m_ch3.SetCheck(false);
	m_ch4.SetCheck(false);
	m_ch5.SetCheck(false);
	m_ch6.SetCheck(true);
	CString info = L"新建一个版本号为6的IMG文件。\r\n";
	info += L"V6是索引数据相同但调色板不同的若干V4结合而成的组合体，被广泛应用于多种颜色版本的时装文件。\r\n";
	info += L"您可以使用V6文件进行颜色操作，操作方式跟V4类似，使用V6可以制作与一个V4相同形状但不同颜色款式的IMG。\r\n";
	info += L"您即将建立一个V6的IMG文件，您需要自行添加颜色方案，并可以像V4那样操作它，但鉴于效率问题，您不能使用添加贴图功能。";
	info.LoadStringW(IDS_STRING_CREATEV6IMG);
	m_ed1.SetWindowText(info);
}


void CDialogNew::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg*dlg = (CExRabbitDlg*)GetParent();
	if(m_ch1.GetCheck()){
		dlg->no.release();
		dlg->no.create();
		dlg->fileNPKname = L"newNPK.npk";
		dlg->fileOpen = true;
		dlg->mixMode = false;
		dlg->updateIMGlist();
	}else if(m_ch2.GetCheck()){
		//施工中
		dlg->no.release();
		dlg->no.create();
		dlg->fileNPKname = L"new_mix_plan.mpl";
		dlg->fileOpen = true;
		dlg->mixMode = true;
		dlg->updateIMGlist();
	}else if(m_ch3.GetCheck()){
		dlg->no.release();
		dlg->no.create();
		dlg->io.Release();
		dlg->io.Create(V2);
		dlg->fileIMGname = L"newV2.img";
		dlg->fileNPKname = L"newNPK.npk";
		dlg->fileOpen = true;
		dlg->mixMode = false;
		dlg->no.IMGpush(dlg->io, "new.img");
		dlg->switchIMGver(dlg->io.version);
		dlg->updateIMGlist();
		dlg->updatePIClist();
		dlg->updateCLRlist();
		dlg->updateDDSlist();
		dlg->updateNPKInfo();
		dlg->updateIMGInfo();
		dlg->updatePICInfo();
	}else if(m_ch4.GetCheck()){
		dlg->no.release();
		dlg->no.create();
		dlg->io.Release();
		dlg->io.Create(V4);
		dlg->fileIMGname = L"newV4.img";
		dlg->fileNPKname = L"newNPK.npk";
		dlg->fileOpen = true;
		dlg->mixMode = false;
		dlg->no.IMGpush(dlg->io, "new.img");
		dlg->switchIMGver(dlg->io.version);
		dlg->updateIMGlist();
		dlg->updatePIClist();
		dlg->updateCLRlist();
		dlg->updateDDSlist();
		dlg->updateNPKInfo();
		dlg->updateIMGInfo();
		dlg->updatePICInfo();
	}else if(m_ch5.GetCheck()){
		dlg->no.release();
		dlg->no.create();
		dlg->io.Release();
		dlg->io.Create(V5);
		dlg->fileIMGname = L"newV5.img";
		dlg->fileNPKname = L"newNPK.npk";
		dlg->fileOpen = true;
		dlg->mixMode = false;
		dlg->no.IMGpush(dlg->io, "new.img");
		dlg->switchIMGver(dlg->io.version);
		dlg->updateIMGlist();
		dlg->updatePIClist();
		dlg->updateCLRlist();
		dlg->updateDDSlist();
		dlg->updateNPKInfo();
		dlg->updateIMGInfo();
		dlg->updatePICInfo();
	}else if(m_ch6.GetCheck()){
		dlg->no.release();
		dlg->no.create();
		dlg->io.Release();
		dlg->io.Create(V6);
		dlg->fileIMGname = L"newV6.img";
		dlg->fileNPKname = L"newNPK.npk";
		dlg->fileOpen = true;
		dlg->mixMode = false;
		dlg->no.IMGpush(dlg->io, "new.img");
		dlg->io.CLRnewPalette();
		dlg->switchIMGver(dlg->io.version);
		dlg->m_cbPro.ResetContent();
		//dlg->m_cbPro.AddString(L"调色板方案0");
		CString cbProText;
		cbProText.LoadStringW(IDS_STRING_PALETTE0);
		dlg->m_cbPro.AddString(cbProText);
		dlg->m_cbPro.SetCurSel(0);
		dlg->updateIMGlist();
		dlg->updatePIClist();
		dlg->updateCLRlist();
		dlg->updateDDSlist();
		dlg->updateNPKInfo();
		dlg->updateIMGInfo();
		dlg->updatePICInfo();
	}
	dlg->m_lIMG.SetSelectionMark(0);
	dlg->crtIMGid = 0;
	ShowWindow(SW_HIDE);
}


void CDialogNew::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
