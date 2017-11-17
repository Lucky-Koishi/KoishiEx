// DlgHSV.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgHSV.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgHSV 对话框

IMPLEMENT_DYNAMIC(CDlgHSV, CDialogEx)

CDlgHSV::CDlgHSV(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgHSV::IDD, pParent)
{

}

CDlgHSV::~CDlgHSV()
{
}

void CDlgHSV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_chHSV);
	DDX_Control(pDX, IDC_CHECK2, m_chRGB);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_EDIT13, m_e3);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SLIDER1, m_s1);
	DDX_Control(pDX, IDC_SLIDER2, m_s2);
	DDX_Control(pDX, IDC_SLIDER3, m_s3);
}


BEGIN_MESSAGE_MAP(CDlgHSV, CDialogEx)
	
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CDlgHSV::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CDlgHSV::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CDlgHSV::OnNMCustomdrawSlider3)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgHSV::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgHSV::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgHSV::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CDlgHSV::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgHSV::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgHSV::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CDlgHSV 消息处理程序


BOOL CDlgHSV::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDlgHSV::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int p1 = m_s1.GetPos();
	int p2 = m_s2.GetPos();
	int p3 = m_s3.GetPos();
	if(m_chHSV.GetCheck()){
		m_e1.SetWindowText(L"H:"+NumToCStr(p1));
		int iCount = m_list.GetSelCount();
		CArray<int,int> selected;
		selected.SetSize(iCount);
		m_list.GetSelItems(iCount, selected.GetData()); //获得所有被选中的索引
		color clr;
		for(int i = 0;i<iCount;i++){
			clr = midClrList[selected[i]];
			clr.moveH(p1);
			clr.moveS((fl2)p2/100);
			clr.moveV((fl2)p3/100);
			newClrList[selected[i]] = clr;
		}
	}else{
		m_e1.SetWindowText(L"R:"+NumToCStr(p1));
		int iCount = m_list.GetSelCount();
		CArray<int,int> selected;
		selected.SetSize(iCount);
		m_list.GetSelItems(iCount, selected.GetData()); //获得所有被选中的索引
		color clr;
		for(int i = 0;i<iCount;i++){
			clr = midClrList[selected[i]];
			clr.moveR(p1);
			clr.moveG(p2);
			clr.moveB(p3);
			newClrList[selected[i]] = clr;
		}
	}
	draw();
	*pResult = 0;
}


void CDlgHSV::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int p1 = m_s1.GetPos();
	int p2 = m_s2.GetPos();
	int p3 = m_s3.GetPos();
	if(m_chHSV.GetCheck()){
		m_e2.SetWindowText(L"S:"+NumToCStr(p2));
		int iCount = m_list.GetSelCount();
		CArray<int,int> selected;
		selected.SetSize(iCount);
		m_list.GetSelItems(iCount, selected.GetData()); //获得所有被选中的索引
		color clr;
		for(int i = 0;i<iCount;i++){
			clr = midClrList[selected[i]];
			clr.moveH(p1);
			clr.moveS((fl2)p2/100);
			clr.moveV((fl2)p3/100);
			newClrList[selected[i]] = clr;
		}
	}else{
		m_e2.SetWindowText(L"G:"+NumToCStr(p2));
		int iCount = m_list.GetSelCount();
		CArray<int,int> selected;
		selected.SetSize(iCount);
		m_list.GetSelItems(iCount, selected.GetData()); //获得所有被选中的索引
		color clr;
		for(int i = 0;i<iCount;i++){
			clr = midClrList[selected[i]];
			clr.moveR(p1);
			clr.moveG(p2);
			clr.moveB(p3);
			newClrList[selected[i]] = clr;
		}
	}
	draw();
	*pResult = 0;
}


void CDlgHSV::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int p1 = m_s1.GetPos();
	int p2 = m_s2.GetPos();
	int p3 = m_s3.GetPos();
	if(m_chHSV.GetCheck()){
		m_e3.SetWindowText(L"V:"+NumToCStr(p3));
		int iCount = m_list.GetSelCount();
		CArray<int,int> selected;
		selected.SetSize(iCount);
		m_list.GetSelItems(iCount, selected.GetData()); //获得所有被选中的索引
		color clr;
		for(int i = 0;i<iCount;i++){
			clr = midClrList[selected[i]];
			clr.moveH(p1);
			clr.moveS((fl2)p2/100);
			clr.moveV((fl2)p3/100);
			newClrList[selected[i]] = clr;
		}
	}else{
		m_e3.SetWindowText(L"B:"+NumToCStr(p3));
		int iCount = m_list.GetSelCount();
		CArray<int,int> selected;
		selected.SetSize(iCount);
		m_list.GetSelItems(iCount, selected.GetData()); //获得所有被选中的索引
		color clr;
		for(int i = 0;i<iCount;i++){
			clr = midClrList[selected[i]];
			clr.moveR(p1);
			clr.moveG(p2);
			clr.moveB(p3);
			newClrList[selected[i]] = clr;
		}
	}
	draw();
	*pResult = 0;
}


void CDlgHSV::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	midClrList.clear();
	for(int i = 0;i<oldClrList.size();i++){
		midClrList.push_back(newClrList[i]);
	}
	draw();
	m_s1.SetPos(0);
	m_s2.SetPos(0);
	m_s3.SetPos(0);
}

void CDlgHSV::draw(){
	int i,j,k;
	CImage img;
	img.Create(450, 30, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();

	for(i=0;i<450;i++){
		for(j=0;j<30;j++){
			*(pst + pit*j + 4*i + 0) = 0X33;
			*(pst + pit*j + 4*i + 1) = 0X33;
			*(pst + pit*j + 4*i + 2) = 0X33;
		}
	}
	for(i=0;i<450;i++){
		for(j=0;j<30;j++){
			k = i/15 + firstpos;
			if(k<oldClrList.size()){
				if(j<10){
					*(pst + pit*j + 4*i + 0) = oldClrList[k].get_B();
					*(pst + pit*j + 4*i + 1) = oldClrList[k].get_G();
					*(pst + pit*j + 4*i + 2) = oldClrList[k].get_R();
				}else if(j<20){
					*(pst + pit*j + 4*i + 0) = midClrList[k].get_B();
					*(pst + pit*j + 4*i + 1) = midClrList[k].get_G();
					*(pst + pit*j + 4*i + 2) = midClrList[k].get_R();
				}else{
					*(pst + pit*j + 4*i + 0) = newClrList[k].get_B();
					*(pst + pit*j + 4*i + 1) = newClrList[k].get_G();
					*(pst + pit*j + 4*i + 2) = newClrList[k].get_R();
				}
			}
		}
	}
	int iCount = m_list.GetSelCount();
	CArray<int,int> selected;
	selected.SetSize(iCount);
	m_list.GetSelItems(iCount, selected.GetData()); //获得所有被选中的索引
	color clr;
	int k1;
	for(k = 0;k<iCount;k++){
		k1 = selected[k]-firstpos;
		if(k1>=0 && k1<30){
			for(i=k1*15;i<k1*15+15;i++){
				for(j=0;j<30;j++){
					if(j == 0||j == 3||j ==26||j==29){
						*(pst + pit*j + 4*i + 0) = 0;
						*(pst + pit*j + 4*i + 1) = 0;
						*(pst + pit*j + 4*i + 2) = 0;
					}
					if(j == 1||j == 2||j ==28||j==27){
						*(pst + pit*j + 4*i + 0) = 0XFF;
						*(pst + pit*j + 4*i + 1) = 0XFF;
						*(pst + pit*j + 4*i + 2) = 0XFF;
					}
				}
			}
		}
	}
	////////////////////////
	
	img.Draw(GetDC()->m_hDC,37,8);
	img.Destroy();
}

void CDlgHSV::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(firstpos>0){
		firstpos -- ;
	}
	draw();
}


void CDlgHSV::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(oldClrList.size()>30 && firstpos<oldClrList.size()-30){
		firstpos ++ ;
	}
	draw();
}


void CDlgHSV::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	midClrList.clear();
	for(i = 0;i<oldClrList.size();i++){
		midClrList.push_back(newClrList[i]);
	}
	draw();
	m_s1.SetPos(0);
	m_s2.SetPos(0);
	m_s3.SetPos(0);
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int clrID = dlg->m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	for(i=0;i<dlg->io.paletteData[clrID].size();i++){
		dlg->io.CLRreplace(i, midClrList[i], clrID);
	}
	dlg->updateCLRlist();
	dlg->updateNPKInfo();
	dlg->updateIMGInfo();
	dlg->updatePICInfo();
	dlg->draw();
}


void CDlgHSV::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_chHSV.SetCheck(1);
	m_chRGB.SetCheck(0);
	int i;
	midClrList.clear();
	for(i = 0;i<oldClrList.size();i++){
		midClrList.push_back(newClrList[i]);
	}
	draw();
}


void CDlgHSV::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_chHSV.SetCheck(0);
	m_chRGB.SetCheck(1);
	int i;
	midClrList.clear();
	for(i = 0;i<oldClrList.size();i++){
		midClrList.push_back(newClrList[i]);
	}
	draw();
	m_e1.SetWindowText(L"R:0");
	m_e2.SetWindowText(L"G:0");
	m_e3.SetWindowText(L"B:0");
	m_s1.SetRange(-255,255);
	m_s2.SetRange(-255,255);
	m_s3.SetRange(-255,255);
	m_s1.SetTic(510);
	m_s2.SetTic(510);
	m_s3.SetTic(510);
	m_s1.SetTicFreq(15);
	m_s2.SetTicFreq(15);
	m_s3.SetTicFreq(15);
	m_s1.SetPos(0);
	m_s2.SetPos(0);
	m_s3.SetPos(0);
}
