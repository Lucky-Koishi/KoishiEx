#pragma once
#include "../KoishiEx/avatar.h"
#include "Profile.h"

// ToolAvatarSuit �Ի���
using namespace Koishi;
using namespace KoishiAvatar;

class ToolAvatarSuit : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarSuit)

public:
	ToolAvatarSuit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarSuit();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_SUIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	AvatarCharacter charInput;
	long outputID[APART_MAXCOUNT];
	Profile prof;
	AvatarMap map;
	void load();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnLbnSelchangeList1();
};
