// ModalAdjustColor.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAdjustColor.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// ModalAdjustColor 对话框

IMPLEMENT_DYNAMIC(ModalAdjustColor, CDialogEx)

ModalAdjustColor::ModalAdjustColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalAdjustColor::IDD, pParent)
{

}

ModalAdjustColor::~ModalAdjustColor()
{
}

void ModalAdjustColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalAdjustColor, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalAdjustColor::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalAdjustColor::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalAdjustColor::OnBnClickedRadioTarget3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_H, &ModalAdjustColor::OnNMCustomdrawSliderH)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_S, &ModalAdjustColor::OnNMCustomdrawSliderS)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_V, &ModalAdjustColor::OnNMCustomdrawSliderV)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_R, &ModalAdjustColor::OnNMCustomdrawSliderR)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_G, &ModalAdjustColor::OnNMCustomdrawSliderG)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_B, &ModalAdjustColor::OnNMCustomdrawSliderB)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_A, &ModalAdjustColor::OnNMCustomdrawSliderA)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_H, &ModalAdjustColor::OnNMReleasedcaptureSliderH)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_S, &ModalAdjustColor::OnNMReleasedcaptureSliderS)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_V, &ModalAdjustColor::OnNMReleasedcaptureSliderV)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_R, &ModalAdjustColor::OnNMReleasedcaptureSliderR)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_G, &ModalAdjustColor::OnNMReleasedcaptureSliderG)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_B, &ModalAdjustColor::OnNMReleasedcaptureSliderB)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_A, &ModalAdjustColor::OnNMReleasedcaptureSliderA)
	ON_BN_CLICKED(IDOK, &ModalAdjustColor::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ModalAdjustColor::OnBnClickedCancel)
END_MESSAGE_MAP()


// ModalAdjustColor 消息处理程序


BOOL ModalAdjustColor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	out.target = 1;
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	if(in.version == V4 || in.version == V6){
		out.target = 3;
		GET_CTRL(CButton, IDC_RADIO_TARGET3)->SetCheck(1);
		GET_CTRL(CButton, IDC_RADIO_TARGET1)->EnableWindow(0);
		GET_CTRL(CButton, IDC_RADIO_TARGET2)->EnableWindow(0);
	}
	out.H = 0;
	out.S = 0;
	out.V = 0;
	out.R = 0;
	out.G = 0;
	out.B = 0;
	out.a = 0;
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ModalAdjustColor::OnBnClickedRadioTarget1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 1;
}


void ModalAdjustColor::OnBnClickedRadioTarget2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 2;
}


void ModalAdjustColor::OnBnClickedRadioTarget3()
{
	// TODO: 在此添加控件通知处理程序代码
	out.target = 3;
}


void ModalAdjustColor::OnNMCustomdrawSliderH(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_H)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_H)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void ModalAdjustColor::OnNMCustomdrawSliderS(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_S)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_S)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void ModalAdjustColor::OnNMCustomdrawSliderV(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_V)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_V)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void ModalAdjustColor::OnNMCustomdrawSliderR(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_R)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_R)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void ModalAdjustColor::OnNMCustomdrawSliderG(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_G)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_G)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void ModalAdjustColor::OnNMCustomdrawSliderB(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_B)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_B)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void ModalAdjustColor::OnNMCustomdrawSliderA(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int delta = GET_CTRL(CSliderCtrl, IDC_SLIDER_A)->GetPos();
	GET_CTRL(CSliderCtrl, IDC_EDIT_A)->SetWindowText(NumToCStr(delta));
	*pResult = 0;
}


void ModalAdjustColor::OnNMReleasedcaptureSliderH(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void ModalAdjustColor::OnNMReleasedcaptureSliderS(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void ModalAdjustColor::OnNMReleasedcaptureSliderV(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void ModalAdjustColor::OnNMReleasedcaptureSliderR(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void ModalAdjustColor::OnNMReleasedcaptureSliderG(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void ModalAdjustColor::OnNMReleasedcaptureSliderB(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void ModalAdjustColor::OnNMReleasedcaptureSliderA(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	applyEffect();
	*pResult = 0;
}


void ModalAdjustColor::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg*dlg = (CExRabbitDlg*)GetParent();
	dlg->saveAlert = true;
	in.oldV2matrix.destory();
	CDialogEx::OnOK();
}

void ModalAdjustColor::OnBnClickedCancel(){
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg*dlg = (CExRabbitDlg*)GetParent();
	dlg->saveAlert = true;
	for(int i = 0;i<in.oldCl.size();i++){
		color clr = in.oldCl[i];
		if(dlg->io.version == V4 || dlg->io.version == V5 || dlg->io.version == V6){
			dlg->io.CLRreplace(i, clr, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			dlg->cl[i] = clr;
		}else{
			dlg->colorOperatePara.v2Color[i] = clr;
			dlg->cl[i] = clr;
		}
	}
	if(dlg->io.version == V2){
		matrix mat = in.oldV2matrix;
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
	in.oldV2matrix.destory();
	CDialogEx::OnCancel();
}


void ModalAdjustColor::applyEffect(){
	CExRabbitDlg*dlg = (CExRabbitDlg*)GetParent();

	int deltaH = out.H = GET_CTRL(CSliderCtrl, IDC_SLIDER_H)->GetPos();
	int deltaS = out.S = GET_CTRL(CSliderCtrl, IDC_SLIDER_S)->GetPos();
	int deltaV = out.V = GET_CTRL(CSliderCtrl, IDC_SLIDER_V)->GetPos();
	int deltaR = out.R = GET_CTRL(CSliderCtrl, IDC_SLIDER_R)->GetPos();
	int deltaG = out.G = GET_CTRL(CSliderCtrl, IDC_SLIDER_G)->GetPos();
	int deltaB = out.B = GET_CTRL(CSliderCtrl, IDC_SLIDER_B)->GetPos();
	int deltaA = out.a = GET_CTRL(CSliderCtrl, IDC_SLIDER_A)->GetPos();

	for(int i = 0;i<in.oldCl.size();i++){
		color clr = in.oldCl[i];
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
	if(in.version == V2){
		matrix mat = in.oldV2matrix;
		PICinfo pi;
		stream s;
		int ID = dlg->crtPICid;
		dlg->io.PICgetInfo(ID, pi);
		if(pi.format == LINK){
			ID = dlg->io.linkFind(ID);
		}
		for(int i = 0;i<in.oldV2matrix.getElemCount();i++){
			color clr = in.oldV2matrix.getElem(i);
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
