#pragma once


// ModalImageHide �Ի���

class ModalImageHide : public CDialogEx
{
	DECLARE_DYNAMIC(ModalImageHide)

public:
	ModalImageHide(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalImageHide();

// �Ի�������
	enum { IDD = IDD_MODAL_IMAGE_HIDE };

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
