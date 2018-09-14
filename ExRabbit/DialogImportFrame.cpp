// DialogImportFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DialogImportFrame.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"


// CDialogImportFrame 对话框

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


// CDialogImportFrame 消息处理程序


BOOL CDialogImportFrame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_c1.ResetContent();
	m_c1.AddString(L"替换帧号相同贴图");
	m_c1.AddString(L"跳过帧号相同贴图");
	m_c1.SetCurSel(0);
	m_c3.ResetContent();
	m_c3.AddString(L"基准点坐标和帧域置零");
	m_c3.AddString(L"保留基准点坐标和帧域");
	m_c3.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDialogImportFrame::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CDialogImportFrame::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = _T("PNG图像(*.PNG)|*.PNG");
	CString extFilter = _T("PNG图像(*.PNG)|*.PNG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_e1.SetWindowText(fileName);
	}
}
