// ToolDownload.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolDownload.h"
#include "afxdialogex.h"
#include <locale.h>
#include <thread>
#include "ModalSaveWarning.h"

#ifdef BLACK_CAT
#include "ExRabbitDlg.h"
#define PROFILE_TYPE			ProfileBlack
#define DIALOG_TYPE				CExRabbitDlg
#define ELM(x)					IMG##x
#define LST_LOAD				getImagePack2
#define LST_LOAD_GF				load
#define INTERNET_FOLDER			_T("ImagePacks2/")
#define RECORD_FILE_NM			_T("record.lsn")
#define LIST_FILE_NM			_T("list_img.lst")
#endif

#ifdef WHITE_CAT
#include "ExParrotDlg.h"
#define PROFILE_TYPE			ProfileWhite
#define DIALOG_TYPE				CExParrotDlg
#define ELM(x)					SND##x
#define LST_LOAD				getSoundPack
#define LST_LOAD_GF				load2
#define INTERNET_FOLDER			_T("SoundPacks/")
#define RECORD_FILE_NM			_T("record.lso")
#define LIST_FILE_NM			_T("list_ogg.lst")
#endif

// ToolDownload �Ի���
using namespace KoishiExpand::KoishiDownloadTool;
IMPLEMENT_DYNAMIC(ToolDownload, CDialogEx)

ToolDownload::ToolDownload(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolDownload::IDD, pParent)
{

}

ToolDownload::~ToolDownload()
{
}

void ToolDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolDownload, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET_LIST, &ToolDownload::OnBnClickedButtonGetList)
	ON_BN_CLICKED(IDC_BUTTON_KEYWORD, &ToolDownload::OnBnClickedButtonKeyword)
	ON_BN_CLICKED(IDC_BUTTON_FOLDER, &ToolDownload::OnBnClickedButtonFolder)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &ToolDownload::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &ToolDownload::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_START, &ToolDownload::OnBnClickedButtonStart)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ORIGIN, &ToolDownload::OnNMRClickListOrigin)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ORIGIN, &ToolDownload::OnNMClickListOrigin)
	ON_COMMAND(ID_CLICK_SELECT_ALL, &ToolDownload::OnClickSelectAll)
	ON_COMMAND(ID_CLICK_SELECT_REVERSE, &ToolDownload::OnClickSelectReverse)
	ON_COMMAND(ID_CLICK_SELECT_HIGHLINE, &ToolDownload::OnClickSelectHighline)
END_MESSAGE_MAP()


// ToolDownload ��Ϣ�������


BOOL ToolDownload::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CREATEW(bar, IDD_TINY_PROGRESSBAR);

	lcIn = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	lcOut = GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD);
	lcIn->SetExtendedStyle(lcIn->GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	lcIn->InsertColumn(0, L"�ļ���", 0, 280);
	lcIn->InsertColumn(1, L"��С", 0, 60);
	lcOut->SetExtendedStyle(lcOut->GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT);
	lcOut->InsertColumn(0, L"�ļ���", 0, 220);
	lcOut->InsertColumn(1, L"��С", 0, 60);
	lcOut->InsertColumn(2, L"״̬", 0, 60);
	lcOut->ShowWindow(SW_HIDE);

	PROFILE_TYPE profile;
	profile.loadProfile();
	folderName = profile.getDownloadPath(serverInfo.region + L"-" + serverInfo.name);
	recordFileName = folderName + RECORD_FILE_NM;
	listFileName = folderName + LIST_FILE_NM;
	skipExistedFile = 0;
	StartThreadFunc(Initial, nullptr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void ToolDownload::Initial(PVOID) {
	//��ʼ����顤�ȼ����������б��ټ���б��ļ�
	//�鿴��û���ϴ����쳣�ж϶�δ����ɾ������־�ļ�
	loadRecord();
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڼ���δ��ɵ�����������");
	if(record.fileName.size() != 0) {
		if(IDYES == MessageBox(L"�ϴ���������������ﻹ��δ��ɵ���������Ҫ��������", L"��ʾ��", MB_YESNO)) {
			StartThreadFunc(DownloadFile, nullptr);
			return;
		} else {
			record.fileLength.clear();
			record.fileName.clear();
			record.completed.clear();
			removeRecord();
		}
	} 
	//����ļ��б�
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڼ����ļ��б�������");
	CStdioFile file;
	if(!file.Open(listFileName, CFile::modeRead)) {
		MessageBox(L"û���ҵ��ļ��б���������ȡ�ļ��б�����ȡ�����ļ�����", L"��ʾ��");
		GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"δ�������ļ��б������Ҳࡰ��ȡ�ļ��б�����");
		return;
	}
	fileNameList.clear();
	fileSizeList.clear();
	CString lineStr, nameStr, sizeStr;
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڵ����ļ��б�������");
	while(file.ReadString(lineStr)) {
		AfxExtractSubString(nameStr, lineStr, 0, ',');
		AfxExtractSubString(sizeStr, lineStr, 1, ',');
		int len = _ttoi(sizeStr);
		if((len >> 20) > 10) {
			sizeStr = NumToCStr(len >> 20) + L" MB";
		} else if((len >> 10) > 10) {
			sizeStr = NumToCStr(len >> 10) + L" KB";
		} else {
			sizeStr = NumToCStr(len) + L" B";
		}
		fileNameList.push_back(nameStr);
		fileSizeList.push_back(sizeStr);
	}
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڸ����б�������");
	QueryFile(L"");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"����ɳ�ʼ������ӭʹ�÷��������ع�������");
}
void ToolDownload::QueryFile(CString para) {
	lcIn->ShowWindow(SW_SHOW);
	lcOut->ShowWindow(SW_HIDE);
	lcIn->DeleteAllItems();
	for(int i = 0; i < fileNameList.size(); i++) {
		if(para.GetLength() > 0 && -1 == fileNameList[i].Find(para))
			continue;
		int count = lcIn->GetItemCount();
		lcIn->InsertItem(count, fileNameList[i]);
		lcIn->SetItemText(count, 1, fileSizeList[i]);
	}
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"��������������ҵ�"+NumToCStr(lcIn->GetItemCount())+L"���롰"+para+L"����ص�NPK�ļ�����");
}
void ToolDownload::DownloadListFile(PVOID) {
	CString sourStr = serverInfo.url + (serverInfo.isTCT ? L"auto.lst" : L"package.lst");
	CString destStr = folderName + (serverInfo.isTCT ? L"auto.lst" : L"package.lst");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"����������������ļ��б�������");
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"��������" + sourStr + L"������");
	if(0 != GetInternetFile(sourStr, destStr)) {
		MessageBox(L"���֣��б��ȡʧ������������������", L"��ʾ��");
		GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"404 NOT FOUND MEOW����");
		GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"������ʧ�ܡ�");
		return;
	}
	if(serverInfo.isTCT) {
		//������Դ
		LSTobjectGF lo2;
		if(!lo2.LST_LOAD_GF(CStrToStr(destStr))) {
			MessageBox(L"���֣��б����ʧ������һ�����ǹٷ�����������", L"��ʾ��");
			GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"�޷��������б��ļ�����������");
			GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"������ʧ�ܡ�");
			return;
		}
		bar.show(lo2.list.size());
		CStdioFile file;
		file.Open(listFileName, CFile::modeCreate | CFile::modeWrite);
		CHS_LOCALE_START;
		for(int i = 0; i < lo2.list.size(); i++) {
			bar.setInfo(L"���������б��ļ�������", i);
			str name = (char*)lo2.list[i].name;
			CString nameStr, sizeStr;
			nameStr = StrToCStr(name);
			str size = (char*)lo2.list[i].lenStr;
			sizeStr = StrToCStr(size);
			file.WriteString(nameStr + L"," + sizeStr + L"\n");
		}
		CHS_LOCALE_END;
		file.Close();
		bar.hide();
	} else {
		LSTobject lo;
		LSTfolder lf;
		if(!lo.load(CStrToStr(destStr))) {
			MessageBox(L"���֣��б����ʧ������һ�����ǹٷ�����������", L"��ʾ��");
			GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"�޷��������б��ļ�����������");
			GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"������ʧ�ܡ�");
			return;
		}
		if(!lo.LST_LOAD(lf)) {
			MessageBox(L"���֣��б����ʧ������һ�����ǹٷ�����������", L"��ʾ��");
			GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"�޷��������б��ļ�����������");
			GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"������ʧ�ܡ�");
			return;
		}
		bar.show(lf.list.size());
		CStdioFile file;
		file.Open(listFileName, CFile::modeCreate | CFile::modeWrite);
		CHS_LOCALE_START;
		for(int i = 0; i < lf.list.size(); i++) {
			bar.setInfo(L"���������б��ļ�������", i);
			CString nameStr, sizeStr;
			str name = (char*)lf.list[i].name;
			nameStr = StrToCStr(name);
			sizeStr = NumToCStr(lf.list[i].fileLen);
			file.WriteString(nameStr + L"," + sizeStr + L"\n");
		}
		CHS_LOCALE_END;
		file.Close();
		bar.hide();
	}

	CStdioFile file;
	file.Open(listFileName, CFile::modeRead);
	fileNameList.clear();
	fileSizeList.clear();
	CString lineStr, nameStr, sizeStr;
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڵ����ļ��б�������");
	while(file.ReadString(lineStr)) {
		AfxExtractSubString(nameStr, lineStr, 0, ',');
		AfxExtractSubString(sizeStr, lineStr, 1, ',');
		int len = _ttoi(sizeStr);
		if((len >> 20) > 10) {
			sizeStr = NumToCStr(len >> 20) + L" MB";
		} else if((len >> 10) > 10) {
			sizeStr = NumToCStr(len >> 10) + L" KB";
		} else {
			sizeStr = NumToCStr(len) + L" B";
		}
		fileNameList.push_back(nameStr);
		fileSizeList.push_back(sizeStr);
	}
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڸ����б�������");
	QueryFile(L"");
	MessageBox(L"�б��ѳɹ���ȡ����", L"��ʾ��");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڷ�������ȡ���б�");
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"����ɡ�");
	QueryFile(L"");
}

void ToolDownload::DownloadFile(PVOID) {
	CProgressCtrl * pc = GET_CTRL(CProgressCtrl, IDC_PROGRESS);
	if(!record.fileName.size()) {
		MessageBox(L"��û��ѡ��Ҫ���ص��ļ�����", L"��ʾ��");
		return;
	}
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"���ڴ��������б�������");
	lcIn->ShowWindow(SW_HIDE);
	lcOut->ShowWindow(SW_SHOW);
	lcOut->DeleteAllItems();
	for(int i = 0; i < record.fileName.size(); i++) {
		int count = lcOut->GetItemCount();
		lcOut->InsertItem(count, record.fileName[i]);
		lcOut->SetItemText(count, 1, record.fileLength[i]);
		lcOut->SetItemText(count, 2, L"�ȴ�������");
	}
	pc->SetRange32(0, lcOut->GetItemCount());
	pc->SetPos(0);
	int totalCount = 0;
	//���������б�
	updateRecord();
	//�����б������
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"��������������");
	for(int i = 0; i < lcOut->GetItemCount(); i++) {
		CString sourStr = serverInfo.url + INTERNET_FOLDER + lcOut->GetItemText(i, 0) + (serverInfo.isTCT ? L".tct" : L".spk");
		CString destStr = folderName + lcOut->GetItemText(i, 0) + (serverInfo.isTCT ? L".tct" : L".spk");
		CString fileStr = folderName + lcOut->GetItemText(i, 0);
		GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"��������" + sourStr + L"������");
		if(skipExistedFile == 0) {
			//������⡤δ��ʾ
			CFile tryOpen;
			if(tryOpen.Open(fileStr, CFile::modeRead)) {
				//�������
				tryOpen.Close();
				if(IDYES == MessageBox(L"�����Ѵ��ڵ��ļ���Ҫ�滻����\r\nѡ���ǡ���һֱ�滻����\r\nѡ�񡰷���һֱ��������", L"��ʾ��", MB_YESNO)) {
					skipExistedFile = 2;
				} else {
					skipExistedFile = 1;
					lcOut->SetItemText(i, 2, L"��������");
					continue;
				}
			}
		} else if(skipExistedFile == 1) {
			CFile tryOpen;
			if(tryOpen.Open(fileStr, CFile::modeRead)) {
				tryOpen.Close();
				lcOut->SetItemText(i, 2, L"��������");
				continue;
			}
		}
		lcOut->SetItemText(i, 2, L"������");
		pc->SetPos(i);
		if(0 != GetInternetFile(sourStr, destStr)) {
			lcOut->SetItemText(i, 2, L"����ʧ��");
			continue;
		}
		lcOut->SetItemText(i, 2, L"������");
		if(serverInfo.isTCT) {
			TCTobject to;
			if(!to.load(CStrToStr(destStr))) {
				lcOut->SetItemText(i, 2, L"����ʧ��");
				continue;
			}
			to.makeNPK(CStrToStr(fileStr));
			DeleteFile(destStr);
			lcOut->SetItemText(i, 2, L"�����");
		} else {
			SPKobject so;
			if(!so.load(CStrToStr(destStr))) {
				lcOut->SetItemText(i, 2, L"����ʧ��");
				continue;
			}
			so.makeNPK(CStrToStr(fileStr));
			DeleteFile(destStr);
			lcOut->SetItemText(i, 2, L"�����");
		}
		totalCount++;
		//�����б�
		record.completed[i] = 1;
		updateRecord();
	}
	pc->SetPos(lcOut->GetItemCount());
	MessageBox(L"�����������\r\n�ɹ�����" + NumToCStr(totalCount) + L"���ļ�����", L"��ʾ��");
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"������������ɹ�����" + NumToCStr(totalCount) + L"���ļ�����");

	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"�������������");
	//ɾ���б����쳣�򲻻����е�����
	removeRecord();
}

void ToolDownload::OnBnClickedButtonGetList() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	StartThreadFunc(DownloadListFile, nullptr);
}

void ToolDownload::OnBnClickedButtonKeyword() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString keyWord;
	GET_CTRL(CEdit, IDC_EDIT_KEYWORD)->GetWindowText(keyWord);
	StartThreadFunc(QueryFile, keyWord);
}

void ToolDownload::OnBnClickedButtonFolder() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL, L"open", folderName, NULL, NULL, SW_NORMAL);
}


void ToolDownload::OnBnClickedButtonOpen() {
	// TODO:  ����
	int row = lcOut->GetSelectionMark();
	if(row < 0 || row >= lcOut->GetItemCount()) {
		MessageBox(L"��ѡ��һ�����غõ��ļ�����", L"��ʾ��");
		return;
	}
	CString fileName = lcOut->GetItemText(row, 0);
	CString destStr = folderName + fileName;
	DIALOG_TYPE *dlg = (DIALOG_TYPE*)context;
	dlg->no.release();
	if(!dlg->no.loadFile(CStrToStr(destStr))) {
		MessageBox(L"���ļ��޷�ʶ������", L"��ʾ��");
	} else {
		dlg->fileNPKname = destStr;
		dlg->ELM(saveAlert) = false;
		dlg->ELM(loadList)();
		dlg->updateInfo();
		MessageBox(L"���ļ�����EX�д�������", L"��ʾ��");
	}
}


void ToolDownload::OnBnClickedButtonExit() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void ToolDownload::OnBnClickedButtonStart() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	record.fileName.clear();
	record.fileLength.clear();
	record.completed.clear();
	for(int i = 0; i < lcIn->GetItemCount(); i++) {
		if(lcIn->GetCheck(i)) {
			CString itemStr = lcIn->GetItemText(i, 0);
			CString sizeStr = lcIn->GetItemText(i, 1);
			record.fileName.push_back(itemStr);
			record.fileLength.push_back(sizeStr);
			record.completed.push_back(0);
		}
	}
	StartThreadFunc(DownloadFile, nullptr);
}

void ToolDownload::loadRecord() {
	CFile file;
	record.fileLength.clear();
	record.fileName.clear();
	record.completed.clear();
	if(file.Open(recordFileName, CFile::modeRead)) {
		while(true) {
			char len = 0;
			char buf[0xFF];
			CString rn, rl;
			memset(buf, 0, 0xFF);
			file.Read(&len, 1);
			if(!len)
				break;
			file.Read(buf, len);
			rn = StrToCStr(str(buf));
			memset(buf, 0, 0xFF);
			file.Read(&len, 1);
			if(!len)
				break;
			file.Read(buf, len);
			rl = StrToCStr(str(buf));
			file.Read(&len, 1);
			if(!len) {
				record.fileName.push_back(rn);
				record.fileLength.push_back(rl);
				record.completed.push_back(0);
			}
		}
		file.Close();
	}
}
void ToolDownload::updateRecord() {
	CFile file;
	file.Open(recordFileName, CFile::modeCreate | CFile::modeWrite);
	for(int i = 0; i < record.fileName.size(); i++) {
		char len = 0;
		str ss = CStrToStr(record.fileName[i]);
		len = ss.size();
		file.Write(&len, 1);
		file.Write(ss.data(), len);
		ss = CStrToStr(record.fileLength[i]);
		len = ss.size();
		file.Write(&len, 1);
		file.Write(ss.data(), len);
		len = record.completed[i] ? 1 : 0;
		file.Write(&len, 1);
	}
	file.Close();
}
void ToolDownload::removeRecord() {
	DeleteFile(recordFileName);
}

void ToolDownload::OnNMRClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU_DOWNLOAD);
	pPopup = menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}


void ToolDownload::OnNMClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CHECK_VALID(pNMListView->iItem >= 0);
	int row = pNMListView->iItem;
	BOOL b = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->GetCheck(row);
	GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->SetCheck(row, !b);
	*pResult = 0;
}


void ToolDownload::OnClickSelectAll() {
	// TODO:  �ڴ���������������
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	for(int i = 0; i < lc->GetItemCount();i++) {
		lc->SetCheck(i, TRUE);
	}
}


void ToolDownload::OnClickSelectReverse() {
	// TODO:  �ڴ���������������
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	for(int i = 0; i < lc->GetItemCount(); i++) {
		lc->SetCheck(i, !(lc->GetCheck(i)));
	}
}


void ToolDownload::OnClickSelectHighline() {
	// TODO:  �ڴ���������������
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	for(int i = 0; i < lc->GetItemCount(); i++) {
		if(lc->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			lc->SetCheck(i, TRUE);
		}
	}
}


void ToolDownload::OnOK() {
	// TODO:  �ڴ����ר�ô����/����û���

	// CDialogEx::OnOK();
}
