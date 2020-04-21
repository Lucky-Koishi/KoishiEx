// TinyClipBoard.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyClipBoard.h"
#include "afxdialogex.h"
#include "GoodListCtrl.h"

// TinyClipBoard 对话框

IMPLEMENT_DYNAMIC(TinyClipBoard, CDialogEx)

TinyClipBoard::TinyClipBoard(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyClipBoard::IDD, pParent)
{

}

TinyClipBoard::~TinyClipBoard()
{
}

void TinyClipBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyClipBoard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &TinyClipBoard::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEALL, &TinyClipBoard::OnBnClickedButtonRemoveall)
	ON_BN_CLICKED(IDOK, &TinyClipBoard::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyClipBoard 消息处理程序


BOOL TinyClipBoard::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	selectID = -1;
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertColumn(L"剪辑库中的IMG,200");
	for(int i = 0;i<ptrClipNo->count;i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertItem(GetTail(StrToCStr(ptrClipNo->entry[i].comment)));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void TinyClipBoard::OnBnClickedButtonRemove(){
	// TODO: 在此添加控件通知处理程序代码
	selectID = GET_CTRL(CGoodListCtrl, IDC_LIST1)->GetSelectionMark();
	CHECK_VALID(selectID >= 0);
	ptrClipNo->remove(selectID);
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->DeleteItem(selectID);
	selectID = -1;
}


void TinyClipBoard::OnBnClickedButtonRemoveall(){
	// TODO: 在此添加控件通知处理程序代码
	ptrClipNo->release();
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->DeleteAllItems();
	selectID = -1;
}


void TinyClipBoard::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	selectID = GET_CTRL(CGoodListCtrl, IDC_LIST1)->GetSelectionMark();
	if(selectID == -1){
		MessageBox(L"请选择一个IMG喵！",L"提示喵");
		return;
	}
	CDialogEx::OnOK();
}
