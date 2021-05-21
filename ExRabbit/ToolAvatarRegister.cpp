// ToolAvatarRegister.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarRegister.h"
#include "afxdialogex.h"


// ToolAvatarRegister �Ի���
extern CString careerName[ACHARACTER_MAXCOUNT];
extern CString avatarCString[APART_MAXCOUNT];
extern CString iconCString[APART_MAXCOUNT];
extern CString weaponCString[AWEAPON_MAXCOUNT];
extern CString iconWeaponCString[ACHARACTER_MAXCOUNT][5];

IMPLEMENT_DYNAMIC(ToolAvatarRegister, CDialogEx)

ToolAvatarRegister::ToolAvatarRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAvatarRegister::IDD, pParent)
{

}

ToolAvatarRegister::~ToolAvatarRegister()
{
}

void ToolAvatarRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAvatarRegister, CDialogEx)
	ON_BN_CLICKED(IDOK, &ToolAvatarRegister::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ToolAvatarRegister::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &ToolAvatarRegister::OnBnClickedButton2)
END_MESSAGE_MAP()


// ToolAvatarRegister ��Ϣ�������


BOOL ToolAvatarRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	load();
	if(partInput == APART_WEAPON){
		GetDlgItem(IDC_EDIT2)->SetWindowText(L"��" + careerName[charInput] + L"��" +  weaponCString[map.weapon[weaponIndexInput]]);
	}else{
		GetDlgItem(IDC_EDIT2)->SetWindowText(L"��" + careerName[charInput] + L"��" +  avatarCString[partInput] + L"װ�磺");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ToolAvatarRegister::load(){
	prof.loadProfile();
	str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"װ���.txt");
	map.initial(charInput);
	map.load(fileName);
	CString infoString;
	if(partInput == APART_WEAPON){
		infoString = weaponCString[map.weapon[weaponIndexInput]] + L"��";
		infoString +=  L"[" + NumToCStr(inputID) + L"]";
	}else{
		infoString = avatarCString[partInput] + L"װ�磺";
		infoString += L"[" + NumToCStr(inputID) + L"]";
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(infoString);
}
void ToolAvatarRegister::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString nameString, iconString;
	str fileName = CStrToStr(prof.getAvatarMapPath() + careerName[charInput] + L"װ���.txt");
	GetDlgItem(IDC_EDIT2)->GetWindowText(nameString);
	GetDlgItem(IDC_EDIT5)->GetWindowText(iconString);
	if(partInput == APART_WEAPON){
		outputStr = nameString;
		map.addWeaponEntry(map.weapon[weaponIndexInput], inputID, CStrToStr(iconString), CStrToStr(nameString));
		map.save(fileName);
	}else{
		outputStr = nameString;
		map.addAvatarEntry(partInput, inputID, CStrToStr(iconString), CStrToStr(nameString));
		map.save(fileName);
	}
	CDialogEx::OnOK();
}


void ToolAvatarRegister::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void ToolAvatarRegister::OnBnClickedButton2()
{
	// TODO: ���ͼ��
	CString defExt = L"����ͼ��(*.PNG)|*.PNG";
	CString extFilter = L"����ͼ��(*.PNG)|*.PNG|";
	for(int p = 0;p < APART_MAXCOUNT;p++){
		extFilter += avatarCString[p] + L"ͼ��(*.PNG)|*" + avatarCString[p] + L"*.PNG|";
	}
	for(int i = 0;i < 5;i++){
		if(iconWeaponCString[charInput][i].GetLength() > 0)
			extFilter += iconWeaponCString[charInput][i] + L"ͼ��(*.PNG)|*" + iconWeaponCString[charInput][i] + L"*.PNG|";
	}
	extFilter += L"|";
	CString defPath = prof.getIconPath(charInput);
	CFileDialog dlg(true, defExt, defPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(IDOK == dlg.DoModal()){
		GetDlgItem(IDC_EDIT5)->SetWindowText(dlg.GetFileTitle());
	}
}
