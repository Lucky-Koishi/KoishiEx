// ModalGradient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalGradient.h"
#include "afxdialogex.h"


// ModalGradient �Ի���

IMPLEMENT_DYNAMIC(ModalGradient, CDialogEx)

ModalGradient::ModalGradient(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalGradient::IDD, pParent)
{

}

ModalGradient::~ModalGradient()
{
}

void ModalGradient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalGradient, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TARGET1, &ModalGradient::OnBnClickedRadioTarget1)
	ON_BN_CLICKED(IDC_RADIO_TARGET2, &ModalGradient::OnBnClickedRadioTarget2)
	ON_BN_CLICKED(IDC_RADIO_TARGET3, &ModalGradient::OnBnClickedRadioTarget3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalGradient::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalGradient::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalGradient::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE4, &ModalGradient::OnBnClickedRadioOperate4)
	ON_BN_CLICKED(IDC_RADIO_OPERATE5, &ModalGradient::OnBnClickedRadioOperate5)
	ON_BN_CLICKED(IDC_BUTTON_COLOR1, &ModalGradient::OnBnClickedButtonColor1)
	ON_BN_CLICKED(IDC_BUTTON_COLOR2, &ModalGradient::OnBnClickedButtonColor2)
	ON_BN_CLICKED(IDC_CHECK1, &ModalGradient::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &ModalGradient::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &ModalGradient::OnBnClickedOk)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_KEYALPHA1, &ModalGradient::OnEnChangeEditKeyalpha1)
	ON_EN_CHANGE(IDC_EDIT_KEYALPHA2, &ModalGradient::OnEnChangeEditKeyalpha2)
END_MESSAGE_MAP()


// ModalGradient ��Ϣ�������


void ModalGradient::OnBnClickedRadioTarget1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 1;
}


void ModalGradient::OnBnClickedRadioTarget2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 2;
}


void ModalGradient::OnBnClickedRadioTarget3(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.target = 3;
}


void ModalGradient::OnBnClickedRadioOperate1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.useProperty = COLOR_GRAYSCALE;
}


void ModalGradient::OnBnClickedRadioOperate2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.useProperty = COLOR_HUE;
}


void ModalGradient::OnBnClickedRadioOperate3(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.useProperty = COLOR_CHANNEL_RED;
}


void ModalGradient::OnBnClickedRadioOperate4(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.useProperty = COLOR_CHANNEL_GREEN;
}


void ModalGradient::OnBnClickedRadioOperate5(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.useProperty = COLOR_CHANNEL_BLUE;
}


void ModalGradient::OnBnClickedButtonColor1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString colorStr;
	GET_CTRL(CEdit, IDC_EDIT_KEYCOLOR1)->GetWindowText(colorStr);
	int colorValue = B16CStrToNum(colorStr);
	COLORREF sclr = RGB(colorValue >> 16, colorValue >> 8, colorValue);
	CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
	if(cdlg.DoModal() == IDOK){
		sclr = cdlg.GetColor();
		colorStr.Format(L"%02X%02X%02X", GetRValue(sclr),
			GetGValue(sclr), GetBValue(sclr));
		out.keyColor1 = color(out.keyColor1.A, GetRValue(sclr),
			GetGValue(sclr), GetBValue(sclr));
		GET_CTRL(CEdit, IDC_EDIT_KEYCOLOR1)->SetWindowText(colorStr);
		drawScale();
	}
}


void ModalGradient::OnBnClickedButtonColor2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString colorStr;
	GET_CTRL(CEdit, IDC_EDIT_KEYCOLOR2)->GetWindowText(colorStr);
	int colorValue = B16CStrToNum(colorStr);
	COLORREF sclr = RGB(colorValue >> 16, colorValue >> 8, colorValue);
	CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
	if(cdlg.DoModal() == IDOK){
		sclr = cdlg.GetColor();
		colorStr.Format(L"%02X%02X%02X", GetRValue(sclr),
			GetGValue(sclr), GetBValue(sclr));
		out.keyColor2 = color(out.keyColor2.A, GetRValue(sclr),
			GetGValue(sclr), GetBValue(sclr));
		GET_CTRL(CEdit, IDC_EDIT_KEYCOLOR2)->SetWindowText(colorStr);
		drawScale();
	}
}


void ModalGradient::OnBnClickedCheck1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	drawScale();
}


void ModalGradient::OnBnClickedCheck2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.remainAlpha = GET_CTRL(CButton, IDC_CHECK2)->GetCheck() == 1;
}


BOOL ModalGradient::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	out.useProperty = COLOR_GRAYSCALE;
	out.keyColor1 = color(0xFF, 0, 0, 0);
	out.keyColor2 = color(0xFF, 0xFF, 0xFF, 0xFF);
	out.target = 1;
	out.remainAlpha = true;
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_TARGET1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CEdit, IDC_EDIT_KEYCOLOR1)->SetWindowText(L"000000");
	GET_CTRL(CEdit, IDC_EDIT_KEYCOLOR2)->SetWindowText(L"FFFFFF");
	GET_CTRL(CEdit, IDC_EDIT_KEYALPHA1)->SetWindowText(L"FF");
	GET_CTRL(CEdit, IDC_EDIT_KEYALPHA2)->SetWindowText(L"FF");
	drawScale();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalGradient::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(GET_CTRL(CButton, IDC_CHECK1)->GetCheck()){
		color middle = out.keyColor1;
		out.keyColor1 = out.keyColor2;
		out.keyColor2 = middle;
	}
	out.remainAlpha = GET_CTRL(CButton, IDC_CHECK2)->GetCheck() == 1;
	CDialogEx::OnOK();
}


void ModalGradient::drawScale(){
	CRect rc;
	GetClientRect(rc);

	color clr;
	color clrLine(0xFF, 0, 0, 0);
	int H = 25;
	int W = rc.Width();
	matrix canvas(H, W);
	matrix gradients(H, W);
	canvas.filledLattice(point(0,0), point(W-1, H-1), color(0xFF,0XFF,0XFF,0XFF),color(0xFF,0xCC,0xCC,0xCC), 5);
	colorList keyColorList;
	if(GET_CTRL(CButton, IDC_CHECK1)->GetCheck()){
		keyColorList.push_back(out.keyColor1);
		keyColorList.push_back(out.keyColor2);
	}else{
		keyColorList.push_back(out.keyColor2);
		keyColorList.push_back(out.keyColor1);
	}
	for(int x = 0;x<W;x++){
		uchar grayed = 0xFF*x/W;
		TRACE(NumToCStr(grayed)+L":");
		color current = KoishiImageTool::gradient(color(0xFF, grayed, grayed, grayed), keyColorList, COLOR_GRAYSCALE);
		TRACE(DoubleToCStr(current.getProperty(COLOR_GRAYSCALE))+L"\n");
		gradients.line(point(x, 0), point(x, H-1), current);
	}
	canvas.putFore(gradients);
	canvas.rectangle(point(0,0), point(W-1,H-1), clrLine);
	canvas.rectangle(point(1,1), point(W-2,H-2), color(0xFF,0xCC,0xCC,0xCC));
	CImage img;
	img.Create(W,H,32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(int i=0;i<W;i++){
		for(int j=0;j<H;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,0,0);
	img.Destroy();
	ReleaseDC(pDC);
}

void ModalGradient::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	drawScale();
}


void ModalGradient::OnEnChangeEditKeyalpha1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString colorStr;
	GET_CTRL(CEdit, IDC_EDIT_KEYALPHA1)->GetWindowText(colorStr);
	int colorValue = B16CStrToNum(colorStr);
	if(colorValue != out.keyColor1.A){
		out.keyColor1.A = colorValue;
		drawScale();
	}
}


void ModalGradient::OnEnChangeEditKeyalpha2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString colorStr;
	GET_CTRL(CEdit, IDC_EDIT_KEYALPHA2)->GetWindowText(colorStr);
	int colorValue = B16CStrToNum(colorStr);
	if(colorValue != out.keyColor2.A){
		out.keyColor2.A = colorValue;
		drawScale();
	}
}
