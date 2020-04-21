// ToolAvatarSuitRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarSuitRegister.h"
#include "afxdialogex.h"


// ToolAvatarSuitRegister 对话框
extern CString careerName[ACHARACTER_MAXCOUNT];
extern CString avatarCString[APART_MAXCOUNT];

IMPLEMENT_DYNAMIC(ToolAvatarSuitRegister, CDialogEx)

ToolAvatarSuitRegister::ToolAvatarSuitRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarSuitRegister::IDD, pParent)
{

}

ToolAvatarSuitRegister::~ToolAvatarSuitRegister()
{
}

void ToolAvatarSuitRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarSuitRegister, CDialogEx)
	ON_BN_CLICKED(IDOK, &ToolAvatarSuitRegister::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ToolAvatarSuitRegister::OnBnClickedCancel)
END_MESSAGE_MAP()


// ToolAvatarSuitRegister 消息处理程序


void ToolAvatarSuitRegister::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString newString;
	GetDlgItem(IDC_EDIT2)->GetWindowText(newString);
	if(newString.GetLength() == 0){
		MessageBox(L"请输入新的套装名喵！",L"提示喵");
		return;
	}else{
		map.addSuitEntry(CStrToStr(newString), inputID);
		str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"装扮表.txt");
		map.save(fileName);
	}
	CDialogEx::OnOK();
}


void ToolAvatarSuitRegister::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL ToolAvatarSuitRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	load();
	GetDlgItem(IDC_EDIT2)->SetWindowText(L"新" + careerName[charInput] + L"的套装");
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ToolAvatarSuitRegister::load(){
	prof.loadProfile();
	str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"装扮表.txt");
	map.initial(charInput);
	map.load(fileName);
	CString infoString = L"含有以下装扮的套装：\r\n";
	int totalCount = 0;
	for(int p = 0;p<APART_MAXCOUNT;p++){
		long id = inputID[p];
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
	}
	if(totalCount == 0){
		infoString += L"该套装竟然不包含任何装扮喵？";
	}else{
		infoString += L"总计"+NumToCStr(totalCount)+L"个。";
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(infoString);
	if(totalCount == 0){
		MessageBox(L"该套装竟然不包含任何装扮喵？",L"提示喵", MB_ICONERROR);
		CDialogEx::OnCancel();
	}
}