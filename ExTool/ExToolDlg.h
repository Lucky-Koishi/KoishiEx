
// ExToolDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
#include "../KoishiEx//KoishiAudioTool.h"

// CExToolDlg �Ի���
class CExToolDlg : public CDialogEx
{
// ����
public:
	CExToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXTOOL_DIALOG };

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

protected:
	void fun();
	static unsigned funThread(void*p){
		((CExToolDlg*)p)->fun();
		return 0U;
	}
public:
	afx_msg void OnBnClickedOk(){
		AfxBeginThread(funThread, this);
	}
	void setPos1(int pos){
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetPos(pos);
	}
	void setPos2(int pos){
		((CProgressCtrl *)GetDlgItem(IDC_PROGRESS2))->SetPos(pos);
	}
	void printf(const CString &ss){
		GetDlgItem(IDC_EDIT1)->SetWindowText(ss);
	}
	CString CStr(int n){
		CString nstr;
		nstr.Format(L"%d",n);
		return nstr;
	}
	CString CStr(std::string n){
		return CString(n.c_str());
	}
	afx_msg void OnBnClickedButton1();

public:
	static void fun20(void*para) {
		((CExToolDlg*)para)->fun2();
	}
	static void fun30(void*para) {
		((CExToolDlg*)para)->fun3();
	}
	//NPK��������
	//���汾��ͳ��NPK����������IMG�ĸ�������������
	//��Բ�ͬ�汾ͳ��֡PIC��ʽ����ǰ����˫�֣��ĸ�������������
	void fun2();	//NPK�������� 
	//װ��ͳ�ƹ���
	//��װ�����Ƹ�ʽ����������ְҵ����װ������ĸ�ͼ�㣨��������
	void fun3();
	afx_msg void OnBnClickedButton2();
};
