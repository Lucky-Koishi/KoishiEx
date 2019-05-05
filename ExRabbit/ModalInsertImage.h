#pragma once


// ModalInsertImage �Ի���

class ModalInsertImage : public CDialogEx
{
	DECLARE_DYNAMIC(ModalInsertImage)

public:
	ModalInsertImage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalInsertImage();

// �Ի�������
	enum { IDD = IDD_MODAL_IMAGE_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioInput1();
	afx_msg void OnBnClickedRadioInput2();
	afx_msg void OnBnClickedRadioInput3();
	afx_msg void OnBnClickedRadioInput4();
	afx_msg void OnBnClickedRadioVersion1();
	afx_msg void OnBnClickedRadioVersion2();
	afx_msg void OnBnClickedRadioVersion3();
	afx_msg void OnBnClickedRadioVersion4();
	afx_msg void OnBnClickedRadioConflick1();
	afx_msg void OnBnClickedRadioConflick2();
	afx_msg void OnBnClickedRadioConflick3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

public:
	struct INPUT{
		bool firstInsert;
	}in;
	struct OUTPUT{
		int operate;
		int type;
		IMGversion newVersion;
		CString pathName;	//ȫ·����
		CString fileName;	//�ı���
		int conflict;
	}out;
};
