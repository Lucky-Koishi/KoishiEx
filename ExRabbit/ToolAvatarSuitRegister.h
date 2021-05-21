#pragma once
#include "../KoishiEx/avatar.h"

// ToolAvatarSuitRegister �Ի���
using namespace Koishi;
using namespace KoishiAvatar;

class ToolAvatarSuitRegister : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarSuitRegister)

public:
	ToolAvatarSuitRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarSuitRegister();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_SUIT_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	AvatarCharacter charInput;
	long inputID[APART_MAXCOUNT];
	ProfileBlack prof;
	AvatarMap map;
	void load();
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
