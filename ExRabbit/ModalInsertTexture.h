#pragma once


// ModalInsertTexture �Ի���

class ModalInsertTexture : public CDialogEx
{
	DECLARE_DYNAMIC(ModalInsertTexture)

public:
	ModalInsertTexture(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalInsertTexture();

// �Ի�������
	enum { IDD = IDD_MODAL_INSERT_TEXTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	//����
	struct INPUT{
		bool firstInsert;
		TEXinfo ti;
		int maxTEXcount;
	}in;
	//����
	struct OUTPUT{
		void *context;
		int operate;		//ѡ����1-4
		bool adjustTexID;	//������������֡�������������
		int outputFormat;	//ѡ����1-4
		CString fileName;	//��Դ�ļ���
		int inputFormat;	//0.�� 1.PNG 2.DDS
	}out;
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioOperate4();
	afx_msg void OnBnClickedRadioFormat1();
	afx_msg void OnBnClickedRadioFormat2();
	afx_msg void OnBnClickedRadioFormat3();
	afx_msg void OnBnClickedRadioFormat4();
	afx_msg void OnBnClickedButtonResource();
	afx_msg void OnBnClickedOk();

	void updateRadio();
};
