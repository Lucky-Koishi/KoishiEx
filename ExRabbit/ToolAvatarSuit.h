#pragma once
#include "../KoishiEx/avatar.h"
#include "Profile.h"

// ToolAvatarSuit 对话框
using namespace Koishi;
using namespace KoishiAvatar;

class ToolAvatarSuit : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarSuit)

public:
	ToolAvatarSuit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatarSuit();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_SUIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
