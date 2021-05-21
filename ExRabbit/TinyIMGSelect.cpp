// TinyIMGSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyIMGSelect.h"
#include "afxdialogex.h"


// TinyIMGSelect 对话框

IMPLEMENT_DYNAMIC(TinyIMGSelect, CDialogEx)

TinyIMGSelect::TinyIMGSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyIMGSelect::IDD, pParent)
{

}

TinyIMGSelect::~TinyIMGSelect()
{
}

void TinyIMGSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyIMGSelect, CDialogEx)
	ON_BN_CLICKED(IDOK, &TinyIMGSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyIMGSelect 消息处理程序


BOOL TinyIMGSelect::OnInitDialog() {
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


void TinyIMGSelect::OnBnClickedOk() {
	// TODO:  在此添加控件通知处理程序代码
	selected = GET_CTRL(CListBox, IDC_LIST1)->GetCurSel();
	CDialogEx::OnOK();
}
