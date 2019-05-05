// TinyBar.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyBar.h"
#include "afxdialogex.h"


// TinyBar 对话框

IMPLEMENT_DYNAMIC(TinyBar, CDialogEx)

TinyBar::TinyBar(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyBar::IDD, pParent)
{

}

TinyBar::~TinyBar(){
}

void TinyBar::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyBar, CDialogEx)
END_MESSAGE_MAP()


// TinyBar 消息处理程序

void TinyBar::setMax(long value){
	GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetRange32(0, value);
}
void TinyBar::setPos(long value){
	GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(value);
}
void TinyBar::setInfo(CString info){
	GET_CTRL(CStatic, IDC_STATIC_INFO)->SetWindowText(info);
}
void TinyBar::setInfo(CString info, long value){
	setPos(value);
	setInfo(info);
}
void TinyBar::show(){
	ShowWindow(SW_SHOW);
}
void TinyBar::show(long value){
	show();
	setMax(value);
}
void TinyBar::hide(){
	ShowWindow(SW_HIDE);
}