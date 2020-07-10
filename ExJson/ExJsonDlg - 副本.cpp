
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
	((CExJsonDlg *)p)->write();
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
#if 1
	for(int i = 0;i<pathList.size();i++){
		pc->SetPos(i*1000/pathList.size());
		if(pathList[i].Right(3) != L"equ")
			continue;
		
	}
#else
	
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
				map[th.charac].addWeaponEntry(th.weaponType, _ttol(th.ID), CStrToStr(th.icon), CStrToStr(th.name));
			}else{
				map[th.charac].addAvatarEntry(th.part, _ttol(th.ID), CStrToStr(th.icon), CStrToStr(th.name));
			}
		}
	}
	for(int c = 0;c<ACHARACTER_MAXCOUNT;c++){
		map[c].save(CStrToStr(careerName[c] + suff));
	}
#endif
	int o0 = 0;

	//setlocale(LC_CTYPE, old_locale);
	//free(old_locale);
	//sf.Close();
}

#ifdef FEIMAO_MODE
	*CString pList[9 * 14] = {
		L"\\avatar\\暗夜使者\\belt",L"\\avatar\\暗夜使者\\cap",L"\\avatar\\暗夜使者\\coat",L"\\avatar\\暗夜使者\\face",
		L"\\avatar\\暗夜使者\\hair",L"\\avatar\\暗夜使者\\neck",L"\\avatar\\暗夜使者\\pants",L"\\avatar\\暗夜使者\\shoes",
		L"\\avatar\\暗夜使者\\skin",
		L"\\avatar\\魔枪士\\belt",
		L"\\avatar\\魔枪士\\cap",
		L"\\avatar\\魔枪士\\coat",
		L"\\avatar\\魔枪士\\face",
		L"\\avatar\\魔枪士\\hair",
		L"\\avatar\\魔枪士\\neck",
		L"\\avatar\\魔枪士\\pants",
		L"\\avatar\\魔枪士\\shoes",
		L"\\avatar\\魔枪士\\skin",
		L"\\avatar\\男法师\\belt",
		L"\\avatar\\男法师\\cap",
		L"\\avatar\\男法师\\coat",
		L"\\avatar\\男法师\\face",
		L"\\avatar\\男法师\\hair",
		L"\\avatar\\男法师\\neck",
		L"\\avatar\\男法师\\pants",
		L"\\avatar\\男法师\\shoes",
		L"\\avatar\\男法师\\skin",
		L"\\avatar\\男格斗\\belt",
		L"\\avatar\\男格斗\\cap",
		L"\\avatar\\男格斗\\coat",
		L"\\avatar\\男格斗\\face",
		L"\\avatar\\男格斗\\hair",
		L"\\avatar\\男格斗\\neck",
		L"\\avatar\\男格斗\\pants",
		L"\\avatar\\男格斗\\shoes",
		L"\\avatar\\男格斗\\skin",
		L"\\avatar\\男鬼剑\\belt",
		L"\\avatar\\男鬼剑\\cap",
		L"\\avatar\\男鬼剑\\coat",
		L"\\avatar\\男鬼剑\\face",
		L"\\avatar\\男鬼剑\\hair",
		L"\\avatar\\男鬼剑\\neck",
		L"\\avatar\\男鬼剑\\pants",
		L"\\avatar\\男鬼剑\\shoes",
		L"\\avatar\\男鬼剑\\skin",
		L"\\avatar\\男枪手\\belt",
		L"\\avatar\\男枪手\\cap",
		L"\\avatar\\男枪手\\coat",
		L"\\avatar\\男枪手\\face",
		L"\\avatar\\男枪手\\hair",
		L"\\avatar\\男枪手\\neck",
		L"\\avatar\\男枪手\\pants",
		L"\\avatar\\男枪手\\shoes",
		L"\\avatar\\男枪手\\skin",
		L"\\avatar\\男圣职\\belt",
		L"\\avatar\\男圣职\\cap",
		L"\\avatar\\男圣职\\coat",
		L"\\avatar\\男圣职\\face",
		L"\\avatar\\男圣职\\hair",
		L"\\avatar\\男圣职\\neck",
		L"\\avatar\\男圣职\\pants",
		L"\\avatar\\男圣职\\shoes",
		L"\\avatar\\男圣职\\skin",
		L"\\avatar\\女法师\\belt",
		L"\\avatar\\女法师\\cap",
		L"\\avatar\\女法师\\coat",
		L"\\avatar\\女法师\\face",
		L"\\avatar\\女法师\\hair",
		L"\\avatar\\女法师\\neck",
		L"\\avatar\\女法师\\pants",
		L"\\avatar\\女法师\\shoes",
		L"\\avatar\\女法师\\skin",
		L"\\avatar\\女格斗\\belt",
		L"\\avatar\\女格斗\\cap",
		L"\\avatar\\女格斗\\coat",
		L"\\avatar\\女格斗\\face",
		L"\\avatar\\女格斗\\hair",
		L"\\avatar\\女格斗\\neck",
		L"\\avatar\\女格斗\\pants",
		L"\\avatar\\女格斗\\shoes",
		L"\\avatar\\女格斗\\skin",
		L"\\avatar\\女鬼剑\\belt",
		L"\\avatar\\女鬼剑\\cap",
		L"\\avatar\\女鬼剑\\coat",
		L"\\avatar\\女鬼剑\\face",
		L"\\avatar\\女鬼剑\\hair",
		L"\\avatar\\女鬼剑\\neck",
		L"\\avatar\\女鬼剑\\pants",
		L"\\avatar\\女鬼剑\\shoes",
		L"\\avatar\\女鬼剑\\skin",
		L"\\avatar\\女枪手\\belt",
		L"\\avatar\\女枪手\\cap",
		L"\\avatar\\女枪手\\coat",
		L"\\avatar\\女枪手\\face",
		L"\\avatar\\女枪手\\hair",
		L"\\avatar\\女枪手\\neck",
		L"\\avatar\\女枪手\\pants",
		L"\\avatar\\女枪手\\shoes",
		L"\\avatar\\女枪手\\skin",
		L"\\avatar\\女圣职\\belt",
		L"\\avatar\\女圣职\\cap",
		L"\\avatar\\女圣职\\coat",
		L"\\avatar\\女圣职\\face",
		L"\\avatar\\女圣职\\hair",
		L"\\avatar\\女圣职\\neck",
		L"\\avatar\\女圣职\\pants",
		L"\\avatar\\女圣职\\shoes",
		L"\\avatar\\女圣职\\skin",
		L"\\avatar\\枪剑士\\belt",
		L"\\avatar\\枪剑士\\cap",
		L"\\avatar\\枪剑士\\coat",
		L"\\avatar\\枪剑士\\face",
		L"\\avatar\\枪剑士\\hair",
		L"\\avatar\\枪剑士\\neck",
		L"\\avatar\\枪剑士\\pants",
		L"\\avatar\\枪剑士\\shoes",
		L"\\avatar\\枪剑士\\skin",
		L"\\avatar\\守护者\\belt",
		L"\\avatar\\守护者\\cap",
		L"\\avatar\\守护者\\coat",
		L"\\avatar\\守护者\\face",
		L"\\avatar\\守护者\\hair",
		L"\\avatar\\守护者\\neck",
		L"\\avatar\\守护者\\pants",
		L"\\avatar\\守护者\\shoes",
		L"\\avatar\\守护者\\skin",
	};
	CString tList[9 * 14] = {
		L"thief,belt",
		L"thief,cap",
		L"thief,coat",
		L"thief,face",
		L"thief,hair",
		L"thief,neck",
		L"thief,pants",
		L"thief,shoes",
		L"thief,skin",
		L"demoniclancer,belt",
		L"demoniclancer,cap",
		L"demoniclancer,coat",
		L"demoniclancer,face",
		L"demoniclancer,hair",
		L"demoniclancer,neck",
		L"demoniclancer,pants",
		L"demoniclancer,shoes",
		L"demoniclancer,skin",
		L"atmage,belt",
		L"atmage,cap",
		L"atmage,coat",
		L"atmage,face",
		L"atmage,hair",
		L"atmage,neck",
		L"atmage,pants",
		L"atmage,shoes",
		L"atmage,skin",
		L"atfighter,belt",
		L"atfighter,cap",
		L"atfighter,coat",
		L"atfighter,face",
		L"atfighter,hair",
		L"atfighter,neck",
		L"atfighter,pants",
		L"atfighter,shoes",
		L"atfighter,skin",
		L"swordman,belt",
		L"swordman,cap",
		L"swordman,coat",
		L"swordman,face",
		L"swordman,hair",
		L"swordman,neck",
		L"swordman,pants",
		L"swordman,shoes",
		L"swordman,skin",
		L"gunner,belt",
		L"gunner,cap",
		L"gunner,coat",
		L"gunner,face",
		L"gunner,hair",
		L"gunner,neck",
		L"gunner,pants",
		L"gunner,shoes",
		L"gunner,skin",
		L"priest,belt",
		L"priest,cap",
		L"priest,coat",
		L"priest,face",
		L"priest,hair",
		L"priest,neck",
		L"priest,pants",
		L"priest,shoes",
		L"priest,skin",
		L"mage,belt",
		L"mage,cap",
		L"mage,coat",
		L"mage,face",
		L"mage,hair",
		L"mage,neck",
		L"mage,pants",
		L"mage,shoes",
		L"mage,skin",
		L"fighter,belt",
		L"fighter,cap",
		L"fighter,coat",
		L"fighter,face",
		L"fighter,hair",
		L"fighter,neck",
		L"fighter,pants",
		L"fighter,shoes",
		L"fighter,skin",
		L"atswordman,belt",
		L"atswordman,cap",
		L"atswordman,coat",
		L"atswordman,face",
		L"atswordman,hair",
		L"atswordman,neck",
		L"atswordman,pants",
		L"atswordman,shoes",
		L"atswordman,skin",
		L"atgunner,belt",
		L"atgunner,cap",
		L"atgunner,coat",
		L"atgunner,face",
		L"atgunner,hair",
		L"atgunner,neck",
		L"atgunner,pants",
		L"atgunner,shoes",
		L"atgunner,skin",
		L"atpriest,belt",
		L"atpriest,cap",
		L"atpriest,coat",
		L"atpriest,face",
		L"atpriest,hair",
		L"atpriest,neck",
		L"atpriest,pants",
		L"atpriest,shoes",
		L"atpriest,skin",
		L"gunblader,belt",
		L"gunblader,cap",
		L"gunblader,coat",
		L"gunblader,face",
		L"gunblader,hair",
		L"gunblader,neck",
		L"gunblader,pants",
		L"gunblader,shoes",
		L"gunblader,skin",
		L"knight,belt",
		L"knight,cap",
		L"knight,coat",
		L"knight,face",
		L"knight,hair",
		L"knight,neck",
		L"knight,pants",
		L"knight,shoes",
		L"knight,skin"
	};
	CString nList[9 * 14] = {
		L"sprite_character_thief_equipment_avatar_belt",
		L"sprite_character_thief_equipment_avatar_cap",
		L"sprite_character_thief_equipment_avatar_coat",
		L"sprite_character_thief_equipment_avatar_face",
		L"sprite_character_thief_equipment_avatar_hair",
		L"sprite_character_thief_equipment_avatar_neck",
		L"sprite_character_thief_equipment_avatar_pants",
		L"sprite_character_thief_equipment_avatar_shoes",
		L"sprite_character_thief_equipment_avatar_skin",
		L"sprite_character_demoniclancer_equipment_avatar_belt",
		L"sprite_character_demoniclancer_equipment_avatar_cap",
		L"sprite_character_demoniclancer_equipment_avatar_coat",
		L"sprite_character_demoniclancer_equipment_avatar_face",
		L"sprite_character_demoniclancer_equipment_avatar_hair",
		L"sprite_character_demoniclancer_equipment_avatar_neck",
		L"sprite_character_demoniclancer_equipment_avatar_pants",
		L"sprite_character_demoniclancer_equipment_avatar_shoes",
		L"sprite_character_demoniclancer_equipment_avatar_skin",
		L"sprite_character_mage_atequipment_avatar_belt",
		L"sprite_character_mage_atequipment_avatar_cap",
		L"sprite_character_mage_atequipment_avatar_coat",
		L"sprite_character_mage_atequipment_avatar_face",
		L"sprite_character_mage_atequipment_avatar_hair",
		L"sprite_character_mage_atequipment_avatar_neck",
		L"sprite_character_mage_atequipment_avatar_pants",
		L"sprite_character_mage_atequipment_avatar_shoes",
		L"sprite_character_mage_atequipment_avatar_skin",
		L"sprite_character_fighter_atequipment_avatar_belt",
		L"sprite_character_fighter_atequipment_avatar_cap",
		L"sprite_character_fighter_atequipment_avatar_coat",
		L"sprite_character_fighter_atequipment_avatar_face",
		L"sprite_character_fighter_atequipment_avatar_hair",
		L"sprite_character_fighter_atequipment_avatar_neck",
		L"sprite_character_fighter_atequipment_avatar_pants",
		L"sprite_character_fighter_atequipment_avatar_shoes",
		L"sprite_character_fighter_atequipment_avatar_skin",
		L"sprite_character_swordman_equipment_avatar_belt",
		L"sprite_character_swordman_equipment_avatar_cap",
		L"sprite_character_swordman_equipment_avatar_coat",
		L"sprite_character_swordman_equipment_avatar_face",
		L"sprite_character_swordman_equipment_avatar_hair",
		L"sprite_character_swordman_equipment_avatar_neck",
		L"sprite_character_swordman_equipment_avatar_pants",
		L"sprite_character_swordman_equipment_avatar_shoes",
		L"sprite_character_swordman_equipment_avatar_skin",
		L"sprite_character_gunner_equipment_avatar_belt",
		L"sprite_character_gunner_equipment_avatar_cap",
		L"sprite_character_gunner_equipment_avatar_coat",
		L"sprite_character_gunner_equipment_avatar_face",
		L"sprite_character_gunner_equipment_avatar_hair",
		L"sprite_character_gunner_equipment_avatar_neck",
		L"sprite_character_gunner_equipment_avatar_pants",
		L"sprite_character_gunner_equipment_avatar_shoes",
		L"sprite_character_gunner_equipment_avatar_skin",
		L"sprite_character_priest_equipment_avatar_belt",
		L"sprite_character_priest_equipment_avatar_cap",
		L"sprite_character_priest_equipment_avatar_coat",
		L"sprite_character_priest_equipment_avatar_face",
		L"sprite_character_priest_equipment_avatar_hair",
		L"sprite_character_priest_equipment_avatar_neck",
		L"sprite_character_priest_equipment_avatar_pants",
		L"sprite_character_priest_equipment_avatar_shoes",
		L"sprite_character_priest_equipment_avatar_skin",
		L"sprite_character_mage_equipment_avatar_belt",
		L"sprite_character_mage_equipment_avatar_cap",
		L"sprite_character_mage_equipment_avatar_coat",
		L"sprite_character_mage_equipment_avatar_face",
		L"sprite_character_mage_equipment_avatar_hair",
		L"sprite_character_mage_equipment_avatar_neck",
		L"sprite_character_mage_equipment_avatar_pants",
		L"sprite_character_mage_equipment_avatar_shoes",
		L"sprite_character_mage_equipment_avatar_skin",
		L"sprite_character_fighter_equipment_avatar_belt",
		L"sprite_character_fighter_equipment_avatar_cap",
		L"sprite_character_fighter_equipment_avatar_coat",
		L"sprite_character_fighter_equipment_avatar_face",
		L"sprite_character_fighter_equipment_avatar_hair",
		L"sprite_character_fighter_equipment_avatar_neck",
		L"sprite_character_fighter_equipment_avatar_pants",
		L"sprite_character_fighter_equipment_avatar_shoes",
		L"sprite_character_fighter_equipment_avatar_skin",
		L"sprite_character_swordman_atequipment_avatar_belt",
		L"sprite_character_swordman_atequipment_avatar_cap",
		L"sprite_character_swordman_atequipment_avatar_coat",
		L"sprite_character_swordman_atequipment_avatar_face",
		L"sprite_character_swordman_atequipment_avatar_hair",
		L"sprite_character_swordman_atequipment_avatar_neck",
		L"sprite_character_swordman_atequipment_avatar_pants",
		L"sprite_character_swordman_atequipment_avatar_shoes",
		L"sprite_character_swordman_atequipment_avatar_skin",
		L"sprite_character_gunner_atequipment_avatar_belt",
		L"sprite_character_gunner_atequipment_avatar_cap",
		L"sprite_character_gunner_atequipment_avatar_coat",
		L"sprite_character_gunner_atequipment_avatar_face",
		L"sprite_character_gunner_atequipment_avatar_hair",
		L"sprite_character_gunner_atequipment_avatar_neck",
		L"sprite_character_gunner_atequipment_avatar_pants",
		L"sprite_character_gunner_atequipment_avatar_shoes",
		L"sprite_character_gunner_atequipment_avatar_skin",
		L"sprite_character_priest_atequipment_avatar_belt",
		L"sprite_character_priest_atequipment_avatar_cap",
		L"sprite_character_priest_atequipment_avatar_coat",
		L"sprite_character_priest_atequipment_avatar_face",
		L"sprite_character_priest_atequipment_avatar_hair",
		L"sprite_character_priest_atequipment_avatar_neck",
		L"sprite_character_priest_atequipment_avatar_pants",
		L"sprite_character_priest_atequipment_avatar_shoes",
		L"sprite_character_priest_atequipment_avatar_skin",
		L"sprite_character_gunblader_equipment_avatar_belt",
		L"sprite_character_gunblader_equipment_avatar_cap",
		L"sprite_character_gunblader_equipment_avatar_coat",
		L"sprite_character_gunblader_equipment_avatar_face",
		L"sprite_character_gunblader_equipment_avatar_hair",
		L"sprite_character_gunblader_equipment_avatar_neck",
		L"sprite_character_gunblader_equipment_avatar_pants",
		L"sprite_character_gunblader_equipment_avatar_shoes",
		L"sprite_character_gunblader_equipment_avatar_skin",
		L"sprite_character_knight_equipment_avatar_belt",
		L"sprite_character_knight_equipment_avatar_cap",
		L"sprite_character_knight_equipment_avatar_coat",
		L"sprite_character_knight_equipment_avatar_face",
		L"sprite_character_knight_equipment_avatar_hair",
		L"sprite_character_knight_equipment_avatar_neck",
		L"sprite_character_knight_equipment_avatar_pants",
		L"sprite_character_knight_equipment_avatar_shoes",
		L"sprite_character_knight_equipment_avatar_skin"
	};
	CString jsonPath;
	CString avatarPath;
	GetDlgItem(IDC_EDIT1)->GetWindowText(jsonPath);
	GetDlgItem(IDC_EDIT2)->GetWindowText(avatarPath);
	CStdioFile file;
	CProgressCtrl *pc = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	pc->SetRange32(0, 9 * 14);
	pc->SetPos(0);
	file.Open(L"avatardict.txt", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	for(int m=0;m<9*14;m++){
		CString t = tList[m];
		GetDlgItem(IDC_EDIT3)->SetWindowText(t);
		
		KoishiNeoplePack::NPKobject no;
		no.loadFile(CStrToStr(avatarPath + L"\\" + nList[m]+L".NPK"));
		std::vector<IMGversion> ivList;
		std::vector<int>idList;
		for(int i = 0;i<no.count;i++){
			str avStr = shorten(no.entry[i].comment);
			KoishiAvatar::avatar av;
			KoishiAvatar::avatarLayer al;
			KoishiAvatar::parseAvatarName(avStr, av, al);
			ivList.push_back((IMGversion)no.IMGgetVersion(i));
			idList.push_back(av.ID);
		}
		CString folderName = jsonPath + pList[m] + L"\\*.json";
		CFileFind fileFind;
		std::vector<CString> fileList;
		std::vector<CString> pathList;
		BOOL ret = fileFind.FindFile(folderName);
		while(ret){
			ret = fileFind.FindNextFile();
			fileList.push_back(fileFind.GetFileName());
			pathList.push_back(fileFind.GetFilePath());
		}
		if(1){
			file.WriteString(L"[" + t + L"]\n");
			/*ICONID,ID,PID*/
			for(int i = 0;i<fileList.size();i++){
				CStdioFile cf;
				cf.Open(pathList[i], CFile::modeRead);
				CString line, nm, iconid, ps, idx, id, pid;
				cf.ReadString(line);//第一行
				cf.ReadString(line);//第2行
				AfxExtractSubString(nm, line, 3, '\"');
				cf.ReadString(line);//第3行
				cf.ReadString(line);//第4行
				cf.ReadString(line);//第5行
				AfxExtractSubString(iconid, line, 1, ':'); //带逗号的
				iconid = iconid.TrimLeft();
				cf.ReadString(line);//第6行
				cf.ReadString(line);//第7行 取数
				AfxExtractSubString(ps, line, 1, '\"');
				for(int j = 0;j<ps.GetLength();j++){
					char p = ps.GetAt(j);
					if(p >= '0' && p <= '9')
						idx += p;
				}
				int p1 = _ttoi(idx);
				int p2 = p1 / 100 * 100;	//余1
				int p3 = p1 % 100;			//余数
				if(nm.GetLength()>0){
					cf.SeekToBegin();
					BYTE p;
					std::string ss;
					while(cf.Read(&p, 1) && p != '\"');//读三个双引号
					while(cf.Read(&p, 1) && p != '\"');
					while(cf.Read(&p, 1) && p != '\"');
					while(cf.Read(&p, 1)){
						if(p == '\"')
							break;
						ss.push_back(p);
					}
					nm = ASCIItoUNICODE(ss.data());
				}else{
					if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == FALSE){
						continue;
					}
					nm.Format(L"未命名[%d]", p1);
				}
				//判断一下V4还是V6
				bool isFound = false;
				bool isV6 = false;
				for(int j = 0;j<idList.size();j++){
					if(idList[j] == p2){
						isFound = true;
					}
					if(idList[j] / 100 *100 == p2 && ivList[j] == KoishiNeoplePack::V6){
						isV6 = true;
						isFound = true;
						break;
					}
				}
				if(!isFound){
					//没找到，如果CHECK2未勾选则不写
					if(((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck() == FALSE){
						continue;
					}
				}
				if(!isV6){
					id.Format(L"%d,0", p1);
					file.WriteString(iconid + id + L","+nm+L"\n");
				}else{
					//V6
					id.Format(L"%d,%d",p2,p3);
					file.WriteString(iconid + id + L","+nm+L"\n");
				}
			}
			file.WriteString(L"[end]\n");
		}
		no.release();
		pc->SetPos(m);
	}
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
	GetDlgItem(IDC_EDIT3)->SetWindowText(L"Done.");
#endif
