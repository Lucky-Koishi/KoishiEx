
// ExToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExTool.h"
#include "ExToolDlg.h"
#include "afxdialogex.h"
//
//#include "../KoishiEx/KoishiNeoplePack.h"
//#include "../KoishiEx/koishiex.h"
//#include "../KoishiEx/KoishiBase.cpp"
//#include "../KoishiEx/Koishidata.cpp"
//#include "../KoishiEx/Koishifactory.cpp"
//#include "../KoishiEx/sha256.cpp"
//#include "../KoishiEx/KoishiImageTool.cpp"
//#include "../KoishiEx/KoishiAudioTool.cpp"
//#include "../KoishiEx/avatar.cpp"
//#include "../KoishiEx/KoishiExpand.cpp"
//#include "../KoishiEx/BZ2.cpp"
#include "../KoishiEx//avatar.h"
#include "../KoishiEx//KoishiAudioTool.h"
#include <locale.h>
#include <vector>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExToolDlg 对话框




CExToolDlg::CExToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CExToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CExToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CExToolDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CExToolDlg 消息处理程序

BOOL CExToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetRange32(0,1000);
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS2))->SetRange32(0,1000);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////
using namespace KoishiAvatar;
WeaponSet CWL(const AvatarCharacter &character){
	WeaponType CWT[ACHARACTER_MAXCOUNT][WEAPON_MAXCOUNT_PER_CHAR] = {
		{AWEAPON_LSWD, AWEAPON_MSWD, AWEAPON_SSWD, AWEAPON_LGSWD, AWEAPON_BONESWD, AWEAPON_GEMSWD, AWEAPON_KATANA, AWEAPON_LKATANA, AWEAPON_CLUB, AWEAPON_BEAMSWD, AWEAPON_UD},
		{AWEAPON_LSWD, AWEAPON_MSWD, AWEAPON_SSWD, AWEAPON_LGSWD, AWEAPON_BONESWD, AWEAPON_GEMSWD, AWEAPON_KATANA, AWEAPON_LKATANA, AWEAPON_CLUB, AWEAPON_BEAMSWD, AWEAPON_UD},
		{AWEAPON_GAUNTLET, AWEAPON_ARM, AWEAPON_GLOVE, AWEAPON_KNUCKLE, AWEAPON_BOXGLOVE, AWEAPON_CLAW, AWEAPON_BONECLAW, AWEAPON_TONFA, AWEAPON_UD},
		{AWEAPON_GAUNTLET, AWEAPON_ARM, AWEAPON_GLOVE, AWEAPON_KNUCKLE, AWEAPON_BOXGLOVE, AWEAPON_CLAW, AWEAPON_BONECLAW, AWEAPON_TONFA, AWEAPON_UD},
		{AWEAPON_AUTO, AWEAPON_REV, AWEAPON_MUSKET, AWEAPON_BOWGUN, AWEAPON_HCAN,AWEAPON_UD},
		{AWEAPON_AUTO, AWEAPON_REV, AWEAPON_MUSKET, AWEAPON_BOWGUN, AWEAPON_HCAN,AWEAPON_UD},
		{AWEAPON_ROD, AWEAPON_STAFF, AWEAPON_POLE, AWEAPON_SPEAR, AWEAPON_BROOM, AWEAPON_UD},
		{AWEAPON_ROD, AWEAPON_STAFF, AWEAPON_POLE, AWEAPON_SPEAR, AWEAPON_BROOM, AWEAPON_UD},
		{AWEAPON_CROSS, AWEAPON_AXE, AWEAPON_SCYTHE, AWEAPON_TOTEM, AWEAPON_ROSARY, AWEAPON_UD},
		{AWEAPON_CROSS, AWEAPON_AXE, AWEAPON_SCYTHE, AWEAPON_TOTEM, AWEAPON_ROSARY, AWEAPON_KHAKKHARA, AWEAPON_UD},
		{AWEAPON_DAGGER, AWEAPON_TWINSWD, AWEAPON_WAND, AWEAPON_CHAKRAWEAPON, AWEAPON_UD},
		{AWEAPON_LSWD, AWEAPON_MSWD, AWEAPON_SSWD, AWEAPON_LGSWD, AWEAPON_BONESWD, AWEAPON_GEMSWD, AWEAPON_KATANA, AWEAPON_LKATANA, AWEAPON_CLUB, AWEAPON_UD},
		{AWEAPON_PIKE, AWEAPON_HALBERD, AWEAPON_JAVELIN, AWEAPON_BEAMSPEAR, AWEAPON_UD},
		{AWEAPON_MSWD, AWEAPON_SBLADE, AWEAPON_LBLADE, AWEAPON_CORESWD, AWEAPON_UD}
	};
	WeaponSet result;
	for(int i = 0;i<WEAPON_MAXCOUNT_PER_CHAR;i++){
		if(CWT[character][i] == AWEAPON_UD)
			return result;
		result.push_back(CWT[character][i]);
	}
	return result;
}

std::vector<str> getFileList(){
	std::vector<str> fileList;
	for(DWORD i = 0;i<ACHARACTER_MAXCOUNT;i++){
		for(DWORD j = 0;j<APART_MAXCOUNT;j++){
			fileList.push_back(KoishiAvatar::NPK_avatar((AvatarCharacter)i, (AvatarPart)j));
		}
		WeaponSet ws = CWL((AvatarCharacter)i);
		for(DWORD j = 0;j<ws.size();j++){
			fileList.push_back(KoishiAvatar::NPK_weapon((AvatarCharacter)i, ws[j]));
		}
		fileList.push_back(KoishiAvatar::NPK_avatarIcon((AvatarCharacter)i));
		std::vector<str> strl = NPK_weaponIcon((AvatarCharacter)i);
		for(DWORD j = 0;j<strl.size();j++){
			fileList.push_back(strl[j]);
		}
	}
	return fileList;
}

typedef struct _ser_data{
	DWORD ID;
	DWORD servFlag;
}ser_data;

typedef union _img_data{
	ULONGLONG value;
	struct{
		DWORD layer;
		LONG ID;
	};
}img_data;

typedef std::vector<ser_data> ser_data_list;
typedef std::vector<img_data> img_data_list;

img_data parse(const str &imgPath){
	str nNum, sLayer;
	bool st = false;
	for(int i = 0;i<imgPath.size();i++){
		char c = imgPath[i];
		if(c >= '0' && c <= '9'){
			st = true;
			nNum.push_back(c);
		}else if(st){
			if(c == '.')
				break;
			sLayer.push_back(c);
		}
	}
	while(sLayer.size() < 3){
		sLayer.push_back('0');
	}
	img_data s1 = {0};
	s1.ID = nNum.size() ? std::stol(nNum) : -1;
	s1.layer = (sLayer[0] - '0') << 16 |  (sLayer[1] - '0') << 8 | (sLayer[2] - '0');
	return s1;
}

///////////////
//void GetFile(CString folderName, std::vector<CString> &fileList, std::vector<CString> &pathList) {
//	CFileFind ff;
//	//	fileList.clear();
//	//	pathList.clear();
//	BOOL ret = ff.FindFile(folderName);
//	while(ret) {
//		ret = ff.FindNextFile();
//		if(ff.IsDots())
//			continue;
//		if(ff.IsDirectory()) {
//			GetFile(ff.GetFilePath() + L"\\*.*", fileList, pathList);
//		} else {
//			fileList.push_back(ff.GetFileName());
//			pathList.push_back(ff.GetFilePath());
//		}
//	}
//}
void CExToolDlg::fun(){
	std::vector<str> fileList = getFileList();
	std::vector<str> serFolder;
	serFolder.push_back("./HF/");
	serFolder.push_back("./GF/");
	serFolder.push_back("./RF/");
	serFolder.push_back("./MF/");
	for(DWORD i = 0;i<fileList.size();i++){
		setPos1(1000 * i / fileList.size());
		NPKobject no_tn;
		NPKobject no;
		ser_data_list il_tn;
		ser_data_list il;
		bool isIcon = fileList[i].find("e_item") != str::npos;
		if(isIcon){
			if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 0)
				continue;
			for(int j = 0;j<4;j++){
				printf(L"Dealing "+CStr(fileList[i])+L" Folder: " + CStr(serFolder[j]) + L" ...");
				NPKobject no_temp;
				if(!no_temp.loadFile(serFolder[j] + fileList[i]))
					continue;
				for(int k = 0;k<no_temp.count;k++){
					str comment = no_temp.entry[k].comment;
					DWORD pos = 0;
					if(no.find(comment, pos)){
						IMGobject io1, io2;
						no.IMGextract(pos, io1);
						no_temp.IMGextract(k, io2);
						for(int m = 0;m<MAX(io1.indexCount, io2.indexCount);m++){
							if(m < io1.indexCount){
								PICinfo pi1, pi2;
								if(m >= io2.indexCount)
									break;
								io1.PICgetInfo(m, pi1);
								io2.PICgetInfo(m, pi2);
								if(pi1.picSize.H > 10)
									continue;
								if(pi2.picSize.H < 10)
									continue;
								image im;
								stream s;
								io2.PICextract(m, im);
								io1.PICpreprocess(im, s, pi2);
								io1.PICreplace(m, pi2, s);
							}else{
								PICinfo pi2;
								if(m >= io2.indexCount)
									break;
								io2.PICgetInfo(m, pi2);
								image im;
								stream s;
								io2.PICextract(m, im);
								io1.PICpreprocess(im, s, pi2);
								io1.PICpush(pi2, s);
							}
						}
						no.IMGreplace(pos, io1);
					}else{
						IMGobject io2;
						no_temp.IMGextract(k, io2);
						no.IMGpush(io2, comment);
					}
				}
			}
		}else{
			for(int j = 0;j<4;j++){
				printf(L"Dealing "+CStr(fileList[i])+L" Folder: " + CStr(serFolder[j]) + L" ...");
				NPKobject no_temp;
				if(!no_temp.loadFile(serFolder[j] + fileList[i]))
					continue;
				for(int k = 0;k<no_temp.count;k++){
					setPos2(1000 * k / (no_temp.count + 1));
					bool tn = false;
					str comment = no_temp.entry[k].comment;
					if(comment.find("waken") != str::npos)
						continue;
					if(comment.find("mask") != str::npos)
						continue;
					if(comment.find("(tn)") != str::npos)
						tn = true;
					std::vector<IMGobject> iol;
					IMGobject io;
					ser_data_list &ill = tn ? il_tn : il;
					NPKobject &noo = tn ? no_tn : no;
					//处理V6
					if(!no_temp.IMGextract(k, io))
						continue;
					if(io.version == V6){
						io.convertToV4(iol, colorList());
					}else{
						iol.push_back(io);
					}
					for(int m = 0;m<iol.size();m++){
						img_data id = parse(comment);
						if(id.ID == -1)
							continue;
						id.ID += m;
						//查找IMG
						if(noo.count == 0){
							noo.IMGpush(iol[m], formatAvatarIDplusBy(comment, m));
						}else{
							int haveFound = 0;
							int insertPos = -1;
							for(int n = 0;n<noo.count;n++){
								img_data ie = parse(noo.entry[n].comment);
								if(ie.ID == -1)
									continue;
								if(ie.value == id.value){
									insertPos = n;
									haveFound = 1;
									break;
								}
								if(ie.value > id.value){
									insertPos = n;
									break;
								}
							}
							if(insertPos == -1){
								noo.IMGpush(iol[m], formatAvatarIDplusBy(comment, m));
							}else if(haveFound){
								//Do nothing with IMGs..
							}else{
								noo.IMGinsert(insertPos, iol[m], formatAvatarIDplusBy(comment, m));
							}
						}
						//查找列表
						ser_data sd = {0};
						sd.ID = id.ID;
						sd.servFlag |= (1 << j);
						if(ill.size() == 0){
							ill.push_back(sd);
						}else{
							int haveFound = 0;
							int insertPos = -1;
							for(int n = 0;n<ill.size();n++){
								ser_data se = ill[n];
								if(se.ID == sd.ID){
									insertPos = n;
									haveFound = 1;
									break;
								}
								if(se.ID > sd.ID){
									insertPos = n;
									break;
								}
							}
							if(insertPos == -1){
								ill.push_back(sd);
							}else if(haveFound){
								ill[insertPos].servFlag |= (1 << j);
							}else{
								ill.insert(ill.begin() + insertPos, sd);
							}
						}
					}
				}
			}
		}
		printf(L"Merging "+CStr(fileList[i]) + L"...");
		for(int p = 0;p<no.count; p++){
			IMGobject io;
			no.IMGextract(p, io);
			no_tn.IMGpush(io, no.entry[p].comment);
		}
		if(no_tn.count){
			no_tn.saveFile(fileList[i]);
			
			if(!isIcon){
				CStdioFile file;
				file.Open(CStr(fileList[i])+L".csv", CFile::modeCreate|CFile::modeReadWrite);
				file.WriteString(L"ID,HF,GF,RF,MF\n");
				for(int i = 0;i<il_tn.size();i++){
					const ser_data &se = il_tn[i];
					CString line = CStr(se.ID) + L"(TN),";
					line += (se.servFlag & 0x01) ? L"O,":L",";
					line += (se.servFlag & 0x02) ? L"O,":L",";
					line += (se.servFlag & 0x04) ? L"O,":L",";
					line += (se.servFlag & 0x08) ? L"O\n":L"\n";
					file.WriteString(line);
				}
				for(int i = 0;i<il.size();i++){
					const ser_data &se = il[i];
					CString line = CStr(se.ID) + L",";
					line += (se.servFlag & 0x01) ? L"O,":L",";
					line += (se.servFlag & 0x02) ? L"O,":L",";
					line += (se.servFlag & 0x04) ? L"O,":L",";
					line += (se.servFlag & 0x08) ? L"O\n":L"\n";
					file.WriteString(line);
				}
				file.Close();
			}
		}
	}
}

#include <thread>
void CExToolDlg::OnBnClickedButton1() {
	// TODO:  线程1
	std::thread(fun20,this).detach();
}

typedef struct _img_version_term {
	long ver;
	int count;
	CString foundInNPKname;
	CString imgPathName;
}img_version_term;
typedef struct _frame_version_term {
	DWORD versString;		// IMGversion << 16 | PICinfo.format << 8 | PICinfo.comp e.g. "040E06"
	int count;
	CString foundInNPKname;
	CString foundInIMGname;
	int frameID;
}frame_version_term;
void updateImgBerQueryTable(const img_version_term &newTerm, std::vector<img_version_term> &imgVerQuery) {
	for(int i = 0; i < imgVerQuery.size(); i++) {
		if(imgVerQuery[i].ver == newTerm.ver) {
			imgVerQuery[i].count++;
			return;
		}
		if(imgVerQuery[i].ver > newTerm.ver) {
			imgVerQuery.insert(imgVerQuery.begin() + i, newTerm);
			return;
		}
	}
	imgVerQuery.push_back(newTerm);
}
void updateFrameVerQueryTable(const frame_version_term &newTerm, std::vector<frame_version_term> &frameVerQuery) {
	if(frameVerQuery.size() == 0) {
		frameVerQuery.push_back(newTerm);
		return;
	}
	for(int i = 0; i < frameVerQuery.size(); i++) {
		if(frameVerQuery[i].versString == newTerm.versString) {
			frameVerQuery[i].count++;
			return;
		}
		if(frameVerQuery[i].versString > newTerm.versString) {
			frameVerQuery.insert(frameVerQuery.begin() + i, newTerm);
			return;
		}
	}
	frameVerQuery.push_back(newTerm);
}
void CExToolDlg::fun2() {
	std::vector<CString> fileList, pathList;
	GetFile(L".", fileList, pathList);
	std::vector<img_version_term> imgVerQuery;
	std::vector<frame_version_term>frameVerQuery;
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
			img_version_term newTerm = {nVer, 1, fileList[i], StrToCStr(no.entry[imgID].comment)};
			updateImgBerQueryTable(newTerm, imgVerQuery);
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
				frame_version_term newTerm = {(isV1 ? 1 : io.version) << 16 | pi.format << 8 | pi.comp, 1, fileList[i], StrToCStr(no.entry[imgID].comment), frameID};
				updateFrameVerQueryTable(newTerm, frameVerQuery);
			}
		}
	}
	CStdioFile file;
	file.Open(L"1.TXT", CFile::modeCreate | CFile::modeWrite);
	for(img_version_term i : imgVerQuery) {
		CString line;
		line.Format(L"V%d,%d," + i.foundInNPKname + L"," + i.imgPathName, i.ver, i.count);
		file.WriteString(line + L"\n");
	}
	file.WriteString(L"\n");
	for(frame_version_term i : frameVerQuery) {
		CString line;
		line.Format(L"%06X,%d," + i.foundInNPKname + L"," + i.foundInIMGname + L",%d", i.versString, i.count, i.frameID);
		file.WriteString(line + L"\n");
	}
	file.Close();
}
typedef union part_and_layer {
	struct {
		BYTE layer[3];
		BYTE part;
	};
	DWORD value;
}part_and_layer;
typedef struct pal_term {
	part_and_layer value;
	int count;
	CString disc;
	CString imgPathName;
}pal_term;
void updatePalQueryTable(const pal_term &newTerm, std::vector<pal_term> &palQuery) {
	for(int i = 0; i < palQuery.size(); i++) {
		if(palQuery[i].value.value == newTerm.value.value) {
			palQuery[i].count++;
			return;
		}
		if(palQuery[i].value.value > newTerm.value.value) {
			palQuery.insert(palQuery.begin() + i, newTerm);
			return;
		}
	}
	palQuery.push_back(newTerm);
}
void CExToolDlg::fun3() {
	CFontDialog dlg;
	MAT2 mat;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	CDC *pDC = GetDC();
	GetTextMetricsW(pDC->m_hDC, &tm);
	
	/*std::vector<CString> fileList, pathList;
	GetFile(L".", fileList, pathList);
	std::vector<pal_term> palQuery;
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
			char ll[4] = {0};
			while(k < path.GetLength() && (path.GetAt(k) < '0' || path.GetAt(k) > '9')) {
				k++;
			}
			while(k < path.GetLength() && path.GetAt(k) >= '0' && path.GetAt(k) <= '9') {
				k++;
			}
			while(k < path.GetLength() && l <= 4 && path.GetAt(k) != '.') {
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
			updatePalQueryTable(newTerm, palQuery);
		}
	}
	CStdioFile file;
	file.Open(L"2.TXT", CFile::modeCreate | CFile::modeWrite);
	for(pal_term i : palQuery) {
		CString line;
		line.Format(i.disc + L",%d," + i.imgPathName ,i.count);
		file.WriteString(line + L"\n");
	}
	file.WriteString(L"\n");
	file.Close();*/
}

void CExToolDlg::OnBnClickedButton2() {
	// TODO:  在此添加控件通知处理程序代码
	// TODO:  线程1
	std::thread(fun30, this).detach();
}
