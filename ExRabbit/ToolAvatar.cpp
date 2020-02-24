// ToolAvatar.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatar.h"
#include "afxdialogex.h"
#include "ExRabbitdlg.h"
#include "ToolAvatarES.h"

// CToolAvatar 对话框

IMPLEMENT_DYNAMIC(CToolAvatar, CDialogEx)

CToolAvatar::CToolAvatar(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolAvatar::IDD, pParent){

}

CToolAvatar::~CToolAvatar(){
}

BEGIN_MESSAGE_MAP(CToolAvatar, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_CAREER, &CToolAvatar::OnCbnSelchangeComboCareer)
	ON_CBN_SELCHANGE(IDC_COMBO_PART1, &CToolAvatar::OnCbnSelchangeComboPart1)
	ON_CBN_SELCHANGE(IDC_COMBO_PART2, &CToolAvatar::OnCbnSelchangeComboPart2)
	ON_CBN_SELCHANGE(IDC_COMBO_PART3, &CToolAvatar::OnCbnSelchangeComboPart3)
	ON_CBN_SELCHANGE(IDC_COMBO_PART4, &CToolAvatar::OnCbnSelchangeComboPart4)
	ON_CBN_SELCHANGE(IDC_COMBO_PART5, &CToolAvatar::OnCbnSelchangeComboPart5)
	ON_CBN_SELCHANGE(IDC_COMBO_PART6, &CToolAvatar::OnCbnSelchangeComboPart6)
	ON_CBN_SELCHANGE(IDC_COMBO_PART7, &CToolAvatar::OnCbnSelchangeComboPart7)
	ON_CBN_SELCHANGE(IDC_COMBO_PART8, &CToolAvatar::OnCbnSelchangeComboPart8)
	ON_CBN_SELCHANGE(IDC_COMBO_PART9, &CToolAvatar::OnCbnSelchangeComboPart9)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE1, &CToolAvatar::OnCbnSelchangeComboPalette1)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE2, &CToolAvatar::OnCbnSelchangeComboPalette2)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE3, &CToolAvatar::OnCbnSelchangeComboPalette3)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE4, &CToolAvatar::OnCbnSelchangeComboPalette4)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE5, &CToolAvatar::OnCbnSelchangeComboPalette5)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE6, &CToolAvatar::OnCbnSelchangeComboPalette6)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE7, &CToolAvatar::OnCbnSelchangeComboPalette7)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE8, &CToolAvatar::OnCbnSelchangeComboPalette8)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE9, &CToolAvatar::OnCbnSelchangeComboPalette9)
	ON_BN_CLICKED(IDCANCEL, &CToolAvatar::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTION, &CToolAvatar::OnCbnSelchangeComboAction)
	ON_BN_CLICKED(IDC_BUTTON_PART1, &CToolAvatar::OnBnClickedButtonPart1)
	ON_BN_CLICKED(IDC_BUTTON_PART2, &CToolAvatar::OnBnClickedButtonPart2)
	ON_BN_CLICKED(IDC_BUTTON_PART3, &CToolAvatar::OnBnClickedButtonPart3)
	ON_BN_CLICKED(IDC_BUTTON_PART4, &CToolAvatar::OnBnClickedButtonPart4)
	ON_BN_CLICKED(IDC_BUTTON_PART5, &CToolAvatar::OnBnClickedButtonPart5)
	ON_BN_CLICKED(IDC_BUTTON_PART6, &CToolAvatar::OnBnClickedButtonPart6)
	ON_BN_CLICKED(IDC_BUTTON_PART7, &CToolAvatar::OnBnClickedButtonPart7)
	ON_BN_CLICKED(IDC_BUTTON_PART8, &CToolAvatar::OnBnClickedButtonPart8)
	ON_BN_CLICKED(IDC_BUTTON_PART9, &CToolAvatar::OnBnClickedButtonPart9)
	ON_BN_CLICKED(IDC_BUTTON_RESOURCE, &CToolAvatar::OnBnClickedButtonResource)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CToolAvatar::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CToolAvatar::OnBnClickedButtonNext)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_AVATAR_SETNAME, &CToolAvatar::OnMenuAvatarSetName)
	ON_COMMAND(ID_MENU_AVATAR_SETICON, &CToolAvatar::OnMenuAvatarSetIcon)
	ON_COMMAND(ID_MENU_AVATARSIZE_SMALL, &CToolAvatar::OnMenuAvatarSizeSmall)
	ON_COMMAND(ID_MENU_AVATARSIZE_MEDIUM, &CToolAvatar::OnMenuAvatarSizeMedium)
	ON_COMMAND(ID_MENU_AVATARSIZE_LARGE, &CToolAvatar::OnMenuAvatarSizeLarge)
	ON_COMMAND(ID_MENU_AVATARSIZE_HUGE, &CToolAvatar::OnMenuAvatarSizeHuge)
	ON_COMMAND(ID_MENU_AVATAR_REFRESH, &CToolAvatar::OnMenuAvatarRefresh)
	ON_COMMAND(ID_MENU_AVATAR_REFRESH_ALL, &CToolAvatar::OnMenuAvatarRefreshAll)
	ON_BN_CLICKED(IDC_RADIO_DISPLAY1, &CToolAvatar::OnBnClickedRadioDisplay1)
	ON_BN_CLICKED(IDC_RADIO_DISPLAY2, &CToolAvatar::OnBnClickedRadioDisplay2)
	ON_BN_CLICKED(IDC_RADIO_DISPLAY3, &CToolAvatar::OnBnClickedRadioDisplay3)
	ON_COMMAND(ID_MENU_AVATAR_REFRESH_ICON, &CToolAvatar::OnMenuAvatarRefreshIcon)
	ON_COMMAND(ID_MENU_AVATAR_SETAVATAR, &CToolAvatar::OnMenuAvatarSetavatar)
	ON_COMMAND(ID_MENU_AVATAR_SETAVATAR2, &CToolAvatar::OnMenuAvatarSetAvatar2)
	ON_BN_CLICKED(IDC_BUTTON_ONE_KEY, &CToolAvatar::OnBnClickedButtonOneKey)
	ON_COMMAND(ID_MENU_ONE_KEY_LOCALIZE, &CToolAvatar::OnMenuOneKeyLocalize)
	ON_COMMAND(ID_MENU_ONE_KEY_PATCH, &CToolAvatar::OnMenuOneKeyPatch)
	ON_COMMAND(ID_MENU_ONE_KEY_NPK, &CToolAvatar::OnMenuOneKeyNPK)
	ON_CBN_SELCHANGE(IDC_COMBO_MULTCOLOR, &CToolAvatar::OnCbnSelchangeComboMultcolor)
	ON_COMMAND(ID_MENU_ONE_KEY_HIDE, &CToolAvatar::OnMenuOneKeyHide)
	ON_CBN_SELCHANGE(IDC_COMBO_SUIT, &CToolAvatar::OnCbnSelchangeComboSuit)
END_MESSAGE_MAP()


// CToolAvatar 消息处理程序
BOOL CToolAvatar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowPos(NULL,0,0,950,630,SWP_NOZORDER|SWP_NOMOVE);
	GET_CTRL(CComboBox, IDC_COMBO_SUIT)->ShowWindow(SW_HIDE);

	SET_CTRL(CButton, IDC_BUTTON_RESOURCE, 10, 10, 70, 30);
	SET_CTRL(CEdit, IDC_EDIT_FOLDER, 80, 10, 200, 30);
	SET_CTRL(CComboBox, IDC_COMBO_CAREER, 10, 40, 150, 60);
	SET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR, 160, 40, 200, 60);
	SET_CTRL(CButton, IDC_BUTTON_PART1, 10, 70, 50, 94);
	SET_CTRL(CComboBox, IDC_COMBO_PART1, 60, 70, 150, 90);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE1, 160, 70, 200, 90);
	SET_CTRL(CButton, IDC_BUTTON_PART2, 10, 100, 50, 124);
	SET_CTRL(CComboBox, IDC_COMBO_PART2, 60, 100, 150, 120);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE2, 160, 100, 200, 120);
	SET_CTRL(CButton, IDC_BUTTON_PART3, 10, 130, 50, 154);
	SET_CTRL(CComboBox, IDC_COMBO_PART3, 60, 130, 150, 150);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE3, 160, 130, 200, 150);
	SET_CTRL(CButton, IDC_BUTTON_PART4, 10, 160, 50, 184);
	SET_CTRL(CComboBox, IDC_COMBO_PART4, 60, 160, 150, 180);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE4, 160, 160, 200, 180);
	SET_CTRL(CButton, IDC_BUTTON_PART5, 10, 190, 50, 214);
	SET_CTRL(CComboBox, IDC_COMBO_PART5, 60, 190, 150, 210);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE5, 160, 190, 200, 210);
	SET_CTRL(CButton, IDC_BUTTON_PART6, 10, 220, 50, 244);
	SET_CTRL(CComboBox, IDC_COMBO_PART6, 60, 220, 150, 240);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE6, 160, 220, 200, 240);
	SET_CTRL(CButton, IDC_BUTTON_PART7, 10, 250, 50, 274);
	SET_CTRL(CComboBox, IDC_COMBO_PART7, 60, 250, 150, 270);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE7, 160, 250, 200, 270);
	SET_CTRL(CButton, IDC_BUTTON_PART8, 10, 280, 50, 304);
	SET_CTRL(CComboBox, IDC_COMBO_PART8, 60, 280, 150, 300);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE8, 160, 280, 200, 300);
	SET_CTRL(CButton, IDC_BUTTON_PART9, 10, 310, 50, 334);
	SET_CTRL(CComboBox, IDC_COMBO_PART9, 60, 310, 150, 330);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE9, 160, 310, 200, 330);
	//画布位置(10, 340, 200, 530)
	SET_CTRL(CButton, IDC_BUTTON_PREV, 10, 540, 55, 564);
	SET_CTRL(CButton, IDC_BUTTON_NEXT, 60, 540, 105, 564);
	SET_CTRL(CComboBox, IDC_COMBO_ACTION, 110, 540, 200, 560);
	SET_CTRL(CButton, IDCANCEL, 10, 570, 200, 594);
	//缩略图位置(210, 70, 930, 550)
	SET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING, 210, 10, 710, 30);
	SET_CTRL(CEdit, IDC_EDIT_LOADING_INFO, 720, 10, 930, 30);
	SET_CTRL(CButton, IDC_RADIO_DISPLAY1, 210, 40, 300, 60);
	SET_CTRL(CButton, IDC_RADIO_DISPLAY2, 310, 40, 500, 60);
	SET_CTRL(CButton, IDC_RADIO_DISPLAY3, 510, 40, 700, 60);
	SET_CTRL(CButton, IDC_BUTTON_ONE_KEY, 720, 40, 930, 64);
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->ResetContent();
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"未选择");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"鬼剑士");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"鬼剑士(女)");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"格斗家");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"格斗家(男)");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"神枪手");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"神枪手(女)");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"魔法师");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"魔法师(男)");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"圣职者");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"圣职者(女)");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"暗夜使者");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"守护者");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"魔枪士");
	GET_CTRL(CComboBox, IDC_COMBO_CAREER)->AddString(L"枪剑士");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->ResetContent();
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->AddString(L"-");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->AddString(L"0");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->AddString(L"1");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->AddString(L"2");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->AddString(L"3");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->AddString(L"4");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->AddString(L"5");
	GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->SetCurSel(0);
	cbPart[0] = NULL;
	cbPart[1] = GET_CTRL(CComboBox, IDC_COMBO_PART1);
	cbPart[2] = GET_CTRL(CComboBox, IDC_COMBO_PART2);
	cbPart[3] = GET_CTRL(CComboBox, IDC_COMBO_PART3);
	cbPart[4] = GET_CTRL(CComboBox, IDC_COMBO_PART4);
	cbPart[5] = GET_CTRL(CComboBox, IDC_COMBO_PART5);
	cbPart[6] = GET_CTRL(CComboBox, IDC_COMBO_PART6);
	cbPart[7] = GET_CTRL(CComboBox, IDC_COMBO_PART7);
	cbPart[8] = GET_CTRL(CComboBox, IDC_COMBO_PART8);
	cbPart[9] = GET_CTRL(CComboBox, IDC_COMBO_PART9);
	cbPalette[0] = NULL;
	cbPalette[1] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE1);
	cbPalette[2] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE2);
	cbPalette[3] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE3);
	cbPalette[4] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE4);
	cbPalette[5] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE5);
	cbPalette[6] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE6);
	cbPalette[7] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE7);
	cbPalette[8] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE8);
	cbPalette[9] = GET_CTRL(CComboBox, IDC_COMBO_PALETTE9);

	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0, 1000);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);

	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->ResetContent();
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"选择动作");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"站立(平常)");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"站立(备战)");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"走路");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"跑动");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"普通攻击");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"Z键攻击");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"释放");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"被攻击");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->AddString(L"倒地");
	GET_CTRL(CComboBox, IDC_COMBO_ACTION)->SetCurSel(0);

	context = GetParent();
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	GET_CTRL(CEdit, IDC_EDIT_FOLDER)->SetWindowText(dlg->profile.getAvatarPath());

	
	canvas.create(190,190);
	frame = 0;
	moving = false;
	drawing = false;
	loading = false;
	setAnimation(0);
	page = 0;
	displayStyle = 0;
	displayPart = APART_COAT;
	changeThumbnailSize(profile.avatarThumbSize);

	dict.setFile(profile.getSupportPath() + L"avatarDict.txt");
 	dict.loadDict();
	
	AfxBeginThread(animationThread, this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CToolAvatar::OnBnClickedButtonResource(){
	MessageBox(L"请在“系统菜单→设置”里对试衣间资源目录进行设置喵！",L"提示喵");
}
void CToolAvatar::OnCbnSelchangeComboPart1(){
	OnComboPartChange(APART_CAP);
}
void CToolAvatar::OnCbnSelchangeComboPart2(){
	OnComboPartChange(APART_HAIR);
}
void CToolAvatar::OnCbnSelchangeComboPart3(){
	OnComboPartChange(APART_FACE);
}
void CToolAvatar::OnCbnSelchangeComboPart4(){
	OnComboPartChange(APART_NECK);
}
void CToolAvatar::OnCbnSelchangeComboPart5(){
	OnComboPartChange(APART_COAT);
}
void CToolAvatar::OnCbnSelchangeComboPart6(){
	OnComboPartChange(APART_PANTS);
}
void CToolAvatar::OnCbnSelchangeComboPart7(){
	OnComboPartChange(APART_BELT);
}
void CToolAvatar::OnCbnSelchangeComboPart8(){
	OnComboPartChange(APART_SHOES);
}
void CToolAvatar::OnCbnSelchangeComboPart9(){
	OnComboPartChange(APART_BODY);
}

void CToolAvatar::OnCbnSelchangeComboPalette1(){
	OnComboPaletteChange(APART_CAP);
}
void CToolAvatar::OnCbnSelchangeComboPalette2(){
	OnComboPaletteChange(APART_HAIR);
}
void CToolAvatar::OnCbnSelchangeComboPalette3(){
	OnComboPaletteChange(APART_FACE);
}
void CToolAvatar::OnCbnSelchangeComboPalette4(){
	OnComboPaletteChange(APART_NECK);
}
void CToolAvatar::OnCbnSelchangeComboPalette5(){
	OnComboPaletteChange(APART_COAT);
}
void CToolAvatar::OnCbnSelchangeComboPalette6(){
	OnComboPaletteChange(APART_PANTS);
}
void CToolAvatar::OnCbnSelchangeComboPalette7(){
	OnComboPaletteChange(APART_BELT);
}
void CToolAvatar::OnCbnSelchangeComboPalette8(){
	OnComboPaletteChange(APART_SHOES);
}
void CToolAvatar::OnCbnSelchangeComboPalette9(){
	OnComboPaletteChange(APART_BODY);
}
void CToolAvatar::OnBnClickedButtonPart1(){
	OnButtonSelectThumbnail(APART_CAP);
}
void CToolAvatar::OnBnClickedButtonPart2(){
	OnButtonSelectThumbnail(APART_HAIR);
}
void CToolAvatar::OnBnClickedButtonPart3(){
	OnButtonSelectThumbnail(APART_FACE);
}
void CToolAvatar::OnBnClickedButtonPart4(){
	OnButtonSelectThumbnail(APART_NECK);
}
void CToolAvatar::OnBnClickedButtonPart5(){
	OnButtonSelectThumbnail(APART_COAT);
}
void CToolAvatar::OnBnClickedButtonPart6(){
	OnButtonSelectThumbnail(APART_PANTS);
}
void CToolAvatar::OnBnClickedButtonPart7(){
	OnButtonSelectThumbnail(APART_BELT);
}
void CToolAvatar::OnBnClickedButtonPart8(){
	OnButtonSelectThumbnail(APART_SHOES);
}
void CToolAvatar::OnBnClickedButtonPart9(){
	OnButtonSelectThumbnail(APART_BODY);
}
void CToolAvatar::OnBnClickedButtonPrev(){
	CHECK_VALID(frame >= 0);
	CHECK_VALID(!moving);
	frame --;
	factory.changeFrame(frame);
	draw();
}
void CToolAvatar::OnBnClickedButtonNext(){
	CHECK_VALID(frame < maxFrame - 1);
	CHECK_VALID(!moving);
	frame ++;
	factory.changeFrame(frame);
	draw();
}
void CToolAvatar::OnBnClickedCancel(){
	ShowWindow(SW_HIDE);
}
void CToolAvatar::setAnimation(int f1, int f2, int f3, int f4, int f5, int f6, int f7, int f8, int f9, int f10, int f11, int f12, int f13, int f14, int f15, int f16){
	animation[0] = f1;
	animationLength = 1;
#define BAT_SET_ANIMATION(x) if(f##x != -1){animation[x-1] = f##x; animationLength = x;}
#define SET_ANIMATION(__sel,__di,__list) if(tempSelected==__sel){setAnimation##__list;}
	BAT_SET_ANIMATION(2);
	BAT_SET_ANIMATION(3);
	BAT_SET_ANIMATION(4);
	BAT_SET_ANIMATION(5);
	BAT_SET_ANIMATION(6);
	BAT_SET_ANIMATION(7);
	BAT_SET_ANIMATION(8);
	BAT_SET_ANIMATION(9);
	BAT_SET_ANIMATION(10);
	BAT_SET_ANIMATION(11);
	BAT_SET_ANIMATION(12);
	BAT_SET_ANIMATION(13);
	BAT_SET_ANIMATION(14);
	BAT_SET_ANIMATION(15);
	BAT_SET_ANIMATION(16);
}
void CToolAvatar::OnCbnSelchangeComboAction(){
	int tempSelected = GET_CTRL(CComboBox, IDC_COMBO_ACTION)->GetCurSel();
	if(tempSelected == 0){
		frame = 0;
		moving = false;
		draw();
	}else{
		moving = true;
	}
	setAnimation(0);
	if(factory.career == ACAREER_SM){
		SET_ANIMATION(1,"普通",(176,176,176,177,178));
		SET_ANIMATION(2,"战时",(90,91,92,93,94,95));
		SET_ANIMATION(3,"走动",(180,181,182,183,184,185,186,187));
		SET_ANIMATION(4,"跑动",(105,106,107,108,109,110,111,112));
		SET_ANIMATION(5,"攻击",(0,2,3,4,5,6,7,8,8,8,8));
		SET_ANIMATION(6,"Z键",(33,34,35,36,37,38,39,39,39,39));
		SET_ANIMATION(7,"释放",(75,76,77,78,79,80,81,82,82,82));
		SET_ANIMATION(8,"被攻击",(96,96,96,99,99,99));
		SET_ANIMATION(9,"倒地",(101,102,102,102,102,102,102,102));
	}else if(factory.career == ACAREER_SG){
		SET_ANIMATION(1,"普通",(0,1,2,3,4,5,6,7,8));
		SET_ANIMATION(2,"战时",(9,10,11,12));
		SET_ANIMATION(3,"走动",(13,14,15,16,17,18,19,20,21,22));
		SET_ANIMATION(4,"跑动",(151,152,153,154,155,156,157,158));
		SET_ANIMATION(5,"攻击",(48,49,50,51,52));
		SET_ANIMATION(6,"Z键",(48,49,50,51,52));
		SET_ANIMATION(7,"释放",(121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136));
		SET_ANIMATION(8,"被攻击",(139, 140));
		SET_ANIMATION(9,"倒地",(141, 142, 143));
	}else if(factory.career == ACAREER_GN){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
		SET_ANIMATION(2,"战时",(13, 14, 15, 16, 17, 18, 19, 20, 21, 22));
		SET_ANIMATION(3,"走动",(55, 56, 57, 58, 59, 60, 61, 62));
		SET_ANIMATION(4,"跑动",(103, 104, 105, 106, 107, 108, 109, 110));
		SET_ANIMATION(5,"攻击",(25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38));
		SET_ANIMATION(6,"Z键",(155, 156, 157, 158));
		SET_ANIMATION(7,"释放",(193, 194, 195, 196, 197));
		SET_ANIMATION(8,"被攻击",(121, 122, 123, 124));
		SET_ANIMATION(9,"倒地",(125, 126, 127));
	}else if(factory.career == ACAREER_GG){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
		SET_ANIMATION(2,"战时",(14, 15, 16, 17, 18, 19, 20));
		SET_ANIMATION(3,"走动",(68, 69, 70, 71, 72, 73, 74, 75));
		SET_ANIMATION(4,"跑动",(76, 77, 78, 79, 80, 71));
		SET_ANIMATION(5,"攻击",(22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35));
		SET_ANIMATION(6,"Z键",(111, 112, 113, 114, 115));
		SET_ANIMATION(7,"释放",(10, 11, 12, 13));
		SET_ANIMATION(8,"被攻击",(89, 90));
		SET_ANIMATION(9,"倒地",(91));
	}else if(factory.career == ACAREER_FT){
		SET_ANIMATION(1,"普通",(113, 114, 115, 116));
		SET_ANIMATION(2,"战时",(132, 133, 134, 135));
		SET_ANIMATION(3,"走动",(136, 137, 138, 139, 140, 141, 142, 143));
		SET_ANIMATION(4,"跑动",(39, 40, 41, 42, 43, 44, 45, 46));
		SET_ANIMATION(5,"攻击",(5, 6, 7, 8, 9));
		SET_ANIMATION(6,"Z键",(30, 31, 32, 33, 34, 35));
		SET_ANIMATION(7,"释放",(92, 93, 94, 95));
		SET_ANIMATION(8,"被攻击",(77, 78, 84, 85));
		SET_ANIMATION(9,"倒地",(79, 80, 81, 82, 83));
	}else if(factory.career == ACAREER_FM){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3));
		SET_ANIMATION(2,"战时",(12, 13, 14, 15));
		SET_ANIMATION(3,"走动",(4, 5, 6, 7, 8, 9, 10, 11));
		SET_ANIMATION(4,"跑动",(136, 137, 138, 139, 140, 141, 142, 143));
		SET_ANIMATION(5,"攻击",(28, 29, 30, 31, 32));
		SET_ANIMATION(6,"Z键",(64, 65, 66, 67, 68));
		SET_ANIMATION(7,"释放",(79, 80, 81, 82, 83, 84, 85));
		SET_ANIMATION(8,"被攻击",(74, 75));
		SET_ANIMATION(9,"倒地",(76, 77, 78));
	}else if(factory.career == ACAREER_MG){
		SET_ANIMATION(1,"普通",(10,11,12,13));
		SET_ANIMATION(2,"战时",(14,15,16,17));
		SET_ANIMATION(3,"走动",(0,1,2,3,4,5,6,7,8,9));
		SET_ANIMATION(4,"跑动",(18,19,20,21));
		SET_ANIMATION(5,"攻击",(109,110,111,112,113,113,113));
		SET_ANIMATION(6,"Z键",(114,115,116,117,118,118,118));
		SET_ANIMATION(7,"释放",(144,145,146,146,146,147));
		SET_ANIMATION(8,"被攻击",(128,128,129,129));
		SET_ANIMATION(9,"倒地",(133,134,134,134,134,134));
	}else if(factory.career == ACAREER_MM){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3, 4, 5, 6, 7));
		SET_ANIMATION(2,"战时",(8, 9, 10, 11, 12, 13, 14, 15, 16, 17));
		SET_ANIMATION(3,"走动",(18, 19, 20, 21, 22, 23, 24, 25, 26, 27));
		SET_ANIMATION(4,"跑动",(28, 29, 30, 31, 32, 33, 34, 35));
		SET_ANIMATION(5,"攻击",(60, 61, 62, 63, 64));
		SET_ANIMATION(6,"Z键",(60, 61, 62, 63, 64));
		SET_ANIMATION(7,"释放",(142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153));
		SET_ANIMATION(8,"被攻击",(175, 176));
		SET_ANIMATION(9,"倒地",(177, 178, 179));
	}else if(factory.career == ACAREER_PR){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3));
		SET_ANIMATION(2,"战时",(4, 5, 6, 7));
		SET_ANIMATION(3,"走动",(65, 66, 67, 68, 69, 70, 71, 72));
		SET_ANIMATION(4,"跑动",(73, 74, 75, 76, 77, 78));
		SET_ANIMATION(5,"攻击",(8, 9, 10, 11, 12, 13, 14, 15));
		SET_ANIMATION(6,"Z键",(31, 32, 33, 34, 35, 36, 37, 38, 39));
		SET_ANIMATION(7,"释放",(146, 147, 148, 149, 150, 151, 152, 153));
		SET_ANIMATION(8,"被攻击",(122, 123));
		SET_ANIMATION(9,"倒地",(124, 126, 126, 126));
	}else if(factory.career == ACAREER_PG){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3, 4, 5, 6, 7, 8));
		SET_ANIMATION(2,"战时",(9, 10, 11, 12));
		SET_ANIMATION(3,"走动",(13, 14, 15, 16, 17, 18, 19, 20));
		SET_ANIMATION(4,"跑动",(21, 22, 23, 24, 25, 26, 27, 28));
		SET_ANIMATION(5,"攻击",(23, 30, 31, 32));
		SET_ANIMATION(6,"Z键",(70, 71, 72, 73));
		SET_ANIMATION(7,"释放",(108, 109, 110, 111, 112));
		SET_ANIMATION(8,"被攻击",(51, 52));
		SET_ANIMATION(9,"倒地",(53, 54, 55));
	}else if(factory.career == ACAREER_TH){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11));
		SET_ANIMATION(2,"战时",(12, 13, 14, 15, 16, 17));
		SET_ANIMATION(3,"走动",(18, 19, 20, 21, 22, 23, 24, 25, 26));
		SET_ANIMATION(4,"跑动",(61, 62, 63, 64, 65, 66));
		SET_ANIMATION(5,"攻击",(67, 68, 69, 70, 71, 72));
		SET_ANIMATION(6,"Z键",(96, 97, 98, 99, 100));
		SET_ANIMATION(7,"释放",(32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45));
		SET_ANIMATION(8,"被攻击",(91, 92));
		SET_ANIMATION(9,"倒地",(93, 94, 95));
	}else if(factory.career == ACAREER_KN){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3, 4, 5));
		SET_ANIMATION(2,"战时",(6, 7, 8, 9, 10, 11));
		SET_ANIMATION(3,"走动",(12, 13, 14, 15, 16, 17, 18, 19, 20, 21));
		SET_ANIMATION(4,"跑动",(22, 23, 24, 25, 26, 27, 28, 29));
		SET_ANIMATION(5,"攻击",(51, 52, 53, 54, 55, 56, 57, 58, 59));
		SET_ANIMATION(6,"Z键",(182, 183, 184, 185, 186));
		SET_ANIMATION(7,"释放",(170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 171));
		SET_ANIMATION(8,"被攻击",(195, 196));
		SET_ANIMATION(9,"倒地",(197, 198, 199));
	}else if(factory.career == ACAREER_DL){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3));
		SET_ANIMATION(2,"战时",(4, 5, 6, 7));
		SET_ANIMATION(3,"走动",(8, 9, 10, 11, 12, 13, 14, 15, 16));
		SET_ANIMATION(4,"跑动",(17, 18, 19, 20, 21, 22, 23, 24));
		SET_ANIMATION(5,"攻击",(62, 63, 64, 65, 66));
		SET_ANIMATION(6,"Z键",(143, 144, 145, 146, 147, 148, 149));
		SET_ANIMATION(7,"释放",(158, 159, 160));
		SET_ANIMATION(8,"被攻击",(175, 176));
		SET_ANIMATION(9,"倒地",(177, 178, 179));
	}else if(factory.career == ACAREER_GB){
		SET_ANIMATION(1,"普通",(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
		SET_ANIMATION(2,"战时",(10, 11, 12, 13, 14));
		SET_ANIMATION(3,"走动",(15, 16, 17, 18, 19, 20, 21, 22));
		SET_ANIMATION(4,"跑动",(23, 24, 25, 26, 27, 28, 29, 30));
		SET_ANIMATION(5,"攻击",(76, 77, 78, 79));
		SET_ANIMATION(6,"Z键",(56, 57, 58, 59, 60, 61, 62));
		SET_ANIMATION(7,"释放",(141, 142, 143, 144));
		SET_ANIMATION(8,"被攻击",(145, 146));
		SET_ANIMATION(9,"倒地",(147, 148, 149));
	}
}
////////////
//绘制线程//
////////////
void CToolAvatar::draw(){
	matrix mat;
	factory.makeMatrix(basePoint,size(190,190),mat);
	canvas.fill(profile.getAvatarColor(0));
	canvas.putFore(mat);
	AfxBeginThread(drawThread, (PVOID)this);
}
UINT CToolAvatar::drawThread(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	CHECK_VALID_RETURN(!dlg->drawing);
	CHECK_VALID_RETURN(!dlg->loading);
	dlg->drawing = true;
	int i,j;
	int canw = 190;
	int canh = 190;
	CImage img;
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = dlg->GetDC();
	for(i=0;i<canw;i++){
		for(j=0;j<canh;j++){
			*(pst + pit*j + 4*i + 0) = dlg->canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = dlg->canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = dlg->canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,10,340);
	dlg->ReleaseDC(pDC);
	dlg->drawing = false;
	return 0;
}
UINT CToolAvatar::animationThread(void*para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	int localFrame = 0;
	int frame;
	while(true){
		while(dlg->moving){
			frame = dlg->animation[localFrame];
			dlg->factory.changeFrame(frame);
			dlg->draw();
			Sleep(dlg->profile.miniSecPerFrame);
			localFrame ++;
			if(localFrame >= dlg->animationLength)
				localFrame = 0;
		}
		Sleep(10);
	}
	return 0;
}
////////////
//生成线程//
////////////
void CToolAvatar::makeThumbnailBySingle(int newSelected){
	CHECK_VALID(newSelected < factory.partAlbum[displayPart].avatarList.size());
	IMGobject bodyIO;
	PICinfo bodyPI;
	matrix bodyMat;
	factory.partAlbum[APART_BODY].sourceNPK.IMGextract(0, bodyIO);
	bodyIO.PICgetInfo(getCareerRepresentativeFrame(factory.career), bodyPI);
	bodyIO.PICextract(getCareerRepresentativeFrame(factory.career), bodyMat);
	bodyMat.turnShield();
	str fileName;
	int tempSize,oldSize = thumbnailSize;
	avatarPart part = displayPart;
	for(tempSize = 0;tempSize<4;tempSize++){
		changeThumbnailSize(tempSize);
		matrix mat;
		factory.makeModel(mat, getCareerColor(factory.career), size(thumbnailWidth, thumbnailHeight), part, newSelected, 0, getAvatarModelOffset(factory.career, part), getCareerRepresentativeFrame(factory.career), &bodyPI, &bodyMat);
		fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, part) + "_" + CStrToStr(NumToCStr(factory.partAlbum[part].avatarList[newSelected].ID)) + ".PNG";
		KoishiImageTool::makePNG(mat, fileName);
	}
	changeThumbnailSize(oldSize);
}
void CToolAvatar::makeThumbnailByPart(){
	IMGobject bodyIO;
	PICinfo bodyPI;
	matrix bodyMat;
	factory.partAlbum[APART_BODY].sourceNPK.IMGextract(0, bodyIO);
	bodyIO.PICgetInfo(getCareerRepresentativeFrame(factory.career), bodyPI);
	bodyIO.PICextract(getCareerRepresentativeFrame(factory.career), bodyMat);
	bodyMat.turnShield();
	str fileName;
	int tempSize,tempSelected,oldSize = thumbnailSize;
	int totalSelect = factory.partAlbum[displayPart].avatarList.size();
	avatarPart part = displayPart;
	for(tempSelected = 0;tempSelected < totalSelect; tempSelected++){
		for(tempSize = 0;tempSize<4;tempSize++){
			changeThumbnailSize(tempSize);
			matrix mat;
			factory.makeModel(mat, getCareerColor(factory.career), size(thumbnailWidth, thumbnailHeight), part, tempSelected, 0, getAvatarModelOffset(factory.career, part), getCareerRepresentativeFrame(factory.career), &bodyPI, &bodyMat);
			fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, part) +"_" + CStrToStr(NumToCStr(factory.partAlbum[part].avatarList[tempSelected].ID)) + ".PNG";
			KoishiImageTool::makePNG(mat, fileName);
			double rate = (double)tempSelected/totalSelect +
				(double)tempSize/4/totalSelect;
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(1000*rate);
			GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"("+	DoubleToCStr(100*rate) +	L"％)生成"+GetTail(StrToCStr(fileName))+L"中。");
		}
	}
	changeThumbnailSize(oldSize);
}
void CToolAvatar::makeThumbnailByAll(){
	IMGobject bodyIO;
	PICinfo bodyPI;
	matrix bodyMat;
	factory.partAlbum[APART_BODY].sourceNPK.IMGextract(0, bodyIO);
	bodyIO.PICgetInfo(getCareerRepresentativeFrame(factory.career), bodyPI);
	bodyIO.PICextract(getCareerRepresentativeFrame(factory.career), bodyMat);
	bodyMat.turnShield();
	str fileName;
	int tempPart, tempSize,selected,oldSize = thumbnailSize;
	int totalSelect;
	for(tempPart = 1;tempPart < APART_MAXCOUNT; tempPart++){
		totalSelect = factory.partAlbum[tempPart].avatarList.size();
		for(selected = 0;selected < totalSelect; selected++){
			for(tempSize = 0;tempSize<4;tempSize++){
				changeThumbnailSize(tempSize);
				matrix mat;
				factory.makeModel(mat, getCareerColor(factory.career), size(thumbnailWidth, thumbnailHeight), (avatarPart)tempPart, selected, 0, getAvatarModelOffset(factory.career, (avatarPart)tempPart), getCareerRepresentativeFrame(factory.career), &bodyPI, &bodyMat);
				fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, (avatarPart)tempPart) +"_" + CStrToStr(NumToCStr(factory.partAlbum[(avatarPart)tempPart].avatarList[selected].ID)) + ".PNG";
				KoishiImageTool::makePNG(mat, fileName);
				mat.destory();
				double rate = (double)(tempPart-1)/(APART_MAXCOUNT-1) +
					(double)selected/totalSelect/(APART_MAXCOUNT-1) +
					(double)tempSize/totalSelect/(APART_MAXCOUNT-1)/4;
				GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(1000*rate);
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"("+	DoubleToCStr(100*rate) +	L"％)生成"+GetTail(StrToCStr(fileName))+L"中。");
			}
		}
	}
	changeThumbnailSize(oldSize);
}
UINT CToolAvatar::makeThumbnailThread(void*para){
	CToolAvatar *dlg = (CToolAvatar *)para;
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0, 1000);
	dlg->makeThumbnailByPart();
	dlg->drawThumbnail(dlg->page);
	GET_DLG_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"展示图生成完毕喵。");
	dlg->MessageBox(L"展示图更新完毕喵。",L"提示喵");
	return 0U;
}
UINT CToolAvatar::makeAllThumbnailThread(void*para){
	CToolAvatar *dlg = (CToolAvatar *)para;
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0, 1000);
	dlg->makeThumbnailByAll();
	dlg->drawThumbnail(dlg->page);
	GET_DLG_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"所有展示图生成完毕喵。");
	dlg->MessageBox(L"展示图更新完毕喵。",L"提示喵");
	return 0U;
}
UINT CToolAvatar::makeIconThread(void*para){
	CToolAvatar *dlg = (CToolAvatar *)para;
	str fileName = CStrToStr(dlg->profile.getAvatarPath()) + KoishiAvatar::getIconNPKName(dlg->factory.career);
	CString fileInfoName = dlg->profile.getIconPath(dlg->factory.career) + L"count.txt";
	int i, j, k;
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0, 1000);
	NPKobject no;
	CStdioFile file;
	file.Open(fileInfoName, CFile::modeCreate|CFile::modeWrite);
	if(!no.loadFile(fileName)){
		dlg->MessageBox(L"没能在时装资源库中找到图标文件喵："+StrToCStr(KoishiAvatar::getIconNPKName(dlg->factory.career))+"。",L"提示喵");
		return 0U;
	}
	for(i = 1;i<APART_MAXCOUNT;i++){
		std::vector<str> s = KoishiAvatar::getIconIMGName(dlg->factory.career, (KoishiAvatar::avatarPart)i);	//同部件图标有可能装入两个IMG中，获得IMG列表
		int id = 0;
		for(j = 0;j<s.size();j++){
			dword pos;
			if(no.find(s[j], pos)){
				IMGobject io;
				no.IMGextract(pos, io);
				for(k = 0;k<io.indexCount;k++){
					matrix iconMat;
					io.PICextract(k, iconMat);
					double rate = (double)(i-1)/(APART_MAXCOUNT-1) +
						(double)j/s.size()/(APART_MAXCOUNT-1) + 
						(double)k/io.indexCount/s.size()/(APART_MAXCOUNT-1);
					GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(1000*rate);
					GET_DLG_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"("+DoubleToCStr(100*rate) +	L"％)提取第"+NumToCStr(k)+"帧中。");
					KoishiImageTool::makePNG(iconMat, CStrToStr(dlg->profile.getIconPath(dlg->factory.career)) + KoishiAvatar::getAvatarPartIMGName((avatarPart)i) + "_" + CStrToStr(NumToCStr(id)) + ".PNG");
					iconMat.destory();
					id ++;
				}
				io.release();
			}
		}
		file.WriteString(StrToCStr(KoishiAvatar::getAvatarPartIMGName((avatarPart)i))+ L"," + NumToCStr(id)+L"\n");
	}
	file.Close();
	no.release();
	dlg->MessageBox(L"图标更新完毕喵。",L"提示喵");
	return 0U;
}
//////////////
//绘制展示图//
//////////////
bool CToolAvatar::loadImage(str fileNameWithoutExp, matrix &mat){
	str fileName = fileNameWithoutExp + ".png";
	if(KoishiImageTool::loadPNG(mat, fileName)){
		return true;
	}
	fileName = fileNameWithoutExp + ".bmp";
	if(KoishiImageTool::loadBMP(mat, fileName)){
		return true;
	}
	return false;
}
void CToolAvatar::loadIconCount(avatarCareer ac){
	iconCount.clear();
	for(int i = 0;i<APART_MAXCOUNT;i++){
		iconCount.push_back(0);
	}
	CString lineStr, countStr;
	CStdioFile file;
	if(file.Open(profile.getIconPath(ac) + L"count.txt", CFile::modeRead)){
		int line = 1;
		while(file.ReadString(lineStr)){
			AfxExtractSubString(countStr, lineStr, 1, ',');
			iconCount[line] = _ttoi(countStr);
			line ++;
		}
		file.Close();
	}
}
void CToolAvatar::drawThumbnail(int page){
	matrix canvas, mat;
	canvas.create(480, 720);
	canvas.fill(profile.getAvatarColor(1));
	//提取文件
	int i, j, id = 0;
	int row= 0, column = 0;
	int maxCount = factory.partAlbum[displayPart].avatarList.size();
	for(i = 0;i<thumbnailCountPerPage;i++){
		id = page*thumbnailCountPerPage + i;
		if(id >= maxCount){
			factory.makeButton(mat, profile.getAvatarColor(1), size(thumbnailWidth, thumbnailHeight), 2);
		}else{
			str fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, displayPart) + "_" + CStrToStr(NumToCStr(factory.partAlbum[displayPart].avatarList[id].ID));
			if(!loadImage(fileName, mat)){
				factory.makeButton(mat, profile.getAvatarColor(0), size(thumbnailWidth, thumbnailHeight), 3);
				
			}
			canvas.putFore(mat, LAY, point(column*thumbnailWidth, row*thumbnailHeight));
		}
		mat.destory();
		column ++;
		if(column == thumbnailCountPerRow){
			column = 0;
			row ++;
		}
		if(row == thumbnailCountRow - 1 && column >= thumbnailCountPerRow - 2)
			break;
		if(row >= thumbnailCountRow)
			break;
	}
	//画按钮
	matrix button1;
	factory.makeButton(button1, color(0x77, 0x99, 0xFF), size(thumbnailWidth, thumbnailHeight/2), 0);
	canvas.putFore(button1, LAY, point(720-2*thumbnailWidth, 480-thumbnailHeight));
	factory.makeButton(button1, color(0xFF, 0x99, 0x77), size(thumbnailWidth, thumbnailHeight/2), 2);
	canvas.putFore(button1, LAY, point(720-thumbnailWidth, 480-thumbnailHeight));
	factory.makeButton(button1, color(0x33, 0xCC, 0x66), size(thumbnailWidth, thumbnailHeight/2), 1);
	canvas.putFore(button1, LAY, point(720-2*thumbnailWidth, 480-thumbnailHeight/2));
	factory.makeButton(button1, color(0x66, 0xCC, 0x33), size(thumbnailWidth, thumbnailHeight/2), 3);
	canvas.putFore(button1, LAY, point(720-thumbnailWidth, 480-thumbnailHeight/2));
	//画选择标记
	matrix mark(thumbnailHeight, thumbnailWidth);
	mark.fill(color(0x66, 0xFF, 0xFF, 0xFF));
	int selected = cbPart[displayPart]->GetCurSel() - 1;
	int rn1 = page*thumbnailCountPerPage;
	int rn2 = (page + 1)*thumbnailCountPerPage - 1;
	if(selected >= rn1 && selected <= rn2){
		selected %= thumbnailCountPerPage;
		canvas.putFore(mark, LAY, point(thumbnailWidth * (selected % thumbnailCountPerRow), thumbnailHeight * (selected / thumbnailCountPerRow)));
	}
	CImage img;
	img.Create(720, 480, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<720;i++){
		for(j=0;j<480;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,210,70);
	ReleaseDC(pDC);
}
void CToolAvatar::drawIconByAvatar(int page){
	matrix canvas, mat, quesMark;
	canvas.create(480, 720);
	canvas.fill(profile.getAvatarColor(1));
	//提取文件
	int i, j, id, fileCount = 0;
	int row= 0, column = 0;
	int maxCount = factory.partAlbum[displayPart].bigramList.size();
	KoishiExpand::KoishiMarkTool::StrMatLarge("?", quesMark, color(0xFF, 0xFF, 0xFF));
	for(i = 0;i<380;i++){
		id = page*380 + i;
		if(id >= maxCount){
			//越界
			factory.makeButton(mat, profile.getAvatarColor(1), size(30, 30), 2);
			//canvas.putFore(mat, LAY, point(column*30, row*30));
		}else{
			avatarBigram ab = factory.partAlbum[displayPart].bigramList[id];
			DictAvatarContent dac = dict.findTerm(factory.career, displayPart, ab.ID, ab.isTN, ab.paletteID);
			if(dac.size() == 0){
				//辞典里未找到对应图标
				factory.makeButton(mat, color(0,0,0), size(30,30), 2);
				mat.putFore(quesMark, LAY, point(11,11));
				canvas.putFore(mat, LAY, point(column*30, row*30));
			}else{
				str fileName = CStrToStr(profile.getIconPath(factory.career)) + getAvatarPartIMGName(displayPart)+"_"+CStrToStr(NumToCStr(dac[0].iconID));
				if(!loadImage(fileName, mat)){
					//辞典里找到但是图标库中未找到
					factory.makeButton(mat, profile.getAvatarColor(0), size(30, 30), 3);
					canvas.putFore(mat, LAY, point(column*30, row*30));
				}else{
					//辞典&图标库都找到
					canvas.putFore(mat, LAY, point(column*30+1, row*30+1));
				}
			}
		}
		mat.destory();
		column ++;
		if(column == 24){
			column = 0;
			row ++;
		}
		if(row == 15 && column >= 20)
			break;
		if(row >= 16)
			break;
	}
	//画按钮
	matrix button1;
	factory.makeButton(button1, color(0x77, 0x99, 0xFF), size(30, 30), 0);
	canvas.putFore(button1, LAY, point(720-30*4, 480-30));
	factory.makeButton(button1, color(0xFF, 0x99, 0x77), size(30, 30), 1);
	canvas.putFore(button1, LAY, point(720-30*3, 480-30));
	factory.makeButton(button1, color(0x33, 0xCC, 0x66), size(30, 30), 2);
	canvas.putFore(button1, LAY, point(720-30*2, 480-30));
	factory.makeButton(button1, color(0x66, 0xCC, 0x33), size(30, 30), 3);
	canvas.putFore(button1, LAY, point(720-30*1, 480-30));
	//画选择标记
	matrix mark(30, 30);
	mark.fill(color(0x66, 0xFF, 0xFF, 0xFF));
	int tempSelected = cbPart[displayPart]->GetCurSel() - 1;
	int rn1 = page*380;
	int rn2 = (page + 1)*380 - 1;
	if(tempSelected >= rn1 && tempSelected <= rn2){
		tempSelected %= 380;
		canvas.putFore(mark, LAY, point(30 * (tempSelected % 24), 30 * (tempSelected / 24)));
	}
	CImage img;
	img.Create(720, 480, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<720;i++){
		for(j=0;j<480;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,210,70);
	ReleaseDC(pDC);
}
void CToolAvatar::drawIconByIcon(int page){
	matrix canvas, mat, unmappedMark1, unmappedMark2;
	canvas.create(480, 720);	//每行24个，16行，380个（因为有4个功能键）
	canvas.fill(profile.getAvatarColor(1));
	int i, j, id;
	int row= 0, column = 0;
	KoishiExpand::KoishiMarkTool::StrMatLarge("N", unmappedMark1, color(0xFF, 0xFF, 0xFF, 0));
	KoishiExpand::KoishiMarkTool::StrMatLarge("N", unmappedMark2, color(0xFF, 0xFF, 0, 0xFF));
	unmappedMark2.expand(0, 1, 1, 0);
	unmappedMark2.putFore(unmappedMark1, LAY, point(0, 1));
	for(i = 0;i<380;i++){
		id = page*380 + i;
		if(id >= iconCount[displayPart]){
			//越界区域
			factory.makeButton(mat, profile.getAvatarColor(1), size(30, 30), 2);
		}else{
			str fileName = CStrToStr(profile.getIconPath(factory.career)) + getAvatarPartIMGName(displayPart)+"_"+CStrToStr(NumToCStr(id));
			if(!loadImage(fileName, mat)){
				//未读出区域
				factory.makeButton(mat, profile.getAvatarColor(0), size(30, 30), 3);
				canvas.putFore(mat, LAY, point(column*30, row*30));
			}else{
				if(dict.findPos(factory.career, displayPart, id).size() == 0){
					mat.putFore(unmappedMark2, LAY, point(0,0));
				}
				canvas.putFore(mat, LAY, point(column*30+1, row*30+1));
			}
		}
		column ++;
		if(column == 24){
			column = 0;
			row ++;
		}
		if(row == 15 && column >= 20)
			break;
		if(row >= 16)
			break;
	}
	//画按钮
	matrix button1;
	factory.makeButton(button1, color(0x77, 0x99, 0xFF), size(30, 30), 0);
	canvas.putFore(button1, LAY, point(720-30*4, 480-30));
	factory.makeButton(button1, color(0xFF, 0x99, 0x77), size(30, 30), 1);
	canvas.putFore(button1, LAY, point(720-30*3, 480-30));
	factory.makeButton(button1, color(0x33, 0xCC, 0x66), size(30, 30), 2);
	canvas.putFore(button1, LAY, point(720-30*2, 480-30));
	factory.makeButton(button1, color(0x66, 0xCC, 0x33), size(30, 30), 3);
	canvas.putFore(button1, LAY, point(720-30*1, 480-30));
	//画选择标记
	matrix mark(30, 30);
	mark.fill(color(0x66, 0xFF, 0xFF, 0xFF));
	int tempSelected = cbPart[displayPart]->GetCurSel() - 1;
	int rn1 = page*380;
	int rn2 = (page + 1)*380 - 1;
	if(tempSelected >= rn1 && tempSelected <= rn2){
		tempSelected %= 380;
		canvas.putFore(mark, LAY, point(30 * (tempSelected % 24), 30 * (tempSelected / 24)));
	}
	CImage img;
	img.Create(720, 480, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<720;i++){
		for(j=0;j<480;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,210,70);
	ReleaseDC(pDC);
}
void CToolAvatar::changeThumbnailSize(int tSize){
	thumbnailSize = tSize;
	switch(tSize){
	case 0:
		//小
		thumbnailWidth = 60;
		thumbnailHeight = 80;
		thumbnailCountPerRow = 12;
		thumbnailCountRow = 6;
		thumbnailCountPerPage = 70;
		break;
	case 1:
		//中
		thumbnailWidth = 72;
		thumbnailHeight = 96;
		thumbnailCountPerRow = 10;
		thumbnailCountRow = 5;
		thumbnailCountPerPage = 48;
		break;
	case 2:
		//大
		thumbnailWidth = 90;
		thumbnailHeight = 120;
		thumbnailCountPerRow = 8;
		thumbnailCountRow = 4;
		thumbnailCountPerPage = 30;
		break;
	case 3:
		//巨大
		thumbnailWidth = 120;
		thumbnailHeight = 160;
		thumbnailCountPerRow = 6;
		thumbnailCountRow = 3;
		thumbnailCountPerPage = 16;
		break;
	case 4:
		//图标
		thumbnailWidth = 30;
		thumbnailHeight = 30;
		thumbnailCountPerRow = 24;
		thumbnailCountRow = 16;
		thumbnailCountPerPage = 380;
		break;
	}
}

//////////////////////////////////////////////////
void CToolAvatar::OnCbnSelchangeComboCareer(){
	// TODO: 在此添加控件通知处理程序代码
	CHECK_VALID(GET_CTRL(CComboBox, IDC_COMBO_CAREER)->GetCurSel()>0);
	factory.clear();
	factory.setPath(CStrToStr(profile.getAvatarPath()));
	factory.setCarrer((avatarCareer)(GET_CTRL(CComboBox, IDC_COMBO_CAREER)->GetCurSel()));
	AfxBeginThread(loadNPKThread, this);
}
UINT CToolAvatar::loadNPKThread(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	dlg->loading = true;
	int i, j;
	CString temp;
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_DLG_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"导入NPK资源中。");
	GET_DLG_CTRL(CButton, IDC_RADIO_DISPLAY1)->SetCheck(1);
	GET_DLG_CTRL(CButton, IDC_RADIO_DISPLAY2)->SetCheck(0);
	GET_DLG_CTRL(CButton, IDC_RADIO_DISPLAY3)->SetCheck(0);
	dlg->displayStyle = 0;
	for(i=1;i<=9;i++){
		if(dlg->factory.loadNPK((avatarPart)i)){
			dlg->cbPart[i]->ResetContent();
			dlg->cbPart[i]->AddString(L"未选择");
			for(j = 0;j <dlg->factory.partAlbum[i].avatarList.size(); j++){
				avatar av = dlg->factory.partAlbum[i].avatarList[j];
				CString str = av.isTN ? L"(TN)":L"";
				str += StrToCStr(getAvatarIDString(av.ID));
				if(av.v6palette >= 1){
					str += L"[×" + NumToCStr(av.v6palette)+L"]";
				}
				dlg->cbPart[i]->AddString(str);
			}
			if(i == APART_BODY || i == APART_COAT || i == APART_PANTS || i == APART_SHOES || i == APART_HAIR){
				dlg->factory.changeIMGByID((avatarPart)i, 0);
				dlg->cbPart[i]->SetCurSel(dlg->factory.partAlbum[i].selected+1);
				dlg->OnComboPartChange((avatarPart)i);
			}else{
				dlg->factory.changeIMG((avatarPart)i, -1);
				dlg->cbPart[i]->SetCurSel(0);
				dlg->OnComboPartChange((avatarPart)i);
			}
			if(i == APART_BODY){
				point basePt;
				dlg->factory.partAlbum[APART_BODY].getBasePoint(ALAYER_UD, basePt);
				int picW = dlg->factory.partAlbum[APART_BODY].layerMatrix[ALAYER_UD].getWidth();
				int picH = dlg->factory.partAlbum[APART_BODY].layerMatrix[ALAYER_UD].getHeight();
				dlg->basePoint = basePt - point(100, 100) + point(picW/2, picH/2);
				dlg->maxFrame = dlg->factory.partAlbum[APART_BODY].layerIMG[ALAYER_UD].indexCount;
			}
		}else{
			dlg->cbPart[i]->ResetContent();
			dlg->cbPart[i]->AddString(L"未找到资源");
			dlg->cbPart[i]->SetCurSel(0);
		}
		GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(i*1000/9);
	}
	GET_DLG_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"导入完毕。");
	dlg->loading = false;
	dlg->draw();
	dlg->drawThumbnail(dlg->page = 0);
	return 0;
}
/////////////////////////////////////////////////
void CToolAvatar::changeDisplayStyle(int newDisplayStyle){
	//更改显示模式
	int i, j;
	switch(newDisplayStyle){
	case 0:
		for(i=1;i<=9;i++){
			if(factory.partAlbum[i].valid){
				//计算新选项
				long newSelected, newSelectedPalette;
				selectionTransform((avatarPart)i, displayStyle, newDisplayStyle,
					cbPart[i]->GetCurSel() - 1, cbPalette[i]->GetCurSel(),
					newSelected, newSelectedPalette);
				//更新选项卡
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未选择");
				for(j = 0;j <factory.partAlbum[i].avatarList.size(); j++){
					avatar av = factory.partAlbum[i].avatarList[j];
					CString str = av.isTN ? L"(TN)":L"";
					str += StrToCStr(getAvatarIDString(av.ID));
					if(av.v6palette >= 1){
						str += L"[×" + NumToCStr(av.v6palette)+L"]";
					}
					cbPart[i]->AddString(str);
				}
				//使用新的选项值
				cbPart[i]->SetCurSel(newSelected+1);
				if(newSelected >= 0 && factory.partAlbum[i].avatarList[newSelected].v6palette > 0){
					cbPalette[i]->ResetContent();
					for(j = 0;j<factory.partAlbum[i].avatarList[newSelected].v6palette;j++){
						cbPalette[i]->AddString(L"P"+NumToCStr(j));
					}
					cbPalette[i]->SetCurSel(0);
					if(newSelectedPalette < factory.partAlbum[i].avatarList[newSelected].v6palette)
						cbPalette[i]->SetCurSel(newSelectedPalette);
				}else{
					cbPalette[i]->ResetContent();
					cbPalette[i]->AddString(L"NA");
					cbPalette[i]->SetCurSel(0);
				}
			}else{
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未找到资源");
				cbPart[i]->SetCurSel(0);
				cbPalette[i]->ResetContent();
				cbPalette[i]->AddString(L"NA");
				cbPalette[i]->SetCurSel(0);
			}
		}
		break;
	case 1:
		for(i=1;i<=9;i++){
			if(factory.partAlbum[i].valid){
				//计算新选项
				long newSelected, newSelectedPalette;
				selectionTransform((avatarPart)i, displayStyle, newDisplayStyle,
					cbPart[i]->GetCurSel() - 1, cbPalette[i]->GetCurSel(),
					newSelected, newSelectedPalette);
				//变换
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未选择");
				for(j = 0;j <factory.partAlbum[i].bigramList.size(); j++){
					DictAvatarContent t = dict.findTerm(factory.career, (avatarPart)i, 
						factory.partAlbum[i].bigramList[j].ID,
						factory.partAlbum[i].bigramList[j].isTN,
						factory.partAlbum[i].bigramList[j].paletteID);
					if(t.size() == 0){
						cbPart[i]->AddString(NumToCStr(factory.partAlbum[i].bigramList[j].ID)+L"号装扮"+ (factory.partAlbum[i].bigramList[j].paletteID == -1?L"":NumToCStr(factory.partAlbum[i].bigramList[j].paletteID)));
					}else if(t.size() == 1){
						cbPart[i]->AddString(t[0].avatarName);
					}else{
						cbPart[i]->AddString(t[0].avatarName + L" 等");
					}
				}
				//更新选项卡
				cbPart[i]->SetCurSel(newSelected+1);
				cbPalette[i]->ResetContent();
				cbPalette[i]->AddString(L"NA");
				cbPalette[i]->SetCurSel(0);
			}else{
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未找到资源");
				cbPart[i]->SetCurSel(0);
			}
		}
		break;
	case 2:
		loadIconCount(factory.career);	
		for(i=1;i<=9;i++){
			if(factory.partAlbum[i].valid){
				//计算新选项
				long newSelected, newSelectedPalette;
				selectionTransform((avatarPart)i, displayStyle, newDisplayStyle,
					cbPart[i]->GetCurSel() - 1, cbPalette[i]->GetCurSel(),
					newSelected, newSelectedPalette);
				//变换
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未选择");
				for(j = 0;j <iconCount[i]; j++){
					DictAvatarContent t = dict.findTerm(factory.career, (avatarPart)i, j);
					if(t.size() == 0){
						cbPart[i]->AddString(L"未对应的"+NumToCStr(j));
					}else if(t.size() == 1){
						cbPart[i]->AddString(t[0].avatarName);
					}else{
						cbPart[i]->AddString(t[0].avatarName + L" 等");
					}
				}
				cbPart[i]->SetCurSel(0);
				//更新选项卡
				cbPart[i]->SetCurSel(newSelected+1);
				cbPalette[i]->ResetContent();
				cbPalette[i]->AddString(L"NA");
				cbPalette[i]->SetCurSel(0);
			}else{
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未找到资源");
				cbPart[i]->SetCurSel(0);
			}
		}
		break;
	}
}
void CToolAvatar::selectionTransform(avatarPart ap, 
	int oldDisplayStyle, int newDisplayStyle, 
	long oldSelected, long oldSelectedPalette,
	long &newSelected, long &newSelectedPalette){
	if(oldSelected < 0 || oldSelectedPalette < 0){
		newSelected = -1;
		newSelectedPalette = 0;
		return;
	}
	if(oldDisplayStyle == 0 && newDisplayStyle == 1){
		newSelected = factory.partAlbum[ap].avatarPosAtBigramList[oldSelected][oldSelectedPalette];
		newSelectedPalette = 0;
	}
	if(oldDisplayStyle == 1 && newDisplayStyle == 0){
		avatarBigram ab = factory.partAlbum[ap].bigramList[oldSelected];
		newSelected = ab.originPos;
		newSelectedPalette = ab.paletteID;
	}
	if(oldDisplayStyle == 0 && newDisplayStyle == 2){
		avatar av = factory.partAlbum[ap].avatarList[oldSelected];
		DictAvatarContent termList = dict.findTerm(factory.career, ap, av.ID, av.isTN, oldSelectedPalette);
		if(termList.size() == 0){
			newSelected = -1;
			newSelectedPalette = 0;
		}else{
			newSelected = termList[0].iconID;
			newSelectedPalette = 0;
		}
	}
	if(oldDisplayStyle == 2 && newDisplayStyle == 0){
		DictAvatarContent termList = dict.findTerm(factory.career, ap, oldSelected);
		if(termList.size() == 0){
			newSelected = -1;
			newSelectedPalette = 0;
		}else{
			newSelected = factory.partAlbum[ap].findPosByID(termList[0].ID, termList[0].isTN);
			newSelectedPalette = termList[0].paletteID;
		}
	}
	if(oldDisplayStyle == 1 && newDisplayStyle == 2){
		avatarBigram ab = factory.partAlbum[ap].bigramList[oldSelected];
		DictAvatarContent termList = dict.findTerm(factory.career, ap, ab.ID, ab.isTN, ab.paletteID);
		if(termList.size() == 0){
			newSelected = -1;
			newSelectedPalette = 0;
		}else{
			newSelected = termList[0].iconID;
			newSelectedPalette = 0;
		}
	}
	if(oldDisplayStyle == 2 && newDisplayStyle == 1){
		DictAvatarContent termList = dict.findTerm(factory.career, ap, oldSelected);
		if(termList.size() == 0){
			newSelected = -1;
			newSelectedPalette = 0;
		}else{
			long pos = factory.partAlbum[ap].findPosByID(termList[0].ID, termList[0].isTN);
			long posPal = termList[0].paletteID;
			newSelected = factory.partAlbum[ap].avatarPosAtBigramList[pos][posPal];
			newSelectedPalette = 0;
		}
	}
}
void CToolAvatar::OnBnClickedRadioDisplay1(){
	// TODO: 切换展示图模式
	changeDisplayStyle(0);
	displayStyle = 0;
	drawThumbnail(page = 0);
}


void CToolAvatar::OnBnClickedRadioDisplay2(){
	// TODO: 切换图标模式，按IMG排列
	changeDisplayStyle(1);
	displayStyle = 1;
	drawIconByAvatar(page = 0);
}


void CToolAvatar::OnBnClickedRadioDisplay3(){
	// TODO: 切换图标模式，按图标排列
	changeDisplayStyle(2);
	displayStyle = 2;
	drawIconByIcon(page = 0);
}

void CToolAvatar::OnComboPartChange(avatarPart ap){
	selected = cbPart[ap]->GetCurSel()-1;
	switch(displayStyle){
	case 0:
		if(selected == -1){
			GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已脱下喵。");
			factory.changeIMG(ap, -1);
		}else{
			GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已切换装扮喵。");
			factory.changeIMG(ap, selected);
			page = selected/thumbnailCountPerPage;
		}
		drawThumbnail(page);
		//更新调色板可选项
		if(selected >= 0 && factory.partAlbum[ap].avatarList[selected].v6palette > 0){
			cbPalette[ap]->ResetContent();
			for(int i = 0;i<factory.partAlbum[ap].avatarList[selected].v6palette;i++){
				cbPalette[ap]->AddString(L"P"+NumToCStr(i));
			}
			cbPalette[ap]->SetCurSel(0);
		}else{
			cbPalette[ap]->ResetContent();
			cbPalette[ap]->AddString(L"NA");
			cbPalette[ap]->SetCurSel(0);
		}
		break;
	case 1:
		if(selected == -1){
			GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已脱下喵。");
			factory.changeIMG(ap, -1);
		}else{
			GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已切换装扮喵。");
			factory.changeIMG(ap, factory.partAlbum[ap].bigramList[selected].originPos);
			factory.partAlbum[ap].changePalette(factory.partAlbum[ap].bigramList[selected].paletteID);
			page = selected/380;
		}
		drawIconByAvatar(page);
		break;
	case 2:
		if(selected == -1){
			GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已脱下喵。");
			factory.changeIMG(ap, -1);
		}else{
			DictAvatarContent t = dict.findTerm(factory.career, ap, selected);
			if(t.size() == 0){
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"辞典里无对应装扮喵。");
				factory.changeIMG(ap, -1);
				factory.partAlbum[ap].changePalette(0);
			}else if(t.size() == 1){
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已切换装扮喵。");
				long pos = factory.partAlbum[ap].findPosByID(t[0].ID, t[0].isTN);
				factory.changeIMG(ap, pos);
				factory.partAlbum[ap].changePalette(t[0].paletteID);
			}else{
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"辞典里有多个装扮对应喵。");
				long pos = factory.partAlbum[ap].findPosByID(t[0].ID, t[0].isTN);
				factory.changeIMG(ap, pos);
				factory.partAlbum[ap].changePalette(t[0].paletteID);
			}
		}
		drawIconByIcon(page);
		break;
	}
	if(!moving)
		draw();
}
void CToolAvatar::OnComboPaletteChange(avatarPart ap){
	CHECK_VALID(displayStyle == 0);
	int selected = cbPalette[ap]->GetCurSel();
	factory.partAlbum[ap].changePalette(selected);
	if(!moving)
		draw();
}
void CToolAvatar::OnCbnSelchangeComboMultcolor(){
	CHECK_VALID(displayStyle == 0);
	int selected = GET_CTRL(CComboBox, IDC_COMBO_MULTCOLOR)->GetCurSel();
	CHECK_VALID(selected > 0);
	for(int i = 1 ; i < ::APART_BODY; i++){
		int maxCount = cbPalette[i]->GetCount();
		if(selected - 1 >= maxCount)
			continue;
		factory.partAlbum[i].changePalette(selected - 1);
		cbPalette[i]->SetCurSel(selected - 1);
	}
	if(!moving)
		draw();
}

//点击对应的按钮
void CToolAvatar::OnButtonSelectThumbnail(avatarPart ap){
	displayPart = ap;
	switch(displayStyle){
	case 0:
		drawThumbnail(page = 0);
		break;
	case 1:
		drawIconByAvatar(page = 0);
		break;
	case 2:
		drawIconByIcon(page = 0);
		break;
	}
}

void CToolAvatar::InvokeMappingDialog1(long getSelected){
	ModalAvatarMap1 dlg;
	if(getSelected == -1){
		getSelected = 0;
	}
	if(displayStyle== 0){
		dlg.in.selected = getSelected;
		dlg.in.selectedPalette = cbPalette[displayPart]->GetCurSel();
	}else{
		avatarBigram ab = factory.partAlbum[displayPart].bigramList[getSelected];
		dlg.in.selected = ab.originPos;
		dlg.in.selectedPalette = ab.paletteID;
	}
	loadIconCount(factory.career);	
	dlg.in.maxIconCount = iconCount[displayPart];
	dlg.in.ptrFactory = &factory;
	dlg.in.ptrDict = &dict;
	dlg.in.part = displayPart;
	dlg.in.ptrProfile = &profile;
	dlg.DoModal();
}

void CToolAvatar::InvokeMappingDialog2(long getSelected){
	ModalAvatarMap2 dlg;
	dlg.in.iconID = getSelected;
	dlg.in.ptrFactory = &factory;
	dlg.in.ptrDict = &dict;
	dlg.in.part = displayPart;
	dlg.in.ptrProfile = &profile;
	dlg.DoModal();
}

CPoint CToolAvatar::getWinMouseAxis(){
	CPoint myPoint;
    GetCursorPos(&myPoint); //鼠标位置
	ScreenToClient(&myPoint);
	return myPoint;
}

BOOL CToolAvatar::getMouseClicked(int &checkSelected){
	CPoint myPoint = getWinMouseAxis();
	point xy(myPoint.x-210, myPoint.y-70);
	if(displayStyle == 0){
		checkSelected = xy.Y / thumbnailHeight * thumbnailCountPerRow + xy.X / thumbnailWidth;
		//点击向上箭头
		if(xy.X > 720 - thumbnailWidth*2 && xy.Y > 480 - thumbnailHeight)
			checkSelected = 1000;
		//点击向下箭头
		if(xy.X > 720 - thumbnailWidth*2 && xy.Y > 480 - thumbnailHeight/2)
			checkSelected = 1001;
		//点击×
		if(xy.X > 720 - thumbnailWidth && xy.Y > 480 - thumbnailHeight)
			checkSelected = 1002;
		//点击刷新菜单
		if(xy.X > 720 - thumbnailWidth && xy.Y > 480 - thumbnailHeight/2)
			checkSelected = 1003;
	}else{
		checkSelected = xy.Y / 30 * 24 + xy.X / 30;
		if(xy.X > 600 && xy.Y > 450)
			checkSelected = 1000;
		if(xy.X > 630 && xy.Y > 450)
			checkSelected = 1001;
		if(xy.X > 660 && xy.Y > 450)
			checkSelected = 1002;
		if(xy.X > 690 && xy.Y > 450)
			checkSelected = 1003;
	}
	return myPoint.x >= 210 && myPoint.y >= 70 && myPoint.x < 930 && myPoint.y < 550;
}

void CToolAvatar::OnLButtonDown(UINT nFlags, CPoint point){
	CDialogEx::OnLButtonDown(nFlags, point);
	int checkSelected;
	if(getMouseClicked(checkSelected)){
		switch(displayStyle){
		case 0:
			//展示图模式
			if(checkSelected < 1000){
				int newSelected = thumbnailCountPerPage * page + checkSelected;
				if(newSelected >= factory.partAlbum[displayPart].avatarList.size()){
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"这里什么都没有喵。");
					return ;
				}else{
					selected = newSelected;
					cbPart[displayPart]->SetCurSel(selected + 1);
					OnComboPartChange(displayPart);
				}
			}else if(checkSelected == 1000){
				//向上翻页
				if(page > 0){
					page --;
					drawThumbnail(page);
				}else{
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已是第一页喵。");
					return;
				}
			}else if(checkSelected == 1001){
				//向下翻页
				if((page + 1)* thumbnailCountPerPage < factory.partAlbum[displayPart].avatarList.size()){
					page ++;
					drawThumbnail(page);
				}else{
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已是最后一页喵。");
					return;
				}
			}else if(checkSelected == 1002){
				//取消该部件显示
				selected = -1;
				cbPart[displayPart]->SetCurSel(0);
				OnComboPartChange(displayPart);
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已脱下喵。");
			}else if(checkSelected == 1003){
				//重绘
				drawThumbnail(page);
			}
			break;
		case 1:
			//图标模式
			if(checkSelected < 1000){
				int newSelected = 380 * page + checkSelected;
				if(newSelected >= factory.partAlbum[displayPart].bigramList.size()){
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"这里什么都没有喵。");
					return ;
				}else{
					selected = newSelected;
					cbPart[displayPart]->SetCurSel(selected + 1);
					OnComboPartChange(displayPart);
				}
			}else if(checkSelected == 1000){
				//向上翻页
				if(page > 0){
					page --;
					drawIconByAvatar(page);
				}else{
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已是第一页喵。");
					return;
				}
			}else if(checkSelected == 1001){
				//向下翻页
				if((page + 1) * 380 < factory.partAlbum[displayPart].bigramList.size()){
					page ++;
					drawIconByAvatar(page);
				}else{
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已是最后一页喵。");
					return;
				}
			}else if(checkSelected == 1002){
				//取消该部件显示
				selected = -1;
				cbPart[displayPart]->SetCurSel(0);
				OnComboPartChange(displayPart);
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已脱下喵。");
			}else if(checkSelected == 1003){
				//重绘
				drawIconByAvatar(page);
			}
			break;
		case 2:
			//图标模式
			if(checkSelected < 1000){
				int newSelected = 380 * page + checkSelected;
				if(newSelected >= iconCount[displayPart]){
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"这里什么都没有喵。");
					return ;
				}else{
					selected = newSelected;
					cbPart[displayPart]->SetCurSel(selected + 1);
					OnComboPartChange(displayPart);
				}
			}else if(checkSelected == 1000){
				//向上翻页
				if(page > 0){
					page --;
					drawIconByIcon(page);
				}else{
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已是第一页喵。");
					return;
				}
			}else if(checkSelected == 1001){
				//向下翻页
				if((page + 1) * 380 < iconCount[displayPart]){
					page ++;
					drawIconByIcon(page);
				}else{
					GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已是最后一页喵。");
					return;
				}
			}else if(checkSelected == 1002){
				//取消该部件显示
				selected = -1;
				cbPart[displayPart]->SetCurSel(0);
				OnComboPartChange(displayPart);
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已脱下喵。");
			}else if(checkSelected == 1003){
				//重绘
				drawIconByIcon(page);
				GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"已刷新喵。");
			}
			break;
		}
	}
}

void CToolAvatar::OnRButtonDown(UINT nFlags, CPoint point){
	CDialogEx::OnRButtonDown(nFlags, point);
	int checkSelected;
	if(getMouseClicked(checkSelected)){
		OnLButtonDown(nFlags, point);
		if(checkSelected < 1000){
			CMenu menu, *pPopup;  
			menu.LoadMenu(IDR_MENU_AVATAR);
			if(displayStyle == 0){
				int newSelected = thumbnailCountPerPage * page + checkSelected;
				if(newSelected < factory.partAlbum[displayPart].avatarList.size()){
					pPopup = menu.GetSubMenu(0);
					CPoint myPoint; 
					ClientToScreen(&myPoint);  
					GetCursorPos(&myPoint); //鼠标位置  
					pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
				}
			}
			if(displayStyle == 1){
				int newSelected = 380 * page + checkSelected;
				if(newSelected < factory.partAlbum[displayPart].bigramList.size()){
					pPopup = menu.GetSubMenu(3);
					CPoint myPoint; 
					ClientToScreen(&myPoint);  
					GetCursorPos(&myPoint); //鼠标位置  
					pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
				}
			}
			if(displayStyle == 2){
				int newSelected = 380 * page + checkSelected;
				if(newSelected < iconCount[displayPart]){
					pPopup = menu.GetSubMenu(2);
					CPoint myPoint; 
					ClientToScreen(&myPoint);  
					GetCursorPos(&myPoint); //鼠标位置  
					pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
				}
			}
		}else if(checkSelected == 1003){
			CMenu menu, *pPopup;  
			menu.LoadMenu(IDR_MENU_AVATAR);  
			pPopup = menu.GetSubMenu(1);  
			CPoint myPoint; 
			ClientToScreen(&myPoint);  
			GetCursorPos(&myPoint); //鼠标位置  
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
		}
	}
}


void CToolAvatar::OnMenuAvatarSetName(){
	// TODO: 设置展示图
	makeThumbnailBySingle(selected);
	drawThumbnail(page);
}
void CToolAvatar::OnMenuAvatarSetIcon(){
	InvokeMappingDialog1(selected);
}

void CToolAvatar::OnMenuAvatarSetAvatar2(){
	InvokeMappingDialog1(selected);
}

void CToolAvatar::OnMenuAvatarSetavatar(){
	InvokeMappingDialog2(selected);
}

void CToolAvatar::OnMenuAvatarSizeSmall(){
	changeThumbnailSize(0);
	drawThumbnail(page);
}
void CToolAvatar::OnMenuAvatarSizeMedium(){
	changeThumbnailSize(1);
	drawThumbnail(page);
}
void CToolAvatar::OnMenuAvatarSizeLarge(){
	changeThumbnailSize(2);
	drawThumbnail(page);
}
void CToolAvatar::OnMenuAvatarSizeHuge(){
	changeThumbnailSize(3);
	drawThumbnail(page);
}
void CToolAvatar::OnMenuAvatarRefresh(){
	AfxBeginThread(makeThumbnailThread, this);
}
void CToolAvatar::OnMenuAvatarRefreshAll(){
	if(IDYES == MessageBox(L"更新本职业所有装扮的展示图将花费较长时间(与装扮数有关)，确定继续喵？", L"提示喵", MB_YESNO)){
		AfxBeginThread(makeAllThumbnailThread, this);
	}
}
void CToolAvatar::OnMenuAvatarRefreshIcon(){
	AfxBeginThread(makeIconThread, this);
}

void CToolAvatar::OnBnClickedButtonOneKey(){
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_AVATAR);
	pPopup = menu.GetSubMenu(4);
	CPoint myPoint; 
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}



void CToolAvatar::OnMenuOneKeyLocalize(){
	ModalAvatarUpdate dlg;
	dlg.profile = profile;
	dlg.DoModal();
}


void CToolAvatar::OnMenuOneKeyPatch(){
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(makeOneKeyPatchThread, this);
}

UINT CToolAvatar::makeOneKeyPatchThread(void*para){
	CToolAvatar*dlg = (CToolAvatar*)para;
	dlg->makeOneKeyPatch();
	return 0U;
}
void CToolAvatar::makeOneKeyPatch(){
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
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0,maxFrameCount);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"拼合资源中。");
	for(long frame=0;frame<maxFrameCount;frame++){
		GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(frame);
		matrix mPic, mPicTemp;
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
				mPic.putFore(mPicTemp, LAY, pi.basePt - ptLT);
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
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0,newIO.indexCount);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"构建色表中。");
	for(long frame = 0;frame<newIO.indexCount;frame ++){
		GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(frame);
		matrix mat;
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
	/////////////////////////////////////
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(newIO.indexCount);
	GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"转换资源中。");
	std::vector<IMGobject> outIOList;
	newIO.convertToV4(outIOList, clrList, false);
	////////////////////////////////////////////
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0, 1000);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"构建引用IMG中。");
	IMGobject emptyIO;
	IMGobject::makeEmpty(emptyIO, outIOList[0].indexCount);
	////////////////////////////////////////////
	CExRabbitDlg *parent = (CExRabbitDlg*)context;
	parent->fileNPKname = L"newNPK.npk";
	parent->saveAlert = false;
	parent->no.release();
	parent->no.create();
	parent->no.IMGpush(outIOList[0], "meow/reference.img");
	parent->no.IMGpush(emptyIO, "meow/empty.img");
	for(int i = 1;i<APART_MAXCOUNT;i++){
		NPKobject *pBase = &(factory.partAlbum[i].sourceNPK);
		for(int j = 0;j<pBase->count;j++){
			str imgPath = pBase->entry[j].comment;
			parent->no.pushLink((i == APART_BODY) ? 0 : 1, imgPath);
			GET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos((i-1)*1000/(APART_MAXCOUNT-1) + j*1000/pBase->count/(APART_MAXCOUNT-1));
		}
		GET_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"构建引用IMG中("+StrToCStr(KoishiAvatar::getAvatarPartNPKName((avatarPart)i))+L")。");
	}
	MessageBox(L"制作完成了喵，请在EX中查看喵！",L"提示喵");
	parent->updateIMGlist();
	parent->updateInfo();
}

void CToolAvatar::OnMenuOneKeyNPK(){
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	dlg->no.release();
	dlg->no.create();
	dlg->fileNPKname = L"newNPK.npk";
	dlg->saveAlert = false;
	factory.makeNPK(dlg->no);
	MessageBox(L"已经将有效IMG都弄到EX里了喵！",L"提示喵");
	dlg->updateIMGlist();
	dlg->updateInfo();
}


void CToolAvatar::OnMenuOneKeyHide()
{
	// TODO: 在此添加命令处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	NPKobject no;
	IMGobject io, emptyIO;
	factory.makeNPK(no);
	if(no.count == 0){
		MessageBox(L"不存在有效的IMG喵！",L"提示喵");
		return;
	}
	no.IMGextract(0, io);
	dlg->no.release();
	dlg->no.create();
	dlg->fileNPKname = L"newNPK.npk";
	dlg->saveAlert = false;
	IMGobject::makeEmpty(emptyIO, io.indexCount);
	dlg->no.IMGpush(emptyIO, "meow/empty.img");
	for(int i = 0;i<no.count;i++){
		dlg->no.pushLink(0, no.entry[i].comment);
	}
	MessageBox(L"已经将有效IMG隐藏后弄到EX里了喵！",L"提示喵");
	dlg->updateIMGlist();
	dlg->updateInfo();
}


void CToolAvatar::OnCbnSelchangeComboSuit()
{
	// TODO: 在此添加控件通知处理程序代码
}
