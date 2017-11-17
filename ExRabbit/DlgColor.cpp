// DlgColor.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgColor.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgColor 对话框

IMPLEMENT_DYNAMIC(CDlgColor, CDialogEx)

CDlgColor::CDlgColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgColor::IDD, pParent)
{

}

CDlgColor::~CDlgColor()
{
}

void CDlgColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_c1);
	DDX_Control(pDX, IDC_SLIDER1, m_s1);
	DDX_Control(pDX, IDC_SLIDER2, m_s2);
	DDX_Control(pDX, IDC_SLIDER3, m_s3);
	DDX_Control(pDX, IDC_STATIC1, m_st1);
	DDX_Control(pDX, IDC_STATIC3, m_st3);
	DDX_Control(pDX, IDC_STATIC2, m_st2);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_EDIT13, m_e3);
}


BEGIN_MESSAGE_MAP(CDlgColor, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgColor::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CDlgColor::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CDlgColor::OnNMReleasedcaptureSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CDlgColor::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CDlgColor::OnNMCustomdrawSlider3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &CDlgColor::OnNMReleasedcaptureSlider2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER3, &CDlgColor::OnNMReleasedcaptureSlider3)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgColor::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgColor::OnBnClickedButton7)
	ON_BN_CLICKED(IDCANCEL, &CDlgColor::OnBnClickedCancel)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_CT_ALL, &CDlgColor::OnCtAll)
	ON_COMMAND(ID_CT_UNALL, &CDlgColor::OnCtUnall)
	ON_COMMAND(ID_CT_REV, &CDlgColor::OnCtRev)
	ON_COMMAND(ID_CT_IMPORTACT, &CDlgColor::OnCtImportAct)
	ON_COMMAND(ID_CT_IMPORTCID, &CDlgColor::OnCtImportCid)
	ON_COMMAND(ID_CT_EXPORTACT, &CDlgColor::OnCtExportAct)
	ON_COMMAND(ID_CT_EXPORTCID, &CDlgColor::OnCtExportCid)
END_MESSAGE_MAP()


// CDlgColor 消息处理程序

void CDlgColor::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(point.x >= 0 && point.y >= 0 && point.x < 320 && point.y < 320){
		CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
		m_s1.SetPos(0);
		m_s2.SetPos(0);
		m_s3.SetPos(0);
		int chosen = point.x/20 + point.y/20*16;
		if(chosen < plc->size()){
			chosenClr[chosen] = !chosenClr[chosen];
			dlg->draw();
			draw();
		}else if(chosen == plc->size()){
			COLORREF sclr = 0;
			CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
			if(cdlg.DoModal() == IDOK){
				sclr = cdlg.GetColor();
				dlg->io.CLRpush(color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)), dlg->m_cbPro.GetCurSel());
				dlg->draw();
				dlg->updateCLRlist();
				draw();
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDlgColor::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(point.x >= 0 && point.y >= 0 && point.x < 320 && point.y < 320){
		CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
		m_s1.SetPos(0);
		m_s2.SetPos(0);
		m_s3.SetPos(0);
		int chosen = point.x/20 + point.y/20*16;
		if(chosen < plc->size()){
			COLORREF sclr = RGB((*plc)[chosen].get_R(),(*plc)[chosen].get_G(),(*plc)[chosen].get_B());
			CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
			if(cdlg.DoModal() == IDOK){
				sclr = cdlg.GetColor();
				dlg->io.CLRreplace(chosen, color((*plc)[chosen].get_A(), GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)), dlg->m_cbPro.GetCurSel());
				dlg->draw();
				dlg->updateCLRlist();
				draw();
			}
		}
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CDlgColor::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(11);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	
	CDialogEx::OnRButtonDown(nFlags, point);
}


BOOL CDlgColor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	plc = NULL;
	for(int i = 0;i<256;i++)
		chosenClr[i] = false;
	m_c1.ResetContent();
	m_c1.AddString(L"HSV调节");
	m_c1.AddString(L"RGB调节");
	m_c1.AddString(L"透明度调节");
	m_c1.SetCurSel(0);
	m_s1.SetRange(-100,100, TRUE);
	m_s2.SetRange(-100,100, TRUE);
	m_s3.SetRange(-100,100, TRUE);
	m_s1.SetPos(0);
	m_s2.SetPos(0);
	m_s3.SetPos(0);
	int i[3] = {m_s1.GetPos(), m_s2.GetPos(), m_s3.GetPos()};
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
int CDlgColor::ptToIndex(const CPoint &pt){
	return pt.x + pt.y*16;
}
CPoint CDlgColor::indexToPt(int i){
	return CPoint(i%16, i/16);
}
void CDlgColor::setClr(lcolor *lclr){
	plc = lclr;
	basePlc = *plc;
	for(int i = 0;i<256;i++)
		chosenClr[i] = false;
}
void CDlgColor::draw(){
	if(!plc)
		return;
	int i,j,k,m;
	color clr;
	matrix canvas(320, 320);
	//先画X表示无颜色
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			//白底
			if(true){
				for(k=0;k<20;k++){
					for(m=0;m<20;m++){
						canvas[20*i+k][20*j+m] = color(0xff,0xff,0xff,0xff);
					}
				}
			}
			//黑线
			for(k=0;k<20;k++){
				canvas[20*i+k][20*j] = color(0xff,0,0,0);
				canvas[20*i][20*j+k] = color(0xff,0,0,0);
				canvas[20*i+k][20*j+19] = color(0xff,0,0,0);
				canvas[20*i+19][20*j+k] = color(0xff,0,0,0);
				canvas[20*i+k][20*j+k] = color(0xff,0,0,0);
				canvas[20*i+k][20*j+19-k] = color(0xff,0,0,0);
			}
		}
	}
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			if(i+16*j < plc->size()){
				clr = (*plc)[i+16*j];
				for(k=0;k<20;k++){
					for(m=0;m<20;m++){
						bool m1 = (k/5 == 1 || k/5 == 3)&&(m/5 == 1 || m/5 == 3)||(k/5 == 2 || k/5 == 0)&&(m/5 == 2 || m/5 == 0);
						if(m1){
							color clr2 = clr;
							clr2.mixWith(color(0xff,0x7f,0x7f,0x7f), LAY);
							canvas[20*i+k][20*j+m] = clr2;
						}else{
							color clr2 = clr;
							clr2.mixWith(color(0xff,0xff,0xff,0xff), LAY);
							canvas[20*i+k][20*j+m] = clr2;
						}
					}
				}
				if(chosenClr[i+16*j]){
					//选定
					for(m=1;m<19;m++){
						canvas[20*i+m][20*j+1] = color(0xff,0xff,0xff,0xff);
						canvas[20*i+m][20*j+18] = color(0xff,0xff,0xff,0xff);
						canvas[20*i+1][20*j+m] = color(0xff,0xff,0xff,0xff);
						canvas[20*i+18][20*j+m] = color(0xff,0xff,0xff,0xff);
					}
					for(m=2;m<18;m++){
						canvas[20*i+m][20*j+2] = color(0xff,0,0,0);
						canvas[20*i+m][20*j+17] = color(0xff,0,0,0);
						canvas[20*i+2][20*j+m] = color(0xff,0,0,0);
						canvas[20*i+17][20*j+m] = color(0xff,0,0,0);
					}
				}
			}
			if(i+16*j == plc->size()){
				for(k=0;k<20;k++){
					for(m=0;m<20;m++){
						canvas[20*i+k][20*j+m] = color(0xff,0xff,0x66,0xff);
					}
				}
				canvas[20*i+2][20*j+12] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+2][20*j+13] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+2][20*j+14] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+2][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+2][20*j+16] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+2][20*j+17] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+3][20*j+13] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+4][20*j+14] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+5][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+6][20*j+12] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+6][20*j+13] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+6][20*j+14] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+6][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+6][20*j+16] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+6][20*j+17] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+8][20*j+14] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+8][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+8][20*j+16] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+9][20*j+13] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+9][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+9][20*j+17] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+10][20*j+13] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+10][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+10][20*j+17] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+11][20*j+14] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+11][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+11][20*j+17] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+13][20*j+13] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+13][20*j+14] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+13][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+13][20*j+16] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+13][20*j+17] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+14][20*j+16] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+15][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+16][20*j+16] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+17][20*j+13] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+17][20*j+14] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+17][20*j+15] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+17][20*j+16] = color(0xff,0xff,0xff,0x99);
				canvas[20*i+17][20*j+17] = color(0xff,0xff,0xff,0x99);
			}
			for(k=0;k<20;k++){
				canvas[20*i+k][20*j] = color(0xff,0,0,0);
				canvas[20*i][20*j+k] = color(0xff,0,0,0);
				canvas[20*i+k][20*j+19] = color(0xff,0,0,0);
				canvas[20*i+19][20*j+k] = color(0xff,0,0,0);
			}
		}
	}
	CImage img;
	img.Create(320, 320, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for(i=0;i<320;i++){
		for(j=0;j<320;j++){
			*(pst + pit*j + 4*i + 0) = canvas[i][j].get_B();
			*(pst + pit*j + 4*i + 1) = canvas[i][j].get_G();
			*(pst + pit*j + 4*i + 2) = canvas[i][j].get_R();
		}
	}
	img.Draw(GetDC()->m_hDC,0,0);
	img.Destroy();
	canvas.release();
}

void CDlgColor::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	basePlc = *plc;
	m_s1.SetPos(0);
	m_s2.SetPos(0);
	m_s3.SetPos(0);
	switch(m_c1.GetCurSel()){
	case 0:
		m_st1.SetWindowText(L"H");
		m_st2.SetWindowText(L"S");
		m_st3.SetWindowText(L"V");
		m_s1.EnableWindow(true);
		m_s3.EnableWindow(true);
		m_e1.SetWindowText(L"0");
		m_e2.SetWindowText(L"0");
		m_e3.SetWindowText(L"0");
		break;
	case 1:
		m_st1.SetWindowText(L"R");
		m_st2.SetWindowText(L"G");
		m_st3.SetWindowText(L"B");
		m_s1.EnableWindow(true);
		m_s3.EnableWindow(true);
		m_e1.SetWindowText(L"0");
		m_e2.SetWindowText(L"0");
		m_e3.SetWindowText(L"0");
		break;
	case 2:
		m_st1.SetWindowText(L"");
		m_st2.SetWindowText(L"α");
		m_st3.SetWindowText(L"");
		m_s1.EnableWindow(false);
		m_s3.EnableWindow(false);
		m_e1.SetWindowText(L"0");
		m_e2.SetWindowText(L"0");
		m_e3.SetWindowText(L"0");
		break;
	}
}


void CDlgColor::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int p1 = m_s1.GetPos();
	m_e1.SetWindowText(NumToCStr(p1));
	*pResult = 0;
}

void CDlgColor::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int p2 = m_s2.GetPos();
	m_e2.SetWindowText(NumToCStr(p2));
	*pResult = 0;
}


void CDlgColor::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int p3 = m_s3.GetPos();
	m_e3.SetWindowText(NumToCStr(p3));
	*pResult = 0;
}


//调节根据basePlc进行，点击其他处将更新basePlc
void CDlgColor::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int p1 = m_s1.GetPos();
	int p2 = m_s2.GetPos();
	int p3 = m_s3.GetPos();
	m_e1.SetWindowText(NumToCStr(p1));
	m_e2.SetWindowText(NumToCStr(p2));
	m_e3.SetWindowText(NumToCStr(p3));
	switch(m_c1.GetCurSel()){
	case 0:
		//HSV
		{
			color clr;
			colorHSV ch;
			for(int i = 0;i<plc->size();i++){
				if(chosenClr[i]){
					clr = basePlc[i];
					clr.getHSV(ch);
					clr.moveH(p1*180/100);
					clr.moveS((p2>=0)?(fl2)p2/100*(1-ch.S):(fl2)p2/100*ch.S);
					clr.moveV((p3>=0)?(fl2)p3/100*(1-ch.V):(fl2)p3/100*ch.V);
					dlg->io.CLRreplace(i, clr, dlg->m_cbPro.GetCurSel());
					dlg->draw();
					draw();
				}
			}
		}
		break;
	case 1:
		//RGB
		{
			color clr;
			for(int i = 0;i<plc->size();i++){
				if(chosenClr[i]){
					clr = basePlc[i];
					clr.moveR((p1>=0)?p1*(0xff-clr.get_R())/100:p1*clr.get_R()/100);
					clr.moveG((p2>=0)?p2*(0xff-clr.get_G())/100:p2*clr.get_G()/100);
					clr.moveB((p3>=0)?p3*(0xff-clr.get_B())/100:p3*clr.get_B()/100);
					dlg->io.CLRreplace(i, clr, dlg->m_cbPro.GetCurSel());
					dlg->draw();
					draw();
				}
			}
		}
		break;
	case 2:
		//alpha
		{
			color clr;
			for(int i = 0;i<plc->size();i++){
				if(chosenClr[i]){
					clr = basePlc[i];
					clr.moveA((p2>=0)?p2*(int)(0xff-clr.get_A())/100:p2*(int)clr.get_A()/100);
					dlg->io.CLRreplace(i, clr, dlg->m_cbPro.GetCurSel());
					dlg->draw();
					draw();
				}
			}
			
		}
		break;
	}
	dlg->saveAlert = true;
	*pResult = 0;
}

void CDlgColor::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	OnNMReleasedcaptureSlider1(pNMHDR, pResult);
}


void CDlgColor::OnNMReleasedcaptureSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	OnNMReleasedcaptureSlider1(pNMHDR, pResult);
}


void CDlgColor::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(12);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
}


void CDlgColor::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(13);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
}


void CDlgColor::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	dlg->useColorTable = false;
	dlg->m_lColor.EnableWindow(true);
	dlg->updateCLRlist();
	ShowWindow(SW_HIDE);;
}



void CDlgColor::OnCtAll()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	for(int i = 0;i<plc->size();i++)
		chosenClr[i] = true;
	dlg->draw();
	draw();
}


void CDlgColor::OnCtUnall()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	for(int i = 0;i<plc->size();i++)
		chosenClr[i] = false;
	dlg->draw();
	draw();
}


void CDlgColor::OnCtRev()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	for(int i = 0;i<plc->size();i++)
		chosenClr[i] = !chosenClr[i];
	dlg->draw();
	draw();
}


void CDlgColor::OnCtImportAct()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int clrID = dlg->m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	CString defExt = _T("Photoshop颜色表(*.act)|*.act");
	CString extFilter = _T("Photoshop颜色表(*.act)|*.act||");
	CFileDialog fdlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	str fn;
	int i,k;
	lcolor lc;
	if(fdlg.DoModal() == IDOK){
		fileName = fdlg.GetPathName();
		CStrToStr(fileName, fn);
		if(!palette::loadACT(fn, lc)){
			MessageBox(L"未识别的调色板文件喵！",L"提示喵");
			return;
		}
		k = dlg->io.paletteData[clrID].size();
		for(i=0;i<k;i++)
			dlg->io.CLRremove(0, clrID);
		for(i=0;i<lc.size();i++){
			dlg->io.CLRpush(lc[i], clrID);
		}
		dlg->saveAlert = true;
		MessageBox(L"读取完毕喵！",L"提示喵");
		dlg->updateInfo();
		dlg->updateNPKInfo();
		dlg->updatePICInfo();
		OnCtUnall();
	}
}


void CDlgColor::OnCtImportCid()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int clrID = dlg->m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	CString defExt = _T("V4调色板(*.cid)|*.cid");
	CString extFilter = _T("V4调色板(*.cid)|*.cid||");
	CFileDialog fdlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	str fn;
	stream s;
	i32 i,j,k;
	b8 b;
	if(fdlg.DoModal() == IDOK){
		fileName = fdlg.GetPathName();
		CStrToStr(fileName, fn);
		if(!s.loadFile(fn)){
			MessageBox(L"无法读取文件喵！",L"提示喵");
			return;
		}
		s.read(i);
		if((b32)i != 0x6F436F4B){
			MessageBox(L"该调色板未能识别喵！",L"提示喵！");
			return;
		}
		s.read(i);
		s.read(i);
		k = dlg->io.paletteData[clrID].size();
		for(j=0;j<k;j++)
			dlg->io.CLRremove(0, clrID);
		for(j=0;j<i;j++){
			color clr;
			s.read(b);
			clr.set_A(b);
			s.read(b);
			clr.set_R(b);
			s.read(b);
			clr.set_G(b);
			s.read(b);
			clr.set_B(b);
			dlg->io.CLRpush(clr, clrID);
		}
		MessageBox(L"读取调色板完毕喵！",L"提示喵");
		dlg->updateNPKInfo();
		dlg->updatePICInfo();
		dlg->saveAlert = true;
		dlg->updateInfo();
		OnCtUnall();
	}
}


void CDlgColor::OnCtExportAct()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int clrID = dlg->m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	str fn;
	CString fileName =  getOutPutDir(dlg->fileNPKname,dlg->fileIMGname) + L"Palette"+NumToCStr(clrID)+L".ACT";
	CStrToStr(fileName, fn);
	palette::makeACT(fn, dlg->io.paletteData[clrID]);
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}


void CDlgColor::OnCtExportCid()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	int clrID = dlg->m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	str fn;
	CString fileName =  getOutPutDir(dlg->fileNPKname,dlg->fileIMGname) + L"Palette"+NumToCStr(clrID)+L".CID";
	CStrToStr(fileName, fn);
	stream s,sHead;
	sHead.allocate(12);
	sHead.push((b32)0x6F436F4B);
	sHead.push((b32)0x72756F6C);
	sHead.push((b32)dlg->io.paletteData[clrID].size());
	s.allocate(12+dlg->io.paletteData[clrID].size()+100);
	s.pushStream(sHead,12);
	for(int i = 0;i<dlg->io.paletteData[clrID].size();i++){
		s.push(dlg->io.paletteData[clrID][i].get_A());
		s.push(dlg->io.paletteData[clrID][i].get_R());
		s.push(dlg->io.paletteData[clrID][i].get_G());
		s.push(dlg->io.paletteData[clrID][i].get_B());
	}
	s.makeFile(fn);
	s.release();
	sHead.release();
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}
