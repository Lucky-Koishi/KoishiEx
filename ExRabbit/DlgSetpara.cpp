// DlgSetpara.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgSetpara.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgSetpara 对话框

IMPLEMENT_DYNAMIC(CDlgSetpara, CDialogEx)

CDlgSetpara::CDlgSetpara(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetpara::IDD, pParent)
{

}

CDlgSetpara::~CDlgSetpara()
{
}

void CDlgSetpara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_c1);
	DDX_Control(pDX, IDC_CHECK2, m_c2);
	DDX_Control(pDX, IDC_CHECK3, m_c3);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_EDIT13, m_e3);
	DDX_Control(pDX, IDC_EDIT3, m_e4);
	DDX_Control(pDX, IDC_CHECK4, m_c4);
}


BEGIN_MESSAGE_MAP(CDlgSetpara, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgSetpara::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgSetpara::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgSetpara::OnBnClickedCheck3)
	ON_BN_CLICKED(IDOK, &CDlgSetpara::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSetpara::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgSetpara::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CDlgSetpara 消息处理程序


void CDlgSetpara::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(1);
	m_c2.SetCheck(0);
	m_c4.SetCheck(0);
}


void CDlgSetpara::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(0);
	m_c2.SetCheck(1);
	m_c4.SetCheck(0);
}


void CDlgSetpara::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(0);
	m_c2.SetCheck(0);
	m_c4.SetCheck(1);
}


void CDlgSetpara::OnBnClickedCheck3()
{
	// TODO: 相对修改
}


void CDlgSetpara::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();

	PICinfo pi;
	CString cstr1,cstr2;
	i32 i1,i2;
	point pt;
	size sz;
	if(m_c1.GetCheck()){
		dlg->io.PICgetInfo(pos, pi);
		m_e1.GetWindowText(cstr1);
		m_e2.GetWindowText(cstr2);
		i1 = _ttoi(cstr1);
		i2 = _ttoi(cstr2);
		if(m_c3.GetCheck()){
			//相对坐标
			i1 += pi.get_basePt().get_X();
			i2 += pi.get_basePt().get_Y();
		}
		pt.set(i1,i2);
		dlg->io.PICsetInfoPara(pos, 1, &pt);
		m_e3.GetWindowText(cstr1);
		m_e4.GetWindowText(cstr2);
		i1 = _ttoi(cstr1);
		i2 = _ttoi(cstr2);
		sz.set(i1,i2);
		dlg->io.PICsetInfoPara(pos, 2, &sz);
		{
			dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
			dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
			dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
			dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
			if(dlg->io.version == V5){
				dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
			}
		}
	}else if(m_c2.GetCheck()){
		std::vector<int> listID;
		dlg->getSelected(&dlg->m_lPicture, 0, 1, listID);
		for(int i = 0;i<listID.size();i++){
			if(dlg->io.PICcontent[listID[i]].get_format() != LINK){
				dlg->io.PICgetInfo(listID[i], pi);
				m_e1.GetWindowText(cstr1);
				m_e2.GetWindowText(cstr2);
				i1 = _ttoi(cstr1);
				i2 = _ttoi(cstr2);
				if(m_c3.GetCheck()){
					//相对坐标
					i1 += pi.get_basePt().get_X();
					i2 += pi.get_basePt().get_Y();
				}
				pt.set(i1,i2);
				dlg->io.PICsetInfoPara(listID[i], 1, &pt);
				m_e3.GetWindowText(cstr1);
				m_e4.GetWindowText(cstr2);
				i1 = _ttoi(cstr1);
				i2 = _ttoi(cstr2);
				sz.set(i1,i2);
				dlg->io.PICsetInfoPara(listID[i], 2, &sz);
				{
					dlg->m_lPicture.SetItemText(listID[i], 1, FmtToCStr(dlg->io.PICcontent[listID[i]].get_format(), dlg->io.version));
					dlg->m_lPicture.SetItemText(listID[i], 2, PtToCStr(dlg->io.PICcontent[listID[i]].get_basePt()));
					dlg->m_lPicture.SetItemText(listID[i], 3, SzToCStr(dlg->io.PICcontent[listID[i]].get_picSize()));
					dlg->m_lPicture.SetItemText(listID[i], 4, SzToCStr(dlg->io.PICcontent[listID[i]].get_frmSize()));
					if(dlg->io.version == V5){
						dlg->m_lPicture.SetItemText(listID[i], 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[listID[i]].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[listID[i]].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[listID[i]].get_TEXpointRB()));
					}
				}
			}
		}
	}else if(m_c4.GetCheck()){
		for(int i = 0;i<dlg->io.indexCount;i++){
			if(dlg->io.PICcontent[i].get_format() != LINK){
				dlg->io.PICgetInfo(i, pi);
				m_e1.GetWindowText(cstr1);
				m_e2.GetWindowText(cstr2);
				i1 = _ttoi(cstr1);
				i2 = _ttoi(cstr2);
				if(m_c3.GetCheck()){
					//相对坐标
					i1 += pi.get_basePt().get_X();
					i2 += pi.get_basePt().get_Y();
				}
				pt.set(i1,i2);
				dlg->io.PICsetInfoPara(i, 1, &pt);
				m_e3.GetWindowText(cstr1);
				m_e4.GetWindowText(cstr2);
				i1 = _ttoi(cstr1);
				i2 = _ttoi(cstr2);
				sz.set(i1,i2);
				dlg->io.PICsetInfoPara(i, 2, &sz);
				{
					dlg->m_lPicture.SetItemText(i, 1, FmtToCStr(dlg->io.PICcontent[i].get_format(), dlg->io.version));
					dlg->m_lPicture.SetItemText(i, 2, PtToCStr(dlg->io.PICcontent[i].get_basePt()));
					dlg->m_lPicture.SetItemText(i, 3, SzToCStr(dlg->io.PICcontent[i].get_picSize()));
					dlg->m_lPicture.SetItemText(i, 4, SzToCStr(dlg->io.PICcontent[i].get_frmSize()));
					if(dlg->io.version == V5){
						dlg->m_lPicture.SetItemText(i, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[i].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[i].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[i].get_TEXpointRB()));
					}
				}
			}
		}
	}
	MessageBox(L"修改完毕喵！",L"提示喵！");
	dlg->updateNPKInfo();
	dlg->updatePICInfo();
	dlg->draw();
	ShowWindow(SW_HIDE);
}


void CDlgSetpara::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
