
// ExKittyDlg.h : ͷ�ļ�
//
#include "../KoishiEx/koishiex.h"
#pragma once


// CExKittyDlg �Ի���
class CExKittyDlg : public CDialogEx
{
// ����
public:
	CExKittyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXKITTY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	bool avatarEnableDisplay[10];
	CBitmap avatarIconEnable[10];
	CBitmap avatarIconDisable[10];

public:
	Koishi::NPKobject no;
	Koishi::IMGobject io;
public:
	void Initial();
	void DrawUI();
	void DrawIconButton();
	void DrawPalette();
	afx_msg void OnBnClickedButtonMenu1();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnBnClickedButtonMenu4();
	afx_msg void OnBnClickedButtonMenu5();
};
