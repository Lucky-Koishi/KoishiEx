// ModalAvatarUpdate.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAvatarUpdate.h"
#include "afxdialogex.h"


// ModalAvatarUpdate 对话框

IMPLEMENT_DYNAMIC(ModalAvatarUpdate, CDialogEx)

ModalAvatarUpdate::ModalAvatarUpdate(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalAvatarUpdate::IDD, pParent)
{

}

ModalAvatarUpdate::~ModalAvatarUpdate()
{
}

void ModalAvatarUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalAvatarUpdate, CDialogEx)
	ON_BN_CLICKED(IDSTART, &ModalAvatarUpdate::OnBnClickedStart)
END_MESSAGE_MAP()


// ModalAvatarUpdate 消息处理程序


void ModalAvatarUpdate::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(updateThread, this);
}

void ModalAvatarUpdate::updateCareer(avatarCareer ac){
	int i, j, k, p = ac - 1;
	avatarFactory factory;
	factory.setCarrer(ac);
	factory.setPath(CStrToStr(resourcePath));

	eList[p]->SetWindowText(L"读取NPK中。");
	pcList[p]->SetRange32(0, 8);
	for(i=1;i<APART_MAXCOUNT;i++){
		factory.loadNPK((avatarPart)i);
		pcList[p]->SetPos(i-1);
		eList[p]->SetWindowText(L"读取"+StrToCStr(KoishiAvatar::getAvatarPartNPKName((avatarPart)i))+L"中。");
	}
	eList[p]->SetWindowText(L"读取NPK完毕喵。");
	IMGobject bodyIO;
	PICinfo bodyPI;
	matrix bodyMat;
	factory.partAlbum[APART_BODY].sourceNPK.IMGextract(0, bodyIO);
	bodyIO.PICgetInfo(getCareerRepresentativeFrame(ac), bodyPI);
	bodyIO.PICextract(getCareerRepresentativeFrame(ac), bodyMat);
	bodyMat.turnShield();
	str fileName;
	int tempPart, tempSize, selected;
	int totalSelect;
	int thumbnailWidthList[4] = {60, 72, 90, 120};
	int thumbnailHeightList[4] = {80, 96, 120, 160};
	pcList[p]->SetRange32(0, 1000);
	for(tempPart = 1;tempPart < APART_MAXCOUNT; tempPart++){
		totalSelect = factory.partAlbum[tempPart].avatarList.size();
		for(selected = 0;selected < totalSelect; selected++){
			for(tempSize = 0;tempSize<4;tempSize++){
				//TRACE(NumToCStr(ac)+L"\n");
				matrix mat;
				factory.makeModel(mat, getCareerColor(ac), size(thumbnailWidthList[tempSize], thumbnailHeightList[tempSize]), (avatarPart)tempPart, selected, 0, getAvatarModelOffset(ac, (avatarPart)tempPart), getCareerRepresentativeFrame(ac), &bodyPI, &bodyMat);
				fileName = CStrToStr(profile.getThumbnailPath(tempSize, ac)) + KoishiAvatar::getAvatarIMGName(ac, (avatarPart)tempPart) +"_" + CStrToStr(NumToCStr(factory.partAlbum[(avatarPart)tempPart].avatarList[selected].ID)) + ".bmp";
				KoishiExpand::KoishiImageTool::makeBMP(mat, fileName);
				mat.destory();
				double rate = (double)(tempPart-1)/(APART_MAXCOUNT-1) +
					(double)selected/totalSelect/(APART_MAXCOUNT-1) +
					(double)tempSize/totalSelect/(APART_MAXCOUNT-1)/4;
				pcList[p]->SetPos(1000*rate);
				eList[p]->SetWindowText(L"("+DoubleToCStr(100*rate)+L"％)生成"+StrToCStr(KoishiAvatar::getAvatarIMGName(ac, (avatarPart)tempPart) + CStrToStr(NumToCStr(factory.partAlbum[(avatarPart)tempPart].avatarList[selected].ID)))+L"的展示图中。");
			}
		}
	}

	fileName = CStrToStr(resourcePath + L"\\") + KoishiAvatar::getIconNPKName(ac);
	CString fileInfoName = profile.getIconPath(ac) + L"count.txt";
	eList[p]->SetWindowText(L"读取图标中。");
	pcList[p]->SetPos(0);
	NPKobject no;
	CStdioFile file;
	file.Open(fileInfoName, CFile::modeCreate|CFile::modeWrite);
	if(!no.loadFile(fileName)){
		pcList[p]->SetPos(1000);
		eList[p]->SetWindowText(L"图标NPK没找到喵。");
		return;
	}else{
		for(i = 1;i<APART_MAXCOUNT;i++){
			std::vector<str> s = KoishiAvatar::getIconIMGName(ac, (KoishiAvatar::avatarPart)i);	//同部件图标有可能装入两个IMG中，获得IMG列表
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
						pcList[p]->SetPos(1000*rate);
						eList[p]->SetWindowText(L"("+DoubleToCStr(100*rate) +	L"％)提取"+ StrToCStr(KoishiAvatar::getAvatarPartIMGName((avatarPart)i) + "_" )+NumToCStr(id)+L"图标中。");
						KoishiExpand::KoishiImageTool::makeBMP(iconMat, CStrToStr(profile.getIconPath(ac)) + KoishiAvatar::getAvatarPartIMGName((avatarPart)i) + "_" + CStrToStr(NumToCStr(id)) + ".bmp");
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
	}
	pcList[p]->SetPos(1000);
	eList[p]->SetWindowText(L"生成完毕喵。");
}

UINT ModalAvatarUpdate::updateThread(void* para){
	ModalAvatarUpdate*dlg = (ModalAvatarUpdate*)para;
	dlg -> updateSerial = 0;
	AfxBeginThread(updateCareerThread, para);
	Sleep(10);
	dlg -> updateSerial = 1;
	AfxBeginThread(updateCareerThread, para);
	Sleep(10);
	dlg -> updateSerial = 2;
	AfxBeginThread(updateCareerThread, para);
	Sleep(10);
	dlg -> updateSerial = 3;
	AfxBeginThread(updateCareerThread, para);
	return 0U;
}
UINT ModalAvatarUpdate::updateCareerThread(void* para){
	ModalAvatarUpdate*dlg = (ModalAvatarUpdate*)para;
	avatarCareer ac = (avatarCareer)(dlg->updateSerial + 1);
	if(ac == ACAREER_MAXCOUNT)
		return 0;
	dlg->isStart[ac - 1] = true;
	/*if(dlg -> updateSerial <14){
		Sleep(10);
		dlg -> updateSerial ++;
		int currentSerial = dlg->updateSerial;
		if(currentSerial >= 4){
			while(dlg->isOver[currentSerial-4] == false);
		}
		AfxBeginThread(updateCareerThread, para);
	}*/
	//TRACE(NumToCStr(ac)+L" START\n");
	if(dlg->bList[ac-1]->GetCheck() == TRUE){
		dlg->updateCareer(ac);
	}else{
		dlg->eList[ac-1]->SetWindowText(L"忽视此项");
	}
	//TRACE(NumToCStr(ac)+L" end\n");
		
	dlg->isOver[ac - 1] = true;
	//检测还有哪个没开始
	for(int i = 4;i<ACAREER_MAXCOUNT-1;i++){
		if(!dlg->isStart[i]){
			dlg->updateSerial = i;
			AfxBeginThread(updateCareerThread, para);
			break;
		}
	}
	return 0;
}

BOOL ModalAvatarUpdate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pcList[0] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A1);
	pcList[1] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A2);
	pcList[2] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A3);
	pcList[3] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A4);
	pcList[4] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A5);
	pcList[5] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A6);
	pcList[6] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A7);
	pcList[7] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A8);
	pcList[8] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A9);
	pcList[9] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A10);
	pcList[10] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A11);
	pcList[11] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A12);
	pcList[12] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A13);
	pcList[13] = GET_CTRL(CProgressCtrl, IDC_PROGRESS_A14);
	eList[0] = GET_CTRL(CEdit, IDC_EDIT_A1);
	eList[1] = GET_CTRL(CEdit, IDC_EDIT_A2);
	eList[2] = GET_CTRL(CEdit, IDC_EDIT_A3);
	eList[3] = GET_CTRL(CEdit, IDC_EDIT_A4);
	eList[4] = GET_CTRL(CEdit, IDC_EDIT_A5);
	eList[5] = GET_CTRL(CEdit, IDC_EDIT_A6);
	eList[6] = GET_CTRL(CEdit, IDC_EDIT_A7);
	eList[7] = GET_CTRL(CEdit, IDC_EDIT_A8);
	eList[8] = GET_CTRL(CEdit, IDC_EDIT_A9);
	eList[9] = GET_CTRL(CEdit, IDC_EDIT_A10);
	eList[10] = GET_CTRL(CEdit, IDC_EDIT_A11);
	eList[11] = GET_CTRL(CEdit, IDC_EDIT_A12);
	eList[12] = GET_CTRL(CEdit, IDC_EDIT_A13);
	eList[13] = GET_CTRL(CEdit, IDC_EDIT_A14);
	bList[0] = GET_CTRL(CButton, IDC_CHECK_A1);
	bList[1] = GET_CTRL(CButton, IDC_CHECK_A2);
	bList[2] = GET_CTRL(CButton, IDC_CHECK_A3);
	bList[3] = GET_CTRL(CButton, IDC_CHECK_A4);
	bList[4] = GET_CTRL(CButton, IDC_CHECK_A5);
	bList[5] = GET_CTRL(CButton, IDC_CHECK_A6);
	bList[6] = GET_CTRL(CButton, IDC_CHECK_A7);
	bList[7] = GET_CTRL(CButton, IDC_CHECK_A8);
	bList[8] = GET_CTRL(CButton, IDC_CHECK_A9);
	bList[9] = GET_CTRL(CButton, IDC_CHECK_A10);
	bList[10] = GET_CTRL(CButton, IDC_CHECK_A11);
	bList[11] = GET_CTRL(CButton, IDC_CHECK_A12);
	bList[12] = GET_CTRL(CButton, IDC_CHECK_A13);
	bList[13] = GET_CTRL(CButton, IDC_CHECK_A14);
	bList[0]->SetWindowText(L"鬼剑士(男)");
	bList[1]->SetWindowText(L"鬼剑士(女)");
	bList[2]->SetWindowText(L"格斗家(女)");
	bList[3]->SetWindowText(L"格斗家(男)");
	bList[4]->SetWindowText(L"神枪手(男)");
	bList[5]->SetWindowText(L"神枪手(女)");
	bList[6]->SetWindowText(L"魔法师(女)");
	bList[7]->SetWindowText(L"魔法师(男)");
	bList[8]->SetWindowText(L"圣职者(男)");
	bList[9]->SetWindowText(L"圣职者(女)");
	bList[10]->SetWindowText(L"暗夜使者");
	bList[11]->SetWindowText(L"守护者");
	bList[12]->SetWindowText(L"魔枪士");
	bList[13]->SetWindowText(L"枪剑士");
	for(int i = 0;i<14;i++){
		eList[i]->SetWindowText(L"等待……");
		bList[i]->SetCheck(TRUE);
		isOver[i] = false;
		isStart[i] = false;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
