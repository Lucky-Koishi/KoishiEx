#pragma once


// ModalSoundHide 对话框

class ModalSoundHide : public CDialogEx
{
	DECLARE_DYNAMIC(ModalSoundHide)

public:
	ModalSoundHide(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalSoundHide();

// 对话框数据
	enum { IDD = IDD_MODAL_SOUND_HIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	struct OUTPUT{
		int operate;
	}out;
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedOk();
};
