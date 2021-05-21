#pragma once
#include "../KoishiEx/avatar.h"

// ToolAvatarRegister �Ի���
using namespace Koishi;
using namespace KoishiAvatar;

class ToolAvatarRegister : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarRegister)

public:
	ToolAvatarRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarRegister();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	AvatarCharacter charInput;
	AvatarPart partInput;
	long weaponIndexInput;
	long inputID;
	ProfileBlack prof;
	AvatarMap map;
	CString outputStr;
	void load();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
};
