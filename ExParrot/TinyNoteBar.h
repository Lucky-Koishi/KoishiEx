#pragma once
#include "Music.h"

// TinyNoteBar 对话框

class TinyNoteBar : public CDialogEx
{
	DECLARE_DYNAMIC(TinyNoteBar)

public:
	TinyNoteBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyNoteBar();

// 对话框数据
	enum { IDD = IDD_TINY_NOTE_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CRect rcBoard;
	NoteBar content;
	virtual BOOL OnInitDialog();

public:
	void drawBar();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
};
