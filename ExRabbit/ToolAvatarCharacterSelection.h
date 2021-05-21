#pragma once


// ToolAvatarCharacterSelection 对话框

class ToolAvatarCharacterSelection : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarCharacterSelection)

public:
	ToolAvatarCharacterSelection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatarCharacterSelection();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_CHARACTER_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CBitmap charImg[16];
	CStatic *charImgCtl[16];
	int output;		//-1,取消 0-14选择职业
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
