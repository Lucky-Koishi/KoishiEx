#include "stdafx.h"
#include "TinyBar.h"
#pragma once

//
//// ToolDownload 对话框
typedef struct _server_info{
	CString name;
	CString url;
	BOOL isTCT;
}SERVER_INFO, *PSERVER_INFO;

class ToolDownload : public CDialogEx
{
	DECLARE_DYNAMIC(ToolDownload)

public:
	ToolDownload(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolDownload();

// 对话框数据
	enum { IDD = IDD_TOOL_DOWNLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void *context;
	Profile profile;
	TinyBar bar;
	std::vector<SERVER_INFO> serverList;

	DeclareThreadFunc(LoadServerList, PVOID);			//读取服务器信息列表
	DeclareThreadFunc(LoadFileList, CString);			//读取文件列表
	DeclareThreadFunc(DownloadListFile, PVOID);			//下载列表文件
	DeclareThreadFunc(DownloadFile, PVOID);				//下载文件	
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

	void loadRecord(const CString &serverName);//更新下载记录
	void updateRecord(const CString &serverName);//更新下载记录
	void removeRecord(const CString &serverName);//删除下载记录

	void enableControls(BOOL b);

	afx_msg void OnNMRClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickSelectAll();
	afx_msg void OnClickSelectReverse();
	afx_msg void OnClickSelectHighline();
};
