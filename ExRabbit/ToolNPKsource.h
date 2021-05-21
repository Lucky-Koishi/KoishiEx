#pragma once
#include "stdafx.h"
#include <locale.h>
#include <vector>

// ToolNPKsource �Ի���

class ToolNPKsource : public CDialogEx
{
	DECLARE_DYNAMIC(ToolNPKsource)

public:
	ToolNPKsource(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolNPKsource();

// �Ի�������
	enum { IDD = IDD_TOOL_NPK_SOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	DeclareThreadFunc(ToolNPKsource, generateMapFile, CString); //������Դ�ļ�����NPKmap.txt
	DeclareThreadFunc(ToolNPKsource, loadDictFile, PVOID);		//��ȡNPKdict.txt�ļ�
	DeclareThreadFunc(ToolNPKsource, loadMapFile, PVOID);			//��ȡNPKmap.txt�ļ�
	DeclareThreadFunc(ToolNPKsource, loadOtherDictFile, CString);	//��ȡ������NPKdict�ļ����ϲ�
	DeclareThreadFunc(ToolNPKsource, loadSomebodysFile, CString);	//��ȡĳ�˵Ĵ����
	DeclareThreadFunc(ToolNPKsource, queryDict, CString);		//���ұ�ע��NPK�������keyWord��NPK
	DeclareThreadFunc(ToolNPKsource, queryMap, CString);			//����·��������keyWord��IMG��������NPK
	DeclareThreadFunc(ToolNPKsource, fixIMG, PVOID);	//�޸�IMG��mode:'r'��ȫ�滻'a'����ȱʧ֡'c'��������

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
