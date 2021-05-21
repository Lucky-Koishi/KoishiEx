// TinyColorSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyColorSelect.h"
#include "afxdialogex.h"


// TinyColorSelect �Ի���

IMPLEMENT_DYNAMIC(TinyColorSelect, CDialogEx)

TinyColorSelect::TinyColorSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyColorSelect::IDD, pParent)
{

}

TinyColorSelect::~TinyColorSelect()
{
}

void TinyColorSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyColorSelect, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// TinyColorSelect ��Ϣ�������


BOOL TinyColorSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void TinyColorSelect::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	int i,j;
	color clr;
	color clrBack(0xFF, 0xFF, 0xFF, 0xFF);
	color clrLine(0xFF, 0, 0, 0);
	image canvas(160, 160);
	image block(10, 10);
	image alphaBlock(10, 10);
	alphaBlock.filledLattice(point(0,0),point(9,9),color(0xff, 0xff, 0xff, 0xff),color(0xff,0xcc,0xcc,0xcc),3);
	int index = 0;
	for(j=0;j<16;j++){
		for(i=0;i<16;i++){
			if(i+16*j >= in.size()){
				block.fill(color(0XFF, 0XFF, 0XFF, 0XFF));
				block.line(point(1,1), point(8,8), color(0xFF, 0, 0, 0));
				block.line(point(1,8), point(8,1), color(0xFF, 0, 0, 0));
			}else{
				block.fill(in[i+16*j]);
				block.putBack(alphaBlock);
			}
			canvas.putFore(block, LAY, point(10*i, 10*j));
		}
	}
	CImage img;
	img.Create(160,160,32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<160;i++){
		for(j=0;j<160;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,0,0);
	img.Destroy();
	ReleaseDC(pDC);
}


void TinyColorSelect::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint myPoint;
    GetCursorPos(&myPoint); //���λ��
	ScreenToClient(&myPoint);
	if(myPoint.x >= 0 && myPoint.x < 160 && myPoint.y >= 0 && myPoint.y < 160){
		int sel = myPoint.x / 10 + myPoint.y / 10 * 16; 
		if(sel < in.size()){
			selection = sel;
			CDialogEx::OnLButtonDown(nFlags, point);
			OnOK();
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
