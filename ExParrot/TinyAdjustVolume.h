#pragma once


// TinyAdjustVolume �Ի���

class TinyAdjustVolume : public CDialogEx
{
	DECLARE_DYNAMIC(TinyAdjustVolume)

public:
	TinyAdjustVolume(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyAdjustVolume();

// �Ի�������
	enum { IDD = IDD_TINY_ADJUST_VOLUME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();

public:
	int maxEnergy;		//������
	double rate;		//�����ֵ
	virtual BOOL OnInitDialog();
};
