// ToolNPKsource.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "ToolNPKsource.h"
#include "afxdialogex.h"
#include <thread>

// ToolNPKsource 对话框

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


// ToolNPKsource 消息处理程序


BOOL ToolNPKsource::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ProfileBlack profile;
	profile.loadProfile();
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(profile.getSourcePath());
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在初始化……");
	GET_CTRL(CListCtrl, IDC_LIST1)->InsertColumn(0, L"NPK文件名", 0, 400);
	GET_CTRL(CListCtrl, IDC_LIST1)->InsertColumn(1, L"内容", 0, 400);
	StartThreadFunc(initialTool, nullptr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ToolNPKsource::OnBnClickedButtonInitial() {
	// TODO:  在此添加控件通知处理程序代码
	CString folderName;
	ProfileBlack profile;
	profile.loadProfile();
	CALL_FOLDER_DIALOG(folderName, L"选择文件夹喵", L"提示喵", L"并不是有效的文件夹喵");
	if(folderName.GetLength() > 0) {
		profile.sourcePath = folderName;
		profile.saveProfile();
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(folderName + L"\\");
		StartThreadFunc(generateMapFile, folderName);
	}
}


void ToolNPKsource::OnBnClickedButtonOpenFolder() {
	// TODO:  在此添加控件通知处理程序代码
	ProfileBlack profile;
	profile.loadProfile();
	ShellExecute(NULL, L"open", profile.getSourcePath(), NULL, NULL, SW_SHOWNORMAL);
}


void ToolNPKsource::OnBnClickedButtonImport() {
	// TODO:  在此添加控件通知处理程序代码
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU_NPK_SOURCE);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}


void ToolNPKsource::OnBnClickedButtonExplore() {
	// TODO:  在此添加控件通知处理程序代码
	ProfileBlack profile;
	profile.loadProfile();
	ShellExecute(NULL, L"open", profile.getSupportPath() + L"npkdict.txt", NULL, NULL, SW_SHOWNORMAL);
}


void ToolNPKsource::OnBnClickedButtonQuery() {
	// TODO:  在此添加控件通知处理程序代码
	CString keyWord;
	GET_CTRL(CEdit, IDC_EDIT3)->GetWindowText(keyWord);
	StartThreadFunc(queryDict, keyWord);
}


void ToolNPKsource::OnBnClickedButtonQueryPath() {
	// TODO:  在此添加控件通知处理程序代码
	CString keyWord;
	GET_CTRL(CEdit, IDC_EDIT3)->GetWindowText(keyWord);
	StartThreadFunc(queryMap, keyWord);
}


void ToolNPKsource::OnBnClickedButtonSearchAnd() {
	// TODO:  在此添加控件通知处理程序代码
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU_NPK_SOURCE);
	pPopup = menu.GetSubMenu(1);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}


void ToolNPKsource::OnBnClickedButtonOpen() {
	// TODO:  在此添加控件通知处理程序代码
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
		MessageBox(L"已经打开所选文件喵！", L"提示喵");
		dlg->IMGloadList();
		dlg->updateInfo();
	} else {
		MessageBox(L"资源文件夹中不存在选定文件喵！", L"提示喵");
	}
}


void ToolNPKsource::OnBnClickedCancel() {
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void ToolNPKsource::OnImport1() {
	// TODO:  在此添加命令处理程序代码
	CString defExt = L"NPK辞典文件(*.TXT)|*.TXT";
	CString extFilter = L"NPK辞典文件(*.TXT)|*.TXT||";
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		StartThreadFunc(loadOtherDictFile, dlg.GetPathName());
	}
}


void ToolNPKsource::OnImport2() {
	// TODO:  在此添加命令处理程序代码
	CString defExt = L"精灵-传说提供的文件(*.TXT)|*.TXT";
	CString extFilter = L"精灵-传说提供的文件(*.TXT)|*.TXT||";
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		StartThreadFunc(loadSomebodysFile, dlg.GetPathName());
	}
}


void ToolNPKsource::OnImgModify1() {
	// TODO:  在此添加命令处理程序代码
	mode = 'r';
	isPatch = FALSE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModify2() {
	// TODO:  在此添加命令处理程序代码
	mode = 'a';
	isPatch = FALSE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModify3() {
	// TODO:  在此添加命令处理程序代码
	mode = 'c';
	isPatch = FALSE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModifyPatch1() {
	// TODO:  在此添加命令处理程序代码
	mode = 'r';
	isPatch = TRUE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModifyPatch2() {
	// TODO:  在此添加命令处理程序代码
	mode = 'a';
	isPatch = TRUE;
	StartThreadFunc(fixIMG, nullptr);
}


void ToolNPKsource::OnImgModifyPatch3() {
	// TODO:  在此添加命令处理程序代码
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
		if(IDYES == MessageBox(L"首次使用这个工具需要进行初始化，可能会花点时间，确认喵？\r\n(使用IMG定位和IMG修复必须)", L"提示喵", MB_YESNO)) {
			OnBnClickedButtonInitial();
		}
	}
	
}

void ToolNPKsource::generateMapFile(CString folders) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_SHOW);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_HIDE);
	addInfo(L"读取资源目录中，请耐心等待。");
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
	addInfo(L"开始生成映射文件。");
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
	addInfo(L"已经生成NPK-IMG映射表文件，马上就使用了。");
	Sleep(500);
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	MessageBox(L"初始化工作完毕喵！现在您可以使用IMG查询和修复功能喵！",L"提示喵");
}
void ToolNPKsource::loadDictFile(PVOID) {
	addInfo(L"正在读取NPK辞典。");
	ProfileBlack profile;
	CStdioFile file;
	profile.loadProfile();
	if(!file.Open(profile.getSupportPath() + L"npkdict.txt", CFile::modeRead)) {
		file.Open(profile.getSupportPath() + L"npkdict.txt", CFile::modeCreate);
		file.Close();
		addInfo(L"未检测到NPK辞典文件“npkdict.txt”，生成空文件以代替之。");
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
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"辞典中共包含词条"+NumToCStr(listDict.size())+L"项。");
	addInfo(L"辞典中共包含词条" + NumToCStr(listDict.size()) + L"项。");
	if(listDict.size()) {
		addInfo(L"辞典读取完毕，NPK辞典已可使用。");
	} else {
		addInfo(L"辞典里无内容，NPK辞典尚不可使用。");
		addInfo(L"请通过导入方式手动导入辞典，或者点击右侧的按钮，自行编写辞典。");
	}
}
void ToolNPKsource::loadMapFile(PVOID) {
	addInfo(L"正在读取NPK-IMG映射表。");
	ProfileBlack profile;
	CStdioFile file;
	profile.loadProfile();
	if(!file.Open(profile.getSupportPath() + L"npkmap.txt", CFile::modeRead)) {
		addInfo(L"未检测到NPK-IMG映射表文件“npkmap.txt”，准备自动生成，稍后请设置资源目录。");
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
	addInfo(L"读取NPK-IMG映射表完毕，IMG定位器和修复工具已可使用。");
}
void ToolNPKsource::loadOtherDictFile(CString fileName) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"正在读取外部NPK辞典。");
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
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"辞典中共包含词条" + NumToCStr(listDict.size()) + L"项。");
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"读取完毕，已导入到本地NPK辞典中。");
}
void ToolNPKsource::loadSomebodysFile(CString fileName) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"正在智能解析辞典。");
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
		rightString = lineString.Right(lineString.GetLength() - 5 - extPos).Trim();	//5是".NPK"长度外加1
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
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"辞典中共包含词条" + NumToCStr(listDict.size()) + L"项。");
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"解析完毕，已导入到本地NPK辞典中。");
}
void ToolNPKsource::queryDict(CString keyWord) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"正在查询“"+keyWord+L"”的相关信息。");
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
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"查询完毕，共查询到" + NumToCStr(i) + L"个与“" + keyWord + L"”有关的条目。");
}
void ToolNPKsource::queryMap(CString keyWord) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_HIDE);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_SHOW);
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"正在搜寻路径名包含“" + keyWord + L"”的IMG。");
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
	GET_CTRL(CEdit, IDC_EDIT5)->SetWindowText(L"搜寻完毕，共搜寻到" + NumToCStr(i) + L"个路径名包含“" + keyWord + L"”的IMG。");
}
void ToolNPKsource::fixIMG(PVOID) {
	GET_CTRL(CWnd, IDC_EDIT4)->ShowWindow(SW_SHOW);
	GET_CTRL(CWnd, IDC_LIST1)->ShowWindow(SW_HIDE);
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	queue selected = dlg->IMGgetChecked(isPatch ? MULTI_SELECT : SINGLE_SELECT);
	if(selected.size() == 0 || selected[0] < 0) {
		MessageBox(L"没有选择IMG喵！请在EX进行选择或者勾选一些你要修复的IMG喵！", L"提示喵");
		return;
	}
	ProfileBlack profile;
	profile.loadProfile();
	clearInfo();
	int count = 0;
	for(int i = 0; i < selected.size(); i++) {
		auto ID = selected[selected.size() - i - 1];
		CString pathInEx = StrToCStr(dlg->no.content[ID].comment);
		addInfo(L"准备修复" + pathInEx + L"……");
		long hitMap = -1;
		for(int j = 0; j < listMap.size(); j++) {
			if(listMap[j].path == pathInEx) {
				hitMap = j;
				break;
			}
		}
		if(hitMap >= 0) {
			addInfo(L"已经命中" + listMap[hitMap].fileName + L"……");
		} else {
			addInfo(L"该IMG未命中NPK，修复失败……");
			continue;
		}
		CString fileName = profile.getSourcePath() + listMap[hitMap].fileName;
		NPKobject no;
		if(!no.loadFile(CStrToStr(fileName))) {
			addInfo(L"但是在资源文件夹中未发现这个NPK，修复失败……");
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
			addInfo(L"已经命中第" + NumToCStr(hitIMG + 1) + L"个IMG，准备替换……");
		} else {
			addInfo(L"该NPK没有这个IMG，似乎是NPK版本发生变更导致，修复失败……");
			continue;
		}
		if(mode == 'r') {
			stream ss;
			no.extract(hitIMG, ss);
			dlg->no.replace(ID, ss);
			addInfo(L"已经替换完毕。");
		} else if(mode == 'a') {
			IMGobject ioOld, ioNew;
			no.IMGextract(hitIMG, ioNew);
			dlg->no.IMGextract(ID, ioOld);
			int frameCount = ioNew.indexCount - ioOld.indexCount;
			if(frameCount <= 0) {
				addInfo(L"帧数不满足替换条件，已经跳过。");
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
				addInfo(L"已经补充了" + NumToCStr(frameCount) + L"帧");
			}
		} else {
			stream ss;
			no.extract(hitIMG, ss);
			dlg->no.insert(ID + 1, no.content[hitIMG].comment, ss);
			addInfo(L"已经新增完毕。");
		}
		count++;
	}
	addInfo(L"修复结束，总计修复了"+NumToCStr(count)+L"个IMG。");
	dlg->IMGupdateList();
	if(dlg->no.getCount())
	dlg->IMGsetHighLine(0);
}
