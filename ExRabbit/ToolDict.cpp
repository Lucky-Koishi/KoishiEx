// ToolDict.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolDict.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"
#include "locale.h"

// CToolDict 对话框

IMPLEMENT_DYNAMIC(CToolDict, CDialogEx)

CToolDict::CToolDict(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolDict::IDD, pParent)
{

}

CToolDict::~CToolDict()
{
}

void CToolDict::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_LIST1, m_l1);
	DDX_Control(pDX, IDC_PROGRESS1, m_p1);
	DDX_Control(pDX, IDC_EDIT10, m_e3);
}


BEGIN_MESSAGE_MAP(CToolDict, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolDict::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CToolDict::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CToolDict::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CToolDict::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON18, &CToolDict::OnBnClickedButton18)
	ON_BN_CLICKED(IDCANCEL, &CToolDict::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON17, &CToolDict::OnBnClickedButton17)
END_MESSAGE_MAP()


// CToolDict 消息处理程序


void CToolDict::OnBnClickedButton1()
{
	// TODO: 更新辞典
	AfxBeginThread(ThreadToolDictLoadDict, (PVOID)this);
}


void CToolDict::OnBnClickedButton4()
{
	// TODO: 修改辞典文件
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	ShellExecute(0,L"open",dlg->profile.getSupportPath()+L"npkdict.txt",L"",L"",SW_MAXIMIZE);
}


void CToolDict::OnBnClickedButton7()
{
	// TODO: 浏览
	MessageBox(L"请在“系统菜单→设置”里对辞典资源目录进行设置喵！",L"提示喵");
}


void CToolDict::OnBnClickedButton5()
{
	// TODO: 关键字查询
	AfxBeginThread(ThreadToolDictSearchDict, (PVOID)this);
}


void CToolDict::OnBnClickedButton18()
{
	// TODO: 使用EX打开NPK
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	CString f1,f2,fileName;
	str fn;
	m_e2.GetWindowText(f1);
	int row = m_l1.GetSelectionMark();
	f2 = m_l1.GetItemText(row, 0);
	fileName = f1+L"\\"+f2;
	CFile file;
	if(file.Open(fileName, CFile::modeRead)){
		file.Close();
		CStrToStr(fileName, fn);
		dlg->no.release();
		dlg->no.loadFile(fn);
		dlg->fileNPKname = fileName;
		dlg->IMGsaveAlert = false;
		MessageBox(L"已经打开所选文件喵！",L"提示喵");
		dlg->updateIMGlist();
		dlg->updateInfo();
	}else{
		MessageBox(L"资源文件夹中不存在选定文件喵！",L"提示喵");
	}
}


void CToolDict::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

UINT ThreadToolDictLoadDict(PVOID para){
	CToolDict *dlg = (CToolDict *)para;
	CStdioFile file;
	if(!file.Open(dlg->contentDir+L"npkdict.txt",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite)){
		dlg->MessageBox(L"无法打开辞典！\r\n确认你没有使用Excel打开它！",L"提示喵");
		return 0;
	}
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	CString cstr;
	long long pos = 0;
	long count = 0;
	dlg->m_p1.SetPos(0);
	dlg->m_l1.DeleteAllItems();
	while(file.ReadString(cstr)){
		if(cstr.Find(L",")>=0){
			dlg->m_l1.EasyInsertItem(cstr);
			count ++;
		}
		pos += cstr.GetLength();
		dlg->m_p1.SetPos(1000*pos/file.GetLength());
	}
	dlg->m_p1.SetPos(1000);
	dlg->m_e3.SetWindowText(L"共录入"+NumToCStr(count)+L"条");
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	return 0;
}
UINT ThreadToolDictSearchDict(PVOID para){
	CToolDict *dlg = (CToolDict *)para;
	CStdioFile file;
	file.Open(dlg->contentDir+L"npkdict.txt",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	CString cstr;
	CString keyWord;
	long long pos = 0;
	dlg->m_e1.GetWindowText(keyWord);
	dlg->m_p1.SetPos(0);
	dlg->m_l1.DeleteAllItems();
	while(file.ReadString(cstr)){
		if(cstr.Find(L",")>=0 && (keyWord.GetLength() == 0 || keyWord.GetLength() > 0 && cstr.Find(keyWord)>=0))
			dlg->m_l1.EasyInsertItem(cstr);
		pos += cstr.GetLength();
		dlg->m_p1.SetPos(1000*pos/file.GetLength());
	}
	dlg->m_p1.SetPos(1000);
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	return 0;
}

BOOL CToolDict::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	// TODO:  在此添加额外的初始化
	m_l1.EasyInsertColumn(L"NPK文件,335,标记,200");
	m_e2.SetWindowText(dlg->profile.getNPKdictPath());
	contentDir = dlg->profile.getSupportPath();
	resourceDir = dlg->profile.getNPKdictPath();
	m_p1.SetRange32(0,1000);
	AfxBeginThread(ThreadToolDictLoadDict, (PVOID)this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CToolDict::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"该工具可以根据辞典进行查询，并通过资源库打开对应的NPK文件。",L"提示喵");
}
