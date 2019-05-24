// ModalAvatarMap2.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAvatarMap2.h"
#include "afxdialogex.h"


// ModalAvatarMap2 对话框

IMPLEMENT_DYNAMIC(ModalAvatarMap2, CDialogEx)

ModalAvatarMap2::ModalAvatarMap2(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalAvatarMap2::IDD, pParent)
{

}

ModalAvatarMap2::~ModalAvatarMap2()
{
}

void ModalAvatarMap2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalAvatarMap2, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_AVATAR, &ModalAvatarMap2::OnCbnSelchangeComboAvatar)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE, &ModalAvatarMap2::OnCbnSelchangeComboPalette)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, &ModalAvatarMap2::OnBnClickedButtonErase)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &ModalAvatarMap2::OnBnClickedButtonConfirm)
	ON_BN_CLICKED(IDCANCEL, &ModalAvatarMap2::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ModalAvatarMap2 消息处理程序


BOOL ModalAvatarMap2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GET_CTRL(CEdit, IDC_EDIT_ICONID)->SetWindowText(NumToCStr(in.iconID));
	DictAvatarContent dac = in.ptrDict->findTerm(in.ptrFactory->career, in.part, in.iconID);
	if(dac.size() == 0){
		GET_CTRL(CEdit, IDC_EDIT_AVATAR_NAME)->SetWindowText(L"未对应的" + NumToCStr(in.iconID));
	}else{
		GET_CTRL(CEdit, IDC_EDIT_AVATAR_NAME)->SetWindowText(dac[0].avatarName);
	}
	GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->ResetContent();
	GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->AddString(L"未选择");
	for(int i = 0;i <in.ptrFactory->partAlbum[in.part].avatarList.size(); i++){
		avatar av = in.ptrFactory->partAlbum[in.part].avatarList[i];
		CString str = av.isTN ? L"(TN)":L"";
		str += StrToCStr(getAvatarIDString(av.ID));
		if(av.v6palette >= 1){
			str += L"[×" + NumToCStr(av.v6palette)+L"]";
		}
		GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->AddString(str);
	}
	if(dac.size() == 0){
		GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->SetCurSel(0);
	}else{
		long selected = in.ptrFactory->partAlbum[in.part].findPosByID(dac[0].ID, dac[0].isTN);
		GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->SetCurSel(selected + 1);
		if(in.ptrFactory->partAlbum[in.part].avatarList[selected].v6palette == 0){
			GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->ResetContent();
			GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->AddString(L"NA");
			GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->SetCurSel(0);
		}else{
			GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->ResetContent();
			for(int i = 0 ; i<in.ptrFactory->partAlbum[in.part].avatarList[selected].v6palette; i++){
				GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->AddString(L"P" + NumToCStr(i));
			}
			GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->SetCurSel(dac[0].paletteID);
		}
	}
	draw();
	return TRUE;  // return TRUE unless you set the focus to a control
}


void ModalAvatarMap2::OnCbnSelchangeComboAvatar(){
	long selected = GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->GetCurSel() - 1;
	if(selected == -1 || in.ptrFactory->partAlbum[in.part].avatarList[selected].v6palette == 0){
		GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->ResetContent();
		GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->AddString(L"NA");
		GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->SetCurSel(0);
	}else{
		GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->ResetContent();
		for(int i = 0 ; i<in.ptrFactory->partAlbum[in.part].avatarList[selected].v6palette; i++){
			GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->AddString(L"P" + NumToCStr(i));
		}
		GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->SetCurSel(0);
	}
	draw();
}

void ModalAvatarMap2::OnCbnSelchangeComboPalette(){
	draw();
}


void ModalAvatarMap2::OnBnClickedButtonErase(){
	queue posList = in.ptrDict->findPos(in.ptrFactory->career, in.part, in.iconID);
	if(posList.size() == 0){
		MessageBox(L"辞典里没有找到与图标关联的装扮。",L"提示");
		return;
	}
	in.ptrDict->deleteTerm(in.ptrFactory->career, in.part, posList[0]);
	MessageBox(L"已删除关联装扮。",L"提示");
	CDialogEx::OnCancel();
}


void ModalAvatarMap2::OnBnClickedButtonConfirm(){
	queue posList = in.ptrDict->findPos(in.ptrFactory->career, in.part, in.iconID);
	int selected = GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->GetCurSel() - 1;
	int selectedPalette = GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->GetCurSel();
	DictAvatarTerm newTerm;
	GET_CTRL(CEdit, IDC_EDIT_AVATAR_NAME)->GetWindowText(newTerm.avatarName);
	newTerm.iconID = in.iconID;
	if(selected == -1){
		newTerm.ID = -1;
		newTerm.isTN = false;
		newTerm.paletteID = 0;
	}else{
		avatar av = in.ptrFactory->partAlbum[in.part].avatarList[selected];
		newTerm.ID = av.ID;
		newTerm.isTN = av.isTN;
		if(av.v6palette == 0){
			newTerm.paletteID = 0;
		}else{
			newTerm.paletteID = selectedPalette;
		}
	}
	if(posList.size() == 0){
		//没有，新添加
		in.ptrDict->insertTerm(in.ptrFactory->career, in.part, newTerm);
		MessageBox(L"已添加关联装扮。",L"提示");
		CDialogEx::OnCancel();
	}else{
		if(IDNO == MessageBox(L"该图标已被关联装扮，要修改吗？",L"提示", MB_YESNO)){
			return;
		}else{
			in.ptrDict->modifiedTerm(in.ptrFactory->career, in.part, posList[0], newTerm);
			MessageBox(L"已修改关联装扮。",L"提示");
			CDialogEx::OnCancel();
		}
	}
}


void ModalAvatarMap2::OnBnClickedCancel(){
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void ModalAvatarMap2::draw(){
	matrix mat;
	IMGobject bodyIO;
	PICinfo bodyPI;
	matrix bodyMat;
	in.ptrFactory->partAlbum[APART_BODY].sourceNPK.IMGextract(0, bodyIO);
	bodyIO.PICgetInfo(getCareerRepresentativeFrame(in.ptrFactory->career), bodyPI);
	bodyIO.PICextract(getCareerRepresentativeFrame(in.ptrFactory->career), bodyMat);
	bodyMat.turnShield();
	in.ptrFactory->makeModel(mat, 
		color(0xFF, 0xCC, 0xCC, 0xCC), 
		size(200, 200), 
		in.part,
		GET_CTRL(CComboBox, IDC_COMBO_AVATAR)->GetCurSel() - 1,
		GET_CTRL(CComboBox, IDC_COMBO_PALETTE)->GetCurSel(),
		point(0, 0),
		::getCareerRepresentativeFrame(in.ptrFactory->career),
		&bodyPI, &bodyMat);
	CImage img;
	img.Create(200, 200, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int i, j, pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<200;i++){
		for(j=0;j<200;j++){
			*(pst + pit*j + 4*i + 0) = mat[j][i].B;
			*(pst + pit*j + 4*i + 1) = mat[j][i].G;
			*(pst + pit*j + 4*i + 2) = mat[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,10,180);
	ReleaseDC(pDC);
}
void ModalAvatarMap2::drawIcon(){
	matrix mat;
	str fileName = CStrToStr(in.ptrProfile->getIconPath(in.ptrFactory->career)) + getAvatarPartIMGName(in.part)+"_"+CStrToStr(NumToCStr(in.iconID));
	if(!loadImage(fileName, mat)){
		//未读出区域
		in.ptrFactory->makeButton(mat, in.ptrProfile->getAvatarColor(0), size(28, 28), 3);
	}
	CImage img;
	img.Create(28, 28, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int i, j, pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<28;i++){
		for(j=0;j<28;j++){
			*(pst + pit*j + 4*i + 0) = mat[j][i].B;
			*(pst + pit*j + 4*i + 1) = mat[j][i].G;
			*(pst + pit*j + 4*i + 2) = mat[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,80,40);
	ReleaseDC(pDC);
}

void ModalAvatarMap2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	drawIcon();
	draw();
}

bool ModalAvatarMap2::loadImage(str fileNameWithoutExp, matrix &mat){
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