#pragma once
#include "../KoishiEx/avatar.h"

// ToolAvatarSuitRegister 对话框
using namespace Koishi;
using namespace KoishiAvatar;

class ToolAvatarSuitRegister : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarSuitRegister)

public:
	ToolAvatarSuitRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatarSuitRegister();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_SUIT_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	AvatarCharacter charInput;
	long inputID[APART_MAXCOUNT];
	Profile prof;
	AvatarMap map;
	void load();
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
