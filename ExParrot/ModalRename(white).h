#pragma once


// ModalRename �Ի���

class ModalRename : public CDialogEx
{
	DECLARE_DYNAMIC(ModalRename)

public:
	ModalRename(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalRename();

// �Ի�������
	enum { IDD = IDD_MODAL_SOUND_RENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString oldName;
	CString newName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
