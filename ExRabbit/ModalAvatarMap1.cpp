// ModalAvatarMap1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAvatarMap1.h"
#include "afxdialogex.h"


// ModalAvatarMap1 �Ի���

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


// ModalAvatarMap1 ��Ϣ�������


BOOL ModalAvatarMap1::OnInitDialog(){
	CDialogEx::OnInitDialog();

	avatar av = in.ptrFactory->partAlbum[in.part].avatarList[in.selected];
	GET_CTRL(CEdit, IDC_EDIT_AVATAR)->SetWindowText((av.isTN ? L"(TN)":L"") + NumToCStr(av.ID));
	GET_CTRL(CEdit, IDC_EDIT_PALETTE)->SetWindowText(NumToCStr(in.selectedPalette));
	DictAvatarContent dac = in.ptrDict->findTerm(in.ptrFactory->career, in.part, av.ID, av.isTN, in.selectedPalette);
	if(dac.size() == 0){
		GET_CTRL(CEdit, IDC_EDIT_NAME)->SetWindowText(
			NumToCStr(av.ID)+L"��װ��_"+ NumToCStr(in.selectedPalette));
		GET_CTRL(CEdit, IDC_EDIT_ICON)->SetWindowText(NumToCStr(-1));
	}else{
		GET_CTRL(CEdit, IDC_EDIT_NAME)->SetWindowText(dac[0].avatarName);
		GET_CTRL(CEdit, IDC_EDIT_ICON)->SetWindowText(NumToCStr(dac[0].iconID));
	}
	page = 0;
	selectedIcon = -1;
	return TRUE;
}


void ModalAvatarMap1::OnPaint(){
	CPaintDC dc(this); 
	draw();
	drawIcon();
}


void ModalAvatarMap1::OnBnClickedButtonErase(){
	avatar av = in.ptrFactory->partAlbum[in.part].avatarList[in.selected];
	queue posList = in.ptrDict->findPos(in.ptrFactory->career, in.part, av.ID, av.isTN, in.selectedPalette);
	if(posList.size() == 0){
		MessageBox(L"�ǵ���û���ҵ���ͼ�������װ�硣",L"��ʾ");
		return;
	}
	in.ptrDict->deleteTerm(in.ptrFactory->career, in.part, posList[0]);
	MessageBox(L"��ɾ������װ�硣",L"��ʾ");
	CDialogEx::OnCancel();
}


void ModalAvatarMap1::OnBnClickedButtonConfirm(){
	avatar av = in.ptrFactory->partAlbum[in.part].avatarList[in.selected];
	queue posList = in.ptrDict->findPos(in.ptrFactory->career, in.part, av.ID, av.isTN, in.selectedPalette);
	DictAvatarTerm newTerm;
	GET_CTRL(CEdit, IDC_EDIT_NAME)->GetWindowText(newTerm.avatarName);
	newTerm.iconID = selectedIcon;
	if(selectedIcon == -1){
		MessageBox(L"��Ҫѡ��һ��ͼ������",L"��ʾ��");
		return;
	}else{
		newTerm.iconID = selectedIcon;
		newTerm.ID = av.ID;
		newTerm.isTN = av.isTN;
		if(av.v6palette == 0){
			newTerm.paletteID = 0;
		}else{
			newTerm.paletteID = in.selectedPalette;
		}
	}
	if(posList.size() == 0){
		//û�У������
		in.ptrDict->insertTerm(in.ptrFactory->career, in.part, newTerm);
		MessageBox(L"����ӹ���װ�硣",L"��ʾ");
		CDialogEx::OnCancel();
	}else{
		if(IDNO == MessageBox(L"��ͼ���ѱ�����װ�磬Ҫ�޸���",L"��ʾ", MB_YESNO)){
			return;
		}else{
			in.ptrDict->modifiedTerm(in.ptrFactory->career, in.part, posList[0], newTerm);
			MessageBox(L"���޸Ĺ���װ�硣",L"��ʾ");
			CDialogEx::OnCancel();
		}
	}
}


void ModalAvatarMap1::OnBnClickedCancel(){
	CDialogEx::OnCancel();
}


void ModalAvatarMap1::OnLButtonDown(UINT nFlags, CPoint pt){
	CDialogEx::OnLButtonDown(nFlags, pt);
	CPoint myPoint;
    GetCursorPos(&myPoint); //���λ��
	ScreenToClient(&myPoint);
	point xy(myPoint.x-270, myPoint.y-10);
	int checkSelected = xy.Y / 30 * 8 + xy.X / 30;
	if(xy.X > 30*6 && xy.Y > 30*11){
		checkSelected = 1000;
	}
	if(xy.X > 30*7 && xy.Y > 30*11){
		checkSelected = 1001;
	}
	if(checkSelected < 1000){
		long newSelected = page * 94 + checkSelected;
		if(newSelected >= in.maxIconCount){
			return;
		}else{
			selectedIcon = newSelected;
			GET_CTRL(CEdit, IDC_EDIT_ICON)->SetWindowText(NumToCStr(selectedIcon));
			drawIcon();
		}
	}else if(checkSelected == 1000){
		if(page > 0){
			page --;
			drawIcon();
		}
	}else if(checkSelected == 1001){
		if((page+1)*94<in.maxIconCount){
			page ++;
			drawIcon();
		}
	}
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
	img.Draw(pDC->m_hDC,40,130);
	ReleaseDC(pDC);
}
void ModalAvatarMap1::drawIcon(){
	matrix canvas, mat;
	canvas.create(360, 240);
	canvas.fill(in.ptrProfile->getAvatarColor(1));
	int i, j, id;
	int row= 0, column = 0;
	for(i = 0;i<94;i++){
		id = page*94 + i;
		if(id >= in.maxIconCount){
			//Խ������
			in.ptrFactory->makeButton(mat, in.ptrProfile->getAvatarColor(1), size(30, 30), 2);
		}else{
			str fileName = CStrToStr(in.ptrProfile->getIconPath(in.ptrFactory->career)) + getAvatarPartIMGName(in.part)+"_"+CStrToStr(NumToCStr(id));
			if(!loadImage(fileName, mat)){
				//δ��������
				in.ptrFactory->makeButton(mat, in.ptrProfile->getAvatarColor(0), size(30, 30), 3);
				canvas.putFore(mat, LAY, point(column*30, row*30));
			}else{
				canvas.putFore(mat, LAY, point(column*30+1, row*30+1));
			}
		}
		column ++;
		if(column == 8){
			column = 0;
			row ++;
		}
		if(row == 11 && column >= 6)
			break;
		if(row >= 12)
			break;
	}
	//����ť
	matrix button1;
	in.ptrFactory->makeButton(button1, color(0x77, 0x99, 0xFF), size(30, 30), 0);
	canvas.putFore(button1, LAY, point(240-60, 360-30));
	in.ptrFactory->makeButton(button1, color(0xFF, 0x99, 0x77), size(30, 30), 1);
	canvas.putFore(button1, LAY, point(240-30, 360-30));
	//��ѡ����
	matrix mark(30, 30);
	mark.rectangle(point(0,0), point(29, 29), color(0xFF, 0xFF, 0xFF, 0));
	mark.rectangle(point(1,1), point(28, 28), color(0xFF, 0xFF, 0xFF, 0));
	int tempSelected = selectedIcon;
	int rn1 = page*94;
	int rn2 = (page + 1)*94 - 1;
	if(tempSelected >= rn1 && tempSelected <= rn2){
		tempSelected %= 94;
		canvas.putFore(mark, LAY, point(30 * (tempSelected % 8), 30 * (tempSelected / 8)));
	}
	CImage img;
	img.Create(240, 360, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<240;i++){
		for(j=0;j<360;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,270,10);
	ReleaseDC(pDC);
}

bool ModalAvatarMap1::loadImage(str fileNameWithoutExp, matrix &mat){
	str fileName = fileNameWithoutExp + ".png";
	if(mat.loadPNG(fileName)){
		return true;
	}
	fileName = fileNameWithoutExp + ".bmp";
	if(KoishiExpand::KoishiImageTool::loadBMP(mat, fileName)){
		return true;
	}
	return false;
}