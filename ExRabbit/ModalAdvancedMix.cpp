// ModalAdvancedMix.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAdvancedMix.h"
#include "afxdialogex.h"


// ModalAdvancedMix �Ի���

IMPLEMENT_DYNAMIC(ModalAdvancedMix, CDialogEx)

ModalAdvancedMix::ModalAdvancedMix(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalAdvancedMix::IDD, pParent)
{

}

ModalAdvancedMix::~ModalAdvancedMix()
{
}

void ModalAdvancedMix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalAdvancedMix, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModalAdvancedMix::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_PREPROCESS, &ModalAdvancedMix::OnCbnSelchangeComboPreprocess)
	ON_CBN_SELCHANGE(IDC_COMBO_MIX_METHOD, &ModalAdvancedMix::OnCbnSelchangeComboMixMethod)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LAYER, &ModalAdvancedMix::OnLvnItemchangedListLayer)
END_MESSAGE_MAP()


// ModalAdvancedMix ��Ϣ�������


BOOL ModalAdvancedMix::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	enumStr1[0] = L"������";
	enumStr1[1] = L"ȥ��";
	enumStr1[2] = L"ȥɫ";
	enumStr1[3] = L"��͸��";
	enumStr1[4] = L"����";
	enumStr1[5] = L"��ǳ";
	enumStr2[0] = L"����";
	enumStr2[1] = L"�䰵";
	enumStr2[2] = L"��Ƭ����";
	enumStr2[3] = L"��ɫ����";
	enumStr2[4] = L"���Լ���";
	enumStr2[5] = L"����";
	enumStr2[6] = L"��ɫ";
	enumStr2[7] = L"��ɫ����";
	enumStr2[8] = L"���Լ���";
	CComboBox *cb = GET_CTRL(CComboBox, IDC_COMBO_PREPROCESS);
	for(int i = 0; i < 6; i++)
		cb->AddString(enumStr1[i]);
	cb->SetCurSel(0);
	cb = GET_CTRL(CComboBox, IDC_COMBO_MIX_METHOD);
	for(int i = 0; i < 9; i++)
		cb->AddString(enumStr2[i]);
	cb->SetCurSel(0);
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_LAYER);
	lc->InsertColumn(0, L"ͼ��", 0, 120);
	lc->InsertColumn(1, L"Ԥ����", 0, 60);
	lc->InsertColumn(2, L"���ģʽ", 0, 60);
	for(int i = 0; i < in.layerName.size(); i++) {
		out.preprocessing.push_back(0);
		out.mixMethod.push_back(0);
		lc->InsertItem(i, GetTail(StrToCStr(in.layerName[i])));
		lc->SetItemText(i, 1, enumStr1[0]);
		lc->SetItemText(i, 2, enumStr2[0]);
	}
	currentSelect = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ModalAdvancedMix::OnBnClickedOk() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void ModalAdvancedMix::OnCbnSelchangeComboPreprocess() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	out.preprocessing[currentSelect] = GET_CTRL(CComboBox, IDC_COMBO_PREPROCESS)->GetCurSel();
	GET_CTRL(CListCtrl, IDC_LIST_LAYER)->SetItemText(currentSelect, 1, enumStr1[out.preprocessing[currentSelect]]);
}


void ModalAdvancedMix::OnCbnSelchangeComboMixMethod() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	out.mixMethod[currentSelect] = GET_CTRL(CComboBox, IDC_COMBO_MIX_METHOD)->GetCurSel();
	GET_CTRL(CListCtrl, IDC_LIST_LAYER)->SetItemText(currentSelect, 2, enumStr2[out.mixMethod[currentSelect]]);
}


void ModalAdvancedMix::OnLvnItemchangedListLayer(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	if(row >= 0 && row < in.layerName.size()) {
		currentSelect = row;
		GET_CTRL(CComboBox, IDC_COMBO_PREPROCESS)->SetCurSel(out.preprocessing[currentSelect]);
		GET_CTRL(CComboBox, IDC_COMBO_MIX_METHOD)->SetCurSel(out.mixMethod[currentSelect]);
	}
	*pResult = 0;
}
