// DlgExpand.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgExpand.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgExpand 对话框

IMPLEMENT_DYNAMIC(CDlgExpand, CDialogEx)

CDlgExpand::CDlgExpand(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgExpand::IDD, pParent)
{

}

CDlgExpand::~CDlgExpand()
{
}

void CDlgExpand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_A1, m_a1);
	DDX_Control(pDX, IDC_EDIT_A2, m_a2);
	DDX_Control(pDX, IDC_EDIT_A3, m_a3);
	DDX_Control(pDX, IDC_EDIT_A4, m_a4);
	DDX_Control(pDX, IDC_EDIT_A5, m_a5);
	DDX_Control(pDX, IDC_EDIT_A6, m_a6);
	DDX_Control(pDX, IDC_EDIT_B1, m_b1);
	DDX_Control(pDX, IDC_EDIT_B2, m_b2);
	DDX_Control(pDX, IDC_EDIT_B3, m_b3);
	DDX_Control(pDX, IDC_EDIT_B4, m_b4);
	DDX_Control(pDX, IDC_EDIT_B5, m_b5);
	DDX_Control(pDX, IDC_EDIT_B6, m_b6);
	DDX_Control(pDX, IDC_EDIT_C1, m_c1);
	DDX_Control(pDX, IDC_EDIT_C2, m_c2);
	DDX_Control(pDX, IDC_EDIT_C3, m_c3);
	DDX_Control(pDX, IDC_EDIT_C4, m_c4);
	DDX_Control(pDX, IDC_STATIC_S1, m_s1);
	DDX_Control(pDX, IDC_STATIC_S2, m_s2);
	DDX_Control(pDX, IDC_STATIC_S3, m_s3);
	DDX_Control(pDX, IDC_STATIC_S4, m_s4);
	DDX_Control(pDX, IDC_COMBO2, m_cb);
}


BEGIN_MESSAGE_MAP(CDlgExpand, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDlgExpand::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDOK, &CDlgExpand::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgExpand::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgExpand 消息处理程序


BOOL CDlgExpand::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cb.ResetContent();
	m_cb.AddString(L"扩充当前帧");
	m_cb.AddString(L"裁切当前帧");
	m_cb.AddString(L"修整当前帧");
	m_cb.AddString(L"根据坐标扩充/裁切当前帧");
	m_cb.AddString(L"根据坐标扩充/裁切所有帧");
	m_cb.AddString(L"修整所有帧");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgExpand::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.EnableWindow(true);
	m_c2.EnableWindow(true);
	m_c3.EnableWindow(true);
	m_c4.EnableWindow(true);
	CString cstr1,cstr2,cstr3,cstr4,cstr5,cstr6,cstr7,cstr8;
	m_a1.GetWindowText(cstr1);
	m_a2.GetWindowText(cstr2);
	m_a3.GetWindowText(cstr3);
	m_a4.GetWindowText(cstr4);
	m_b1.GetWindowText(cstr5);
	m_b2.GetWindowText(cstr6);
	m_b3.GetWindowText(cstr7);
	m_b4.GetWindowText(cstr8);
	switch(m_cb.GetCurSel()){
	case 0:
		m_s1.SetWindowText(L"向左扩充px");
		m_s2.SetWindowText(L"向上扩充px");
		m_s3.SetWindowText(L"向右扩充px");
		m_s4.SetWindowText(L"向下扩充px");
		m_c1.SetWindowText(L"0");
		m_c2.SetWindowText(L"0");
		m_c3.SetWindowText(L"0");
		m_c4.SetWindowText(L"0");
		break;
	case 1:
		m_s1.SetWindowText(L"左边裁切px");
		m_s2.SetWindowText(L"上边裁切px");
		m_s3.SetWindowText(L"右边裁切px");
		m_s4.SetWindowText(L"下边裁切px");
		m_c1.SetWindowText(L"0");
		m_c2.SetWindowText(L"0");
		m_c3.SetWindowText(L"0");
		m_c4.SetWindowText(L"0");
		break;
	case 2:
		m_c1.EnableWindow(false);
		m_c2.EnableWindow(false);
		m_c3.EnableWindow(false);
		m_c4.EnableWindow(false);
		m_c1.SetWindowText(L"");
		m_c2.SetWindowText(L"");
		m_c3.SetWindowText(L"");
		m_c4.SetWindowText(L"");
		break;
	case 3:
		m_s1.SetWindowText(L"左上X坐标");
		m_s2.SetWindowText(L"左上Y坐标");
		m_s3.SetWindowText(L"右下X坐标");
		m_s4.SetWindowText(L"右下Y坐标");
		m_c1.SetWindowText(cstr1);
		m_c2.SetWindowText(cstr2);
		m_c3.SetWindowText(cstr3);
		m_c4.SetWindowText(cstr4);
		break;
	case 4:
		m_s1.SetWindowText(L"左上X坐标");
		m_s2.SetWindowText(L"左上Y坐标");
		m_s3.SetWindowText(L"右下X坐标");
		m_s4.SetWindowText(L"右下Y坐标");
		m_c1.SetWindowText(cstr5);
		m_c2.SetWindowText(cstr6);
		m_c3.SetWindowText(cstr7);
		m_c4.SetWindowText(cstr8);
		break;
	case 5:
		m_c1.EnableWindow(false);
		m_c2.EnableWindow(false);
		m_c3.EnableWindow(false);
		m_c4.EnableWindow(false);
		m_c1.SetWindowText(L"");
		m_c2.SetWindowText(L"");
		m_c3.SetWindowText(L"");
		m_c4.SetWindowText(L"");
		break;
	}
}


void CDlgExpand::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	CString cstr1, cstr2, cstr3, cstr4;
	int x1,y1,x2,y2;
	m_c1.GetWindowText(cstr1);
	m_c2.GetWindowText(cstr2);
	m_c3.GetWindowText(cstr3);
	m_c4.GetWindowText(cstr4);
	x1 = _ttoi(cstr1);
	y1 = _ttoi(cstr2);
	x2 = _ttoi(cstr3);
	y2 = _ttoi(cstr4);
	int row = dlg->m_lPicture.GetSelectionMark();
	switch(m_cb.GetCurSel()){
	case 0:
		{
			if(x1<0 || x2<0 || y1< 0 || y2<0){
				MessageBox(L"扩充距离不能为负喵！",L"提示喵");
				return;
			}
			matrix mat,mat2;
			stream s;
			PICinfo pi;
			dlg->io.GetPICInfo(row, pi);
			dlg->io.PICextract(row, mat, 0);
			mat.expandMatrix(mat2, y1, y2, x1, x2);
			dlg->io.PICpreprocess(mat2, s, pi);
			point newPt(pi.get_basePt().get_X()-x1, pi.get_basePt().get_Y()-y1);
			pi.set_basePt(newPt);
			dlg->io.PICreplace(row, pi, s);
			{
				dlg->m_lPicture.SetItemText(row, 1, FmtToCStr(dlg->io.PICcontent[row].get_format(), dlg->io.version));
				dlg->m_lPicture.SetItemText(row, 2, PtToCStr(dlg->io.PICcontent[row].get_basePt()));
				dlg->m_lPicture.SetItemText(row, 3, SzToCStr(dlg->io.PICcontent[row].get_picSize()));
				dlg->m_lPicture.SetItemText(row, 4, SzToCStr(dlg->io.PICcontent[row].get_frmSize()));
			}
			s.release();
			mat.release();
			mat2.release();
			MessageBox(L"扩充完毕了喵！",L"提示喵");
		}
		break;
	case 1:
		{
			if(x1<0 || x2<0 || y1< 0 || y2<0){
				MessageBox(L"裁切距离不能为负喵！",L"提示喵");
				return;
			}
			matrix mat,mat2;
			stream s;
			PICinfo pi;
			dlg->io.GetPICInfo(row, pi);
			if(x1+x2>=pi.get_picSize().get_W()||y1+y2>=pi.get_picSize().get_H()){
				MessageBox(L"如果就这样裁切，图片就会没掉喵！\r\n请重新调整裁切距离喵！",L"提示喵");
				return;
			}
			dlg->io.PICextract(row, mat, 0);
			mat.getSubMatrix(mat2,y1,mat.getRowCount()-y2-1,x1,mat.getColumnCount()-x2-1);
			dlg->io.PICpreprocess(mat2, s, pi);
			point newPt(pi.get_basePt().get_X()+x1, pi.get_basePt().get_Y()+y1);
			pi.set_basePt(newPt);
			dlg->io.PICreplace(row, pi, s);
			{
				dlg->m_lPicture.SetItemText(row, 1, FmtToCStr(dlg->io.PICcontent[row].get_format(), dlg->io.version));
				dlg->m_lPicture.SetItemText(row, 2, PtToCStr(dlg->io.PICcontent[row].get_basePt()));
				dlg->m_lPicture.SetItemText(row, 3, SzToCStr(dlg->io.PICcontent[row].get_picSize()));
				dlg->m_lPicture.SetItemText(row, 4, SzToCStr(dlg->io.PICcontent[row].get_frmSize()));
			}
			s.release();
			mat.release();
			mat2.release();
			MessageBox(L"裁切完毕了喵！",L"提示喵");
		}
		break;
	case 2:
		{
			matrix mat,mat2;
			stream s;
			PICinfo pi;
			dlg->io.GetPICInfo(row,pi);
			dlg->io.PICextract(row,mat,0);
			b32 x1_,y1_,x2_,y2_;
			mat.getElemHonzBound(x1_,x2_);
			mat.getElemVertBound(y1_,y2_);
			if(x1_>=x2_){
				//完全空
				MessageBox(L"空帧无法进行修整喵！",L"提示喵");
			}else{
				mat.getSubMatrix(mat2, y1_, y2_+1, x1_, x2_+1);
				dlg->io.PICpreprocess(mat2, s, pi);
				point newPt(pi.get_basePt().get_X()+x1_,pi.get_basePt().get_Y()+y1_);
				pi.set_basePt(newPt);
				dlg->io.PICreplace(row, pi, s);
				{
					dlg->m_lPicture.SetItemText(row, 1, FmtToCStr(dlg->io.PICcontent[row].get_format(), dlg->io.version));
					dlg->m_lPicture.SetItemText(row, 2, PtToCStr(dlg->io.PICcontent[row].get_basePt()));
					dlg->m_lPicture.SetItemText(row, 3, SzToCStr(dlg->io.PICcontent[row].get_picSize()));
					dlg->m_lPicture.SetItemText(row, 4, SzToCStr(dlg->io.PICcontent[row].get_frmSize()));
				}
				MessageBox(L"修整完毕了喵！",L"提示喵");
			}
			s.release();
			mat.release();
			mat2.release();
		}
		break;
	case 3:
		{
			if(x1>x2 || y1>y2){
				MessageBox(L"左上角坐标必须在右下角坐标的左上方喵！",L"提示喵");
				return;
			}
			matrix mat,mat2,mat3;
			stream s;
			PICinfo pi;
			dlg->io.GetPICInfo(row, pi);
			dlg->io.PICextract(row, mat, 0);
			int x10 = pi.get_basePt().get_X();
			int y10 = pi.get_basePt().get_Y();
			int x20 = pi.get_basePt().get_X()+pi.get_picSize().get_W()-1;
			int y20 = pi.get_basePt().get_Y()+pi.get_picSize().get_H()-1;
			int x1_ = min(x1,x10);
			int x2_ = max(x2,x20);
			int y1_ = min(y1,y10);
			int y2_ = max(y2,y20);
			mat2.allocate(y2_-y1_+1,x2_-x1_+1);
			mat2.putFore(mat, LAY);
			mat2.elemMoveHonz(x10-x1_);
			mat2.elemMoveVert(y10-y1_);
			mat2.getSubMatrix(mat3,y1-y1_,y2-y1_+1,x1-x1_,x2-x1_+1);
			dlg->io.PICpreprocess(mat3, s, pi);
			point newPt(x1,y1);
			pi.set_basePt(newPt);
			dlg->io.PICreplace(row, pi, s);
			{
				dlg->m_lPicture.SetItemText(row, 1, FmtToCStr(dlg->io.PICcontent[row].get_format(), dlg->io.version));
				dlg->m_lPicture.SetItemText(row, 2, PtToCStr(dlg->io.PICcontent[row].get_basePt()));
				dlg->m_lPicture.SetItemText(row, 3, SzToCStr(dlg->io.PICcontent[row].get_picSize()));
				dlg->m_lPicture.SetItemText(row, 4, SzToCStr(dlg->io.PICcontent[row].get_frmSize()));
			}
			s.release();
			mat.release();
			mat2.release();
			mat3.release();
			MessageBox(L"处理完毕了喵！",L"提示喵");
		}
		break;
	case 4:
		{
			if(x1>x2 || y1>y2){
				MessageBox(L"左上角坐标必须在右下角坐标的左上方喵！",L"提示喵");
				return;
			}
			dlg->canvasPara.x1 = x1;
			dlg->canvasPara.x2 = x2;
			dlg->canvasPara.y1 = y1;
			dlg->canvasPara.y2 = y2;
			AfxBeginThread(canvasThread, (LPVOID)GetParent());
		}
		break;
	case 5:
		{
			AfxBeginThread(uncanvasThread, (LPVOID)GetParent());
		}
	}
	dlg->saveAlert = true;
	dlg->draw();
	ShowWindow(SW_HIDE);
}


void CDlgExpand::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
