// ModalAdvancedMix.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalAdvancedMix.h"
#include "afxdialogex.h"


// ModalAdvancedMix 对话框

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


// ModalAdvancedMix 消息处理程序


BOOL ModalAdvancedMix::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	enumStr1[0] = L"不处理";
	enumStr1[1] = L"去黑";
	enumStr1[2] = L"去色";
	enumStr1[3] = L"半透明";
	enumStr1[4] = L"变深";
	enumStr1[5] = L"变浅";
	enumStr2[0] = L"覆盖";
	enumStr2[1] = L"变暗";
	enumStr2[2] = L"正片叠底";
	enumStr2[3] = L"颜色加深";
	enumStr2[4] = L"线性加深";
	enumStr2[5] = L"变亮";
	enumStr2[6] = L"滤色";
	enumStr2[7] = L"颜色减淡";
	enumStr2[8] = L"线性减淡";
	CComboBox *cb = GET_CTRL(CComboBox, IDC_COMBO_PREPROCESS);
	for(int i = 0; i < 6; i++)
		cb->AddString(enumStr1[i]);
	cb->SetCurSel(0);
	cb = GET_CTRL(CComboBox, IDC_COMBO_MIX_METHOD);
	for(int i = 0; i < 9; i++)
		cb->AddString(enumStr2[i]);
	cb->SetCurSel(0);
	CListCtrl *lc = GET_CTRL(CListCtrl, IDC_LIST_LAYER);
	lc->InsertColumn(0, L"图层", 0, 120);
	lc->InsertColumn(1, L"预处理", 0, 60);
	lc->InsertColumn(2, L"混合模式", 0, 60);
	for(int i = 0; i < in.layerName.size(); i++) {
		out.preprocessing.push_back(0);
		out.mixMethod.push_back(0);
		lc->InsertItem(i, GetTail(StrToCStr(in.layerName[i])));
		lc->SetItemText(i, 1, enumStr1[0]);
		lc->SetItemText(i, 2, enumStr2[0]);
	}
	currentSelect = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ModalAdvancedMix::OnBnClickedOk() {
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void ModalAdvancedMix::OnCbnSelchangeComboPreprocess() {
	// TODO:  在此添加控件通知处理程序代码
	out.preprocessing[currentSelect] = GET_CTRL(CComboBox, IDC_COMBO_PREPROCESS)->GetCurSel();
	GET_CTRL(CListCtrl, IDC_LIST_LAYER)->SetItemText(currentSelect, 1, enumStr1[out.preprocessing[currentSelect]]);
}


void ModalAdvancedMix::OnCbnSelchangeComboMixMethod() {
	// TODO:  在此添加控件通知处理程序代码
	out.mixMethod[currentSelect] = GET_CTRL(CComboBox, IDC_COMBO_MIX_METHOD)->GetCurSel();
	GET_CTRL(CListCtrl, IDC_LIST_LAYER)->SetItemText(currentSelect, 2, enumStr2[out.mixMethod[currentSelect]]);
}


void ModalAdvancedMix::OnLvnItemchangedListLayer(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	if(row >= 0 && row < in.layerName.size()) {
		currentSelect = row;
		GET_CTRL(CComboBox, IDC_COMBO_PREPROCESS)->SetCurSel(out.preprocessing[currentSelect]);
		GET_CTRL(CComboBox, IDC_COMBO_MIX_METHOD)->SetCurSel(out.mixMethod[currentSelect]);
	}
	*pResult = 0;
}
