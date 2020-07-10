// ToolDownload.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolDownload.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"
#include <locale.h>
#include <thread>
#include "ModalSaveWarning.h"

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
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &ToolDownload::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_KEYWORD, &ToolDownload::OnBnClickedButtonKeyword)
	ON_BN_CLICKED(IDC_BUTTON_FOLDER, &ToolDownload::OnBnClickedButtonFolder)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &ToolDownload::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &ToolDownload::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_START, &ToolDownload::OnBnClickedButtonStart)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER, &ToolDownload::OnCbnSelchangeComboServer)
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
	GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->SetExtendedStyle(GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->InsertColumn(0, L"�ļ���", 0, 280);
	GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->InsertColumn(1, L"��С", 0, 60);
	GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD)->SetExtendedStyle(GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD)->GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT);
	GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD)->InsertColumn(0, L"�ļ���", 0, 220);
	GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD)->InsertColumn(1, L"��С", 0, 60);
	GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD)->InsertColumn(2, L"״̬", 0, 60);
	profile.loadProfile();
	LoadServerList(nullptr);
	StartThreadFunc(LoadFileList, L"");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

DefineThreadFunc(ToolDownload, LoadServerList, PVOID) {
	CString listFilePath = profile.getDownloadPath();
	CStdioFile listFile;
	if(listFile.Open(listFilePath + L"server_url.txt", CFile::modeRead)) {
		CString lineString;
		SERVER_INFO info;
		CHS_LOCALE_START;
		while(listFile.ReadString(lineString)) {
			if(lineString.Left(1) == L"[" && lineString.Right(1) == L"]") {
				lineString = lineString.Left(lineString.GetLength() - 1);
				lineString = lineString.Right(lineString.GetLength() - 1);
				if(lineString.GetLength() == 0)
					lineString = L"������";
				info.name = lineString;
				if(!listFile.ReadString(lineString))
					break;
				CString urlString, isTCTstring;
				AfxExtractSubString(urlString, lineString, 0, ',');
				AfxExtractSubString(isTCTstring, lineString, 1, ',');
				if(urlString.Left(1) == L"\"" && urlString.Right(1) == L"\"") {
					urlString = urlString.Left(urlString.GetLength() - 1);
					urlString = urlString.Right(urlString.GetLength() - 1);
					if(lineString.GetLength() == 0)
						continue;
					info.url = urlString;
				}
				info.isTCT = _ttoi(isTCTstring) == 1;
				serverList.push_back(info);
			}
		}
		CHS_LOCALE_END;
		listFile.Close();
		if(serverList.size() == 0) {
			if(IDYES == MessageBox(L"û�з������б���Ϣ���Ƿ�ʹ��Ĭ���б���Ϣ����", L"��ʾ��", MB_YESNO)) {
				goto read_list_fail;
			} else {
				OnCancel();
				return;
			}
		} else {
			for(int i = 0; i < serverList.size(); i++) {
				GET_CTRL(CComboBox, IDC_COMBO_SERVER)->AddString(serverList[i].name);
			}
			GET_CTRL(CComboBox, IDC_COMBO_SERVER)->SetCurSel(0);
		}
		return;
	} else {
		goto read_list_fail;
	}
read_list_fail:
	if(IDNO == MessageBox(L"û�з������б���Ϣ���Ƿ�����Ĭ�ϵķ������б���Ϣ����", L"��ʾ��", MB_YESNO)) {
		OnCancel();
		return;
	}
	if(listFile.Open(listFilePath + L"server_url.txt", CFile::modeWrite | CFile::modeCreate)) {
		SERVER_INFO info[9] = {
				{L"������ʽ��", L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_hg/", 0},
				{L"�������Է�", L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_open/", 0},
				{L"�շ�", L"http://webdown2.nexon.co.jp/arad/real/", 0},
				{L"����", L"http://download.dfoneople.com/Patch/", 0},
				{L"�������", L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp12.full.tct/", 1},
				{L"����ħ��", L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp56.full.tct/", 1},
				{L"����������1��", L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp1.full.tct/", 1},
				{L"����������2��", L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp2.full.tct/", 1},
				{L"�������֮��", L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp5.full.tct/", 1},
		};
		CHS_LOCALE_START;
		for(int i = 0; i < 9; i++) {
			CString lineStr = L"[" + info[i].name + L"]";
			listFile.WriteString(lineStr + L"\n");
			lineStr = L"\"" + info[i].url + L"\",";
			lineStr += info[i].isTCT ? L"1" : L"0";
			listFile.WriteString(lineStr + L"\n");
			serverList.push_back(info[i]);
		}
		CHS_LOCALE_END;
		listFile.Close();
		for(int i = 0; i < serverList.size(); i++) {
			GET_CTRL(CComboBox, IDC_COMBO_SERVER)->AddString(serverList[i].name);
		}
		GET_CTRL(CComboBox, IDC_COMBO_SERVER)->SetCurSel(0);
	} else {
		MessageBox(L"�޷���ȡ��Ҳ�޷�����Ĭ�Ϸ������б���");
		OnCancel();
	}
}

DefineThreadFunc(ToolDownload, LoadFileList, CString) {
	GET_CTRL(CComboBox, IDC_COMBO_SERVER)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_BUTTON_KEYWORD)->EnableWindow(FALSE);
	int s = GET_CTRL(CComboBox, IDC_COMBO_SERVER)->GetCurSel();
	if(s < 0 || s >= serverList.size())
		return;
	const SERVER_INFO &server = serverList[s];
	CString listFileName = profile.getDownloadPath(server.name) + (server.isTCT ? L"auto.lst" : L"package.lst");
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	lc->DeleteAllItems();
	if(server.isTCT) {
		//������Դ
		LSTobjectGF lo2;
		if(lo2.load(CStrToStr(listFileName))) {
			bar.show(lo2.list.size());
			for(int i = 0; i < lo2.list.size(); i++) {
				bar.setInfo(L"��ȡ�б�������", i);
				int count = lc->GetItemCount();
				CString nameStr;
				CString sizeStr;
				str name = (char*)lo2.list[i].name;
				nameStr = StrToCStr(name);
				if(para.GetLength() > 0 && -1 == nameStr.Find(para))
					continue;
				str size = (char*)lo2.list[i].lenStr;
				int len = _ttoi(StrToCStr(size));
				if((len >> 20) > 10) {
					sizeStr = NumToCStr(len >> 20) + L" MB";
				} else if((len >> 10) > 10) {
					sizeStr = NumToCStr(len >> 10) + L" KB";
				} else {
					sizeStr = NumToCStr(len) + L" B";
				}
				lc->InsertItem(count, nameStr);
				lc->SetItemText(count, 1, sizeStr);
			}
			bar.hide();
		} else {
			lc->InsertItem(0, L"δ�ҵ��б��ļ������ȡ�б�");
		}
	} else {
		LSTobject lo;
		LSTfolder lf;
		if(lo.load(CStrToStr(listFileName))) {
			if(!lo.getImagePack2(lf)) {
				lc->InsertItem(0, L"�б���δ���ҵ�ImagePack2�ļ��С�");
				GET_CTRL(CComboBox, IDC_COMBO_SERVER)->EnableWindow(TRUE);
				GET_CTRL(CButton, IDC_BUTTON_KEYWORD)->EnableWindow(TRUE);
				return;
			}
			bar.show(lf.list.size());
			for(int i = 0; i < lf.list.size(); i++) {
				bar.setInfo(L"��ȡ�б�������", i);
				int count = lc->GetItemCount();
				CString nameStr;
				CString sizeStr;
				str name = (char*)lf.list[i].name;
				nameStr = StrToCStr(name);
				if(para.GetLength() > 0 && -1 == nameStr.Find(para))
					continue;
				int len = lf.list[i].fileLen;
				if((len >> 20) > 10) {
					sizeStr = NumToCStr(len >> 20) + L" MB";
				} else if((len >> 10) > 10) {
					sizeStr = NumToCStr(len >> 10) + L" KB";
				} else {
					sizeStr = NumToCStr(len) + L" B";
				}
				lc->InsertItem(count, nameStr);
				lc->SetItemText(count, 1, sizeStr);
			}
			bar.hide();
		} else {
			lc->InsertItem(0, L"δ�ҵ��б��ļ������ȡ�б�");
		}
	}
	GET_CTRL(CComboBox, IDC_COMBO_SERVER)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON_KEYWORD)->EnableWindow(TRUE);
	//�鿴��û���ϴ����쳣�ж϶�δ����ɾ������־�ļ�
	loadRecord(server.name);
	if(record.fileName.size() != 0) {
		if(IDYES == MessageBox(L"�ϴ�����" + server.name + L"�ﻹ��δ��ɵ���������Ҫ��������", L"��ʾ��", MB_YESNO)) {
			CListCtrl *lco = GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD);
			lco->DeleteAllItems();
			for(int i = 0; i < record.fileName.size(); i++) {
				int count = lco->GetItemCount();
				lco->InsertItem(count, record.fileName[i]);
				lco->SetItemText(count, 1, record.fileLength[i]);
				lco->SetItemText(count, 2, L"�ȴ�������");
			}
			StartThreadFunc(DownloadFile, nullptr);
		} else {
			record.fileLength.clear();
			record.fileName.clear();
			record.completed.clear();
			removeRecord(server.name);
		}
	}
}
DefineThreadFunc(ToolDownload,DownloadListFile,PVOID) {
	int s = GET_CTRL(CComboBox, IDC_COMBO_SERVER)->GetCurSel();
	if(s < 0 || s >= serverList.size())
		return;
	const SERVER_INFO &server = serverList[s];
	CString sourStr = server.url + (server.isTCT ? L"auto.lst" : L"package.lst");
	CString destStr = profile.getDownloadPath(server.name) + (server.isTCT ? L"auto.lst" : L"package.lst");
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	lc->DeleteAllItems();
	lc->InsertItem(0, L"���ڻ�ȡ�б���");
	if(0 == GetInternetFile(sourStr, destStr)) {
		MessageBox(L"�б��ѻ�ȡ����", L"��ʾ��");
		LoadFileList(L"");
	} else {
		MessageBox(L"���֣��б��ȡʧ������", L"��ʾ��");
		lc->InsertItem(1, L"δ�ܻ�ȡ�б�");
	}
}

DefineThreadFunc(ToolDownload, DownloadFile, PVOID) {
	enableControls(FALSE);
	CListCtrl *lco = GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD);
	CProgressCtrl * pc = GET_CTRL(CProgressCtrl, IDC_PROGRESS);
	if(lco->GetItemCount() == 0) {
		MessageBox(L"��û��ѡ��Ҫ���ص��ļ�����", L"��ʾ��");
		enableControls(TRUE);
		return;
	}
	pc->SetRange32(0, lco->GetItemCount());
	pc->SetPos(0);
	int s = GET_CTRL(CComboBox, IDC_COMBO_SERVER)->GetCurSel();
	if(s < 0 || s >= serverList.size()) {
		MessageBox(L"��������������ȷ����", L"��ʾ��");
		enableControls(TRUE);
		return;
	}
	const SERVER_INFO &server = serverList[s];
	CString sourStr = server.url + L"ImagePacks2/";
	CString destStr = profile.getDownloadPath(server.name);
	int totalCount = 0;
	//���������б�
	updateRecord(server.name);
	//�����б������
	for(int i = 0; i < lco->GetItemCount(); i++) {
		CString sourStr = server.url + L"ImagePacks2/" + lco->GetItemText(i, 0) + (server.isTCT ? L".tct" : L".spk");
		CString destStr = profile.getDownloadPath(server.name) + lco->GetItemText(i, 0) + (server.isTCT ? L".tct" : L".spk");
		CString fileStr = profile.getDownloadPath(server.name) + lco->GetItemText(i, 0);
		lco->SetItemText(i, 2, L"������");
		pc->SetPos(i);
		if(0 != GetInternetFile(sourStr, destStr)) {
			lco->SetItemText(i, 2, L"����ʧ��");
			continue;
		}
		lco->SetItemText(i, 2, L"������");
		if(server.isTCT) {
			TCTobject to;
			if(!to.load(CStrToStr(destStr))) {
				lco->SetItemText(i, 2, L"����ʧ��");
				continue;
			}
			to.makeNPK(CStrToStr(fileStr));
			DeleteFile(destStr);
			lco->SetItemText(i, 2, L"�����");
		} else {
			SPKobject so;
			if(!so.load(CStrToStr(destStr))) {
				lco->SetItemText(i, 2, L"����ʧ��");
				continue;
			}
			so.makeNPK(CStrToStr(fileStr));
			DeleteFile(destStr);
			lco->SetItemText(i, 2, L"�����");
		}
		totalCount++;
		//�����б�
		record.completed[i] = 1;
		updateRecord(server.name);
	}
	pc->SetPos(lco->GetItemCount());
	MessageBox(L"�����������\r\n�ɹ�����" + NumToCStr(totalCount) + L"���ļ�����", L"��ʾ��");
	enableControls(TRUE);
	//ɾ���б����쳣�򲻻����е�����
	removeRecord(server.name);
}

void ToolDownload::OnBnClickedButtonGetList() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	StartThreadFunc(DownloadListFile, nullptr);
}


void ToolDownload::OnBnClickedButtonSetting() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL, L"open", profile.getDownloadPath() + L"server_url.txt", NULL, NULL, SW_NORMAL);
}


void ToolDownload::OnBnClickedButtonKeyword() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString keyWord;
	GET_CTRL(CEdit, IDC_EDIT_KEYWORD)->GetWindowText(keyWord);
	StartThreadFunc(LoadFileList, keyWord);
}

void ToolDownload::OnBnClickedButtonFolder() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int s = GET_CTRL(CComboBox, IDC_COMBO_SERVER)->GetCurSel();
	if(s < 0 || s >= serverList.size())
		return;
	ShellExecute(NULL, L"open", profile.getDownloadPath(serverList[s].name), NULL, NULL, SW_NORMAL);
}


void ToolDownload::OnBnClickedButtonOpen() {
	// TODO:  ����
	CListCtrl *lco = GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD);
	int row = lco->GetSelectionMark();
	if(row < 0 || row >= lco->GetItemCount()) {
		MessageBox(L"��ѡ��һ�����غõ��ļ�����", L"��ʾ��");
		return;
	}
	int s = GET_CTRL(CComboBox, IDC_COMBO_SERVER)->GetCurSel();
	if(s < 0 || s >= serverList.size())
		return;
	const SERVER_INFO &server = serverList[s];
	CString fileName = lco->GetItemText(row, 0);
	CString destStr = profile.getDownloadPath(server.name) + fileName;
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	if(dlg->NPKsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = dlg->IMGsaveAlert ? ModalSaveWarning::MODIFIED_IMG_NPK : ModalSaveWarning::MODIFIED_NPK;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			dlg->IMGsaveAlert = FALSE;
			dlg->NPKsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			dlg->no.saveFile(CStrToStr(dlg->fileNPKname));
			dlg->IMGsaveAlert = FALSE;
			dlg->NPKsaveAlert = FALSE;
			dlg->updateInfo();
			break;
		case ModalSaveWarning::RETURN_ALL_SAVE:
			dlg->no.IMGreplace(dlg->crtIMGid, dlg->io);
			dlg->no.saveFile(CStrToStr(dlg->fileNPKname));
			dlg->IMGsaveAlert = FALSE;
			dlg->NPKsaveAlert = FALSE;
			dlg->updateInfo();
			break;
		}
	}
	dlg->no.release();
	if(!dlg->no.loadFile(CStrToStr(destStr))) {
		MessageBox(L"���ļ��޷�ʶ������", L"��ʾ��");
	} else {
		dlg->fileNPKname = destStr;
		dlg->IMGsaveAlert = false;
		dlg->updateIMGlist();
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
	CListCtrl *lci = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	CListCtrl *lco = GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD);
	record.fileName.clear();
	record.fileLength.clear();
	record.completed.clear();
	for(int i = 0; i < lci->GetItemCount(); i++) {
		if(lci->GetCheck(i)) {
			CString itemStr = lci->GetItemText(i, 0);
			CString sizeStr = lci->GetItemText(i, 1);
			int count = lco->GetItemCount();
			lco->InsertItem(count, lci->GetItemText(i, 0));
			lco->SetItemText(count, 1, lci->GetItemText(i, 1));
			lco->SetItemText(count, 2, L"�ȴ�������");
			record.fileName.push_back(itemStr);
			record.fileLength.push_back(sizeStr);
			record.completed.push_back(0);
		}
	}
	StartThreadFunc(DownloadFile, nullptr);
}

void ToolDownload::OnCbnSelchangeComboServer() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	StartThreadFunc(LoadFileList, L"");
}

void ToolDownload::loadRecord(const CString &serverName) {
	CFile file;
	record.fileLength.clear();
	record.fileName.clear();
	record.completed.clear();
	if(file.Open(profile.getDownloadPath(serverName) + L"record.lsn", CFile::modeRead)) {
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
void ToolDownload::updateRecord(const CString &serverName) {
	CFile file;
	file.Open(profile.getDownloadPath(serverName) + L"record.lsn", CFile::modeCreate | CFile::modeWrite);
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
void ToolDownload::removeRecord(const CString &serverName) {
	DeleteFile(profile.getDownloadPath(serverName) + L"record.lsn");
}

void ToolDownload::enableControls(BOOL b) {
	GET_CTRL(CButton, IDC_BUTTON_START)->EnableWindow(b);
	GET_CTRL(CButton, IDC_COMBO_SERVER)->EnableWindow(b);
	GET_CTRL(CButton, IDC_BUTTON_GET_LIST)->EnableWindow(b);
	GET_CTRL(CButton, IDC_BUTTON_SETTING)->EnableWindow(b);
	GET_CTRL(CButton, IDC_BUTTON_OPEN)->EnableWindow(b);
	GET_CTRL(CButton, IDC_BUTTON_EXIT)->EnableWindow(b);
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
