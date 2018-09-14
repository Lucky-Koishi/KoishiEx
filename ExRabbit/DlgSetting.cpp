// DlgSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgSetting.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgSetting �Ի���

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


// CDlgSetting ��Ϣ�������


void CDlgSetting::OnBnClickedButtonS1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND hwnd= GetSafeHwnd();   //�õ����ھ��
	CString filePath= L"";	//�õ��ļ�·��
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//ȡ��IMalloc�������ӿ�
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("ѡ���ļ���");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//ȡ��IMalloc�������ӿ�   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //���һ���ļ�ϵͳ·��
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//�ͷ��ڴ�
			if(filePath.GetLength()<=1){
				MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				m_e1.SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//�ͷŽӿ�
	}
}


void CDlgSetting::OnBnClickedButtonS2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND hwnd= GetSafeHwnd();   //�õ����ھ��
	CString filePath= L"";	//�õ��ļ�·��
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//ȡ��IMalloc�������ӿ�
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("ѡ���ļ���");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//ȡ��IMalloc�������ӿ�   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //���һ���ļ�ϵͳ·��
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//�ͷ��ڴ�
			if(filePath.GetLength()<=1){
				MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				m_e2.SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//�ͷŽӿ�
	}
}


void CDlgSetting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	MessageBox(L"�ѱ�������������������Ч����",L"��ʾ��");
	ShowWindow(SW_HIDE);
	dlg->OnPaint();
}


void CDlgSetting::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}


void CDlgSetting::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_e1.SetWindowText(getCurDir()+L"output");
	m_e2.SetWindowText(L"D:\\���³�����ʿ\\ImagePacks2");
	m_e3.SetWindowText(L"16764091");
}


void CDlgSetting::OnBnClickedButtonS3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
