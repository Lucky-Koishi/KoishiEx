// ToolDownload.cpp : 实现文件
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

// ToolDownload 对话框
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


// ToolDownload 消息处理程序


BOOL ToolDownload::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CREATEW(bar, IDD_TINY_PROGRESSBAR);

	lcIn = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	lcOut = GET_CTRL(CListCtrl, IDC_LIST_DOWNLOAD);
	lcIn->SetExtendedStyle(lcIn->GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	lcIn->InsertColumn(0, L"文件名", 0, 280);
	lcIn->InsertColumn(1, L"大小", 0, 60);
	lcOut->SetExtendedStyle(lcOut->GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT);
	lcOut->InsertColumn(0, L"文件名", 0, 220);
	lcOut->InsertColumn(1, L"大小", 0, 60);
	lcOut->InsertColumn(2, L"状态", 0, 60);
	lcOut->ShowWindow(SW_HIDE);

	PROFILE_TYPE profile;
	profile.loadProfile();
	folderName = profile.getDownloadPath(serverInfo.region + L"-" + serverInfo.name);
	recordFileName = folderName + RECORD_FILE_NM;
	listFileName = folderName + LIST_FILE_NM;
	skipExistedFile = 0;
	StartThreadFunc(Initial, nullptr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void ToolDownload::Initial(PVOID) {
	//初始化检查·先检查继续下载列表·再检查列表文件
	//查看有没有上次因异常中断而未进行删除的日志文件
	loadRecord();
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在检索未完成的任务喵……");
	if(record.fileName.size() != 0) {
		if(IDYES == MessageBox(L"上次您在这个服务器里还有未完成的下载任务，要继续喵？", L"提示喵", MB_YESNO)) {
			StartThreadFunc(DownloadFile, nullptr);
			return;
		} else {
			record.fileLength.clear();
			record.fileName.clear();
			record.completed.clear();
			removeRecord();
		}
	} 
	//检查文件列表
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在检索文件列表喵……");
	CStdioFile file;
	if(!file.Open(listFileName, CFile::modeRead)) {
		MessageBox(L"没有找到文件列表，请点击“获取文件列表”来获取最新文件喵！", L"提示喵");
		GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"未检索到文件列表，请点击右侧“获取文件列表”喵！");
		return;
	}
	fileNameList.clear();
	fileSizeList.clear();
	CString lineStr, nameStr, sizeStr;
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在导入文件列表喵……");
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
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在更新列表喵……");
	QueryFile(L"");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"已完成初始化，欢迎使用服务器下载工具喵！");
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
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"检索完成喵，共找到"+NumToCStr(lcIn->GetItemCount())+L"个与“"+para+L"”相关的NPK文件喵！");
}
void ToolDownload::DownloadListFile(PVOID) {
	CString sourStr = serverInfo.url + (serverInfo.isTCT ? L"auto.lst" : L"package.lst");
	CString destStr = folderName + (serverInfo.isTCT ? L"auto.lst" : L"package.lst");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在向服务器请求文件列表喵……");
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"正在下载" + sourStr + L"喵……");
	if(0 != GetInternetFile(sourStr, destStr)) {
		MessageBox(L"啊咧！列表获取失败喵！请检查网络喵！", L"提示喵");
		GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"404 NOT FOUND MEOW……");
		GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"：下载失败。");
		return;
	}
	if(serverInfo.isTCT) {
		//国服资源
		LSTobjectGF lo2;
		if(!lo2.LST_LOAD_GF(CStrToStr(destStr))) {
			MessageBox(L"啊咧！列表解码失败喵！一定又是官方暗改了喵！", L"提示喵");
			GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"无法针对这个列表文件解码喵……");
			GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"：解析失败。");
			return;
		}
		bar.show(lo2.list.size());
		CStdioFile file;
		file.Open(listFileName, CFile::modeCreate | CFile::modeWrite);
		CHS_LOCALE_START;
		for(int i = 0; i < lo2.list.size(); i++) {
			bar.setInfo(L"正在生成列表文件喵……", i);
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
			MessageBox(L"啊咧！列表解码失败喵！一定又是官方暗改了喵！", L"提示喵");
			GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"无法针对这个列表文件解码喵……");
			GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"：解析失败。");
			return;
		}
		if(!lo.LST_LOAD(lf)) {
			MessageBox(L"啊咧！列表解码失败喵！一定又是官方暗改了喵！", L"提示喵");
			GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"无法针对这个列表文件解码喵……");
			GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"：解析失败。");
			return;
		}
		bar.show(lf.list.size());
		CStdioFile file;
		file.Open(listFileName, CFile::modeCreate | CFile::modeWrite);
		CHS_LOCALE_START;
		for(int i = 0; i < lf.list.size(); i++) {
			bar.setInfo(L"正在生成列表文件喵……", i);
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
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在导入文件列表喵……");
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
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在更新列表喵……");
	QueryFile(L"");
	MessageBox(L"列表已成功获取喵！", L"提示喵");
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"已在服务器获取了列表。");
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(sourStr + L"：完成。");
	QueryFile(L"");
}

void ToolDownload::DownloadFile(PVOID) {
	CProgressCtrl * pc = GET_CTRL(CProgressCtrl, IDC_PROGRESS);
	if(!record.fileName.size()) {
		MessageBox(L"还没有选择要下载的文件喵！", L"提示喵");
		return;
	}
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在创建下载列表喵……");
	lcIn->ShowWindow(SW_HIDE);
	lcOut->ShowWindow(SW_SHOW);
	lcOut->DeleteAllItems();
	for(int i = 0; i < record.fileName.size(); i++) {
		int count = lcOut->GetItemCount();
		lcOut->InsertItem(count, record.fileName[i]);
		lcOut->SetItemText(count, 1, record.fileLength[i]);
		lcOut->SetItemText(count, 2, L"等待下载中");
	}
	pc->SetRange32(0, lcOut->GetItemCount());
	pc->SetPos(0);
	int totalCount = 0;
	//创建下载列表
	updateRecord();
	//下载列表创建完成
	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"正在下载喵……");
	for(int i = 0; i < lcOut->GetItemCount(); i++) {
		CString sourStr = serverInfo.url + INTERNET_FOLDER + lcOut->GetItemText(i, 0) + (serverInfo.isTCT ? L".tct" : L".spk");
		CString destStr = folderName + lcOut->GetItemText(i, 0) + (serverInfo.isTCT ? L".tct" : L".spk");
		CString fileStr = folderName + lcOut->GetItemText(i, 0);
		GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"正在下载" + sourStr + L"喵……");
		if(skipExistedFile == 0) {
			//重名检测·未提示
			CFile tryOpen;
			if(tryOpen.Open(fileStr, CFile::modeRead)) {
				//如果存在
				tryOpen.Close();
				if(IDYES == MessageBox(L"发现已存在的文件，要替换喵？\r\n选择“是”则一直替换喵；\r\n选择“否”则一直跳过喵。", L"提示喵", MB_YESNO)) {
					skipExistedFile = 2;
				} else {
					skipExistedFile = 1;
					lcOut->SetItemText(i, 2, L"重名跳过");
					continue;
				}
			}
		} else if(skipExistedFile == 1) {
			CFile tryOpen;
			if(tryOpen.Open(fileStr, CFile::modeRead)) {
				tryOpen.Close();
				lcOut->SetItemText(i, 2, L"重名跳过");
				continue;
			}
		}
		lcOut->SetItemText(i, 2, L"下载中");
		pc->SetPos(i);
		if(0 != GetInternetFile(sourStr, destStr)) {
			lcOut->SetItemText(i, 2, L"下载失败");
			continue;
		}
		lcOut->SetItemText(i, 2, L"解析中");
		if(serverInfo.isTCT) {
			TCTobject to;
			if(!to.load(CStrToStr(destStr))) {
				lcOut->SetItemText(i, 2, L"解析失败");
				continue;
			}
			to.makeNPK(CStrToStr(fileStr));
			DeleteFile(destStr);
			lcOut->SetItemText(i, 2, L"已完成");
		} else {
			SPKobject so;
			if(!so.load(CStrToStr(destStr))) {
				lcOut->SetItemText(i, 2, L"解析失败");
				continue;
			}
			so.makeNPK(CStrToStr(fileStr));
			DeleteFile(destStr);
			lcOut->SetItemText(i, 2, L"已完成");
		}
		totalCount++;
		//更新列表
		record.completed[i] = 1;
		updateRecord();
	}
	pc->SetPos(lcOut->GetItemCount());
	MessageBox(L"下载完毕喵！\r\n成功下载" + NumToCStr(totalCount) + L"个文件喵！", L"提示喵");
	GET_CTRL(CEdit, IDC_EDIT_INFO2)->SetWindowText(L"下载完毕喵！成功下载" + NumToCStr(totalCount) + L"个文件喵！");

	GET_CTRL(CEdit, IDC_EDIT_INFO)->SetWindowText(L"下载完成喵……");
	//删除列表，若异常则不会运行到这里
	removeRecord();
}

void ToolDownload::OnBnClickedButtonGetList() {
	// TODO:  在此添加控件通知处理程序代码
	StartThreadFunc(DownloadListFile, nullptr);
}

void ToolDownload::OnBnClickedButtonKeyword() {
	// TODO:  在此添加控件通知处理程序代码
	CString keyWord;
	GET_CTRL(CEdit, IDC_EDIT_KEYWORD)->GetWindowText(keyWord);
	StartThreadFunc(QueryFile, keyWord);
}

void ToolDownload::OnBnClickedButtonFolder() {
	// TODO:  在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", folderName, NULL, NULL, SW_NORMAL);
}


void ToolDownload::OnBnClickedButtonOpen() {
	// TODO:  待定
	int row = lcOut->GetSelectionMark();
	if(row < 0 || row >= lcOut->GetItemCount()) {
		MessageBox(L"请选择一个下载好的文件喵。", L"提示喵");
		return;
	}
	CString fileName = lcOut->GetItemText(row, 0);
	CString destStr = folderName + fileName;
	DIALOG_TYPE *dlg = (DIALOG_TYPE*)context;
	dlg->no.release();
	if(!dlg->no.loadFile(CStrToStr(destStr))) {
		MessageBox(L"该文件无法识别喵！", L"提示喵");
	} else {
		dlg->fileNPKname = destStr;
		dlg->ELM(saveAlert) = false;
		dlg->ELM(loadList)();
		dlg->updateInfo();
		MessageBox(L"该文件已在EX中打开了喵！", L"提示喵");
	}
}


void ToolDownload::OnBnClickedButtonExit() {
	// TODO:  在此添加控件通知处理程序代码
	OnCancel();
}


void ToolDownload::OnBnClickedButtonStart() {
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //鼠标位置
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU_DOWNLOAD);
	pPopup = menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}


void ToolDownload::OnNMClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CHECK_VALID(pNMListView->iItem >= 0);
	int row = pNMListView->iItem;
	BOOL b = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->GetCheck(row);
	GET_CTRL(CListCtrl, IDC_LIST_ORIGIN)->SetCheck(row, !b);
	*pResult = 0;
}


void ToolDownload::OnClickSelectAll() {
	// TODO:  在此添加命令处理程序代码
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	for(int i = 0; i < lc->GetItemCount();i++) {
		lc->SetCheck(i, TRUE);
	}
}


void ToolDownload::OnClickSelectReverse() {
	// TODO:  在此添加命令处理程序代码
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	for(int i = 0; i < lc->GetItemCount(); i++) {
		lc->SetCheck(i, !(lc->GetCheck(i)));
	}
}


void ToolDownload::OnClickSelectHighline() {
	// TODO:  在此添加命令处理程序代码
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_ORIGIN);
	for(int i = 0; i < lc->GetItemCount(); i++) {
		if(lc->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			lc->SetCheck(i, TRUE);
		}
	}
}


void ToolDownload::OnOK() {
	// TODO:  在此添加专用代码和/或调用基类

	// CDialogEx::OnOK();
}
