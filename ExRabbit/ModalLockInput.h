#pragma once


// ModalLockInput �Ի���

class ModalLockInput : public CDialogEx
{
	DECLARE_DYNAMIC(ModalLockInput)

public:
	ModalLockInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalLockInput();

// �Ի�������
	enum { IDD = IDD_MODAL_LOCK_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString fileCheckName;
	int restTime;
	afx_msg void OnBnClickedOk();
};
