
// ExJsonDlg.cpp : ʵ���ļ�
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


// CExJsonDlg �Ի���

void CStrToStr(CString cstr,str &str1){  
    int n = cstr.GetLength();										//���ַ����㣬str�ĳ���  
    int len = WideCharToMultiByte(CP_ACP,0,cstr,n,NULL,0,NULL,NULL);//��Byte����str����  
    char *pChStr = new char[len+1];									//���ֽ�Ϊ��λ  
    WideCharToMultiByte(CP_ACP,0,cstr,n,pChStr,len,NULL,NULL);		//���ֽ�ת��Ϊ���ֽڱ���  
    pChStr[len] = '\0';												//��Ҫ����ĩβ������־  
  
    str1 = pChStr;  
    delete []pChStr;  
}
str CStrToStr(CString cstr){
	str p;
	CStrToStr(cstr, p);
	return p;
}
CString careerName[ACHARACTER_MAXCOUNT] = {
	L"��ʿ(��)",L"��ʿ(Ů)",L"�񶷼�(Ů)",L"�񶷼�(��)",
	L"��ǹ��(��)",L"��ǹ��(Ů)",L"ħ��ʦ(Ů)",L"ħ��ʦ(��)",
	L"ʥְ��(��)",L"ʥְ��(Ů)",
	L"��ҹʹ��",L"�ػ���",L"ħǹʿ",L"ǹ��ʿ"
};
CString suff =  L"װ���.txt";
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


// CExJsonDlg ��Ϣ�������

BOOL CExJsonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"F:\\AvatarJson");
	GetDlgItem(IDC_EDIT2)->SetWindowText(L"F:\\DNF\\ImagePacks2");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExJsonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	AvatarCharacter charac;	//ְҵ����ѯusable job�ֶ�
	AvatarPart part;		//��������ѯlayer variation�ֶΣ���Find�ķ�ʽ����
	WeaponType weaponType;	//��������ѯlayer variation�ֶΣ���Find�ķ�ʽ����
	CString ID;				//ID����ѯvariation�ֶ� ��һ���������ܱ�ţ��ڶ��������ǵ�ɫ�壬���㷽ʽΪa*100+b
	CString name;			//[name]�ֶΡ������name�����Ͳ�����
	CString icon;			//ͼ�����֣���ѯicon�ֶΣ�������ӳ����ɣ�ӳ���鲻���򲻼���
	CString partSet;		//��ѯ��װ��ţ������ȼ�ס(2Ϊ�߼�3Ϊ��գ�������Ч
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
		L"�޽�", L"�̽�", L"����", L"̫��", L"�⽣",
		L"ȭ��", L"צ", L"����", L"����", L"������",
		L"�Զ���ǹ", L"����",L"����",L"��ǹ",L"����ǹ",
		L"ɨ��",L"����",L"ħ��",L"ì",L"����",
		L"ս��", L"ʮ�ּ�",L"����",L"����",L"ͼ��",
		L"����",L"ذ��",L"˫��",L"����",
		L"��ǹ",L"ս�",L"��ì",L"��ǹ",
		L"Դ����", L"С̫��", L"����", L"�ؽ�"
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
		L"ͷ��", L"����", L"�沿", L"�ز�", L"����", L"��װ", L"����", L"Ь��", L"Ƥ��"
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
			if(th.name.Find(L"����ȷ��") != -1)
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
		L"\\avatar\\��ҹʹ��\\belt",L"\\avatar\\��ҹʹ��\\cap",L"\\avatar\\��ҹʹ��\\coat",L"\\avatar\\��ҹʹ��\\face",
		L"\\avatar\\��ҹʹ��\\hair",L"\\avatar\\��ҹʹ��\\neck",L"\\avatar\\��ҹʹ��\\pants",L"\\avatar\\��ҹʹ��\\shoes",
		L"\\avatar\\��ҹʹ��\\skin",
		L"\\avatar\\ħǹʿ\\belt",
		L"\\avatar\\ħǹʿ\\cap",
		L"\\avatar\\ħǹʿ\\coat",
		L"\\avatar\\ħǹʿ\\face",
		L"\\avatar\\ħǹʿ\\hair",
		L"\\avatar\\ħǹʿ\\neck",
		L"\\avatar\\ħǹʿ\\pants",
		L"\\avatar\\ħǹʿ\\shoes",
		L"\\avatar\\ħǹʿ\\skin",
		L"\\avatar\\�з�ʦ\\belt",
		L"\\avatar\\�з�ʦ\\cap",
		L"\\avatar\\�з�ʦ\\coat",
		L"\\avatar\\�з�ʦ\\face",
		L"\\avatar\\�з�ʦ\\hair",
		L"\\avatar\\�з�ʦ\\neck",
		L"\\avatar\\�з�ʦ\\pants",
		L"\\avatar\\�з�ʦ\\shoes",
		L"\\avatar\\�з�ʦ\\skin",
		L"\\avatar\\�и�\\belt",
		L"\\avatar\\�и�\\cap",
		L"\\avatar\\�и�\\coat",
		L"\\avatar\\�и�\\face",
		L"\\avatar\\�и�\\hair",
		L"\\avatar\\�и�\\neck",
		L"\\avatar\\�и�\\pants",
		L"\\avatar\\�и�\\shoes",
		L"\\avatar\\�и�\\skin",
		L"\\avatar\\�й�\\belt",
		L"\\avatar\\�й�\\cap",
		L"\\avatar\\�й�\\coat",
		L"\\avatar\\�й�\\face",
		L"\\avatar\\�й�\\hair",
		L"\\avatar\\�й�\\neck",
		L"\\avatar\\�й�\\pants",
		L"\\avatar\\�й�\\shoes",
		L"\\avatar\\�й�\\skin",
		L"\\avatar\\��ǹ��\\belt",
		L"\\avatar\\��ǹ��\\cap",
		L"\\avatar\\��ǹ��\\coat",
		L"\\avatar\\��ǹ��\\face",
		L"\\avatar\\��ǹ��\\hair",
		L"\\avatar\\��ǹ��\\neck",
		L"\\avatar\\��ǹ��\\pants",
		L"\\avatar\\��ǹ��\\shoes",
		L"\\avatar\\��ǹ��\\skin",
		L"\\avatar\\��ʥְ\\belt",
		L"\\avatar\\��ʥְ\\cap",
		L"\\avatar\\��ʥְ\\coat",
		L"\\avatar\\��ʥְ\\face",
		L"\\avatar\\��ʥְ\\hair",
		L"\\avatar\\��ʥְ\\neck",
		L"\\avatar\\��ʥְ\\pants",
		L"\\avatar\\��ʥְ\\shoes",
		L"\\avatar\\��ʥְ\\skin",
		L"\\avatar\\Ů��ʦ\\belt",
		L"\\avatar\\Ů��ʦ\\cap",
		L"\\avatar\\Ů��ʦ\\coat",
		L"\\avatar\\Ů��ʦ\\face",
		L"\\avatar\\Ů��ʦ\\hair",
		L"\\avatar\\Ů��ʦ\\neck",
		L"\\avatar\\Ů��ʦ\\pants",
		L"\\avatar\\Ů��ʦ\\shoes",
		L"\\avatar\\Ů��ʦ\\skin",
		L"\\avatar\\Ů��\\belt",
		L"\\avatar\\Ů��\\cap",
		L"\\avatar\\Ů��\\coat",
		L"\\avatar\\Ů��\\face",
		L"\\avatar\\Ů��\\hair",
		L"\\avatar\\Ů��\\neck",
		L"\\avatar\\Ů��\\pants",
		L"\\avatar\\Ů��\\shoes",
		L"\\avatar\\Ů��\\skin",
		L"\\avatar\\Ů��\\belt",
		L"\\avatar\\Ů��\\cap",
		L"\\avatar\\Ů��\\coat",
		L"\\avatar\\Ů��\\face",
		L"\\avatar\\Ů��\\hair",
		L"\\avatar\\Ů��\\neck",
		L"\\avatar\\Ů��\\pants",
		L"\\avatar\\Ů��\\shoes",
		L"\\avatar\\Ů��\\skin",
		L"\\avatar\\Ůǹ��\\belt",
		L"\\avatar\\Ůǹ��\\cap",
		L"\\avatar\\Ůǹ��\\coat",
		L"\\avatar\\Ůǹ��\\face",
		L"\\avatar\\Ůǹ��\\hair",
		L"\\avatar\\Ůǹ��\\neck",
		L"\\avatar\\Ůǹ��\\pants",
		L"\\avatar\\Ůǹ��\\shoes",
		L"\\avatar\\Ůǹ��\\skin",
		L"\\avatar\\Ůʥְ\\belt",
		L"\\avatar\\Ůʥְ\\cap",
		L"\\avatar\\Ůʥְ\\coat",
		L"\\avatar\\Ůʥְ\\face",
		L"\\avatar\\Ůʥְ\\hair",
		L"\\avatar\\Ůʥְ\\neck",
		L"\\avatar\\Ůʥְ\\pants",
		L"\\avatar\\Ůʥְ\\shoes",
		L"\\avatar\\Ůʥְ\\skin",
		L"\\avatar\\ǹ��ʿ\\belt",
		L"\\avatar\\ǹ��ʿ\\cap",
		L"\\avatar\\ǹ��ʿ\\coat",
		L"\\avatar\\ǹ��ʿ\\face",
		L"\\avatar\\ǹ��ʿ\\hair",
		L"\\avatar\\ǹ��ʿ\\neck",
		L"\\avatar\\ǹ��ʿ\\pants",
		L"\\avatar\\ǹ��ʿ\\shoes",
		L"\\avatar\\ǹ��ʿ\\skin",
		L"\\avatar\\�ػ���\\belt",
		L"\\avatar\\�ػ���\\cap",
		L"\\avatar\\�ػ���\\coat",
		L"\\avatar\\�ػ���\\face",
		L"\\avatar\\�ػ���\\hair",
		L"\\avatar\\�ػ���\\neck",
		L"\\avatar\\�ػ���\\pants",
		L"\\avatar\\�ػ���\\shoes",
		L"\\avatar\\�ػ���\\skin",
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
				cf.ReadString(line);//��һ��
				cf.ReadString(line);//��2��
				AfxExtractSubString(nm, line, 3, '\"');
				cf.ReadString(line);//��3��
				cf.ReadString(line);//��4��
				cf.ReadString(line);//��5��
				AfxExtractSubString(iconid, line, 1, ':'); //�����ŵ�
				iconid = iconid.TrimLeft();
				cf.ReadString(line);//��6��
				cf.ReadString(line);//��7�� ȡ��
				AfxExtractSubString(ps, line, 1, '\"');
				for(int j = 0;j<ps.GetLength();j++){
					char p = ps.GetAt(j);
					if(p >= '0' && p <= '9')
						idx += p;
				}
				int p1 = _ttoi(idx);
				int p2 = p1 / 100 * 100;	//��1
				int p3 = p1 % 100;			//����
				if(nm.GetLength()>0){
					cf.SeekToBegin();
					BYTE p;
					std::string ss;
					while(cf.Read(&p, 1) && p != '\"');//������˫����
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
					nm.Format(L"δ����[%d]", p1);
				}
				//�ж�һ��V4����V6
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
					//û�ҵ������CHECK2δ��ѡ��д
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
