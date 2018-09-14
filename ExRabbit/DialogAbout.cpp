// DialogAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DialogAbout.h"
#include "afxdialogex.h"


// CDialogAbout �Ի���

IMPLEMENT_DYNAMIC(CDialogAbout, CDialogEx)

CDialogAbout::CDialogAbout(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogAbout::IDD, pParent)
{

}

CDialogAbout::~CDialogAbout()
{
}

void CDialogAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_QR, m_QR);
}


BEGIN_MESSAGE_MAP(CDialogAbout, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogAbout::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogAbout ��Ϣ�������


BOOL CDialogAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_QRbmp.LoadBitmap(IDB_BITMAP2);
	m_QR.SetBitmap(m_QRbmp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogAbout::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}
