// ToolAvatarES.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatarES.h"
#include "afxdialogex.h"


// CToolAvatarES �Ի���

IMPLEMENT_DYNAMIC(CToolAvatarES, CDialogEx)

CToolAvatarES::CToolAvatarES(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolAvatarES::IDD, pParent)
{

}

CToolAvatarES::~CToolAvatarES()
{
}

void CToolAvatarES::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolAvatarES, CDialogEx)
	ON_BN_CLICKED(IDOK, &CToolAvatarES::OnBnClickedOk)
END_MESSAGE_MAP()


// CToolAvatarES ��Ϣ�������


void CToolAvatarES::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i, j;
	type = 0;
	for(i = 0;i<10;i++){
		partID[i] = L"UNNAMED";
	}
	CString totalStr;
	CString typeStr;
	CString partStr;
	CString partOneStr;
	CString partNameStr;
	CString partNumStr;
	CString cTypeStr[15] = {
		L"undefined", L"swordman", L"swordman_at",
		L"fighter", L"fighter_at",
		L"gunner", L"gunner_at",
		L"mage", L"mage_at",
		L"priest", L"priest_at",
		L"thief", L"knight",
		L"demoniclancer",L"gunblader"
	};
	CString pTypeStr[9] = {
		L"cap", L"hair", L"face", L"neck", L"coat", L"pants", L"belt", L"shoes", L"skin"
	};
	GetDlgItem(IDC_EDIT1)->GetWindowText(totalStr);
	AfxExtractSubString(typeStr, totalStr, 0, '?');
	AfxExtractSubString(partStr, totalStr, 1, '?');
	for(i=0;i<15;i++){
		if(cTypeStr[i] == typeStr){
			type = i;
		}
	}
	if(type == 0){
		MessageBox(L"�޷�ʶ��ְҵ����");
		return;
	}
	i = 0;
	while(AfxExtractSubString(partOneStr, partStr, i, '&')){
		AfxExtractSubString(partNameStr, partOneStr, 0, '=');
		AfxExtractSubString(partNumStr, partOneStr, 1, '=');
		for(j = 0;j<8;j++){
			if(pTypeStr[j] == partNameStr){
				partID[j] = partNumStr;
				break;
			}
		}
		i++;
	}
	CDialogEx::OnOK();
}
