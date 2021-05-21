// ToolAvatarLocalizer.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarLocalizer.h"
#include "afxdialogex.h"
#include "ToolAvatarModelConfig.h"

// ToolAvatarLocalizer 对话框

extern long modelCFrame[ACHARACTER_MAXCOUNT];

extern CString avatarCString[APART_MAXCOUNT];
extern CString weaponCString[AWEAPON_MAXCOUNT];
extern CString careerName[ACHARACTER_MAXCOUNT];
extern CString iconCString[APART_MAXCOUNT];
extern CString iconSpecCString;
//武器图标的字符串信息，排序方式由avatar.cpp下NPK_weaponIcon函数中的顺序决定
extern CString iconWeaponCString[ACHARACTER_MAXCOUNT][5];
extern CString weaponIconClassified[ACHARACTER_MAXCOUNT][WEAPON_MAXCOUNT_PER_CHAR];
CString sizeCString[4] = {
	L"小",L"中",L"大",L"巨大"
};
IMPLEMENT_DYNAMIC(ToolAvatarLocalizer, CDialogEx)

ToolAvatarLocalizer::ToolAvatarLocalizer(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarLocalizer::IDD, pParent)
{

}

ToolAvatarLocalizer::~ToolAvatarLocalizer()
{
}

void ToolAvatarLocalizer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarLocalizer, CDialogEx)
	ON_BN_CLICKED(ID_START, &ToolAvatarLocalizer::OnBnClickedStart)
	ON_BN_CLICKED(IDCANCEL, &ToolAvatarLocalizer::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ALL, &ToolAvatarLocalizer::OnBnClickedButtonAll)
	ON_BN_CLICKED(IDC_BUTTON_NOS, &ToolAvatarLocalizer::OnBnClickedButtonNos)
END_MESSAGE_MAP()


// ToolAvatarLocalizer 消息处理程序
void ToolAvatarLocalizer::localize(AvatarCharacter ac, ProfileBlack *ppf, CEdit *ce, CProgressCtrl* cp, uchar flag) {
	long widthEnum1[5] = {54, 63, 84, 126, 28};		//750→756
	long heightEnum1[5] = {84, 96, 112, 168, 28};	//675→672
	int p;
	AvatarFactory factory;
	ToolAvatarModelConfig mc;
	mc.load(ppf->getAvatarMapPath());
	factory.initial(ac, CStrToStr(ppf->getAvatarPath()));
	ce->SetWindowText(L"开始");
	cp->SetRange32(0, 600);
	if(flag & 0x01){
		for(int sizeMode = 0; sizeMode < 4; sizeMode ++){
			ce->SetWindowText(careerName[ac] + L":正在为尺寸(" +sizeCString[sizeMode] + L")建模");	
			for(int iPart = 0;iPart < APART_MAXCOUNT;iPart++){
				ce->SetWindowText(careerName[ac] + L":读取" + avatarCString[iPart] + L"(" +sizeCString[sizeMode] + L")资源中");
				cp->SetPos(sizeMode*50 + iPart*50/APART_MAXCOUNT);
				//
				factory.loadAvatar(APART_BODY);
				factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]),
					mc.modelAvatarOffset[ac][iPart], mc.modelAvatarFrame[ac][iPart]);
				factory.releaseAvatar(APART_BODY);
				//
				factory.loadAvatar((AvatarPart)iPart);
				const AvatarAlbum &aa = factory.album[iPart];
				for(int cIndex = 0; cIndex < aa.content.size(); cIndex ++){
					image im;
					ce->SetWindowText(careerName[ac] + L":生成" + avatarCString[iPart]  + NumToCStr(aa.content[cIndex].ID) + L"(" + sizeCString[sizeMode] + L")中");
					CString fileName = ppf->getModelPath(sizeMode, ac) + avatarCString[iPart] + NumToCStr(aa.content[cIndex].ID);
					factory.makeAvatarModel(im, (AvatarPart)iPart, cIndex);
					makePNG(im, CStrToStr(fileName)+".png");
					countAvatar ++;
					if(aa.content[cIndex].infoTN.size() > 0){
						im.destory();
						factory.makeAvatarModel(im, (AvatarPart)iPart, cIndex, true);
						makePNG(im, CStrToStr(fileName)+"(TN).png");
						countAvatar ++;
					}
				}
				factory.releaseAvatar((AvatarPart)iPart);
			}
		}
	}
	if(flag & 0x02){
		for(int sizeMode = 0; sizeMode < 4; sizeMode ++){
			ce->SetWindowText(careerName[ac] + L":正在为尺寸(" +sizeCString[sizeMode] + L")建模");	
			for(int iWeaponTypeIndex = 0;iWeaponTypeIndex < factory.weapon.size(); iWeaponTypeIndex++){
				ce->SetWindowText(careerName[ac] + L":读取" + weaponCString[factory.weapon[iWeaponTypeIndex]] + 
					L"(" + sizeCString[sizeMode] + L")资源中");
				cp->SetPos(200 + sizeMode*50 + iWeaponTypeIndex*50/factory.weapon.size());
				factory.loadAvatar(APART_BODY);
				if(ac == ACHARACTER_PG && factory.weapon[iWeaponTypeIndex] == AWEAPON_ROSARY){
					factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]), point(0,0), 0);
				}else{
					factory.initialModelMaker(size(widthEnum1[sizeMode], heightEnum1[sizeMode]),
						mc.modelWeaponOffset[ac], mc.modelWeaponFrame[ac]);
				}
				factory.releaseAvatar(APART_BODY);

				factory.loadWeapon(iWeaponTypeIndex);
				const WeaponAlbum &wa = factory.weaponAlbum[iWeaponTypeIndex];
				for(int cIndex = 0; cIndex < wa.content.size(); cIndex ++){
					image im;
					ce->SetWindowText(careerName[ac] + L":生成" + weaponCString[factory.weapon[iWeaponTypeIndex]] + NumToCStr(wa.content[cIndex].ID)+
					L"(" + sizeCString[sizeMode] + L")中");
					CString fileName = ppf->getModelPath(sizeMode, ac) + weaponCString[factory.weapon[iWeaponTypeIndex]] + NumToCStr(wa.content[cIndex].ID);
					factory.makeWeaponModel(im, iWeaponTypeIndex, cIndex);
					makePNG(im, CStrToStr(fileName)+".png");
					countWeapon ++;
					if(wa.content[cIndex].infoTN.size() > 0){
						im.destory();
						factory.makeWeaponModel(im, iWeaponTypeIndex, cIndex, true);
						makePNG(im, CStrToStr(fileName)+"(TN).png");
						countWeapon ++;
					}
				}
				factory.releaseWeapon(iWeaponTypeIndex);
			}
		}
	}
	//第五步：读取图标
	if(flag & 0x04){
		str fileStr = NPK_avatarIcon(ac);
		NPKobject no;
		if(no.loadFile(CStrToStr(ppf->getAvatarPath()) + fileStr)){
			for(int p = 0;p<APART_MAXCOUNT;p++){
				ce->SetWindowText(careerName[ac] + L":生成" + iconCString[p] + L"图标中");
				cp->SetPos(400 + p*100/APART_MAXCOUNT);
				str imgPath = IMG_avatarIcon(ac, (AvatarPart)p);
				long pos;
				if(!no.find(imgPath, pos, 0))
					continue;
				IMGobject io;
				no.IMGextract(pos, io);
				for(int id = 0;id<io.indexCount;id++){
					image iconImage;
					io.PICextract(id, iconImage);
					if(iconImage.width > 10/* == 28*/){
						makePNG(iconImage, CStrToStr(ppf->getIconPath(ac) + iconCString[p] + NumToCStr(id) + L".png"));
						countIcon ++;
					}
				}
			}
			str imgPath = IMG_avatarIcon(ac, "tong");
			long pos;
			if(no.find(imgPath, pos, 0)){
				IMGobject io;
				no.IMGextract(pos, io);
				for(int id = 0;id<io.indexCount;id++){
					image iconImage;
					io.PICextract(id, iconImage);
					if(iconImage.width > 10/* == 28*/){
						makePNG(iconImage, CStrToStr(ppf->getIconPath(ac) + iconCString[APART_BODY] + NumToCStr(108+id) + L".png"));
						countIcon ++;
					}
				}
			}
		}
		no.release();
		std::vector<str> fileList = NPK_weaponIcon(ac);
		for(int fileID = 0; fileID < fileList.size(); fileID ++){
			ce->SetWindowText(careerName[ac] + L":生成" + iconWeaponCString[ac][fileID] + L"图标中");
			cp->SetPos(500 + fileID*100/fileList.size());
			NPKobject now;
			if(!now.loadFile(CStrToStr(ppf->getAvatarPath()) + fileList[fileID]))
				continue;
			if(now.getCount() == 0)
				continue;
			IMGobject io;
			if(!now.IMGextract(0, io))
				continue;
			for(int id = 0;id<io.indexCount;id++){
				image iconImage;
				io.PICextract(id, iconImage);
				if(iconImage.width > 10/* == 28*/){
					makePNG(iconImage, CStrToStr(ppf->getIconPath(ac) + iconWeaponCString[ac][fileID] + NumToCStr(id) + L".png"));
					countIcon ++;
				}
			}
		}
		ce->SetWindowText(careerName[ac] + L":本地化已完成");
		cp->SetPos(600);
	}
}

BOOL ToolAvatarLocalizer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	cel[0] = GET_CTRL(CEdit, IDC_EDIT_OO1);
	cel[1] = GET_CTRL(CEdit, IDC_EDIT_OO2);
	cel[2] = GET_CTRL(CEdit, IDC_EDIT_OO3);
	cel[3] = GET_CTRL(CEdit, IDC_EDIT_OO4);
	cel[4] = GET_CTRL(CEdit, IDC_EDIT_OO5);
	cel[5] = GET_CTRL(CEdit, IDC_EDIT_OO6);
	cel[6] = GET_CTRL(CEdit, IDC_EDIT_OO7);
	cel[7] = GET_CTRL(CEdit, IDC_EDIT_OO8);
	cel[8] = GET_CTRL(CEdit, IDC_EDIT_OO9);
	cel[9] = GET_CTRL(CEdit, IDC_EDIT_OO10);
	cel[10] = GET_CTRL(CEdit, IDC_EDIT_OO11);
	cel[11] = GET_CTRL(CEdit, IDC_EDIT_OO12);
	cel[12] = GET_CTRL(CEdit, IDC_EDIT_OO13);
	cel[13] = GET_CTRL(CEdit, IDC_EDIT_OO14);
	cpl[0] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO1);
	cpl[1] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO2);
	cpl[2] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO3);
	cpl[3] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO4);
	cpl[4] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO5);
	cpl[5] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO6);
	cpl[6] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO7);
	cpl[7] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO8);
	cpl[8] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO9);
	cpl[9] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO10);
	cpl[10] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO11);
	cpl[11] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO12);
	cpl[12] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO13);
	cpl[13] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_OO14);
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
	GET_CTRL(CComboBox, IDC_COMBO1)->ResetContent();
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"1");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"2");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"3");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"4(四核推荐)");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"5");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"6");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"7");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"8(八核推荐)");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"9");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"10");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"11");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"12");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"13");
	GET_CTRL(CComboBox, IDC_COMBO1)->AddString(L"14");
	GET_CTRL(CComboBox, IDC_COMBO1)->SetCurSel(3);
	maxEstablished = 4;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
unsigned LocalSub1(void *para){
	ToolAvatarLocalizer *dlg = (ToolAvatarLocalizer*)para;
	queue ql0 = dlg->ql[dlg->established];
	TRACE(NumToCStr(dlg->established));
	TRACE(L"-");
	for(int i = 0;i<ql0.size();i++){	
		TRACE(NumToCStr(ql0[i]));
		TRACE(L" ");
	}
	TRACE(L"\n");
	for(int i = 0;i<ql0.size();i++){
		dlg->localize((AvatarCharacter)ql0[i], &dlg->profile, dlg->cel[ql0[i]], dlg->cpl[ql0[i]], dlg->localFlag);
		Sleep(100);
	}
	dlg->finished ++;
	return 0U;
}
unsigned Local1(void *para){
	ToolAvatarLocalizer *dlg = (ToolAvatarLocalizer*)para;
	dlg->established = 0;
	dlg->finished = 0;
	for(int i = 0;i<dlg->ql.size();i++){
		AfxBeginThread(LocalSub1, para);
		Sleep(100);
		dlg->established ++;
	}
	while(dlg->finished != dlg->established);
	GET_DLG_CTRL(CButton, ID_START)->EnableWindow(1);
	GET_DLG_CTRL(CButton, IDCANCEL)->EnableWindow(1);
	GET_DLG_CTRL(CComboBox, IDC_COMBO1)->EnableWindow(1);
	if(dlg->countAvatar + dlg->countWeapon + dlg->countIcon == 0){
		dlg->MessageBox(L"嗯喵？找不到任何资源喵！查看资源目录是否设置完毕喵！",L"提示喵");
	}else{
		CString statStr;
		dlg->MessageBox(L"恭喜喵！本地化已完成喵！\r\n已生成装扮展示图" + 
			NumToCStr(dlg->countAvatar) + L"个，武器展示图" + 
			NumToCStr(dlg->countWeapon) + L"个，图标" + 
			NumToCStr(dlg->countIcon) + L"个喵！\r\n欢迎使用肥猫的试衣间喵！",L"提示喵");
	}
	return 0U;
}
void ToolAvatarLocalizer::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	countAvatar = 0;
	countWeapon = 0;
	countIcon = 0;
	GET_CTRL(CButton, ID_START)->EnableWindow(0);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(0);
	GET_CTRL(CComboBox, IDC_COMBO1)->EnableWindow(0);
	for(int i = 0;i<ACHARACTER_MAXCOUNT;i++)
		cel[i]->SetWindowText(careerName[i] + L":未进行");
	profile.loadProfile();
	maxEstablished = GET_CTRL(CComboBox, IDC_COMBO1)->GetCurSel() + 1;
	localFlag = 0;
	localFlag |= (GET_CTRL(CButton, IDC_CHECK_A1)->GetCheck() ? 0x01 : 0);
	localFlag |= (GET_CTRL(CButton, IDC_CHECK_A2)->GetCheck() ? 0x02 : 0);
	localFlag |= (GET_CTRL(CButton, IDC_CHECK_A3)->GetCheck() ? 0x04 : 0);
	ql.clear();
	for(int i = 0;i<maxEstablished;i++)
		ql.push_back(queue());
	queue ql0;
	if(GET_CTRL(CButton, IDC_CHECK_CAREER1)->GetCheck())
		ql0.push_back(0);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER2)->GetCheck())
		ql0.push_back(1);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER3)->GetCheck())
		ql0.push_back(2);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER4)->GetCheck())
		ql0.push_back(3);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER5)->GetCheck())
		ql0.push_back(4);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER6)->GetCheck())
		ql0.push_back(5);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER7)->GetCheck())
		ql0.push_back(6);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER8)->GetCheck())
		ql0.push_back(7);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER9)->GetCheck())
		ql0.push_back(8);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER10)->GetCheck())
		ql0.push_back(9);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER11)->GetCheck())
		ql0.push_back(10);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER12)->GetCheck())
		ql0.push_back(11);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER13)->GetCheck())
		ql0.push_back(12);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER14)->GetCheck())
		ql0.push_back(13);
	for(int i = 0;i<ql0.size();i++)
		ql[i%ql.size()].push_back(ql0[i]);
	AfxBeginThread(Local1, this);
}


void ToolAvatarLocalizer::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void ToolAvatarLocalizer::OnBnClickedButtonAll()
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


void ToolAvatarLocalizer::OnBnClickedButtonNos()
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
