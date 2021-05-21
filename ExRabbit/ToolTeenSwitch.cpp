// ToolTeenSwitch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolTeenSwitch.h"
#include "afxdialogex.h"
#include <thread>
// ToolTeenSwitch �Ի���

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


// ToolTeenSwitch ��Ϣ�������


void ToolTeenSwitch::OnOK() {
	// TODO:  ���λس���
}


BOOL ToolTeenSwitch::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ProfileBlack pf;
	pf.loadProfile();
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(pf.getOutputPath());
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(TRUE);
	GET_CTRL(CEdit, IDC_EDIT6)->SetWindowText(L"(18+)");
	GET_CTRL(CEdit, IDC_EDIT7)->SetWindowText(L"sprite(18+).NPK");
	showKeyWordFile();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString folderName;
	CALL_FOLDER_DIALOG(folderName, L"ѡ���ļ�����", L"��ʾ��", L"��������Ч���ļ�����");
	if(folderName.GetLength() > 0) {
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(folderName+L"\\");
	}
}


void ToolTeenSwitch::OnBnClickedButton2() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ProfileBlack pf;
	pf.loadProfile();
	CString keyFileName = pf.getSupportPath() + L"teen_keywords.txt";
	ShellExecute(NULL, L"open", keyFileName, NULL, NULL, SW_SHOW);
}


void ToolTeenSwitch::OnBnClickedButton3() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	showKeyWordFile();
}


void ToolTeenSwitch::OnBnClickedCheck2() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(FALSE);
	GET_CTRL(CEdit, IDC_EDIT6)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT7)->EnableWindow(FALSE);
}


void ToolTeenSwitch::OnBnClickedCheck3() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(TRUE);
	GET_CTRL(CEdit, IDC_EDIT6)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT7)->EnableWindow(TRUE);
}


void ToolTeenSwitch::OnBnClickedButton4() {
	// TODO:  ��ʼ
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
	addInfo(L"���ڻ�ȡNPK�б�������");
	GetFile(folderName + L".", fileList, pathList);
	if(pathList.size() == 0) {
		addInfo(L"û���ҵ�NPK�ļ�����");
		GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
		return;
	}
	addInfo(L"��ʼ��������");
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
		//��ʼ����
		for(int i = 0; i < no.getCount(); i++) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			if(pathName.GetLength() <= 4)
				continue;
			BOOL isTN = FALSE;
			//��ÿ���ؼ��ʽ��бȶ�
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
			//�������ؼ��ʵ�NPK�ļ�ֱ��������ûʲô�¶���
			addInfo(L"δ��" + GetTail(pathName) + L"�з��ֿ��Ժ�г�����ݡ�");
			continue;
		}
		addInfo(L"����" + NumToCStr(entryWithTN.size())+L"����г�ؼ��ʣ�λ��" + GetTail(pathName) + L"�С�");
		//�Բ����ؼ��ʵ���Ŀ�е�ÿһ��ڴ��ؼ��ʵ���Ŀ����һ����
		for(int i : entryWithoutTN) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			pathName = pathName.Left(pathName.GetLength() - 4);
			for(int j : entryWithTN) {
				CString pathNameTN = GetTail(StrToCStr(no.content[j].comment));
				//����ģ���Աȣ����������
				if(pathNameTN.Find(pathName) != -1) {
					//����ҵ��ˣ�����ȷ�Ա�
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
						//�Ѿ���ȷƥ��
						stream sData;
						str comm;
						no.extract(i, sData);		//�ò����ؼ��ʵ���Դ
						comm = no.content[j].comment;	//�ô��ؼ��ʵ�·����
						if(oneFile) {
							newTotalNo.push(comm, sData);
							sizeTotal += sData.length;
							if(sizeTotal >= (100 << 20)) {
								//����100M�ˣ�����Ҫ����ļ���
								CString newNoFileName = folderName + genFileName;
								if(fileCount > 0) {
									newNoFileName = newNoFileName.Left(newNoFileName.GetLength() - 4);
									newNoFileName += L"(" + NumToCStr(fileCount) + L").NPK";
								}
								newTotalNo.saveFile(CStrToStr(newNoFileName));
								addInfo(L"������" + GetTail(newNoFileName));
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
						//δ��ȷƥ�䡤������һ��pathNameTN���Ƿ���ƥ��
					}
				}
			}
		}
		//�����ļ�
		if(!oneFile) {
			if(newNo.getCount() > 0) {
				CString newNoFileName = pathName.Left(pathName.GetLength() - 4);
				newNoFileName += genSuffix + L".NPK";
				newNo.saveFile(CStrToStr(newNoFileName));
				addInfo(L"������" + GetTail(newNoFileName));
			} else {
				addInfo(L"δ��ȷ����г���֣��������ɡ�");
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
			addInfo(L"������" + GetTail(newNoFileName));
		} else {
			addInfo(L"δ��ȷ����г���֣��������ɡ�");
		}
	}
	addInfo(L"���������");
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
	addInfo(L"���ڻ�ȡNPK�б�������");
	if(pathList.size() == 0) {
		addInfo(L"û���ҵ�NPK�ļ�����");
		GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
		return;
	}
	addInfo(L"��ʼ��������");
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
		//��ʼ����
		for(int i = 0; i < no.getCount(); i++) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			if(pathName.GetLength() <= 4)
				continue;
			BOOL isTN = FALSE;
			//��ÿ���ؼ��ʽ��бȶ�
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
			//�������ؼ��ʵ�NPK�ļ�ֱ��������ûʲô�¶���
			addInfo(L"δ��" + GetTail(pathName) + L"�з��ֿ��Ժ�г�����ݡ�");
			continue;
		}
		addInfo(L"����" + NumToCStr(entryWithTN.size()) + L"����г�ؼ��ʣ�λ��" + GetTail(pathName) + L"�С�");
		//�Բ����ؼ��ʵ���Ŀ�е�ÿһ��ڴ��ؼ��ʵ���Ŀ����һ����
		for(int i : entryWithoutTN) {
			CString pathName = GetTail(StrToCStr(no.content[i].comment));
			pathName = pathName.Left(pathName.GetLength() - 4);
			for(int j : entryWithTN) {
				CString pathNameTN = GetTail(StrToCStr(no.content[j].comment));
				//����ģ���Աȣ����������
				if(pathNameTN.Find(pathName) != -1) {
					//����ҵ��ˣ�����ȷ�Ա�
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
						//�Ѿ���ȷƥ��
						stream sData;
						str comm;
						no.extract(i, sData);		//�ò����ؼ��ʵ���Դ
						comm = no.content[j].comment;	//�ô��ؼ��ʵ�·����
						newNo.push(comm, sData);
						break;
					} else {
						//δ��ȷƥ�䡤������һ��pathNameTN���Ƿ���ƥ��
					}
				}
			}
		}
		//�����ļ�
		if(newNo.getCount() > 0) {
			CString newNoFileName = pathName.Left(pathName.GetLength() - 4);
			newNoFileName += genSuffix + L".NPK";
			newNo.saveFile(CStrToStr(newNoFileName));
			addInfo(L"������" + GetTail(newNoFileName));
		} else {
			addInfo(L"δ��ȷ����г���֣��������ɡ�");
		}
	}
	addInfo(L"���������");
	GET_CTRL(CButton, IDC_BUTTON4)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
}
void ToolTeenSwitch::OnDropFiles(HDROP hDropInfo) {
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	WCHAR szPath[MAX_PATH] = L"";
	UINT fileCount = ::DragQueryFile(hDropInfo, -1, NULL, NULL);		//��ȡ�Ͻ������ļ���
	UINT nChars = ::DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);		//��ȡ�Ͻ����ĵ�һ���ļ�
	CString fileName(szPath, nChars);									//���we����
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
