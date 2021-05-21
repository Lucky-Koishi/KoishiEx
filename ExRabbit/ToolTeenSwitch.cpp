// ToolTeenSwitch.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolTeenSwitch.h"
#include "afxdialogex.h"
#include <thread>
// ToolTeenSwitch 对话框

IMPLEMENT_DYNAMIC(ToolTeenSwitch, CDialogEx)

ToolTeenSwitch::ToolTeenSwitch(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolTeenSwitch::IDD, pParent)
{

}

ToolTeenSwitch::~ToolTeenSwitch()
{
}

void ToolTeenSwitch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolTeenSwitch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ToolTeenSwitch::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ToolTeenSwitch::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ToolTeenSwitch::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK2, &ToolTeenSwitch::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &ToolTeenSwitch::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON4, &ToolTeenSwitch::OnBnClickedButton4)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// ToolTeenSwitch 消息处理程序


void ToolTeenSwitch::OnOK() {
	// TODO:  屏蔽回车键
}


BOOL ToolTeenSwitch::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ProfileBlack pf;
	pf.loadProfile();
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(pf.getOutputPath());
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(TRUE);
	GET_CTRL(CEdit, IDC_EDIT6)->SetWindowText(L"(18+)");
	GET_CTRL(CEdit, IDC_EDIT7)->SetWindowText(L"sprite(18+).NPK");
	showKeyWordFile();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

std::vector<CString>  ToolTeenSwitch::loadKeyWordFile() {
	ProfileBlack pf;
	pf.loadProfile();
	CString keyFileName = pf.getSupportPath() + L"teen_keywords.txt";
	CStdioFile file;
	if(file.Open(keyFileName, CFile::modeRead)) {
		std::vector<CString> keyList;
		CString keyWord;
		while(file.ReadString(keyWord) && keyWord.GetLength())
			keyList.push_back(keyWord);
		return keyList;
	} else {
		std::vector<CString> keyList = {L"(tn)", L"(18)", L"_teen", L"teen_"};
		file.Open(keyFileName, CFile::modeCreate | CFile::modeWrite);
		for(CString keyWord : keyList)
			file.WriteString(keyWord + L"\n");
		file.Close();
		return keyList;
	}
}

void ToolTeenSwitch::showKeyWordFile() {
	std::vector<CString> keyList = loadKeyWordFile();
	CString showList;
	for(CString keyWord : keyList) {
		showList += keyWord + L" ";
	}
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(showList);
}

void ToolTeenSwitch::addInfo(const CString &rString) {
	infoString += rString + L"\r\n";
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(infoString);
	GET_CTRL(CEdit, IDC_EDIT3)->LineScroll(GET_CTRL(CEdit, IDC_EDIT3)->GetLineCount());
}
void ToolTeenSwitch::OnBnClickedButton1() {
	// TODO:  在此添加控件通知处理程序代码
	CString folderName;
	CALL_FOLDER_DIALOG(folderName, L"选择文件夹喵", L"提示喵", L"并不是有效的文件夹喵");
	if(folderName.GetLength() > 0) {
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(folderName+L"\\");
	}
}


void ToolTeenSwitch::OnBnClickedButton2() {
	// TODO:  在此添加控件通知处理程序代码
	ProfileBlack pf;
	pf.loadProfile();
	CString keyFileName = pf.getSupportPath() + L"teen_keywords.txt";
	ShellExecute(NULL, L"open", keyFileName, NULL, NULL, SW_SHOW);
}


void ToolTeenSwitch::OnBnClickedButton3() {
	// TODO:  在此添加控件通知处理程序代码
	showKeyWordFile();
}


void ToolTeenSwitch::OnBnClickedCheck2() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(FALSE);
	GET_CTRL(CEdit, IDC_EDIT6)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT7)->EnableWindow(FALSE);
}


void ToolTeenSwitch::OnBnClickedCheck3() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(TRUE);
	GET_CTRL(CEdit, IDC_EDIT6)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT7)->EnableWindow(TRUE);
}


void ToolTeenSwitch::OnBnClickedButton4() {
	// TODO:  开始
	StartThreadFunc(Make18plus, 0);
}

void ToolTeenSwitch::Make18plus(INT para) {
	GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(FALSE);
	CString folderName;
	CString genFileName, genSuffix;
	showKeyWordFile();
	std::vector<CString> keyList = loadKeyWordFile();
	std::vector<CString> fileList;
	std::vector<CString> pathList;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderName);
	GET_CTRL(CEdit, IDC_EDIT6)->GetWindowText(genSuffix);
	GET_CTRL(CEdit, IDC_EDIT7)->GetWindowText(genFileName);
	if(folderName.Right(1) != L"\\")
		folderName += L"\\";
	BOOL oneFile = GET_CTRL(CButton, IDC_CHECK3)->GetCheck();
	NPKobject newTotalNo;
	infoString = L"";
	addInfo(L"正在获取NPK列表喵……");
	GetFile(folderName + L".", fileList, pathList);
	if(pathList.size() == 0) {
		addInfo(L"没有找到NPK文件喵。");
		GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
		return;
	}
	addInfo(L"开始生成喵。");
	GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetRange32(0, pathList.size());
	int p = 0;
	int fileCount = 0;
	LONGLONG sizeTotal = 0;
	newTotalNo.create();
	for(CString pathName : pathList) {
		GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(++p);
		if(pathName.Right(4).MakeUpper() != L".NPK")
			continue;
		NPKobject no,newNo;
		if(!no.loadFile(CStrToStr(pathName)))
		   continue;
		std::vector<int> entryWithTN, entryWithoutTN;
		//开始分类
		for(int i = 0; i < no.getCount(); i++) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			if(pathName.GetLength() <= 4)
				continue;
			BOOL isTN = FALSE;
			//和每个关键词进行比对
			for(CString keyWord : keyList) {
				if(pathName.Find(keyWord) != -1) {
					isTN = TRUE;
					break;
				}
			}
			if(isTN) {
				entryWithTN.push_back(i);
			} else {
				entryWithoutTN.push_back(i);
			}
		}
		if(entryWithTN.size() == 0 || entryWithoutTN.size() == 0) {
			//都不带关键词的NPK文件直接跳过，没什么事儿了
			addInfo(L"未在" + GetTail(pathName) + L"中发现可以和谐的内容。");
			continue;
		}
		addInfo(L"发现" + NumToCStr(entryWithTN.size())+L"个和谐关键词，位于" + GetTail(pathName) + L"中。");
		//对不带关键词的条目中的每一项，在带关键词的条目中逐一查找
		for(int i : entryWithoutTN) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			pathName = pathName.Left(pathName.GetLength() - 4);
			for(int j : entryWithTN) {
				CString pathNameTN = GetTail(StrToCStr(no.content[j].comment));
				//先做模糊对比，检查包含结果
				if(pathNameTN.Find(pathName) != -1) {
					//如果找到了，做精确对比
					BOOL isOK = FALSE;
					for(CString keyWord : keyList) {
						CString ss[2] = {
							pathName + keyWord + L".img", 
							keyWord + pathName + L".img"
						};
						if(ss[0] == pathNameTN || ss[1] == pathNameTN) {
							isOK = TRUE;
							break;
						}
					}
					if(isOK) {
						//已经精确匹配
						stream sData;
						str comm;
						no.extract(i, sData);		//用不带关键词的资源
						comm = no.content[j].comment;	//用带关键词的路径名
						if(oneFile) {
							newTotalNo.push(comm, sData);
							sizeTotal += sData.length;
							if(sizeTotal >= (100 << 20)) {
								//超过100M了，必须要存个文件了
								CString newNoFileName = folderName + genFileName;
								if(fileCount > 0) {
									newNoFileName = newNoFileName.Left(newNoFileName.GetLength() - 4);
									newNoFileName += L"(" + NumToCStr(fileCount) + L").NPK";
								}
								newTotalNo.saveFile(CStrToStr(newNoFileName));
								addInfo(L"生成了" + GetTail(newNoFileName));
								fileCount++;
								sizeTotal = 0;
								newTotalNo.release();
								newTotalNo.create();
							}
						} else {
							newNo.push(comm, sData);
						}
						break;
					} else {
						//未精确匹配·看看下一个pathNameTN项是否能匹配
					}
				}
			}
		}
		//保存文件
		if(!oneFile) {
			if(newNo.getCount() > 0) {
				CString newNoFileName = pathName.Left(pathName.GetLength() - 4);
				newNoFileName += genSuffix + L".NPK";
				newNo.saveFile(CStrToStr(newNoFileName));
				addInfo(L"生成了" + GetTail(newNoFileName));
			} else {
				addInfo(L"未能确定和谐部分，跳过生成。");
			}
		}
	}
	if(oneFile) {
		if(newTotalNo.getCount() > 0) {
			CString newNoFileName = folderName + genFileName;
			if(fileCount > 0) {
				newNoFileName = newNoFileName.Left(newNoFileName.GetLength() - 4);
				newNoFileName += L"(" + NumToCStr(fileCount) + L").NPK";
			}
			newTotalNo.saveFile(CStrToStr(newNoFileName));
			addInfo(L"生成了" + GetTail(newNoFileName));
		} else {
			addInfo(L"未能确定和谐部分，跳过生成。");
		}
	}
	addInfo(L"完成了喵。");
	GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
}
void ToolTeenSwitch::Make18plus1(std::vector<CString> para) {
	GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(FALSE);
	CString genSuffix;
	showKeyWordFile();
	std::vector<CString> keyList = loadKeyWordFile();
	std::vector<CString> pathList = para;
	GET_CTRL(CEdit, IDC_EDIT6)->GetWindowText(genSuffix);
	infoString = L"";
	addInfo(L"正在获取NPK列表喵……");
	if(pathList.size() == 0) {
		addInfo(L"没有找到NPK文件喵。");
		GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
		return;
	}
	addInfo(L"开始生成喵。");
	GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetRange32(0, pathList.size());
	int p = 0;
	int fileCount = 0;
	LONGLONG sizeTotal = 0;
	for(CString pathName : pathList) {
		GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos(++p);
		if(pathName.Right(4).MakeUpper() != L".NPK")
			continue;
		NPKobject no, newNo;
		if(!no.loadFile(CStrToStr(pathName)))
			continue;
		std::vector<int> entryWithTN, entryWithoutTN;
		//开始分类
		for(int i = 0; i < no.getCount(); i++) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			if(pathName.GetLength() <= 4)
				continue;
			BOOL isTN = FALSE;
			//和每个关键词进行比对
			for(CString keyWord : keyList) {
				if(pathName.Find(keyWord) != -1) {
					isTN = TRUE;
					break;
				}
			}
			if(isTN) {
				entryWithTN.push_back(i);
			} else {
				entryWithoutTN.push_back(i);
			}
		}
		if(entryWithTN.size() == 0 || entryWithoutTN.size() == 0) {
			//都不带关键词的NPK文件直接跳过，没什么事儿了
			addInfo(L"未在" + GetTail(pathName) + L"中发现可以和谐的内容。");
			continue;
		}
		addInfo(L"发现" + NumToCStr(entryWithTN.size()) + L"个和谐关键词，位于" + GetTail(pathName) + L"中。");
		//对不带关键词的条目中的每一项，在带关键词的条目中逐一查找
		for(int i : entryWithoutTN) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			pathName = pathName.Left(pathName.GetLength() - 4);
			for(int j : entryWithTN) {
				CString pathNameTN = GetTail(StrToCStr(no.content[j].comment));
				//先做模糊对比，检查包含结果
				if(pathNameTN.Find(pathName) != -1) {
					//如果找到了，做精确对比
					BOOL isOK = FALSE;
					for(CString keyWord : keyList) {
						CString ss[2] = {
							pathName + keyWord + L".img",
							keyWord + pathName + L".img"
						};
						if(ss[0] == pathNameTN || ss[1] == pathNameTN) {
							isOK = TRUE;
							break;
						}
					}
					if(isOK) {
						//已经精确匹配
						stream sData;
						str comm;
						no.extract(i, sData);		//用不带关键词的资源
						comm = no.content[j].comment;	//用带关键词的路径名
						newNo.push(comm, sData);
						break;
					} else {
						//未精确匹配·看看下一个pathNameTN项是否能匹配
					}
				}
			}
		}
		//保存文件
		if(newNo.getCount() > 0) {
			CString newNoFileName = pathName.Left(pathName.GetLength() - 4);
			newNoFileName += genSuffix + L".NPK";
			newNo.saveFile(CStrToStr(newNoFileName));
			addInfo(L"生成了" + GetTail(newNoFileName));
		} else {
			addInfo(L"未能确定和谐部分，跳过生成。");
		}
	}
	addInfo(L"完成了喵。");
	GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
}
void ToolTeenSwitch::OnDropFiles(HDROP hDropInfo) {
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	WCHAR szPath[MAX_PATH] = L"";
	UINT fileCount = ::DragQueryFile(hDropInfo, -1, NULL, NULL);		//获取拖进来的文件数
	UINT nChars = ::DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);		//获取拖进来的第一个文件
	CString fileName(szPath, nChars);									//获得we年明
	std::vector<CString> fileList;
	for(int i = 0; i<fileCount; i++) {
		memset(szPath, 0, MAX_PATH * sizeof(WCHAR));
		nChars = ::DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
		fileName = CString(szPath, nChars);
		fileList.push_back(fileName);	
	}
	if(fileList.size() > 0) {
		StartThreadFunc(Make18plus1, fileList);
	}
	CDialogEx::OnDropFiles(hDropInfo);
}
