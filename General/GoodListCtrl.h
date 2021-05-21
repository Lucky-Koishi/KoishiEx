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
		SORT_ASCENDING =  (int)0,	//����
		SORT_DESCENDING = (int)1	//����
	};
	enum {
		SORT_STRING =	(int)0,	//�ַ�������
		SORT_INTEGER =	(int)1,	//��������
		SORT_DECIMAL =	(int)2,	//С������
		SORT_DATE =		(int)3,	//�������� �ͣ�yy-mm-dd
		SORT_TIME =		(int)4,	//ʱ������ �ͣ�HH:MM:SS
		SORT_DATETIME = (int)5	//����ʱ������ �ͣ�yy-mm-dd,HH:MM:SS
	};
protected:
	int sortType;
	int sortOrder;
	int sortColumn;
	static int CALLBACK compareMethod(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
public:
	//�������������
	void EasyInsertColumn(CString str);	//�ԡ�����1,���,����2,���,����3,���,..���ַ��������¶����ͷ
	void EasyInsertItem(CString str);	//�ԡ���һ��ֵ,�ڶ���ֵ,������ֵ,..���ַ�������������
	void EasyInsertItem(CString str, int nImage);	//�ԡ���һ��ֵ,�ڶ���ֵ,������ֵ,..���ַ�������������
	//����������
	void EasySortSet(int column, int type, int order);		//��������ʽ
	void EasySortItems();									//����
	void EasySortItems(int column, int type, int order);	//��������ʽ������
public:
	//�����ͷ��������
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
};


