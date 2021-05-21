// ToolAudioMark.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ToolAudioMark.h"
#include "afxdialogex.h"
#include <thread>

// ToolAudioMark 对话框

IMPLEMENT_DYNAMIC(ToolAudioMark, CDialogEx)

ToolAudioMark::ToolAudioMark(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAudioMark::IDD, pParent)
{
	interval = 300;
	beginID = 0;
	digitCount = 3;
	ProfileWhite profile;
	profile.loadProfile();
	reporter.loadFile(CStrToStr(profile.getSupportPath() + L"标记语音.NPK"));
	isOverlapped = FALSE;
	useFolder = FALSE;
}

ToolAudioMark::~ToolAudioMark()
{
}

void ToolAudioMark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolAudioMark, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &ToolAudioMark::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &ToolAudioMark::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK_MARK1, &ToolAudioMark::OnBnClickedCheckMark1)
	ON_BN_CLICKED(IDC_CHECK_MARK2, &ToolAudioMark::OnBnClickedCheckMark2)
	ON_BN_CLICKED(IDC_BUTTON_REPORT_SEARTCH, &ToolAudioMark::OnBnClickedButtonReportSeartch)
	ON_BN_CLICKED(IDC_BUTTON_REPORT_LISTEN, &ToolAudioMark::OnBnClickedButtonReportListen)
	ON_BN_CLICKED(IDC_BUTTON_MARKA, &ToolAudioMark::OnBnClickedButtonMarka)
	ON_BN_CLICKED(IDC_BUTTON_MARKB, &ToolAudioMark::OnBnClickedButtonMarkb)
	ON_BN_CLICKED(ID_START, &ToolAudioMark::OnBnClickedStart)
END_MESSAGE_MAP()


// ToolAudioMark 消息处理程序


BOOL ToolAudioMark::OnInitDialog() {
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	GET_CTRL(CEdit, IDC_EDIT_REPORT1)->SetWindowText(L"语音包");
	GET_CTRL(CEdit, IDC_EDIT_REPORT2)->SetWindowText(L"语音间隔(ms)");
	GET_CTRL(CEdit, IDC_EDIT_REPORTA)->SetWindowText(L"标记语音.NPK");
	GET_CTRL(CEdit, IDC_EDIT_REPORTB)->SetWindowText(L"300");
	GET_CTRL(CEdit, IDC_EDIT_NUMBER1)->SetWindowText(L"起始标记号码");
	GET_CTRL(CEdit, IDC_EDIT_NUMBER2)->SetWindowText(L"补零位数");
	GET_CTRL(CEdit, IDC_EDIT_NUMBERA)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_NUMBERB)->SetWindowText(L"3");
	GET_CTRL(CButton, IDC_RADIO1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ToolAudioMark::OnBnClickedRadio1() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_RADIO1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO2)->SetCheck(FALSE);
	isOverlapped = FALSE;
}


void ToolAudioMark::OnBnClickedRadio2() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_RADIO1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO2)->SetCheck(TRUE);
	isOverlapped = TRUE;
}


void ToolAudioMark::OnBnClickedCheckMark1() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK_MARK2)->SetCheck(FALSE);
	useFolder = FALSE;
}


void ToolAudioMark::OnBnClickedCheckMark2() {
	// TODO:  在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK_MARK2)->SetCheck(TRUE);
	useFolder = TRUE;
}


void ToolAudioMark::OnBnClickedButtonReportSeartch() {
	// TODO:  在此添加控件通知处理程序代码
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		GET_CTRL(CEdit, IDC_EDIT_REPORTA)->SetWindowText(dlg.GetPathName());
		if(reporter.getCount() > 0)
			reporter.release();
		if(!reporter.loadFile(CStrToStr(dlg.GetPathName()))) {
			MessageBox(L"无法识别的NPK文件，请换一个语音包导入喵！");
		}
		if(reporter.getCount() < 10) {
			MessageBox(L"NPK内的语音对象不足，请重新导入语音包喵！");
		}
	}
}


void ToolAudioMark::OnBnClickedButtonReportListen() {
	// TODO:  在此添加控件通知处理程序代码
	StartThreadFunc(TryPlay, nullptr);
}


void ToolAudioMark::OnBnClickedButtonMarka() {
	// TODO:  在此添加控件通知处理程序代码
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		GET_CTRL(CEdit, IDC_EDIT_MARKA)->SetWindowText(dlg.GetPathName());
		sourceFileName = dlg.GetPathName();
		GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(TRUE);
		GET_CTRL(CButton, IDC_CHECK_MARK2)->SetCheck(FALSE);
		useFolder = FALSE;
	}
}


void ToolAudioMark::OnBnClickedButtonMarkb() {
	// TODO:  在此添加控件通知处理程序代码
	CString folderName;
	CALL_FOLDER_DIALOG(folderName, L"选择文件夹喵", L"提示喵", L"并不是有效的文件夹喵。");
	if(folderName.GetLength()) {
		folderName += L"\\*.NPK";
		GET_CTRL(CEdit, IDC_EDIT_MARKB)->SetWindowText(folderName);
		sourceFolderName = folderName;
		GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(FALSE);
		GET_CTRL(CButton, IDC_CHECK_MARK2)->SetCheck(TRUE);
		useFolder = TRUE;
	} else {
		MessageBox(L"并不是有效的文件夹喵。");
	}
}

void ToolAudioMark::TryPlay(PVOID) {
	for(int i = 0; i < reporter.getCount(); i++) {
		const auto sv = reporter.SNDgetVersion(i);
		if(sv != VWAVE && sv != VVORBIS)
			continue;
		stream aStream;
		audio ad;
		if(!reporter.extract(i, aStream))
			continue;
		if(sv == VWAVE) {
			WAV::WAVobject wo;
			if(!wo.decodeAndMake(aStream, ad))
				continue;
			player.play(ad);
		} else {
			OGGvorbis::OGGobject oo;
			if(!oo.decodeAndMake(aStream, ad))
				continue;
			player.play(ad);
		}
		Sleep(10);
	}
}

void ToolAudioMark::addInfo(CString content) {
	info += content + L"\r\n";
	auto ectl = GET_CTRL(CEdit, IDC_EDIT_DETAIL);
	ectl->SetWindowText(info);
	ectl->LineScroll(ectl->GetLineCount());
}

queue ToolAudioMark::makeNumberSeq(long num) {
	queue digitSeq;
	for(int i = 0;;i++) {
		long n = num % 10;
		long m = num / 10;
		if(n == 0 && m == 0 && i >= digitCount)
			break;
		digitSeq.insert(digitSeq.begin(), n);
		num = m;
	}
	return digitSeq;
}
void ToolAudioMark::Marking(PVOID) {
	GET_CTRL(CButton, ID_START)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(FALSE);
	auto pctl = GET_CTRL(CProgressCtrl, IDC_PROGRESS1);
	info = L"";
	pctl->SetRange32(0, 1000);
	pctl->SetPos(0);
	CString text;
	GET_CTRL(CEdit, IDC_EDIT_REPORTB)->GetWindowText(text);
	interval = _ttoi(text);
	GET_CTRL(CEdit, IDC_EDIT_NUMBERA)->GetWindowText(text);
	beginID = _ttoi(text);
	GET_CTRL(CEdit, IDC_EDIT_NUMBERB)->GetWindowText(text);
	digitCount = min(10, _ttoi(text));
	addInfo(L"准备开始打标工作。");
	addInfo(L"正在导入语音包。");
	if(reporter.getCount() < 10) {
		addInfo(L"意外停止：语音包数目不足（≤10），当前为" + NumToCStr(reporter.getCount()));
		return;
	}
	audio numVoice[10];
	for(int i = 0; i < 10; i++) {
		const auto sv = reporter.SNDgetVersion(i);
		if(sv != VWAVE && sv != VVORBIS) {
			addInfo(L"意外停止：语音包中第" + NumToCStr(i + 1) + L"个对象格式不被支持。");
			return;
		}
		stream aStream;
		reporter.extract(i, aStream);
		if(sv == VWAVE) {
			WAV::WAVobject wo;
			if(!wo.decodeAndMake(aStream, numVoice[i])) {
				addInfo(L"意外停止：语音包中第" + NumToCStr(i + 1) + L"个音效解码失败。");
				return;
			}
		} else {
			OGGvorbis::OGGobject oo;
			if(!oo.decodeAndMake(aStream, numVoice[i])) {
				addInfo(L"意外停止：语音包中第" + NumToCStr(i + 1) + L"个音效解码失败。");
				return;
			}
		}
		addInfo(L"已导入音效作为数字" + NumToCStr(i) + L"的提示音");
		pctl->SetPos(100 * i);
	}
	addInfo(L"导入语音包完毕。");
	int trackInterval = interval * numVoice->sampleRate / 1000;
	pctl->SetPos(0);
	NPKobject sourceNPK, goalNPK;
	CStdioFile listTXT;
	int serial = beginID;
	if(!useFolder) {
		if(!sourceNPK.loadFile(CStrToStr(sourceFileName))) {
			addInfo(L"意外停止：文件" + sourceFileName + L"不能被识别。");
			return;
		}
		addInfo(L"已读取" + sourceFileName + L"。");
		goalNPK.create();
		listTXT.Open(sourceFileName.Left(sourceFileName.GetLength() - 4) + L"(标记列表).TXT", CFile::modeCreate | CFile::modeWrite);
		for(int i = 0; i < sourceNPK.getCount(); i++) {
			audio addedAd;
			stream addedStream;
			const auto sv = sourceNPK.SNDgetVersion(i);
			if(sv != VMP3 && sv != VVORBIS && sv != VWAVE) {
				addInfo(L"跳过：" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"不是音效文件。");
				continue;
			}
			if(1/*!isOverlapped*/) {
				queue digitSeq = makeNumberSeq(serial);
				addedAd.destory();
				addedAd.create((digitSeq.size() + 2) * trackInterval);
				addedAd.channel = numVoice->channel;
				addedAd.sampleRate = numVoice->sampleRate;
				for(int j = 0; j < digitSeq.size(); j++) {
					addedAd.mixWith(numVoice[digitSeq[j]], 1, trackInterval * j);
				}
				OGGvorbis::OGGobject newOo;
				newOo.loadAndEncode(addedAd, addedStream);
				if(addedStream.length) {
					goalNPK.push(sourceNPK.content[i].comment, addedStream);
					addInfo(L"已完成对" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"的打标（编号" + NumToCStr(serial) + L"）。");
					listTXT.WriteString(NumToCStr(serial) + L"-" + StrToCStr(sourceNPK.content[i].comment) + L"\n");
					serial++;
				}
			} 
			pctl->SetPos(i * 1000 / sourceNPK.getCount());
		}
		listTXT.Close();
		goalNPK.saveFile(CStrToStr(sourceFileName.Left(sourceFileName.GetLength() - 4) + L"(标记列表).NPK"));
		addInfo(L"已完成对" + sourceFileName + L"的打标。");
	} else {
		CFileFind fileFind;
		std::vector<CString> fileList;
		BOOL ret = fileFind.FindFile(sourceFolderName);
		while(ret) {
			ret = fileFind.FindNextFile();
			fileList.push_back(fileFind.GetFilePath());
		}
		for(int n = 0; n < fileList.size(); n++) {
			auto sourceName = fileList[n];
			sourceNPK.release();
			if(!sourceNPK.loadFile(CStrToStr(sourceName))) {
				addInfo(L"跳过：文件" + sourceName + L"不能被识别。");
				continue;
			}
			addInfo(L"已读取" + sourceName + L"。");
			goalNPK.create();
			listTXT.Open(sourceName.Left(sourceName.GetLength() - 4) + L"(标记列表).TXT", CFile::modeCreate | CFile::modeWrite);
			for(int i = 0; i < sourceNPK.getCount(); i++) {
				audio addedAd;
				stream addedStream;
				const auto sv = sourceNPK.SNDgetVersion(i);
				if(sv != VMP3 && sv != VVORBIS && sv != VWAVE) {
					addInfo(L"跳过：" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"不是音效文件。");
					continue;
				}
				if(1/*!isOverlapped*/) {
					queue digitSeq = makeNumberSeq(serial);
					addedAd.destory();
					addedAd.create((digitSeq.size() + 2) * trackInterval);
					addedAd.channel = numVoice->channel;
					addedAd.sampleRate = numVoice->sampleRate;
					for(int j = 0; j < digitSeq.size(); j++) {
						addedAd.mixWith(numVoice[digitSeq[j]], 1, trackInterval * j);
					}
					OGGvorbis::OGGobject newOo;
					newOo.loadAndEncode(addedAd, addedStream);
					if(addedStream.length) {
						goalNPK.push(sourceNPK.content[i].comment, addedStream);
						addInfo(L"已完成对" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"的打标（编号" + NumToCStr(serial) + L"）。");
						listTXT.WriteString(NumToCStr(serial) + L"-" + StrToCStr(sourceNPK.content[i].comment) + L"\n");
						serial++;
					}
				}
			}
			listTXT.Close();
			goalNPK.saveFile(CStrToStr(sourceName.Left(sourceName.GetLength() - 4) + L"(标记列表).NPK"));
			addInfo(L"已完成对" + sourceName + L"的打标。");
			pctl->SetPos(n * 1000 / fileList.size());
		}
	}
	pctl->SetPos(1000);
	addInfo(L"所有打标工作已结束。");
	MessageBox(L"标记完毕喵！");
	GET_CTRL(CButton, ID_START)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
}

void ToolAudioMark::OnBnClickedStart() {
	// TODO:  在此添加控件通知处理程序代码
	StartThreadFunc(Marking, nullptr);
}
