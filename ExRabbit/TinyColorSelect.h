#pragma once


// TinyColorSelect �Ի���

class TinyColorSelect : public CDialogEx
{
	DECLARE_DYNAMIC(TinyColorSelect)

public:
	TinyColorSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyColorSelect();

// �Ի�������
	enum { IDD = IDD_TINY_COLOR_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	colorList in;	//��ɫ
	int selection;	//ѡ���
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
