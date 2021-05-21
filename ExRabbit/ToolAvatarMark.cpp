// ToolAvatarMark.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarMark.h"
#include "afxdialogex.h"

// ToolAvatarMark �Ի���

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


// ToolAvatarMark ��Ϣ�������


BOOL ToolAvatarMark::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"��ѡ��Ŀ���ļ��У����ɵĴ���ǵ�NPK��洢��ͬһ�ļ����¡�");
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"������ʾ���ڴ����NPK�ļ���");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"������ʾ���ڴ����IMG�ļ���");

	
	GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetRange32(0, 1000);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetRange32(0, 1000);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	HWND hwnd= GetSafeHwnd();   //�õ����ھ��
	CString filePath= L"";	//�õ��ļ�·��
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//ȡ��IMalloc�������ӿ�
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("ѡ���ļ���");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//ȡ��IMalloc�������ӿ�   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //���һ���ļ�ϵͳ·��
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//�ͷ��ڴ�
			if(filePath.GetLength()<=1){
				MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//�ͷŽӿ�
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
	//��ʼ��һЩ���ʹ�õĳ���
	//��ְҵ���λ��
	point ptBaseCareer[ACHARACTER_MAXCOUNT] = {
		point(120,150),		//SM
		point(138,200),		//SG
		point(140,210),		//FT
		point(140,140),		//FM
		point(135,180),		//GN
		point(130,140),		//GG
		point(137,220),		//MG	��ȷ��
		point(136,210),		//MM
		point(108,120),		//PR
		point(140,110),		//PG
		point(128,140),		//TH
		point(135,210),		//KN
		point(130,140),		//DL
		point(110,120)		//GB
	};
	//�������Ĵ��λ��ƫ����
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
	//��ְҵ��վ��֡��Χ
	int frameEnum[ACHARACTER_MAXCOUNT][2] = {
		{176, 179},{0, 8},{113, 116},{0, 3},{0, 13},{0, 9},{10, 13},{0, 7},{0, 3},{0, 8},{0, 11},{0, 5},{0, 3},{0, 9}
	};
	//�������ת���
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
	BOOL singleNPK = GET_CTRL(CButton, IDC_CHECK1)->GetCheck();
	BOOL wantWeapon = GET_CTRL(CButton, IDC_CHECK2)->GetCheck();
	BOOL onlyNormal = GET_CTRL(CButton, IDC_CHECK3)->GetCheck();
	//����ȡ��������NPK
	CString folderPath;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderPath);
	str pathStr = CStrToStr(folderPath + L"\\");
	int NPKpart, careerID, imgID, frmID;
	for(careerID = 0;careerID < careerList.size(); careerID++){
		AvatarCharacter ac = careerList[careerID];
		NPKobject totalNo, totalWeaponNo;
		str afterTotalStr = pathStr + "marker(" + fixn1[ac] + ").NPK";
		str afterTotalWeaponStr = pathStr + "marker(" +  fixn1[ac] + "_weapon).NPK";
		//װ�粿��
		for(NPKpart = 0;NPKpart < APART_MAXCOUNT;NPKpart++){
			str fileStr = pathStr + NPK_avatar(ac, (AvatarPart)NPKpart);
			str afterStr = pathStr + "marker(" + NPK_avatar(ac, (AvatarPart)NPKpart)+").NPK";
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"���ڶ�"+StrToCStr(NPK_avatar(ac, (AvatarPart)NPKpart))+L"���д���С���");
			NPKobject no;
			if(!no.loadFile(fileStr))
				continue;
			NPKobject partNo;
			int prevID = -1;		//��¼��һ�α�ţ�ͬһ��ŵ�IMGֻ��һ��
			for(imgID = 0;imgID < no.getCount(); imgID++){
				IMGobject io;
				if(!no.IMGextract(imgID,io))
					continue;
				if(io.version == V5)
					continue;
				if(io.version == V6 && io.paletteData.getCount() == 0)
					continue;
				//������һ����Ϊ�˷�ֹ���䲿��Ϊʵɫ
				if((io.version == V4 || io.version == V6) && io.paletteData[0].size() > 0 && io.paletteData[0][0].alpha > 0)
					continue;
				
				//avatar av;
				//avatarLayer al;
				//if(!parseAvatarName(no.entry[imgID].comment, av, al))
				//	continue;
				//if(al == ALAYER_F || al == ALAYER_G)
				//	continue;
				str IDstr = getSerialID(no.content[imgID].comment);
				int avID = std::stoi(IDstr);
				if(avID == prevID)
					continue;
				prevID = avID;
				GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"���ڶ�"+GetTail(StrToCStr(no.content[imgID].comment))+L"���д���С���");
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
					totalNo.IMGpush(no.content[imgID].comment, io);
				}else{
					partNo.IMGpush(no.content[imgID].comment, io);
				}
				GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000 * imgID / no.getCount());
			}
			if(!singleNPK){
				partNo.saveFile(afterStr);
			}
			GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000);
			GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(1000*(NPKpart)/APART_MAXCOUNT);
		}
		if(singleNPK){
			if(totalNo.getCount() > 0)
				totalNo.saveFile(afterTotalStr);
		}
		//��������
		if(wantWeapon){
			int i = 0;
			std::vector<str> weaponNPK = getWeaponNPKlist(ac);
			for(i = 1;i < weaponNPK.size();i++){
				str fileStr = pathStr + weaponNPK[i];
				str afterStr = pathStr + "marker(" + weaponNPK[i]+").NPK";
				GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"���ڶ�"+StrToCStr(weaponNPK[i])+L"���д���С���");
				NPKobject no;
				if(!no.loadFile(fileStr))
					continue;
				NPKobject partNo;
				int prevID = -1;		//��¼��һ�α�ţ�ͬһ��ŵ�IMGֻ��һ��
				for(imgID = 0;imgID < no.getCount(); imgID++){
					IMGobject io;
					if(!no.IMGextract(imgID,io))
						continue;
					if(io.version == V5)
						continue;
					if(io.version == V6 && io.paletteData.getCount() == 0)
						continue;
					//������һ����Ϊ�˷�ֹ���䲿��Ϊʵɫ
					if((io.version == V4 || io.version == V6) && io.paletteData[0].size() > 0 && io.paletteData[0][0].alpha > 0)
						continue;
					str IDstr = getSerialID(no.content[imgID].comment);
					int avID = std::stoi(IDstr);
					if(avID == prevID)
						continue;
					prevID = avID;
					GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"���ڶ�" + GetTail(StrToCStr(no.content[imgID].comment)) + L"���д���С���");
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
						totalWeaponNo.IMGpush(no.content[imgID].comment, io);
					}else{
						partNo.IMGpush(no.content[imgID].comment, io);
					}
					GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000*imgID/no.getCount());
				}
				if(!singleNPK){
					partNo.saveFile(afterStr);
				}
				GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(1000);
				GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(1000*(i)/weaponNPK.size());
			}
			if(singleNPK){
				if(totalWeaponNo.getCount() > 0)
					totalWeaponNo.saveFile(afterTotalWeaponStr);
			}
		}
		GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(1000);
	}
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"����������");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"����������");
}