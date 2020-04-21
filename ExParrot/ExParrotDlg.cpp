
// ExParrotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ExParrotDlg.h"
#include "afxdialogex.h"
#include "TinyAdjustVolume.h"
#include "TinyStretch.h"
#include "TinyEcho.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef DEBUG
#define UGLY			0
#define trace(x)		TRACE(L##x)
#else
#define UGLY 1
#define trace(x)
#endif

// CExParrotDlg 对话框




CExParrotDlg::CExParrotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExParrotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAIN);
	profile.loadProfile();
	width = 1210;
	height = 650;
	saveAlert = false;
	recording = false;
	crtSNDid = 0;
	fndSNDid = 0;
	leftBound = 0;
	rightBound = 0;
	dispLeftBound = 0;
	dispRightBound = 441000;		//显示的边界就默认10秒（默认采样频率44100Hz)
	zoomBound1 = 0;
	zoomBound2 = 0;
	processing = 0;
	sizing = 0;
	for(int i = 0;i<16;i++)
		power[i] = 0;								//功率谱
	cur[0] = cur[1] = 0;	
	canvasOperatePara.canvasOperating = false;
	canvasOperatePara.canvasOperation = CANVAS_SELECT;
	canvasOperatePara.firstPos = 0;
}

void CExParrotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExParrotDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TOOL_BUTTON1, &CExParrotDlg::OnBnClickedToolButton1)
	ON_BN_CLICKED(IDC_BUTTON_MENU, &CExParrotDlg::OnBnClickedButtonMenu)
	ON_BN_CLICKED(IDC_BUTTON_MENU2, &CExParrotDlg::OnBnClickedButtonMenu2)
	ON_BN_CLICKED(IDC_BUTTON_MENU3, &CExParrotDlg::OnBnClickedButtonMenu3)
	ON_COMMAND(IDM_MAIN_01, &CExParrotDlg::OnMain01)
	ON_COMMAND(IDM_MAIN_02, &CExParrotDlg::OnMain02)
	ON_COMMAND(IDM_MAIN_03, &CExParrotDlg::OnMain03)
	ON_COMMAND(IDM_MAIN_04, &CExParrotDlg::OnMain04)
	ON_COMMAND(IDM_MAIN_05, &CExParrotDlg::OnMain05)
	ON_COMMAND(IDM_MAIN_06, &CExParrotDlg::OnMain06)
	ON_COMMAND(IDM_MAIN_07, &CExParrotDlg::OnMain07)
	ON_COMMAND(IDM_MAIN_08, &CExParrotDlg::OnMain08)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SND, &CExParrotDlg::OnNMClickListSnd)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SND, &CExParrotDlg::OnNMRClickListSnd)
	ON_COMMAND(ID_MENU_SOUND_EXTRACT, &CExParrotDlg::OnMenuSoundExtract)
	ON_COMMAND(ID_MENU_SOUND_EXTRACT_PATCH, &CExParrotDlg::OnMenuSoundExtractPatch)
	ON_COMMAND(ID_MENU_SOUND_INSERT, &CExParrotDlg::OnMenuSoundInsert)
	ON_COMMAND(ID_MENU_SOUND_REPLACE, &CExParrotDlg::OnMenuSoundReplace)
	ON_COMMAND(ID_MENU_SOUND_DELETE, &CExParrotDlg::OnMenuSoundDelete)
	ON_COMMAND(ID_MENU_SOUND_DELETE_PATCH, &CExParrotDlg::OnMenuSoundDeletePatch)
	ON_COMMAND(ID_MENU_SOUND_RENAME, &CExParrotDlg::OnMenuSoundRename)
	ON_COMMAND(ID_MENU_SOUND_INSERT_COPY, &CExParrotDlg::OnMenuSoundInsertCopy)
	ON_COMMAND(ID_MENU_SOUND_INSERT_REF, &CExParrotDlg::OnMenuSoundInsertRef)
	ON_COMMAND(ID_MENU_SOUND_DELINK, &CExParrotDlg::OnMenuSoundDelink)
	ON_COMMAND(ID_MENU_SOUND_HIDE, &CExParrotDlg::OnMenuSoundHide)
	ON_COMMAND(ID_MENU_SOUND_CHOOSE_ALL, &CExParrotDlg::OnMenuSoundChooseAll)
	ON_COMMAND(ID_MENU_SOUND_CHOOSE_HIGHLINE, &CExParrotDlg::OnMenuSoundChooseHighline)
	ON_COMMAND(ID_MENU_SOUND_CHOOSE_REVERSE, &CExParrotDlg::OnMenuSoundChooseReverse)
	ON_COMMAND(ID_MENU_SOUND_MOVE_UP, &CExParrotDlg::OnMenuSoundMoveUp)
	ON_COMMAND(ID_MENU_SOUND_MOVE_DOWN, &CExParrotDlg::OnMenuSoundMoveDown)
	ON_COMMAND(ID_MENU_SOUND_INSERT_OTHER, &CExParrotDlg::OnMenuSoundInsertOther)
	ON_COMMAND(ID_MENU_SOUND_SAVE, &CExParrotDlg::OnMenuSoundSave)
	ON_COMMAND(ID_MENU_SOUND_INSERT2, &CExParrotDlg::OnMenuSoundInsert2)
	ON_BN_CLICKED(IDC_TOOL_BUTTON2, &CExParrotDlg::OnBnClickedToolButton2)
	ON_BN_CLICKED(IDC_TOOL_BUTTON3, &CExParrotDlg::OnBnClickedToolButton3)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL1, &CExParrotDlg::OnBnClickedButtonControl1)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL2, &CExParrotDlg::OnBnClickedButtonControl2)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL3, &CExParrotDlg::OnBnClickedButtonControl3)
	ON_BN_CLICKED(IDC_TOOL_BUTTON4, &CExParrotDlg::OnBnClickedToolButton4)
	ON_BN_CLICKED(IDC_TOOL_BUTTON5, &CExParrotDlg::OnBnClickedToolButton5)
	ON_BN_CLICKED(IDC_TOOL_BUTTON6, &CExParrotDlg::OnBnClickedToolButton6)
	ON_BN_CLICKED(IDC_TOOL_BUTTON7, &CExParrotDlg::OnBnClickedToolButton7)
	ON_BN_CLICKED(IDC_TOOL_BUTTON8, &CExParrotDlg::OnBnClickedToolButton8)
	ON_BN_CLICKED(IDC_TOOL_BUTTON9, &CExParrotDlg::OnBnClickedToolButton9)
	ON_BN_CLICKED(IDC_TOOL_BUTTON10, &CExParrotDlg::OnBnClickedToolButton10)
	ON_BN_CLICKED(IDC_TOOL_BUTTON11, &CExParrotDlg::OnBnClickedToolButton11)
	ON_BN_CLICKED(IDC_TOOL_BUTTON12, &CExParrotDlg::OnBnClickedToolButton12)
	ON_BN_CLICKED(IDC_TOOL_BUTTON13, &CExParrotDlg::OnBnClickedToolButton13)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_BUTTON_CONTROL4, &CExParrotDlg::OnBnClickedButtonControl4)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL5, &CExParrotDlg::OnBnClickedButtonControl5)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_IMGSEARCH, &CExParrotDlg::OnBnClickedButtonSNDsearch)
	ON_COMMAND(IDM_TOOL_DOWNLOAD, &CExParrotDlg::OnToolDownload)
END_MESSAGE_MAP()


// CExParrotDlg 消息处理程序

BOOL CExParrotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowText(_T(VERSION_STR));
	SetWindowPos(NULL,0,0,width,height,SWP_NOZORDER|SWP_NOMOVE);
	CRect rc;
	GetClientRect(rc);
	adjustWindow(rc.Width(), rc.Height());
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->EasyInsertColumn(L"音效名,200");
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(L"这里显示NPK文件的信息");
	GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"这里显示音频的信息");
	GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(L"这里显示音频的版权信息");

	i_lSND.Create(16,16, TRUE|ILC_COLOR24, 6, 1);
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_UNKNOWN));	//0号资源·无效
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_LINK));		//1号资源·LINK
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_IMAGE));	//2号资源
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_SOUND_WAVE));		//3号资源
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_SOUND_VORBIS));
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_SOUND_MP3));
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetImageList(&i_lSND, LVSIL_SMALL);

	CREATEW(bar, IDD_TINY_PROGRESSBAR);
#if UGLY
	m_buttonPic[0].LoadBitmap(IDB_BITMAP_TOOL1);
	m_buttonPic[1].LoadBitmap(IDB_BITMAP_TOOL2);
	m_buttonPic[2].LoadBitmap(IDB_BITMAP_TOOL3);
	m_buttonPic[3].LoadBitmap(IDB_BITMAP_TOOL4);
	m_buttonPic[4].LoadBitmap(IDB_BITMAP_TOOL5);
	m_buttonPic[5].LoadBitmap(IDB_BITMAP_TOOL6);
	m_buttonPic[6].LoadBitmap(IDB_BITMAP_TOOL7);
	m_buttonPic[7].LoadBitmap(IDB_BITMAP_TOOL8);
	m_buttonPic[8].LoadBitmap(IDB_BITMAP_TOOL9);
	m_buttonPic[9].LoadBitmap(IDB_BITMAP_TOOL10);
	m_buttonPic[10].LoadBitmap(IDB_BITMAP_TOOL11);
	m_buttonPic[11].LoadBitmap(IDB_BITMAP_TOOL12);
	m_buttonPic[12].LoadBitmap(IDB_BITMAP_TOOL13);
	GET_CTRL(CButton, IDC_TOOL_BUTTON1)->SetBitmap(m_buttonPic[0]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON2)->SetBitmap(m_buttonPic[1]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON3)->SetBitmap(m_buttonPic[2]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON4)->SetBitmap(m_buttonPic[3]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON5)->SetBitmap(m_buttonPic[4]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON6)->SetBitmap(m_buttonPic[5]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON7)->SetBitmap(m_buttonPic[6]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON8)->SetBitmap(m_buttonPic[7]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON9)->SetBitmap(m_buttonPic[8]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON10)->SetBitmap(m_buttonPic[9]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON11)->SetBitmap(m_buttonPic[10]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON12)->SetBitmap(m_buttonPic[11]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON13)->SetBitmap(m_buttonPic[12]);
	if(!m_logoPic.Attach((HBITMAP)::LoadImage(NULL,
		profile.getSupportPath() + L"LOGO.bmp",
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE|LR_DEFAULTSIZE))){
			m_logoPic.LoadBitmapW(IDB_BITMAP_LOGO);
	}
	GET_CTRL(CStatic, IDC_LOGO)->SetBitmap(m_logoPic);
#endif

	CREATEW(toolSPK,IDD_TOOL_SPK);

	m_ttc.Create(this);
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON1), L"选择");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON2), L"放大");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON3), L"拖动");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON4), L"选择左边");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON5), L"选择右边");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON6), L"全选");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON7), L"裁切");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON8), L"银屏调节");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON9), L"淡入");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON10), L"淡出");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON11), L"反转");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON12), L"拉伸");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON13), L"回声");

	MP3image.create(1,1);
	MP3image.fill(profile.getAudioColor(4));

	AfxBeginThread(xThread, this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExParrotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		

#if UGLY
		CPaintDC dc(this);
		CRect   rect;        
		GetClientRect(rect);    
		dc.FillSolidRect(rect,profile.mainColor); 
#endif
		CDialogEx::OnPaint();
		draw();
		updateMP3image();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExParrotDlg::OnQueryDragIcon(){
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CExParrotDlg::decodeThread(void*p){
	CExParrotDlg*dlg = (CExParrotDlg*)p;
	int id = dlg->crtSNDid;
	stream s, sPCM;
	switch(dlg->no.SNDgetVersion(id)){
	case VVORBIS:
		{
			dlg->bar.show(4);
			dlg->bar.setInfo(L"正在解码喵……", 0);
			OGG::OGGobject oo;
			dlg->no.extract(dlg->crtSNDid, s);
			dlg->fileSNDname = StrToCStr(dlg->no.entry[id].comment);
			oo.load(s);
			oo.initDecoder();
			
			{
				stream s;
				oo.initPCM();
				int i = 3;
				int j = 0;
				dlg->bar.setMax(oo.packs.size());
				while(oo.packDecode(i++)){
					oo.makePCM(j++);
					dlg->bar.setPos(i);
				}
				oo.makePCMstream(s);
				dlg->au.create(s, oo.info.channels, oo.info.sampleRate);
			}
			dlg->dispLeftBound = 0;
			dlg->dispRightBound = dlg->au.length - 1;
			dlg->leftBound = 0;
			dlg->rightBound = 0;
			dlg->updateInfo();
			CString tempStr = L"类别:Ogg音频\r\n编码器信息:\r\n" + StrToCStr(oo.comment.vendorInfo) + L"\r\n";
			tempStr += L"其他信息:\r\n";
			if(oo.comment.otherInfo.size() == 0){
				tempStr += L"无";
			}else{
				for(int i = 0;i<oo.comment.otherInfo.size();i++)
					tempStr += StrToCStr(oo.comment.otherInfo[i]) + L"\r\n";
			}
			GET_DLG_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(tempStr);
			dlg->bar.hide();
			dlg->draw();
			dlg->player.play(dlg->au);
			Sleep(10);
			return 0;
		}
	case VMP3:
		GET_DLG_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"MP3解码还没写好喵！");
		GET_DLG_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(L"MP3解码还没写好喵！");
		return 0;
	case VWAVE:
		{
			dlg->bar.show(4);
			dlg->bar.setInfo(L"正在解码喵……", 0);
			WAV::WAVobject wo;
			dlg->no.extract(dlg->crtSNDid, s);
			dlg->fileSNDname = StrToCStr(dlg->no.entry[id].comment);
			wo.load(s);
			loadWAV(dlg->au, wo);
			dlg->dispLeftBound = 0;
			dlg->dispRightBound = dlg->au.length - 1;
			dlg->leftBound = 0;
			dlg->rightBound = 0;
			dlg->updateInfo();
			CString tempStr = L"类别:波形文件\r\n编码器信息:PCM\r\n";
			GET_DLG_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(tempStr);
			dlg->bar.hide();
			dlg->draw();
			dlg->player.play(dlg->au);
			Sleep(10);
			return 0;
		}
	default:
		GET_DLG_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"未能识别这个文件！");
		GET_DLG_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(L"类别:其他文件");
		return 0;
	}
}
void CExParrotDlg::decode(){
	AfxBeginThread(decodeThread, this);
}
void CExParrotDlg::draw(){
	if(rightBound - leftBound > 0){
		GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowText(L"左端:" + DoubleToCStr(0.001F*au.getTime(leftBound))+L"s");
		GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowText(L"右端:" + DoubleToCStr(0.001F*au.getTime(rightBound))+L"s");
	}else{
		GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowText(L"左端:" + DoubleToCStr(0.001F*au.getTime(0))+L"s");
		GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowText(L"右端:" + DoubleToCStr(0.001F*au.getLastTime())+L"s");
	}
	AfxBeginThread(drawThread, this);
}
void CExParrotDlg::makeGraph(image &graphMat, int w, int h){
	color clrLeftChannel = profile.getAudioColor(1);//color(0xFF, 0xff, 0x66, 0x00);
	color clrRightChannel = profile.getAudioColor(2);//color(0xFF, 0xff, 0x00, 0xCC);
	color clrBack = profile.getAudioColor(0);//color(0xFF,0x66,0xCC,0xFF);
	color clrBound = color(0xFF,0,0,0);
	color clrZoom = color(0xFF,0xFF,0x22,0x22);
	graphMat.create(h, w);
	graphMat.fill(clrBack);
	int i, j;
	image content;
	if(KoishiImageTool::loadPNG(content, CStrToStr(profile.getSupportPath() + L"back.png"))){
		for(i = 0;i<content.getWidth();i++){
			for(j = 0;j<content.getHeight();j++){
				color clr = content.getElem(j, i);
				if(i<content.getWidth()*0.3 || j < content.getHeight()*0.3){
					clr.alpha = MIN(0xB0*j/(0.3*content.getHeight()), 0xB0*i/(0.3*content.getWidth()));
				}else{
					clr.alpha = 0xB0;
				}
				content.setElem(j,i,clr);
			}
		}
		graphMat.putFore(content, LAY, point(w - content.getWidth(), h - content.getHeight()));
	}
	content.destory();

	graphMat.rectangle(point(0,0),point(w-1,h-1),clrBound);
	graphMat.rectangle(point(1,1),point(w-2,h-2),clrBound);
	graphMat.line(point(0,(h-1)/2),point(w-1,(h-1)/2),clrBound);
	for(i = 0;i<h*w;i++){
		int x = i % w;
		int y = i / w;
		int xd = (dispRightBound - dispLeftBound) * x / w + dispLeftBound;
		int yd = 32768 - 65536 * y / (h / 2);
		if(xd<au.length && xd >= 0){
			//已定义区域
			int yd0 = abs(au[xd][0]);
			int yd1 = abs(au[xd][1]);
			if( yd >= -abs(yd0) && yd <= abs(yd0)){
				graphMat.setElem(i, clrLeftChannel);
			}else if(yd + 65536 >= -abs(yd1) && yd + 65536 <= abs(yd1)){
				graphMat.setElem(i, clrRightChannel);
			}
			//被选择区域
			if(leftBound < rightBound && xd >= leftBound && xd <rightBound){
				color T = graphMat.getElem(i);
				color T1 = color(0XFF, 0XFF-T.R, 0XFF-T.G, 0XFF-T.B);
				graphMat.setElem(i, T1);
			}
		}else{
			//未定义区域
			color T = graphMat.getElem(i);
			color T1 = color(0XFF, T.R/2, T.G/2, T.B/2);
			graphMat.setElem(i, T1);
		}
	}
	if(zoomBound1 != 0 && zoomBound1 >= dispLeftBound && zoomBound1 < dispRightBound){
		int XX = (zoomBound1 - dispLeftBound) * w / (dispRightBound - dispLeftBound);
		graphMat.line(point(XX,1), point(XX,h-1), clrZoom);
	}
	if(zoomBound2 != 0 && zoomBound2 >= dispLeftBound && zoomBound2 < dispRightBound){
		int XX = (zoomBound2 - dispLeftBound) * w / (dispRightBound - dispLeftBound);
		graphMat.line(point(XX,1), point(XX,h-1), clrZoom);
	}
	return;
}
void CExParrotDlg::drawPower(){
	image mat;
	int canw = 520-170;
	int canh = height-10-380;
	mat.create(canh, canw);
	mat.fill(color(0xFF,0,0,0));
	for(int i = 0;i<16;i++){
		colorHSV hsv = {i*360/16, 1.0F, 1.0F};
		color clr;
		clr.useHSV(hsv);
		mat.filledRectangle(point(2+18*i, canh - (canh - 5)*(power[i] + 2)/100), point(17+18*i, canh - 3), clr);
	}
	mat.filledRectangle(point(290, canh - (canh - 5)*(cur[0] + 2)/100), point(290 + (canw - 296)/2, canh - 3), profile.getAudioColor(3));
	mat.filledRectangle(point(293 + (canw - 296)/2, canh - (canh - 5)*(cur[1] + 2)/100), point(canw - 3, canh - 3), profile.getAudioColor(3));
	int i, j;
	CImage img;
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<canw;i++){
		for(j=0;j<canh;j++){
			*(pst + pit*j + 4*i + 0) = mat[j][i].B;
			*(pst + pit*j + 4*i + 1) = mat[j][i].G;
			*(pst + pit*j + 4*i + 2) = mat[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,170,380);
	img.Destroy();
	ReleaseDC(pDC);
	//dlg->drawing = 0;
	mat.destory();
}
void CExParrotDlg::adjustWindow(int w, int h){
	//调整窗口控件
	CHECK_VALID(w>=700);
	CHECK_VALID(h>=500);
	width = w;
	height = h;
	barWidth = (w-540);
	barPart1 = barWidth*26/45;
	barPart2 = barWidth*19/45;
	barHeight = 30;
	GET_CTRL(CStatic, IDC_LOGO)->SetWindowPos(NULL,10,10,150,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU)->SetWindowPos(NULL,170,10,110,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU2)->SetWindowPos(NULL,290,10,110,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU3)->SetWindowPos(NULL,410,10,110,40,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_SNDSEARCH)->SetWindowPos(NULL,10,60,100,25,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_IMGSEARCH)->SetWindowPos(NULL,120,60,40,25,SWP_NOZORDER);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetWindowPos(NULL,10,95,150,h-115,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowPos(NULL,170,60,170,80,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowPos(NULL,350,60,170,80,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowPos(NULL,170,150,170,170,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL1)->SetWindowPos(NULL,170,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL2)->SetWindowPos(NULL,241,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL3)->SetWindowPos(NULL,312,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowPos(NULL,383,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL5)->SetWindowPos(NULL,454,330,66,40,SWP_NOZORDER);

	int delta = barPart1/13;
	GET_CTRL(CButton, IDC_TOOL_BUTTON1)->SetWindowPos(NULL,530+delta*0,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON2)->SetWindowPos(NULL,530+delta*1,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON3)->SetWindowPos(NULL,530+delta*2,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON4)->SetWindowPos(NULL,530+delta*3,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON5)->SetWindowPos(NULL,530+delta*4,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON6)->SetWindowPos(NULL,530+delta*5,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON7)->SetWindowPos(NULL,530+delta*6,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON8)->SetWindowPos(NULL,530+delta*7,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON9)->SetWindowPos(NULL,530+delta*8,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON10)->SetWindowPos(NULL,530+delta*9,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON11)->SetWindowPos(NULL,530+delta*10,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON12)->SetWindowPos(NULL,530+delta*11,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON13)->SetWindowPos(NULL,530+delta*12,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowPos(NULL,530+barPart1+barPart2*0/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_RANGE2)->SetWindowPos(NULL,530+barPart1+barPart2*1/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowPos(NULL,530+barPart1+barPart2*2/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
}
int CExParrotDlg::getIconSND(dword ext){
	dword d[5] = {3,4,5,2,0};
	return d[ext];
}
void CExParrotDlg::updateSNDlist(){
	updateInfo();
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->DeleteAllItems();
	for(int i = 0;i<no.count;i++){
		int li = no.checkLink(i);
		if(li == i){
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->EasyInsertItem(GetTail(StrToCStr(no.entry[i].comment)), getIconSND(no.SNDgetVersion(i)));
		}else{
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->EasyInsertItem(GetTail(StrToCStr(no.entry[i].comment) + L"["+GetTail(StrToCStr(no.entry[li].comment))+L"]"), 1);
		}
	}
}
void CExParrotDlg::updateInfo(){
	CString cstr;
	cstr = L"文件名："+GetTail(fileNPKname)+L"\r\n";
	cstr += L"大小："+NumToCStr(no.getSize())+L"字节\r\n";
	cstr += L"条目数："+NumToCStr(no.count);
	cstr += (crtSNDid  == -1) ? L"" : ( L"/"  + NumToCStr(crtSNDid));
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(cstr);
	cstr = saveAlert ? L"音效状态：已变动\r\n" : L"音效状态：未变动\r\n";
	cstr += L"声道数:" + NumToCStr(au.channel) + L"\r\n";
	cstr += L"采样频率:" + NumToCStr(au.sampleRate) + L"Hz\r\n";
	cstr += L"时长:" + DoubleToCStr(au.getLastTime() * 0.001f) + L"s";
	GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(cstr);
}
void CExParrotDlg::updateMP3image(){
	int i, j;
	image mat;
	MP3image.zoom(mat, 170.0f/MP3image.width, 170.0f/MP3image.height);
	CImage img;
	img.Create(170, 170, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<170;i++){
		for(j=0;j<170;j++){
			*(pst + pit*j + 4*i + 0) = mat[j][i].B;
			*(pst + pit*j + 4*i + 1) = mat[j][i].G;
			*(pst + pit*j + 4*i + 2) = mat[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,350,150);
	img.Destroy();
	ReleaseDC(pDC);
	//dlg->drawing = 0;
	mat.destory();
}
/////////////////////
UINT CExParrotDlg::playThread(void *para){
	CExParrotDlg*dlg = (CExParrotDlg*)para;
	if(dlg->rightBound - dlg->leftBound <= 0){
		dlg->player.play(dlg->au);
	}else{
		audio ad = dlg->au;
		ad.clip(dlg->leftBound, dlg->rightBound);
		dlg->player.play(ad);
	}
	return 0;
}
UINT CExParrotDlg::xThread(void *para){
	CExParrotDlg*dlg = (CExParrotDlg*)para;
	while(1){
		if(dlg->recording){
			dlg->cur[0] = dlg->recorder.energyLeft*100/32767;
			dlg->cur[1] = dlg->recorder.energyRight*100/32767;
			for(int i = 0;i<16;i++){
				dlg->power[i] = dlg->recorder.freq[i]* 100 / 10000;
				if(dlg->power[i] > 100)
					dlg->power[i] = 100;
			}
		}else if(dlg->player.idv != -1){
			dlg->cur[0] = dlg->player.dv[dlg->player.idv].energyLeft*100/32767;
			dlg->cur[1] = dlg->player.dv[dlg->player.idv].energyRight*100/32767;
			for(int i = 0;i<16;i++){
				dlg->power[i] = dlg->player.dv[dlg->player.idv].freq[i]* 100 / 10000;
				if(dlg->power[i] > 100)
					dlg->power[i] = 100;
			}
		}
		if(dlg->cur[0]>100)
			dlg->cur[0] = 100;
		if(dlg->cur[1]>100)
			dlg->cur[1] = 100;
		dlg->drawPower();
		Sleep(4);
	}
	return 0U;
}
UINT CExParrotDlg::drawThread(void *para){
	CExParrotDlg*dlg = (CExParrotDlg*)para;
	dlg->drawPower();
	int canw = dlg->width - 540;
	int canh = dlg->height - 50;
	image canvas;
	dlg->makeGraph(canvas, canw, canh);
	int i, j;
	CImage img;
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = dlg->GetDC();
	for(i=0;i<canw;i++){
		for(j=0;j<canh;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,530,10);
	img.Destroy();
	dlg->ReleaseDC(pDC);
	//dlg->drawing = 0;
	canvas.destory();
	return 0;
}
/////////////////////
void CExParrotDlg::getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected){
	selected.clear();
	int k;
	switch(targetPara){
	case SINGLE_SELECT:
		//单选
		selected.push_back(highLine);
		break;
	case MULTI_SELECT:
		//多选
		for(k=0;k<listCtrl->GetItemCount();k++)
			if(listCtrl->GetCheck(k))
				selected.push_back(k);
		break;
	default:
		//全选
		for(k=0;k<listCtrl->GetItemCount();k++)
			selected.push_back(k);
		break;
	}
}
void CExParrotDlg::OnBnClickedButtonMenu(){
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}

void CExParrotDlg::OnBnClickedButtonMenu2(){
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_TOOL);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}

void CExParrotDlg::OnBnClickedButtonMenu3(){
	// TODO: 在此添加控件通知处理程序代码
	stream s;
	makeWAV(au, s);
	if(no.replace(crtSNDid, s)){
		MessageBox(L"音效修改完毕喵！",L"提示喵！");
		saveAlert = false;
	}else{
		MessageBox(L"音效修改失败喵！",L"提示喵！");
	}
	s.release();
}

void CExParrotDlg::OnMain01(){
	// TODO: 在此添加命令处理程序代码
	no.release();
	no.create();
	au.destory();
	fileNPKname = L"newNPK.npk";
	fileSNDname = L"newSound.ogg";
	au.create(44100);
	au.channel = 1;
	au.sampleRate = 44100;
	stream s;
	makeWAV(au, s);
	no.push(s, "newSound.ogg");
	updateInfo();
	updateSNDlist();
	s.release();
	au.channel = 2;
	au.sampleRate = 44100;
	au.create(1);
}

void CExParrotDlg::OnMain02(){
	// TODO: 在此添加命令处理程序代码
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("所有支持的文件(*.NPK,*.WAV,*.OGG,*.MP3)|*.NPK;*.WAV;*.OGG;*.MP3|音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3|NPK文件(*.NPK)|*.NPK|vorbis音效(*.OGG)|*.OGG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		fmt = fileName.Right(1);
		CStrToStr(fileName, fn);
		if(fmt == L"K" || fmt == L"k"){
			no.release();
			if(no.loadFile(fn)){
			}else{
				MessageBox(L"读取失败喵！");
				return;
			}
			fileNPKname = fileName;
			saveAlert = false;
			updateSNDlist();
			if(no.count>0){
				GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(0);
				crtSNDid = 0;
			}
		}else{
			no.release();
			no.create();
			fileNPKname = L"newNPK.npk";
			fileSNDname = fileName;
			saveAlert = false;
			stream s;
			s.loadFile(fn);
			fileName = GetTail(fileName);
			CStrToStr(Slashing(fileName), fn);
			no.push(s, fn);
			updateSNDlist();
			updateInfo();
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(0);
			crtSNDid = 0;
		}
	}
}

void CExParrotDlg::OnMain03(){
	// TODO: 在此添加命令处理程序代码
	if(saveAlert){
		if(IDYES == MessageBox(L"这个音效已经被你改动了喵，要保存喵？",L"提示喵",MB_YESNO))
			OnBnClickedButtonMenu3();
	}
	str fn;
	CString fileName;
	fileName = fileNPKname;
	CStrToStr(fileName, fn);
	if(no.saveFile(fn)){
		MessageBox(_T("NPK保存完毕喵！"),L"提示喵");
	}else{
		MessageBox(_T("NPK保存失败喵！"),L"提示喵");
	}
}

void CExParrotDlg::OnMain04(){
	// TODO: 在此添加命令处理程序代码
	if(saveAlert){
		if(IDYES == MessageBox(L"这个音效已经被你改动了喵，要保存喵？",L"提示喵",MB_YESNO))
			OnBnClickedButtonMenu3();
	}
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(false, defExt, GetTail(fileNPKname), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if(no.saveFile(fn)){
			MessageBox(_T("NPK保存完毕喵！"),L"提示喵");
			fileNPKname = fileName;
			fmt = fileName.Right(1);
			updateInfo();
		}else{
			MessageBox(_T("NPK保存失败喵！"),L"提示喵");
		}
	}
}

void CExParrotDlg::OnMain05(){
	// TODO: 在此添加命令处理程序代码
	ModalPreference2 dlg;
	dlg.modifiedProfile = profile;
	if(IDOK == dlg.DoModal()){
		profile = dlg.modifiedProfile;
		MessageBox(L"软件配置被修改喵，请重启以生效。",L"提示喵");
	}
}

void CExParrotDlg::OnMain06(){
	// TODO: 在此添加命令处理程序代码
	MessageBox(L"施工中");
}

void CExParrotDlg::OnMain07(){
	ShellExecute(NULL, L"open",L"https://github.com/Lucky-Koishi/KoishiExAPI/wiki/%E6%81%8B%E6%81%8B%E3%81%AEEx%E5%85%94%E5%AD%90%E7%89%88", NULL, NULL, SW_MAXIMIZE); 
}

void CExParrotDlg::OnMain08(){
	CDialogEx::OnCancel();
}


void CExParrotDlg::OnNMClickListSnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	////////////////////////////
	//切换IMG时提示保存
	if(saveAlert){
		switch(MessageBox(L"这个音效已经被你改动了喵，要保存喵？",L"提示喵",MB_YESNOCANCEL)){
		case IDYES:
			OnBnClickedButtonMenu3();
			break;
		case IDNO:
			saveAlert = false;
			break;
		default:
			return;
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(row);
	if(row>=0){
		crtSNDid = row;
		fndSNDid = row;
		au.destory();
		decode();
	}
	updateInfo();
	*pResult = 0;
}


void CExParrotDlg::OnNMRClickListSnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListSnd(pNMHDR, pResult);
	/////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_SOUND);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}


void CExParrotDlg::OnMenuSoundExtract(){
	CHECK_VALID(crtSNDid >= 0);
	ParaSoundExtract = SINGLE_SELECT;
	AfxBeginThread(ThreadSoundExtract, this);
}
void CExParrotDlg::OnMenuSoundExtractPatch(){
	ParaSoundExtract = MULTI_SELECT;
	AfxBeginThread(ThreadSoundExtract, this);
}
UINT CExParrotDlg::ThreadSoundExtract(void*context){
	CExParrotDlg *dlg = (CExParrotDlg *)context;
	dlg->processing = 1;
	CString filePath = dlg->profile.getOutputPath(dlg->fileNPKname);
	CString fileName;
	std::vector<int> targetList;					//待转换目标列表
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_SND), dlg->crtSNDid, dlg->ParaSoundExtract, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i=0;i<targetList.size();i++){
		int id = targetList[i];
		dlg->bar.setInfo(L"正在提取"+GetTail(StrToCStr(dlg->no.entry[id].comment))+L"喵……", i);
		fileName = filePath+Underlining(StrToCStr(dlg->no.entry[id].comment));
		dlg->no.extract(id, CStrToStr(fileName));
	}
	dlg->MessageBox(L"全部提取完毕喵！已保存到"+dlg->profile.getOutputPath(dlg->fileNPKname)+L"了喵！",L"提示喵");
	dlg->bar.hide();
	dlg->processing = 0;
	return 0U;
}

void CExParrotDlg::OnMenuSoundInsert(){
	ModalSoundInsert dlg;
	dlg.in.firstInsert = false;
	if(IDOK == dlg.DoModal()){
		ParaSoundInsert = dlg.out;
		AfxBeginThread(ThreadSoundInsert, this);
	}
}
void CExParrotDlg::OnMenuSoundInsert2(){
	ModalSoundInsert dlg;
	dlg.in.firstInsert = true;
	if(IDOK == dlg.DoModal()){
		ParaSoundInsert = dlg.out;
		AfxBeginThread(ThreadSoundInsert, this);
	}
}

UINT CExParrotDlg::ThreadSoundInsert(void*context){
	CExParrotDlg*dlg = (CExParrotDlg*)context;
	ModalSoundInsert::OUTPUT *para = &dlg->ParaSoundInsert;
	dlg->processing = 1;
	int insertPos;
	switch(para->operate){
	case 1:
		insertPos = dlg->crtSNDid;
		break;
	case 2:
		insertPos = dlg->crtSNDid + 1;
		break;
	case 3:
		insertPos = dlg->no.count;
		break;
	}
	switch(para->type){
	case 1:
		if(true){
			audio newAu(44100);
			newAu.channel = 1;
			newAu.sampleRate = 44100;
			stream s;
			makeWAV(newAu, s);
			dlg->no.insert(insertPos, s, CStrToStr(para->pathName));
			GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(insertPos,GetTail(para->pathName),dlg->getIconSND(VWAVE));
			s.release();
			newAu.destory();
		}
		break;
	case 2:
		if(true){
			stream s;
			s.loadFile(CStrToStr(para->fileName));
			dlg->no.insert(insertPos, s, CStrToStr(para->pathName));
			GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(insertPos,GetTail(para->pathName),dlg->getIconSND(dlg->no.SNDgetVersion(insertPos)));
			s.release();
		}
		break;
	case 3:
		if(true){
			NPKobject newNO;
			newNO.loadFile(CStrToStr(para->fileName));
			dlg->bar.show(newNO.count);
			int countFail = 0;
			int countSkip = 0;
			int countReplace = 0;
			int countSuccess = 0;
			int conflict = -1;
			for(int i = 0;i<newNO.count; i++){
				dlg->bar.setInfo(L"当前插入"+GetTail(StrToCStr(newNO.entry[i].comment))+
					L"喵……(成功"+NumToCStr(countSuccess)+
					L"个,跳过"+NumToCStr(countSkip)+
					L"个,替换"+NumToCStr(countReplace)+
					L"个,失败"+NumToCStr(countFail)+
					L"个)", i);
				if(newNO.SNDgetVersion(i) == VIMAGE || newNO.SNDgetVersion(i) == VSNDUKNOWN){
					countFail ++;
					continue;
				}
				stream s;
				newNO.extract(i, s);
				conflict =  -1;
				for(int j = 0;j<dlg->no.count;j++){
					CString s1 = GetTail(StrToCStr(newNO.entry[i].comment));
					CString s2 = GetTail(StrToCStr(dlg->no.entry[j].comment));
					if(s1 == s2){
						conflict = j;
						break;
					}
				}
				if(conflict < 0){
					dlg->no.insert(insertPos + countSuccess, s, newNO.entry[i].comment);
					countSuccess ++;
				}else{
					//冲突处理
					switch(para->conflict){
					case 1:
						countSkip ++;
						break;
					case 2:
						dlg->no.replace(conflict, s);
						countReplace ++;
						break;
					case 3:
						dlg->no.insert(insertPos + countSuccess, s, newNO.entry[i].comment+"(new)");
						countSuccess ++;
						break;
					}
				}
				s.release();
			}
			dlg->MessageBox(L"导入完毕喵！总"+NumToCStr(newNO.count)+
					L"个,成功"+NumToCStr(countSuccess)+
					L"个,跳过"+NumToCStr(countSkip)+
					L"个,替换"+NumToCStr(countReplace)+
					L"个,失败"+NumToCStr(countFail)+
					L"个喵！",L"提示喵");
			dlg->bar.hide();
			newNO.release();
		}
		break;
	case 4:
		if(true){
			CString folderName = para->fileName + L"\\*.*";
			CFileFind fileFind;
			std::vector<CString> fileList;
			std::vector<CString> pathList;
			BOOL ret = fileFind.FindFile(folderName);
			while(ret){
				ret = fileFind.FindNextFile();
				fileList.push_back(fileFind.GetFileName());
				pathList.push_back(fileFind.GetFilePath());
			}
			NPKobject newNO;
			stream s;
			int countNPK = 0;
			int countNPKIMG = 0;
			int countIMG = 0;
			int totalSuccess = 0;
			dlg->bar.show(100);
			for(int fileID = 0;fileID<pathList.size();fileID++){
				if(fileList[fileID].Right(4) == L".npk" || fileList[fileID].Right(4) == L".NPK" ){
					if(!newNO.loadFile(CStrToStr(pathList[fileID]))){
						continue;
					}
					int countFail = 0;
					int countSkip = 0;
					int countReplace = 0;
					int countSuccess = 0;
					int conflict = -1;
					dlg->bar.setMax(newNO.count);
					for(int i = 0;i<newNO.count; i++){
						dlg->bar.setInfo(L"当前插入"+fileList[fileID] +
							L"中的" + GetTail(StrToCStr(newNO.entry[i].comment))+
							L"喵……(成功"+NumToCStr(countSuccess)+
							L"个,跳过"+NumToCStr(countSkip)+
							L"个,替换"+NumToCStr(countReplace)+
							L"个,失败"+NumToCStr(countFail)+
							L"个)", i);
						if(!newNO.extract(i, s)){
							countFail ++;
							continue;
						}
						conflict =  -1;
						for(int j = 0;j<dlg->no.count;j++){
							CString s1 = GetTail(StrToCStr(newNO.entry[i].comment));
							CString s2 = GetTail(StrToCStr(dlg->no.entry[j].comment));
							if(s1 == s2){
								conflict = j;
								break;
							}
						}
						if(conflict < 0){
							dlg->no.insert(insertPos + totalSuccess, s, newNO.entry[i].comment);
							countSuccess ++;
							totalSuccess ++;
						}else{
							//冲突处理
							switch(para->conflict){
							case 1:
								countSkip ++;
								break;
							case 2:
								dlg->no.replace(conflict, s);
								countReplace ++;
								break;
							case 3:
								dlg->no.insert(insertPos + totalSuccess, s, newNO.entry[i].comment+"(new)");
								countSuccess ++;
								totalSuccess ++;
								break;
							}
						}
						s.release();
					}
					newNO.release();
					countNPK ++;
					countNPKIMG += countSuccess;
				}else if(fileList[fileID].Right(4) == L".wav" || fileList[fileID].Right(4) == L".WAV" || fileList[fileID].Right(4) == L".ogg" || fileList[fileID].Right(4) == L".OGG" || fileList[fileID].Right(4) == L".mp3" || fileList[fileID].Right(4) == L".MP3" ){
					s.loadFile(CStrToStr(pathList[fileID]));
					dlg->bar.setInfo(L"当前插入"+fileList[fileID] +	L"喵……", 0);
					CString newPathName = Slashing(fileList[fileID]);
					dlg->no.insert(insertPos + totalSuccess, s, CStrToStr(newPathName));
					totalSuccess ++;
					s.release();
					countIMG ++;
				}
			}
			dlg->MessageBox(L"导入完毕喵！成功导入了"+NumToCStr(countIMG)+L"个外部音效对象喵，并从"+NumToCStr(countNPK)+L"个NPK文件中导入了"+NumToCStr(countNPKIMG)+L"个音效对象喵。",L"提示喵");
			dlg->bar.hide();
		}
		break;
	}
	dlg->updateSNDlist();
	return 0U;
}

void CExParrotDlg::OnMenuSoundReplace(){
	CHECK_VALID(crtSNDid>=0);
	CString defExt = _T("音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3");
	CString extFilter = _T("音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3|波形音效(*.WAV)|*.WAV|vorbis音效(*.OGG)|*.OGG|MP3音效(*.MP3)|*.MP3||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		stream s;
		s.loadFile(CStrToStr(dlg.GetPathName()));
		no.replace(crtSNDid, s);
		MessageBox(L"替换完毕喵！");
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(crtSNDid, 0, LVIF_IMAGE, NULL, getIconSND(no.SNDgetVersion(crtSNDid)),0,0,0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(crtSNDid);
		s.release();
	}
}


void CExParrotDlg::OnMenuSoundDelete(){
	CHECK_VALID(crtSNDid >= 0);
	ParaSoundDelete = SINGLE_SELECT;
	AfxBeginThread(ThreadSoundDelete, this);
}


void CExParrotDlg::OnMenuSoundDeletePatch(){
	ParaSoundDelete = MULTI_SELECT;
	AfxBeginThread(ThreadSoundDelete, this);
}

UINT CExParrotDlg::ThreadSoundDelete(void*context){
	CExParrotDlg *dlg = (CExParrotDlg *)context;
	dlg->processing = 1;
	std::vector<int> targetList;					//待转换目标列表
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_SND), dlg->crtSNDid, dlg->ParaSoundDelete, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i=0;i<targetList.size();i++){
		int id = targetList[targetList.size()-i-1];
		dlg->bar.setInfo(L"正在删除"+GetTail(StrToCStr(dlg->no.entry[id].comment))+L"喵……", i);
		dlg->no.IMGremove(id);
	}
	dlg->bar.hide();
	dlg->updateSNDlist();
	dlg->processing = 0;
	dlg->crtSNDid = -1;
	return 0U;
}

void CExParrotDlg::OnMenuSoundRename(){
	CHECK_VALID(crtSNDid>=0);
	ModalRename dlg;
	dlg.oldName = StrToCStr(no.entry[crtSNDid].comment);
	if(IDOK == dlg.DoModal()){
		no.rename(crtSNDid,  CStrToStr(dlg.newName));
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(crtSNDid, 0, GetTail(dlg.newName));
		fileSNDname = dlg.newName;
		updateInfo();
	}
}


void CExParrotDlg::OnMenuSoundInsertCopy(){
	CHECK_VALID(crtSNDid>=0);
	stream sr;
	str newComment = no.entry[crtSNDid].comment;
	if(newComment.size() > 4 && newComment[newComment.size() - 4 ] == '.'){
		newComment.insert(newComment.end() - 4, '2');
	}else{
		newComment.push_back('2');
	}
	no.extract(crtSNDid, sr);
	no.insert(crtSNDid + 1, sr, newComment);
	updateSNDlist();
}


void CExParrotDlg::OnMenuSoundInsertRef(){
	CHECK_VALID(crtSNDid>=0);
	str newComment = no.entry[crtSNDid].comment;
	if(newComment.size() > 4 && newComment[newComment.size() - 4 ] == '.'){
		newComment.insert(newComment.end() - 4, '2');
	}else{
		newComment.push_back('2');
	}
	no.insertLink(crtSNDid + 1, crtSNDid, newComment); 
	updateSNDlist();
}


void CExParrotDlg::OnMenuSoundDelink(){
	CHECK_VALID(crtSNDid>=0);
	if(no.delink(crtSNDid)){
		updateSNDlist();
	}else{
		MessageBox(L"并不是引用喵！");
	}
}


void CExParrotDlg::OnMenuSoundHide(){
	ModalSoundHide dlg;
	if(IDOK == dlg.DoModal()){
		ParaSoundHide = dlg.out;
		AfxBeginThread(ThreadSoundHide, this);
	}
}

UINT CExParrotDlg::ThreadSoundHide(void*context){
	CExParrotDlg*dlg=(CExParrotDlg*)context;
	ModalSoundHide::OUTPUT para = dlg->ParaSoundHide;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_SND), dlg->crtSNDid, para.operate-1, targetList);
	dlg->bar.show(targetList.size()-1);
	audio emptyAu(1,1);
	stream s;
	makeWAV(emptyAu, s);
	for(int i = 0; i<targetList.size();i++){
		int id = targetList[targetList.size() - 1 - i];
		dlg->bar.setInfo(L"正在隐藏"+GetTail(StrToCStr(dlg->no.entry[id].comment))+L"喵……", i);
		dlg->no.replace(id, s);
	}
	emptyAu.destory();
	s.release();
	dlg->bar.hide();
	dlg->updateSNDlist();
	dlg->updateInfo();
	dlg->processing = 0;
	return 0U;
}

void CExParrotDlg::OnMenuSoundChooseAll(){
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, TRUE);
}


void CExParrotDlg::OnMenuSoundChooseHighline(){
	for(int i=0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(); i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i,TRUE);
}


void CExParrotDlg::OnMenuSoundChooseReverse(){
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, 1-GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetCheck(i));
}


void CExParrotDlg::OnMenuSoundMoveUp(){
	int row = crtSNDid;
	CHECK_VALID(row>=1);
	NPKentry ne = no.entry[row];
	no.entry[row] = no.entry[row - 1];
	no.entry[row - 1] = ne;
	for(int i = 0;i<=1;i++){
		int id = row - i;
		int li = no.checkLink(id);
		if(li == id){
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconSND(no.SNDgetVersion(id)),0,0,0);
		}else{
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)
				+ L"["+GetTail(StrToCStr(no.entry[li].comment))+L"]"));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, 1, 0,0,0);
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(row - 1);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row - 1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row ,0, LVIS_SELECTED|LVIS_FOCUSED);
	crtSNDid = row - 1;
	updateInfo();
}


void CExParrotDlg::OnMenuSoundMoveDown(){
	int row = crtSNDid;
	CHECK_VALID(row>=0);
	CHECK_VALID(row<no.count);
	NPKentry ne = no.entry[row];
	no.entry[row] = no.entry[row + 1];
	no.entry[row + 1] = ne;
	for(int i = 0;i<=1;i++){
		int id = row + i;
		int li = no.checkLink(id);
		if(li == id){
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconSND(no.SNDgetVersion(id)),0,0,0);
		}else{
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)
				+ L"["+GetTail(StrToCStr(no.entry[li].comment))+L"]"));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, 1, 0,0,0);
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(row + 1);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row + 1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row ,0, LVIS_SELECTED|LVIS_FOCUSED);
	crtSNDid = row + 1;
	updateInfo();
}

void CExParrotDlg::OnMenuSoundInsertOther(){
	CString defExt = _T("所有文件(*.*)|*.*");
	CString extFilter = _T("所有文件(*.*)|*.*||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK){
		no.insert(crtSNDid, CStrToStr(dlg.GetPathName()),CStrToStr(GetTail(dlg.GetPathName())));
		updateSNDlist();
	}
}

void CExParrotDlg::OnMenuSoundSave(){
	CHECK_VALID(crtSNDid >= 0);
	CString defExt = _T("所有文件(*.*)|*.*");
	CString extFilter = _T("所有文件(*.*)|*.*||");
	CFileDialog dlg(false, defExt, Underlining(StrToCStr(no.entry[crtSNDid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		no.extract(crtSNDid, CStrToStr(dlg.GetPathName()));
		MessageBox(_T("保存完毕喵！"));
	}
}


void CExParrotDlg::OnBnClickedButtonControl1(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法播放喵！",L"提示喵");
		return;
	}
	AfxBeginThread(playThread, this);
}

void CExParrotDlg::OnBnClickedButtonControl2(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法停止喵！",L"提示喵");
		return;
	}
	player.stop();
}


void CExParrotDlg::OnBnClickedButtonControl3(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法播放喵！",L"提示喵");
		return;
	}
	AfxBeginThread(ThreadControlPlay, this);
}

UINT CExParrotDlg::ThreadControlPlay(void*context){
	CExParrotDlg*dlg = (CExParrotDlg*)context;
	dlg->player.play(dlg->au);
	return 0;
}

void CExParrotDlg::OnBnClickedButtonControl4(){
	// TODO: 在此添加控件通知处理程序代码
	if(!recording){
		loadReplace = rightBound-leftBound <= 0;	//未选择时为替换全部，否则替换选择区域
		newRecord = au.length == 0;
		AfxBeginThread(ThreadControlRecord, this);
	}else{
		recorder.stop();
		stream s;
		recorder.getData(s);
		audio newAd;
		newAd.create(s, 2, 44100);
		if(1/*如果录音过小·自动放大录音*/){
			long maxEnergy = 0;
			for(int i = 0;i<newAd.length;i++){
				long a1 = abs((long)newAd[i].value[0]);
				long a2 = abs((long)newAd[i].value[1]);
				if(a1 > maxEnergy)
					maxEnergy = a1;
				if(a2 > maxEnergy)
					maxEnergy = a2;
			}
			if(maxEnergy < 16384){
				double powerup = 16384.f / maxEnergy;
				newAd.mult(powerup);
			}
		}
		recording = false;
		if(newRecord){
			au.destory();
			au = newAd;
			stream s1;
			makeWAV(newAd, s1);
			no.push(s1, "new_record.ogg");
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(no.count,L"new_record.ogg", getIconSND(VWAVE));
		}else if(loadReplace){
			au.destory();
			au = newAd;
		}else{
			audio au1, au2, au3;
			au.clip(au1, 0, leftBound);
			au.clip(au3, rightBound, au.length - 1);
			au.destory();
			au = au1;
			au.cat(newAd);
			au.cat(au3);
			rightBound = leftBound + newAd.length;
		}
		draw();
		MessageBox(L"录音完毕喵！",L"提示喵");
		saveAlert = true;
		updateInfo();
		GET_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowText(L"录音");
	}
}

UINT CExParrotDlg::ThreadControlRecord(void*context){
	CExParrotDlg*dlg = (CExParrotDlg*)context;
	dlg->recorder.initFormat(2, 16, 44100, 88200, 4, 0);
	if(!dlg->recorder.record()){
		dlg->MessageBox(L"没找到录音设备喵！无法录音喵！",L"提示喵");
		return 0;
	}
	dlg->recording = true;
	GET_DLG_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowText(L"停止录音");
	return 0;
}

void CExParrotDlg::OnBnClickedButtonControl5(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法导入喵！",L"提示喵");
		return;
	}
	loadReplace = false;
	if(rightBound-leftBound <= 0){
		if(IDNO == MessageBox(L"当前未对音频段进行选择喵！如果继续的话，将会替换整个音频喵，确定喵？",L"提示喵")){
			return;
		}
		loadReplace = true;
	}
	CString defExt = _T("支持的音效文件(*.WAV,*.OGG)|*.WAV;*.OGG");
	CString extFilter = _T("支持的音效文件(*.WAV,*.OGG)|*.WAV;*.OGG|vorbis音效(*.OGG)|*.OGG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		loadPara = dlg.GetPathName();
		AfxBeginThread(ThreadControlLoad, this);
	}
	
}

UINT CExParrotDlg::ThreadControlLoad(void*context){
	CExParrotDlg*dlg = (CExParrotDlg*)context;
	stream s, sPCM;
	SNDversion sv;
	if(!s.loadFile(CStrToStr(dlg->loadPara))){
		dlg->MessageBox(L"读取失败喵！",L"提示喵");
		return 0U;
	}
	long r;
	s.resetPosition();
	s.readInt(r);
	s.resetPosition();
	if(r == 0x5367674F){
		sv = VVORBIS;//OggS
	}else if(r == 0x46464952){
		sv = VWAVE;//RIFF
	}else if((r & 0xFFFFFF) == 0x334449 || (r & 0xF0FF) == 0xF0FF){
		dlg->MessageBox(L"暂不支持MP3解码喵！",L"提示喵");
		return 0;
	}else{
		dlg->MessageBox(L"未能识别这个文件喵！",L"提示喵");
		return 0;
	}
	audio newAd;
	switch(sv){
	case VVORBIS:
		{
			dlg->bar.show(4);
			dlg->bar.setInfo(L"正在解码喵……", 0);
			OGG::OGGobject oo;
			if(!oo.load(s)){
				dlg->bar.hide();
				dlg->MessageBox(L"Ogg格式无效喵！",L"提示喵");
				return 0;
			}
			if(!oo.initDecoder()){
				dlg->bar.hide();
				dlg->MessageBox(L"Ogg解码失败喵！",L"提示喵");
				return 0;
			}
			loadOGG(newAd, oo);
			dlg->bar.hide();
			break;
		}
	case VMP3:
		dlg->MessageBox(L"暂不支持MP3解码喵！",L"提示喵");
		return 0;
	case VWAVE:
		{
			dlg->bar.show(4);
			dlg->bar.setInfo(L"正在解码喵……", 0);
			WAV::WAVobject wo;
			wo.load(s);
			loadWAV(newAd, wo);
			dlg->bar.hide();
			break;
		}
	default:
		dlg->MessageBox(L"未能识别这个文件喵！",L"提示喵");
		return 0;
	}
	//识别完成开始插入
	if(dlg->loadReplace){
		dlg->au.destory();
		dlg->au = newAd;
	}else{
		audio au1, au2, au3;
		dlg->au.clip(au1, 0, dlg->leftBound);
		dlg->au.clip(au3, dlg->rightBound, dlg->au.length - 1);
		dlg->au.destory();
		dlg->au = au1;
		dlg->au.cat(newAd);
		dlg->au.cat(au3);
		dlg->rightBound = dlg->leftBound + newAd.length;
	}
	dlg->draw();
	dlg->MessageBox(L"导入完毕喵！",L"提示喵");
	dlg->saveAlert = true;
	dlg->updateInfo();
	return 0;
}

void CExParrotDlg::OnBnClickedToolButton1(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法选择喵！",L"提示喵");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_SELECT;
}
void CExParrotDlg::OnBnClickedToolButton2(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法缩放喵！",L"提示喵");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_ZOOM;
}
void CExParrotDlg::OnBnClickedToolButton3(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法拖动喵！",L"提示喵");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_DRAG;
}
void CExParrotDlg::OnBnClickedToolButton4(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法选择喵！",L"提示喵");
		return;
	}
	rightBound = leftBound;
	leftBound = 0;
	draw();
}
void CExParrotDlg::OnBnClickedToolButton5(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法选择喵！",L"提示喵");
		return;
	}
	leftBound = rightBound;
	rightBound = au.length - 1;
	draw();
}
void CExParrotDlg::OnBnClickedToolButton6(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法选择喵！",L"提示喵");
		return;
	}
	leftBound = 0;
	rightBound = au.length - 1;
	draw();
}
void CExParrotDlg::OnBnClickedToolButton7(){
	//删除
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法删除喵！",L"提示喵");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"请选择一段音频喵！",L"提示喵");
		return;
	}
	audio au1,au2;
	au.clip(au1, 0, leftBound);
	au.clip(au2, rightBound, au.length-1);
	au.destory();
	au = au1;
	au.cat(au2);
	rightBound = leftBound;
	saveAlert = true;
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton8(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法调节喵！",L"提示喵");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"请选择一段音频喵！",L"提示喵");
		return;
	}
	TinyAdjustVolume dlg;
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	if(true){
		TinyAdjustVolume dlg;
		long maxEnergy = 0;
		for(int i = 0;i<au2.length;i++){
			long a1 = abs((long)au2[i].value[0]);
			long a2 = abs((long)au2[i].value[1]);
			if(a1 > maxEnergy)
				maxEnergy = a1;
			if(a2 > maxEnergy)
				maxEnergy = a2;
		}
		dlg.maxEnergy = maxEnergy;
		if(dlg.DoModal() == IDOK){
			au2.mult(dlg.rate);
		}else{
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	saveAlert = true;
	updateInfo();
	draw();

}
void CExParrotDlg::OnBnClickedToolButton9(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法调节喵！",L"提示喵");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"请选择一段音频喵！",L"提示喵");
		return;
	}
	audio au1,au2,au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	au2.applayFadeIn(au2.length);
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	saveAlert = true;
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton10(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法调节喵！",L"提示喵");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"请选择一段音频喵！",L"提示喵");
		return;
	}
	audio au1,au2,au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	au2.applayFadeOut(au2.length);
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	saveAlert = true;
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton11(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法翻转喵！",L"提示喵");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"请选择一段音频喵！",L"提示喵");
		return;
	}
	audio au1,au2,au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	au2.reverse();
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	saveAlert = true;
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton12(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法调节喵！",L"提示喵");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"请选择一段音频喵！",L"提示喵");
		return;
	}
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	if(true){
		TinyStretch dlg;
		long len = au2.length;
		dlg.originLen = len;
		dlg.sampleRate = au2.sampleRate;
		if(dlg.DoModal() == IDOK){
			au2.zoom(dlg.rate);
		}else{
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	saveAlert = true;
	updateInfo();
	draw();
}


void CExParrotDlg::OnBnClickedToolButton13(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法调节喵！",L"提示喵");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"请选择一段音频喵！",L"提示喵");
		return;
	}
	TinyAdjustVolume dlg;
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	if(true){
		TinyEcho dlg;
		long len = au2.length;
		if(dlg.DoModal() == IDOK){
			audio au21, au22;
			au2.echo(dlg.times, au.getPos(dlg.offset), dlg.attenu);
			au2.clip(au21, 0, len);
			au2.clip(au22, len, au2.length - 1);
			len = au2.length;
			au2.destory();
			au2 = au21;
			if(au3.length < au22.length){
				au3.expand(au22.length);
			}
			au3.mixWith(au22, 1.f, 0);
			rightBound = leftBound + len;
		}else{
			return;
		}
	}
	
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	saveAlert = true;
	updateInfo();
	draw();
}


void CExParrotDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rc;
	GetClientRect(rc);
	if(sizing){
		adjustWindow(rc.Width(), rc.Height());
		draw();
		OnMouseMove(0, CPoint(0,0));
		Invalidate();
		sizing = 0;
	}
	// TODO: 在此处添加消息处理程序代码
}


void CExParrotDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	if(fwSide == WMSZ_LEFT || fwSide ==WMSZ_TOPLEFT || fwSide ==WMSZ_BOTTOMLEFT){
		if(pRect->right-pRect->left<=920){
			pRect->left = pRect->right-920;
		}
	}else{
		if(pRect->right-pRect->left<=920){
			pRect->right = pRect->left+920;
		}
	}
	if(fwSide == WMSZ_TOP || fwSide ==WMSZ_TOPLEFT || fwSide ==WMSZ_TOPRIGHT){
		if(pRect->bottom-pRect->top<=640){
			pRect->top = pRect->bottom-640;
		}
	}else{
		if(pRect->bottom-pRect->top<=640){
			pRect->bottom = pRect->top+640;
		}
	}
	sizing = 1;
	CDialogEx::OnSizing(fwSide, pRect);
	// TODO: 在此处添加消息处理程序代码
}

BOOL CExParrotDlg::getMouseAxis(point &pt){
	CPoint myPoint = getWinMouseAxis();
	point xy(myPoint.x-530, myPoint.y-10);
	pt = xy;
	
	return myPoint.x >= 530 && myPoint.y >= 10 && myPoint.x <= width - 10 && myPoint.y <= height - 40;
}
CPoint CExParrotDlg::getWinMouseAxis(){
	CPoint myPoint;
    GetCursorPos(&myPoint); //鼠标位置
	ScreenToClient(&myPoint);
	return myPoint;
}
BOOL CExParrotDlg::getMousePos(longex &pos){
	point pt;
	getMouseAxis(pt);
	pos = dispLeftBound + pt.X * (dispRightBound - dispLeftBound) / (width - 540);
	return pt.X >= 0;
}
void CExParrotDlg::OnLButtonDown(UINT nFlags, CPoint pt){
	CDialogEx::OnLButtonDown(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_LEFT_PRESS, mousePt);
	}
}
void CExParrotDlg::OnRButtonDown(UINT nFlags, CPoint pt){
	CDialogEx::OnRButtonDown(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_RIGHT_PRESS, mousePt);
	}
}
void CExParrotDlg::OnMouseMove(UINT nFlags, CPoint pt){
	CDialogEx::OnMouseMove(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		//TRACE(NumToCStr(mousePt.X)+L","+NumToCStr(mousePt.Y)+L"\r\n");
		longex pt;
		getMousePos(pt);
		GET_CTRL(CEdit, IDC_EDIT_RANGE2)->SetWindowText(L"滑鼠:"+DoubleToCStr(0.001F*au.getTime(pt))+L"s");
		OnMouseEventCanvas(canvasOperatePara.canvasOperating ? CANVAS_MOUSE_LEFT_DRAG : CANVAS_MOUSE_MOVE, mousePt);
	}else{
		OnMouseEventCanvas(canvasOperatePara.canvasOperating ? CANVAS_MOUSE_LEFT_RELEASE : CANVAS_MOUSE_MOVE, mousePt);
	}
}
void CExParrotDlg::OnLButtonUp(UINT nFlags, CPoint pt){
	CDialogEx::OnLButtonUp(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_LEFT_RELEASE, mousePt);
	}
}

void CExParrotDlg::OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt){
	CHECK_VALID(crtSNDid >= 0);
	switch(canvasOperatePara.canvasOperation){
	case CANVAS_SELECT:
		//选择
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 1;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.firstPos = 0;
			{
				longex pos;
				getMousePos(pos);
				leftBound = pos;
				canvasOperatePara.firstPos = pos;
			}
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			{
				longex pos;
				getMousePos(pos);
				if(pos<canvasOperatePara.firstPos){
					rightBound = canvasOperatePara.firstPos;
					leftBound = pos;
				}else{
					leftBound =  canvasOperatePara.firstPos;
					rightBound = pos;
				}
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			dispLeftBound = 0;
			dispRightBound = au.length - 1;
			draw();
			break;
		}
		break;
	case CANVAS_DRAG:
		//拖动操作
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.firstPos = 0;
			{
				point pt;
				getMouseAxis(pt);
				canvasOperatePara.firstPos = pt.X;
				canvasOperatePara.oldDispLeftBound = dispLeftBound;
				canvasOperatePara.oldDispRightBound = dispRightBound;
			}
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			{
				point pt;
				getMouseAxis(pt);
				long xDelta = pt.X - canvasOperatePara.firstPos;
				longex xxDelta = xDelta * (canvasOperatePara.oldDispRightBound - canvasOperatePara.oldDispLeftBound) / (width - 540);
				dispLeftBound = canvasOperatePara.oldDispLeftBound - xDelta * (canvasOperatePara.oldDispRightBound - canvasOperatePara.oldDispLeftBound) / (width - 540);
				dispRightBound = canvasOperatePara.oldDispRightBound - xDelta * (canvasOperatePara.oldDispRightBound - canvasOperatePara.oldDispLeftBound) / (width - 540);
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			dispLeftBound = 0;
			dispRightBound = au.length - 1;
			draw();
			break;
		}
		break;
	case CANVAS_ZOOM:
		//缩放
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 3;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.firstPos = 0;
			{
				longex pos;
				getMousePos(pos);
				zoomBound1 = pos;
				zoomBound2 = pos;
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			{
				longex pos;
				getMousePos(pos);
				zoomBound2 = pos;
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			{
				longex pos;
				getMousePos(pos);
				zoomBound2 = pos;
				if(zoomBound1 != zoomBound2){
					dispLeftBound = MIN(zoomBound1, zoomBound2);
					dispRightBound = MAX(zoomBound1, zoomBound2);
				}
				zoomBound1 = 0;
				zoomBound2 = 0;
				draw();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			dispLeftBound = 0;
			dispRightBound = au.length - 1;
			draw();
			break;
		}
		break;
	}
}



void CExParrotDlg::OnBnClickedButtonSNDsearch(){
	CString str1,str2;
	GET_CTRL(CEdit, IDC_EDIT_SNDSEARCH)->GetWindowText(str1);
	int i;
	for (i = fndSNDid;i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount();i++){
		str2 = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndSNDid = i;
			int nItem = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetTopIndex(); 
			CRect rc;
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndSNDid - nItem)*rc.Height());
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->Scroll(sz);
			return;
		}
	}
	for (i = 0;i<fndSNDid;i++){
		str2 = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndSNDid = i;
			int nItem = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetTopIndex(); 
			CRect rc;
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndSNDid - nItem)*rc.Height());
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->Scroll(sz);
			return;
		}
	}
	MessageBox(L"没有找到路径名包含“"+str1+"”的音效喵！",L"提示喵");
}


void CExParrotDlg::OnToolDownload(){
	MOVEW(toolSPK);
	toolSPK.localAddr = profile.getDownloadPath();
	toolSPK.OnCbnSelchangeCombo2();
	toolSPK.ShowWindow(SW_SHOW);
}


BOOL CExParrotDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_MOUSEMOVE){
		m_ttc.RelayEvent(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
