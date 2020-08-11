#pragma once
#include "../KoishiEx/KoishiAudioTool.h"
#include "TinyBar(white).h"
#include "Music.h"

// ToolPiano 对话框

class ToolPiano : public CDialogEx
{
	DECLARE_DYNAMIC(ToolPiano)

public:
	ToolPiano(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolPiano();

// 对话框数据
	enum { IDD = IDD_TOOL_PAINO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	audio originNote;
	audio track;
	TinyBar bar;
	KoishiAudioTool::PCMplayer player;
	std::vector<NoteBar> staff;
	CRect rcBoard;
	CRect rcStaff;
	DeclareThreadFunc(playNotes, double);
	DeclareThreadFunc(punchSave, int);
	DeclareThreadFunc(punchPlay, int);
	BOOL graphicMode;
	BOOL playing;
	int offsetLine;
	void staffFromText();
	void showStaffText();
	void drawStaff(int lineCount, int barPerLine, int offset);
	void drawBoards(int clicked);
	void makeTrack();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	virtual void OnOK();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();

	int getBoardHit(const point &pt);
	int getClickedBar(const point &pt, int lineCount, int barPerLine, int offset);
	afx_msg void OnBnClickedStop();
};