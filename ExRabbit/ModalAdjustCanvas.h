#pragma once


// ModalAdjustCanvas �Ի���

class ModalAdjustCanvas : public CDialogEx
{
	DECLARE_DYNAMIC(ModalAdjustCanvas)

public:
	ModalAdjustCanvas(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalAdjustCanvas();

// �Ի�������
	enum { IDD = IDD_MODAL_ADJUST_CANVAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//����
	struct INPUT{
		long imgX1, imgY1, imgX2, imgY2;
		long curX1, curX2, curY1, curY2;
	}in;
public:
	//���
	struct OUTPUT{
		int target;
		int operate;
		bool enable[4];
		int para[4];
	}out;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioOperate4();
	afx_msg void OnBnClickedOk();
};
