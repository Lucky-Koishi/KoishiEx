// ModalAvatarMap1.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAvatarMap1.h"
#include "afxdialogex.h"


// ModalAvatarMap1 对话框

IMPLEMENT_DYNAMIC(ModalAvatarMap1, CDialogEx)

ModalAvatarMap1::ModalAvatarMap1(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalAvatarMap1::IDD, pParent)
{

}

ModalAvatarMap1::~ModalAvatarMap1()
{
}

void ModalAvatarMap1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalAvatarMap1, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ERASE, &ModalAvatarMap1::OnBnClickedButtonErase)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &ModalAvatarMap1::OnBnClickedButtonConfirm)
	ON_BN_CLICKED(IDCANCEL, &ModalAvatarMap1::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// ModalAvatarMap1 消息处理程序


BOOL ModalAvatarMap1::OnInitDialog(){
	CDialogEx::OnInitDialog();

	avatar av = in.ptrFactory->partAlbum[in.part].avatarList[in.selected];
	GET_CTRL(CEdit, IDC_EDIT_AVATAR)->SetWindowText(av.isTN ? L"(TN)":L"" + NumToCStr(av.ID));
	GET_CTRL(CEdit, IDC_EDIT_PALETTE)->SetWindowText(NumToCStr(in.selectedPalette));
	DictAvatarContent dac = in.ptrDict->findTerm(in.ptrFactory->career, in.part, av.ID, av.isTN, in.selectedPalette);
	if(dac.size() == 0){
		GET_CTRL(CEdit, IDC_EDIT_NAME)->SetWindowText(
			NumToCStr(av.ID)+L"号装扮_"+ NumToCStr(in.selectedPalette));
		GET_CTRL(CEdit, IDC_EDIT_ICON)->SetWindowText(NumToCStr(-1));
	}else{
		GET_CTRL(CEdit, IDC_EDIT_NAME)->SetWindowText(dac[0].avatarName);
		GET_CTRL(CEdit, IDC_EDIT_ICON)->SetWindowText(NumToCStr(dac[0].iconID));
	}

	return TRUE;
}


void ModalAvatarMap1::OnPaint()
{
	CPaintDC dc(this); 
	draw();
}


void ModalAvatarMap1::OnBnClickedButtonErase()
{
	// TODO: 在此添加控件通知处理程序代码
}


void ModalAvatarMap1::OnBnClickedButtonConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
}


void ModalAvatarMap1::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void ModalAvatarMap1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
}

void ModalAvatarMap1::draw(){
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
		in.selected,
		in.selectedPalette,
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
	img.Draw(pDC->m_hDC,10,100);
	ReleaseDC(pDC);
}
void ModalAvatarMap1::drawIcon(){
	//matrix mat;
	//str fileName = CStrToStr(in.ptrProfile->getIconPath(in.ptrFactory->career)) + getAvatarPartIMGName(in.part)+"_"+CStrToStr(NumToCStr(in.iconID))+".PNG";
	//if(!mat.loadPNG(fileName)){
	//	//未读出区域
	//	in.ptrFactory->makeButton(mat, in.ptrProfile->getAvatarColor(0), size(28, 28), 3);
	//}
	//CImage img;
	//img.Create(28, 28, 32);
	//UCHAR* pst = (UCHAR*)img.GetBits();
	//int i, j, pit = img.GetPitch();
	//CDC *pDC = GetDC();
	//for(i=0;i<28;i++){
	//	for(j=0;j<28;j++){
	//		*(pst + pit*j + 4*i + 0) = mat[j][i].B;
	//		*(pst + pit*j + 4*i + 1) = mat[j][i].G;
	//		*(pst + pit*j + 4*i + 2) = mat[j][i].R;
	//	}
	//}
	//img.Draw(pDC->m_hDC,80,40);
	//ReleaseDC(pDC);
}