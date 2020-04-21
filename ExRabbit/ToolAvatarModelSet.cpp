// ToolAvatarModelSet.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarModelSet.h"
#include "afxdialogex.h"


extern CString avatarCString[APART_MAXCOUNT];
extern CString weaponCString[AWEAPON_MAXCOUNT];
extern CString careerName[ACHARACTER_MAXCOUNT];
extern CString weaponIconClassified[ACHARACTER_MAXCOUNT][WEAPON_MAXCOUNT_PER_CHAR];

// ToolAvatarModelSet 对话框

IMPLEMENT_DYNAMIC(ToolAvatarModelSet, CDialogEx)

ToolAvatarModelSet::ToolAvatarModelSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarModelSet::IDD, pParent)
{

}

ToolAvatarModelSet::~ToolAvatarModelSet()
{
}

void ToolAvatarModelSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarModelSet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ToolAvatarModelSet::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &ToolAvatarModelSet::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAR, &ToolAvatarModelSet::OnCbnSelchangeComboChar)
	ON_CBN_SELCHANGE(IDC_COMBO_PART, &ToolAvatarModelSet::OnCbnSelchangeComboPart)
	ON_BN_CLICKED(IDC_BUTTON2, &ToolAvatarModelSet::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO_SIZE, &ToolAvatarModelSet::OnCbnSelchangeComboSize)
END_MESSAGE_MAP()


// ToolAvatarModelSet 消息处理程序


BOOL ToolAvatarModelSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Profile pf;
	pf.loadProfile();
	mc.load(pf.getAvatarMapPath());
	CComboBox *ccb = GET_CTRL(CComboBox, IDC_COMBO_CHAR);
	for(int i = 0;i<ACHARACTER_MAXCOUNT;i++)
		ccb->AddString(careerName[i]);
	ccb->SetCurSel(0);
	ccb = GET_CTRL(CComboBox, IDC_COMBO_PART);
	for(int i = 0;i<APART_MAXCOUNT;i++)
		ccb->AddString(avatarCString[i]);
	ccb->AddString(L"武器");
	ccb->SetCurSel(0);
	ccb = GET_CTRL(CComboBox, IDC_COMBO_SIZE);
	ccb->AddString(L"小");
	ccb->AddString(L"中");
	ccb->AddString(L"大");
	ccb->AddString(L"巨大");
	ccb->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ToolAvatarModelSet::OnBnClickedButton1()
{
	// TODO: 打开配置文件
	Profile pf;
	pf.loadProfile();
	mc.load(pf.getAvatarMapPath());
	ShellExecute(0, L"open", pf.getAvatarMapPath() +  L"模型生成设置.txt", 0, 0, SW_SHOWNORMAL);
}


void ToolAvatarModelSet::OnBnClickedButton4()
{
	// TODO: 重新读取
	Profile pf;
	pf.loadProfile();
	mc.load(pf.getAvatarMapPath());
}


void ToolAvatarModelSet::OnCbnSelchangeComboChar()
{
	// TODO: 在此添加控件通知处理程序代码
	Profile pf;
	pf.loadProfile();
	fc.initial((AvatarCharacter)GET_CTRL(CComboBox, IDC_COMBO_CHAR)->GetCurSel(), CStrToStr(pf.getAvatarPath()));
	fc.loadAvatar(APART_BODY);
	//
	GET_CTRL(CComboBox, IDC_COMBO_PART)->SetCurSel(0);
	fc.loadAvatar((AvatarPart)0);
	autoFill();
	draw();
}


void ToolAvatarModelSet::OnCbnSelchangeComboPart()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = GET_CTRL(CComboBox, IDC_COMBO_PART)->GetCurSel();
	if(sel == APART_MAXCOUNT){
		if(fc.weaponAlbum[1].content.size() == 0){
			fc.loadWeapon(1);
		}
	}else{
		if(fc.album[sel].content.size() == 0){
			fc.loadAvatar((AvatarPart)sel);
		}
	}
	autoFill();
	draw();
}


void ToolAvatarModelSet::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	draw();
}


void ToolAvatarModelSet::OnCbnSelchangeComboSize()
{
	// TODO: 在此添加控件通知处理程序代码
	draw();
}
void ToolAvatarModelSet::autoFill(){
	if(GET_CTRL(CComboBox, IDC_COMBO_PART)->GetCurSel() == APART_MAXCOUNT){
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(NumToCStr(mc.modelWeaponOffset[fc.character].X));
		GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(NumToCStr(mc.modelWeaponOffset[fc.character].Y));
		GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(NumToCStr(mc.modelWeaponFrame[fc.character]));
	}else{
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(NumToCStr(mc.modelAvatarOffset[fc.character][GET_CTRL(CComboBox, IDC_COMBO_PART)->GetCurSel()].X));
		GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(NumToCStr(mc.modelAvatarOffset[fc.character][GET_CTRL(CComboBox, IDC_COMBO_PART)->GetCurSel()].Y));
		GET_CTRL(CEdit, IDC_EDIT4)->SetWindowText(NumToCStr(mc.modelAvatarFrame[fc.character][GET_CTRL(CComboBox, IDC_COMBO_PART)->GetCurSel()]));
	}
	
}
void ToolAvatarModelSet::draw(){
	long widthEnum1[5] = {54, 63, 84, 126};
	long heightEnum1[5] = {84, 96, 112, 168};
	long width = widthEnum1[GET_CTRL(CComboBox, IDC_COMBO_SIZE)->GetCurSel()];
	long height = heightEnum1[GET_CTRL(CComboBox, IDC_COMBO_SIZE)->GetCurSel()];
	AvatarPart ap = (AvatarPart)GET_CTRL(CComboBox, IDC_COMBO_PART)->GetCurSel();
	CString x1,y1,f1;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(x1);
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(y1);
	GET_CTRL(CEdit, IDC_EDIT4)->GetWindowText(f1);
	fc.initialModelMaker(size(width, height), point(_ttol(x1), _ttol(y1)), _ttol(f1));
	image im;
	if(ap == APART_MAXCOUNT){
		fc.makeWeaponModel(im, 1, 0);
	}else{
		fc.makeAvatarModel(im, ap, 0);
	}
	if(1){
		int i,j;
		int canw = im.width;
		int canh = im.height;
		CImage cimg;
		cimg.Create(canw, canh, 32);
		UCHAR* pst = (UCHAR*)cimg.GetBits();
		int pit = cimg.GetPitch();
		CDC *pDC = GetDC();
		for(i=0;i<canw;i++){
			for(j=0;j<canh;j++){
				*(pst + pit*j + 4*i + 0) = im[j][i].B;
				*(pst + pit*j + 4*i + 1) = im[j][i].G;
				*(pst + pit*j + 4*i + 2) = im[j][i].R;
			}
		}
		cimg.Draw(pDC->m_hDC,10, 10);
		ReleaseDC(pDC);
	}

}