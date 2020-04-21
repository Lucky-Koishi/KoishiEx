// ToolAvatarSuit.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarSuit.h"
#include "afxdialogex.h"


// ToolAvatarSuit 对话框
extern CString careerName[ACHARACTER_MAXCOUNT];
extern CString avatarCString[APART_MAXCOUNT];

IMPLEMENT_DYNAMIC(ToolAvatarSuit, CDialogEx)

ToolAvatarSuit::ToolAvatarSuit(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarSuit::IDD, pParent)
{

}

ToolAvatarSuit::~ToolAvatarSuit()
{
}

void ToolAvatarSuit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarSuit, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_OK, &ToolAvatarSuit::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &ToolAvatarSuit::OnBnClickedButtonExit)
	ON_LBN_SELCHANGE(IDC_LIST1, &ToolAvatarSuit::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// ToolAvatarSuit 消息处理程序


BOOL ToolAvatarSuit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"无此套装信息。");
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(0);
	load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ToolAvatarSuit::load(){
	prof.loadProfile();
	str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"装扮表.txt");
	map.initial(charInput);
	map.load(fileName);
	CListBox *clc = (CListBox*)GetDlgItem(IDC_LIST1);
	for(int i = 0;i<map.suitContent.size();i++)
		clc->AddString(StrToCStr(map.suitContent[i].suitName));
	if(map.suitContent.size()>0){
		clc->SetCurSel(0);
		OnLbnSelchangeList1();
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(1);
	}
}

void ToolAvatarSuit::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int r = ((CListBox*)GetDlgItem(IDC_LIST1))->GetCurSel();
	CHECK_VALID(r >= 0);
	CHECK_VALID(r < map.suitContent.size());
	CString infoString = L"该套装包含如下装扮：\r\n";
	int totalCount = 0;
	for(int p = 0;p<APART_MAXCOUNT;p++){
		long id = map.suitContent[r].avatarID[p];
		if(id >= 0){
			totalCount ++;
			infoString += avatarCString[p] + L":[";
			infoString += NumToCStr(id) + L"]";
			queue q = map.findAvatarPos((AvatarPart)p, id);
			if(q.size() == 0){
				infoString += L"未知名称";
			}else for(int q1 = 0;q1<q.size();q1++){
				infoString += StrToCStr(map.avatarContent[p][q[q1]].avatarTitle);
				if(q1 < q.size() - 1)
					infoString += L", ";
			}
			infoString += L"\r\n";
		}
		outputID[p] = id;
	}
	if(outputID[APART_BODY] == -1)
		outputID[APART_BODY] = 0;
	if(totalCount == 0){
		infoString += L"该套装竟然不包含任何装扮喵？";
	}else{
		infoString += L"总计"+NumToCStr(totalCount)+L"个。";
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(infoString);
}

void ToolAvatarSuit::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void ToolAvatarSuit::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
