#pragma once


// TinyStretch �Ի���

class TinyStretch : public CDialogEx
{
	DECLARE_DYNAMIC(TinyStretch)

public:
	TinyStretch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyStretch();

// �Ի�������
	enum { IDD = IDD_TINY_STRETCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
public:
	int sampleRate;
	longex originLen;		//������
	double rate;		//�����ֵ
};
