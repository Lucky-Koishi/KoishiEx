// DialogImportFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DialogImportFrame.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"


// CDialogImportFrame �Ի���

IMPLEMENT_DYNAMIC(CDialogImportFrame, CDialogEx)

CDialogImportFrame::CDialogImportFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogImportFrame::IDD, pParent)
{

}

CDialogImportFrame::~CDialogImportFrame()
{
}

void CDialogImportFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_c1);
	DDX_Control(pDX, IDC_COMBO3, m_c3);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
}


BEGIN_MESSAGE_MAP(CDialogImportFrame, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogImportFrame::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogImportFrame::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogImportFrame::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialogImportFrame ��Ϣ�������


BOOL CDialogImportFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_c1.ResetContent();
	m_c1.AddString(L"�滻֡����ͬ��ͼ");
	m_c1.AddString(L"����֡����ͬ��ͼ");
	m_c1.SetCurSel(0);
	m_c3.ResetContent();
	m_c3.AddString(L"��׼�������֡������");
	m_c3.AddString(L"������׼�������֡��");
	m_c3.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogImportFrame::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg * dlg = (CExRabbitDlg *) GetParent();
	CString fileName, shortName, filePath;
	str fn;
	m_e1.GetWindowText(fileName);
	int pathSpl = fileName.ReverseFind('\\');
	shortName = fileName.Right(fileName.GetLength()-pathSpl-1);
	filePath = fileName.Left(pathSpl+1);
	CStrToStr(filePath, fn);
	dlg->importFramePara.filePath = fn;
	dlg->importFramePara.maxFrame = _ttoi(shortName.Left(shortName.GetLength()-4));
	dlg->importFramePara.oldFramePara = m_c1.GetCurSel();
	dlg->importFramePara.scalePara = m_c3.GetCurSel();
	AfxBeginThread(CExRabbitDlg::threadImportFrame,(PVOID)GetParent());
	ShowWindow(SW_HIDE);
}


void CDialogImportFrame::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}


void CDialogImportFrame::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defExt = _T("PNGͼ��(*.PNG)|*.PNG");
	CString extFilter = _T("PNGͼ��(*.PNG)|*.PNG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_e1.SetWindowText(fileName);
	}
}
