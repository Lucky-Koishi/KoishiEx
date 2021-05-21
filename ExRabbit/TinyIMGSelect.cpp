// TinyIMGSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyIMGSelect.h"
#include "afxdialogex.h"


// TinyIMGSelect �Ի���

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


// TinyIMGSelect ��Ϣ�������


BOOL TinyIMGSelect::OnInitDialog() {
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


void TinyIMGSelect::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	selected = GET_CTRL(CListBox, IDC_LIST1)->GetCurSel();
	CDialogEx::OnOK();
}
