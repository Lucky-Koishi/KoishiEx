#pragma once


// TinyBar �Ի���

class TinyBar : public CDialogEx
{
	DECLARE_DYNAMIC(TinyBar)

public:
	TinyBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TinyBar();

// �Ի�������
	enum { IDD = IDD_TINY_PROGRESSBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void setMax(long value);
	void setPos(long value);
	void setInfo(CString info);
	void setInfo(CString info, long value);
	void show();
	void show(long value);
	void hide();
};
