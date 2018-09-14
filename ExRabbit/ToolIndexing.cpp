// ToolIndexing.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolIndexing.h"
#include "afxdialogex.h"
#include "ExRabbitdlg.h"

// CToolIndexing �Ի���

IMPLEMENT_DYNAMIC(CToolIndexing, CDialogEx)

CToolIndexing::CToolIndexing(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolIndexing::IDD, pParent)
{

}

CToolIndexing::~CToolIndexing()
{
}

void CToolIndexing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_c1);
	DDX_Control(pDX, IDC_CHECK2, m_c2);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_PROGRESS1, m_p);
}


BEGIN_MESSAGE_MAP(CToolIndexing, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolIndexing::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CToolIndexing::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CToolIndexing::OnBnClickedCheck2)
	ON_BN_CLICKED(IDCANCEL, &CToolIndexing::OnBnClickedCancel)
END_MESSAGE_MAP()


// CToolIndexing ��Ϣ�������


void CToolIndexing::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_c2.GetCheck()){
		m_e1.SetWindowText(L"��ʼת��");
		AfxBeginThread(indexingThread, (PVOID)GetParent());
		AfxBeginThread(indexingProcessThread, (PVOID)GetParent());
	}else{
		m_e1.SetWindowText(L"��ʼת���ⲿ�ļ�");
		AfxBeginThread(indexingExternThread, (PVOID)GetParent());
		AfxBeginThread(indexingProcessThread, (PVOID)GetParent());
	}
	//AfxBeginThread(PH, (PVOID)this);
}


UINT CToolIndexing::PH(PVOID para){
	//CToolIndexing* dlg = (CToolIndexing*)para;
	//while(dlg->ii.millages < 1000){
	//	dlg->m_p.SetPos(dlg->ii.millages);
	//	if(dlg->ii.millages > 0 && dlg->ii.millages < 500){
	//		dlg->m_e1.SetWindowText(L"�����ؽ���ɫ����");
	//	}
	//	if(dlg->ii.millages > 500 && dlg->ii.millages < 1000){
	//		dlg->m_e1.SetWindowText(L"���������������");
	//	}
	//	Sleep(5);
	//}
	//dlg->m_e1.SetWindowText(L"ת����ϡ�");
	return 0;
}
BOOL CToolIndexing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_e1.SetWindowText(L"�ȴ�");
	m_e2.SetWindowText(L"���ⲿIMG�ļ���EX��ѡ����IMG�ļ�ת��ΪV4�汾(����ͼ��)����EX���õ�IMGת����ȣ�����������û�����ɫͳ���������ɫŷ�Ͼ���ƥ��ķ�ʽ������ɫ����趨������������ڱ��ֽϵ�ʧ���ʵ�ǰ���£�ͻ����ɫ������255�����ơ�ע�⣺��͸�����ؽ��ᱻ���ԡ�");
	m_p.SetRange32(0,1000);
	m_c2.SetCheck(1);
	m_c1.SetCheck(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CToolIndexing::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_e1.SetWindowText(L"׼��ת��"+shorten(fileName));
		m_c1.SetCheck(1);
		m_c2.SetCheck(0);
	}else{
		m_c1.SetCheck(0);
		m_c2.SetCheck(1);
	}
}


void CToolIndexing::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_c1.SetCheck(0);
	m_c2.SetCheck(1);
}


void CToolIndexing::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}
