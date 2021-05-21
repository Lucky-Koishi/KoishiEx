#pragma once


// ModalInsertPicturePatch �Ի���

class ModalInsertPicturePatch : public CDialogEx
{
	DECLARE_DYNAMIC(ModalInsertPicturePatch)

public:
	ModalInsertPicturePatch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalInsertPicturePatch();

// �Ի�������
	enum { IDD = IDD_MODAL_INSERT_PICTURE_PATCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioFormat1();
	afx_msg void OnBnClickedRadioFormat2();
	afx_msg void OnBnClickedRadioFormat3();
	afx_msg void OnBnClickedRadioFormat4();
	afx_msg void OnBnClickedRadioMethod1();
	afx_msg void OnBnClickedRadioMethod2();
	afx_msg void OnBnClickedOk();

public:
	//����
	struct INPUT{
		IMGversion version;
		int maxPICcount;
	}in;
	//����
	struct OUTPUT{
		int operate;		//ѡ����1-2
		bool holdCoordinate;//operate=2ʱ�� �Ƿ���ԭ����
		int outputFormat;	//ѡ����1-4
		CString filePath;	//PNGʱΪ������Դ�ļ�������IMGʱΪIMG�ļ���
		int PNGcount;		//��ԴΪPNGʱ����ȡ��PNG��������ֵ�ϵ��ڵ����֡�ż�1����Ϊ����0��
		int inputFormat;	//1.PNG 2.IMG
	}out;
};
