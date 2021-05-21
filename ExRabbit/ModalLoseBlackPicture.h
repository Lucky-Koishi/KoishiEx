#pragma once


// ModalLoseBlackPicture �Ի���

class ModalLoseBlackPicture : public CDialogEx
{
	DECLARE_DYNAMIC(ModalLoseBlackPicture)

public:
	ModalLoseBlackPicture(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalLoseBlackPicture();

// �Ի�������
	enum { IDD = IDD_MODAL_LOSEBLACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();

	//����
	struct INPUT{
		IMGversion version;
	}in;
	struct OUTPUT{
		int target;		//ѡ����1-2
		int gamma;		//1.PNG 2.IMG
	}out;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
