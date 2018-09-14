// DlgSetXY.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgSetXY.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgSetXY 对话框

IMPLEMENT_DYNAMIC(CDlgSetXY, CDialogEx)

CDlgSetXY::CDlgSetXY(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetXY::IDD, pParent)
{

}

CDlgSetXY::~CDlgSetXY()
{
}

void CDlgSetXY::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
}


BEGIN_MESSAGE_MAP(CDlgSetXY, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgSetXY::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgSetXY::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgSetXY::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgSetXY::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgSetXY::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgSetXY::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgSetXY::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgSetXY::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlgSetXY::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlgSetXY::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CDlgSetXY::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlgSetXY::OnBnClickedButton13)
	ON_BN_CLICKED(IDCANCEL, &CDlgSetXY::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSetXY 消息处理程序


void CDlgSetXY::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_X(pt.get_X()-100);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_X(pt.get_X()-10);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_X(pt.get_X()-1);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_X(pt.get_X()+1);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_X(pt.get_X()+10);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_X(pt.get_X()+100);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_Y(pt.get_Y()-100);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_Y(pt.get_Y()-10);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_Y(pt.get_Y()-1);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_Y(pt.get_Y()+1);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_Y(pt.get_Y()+10);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	if(pos<0)
		return;
	PICinfo pi;
	point pt;
	dlg->io.PICgetInfo(pos, pi);
	pt = pi.get_basePt();
	pt.set_Y(pt.get_Y()+100);
	dlg->io.PICsetInfoPara(pos, 1, &pt);
	m_e1.SetWindowText(NumToCStr(pt.get_X())+L","+NumToCStr(pt.get_Y()));
	{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	dlg->saveAlert = true;
	if(dlg->drawPara.realAxis)
		dlg->draw();
}


void CDlgSetXY::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
