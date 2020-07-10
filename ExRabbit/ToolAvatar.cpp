// ToolAvatar.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "ToolAvatar.h"
#include "TinyBar.h"
#include "afxdialogex.h"
#include "ToolAvatarLocalizer.h"
#include "ToolAvatarCharacterSelection.h"
#include "ToolAvatarModelSet.h"
#include "ToolAvatarRegister.h"
#include "ToolAvatarSuit.h"
#include "ToolAvatarSuitRegister.h"
#include "ToolAvatarIO.h"
#include "ToolAvatarDownload.h"
#include "TinyFrame.h"
#include "ModalSaveWarning.h"

//自定义预先变量

long modelCFrame[ACHARACTER_MAXCOUNT] = {
	176, 0, 113, 0, 0, 0, 12, 0, 150, 0, 0, 0, 0, 0
};

CString avatarCString[APART_MAXCOUNT] = {
	L"头饰", L"发型", L"面部", L"胸部", L"上衣", L"下装", L"腰带", L"鞋子", L"皮肤"
};
CString weaponCString[AWEAPON_MAXCOUNT] = {
	L"西洋剑",L"巨剑",L"重剑",L"短剑",L"骨剑",L"宝石剑",L"光剑",L"钝器",L"太刀",L"长太刀",L"长刀",L"小太刀",L"源力剑",
	L"护肘",L"东方棍",L"臂铠",L"骨爪",L"金属爪",L"拳套",L"布手套",L"手套",
	L"自动手枪",L"手弩",L"手炮",L"步枪",L"左轮枪",
	L"棍棒", L"魔杖", L"矛", L"法杖", L"扫把", L"匕首", L"双剑", L"手杖", L"苦无", L"战戟", L"长枪", L"暗矛", L"光枪",
	L"锡杖",L"念珠", L"镰刀", L"图腾", L"战斧", L"十字架"
};
CString careerName[ACHARACTER_MAXCOUNT] = {
	L"鬼剑士(男)",L"鬼剑士(女)",L"格斗家(女)",L"格斗家(男)",
	L"神枪手(男)",L"神枪手(女)",L"魔法师(女)",L"魔法师(男)",
	L"圣职者(男)",L"圣职者(女)",
	L"暗夜使者",L"守护者",L"魔枪士",L"枪剑士"
};
CString iconCString[APART_MAXCOUNT] = {
	L"头饰", L"发型", L"面部", L"胸部", L"上衣", L"下装", L"腰带", L"鞋子", L"皮肤"
};
CString iconSpecCString = L"特殊皮肤";
//武器图标的字符串信息，排序方式由avatar.cpp下NPK_weaponIcon函数中的顺序决定
CString iconWeaponCString[ACHARACTER_MAXCOUNT][5] = {
	{L"巨剑", L"短剑", L"钝器", L"太刀", L"光剑"}, {L"巨剑", L"短剑", L"钝器", L"太刀", L"光剑"}, 
	{L"拳套", L"爪", L"臂铠", L"手套", L"东方棍"}, {L"拳套", L"爪", L"臂铠", L"手套", L"东方棍"}, 
	{L"自动手枪", L"手弩", L"手炮", L"步枪", L"左轮枪"}, {L"自动手枪", L"手弩", L"手炮", L"步枪", L"左轮枪"}, 
	{L"扫把", L"棍棒", L"魔杖", L"矛", L"法杖"}, {L"扫把", L"棍棒", L"魔杖", L"矛", L"法杖"}, 
	{L"战斧", L"十字架", L"念珠", L"镰刀", L"图腾"}, {L"战斧", L"十字架", L"念珠", L"镰刀", L"图腾"}, 
	{L"苦无", L"匕首", L"双剑", L"手杖", L""}, {L"巨剑", L"短剑", L"钝器", L"太刀", L"光剑"}, 
	{L"光枪", L"战戟", L"暗矛", L"长枪", L""}, {L"源力剑", L"小太刀", L"长刀", L"重剑", L""}
};
CString weaponIconClassified[ACHARACTER_MAXCOUNT][WEAPON_MAXCOUNT_PER_CHAR] = {
	{L"巨剑", L"巨剑", L"短剑", L"短剑", L"短剑", L"短剑", L"太刀", L"太刀", L"钝器", L"光剑", L""},
	{L"巨剑", L"巨剑", L"短剑", L"短剑", L"短剑", L"短剑", L"太刀", L"太刀", L"钝器", L"光剑", L""},
	{L"臂铠", L"臂铠", L"手套", L"手套", L"拳套", L"爪", L"爪", L"东方棍", L""},
	{L"臂铠", L"臂铠", L"手套", L"手套", L"拳套", L"爪", L"爪", L"东方棍", L""},
	{L"自动手枪", L"左轮枪", L"步枪", L"手弩", L"手炮",L""},
	{L"自动手枪", L"左轮枪", L"步枪", L"手弩", L"手炮",L""},
	{L"魔杖", L"法杖", L"棍棒", L"矛", L"扫把", L""},
	{L"魔杖", L"法杖", L"棍棒", L"矛", L"扫把", L""},
	{L"十字架", L"战斧", L"镰刀", L"图腾", L"念珠", L""},
	{L"十字架", L"战斧", L"镰刀", L"图腾", L"念珠", L"十字架", L""},
	{L"匕首", L"双剑", L"手杖", L"苦无", L""},
	{L"巨剑", L"巨剑", L"短剑", L"短剑", L"短剑", L"短剑", L"太刀", L"太刀", L"钝器", L""},
	{L"长枪", L"战戟", L"暗矛", L"光枪", L""},
	{L"重剑", L"小太刀", L"长刀", L"源力剑", L""}
};

// ToolAvatar 对话框

IMPLEMENT_DYNAMIC(ToolAvatar, CDialogEx)

ToolAvatar::ToolAvatar(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatar::IDD, pParent)
{
	currentPart = APART_COAT;
	currentWeaponIndex = 0;
	currentFrame = 0;
	currentPage = 0;
	currentIconSelect = -1;
	maxPage = 0;
	playing = false;
	TNmode = false;
	isIconic = false;
	loading = false;
}

ToolAvatar::~ToolAvatar()
{
}

void ToolAvatar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatar, CDialogEx)
	
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_WEAPON, &ToolAvatar::OnCbnSelchangeComboWeapon)
	ON_LBN_SELCHANGE(IDC_LIST_CONTENT, &ToolAvatar::OnLbnSelchangeListContent)
	ON_BN_CLICKED(IDC_BUTTON_PFRAME, &ToolAvatar::OnBnClickedButtonPframe)
	ON_BN_CLICKED(IDC_BUTTON_NFRAME, &ToolAvatar::OnBnClickedButtonNframe)
	ON_BN_CLICKED(IDC_BUTTON_TOOL1, &ToolAvatar::OnBnClickedButtonTool1)
	ON_BN_CLICKED(IDC_BUTTON_TOOL2, &ToolAvatar::OnBnClickedButtonTool2)
	ON_BN_CLICKED(IDC_BUTTON_TOOL3, &ToolAvatar::OnBnClickedButtonTool3)
	ON_BN_CLICKED(IDC_BUTTON_TOOL4, &ToolAvatar::OnBnClickedButtonTool4)
	ON_BN_CLICKED(IDC_BUTTON_TOOL5, &ToolAvatar::OnBnClickedButtonTool5)
	ON_BN_CLICKED(IDC_BUTTON_TOOL6, &ToolAvatar::OnBnClickedButtonTool6)
	ON_BN_CLICKED(IDC_BUTTON_TOOL7, &ToolAvatar::OnBnClickedButtonTool7)
	ON_BN_CLICKED(IDC_BUTTON_TOOL8, &ToolAvatar::OnBnClickedButtonTool8)
	ON_COMMAND(ID_MENU_AVATARSIZE_SMALL, &ToolAvatar::OnMenuAvatarsize1)
	ON_COMMAND(ID_MENU_AVATARSIZE_MEDIUM, &ToolAvatar::OnMenuAvatarsize2)
	ON_COMMAND(ID_MENU_AVATARSIZE_LARGE, &ToolAvatar::OnMenuAvatarsize3)
	ON_COMMAND(ID_MENU_AVATARSIZE_HUGE, &ToolAvatar::OnMenuAvatarsize4)
	ON_BN_CLICKED(IDC_BUTTON_TOOL10, &ToolAvatar::OnBnClickedButtonTool10)
	ON_BN_CLICKED(IDC_BUTTON_TOOL9, &ToolAvatar::OnBnClickedButtonTool9)
	ON_BN_CLICKED(IDC_BUTTON_TOOL11, &ToolAvatar::OnBnClickedButtonTool11)
	ON_COMMAND(ID_MENU_LOCALIZE_ONE, &ToolAvatar::OnMenuLocalizeOne)
	ON_COMMAND(ID_MENU_LOCALIZE_ALL, &ToolAvatar::OnMenuLocalizeAll)
	ON_COMMAND(ID_MENU_LOCALIZE_SET, &ToolAvatar::OnMenuLocalizeSet)
	ON_COMMAND(ID_MENU_AVATAR_FUN_TOEX, &ToolAvatar::OnMenuAvatarFunToEX)
	ON_COMMAND(ID_MENU_AVATAR_FUN_MAKENPK, &ToolAvatar::OnMenuAvatarFunMakeNPK)
	ON_COMMAND(ID_MENU_AVATAR_FUN_MAKEANTINPK, &ToolAvatar::OnMenuAvatarFunMakeAntiNPK)
	ON_COMMAND(ID_MENU_AVATAR_FUN_MAKE_ALLIN1_NPK, &ToolAvatar::OnMenuAvatarFunMakeAllIn1NPK)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTION, &ToolAvatar::OnCbnSelchangeComboAction)
	ON_COMMAND(ID_MENU_LOCALIZE_MAP_EDIT, &ToolAvatar::OnMenuLocalizeMapEdit)
	ON_COMMAND(ID_MENU_SUIT_LIST, &ToolAvatar::OnMenuSuitList)
	ON_COMMAND(ID_MENU_SUIT_REGISTER, &ToolAvatar::OnMenuSuitRegister)
	ON_COMMAND(ID_MENU_SUIT_IMPORT, &ToolAvatar::OnMenuSuitImport)
	ON_COMMAND(ID_MENU_SUIT_EXPORT, &ToolAvatar::OnMenuSuitExport)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_AVATARMODEL_REFRESH, &ToolAvatar::OnMenuAvatarmodelRefresh)
	ON_COMMAND(ID_MENU_AVATARMODEL_REGISTER, &ToolAvatar::OnMenuAvatarmodelRegister)
	ON_BN_CLICKED(IDC_BUTTON_TOOL12, &ToolAvatar::OnBnClickedButtonTool12)
	ON_COMMAND(ID_MENU_LOCALIZE_MAP_COMBINE, &ToolAvatar::OnMenuLocalizeMapCombine)
	ON_COMMAND(ID_MENU_LOCALIZE_MAP_RESORT, &ToolAvatar::OnMenuLocalizeMapResort)
	ON_COMMAND(ID_MENU_LOCALIZE_SET_RESOURCE, &ToolAvatar::OnMenuLocalizeSetResource)
	ON_COMMAND(ID_MENU_LOCALIZE_OPEN_RESOURCE, &ToolAvatar::OnMenuLocalizeOpenResource)
	ON_COMMAND(ID_MENU_LOCALIZE_DOWNLOAD_RESOURCE, &ToolAvatar::OnMenuLocalizeDownloadResource)
	ON_COMMAND(ID_MENU_SUIT_ANIMATION, &ToolAvatar::OnMenuSuitAnimation)
	ON_BN_CLICKED(IDC_BUTTON_AFRAME, &ToolAvatar::OnBnClickedButtonAframe)
	ON_BN_CLICKED(IDC_BUTTON_TOOL13, &ToolAvatar::OnBnClickedButtonTool13)
END_MESSAGE_MAP()


// ToolAvatar 消息处理程序


BOOL ToolAvatar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CREATEW(bar, IDD_TINY_PROGRESSBAR);

	SetWindowPos(NULL,0,0,1010,760,SWP_NOZORDER|SWP_NOMOVE);
	cbWeaponType = GET_CTRL(CComboBox, IDC_COMBO_WEAPON);
	lbContent = GET_CTRL(CListBox, IDC_LIST_CONTENT);
	eAvatarSuit = GET_CTRL(CEdit, IDC_EDIT_SUIT);
	eAvatarInfo = GET_CTRL(CEdit, IDC_EDIT_INFO);
	bTool[0] = GET_CTRL(CButton, IDC_BUTTON_TOOL1);
	bTool[1] = GET_CTRL(CButton, IDC_BUTTON_TOOL2);
	bTool[2] = GET_CTRL(CButton, IDC_BUTTON_TOOL3);
	bTool[3] = GET_CTRL(CButton, IDC_BUTTON_TOOL4);
	bTool[4] = GET_CTRL(CButton, IDC_BUTTON_TOOL5);
	bTool[5] = GET_CTRL(CButton, IDC_BUTTON_TOOL6);
	bTool[6] = GET_CTRL(CButton, IDC_BUTTON_TOOL7);
	bTool[7] = GET_CTRL(CButton, IDC_BUTTON_TOOL8);
	bTool[8] = GET_CTRL(CButton, IDC_BUTTON_TOOL9);
	bTool[9] = GET_CTRL(CButton, IDC_BUTTON_TOOL10);
	bTool[10] = GET_CTRL(CButton, IDC_BUTTON_TOOL11);
	bTool[11] = GET_CTRL(CButton, IDC_BUTTON_TOOL13);
	ePageInfo = GET_CTRL(CEdit, IDC_EDIT_PAGE);
	bPFrame = GET_CTRL(CButton, IDC_BUTTON_PFRAME);
	bNFrame = GET_CTRL(CButton, IDC_BUTTON_NFRAME);
	cbAction = GET_CTRL(CComboBox, IDC_COMBO_ACTION);

	m_buttonPic[0].LoadBitmap(IDB_TOOL_AV1);
	m_buttonPic[1].LoadBitmap(IDB_TOOL_AV2);
	m_buttonPic[2].LoadBitmap(IDB_TOOL_AV3);
	m_buttonPic[3].LoadBitmap(IDB_TOOL_AV4);
	m_buttonPic[4].LoadBitmap(IDB_TOOL_AV5);
	m_buttonPic[5].LoadBitmap(IDB_TOOL_AV6);
	m_buttonPic[6].LoadBitmap(IDB_TOOL_AV7);
	m_buttonPic[7].LoadBitmap(IDB_TOOL_AV8);
	m_buttonPic[8].LoadBitmap(IDB_TOOL_AV9);
	m_buttonPic[9].LoadBitmap(IDB_TOOL_AV10);
	m_buttonPic[10].LoadBitmap(IDB_TOOL_AV11);
	m_buttonPic[11].LoadBitmap(IDB_TOOL_AV12);
	m_buttonPicX[0].LoadBitmap(IDB_TOOL_AV1);
	m_buttonPicX[1].LoadBitmap(IDB_TOOL_AV2X);
	m_buttonPicX[2].LoadBitmap(IDB_TOOL_AV3X);
	m_buttonPicX[3].LoadBitmap(IDB_TOOL_AV4X);
	m_buttonPicX[4].LoadBitmap(IDB_TOOL_AV5);
	m_buttonPicX[5].LoadBitmap(IDB_TOOL_AV6);
	m_buttonPicX[6].LoadBitmap(IDB_TOOL_AV7);
	m_buttonPicX[7].LoadBitmap(IDB_TOOL_AV8);
	m_buttonPicX[8].LoadBitmap(IDB_TOOL_AV9);
	m_buttonPicX[9].LoadBitmap(IDB_TOOL_AV10);
	m_buttonPicX[10].LoadBitmap(IDB_TOOL_AV11);
	m_buttonPicX[11].LoadBitmap(IDB_TOOL_AV12);
	m_partPic[0].LoadBitmap(IDB_PART_0);
	m_partPic[1].LoadBitmap(IDB_PART_1);
	m_partPic[2].LoadBitmap(IDB_PART_2);
	m_partPic[3].LoadBitmap(IDB_PART_3);
	m_partPic[4].LoadBitmap(IDB_PART_4);
	m_partPic[5].LoadBitmap(IDB_PART_5);
	m_partPic[6].LoadBitmap(IDB_PART_6);
	m_partPic[7].LoadBitmap(IDB_PART_7);
	m_partPic[8].LoadBitmap(IDB_PART_8);
	m_partPic[9].LoadBitmap(IDB_PART_9);
	CString ttipstr[12] = {
		L"切换展示图尺寸", L"和谐开关", L"展示图模式", L"图标模式", L"脱下", L"更新", L"上一页", L"下一页", L"套装工具", L"补丁制作工具", L"本地化设置", L"随机装扮"
	};
	m_ttc.Create(this);
	for(int bi = 0;bi<12;bi++){
		bTool[bi]->SetBitmap(m_buttonPic[bi]);
		CString sw;
		bTool[bi]->GetWindowText(sw);
		m_ttc.AddTool(bTool[bi], ttipstr[bi]);
	}
	//图标菜单区域 x:10-220 y:10-70
	//职业选择区域 x:10-70 y:10-70
	//部件选择区域 边长30,5×2排列
	charImg[0].LoadBitmap(IDB_CHAR_0);
	charImg[1].LoadBitmap(IDB_CHAR_1);
	charImg[2].LoadBitmap(IDB_CHAR_2);
	charImg[3].LoadBitmap(IDB_CHAR_3);
	charImg[4].LoadBitmap(IDB_CHAR_4);
	charImg[5].LoadBitmap(IDB_CHAR_5);
	charImg[6].LoadBitmap(IDB_CHAR_6);
	charImg[7].LoadBitmap(IDB_CHAR_7);
	charImg[8].LoadBitmap(IDB_CHAR_8);
	charImg[9].LoadBitmap(IDB_CHAR_9);
	charImg[10].LoadBitmap(IDB_CHAR_10);
	charImg[11].LoadBitmap(IDB_CHAR_11);
	charImg[12].LoadBitmap(IDB_CHAR_12);
	charImg[13].LoadBitmap(IDB_CHAR_13);
	charImg[14].LoadBitmap(IDB_CHAR_NONE);
	charButton = new CStatic;
	charButton->Create(L"", SS_BITMAP | WS_VISIBLE | WS_CHILD, CRect(10, 10, 70, 70), this, 1999);
	charButton->SetBitmap(charImg[14]);
	for(int p0 = 0;p0<10;p0++){
		partButton[p0] = new CStatic;
		partButton[p0]->Create(L"", SS_BITMAP | WS_VISIBLE | WS_CHILD, CRect(70 + 30 * (p0 % 5), 10 + 30 * (p0 / 5), 100 + 30 * (p0 % 5), 40 + 30 * (p0 / 5)), this, 2000 + p0);
		partButton[p0]->SetBitmap(m_partPic[p0]);
	}

	SET_CTRL(CComboBox, IDC_COMBO_WEAPON, 10, 75, 220, 95);
	SET_CTRL(CListBox, IDC_LIST_CONTENT, 10, 100, 220, 240);
	SET_CTRL(CEdit, IDC_EDIT_INFO, 10, 245, 220, 305);
	SET_CTRL(CEdit, IDC_EDIT_SUIT, 10, 310, 220, 470);
	
	//画布区域 x:10-220 475-685
	SET_CTRL(CButton, IDC_BUTTON_PFRAME, 10, 690, 39, 715);
	SET_CTRL(CButton, IDC_BUTTON_AFRAME, 43, 690, 72, 715);
	SET_CTRL(CButton, IDC_BUTTON_NFRAME, 76, 690, 105, 715);
	SET_CTRL(CComboBox, IDC_COMBO_ACTION, 110, 690, 220, 715);

	int buttonSize = 30;
	int buttonGap = 2;
	SET_CTRL(CButton, IDC_BUTTON_TOOL1, 230 + 0 * (buttonSize + buttonGap), 10, 230 + buttonSize + 0 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL2, 230 + 1 * (buttonSize + buttonGap), 10, 230 + buttonSize + 1 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL3, 230 + 2 * (buttonSize + buttonGap), 10, 230 + buttonSize + 2 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL4, 230 + 3 * (buttonSize + buttonGap), 10, 230 + buttonSize + 3 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL5, 230 + 4 * (buttonSize + buttonGap), 10, 230 + buttonSize + 4 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL6, 230 + 5 * (buttonSize + buttonGap), 10, 230 + buttonSize + 5 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL7, 230 + 6 * (buttonSize + buttonGap), 10, 230 + buttonSize + 6 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CEdit, IDC_EDIT_PAGE,		230 + 7 * (buttonSize + buttonGap), 10, 230 + buttonSize + 8 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL8, 230 + 9 * (buttonSize + buttonGap), 10, 230 + buttonSize + 9 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL9, 230 + 10 * (buttonSize + buttonGap), 10, 230 + buttonSize + 10 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL10, 230 + 11 * (buttonSize + buttonGap), 10, 230 + buttonSize + 11 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL11, 230 + 12 * (buttonSize + buttonGap), 10, 230 + buttonSize + 12 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CEdit, IDC_EDIT_SEARCH, 230  + 13 * (buttonSize + buttonGap), 10, 230 + buttonSize + 16 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL12, 230 + 17 * (buttonSize + buttonGap), 10, 230 + buttonSize + 18 * (buttonSize + buttonGap), 10 + buttonSize);
	SET_CTRL(CButton, IDC_BUTTON_TOOL13, 230 + 19 * (buttonSize + buttonGap), 10, 230 + buttonSize + 19 * (buttonSize + buttonGap), 10 + buttonSize);

	//展示图区域
	//x:230-986 756
	//y:40-712 672
	lbContent->ResetContent();
	lbContent->AddString(L"无");
	lbContent->SetCurSel(0);
	cbWeaponType->ResetContent();
	cbWeaponType->AddString(L"不适用");
	cbWeaponType->SetCurSel(0);
	cbAction->ResetContent();
	cbAction->AddString(L"选择动作");
	cbAction->AddString(L"站立(通常)");
	cbAction->AddString(L"站立(备战)");
	cbAction->AddString(L"走路");
	cbAction->AddString(L"跑动");
	cbAction->AddString(L"普通攻击");
	cbAction->AddString(L"Z键攻击");
	cbAction->AddString(L"释放");
	cbAction->AddString(L"被攻击");
	cbAction->AddString(L"倒地");
	cbAction->AddString(L"全帧播放");
	cbAction->SetCurSel(0);

	currentPart = APART_COAT;
	currentWeaponIndex = 0;
	currentFrame = 0;
	currentPage = 0;
	currentIconSelect = -1;
	maxPage = 0;
	playing = false;
	TNmode = false;
	isIconic = false;
	bTool[2]->SetBitmap(m_buttonPicX[2]);
	bTool[3]->SetBitmap(m_buttonPic[3]);

	lastSelected = 0;

	AfxBeginThread(p,this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL ToolAvatar::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_MOUSEMOVE){
		m_ttc.RelayEvent(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void ToolAvatar::chooseCharacter(const AvatarCharacter &newCharacter){
	profile.loadProfile();
	character = newCharacter;
	currentPart = APART_COAT;
	currentWeaponIndex = 0;
	currentFrame = 0;
	playing = false;
	isIconic = false;
	bTool[2]->SetBitmap(m_buttonPicX[2]);
	bTool[3]->SetBitmap(m_buttonPic[3]);
	charButton->SetBitmap(charImg[character]);
	currentIconSelect = -1;
	initalModel(profile.avatarModelSize);
	factory.initial(newCharacter, CStrToStr(profile.getAvatarPath()));
	loadResource();
}
unsigned loadResource1(void*para){
	int i;
	ToolAvatar*dlg=(ToolAvatar*)para;
	dlg->loading = true;
	dlg->cbWeaponType->EnableWindow(false);
	dlg->bar.setInfo(L"");
	dlg->bar.show(dlg->factory.album.size() + dlg->factory.weaponAlbum.size());
	for(i = 0;i<dlg->factory.album.size();i++){
		dlg->bar.setInfo(L"导入"+avatarCString[i]+L"资源中……", i);
		dlg->factory.loadAvatar((AvatarPart)i);
		dlg->factory.album[i].changeAvatarByID((i == APART_CAP || i == APART_NECK || i == APART_BELT || i == APART_FACE)?-1:0);
	}
	dlg->cbWeaponType->ResetContent();
	for(i = 0;i<dlg->factory.weapon.size();i++){
		dlg->cbWeaponType->AddString(weaponCString[dlg->factory.weapon[i]]);
	}
	dlg->cbWeaponType->SetCurSel(0);
	for(i = 0;i<dlg->factory.weaponAlbum.size();i++){
		dlg->bar.setInfo(L"导入"+weaponCString[dlg->factory.weapon[i]]+L"资源中……", i + dlg->factory.album.size());
		dlg->factory.loadWeapon(i);
		dlg->factory.weaponAlbum[i].changeWeaponByID(0);
	}
	dlg->factory.changeWeaponType(0);
	//导入映射表
	dlg->bar.setInfo(L"导入装扮映射表中……", dlg->factory.album.size() + dlg->factory.weaponAlbum.size());
	str fileName = CStrToStr(dlg->profile.getAvatarMapPath() + careerName[dlg->character] + L"装扮表.txt");
	dlg->map.initial(dlg->character);
	dlg->map.load(fileName);
	dlg->map.save(fileName);
	//准备绘制元素
	dlg->bar.setInfo(L"准备绘制中……", dlg->factory.album.size() + dlg->factory.weaponAlbum.size());
	long modelFrame[ACHARACTER_MAXCOUNT] = {
		176, 0, 113, 0, 0, 0, 12, 0, 150, 0, 0, 0, 0, 0
	};
	dlg->stage.load(dlg->profile.getAvatarStagePath());
	dlg->factory.changeFrame(modelCFrame[dlg->character]);
	dlg->factory.updateImage();
	dlg->currentPart = APART_COAT;
	dlg->currentWeaponIndex = 0;
	if(dlg->factory.album[APART_BODY].content.size() > 0){
		dlg->basePoint = dlg->factory.album[APART_BODY].layerBasePointList[0] - point(100, 100) + point(dlg->factory.album[APART_BODY].layerImageList[0].getWidth(), dlg->factory.album[APART_BODY].layerImageList[0].getHeight())/2;
		dlg->maxFrame = dlg->factory.album[APART_BODY].layerIMGlist[0].indexCount;
	}else{
		dlg->bar.setInfo(L"皮肤资源缺失，无法确定基准坐标。", dlg->factory.album.size() + dlg->factory.weaponAlbum.size());
		dlg->basePoint = point(0, 0);
		dlg->maxFrame = 0;
		Sleep(100);
	}
	dlg->drawAvatar();
	dlg->updateList();
	dlg->currentPage = 0;
	dlg->maxPage = dlg->factory.album[dlg->currentPart].content.size() / dlg->modelInfo.countPerPage + 1;
	dlg->updateSuitInfo();
	dlg->updatePageInfo();
	dlg->showAvatarInfo();
	dlg->drawModel(-1);
	dlg->bar.setInfo(L"准备完毕。", dlg->factory.album.size() + dlg->factory.weaponAlbum.size());
	Sleep(50);
	dlg->bar.hide();
	dlg->loading = false;
	if(dlg->factory.album[APART_BODY].content.size() == 0){
		dlg->MessageBox(L"未能读取到数据喵，请先设置好资源文件夹喵！", L"提示喵");
	}
	return 0U;
}
void ToolAvatar::loadResource(){
	AfxBeginThread(loadResource1, this);
}
void ToolAvatar::initalModel(const int &newSizeMode){
	//672-84 96 112 168 28
	//756:54 63 84 126
	long widthEnum[5] = {54, 63, 84, 126, 28};		//750→756
	long heightEnum[5] = {84, 96, 112, 168, 28};	//675→672
	long countPerRowEnum[5] = {14, 12, 9, 6, 27};
	long rowEnum[5] = {8, 7, 6, 4, 24};
	modelInfo.sizeMode = newSizeMode > 4 ? 4 : (newSizeMode < 0 ? 0 : newSizeMode);
	modelInfo.width = widthEnum[modelInfo.sizeMode];
	modelInfo.height = heightEnum[modelInfo.sizeMode];
	modelInfo.countPerRow = countPerRowEnum[modelInfo.sizeMode];
	modelInfo.row = rowEnum[modelInfo.sizeMode];
	modelInfo.countPerPage = modelInfo.row * modelInfo.countPerRow;
}
void ToolAvatar::updateList(){
	lbContent->ResetContent();
	if(currentPart == APART_WEAPON){
		lbContent->InsertString(0, L"无");
		for(long i = 0; i < factory.weaponAlbum[currentWeaponIndex].content.size();i++){
		//	lbContent->InsertString(i+1, NumToCStr(factory.weaponAlbum[currentWeaponIndex].content[i].ID));
			CString tStr;
			CString iStr = L"[" + NumToCStr(factory.weaponAlbum[currentWeaponIndex].content[i].ID) + L"]";
			queue q = map.findWeaponPos(map.weapon[currentWeaponIndex], factory.weaponAlbum[currentWeaponIndex].content[i].ID);
			if(q.size() == 0){
				tStr = iStr + L"未命名"+weaponCString[factory.weapon[currentWeaponIndex]];
			}else if(q.size() == 1){
				tStr = iStr + StrToCStr(map.weaponContent[currentWeaponIndex][q[0]].avatarTitle);
			}else{
				tStr = iStr + StrToCStr(map.weaponContent[currentWeaponIndex][q[0]].avatarTitle) + L"[...]";
			}
			lbContent->InsertString(i+1, tStr);
		}
		if(factory.weaponAlbum[currentWeaponIndex].currentSelect < factory.weaponAlbum[currentWeaponIndex].content.size()){
			lbContent->SetCurSel(factory.weaponAlbum[currentWeaponIndex].currentSelect + 1);
		}else{
			lbContent->SetCurSel(0);
		}
	}else{
		lbContent->InsertString(0, L"无");
		for(long i = 0; i < factory.album[currentPart].content.size();i++){
		//	lbContent->InsertString(i+1, NumToCStr(factory.album[currentPart].content[i].ID));
			CString tStr;
			CString iStr = L"[" + NumToCStr(factory.album[currentPart].content[i].ID) + L"]";
			queue q = map.findAvatarPos(currentPart, factory.album[currentPart].content[i].ID);
			if(q.size() == 0){
				tStr = iStr + L"未命名"+avatarCString[currentPart];
			}else if(q.size() == 1){
				tStr = iStr + StrToCStr(map.avatarContent[currentPart][q[0]].avatarTitle);
			}else{
				tStr = iStr + StrToCStr(map.avatarContent[currentPart][q[0]].avatarTitle) + L"[...]";
			}
			lbContent->InsertString(i+1, tStr);
		}
		if(factory.album[currentPart].currentSelect < factory.album[currentPart].content.size()){
			lbContent->SetCurSel(factory.album[currentPart].currentSelect + 1);
		}else{
			lbContent->SetCurSel(0);
		}
	}
}
void ToolAvatar::updatePageInfo(){
	ePageInfo->SetWindowText(NumToCStr(1+currentPage)+L"/"+NumToCStr(maxPage));
}
void ToolAvatar::showAvatarInfo(){
	CString s;
	if(currentPart == APART_WEAPON){
		const WeaponAlbum &wa = factory.weaponAlbum[currentWeaponIndex];
		if(wa.currentSelect == -1){
			s = L"当前处于未选择状态。";
		}else{
			s.Format(L"图层信息：(%d个)", wa.layerList.size());
			for(int i = 0;i<wa.layerList.size();i++){
				s += StrToCStr(wa.layerList[i].layer);
				if(i < wa.layerList.size() - 1)
					s += L", ";
			}
			s+=L"\r\n";
			const WeaponType &wt = map.weapon[currentWeaponIndex];
			s += L"武器类型：" + weaponCString[wt] + L"\r\n";
			queue q = map.findWeaponPos(wt, wa.content[wa.currentSelect].ID);
			s += L"武器信息：";
			if(q.size() == 0){
				s += L"未知名称";
			}else for(int q1 = 0;q1<q.size();q1++){
				s += StrToCStr(map.weaponContent[currentWeaponIndex][q[q1]].avatarTitle);
				if(q1 < q.size() - 1)
					s += L", ";
			}
			CString s1;
			s1.Format(L"[%d]", wa.content[wa.currentSelect].ID);
			s += s1;
			s += L"\r\n";
			s += L"图标信息：";
			if(q.size() == 0){
				s += L"未知项";
			}else{
				s += StrToCStr(map.weaponContent[currentWeaponIndex][q[0]].iconName);
			}
		}
	}else{
		const AvatarAlbum &aa = factory.album[currentPart];
		if(aa.currentSelect == -1){
			s = L"当前处于未选择状态。";
		}else{
			s.Format(L"图层信息：(%d个)", aa.layerList.size());
			for(int i = 0;i<aa.layerList.size();i++){
				s += StrToCStr(aa.layerList[i].layer);
				if(i < aa.layerList.size() - 1)
					s += L", ";
			}
			s+=L"\r\n";
			queue q = map.findAvatarPos(currentPart, aa.content[aa.currentSelect].ID);
			s += L"装扮信息：";
			if(q.size() == 0){
				s += L"未知名称";
			}else for(int q1 = 0;q1<q.size();q1++){
				s += StrToCStr(map.avatarContent[currentPart][q[q1]].avatarTitle);
				if(q1 < q.size() - 1)
					s += L", ";
			}
			CString s1;
			s1.Format(L"[%d]", aa.content[aa.currentSelect].ID);
			s += s1;
			s += L"\r\n";
			s += L"套装信息：";
			queue qs = map.findSuitPos(currentPart, aa.content[aa.currentSelect].ID);
			if(qs.size() == 0){
				s += L"散装";
			}else for(int q1 = 0;q1<qs.size();q1++){
				s += StrToCStr(map.suitContent[q1].suitName);
				if(q1 < qs.size() - 1)
					s += L", ";
			}
			s += L"\r\n";
			s += L"图标信息：";
			if(q.size() == 0){
				s += L"未知项";
			}else{
				s += StrToCStr(map.avatarContent[currentPart][q[0]].iconName);
			}
		}
	}
	eAvatarInfo->SetWindowText(s);
}
void ToolAvatar::updateSuitInfo(){
	CString cstr;
	for(int i = 0;i<APART_MAXCOUNT;i++){
		cstr += avatarCString[i] + L"：";
		if(factory.album[i].currentSelect == -1){
			cstr += L"未选择";
		}else{
			cstr +=NumToCStr(factory.album[i].content[factory.album[i].currentSelect].ID);
		}
		cstr += L"\r\n";
	}
	cstr += L"武器：";
	if(factory.weaponAlbum[factory.currentWeapon].currentSelect == -1){
		cstr += L"未选择";
	}else{
		cstr += weaponCString[factory.weapon[factory.currentWeapon]] + L"_";
		cstr += NumToCStr(factory.weaponAlbum[factory.currentWeapon].currentSelect);
	}
	eAvatarSuit->SetWindowText(cstr);
}
void ToolAvatar::drawModel(int indexInPage){
	if(indexInPage == -1){
		for(int i = 0;i<modelInfo.countPerPage;i++)
			drawModel(i);
		return;
	}
	image oneImage;
	if(!isIconic){
		if(currentPart == APART_WEAPON){
			const WeaponAlbum &wa = factory.weaponAlbum[currentWeaponIndex];
			int id = indexInPage + modelInfo.countPerPage * currentPage;
			if(id < wa.content.size()){
				int weaponID = wa.content[id].ID;
				CString fileNameW = profile.getModelPath(modelInfo.sizeMode, character) 
						+ weaponCString[factory.weapon[currentWeaponIndex]] 
						+ NumToCStr(weaponID);
				str fileName = CStrToStr(fileNameW) + ".png";
				str fileNameTN = CStrToStr(fileNameW) + "(TN).png";
				if(TNmode){
					if(!loadPNG(oneImage, fileNameTN) && !loadPNG(oneImage, fileName)){
						factory.makeButtonImage(oneImage, size(modelInfo.width, modelInfo.height), 1);
					}
				}else{
					if(!loadPNG(oneImage, fileName)){
						factory.makeButtonImage(oneImage, size(modelInfo.width, modelInfo.height), 1);
					}
				}
			}else{
				factory.makeButtonImage(oneImage, size(modelInfo.width, modelInfo.height), 0);
			}
			if(id == wa.currentSelect){
				oneImage.getBrighten();
			}
		}else/*if(currentPart != APART_WEAPON)*/{
			const AvatarAlbum &aa = factory.album[currentPart];
			int id = indexInPage + modelInfo.countPerPage * currentPage;
			if(id < aa.content.size()){
				int avatarID = aa.content[id].ID;
				CString fileNameW = profile.getModelPath(modelInfo.sizeMode, character) 
						+ avatarCString[currentPart] 
						+ NumToCStr(avatarID);
				str fileName = CStrToStr(fileNameW) + ".png";
				str fileNameTN = CStrToStr(fileNameW) + "(TN).png";
				if(TNmode){
					if(!loadPNG(oneImage, fileNameTN) && !loadPNG(oneImage, fileName)){
						factory.makeButtonImage(oneImage, size(modelInfo.width, modelInfo.height), 1);
					}
				}else{
					if(!loadPNG(oneImage, fileName)){
						factory.makeButtonImage(oneImage, size(modelInfo.width, modelInfo.height), 1);
					}
				}
			}else{
				factory.makeButtonImage(oneImage, size(modelInfo.width, modelInfo.height), 0);
			}
			if(id == aa.currentSelect){
				oneImage.getBrighten();
			}
		}
	}else/*if(isIconic)*/{
		image noEntry, othEntry;
		noEntry.create(14, 14);
		othEntry.create(14, 14);
		for(int t = 0;t<14;t++){
			noEntry.line(point(t, 0), point(0, t), color(0xFF, 0, 0));
			othEntry.line(point(t, 0), point(0, t), color(0, 0, 0xFF));
		}
		for(int t = 3;t<=5;t++){
			noEntry.line(point(t,1), point(t,7),color(0xFF, 0xFF, 0));
			othEntry.line(point(t,1), point(t,7),color(0xFF, 0xFF, 0));
		}
		noEntry.line(point(3, 5), point(5,5), color(0xFF, 0, 0));
		othEntry.line(point(3, 5), point(5,5), color(0, 0, 0xFF));
		if(currentPart == APART_WEAPON){
			int id = indexInPage + modelInfo.countPerPage * currentPage;
			iconEnabled[id] = false;
			str fileName = CStrToStr(profile.getIconPath(character) 
				+ weaponIconClassified[character][currentWeaponIndex]
				+ NumToCStr(id)) + ".png";
			if(!loadPNG(oneImage, fileName)){
				oneImage.create(28,28);
				oneImage.fill(color(0, 0, 0));
			}else{
				iconEnabled[id] = true;
				oneImage.rectangle(point(0,0), point(27,27), color(0,0,0));
				queue q = map.findWeaponPosByIcon(map.weapon[currentWeaponIndex], CStrToStr(weaponIconClassified[character][currentWeaponIndex]+NumToCStr(id)));
				if(q.size() == 0)
					oneImage.putFore(noEntry);
				if(q.size() > 0){
					int idx = map.weaponContent[currentWeaponIndex][q[0]].avatarID;
					if(factory.weaponAlbum[currentWeaponIndex].findWeaponID(idx) == -1)
						oneImage.putFore(othEntry);
				}
				if(id == currentIconSelect)
					oneImage.getBrighten();
			}
		}else{
			int id = indexInPage + modelInfo.countPerPage * currentPage;
			iconEnabled[id] = false;
			str fileName = CStrToStr(profile.getIconPath(character) 
				+ avatarCString[currentPart] 
				+ NumToCStr(id)) + ".png";
			if(!loadPNG(oneImage, fileName)){
				oneImage.create(28,28);
				oneImage.fill(color(0, 0, 0));
			}else{
				iconEnabled[id] = true;
				oneImage.rectangle(point(0,0), point(27,27), color(0,0,0));
				queue q = map.findAvatarPosByIcon(currentPart, CStrToStr(avatarCString[currentPart]+NumToCStr(id)));
				if(q.size() == 0)
					oneImage.putFore(noEntry);
				if(q.size() > 0){
					int idx = map.avatarContent[currentPart][q[0]].avatarID;
					if(factory.album[currentPart].findAvatarID(idx) == -1)
						oneImage.putFore(othEntry);
				}
				if(id == currentIconSelect)
					oneImage.getBrighten();
			}
		}
	}
	int xOffset = (indexInPage % modelInfo.countPerRow) * modelInfo.width;
	int yOffset = (indexInPage / modelInfo.countPerRow) * modelInfo.height;
	drawImage(oneImage, point(230 + xOffset, 40 + yOffset));
}
void ToolAvatar::drawAvatar(){
	image imageAvatar;
	factory.makeImage(basePoint, size(210, 210), imageAvatar);
	if(stage.loaded){
		imageAvatar.putBack(stage.backLayer);
		imageAvatar.putFore(stage.foreLayer);
	}
	drawImage(imageAvatar, point(10, 475));
}
unsigned ToolAvatar::p(void*para){
	((ToolAvatar*)para)->playAvatar();
	return 0U;
}
void ToolAvatar::playAvatar(){
	int localFrame = 0;
	int frame;
	while(true){
		while(playing){
			frame = animation[localFrame];
			factory.changeFrame(frame);
			factory.updateImage();
			drawAvatar();
			Sleep(profile.miniSecPerFrame);
			localFrame ++;
			if(localFrame >= ~animation)
				localFrame = 0;
		}
	}
}
void ToolAvatar::drawImage(const image &img, const point &leftTop){
	int i,j;
	int canw = img.width;
	int canh = img.height;
	CImage cimg;
	cimg.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)cimg.GetBits();
	int pit = cimg.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<canw;i++){
		for(j=0;j<canh;j++){
			*(pst + pit*j + 4*i + 0) = img[j][i].B;
			*(pst + pit*j + 4*i + 1) = img[j][i].G;
			*(pst + pit*j + 4*i + 2) = img[j][i].R;
		}
	}
	cimg.Draw(pDC->m_hDC,leftTop.X, leftTop.Y);
	ReleaseDC(pDC);
}
///////////////////////////////////////////////////////////////
//缩略图生成
///////////////////////////////////////////////////////////////
void ToolAvatar::buildModel(const int &index){
	long widthEnum1[5] = {54, 63, 84, 126, 28};		//750→756
	long heightEnum1[5] = {84, 96, 112, 168, 28};	//675→672
	ToolAvatarModelConfig mc;
	mc.load(profile.getAvatarMapPath());
	for(int sizeMode = 0; sizeMode < 4; sizeMode ++){
		if(currentPart == APART_WEAPON){
			if(character == ACHARACTER_PG && factory.weapon[currentWeaponIndex] == AWEAPON_ROSARY){
				factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), point(0,0), 0);
			}else{
				factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), mc.modelWeaponOffset[character], mc.modelWeaponFrame[character]);
			}
			const WeaponAlbum &wa = factory.weaponAlbum[currentWeaponIndex];
			image im;
			factory.makeWeaponModel(im, currentWeaponIndex, wa.currentSelect);
			makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
				weaponCString[factory.weapon[currentWeaponIndex]] + 
				NumToCStr(wa.content[wa.currentSelect].ID))+".png");
		}else{
			factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), mc.modelAvatarOffset[character][currentPart], mc.modelAvatarFrame[character][currentPart]);
			const AvatarAlbum &aa = factory.album[currentPart];
			image im;
			factory.makeAvatarModel(im, currentPart, aa.currentSelect);
			makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
				avatarCString[currentPart] + 
				NumToCStr(aa.content[aa.currentSelect].ID))+".png");
		}
	}
}
unsigned buildModelPatch1(void*para){
	ToolAvatar*dlg = (ToolAvatar*)para;
	dlg->buildModelPatch();
	dlg->drawModel(-1);
	return 0U;
}
void ToolAvatar::buildModelPatch(){
	long widthEnum1[5] = {54, 63, 84, 126, 28};		//750→756
	long heightEnum1[5] = {84, 96, 112, 168, 28};	//675→672
	bar.show(100);
	ToolAvatarModelConfig mc;
	mc.load(profile.getAvatarMapPath());
	for(int sizeMode = 0; sizeMode < 4; sizeMode ++){
		bar.setInfo(L"生成中", sizeMode * 25);
		if(currentPart == APART_WEAPON){
			if(character == ACHARACTER_PG && factory.weapon[currentWeaponIndex] == AWEAPON_ROSARY){
				factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), point(0,0), 0);
			}else{
				factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), mc.modelWeaponOffset[character], mc.modelWeaponFrame[character] );
			}
			const WeaponAlbum &wa = factory.weaponAlbum[currentWeaponIndex];
			for(int cIndex = 0; cIndex < wa.content.size(); cIndex ++){
				bar.setInfo(L"导入中", sizeMode * 25 + cIndex * 25 / wa.content.size());
				image im;
				factory.makeWeaponModel(im, currentWeaponIndex, cIndex);
				makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
					weaponCString[factory.weapon[currentWeaponIndex]] + 
					NumToCStr(wa.content[cIndex].ID))+".png");
				if(wa.content[cIndex].infoTN.size() > 0){
					im.destory();
					factory.makeWeaponModel(im, currentWeaponIndex, cIndex, true);
					makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
						weaponCString[factory.weapon[currentWeaponIndex]] + 
						NumToCStr(wa.content[cIndex].ID))+"(TN).png");
				}
			}
		}else{
			factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), mc.modelAvatarOffset[character][currentPart], mc.modelAvatarFrame[character][currentPart]);
			const AvatarAlbum &aa = factory.album[currentPart];
			for(int cIndex = 0; cIndex < aa.content.size(); cIndex ++){
				bar.setInfo(L"导入中", sizeMode * 25 + cIndex * 25 / aa.content.size());
				image im;
				factory.makeAvatarModel(im, currentPart, cIndex);
				makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
					avatarCString[currentPart] + 
					NumToCStr(aa.content[cIndex].ID))+".png");
				if(aa.content[cIndex].infoTN.size() > 0){
					im.destory();
					factory.makeAvatarModel(im, currentPart, cIndex, true);
					makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
					avatarCString[currentPart] + 
						NumToCStr(aa.content[cIndex].ID))+"(TN).png");
				}
			}
		}
	}
	bar.hide();
}
unsigned buildIconPatch1(void*para){
	ToolAvatar*dlg = (ToolAvatar*)para;
	dlg->buildIconPatch();
	dlg->drawModel(-1);
	return 0U;
}
void ToolAvatar::buildIconPatch(){
	//根据当前部件决定NPK和IMG名
	str fileStr = NPK_avatarIcon(character);
	NPKobject no;
	bar.show(APART_MAXCOUNT + 6);
	if(no.loadFile(CStrToStr(profile.getAvatarPath()) + fileStr)){
		for(int p = 0;p<APART_MAXCOUNT;p++){
			bar.setInfo(L"生成" + iconCString[p] + L"的图标中……", p);
			str imgPath = IMG_avatarIcon(character, (AvatarPart)p);
			dword pos;
			if(!no.find(imgPath, pos))
				continue;
			IMGobject io;
			no.IMGextract(pos, io);
			for(int id = 0;id<io.indexCount;id++){
				image iconImage;
				io.PICextract(id, iconImage);
				if(iconImage.width > 10/* == 28*/){
					makePNG(iconImage, CStrToStr(profile.getIconPath(character) + iconCString[p] + NumToCStr(id) + L".png"));
				}
			}
		}
		bar.setInfo(L"生成" + iconSpecCString + L"的图标中……", APART_MAXCOUNT);
		str imgPath = IMG_avatarIcon(character, "tong");
		dword pos;
		if(no.find(imgPath, pos)){
			IMGobject io;
			no.IMGextract(pos, io);
			for(int id = 0;id<io.indexCount;id++){
				image iconImage;
				io.PICextract(id, iconImage);
				if(iconImage.width > 10/* == 28*/){
					makePNG(iconImage, CStrToStr(profile.getIconPath(character) + iconCString[APART_BODY] + NumToCStr(108+id) + L".png"));
				}
			}
		}
	}
	std::vector<str> fileList = NPK_weaponIcon(character);
	for(int fileID = 0; fileID < fileList.size(); fileID ++){
		bar.setInfo(L"生成" + iconWeaponCString[character][fileID] + L"的图标中……", APART_MAXCOUNT + fileID);
		NPKobject now;
		if(!now.loadFile(CStrToStr(profile.getAvatarPath()) + fileList[fileID]))
			continue;
		if(now.count == 0)
			continue;
		IMGobject io;
		if(!now.IMGextract(0, io))
			continue;
		for(int id = 0;id<io.indexCount;id++){
			image iconImage;
			io.PICextract(id, iconImage);
			if(iconImage.width > 10/* == 28*/){
				makePNG(iconImage, CStrToStr(profile.getIconPath(character) + iconWeaponCString[character][fileID] + NumToCStr(id) + L".png"));
			}
		}
	}
	bar.setInfo(L"生成完毕……", APART_MAXCOUNT + 5);
	bar.hide();
}

void ToolAvatar::buildPatch(){
	long widthEnum1[5] = {54, 63, 84, 126, 28};		//750→756
	long heightEnum1[5] = {84, 96, 112, 168, 28};	//675→672
	bar.show(2000);
	ToolAvatarModelConfig mc;
	mc.load(profile.getAvatarMapPath());
	for(int sizeMode = 0; sizeMode < 4; sizeMode ++){
		for(int iWeaponTypeIndex = 0;iWeaponTypeIndex < factory.weapon.size(); iWeaponTypeIndex++){
			bar.setInfo(
				L"生成" + weaponCString[factory.weapon[iWeaponTypeIndex]] + 
				L"(尺寸" + NumToCStr(sizeMode + 1) + L")的展示图中……", 
				sizeMode * 250 + 125 * iWeaponTypeIndex / factory.weapon.size());
			if(character == ACHARACTER_PG && factory.weapon[currentWeaponIndex] == AWEAPON_ROSARY){
				factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), point(0,0), 0);
			}else{
				factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), mc.modelWeaponOffset[character], mc.modelWeaponFrame[character]);
			}
			const WeaponAlbum &wa = factory.weaponAlbum[iWeaponTypeIndex];
			for(int cIndex = 0; cIndex < wa.content.size(); cIndex ++){
				image im;
				factory.makeWeaponModel(im, iWeaponTypeIndex, cIndex);
				makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
					weaponCString[factory.weapon[iWeaponTypeIndex]] + 
					NumToCStr(wa.content[cIndex].ID))+".png");
				if(wa.content[cIndex].infoTN.size() > 0){
					im.destory();
					factory.makeWeaponModel(im, iWeaponTypeIndex, cIndex, true);
					makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
						weaponCString[factory.weapon[iWeaponTypeIndex]] + 
						NumToCStr(wa.content[cIndex].ID))+"(TN).png");
				}
			}
		}
		for(int iPart = 0;iPart < APART_MAXCOUNT;iPart++){
			bar.setInfo(
				L"生成" + avatarCString[iPart] + 
				L"(尺寸" + NumToCStr(sizeMode + 1) + L")的展示图中……", 
				sizeMode * 250 + 125 + 125 * iPart / APART_MAXCOUNT);
			factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), mc.modelAvatarOffset[character][iPart], mc.modelAvatarFrame[character][iPart]);
			const AvatarAlbum &aa = factory.album[iPart];
			for(int cIndex = 0; cIndex < aa.content.size(); cIndex ++){
				image im;
				factory.makeAvatarModel(im, (AvatarPart)iPart, cIndex);
				makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
					avatarCString[iPart] + 
					NumToCStr(aa.content[cIndex].ID))+".png");
				if(aa.content[cIndex].infoTN.size() > 0){
					im.destory();
					factory.makeAvatarModel(im, (AvatarPart)iPart, cIndex, true);
					makePNG(im, CStrToStr(profile.getModelPath(sizeMode, character) + 
					avatarCString[iPart] + 
						NumToCStr(aa.content[cIndex].ID))+"(TN).png");
				}
			}
		}
	}
	str fileStr = NPK_avatarIcon(character);
	NPKobject no;
	if(no.loadFile(CStrToStr(profile.getAvatarPath()) + fileStr)){
		for(int p = 0;p<APART_MAXCOUNT;p++){
			bar.setInfo(L"生成" + iconCString[p] + L"的图标中……", 1000 + p * 500 / APART_MAXCOUNT);
			str imgPath = IMG_avatarIcon(character, (AvatarPart)p);
			dword pos;
			if(!no.find(imgPath, pos))
				continue;
			IMGobject io;
			no.IMGextract(pos, io);
			for(int id = 0;id<io.indexCount;id++){
				image iconImage;
				io.PICextract(id, iconImage);
				if(iconImage.width > 10/* == 28*/){
					makePNG(iconImage, CStrToStr(profile.getIconPath(character) + iconCString[p] + NumToCStr(id) + L".png"));
				}
			}
		}
		bar.setInfo(L"生成" + iconSpecCString + L"的图标中……", 1500);
		str imgPath = IMG_avatarIcon(character, "tong");
		dword pos;
		if(no.find(imgPath, pos)){
			IMGobject io;
			no.IMGextract(pos, io);
			for(int id = 0;id<io.indexCount;id++){
				image iconImage;
				io.PICextract(id, iconImage);
				if(iconImage.width > 10/* == 28*/){
					makePNG(iconImage, CStrToStr(profile.getIconPath(character) + iconCString[APART_BODY] + NumToCStr(108+id) + L".png"));
				}
			}
		}
	}
	std::vector<str> fileList = NPK_weaponIcon(character);
	for(int fileID = 0; fileID < fileList.size(); fileID ++){
		bar.setInfo(L"生成" + iconWeaponCString[character][fileID] + L"的图标中……", 1500 + fileID * 500 / fileList.size());
		NPKobject now;
		if(!now.loadFile(CStrToStr(profile.getAvatarPath()) + fileList[fileID]))
			continue;
		if(now.count == 0)
			continue;
		IMGobject io;
		if(!now.IMGextract(0, io))
			continue;
		for(int id = 0;id<io.indexCount;id++){
			image iconImage;
			io.PICextract(id, iconImage);
			if(iconImage.width > 10/* == 28*/){
				makePNG(iconImage, CStrToStr(profile.getIconPath(character) + iconWeaponCString[character][fileID] + NumToCStr(id) + L".png"));
			}
		}
	}
	bar.hide();
	MessageBox(L"生成完毕。");
}
///////////////////////////////////////////////////////////////
//控件函数
///////////////////////////////////////////////////////////////
BOOL ToolAvatar::getMouseClicked(int &type, long &checkSelected){
	CPoint myPoint;
    GetCursorPos(&myPoint); //鼠标位置
	ScreenToClient(&myPoint);
	long x = myPoint.x;
	long y = myPoint.y;
	if(x >= 10 && x < 70 && y >= 10 && y < 70){
		type = 0;
		checkSelected = 0;
		return TRUE;
	}
	if(x >= 70 && x < 220 && y >= 10 && y < 70){
		type = 1;
		checkSelected = (y - 10) / 30 * 5 + (x - 70) / 30;
		return TRUE;
	}
	if(x >= 230 && x < 986 && y >= 40 && y < 712){
		type = 2;
		checkSelected = (y - 40) / modelInfo.height * modelInfo.countPerRow + (x - 230) / modelInfo.width;
		return TRUE;
	}
	type = -1;
	checkSelected = -1;
	return FALSE;
}

void ToolAvatar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 点下鼠标左键
	int type;
	long checkSelected;
	getMouseClicked(type, checkSelected);
	if(loading)
		return;
	switch(type){
	case 0:
		if(true){
			ToolAvatarCharacterSelection mySelection;
			if(IDOK == mySelection.DoModal()){
				chooseCharacter((AvatarCharacter)mySelection.output);
			}
		}
		break;
	case 1:
		if(checkSelected == 9){
			if(currentPart == APART_WEAPON)
				break;
			cbWeaponType->EnableWindow(true);
			currentPart = APART_WEAPON;
			cbWeaponType->SetCurSel(currentWeaponIndex);
			updateList();
			if(isIconic){
				currentPage = 0;
				maxPage = 2;
			}else{
				currentPage = factory.weaponAlbum[currentWeaponIndex].currentSelect / modelInfo.countPerPage;
				maxPage = factory.weaponAlbum[currentWeaponIndex].content.size() / modelInfo.countPerPage + 1;
			}
			showAvatarInfo();
			updatePageInfo();
			drawModel(-1);
		}else{
			if(currentPart == checkSelected)
				break;
			cbWeaponType->EnableWindow(false);
			currentPart = (AvatarPart)checkSelected;
			updateList();
			if(isIconic){
				currentPage = 0;
				maxPage = 2;
			}else{
				currentPage = factory.album[currentPart].currentSelect / modelInfo.countPerPage;
				maxPage = factory.album[currentPart].content.size() / modelInfo.countPerPage + 1;
			}
			showAvatarInfo();
			updatePageInfo();
			drawModel(-1);
		}
		break;
	case 2:
		if(!isIconic){
			if(currentPart == APART_WEAPON){
				int clickIndex = checkSelected + currentPage * modelInfo.countPerPage;
				if(clickIndex < factory.weaponAlbum[currentWeaponIndex].content.size()){
					PLAYING_PAUSE;
					factory.changeWeapon(clickIndex);
					lbContent->SetCurSel(clickIndex+1); 
					showAvatarInfo();
					updateSuitInfo();
					drawModel(checkSelected);
					drawModel(lastSelected);
					PLAYING_CONTINUE;
				}
			}else{
				int clickIndex = checkSelected + currentPage * modelInfo.countPerPage;
				if(clickIndex < factory.album[currentPart].content.size()){
					PLAYING_PAUSE;
					factory.changeAvatar(currentPart, clickIndex);
					lbContent->SetCurSel(clickIndex+1); 
					showAvatarInfo();
					updateSuitInfo();
					drawModel(checkSelected);
					drawModel(lastSelected);
					PLAYING_CONTINUE;
				}
			}
		}else{
			//图标模式
			if(currentPart == APART_WEAPON){
				int clickIndex = checkSelected + currentPage * modelInfo.countPerPage;
				if(iconEnabled[clickIndex]){
					PLAYING_PAUSE;
					currentIconSelect = clickIndex;
					queue q = map.findWeaponPosByIcon(map.weapon[currentWeaponIndex], CStrToStr(weaponIconClassified[character][currentWeaponIndex]+NumToCStr(clickIndex)));
					if(q.size() == 0){
						factory.changeWeapon(-1);
						lbContent->SetCurSel(0); 
					}else{
						long newID = factory.weaponAlbum[currentWeaponIndex].findWeaponID(map.weaponContent[currentWeaponIndex][q[0]].avatarID);
						factory.changeWeapon(newID);
						lbContent->SetCurSel(newID+1);
					}
					showAvatarInfo();
					updateSuitInfo();
					drawModel(checkSelected);
					drawModel(lastSelected);
					PLAYING_CONTINUE;
				}
			}else{
				int clickIndex = checkSelected + currentPage * modelInfo.countPerPage;
				if(iconEnabled[clickIndex]){
					PLAYING_PAUSE;
					currentIconSelect = clickIndex;
					queue q = map.findAvatarPosByIcon(currentPart, CStrToStr(avatarCString[currentPart]+NumToCStr(clickIndex)));
					if(q.size() == 0){
						factory.changeAvatar(currentPart, -1);
						lbContent->SetCurSel(0); 
					}else{
						long newID = factory.album[currentPart].findAvatarID(map.avatarContent[currentPart][q[0]].avatarID);
						factory.changeAvatar(currentPart, newID);
						lbContent->SetCurSel(newID+1);
					}
					showAvatarInfo();
					updateSuitInfo();
					drawModel(checkSelected);
					drawModel(lastSelected);
					PLAYING_CONTINUE;
				}
			}
		}
		lastSelected = checkSelected;
		break;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void ToolAvatar::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnLButtonDown(nFlags, point);
	if(loading)
		return;
	int type;
	long checkSelected;
	getMouseClicked(type, checkSelected);
	switch(type){
	case 2:
		lastSelected = checkSelected;
		if(!isIconic){
			bool doInvoke = false;
			if(currentPart == APART_WEAPON){
				int clickIndex = checkSelected + currentPage * modelInfo.countPerPage;
				if(clickIndex < factory.weaponAlbum[currentWeaponIndex].content.size()){
					doInvoke = true;
				}
			}else{
				int clickIndex = checkSelected + currentPage * modelInfo.countPerPage;
				if(clickIndex < factory.album[currentPart].content.size()){
					doInvoke = true;
				}
			}
			if(doInvoke){
				CMenu menu, *pPopup;  
				menu.LoadMenu(IDR_MENU_AVATAR);  
				pPopup = menu.GetSubMenu(0);  
				CPoint myPoint;  
				ClientToScreen(&myPoint);  
				GetCursorPos(&myPoint); //鼠标位置  
				pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
			}
		}else{
			//图标模式
		}
		break;
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

void ToolAvatar::OnCbnSelchangeComboWeapon(){
	// TODO: 在此添加控件通知处理程序代码
	if(loading)
		return;
	PLAYING_PAUSE;
	currentWeaponIndex = cbWeaponType->GetCurSel();
	factory.changeWeaponType(currentWeaponIndex);
	updateList();
	if(isIconic){
		currentPage = 0;
		maxPage = 2;
	}else{
		currentPage = factory.weaponAlbum[currentWeaponIndex].currentSelect / modelInfo.countPerPage;
		maxPage = factory.weaponAlbum[currentWeaponIndex].content.size() / modelInfo.countPerPage + 1;
	}
	updatePageInfo();
	updateSuitInfo();
	showAvatarInfo();
	drawModel(-1);
	PLAYING_CONTINUE;
}


void ToolAvatar::OnLbnSelchangeListContent(){
	// TODO: 在此添加控件通知处理程序代码
	if(loading)
		return;
	PLAYING_PAUSE;
	if(currentPart == APART_WEAPON){
		factory.changeWeapon(lbContent->GetCurSel() - 1);
		if(!isIconic){
			int selected = factory.weaponAlbum[currentWeaponIndex].currentSelect - modelInfo.countPerPage * currentPage;
			if(lastSelected >= 0 && lastSelected <  modelInfo.countPerPage)
				drawModel(lastSelected);
			if(selected >= 0 && selected <  modelInfo.countPerPage)
				drawModel(selected);
			lastSelected = selected;
		}
	}else{
		factory.changeAvatar(currentPart, lbContent->GetCurSel() - 1);
		if(!isIconic){
			int selected = factory.album[currentPart].currentSelect - modelInfo.countPerPage * currentPage;
			if(lastSelected >= 0 && lastSelected <  modelInfo.countPerPage)
				drawModel(lastSelected);
			if(selected >= 0 && selected <  modelInfo.countPerPage)
				drawModel(selected);
			lastSelected = selected;
		}
		
	};
	updateSuitInfo();
	showAvatarInfo();
	PLAYING_CONTINUE;
}


void ToolAvatar::OnBnClickedButtonPframe()
{
	// TODO: 在此添加控件通知处理程序代码
	if(loading)
		return;
	if(playing)
		return;
	if(currentFrame > 0 && !playing){
		currentFrame--;
		GET_CTRL(CButton, IDC_BUTTON_AFRAME)->SetWindowText(NumToCStr(currentFrame));
		factory.changeFrame(currentFrame);
		factory.updateImage();
		drawAvatar();
	}
}


void ToolAvatar::OnBnClickedButtonNframe()
{
	// TODO: 在此添加控件通知处理程序代码
	if(loading)
		return;
	if(playing)
		return;
	if(currentFrame < maxFrame - 1 && !playing){
		currentFrame++;
		GET_CTRL(CButton, IDC_BUTTON_AFRAME)->SetWindowText(NumToCStr(currentFrame));
		factory.changeFrame(currentFrame);
		factory.updateImage();
		drawAvatar();
	}
}


void ToolAvatar::OnBnClickedButtonAframe() {
	// TODO:  在此添加控件通知处理程序代码
	if(loading)
		return;
	if(playing)
		return;
	if(maxFrame < 0)
		return;
	TinyFrame dlg;
	dlg.cur = currentFrame;
	dlg.min = 0;
	dlg.max = maxFrame - 1;
	if(IDOK == dlg.DoModal()) {
		currentFrame = dlg.output;
		GET_CTRL(CButton, IDC_BUTTON_AFRAME)->SetWindowText(NumToCStr(currentFrame));
		factory.changeFrame(currentFrame);
		factory.updateImage();
		drawAvatar();
	}
}

void ToolAvatar::OnBnClickedButtonTool1()
{
	// TODO: 更改展示图尺寸
	if(loading)
		return;
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_AVATAR);  
    pPopup = menu.GetSubMenu(1);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}


void ToolAvatar::OnBnClickedButtonTool2()
{
	// TODO: 更改TN开关
	if(loading)
		return;
	TNmode = !TNmode;
	factory.changeTN(TNmode);
	bTool[1]->SetBitmap(TNmode ? m_buttonPicX[1] : m_buttonPic[1]);
	if(!isIconic)
		drawModel(-1);
}


void ToolAvatar::OnBnClickedButtonTool3()
{
	// TODO: 切换展示图模式
	if(loading)
		return;
	if(!isIconic)
		return;
	bTool[2]->SetBitmap(m_buttonPicX[2]);
	bTool[3]->SetBitmap(m_buttonPic[3]);
	isIconic = false;
	initalModel(oldSizeMode);
	if(currentPart == APART_WEAPON){
		currentPage = factory.weaponAlbum[currentWeaponIndex].currentSelect / modelInfo.countPerPage;
		maxPage = factory.weaponAlbum[currentWeaponIndex].content.size() / modelInfo.countPerPage + 1;
	}else{
		currentPage = factory.album[currentPart].currentSelect / modelInfo.countPerPage;
		maxPage = factory.album[currentPart].content.size() / modelInfo.countPerPage + 1;
	}
	updatePageInfo();
	drawModel(-1);
}


void ToolAvatar::OnBnClickedButtonTool4()
{
	// TODO: 切换图标模式
	if(loading)
		return;
	if(isIconic)
		return;
	bTool[2]->SetBitmap(m_buttonPic[2]);
	bTool[3]->SetBitmap(m_buttonPicX[3]);
	isIconic = true;
	oldSizeMode = modelInfo.sizeMode;
	initalModel(4);
	currentPage = 0;
	maxPage = 2;
	updatePageInfo();
	drawModel(-1);
}


void ToolAvatar::OnBnClickedButtonTool5()
{
	// TODO: 脱下装扮
	if(loading)
		return;
	PLAYING_PAUSE;
	if(currentPart == APART_WEAPON){
		factory.changeWeapon(-1);
	}else{
		factory.changeAvatar(currentPart, -1);
	}
	updateSuitInfo();
	PLAYING_CONTINUE;
}


void ToolAvatar::OnBnClickedButtonTool6()
{
	// TODO: 更新缩略图文件
	if(loading)
		return;
	if(isIconic){
		if(IDYES == MessageBox(L"将更新"+careerName[character] + L"的装扮图标，确定喵？", L"提示喵", MB_YESNO)){
			AfxBeginThread(buildIconPatch1, this);
		}
	}else{
		CString pstr;
		if(currentPart == APART_WEAPON){
			pstr = weaponCString[factory.weapon[currentWeaponIndex]];
		}else{
			pstr = avatarCString[currentPart];
		}
		if(IDYES == MessageBox(L"将更新"+careerName[character] + pstr + L"的展示图，确定喵？", L"提示喵", MB_YESNO)){
			AfxBeginThread(buildModelPatch1, this);
		}
	}
}


void ToolAvatar::OnBnClickedButtonTool7()
{
	// TODO: 上翻页
	if(loading)
		return;
	if(currentPage > 0){
		currentPage --;
		drawModel(-1);
		updatePageInfo();
	}
}


void ToolAvatar::OnBnClickedButtonTool8()
{
	// TODO: 在此添加控件通知处理程序代码
	if(loading)
		return;
	if(currentPage <maxPage - 1){
		currentPage ++;
		drawModel(-1);
		updatePageInfo();
	}
}


void ToolAvatar::OnMenuAvatarsize1()
{
	// TODO: 在此添加命令处理程序代码
	int newSizeMode = 0;
	if(isIconic || modelInfo.sizeMode == newSizeMode)
		return;
	initalModel(newSizeMode);
	if(currentPart == APART_WEAPON){
		currentPage = factory.weaponAlbum[currentWeaponIndex].currentSelect / modelInfo.countPerPage;
		maxPage = factory.weaponAlbum[currentWeaponIndex].content.size() / modelInfo.countPerPage + 1;
	}else{
		currentPage = factory.album[currentPart].currentSelect / modelInfo.countPerPage;
		maxPage = factory.album[currentPart].content.size() / modelInfo.countPerPage + 1;
	}
	updatePageInfo();
	drawModel(-1);
}


void ToolAvatar::OnMenuAvatarsize2()
{
	// TODO: 在此添加命令处理程序代码
	int newSizeMode = 1;
	if(isIconic || modelInfo.sizeMode == newSizeMode)
		return;
	initalModel(newSizeMode);
	if(currentPart == APART_WEAPON){
		currentPage = factory.weaponAlbum[currentWeaponIndex].currentSelect / modelInfo.countPerPage;
		maxPage = factory.weaponAlbum[currentWeaponIndex].content.size() / modelInfo.countPerPage + 1;
	}else{
		currentPage = factory.album[currentPart].currentSelect / modelInfo.countPerPage;
		maxPage = factory.album[currentPart].content.size() / modelInfo.countPerPage + 1;
	}
	updatePageInfo();
	drawModel(-1);
}


void ToolAvatar::OnMenuAvatarsize3()
{
	// TODO: 在此添加命令处理程序代码
	int newSizeMode = 2;
	if(isIconic || modelInfo.sizeMode == newSizeMode)
		return;
	initalModel(newSizeMode);
	if(currentPart == APART_WEAPON){
		currentPage = factory.weaponAlbum[currentWeaponIndex].currentSelect / modelInfo.countPerPage;
		maxPage = factory.weaponAlbum[currentWeaponIndex].content.size() / modelInfo.countPerPage + 1;
	}else{
		currentPage = factory.album[currentPart].currentSelect / modelInfo.countPerPage;
		maxPage = factory.album[currentPart].content.size() / modelInfo.countPerPage + 1;
	}
	updatePageInfo();
	drawModel(-1);
}


void ToolAvatar::OnMenuAvatarsize4()
{
	// TODO: 在此添加命令处理程序代码
	int newSizeMode = 3;
	if(isIconic || modelInfo.sizeMode == newSizeMode)
		return;
	initalModel(newSizeMode);
	if(currentPart == APART_WEAPON){
		currentPage = factory.weaponAlbum[currentWeaponIndex].currentSelect / modelInfo.countPerPage;
		maxPage = factory.weaponAlbum[currentWeaponIndex].content.size() / modelInfo.countPerPage + 1;
	}else{
		currentPage = factory.album[currentPart].currentSelect / modelInfo.countPerPage;
		maxPage = factory.album[currentPart].content.size() / modelInfo.countPerPage + 1;
	}
	updatePageInfo();
	drawModel(-1);
}


void ToolAvatar::OnBnClickedButtonTool10()
{
	// TODO: NPK功能菜单
	if(loading)
		return;
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_AVATAR);  
    pPopup = menu.GetSubMenu(2);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}


void ToolAvatar::OnBnClickedButtonTool9()
{
	// TODO: 套装浏览
	if(loading)
		return;
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_AVATAR);  
    pPopup = menu.GetSubMenu(3);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}


void ToolAvatar::OnBnClickedButtonTool11()
{
	// TODO: 本地化功能菜单
	if(loading)
		return;
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_AVATAR);  
    pPopup = menu.GetSubMenu(4);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}

unsigned localize1(void*para){
	ToolAvatar*dlg = (ToolAvatar*)para;
	dlg->buildPatch();
	dlg->drawModel(-1);
	return 0U;
}
void ToolAvatar::OnMenuLocalizeOne(){
	// TODO: 在此添加命令处理程序代码
	if(IDYES == MessageBox(L"即将更新本职业所有装扮的展示图和图标，这要耗费几分钟的时间，确定吗？", L"提示喵", MB_YESNO)){
		AfxBeginThread(localize1, this);
	}
}


void ToolAvatar::OnMenuLocalizeAll(){
	// TODO: 在此添加命令处理程序代码
	ToolAvatarLocalizer dlg;
	dlg.DoModal();
}


void ToolAvatar::OnMenuLocalizeSet(){
	// TODO: 在此添加命令处理程序代码
	ShellExecute(0, L"open", profile.getAvatarMapPath() +  L"模型生成设置.txt", 0, 0, SW_SHOWNORMAL);
}


void ToolAvatar::OnMenuAvatarFunToEX(){
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
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
	
	dlg->fileNPKname = "mySuit.NPK";
	dlg->IMGsaveAlert = FALSE;
	factory.makeNPK(dlg->no);
	MessageBox(L"已导入到EX里了！",L"提示喵");
	dlg->updateIMGlist();
	dlg->updateInfo();
}

void ToolAvatar::buildMixedIMG(IMGobject &io){
	NPKobject mixNo;
	factory.makeNPK(mixNo);
	IMGobject *ioList = new IMGobject[mixNo.count];
	IMGobject newIO;
	newIO.create(V2);
	int maxFrameCount = 0;
	//取最大帧数
	for(int i=0;i<mixNo.count;i++){
		mixNo.IMGextract(i, ioList[i]);
		if(ioList[i].indexCount> maxFrameCount)
			maxFrameCount = ioList[i].indexCount;
	}
	bar.show(400);
	for(long frame=0;frame<maxFrameCount;frame++){
		bar.setInfo(L"拼合第"+NumToCStr(frame)+L"帧中……", 100 * frame / maxFrameCount);
		image mPic, mPicTemp;
		stream s;
		PICinfo pi;
		point ptLT, ptRB;
		std::vector<int> mLeft, mTop, mRight, mBottom;
		//计算点集的边界
		for(int i=0;i<mixNo.count;i++){
			long newFrame = ioList[i].linkFind(frame);
			if(ioList[i].PICgetInfo(newFrame, pi)){
				CHECK_VALID_CONTINUE(pi.picSize.area() > 1);
				mLeft.push_back(pi.basePt.X);
				mTop.push_back(pi.basePt.Y);
				mRight.push_back(pi.basePt.X+pi.picSize.W-1);
				mBottom.push_back(pi.basePt.Y+pi.picSize.H-1);
			}
		}
		//所有帧都是空的
		if(mLeft.size() == 0){
			pi.basePt = point(0,0);
			pi.comp = COMP_NONE;
			pi.format = ARGB4444;
			pi.dataSize = 2;
			pi.picSize = size(1,1);
			pi.frmSize = size(1,1);
			s.allocate(2);
			s.pushByte(0);
			s.pushByte(0);
			newIO.PICpush(pi, s);
			s.release();
			continue;
		}
		//计算帧的边界
		int tLeft, tTop, tRight, tBottom;
		for(int i=0;i<mLeft.size();i++){
			if(i == 0){
				tLeft = mLeft[0];
				tTop = mTop[0];
				tRight = mRight[0];
				tBottom = mBottom[0];
				continue;
			}
			if(mLeft[i]<tLeft)
				tLeft = mLeft[i];
			if(mRight[i]>tRight)
				tRight = mRight[i];
			if(mTop[i]<tTop)
				tTop = mTop[i];
			if(mBottom[i]>tBottom)
				tBottom = mBottom[i];
		}
		ptLT = point(tLeft, tTop);
		ptRB = point(tRight, tBottom);
		mPic.create(tBottom-tTop+1, tRight-tLeft+1);
		for(int i=0;i<mixNo.count;i++){
			long newFrame = ioList[i].linkFind(frame);
			if(ioList[i].PICgetInfo(newFrame, pi)){
				CHECK_VALID_CONTINUE(pi.picSize.area() > 1);
				ioList[i].PICextract(newFrame, mPicTemp);
				if(mixNo.entry[i].comment.find("f.") != str::npos || mixNo.entry[i].comment.find("f1.") != str::npos){
					mPicTemp.loseBlack(3);
				}
				mPic.putBack(mPicTemp, LAY, pi.basePt - ptLT);
				mPicTemp.destory();
			}
		}
		newIO.PICpreprocess(mPic, s, pi);
		pi.basePt = ptLT;
		newIO.PICpush(pi, s);
		mPic.destory();
		s.release();
	}
	///////////////////////////////////////
#ifdef MAKE_ONE_STEP_V4
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	for(long frame = 0;frame<newIO.indexCount;frame ++){
		bar.setInfo(L"构建色表中……", 100 + 50 * frame / newIO.indexCount);
		image mat;
		if(!newIO.PICextract(frame, mat)){
			continue;
		}
		for(int i = 0;i<mat.getElemCount();i++){
			color clr = mat.getElem(i);
			long clrPos = pal.findColor(clr,0);
			if(clrPos == -1){
				pal[0].push_back(clr);
				clrCount.push_back(1);
			}else{
				clrCount[clrPos] ++;
			}
		}
		mat.destory();
	}
	clrList = pal[0];
	long finalColorCount = MIN(0xFF, pal.getColorCount(0));
	colorList finalColorList;
	for(int i = 0;i<finalColorCount; i++){
		bar.setInfo(L"着色中……", 150 + 50 * i / (finalColorCount + 1));
		long maxCount = 0;
		long maxID = -1;
		for(int j = 0;j<clrCount.size();j++){
			if(clrCount[j] > maxCount){
				maxCount =clrCount[j];
				maxID = j;
			}
		}
		finalColorList.push_back(clrList[maxID]);
		clrList.erase(clrList.begin() + maxID);
		clrCount.erase(clrCount.begin() + maxID);
	}
	clrList = KoishiImageTool::nearbySort(finalColorList);
	std::vector<IMGobject> outIOList;
	newIO.convertToV4(outIOList, clrList, false);
	io = outIOList[0];
#else
	io = newIO;
#endif
}
unsigned buildGIF(void*para){
	ToolAvatar* dlg = (ToolAvatar*)para;
	IMGobject picIO;
	dlg->buildMixedIMG(picIO);
	std::vector<long> frameList;
	if(!dlg->playing)
		dlg->setAnimation(10);
	for(int i = 0;i<~dlg->animation;i++)
		frameList.push_back(dlg->animation[i]);
	std::vector<image> matList;
	long imgX1, imgX2, imgY1, imgY2;
	picIO.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
	for(int i=0;i<frameList.size();i++){
		dlg->bar.setInfo(L"正在处理第"+NumToCStr(frameList[i])+L"帧喵……",i);
		image mOrigin, mExpanded;
		PICinfo pInfo;
		picIO.PICgetInfo(picIO.linkFind(frameList[i]), pInfo); 
		picIO.PICextract(picIO.linkFind(frameList[i]), mOrigin, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
		int x1old = pInfo.basePt.X;
		int y1old = pInfo.basePt.Y;
		int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
		int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
		int x1new = imgX1;
		int y1new = imgY1;
		int x2new = imgX2;
		int y2new = imgY2;
		int x1 = min(x1old,x1new);
		int x2 = max(x2old,x2new);
		int y1 = min(y1old,y1new);
		int y2 = max(y2old,y2new);
		mExpanded.create(y2-y1+1,x2-x1+1);
		mExpanded.putFore(mOrigin, LAY, point(x1old-x1, y1old-y1));
		mExpanded.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
		matList.push_back(mExpanded);
		mOrigin.destory();
		mExpanded.destory();
	}
	dlg->bar.setInfo(L"正在生成GIF喵……",frameList.size());
	KoishiImageTool::GIF::GIFobject go;
	go.input(matList, picIO.paletteData[0], dlg->profile.miniSecPerFrame);
	CString fileName = dlg->profile.getAvatarMapPath()+careerName[dlg->character]+L"套装"+CTime::GetTickCount().Format(L"%H%M%S")+L".GIF";
	go.makeFile(CStrToStr(fileName));
	dlg->MessageBox(L"已保存为"+fileName+L"了喵。",L"提示喵");
	dlg->bar.hide();
	return 0U;
}
unsigned buildNPK1(void*para){
	ToolAvatar* dlg = (ToolAvatar*)para;
	CExRabbitDlg *parent = (CExRabbitDlg*)(dlg->context);
	IMGobject picIO, emptyIO;
	dlg->buildMixedIMG(picIO);
	IMGobject::makeEmpty(emptyIO, picIO.indexCount);
	parent->no.release();
	parent->no.create();
	parent->no.IMGpush(picIO, "meow/本体图层.img");
	if(dlg->factory.album[APART_COAT].layerNameList.size() == 0) {
		dlg->MessageBox(L"制作错误喵，必须制定一个上衣部件作为本体喵！", L"提示喵");
		return 0U;
	}
	parent->no.pushLink(0, dlg->factory.album[APART_COAT].layerNameList[0]);
	parent->no.IMGpush(emptyIO, "meow/隐藏图层.img");
	for(int iPart = 0;iPart<APART_MAXCOUNT;iPart++){
		dlg->bar.setInfo(L"建立空图层中……", 200 + 200 * iPart / APART_MAXCOUNT);
		for(int t = 0;t<dlg->factory.album[iPart].layerNameList.size();t++){
			if(iPart == APART_BODY || iPart == APART_COAT && t == 0)
				continue;
			parent->no.pushLink(2, dlg->factory.album[iPart].layerNameList[t]);
		}
	}
	dlg->bar.hide();
	dlg->MessageBox(L"制作完成了喵，请在EX中查看喵！",L"提示喵");
	parent->updateIMGlist();
	parent->updateInfo();
	return 0U;
}
unsigned buildNPK2(void*para){
	ToolAvatar* dlg = (ToolAvatar*)para;
	CExRabbitDlg *parent = (CExRabbitDlg*)(dlg->context);
	IMGobject picIO, emptyIO;
	dlg->buildMixedIMG(picIO);
	IMGobject::makeEmpty(emptyIO, picIO.indexCount);
	parent->no.release();
	parent->no.create();
	parent->no.IMGpush(picIO, "meow/本体图层.img");
	parent->no.IMGpush(emptyIO, "meow/隐藏图层.img");
	for(int iPart = 0;iPart<APART_MAXCOUNT;iPart++){
		dlg->bar.setInfo(L"建立空图层中……", 200 + 200 * iPart / APART_MAXCOUNT);
		for(int t = 0;t<dlg->factory.album[iPart].layerNameList.size();t++){
			if(iPart == APART_BODY)
				continue;
			parent->no.pushLink(1, dlg->factory.album[iPart].layerNameList[t]);
		}
	}
	dlg->bar.hide();
	dlg->MessageBox(L"制作完成了喵，请在EX中查看喵！",L"提示喵");
	parent->updateIMGlist();
	parent->updateInfo();
	return 0U;
}
unsigned buildNPK3(void*para){
	ToolAvatar* dlg = (ToolAvatar*)para;
	CExRabbitDlg *parent = (CExRabbitDlg*)(dlg->context);
	IMGobject picIO, emptyIO;
	dlg->buildMixedIMG(picIO);
	IMGobject::makeEmpty(emptyIO, picIO.indexCount);
	parent->no.release();
	parent->no.create();
	parent->no.IMGpush(picIO, "meow/本体图层.img");
	for(int t = 0;t<dlg->factory.album[APART_BODY].source.count;t++){
		IMGobject io;
		parent->no.pushLink(0, dlg->factory.album[APART_BODY].source.entry[t].comment);
	}
	int sl = parent->no.count;
	parent->no.IMGpush(emptyIO, "meow/隐藏图层.img");
	for(int iPart = 0;iPart<APART_MAXCOUNT;iPart++){
		dlg->bar.setInfo(L"建立"+avatarCString[iPart]+L"空图层中……", 200 + 200 * iPart / APART_MAXCOUNT);
		if(iPart == APART_BODY)
			continue;
		for(int t = 0;t<dlg->factory.album[iPart].source.count;t++){
			parent->no.pushLink(sl, dlg->factory.album[iPart].source.entry[t].comment);
		}
	}
	dlg->MessageBox(L"制作完成了喵，请在EX中查看喵！",L"提示喵");
	dlg->bar.hide();
	parent->updateIMGlist();
	parent->updateInfo();
	return 0U;
}
void ToolAvatar::OnMenuAvatarFunMakeNPK(){
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
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
	dlg->fileNPKname = "mySuit.NPK";
	dlg->IMGsaveAlert = FALSE;
	AfxBeginThread(buildNPK1, this);
}


void ToolAvatar::OnMenuAvatarFunMakeAntiNPK(){
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
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
	dlg->fileNPKname = "mySuit.NPK";
	dlg->IMGsaveAlert = FALSE;
	AfxBeginThread(buildNPK2, this);
}


void ToolAvatar::OnMenuAvatarFunMakeAllIn1NPK(){
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
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
	dlg->fileNPKname = "mySuit.NPK";
	dlg->IMGsaveAlert = false;
	AfxBeginThread(buildNPK3, this);
}

ToolAvatar::_ani::_ani(){
	frameLength = 0;
	memset(frame, 0, sizeof(long)*255);
	frame[0] = -1;
}
ToolAvatar::_ani  &ToolAvatar::_ani::operator>(long newFrame){
	frame[frameLength++] = newFrame;
	frame[frameLength] = -1;
	return *this;
}
ToolAvatar::_ani  &ToolAvatar::_ani::operator>=(long totalFrame){
	frameLength = totalFrame;
	for(int i = 0;i<totalFrame;i++){
		frame[i] = i;
	}
	frame[frameLength] = -1;
	return *this;
}
long &ToolAvatar::_ani::operator[](long ID){
	return frame[ID];
}
long ToolAvatar::_ani::operator~() const{
	return frameLength;
}
void ToolAvatar::setAnimation(const long &aniID){
#define SET_ANIMATION(__ac, __ai, __ani) if(__ac == character && aniID == __ai){animation = (_ani()>__ani);}
	SET_ANIMATION(ACHARACTER_SM, ANI_NORMAL,	176 > 176 > 176 > 177 > 178);
	SET_ANIMATION(ACHARACTER_SM, ANI_PREPARE,	90 > 91 > 92 > 93 > 94 > 95);
	SET_ANIMATION(ACHARACTER_SM, ANI_WALK,		180 > 181 > 182 > 183 > 184 > 185 > 186 > 187);
	SET_ANIMATION(ACHARACTER_SM, ANI_DASH,		105 > 106 > 107 > 108 > 109 > 110 > 111 > 112);
	SET_ANIMATION(ACHARACTER_SM, ANI_ATTACK,	0 > 2 > 3 > 4 > 5 > 6 > 7 > 8 > 8 > 8 > 8);
	SET_ANIMATION(ACHARACTER_SM, ANI_ZATTACK,	33 > 34 > 35 > 36 > 37 > 38 > 39 > 39 > 39 > 39);
	SET_ANIMATION(ACHARACTER_SM, ANI_CAST,		75 > 76 > 77 > 78 > 79 > 80 > 81 > 82 > 82 > 82);
	SET_ANIMATION(ACHARACTER_SM, ANI_HIT,		96 > 96 > 96 > 99 > 99 > 99);
	SET_ANIMATION(ACHARACTER_SM, ANI_FALL,		101 > 102 > 102 > 102 > 102 > 102 > 102 > 102);
	SET_ANIMATION(ACHARACTER_SM, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_SG, ANI_NORMAL,	0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8);
	SET_ANIMATION(ACHARACTER_SG, ANI_PREPARE,	9 > 10 > 11 > 12);
	SET_ANIMATION(ACHARACTER_SG, ANI_WALK,		13 > 14 > 15 > 16 > 17 > 18 > 19 > 20 > 21 > 22);
	SET_ANIMATION(ACHARACTER_SG, ANI_DASH,		151 > 152 > 153 > 154 > 155 > 156 > 157 > 158);
	SET_ANIMATION(ACHARACTER_SG, ANI_ATTACK,	48 > 49 > 50 > 51 > 52);
	SET_ANIMATION(ACHARACTER_SG, ANI_ZATTACK,	48 > 49 > 50 > 51 > 52);
	SET_ANIMATION(ACHARACTER_SG, ANI_CAST,		121 > 122 > 123 > 124 > 125 > 126 > 127 > 128 > 129 > 130 > 131 > 132 > 133 > 134 > 135 > 136);
	SET_ANIMATION(ACHARACTER_SG, ANI_HIT,		139 > 140);
	SET_ANIMATION(ACHARACTER_SG, ANI_FALL,		141 > 142 > 143);
	SET_ANIMATION(ACHARACTER_SG, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_GN, ANI_NORMAL,	0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8 > 9 > 10 > 11 > 12);
	SET_ANIMATION(ACHARACTER_GN, ANI_PREPARE,	13 > 14 > 15 > 16 > 17 > 18 > 19 > 20 > 21 > 22);
	SET_ANIMATION(ACHARACTER_GN, ANI_WALK,		55 > 56 > 57 > 58 > 59 > 60 > 61 > 62);
	SET_ANIMATION(ACHARACTER_GN, ANI_DASH,		103 > 104 > 105 > 106 > 107 > 108 > 109 > 110);
	SET_ANIMATION(ACHARACTER_GN, ANI_ATTACK,	25 > 26 > 27 > 28 > 29 > 30 > 31 > 32 > 33 > 34 > 35 > 36 > 37 > 38);
	SET_ANIMATION(ACHARACTER_GN, ANI_ZATTACK,	155 > 156 > 157 > 158);
	SET_ANIMATION(ACHARACTER_GN, ANI_CAST,		193 > 194 > 195 > 196 > 197);
	SET_ANIMATION(ACHARACTER_GN, ANI_HIT,		121 > 122 > 123 > 124);
	SET_ANIMATION(ACHARACTER_GN, ANI_FALL,		125 > 126 > 127);
	SET_ANIMATION(ACHARACTER_GN, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_GG, ANI_NORMAL,	0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8 > 9);
	SET_ANIMATION(ACHARACTER_GG, ANI_PREPARE,	14 > 15 > 16 > 17 > 18 > 19 > 20);
	SET_ANIMATION(ACHARACTER_GG, ANI_WALK,		68 > 69 > 70 > 71 > 72 > 73 > 74 > 75);
	SET_ANIMATION(ACHARACTER_GG, ANI_DASH,		76 > 77 > 78 > 79 > 80 > 71);
	SET_ANIMATION(ACHARACTER_GG, ANI_ATTACK,	22 > 23 > 24 > 25 > 26 > 27 > 28 > 29 > 30 > 31 > 32 > 33 > 34 > 35);
	SET_ANIMATION(ACHARACTER_GG, ANI_ZATTACK,	111 > 112 > 113 > 114 > 115);
	SET_ANIMATION(ACHARACTER_GG, ANI_CAST,		10 > 11 > 12 > 13);
	SET_ANIMATION(ACHARACTER_GG, ANI_HIT,		89 > 90);
	SET_ANIMATION(ACHARACTER_GG, ANI_FALL,		91);
	SET_ANIMATION(ACHARACTER_GG, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_FT, ANI_PREPARE,	132 > 133 > 134 > 135);
	SET_ANIMATION(ACHARACTER_FT, ANI_WALK,		136 > 137 > 138 > 139 > 140 > 141 > 142 > 143);
	SET_ANIMATION(ACHARACTER_FT, ANI_DASH,		39 > 40 > 41 > 42 > 43 > 44 > 45 > 46);
	SET_ANIMATION(ACHARACTER_FT, ANI_ATTACK,	5 > 6 > 7 > 8 > 9);
	SET_ANIMATION(ACHARACTER_FT, ANI_ZATTACK,	30 > 31 > 32 > 33 > 34 > 35);
	SET_ANIMATION(ACHARACTER_FT, ANI_CAST,		92 > 93 > 94 > 95);
	SET_ANIMATION(ACHARACTER_FT, ANI_HIT,		77 > 78 > 84 > 85);
	SET_ANIMATION(ACHARACTER_FT, ANI_FALL,		79 > 80 > 81 > 82 > 83);
	SET_ANIMATION(ACHARACTER_FT, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_FM, ANI_NORMAL,	0 > 1 > 2 > 3);
	SET_ANIMATION(ACHARACTER_FM, ANI_PREPARE,	12 > 13 > 14 > 15);
	SET_ANIMATION(ACHARACTER_FM, ANI_WALK,		4 > 5 > 6 > 7 > 8 > 9 > 10 > 11);
	SET_ANIMATION(ACHARACTER_FM, ANI_DASH,		136 > 137 > 138 > 139 > 140 > 141 > 142 > 143);
	SET_ANIMATION(ACHARACTER_FM, ANI_ATTACK,	28 > 29 > 30 > 31 > 32);
	SET_ANIMATION(ACHARACTER_FM, ANI_ZATTACK,	64 > 65 > 66 > 67 > 68);
	SET_ANIMATION(ACHARACTER_FM, ANI_CAST,		79 > 80 > 81 > 82 > 83 > 84 > 85);
	SET_ANIMATION(ACHARACTER_FM, ANI_HIT,		74 > 75);
	SET_ANIMATION(ACHARACTER_FM, ANI_FALL,		76 > 77 > 78);
	SET_ANIMATION(ACHARACTER_FM, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_MG, ANI_NORMAL,	10 > 11 > 12 > 13);
	SET_ANIMATION(ACHARACTER_MG, ANI_PREPARE,	14 > 15 > 16 > 17);
	SET_ANIMATION(ACHARACTER_MG, ANI_WALK,		0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8 > 9);
	SET_ANIMATION(ACHARACTER_MG, ANI_DASH, 18 > 19 > 20 > 21);
	SET_ANIMATION(ACHARACTER_MG, ANI_ATTACK, 109 > 110 > 111 > 112 > 113 > 113 > 113);
	SET_ANIMATION(ACHARACTER_MG, ANI_ZATTACK, 114 > 115 > 116 > 117 > 118 > 118 > 118);
	SET_ANIMATION(ACHARACTER_MG, ANI_CAST, 144 > 145 > 146 > 146 > 146 > 147);
	SET_ANIMATION(ACHARACTER_MG, ANI_HIT, 128 > 128 > 129 > 129);
	SET_ANIMATION(ACHARACTER_MG, ANI_FALL, 133 > 134 > 134 > 134 > 134 > 134);
	SET_ANIMATION(ACHARACTER_MG, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_MM, ANI_NORMAL, 0 > 1 > 2 > 3 > 4 > 5 > 6 > 7);
	SET_ANIMATION(ACHARACTER_MM, ANI_PREPARE, 8 > 9 > 10 > 11 > 12 > 13 > 14 > 15 > 16 > 17);
	SET_ANIMATION(ACHARACTER_MM, ANI_WALK, 18 > 19 > 20 > 21 > 22 > 23 > 24 > 25 > 26 > 27);
	SET_ANIMATION(ACHARACTER_MM, ANI_DASH, 28 > 29 > 30 > 31 > 32 > 33 > 34 > 35);
	SET_ANIMATION(ACHARACTER_MM, ANI_ATTACK, 60 > 61 > 62 > 63 > 64);
	SET_ANIMATION(ACHARACTER_MM, ANI_ZATTACK, 60 > 61 > 62 > 63 > 64);
	SET_ANIMATION(ACHARACTER_MM, ANI_CAST, 142 > 143 > 144 > 145 > 146 > 147 > 148 > 149 > 150 > 151 > 152 > 153);
	SET_ANIMATION(ACHARACTER_MM, ANI_HIT, 175 > 176);
	SET_ANIMATION(ACHARACTER_MM, ANI_FALL, 177 > 178 > 179);
	SET_ANIMATION(ACHARACTER_MM, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_PR, ANI_NORMAL, 0 > 1 > 2 > 3);
	SET_ANIMATION(ACHARACTER_PR, ANI_PREPARE, 4 > 5 > 6 > 7);
	SET_ANIMATION(ACHARACTER_PR, ANI_WALK, 65 > 66 > 67 > 68 > 69 > 70 > 71 > 72);
	SET_ANIMATION(ACHARACTER_PR, ANI_DASH, 73 > 74 > 75 > 76 > 77 > 78);
	SET_ANIMATION(ACHARACTER_PR, ANI_ATTACK, 8 > 9 > 10 > 11 > 12 > 13 > 14 > 15);
	SET_ANIMATION(ACHARACTER_PR, ANI_ZATTACK, 31 > 32 > 33 > 34 > 35 > 36 > 37 > 38 > 39);
	SET_ANIMATION(ACHARACTER_PR, ANI_CAST, 146 > 147 > 148 > 149 > 150 > 151 > 152 > 153);
	SET_ANIMATION(ACHARACTER_PR, ANI_HIT, 122 > 123);
	SET_ANIMATION(ACHARACTER_PR, ANI_FALL, 124 > 126 > 126 > 126);
	SET_ANIMATION(ACHARACTER_PR, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_PG, ANI_NORMAL, 0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8);
	SET_ANIMATION(ACHARACTER_PG, ANI_PREPARE, 9 > 10 > 11 > 12);
	SET_ANIMATION(ACHARACTER_PG, ANI_WALK, 13 > 14 > 15 > 16 > 17 > 18 > 19 > 20);
	SET_ANIMATION(ACHARACTER_PG, ANI_DASH, 21 > 22 > 23 > 24 > 25 > 26 > 27 > 28);
	SET_ANIMATION(ACHARACTER_PG, ANI_ATTACK, 23 > 30 > 31 > 32);
	SET_ANIMATION(ACHARACTER_PG, ANI_ZATTACK, 70 > 71 > 72 > 73);
	SET_ANIMATION(ACHARACTER_PG, ANI_CAST, 108 > 109 > 110 > 111 > 112);
	SET_ANIMATION(ACHARACTER_PG, ANI_HIT, 51 > 52);
	SET_ANIMATION(ACHARACTER_PG, ANI_FALL, 53 > 54 > 55);
	SET_ANIMATION(ACHARACTER_PG, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_TH, ANI_NORMAL, 0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8 > 9 > 10 > 11);
	SET_ANIMATION(ACHARACTER_TH, ANI_PREPARE, 12 > 13 > 14 > 15 > 16 > 17);
	SET_ANIMATION(ACHARACTER_TH, ANI_WALK, 18 > 19 > 20 > 21 > 22 > 23 > 24 > 25 > 26);
	SET_ANIMATION(ACHARACTER_TH, ANI_DASH, 61 > 62 > 63 > 64 > 65 > 66);
	SET_ANIMATION(ACHARACTER_TH, ANI_ATTACK, 67 > 68 > 69 > 70 > 71 > 72);
	SET_ANIMATION(ACHARACTER_TH, ANI_ZATTACK, 96 > 97 > 98 > 99 > 100);
	SET_ANIMATION(ACHARACTER_TH, ANI_CAST, 32 > 33 > 34 > 35 > 36 > 37 > 38 > 39 > 40 > 41 > 42 > 43 > 44 > 45);
	SET_ANIMATION(ACHARACTER_TH, ANI_HIT, 91 > 92);
	SET_ANIMATION(ACHARACTER_TH, ANI_FALL, 93 > 94 > 95);
	SET_ANIMATION(ACHARACTER_TH, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_KN, ANI_NORMAL, 0 > 1 > 2 > 3 > 4 > 5);
	SET_ANIMATION(ACHARACTER_KN, ANI_PREPARE, 6 > 7 > 8 > 9 > 10 > 11);
	SET_ANIMATION(ACHARACTER_KN, ANI_WALK, 12 > 13 > 14 > 15 > 16 > 17 > 18 > 19 > 20 > 21);
	SET_ANIMATION(ACHARACTER_KN, ANI_DASH, 22 > 23 > 24 > 25 > 26 > 27 > 28 > 29);
	SET_ANIMATION(ACHARACTER_KN, ANI_ATTACK, 51 > 52 > 53 > 54 > 55 > 56 > 57 > 58 > 59);
	SET_ANIMATION(ACHARACTER_KN, ANI_ZATTACK, 182 > 183 > 184 > 185 > 186);
	SET_ANIMATION(ACHARACTER_KN, ANI_CAST, 170 > 171 > 172 > 173 > 174 > 175 > 176 > 177 > 178 > 179 > 180 > 171);
	SET_ANIMATION(ACHARACTER_KN, ANI_HIT, 195 > 196);
	SET_ANIMATION(ACHARACTER_KN, ANI_FALL, 197 > 198 > 199);
	SET_ANIMATION(ACHARACTER_KN, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_DL, ANI_NORMAL, 0 > 1 > 2 > 3);
	SET_ANIMATION(ACHARACTER_DL, ANI_PREPARE, 4 > 5 > 6 > 7);
	SET_ANIMATION(ACHARACTER_DL, ANI_WALK, 8 > 9 > 10 > 11 > 12 > 13 > 14 > 15 > 16);
	SET_ANIMATION(ACHARACTER_DL, ANI_DASH, 17 > 18 > 19 > 20 > 21 > 22 > 23 > 24);
	SET_ANIMATION(ACHARACTER_DL, ANI_ATTACK, 62 > 63 > 64 > 65 > 66);
	SET_ANIMATION(ACHARACTER_DL, ANI_ZATTACK, 143 > 144 > 145 > 146 > 147 > 148 > 149);
	SET_ANIMATION(ACHARACTER_DL, ANI_CAST, 158 > 159 > 160);
	SET_ANIMATION(ACHARACTER_DL, ANI_HIT, 175 > 176);
	SET_ANIMATION(ACHARACTER_DL, ANI_FALL, 177 > 178 > 179);
	SET_ANIMATION(ACHARACTER_DL, ANI_FULLPLAY,	0 >= maxFrame);
	SET_ANIMATION(ACHARACTER_GB, ANI_NORMAL, 0 > 1 > 2 > 3 > 4 > 5 > 6 > 7 > 8 > 9);
	SET_ANIMATION(ACHARACTER_GB, ANI_PREPARE, 10 > 11 > 12 > 13 > 14);
	SET_ANIMATION(ACHARACTER_GB, ANI_WALK, 15 > 16 > 17 > 18 > 19 > 20 > 21 > 22);
	SET_ANIMATION(ACHARACTER_GB, ANI_DASH, 23 > 24 > 25 > 26 > 27 > 28 > 29 > 30);
	SET_ANIMATION(ACHARACTER_GB, ANI_ATTACK, 76 > 77 > 78 > 79);
	SET_ANIMATION(ACHARACTER_GB, ANI_ZATTACK, 56 > 57 > 58 > 59 > 60 > 61 > 62);
	SET_ANIMATION(ACHARACTER_GB, ANI_CAST, 141 > 142 > 143 > 144);
	SET_ANIMATION(ACHARACTER_GB, ANI_HIT, 145 > 146);
	SET_ANIMATION(ACHARACTER_GB, ANI_FALL, 147 > 148 > 149);
	SET_ANIMATION(ACHARACTER_GB, ANI_FULLPLAY,	0 >= maxFrame);
#undef SET_ANIMATION
}

void ToolAvatar::OnCbnSelchangeComboAction()
{
	int aniID = cbAction->GetCurSel();
	setAnimation(aniID);
	playing = aniID > 0;
}


void ToolAvatar::OnMenuLocalizeMapEdit()
{
	//打开映射表文件
	ShellExecute(NULL, L"open", profile.getAvatarMapPath() + careerName[character] + L"装扮表.txt", NULL, NULL, SW_SHOWNORMAL);
}


void ToolAvatar::OnMenuLocalizeMapCombine()
{
	//合并其他映射表
	if(IDYES != MessageBox(L"要先确认你要合并的映射表的职业跟当前职业一样。\r\n当前职业为："+careerName[character]+L"，确认喵？",L"提示喵", MB_YESNO))
		return;
	CString defExt = L"映射表文件(*.TXT)|*.TXT";
	CString extFilter = L"映射表文件(*.TXT)|*.TXT||";
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(IDOK == dlg.DoModal()){
		AvatarMap newMap;
		newMap.initial(character);
		newMap.load(CStrToStr(dlg.GetPathName()));
		//导入套装信息
		int count = 0;
		int totalCount = 0;
		for(int i = 0;i<newMap.suitContent.size();i++){
			totalCount ++;
			const AvatarSuitEntry &ase = newMap.suitContent[i];
			if(map.checkSuitEntry(ase.suitName, ase.avatarID))
				continue;
			map.addSuitEntry(ase.suitName, ase.avatarID);
			count ++;
		}
		for(int i = 0;i<newMap.weapon.size();i++){
			const WeaponType &wt = newMap.weapon[i];
			for(int j = 0;j<newMap.weaponContent[i].size();j++){
				totalCount ++;
				const AvatarMapEntry &ame = newMap.weaponContent[i][j];
				if(map.checkWeaponEntry(wt, ame.avatarID, ame.iconName, ame.avatarTitle))
					continue;
				map.addWeaponEntry(wt, ame.avatarID, ame.iconName, ame.avatarTitle);
				count ++;
			}
		}
		for(int i = 0;i<newMap.avatarContent.size();i++){
			for(int j = 0;j<newMap.avatarContent[i].size();j++){
				totalCount ++;
				const AvatarMapEntry &ame = newMap.avatarContent[i][j];
				if(map.checkAvatarEntry((AvatarPart)i, ame.avatarID, ame.iconName, ame.avatarTitle))
					continue;
				map.addAvatarEntry((AvatarPart)i, ame.avatarID, ame.iconName, ame.avatarTitle);
				count ++;
			}
		}
		map.save(CStrToStr(profile.getAvatarMapPath() + careerName[character] + L"装扮表.txt"));
		MessageBox(L"导入完毕喵！\r\n已成功导入："+NumToCStr(count) + L"条，跳过"+NumToCStr(totalCount - count) +L"条。",L"提示喵");
		updateList();
	}
}


void ToolAvatar::OnMenuLocalizeMapResort()
{
	//映射表去重复项
	if(IDYES != MessageBox(L"即将搜寻并去除映射表中的重复项，确定喵？",L"提示喵", MB_YESNO))
		return;
	map.save(CStrToStr(profile.getAvatarMapPath() + careerName[character] + L"装扮表(清理前的).txt"));
	long i, j;
	std::vector<long> deleteList, deleteListSorted;
	deleteList.clear();
	deleteListSorted.clear();
	int count = 0;
	for(i = 0;i<map.suitContent.size();i++){
		//先查看i是不是处在待删除的名单上
		bool iIsDeleted = false;
		for(int k = 0;k<deleteList.size();k++){
			if(i == deleteList[k]){
				iIsDeleted = true;
				break;
			}
		}
		if(iIsDeleted)
			continue;
		//以i做对比，寻找j
		const AvatarSuitEntry &ase1 = map.suitContent[i];
		for(j = i + 1;j<map.suitContent.size();j++){
			//先查看j是不是处在待删除的名单上
			bool jIsDeleted = false;
			for(int k = 0;k<deleteList.size();k++){
				if(j == deleteList[k]){
					iIsDeleted = true;
					break;
				}
			}
			if(jIsDeleted)
				continue;	
			//二者都没删除，开始进行对比
			const AvatarSuitEntry &ase2 = map.suitContent[j];
			bool allSame = true;
			for(int k = 0;k<9;k++){
				if(ase1.avatarID[k] != ase2.avatarID[k]){
					allSame = false;
					break;
				}
			}
			if(!allSame)
				continue;
			//如果套装ID完全一样，将名字长的塞进删除名单
			if(ase2.suitName.find(ase1.suitName) != str::npos){
				deleteList.push_back(j);
			}else if(ase1.suitName.find(ase2.suitName) != str::npos){
				deleteList.push_back(i);
				break;
			}
		}
	}
	//对deleteList进行排序
	for(i = 0;i<deleteList.size();i++){
		bool hasFound = false;
		for(j = 0;j<deleteListSorted.size();j++){
			if(deleteListSorted[j] > deleteList[i]){
				hasFound = true;
				deleteListSorted.insert(deleteListSorted.begin() + j, deleteList[i]);
				break;
			}
		}
		if(!hasFound){
			deleteListSorted.push_back(deleteList[i]);
		}
	}
	for(i = 0;i<deleteListSorted.size();i++){
		count ++;
		map.deleteSuitEntry(deleteListSorted[deleteList.size() - i - 1]);
	}


	for(int p = 0;p<map.avatarContent.size();p++){
		deleteList.clear();
		deleteListSorted.clear();
		for(i = 0;i<map.avatarContent[p].size();i++){
			//先查看i是不是处在待删除的名单上
			bool iIsDeleted = false;
			for(int k = 0;k<deleteList.size();k++){
				if(i == deleteList[k]){
					iIsDeleted = true;
					break;
				}
			}
			if(iIsDeleted)
				continue;
			//以i做对比，寻找j
			const AvatarMapEntry &ame1 = map.avatarContent[p][i];
			for(j = i + 1;j<map.avatarContent[p].size();j++){
				//先查看j是不是处在待删除的名单上
				bool jIsDeleted = false;
				for(int k = 0;k<deleteList.size();k++){
					if(j == deleteList[k]){
						jIsDeleted = true;
						break;
					}
				}
				if(jIsDeleted)
					continue;	
				//二者都没删除，开始进行对比
				const AvatarMapEntry &ame2 = map.avatarContent[p][j];
				bool allSame = true;
				if(ame1.avatarID != ame2.avatarID)
					allSame = false;
				if(ame1.iconName.find(ame2.iconName) == str::npos)
					allSame = false;
				if(!allSame)
					continue;
				//如果套装ID完全一样，将名字长的塞进删除名单
				if(ame2.avatarTitle.find(ame1.avatarTitle) != str::npos){
					deleteList.push_back(j);
				}else if(ame1.avatarTitle.find(ame2.avatarTitle) != str::npos){
					deleteList.push_back(i);
					break;
				}
			}
		}
		//对deleteList进行排序
		for(i = 0;i<deleteList.size();i++){
			bool hasFound = false;
			for(j = 0;j<deleteListSorted.size();j++){
				if(deleteListSorted[j] > deleteList[i]){
					hasFound = true;
					deleteListSorted.insert(deleteListSorted.begin() + j, deleteList[i]);
					break;
				}
			}
			if(!hasFound){
				deleteListSorted.push_back(deleteList[i]);
			}
		}
		for(i = 0;i<deleteListSorted.size();i++){
			count ++;
			map.deleteAvatarEntry((AvatarPart)p, deleteListSorted[deleteList.size() - i - 1]);
		}
	}


	for(int h = 0;h<map.weaponContent.size();h++){
		deleteList.clear();
		deleteListSorted.clear();
		for(i = 0;i<map.weaponContent[h].size();i++){
			//先查看i是不是处在待删除的名单上
			bool iIsDeleted = false;
			for(int k = 0;k<deleteList.size();k++){
				if(i == deleteList[k]){
					iIsDeleted = true;
					break;
				}
			}
			if(iIsDeleted)
				continue;
			//以i做对比，寻找j
			const AvatarMapEntry &ame1 = map.weaponContent[h][i];
			for(j = i + 1;j<map.weaponContent[h].size();j++){
				//先查看j是不是处在待删除的名单上
				bool jIsDeleted = false;
				for(int k = 0;k<deleteList.size();k++){
					if(j == deleteList[k]){
						jIsDeleted = true;
						break;
					}
				}
				if(jIsDeleted)
					continue;	
				//二者都没删除，开始进行对比
				const AvatarMapEntry &ame2 = map.weaponContent[h][j];
				bool allSame = true;
				if(ame1.avatarID != ame2.avatarID)
					allSame = false;
				if(ame1.iconName.find(ame2.iconName) == str::npos)
					allSame = false;
				if(!allSame)
					continue;
				//如果套装ID完全一样，将名字长的塞进删除名单
				if(ame2.avatarTitle.find(ame1.avatarTitle) != str::npos){
					deleteList.push_back(j);
				}else if(ame1.avatarTitle.find(ame2.avatarTitle) != str::npos){
					deleteList.push_back(i);
					break;
				}
			}
		}
		//对deleteList进行排序
		for(i = 0;i<deleteList.size();i++){
			bool hasFound = false;
			for(j = 0;j<deleteListSorted.size();j++){
				if(deleteListSorted[j] > deleteList[i]){
					hasFound = true;
					deleteListSorted.insert(deleteListSorted.begin() + j, deleteList[i]);
					break;
				}
			}
			if(!hasFound){
				deleteListSorted.push_back(deleteList[i]);
			}
		}
		WeaponType wt = map.weapon[h];
		for(i = 0;i<deleteListSorted.size();i++){
			count ++;
			map.deleteWeaponEntry(wt, deleteListSorted[deleteList.size() - i - 1]);
		}
	}
	if(count == 0){
		MessageBox(L"已经清理不动了喵！",L"提示喵");
	}else{
		map.save(CStrToStr(profile.getAvatarMapPath() + careerName[character] + L"装扮表.txt"));
		MessageBox(L"整理完毕，总共清除了"+NumToCStr(count)+L"个重复的条目喵！",L"提示喵");
		updateList();
	}
}

void ToolAvatar::OnMenuSuitList()
{
	// TODO: 在此添加命令处理程序代码
	ToolAvatarSuit dlg;
	dlg.charInput = character;
	if(IDOK == dlg.DoModal()){
		PLAYING_PAUSE;
		for(int p = 0;p<APART_MAXCOUNT;p++){
			long index = factory.album[p].findAvatarID(dlg.outputID[p]);
			factory.changeAvatar((AvatarPart)p, index);
			if(p == currentPart){
				lbContent->SetCurSel(index+1); 
				showAvatarInfo();
			}
		}
		updateSuitInfo();
		drawModel(-1);
		PLAYING_CONTINUE;
	}
}


void ToolAvatar::OnMenuSuitRegister()
{
	// TODO: 在此添加命令处理程序代码
	ToolAvatarSuitRegister dlg;
	dlg.charInput = character;
	for(int p = 0;p<APART_MAXCOUNT;p++){
		if(factory.album[p].currentSelect == -1){
			dlg.inputID[p] = -1;
		}else{
			dlg.inputID[p] = factory.album[p].content[factory.album[p].currentSelect].ID;
		}
	}
	if(IDOK == dlg.DoModal()){
		str fileName = CStrToStr(profile.getAvatarMapPath() + careerName[character] + L"装扮表.txt");
		map.load(fileName);
		updateSuitInfo();
		showAvatarInfo();
	}
}


void ToolAvatar::OnMenuSuitImport()
{
	// TODO: 在此添加命令处理程序代码
	CString inStr;
	ToolAvatarIO dlg;
	dlg.style = ToolAvatarIO::AVA_IMPORT;
	if(IDOK == dlg.DoModal()){
		inStr = dlg.content;
		CString charStr;
		if(!AfxExtractSubString(charStr, inStr, 0, '{')){
			MessageBox(L"共享码无效喵！");
			return;
		}
		if(charStr.GetLength() == 0){
			MessageBox(L"共享码无效喵！");
			return;
		}
		if(charStr != careerName[character]){
			MessageBox(L"当前共享码不属于" + careerName[character] + L"的共享码喵！");
			return;
		}
		CString contentStr;
		if(!AfxExtractSubString(contentStr, inStr, 1, '{')){
			MessageBox(L"共享码无效喵！");
			return;
		}
		//把"}"去掉
		CString entryStr;
		contentStr = contentStr.Left(contentStr.GetLength() - 1);
		int np = 0;
		PLAYING_PAUSE;
		while(AfxExtractSubString(entryStr, contentStr, np, ',')){
			np ++;
			CString partStr, idStr;
			AfxExtractSubString(partStr, entryStr, 0, ':');
			AfxExtractSubString(idStr, entryStr, 1, ':');
			for(int p = 0;p<APART_MAXCOUNT;p++){
				if(partStr == avatarCString[p]){
					long index = factory.album[p].findAvatarID(_ttol(idStr));
					factory.changeAvatar((AvatarPart)p, index);
					if(p == currentPart){
						lbContent->SetCurSel(index+1); 
						showAvatarInfo();
					}
				}
			}
		}
		updateSuitInfo();
		drawModel(-1);
		PLAYING_CONTINUE;
	}
}


void ToolAvatar::OnMenuSuitExport()
{
	// TODO: 在此添加命令处理程序代码
	CString exStr = careerName[character];
	exStr += L"{";
	for(int p = 0;p<APART_MAXCOUNT;p++){
		long currentSelect = factory.album[p].currentSelect;
		if(currentSelect != -1){
			exStr += avatarCString[p] + L":" + NumToCStr(factory.album[p].content[currentSelect].ID)+L",";
		}
	}
	if(exStr.Right(1) == L",")
		exStr = exStr.Left(exStr.GetLength() - 1);
	exStr += L"}";
	ToolAvatarIO dlg;
	dlg.style = ToolAvatarIO::AVA_EXPORT;
	dlg.content = exStr;
	dlg.DoModal();
}


void ToolAvatar::OnMenuAvatarmodelRefresh()
{
	// TODO: 更新展示图
	buildModel(lastSelected + currentPage * modelInfo.countPerPage);
	drawModel(-1);
}


void ToolAvatar::OnMenuAvatarmodelRegister()
{
	// TODO: 注册模型
	ToolAvatarRegister dlg;
	dlg.charInput = character;
	dlg.partInput = currentPart;
	dlg.weaponIndexInput = currentWeaponIndex;
	if(currentPart == APART_WEAPON){
		dlg.inputID = factory.weaponAlbum[currentWeaponIndex].content[factory.weaponAlbum[currentWeaponIndex].currentSelect].ID;
	}else{
		dlg.inputID = factory.album[currentPart].content[factory.album[currentPart].currentSelect].ID;
	}
	if(IDOK == dlg.DoModal()){
		int n = lbContent->GetCurSel();
		map.load(CStrToStr(profile.getAvatarMapPath() + careerName[character] + L"装扮表.txt"));
		updateList();
		lbContent->SetCurSel(n);
		showAvatarInfo();
		updateSuitInfo();
	}
}


void ToolAvatar::OnBnClickedButtonTool12()
{
	// TODO: 在此添加控件通知处理程序代码
	if(loading)
		return;
	CString findStr;
	GET_CTRL(CEdit, IDC_EDIT_SEARCH)->GetWindowText(findStr);
	if(findStr.GetLength() == 0)
		return;
	for(int i = lbContent->GetCurSel() + 1; i<lbContent->GetCount(); i++) {
		CString cstr;
		lbContent->GetText(i, cstr);
		if(cstr.Find(findStr) != -1){
			lbContent->SetCurSel(i);
			OnLbnSelchangeListContent();
			return;
		}
	}
	MessageBox(L"没有找到字符串“"+findStr+L"”喵。",L"提示喵");
}


void ToolAvatar::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//Do nothing
	//CDialogEx::OnOK();
}


void ToolAvatar::OnMenuLocalizeSetResource()
{
	// TODO: 在此添加命令处理程序代码
	HWND hwnd= GetSafeHwnd();
	CString filePath= L"";
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("选择资源文件夹");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){  
			if(::SHGetPathFromIDList(pidl, pszBuffer)){
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);
			if(filePath.GetLength()<=1){
				MessageBox(L"并不是有效的文件夹喵！",L"提示喵");
			}else{
				profile.avatarPath = filePath;
				profile.saveProfile();
				MessageBox(L"已设置资源文件夹喵！");
				chooseCharacter(character);
			}
		}
		pMalloc->Release();
	}
}


void ToolAvatar::OnMenuLocalizeOpenResource()
{
	// TODO: 在此添加命令处理程序代码
	ShellExecute(NULL, L"open", profile.getAvatarPath(), NULL, NULL, SW_SHOWNORMAL);
}


void ToolAvatar::OnMenuLocalizeDownloadResource()
{
	// TODO: 在此添加命令处理程序代码
	ToolAvatarDownload dlg;
	dlg.DoModal();
}


void ToolAvatar::OnMenuSuitAnimation()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(buildGIF, this);
}


void ToolAvatar::OnBnClickedButtonTool13() {
	// TODO:  在此添加控件通知处理程序代码
	PLAYING_PAUSE;
	srand(time(0));
	for(int p = 0; p<APART_MAXCOUNT; p++) {
		if(p == APART_BODY)
			continue;
		long index = -1;
		if(factory.album[p].content.size() > 0)
			index = rand() % factory.album[p].content.size();
		factory.changeAvatar((AvatarPart)p, index);
		if(p == currentPart) {
			lbContent->SetCurSel(index + 1);
			showAvatarInfo();
		}
		
	}
	updateSuitInfo();
	drawModel(-1);
	PLAYING_CONTINUE;
}
