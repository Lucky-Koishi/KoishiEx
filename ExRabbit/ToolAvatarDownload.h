#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"

// ToolAvatarDownload �Ի���
using namespace Koishi;
using namespace KoishiAvatar;
class ToolAvatarDownload : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarDownload)

public:
	ToolAvatarDownload(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarDownload();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_DOWNLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	Profile profile;
	CString downloadPath;
	std::vector<CString> fileList;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonAll();
	afx_msg void OnBnClickedButtonNos();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedStart();


	static UINT threadDownloadSPKpatch(PVOID para);
	void downloadSPKpatch();
};
