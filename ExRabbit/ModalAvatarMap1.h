#pragma once
#include "ToolAvatar.h"
#include "Profile.h"

// ModalAvatarMap1 �Ի���

class ModalAvatarMap1 : public CDialogEx
{
	DECLARE_DYNAMIC(ModalAvatarMap1)

public:
	ModalAvatarMap1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalAvatarMap1();

// �Ի�������
	enum { IDD = IDD_MODAL_AVATAR_MAPPING_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	struct INPUT{
		avatarFactory *ptrFactory;
		avatarPart part;
		long selected;
		long selectedPalette;
		long maxIconCount;
		DictAvatar *ptrDict;
		Profile *ptrProfile;
	}in;
	//void draw();
	//void drawIcon();
	//afx_msg void OnPaint();
	void draw();
	void drawIcon();
	virtual BOOL OnInitDialog();
	int page;
	int selectedIcon;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonErase();
	afx_msg void OnBnClickedButtonConfirm();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	bool loadImage(str fileNameWithoutExp, matrix &mat);
};
