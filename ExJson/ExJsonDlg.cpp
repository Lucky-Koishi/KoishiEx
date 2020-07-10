
// ExJsonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExJson.h"
#include "ExJsonDlg.h"
#include "afxdialogex.h"
#include "../KoishiEx/KoishiNeoplePack.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiBase.cpp"
#include "../KoishiEx/Koishidata.cpp"
#include "../KoishiEx/Koishifactory.cpp"
#include "../KoishiEx/sha256.cpp"
#include "../KoishiEx/KoishiImageTool.cpp"
#include "../KoishiEx/KoishiAudioTool.cpp"
#include "../KoishiEx/avatar.cpp"
#include "../KoishiEx/KoishiExpand.cpp"
#include "../KoishiEx/BZ2.cpp"
#include <locale.h>
#include <vector>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void merge();
// CExJsonDlg 对话框

void CStrToStr(CString cstr,str &str1){  
    int n = cstr.GetLength();										//按字符计算，str的长度  
    int len = WideCharToMultiByte(CP_ACP,0,cstr,n,NULL,0,NULL,NULL);//按Byte计算str长度  
    char *pChStr = new char[len+1];									//按字节为单位  
    WideCharToMultiByte(CP_ACP,0,cstr,n,pChStr,len,NULL,NULL);		//宽字节转换为多字节编码  
    pChStr[len] = '\0';												//不要忽略末尾结束标志  
  
    str1 = pChStr;  
    delete []pChStr;  
}
str CStrToStr(CString cstr){
	str p;
	CStrToStr(cstr, p);
	return p;
}
CString NumToCStr(int n){
	CString s;
	s.Format(L"%d",n);
	return s;
}
CString NumToHexCStr(int n){
	CString s;
	s.Format(L"0x%04X",n);
	return s;
}
CString careerName[ACHARACTER_MAXCOUNT] = {
	L"鬼剑士(男)",L"鬼剑士(女)",L"格斗家(女)",L"格斗家(男)",
	L"神枪手(男)",L"神枪手(女)",L"魔法师(女)",L"魔法师(男)",
	L"圣职者(男)",L"圣职者(女)",
	L"暗夜使者",L"守护者",L"魔枪士",L"枪剑士"
};
CString suff =  L"装扮表.txt";
CExJsonDlg::CExJsonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExJsonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExJsonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExJsonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDSTART, &CExJsonDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CExJsonDlg 消息处理程序

BOOL CExJsonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"F:\\AvatarJson");
	GetDlgItem(IDC_EDIT2)->SetWindowText(L"F:\\DNF\\ImagePacks2");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExJsonDlg::OnPaint()
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
HCURSOR CExJsonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExJsonDlg::OnBnClickedStart()
{
	AfxBeginThread(writeThread, this);
}

CString ASCIItoUNICODE(const char*p){
	int len = MultiByteToWideChar(CP_UTF8, 0, (const char*)p, -1, NULL, 0);
	wchar_t *wszGBK = new wchar_t[len + 1];
	memset(wszGBK,0,len*2+2);
	MultiByteToWideChar(CP_UTF8, 0, (const char*)p, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len+1];
	memset(szGBK,0,len+1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	CString s1(szGBK);
	delete[] wszGBK;
	delete[] szGBK;
	return s1;
}
UINT CExJsonDlg::writeThread(void *p){
	//((CExJsonDlg *)p)->write();
	merge();
	return 0;
}
typedef std::vector<long> CLongArray;
typedef std::vector<CString> CStringMyArray;
void GetFile(CString folderName, CStringMyArray &fileList, CStringMyArray &pathList){
	CFileFind ff;
//	fileList.clear();
//	pathList.clear();
	BOOL ret = ff.FindFile(folderName);
	while(ret){
		ret = ff.FindNextFile();
		if(ff.IsDots())
			continue;
		if(ff.IsDirectory()){
			GetFile(ff.GetFilePath() + L"\\*.*", fileList, pathList);
		}else{
			fileList.push_back(ff.GetFileName());
			pathList.push_back(ff.GetFilePath());
		}
	}
}
typedef struct{
	AvatarCharacter charac;	//职业：查询usable job字段
	AvatarPart part;		//部件：查询layer variation字段，以Find的方式辨认
	WeaponType weaponType;	//部件：查询layer variation字段，以Find的方式辨认
	CString ID;				//ID：查询variation字段 第一个数字是总编号，第二个数字是调色板，计算方式为a*100+b
	CString name;			//[name]字段·如果带name字样就不计入
	CString icon;			//图标文字：查询icon字段，制作个映射表即可，映射表查不到则不计入
	CString partSet;		//查询套装编号，可以先记住(2为高级3为天空）武器无效
}UsefulThing;
typedef std::vector<UsefulThing> UsefulList;
BOOL parseLine1(const CString &line, std::vector<AvatarCharacter> &charList){
	charList.clear();
	CStringMyArray sa;
	CString theString;
	int i = 0;
	while(AfxExtractSubString(theString, line, i, '[')){
		CString tString;
		if(AfxExtractSubString(tString, theString, 0, ']')){
			if(tString == L"swordman"){
				charList.push_back(ACHARACTER_SM);
			}
			if(tString == L"at swordman"){
				charList.push_back(ACHARACTER_SG);
			}
			if(tString == L"fighter"){
				charList.push_back(ACHARACTER_FT);
			}
			if(tString == L"at fighter"){
				charList.push_back(ACHARACTER_FM);
			}
			if(tString == L"gunner"){
				charList.push_back(ACHARACTER_GN);
			}
			if(tString == L"at gunner"){
				charList.push_back(ACHARACTER_GG);
			}
			if(tString == L"mage"){
				charList.push_back(ACHARACTER_MG);
			}
			if(tString == L"at mage"){
				charList.push_back(ACHARACTER_MM);
			}
			if(tString == L"priest"){
				charList.push_back(ACHARACTER_PR);
			}
			if(tString == L"at priest"){
				charList.push_back(ACHARACTER_PG);
			}
			if(tString == L"thief"){
				charList.push_back(ACHARACTER_TH);
			}
			if(tString == L"knight"){
				charList.push_back(ACHARACTER_KN);
			}
			if(tString == L"demonic lancer"){
				charList.push_back(ACHARACTER_DL);
			}
			if(tString == L"gun blader"){
				charList.push_back(ACHARACTER_GB);
			}
		}
		i++;
	}
	return charList.size() > 0;
}
BOOL parseLine2(const CString &rString, AvatarPart &ap, WeaponType &wt){
	CString myString;
	if(AfxExtractSubString(myString, rString, 1, '`')){
		CString wpStr[AWEAPON_MAXCOUNT] = {
			L"lgswd", L"lswd", L"mswd", L"sswd", L"bswd", L"gemswd", L"beamswd", L"club", L"katana", L"lkatana",
			L"lblade", L"sblade", L"coreswd", L"arm", L"tonfa", L"gauntlet", L"boneclaw", L"claw", L"boxglove",L"glove",L"knuckle",
			L"auto", L"bowgun", L"hcan", L"musket", L"rev", L"pole", L"rod", L"spear", L"staff", L"broom",
			L"dagger", L"twinsword", L"wand", L"chakraweapon",L"halberd",L"pike",L"javelin",L"beamspear",
			L"khakkhara", L"rosary", L"scythe", L"totem", L"axe", L"cross"
		};
		for(int tt = 0;tt<AWEAPON_MAXCOUNT; tt++){
			if(myString.Find(wpStr[tt]) != -1){
				wt = (WeaponType)tt;
				if(tt == AWEAPON_MSWD){
					if(myString.Find(wpStr[AWEAPON_GEMSWD]) != -1){
						wt = AWEAPON_GEMSWD;
					}
					if(myString.Find(wpStr[AWEAPON_BEAMSWD]) != -1){
						wt = AWEAPON_BEAMSWD;
					}
				}
				if(tt == AWEAPON_KATANA){
					if(-1 != myString.Find(wpStr[AWEAPON_LKATANA])){
						wt = AWEAPON_LKATANA;
					}
				}
				goto find_weapon_over;
			}
		}
		CString apStr[APART_MAXCOUNT] = {
			L"cap", L"hair", L"face", L"neck", L"coat", L"pants", L"belt", L"shoes", L"body"
		};
		for(int tt = 0;tt<APART_MAXCOUNT; tt++){
			if(myString.Find(apStr[tt]) != -1){
				ap = (AvatarPart)tt;
				goto find_avatar_over;
			}
		}
	}
	ap = APART_UD;
	wt = AWEAPON_UD;
	return 0;
find_weapon_over:
	ap = APART_WEAPON;
	return 1;
find_avatar_over:
	wt = AWEAPON_UD;
	return 1;
}
BOOL parseLine3(const CString &rString, long &lID){
	CString s1, s2;
	if(!AfxExtractSubString(s1, rString, 0, 9))
		return 0;
	if(!AfxExtractSubString(s2, rString, 1, 9))
		return 0;
	lID = _ttol(s1) * 100 + _ttol(s2);
	return 1;
}
BOOL parseLine4(const CString &rString, CString &name){
	std::string ss;
	for(int i = 0;i<rString.GetLength();i++){
		if(rString.GetAt(i) != '`')
			ss.push_back(rString.GetAt(i));
	}
	name = ASCIItoUNICODE(ss.data());
	return 1;
}
BOOL parseLine5(const CString &rString, CString &final){
	CString s1, s2;
	if(!AfxExtractSubString(s1, rString, 0, 9))
		return 0;
	if(!AfxExtractSubString(s2, rString, 1, 9))
		return 0;
	CString enStr[37] = {
		L"lswd", L"sswd", L"club", L"katana", L"beamswd",
		L"bglove", L"claw", L"gauntlet", L"knuckle", L"tonfa",
		L"automatic", L"bowgun",L"hcannon",L"musket",L"revolver",
		L"broom",L"pole",L"rod",L"spear",L"staff",
		L"axe", L"cross",L"rosary",L"scythe",L"totem",
		L"chakra",L"dagger",L"twins",L"wand",
		L"beamspear",L"halberd",L"javelin",L"pike",
		L"coreswd",L"sblade",L"lblade",L"mswd"
	};
	CString chnStr[37] = {
		L"巨剑", L"短剑", L"钝器", L"太刀", L"光剑",
		L"拳套", L"爪", L"臂铠", L"手套", L"东方棍",
		L"自动手枪", L"手弩",L"手炮",L"步枪",L"左轮枪",
		L"扫把",L"棍棒",L"魔杖",L"矛",L"法杖",
		L"战斧", L"十字架",L"念珠",L"镰刀",L"图腾",
		L"苦无",L"匕首",L"双剑",L"手杖",
		L"光枪",L"战戟",L"暗矛",L"长枪",
		L"源力剑", L"小太刀", L"长刀", L"重剑"
	};
	for(int tt = 0;tt<37;tt++){
		if(s1.Find(enStr[tt]) != -1){
			final = chnStr[tt] + s2;
			return 1;
		}
	}
	CString enStr2[9] = {
		L"cap", L"hair", L"face", L"neck", L"coat", L"pants", L"belt", L"shoes", L"body"
	};
	CString chnStr2[9] = {
		L"头饰", L"发型", L"面部", L"胸部", L"上衣", L"下装", L"腰带", L"鞋子", L"皮肤"
	};
	for(int tt = 0;tt<9;tt++){
		if(s1.Find(enStr2[tt]) != -1){
			final = chnStr2[tt] + s2;
			return 1;
		}
	}
	return 0;
}
void GetUseFullThings(CString eduFileName, UsefulList &use){
	CStdioFile sf;
	if(!sf.Open(eduFileName, CFile::modeRead))
		return;
	CString line;
	UsefulThing useful;
	useful.part = APART_UD;
	useful.weaponType = AWEAPON_UD;
	std::vector<AvatarCharacter> charList;
	bool haveVariation = false;
	while(sf.ReadString(line)){
		if(line == L"[usable job]"){
			sf.ReadString(line);
			if(!parseLine1(line, charList))
				goto err_over;
		}else if(line == L"[layer variation]"){
			sf.ReadString(line);
			haveVariation = true;
			if(!parseLine2(line, useful.part, useful.weaponType))
				goto err_over;
		}else if(line == L"[variation]"){
			sf.ReadString(line);
			long lID;
			if(!parseLine3(line, lID))
				goto err_over;
			useful.ID.Format(L"%d", lID);
		}else if(line == L"[name]"){
			sf.ReadString(line);
			if(!parseLine4(line, useful.name))
				goto err_over;
		}else if(line == L"[icon]"){
			sf.ReadString(line);
			if(!parseLine5(line, useful.icon))
				goto err_over;
		}else if(line == L"[part set index]"){
			sf.ReadString(line);
			useful.partSet = line;
		}
	}
	if(!haveVariation)
		useful.part = APART_BODY;
	sf.Close();
	use.clear();
	for(int i = 0;i<charList.size();i++){
		useful.charac = charList[i];
		use.push_back(useful);
	}
	return;
err_over:
	use.clear();
	sf.Close();
	return;
}
void GetMixThings(CString eduFileName, CStringMyArray &rStringArray){
	CStdioFile sf;
	if(!sf.Open(eduFileName, CFile::modeRead))
		return;
	CString line;
	rStringArray.clear();
	while(sf.ReadString(line)){
		if(line == L"[layer variation]"){
			sf.ReadString(line);
			rStringArray.push_back(line);
		}
	}
}
void CExJsonDlg::write(){
	CProgressCtrl *pc = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	pc->SetRange32(0, 1000);
	CString folderName = L"E:\\VS2010\\Projects\\KoishiEx_Test\\character\\character\\*.*";
	std::vector<CString> fileList;
	std::vector<CString> pathList;
	GetFile(folderName, fileList, pathList);

	CLongArray la;
	CStringMyArray sa;
	AvatarMap map[ACHARACTER_MAXCOUNT];
	for(int c = 0;c<ACHARACTER_MAXCOUNT;c++){
		map[c].initial(AvatarCharacter(c));
	}
	for(int i = 0;i<pathList.size();i++){
		pc->SetPos(i*1000/pathList.size());
		if(pathList[i].Right(3) != L"equ")
			continue;
		UsefulList use;
		GetUseFullThings(pathList[i], use);
		for(int p = 0;p<use.size();p++){
			UsefulThing th = use[p];
			if(th.part == APART_UD)
				continue;
			if(th.name.Trim().GetLength() == 0)
				continue;
			if(th.name.Find(L"name") != -1)
				continue;
			if(th.name.Find(L"后续确认") != -1)
				continue;
			if(th.part == APART_WEAPON){
				if(map[th.charac].checkWeaponEntry(th.weaponType, _ttol(th.ID), CStrToStr(th.icon), CStrToStr(th.name)))
					continue;
			}else{
				if(map[th.charac].checkAvatarEntry(th.part, _ttol(th.ID), CStrToStr(th.icon), CStrToStr(th.name)))
					continue;
			}
			if(th.part == APART_WEAPON){
				map[th.charac].addWeaponEntry(th.weaponType, _ttol(th.ID), CStrToStr(th.icon), CStrToStr(th.name));
			}else{
				map[th.charac].addAvatarEntry(th.part, _ttol(th.ID), CStrToStr(th.icon), CStrToStr(th.name));
			}
		}
	}
	for(int c = 0;c<ACHARACTER_MAXCOUNT;c++){
		map[c].save(CStrToStr(careerName[c] + suff));
	}
	/*CStdioFile cf;
	cf.Open(L"ret.txt",CFile::modeCreate|CFile::modeReadWrite);
	for(int i = 0;i<fileList.size();i++){
		pc->SetPos(i * 1000 / fileList.size());
		if(pathList[i].Right(3) != L"NPK")
			continue;
		NPKobject no;
		if(!no.loadFile(CStrToStr(pathList[i])))
			continue;
		cf.WriteString(fileList[i]+L"\n");
		for(int j = 0;j<no.count;j++){
			IMGobject io;
			if(!no.IMGextract(j, io))
				continue;
			CString iname = CString(no.entry[j].comment.c_str());
			CString ivers = L"V" + NumToCStr(io.version);
			CString oneLine = iname + L"," + ivers + L",";
			std::vector<short> formatList;
			std::vector<int> formatCount;
			for(int k = 0;k<io.indexCount;k++){
				PICinfo pi;
				io.PICgetInfo(k, pi);
				if(pi.format == LINK)
					continue;
				short format = pi.format << 8 | pi.comp;
				if(formatList.size() == 0){
					formatList.push_back(format);
					formatCount.push_back(1);
					continue;
				}
				for(int l = 0;l<formatList.size();l++){
					if(format == formatList[l]){
						formatCount[l] ++;
						break;
					}else if(format > formatList[l]){
						formatList.insert(formatList.begin() + l, format);
						formatCount.insert(formatCount.begin() + l, 1);
						break;
					}
				}
			}
			for(int k = 0;k<formatList.size();k++){
				oneLine += NumToHexCStr(formatList[k]) + L",";
				oneLine += NumToCStr(formatCount[k]) + L",";
			}
			cf.WriteString(oneLine + L"\n");
		}
	}
	cf.Close();*/
}

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
WeaponSet CWL(const AvatarCharacter &character){
	WeaponSet result;
	for(int i = 0;i<WEAPON_MAXCOUNT_PER_CHAR;i++){
		if(CWT[character][i] == AWEAPON_UD)
			return result;
		result.push_back(CWT[character][i]);
	}
	return result;
}
typedef struct{
	long value;
	long layer;
	bool serv[4];
}infos1;
typedef std::vector<infos1> infos1List;
infos1 getNum(const str& nName){
	str nNum, sLayer;
	bool st = false;
	for(int i = 0;i<nName.size();i++){
		char c = nName[i];
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
	infos1 s1 = {0};
	s1.value = std::stol(nNum);
	s1.layer = (sLayer[0] - '0') << 16 |  (sLayer[1] - '0') << 8 | (sLayer[2] - '0');
	return s1;
}
void merge(){
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
	std::vector<str> serFolder;
	serFolder.push_back("./HF/");
	serFolder.push_back("./GF/");
	serFolder.push_back("./RF/");
	serFolder.push_back("./MF/");
	for(DWORD i = 0;i<fileList.size();i++){
		NPKobject no_tn;
		NPKobject no;
		infos1List il_tn;
		infos1List il;
		bool isIcon = fileList[i].find("e_item") != str::npos;
		if(isIcon){
			//...
		}else{
			for(int j = 0;j<4;j++){
				NPKobject no_temp;
				if(!no_temp.loadFile(serFolder[j] + fileList[i]))
					continue;
				for(int k = 0;k<no_temp.count;k++){
					bool tn = false;
					if(no_temp.entry[k].comment.find("waken") != str::npos)
						continue;
					if(no_temp.entry[k].comment.find("mask") != str::npos)
						continue;
					if(no_temp.entry[k].comment.find("(tn)") != str::npos)
						tn = true;
					std::vector<IMGobject> iol;
					IMGobject io;
					infos1List &ill = tn ? il_tn : il;
					NPKobject &noo = tn ? no_tn : no;
					if(!no_temp.IMGextract(k, io))
						continue;
					if(io.version == V6){
						io.convertToV4(iol, colorList());
					}else{
						iol.push_back(io);
					}
					for(int m = 0;m<iol.size();m++){
						infos1 is = {0};
						is.value = getNum(no_temp.entry[k].comment) + m;
						is.serv[j] = 1;
						if(ill.size() == 0){
							ill.push_back(is);
							noo.IMGpush(iol[m], ::formatAvatarIDplusBy(no_temp.entry[k].comment, m));
						}else{
							int insPos = -1;
							int haveSame = 0;
							for(int n = 0;n<ill.size();n++){
								if(ill[n].value >= is.value){
									insPos = n;
									if(ill[n].value == is.value)
										haveSame = 1;
									break;
								}
							}
							if(insPos == -1){
								ill.push_back(is);
								noo.IMGpush(iol[m], ::formatAvatarIDplusBy(no_temp.entry[k].comment, m));
							}else if(haveSame){
								ill[insPos].serv[j] = 1;
							}else{
								ill.insert(ill.begin() + insPos, is);
								noo.IMGinsert(insPos, iol[m], ::formatAvatarIDplusBy(no_temp.entry[k].comment, m));
							}
						}
					}
				}
			}
		}
		if(no.count)
			no.saveFile(fileList[i]);
	}
	int j = 0;
}