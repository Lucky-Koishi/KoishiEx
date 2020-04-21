#pragma once


// ModalCopyReplace �Ի���

class ModalCopyReplace : public CDialogEx
{
	DECLARE_DYNAMIC(ModalCopyReplace)

public:
	ModalCopyReplace(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalCopyReplace();

// �Ի�������
	enum { IDD = IDD_MODAL_IMAGE_REPLACE_COPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioInput1();
	afx_msg void OnBnClickedRadioInput2();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

public:
	struct INPUT{
		NPKobject *ptrNo;
	}in;
	struct OUTPUT{
		int operate;
		int type;
		int selectID;
	}out;
};
