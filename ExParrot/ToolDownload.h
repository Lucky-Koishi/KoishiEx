#include "stdafx.h"
#include "TinyBar.h"
#pragma once

//
//// ToolDownload �Ի���
//��ʼ�����Ȳ鿴��û��δ��������б�����У���ʾ�Ƿ��������
//���û��δ��������б���߱��û��ж������أ�
//��ȡ�����б��ļ�����������б��ļ�������
//��ʾ�Ƿ����ط������б��ļ�������������ʧ�ܻ��߷������ط������б�Ļ����ᱻǿ�йرգ�
//�б��ļ���ȡ����ʾ���б��У����Խ���ѡ��ɸ�鲢��������


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
	void *context;				//������
	TinyBar bar;				//������
	CListCtrl *lcIn, *lcOut;	//�ļ��б������б�
public:
	SERVER_INFO serverInfo;
	CString folderName;
	CString recordFileName;
	CString listFileName;
	CString destFolderName;
	std::vector<CString> fileNameList;
	std::vector<CString> fileSizeList;

	DeclareThreadFunc(ToolDownload, Initial, PVOID);
	DeclareThreadFunc(ToolDownload, DownloadListFile, PVOID);			//�����б��ļ�
	DeclareThreadFunc(ToolDownload, DownloadFile, PVOID);				//�����ļ�	
	DeclareThreadFunc(ToolDownload, QueryFile, CString);				//��ѯ�ļ��б��ļ�	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGetList();
	afx_msg void OnBnClickedButtonKeyword();
	afx_msg void OnBnClickedButtonFolder();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonStart();

public:
	//�������ϴ����ء���ع���
	struct {
		std::vector<CString> fileName;
		std::vector<CString> fileLength;
		std::vector<char> completed;
	}record;
	void loadRecord();//�������ؼ�¼
	void updateRecord();//�������ؼ�¼
	void removeRecord();//ɾ�����ؼ�¼

	//����ʱ��ʾ����
	//0. ��ʾ��Ҫ�û�ѡ��
	//1. ����ʱ������
	//2. ����ʱ����Ȼ���ز��滻
	UCHAR skipExistedFile;
	afx_msg void OnNMRClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickSelectAll();
	afx_msg void OnClickSelectReverse();
	afx_msg void OnClickSelectHighline();
	virtual void OnOK();
};
