#pragma once


// CGoodListCtrl

class CGoodListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CGoodListCtrl)

public:
	CGoodListCtrl();
	virtual ~CGoodListCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	enum {
		SORT_ASCENDING =  (int)0,	//升序
		SORT_DESCENDING = (int)1	//降序
	};
	enum {
		SORT_STRING =	(int)0,	//字符串排列
		SORT_INTEGER =	(int)1,	//整数排列
		SORT_DECIMAL =	(int)2,	//小数排列
		SORT_DATE =		(int)3,	//日期排列 型：yy-mm-dd
		SORT_TIME =		(int)4,	//时间排列 型：HH:MM:SS
		SORT_DATETIME = (int)5	//日期时间排列 型：yy-mm-dd,HH:MM:SS
	};
protected:
	int sortType;
	int sortOrder;
	int sortColumn;
	static int CALLBACK compareMethod(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
public:
	//快捷添加数据相关
	void EasyInsertColumn(CString str);	//以“标题1,宽度,标题2,宽度,标题3,宽度,..”字符串来重新定义表头
	void EasyInsertItem(CString str);	//以“第一项值,第二项值,第三项值,..”字符串来插入数据
	void EasyInsertItem(CString str, int nImage);	//以“第一项值,第二项值,第三项值,..”字符串来插入数据
	//快捷排序相关
	void EasySortSet(int column, int type, int order);		//设置排序方式
	void EasySortItems();									//排序
	void EasySortItems(int column, int type, int order);	//设置排序方式并排序
public:
	//点击标头进行排序
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
};


