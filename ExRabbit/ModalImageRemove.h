#pragma once


// ModalImageRemove �Ի���

class ModalImageRemove : public CDialogEx
{
	DECLARE_DYNAMIC(ModalImageRemove)

public:
	ModalImageRemove(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalImageRemove();

// �Ի�������
	enum { IDD = IDD_MODAL_IMAGE_REMOVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	struct OUTPUT{
		int operate;
	}out;
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	virtual BOOL OnInitDialog();
};
