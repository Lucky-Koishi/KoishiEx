#include "stdafx.h"
#include "TinyBar.h"
#pragma once

//
//// ToolDownload 对话框
//初始化：先查看有没有未下载完的列表，如果有，提示是否继续下载
//如果没有未下载完的列表或者被用户中断了下载，
//读取本地列表文件，如果本地列表文件不存在
//提示是否下载服务器列表文件并解析（解析失败或者放弃下载服务器列表的话，会被强行关闭）
//列表文件读取后，显示在列表中，可以进行选择、筛查并进行下载


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
	void *context;				//上下文
	TinyBar bar;				//滚动条
	CListCtrl *lcIn, *lcOut;	//文件列表、下载列表
public:
	SERVER_INFO serverInfo;
	CString folderName;
	CString recordFileName;
	CString listFileName;
	CString destFolderName;
	std::vector<CString> fileNameList;
	std::vector<CString> fileSizeList;

	DeclareThreadFunc(ToolDownload, Initial, PVOID);
	DeclareThreadFunc(ToolDownload, DownloadListFile, PVOID);			//下载列表文件
	DeclareThreadFunc(ToolDownload, DownloadFile, PVOID);				//下载文件	
	DeclareThreadFunc(ToolDownload, QueryFile, CString);				//查询文件列表文件	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGetList();
	afx_msg void OnBnClickedButtonKeyword();
	afx_msg void OnBnClickedButtonFolder();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonStart();

public:
	//“继续上次下载”相关功能
	struct {
		std::vector<CString> fileName;
		std::vector<CString> fileLength;
		std::vector<char> completed;
	}record;
	void loadRecord();//更新下载记录
	void updateRecord();//更新下载记录
	void removeRecord();//删除下载记录

	//重名时提示内容
	//0. 提示，要用户选择
	//1. 重名时，跳过
	//2. 重名时，仍然下载并替换
	UCHAR skipExistedFile;
	afx_msg void OnNMRClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListOrigin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickSelectAll();
	afx_msg void OnClickSelectReverse();
	afx_msg void OnClickSelectHighline();
	virtual void OnOK();
};
