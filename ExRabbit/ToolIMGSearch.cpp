// ToolIMGSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolIMGSearch.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CToolIMGSearch 对话框

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


// CToolIMGSearch 消息处理程序


BOOL CToolIMGSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT);
	m_list.EasyInsertColumn(L"NPK名字,350,IMG名字,550,IMG版本,50,NPK路径,550");
	m_p1.SetRange32(0,1000);
	m_b6.EnableWindow(false);
	stopSign =false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CToolIMGSearch::OnBnClickedButton3()
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


void CToolIMGSearch::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_b3.EnableWindow(false);
	m_b5.EnableWindow(false);
	m_e1.EnableWindow(false);
	m_e2.EnableWindow(false);
	AfxBeginThread(ThreadToolIMGSearch, (PVOID)this);
}


void CToolIMGSearch::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"可以在指定文件夹内的所有NPK检索含有关键词的IMG文件，并用EX工具读取他们。\r\n --by 精灵-传说(colg)");
}


void CToolIMGSearch::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_list.GetItemCount()<1){
		MessageBox(L"并没有记录喵！",L"提示喵");
		return;
	}
	AfxBeginThread(ThreadToolIMGSearchOutput, (PVOID)this);
}


void CToolIMGSearch::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	int row = m_list.GetSelectionMark();
	if(row<0){
		MessageBox(L"选择一个NPK喵！",L"提示喵");
		return;
	}
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	str fn;
	CStrToStr(m_list.GetItemText(row, 3), fn);
	dlg->no.release();
	if(dlg->no.loadFile(fn)){
		MessageBox(L"读取完毕！");
	}else{
		MessageBox(L"读取失败！");
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
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

UINT ThreadToolIMGSearch(PVOID para){
	CToolIMGSearch *dlg = (CToolIMGSearch *)para;
	CFileFind fileFind;
	CString dir,keyWordCStr;
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
	dlg->MessageBox(L"查询完毕了喵！",L"提示喵");
	return 0;
}

UINT ThreadToolIMGSearchOutput(PVOID para){
	CToolIMGSearch *dlg = (CToolIMGSearch *)para;
	CStdioFile csf;
	csf.Open(getOutPutDir()+L"IMG查询结果.csv", CFile::modeCreate|CFile::modeWrite);
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
	dlg->MessageBox(L"保存到"+getOutPutDir()+L"IMG查询结果.csv了喵！",L"提示喵");
	return 0;
}

void CToolIMGSearch::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	stopSign = true;
}
