// DlgLoseBlack.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgLoseBlack.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// DlgLoseBlack �Ի���

IMPLEMENT_DYNAMIC(CDlgLoseBlack, CDialogEx)

CDlgLoseBlack::CDlgLoseBlack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLoseBlack::IDD, pParent)
{

}

CDlgLoseBlack::~CDlgLoseBlack()
{
}

void CDlgLoseBlack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eGamma);
}


BEGIN_MESSAGE_MAP(CDlgLoseBlack, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLoseBlack::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgLoseBlack::OnBnClickedCancel)
END_MESSAGE_MAP()


// DlgLoseBlack ��Ϣ�������


void CDlgLoseBlack::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	CString gammaStr;
	m_eGamma.GetWindowText(gammaStr);
	dlg->loseBlackPara.gamma = _ttoi(gammaStr);
	AfxBeginThread(dlg->threadLoseBlack, (void*)GetParent());
	ShowWindow(SW_HIDE);
}


void CDlgLoseBlack::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}
