#pragma once


// ModalClearPicture �Ի���

class ModalClearPicture : public CDialogEx
{
	DECLARE_DYNAMIC(ModalClearPicture)

public:
	ModalClearPicture(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalClearPicture();

// �Ի�������
	enum { IDD = IDD_MODAL_CLEAR_PICTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	struct OUTPUT{
		int target;
		int operate;
	}out;

	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
