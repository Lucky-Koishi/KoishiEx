// ToolAvatarMark.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarMark.h"
#include "afxdialogex.h"

// ToolAvatarMark 对话框

IMPLEMENT_DYNAMIC(ToolAvatarMark, CDialogEx)

ToolAvatarMark::ToolAvatarMark(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarMark::IDD, pParent)
{

}

ToolAvatarMark::~ToolAvatarMark()
{
}

void ToolAvatarMark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarMark, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ToolAvatarMark::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &ToolAvatarMark::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON2, &ToolAvatarMark::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ToolAvatarMark::OnBnClickedButton3)
END_MESSAGE_MAP()


// ToolAvatarMark 消息处理程序


BOOL ToolAvatarMark::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(1);

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
	
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"请选择目标文件夹，生成的带标记的NPK会存储在同一文件夹下。");
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"这里显示正在处理的NPK文件。");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"这里显示正在处理的IMG文件。");

	
	GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetRange32(0, 1000);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetRange32(0, 1000);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ToolAvatarMark::OnBnClickedButton1()
{
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


void ToolAvatarMark::OnBnClickedButton7()
{
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


void ToolAvatarMark::OnBnClickedButton2()
{
	HWND hwnd= GetSafeHwnd();   //得到窗口句柄
	CString filePath= L"";	//得到文件路径
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//取得IMalloc分配器接口
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
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//取得IMalloc分配器接口   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //获得一个文件系统路径
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//释放内存
			if(filePath.GetLength()<=1){
				MessageBox(L"并不是有效的文件夹喵！",L"提示喵");
			}else{
				GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//释放接口
	}
}


void ToolAvatarMark::OnBnClickedButton3(){
	AfxBeginThread(go, this);
}
unsigned ToolAvatarMark::go(void*context){
	ToolAvatarMark* dlg = (ToolAvatarMark*)context;
	GET_DLG_CTRL(CButton, IDC_BUTTON3)->EnableWindow(FALSE);
	GET_DLG_CTRL(CButton, IDCANCEL)->EnableWindow(FALSE);
	dlg->title();
	GET_DLG_CTRL(CButton, IDC_BUTTON3)->EnableWindow(TRUE);
	GET_DLG_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
	return 0;
}
void ToolAvatarMark::title(){
	//初始化一些打标使用的常量
	//各职业打标位置
	point ptBaseCareer[ACHARACTER_MAXCOUNT] = {
		point(120,150),		//SM
		point(138,200),		//SG
		point(140,210),		//FT
		point(140,140),		//FM
		point(135,180),		//GN
		point(130,140),		//GG
		point(137,220),		//MG	已确定
		point(136,210),		//MM
		point(108,120),		//PR
		point(140,110),		//PG
		point(128,140),		//TH
		point(135,210),		//KN
		point(130,140),		//DL
		point(110,120)		//GB
	};
	//各部件的打标位置偏移量
	point ptBasePart[APART_MAXCOUNT+1] = {
		point(40, -60),		//CAP
		point(40, -48),		//HAIR
		point(40, -36),		//FACE
		point(40, -24),		//NECK
		point(40, -12),		//COAT
		point(40, 0),		//PANTS
		point(40, 12),		//BELT
		point(40, 24),		//SHOES
		point(40, 36),		//SKIN
		point(40, 48)		//DEFAULT(WEAPON)
	};
	//各职业的站街帧范围
	int frameEnum[ACHARACTER_MAXCOUNT][2] = {
		{176, 179},{0, 8},{113, 116},{0, 3},{0, 13},{0, 9},{10, 13},{0, 7},{0, 3},{0, 8},{0, 11},{0, 5},{0, 3},{0, 9}
	};
	//部件打标转义符
	str fixn1[ACHARACTER_MAXCOUNT] = {"sm","sg","ft","fm","gn","gg","mg","mm","pr","pg","th","kn","dl","gb"};
	str strBasePart[APART_MAXCOUNT+1] = {"   CAP ","  HAIR ","  FACE ","  NECK ","  COAT "," PANTS ","  BELT "," SHOES ","  BODY ","WEAPON "};
	//
	std::vector<AvatarCharacter> careerList;
	if(GET_CTRL(CButton, IDC_CHECK_CAREER1)->GetCheck())
		careerList.push_back(ACHARACTER_SM);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER2)->GetCheck())
		careerList.push_back(ACHARACTER_SG);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER3)->GetCheck())
		careerList.push_back(ACHARACTER_FT);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER4)->GetCheck())
		careerList.push_back(ACHARACTER_FM);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER5)->GetCheck())
		careerList.push_back(ACHARACTER_GN);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER6)->GetCheck())
		careerList.push_back(ACHARACTER_GG);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER7)->GetCheck())
		careerList.push_back(ACHARACTER_MG);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER8)->GetCheck())
		careerList.push_back(ACHARACTER_MM);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER9)->GetCheck())
		careerList.push_back(ACHARACTER_PR);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER10)->GetCheck())
		careerList.push_back(ACHARACTER_PG);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER11)->GetCheck())
		careerList.push_back(ACHARACTER_TH);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER12)->GetCheck())
		careerList.push_back(ACHARACTER_KN);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER13)->GetCheck())
		careerList.push_back(ACHARACTER_DL);
	if(GET_CTRL(CButton, IDC_CHECK_CAREER14)->GetCheck())
		careerList.push_back(ACHARACTER_GB);
	bool singleNPK = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	bool wantWeapon = GET_CTRL(CButton, IDC_CHECK2)->GetCheck();
	bool onlyNormal = GET_CTRL(CButton, IDC_CHECK3)->GetCheck();
	//待读取的武器类NPK
	CString folderPath;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderPath);
	str pathStr = CStrToStr(folderPath + L"\\");
	int NPKpart, careerID, imgID, frmID;
	for(careerID = 0;careerID < careerList.size(); careerID++){
		AvatarCharacter ac = careerList[careerID];
		NPKobject totalNo, totalWeaponNo;
		str afterTotalStr = pathStr + "marker(" + fixn1[ac] + ").NPK";
		str afterTotalWeaponStr = pathStr + "marker(" +  fixn1[ac] + "_weapon).NPK";
		//装扮部件
		for(NPKpart = 0;NPKpart < APART_MAXCOUNT;NPKpart++){
			str fileStr = pathStr + NPK_avatar(ac, (AvatarPart)NPKpart);
			str afterStr = pathStr + "marker(" + NPK_avatar(ac, (AvatarPart)NPKpart)+").NPK";
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在对"+StrToCStr(NPK_avatar(ac, (AvatarPart)NPKpart))+L"进行打标中……");
			NPKobject no;
			if(!no.loadFile(fileStr))
				continue;
			NPKobject partNo;
			int prevID = -1;		//记录上一次编号，同一编号的IMG只打一次
			for(imgID = 0;imgID < no.count; imgID++){
				IMGobject io;
				if(!no.IMGextract(imgID,io))
					continue;
				if(io.version == V5)
					continue;
				if(io.version == V6 && io.paletteData.getCount() == 0)
					continue;
				//增加这一步是为了防止扩充部分为实色
				if((io.version == V4 || io.version == V6) && io.paletteData[0].size() > 0 && io.paletteData[0][0].alpha > 0)
					continue;
				
				//avatar av;
				//avatarLayer al;
				//if(!parseAvatarName(no.entry[imgID].comment, av, al))
				//	continue;
				//if(al == ALAYER_F || al == ALAYER_G)
				//	continue;
				str IDstr = getSerialID(no.entry[imgID].comment);
				int avID = std::stoi(IDstr);
				if(avID == prevID)
					continue;
				prevID = avID;
				GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在对"+GetTail(StrToCStr(no.entry[imgID].comment))+L"进行打标中……");
				int startFrame = onlyNormal ? frameEnum[careerID][0]:0;
				int endFrame = onlyNormal ? frameEnum[careerID][1]:(io.indexCount-1);
				for(frmID = startFrame;frmID<=endFrame;frmID++){
					PICinfo pi;
					if(!io.PICgetInfo(frmID, pi))
						continue;
					if(pi.format == LINK)
						continue;
					image oldPic, newPic;
					stream sPic;
					point pt = ptBaseCareer[careerID] + ptBasePart[NPKpart] - pi.basePt;
					if(io.version == V2){
						io.PICextract(frmID, oldPic);
						KoishiExpand::KoishiMarkTool::ImageMarking(
							oldPic, newPic, 
							strBasePart[NPKpart] + formatAvatarID(avID), 
							pt, color(0xFF, 0, 0, 0));
						if(pt.X < 0){
							pi.basePt.X += pt.X;
						}
						if(pt.Y < 0){
							pi.basePt.Y += pt.Y;
						}
						io.PICpreprocess(newPic, sPic, pi, pi.format);
					}else if(io.version != V5){
						io.PICextractIndexImage(frmID, oldPic);
						KoishiExpand::KoishiMarkTool::ImageMarking(
							oldPic, newPic, 
							strBasePart[NPKpart] + formatAvatarID(avID), 
							pt, color(1,0,0,0));
						if(pt.X < 0){
							pi.basePt.X += pt.X;
						}
						if(pt.Y < 0){
							pi.basePt.Y += pt.Y;
						}
						io.PICpreprocessIndexImage(newPic, sPic, pi);
					}
					io.PICreplace(frmID, pi, sPic);
				}
				if(singleNPK){
					totalNo.IMGpush(io, no.entry[imgID].comment);
				}else{
					partNo.IMGpush(io, no.entry[imgID].comment);
				}
				GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000*imgID/no.count);
			}
			if(!singleNPK){
				partNo.saveFile(afterStr);
			}
			GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000);
			GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(1000*(NPKpart)/APART_MAXCOUNT);
		}
		if(singleNPK){
			if(totalNo.count > 0)
				totalNo.saveFile(afterTotalStr);
		}
		//武器部件
		if(wantWeapon){
			int i = 0;
			std::vector<str> weaponNPK = getWeaponNPKlist(ac);
			for(i = 1;i < weaponNPK.size();i++){
				str fileStr = pathStr + weaponNPK[i];
				str afterStr = pathStr + "marker(" + weaponNPK[i]+").NPK";
				GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在对"+StrToCStr(weaponNPK[i])+L"进行打标中……");
				NPKobject no;
				if(!no.loadFile(fileStr))
					continue;
				NPKobject partNo;
				int prevID = -1;		//记录上一次编号，同一编号的IMG只打一次
				for(imgID = 0;imgID < no.count; imgID++){
					IMGobject io;
					if(!no.IMGextract(imgID,io))
						continue;
					if(io.version == V5)
						continue;
					if(io.version == V6 && io.paletteData.getCount() == 0)
						continue;
					//增加这一步是为了防止扩充部分为实色
					if((io.version == V4 || io.version == V6) && io.paletteData[0].size() > 0 && io.paletteData[0][0].alpha > 0)
						continue;
					str IDstr = getSerialID(no.entry[imgID].comment);
					int avID = std::stoi(IDstr);
					if(avID == prevID)
						continue;
					prevID = avID;
					GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在对"+GetTail(StrToCStr(no.entry[imgID].comment))+L"进行打标中……");
					int startFrame = onlyNormal ? frameEnum[ac][0]:0;
					int endFrame = onlyNormal ? frameEnum[ac][1]:(io.indexCount-1);
					for(frmID = startFrame;frmID<=endFrame;frmID++){
						PICinfo pi;
						if(!io.PICgetInfo(frmID, pi))
							continue;
						if(pi.format == LINK)
							continue;
						image oldPic, newPic;
						stream sPic;
						point pt = ptBaseCareer[ac] + ptBasePart[0] - pi.basePt;
						if(io.version == V2){
							io.PICextract(frmID, oldPic);
							KoishiExpand::KoishiMarkTool::ImageMarking(
								oldPic, newPic, 
								strBasePart[APART_MAXCOUNT] + formatAvatarID(avID), 
								pt, color(0xFF, 0, 0, 0));
							if(pt.X < 0){
								pi.basePt.X += pt.X;
							}
							if(pt.Y < 0){
								pi.basePt.Y += pt.Y;
							}
							io.PICpreprocess(newPic, sPic, pi, pi.format);
						}else if(io.version != V5){
							io.PICextractIndexImage(frmID, oldPic);
							KoishiExpand::KoishiMarkTool::ImageMarking(
								oldPic, newPic, 
								strBasePart[APART_MAXCOUNT] + formatAvatarID(avID), 
								pt, color(1,0,0,0));
							if(pt.X < 0){
								pi.basePt.X += pt.X;
							}
							if(pt.Y < 0){
								pi.basePt.Y += pt.Y;
							}
							io.PICpreprocessIndexImage(newPic, sPic, pi);
						}
						io.PICreplace(frmID, pi, sPic);
					}
					if(singleNPK){
						totalWeaponNo.IMGpush(io, no.entry[imgID].comment);
					}else{
						partNo.IMGpush(io, no.entry[imgID].comment);
					}
					GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000*imgID/no.count);
				}
				if(!singleNPK){
					partNo.saveFile(afterStr);
				}
				GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000);
				GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(1000*(i)/weaponNPK.size());
			}
			if(singleNPK){
				if(totalWeaponNo.count > 0)
					totalWeaponNo.saveFile(afterTotalWeaponStr);
			}
		}
		GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(1000);
	}
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"打标完毕喵。");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"打标完毕喵。");
}