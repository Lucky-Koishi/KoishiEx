#pragma once


// TinyAdjustSpeed �Ի���

class TinyAdjustSpeed : public CDialogEx
{
	DECLARE_DYNAMIC(TinyAdjustSpeed)

public:
	TinyAdjustSpeed(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyAdjustSpeed();

// �Ի�������
	enum { IDD = IDD_TINY_ADJUST_SPEED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	enum {
		ADJUST_SPEED, ADJUST_PITCH
	};
	int type;
	double rate;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
