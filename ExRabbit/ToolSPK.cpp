// ToolSPK.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolSPK.h"
#include "afxdialogex.h"
#include <afxinet.h> 
#include "ExRabbitDlg.h"

// CToolSPK �Ի���

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


// CToolSPK ��Ϣ�������


BOOL CToolSPK::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
#ifndef DISABLE_TEST
	m_cRec.ResetContent();
	m_cRec.AddString(L"�����ͻ���");
	m_cRec.AddString(L"�������Է��ͻ���");
	m_cRec.AddString(L"�շ��ͻ���");
	m_cRec.AddString(L"�����ͻ���");
	m_cRec.AddString(L"����������1���ͻ���");
	m_cRec.AddString(L"����������2���ͻ���");
	m_cRec.AddString(L"�������֮�ǿͻ���");
	m_cRec.AddString(L"�Զ���URL");
	m_cRec.SetCurSel(0);

	m_lSPK.EasyInsertColumn(L"NPK�ļ���,320,��С,80");
	GET_CTRL(CGoodListCtrl, IDC_LIST3)->EasyInsertColumn(L"NPK�ļ���,260,״̬,70");
	serverChoose = 0;

	URLaddr = L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_hg/";
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CToolSPK::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}

void CToolSPK::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			m_lSPK.EasyInsertItem(L"û���б���б��ļ����𻵣������NPK�б�,");
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
				m_lSPK.EasyInsertItem(L"�б��в�������Ч�ļ��С�,");
			}
		}else{
			m_lSPK.DeleteAllItems();
			m_lSPK.EasyInsertItem(L"û���б���б��ļ����𻵣������NPK�б�,");
		}
	}
}
////////////////////////////////////////////////////////////////////////////
//���´�����Դ��https://blog.csdn.net/charlessimonyi/article/details/8666108
//���������������ļ�������//////////////////////////////////////////////////
INT CToolSPK::GetInternetFile(const CString strUrl,const CString strSavePath){
	#ifndef DISABLE_TEST
	if (strUrl.IsEmpty())  
		return -5;  
	if (strSavePath.IsEmpty())  
		return -6;  

	unsigned short nPort;       //���ڱ���Ŀ��HTTP����˿�  
	CString strServer, strObject;   //strServer���ڱ����������ַ��strObject���ڱ����ļ���������  
	DWORD dwServiceType,dwRet;      //dwServiceType���ڱ���������ͣ�dwRet���ڱ����ύGET���󷵻ص�״̬��  

	//����URL����ȡ��Ϣ  
	if(!AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort)){  
		//����ʧ�ܣ���Url����ȷ  
		return -1;  
	}  
	//�����������Ӷ���HTTP���Ӷ���ָ������ڸ����ӵ�HttpFile�ļ�����ָ�룬ע��delete  
	CInternetSession intsess;  
	CHttpFile *pHtFile = NULL;  
	//������������  
	CHttpConnection *pHtCon = intsess.GetHttpConnection(strServer,nPort);  
	if(pHtCon == NULL){  
		//������������ʧ��  
		intsess.Close();  
		return -2;  
	}  
	//����GET����  
	pHtFile = pHtCon->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject);  
	if(pHtFile == NULL){  
		//����GET����ʧ��  
		intsess.Close();  
		delete pHtCon;pHtCon = NULL;  
		return -3;  
	}  
	//�ύ����
	try{
		pHtFile->SendRequest();  
	}catch(CException *e){
		intsess.Close();
		delete pHtCon;pHtCon = NULL;  
		delete pHtFile;pHtFile = NULL;  
		return -8;  
	}
	//��ȡ���������ص�״̬��  
	pHtFile->QueryInfoStatusCode(dwRet);  
	if (dwRet != HTTP_STATUS_OK){  
		//����������������  
		intsess.Close();  
		delete pHtCon;pHtCon = NULL;  
		delete pHtFile;pHtFile = NULL;  
		return -4;  
	}  
	//��ȡ�ļ���С  
	UINT nFileLen = (UINT)pHtFile->GetLength();  
	DWORD dwRead = 1;       //���ڱ�ʶ���˶��٣�Ϊ1��Ϊ�˽���ѭ��  
	//����������  
	CHAR *szBuffer = new CHAR[nFileLen+1];  
	TRY
	{  
		//�����ļ�  
		CFile PicFile(strSavePath,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);  
		while(dwRead>0)  
		{    
			//��ջ�����  
			memset(szBuffer,0,(size_t)(nFileLen+1));  
			//��ȡ��������  
			dwRead = pHtFile->Read(szBuffer,nFileLen);   
			//д�뵽�ļ�  
			PicFile.Write(szBuffer,dwRead);  
		}  
		//�ر��ļ�  
		PicFile.Close();  
		//�ͷ��ڴ�  
		delete []szBuffer;  
		delete pHtFile;  
		delete pHtCon;  
		//�ر���������  
		intsess.Close();  
	}  
	CATCH(CFileException,e){  
		//�ͷ��ڴ�  
		delete []szBuffer;  
		delete pHtFile;  
		delete pHtCon;  
		//�ر���������  
		intsess.Close();  
		return -7;          //��д�ļ��쳣  
	}  
	END_CATCH  
		#endif
		return 0;  

}
//ת��END/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
UINT CToolSPK::threadDownloadPackageList(PVOID para){
	CToolSPK *dlg = (CToolSPK*)para;
	CString URL = dlg->URLaddr + L"package.lst";
	if(dlg->serverChoose >=4 && dlg->serverChoose<=6)
		URL =  dlg->URLaddr + L"auto.lst";
	CString fileFour[8] = {L"(HF)package.lst", L"(HFC)package.lst",L"(RF)package.lst",L"(MF)package.lst",L"(WC1)auto.lst",L"(WC2)auto.lst",L"(SC)auto.lst",L"(Custom)package.lst"};
	dlg->m_eDownloadSPK.SetWindowText(L"���������б�������");
	if(0 == GetInternetFile(URL, dlg->localAddr+fileFour[dlg->m_cRec.GetCurSel()])){
		dlg->MessageBox(L"�б�����������",L"��ʾ��");
		dlg->m_eDownloadSPK.SetWindowText(L"���ڸ����б�������");
		dlg->loadPackage();
		dlg->m_eDownloadSPK.SetWindowText(L"�����������ѡ��һ������");
	}else{
		dlg->MessageBox(L"����ʧ������",L"��ʾ��");
		dlg->m_eSPK.SetWindowText(L"�����б�ʧ������");
	}
	return 0;
}
UINT CToolSPK::threadDownloadSPK(PVOID para){
	CToolSPK *dlg = (CToolSPK*)para;
	CString URL;
	int pos = dlg->m_lSPK.GetSelectionMark();
	dlg->m_eDownloadSPK.GetWindowText(URL);
	dlg->m_eSPK.SetWindowText(L"��������������");
	if(0 == GetInternetFile(URL, dlg->localAddrFileName)){
		dlg->MessageBox(L"�����������",L"��ʾ��");
		dlg->m_eSPK.SetWindowText(dlg->localAddrFileName);
	}else{
		dlg->MessageBox(L"����ʧ������",L"��ʾ��");
		dlg->m_eSPK.SetWindowText(L"����ʧ������");
	}
	return 0;
}

void CToolSPK::OnBnClickedButton16(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxBeginThread(threadDownloadSPK, (PVOID)this);
}


void CToolSPK::OnBnClickedButton19(){
	// TODO: ������SPK�ļ�
	CString defExt = _T("SPK�ļ�(*.SPK)|*.SPK");
	CString extFilter = _T("SPK�ļ�(*.SPK)|*.SPK|TCT�ļ�(*.TCT)|*.TCT||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_eSPK.SetWindowText(fileName);
	}
}


void CToolSPK::OnBnClickedButton17()
{
	// TODO: ����SPK�ļ�
	CString SPKfileName, NPKfileName, ext;
	m_eSPK.GetWindowText(SPKfileName);
	if(SPKfileName.GetLength() == 0){
		MessageBox(L"�ȴ��б������ػ��ڱ�����ѡ��һ��SPK��TCT�ļ�����",L"��ʾ��");
		return;
	}
	NPKfileName = SPKfileName.Left(SPKfileName.GetLength()-4);
	ext = SPKfileName.Right(3);
	SPKobject so;
	TCTobject to;
	if(ext == L"TCT" || ext == L"tct"){
		if(!to.load(CStrToStr(SPKfileName))){
			MessageBox(L"��Ч��TCT�ļ�����",L"��ʾ��");
			return;
		}
		to.makeNPK(CStrToStr(NPKfileName));
		to.release();
	}else{
		if(!so.load(CStrToStr(SPKfileName))){
			MessageBox(L"��Ч��SPK����",L"��ʾ��");
			return;
		}
		so.makeNPK(CStrToStr(NPKfileName));
		so.release();
	}
	MessageBox(L"������NPK����",L"��ʾ��");
	m_eConvertToNPK.SetWindowText(NPKfileName);
}


void CToolSPK::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: ʹ��EX��
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	CString NPKfileName;
	m_eConvertToNPK.GetWindowText(NPKfileName);
	dlg->no.release();
	if(!dlg->no.loadFile(CStrToStr(NPKfileName))){
		MessageBox(L"��Ч��NPK����",L"��ʾ��");
		return;
	}
	dlg->fileNPKname = NPKfileName;
	dlg->saveAlert = false;
	MessageBox(L"����EX������NPK����",L"��ʾ��");
	dlg->updateIMGlist();
	dlg->updateInfo();
}


void CToolSPK::OnBnClickedButton22()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			m_lSPK.EasyInsertItem(L"û���б���б��ļ����𻵣������NPK�б�,");
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
				m_lSPK.EasyInsertItem(L"�б��в�����I2�ļ��С�,");
			}
		}else{
			m_lSPK.DeleteAllItems();
			m_lSPK.EasyInsertItem(L"û���б���б��ļ����𻵣������NPK�б�,");
		}
	}
}


void CToolSPK::OnBnClickedButtonAddone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int selected = m_lSPK.GetSelectionMark();
	if(selected >= 0 && selected < m_lSPK.GetItemCount()){
		CString s = m_lSPK.GetItemText(selected, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->EasyInsertItem(s+L",�ȴ�");
	}
}


void CToolSPK::OnBnClickedButtonAddall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int selected = 0;selected<m_lSPK.GetItemCount();selected++){
		CString s = m_lSPK.GetItemText(selected, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->EasyInsertItem(s+L",�ȴ�");
	}
}


void CToolSPK::OnBnClickedButtonRemoveone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CGoodListCtrl, IDC_LIST3)->DeleteItem(GET_CTRL(CGoodListCtrl, IDC_LIST3)->GetItemCount()-1);
}


void CToolSPK::OnBnClickedButtonRemoveall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CGoodListCtrl, IDC_LIST3)->DeleteAllItems();
}


void CToolSPK::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		GET_CTRL(CEdit, IDC_EDIT_DOWNLOAD_INFO)->SetWindowText(L"��������"+fileList[i]);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"������");
		CString URL = URLaddr + L"ImagePacks2/" + fileList[i] + ext;
		localAddrFileName = localAddr + fileList[i] + ext;
		if(0 != GetInternetFile(URL, localAddrFileName)){
			GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"����ʧ��");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_DOWNLOAD_INFO)->SetPos(i+1);
			continue;
		}
		GET_CTRL(CProgressCtrl, IDC_PROGRESS_DOWNLOAD_INFO)->SetPos(i+1);
		//����
		CString NPKfileName = localAddrFileName.Left(localAddrFileName.GetLength() - 4);
		GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"���ڽ���"+fileList[i]);
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"������");
		if(ext == L".TCT" || ext == L".tct"){
			TCTobject to;
			if(!to.load(CStrToStr(localAddrFileName))){
				GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"����ʧ��"+fileList[i]);
				GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"����ʧ��");
				GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
				continue;
			}
			to.makeNPK(CStrToStr(NPKfileName));
			GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"�������"+fileList[i]);
			GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"�����ɹ�");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
			continue;
		}
		if(ext == L".SPK" || ext == L".spk"){
			SPKobject so;
			if(!so.load(CStrToStr(localAddrFileName))){
				GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"����ʧ��"+fileList[i]);
				GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"����ʧ��");
				GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
				continue;
			}
			so.makeNPK(CStrToStr(NPKfileName));
			GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"�������"+fileList[i]);
			GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"�����ɹ�");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
			continue;
		}
		GET_CTRL(CGoodListCtrl, IDC_LIST3)->SetItemText(i,1, L"����ʧ��");
		GET_CTRL(CProgressCtrl, IDC_PROGRESS_PARSE_INFO)->SetPos(i+1);
	}
	GET_CTRL(CEdit, IDC_EDIT_DOWNLOAD_INFO)->SetWindowText(L"���");
	GET_CTRL(CEdit, IDC_EDIT_PARSE_INFO)->SetWindowText(L"���");
}