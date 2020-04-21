// TinyClipBoard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "TinyClipBoard.h"
#include "afxdialogex.h"
#include "GoodListCtrl.h"

// TinyClipBoard �Ի���

IMPLEMENT_DYNAMIC(TinyClipBoard, CDialogEx)

TinyClipBoard::TinyClipBoard(CWnd* pParent /*=NULL*/)
	: CDialogEx(TinyClipBoard::IDD, pParent)
{

}

TinyClipBoard::~TinyClipBoard()
{
}

void TinyClipBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TinyClipBoard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &TinyClipBoard::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEALL, &TinyClipBoard::OnBnClickedButtonRemoveall)
	ON_BN_CLICKED(IDOK, &TinyClipBoard::OnBnClickedOk)
END_MESSAGE_MAP()


// TinyClipBoard ��Ϣ�������


BOOL TinyClipBoard::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	selectID = -1;
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertColumn(L"�������е�IMG,200");
	for(int i = 0;i<ptrClipNo->count;i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST1)->EasyInsertItem(GetTail(StrToCStr(ptrClipNo->entry[i].comment)));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void TinyClipBoard::OnBnClickedButtonRemove(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	selectID = GET_CTRL(CGoodListCtrl, IDC_LIST1)->GetSelectionMark();
	CHECK_VALID(selectID >= 0);
	ptrClipNo->remove(selectID);
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->DeleteItem(selectID);
	selectID = -1;
}


void TinyClipBoard::OnBnClickedButtonRemoveall(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ptrClipNo->release();
	GET_CTRL(CGoodListCtrl, IDC_LIST1)->DeleteAllItems();
	selectID = -1;
}


void TinyClipBoard::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	selectID = GET_CTRL(CGoodListCtrl, IDC_LIST1)->GetSelectionMark();
	if(selectID == -1){
		MessageBox(L"��ѡ��һ��IMG����",L"��ʾ��");
		return;
	}
	CDialogEx::OnOK();
}
