// ToolIMGSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolIMGSearch.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CToolIMGSearch �Ի���

IMPLEMENT_DYNAMIC(CToolIMGSearch, CDialogEx)

CToolIMGSearch::CToolIMGSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolIMGSearch::IDD, pParent)
{

}

CToolIMGSearch::~CToolIMGSearch()
{
}

void CToolIMGSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON2, m_b2);
	DDX_Control(pDX, IDC_BUTTON3, m_b3);
	DDX_Control(pDX, IDC_PROGRESS1, m_p1);
	DDX_Control(pDX, IDC_BUTTON5, m_b5);
	DDX_Control(pDX, IDC_BUTTON10, m_b10);
	DDX_Control(pDX, IDC_BUTTON11, m_b11);
	DDX_Control(pDX, IDC_BUTTON6, m_b6);
}


BEGIN_MESSAGE_MAP(CToolIMGSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CToolIMGSearch::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CToolIMGSearch::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolIMGSearch::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON11, &CToolIMGSearch::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON10, &CToolIMGSearch::OnBnClickedButton10)
	ON_BN_CLICKED(IDOK, &CToolIMGSearch::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON6, &CToolIMGSearch::OnBnClickedButton6)
END_MESSAGE_MAP()


// CToolIMGSearch ��Ϣ�������


BOOL CToolIMGSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString tra;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT);
	tra.LoadStringW(IDS_STRING_LOCATORCOLOMN);
	m_list.EasyInsertColumn(tra);
	//m_list.EasyInsertColumn(L"NPK����,350,IMG����,550,IMG�汾,50,NPK·��,550");
	m_p1.SetRange32(0,1000);
	m_b6.EnableWindow(false);
	stopSign =false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CToolIMGSearch::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND hwnd= GetSafeHwnd();   //�õ����ھ��
	CString filePath= L"";	//�õ��ļ�·��
	CString tra, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//ȡ��IMalloc�������ӿ�
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		tra.LoadStringW(IDS_STRING_SELECTFOLDER);
		bi.lpszTitle = tra;
		//bi.lpszTitle = _T("ѡ���ļ���");
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
				tra.LoadStringW(IDS_STRING_NOTAVAILABLEFOLDER);
				MessageBox(tra, title);
				//MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				m_e1.SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//�ͷŽӿ�
	}
}


void CToolIMGSearch::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_b3.EnableWindow(false);
	m_b5.EnableWindow(false);
	m_e1.EnableWindow(false);
	m_e2.EnableWindow(false);
	AfxBeginThread(ThreadToolIMGSearch, (PVOID)this);
}


void CToolIMGSearch::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString info, title;
	info.LoadStringW(IDS_STRING_IMGLOCATORINTRODUCTION);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	MessageBox(info, title);
	//MessageBox(L"������ָ���ļ����ڵ�����NPK�������йؼ��ʵ�IMG�ļ�������EX���߶�ȡ���ǡ�\r\n --by ����-��˵(colg)");
}


void CToolIMGSearch::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if(m_list.GetItemCount()<1){
		info.LoadStringW(IDS_STRING_NORECORD);
		MessageBox(info, title);
		//MessageBox(L"��û�м�¼����",L"��ʾ��");
		return;
	}
	AfxBeginThread(ThreadToolIMGSearchOutput, (PVOID)this);
}


void CToolIMGSearch::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	int row = m_list.GetSelectionMark();
	if(row<0){
		info.LoadStringW(IDS_STRING_SELECTNPKFIRST);
		MessageBox(info, title);
		//MessageBox(L"ѡ��һ��NPK����",L"��ʾ��");
		return;
	}
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	str fn;
	CStrToStr(m_list.GetItemText(row, 3), fn);
	dlg->no.release();
	if(dlg->no.loadFile(fn)){
		info.LoadStringW(IDS_STRING_READFINISHED);
		MessageBox(info, title);
		//MessageBox(L"��ȡ��ϣ�");
	}else{
		info.LoadStringW(IDS_STRING_READFAILED);
		MessageBox(info, title);
		//MessageBox(L"��ȡʧ�ܣ�");
		return;
	}
	dlg->fileNPKname = m_list.GetItemText(row, 0);
	dlg->fileOpen = true;
	dlg->mixMode = false;
	dlg->saveAlert = false;
	dlg->dispModeShowAll = false;
	dlg->updateIMGlist();
	if(dlg->no.count>0){
		dlg->m_lIMG.SetSelectionMark(0);
		dlg->crtIMGid = 0;
	}
}


void CToolIMGSearch::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}

UINT ThreadToolIMGSearch(PVOID para){
	CToolIMGSearch *dlg = (CToolIMGSearch *)para;
	CFileFind fileFind;
	CString dir,keyWordCStr;
	CString info, title;
	dlg->m_e1.GetWindowText(dir);
	dlg->m_e2.GetWindowText(keyWordCStr);
	dlg->m_b6.EnableWindow(true);
	dlg->m_p1.SetPos(0);
	dir += L"\\*.npk";
	BOOL ret = fileFind.FindFile(dir);
	std::vector<CString> fileList;
	std::vector<CString> filePath;
	std::vector<IMGversion> unused;
	fileList.clear();
	while (ret){
		ret = fileFind.FindNextFile();
		CString name = fileFind.GetFileName();
		CString path = fileFind.GetFilePath();
        fileList.push_back(name);
		filePath.push_back(path);
    }
	int i,j;
	NPKobject no;
	str fn,keyword;
	CStrToStr(keyWordCStr, keyword);
	dlg->m_list.DeleteAllItems();
	for(i=0;i<fileList.size();i++){
		CStrToStr(filePath[i], fn);
		no.loadIndex(fn,unused);
		for(j=0;j<no.count;j++){
			if(no.content[j].get_imgname().find(keyword) != str::npos){
				dlg->m_list.EasyInsertItem(fileList[i]+L","+StrToCStr(no.content[j].get_imgname())+L","+NumToCStr(unused[j])+L","+filePath[i]);
				if(j%10==1){
					dlg->m_p1.SetPos(1000*i/fileList.size()+1000*j/fileList.size()/no.count);
					if(dlg->stopSign){
						dlg->stopSign = false;
						no.release();
						dlg->m_b3.EnableWindow(true);
						dlg->m_b5.EnableWindow(true);
						dlg->m_e1.EnableWindow(true);
						dlg->m_e2.EnableWindow(true);
						dlg->m_b6.EnableWindow(false);
						return 0;
					}
				}
			}
		}
		no.release();
	}
	dlg->stopSign = false;
	dlg->m_p1.SetPos(1000);
	dlg->m_b3.EnableWindow(true);
	dlg->m_b5.EnableWindow(true);
	dlg->m_e1.EnableWindow(true);
	dlg->m_e2.EnableWindow(true);
	dlg->m_b6.EnableWindow(false);
	info.LoadStringW(IDS_STRING_QUERYFINISHED);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->MessageBox(info, title);
	//dlg->MessageBox(L"��ѯ���������",L"��ʾ��");
	return 0;
}

UINT ThreadToolIMGSearchOutput(PVOID para){
	CToolIMGSearch *dlg = (CToolIMGSearch *)para;
	CStdioFile csf;
	CString info, title, tmp;
	csf.Open(getOutPutDir()+L"IMGQueryResult.csv", CFile::modeCreate|CFile::modeWrite);
	dlg->m_p1.SetPos(0);
	dlg->m_b11.EnableWindow(false);
	csf.WriteString(L"NPK list, IMG list, IMG version, NPK path\n");
	for(int i =0;i<dlg->m_list.GetItemCount();i++){
		csf.WriteString(dlg->m_list.GetItemText(i,0)+L","+dlg->m_list.GetItemText(i,1)+L","+dlg->m_list.GetItemText(i,2)+L","+dlg->m_list.GetItemText(i,3)+L"\n");
		dlg->m_p1.SetPos(1000*i/dlg->m_list.GetItemCount());
	}
	dlg->m_p1.SetPos(1000);
	dlg->m_b11.EnableWindow(true);
	csf.Close();
	title.LoadStringW(IDS_MESSAGE_TITLE);
	tmp.LoadStringW(IDS_STRING_SAVEDTOQUERYRESULT);
	info.Format(tmp, getOutPutDir());
	dlg->MessageBox(info, title);
	//dlg->MessageBox(L"���浽"+getOutPutDir()+L"IMGQueryResult.csv������",L"��ʾ��");
	return 0;
}

void CToolIMGSearch::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	stopSign = true;
}
