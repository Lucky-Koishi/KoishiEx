#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"
#include "TinyBar.h"
#include "ToolAvatarModelConfig.h"

using namespace Koishi;
using namespace KoishiAvatar;
// ToolAvatarModelSet �Ի���

class ToolAvatarModelSet : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarModelSet)

public:
	ToolAvatarModelSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarModelSet();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_MODEL_CONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnCbnSelchangeComboChar();
	afx_msg void OnCbnSelchangeComboPart();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeComboSize();
	ToolAvatarModelConfig mc;
	AvatarFactory fc;
	void autoFill();
	void draw();
};
