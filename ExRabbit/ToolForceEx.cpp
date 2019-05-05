// ToolForceEx.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolForceEx.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CToolForceEx 对话框

IMPLEMENT_DYNAMIC(CToolForceEx, CDialogEx)

CToolForceEx::CToolForceEx(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolForceEx::IDD, pParent)
{

}

CToolForceEx::~CToolForceEx()
{
}

void CToolForceEx::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eNPK);
	DDX_Control(pDX, IDC_EDIT18, m_eOK);
	DDX_Control(pDX, IDC_EDIT2, m_eProc);
	DDX_Control(pDX, IDC_PROGRESS1, m_pProc);
}


BEGIN_MESSAGE_MAP(CToolForceEx, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolForceEx::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CToolForceEx::OnBnClickedButton4)
END_MESSAGE_MAP()


// CToolForceEx 消息处理程序


void CToolForceEx::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_eNPK.SetWindowText(fileName);
	}
}


void CToolForceEx::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(fileName.GetLength() == 0){
		OnBnClickedButton1();
	}
	if(fileName.GetLength() == 0){
		return;
	}
	AfxBeginThread(extractIMGthread, (PVOID)this);
}

UINT CToolForceEx::extractIMGthread(PVOID para){
	CToolForceEx*dlg = (CToolForceEx*)para;
	stream s, sMagic, sPart;
	dlg->m_eOK.SetWindowText(L"打开中");
	str fn;
	CStrToStr(dlg->fileName, fn);
	if(!s.loadFile(fn)){
		dlg->MessageBox(L"打不开这个文件喵！");
		dlg->m_eOK.SetWindowText(L"被中断");
		return 0;
	}
	dlg->GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	queueex pos, len;
	sMagic.allocate(10);
	sMagic.pushString("Neople I");
	s.splitStream(sMagic, pos, len);
	int i, max = pos.size();
	CString info1, info2, fileN;
	for(i=1;i<max;i++){
		info1.Format(L"%.3lf％", (double)(i+1)*100/max);
		info2.Format(L"%d个",i);
		dlg->m_eProc.SetWindowText(info1);
		dlg->m_eOK.SetWindowText(info2);
		dlg->m_pProc.SetPos((i+1)*100/max);
		s.ptMoveTo(pos[i]-8);
		s.readStream(sPart, len[i]+8);
		fileN.Format(dlg->fileName + L".%d.IMG", i);
		CStrToStr(fileN, fn);
		sPart.makeFile(fn);
		sPart.release();
	}
	dlg->MessageBox(L"提取完成喵，已存在与NPK相同的文件夹下喵！");
	s.release();
	sMagic.release();
	dlg->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	return 0;
}