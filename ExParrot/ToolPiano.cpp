// ToolPiano.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ToolPiano.h"
#include "afxdialogex.h"
#include "TinySNDSelect.h"
#include "TinyNoteBar.h"
#include <thread>

// ToolPiano 对话框
IMPLEMENT_DYNAMIC(ToolPiano, CDialogEx)

ToolPiano::ToolPiano(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolPiano::IDD, pParent)
{
	graphicMode = FALSE;
	offsetLine = 0;
}

ToolPiano::~ToolPiano()
{
}

void ToolPiano::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolPiano, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ToolPiano::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ToolPiano::OnBnClickedButton2)
	ON_BN_CLICKED(IDPLAY, &ToolPiano::OnBnClickedPlay)
	ON_BN_CLICKED(IDSAVE, &ToolPiano::OnBnClickedSave)
	ON_BN_CLICKED(IDCANCEL, &ToolPiano::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON3, &ToolPiano::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ToolPiano::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &ToolPiano::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &ToolPiano::OnBnClickedButton6)
	ON_BN_CLICKED(IDSTOP, &ToolPiano::OnBnClickedStop)
END_MESSAGE_MAP()


// ToolPiano 消息处理程序
BOOL ToolPiano::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	GET_CTRL(CEdit, IDC_EDIT_FILENAME)->SetWindowText(L"请选择一个音效");
	GET_CTRL(CEdit, IDC_EDIT_ADJUST1)->SetWindowText(L"基音频率偏移");
	GET_CTRL(CEdit, IDC_EDIT_ADJUST2)->SetWindowText(L"1");
	GET_CTRL(CEdit, IDC_EDIT_INTERVAL1)->SetWindowText(L"速度调节");
	GET_CTRL(CEdit, IDC_EDIT_INTERVAL2)->SetWindowText(L"1");

	GET_CTRL(CStatic, IDC_STATIC_PIANO_FRAME)->GetWindowRect(&rcBoard);
	ScreenToClient(&rcBoard);
	GET_CTRL(CStatic, IDC_STATIC_PIANO_FRAME)->ShowWindow(SW_HIDE);

	GET_CTRL(CEdit, IDC_EDIT_NOTES)->GetWindowRect(&rcStaff);
	ScreenToClient(&rcStaff);
	playing = FALSE;

	CREATEW(bar, IDD_TINY_PROGRESSBAR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ToolPiano::OnBnClickedButton1() {
	// TODO:  在此添加控件通知处理程序代码
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("所有支持的文件(*.NPK,*.WAV,*.OGG)|*.NPK;*.WAV;*.OGG|音效文件(*.WAV,*.OGG)|*.WAV;*.OGG|NPK文件(*.NPK)|*.NPK|vorbis音效(*.OGG)|*.OGG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		stream auStream;
		CString fileName = dlg.GetPathName();
		CString fmt = fileName.Right(4).MakeUpper();
		if(fmt == L".NPK") {
			NPKobject no;
			if(!no.loadFile(CStrToStr(fileName))) {
				MessageBox(L"不识别的NPK喵。", L"提示喵");
				return;
			}
			if(no.count == 0) {
				MessageBox(L"指定NPK里无内容喵。", L"提示喵");
				return;
			}
			TinySNDSelect dlg2;
			dlg2.listStr.clear();
			dlg2.defaultSelected = 0;
			for(int i = 0; i < no.count; i++)
				dlg2.listStr.push_back(no.entry[i].comment);
			if(IDOK != dlg2.DoModal()) {
				return;
			}
			if(!no.extract(dlg2.selected, auStream)) {
				MessageBox(L"无法提取的对象喵。", L"提示喵");
				return;
			}
			GET_CTRL(CEdit, IDC_EDIT_FILENAME)->SetWindowText(StrToCStr(no.entry[dlg2.selected].comment));
		} else if(fmt == L".WAV" ||fmt == L".OGG"){
			if(!auStream.loadFile(CStrToStr(fileName))) {
				MessageBox(L"无法读取的文件喵。", L"提示喵");
				return;
			}
			GET_CTRL(CEdit, IDC_EDIT_FILENAME)->SetWindowText(fileName);
		}
		NPKobject noTemp;
		noTemp.create();
		noTemp.push(auStream, "temp");
		bar.show();
		bar.setInfo(L"正在解码喵……", 0);
		switch(noTemp.SNDgetVersion(0)) {
		case VVORBIS:
			{
				KoishiAudioTool::OGGvorbis::OGGobject oo;
				if(oo.decodeAndMake(auStream, originNote)) {
					if(originNote.length > 0)
						StartThreadFunc(playNotes, 1);
				} else {
					MessageBox(L"这个OGG文件解码失败喵。", L"提示喵");
				}
			}
			break;
		case VWAVE:
			{
				KoishiAudioTool::WAV::WAVobject wo;
				if(wo.decodeAndMake(auStream, originNote)) {
					if(originNote.length > 0)
						StartThreadFunc(playNotes, 1);
				} else {
					MessageBox(L"这个WAV文件解码失败喵。", L"提示喵");
				}
			}
			break;
		}
		bar.hide();
	}
}


void ToolPiano::OnBnClickedButton2() {
	// TODO:  在此添加控件通知处理程序代码
	if(originNote.length == 0)
		MessageBox(L"当前没有音频喵。", L"提示喵");
	if(originNote.length > 0)
		StartThreadFunc(playNotes, 1);
		//player.play(originNote);
}

DefineThreadFunc(ToolPiano, playNotes, double) {
	audio currentNote;
	CString rateStr;
	GET_CTRL(CEdit, IDC_EDIT_ADJUST2)->GetWindowText(rateStr);
	double rate2 = _ttof(rateStr);
	originNote.adjustPitch(currentNote, para * rate2);
	if(currentNote.length > 0)
		player.play(currentNote);
}
void ToolPiano::drawBoards(int clicked) {
	int width = rcBoard.Width();
	int height = rcBoard.Height();
	image imBoard(height, width);
	int whiteKeyCount = 14;
	int whiteKeyBound[15] = {0};
	int blackKeyHeight = height / 2;
	int blackKeyBound[25] = {0};
	for(int i = 0; i < 15; i++) {
		whiteKeyBound[i] = i * width / 14;
	}
	int keyInterval[24] = {
		0, 3, 5, 7, 9, 12, 15, 17, 19, 21, 24, 27, 29, 31, 33, 35, 37, 40, 43, 45, 47, 49, 52, 56
	};
	int whiteKeyID[14] = {
		0, 2, 4, 5, 7, 9, 10, 12, 14, 16, 17, 19, 21, 22
	};
	int blackKeyID[9] = {
		1, 3, 6, 8, 11, 13, 15, 18, 20
	};
	for(int i = 0; i < 25; i++) {
		blackKeyBound[i] = keyInterval[i] * width / 56;
	}
	imBoard.fill(color(0xFF, 0xFF, 0xFF));
	imBoard.rectangle(point(0, 0), point(width - 1, height - 1), color(0, 0, 0));
	for(int i = 1; i < 14; i++) {
		imBoard.line(point(whiteKeyBound[i], 0), point(whiteKeyBound[i], height - 1), color(0, 0, 0));
	}
	for(int i = 0; i < 14; i++) {
		if(whiteKeyID[i] == clicked) {
			imBoard.filledRectangle(point(whiteKeyBound[i] + 1, 1), point(whiteKeyBound[i + 1] - 1, height - 2), color(0xFF, 0x7F, 0x7F));
		}
	}
	for(int i = 0; i < 9; i++) {
		color clr(0, 0, 0);
		if(clicked == blackKeyID[i])
			clr = color(0xFF, 0x7F, 0x7F);
		imBoard.filledRectangle(point(blackKeyBound[blackKeyID[i]], 0), point(blackKeyBound[blackKeyID[i] + 1], blackKeyHeight), clr);
	}
	CImage img;
	img.Create(width, height, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(int i = 0; i<width; i++) {
		for(int j = 0; j<height; j++) {
			*(pst + pit*j + 4 * i + 0) = imBoard[j][i].B;
			*(pst + pit*j + 4 * i + 1) = imBoard[j][i].G;
			*(pst + pit*j + 4 * i + 2) = imBoard[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC, rcBoard.left, rcBoard.top);
	img.Destroy();
	ReleaseDC(pDC);
}

void ToolPiano::drawStaff(int lineCount, int barPerLine, int offset) {
	int width = rcStaff.Width();
	int height = rcStaff.Height();
	image imStaff(height, width);
	//滚动条部分
	image btnTriangle1(size(7, 4));
	image btnTriangle2(size(7, 4));
	for(int i = 0; i < 4; i++) {
		btnTriangle2.line(point(i, i), point(6 - i, i), color(0xFF, 0xFF, 0xFF));
		btnTriangle1.line(point(3 - i, i), point(3 + i, i), color(0xFF, 0xFF, 0xFF));
	}
	imStaff.filledRectangle(point(width - 20, 0), point(width, height), color(0X77, 0X77, 0X77));
	int btnBaseX = width - 20;
	int btnBaseY[6] = {0, 20, 40, height - 60, height - 40, height - 20};
	for(int i = 0; i < 6; i++) {
		imStaff.rectangle(point(btnBaseX, btnBaseY[i]), point(btnBaseX + 19, btnBaseY[i] + 19), color(0, 0, 0));
		imStaff.line(point(btnBaseX + 1, btnBaseY[i] + 1), point(btnBaseX + 18, btnBaseY[i] + 1), color(0xFF, 0xFF, 0xFF));
		imStaff.line(point(btnBaseX + 1, btnBaseY[i] + 1), point(btnBaseX + 1, btnBaseY[i] + 18), color(0xFF, 0xFF, 0xFF));
		imStaff.line(point(btnBaseX + 18, btnBaseY[i] + 1), point(btnBaseX + 18, btnBaseY[i] + 18), color(0x44, 0x44, 0x44));
		imStaff.line(point(btnBaseX + 1, btnBaseY[i] + 18), point(btnBaseX + 18, btnBaseY[i] + 18), color(0x44, 0x44, 0x44));
		switch(i) {
		case 0:
			imStaff.putFore(btnTriangle1, LAY, point(btnBaseX + 7, btnBaseY[i] + 8));
			imStaff.rectangle(point(btnBaseX + 7, btnBaseY[i] + 6), point(btnBaseX + 13, btnBaseY[i] + 7), color(0xFF, 0xFF, 0xFF));
			break;
		case 1:
			imStaff.putFore(btnTriangle1, LAY, point(btnBaseX + 7, btnBaseY[i] + 10));
			imStaff.putFore(btnTriangle1, LAY, point(btnBaseX + 7, btnBaseY[i] + 6));
			break;
		case 2:
			imStaff.putFore(btnTriangle1, LAY, point(btnBaseX + 7, btnBaseY[i] + 8));
			break;
		case 3:
			imStaff.putFore(btnTriangle2, LAY, point(btnBaseX + 7, btnBaseY[i] + 8));
			break;
		case 4:
			imStaff.putFore(btnTriangle2, LAY, point(btnBaseX + 7, btnBaseY[i] + 10));
			imStaff.putFore(btnTriangle2, LAY, point(btnBaseX + 7, btnBaseY[i] + 6));
			break;
		case 5:
			imStaff.putFore(btnTriangle2, LAY, point(btnBaseX + 7, btnBaseY[i] + 8));
			imStaff.rectangle(point(btnBaseX + 7, btnBaseY[i] + 13), point(btnBaseX + 13, btnBaseY[i] + 14), color(0xFF, 0xFF, 0xFF));

			break;
		}
	}
	//滚动条滑块当前位置
	if(staff.size() > 0){
		int startPos = offset * barPerLine;
		int lastPos = startPos + lineCount*barPerLine;
		if(lastPos >= staff.size())
			lastPos = staff.size();
		if(lastPos >= startPos) {
			int minY = 60;	//60为滚动条开始地方
			int maxY = height - 61;//为滚动条结束地方
			int len = maxY - minY;
			imStaff.filledRectangle(
				point(btnBaseX, minY + startPos * len / staff.size()),
				point(btnBaseX + 19, minY + lastPos * len /staff.size()),
				color(0xff, 0x77, 0x77)
			);
		}
	}
	width -= 20;//20是滚动条宽度
	int firstBar = offset * barPerLine;
	for(int i = 0; i < lineCount*barPerLine; i++) {
		if(firstBar + i > staff.size())
			break;
		int baseX = (i % barPerLine) * width / barPerLine;
		int baseWidth = ((i % barPerLine) + 1)* width / barPerLine - baseX;
		int baseY = (i / barPerLine) * height / lineCount;
		int baseHeight= ((i / barPerLine) + 1)* height / lineCount - baseY;
		image imBar;
		if(firstBar + i == staff.size()) {
			imBar.create(size(baseWidth, baseHeight));
			imBar.fill(color(0x66, 0x66, 0x66));
			imBar.line(point(0, 0), point(baseWidth - 1, 0), color(0x99, 0x99, 0x99));
			imBar.line(point(0, 0), point(0, baseHeight - 1), color(0x99, 0x99, 0x99));
			imBar.line(point(1, 1), point(baseWidth - 2, 1), color(0x99, 0x99, 0x99));
			imBar.line(point(1, 1), point(1, baseHeight - 2), color(0x99, 0x99, 0x99));
			imBar.line(point(baseWidth - 1, 0), point(baseWidth - 1, baseHeight - 1), color(0x33, 0x33, 0x33));
			imBar.line(point(0, baseHeight - 1), point(baseWidth - 1, baseHeight - 1), color(0x33, 0x33, 0x33));
			imBar.line(point(baseWidth - 2, 1), point(baseWidth - 2, baseHeight - 2), color(0x33, 0x33, 0x33));
			imBar.line(point(1, baseHeight - 2), point(baseWidth - 2, baseHeight - 2), color(0x33, 0x33, 0x33));
			image imAdd(size(11, 11));
			imAdd.filledRectangle(point(0, 4), point(10, 6), color(0xFF, 0xFF, 0xFF));
			imAdd.filledRectangle(point(4, 0), point(6, 10), color(0xFF, 0xFF, 0xFF));
			imBar.putFore(imAdd, LAY, point(baseWidth / 2 - 5, baseHeight / 2 - 5));
		} else {
			NoteBar &nb = staff[firstBar + i];
			nb.makeImage(imBar, size(baseWidth, baseHeight));
		}
		imStaff.putFore(imBar, LAY, point(baseX, baseY));
	}
	width += 20;
	CImage img;
	img.Create(width, height, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(int i = 0; i<width; i++) {
		for(int j = 0; j<height; j++) {
			*(pst + pit*j + 4 * i + 0) = imStaff[j][i].B;
			*(pst + pit*j + 4 * i + 1) = imStaff[j][i].G;
			*(pst + pit*j + 4 * i + 2) = imStaff[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC, rcStaff.left, rcStaff.top);
	img.Destroy();
	ReleaseDC(pDC);
}

void ToolPiano::OnBnClickedPlay() {
	// TODO:  在此添加控件通知处理程序代码
	if(originNote.length == 0) {
		MessageBox(L"当前没有音频喵。", L"提示喵");
		return;
	}
	StartThreadFunc(punchPlay, 0);
}


void ToolPiano::OnBnClickedSave() {
	// TODO:  在此添加控件通知处理程序代码
	if(originNote.length == 0) {
		MessageBox(L"当前没有音频喵。", L"提示喵");
		return;
	}
	StartThreadFunc(punchSave, 0);
}


void ToolPiano::OnBnClickedCancel() {
	// TODO:  在此添加控件通知处理程序代码
	player.stop();
	Sleep(5);
	CDialogEx::OnCancel();
}

void ToolPiano::staffFromText() {
	CString musStr, noteStr;
	GET_CTRL(CEdit, IDC_EDIT_NOTES)->GetWindowText(musStr);
	staff.clear();
	int i = 1;
	while(AfxExtractSubString(noteStr, musStr, i++, '[')) {
		noteStr = noteStr.Left(noteStr.GetLength() - 1);	//去掉"]"
		staff.push_back(NoteBar(noteStr));
	}
}
void ToolPiano::showStaffText() {
	CString musStr;
	int i = 0;
	for(NoteBar nb : staff) {
		musStr += L"[";
		musStr += nb.toString();
		musStr += L"]";
		if((i++ % 4) == 3)
			musStr += L"\r\n";
	}
	GET_CTRL(CEdit, IDC_EDIT_NOTES)->SetWindowText(musStr);
}
DefineThreadFunc(ToolPiano, punchSave, int) {
	CString defExt = _T("Ogg音效(*.ogg)|*.ogg|波形声音(*.wav)|*.wav");
	CString extFilter = _T("Ogg音效(*.ogg)|*.ogg|波形声音(*.wav)|*.wav||");
	CFileDialog dlg(false, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() != IDOK)
		return;
	CString fileName = dlg.GetPathName();
	if(!graphicMode) {
		staffFromText();
	}
	CString fileExt = dlg.GetFileExt().MakeUpper();
	makeTrack();
	if(fileExt == L".WAV") {
		KoishiAudioTool::WAV::WAVobject wo;
		if(!wo.loadAndEncodeToFile(track, CStrToStr(fileName))) {
			MessageBox(L"无法将其转换为WAV喵！", L"提示喵");
		}
	} else {
		KoishiAudioTool::OGGvorbis::OGGobject oo;
		Profile profile;
		profile.loadProfile();
		oo.comment.addInfo_author(CStrToStr(profile.artist), CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S")));
		if(!oo.loadAndEncodeToFile(track, CStrToStr(fileName))) {
			MessageBox(L"编码错误喵！\r\n" + StrToCStr(oo.errorMessage), L"提示喵");
		}
	}
}
DefineThreadFunc(ToolPiano, punchPlay, int) {
	if(!graphicMode) {
		staffFromText();
	}
	makeTrack();
	player.stop();
	player.play(track);
}
void ToolPiano::makeTrack() {
	int interval = originNote.sampleRate;
	double speed = 0.f;
	CString spdStr;
	GET_CTRL(CEdit, IDC_EDIT_INTERVAL2)->GetWindowText(spdStr);
	speed = _ttof(spdStr);
	interval /= speed;
	std::vector<NoteInfo> niList;
	for(int i = 0; i < staff.size(); i++) {
		std::vector<NoteInfo> nil = staff[i].serial();
		for(NoteInfo ni : nil) {
			if(ni.note.base == 0)
				continue;
			ni.pos += i;
			niList.push_back(ni);
		}
	}
	track.destory();
	track.create((staff.size() + 4) * interval + originNote.length);
	track.channel = originNote.channel;
	track.sampleRate = originNote.sampleRate;
	bar.setInfo(L"正在作曲喵……", niList.size());
	bar.show();
	for(int i = 0; i < niList.size(); i++) {
		bar.setInfo(L"正在作曲喵……", i);
		audio currentNote;
		if(niList[i].rate == 0)
			continue;
		originNote.adjustPitch(currentNote, niList[i].rate);
		track.mixWith(currentNote, 1.f, interval * niList[i].pos);
	}
	bar.hide();
}
int ToolPiano::getBoardHit(const point &pt) {
	int width = rcBoard.Width();
	int height = rcBoard.Height();
	int whiteKeyCount = 14;
	int whiteKeyBound[15] = {0};
	int blackKeyHeight = height / 2;
	int blackKeyBound[25] = {0};
	for(int i = 0; i < 15; i++) {
		whiteKeyBound[i] = i * width / 14;
	}
	int keyInterval[24] = {
		0, 3, 5, 7, 9, 12, 15, 17, 19, 21, 24, 27, 29, 31, 33, 35, 37, 40, 43, 45, 47, 49, 52, 56
	};
	int whiteKeyID[14] = {
		0, 2, 4, 5, 7, 9, 10, 12, 14, 16, 17, 19, 21, 22
	};
	int blackKeyID[9] = {
		1, 3, 6, 8, 11, 13, 15, 18, 20
	};
	for(int i = 0; i < 25; i++) {
		blackKeyBound[i] = keyInterval[i] * width / 56;
	}
	if(pt.Y > blackKeyHeight) {
		//hit white keys
		for(int i = 0; i < 14; i++) {
			if(pt.X >= whiteKeyBound[i] && pt.X < whiteKeyBound[i + 1]) {
				return whiteKeyID[i];
			}
		}
	} else {
		//hit black or white keys
		for(int i = 0; i < 24; i++) {
			if(pt.X >= blackKeyBound[i] && pt.X < blackKeyBound[i + 1]) {
				return i;
			}
		}
	}
	return -1;
}

int ToolPiano::getClickedBar(const point &pt, int lineCount, int barPerLine, int offset) {
	int width = rcStaff.Width() - 20;
	int height = rcStaff.Height();
	int bx = pt.X * barPerLine / width;
	int by = pt.Y * lineCount / height;
	if(pt.X >= width) {
		if(pt.Y < 20) {
			return -1;
		}
		if(pt.Y < 40) {
			return -2;
		}
		if(pt.Y < 60) {
			return -3;
		}
		if(pt.Y > height - 20) {
			return -6;
		}
		if(pt.Y > height - 40) {
			return -5;
		}
		if(pt.Y > height - 60) {
			return -4;
		}
		return -7;
	}
	int barPos = (offset + by) * barPerLine + bx;
	return barPos;
}

void ToolPiano::OnLButtonDown(UINT nFlags, CPoint pt) {
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CPoint myPoint;
	GetCursorPos(&myPoint);
	ScreenToClient(&myPoint);
	if(rcBoard.PtInRect(myPoint)) {
		point xy(myPoint.x - rcBoard.left, myPoint.y - rcBoard.top);
		int hit = getBoardHit(xy);
		if(hit != -1) {
			drawBoards(hit);
			Note n[23] = {
				Note(5, 0, -1), Note(5, 1, -1), Note(6, 0, -1), Note(6, 1, -1), Note(7, 0, -1),
				Note(1, 0, 0), Note(1, 1, 0), Note(2, 0, 0), Note(2, 1, 0), Note(3, 0, 0),
				Note(4, 0, 0), Note(4, 1, 0), Note(5, 0, 0), Note(5, 1, 0), Note(6, 0, 0),
				Note(6, 1, 0), Note(7, 0, 0), Note(1, 0, 1), Note(1, 1, 1), Note(2, 0, 1),
				Note(2, 1, 1), Note(3, 0, 1), Note(4, 0, 1)
			};
			StartThreadFunc(playNotes, n[hit].rate());
		}
	} else if(rcStaff.PtInRect(myPoint) && graphicMode) {
		point xy(myPoint.x - rcStaff.left, myPoint.y - rcStaff.top);
		int hit = getClickedBar(xy, 8, 4, offsetLine);
		if(hit >= 0 && hit < staff.size()) {
			TinyNoteBar dlg;
			dlg.content = staff[hit];
			if(IDOK == dlg.DoModal()) {
				staff[hit] = dlg.content;
				drawStaff(8, 4, offsetLine);
			}
		} else if(hit == staff.size()) {
			TinyNoteBar dlg;
			dlg.content = NoteBar(Note(0));
			if(IDOK == dlg.DoModal()) {
				staff.push_back(dlg.content);
				drawStaff(8, 4, offsetLine);
			}
		} else if(hit <= -1 && hit >= -6){
			switch(hit) {
			case -1:
				offsetLine = 0;
				break;
			case -2:
				offsetLine -= 8;
				break;
			case -3:
				offsetLine --;
				break;
			case -4:
				offsetLine ++;
				break;
			case -5:
				offsetLine += 8;
				break;
			case -6:
				offsetLine = staff.size() / 4;
				break;
			}
			if(offsetLine < 0)
				offsetLine = 0;
			if(offsetLine > staff.size() / 4)
				offsetLine = staff.size() / 4;
			drawStaff(8, 4, offsetLine);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, pt);
}


void ToolPiano::OnPaint() {
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	drawBoards(-1);
}


void ToolPiano::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnLButtonUp(nFlags, point);
	drawBoards(-1);
}


void ToolPiano::OnOK() {
}


void ToolPiano::OnBnClickedButton3() {
	// TODO:  文字模式
	if(!graphicMode)
		return;
	graphicMode = FALSE;
	GET_CTRL(CEdit, IDC_EDIT_NOTES)->ShowWindow(SW_SHOW);
	showStaffText();
}


void ToolPiano::OnBnClickedButton4() {
	// TODO:  图形模式
	if(graphicMode)
		return;
	graphicMode = TRUE;
	GET_CTRL(CEdit, IDC_EDIT_NOTES)->ShowWindow(SW_HIDE);
	staffFromText();
	drawStaff(8, 4, offsetLine);
}


void ToolPiano::OnBnClickedButton5() {
	CString defExt = L"文本文档(*.TXT)|*.TXT";
	CString extFilter = defExt + L"||";
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() != IDOK)
		return;
	CString fileName = dlg.GetPathName();
	CString fmt = fileName.Right(4).MakeUpper();
	if(fmt == L".TXT") {
		CString totalStr,mStr;
		GET_CTRL(CEdit, IDC_EDIT_NOTES)->GetWindowText(mStr);
		CStdioFile file;
		file.Open(fileName, CFile::modeRead);
		CHS_LOCALE_START;
		while(file.ReadString(mStr)) {
			totalStr += mStr;
		}
		CHS_LOCALE_END;
		file.Close();
		GET_CTRL(CEdit, IDC_EDIT_NOTES)->SetWindowText(totalStr);
		if(graphicMode) {
			staffFromText();
			drawStaff(8, 4, offsetLine);
		}
	}
}


void ToolPiano::OnBnClickedButton6() {
	CString defExt = L"文本文档(*.TXT)|*.TXT";
	CString extFilter = defExt + L"||";
	CFileDialog dlg(false, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() != IDOK)
		return;
	CString fileName = dlg.GetPathName();
	CString fmt = fileName.Right(4).MakeUpper();
	if(fmt == L".TXT") {
		CString mStr;
		if(graphicMode) {
			showStaffText();
		}
		GET_CTRL(CEdit, IDC_EDIT_NOTES)->GetWindowText(mStr);
		CStdioFile file;
		file.Open(fileName, CFile::modeCreate | CFile::modeReadWrite);
		CHS_LOCALE_START;
		file.WriteString(mStr);
		CHS_LOCALE_END;
		file.Close();
		return;
	}
}


void ToolPiano::OnBnClickedStop() {
	// TODO:  在此添加控件通知处理程序代码
	player.stop();
}
