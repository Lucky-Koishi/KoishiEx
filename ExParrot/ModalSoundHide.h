#pragma once


// ModalSoundHide �Ի���

class ModalSoundHide : public CDialogEx
{
	DECLARE_DYNAMIC(ModalSoundHide)

public:
	ModalSoundHide(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalSoundHide();

// �Ի�������
	enum { IDD = IDD_MODAL_SOUND_HIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
