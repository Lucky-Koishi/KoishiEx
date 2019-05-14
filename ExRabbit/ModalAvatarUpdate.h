#pragma once

#include "../KoishiEx/KoishiEx.h"
#include "Profile.h"

// ModalAvatarUpdate �Ի���
using namespace Koishi;
using namespace KoishiAvatar;
class ModalAvatarUpdate : public CDialogEx
{
	DECLARE_DYNAMIC(ModalAvatarUpdate)

public:
	ModalAvatarUpdate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalAvatarUpdate();

// �Ի�������
	enum { IDD = IDD_MODAL_AVATAR_UPDATING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl *pcList[14];
	CEdit *eList[14];
	CButton *bList[14];
	bool isStart[14];
	bool isOver[14];
public:
	CString resourcePath;
	Profile profile;
	volatile int updateSerial;
	static UINT updateThread(void* para);
	static UINT updateCareerThread(void* para);
	afx_msg void OnBnClickedStart();
	virtual BOOL OnInitDialog();
	void updateCareer(avatarCareer ac);
};
