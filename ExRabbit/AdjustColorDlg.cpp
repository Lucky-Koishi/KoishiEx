// AdjustColorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "AdjustColorDlg.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CAdjustColorDlg 对话框

IMPLEMENT_DYNAMIC(CAdjustColorDlg, CDialogEx)

CAdjustColorDlg::CAdjustColorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdjustColorDlg::IDD, pParent){

}

CAdjustColorDlg::~CAdjustColorDlg(){
}

void CAdjustColorDlg::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdjustColorDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_H, &CAdjustColorDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_S, &CAdjustColorDlg::OnNMCustomdrawSliderS)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_V, &CAdjustColorDlg::OnNMCustomdrawSliderV)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_R, &CAdjustColorDlg::OnNMCustomdrawSliderR)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_G, &CAdjustColorDlg::OnNMCustomdrawSliderG)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_B, &CAdjustColorDlg::OnNMCustomdrawSliderB)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_A, &CAdjustColorDlg::OnNMCustomdrawSliderA)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdjustColorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdjustColorDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_H, &CAdjustColorDlg::OnNMReleasedcaptureSliderH)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_S, &CAdjustColorDlg::OnNMReleasedcaptureSliderS)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_V, &CAdjustColorDlg::OnNMReleasedcaptureSliderV)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_R, &CAdjustColorDlg::OnNMReleasedcaptureSliderR)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_G, &CAdjustColorDlg::OnNMReleasedcaptureSliderG)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_B, &CAdjustColorDlg::OnNMReleasedcaptureSliderB)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_A, &CAdjustColorDlg::OnNMReleasedcaptureSliderA)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_H, &CAdjustColorDlg::OnNMCustomdrawSliderH)
END_MESSAGE_MAP()


// CAdjustColorDlg 消息处理程序


BOOL CAdjustColorDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	resetSlider();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAdjustColorDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_H)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_H)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void CAdjustColorDlg::OnNMCustomdrawSliderS(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_S)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_S)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void CAdjustColorDlg::OnNMCustomdrawSliderV(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_V)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_V)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void CAdjustColorDlg::OnNMCustomdrawSliderR(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_R)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_R)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void CAdjustColorDlg::OnNMCustomdrawSliderG(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_G)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_G)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void CAdjustColorDlg::OnNMCustomdrawSliderB(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_B)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_B)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void CAdjustColorDlg::OnNMCustomdrawSliderA(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_A)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_A)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}
void CAdjustColorDlg::resetSlider(){
	H = 0;
	S = 0;
	V = 0;
	R = 0;
	G = 0;
	B = 0;
	a = 0;
	GET_CTRL(CSliderCtrl, IDC_SLIDER_H)->SetRange(-100, 100, TRUE);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_S)->SetRange(-100, 100, TRUE);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_V)->SetRange(-100, 100, TRUE);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_R)->SetRange(-100, 100, TRUE);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_G)->SetRange(-100, 100, TRUE);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_B)->SetRange(-100, 100, TRUE);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_A)->SetRange(-100, 100, TRUE);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_H)->SetPos(0);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_S)->SetPos(0);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_V)->SetPos(0);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_R)->SetPos(0);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_G)->SetPos(0);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_B)->SetPos(0);
	GET_CTRL(CSliderCtrl, IDC_SLIDER_A)->SetPos(0);
	GET_CTRL(CSliderCtrl, IDC_EDIT_H)->SetWindowText(L"0");
	GET_CTRL(CSliderCtrl, IDC_EDIT_S)->SetWindowText(L"0");
	GET_CTRL(CSliderCtrl, IDC_EDIT_V)->SetWindowText(L"0");
	GET_CTRL(CSliderCtrl, IDC_EDIT_R)->SetWindowText(L"0");
	GET_CTRL(CSliderCtrl, IDC_EDIT_G)->SetWindowText(L"0");
	GET_CTRL(CSliderCtrl, IDC_EDIT_B)->SetWindowText(L"0");
	GET_CTRL(CSliderCtrl, IDC_EDIT_A)->SetWindowText(L"0");
}
void CAdjustColorDlg::applyEffect(){
	CExRabbitDlg*dlg = (CExRabbitDlg*)GetParent();
	int deltaH = GET_CTRL(CSliderCtrl, IDC_SLIDER_H)->GetPos();
	int deltaS = GET_CTRL(CSliderCtrl, IDC_SLIDER_S)->GetPos();
	int deltaV = GET_CTRL(CSliderCtrl, IDC_SLIDER_V)->GetPos();
	int deltaR = GET_CTRL(CSliderCtrl, IDC_SLIDER_R)->GetPos();
	int deltaG = GET_CTRL(CSliderCtrl, IDC_SLIDER_G)->GetPos();
	int deltaB = GET_CTRL(CSliderCtrl, IDC_SLIDER_B)->GetPos();
	int deltaA = GET_CTRL(CSliderCtrl, IDC_SLIDER_A)->GetPos();

	for(int i = 0;i<oldCl.size();i++){
		if(dlg->colorOperatePara.isChosen[i]){
			color clr = oldCl[i];
			colorHSV ch;
			clr.getHSV(ch);
			clr.moveH(deltaH*180/100);
			clr.moveS((deltaS>=0)?(double)deltaS/100*(1-ch.S):(double)deltaS/100*ch.S);
			clr.moveV((deltaV>=0)?(double)deltaV/100*(1-ch.V):(double)deltaV/100*ch.V);
			clr.moveR((deltaR>=0)?deltaR*(0xff-clr.R)/100:deltaR*clr.R/100);
			clr.moveG((deltaR>=0)?deltaG*(0xff-clr.G)/100:deltaG*clr.G/100);
			clr.moveB((deltaR>=0)?deltaB*(0xff-clr.B)/100:deltaB*clr.B/100);
			clr.moveA((deltaA>=0)?deltaA*(0xff-clr.alpha)/100:deltaA*clr.alpha/100);
			if(dlg->io.version == V4 || dlg->io.version == V5 || dlg->io.version == V6){
				dlg->io.CLRreplace(i, clr, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
				dlg->cl[i] = clr;
			}else{
				dlg->colorOperatePara.v2Color[i] = clr;
				dlg->cl[i] = clr;
			}
		}
	}
	if(dlg->io.version == V2){
		image mat = oldV2matrix;
		PICinfo pi;
		stream s;
		int ID = dlg->crtPICid;
		dlg->io.PICgetInfo(dlg->io.linkFind(ID), pi);
		for(int i = 0;i<oldV2matrix.getElemCount();i++){
			color clr = oldV2matrix.getElem(i);
			colorHSV ch;
			clr.getHSV(ch);
			clr.moveH(deltaH*180/100);
			clr.moveS((deltaS>=0)?(double)deltaS/100*(1-ch.S):(double)deltaS/100*ch.S);
			clr.moveV((deltaV>=0)?(double)deltaV/100*(1-ch.V):(double)deltaV/100*ch.V);
			clr.moveR((deltaR>=0)?deltaR*(0xff-clr.R)/100:deltaR*clr.R/100);
			clr.moveG((deltaR>=0)?deltaG*(0xff-clr.G)/100:deltaG*clr.G/100);
			clr.moveB((deltaR>=0)?deltaB*(0xff-clr.B)/100:deltaB*clr.B/100);
			clr.moveA((deltaA>=0)?deltaA*(0xff-clr.alpha)/100:deltaA*clr.alpha/100);
			mat.setElem(i, clr);
		}
		dlg->io.PICpreprocess(mat, s, pi, pi.format);
		dlg->io.PICreplace(ID, pi, s);
		mat.destory();
		s.release();
	}
	dlg->updateColorTable();
	dlg->draw();
}
void CAdjustColorDlg::OnBnClickedButton2(){
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg*dlg = (CExRabbitDlg*)GetParent();
	dlg->updateModified();
	resetSlider();
	oldV2matrix.destory();
	CDialogEx::OnOK();
}
void CAdjustColorDlg::OnBnClickedButton3(){
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg*dlg = (CExRabbitDlg*)GetParent();
	dlg->updateModified();
	resetSlider();
	for(int i = 0;i<oldCl.size();i++){
		if(dlg->colorOperatePara.isChosen[i]){
			color clr = oldCl[i];
			if(dlg->io.version == V4 || dlg->io.version == V5 || dlg->io.version == V6){
				dlg->io.CLRreplace(i, clr, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
				dlg->cl[i] = clr;
			}else{
				dlg->colorOperatePara.v2Color[i] = clr;
				dlg->cl[i] = clr;
			}
		}
	}

	if(dlg->io.version == V2){
		image mat = oldV2matrix;
		PICinfo pi;
		stream s;
		int ID = dlg->crtPICid;
		dlg->io.PICgetInfo(ID, pi);
		if(pi.format == LINK){
			ID = dlg->io.linkFind(ID);
		}
		dlg->io.PICpreprocess(mat, s, pi, pi.format);
		dlg->io.PICreplace(ID, pi, s);
		mat.destory();
		s.release();
	}
	dlg->updateColorTable();
	dlg->draw();
	oldV2matrix.destory();
	CDialogEx::OnCancel();
}


void CAdjustColorDlg::OnNMReleasedcaptureSliderH(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void CAdjustColorDlg::OnNMReleasedcaptureSliderS(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void CAdjustColorDlg::OnNMReleasedcaptureSliderV(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void CAdjustColorDlg::OnNMReleasedcaptureSliderR(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void CAdjustColorDlg::OnNMReleasedcaptureSliderG(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void CAdjustColorDlg::OnNMReleasedcaptureSliderB(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void CAdjustColorDlg::OnNMReleasedcaptureSliderA(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void CAdjustColorDlg::OnNMCustomdrawSliderH(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
