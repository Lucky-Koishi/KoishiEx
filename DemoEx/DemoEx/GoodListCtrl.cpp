// GoodListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "GoodListCtrl.h"


// CGoodListCtrl

IMPLEMENT_DYNAMIC(CGoodListCtrl, CListCtrl)

CGoodListCtrl::CGoodListCtrl()
{
	sortType = SORT_STRING;
	sortOrder = SORT_ASCENDING;
	sortColumn = 0;
}

CGoodListCtrl::~CGoodListCtrl()
{
}


BEGIN_MESSAGE_MAP(CGoodListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CGoodListCtrl::OnLvnColumnclick)
END_MESSAGE_MAP()



// CGoodListCtrl 消息处理程序


int CALLBACK CGoodListCtrl::compareMethod(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CGoodListCtrl* pListCtl = (CGoodListCtrl*)lParamSort;
	int type = pListCtl->sortType;
	int order = pListCtl->sortOrder;
	CString s1 = pListCtl->GetItemText(lParam1,pListCtl->sortColumn);
	CString s2 = pListCtl->GetItemText(lParam2,pListCtl->sortColumn);
	BYTE b1,b2;
	CString tStr1,tStr2,dStr1,dStr2,strTemp1,strTemp2;
	int i1,i2,y1,y2,m1,m2,d1,d2,h1,h2,mm1,mm2,se1,se2;
	double f1,f2;
	int i = 0;
	int result = 0;
	switch(type){
	case SORT_STRING:
		while(i<=s1.GetLength() && i<=s2.GetLength()){
			b1 = (BYTE)(TCHAR)s1.GetAt(i);
			b2 = (BYTE)(TCHAR)s2.GetAt(i);
			if(b1 == b2){
				i++;
			}else{
				result = (int)b1-(int)b2;
				break;
			}
		}
		break;
	case SORT_INTEGER:
		i1 = _ttoi(s1);
		i2 = _ttoi(s2);
		result = i1 - i2;
		break;
	case SORT_DECIMAL:
		f1 = _ttof(s1);
		f2 = _ttof(s2);
		result = (s1 > s2)?1:((s1==s2)?0:-1);
		break;
	case SORT_DATE:
		AfxExtractSubString(dStr1,s1,0,'-');
		AfxExtractSubString(dStr2,s2,0,'-');
		y1 = _ttoi(dStr1);
		y2 = _ttoi(dStr2);
		AfxExtractSubString(dStr1,s1,1,'-');
		AfxExtractSubString(dStr2,s2,1,'-');
		m1 = _ttoi(dStr1);
		m2 = _ttoi(dStr2);
		AfxExtractSubString(dStr1,s1,2,'-');
		AfxExtractSubString(dStr2,s2,2,'-');
		d1 = _ttoi(dStr1);
		d2 = _ttoi(dStr2);
		result = 3600*(y1-y2)+60*(m1-m2)+d1-d2;
		break;
	case SORT_TIME:
		AfxExtractSubString(dStr1,s1,0,':');
		AfxExtractSubString(dStr2,s2,0,':');
		y1 = _ttoi(dStr1);
		y2 = _ttoi(dStr2);
		AfxExtractSubString(dStr1,s1,1,':');
		AfxExtractSubString(dStr2,s2,1,':');
		m1 = _ttoi(dStr1);
		m2 = _ttoi(dStr2);
		AfxExtractSubString(dStr1,s1,2,':');
		AfxExtractSubString(dStr2,s2,2,':');
		d1 = _ttoi(dStr1);
		d2 = _ttoi(dStr2);
		result = 3600*(y1-y2)+60*(m1-m2)+d1-d2;
		break;
	case SORT_DATETIME:
		AfxExtractSubString(dStr1,s1,0,' ');
		AfxExtractSubString(dStr2,s2,0,' ');
		AfxExtractSubString(tStr1,s1,1,' ');
		AfxExtractSubString(tStr2,s2,1,' ');
		AfxExtractSubString(strTemp1,dStr1,0,'-');
		AfxExtractSubString(strTemp2,dStr2,0,'-');
		y1 = _ttoi(strTemp1);
		y2 = _ttoi(strTemp2);
		AfxExtractSubString(strTemp1,dStr1,1,'-');
		AfxExtractSubString(strTemp2,dStr2,1,'-');
		m1 = _ttoi(strTemp1);
		m2 = _ttoi(strTemp2);
		AfxExtractSubString(strTemp1,dStr1,2,'-');
		AfxExtractSubString(strTemp2,dStr2,2,'-');
		d1 = _ttoi(strTemp1);
		d2 = _ttoi(strTemp2);
		AfxExtractSubString(strTemp1,tStr1,0,'-');
		AfxExtractSubString(strTemp2,tStr2,0,'-');
		h1 = _ttoi(strTemp1);
		h2 = _ttoi(strTemp2);
		AfxExtractSubString(strTemp1,tStr1,1,'-');
		AfxExtractSubString(strTemp2,tStr2,1,'-');
		mm1 = _ttoi(strTemp1);
		mm2 = _ttoi(strTemp2);
		AfxExtractSubString(strTemp1,tStr1,2,'-');
		AfxExtractSubString(strTemp2,tStr2,2,'-');
		se1 = _ttoi(strTemp1);
		se2 = _ttoi(strTemp2);
		result = 64800000*(y1-y2) + 4320000*(m1-m2) + 108000*(d1-d2) + 3600*(h1-h2) + 60*(mm1-mm2) + se1-se2;
		break;
	}
	if(order == SORT_DESCENDING)
		result = -result;
	return result;
}

void CGoodListCtrl::EasyInsertColumn(CString str){
	CString titleName,titleWidth;
	BOOL ret1,ret2;
	int i = 0;
	while(true){
		ret1 = AfxExtractSubString(titleName,str,2*i,',');
		ret2 = AfxExtractSubString(titleWidth,str,2*i+1,',');
		if(ret1 == FALSE){
			break;
		}
		InsertColumn(i,titleName,0,_ttoi(titleWidth));
		i++;
	}
}

void CGoodListCtrl::EasyInsertItem(CString str){
	CString itemText;
	BOOL ret;
	int i = 0;
	int newID = GetItemCount();
	if(str.GetLength() == 0)
		return;
	AfxExtractSubString(itemText,str,i,',');
	InsertItem(newID,itemText);
	i++;
	while(i<GetHeaderCtrl()->GetItemCount()){
		ret = AfxExtractSubString(itemText,str,i,',');
		if(ret == FALSE){
			break;
		}
		SetItemText(newID,i,itemText);
		i++;
	}
}
void CGoodListCtrl::EasySortSet(int column, int type, int order){
	sortColumn = column;
	sortType = type;
	sortOrder = order;
}
void CGoodListCtrl::EasySortItems(){
	CListCtrl::SortItems(compareMethod,(LPARAM)this);
}
void CGoodListCtrl::EasySortItems(int column, int type, int order){
	sortColumn = column;
	sortType = type;
	sortOrder = order;
	CListCtrl::SortItems(compareMethod,(LPARAM)this);
}

void CGoodListCtrl::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	for (int i=0; i< GetItemCount();i++){  
		SetItemData(i,i);
	}
	if(pNMListView->iSubItem != sortColumn){
		sortColumn = pNMListView->iSubItem;
		sortOrder = SORT_ASCENDING;
	}else{
		sortOrder = 1 - sortOrder;
	}
	//EasySortItems();
	*pResult = 0;
}
