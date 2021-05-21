// ToolAvatarSuitRegister.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarSuitRegister.h"
#include "afxdialogex.h"


// ToolAvatarSuitRegister �Ի���
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


// ToolAvatarSuitRegister ��Ϣ�������


void ToolAvatarSuitRegister::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString newString;
	GetDlgItem(IDC_EDIT2)->GetWindowText(newString);
	if(newString.GetLength() == 0){
		MessageBox(L"�������µ���װ������",L"��ʾ��");
		return;
	}else{
		map.addSuitEntry(CStrToStr(newString), inputID);
		str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"װ���.txt");
		map.save(fileName);
	}
	CDialogEx::OnOK();
}


void ToolAvatarSuitRegister::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL ToolAvatarSuitRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	load();
	GetDlgItem(IDC_EDIT2)->SetWindowText(L"��" + careerName[charInput] + L"����װ");
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ToolAvatarSuitRegister::load(){
	prof.loadProfile();
	str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"װ���.txt");
	map.initial(charInput);
	map.load(fileName);
	CString infoString = L"��������װ�����װ��\r\n";
	int totalCount = 0;
	for(int p = 0;p<APART_MAXCOUNT;p++){
		long id = inputID[p];
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
	}
	if(totalCount == 0){
		infoString += L"����װ��Ȼ�������κ�װ������";
	}else{
		infoString += L"�ܼ�"+NumToCStr(totalCount)+L"����";
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(infoString);
	if(totalCount == 0){
		MessageBox(L"����װ��Ȼ�������κ�װ������",L"��ʾ��", MB_ICONERROR);
		CDialogEx::OnCancel();
	}
}