#pragma once


// ModalLock �Ի���

class ModalLock : public CDialogEx
{
	DECLARE_DYNAMIC(ModalLock)

public:
	ModalLock(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalLock();

// �Ի�������
	enum { IDD = IDD_MODAL_LOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnToolsNPKLock();
};
