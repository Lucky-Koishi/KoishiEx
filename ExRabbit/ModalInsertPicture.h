#pragma once


// ModalInsertPicture �Ի���

class ModalInsertPicture : public CDialogEx
{
	DECLARE_DYNAMIC(ModalInsertPicture)

public:
	ModalInsertPicture(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalInsertPicture();

// �Ի�������
	enum { IDD = IDD_MODAL_INSERT_PICTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	//����
	struct INPUT{
		bool firstInsert;
		IMGversion version;
		PICinfo pi;
		int maxPICcount;
		int maxTEXcount;
	}in;
	//����
	struct OUTPUT{
		void *context;
		int operate;		//ѡ����1-5
		int type;			//ѡ����1-3
		int outputFormat;	//ѡ����1-4
		CString fileName;	//��Դ�ļ���
		int inputFormat;	//0.�� 1.PNG 2.DDS
		int para[10];		//�������
	}out;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioOperate4();
	afx_msg void OnBnClickedRadioOperate5();
	afx_msg void OnBnClickedRadioType1();
	afx_msg void OnBnClickedRadioType2();
	afx_msg void OnBnClickedRadioType3();
	afx_msg void OnBnClickedRadioFormat1();
	afx_msg void OnBnClickedRadioFormat2();
	afx_msg void OnBnClickedRadioFormat3();
	afx_msg void OnBnClickedRadioFormat4();
	afx_msg void OnBnClickedButtonResource();
	afx_msg void OnBnClickedOk();
};
