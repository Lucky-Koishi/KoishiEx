#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"
#include "Profile.h"
#include "ToolAvatarModelConfig.h"

// ToolAvatarLocalizer 对话框
using namespace Koishi;
using namespace KoishiAvatar;
class ToolAvatarLocalizer : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarLocalizer)

public:
	ToolAvatarLocalizer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatarLocalizer();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_LOCALIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Profile profile;
	uchar maxEstablished;
	uchar localFlag;
	volatile uchar established;
	volatile uchar finished;
	CEdit *cel[ACHARACTER_MAXCOUNT];
	CProgressCtrl * cpl[ACHARACTER_MAXCOUNT];
	CButton *cbl[ACHARACTER_MAXCOUNT];
	std::vector<queue> ql;
	static void localize(AvatarCharacter, Profile*,  CEdit*, CProgressCtrl*, uchar);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonAll();
	afx_msg void OnBnClickedButtonNos();
};
