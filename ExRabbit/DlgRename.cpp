// CDlgRename.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgRename.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgRename �Ի���

IMPLEMENT_DYNAMIC(CDlgRename, CDialogEx)

CDlgRename::CDlgRename(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRename::IDD, pParent)
{

}

CDlgRename::~CDlgRename()
{
}

void CDlgRename::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ed1);
	DDX_Control(pDX, IDC_EDIT2, m_ed2);
}


BEGIN_MESSAGE_MAP(CDlgRename, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRename::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgRename::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgRename ��Ϣ�������


void CDlgRename::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	int i = dlg->crtIMGid;
	CString cstr;
	str fn;
	m_ed2.GetWindowText(cstr);
	CStrToStr(cstr, fn);
	dlg->no.IMGrename(i, fn);
	dlg->updateNPKInfo();
	{
		dlg->m_lIMG.SetItemText(i, 0, shorten(cstr));
		dlg->fileIMGname = cstr;
	}
	ShowWindow(SW_HIDE);
}


void CDlgRename::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}
