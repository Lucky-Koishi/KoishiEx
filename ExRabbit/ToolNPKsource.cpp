// ToolNPKsource.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "ToolNPKsource.h"
#include "afxdialogex.h"
#include <thread>

// ToolNPKsource �Ի���

IMPLEMENT_DYNAMIC(ToolNPKsource, CDialogEx)

ToolNPKsource::ToolNPKsource(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolNPKsource::IDD, pParent)
{

}

ToolNPKsource::~ToolNPKsource()
{
}

void ToolNPKsource::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolNPKsource, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, &ToolNPKsource::OnBnClickedButtonInitial)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FOLDER, &ToolNPKsource::OnBnClickedButtonOpenFolder)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &ToolNPKsource::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_EXPLORE, &ToolNPKsource::OnBnClickedButtonExplore)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &ToolNPKsource::OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_PATH, &ToolNPKsource::OnBnClickedButtonQueryPath)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_AND, &ToolNPKsource::OnBnClickedButtonSearchAnd)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &ToolNPKsource::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDCANCEL, &ToolNPKsource::OnBnClickedCancel)
	ON_COMMAND(ID_IMPORT_1, &ToolNPKsource::OnImport1)
	ON_COMMAND(ID_IMPORT_2, &ToolNPKsource::OnImport2)
	ON_COMMAND(ID_IMG_MODIFY1, &ToolNPKsource::OnImgModify1)
	ON_COMMAND(ID_IMG_MODIFY2, &ToolNPKsource::OnImgModify2)
	ON_COMMAND(ID_IMG_MODIFY3, &ToolNPKsource::OnImgModify3)
	ON_COMMAND(ID_IMG_MODIFY_PATCH1, &ToolNPKsource::OnImgModifyPatch1)
	ON_COMMAND(ID_IMG_MODIFY_PATCH2, &ToolNPKsource::OnImgModifyPatch2)
	ON_COMMAND(ID_IMG_MODIFY_PATCH3, &ToolNPKsource::OnImgModifyPatch3)
END_MESSAGE_MAP()


// ToolNPKsource ��Ϣ�������


BOOL ToolNPKsource::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ProfileBlack profile;
	profile.loadProfile();
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(profile.getSourcePath());
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"���ڳ�ʼ������");
	GET_CTRL(CListCtrl, IDC_LIST1)->InsertColumn(0, L"NPK�ļ���", 0, 400);
	GET_CTRL(CListCtrl, IDC_LIST1)->InsertColumn(1, L"����", 0, 400);
	StartThreadFunc(initialTool, nullptr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ToolNPKsource::OnBnClickedButtonInitial() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString folderName;
	ProfileBlack profile;
	profile.loadProfile();
	CALL_FOLDER_DIALOG(folderName, L"ѡ���ļ�����", L"��ʾ��", L"��������Ч���ļ�����");
	if(folderName.GetLength() > 0) {
		profile.sourcePath = folderName;
		profile.saveProfile();
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(folderName + L"\\");
		StartThreadFunc(generateMapFile, folderName);
	}
}


void ToolNPKsource::OnBnClickedButtonOpenFolder() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ProfileBlack profile;
	profile.loadProfile();
	ShellExecute(NULL, L"open", profile.getSourcePath(), NULL, NULL, SW_SHOWNORMAL);
}


void ToolNPKsource::OnBnClickedButtonImport() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU_NPK_SOURCE);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}


void ToolNPKsource::OnBnClickedButtonExplore() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ProfileBlack profile;
	profile.loadProfile();
	ShellExecute(NULL, L"open", profile.getSupportPath() + L"npkdict.txt", NULL, NULL, SW_SHOWNORMAL);
}


void ToolNPKsource::OnBnClickedButtonQuery() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString keyWord;
	GET_CTRL(CEdit, IDC_EDIT3)->GetWindowText(keyWord);
	StartThreadFunc(queryDict, keyWord);
}


void ToolNPKsource::OnBnClickedButtonQueryPath() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString keyWord;
	GET_CTRL(CEdit, IDC_EDIT3)->GetWindowText(keyWord);
	StartThreadFunc(queryMap, keyWord);
}


void ToolNPKsource::OnBnClickedButtonSearchAnd() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU_NPK_SOURCE);
	pPopup = menu.GetSubMenu(1);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}


void ToolNPKsource::OnBnClickedButtonOpen() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	ProfileBlack profile;
	auto listCtl = GET_CTRL(CListCtrl, IDC_LIST1);
	CString fileName = listCtl->GetItemText(listCtl->GetSelectionMark(), 0);
	profile.loadProfile();
	fileName = profile.getSourcePath() + fileName;
	CFile file;
	if(file.Open(fileName, CFile::modeRead)) {
		file.Close();
		dlg->no.release();
		dlg->no.loadFile(CStrToStr(fileName));
		dlg->fileNPKname = fileName;
		dlg->IMGsaveAlert = false;
		MessageBox(L"�Ѿ�����ѡ�ļ�����", L"��ʾ��");
		dlg->IMGloadList();
		dlg->updateInfo();
	} else {
		MessageBox(L"��Դ�ļ����в�����ѡ���ļ�����", L"��ʾ��");
	}
}


void ToolNPKsource::OnBnClickedCancel() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void ToolNPKsource::OnImport1() {
	// TODO:  �ڴ���������������
	CString defExt = L"NPK�ǵ��ļ�(*.TXT)|*.TXT";
	CString extFilter = L"NPK�ǵ��ļ�(*.TXT)|*.TXT||";
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		StartThreadFunc(loadOtherDictFile, dlg.GetPathName());
	}
}


void ToolNPKsource::OnImport2() {
	// TODO:  �ڴ���������������
	CString defExt = L"����-��˵�ṩ���ļ�(*.TXT)|*.TXT";
	CString extFilter = L"����-��˵�ṩ���ļ�(*.TXT)|*.TXT||";
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		StartThreadFunc(loadSomebodysFile, dlg.GetPathName());
	}
}


void ToolNPKsource::OnImgModify1() {
	// TODO:  �ڴ���������������
	mode = 'r';
	isPatch = FALSE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModify2() {
	// TODO:  �ڴ���������������
	mode = 'a';
	isPatch = FALSE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModify3() {
	// TODO:  �ڴ���������������
	mode = 'c';
	isPatch = FALSE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModifyPatch1() {
	// TODO:  �ڴ���������������
	mode = 'r';
	isPatch = TRUE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModifyPatch2() {
	// TODO:  �ڴ���������������
	mode = 'a';
	isPatch = TRUE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModifyPatch3() {
	// TODO:  �ڴ���������������
	mode = 'c';
	isPatch = TRUE;
	StartThreadFunc(fixIMG, nullptr);
}

void ToolNPKsource::initialTool(PVOID) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_SHOW);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_HIDE);
	loadMapFile(nullptr);
	loadDictFile(nullptr);
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	if(listMap.size() == 0) {
		if(IDYES == MessageBox(L"�״�ʹ�����������Ҫ���г�ʼ�������ܻỨ��ʱ�䣬ȷ������\r\n(ʹ��IMG��λ��IMG�޸�����)", L"��ʾ��", MB_YESNO)) {
			OnBnClickedButtonInitial();
		}
	}
	
}

void ToolNPKsource::generateMapFile(CString folders) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_SHOW);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_HIDE);
	addInfo(L"��ȡ��ԴĿ¼�У������ĵȴ���");
	CString folderName = folders + L"\\sprite_*.NPK";
	CFileFind fileFind;
	std::vector<CString> fileList;
	std::vector<CString> pathList;
	BOOL ret = fileFind.FindFile(folderName);
	while(ret) {
		ret = fileFind.FindNextFile();
		fileList.push_back(fileFind.GetFileName());
		pathList.push_back(fileFind.GetFilePath());
	}
	ProfileBlack profile;
	CStdioFile mapFile;
	profile.loadProfile();
	mapFile.Open(profile.getSupportPath() + L"npkmap.txt", CFile::modeCreate | CFile::modeWrite);
	CHS_LOCALE_START;
	listMap.clear();
	addInfo(L"��ʼ����ӳ���ļ���");
	for(long i = 0; i < pathList.size();i++) {
		NPKobject no;
		if(!no.loadEntry(CStrToStr(pathList[i])))
		   continue;
		for(long j = 0; j < no.content.size(); j++) {
			ToolNPK_Nmap newMap;
			newMap.fileName = fileList[i];
			newMap.path = StrToCStr(no.content[j].comment);
			mapFile.WriteString(newMap.fileName + L"," + newMap.path + L"\n");
			listMap.push_back(newMap);
		}
	}
	CHS_LOCALE_END;
	mapFile.Close();
	addInfo(L"�Ѿ�����NPK-IMGӳ����ļ������Ͼ�ʹ���ˡ�");
	Sleep(500);
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	MessageBox(L"��ʼ�����������������������ʹ��IMG��ѯ���޸���������",L"��ʾ��");
}
void ToolNPKsource::loadDictFile(PVOID) {
	addInfo(L"���ڶ�ȡNPK�ǵ䡣");
	ProfileBlack profile;
	CStdioFile file;
	profile.loadProfile();
	if(!file.Open(profile.getSupportPath() + L"npkdict.txt", CFile::modeRead)) {
		file.Open(profile.getSupportPath() + L"npkdict.txt", CFile::modeCreate);
		file.Close();
		addInfo(L"δ��⵽NPK�ǵ��ļ���npkdict.txt�������ɿ��ļ��Դ���֮��");
		return;
	}
	CHS_LOCALE_START;
	CString lineString;
	auto listCtl = GET_CTRL(CListCtrl, IDC_LIST1);
	listDict.clear();
	listCtl->DeleteAllItems();
	int i = 0;
	while(file.ReadString(lineString)) {
		ToolNPKentry newEntry;
		AfxExtractSubString(newEntry.fileName, lineString, 0, ',');
		AfxExtractSubString(newEntry.comment, lineString, 1, ',');
		listDict.push_back(newEntry);
		listCtl->InsertItem(i, newEntry.fileName);
		listCtl->SetItemText(i, 1, newEntry.comment);
		i++;
	}
	CHS_LOCALE_END;
	file.Close();
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"�ǵ��й���������"+NumToCStr(listDict.size())+L"�");
	addInfo(L"�ǵ��й���������" + NumToCStr(listDict.size()) + L"�");
	if(listDict.size()) {
		addInfo(L"�ǵ��ȡ��ϣ�NPK�ǵ��ѿ�ʹ�á�");
	} else {
		addInfo(L"�ǵ��������ݣ�NPK�ǵ��в���ʹ�á�");
		addInfo(L"��ͨ�����뷽ʽ�ֶ�����ǵ䣬���ߵ���Ҳ�İ�ť�����б�д�ǵ䡣");
	}
}
void ToolNPKsource::loadMapFile(PVOID) {
	addInfo(L"���ڶ�ȡNPK-IMGӳ���");
	ProfileBlack profile;
	CStdioFile file;
	profile.loadProfile();
	if(!file.Open(profile.getSupportPath() + L"npkmap.txt", CFile::modeRead)) {
		addInfo(L"δ��⵽NPK-IMGӳ����ļ���npkmap.txt����׼���Զ����ɣ��Ժ���������ԴĿ¼��");
		return;
	}
	CHS_LOCALE_START;
	CString lineString;
	listMap.clear();
	int i = 0;
	while(file.ReadString(lineString)) {
		ToolNPK_Nmap newMap;
		AfxExtractSubString(newMap.fileName, lineString, 0, ',');
		AfxExtractSubString(newMap.path, lineString, 1, ',');
		listMap.push_back(newMap);
	}
	CHS_LOCALE_END;
	file.Close();
	addInfo(L"��ȡNPK-IMGӳ�����ϣ�IMG��λ�����޸������ѿ�ʹ�á�");
}
void ToolNPKsource::loadOtherDictFile(CString fileName) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"���ڶ�ȡ�ⲿNPK�ǵ䡣");
	ProfileBlack profile;
	CStdioFile file, makeFile;
	profile.loadProfile();
	if(!file.Open(fileName, CFile::modeRead)) {
		return;
	}
	makeFile.Open(profile.getSupportPath() + L"npkdict.txt", CFile::modeCreate | CFile::modeWrite);
	CHS_LOCALE_START;
	CString lineString;
	auto listCtl = GET_CTRL(CListCtrl, IDC_LIST1);
	listDict.clear();
	listCtl->DeleteAllItems();
	int i = 0;
	while(file.ReadString(lineString)) {
		ToolNPKentry newEntry;
		AfxExtractSubString(newEntry.fileName, lineString, 0, ',');
		AfxExtractSubString(newEntry.comment, lineString, 1, ',');
		listDict.push_back(newEntry);
		listCtl->InsertItem(i, newEntry.fileName);
		listCtl->SetItemText(i, 1, newEntry.comment);
		makeFile.WriteString(newEntry.fileName + L"," + newEntry.comment + L"\n");
		i++;
	}
	CHS_LOCALE_END;
	file.Close();
	makeFile.Close();
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"�ǵ��й���������" + NumToCStr(listDict.size()) + L"�");
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"��ȡ��ϣ��ѵ��뵽����NPK�ǵ��С�");
}
void ToolNPKsource::loadSomebodysFile(CString fileName) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"�������ܽ����ǵ䡣");
	ProfileBlack profile;
	CStdioFile file, makeFile;
	profile.loadProfile();
	if(!file.Open(fileName, CFile::modeRead)) {
		return;
	}
	makeFile.Open(profile.getSupportPath() + L"npkdict.txt", CFile::modeCreate | CFile::modeWrite);
	CHS_LOCALE_START;
	CString lineString, tempString, leftString, rightString;
	auto listCtl = GET_CTRL(CListCtrl, IDC_LIST1);
	listDict.clear();
	listCtl->DeleteAllItems();
	int i = 0;
	BOOL overNamed = FALSE;
	std::vector<CString> overNameList;
	while(file.ReadString(lineString)) {
		long extPos1 = lineString.Find(L".NPK");
		long extPos2 = lineString.Find(L".npk");
		long extPos = max(extPos1, extPos2);
		if(extPos <= 0) {
			if(overNamed) {
				rightString = lineString.Trim();
				for(auto overString : overNameList) {
					ToolNPKentry newEntry;
					newEntry.fileName = overString;
					newEntry.comment = rightString;
					listDict.push_back(newEntry);
					listCtl->InsertItem(i, newEntry.fileName);
					listCtl->SetItemText(i, 1, newEntry.comment);
					makeFile.WriteString(newEntry.fileName + L"," + newEntry.comment + L"\n");
					i++;
				}
				overNameList.clear();
				overNamed = FALSE;
			}
			continue;
		}
		leftString = lineString.Left(extPos) + L".NPK";
		rightString = lineString.Right(lineString.GetLength() - 5 - extPos).Trim();	//5��".NPK"�������1
		if(!rightString.GetLength()) {
			overNamed = TRUE;
			overNameList.push_back(leftString);
			continue;
		} else {
			if(overNamed) {
				overNameList.push_back(leftString);
				for(auto overString : overNameList) {
					ToolNPKentry newEntry;
					newEntry.fileName = overString;
					newEntry.comment = rightString;
					listDict.push_back(newEntry);
					listCtl->InsertItem(i, newEntry.fileName);
					listCtl->SetItemText(i, 1, newEntry.comment);
					makeFile.WriteString(newEntry.fileName + L"," + newEntry.comment + L"\n");
					i++;
				}
				overNameList.clear();
				overNamed = FALSE;
				continue;
			} else {
				ToolNPKentry newEntry;
				newEntry.fileName = leftString;
				newEntry.comment = rightString;
				listDict.push_back(newEntry);
				listCtl->InsertItem(i, newEntry.fileName);
				listCtl->SetItemText(i, 1, newEntry.comment);
				makeFile.WriteString(newEntry.fileName + L"," + newEntry.comment + L"\n");
				i++;
			}
		}
	}
	CHS_LOCALE_END;
	file.Close();
	makeFile.Close();
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"�ǵ��й���������" + NumToCStr(listDict.size()) + L"�");
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"������ϣ��ѵ��뵽����NPK�ǵ��С�");
}
void ToolNPKsource::queryDict(CString keyWord) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"���ڲ�ѯ��"+keyWord+L"���������Ϣ��");
	auto listCtl = GET_CTRL(CListCtrl, IDC_LIST1);
	resultDict.clear();
	listCtl->DeleteAllItems();
	int i = 0;
	for(auto entry : listDict) {
		if(entry.fileName.Find(keyWord) >= 0 || entry.comment.Find(keyWord) >= 0) {
			resultDict.push_back(entry);
			listCtl->InsertItem(i, entry.fileName);
			listCtl->SetItemText(i, 1, entry.comment);
			i++;
		}
	}
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"��ѯ��ϣ�����ѯ��" + NumToCStr(i) + L"���롰" + keyWord + L"���йص���Ŀ��");
}
void ToolNPKsource::queryMap(CString keyWord) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"������Ѱ·����������" + keyWord + L"����IMG��");
	auto listCtl = GET_CTRL(CListCtrl, IDC_LIST1);
	resultMap.clear();
	listCtl->DeleteAllItems();
	int i = 0;
	for(auto entry : listMap) {
		if(entry.path.Find(keyWord) >= 0) {
			resultMap.push_back(entry);
			listCtl->InsertItem(i, entry.fileName);
			listCtl->SetItemText(i, 1, entry.path);
			i++;
		}
	}
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"��Ѱ��ϣ�����Ѱ��" + NumToCStr(i) + L"��·����������" + keyWord + L"����IMG��");
}
void ToolNPKsource::fixIMG(PVOID) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_SHOW);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_HIDE);
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	queue selected = dlg->IMGgetChecked(isPatch ? MULTI_SELECT : SINGLE_SELECT);
	if(selected.size() == 0 || selected[0] < 0) {
		MessageBox(L"û��ѡ��IMG��������EX����ѡ����߹�ѡһЩ��Ҫ�޸���IMG����", L"��ʾ��");
		return;
	}
	ProfileBlack profile;
	profile.loadProfile();
	clearInfo();
	int count = 0;
	for(int i = 0; i < selected.size(); i++) {
		auto ID = selected[selected.size() - i - 1];
		CString pathInEx = StrToCStr(dlg->no.content[ID].comment);
		addInfo(L"׼���޸�" + pathInEx + L"����");
		long hitMap = -1;
		for(int j = 0; j < listMap.size(); j++) {
			if(listMap[j].path == pathInEx) {
				hitMap = j;
				break;
			}
		}
		if(hitMap >= 0) {
			addInfo(L"�Ѿ�����" + listMap[hitMap].fileName + L"����");
		} else {
			addInfo(L"��IMGδ����NPK���޸�ʧ�ܡ���");
			continue;
		}
		CString fileName = profile.getSourcePath() + listMap[hitMap].fileName;
		NPKobject no;
		if(!no.loadFile(CStrToStr(fileName))) {
			addInfo(L"��������Դ�ļ�����δ�������NPK���޸�ʧ�ܡ���");
			continue;
		}
		long hitIMG = -1;
		for(int j = 0; j < no.getCount(); j++) {
			CString imgPath = StrToCStr(no.content[j].comment);
			if(imgPath == pathInEx) {
				hitIMG = j;
				break;
			}
		}
		if(hitIMG >= 0) {
			addInfo(L"�Ѿ����е�" + NumToCStr(hitIMG + 1) + L"��IMG��׼���滻����");
		} else {
			addInfo(L"��NPKû�����IMG���ƺ���NPK�汾����������£��޸�ʧ�ܡ���");
			continue;
		}
		if(mode == 'r') {
			stream ss;
			no.extract(hitIMG, ss);
			dlg->no.replace(ID, ss);
			addInfo(L"�Ѿ��滻��ϡ�");
		} else if(mode == 'a') {
			IMGobject ioOld, ioNew;
			no.IMGextract(hitIMG, ioNew);
			dlg->no.IMGextract(ID, ioOld);
			int frameCount = ioNew.indexCount - ioOld.indexCount;
			if(frameCount <= 0) {
				addInfo(L"֡���������滻�������Ѿ�������");
			} else {
				for(int k = 0; k < frameCount; k++) {
					PICinfo pi;
					image im;
					stream ss;
					ioNew.PICgetInfo(ioOld.indexCount + k, pi);
					ioNew.PICextract(ioOld.indexCount + k, im);
					ioOld.PICpreprocess(im, ss, pi);
					ioOld.PICpush(pi, ss);
				}
				dlg->no.IMGreplace(ID, ioOld);
				addInfo(L"�Ѿ�������" + NumToCStr(frameCount) + L"֡");
			}
		} else {
			stream ss;
			no.extract(hitIMG, ss);
			dlg->no.insert(ID + 1, no.content[hitIMG].comment, ss);
			addInfo(L"�Ѿ�������ϡ�");
		}
		count++;
	}
	addInfo(L"�޸��������ܼ��޸���"+NumToCStr(count)+L"��IMG��");
	dlg->IMGupdateList();
	if(dlg->no.getCount())
	dlg->IMGsetHighLine(0);
}
