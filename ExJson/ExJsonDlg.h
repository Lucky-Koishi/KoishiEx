
// ExJsonDlg.h : ͷ�ļ�
//

#pragma once


// CExJsonDlg �Ի���
class CExJsonDlg : public CDialogEx
{
// ����
public:
	CExJsonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXJSON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	static UINT writeThread(void *p);
	void write();
	afx_msg void OnBnClickedStart();
};
