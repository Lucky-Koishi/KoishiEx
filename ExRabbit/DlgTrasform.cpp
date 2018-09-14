// DlgTrasform.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgTrasform.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgTrasform �Ի���

IMPLEMENT_DYNAMIC(CDlgTrasform, CDialogEx)

CDlgTrasform::CDlgTrasform(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTrasform::IDD, pParent)
{

}

CDlgTrasform::~CDlgTrasform()
{
}

void CDlgTrasform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
	DDX_Control(pDX, IDC_CHECK2, m_ch2);
	DDX_Control(pDX, IDC_CHECK3, m_ch3);
	DDX_Control(pDX, IDC_CHECK4, m_ch4);
	DDX_Control(pDX, IDC_COMBO1, m_c1);
	DDX_Control(pDX, IDC_COMBO3, m_c2);
	DDX_Control(pDX, IDC_CHECK7, m_ch5);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_STATIC_1, m_s1);
}


BEGIN_MESSAGE_MAP(CDlgTrasform, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTrasform::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgTrasform::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgTrasform::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgTrasform::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgTrasform::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgTrasform::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK7, &CDlgTrasform::OnBnClickedCheck7)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgTrasform::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDlgTrasform::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CDlgTrasform ��Ϣ�������


BOOL CDlgTrasform::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ch1.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgTrasform::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	CString s;
	if(m_ch1.GetCheck()){
		dlg->transformPara.target = 1;
	}
	if(m_ch2.GetCheck()){
		dlg->transformPara.target = 2;
	}
	if(m_ch3.GetCheck()){
		dlg->transformPara.target = 3;
	}
	if(m_ch4.GetCheck()){
		dlg->transformPara.bitMode = false;
		m_e1.GetWindowText(s);
		dlg->transformPara.bitPara = _ttoi(s);
	}
	if(m_ch5.GetCheck()){
		dlg->transformPara.bitMode = true;
		m_e2.GetWindowText(s);
		dlg->transformPara.bitPara = _ttoi(s);
	}
	switch(m_c1.GetCurSel()){
	case 0:
		dlg->transformPara.verPara = V2;
		dlg->transformPara.makeTexture = false;
		switch(m_c2.GetCurSel()){
		case 0:
			dlg->transformPara.fmtPara = ARGB8888;
			break;
		case 1:
			dlg->transformPara.fmtPara = ARGB4444;
			break;
		case 2:
			dlg->transformPara.fmtPara = ARGB1555;
			break;
		default:
			dlg->transformPara.fmtPara = COLOR_UDEF;
			break;
		}
		break;
	case 1:
		dlg->transformPara.verPara = V4;
		dlg->transformPara.fmtPara = INDEX_FMT_PALETTE;
		dlg->transformPara.makeTexture = false;
		break;
	case 2:
		dlg->transformPara.verPara = V5;
		switch(m_c2.GetCurSel()){
		case 0:
			dlg->transformPara.fmtPara = ARGB8888;
			dlg->transformPara.makeTexture = false;
			break;
		case 1:
			dlg->transformPara.fmtPara = ARGB4444;
			dlg->transformPara.makeTexture = false;
			break;
		case 2:
			dlg->transformPara.fmtPara = ARGB1555;
			dlg->transformPara.makeTexture = false;
			break;
		case 3:
			dlg->transformPara.fmtPara = INDEX_FMT_PALETTE;
			dlg->transformPara.makeTexture = false;
			break;
		case 4:
			dlg->transformPara.fmtPara = DDS_DXT5;
			dlg->transformPara.makeTexture = false;
			break;
		case 5:
			dlg->transformPara.fmtPara = ARGB8888;
			dlg->transformPara.makeTexture = true;
			break;
		case 6:
			dlg->transformPara.fmtPara = ARGB4444;
			dlg->transformPara.makeTexture = true;
			break;
		case 7:
			dlg->transformPara.fmtPara = ARGB1555;
			dlg->transformPara.makeTexture = true;
			break;
		case 8:
			dlg->transformPara.fmtPara = DDS_DXT5;
			dlg->transformPara.makeTexture = true;
			break;
		default:
			dlg->transformPara.fmtPara = COLOR_UDEF;
			dlg->transformPara.makeTexture = false;
			break;
		}
		break;
	case 3:
		dlg->transformPara.verPara = V6;
		dlg->transformPara.fmtPara = INDEX_FMT_PALETTE;
		dlg->transformPara.makeTexture = false;
		break;
	}
	::AfxBeginThread(CExRabbitDlg::threadTransform, (LPVOID)GetParent());
	ShowWindow(SW_HIDE);
}


void CDlgTrasform::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}


void CDlgTrasform::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
}


void CDlgTrasform::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
}


void CDlgTrasform::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
}


void CDlgTrasform::OnBnClickedCheck4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch5.SetCheck(0);
	m_ch4.SetCheck(1);
}


void CDlgTrasform::OnBnClickedCheck7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch5.SetCheck(1);
	m_ch4.SetCheck(0);
}


void CDlgTrasform::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(m_c1.GetCurSel()){
	case 0:
		m_c2.ResetContent();
		m_c2.AddString(L"ARGB8888�����ɫ24λ��");
		m_c2.AddString(L"ARGB4444����ǿɫ12λ������͸����");
		m_c2.AddString(L"ARGB1555����ǿɫ15λ���ް�͸����");
		m_c2.SetCurSel(0);
		break;
	case 1:
		m_c2.ResetContent();
		m_c2.AddString(L"������ɫ��8λ��ɫ�塿");
		m_c2.SetCurSel(0);
		break;
	case 2:
		m_c2.ResetContent();
		m_c2.AddString(L"ARGB8888�����ɫ24λ��");
		m_c2.AddString(L"ARGB4444����ǿɫ12λ������͸����");
		m_c2.AddString(L"ARGB1555����ǿɫ15λ���ް�͸����");
		m_c2.AddString(L"������ɫ��8λ��ɫ�塿");
		m_c2.AddString(L"DXT5��D3D-Format5������͸����");
		m_c2.AddString(L"ARGB8888���������ɫ��");
		m_c2.AddString(L"ARGB4444��������ǿɫ12λ������͸����");
		m_c2.AddString(L"ARGB1555��������ǿɫ15λ���ް�͸����");
		m_c2.AddString(L"DXT5������D3D-Format5������͸����");
		m_c2.SetCurSel(0);
		break;
	case 3:
		m_c2.ResetContent();
		m_c2.AddString(L"������ɫ��8λ��ɫ���1��");
		m_c2.SetCurSel(0);
		break;
	}
	OnCbnSelchangeCombo3();
}


void CDlgTrasform::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i1 = m_c1.GetCurSel();
	int i2 = m_c2.GetCurSel();
	if(i1 == 1 || i1 == 3 || i1 == 2 && i2 == 3){
		m_s1.EnableWindow(true);
		m_ch4.EnableWindow(true);
		m_ch5.EnableWindow(true);
		m_e1.EnableWindow(true);
		m_e2.EnableWindow(true);
	}else{
		m_s1.EnableWindow(false);
		m_ch4.EnableWindow(false);
		m_ch5.EnableWindow(false);
		m_e1.EnableWindow(false);
		m_e2.EnableWindow(false);
	}
}
