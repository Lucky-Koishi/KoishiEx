#pragma once


// ToolAvatarCharacterSelection �Ի���

class ToolAvatarCharacterSelection : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarCharacterSelection)

public:
	ToolAvatarCharacterSelection(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatarCharacterSelection();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR_CHARACTER_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CBitmap charImg[16];
	CStatic *charImgCtl[16];
	int output;		//-1,ȡ�� 0-14ѡ��ְҵ
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
