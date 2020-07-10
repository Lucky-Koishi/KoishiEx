// TinySNDSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "TinySNDSelect.h"
#include "afxdialogex.h"


// TinySNDSelect �Ի���

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


// TinySNDSelect ��Ϣ�������


BOOL TinySNDSelect::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void TinySNDSelect::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	selected = GET_CTRL(CListBox, IDC_LIST1)->GetCurSel();
	CDialogEx::OnOK();
}
