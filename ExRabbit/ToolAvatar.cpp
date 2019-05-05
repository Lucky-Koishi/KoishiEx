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
	ON_BN_CLICKED(IDC_BUTTON_MAKENPK, &CToolAvatar::OnBnClickedButtonMakenpk)
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
END_MESSAGE_MAP()


// CToolAvatar 消息处理程序
BOOL CToolAvatar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowPos(NULL,0,0,1000,630,SWP_NOZORDER|SWP_NOMOVE);

	SET_CTRL(CButton, IDC_BUTTON_RESOURCE, 10, 10, 70, 30);
	SET_CTRL(CEdit, IDC_EDIT_FOLDER, 80, 10, 200, 30);
	SET_CTRL(CComboBox, IDC_COMBO_CAREER, 10, 40, 200, 60);

	SET_CTRL(CButton, IDC_BUTTON_PART1, 10, 70, 50, 90);
	SET_CTRL(CComboBox, IDC_COMBO_PART1, 60, 70, 150, 90);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE1, 160, 70, 200, 90);
	SET_CTRL(CButton, IDC_BUTTON_PART2, 10, 100, 50, 120);
	SET_CTRL(CComboBox, IDC_COMBO_PART2, 60, 100, 150, 120);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE2, 160, 100, 200, 120);
	SET_CTRL(CButton, IDC_BUTTON_PART3, 10, 130, 50, 150);
	SET_CTRL(CComboBox, IDC_COMBO_PART3, 60, 130, 150, 150);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE3, 160, 130, 200, 150);
	SET_CTRL(CButton, IDC_BUTTON_PART4, 10, 160, 50, 180);
	SET_CTRL(CComboBox, IDC_COMBO_PART4, 60, 160, 150, 180);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE4, 160, 160, 200, 180);
	SET_CTRL(CButton, IDC_BUTTON_PART5, 10, 190, 50, 210);
	SET_CTRL(CComboBox, IDC_COMBO_PART5, 60, 190, 150, 210);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE5, 160, 190, 200, 210);
	SET_CTRL(CButton, IDC_BUTTON_PART6, 10, 220, 50, 240);
	SET_CTRL(CComboBox, IDC_COMBO_PART6, 60, 220, 150, 240);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE6, 160, 220, 200, 240);
	SET_CTRL(CButton, IDC_BUTTON_PART7, 10, 250, 50, 270);
	SET_CTRL(CComboBox, IDC_COMBO_PART7, 60, 250, 150, 270);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE7, 160, 250, 200, 270);
	SET_CTRL(CButton, IDC_BUTTON_PART8, 10, 280, 50, 300);
	SET_CTRL(CComboBox, IDC_COMBO_PART8, 60, 280, 150, 300);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE8, 160, 280, 200, 300);
	SET_CTRL(CButton, IDC_BUTTON_PART9, 10, 310, 50, 330);
	SET_CTRL(CComboBox, IDC_COMBO_PART9, 60, 310, 150, 330);
	SET_CTRL(CComboBox, IDC_COMBO_PALETTE9, 160, 310, 200, 330);
	//画布位置(10, 340, 200, 530)
	SET_CTRL(CButton, IDC_BUTTON_PREV, 10, 540, 50, 560);
	SET_CTRL(CButton, IDC_BUTTON_NEXT, 60, 540, 100, 560);
	SET_CTRL(CComboBox, IDC_COMBO_ACTION, 110, 540, 200, 560);
	SET_CTRL(CButton, IDC_BUTTON_MAKENPK, 10, 570, 100, 590);
	SET_CTRL(CButton, IDCANCEL, 110, 570, 200, 590);
	//缩略图位置(210, 70, 930, 550)
	SET_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING, 210, 10, 710, 30);
	SET_CTRL(CEdit, IDC_EDIT_LOADING_INFO, 720, 10, 930, 30);
	SET_CTRL(CButton, IDC_RADIO_DISPLAY1, 210, 40, 300, 60);
	SET_CTRL(CButton, IDC_RADIO_DISPLAY2, 310, 40, 500, 60);
	SET_CTRL(CButton, IDC_RADIO_DISPLAY3, 510, 40, 700, 60);

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

	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
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
		bi.lpszTitle = _T("选择文件夹");
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
				GET_CTRL(CEdit, IDC_EDIT_FOLDER)->SetWindowText(filePath);
				factory.setPath(CStrToStr(filePath));
			}
		}
		pMalloc->Release();
	}
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
void CToolAvatar::OnBnClickedButtonMakenpk(){
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	dlg->no.release();
	dlg->no.create();
	dlg->fileNPKname = L"newNPK.npk";
	dlg->saveAlert = false;
	factory.makeNPK(dlg->no);
	MessageBox(L"已经将有效IMG都弄到EX里了喵！",L"提示喵");
	dlg->updateIMGlist();
	dlg->updateInfo();
}
void CToolAvatar::OnBnClickedCancel(){
	ShowWindow(SW_HIDE);
}
void CToolAvatar::setAnimation(int f1, int f2, int f3, int f4, int f5, int f6, int f7, int f8, int f9, int f10, int f11, int f12, int f13, int f14, int f15, int f16){
	animation[0] = f1;
	animationLength = 1;
#define BAT_SET_ANIMATION(x) if(f##x != -1){animation[x-1] = f##x; animationLength = x;}
#define SET_ANIMATION(__sel,__di,__list) if(selected==__sel){setAnimation##__list;}
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
	int selected = GET_CTRL(CComboBox, IDC_COMBO_ACTION)->GetCurSel();
	if(selected == 0){
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
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_GN){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_GG){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_FT){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_FM){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
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
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_PR){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_PG){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_TH){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_KN){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_DL){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
	}else if(factory.career == ACAREER_GB){
		SET_ANIMATION(1,"普通",(0));
		SET_ANIMATION(2,"战时",(0));
		SET_ANIMATION(3,"走动",(0));
		SET_ANIMATION(4,"跑动",(0));
		SET_ANIMATION(5,"攻击",(0));
		SET_ANIMATION(6,"Z键",(0));
		SET_ANIMATION(7,"释放",(0));
		SET_ANIMATION(8,"被攻击",(0));
		SET_ANIMATION(9,"倒地",(0));
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
			Sleep(10);
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
		fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, part) + "_" + CStrToStr(NumToCStr(factory.partAlbum[part].avatarList[newSelected].ID)) + ".png";
		mat.makePNG(fileName);
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
	int tempSize,selected,oldSize = thumbnailSize;
	int totalSelect = factory.partAlbum[displayPart].avatarList.size();
	avatarPart part = displayPart;
	for(selected = 0;selected < totalSelect; selected++){
		for(tempSize = 0;tempSize<4;tempSize++){
			changeThumbnailSize(tempSize);
			matrix mat;
			factory.makeModel(mat, getCareerColor(factory.career), size(thumbnailWidth, thumbnailHeight), part, selected, 0, getAvatarModelOffset(factory.career, part), getCareerRepresentativeFrame(factory.career), &bodyPI, &bodyMat);
			fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, part) +"_" + CStrToStr(NumToCStr(factory.partAlbum[part].avatarList[selected].ID)) + ".png";
			mat.makePNG(fileName);
			double rate = (double)selected/totalSelect +
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
				fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, (avatarPart)tempPart) +"_" + CStrToStr(NumToCStr(factory.partAlbum[(avatarPart)tempPart].avatarList[selected].ID)) + ".png";
				mat.makePNG(fileName);
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
	GET_DLG_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"展示图生成完毕。");
	dlg->MessageBox(L"展示图更新完毕。",L"提示");
	return 0U;
}
UINT CToolAvatar::makeAllThumbnailThread(void*para){
	CToolAvatar *dlg = (CToolAvatar *)para;
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetPos(0);
	GET_DLG_CTRL(CProgressCtrl, IDC_PROGRESS_LOADING)->SetRange32(0, 1000);
	dlg->makeThumbnailByAll();
	dlg->drawThumbnail(dlg->page);
	GET_DLG_CTRL(CEdit, IDC_EDIT_LOADING_INFO)->SetWindowText(L"所有展示图生成完毕。");
	dlg->MessageBox(L"展示图更新完毕。",L"提示");
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
		dlg->MessageBox(L"没能在时装资源库中找到图标文件："+StrToCStr(KoishiAvatar::getIconNPKName(dlg->factory.career))+"。",L"提示");
		return 0U;
	}
	for(i = 1;i<APART_MAXCOUNT;i++){
		std::vector<str> s = KoishiAvatar::getIconIMGName(dlg->factory.career, (KoishiAvatar::avatarPart)i);	//同部件图标有可能装入两个IMG中，获得IMG列表
		int id = 0;
		for(j = 0;j<s.size();j++){
			dword pos;
			if(no.IMGfind(s[j], pos)){
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
					iconMat.makePNG(CStrToStr(dlg->profile.getIconPath(dlg->factory.career)) + KoishiAvatar::getAvatarPartIMGName((avatarPart)i) + "_" + CStrToStr(NumToCStr(id)) + ".PNG");
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
	dlg->MessageBox(L"图标更新完毕。",L"提示");
	return 0U;
}
//////////////
//绘制展示图//
//////////////
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
			str fileName = CStrToStr(profile.getThumbnailPath(thumbnailSize, factory.career)) + KoishiAvatar::getAvatarIMGName(factory.career, displayPart) + "_" + CStrToStr(NumToCStr(factory.partAlbum[displayPart].avatarList[id].ID)) + ".png";
			if(!mat.loadPNG(fileName)){
				factory.makeButton(mat, profile.getAvatarColor(0), size(thumbnailWidth, thumbnailHeight), 3);
				canvas.putFore(mat, LAY, point(column*thumbnailWidth, row*thumbnailHeight));
			}
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
				str fileName = CStrToStr(profile.getIconPath(factory.career)) + getAvatarPartIMGName(displayPart)+"_"+CStrToStr(NumToCStr(dac[0].iconID))+".PNG";
				if(!mat.loadPNG(fileName)){
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
	selected = cbPart[displayPart]->GetCurSel() - 1;
	int rn1 = page*380;
	int rn2 = (page + 1)*380 - 1;
	if(selected >= rn1 && selected <= rn2){
		selected %= 380;
		canvas.putFore(mark, LAY, point(30 * (selected % 24), 30 * (selected / 24)));
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
			str fileName = CStrToStr(profile.getIconPath(factory.career)) + getAvatarPartIMGName(displayPart)+"_"+CStrToStr(NumToCStr(id))+".PNG";
			if(!mat.loadPNG(fileName)){
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
	selected = cbPart[displayPart]->GetCurSel() - 1;
	int rn1 = page*380;
	int rn2 = (page + 1)*380 - 1;
	if(selected >= rn1 && selected <= rn2){
		selected %= 380;
		canvas.putFore(mark, LAY, point(30 * (selected % 24), 30 * (selected / 24)));
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
	CString sourcePath;
	GET_CTRL(CEdit, IDC_EDIT_FOLDER)->GetWindowText(sourcePath);
	factory.clear();
	factory.setPath(CStrToStr(sourcePath+L"\\"));
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
		for(int i=1;i<=9;i++){
			//int oldSelected = cbPart[i]->GetCurSel() - 1;
			//int newSelected = -1;
			//int newSelectedPalette = -1;
			if(factory.partAlbum[i].valid){
				//计算变更显示样式后新的选项值
				//if(displayStyle == 1){
				//	if(oldSelected == -1){
				//		newSelected = -1;
				//		newSelectedPalette = -1;
				//	}else{
				//		newSelected = factory.partAlbum[i].bigramList[selected].originPos;
				//		newSelectedPalette = factory.partAlbum[i].bigramList[selected].paletteID;
				//	}
				//}
				//if(displayStyle == 2){
				//	if(oldSelected == -1){
				//		newSelected = -1;
				//		newSelectedPalette = -1;
				//	}else{
				//		DictAvatarContent content = dict.findTerm(factory.career, (avatarPart)i, oldSelected);
				//		if(content.size() == 0){
				//			newSelected = -1;
				//			newSelectedPalette = -1;
				//		}else{
				//			newSelected = factory.partAlbum[i].findPosByID(content[0].ID, content[0].isTN);
				//			newSelectedPalette = content[0].paletteID;
				//		}
				//	}
				//}
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
				//cbPart[i]->SetCurSel(newSelected+1);
				//if(factory.partAlbum[i].avatarList[newSelected].v6palette > 0){
				//	cbPalette[i]->ResetContent();
				//	for(j = 0;j<factory.partAlbum[i].avatarList[newSelected].v6palette;j++){
				//		cbPalette[i]->AddString(L"P"+NumToCStr(j));
				//	}
				//	cbPalette[i]->SetCurSel(newSelectedPalette);
				//}else{
				//	cbPalette[i]->ResetContent();
				//	cbPalette[i]->AddString(L"NA");
				//	cbPalette[i]->SetCurSel(0);
				//}
			}else{
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未找到资源");
				cbPart[i]->SetCurSel(0);
			}
		}
		break;
	case 1:
		for(int i=1;i<=9;i++){
			int oldSelected = cbPart[i]->GetCurSel() - 1;
			int oldSelectedPalette = cbPalette[i]->GetCurSel();
			int newSelected = -1;
			if(factory.partAlbum[i].valid){
				//计算变更显示样式后新的选项值
				//if(displayStyle == 0){
				//	if(oldSelected == -1){
				//		newSelected = -1;
				//	}else{
				//		newSelected = factory.partAlbum[i].avatarPosAtBigramList[oldSelected][oldSelectedPalette];
				//	}
				//}
				//if(displayStyle == 2){
				//	if(oldSelected == -1){
				//		newSelected = -1;
				//	}else{
				//		avatar av = factory.partAlbum[i].avatarList[oldSelected];
				//		DictAvatarContent content = dict.findTerm(factory.career, (avatarPart)i, av.ID, av.isTN, oldSelectedPalette);
				//		if(content.size() == 0){
				//			newSelected = -1;
				//		}else{
				//			//newSelected = factory.partAlbum[i].avatarPosAtBigramList[]
				//			newSelected = factory.partAlbum[i].findPosByID(content[0].ID, content[0].isTN);
				//		}
				//	}
				//}
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
				cbPart[i]->SetCurSel(0);
			}else{
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未找到资源");
				cbPart[i]->SetCurSel(0);
			}
		}
		break;
	case 2:
		loadIconCount(factory.career);	
		for(int i=1;i<=9;i++){
			if(factory.partAlbum[i].valid){
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
			}else{
				cbPart[i]->ResetContent();
				cbPart[i]->AddString(L"未找到资源");
				cbPart[i]->SetCurSel(0);
			}
		}
		break;
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
			factory.changeIMG(ap, -1);
		}else{
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
			cbPalette[ap]->EnableWindow(TRUE);
		}else{
			cbPalette[ap]->ResetContent();
			cbPalette[ap]->AddString(L"NA");
			cbPalette[ap]->SetCurSel(0);
			cbPalette[ap]->EnableWindow(FALSE);
		}
		break;
	case 1:
		if(selected == -1){
			factory.changeIMG(ap, -1);
		}else{
			factory.changeIMG(ap, factory.partAlbum[ap].bigramList[selected].originPos);
			factory.partAlbum[ap].changePalette(factory.partAlbum[ap].bigramList[selected].paletteID);
			page = selected/380;
		}
		drawIconByAvatar(page);
		break;
	case 2:
		if(selected == -1){
			factory.changeIMG(ap, -1);
		}else{
			DictAvatarContent t = dict.findTerm(factory.career, ap, selected);
			if(t.size() == 0){
				factory.changeIMG(ap, -1);
				factory.partAlbum[ap].changePalette(0);
				if(IDYES == MessageBox(L"辞典里没有与该图标对应装扮，要为此图标添加装扮吗？", L"提示", MB_YESNO)){
					MessageBox(L"施工中");
				}
			}else if(t.size() == 1){
				long pos = factory.partAlbum[ap].findPosByID(t[0].ID, t[0].isTN);
				factory.changeIMG(ap, pos);
				factory.partAlbum[ap].changePalette(t[0].paletteID);
			}else{
				MessageBox(L"注意：辞典里有个装扮与该图标对应，将只显示第一个对应的装扮。");
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
		return;
	}
	if(displayStyle== 0){
		dlg.in.selected = cbPart[displayPart]->GetCurSel() + 1;
		dlg.in.selectedPalette = cbPalette[displayPart]->GetCurSel();
	}else{
		avatarBigram ab = factory.partAlbum[displayPart].bigramList[getSelected];
		dlg.in.selected = ab.originPos;
		dlg.in.selectedPalette = ab.paletteID;
	}
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
					MessageBox(L"此处没有内容。",L"提示");
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
					MessageBox(L"已是第一页。",L"提示");
					return;
				}
			}else if(checkSelected == 1001){
				//向下翻页
				if((page + 1)* thumbnailCountPerPage < factory.partAlbum[displayPart].avatarList.size()){
					page ++;
					drawThumbnail(page);
				}else{
					MessageBox(L"已是最后页。",L"提示");
					return;
				}
			}else if(checkSelected == 1002){
				//取消该部件显示
				selected = -1;
				cbPart[displayPart]->SetCurSel(0);
				OnComboPartChange(displayPart);
			}else if(checkSelected == 1003){
				//点开更新菜单
				CMenu menu, *pPopup;  
				menu.LoadMenu(IDR_MENU_AVATAR);  
				pPopup = menu.GetSubMenu(1);  
				CPoint myPoint; 
				ClientToScreen(&myPoint);  
				GetCursorPos(&myPoint); //鼠标位置  
				pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
			}
			break;
		case 1:
			//图标模式
			if(checkSelected < 1000){
				int newSelected = 380 * page + checkSelected;
				if(newSelected >= factory.partAlbum[displayPart].bigramList.size()){
					MessageBox(L"此处没有内容。",L"提示");
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
					MessageBox(L"已是第一页。",L"提示");
					return;
				}
			}else if(checkSelected == 1001){
				//向下翻页
				if((page + 1) * 380 < factory.partAlbum[displayPart].bigramList.size()){
					page ++;
					drawIconByAvatar(page);
				}else{
					MessageBox(L"已是最后页。",L"提示");
					return;
				}
			}else if(checkSelected == 1002){
				//取消该部件显示
				selected = -1;
				cbPart[displayPart]->SetCurSel(0);
				OnComboPartChange(displayPart);
			}else if(checkSelected == 1003){
				//点开更新菜单
				CMenu menu, *pPopup;  
				menu.LoadMenu(IDR_MENU_AVATAR);  
				pPopup = menu.GetSubMenu(1);  
				CPoint myPoint; 
				ClientToScreen(&myPoint);  
				GetCursorPos(&myPoint); //鼠标位置  
				pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
			}
			break;
		case 2:
			//图标模式
			if(checkSelected < 1000){
				int newSelected = 380 * page + checkSelected;
				if(newSelected >= iconCount[displayPart]){
					MessageBox(L"此处没有内容。",L"提示");
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
					MessageBox(L"已是第一页。",L"提示");
					return;
				}
			}else if(checkSelected == 1001){
				//向下翻页
				if((page + 1) * 380 < iconCount[displayPart]){
					page ++;
					drawIconByIcon(page);
				}else{
					MessageBox(L"已是最后页。",L"提示");
					return;
				}
			}else if(checkSelected == 1002){
				//取消该部件显示
				selected = -1;
				cbPart[displayPart]->SetCurSel(0);
				OnComboPartChange(displayPart);
			}else if(checkSelected == 1003){
				//点开更新菜单
				CMenu menu, *pPopup;  
				menu.LoadMenu(IDR_MENU_AVATAR);  
				pPopup = menu.GetSubMenu(1);  
				CPoint myPoint; 
				ClientToScreen(&myPoint);  
				GetCursorPos(&myPoint); //鼠标位置  
				pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
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
				pPopup = menu.GetSubMenu(0);
			}
			if(displayStyle == 1){
				pPopup = menu.GetSubMenu(3);
			}
			if(displayStyle == 2){
				pPopup = menu.GetSubMenu(2);
			}
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
	if(IDYES == MessageBox(L"更新本职业所有装扮的展示图将花费较长时间(与装扮数有关)，确定继续喵？", L"提示", MB_YESNO)){
		AfxBeginThread(makeAllThumbnailThread, this);
	}
}
void CToolAvatar::OnMenuAvatarRefreshIcon(){
	if(IDYES == MessageBox(L"更新本职业所有装扮的图标将花费较长时间(与图标数有关)，确定继续喵？", L"提示", MB_YESNO)){
		AfxBeginThread(makeIconThread, this);
	}
}