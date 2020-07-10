#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"
#include "ToolAvatarModelConfig.h"

// ToolAvatarLocalizer �Ի���
using namespace Koishi;
using namespace KoishiAvatar;
class ToolAvatarLocalizer : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarLocalizer)

public:
	ToolAvatarLocalizer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarLocalizer();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_LOCALIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Profile profile;
	uchar maxEstablished;
	uchar localFlag;
	volatile uchar established;
	volatile uchar finished;
	volatile long countAvatar;
	volatile long countWeapon;
	volatile long countIcon;
	CEdit *cel[ACHARACTER_MAXCOUNT];
	CProgressCtrl * cpl[ACHARACTER_MAXCOUNT];
	CButton *cbl[ACHARACTER_MAXCOUNT];
	std::vector<queue> ql;
	void localize(AvatarCharacter, Profile*,  CEdit*, CProgressCtrl*, uchar);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonAll();
	afx_msg void OnBnClickedButtonNos();
};
