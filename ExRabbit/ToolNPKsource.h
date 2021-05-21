#pragma once
#include "stdafx.h"
#include <locale.h>
#include <vector>

// ToolNPKsource 对话框

class ToolNPKsource : public CDialogEx
{
	DECLARE_DYNAMIC(ToolNPKsource)

public:
	ToolNPKsource(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolNPKsource();

// 对话框数据
	enum { IDD = IDD_TOOL_NPK_SOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	typedef struct ToolNPKentry {
		CString fileName;
		CString comment;
	}ToolNPKentry;
	typedef struct ToolNPK_Nmap{
		CString fileName;
		CString path;
	}ToolNPK_Nmap;
	std::vector<ToolNPKentry> listDict;
	std::vector<ToolNPK_Nmap> listMap;
	std::vector<ToolNPKentry> resultDict;
	std::vector<ToolNPK_Nmap> resultMap;
	char mode;
	BOOL isPatch;

	CString fixInfo;
	void clearInfo() {
		auto mm = GET_CTRL(CEdit, IDC_EDIT4);
		fixInfo += L"";
		mm->SetWindowText(fixInfo);
	}
	void addInfo(CString newInfo) {
		auto mm = GET_CTRL(CEdit, IDC_EDIT4);
		fixInfo += newInfo + L"\r\n";
		mm->SetWindowText(fixInfo);
		mm->LineScroll(mm->GetLineCount());
	}
public:
	void* context;
protected:
	DeclareThreadFunc(ToolNPKsource, initialTool, PVOID);
	DeclareThreadFunc(ToolNPKsource, generateMapFile, CString); //根据资源文件生成NPKmap.txt
	DeclareThreadFunc(ToolNPKsource, loadDictFile, PVOID);		//读取NPKdict.txt文件
	DeclareThreadFunc(ToolNPKsource, loadMapFile, PVOID);			//读取NPKmap.txt文件
	DeclareThreadFunc(ToolNPKsource, loadOtherDictFile, CString);	//读取其他的NPKdict文件并合并
	DeclareThreadFunc(ToolNPKsource, loadSomebodysFile, CString);	//读取某人的代码表
	DeclareThreadFunc(ToolNPKsource, queryDict, CString);		//查找标注和NPK名里包含keyWord的NPK
	DeclareThreadFunc(ToolNPKsource, queryMap, CString);			//查找路径名包括keyWord的IMG及其所在NPK
	DeclareThreadFunc(ToolNPKsource, fixIMG, PVOID);	//修复IMG，mode:'r'完全替换'a'增加缺失帧'c'制作副本

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonInitial();
	afx_msg void OnBnClickedButtonOpenFolder();
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonExplore();
	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonQueryPath();
	afx_msg void OnBnClickedButtonSearchAnd();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnImport1();
	afx_msg void OnImport2();
	afx_msg void OnImgModify1();
	afx_msg void OnImgModify2();
	afx_msg void OnImgModify3();
	afx_msg void OnImgModifyPatch1();
	afx_msg void OnImgModifyPatch2();
	afx_msg void OnImgModifyPatch3();
};
