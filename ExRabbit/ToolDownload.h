#include "stdafx.h"
#include "TinyBar.h"
#pragma once

//
//// ToolDownload �Ի���
typedef struct _server_info{
	CString name;
	CString url;
	BOOL isTCT;
}SERVER_INFO, *PSERVER_INFO;

class ToolDownload : public CDialogEx
{
	DECLARE_DYNAMIC(ToolDownload)

public:
	ToolDownload(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolDownload();

// �Ի�������
	enum { IDD = IDD_TOOL_DOWNLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void *context;
	Profile profile;
	TinyBar bar;
	std::vector<SERVER_INFO> serverList;

	DeclareThreadFunc(LoadServerList, PVOID);			//��ȡ��������Ϣ�б�
	DeclareThreadFunc(LoadFileList, CString);			//��ȡ�ļ��б�
	DeclareThreadFunc(DownloadListFile, PVOID);			//�����б��ļ�
	DeclareThreadFunc(DownloadFile, PVOID);				//�����ļ�	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGetList();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonKeyword();
	afx_msg void OnBnClickedButtonFolder();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnCbnSelchangeComboServer();

	struct {
		std::vector<CString> fileName;
		std::vector<CString> fileLength;
		std::vector<char> completed;
	}record;

	void loadRecord(const CString &serverName);//�������ؼ�¼
	void updateRecord(const CString &serverName);//�������ؼ�¼
	void removeRecord(const CString &serverName);//ɾ�����ؼ�¼

	void enableControls(BOOL b);

	afx_msg void OnNMRClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickSelectAll();
	afx_msg void OnClickSelectReverse();
	afx_msg void OnClickSelectHighline();
};
