// TinySNDSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinySNDSelect.h"
#include "afxdialogex.h"


// TinySNDSelect 对话框

IMPLEMENT_DYNAMIC(TinySNDSelect, CDialogEx)

TinySNDSelect::TinySNDSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinySNDSelect::IDD, pParent)
{

}

TinySNDSelect::~TinySNDSelect()
{
}

void TinySNDSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinySNDSelect, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinySNDSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// TinySNDSelect 消息处理程序


BOOL TinySNDSelect::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CListBox *lb = GET_CTRL(CListBox, IDC_LIST1);
	lb->ResetContent();
	for(int i = 0; i < listStr.size(); i++)
		lb->AddString(GetTail(StrToCStr(listStr[i])));
	if(defaultSelected < listStr.size()) { 
		lb->SetCurSel(defaultSelected);
		selected = defaultSelected;
	} else {
		selected = -1;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void TinySNDSelect::OnBnClickedOk() {
	// TODO:  在此添加控件通知处理程序代码
	selected = GET_CTRL(CListBox, IDC_LIST1)->GetCurSel();
	CDialogEx::OnOK();
}
