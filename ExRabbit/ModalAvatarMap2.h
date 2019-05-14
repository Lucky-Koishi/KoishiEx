#pragma once
#include "ToolAvatar.h"
#include "Profile.h"

// ModalAvatarMap2 对话框

class ModalAvatarMap2 : public CDialogEx
{
	DECLARE_DYNAMIC(ModalAvatarMap2)

public:
	ModalAvatarMap2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalAvatarMap2();

// 对话框数据
	enum { IDD = IDD_MODAL_AVATAR_MAPPING_2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboAvatar();
	afx_msg void OnCbnSelchangeComboPalette();
	afx_msg void OnBnClickedButtonErase();
	afx_msg void OnBnClickedButtonConfirm();
	afx_msg void OnBnClickedCancel();

public:
	struct INPUT{
		avatarFactory *ptrFactory;
		avatarPart part;
		long iconID;
		DictAvatar *ptrDict;
		Profile *ptrProfile;
	}in;
	void draw();
	void drawIcon();
	afx_msg void OnPaint();

	bool loadImage(str fileNameWithoutExp, matrix &mat);
};
