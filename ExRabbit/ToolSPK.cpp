// ToolSPK.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolSPK.h"
#include "afxdialogex.h"
#include <afxinet.h> 
#include "ExRabbitDlg.h"

// CToolSPK 对话框

//#define DISABLE_TEST 

IMPLEMENT_DYNAMIC(CToolSPK, CDialogEx)

CToolSPK::CToolSPK(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolSPK::IDD, pParent)
{

}

CToolSPK::~CToolSPK()
{
}

void CToolSPK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_cRec);
	DDX_Control(pDX, IDC_LIST2, m_lSPK);
	DDX_Control(pDX, IDC_EDIT1, m_eURL);
	DDX_Control(pDX, IDC_EDIT20, m_eDownloadSPK);
	DDX_Control(pDX, IDC_EDIT21, m_eSPK);
	DDX_Control(pDX, IDC_EDIT22, m_eConvertToNPK);
	DDX_Control(pDX, IDC_EDIT23, m_eKeyWord);
}


BEGIN_MESSAGE_MAP(CToolSPK, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON21, &CToolSPK::OnBnClickedButton21)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CToolSPK::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDCANCEL, &CToolSPK::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON16, &CToolSPK::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON19, &CToolSPK::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON17, &CToolSPK::OnBnClickedButton17)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CToolSPK::OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON20, &CToolSPK::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON22, &CToolSPK::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON_ADDONE, &CToolSPK::OnBnClickedButtonAddone)
	ON_BN_CLICKED(IDC_BUTTON_ADDALL, &CToolSPK::OnBnClickedButtonAddall)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEONE, &CToolSPK::OnBnClickedButtonRemoveone)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEALL, &CToolSPK::OnBnClickedButtonRemoveall)
	ON_BN_CLICKED(IDC_BUTTON4, &CToolSPK::OnBnClickedButton4)
END_MESSAGE_MAP()


// CToolSPK 消息处理程序


BOOL CToolSPK::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
#ifndef DISABLE_TEST
	m_cRec.ResetContent();
	m_cRec.AddString(L"韩服客户端");
	m_cRec.AddString(L"韩服测试服客户端");
	m_cRec.AddString(L"日服客户端");
	m_cRec.AddString(L"美服客户端");
	m_cRec.AddString(L"国服西海岸1区客户端");
	m_cRec.AddString(L"国服西海岸2区客户端");
	m_cRec.AddString(L"国服天空之城客户端");
	m_cRec.AddString(L"自定义URL");
	m_cRec.SetCurSel(0);

	m_lSPK.EasyInsertColumn(L"NPK文件名,320,大小,80");
	GET_CTRL(CGoodListCtrl, IDC_LIST3)->EasyInsertColumn(L"NPK文件名,260,状态,70");
	serverChoose = 0;

	URLaddr = L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_hg/";
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CToolSPK::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

void CToolSPK::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	serverChoose = m_cRec.GetCurSel();
	switch(serverChoose){
	case 0 :
		URLaddr = L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_hg/";
		m_eURL.SetWindowText(URLaddr);
		m_eURL.SetReadOnly(true);
		loadPackage();
		break;
	case 1:
		URLaddr = L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_open/";
		m_eURL.SetWindowText(URLaddr);
		m_eURL.SetReadOnly(true);
		loadPackage();
		break;
	case 2:
		URLaddr = L"http://webdown2.nexon.co.jp/arad/real/";
		m_eURL.SetWindowText(URLaddr);
		m_eURL.SetReadOnly(true);
		loadPackage();
		break;
	case 3:
		URLaddr = L"http://download.dfoneople.com/Patch/";
		m_eURL.SetWindowText(URLaddr);
		m_eURL.SetReadOnly(true);
		loadPackage();
		break;
	case 4:
		URLaddr = L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp1.full.tct/";
		m_eURL.SetWindowText(URLaddr);
		m_eURL.SetReadOnly(true);
		loadPackage();
		break;
	case 5:
		URLaddr = L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp2.full.tct/";
		m_eURL.SetWindowText(URLaddr);
		m_eURL.SetReadOnly(true);
		loadPackage();
		break;
	case 6:
		URLaddr = L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp5.full.tct/";
		m_eURL.SetWindowText(URLaddr);
		m_eURL.SetReadOnly(true);
		loadPackage();
		break;
	case 7:
		m_eURL.SetReadOnly(false);
		break;
	}
}

void CToolSPK::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(threadDownloadPackageList, (PVOID)this);
}

void CToolSPK::loadPackage(){
	str fileFour[8] = {"(HF)package.lst", "(HFC)package.lst","(RF)package.lst","(MF)package.lst","(WC1)auto.lst","(WC2)auto.lst","(SC)auto.lst","(Custom)package.lst"};
	LSTobject lo;
	LSTobjectGF lo2;
	LSTfolder lf;
	if(serverChoose >=4 && serverChoose<=6){
		if(lo2.load(CStrToStr(localAddr) + fileFour[m_cRec.GetCurSel()])){
			m_lSPK.DeleteAllItems();
			for(int i = 0;i<lo2.list.size();i++){
				CString nameStr;
				CString sizeStr;
				str name = (char*)lo2.list[i].name;
				nameStr = StrToCStr(name);
				str size = (char*)lo2.list[i].lenStr;
				sizeStr = StrToCStr(size);
				int len = _ttoi(sizeStr);
				if(len > 1024 * 1024 * 10){
					sizeStr = NumToCStr(len / 1024 / 1024)+L" MB";
				}else if(len > 1024 * 10){
					sizeStr = NumToCStr(len / 1024)+L" KB";
				}else{
					sizeStr = NumToCStr(len)+L" B";
				}
				m_lSPK.EasyInsertItem(nameStr+L","+sizeStr);
			}
		}else{
			m_lSPK.DeleteAllItems();
			m_lSPK.EasyInsertItem(L"没有列表或列表文件已损坏，请更新NPK列表。,");
		}
	}else{
		if(lo.load(CStrToStr(localAddr) + fileFour[m_cRec.GetCurSel()])){
			if(lo.getImagePack2(lf)){
				m_lSPK.DeleteAllItems();
				for(int i = 0;i<lf.list.size();i++){
					CString nameStr;
					CString sizeStr;
					str name = (char*)lf.list[i].name;
					nameStr = StrToCStr(name);
					if(lf.list[i].fileLen > 1024 * 1024 * 10){
						sizeStr = NumToCStr(lf.list[i].fileLen / 1024 / 1024)+L" MB";
					}else if(lf.list[i].fileLen > 1024 * 10){
						sizeStr = NumToCStr(lf.list[i].fileLen / 1024)+L" KB";
					}else{
						sizeStr = NumToCStr(lf.list[i].fileLen)+L" B";
					}
					m_lSPK.EasyInsertItem(nameStr+L","+sizeStr);
				}
			}else{
				m_lSPK.DeleteAllItems();
				m_lSPK.EasyInsertItem(L"列表中不包含音效文件夹。,");
			}
		}else{
			m_lSPK.DeleteAllItems();
			m_lSPK.EasyInsertItem(L"没有列表或列表文件已损坏，请更新NPK列表。,");
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//以下代码来源：https://blog.csdn.net/charlessimonyi/article/details/8666108
//用于在网上下载文件到本地//////////////////////////////////////////////////
INT CToolSPK::GetInternetFile(const CString strUrl,const CString strSavePath){
	#ifndef DISABLE_TEST
	if (strUrl.IsEmpty())  
		return -5;  
	if (strSavePath.IsEmpty())  
		return -6;  

	unsigned short nPort;       //用于保存目标HTTP服务端口  
	CString strServer, strObject;   //strServer用于保存服务器地址，strObject用于保存文件对象名称  
	DWORD dwServiceType,dwRet;      //dwServiceType用于保存服务类型，dwRet用于保存提交GET请求返回的状态号  

	//解析URL，获取信息  
	if(!AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort)){  
		//解析失败，该Url不正确  
		return -1;  
	}  
	//创建网络连接对象，HTTP连接对象指针和用于该连接的HttpFile文件对象指针，注意delete  
	CInternetSession intsess;  
	CHttpFile *pHtFile = NULL;  
	//建立网络连接  
	CHttpConnection *pHtCon = intsess.GetHttpConnection(strServer,nPort);  
	if(pHtCon == NULL){  
		//建立网络连接失败  
		intsess.Close();  
		return -2;  
	}  
	//发起GET请求  
	pHtFile = pHtCon->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject);  
	if(pHtFile == NULL){  
		//发起GET请求失败  
		intsess.Close();  
		delete pHtCon;pHtCon = NULL;  
		return -3;  
	}  
	//提交请求
	try{
		pHtFile->SendRequest();  
	}catch(CException *){
		intsess.Close();
		delete pHtCon;pHtCon = NULL;  
		delete pHtFile;pHtFile = NULL;  
		return -8;  
	}
	//获取服务器返回的状态号  
	pHtFile->QueryInfoStatusCode(dwRet);  
	if (dwRet != HTTP_STATUS_OK){  
		//服务器不接受请求  
		intsess.Close();  
		delete pHtCon;pHtCon = NULL;  
		delete pHtFile;pHtFile = NULL;  
		return -4;  
	}  
	//获取文件大小  
	UINT nFileLen = (UINT)pHtFile->GetLength();  
	DWORD dwRead = 1;       //用于标识读了多少，为1是为了进入循环  
	//创建缓冲区  
	CHAR *szBuffer = new CHAR[nFileLen+1];  
	TRY
	{  
		//创建文件  
		CFile PicFile(strSavePath,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);  
		while(dwRead>0)  
		{    
			//清空缓冲区  
			memset(szBuffer,0,(size_t)(nFileLen+1));  
			//读取到缓冲区  
			dwRead = pHtFile->Read(szBuffer,nFileLen);   
			//写入到文件  
			PicFile.Write(szBuffer,dwRead);  
		}  
		//关闭文件  
		PicFile.Close();  
		//释放内存  
		delete []szBuffer;  
		delete pHtFile;  
		delete pHtCon;  
		//关闭网络连接  
		intsess.Close();  
	}  
	CATCH(CFileException,e){  
		//释放内存  
		delete []szBuffer;  
		delete pHtFile;  
		delete pHtCon;  
		//关闭网络连接  
		intsess.Close();  
		return -7;          //读写文件异常  
	}  
	END_CATCH  
		#endif
		return 0;  

}
//转载END/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
UINT CToolSPK::threadDownloadPackageList(PVOID para){
	CToolSPK *dlg = (CToolSPK*)para;
	CString URL = dlg->URLaddr + L"package.lst";
	if(dlg->serverChoose >=4 && dlg->serverChoose<=6)
		URL =  dlg->URLaddr + L"auto.lst";
	CString fileFour[8] = {L"(HF)package.lst", L"(HFC)package.lst",L"(RF)package.lst",L"(MF)package.lst",L"(WC1)auto.lst",L"(WC2)auto.lst",L"(SC)auto.lst",L"(Custom)package.lst"};
	dlg->m_eDownloadSPK.SetWindowText(L"正在下载列表喵……");
	if(0 == GetInternetFile(URL, dlg->localAddr+fileFour[dlg->m_cRec.GetCurSel()])){
		dlg->MessageBox(L"列表已下载喵！",L"提示喵");
		dlg->m_eDownloadSPK.SetWindowText(L"正在更新列表喵……");
		dlg->loadPackage();
		dlg->m_eDownloadSPK.SetWindowText(L"更新完毕喵，选择一个喵。");
	}else{
		dlg->MessageBox(L"下载失败喵！",L"提示喵");
		dlg->m_eSPK.SetWindowText(L"下载列表失败喵。");
	}
	return 0;
}
UINT CToolSPK::threadDownloadSPK(PVOID para){
	CToolSPK *dlg = (CToolSPK*)para;
	CString URL;
	int pos = dlg->m_lSPK.GetSelectionMark();
	dlg->m_eDownloadSPK.GetWindowText(URL);
	dlg->m_eSPK.SetWindowText(L"正在下载喵……");
	if(0 == GetInternetFile(URL, dlg->localAddrFileName)){
		dlg->MessageBox(L"下载完毕喵！",L"提示喵");
		dlg->m_eSPK.SetWindowText(dlg->localAddrFileName);
	}else{
		dlg->MessageBox(L"下载失败喵！",L"提示喵");
		dlg->m_eSPK.SetWindowText(L"下载失败喵。");
	}
	return 0;
}

void CToolSPK::OnBnClickedButton16(){
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(threadDownloadSPK, (PVOID)this);
}


void CToolSPK::OnBnClickedButton19(){
	// TODO: 打开其他SPK文件
	CString defExt = _T("SPK文件(*.SPK)|*.SPK");
	CString extFilter = _T("SPK文件(*.SPK)|*.SPK|TCT文件(*.TCT)|*.TCT||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_eSPK.SetWindowText(fileName);
	}
}


void CToolSPK::OnBnClickedButton17()
{
	// TODO: 解析SPK文件
	CString SPKfileName, NPKfileName, ext;
	m_eSPK.GetWindowText(SPKfileName);
	if(SPKfileName.GetLength() == 0){
		MessageBox(L"先从列表中下载或在本地中选择一个SPK或TCT文件喵！",L"提示喵");
		return;
	}
	NPKfileName = SPKfileName.Left(SPKfileName.GetLength()-4);
	ext = SPKfileName.Right(3);
	SPKobject so;
	TCTobject to;
	if(ext == L"TCT" || ext == L"tct"){
		if(!to.load(CStrToStr(SPKfileName))){
			MessageBox(L"无效的TCT文件喵！",L"提示喵");
			return;
		}
		to.makeNPK(CStrToStr(NPKfileName));
		to.release();
	}else{
		if(!so.load(CStrToStr(SPKfileName))){
			MessageBox(L"无效的SPK喵！",L"提示喵");
			return;
		}
		so.makeNPK(CStrToStr(NPKfileName));
		so.release();
	}
	MessageBox(L"已生成NPK喵！",L"提示喵");
	m_eConvertToNPK.SetWindowText(NPKfileName);
}


void CToolSPK::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	CString ext;
	if(serverChoose >=4 && serverChoose<=6){
		ext = L".tct";
	}else{
		ext = L".spk";
	}
	m_eDownloadSPK.SetWindowText(URLaddr + L"ImagePacks2/"+m_lSPK.GetItemText(row, 0)+ext);
	localAddrFileName = localAddr+m_lSPK.GetItemText(row, 0)+ext;
	*pResult = 0;
}


void CToolSPK::OnBnClickedButton20()
{
	// TODO: 使用EX打开
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	CString NPKfileName;
	m_eConvertToNPK.GetWindowText(NPKfileName);
	dlg->no.release();
	if(!dlg->no.loadFile(CStrToStr(NPKfileName))){
		MessageBox(L"无效的NPK喵！",L"提示喵");
		return;
	}
	dlg->fileNPKname = NPKfileName;
	dlg->saveAlert = false;
	MessageBox(L"已在EX里打开这个NPK喵！",L"提示喵");
	dlg->updateIMGlist();
	dlg->updateInfo();
}


void CToolSPK::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	CString keyWord;
	m_eKeyWord.GetWindowText(keyWord);

	str fileFour[8] = {"(HF)package.lst", "(HFC)package.lst","(RF)package.lst","(MF)package.lst","(WC1)auto.lst","(WC2)auto.lst","(SC)auto.lst","(Custom)package.lst"};
	LSTobject lo;
	LSTobjectGF lo2;
	LSTfolder lf;
	if(serverChoose >=4 && serverChoose<=6){
		if(lo2.load(CStrToStr(localAddr) + fileFour[m_cRec.GetCurSel()])){
			m_lSPK.DeleteAllItems();
			for(int i = 0;i<lo2.list.size();i++){
				CString nameStr;
				CString sizeStr;
				str name = (char*)lo2.list[i].name;
				nameStr = StrToCStr(name);
				if(nameStr.Find(keyWord) == -1){
					continue;
				}
				str size= (char*)lo2.list[i].lenStr;
				sizeStr = StrToCStr(size);
				int len = _ttoi(sizeStr);
				if(len > 1024 * 1024 * 10){
					sizeStr = NumToCStr(len / 1024 / 1024)+L" MB";
				}else if(len > 1024 * 10){
					sizeStr = NumToCStr(len / 1024)+L" KB";
				}else{
					sizeStr = NumToCStr(len)+L" B";
				}
				m_lSPK.EasyInsertItem(nameStr+L","+sizeStr);
			}
		}else{
			m_lSPK.DeleteAllItems();
			m_lSPK.EasyInsertItem(L"没有列表或列表文件已损坏，请更新NPK列表。,");
		}
	}else{
		if(lo.load(CStrToStr(localAddr) + fileFour[m_cRec.GetCurSel()])){
			if(lo.getImagePack2(lf)){
				m_lSPK.DeleteAllItems();
				for(int i = 0;i<lf.list.size();i++){
					CString nameStr;
					CString sizeStr;
					str name = (char*)lf.list[i].name;
					nameStr = StrToCStr(name);
					if(nameStr.Find(keyWord) == -1){
						continue;
					}
					if(lf.list[i].fileLen > 1024 * 1024 * 10){
						sizeStr = NumToCStr(lf.list[i].fileLen / 1024 / 1024)+L" MB";
					}else if(lf.list[i].fileLen > 1024 * 10){
						sizeStr = NumToCStr(lf.list[i].fileLen / 1024)+L" KB";
					}else{
						sizeStr = NumToCStr(lf.list[i].fileLen)+L" B";
					}
					m_lSPK.EasyInsertItem(nameStr+L","+sizeStr);
				}
			}else{
				m_lSPK.DeleteAllItems();
				m_lSPK.EasyInsertItem(L"列表中不包含I2文件夹。,");
			}
		}else{
			m_lSPK.DeleteAllItems();
			m_lSPK.EasyInsertItem(L"没有列表或列表文件已损坏，请更新NPK列表。,");
		}
	}
}


void CToolSPK::OnBnClickedButtonAddone()
{
	// TODO: 在此添加控件通知处理程序代码
	int selected = m_lSPK.GetSelectionMark();
	if(selected >= 0 && selected < m_lSPK.GetItemCount()){
		CString s = m_lSPK.GetItemText(selected, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->EasyInsertItem(s+L",等待");
	}
}


void CToolSPK::OnBnClickedButtonAddall()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int selected = 0;selected<m_lSPK.GetItemCount();selected++){
		CString s = m_lSPK.GetItemText(selected, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->EasyInsertItem(s+L",等待");
	}
}


void CToolSPK::OnBnClickedButtonRemoveone()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CGoodListCtrl, IDC_LIST3)->DeleteItem(GET_CTRL(CGoodListCtrl, IDC_LIST3)->GetItemCount()-1);
}


void CToolSPK::OnBnClickedButtonRemoveall()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CGoodListCtrl, IDC_LIST3)->DeleteAllItems();
}


void CToolSPK::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(threadDownloadSPKpatch, this);
}

UINT CToolSPK::threadDownloadSPKpatch(PVOID para){
	CToolSPK*dlg = (CToolSPK*)para;
	GET_DLG_CTRL(CButton, IDC_BUTTON_ADDONE)->EnableWindow(false);
	GET_DLG_CTRL(CButton, IDC_BUTTON_ADDALL)->EnableWindow(false);
	GET_DLG_CTRL(CButton, IDC_BUTTON_REMOVEONE)->EnableWindow(false);
	GET_DLG_CTRL(CButton, IDC_BUTTON_REMOVEALL)->EnableWindow(false);
	GET_DLG_CTRL(CButton, IDC_BUTTON4)->EnableWindow(false);
	dlg->downloadSPKpatch();
	GET_DLG_CTRL(CButton, IDC_BUTTON_ADDONE)->EnableWindow(true);
	GET_DLG_CTRL(CButton, IDC_BUTTON_ADDALL)->EnableWindow(true);
	GET_DLG_CTRL(CButton, IDC_BUTTON_REMOVEONE)->EnableWindow(true);
	GET_DLG_CTRL(CButton, IDC_BUTTON_REMOVEALL)->EnableWindow(true);
	GET_DLG_CTRL(CButton, IDC_BUTTON4)->EnableWindow(true);
	return 0U;
}

void CToolSPK::downloadSPKpatch(){
	int i;
	std::vector<CString> fileList;
	CString ext = (serverChoose >=4 && serverChoose<=6) ? L".tct":L".spk";
	for(i = 0;i<GET_CTRL(CGoodListCtrl, IDC_LIST3)->GetItemCount();i++)
		fileList.push_back(GET_CTRL(CGoodListCtrl, IDC_LIST3)->GetItemText(i,0));
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_DOWNLOAD_INFO)->SetPos(0);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(0);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_DOWNLOAD_INFO)->SetRange32(0, fileList.size());
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetRange32(0, fileList.size());
	for(i = 0;i<fileList.size();i++){
		GET_CTRL(CEdit, IDC_EDIT_DOWNLOAD_INFO)->SetWindowText(L"正在下载"+fileList[i]);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"下载中");
		CString URL = URLaddr + L"ImagePacks2/" + fileList[i] + ext;
		localAddrFileName = localAddr + fileList[i] + ext;
		if(0 != GetInternetFile(URL, localAddrFileName)){
			GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"下载失败");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_DOWNLOAD_INFO)->SetPos(i+1);
			continue;
		}
		GET_CTRL(CProgressCtrl, IDC_PROGRESS_DOWNLOAD_INFO)->SetPos(i+1);
		//解析
		CString NPKfileName = localAddrFileName.Left(localAddrFileName.GetLength() - 4);
		GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"正在解析"+fileList[i]);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"解析中");
		if(ext == L".TCT" || ext == L".tct"){
			TCTobject to;
			if(!to.load(CStrToStr(localAddrFileName))){
				GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"解析失败"+fileList[i]);
				GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"解析失败");
				GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
				continue;
			}
			to.makeNPK(CStrToStr(NPKfileName));
			GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"解析完毕"+fileList[i]);
			GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"解析成功");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
			continue;
		}
		if(ext == L".SPK" || ext == L".spk"){
			SPKobject so;
			if(!so.load(CStrToStr(localAddrFileName))){
				GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"解析失败"+fileList[i]);
				GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"解析失败");
				GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
				continue;
			}
			so.makeNPK(CStrToStr(NPKfileName));
			GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"解析完毕"+fileList[i]);
			GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"解析成功");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
			continue;
		}
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"解析失败");
		GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
	}
	GET_CTRL(CEdit, IDC_EDIT_DOWNLOAD_INFO)->SetWindowText(L"完成");
	GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"完成");
}