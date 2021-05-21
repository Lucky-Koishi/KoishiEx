// ToolDownloadServerSelection.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolDownloadServerSelection.h"
#include "afxdialogex.h"


// ToolDownloadServerSelection 对话框

IMPLEMENT_DYNAMIC(ToolDownloadServerSelection, CDialogEx)

ToolDownloadServerSelection::ToolDownloadServerSelection(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolDownloadServerSelection::IDD, pParent)
{
	loadServerList();
	firstDraw = TRUE;
}

ToolDownloadServerSelection::~ToolDownloadServerSelection()
{
}

void ToolDownloadServerSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolDownloadServerSelection, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ToolDownloadServerSelection 消息处理程序


BOOL ToolDownloadServerSelection::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	quickSetFont(&dataFont, 14, L"宋体", FALSE, FALSE, FALSE);
	initLayout();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ToolDownloadServerSelection::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	for(int i = 0; i < list.size(); i++) {
		for(int j = 0; j < list[i].list.size(); j++) {
			if(rcServer[i][j].PtInRect(point)) {
				serverInfo = list[i].list[j];
				CDialogEx::OnOK();
			}
		}
	}
	if(rcCtrl[0].PtInRect(point)) {
		ProfileBlack profile;
		profile.loadProfile();
		MessageBox(L"修改完后请重启下载器喵！", L"提示喵");
		ShellExecute(NULL, L"open", profile.getDownloadPath() + L"server_url_data.txt", 0, 0, SW_SHOW);
	}
	if(rcCtrl[1].PtInRect(point)) {
		CDialogEx::OnCancel();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void ToolDownloadServerSelection::loadServerList() {
	ProfileBlack profile;
	profile.loadProfile();
	CStdioFile listFile;
	CString listFilePath = profile.getDownloadPath();
	if(!listFile.Open(listFilePath + L"server_url_data.txt", CFile::modeRead)) {
		defaultServerList();
		listFile.Open(listFilePath + L"server_url_data.txt", CFile::modeRead);
	}
	CHS_LOCALE_START;
	CString lineString;
	list.clear();
	SERVER_REGION region;
	SERVER_INFO info;
	BOOL isFirstRegion = TRUE;
	while(listFile.ReadString(lineString)) {
		if(lineString.Left(1) == L"[" && lineString.Right(1) == L"]") {
			if(isFirstRegion) {
				isFirstRegion = FALSE;
			} else {
				list.push_back(region);
				region.list.clear();
			}
			lineString = lineString.Left(lineString.GetLength() - 1);
			lineString = lineString.Right(lineString.GetLength() - 1);
			if(lineString.GetLength() == 0)
				lineString = L"无名称";
			region.region = lineString;
		} else {
			CString nameString, urlString, isTCTstring;
			AfxExtractSubString(nameString, lineString, 0, ',');
			AfxExtractSubString(urlString, lineString, 1, ',');
			AfxExtractSubString(isTCTstring, lineString, 2, ',');
			info.region = region.region;
			info.name = nameString;
			if(urlString.Left(1) == L"\"" && urlString.Right(1) == L"\"") {
				urlString = urlString.Left(urlString.GetLength() - 1);
				urlString = urlString.Right(urlString.GetLength() - 1);
				if(lineString.GetLength() == 0)
					continue;
				info.url = urlString;
			}
			info.isTCT = _ttoi(isTCTstring) == 1;
			region.list.push_back(info);
		}
	}
	list.push_back(region);
	CHS_LOCALE_END;
	listFile.Close();
}
void ToolDownloadServerSelection::defaultServerList() {
	ProfileBlack profile;
	profile.loadProfile();
	CStdioFile listFile;
	CString listFilePath = profile.getDownloadPath();
	listFile.Open(listFilePath + L"server_url_data.txt", CFile::modeWrite | CFile::modeCreate);
	CHS_LOCALE_START;
	listFile.WriteString(L"[中国大陆]\n");
	listFile.WriteString(L"天界,\"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp12.full.tct/\",1\n");
	listFile.WriteString(L"魔界,\"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp56.full.tct/\",1\n");
	listFile.WriteString(L"西海岸1区,\"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp1.full.tct/\",1\n");
	listFile.WriteString(L"西海岸2区,\"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp2.full.tct/\",1\n");
	listFile.WriteString(L"天空之城,\"http://down-update.qq.com/dnf/autopatch/dnf_exp/dnf.exp5.full.tct/\",1\n");
	listFile.WriteString(L"[韩国]\n");
	listFile.WriteString(L"正式服,\"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_hg/\",0\n");
	listFile.WriteString(L"测试服,\"http://d-fighter.dn.nexoncdn.co.kr/samsungdnf/neople/dnf_open/\",0\n");
	listFile.WriteString(L"[日本]\n");
	listFile.WriteString(L"正式服,\"http://webdown2.nexon.co.jp/arad/real/\",0\n");
	listFile.WriteString(L"[北美地区]\n");
	listFile.WriteString(L"正式服,\"http://download.dfoneople.com/Patch/\",0\n");
	CHS_LOCALE_END;
	listFile.Close();
}

void ToolDownloadServerSelection::initLayout() {
	int unit_h = 60;
	int unit_w = 120;
	int width = unit_w * 3;
	int level = 0;
	for(long i = 0; i < list.size();i++) {
		std::vector<CRect> rcTemp;
		rcRegion.push_back(CRect(0, level, width, level + unit_h / 2));
		rcRegionBack.push_back(CRect(0, level + unit_h / 2, width, level + unit_h / 2 + unit_h * (list[i].list.size() + 2) / 3));
		level += unit_h / 2;
		for(long j = 0; j < list[i].list.size(); j++) {
			rcTemp.push_back(CRect(unit_w * (j % 3), level, unit_w * (1 + (j % 3)), level + unit_h));
			if(j % 3 == 2 || j == list[i].list.size() - 1) {
				level += unit_h;
			}
		}
		rcServer.push_back(rcTemp);
	}
	for(long i = 0; i < 2; i++) {
		rcCtrl.push_back(CRect(unit_w * 1.5 * i, level, unit_w * 1.5 * (1 + i), level + unit_h));
	}
	int height = level + unit_h;
	rcFull = CRect(0, 0, width, height);
	SetWindowPos(NULL, 0, 0, width + 16, height + 38, SWP_NOZORDER | SWP_NOMOVE);
}
void ToolDownloadServerSelection::drawLayout() {
	image im(rcFull.Height(), rcFull.Width());
	im.rectangle(point(0, 0), point(im.width - 1, im.height - 1), 0);
	im.rectangle(point(1, 1), point(im.width - 2, im.height - 2), 0);
	color cList[6] = {
		color(0xAA, 0xAA, 0xAA),
		color(0xFF, 0x66, 0x66),
		color(0xFF, 0xCC, 0x66),
		color(0x66, 0xFF, 0x66),
		color(0x33, 0xCC, 0xFF),
		color(0xCC, 0x66, 0xFF)
	};
	for(int i = 0; i < list.size(); i++) {
		addButton(rcRegion[i], im, cList[0]);
		im.filledRectangle(point(
			rcRegionBack[i].left, rcRegionBack[i].top), point(
			rcRegionBack[i].right - 1, rcRegionBack[i].bottom - 1),
			color::getDarken(cList[(i + 1) % 6]));
		for(int j = 0; j < list[i].list.size(); j++) {
			addButton(rcServer[i][j], im, cList[(i + 1) % 6]);
		}
	}
	for(int i = 0; i < 2; i++) {
		addButton(rcCtrl[i], im, color(0x88, 0x88, 0x88));
	}
	CImage img;
	img.Create(im.width, im.height, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for(int i = 0; i<im.width; i++) {
		for(int j = 0; j<im.height; j++) {
			*(pst + pit*j + 4 * i + 0) = im[j][i].B;
			*(pst + pit*j + 4 * i + 1) = im[j][i].G;
			*(pst + pit*j + 4 * i + 2) = im[j][i].R;
		}
	}
	CDC *pDC = GetDC();
	img.Draw(pDC->m_hDC, 0, 0);
	img.Destroy();
	ReleaseDC(pDC);
	for(int i = 0; i < list.size(); i++) {
		drawText(rcRegion[i], list[i].region, &dataFont, 0);
		for(int j = 0; j < list[i].list.size(); j++) {
			drawText(rcServer[i][j], list[i].list[j].name, &dataFont, 0);
		}
	}
	drawText(rcCtrl[0], L"修改URL", &dataFont, 0xffffff);
	drawText(rcCtrl[1], L"退出", &dataFont, 0xffffff);
}

void ToolDownloadServerSelection::addButton(CRect rc, image &im, color btnColor) {
	color btnColorLight = btnColor.getBrighten(btnColor);
	color btnColorDark = btnColor.getDarken(btnColor);
	im.filledRectangle(point(rc.left, rc.top), point(rc.right - 1, rc.bottom - 1), btnColor);
	for(int i = 0; i < 3; i++) {
		im.line(point(rc.left + i, rc.top + i), point(rc.left + i, rc.bottom - i - 1), btnColorLight);
		im.line(point(rc.left + i, rc.top + i), point(rc.right - i - 1, rc.top + i), btnColorLight);
		im.line(point(rc.right - i - 1, rc.top + i), point(rc.right - i - 1, rc.bottom - i - 1), btnColorDark);
		im.line(point(rc.left + i, rc.bottom - i - 1), point(rc.right - i - 1, rc.bottom - i - 1), btnColorDark);
	}
	for(int i = 3; i < 5; i++) {
		im.line(point(rc.left + i, rc.top + i), point(rc.left + i, rc.bottom - i - 1), btnColorDark);
		im.line(point(rc.left + i, rc.top + i), point(rc.right - i - 1, rc.top + i), btnColorDark);
		im.line(point(rc.right - i - 1, rc.top + i), point(rc.right - i - 1, rc.bottom - i - 1), btnColorLight);
		im.line(point(rc.left + i, rc.bottom - i - 1), point(rc.right - i - 1, rc.bottom - i - 1), btnColorLight);
	}
}

void ToolDownloadServerSelection::OnPaint() {
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if(firstDraw) {
		drawLayout();
		firstDraw = FALSE;
	}
	CDialogEx::OnPaint();
}


void ToolDownloadServerSelection::quickSetFont(CFont *ft, int size, CString fontName, BOOL isBold, BOOL isItalic, BOOL isUnderline) {
	ft->CreateFont(
		size,/*cHeight*/0,/*cWidth*/0,/*cEscapement*/0,/*cOrientation*/
		isBold ? FW_BOLD : FW_THIN, /*cWeight*/isItalic,/*bItalic*/isUnderline, /*bUnderline*/0, /*bStrikeOut*/
		DEFAULT_CHARSET,/*iCharSet*/OUT_CHARACTER_PRECIS, /*iOutPrecision*/CLIP_CHARACTER_PRECIS, /*iClipPrecision*/
		DEFAULT_QUALITY, /*iQuality*/FF_MODERN, /*iPitchAndFamily*/fontName);
}

void ToolDownloadServerSelection::drawText(CRect rc, CString myString, CFont *ft, COLORREF fontColor) {
	CClientDC dc(this);
	oldFont = dc.SelectObject(ft);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(fontColor);
	dc.DrawText(myString, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dc.SelectObject(oldFont);
}