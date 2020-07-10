// ToolStat.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolStat.h"
#include "afxdialogex.h"
#include <thread>

// ToolStat 对话框

IMPLEMENT_DYNAMIC(ToolStat, CDialogEx)

ToolStat::ToolStat(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolStat::IDD, pParent)
{

}

ToolStat::~ToolStat()
{
}

void ToolStat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolStat, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &ToolStat::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_TOOL1, &ToolStat::OnBnClickedButtonTool1)
	ON_BN_CLICKED(IDC_BUTTON_TOOL2, &ToolStat::OnBnClickedButtonTool2)
	ON_BN_CLICKED(IDC_BUTTON_TOOL3, &ToolStat::OnBnClickedButtonTool3)
END_MESSAGE_MAP()


// ToolStat 消息处理程序


void ToolStat::OnBnClickedButtonSelect() {
	// TODO:  在此添加控件通知处理程序代码
	CString folderName;
	CALL_FOLDER_DIALOG(folderName, L"选择文件夹", L"提示", L"并不是有效的文件夹");
	if(folderName.GetLength() == 0) {
		return;
	}
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(folderName);
}
DefineThreadFunc(ToolStat, Tool1, int) {
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST1);
	lc->DeleteAllItems();
	while(lc->DeleteColumn(0));
	lc->InsertColumn(0, L"版本", 0, 40);
	lc->InsertColumn(1, L"个数", 0, 80);
	lc->InsertColumn(2, L"举例NPK", 0, 120);
	lc->InsertColumn(3, L"举例IMG", 0, 180);
	std::vector<CString> fileList, pathList;
	CString folderName;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderName);
	GetFile(folderName+L".", fileList, pathList);
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetRange32(0, pathList.size());
	for(int i = 0; i < pathList.size(); i++) {
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetPos(i);
		if(pathList[i].Right(3).MakeUpper() != L"NPK")
			continue;
		NPKobject no;
		if(!no.loadFile(CStrToStr(pathList[i])))
			continue;
		for(int imgID = 0; imgID < no.count; imgID++) {
			DWORD magic = 0;
			long nVer = 0;
			stream &s = no.block[no.entry[imgID].link];
			s.resetPosition();
			s.readDWord(magic);
			if(magic == 0x706F654E) {
				s.movePosition(20);
				s.readInt(nVer);
			}
			img_version_term newTerm = {nVer, 1, fileList[i], GetTail(StrToCStr(no.entry[imgID].comment))};
			updateImgBerQueryTable(newTerm);
		}
		lc->DeleteAllItems();
		for(int k = 0; k < imgVerQuery.size(); k++) {
			lc->InsertItem(k, L"V" + NumToCStr(imgVerQuery[k].ver));
			lc->SetItemText(k, 1, NumToCStr(imgVerQuery[k].count));
			lc->SetItemText(k, 2, imgVerQuery[k].foundInNPKname);
			lc->SetItemText(k, 3, imgVerQuery[k].imgPathName);
		}
	}
	lc->DeleteAllItems();
	for(int k = 0; k < imgVerQuery.size(); k++) {
		lc->InsertItem(k, L"V" + NumToCStr(imgVerQuery[k].ver));
		lc->SetItemText(k, 1, NumToCStr(imgVerQuery[k].count));
		lc->SetItemText(k, 2, imgVerQuery[k].foundInNPKname);
		lc->SetItemText(k, 3, imgVerQuery[k].imgPathName);
	}
	CStdioFile file;
	Profile prof;
	prof.loadProfile();
	file.Open(prof.getOutputPath() + L"IMG版本统计.csv", CFile::modeCreate | CFile::modeWrite);
	for(img_version_term i : imgVerQuery) {
		CString line;
		line.Format(L"V%d,%d," + i.foundInNPKname + L"," + i.imgPathName, i.ver, i.count);
		file.WriteString(line + L"\n");
	}
	file.Close();
}
DefineThreadFunc(ToolStat, Tool2, int) {
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST1);
	lc->DeleteAllItems();
	while(lc->DeleteColumn(0));
	lc->InsertColumn(0, L"代号", 0, 60);
	lc->InsertColumn(1, L"个数", 0, 60);
	lc->InsertColumn(2, L"举例NPK", 0, 120);
	lc->InsertColumn(3, L"举例IMG", 0, 140);
	lc->InsertColumn(4, L"举例帧", 0, 40);
	std::vector<CString> fileList, pathList;
	CString folderName;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderName);
	GetFile(folderName + L".", fileList, pathList);
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetRange32(0, pathList.size());
	for(int i = 0; i < pathList.size(); i++) {
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetPos(i);
		if(pathList[i].Right(3).MakeUpper() != L"NPK")
			continue;
		NPKobject no;
		if(!no.loadFile(CStrToStr(pathList[i])))
			continue;
		for(int imgID = 0; imgID < no.count; imgID++) {
			long nVer = no.IMGgetVersion(imgID);
			IMGobject io;
			BOOL isV1 = FALSE;
			if(no.IMGgetVersion(imgID) == V1) {
				isV1 = TRUE;
				stream ios;
				KoishiExpand::IMGobjectV1 io1;
				if(!no.extract(imgID, ios))
					continue;
				if(!io1.load(ios))
					continue;
				if(!io1.make(io))
					continue;
			} else {
				if(!no.IMGextract(imgID, io))
					continue;
			}
			for(int frameID = 0; frameID < io.indexCount; frameID++) {
				PICinfo pi;
				if(!io.PICgetInfo(frameID, pi))
					continue;
				if(pi.format == LINK)
					pi.comp = (IMGcomp)0;
				frame_version_term newTerm = {(isV1 ? 1 : io.version) << 16 | pi.format << 8 | pi.comp, 1, fileList[i], GetTail(StrToCStr(no.entry[imgID].comment)), frameID};
				updateFrameVerQueryTable(newTerm);
			}
		}
		lc->DeleteAllItems();
		for(int k = 0; k < frameVerQuery.size(); k++) {
			CString nstr;
			nstr.Format(L"%06X", frameVerQuery[k].versString);
			lc->InsertItem(k, nstr);
			lc->SetItemText(k, 1, NumToCStr(frameVerQuery[k].count));
			lc->SetItemText(k, 2, frameVerQuery[k].foundInNPKname);
			lc->SetItemText(k, 3, frameVerQuery[k].foundInIMGname);
			lc->SetItemText(k, 4, NumToCStr(frameVerQuery[k].frameID));
		}
	}
	lc->DeleteAllItems();
	for(int k = 0; k < frameVerQuery.size(); k++) {
		CString nstr;
		nstr.Format(L"%06X", frameVerQuery[k].versString);
		lc->InsertItem(k, nstr);
		lc->SetItemText(k, 1, NumToCStr(frameVerQuery[k].count));
		lc->SetItemText(k, 2, frameVerQuery[k].foundInNPKname);
		lc->SetItemText(k, 3, frameVerQuery[k].foundInIMGname);
		lc->SetItemText(k, 4, NumToCStr(frameVerQuery[k].frameID));
	}
	CStdioFile file;
	Profile prof;
	prof.loadProfile();
	file.Open(prof.getOutputPath() + L"贴图版本统计.csv", CFile::modeCreate | CFile::modeWrite);
	for(frame_version_term i : frameVerQuery) {
		CString line;
		line.Format(L"%06X,%d," + i.foundInNPKname + L"," + i.foundInIMGname + L",%d", i.versString, i.count, i.frameID);
		file.WriteString(line + L"\n");
	}
	file.Close();
}
DefineThreadFunc(ToolStat, Tool3, int) {
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST1);
	lc->DeleteAllItems();
	while(lc->DeleteColumn(0));
	lc->InsertColumn(0, L"图层", 0, 120);
	lc->InsertColumn(1, L"个数", 0, 80);
	lc->InsertColumn(2, L"举例IMG", 0, 220);
	std::vector<CString> fileList, pathList;
	CString folderName;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderName);
	GetFile(folderName + L".", fileList, pathList);
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetRange32(0, pathList.size());
	for(int i = 0; i < pathList.size(); i++) {
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetPos(i);
		if(pathList[i].Right(3).MakeUpper() != L"NPK")
			continue;
		if(-1 == pathList[i].Find(L"sprite_character"))
			continue;
		if(-1 == pathList[i].Find(L"equipment"))
			continue;
		if(-1 != pathList[i].Find(L"growtype"))
			continue;
		if(-1 != pathList[i].Find(L"shield"))
			continue;
		NPKobject no;
		if(!no.loadFile(CStrToStr(pathList[i])))
			continue;
		for(int imgID = 0; imgID < no.count; imgID++) {
			CString path = GetTail(StrToCStr(no.entry[imgID].comment));
			pal_term newTerm = {{0}, 1, L"", path};
			newTerm.value.value = 0;
			if(-1 != path.Find(L"mask")) {
				continue;
			}
			if(-1 != path.Find(L"wake")) {
				continue;
			}
			if(-1 != path.Find(L"coat")) {
				newTerm.value.part = 1;
			}
			if(-1 != path.Find(L"pants")) {
				newTerm.value.part = 2;
			}
			if(-1 != path.Find(L"hair")) {
				newTerm.value.part = 3;
			}
			if(-1 != path.Find(L"cap")) {
				newTerm.value.part = 4;
			}
			if(-1 != path.Find(L"face")) {
				newTerm.value.part = 5;
			}
			if(-1 != path.Find(L"neck")) {
				newTerm.value.part = 6;
			}
			if(-1 != path.Find(L"shoes")) {
				newTerm.value.part = 7;
			}
			if(-1 != path.Find(L"belt")) {
				newTerm.value.part = 8;
			}
			if(-1 != path.Find(L"body")) {
				newTerm.value.part = 9;
			}
			if(-1 != path.Find(L"skin")) {
				newTerm.value.part = 9;
			}
			int k = 0;
			int l = 0;
			char ll[4] = {0,0,0,0};
			while(k < path.GetLength() && (path.GetAt(k) < '0' || path.GetAt(k) > '9')) {
				k++;
			}
			while(k < path.GetLength() && path.GetAt(k) >= '0' && path.GetAt(k) <= '9') {
				k++;
			}
			while(k < path.GetLength() && l < 4 && path.GetAt(k) != '.') {
				ll[l++] = path.GetAt(k);
				k++;
			}
			ll[3] = 0;
			CString s1[10] = {L"weapon", L"coat", L"pants", L"hair", L"cap", L"face", L"neck", L"shoes", L"belt", L"body"};
			CString s2 = ll[0] == 0 ? L"" : CString(ll);
			newTerm.disc = s2.GetLength() ? (s1[newTerm.value.part] + L"_" + s2) : s1[newTerm.value.part];
			ll[3] = ll[0];
			ll[0] = ll[2];
			ll[2] = ll[3];
			memcpy(newTerm.value.layer, ll, 3);
			updatePalQueryTable(newTerm);
		}
		lc->DeleteAllItems();
		for(int k = 0; k < palQuery.size(); k++) {
			lc->InsertItem(k, palQuery[k].disc);
			lc->SetItemText(k, 1, NumToCStr(palQuery[k].count));
			lc->SetItemText(k, 2, palQuery[k].imgPathName);
		}
	}
	lc->DeleteAllItems();
	for(int k = 0; k < palQuery.size(); k++) {
		lc->InsertItem(k, palQuery[k].disc);
		lc->SetItemText(k, 1, NumToCStr(palQuery[k].count));
		lc->SetItemText(k, 2, palQuery[k].imgPathName);
	}
	CStdioFile file;
	Profile prof;
	prof.loadProfile();
	file.Open(prof.getOutputPath() + L"图层统计.csv", CFile::modeCreate | CFile::modeWrite);
	for(pal_term i : palQuery) {
		CString line;
		line.Format(i.disc + L",%d," + i.imgPathName, i.count);
		file.WriteString(line + L"\n");
	}
	file.WriteString(L"\n");
	file.Close();
}


void ToolStat::OnBnClickedButtonTool1() {
	// TODO:  在此添加控件通知处理程序代码
	StartThreadFunc(Tool1, 0);
}


void ToolStat::OnBnClickedButtonTool2() {
	// TODO:  在此添加控件通知处理程序代码
	StartThreadFunc(Tool2, 0);
}


void ToolStat::OnBnClickedButtonTool3() {
	// TODO:  在此添加控件通知处理程序代码
	StartThreadFunc(Tool3, 0);
}


BOOL ToolStat::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Profile prof;
	prof.loadProfile();
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(prof.getAvatarPath());
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
