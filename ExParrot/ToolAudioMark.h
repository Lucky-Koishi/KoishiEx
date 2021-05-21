#pragma once
#include "../KoishiEx/KoishiAudioTool.h"

// ToolAudioMark �Ի���

using namespace KoishiAudioTool;
class ToolAudioMark : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAudioMark)

public:
	ToolAudioMark(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAudioMark();

// �Ի�������
	enum { IDD = IDD_TOOL_AUDIO_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
	long interval;
	long beginID;
	long digitCount;
	NPKobject reporter;
	PCMplayer player;
	BOOL isOverlapped;
	BOOL useFolder;
	CString sourceFileName;
	CString sourceFolderName;

	DeclareThreadFunc(ToolAudioMark, TryPlay, PVOID);
	DeclareThreadFunc(ToolAudioMark, Marking, PVOID);
public:
	virtual BOOL OnInitDialog();

	CString info;
	void addInfo(CString);
	queue makeNumberSeq(long);

	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheckMark1();
	afx_msg void OnBnClickedCheckMark2();
	afx_msg void OnBnClickedButtonReportSeartch();
	afx_msg void OnBnClickedButtonReportListen();
	afx_msg void OnBnClickedButtonMarka();
	afx_msg void OnBnClickedButtonMarkb();
	afx_msg void OnBnClickedStart();
};
