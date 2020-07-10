// ToolAvatarCharacterSelection.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarCharacterSelection.h"
#include "afxdialogex.h"


// ToolAvatarCharacterSelection 对话框

IMPLEMENT_DYNAMIC(ToolAvatarCharacterSelection, CDialogEx)

ToolAvatarCharacterSelection::ToolAvatarCharacterSelection(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarCharacterSelection::IDD, pParent)
{

}

ToolAvatarCharacterSelection::~ToolAvatarCharacterSelection()
{
}

void ToolAvatarCharacterSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarCharacterSelection, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// ToolAvatarCharacterSelection 消息处理程序



BOOL ToolAvatarCharacterSelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowPos(NULL,0,0,256,278,SWP_NOZORDER|SWP_NOMOVE);
	charImg[0].LoadBitmap(IDB_CHAR_0X);
	charImg[1].LoadBitmap(IDB_CHAR_1X);
	charImg[2].LoadBitmap(IDB_CHAR_2X);
	charImg[3].LoadBitmap(IDB_CHAR_3X);
	charImg[4].LoadBitmap(IDB_CHAR_4X);
	charImg[5].LoadBitmap(IDB_CHAR_5X);
	charImg[6].LoadBitmap(IDB_CHAR_6X);
	charImg[7].LoadBitmap(IDB_CHAR_7X);
	charImg[8].LoadBitmap(IDB_CHAR_8X);
	charImg[9].LoadBitmap(IDB_CHAR_9X);
	charImg[10].LoadBitmap(IDB_CHAR_10X);
	charImg[11].LoadBitmap(IDB_CHAR_11X);
	charImg[12].LoadBitmap(IDB_CHAR_12X);
	charImg[13].LoadBitmap(IDB_CHAR_13X);
	charImg[14].LoadBitmap(IDB_CHAR_EXIT);
	charImg[15].LoadBitmap(IDB_CHAR_NONE);
	for(int i = 0;i<16;i++){
		charImgCtl[i] = new CStatic;
		charImgCtl[i]->Create(L"", SS_BITMAP | WS_CHILD | WS_VISIBLE, CRect(
			60 * (i % 4), 60 * (i / 4), 
			60 * (i % 4) + 60, 60 * (i / 4) + 60
		), this);
		charImgCtl[i]->SetBitmap(charImg[i]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ToolAvatarCharacterSelection::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void ToolAvatarCharacterSelection::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint myPoint;
    GetCursorPos(&myPoint); //鼠标位置
	ScreenToClient(&myPoint);
	long x = myPoint.x;
	long y = myPoint.y;
	int clicked = y/ 60 * 4 + x / 60;
	if(clicked <= 13){
		output = clicked;
		OnOK();
	}else{
		OnCancel();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
