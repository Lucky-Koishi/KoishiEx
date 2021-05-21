#pragma once
#include "../KoishiEx/avatar.h"

// ToolAvatarRegister 对话框
using namespace Koishi;
using namespace KoishiAvatar;

class ToolAvatarRegister : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarRegister)

public:
	ToolAvatarRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatarRegister();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
