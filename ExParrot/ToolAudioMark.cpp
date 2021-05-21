// ToolAudioMark.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ToolAudioMark.h"
#include "afxdialogex.h"
#include <thread>

// ToolAudioMark �Ի���

IMPLEMENT_DYNAMIC(ToolAudioMark, CDialogEx)

ToolAudioMark::ToolAudioMark(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolAudioMark::IDD, pParent)
{
	interval = 300;
	beginID = 0;
	digitCount = 3;
	ProfileWhite profile;
	profile.loadProfile();
	reporter.loadFile(CStrToStr(profile.getSupportPath() + L"�������.NPK"));
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


// ToolAudioMark ��Ϣ�������


BOOL ToolAudioMark::OnInitDialog() {
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT_REPORT1)->SetWindowText(L"������");
	GET_CTRL(CEdit, IDC_EDIT_REPORT2)->SetWindowText(L"�������(ms)");
	GET_CTRL(CEdit, IDC_EDIT_REPORTA)->SetWindowText(L"�������.NPK");
	GET_CTRL(CEdit, IDC_EDIT_REPORTB)->SetWindowText(L"300");
	GET_CTRL(CEdit, IDC_EDIT_NUMBER1)->SetWindowText(L"��ʼ��Ǻ���");
	GET_CTRL(CEdit, IDC_EDIT_NUMBER2)->SetWindowText(L"����λ��");
	GET_CTRL(CEdit, IDC_EDIT_NUMBERA)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_NUMBERB)->SetWindowText(L"3");
	GET_CTRL(CButton, IDC_RADIO1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ToolAudioMark::OnBnClickedRadio1() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_RADIO1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_RADIO2)->SetCheck(FALSE);
	isOverlapped = FALSE;
}


void ToolAudioMark::OnBnClickedRadio2() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_RADIO1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_RADIO2)->SetCheck(TRUE);
	isOverlapped = TRUE;
}


void ToolAudioMark::OnBnClickedCheckMark1() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(TRUE);
	GET_CTRL(CButton, IDC_CHECK_MARK2)->SetCheck(FALSE);
	useFolder = FALSE;
}


void ToolAudioMark::OnBnClickedCheckMark2() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(FALSE);
	GET_CTRL(CButton, IDC_CHECK_MARK2)->SetCheck(TRUE);
	useFolder = TRUE;
}


void ToolAudioMark::OnBnClickedButtonReportSeartch() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		GET_CTRL(CEdit, IDC_EDIT_REPORTA)->SetWindowText(dlg.GetPathName());
		if(reporter.getCount() > 0)
			reporter.release();
		if(!reporter.loadFile(CStrToStr(dlg.GetPathName()))) {
			MessageBox(L"�޷�ʶ���NPK�ļ����뻻һ����������������");
		}
		if(reporter.getCount() < 10) {
			MessageBox(L"NPK�ڵ����������㣬�����µ�������������");
		}
	}
}


void ToolAudioMark::OnBnClickedButtonReportListen() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	StartThreadFunc(TryPlay, nullptr);
}


void ToolAudioMark::OnBnClickedButtonMarka() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString folderName;
	CALL_FOLDER_DIALOG(folderName, L"ѡ���ļ�����", L"��ʾ��", L"��������Ч���ļ�������");
	if(folderName.GetLength()) {
		folderName += L"\\*.NPK";
		GET_CTRL(CEdit, IDC_EDIT_MARKB)->SetWindowText(folderName);
		sourceFolderName = folderName;
		GET_CTRL(CButton, IDC_CHECK_MARK1)->SetCheck(FALSE);
		GET_CTRL(CButton, IDC_CHECK_MARK2)->SetCheck(TRUE);
		useFolder = TRUE;
	} else {
		MessageBox(L"��������Ч���ļ�������");
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
	addInfo(L"׼����ʼ��깤����");
	addInfo(L"���ڵ�����������");
	if(reporter.getCount() < 10) {
		addInfo(L"����ֹͣ����������Ŀ���㣨��10������ǰΪ" + NumToCStr(reporter.getCount()));
		return;
	}
	audio numVoice[10];
	for(int i = 0; i < 10; i++) {
		const auto sv = reporter.SNDgetVersion(i);
		if(sv != VWAVE && sv != VVORBIS) {
			addInfo(L"����ֹͣ���������е�" + NumToCStr(i + 1) + L"�������ʽ����֧�֡�");
			return;
		}
		stream aStream;
		reporter.extract(i, aStream);
		if(sv == VWAVE) {
			WAV::WAVobject wo;
			if(!wo.decodeAndMake(aStream, numVoice[i])) {
				addInfo(L"����ֹͣ���������е�" + NumToCStr(i + 1) + L"����Ч����ʧ�ܡ�");
				return;
			}
		} else {
			OGGvorbis::OGGobject oo;
			if(!oo.decodeAndMake(aStream, numVoice[i])) {
				addInfo(L"����ֹͣ���������е�" + NumToCStr(i + 1) + L"����Ч����ʧ�ܡ�");
				return;
			}
		}
		addInfo(L"�ѵ�����Ч��Ϊ����" + NumToCStr(i) + L"����ʾ��");
		pctl->SetPos(100 * i);
	}
	addInfo(L"������������ϡ�");
	int trackInterval = interval * numVoice->sampleRate / 1000;
	pctl->SetPos(0);
	NPKobject sourceNPK, goalNPK;
	CStdioFile listTXT;
	int serial = beginID;
	if(!useFolder) {
		if(!sourceNPK.loadFile(CStrToStr(sourceFileName))) {
			addInfo(L"����ֹͣ���ļ�" + sourceFileName + L"���ܱ�ʶ��");
			return;
		}
		addInfo(L"�Ѷ�ȡ" + sourceFileName + L"��");
		goalNPK.create();
		listTXT.Open(sourceFileName.Left(sourceFileName.GetLength() - 4) + L"(����б�).TXT", CFile::modeCreate | CFile::modeWrite);
		for(int i = 0; i < sourceNPK.getCount(); i++) {
			audio addedAd;
			stream addedStream;
			const auto sv = sourceNPK.SNDgetVersion(i);
			if(sv != VMP3 && sv != VVORBIS && sv != VWAVE) {
				addInfo(L"������" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"������Ч�ļ���");
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
					addInfo(L"����ɶ�" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"�Ĵ�꣨���" + NumToCStr(serial) + L"����");
					listTXT.WriteString(NumToCStr(serial) + L"-" + StrToCStr(sourceNPK.content[i].comment) + L"\n");
					serial++;
				}
			} 
			pctl->SetPos(i * 1000 / sourceNPK.getCount());
		}
		listTXT.Close();
		goalNPK.saveFile(CStrToStr(sourceFileName.Left(sourceFileName.GetLength() - 4) + L"(����б�).NPK"));
		addInfo(L"����ɶ�" + sourceFileName + L"�Ĵ�ꡣ");
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
				addInfo(L"�������ļ�" + sourceName + L"���ܱ�ʶ��");
				continue;
			}
			addInfo(L"�Ѷ�ȡ" + sourceName + L"��");
			goalNPK.create();
			listTXT.Open(sourceName.Left(sourceName.GetLength() - 4) + L"(����б�).TXT", CFile::modeCreate | CFile::modeWrite);
			for(int i = 0; i < sourceNPK.getCount(); i++) {
				audio addedAd;
				stream addedStream;
				const auto sv = sourceNPK.SNDgetVersion(i);
				if(sv != VMP3 && sv != VVORBIS && sv != VWAVE) {
					addInfo(L"������" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"������Ч�ļ���");
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
						addInfo(L"����ɶ�" + GetTail(StrToCStr(sourceNPK.content[i].comment)) + L"�Ĵ�꣨���" + NumToCStr(serial) + L"����");
						listTXT.WriteString(NumToCStr(serial) + L"-" + StrToCStr(sourceNPK.content[i].comment) + L"\n");
						serial++;
					}
				}
			}
			listTXT.Close();
			goalNPK.saveFile(CStrToStr(sourceName.Left(sourceName.GetLength() - 4) + L"(����б�).NPK"));
			addInfo(L"����ɶ�" + sourceName + L"�Ĵ�ꡣ");
			pctl->SetPos(n * 1000 / fileList.size());
		}
	}
	pctl->SetPos(1000);
	addInfo(L"���д�깤���ѽ�����");
	MessageBox(L"����������");
	GET_CTRL(CButton, ID_START)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
}

void ToolAudioMark::OnBnClickedStart() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	StartThreadFunc(Marking, nullptr);
}
