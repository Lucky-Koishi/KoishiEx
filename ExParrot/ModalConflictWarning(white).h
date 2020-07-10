#pragma once


// ModalConflictWarning �Ի���

class ModalConflictWarning : public CDialogEx
{
	DECLARE_DYNAMIC(ModalConflictWarning)

public:
	ModalConflictWarning(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalConflictWarning();

// �Ի�������
	enum { IDD = IDD_MODAL_CONFLICT_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString conflictName;
	int method;
	BOOL noAlarm;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedIgnore();
	afx_msg void OnBnClickedRemain();
	afx_msg void OnBnClickedRename();
};
