#pragma once


// ModalPictureStretch �Ի���

class ModalPictureStretch : public CDialogEx
{
	DECLARE_DYNAMIC(ModalPictureStretch)

public:
	ModalPictureStretch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalPictureStretch();

// �Ի�������
	enum { IDD = IDD_MODAL_PICTURE_STRETCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	//����
	struct __input {
		long imgX1, imgY1, imgX2, imgY2;
		long curX1, curX2, curY1, curY2;
	}in;
public:
	//���
	enum __mode{
		PIXEL_MODE, RATIO_MODE
	};
	struct __output {
		enumSelectType target;
		__mode mode;
		BOOL enable[4];
		long para[4];
	}out;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();


	afx_msg void OnBnClickedOk();
};
