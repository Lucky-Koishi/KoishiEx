#pragma once

// ModalPreference �Ի���

class ModalPreference : public CDialogEx
{
	DECLARE_DYNAMIC(ModalPreference)

public:
	ModalPreference(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalPreference();

// �Ի�������
	enum { IDD = IDD_MODAL_PREFERENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPreference1();
	afx_msg void OnBnClickedButtonPreference2();
	afx_msg void OnBnClickedButtonPreference3();
	afx_msg void OnBnClickedButtonPreference4();
	afx_msg void OnBnClickedButtonPreference5();
	afx_msg void OnBnClickedButtonPreference6();
	afx_msg void OnBnClickedButtonPreference7();
	afx_msg void OnBnClickedButtonPreference8();
	afx_msg void OnBnClickedButtonPreference9();
	virtual BOOL OnInitDialog();

public:
	Profile modifiedProfile;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSetpic1();
	afx_msg void OnBnClickedButtonSetpic2();
};
