// ToolAvatarDownload.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarDownload.h"
#include "afxdialogex.h"
#include "../KoishiEx/avatar.h"
#include "../KoishiEx/KoishiNeoplePack.h"

// ToolAvatarDownload 对话框

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
//

IMPLEMENT_DYNAMIC(ToolAvatarDownload, CDialogEx)

ToolAvatarDownload::ToolAvatarDownload(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarDownload::IDD, pParent)
{

}

ToolAvatarDownload::~ToolAvatarDownload()
{
}

void ToolAvatarDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarDownload, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ToolAvatarDownload::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_ALL, &ToolAvatarDownload::OnBnClickedButtonAll)
	ON_BN_CLICKED(IDC_BUTTON_NOS, &ToolAvatarDownload::OnBnClickedButtonNos)
	ON_BN_CLICKED(IDC_CHECK1, &ToolAvatarDownload::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &ToolAvatarDownload::OnBnClickedCheck2)
	ON_BN_CLICKED(ID_START, &ToolAvatarDownload::OnBnClickedStart)
END_MESSAGE_MAP()


// ToolAvatarDownload 消息处理程序


BOOL ToolAvatarDownload::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CButton, IDC_CHECK_CAREER1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER2)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER3)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER4)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER5)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER6)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER7)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER8)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER9)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER10)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER11)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER12)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER13)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER14)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_A1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_A2)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_A3)->SetCheck(1);
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"快速输入服务器");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"韩服客户端");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"韩服测试服客户端");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"日服客户端");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"美服客户端");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"国服西海岸1区客户端");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"国服西海岸2区客户端");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"国服天空之城客户端");
	GET_CTRL(CComboBox, IDC_COMBO1)->SetCurSel(0);
	GET_CTRL(CListCtrl, IDC_LIST1)->InsertColumn(0,L"资源文件名",0, 200);
	GET_CTRL(CListCtrl, IDC_LIST1)->InsertColumn(1,L"状态",0, 50);
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_hg/");
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ToolAvatarDownload::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(GET_CTRL(CComboBox, IDC_COMBO1)->GetCurSel()){
	case 1:
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_hg/");
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
		break;
	case 2:
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_open/");
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
		break;
	case 3:
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://webdown2.nexon.co.jp/arad/real/");
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
		break;
	case 4:
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://download.dfoneople.com/Patch/");
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
		break;
	case 5:
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp1.full.tct/");
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(0);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
		break;
	case 6:
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp2.full.tct/");
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(0);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
		break;
	case 7:
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp5.full.tct/");
		GET_CTRL(CButton, IDC_CHECK1)->SetCheck(0);
		GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
		break;
	}
}


void ToolAvatarDownload::OnBnClickedButtonAll()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK_CAREER1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER2)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER3)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER4)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER5)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER6)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER7)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER8)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER9)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER10)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER11)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER12)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER13)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK_CAREER14)->SetCheck(1);
}


void ToolAvatarDownload::OnBnClickedButtonNos()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK_CAREER1)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER2)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER3)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER4)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER5)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER6)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER7)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER8)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER9)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER10)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER11)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER12)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER13)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK_CAREER14)->SetCheck(0);
}


void ToolAvatarDownload::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
}


void ToolAvatarDownload::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
}


void ToolAvatarDownload::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	std::vector<DWORD> charList;
	if(GET_CTRL(CButton, IDC_CHECK_CAREER1)->GetCheck())
		charList.push_back(0);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER2)->GetCheck())
		charList.push_back(1);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER3)->GetCheck())
		charList.push_back(2);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER4)->GetCheck())
		charList.push_back(3);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER5)->GetCheck())
		charList.push_back(4);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER6)->GetCheck())
		charList.push_back(5);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER7)->GetCheck())
		charList.push_back(6);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER8)->GetCheck())
		charList.push_back(7);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER9)->GetCheck())
		charList.push_back(8);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER10)->GetCheck())
		charList.push_back(9);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER11)->GetCheck())
		charList.push_back(10);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER12)->GetCheck())
		charList.push_back(11);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER13)->GetCheck())
		charList.push_back(12);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER14)->GetCheck())
		charList.push_back(13);
	fileList.clear();
	for(DWORD i = 0;i<charList.size();i++){
		if(GET_CTRL(CButton, IDC_CHECK_A1)->GetCheck()){
			for(DWORD j = 0;j<APART_MAXCOUNT;j++){
				fileList.push_back(StrToCStr(KoishiAvatar::NPK_avatar((AvatarCharacter)charList[i], (AvatarPart)j)));
			}
		}
		if(GET_CTRL(CButton, IDC_CHECK_A2)->GetCheck()){
			WeaponSet ws = CWL((AvatarCharacter)charList[i]);
			for(DWORD j = 0;j<ws.size();j++){
				fileList.push_back(StrToCStr(KoishiAvatar::NPK_weapon((AvatarCharacter)charList[i], ws[j])));
			}
		}
		if(GET_CTRL(CButton, IDC_CHECK_A3)->GetCheck()){
			fileList.push_back(StrToCStr(KoishiAvatar::NPK_avatarIcon((AvatarCharacter)charList[i])));
		}
		if(GET_CTRL(CButton, IDC_CHECK_A3)->GetCheck()){
			std::vector<str> strl = NPK_weaponIcon((AvatarCharacter)charList[i]);
			for(DWORD j = 0;j<strl.size();j++){
				fileList.push_back(StrToCStr(strl[j]));
			}
		}
	}
	AfxBeginThread(threadDownloadSPKpatch, this);
}


UINT ToolAvatarDownload::threadDownloadSPKpatch(PVOID para){
	ToolAvatarDownload*dlg = (ToolAvatarDownload*)para;
	GET_DLG_CTRL(CButton, ID_START)->EnableWindow(false);
	GET_DLG_CTRL(CButton, IDCANCEL)->EnableWindow(false);
	dlg->downloadSPKpatch();
	GET_DLG_CTRL(CButton, ID_START)->EnableWindow(true);
	GET_DLG_CTRL(CButton, IDCANCEL)->EnableWindow(true);
	return 0U;
}

void ToolAvatarDownload::downloadSPKpatch(){
	profile.loadProfile();
	downloadPath = profile.getAvatarDownloadPath();
	CString ext = GET_CTRL(CButton, IDC_CHECK1)->GetCheck() ? L".spk":L".tct";
	CString urlText;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(urlText);
	int i, count = 0;
	for(i = 0;i<fileList.size();i++){
		GET_CTRL(CListCtrl, IDC_LIST1)->InsertItem(0, fileList[fileList.size() - 1 - i]);
		GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(0, 1, L"等待中");
	}
	for(i = 0;i<fileList.size();i++){
		GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"下载中");
		CString URL = urlText + L"ImagePacks2/" + fileList[i] + ext;
		CString localAddrFileName = downloadPath + fileList[i] + ext;
		if(0 != GetInternetFile(URL, localAddrFileName)){
			GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"下载失败");
			continue;
		}
		//解析
		CString NPKfileName = localAddrFileName.Left(localAddrFileName.GetLength() - 4);
		GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"解析中");
		if(ext == L".TCT" || ext == L".tct"){
			KoishiExpand::KoishiDownloadTool::TCTobject to;
			if(!to.load(CStrToStr(localAddrFileName))){
				GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"解析失败");
				continue;
			}
			to.makeNPK(CStrToStr(NPKfileName));
			GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"解析成功");
			count ++;
			continue;
		}
		if(ext == L".SPK" || ext == L".spk"){
			KoishiExpand::KoishiDownloadTool::SPKobject so;
			if(!so.load(CStrToStr(localAddrFileName))){
				GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"解析失败");
				continue;
			}
			so.makeNPK(CStrToStr(NPKfileName));
			GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"解析成功");
			count ++;
			continue;
		}
		GET_CTRL(CListCtrl, IDC_LIST1)->SetItemText(i,1, L"解析失败");
	}
	MessageBox(L"下载完毕喵！总共"+NumToCStr(fileList.size()) +L"个，成功"+NumToCStr(count)+L"个喵！",L"提示喵");
}