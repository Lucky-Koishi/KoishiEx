// TinyNoteBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinyNoteBar.h"
#include "afxdialogex.h"


// TinyNoteBar �Ի���

IMPLEMENT_DYNAMIC(TinyNoteBar, CDialogEx)

TinyNoteBar::TinyNoteBar(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyNoteBar::IDD, pParent)
{

}

TinyNoteBar::~TinyNoteBar()
{
}

void TinyNoteBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyNoteBar, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &TinyNoteBar::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &TinyNoteBar::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TinyNoteBar::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// TinyNoteBar ��Ϣ�������


BOOL TinyNoteBar::OnInitDialog() {
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CStatic, IDC_STATIC1)->GetWindowRect(&rcBoard);
	ScreenToClient(&rcBoard);
	GET_CTRL(CStatic, IDC_STATIC1)->ShowWindow(SW_HIDE);
	drawBar();
	CString mstr = content.toString();
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(mstr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void TinyNoteBar::drawBar() {
	image im;
	content.makeImage(im, size(rcBoard.Width(), rcBoard.Height()));
	CImage img;
	img.Create(im.width, im.height, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(int i = 0; i<im.width; i++) {
		for(int j = 0; j<im.height; j++) {
			*(pst + pit*j + 4 * i + 0) = im[j][i].B;
			*(pst + pit*j + 4 * i + 1) = im[j][i].G;
			*(pst + pit*j + 4 * i + 2) = im[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC, rcBoard.left, rcBoard.top);
	img.Destroy();
	ReleaseDC(pDC);
}

void TinyNoteBar::OnEnChangeEdit1() {
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString mstr ;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(mstr);
	content.parse(mstr);
	drawBar();
}


void TinyNoteBar::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void TinyNoteBar::OnBnClickedCancel() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void TinyNoteBar::OnPaint() {
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	drawBar();
}
