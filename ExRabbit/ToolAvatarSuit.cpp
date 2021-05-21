// ToolAvatarSuit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarSuit.h"
#include "afxdialogex.h"


// ToolAvatarSuit �Ի���
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


// ToolAvatarSuit ��Ϣ�������


BOOL ToolAvatarSuit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"�޴���װ��Ϣ��");
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(0);
	load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ToolAvatarSuit::load(){
	prof.loadProfile();
	str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"װ���.txt");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int r = ((CListBox*)GetDlgItem(IDC_LIST1))->GetCurSel();
	CHECK_VALID(r >= 0);
	CHECK_VALID(r < map.suitContent.size());
	CString infoString = L"����װ��������װ�磺\r\n";
	int totalCount = 0;
	for(int p = 0;p<APART_MAXCOUNT;p++){
		long id = map.suitContent[r].avatarID[p];
		if(id >= 0){
			totalCount ++;
			infoString += avatarCString[p] + L":[";
			infoString += NumToCStr(id) + L"]";
			queue q = map.findAvatarPos((AvatarPart)p, id);
			if(q.size() == 0){
				infoString += L"δ֪����";
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
		infoString += L"����װ��Ȼ�������κ�װ������";
	}else{
		infoString += L"�ܼ�"+NumToCStr(totalCount)+L"����";
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(infoString);
}

void ToolAvatarSuit::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

void ToolAvatarSuit::OnBnClickedButtonExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
