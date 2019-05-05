#pragma once


// ModalPictureParameter �Ի���

class ModalPictureParameter : public CDialogEx
{
	DECLARE_DYNAMIC(ModalPictureParameter)

public:
	ModalPictureParameter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalPictureParameter();

// �Ի�������
	enum { IDD = IDD_MODAL_MODIFY_PICTURE_PARAMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	//����
	struct INPUT{
		long curFH, curFW;
		long curBX, curBY;
	}in;
public:
	//���
	struct OUTPUT{
		int target;
		int operate;
		bool enable[2];
		int para[2];
	}out;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedOk();
};
