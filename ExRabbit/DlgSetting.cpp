// DlgSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgSetting.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgSetting 对话框

IMPLEMENT_DYNAMIC(CDlgSetting, CDialogEx)

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetting::IDD, pParent)
{

}

CDlgSetting::~CDlgSetting()
{
}

void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_EDIT3, m_e3);
}


BEGIN_MESSAGE_MAP(CDlgSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_S1, &CDlgSetting::OnBnClickedButtonS1)
	ON_BN_CLICKED(IDC_BUTTON_S2, &CDlgSetting::OnBnClickedButtonS2)
	ON_BN_CLICKED(IDOK, &CDlgSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSetting::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgSetting::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_S3, &CDlgSetting::OnBnClickedButtonS3)
END_MESSAGE_MAP()


// CDlgSetting 消息处理程序


void CDlgSetting::OnBnClickedButtonS1()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND hwnd= GetSafeHwnd();   //得到窗口句柄
	CString filePath= L"";	//得到文件路径
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//取得IMalloc分配器接口
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("选择文件夹");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//取得IMalloc分配器接口   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //获得一个文件系统路径
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//释放内存
			if(filePath.GetLength()<=1){
				MessageBox(L"并不是有效的文件夹喵！",L"提示喵");
			}else{
				m_e1.SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//释放接口
	}
}


void CDlgSetting::OnBnClickedButtonS2()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND hwnd= GetSafeHwnd();   //得到窗口句柄
	CString filePath= L"";	//得到文件路径
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//取得IMalloc分配器接口
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("选择文件夹");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//取得IMalloc分配器接口   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //获得一个文件系统路径
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//释放内存
			if(filePath.GetLength()<=1){
				MessageBox(L"并不是有效的文件夹喵！",L"提示喵");
			}else{
				m_e2.SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//释放接口
	}
}


void CDlgSetting::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile file;
	CString s1,s2,s3;
	m_e1.GetWindowText(s1);
	m_e2.GetWindowText(s2);
	m_e3.GetWindowText(s3);
	file.Open(L"profile.ini", CFile::modeCreate|CFile::modeWrite);
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	file.WriteString(s1+L"\n");
	file.WriteString(s2+L"\n");
	file.WriteString(s3+L"\n");
	CExRabbitDlg *dlg = (CExRabbitDlg *)GetParent();
	dlg->outputDir = s1;
	dlg->imPack2Dir = s2;
	dlg->bgColor = _ttoi(s3);
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
	MessageBox(L"已保存设置喵，重启后生效喵！",L"提示喵");
	ShowWindow(SW_HIDE);
	dlg->OnPaint();
}


void CDlgSetting::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CDlgSetting::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_e1.SetWindowText(getCurDir()+L"output");
	m_e2.SetWindowText(L"D:\\地下城与勇士\\ImagePacks2");
	m_e3.SetWindowText(L"16764091");
}


void CDlgSetting::OnBnClickedButtonS3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	m_e3.GetWindowText(s);
	DWORD clr = _ttoi(s);
	CColorDialog dlg(clr, CC_FULLOPEN | CC_RGBINIT, this);
	if(dlg.DoModal()){
		clr = dlg.GetColor();
	}
	s.Format(L"%d", clr);
	m_e3.SetWindowText(s);
}
