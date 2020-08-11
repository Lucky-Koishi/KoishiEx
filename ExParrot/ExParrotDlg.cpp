
// ExParrotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ExParrotDlg.h"
#include "afxdialogex.h"
#include "TinyAdjustVolume.h"
#include "TinyAdjustSpeed.h"
#include "TinyStretch.h"
#include "TinyEcho.h"
#include "TinySetName(white).h"
#include "TinySNDSelect.h"
#include "ModalConflictWarning(white).h"
#include "ModalSaveWarning(white).h"
#include "ToolDownload(white).h"
#include <thread>
#include "ToolPiano.h"
#include "Music.h"

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
	SNDsaveAlert = false;
	NPKsaveAlert = false;
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
	ON_COMMAND(ID_MENU_SOUND_INERT_EMPTY, &CExParrotDlg::OnMenuSoundInertEmpty)
	ON_COMMAND(ID_MENU_SOUND_INERT_SND, &CExParrotDlg::OnMenuSoundInertSnd)
	ON_COMMAND(ID_MENU_SOUND_INERT_NPK, &CExParrotDlg::OnMenuSoundInertNPK)
	ON_COMMAND(ID_MENU_SOUND_INERT_FOLDER, &CExParrotDlg::OnMenuSoundInertFolder)
	ON_COMMAND(ID_MENU_SOUND_INERT_OTHER, &CExParrotDlg::OnMenuSoundInertOther)
	ON_COMMAND(ID_MENU_SOUND_INERT_EMPTY_BLANK, &CExParrotDlg::OnMenuSoundInertEmptyBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_SND_BLANK, &CExParrotDlg::OnMenuSoundInertSNDBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_NPK_BLANK, &CExParrotDlg::OnMenuSoundInertNPKBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_FOLDER_BLANK, &CExParrotDlg::OnMenuSoundInertFolderBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_OTHER_BLANK, &CExParrotDlg::OnMenuSoundInertOtherBlank)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_SND, &CExParrotDlg::OnMenuSoundReplaceSND)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_COPY, &CExParrotDlg::OnMenuSoundReplaceCopy)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_QUOTE, &CExParrotDlg::OnMenuSoundReplaceQuote)
	ON_COMMAND(ID_MENU_SOUND_INSERT_SND_PATCH, &CExParrotDlg::OnMenuSoundInsertSndPatch)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_COPY_PATCH, &CExParrotDlg::OnMenuSoundReplaceCopyPatch)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_QUOTE_PATCH, &CExParrotDlg::OnMenuSoundReplaceQuotePatch)
	ON_COMMAND(ID_MENU_SOUND_REMOVE, &CExParrotDlg::OnMenuSoundRemove)
	ON_COMMAND(ID_MENU_SOUND_REMOVE_PATCH, &CExParrotDlg::OnMenuSoundRemovePatch)
	ON_COMMAND(ID_MENU_SOUND_SAVE_NPK, &CExParrotDlg::OnMenuSoundSaveNPK)
	ON_COMMAND(ID_MENU_SOUND_SAVE_NPK_PATCH, &CExParrotDlg::OnMenuSoundSaveNPKPatch)
	ON_COMMAND(ID_MENU_SOUND_COPY_RESOURCE, &CExParrotDlg::OnMenuSoundCopyResource)
	ON_COMMAND(ID_MENU_SOUND_COPY_QUOTE, &CExParrotDlg::OnMenuSoundCopyQuote)
	ON_COMMAND(ID_MENU_SOUND_DEQUOTE, &CExParrotDlg::OnMenuSoundDequote)
	ON_COMMAND(ID_MENU_SOUND_DEQUOTE_PATCH, &CExParrotDlg::OnMenuSoundDequotePatch)
	ON_COMMAND(ID_MENU_SOUND_HIDE_PATCH, &CExParrotDlg::OnMenuSoundHidePatch)
	ON_COMMAND(ID_MENU_SOUND_SELECT_ALL, &CExParrotDlg::OnMenuSoundSelectAll)
	ON_COMMAND(ID_MENU_SOUND_SELECT_REVERSE, &CExParrotDlg::OnMenuSoundSelectReverse)
	ON_COMMAND(ID_MENU_SOUND_SELECT_HIGHLINE, &CExParrotDlg::OnMenuSoundSelectHighline)
	ON_COMMAND(ID_MENU_SOUND_EXTRACT, &CExParrotDlg::OnMenuSoundExtract)
	ON_COMMAND(ID_MENU_SOUND_EXTRACT_PATCH, &CExParrotDlg::OnMenuSoundExtractPatch)
	ON_COMMAND(ID_MENU_SOUND_RENAME, &CExParrotDlg::OnMenuSoundRename)
	ON_COMMAND(ID_MENU_SOUND_HIDE, &CExParrotDlg::OnMenuSoundHide)
	ON_COMMAND(ID_MENU_SOUND_MOVE_UP, &CExParrotDlg::OnMenuSoundMoveUp)
	ON_COMMAND(ID_MENU_SOUND_MOVE_DOWN, &CExParrotDlg::OnMenuSoundMoveDown)
	ON_COMMAND(ID_MENU_SOUND_SAVE, &CExParrotDlg::OnMenuSoundSave)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL1, &CExParrotDlg::OnBnClickedButtonControl1)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL2, &CExParrotDlg::OnBnClickedButtonControl2)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL3, &CExParrotDlg::OnBnClickedButtonControl3)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL4, &CExParrotDlg::OnBnClickedButtonControl4)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL5, &CExParrotDlg::OnBnClickedButtonControl5)
	ON_BN_CLICKED(IDC_TOOL_BUTTON1, &CExParrotDlg::OnBnClickedToolButton1)
	ON_BN_CLICKED(IDC_TOOL_BUTTON2, &CExParrotDlg::OnBnClickedToolButton2)
	ON_BN_CLICKED(IDC_TOOL_BUTTON3, &CExParrotDlg::OnBnClickedToolButton3)
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
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_IMGSEARCH, &CExParrotDlg::OnBnClickedButtonSNDsearch)
	ON_COMMAND(IDM_TOOL_DOWNLOAD, &CExParrotDlg::OnToolDownload)
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_TOOL_BUTTON14, &CExParrotDlg::OnBnClickedToolButton14)
	ON_BN_CLICKED(IDC_TOOL_BUTTON15, &CExParrotDlg::OnBnClickedToolButton15)
	ON_COMMAND(ID_TOOLS_PIANO, &CExParrotDlg::OnToolsPiano)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_WAV, &CExParrotDlg::OnMenuSoundTransformToWAV)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_OGG, &CExParrotDlg::OnMenuSoundTransformToOGG)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_WAV_PATCH, &CExParrotDlg::OnMenuSoundTransformToWAVPatch)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_OGG_PATCH, &CExParrotDlg::OnMenuSoundTransformToOGGPatch)
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
	m_buttonPic[13].LoadBitmap(IDB_BITMAP_TOOL14);
	m_buttonPic[14].LoadBitmap(IDB_BITMAP_TOOL15);
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
	GET_CTRL(CButton, IDC_TOOL_BUTTON14)->SetBitmap(m_buttonPic[13]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON15)->SetBitmap(m_buttonPic[14]);
	if(!m_logoPic.Attach((HBITMAP)::LoadImage(NULL,
		profile.getSupportPath() + L"LOGO.bmp",
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE|LR_DEFAULTSIZE))){
			m_logoPic.LoadBitmapW(IDB_BITMAP_LOGO);
	}
	GET_CTRL(CStatic, IDC_LOGO)->SetBitmap(m_logoPic);
#endif
	no.create();
	fileNPKname = L"newNPK.npk";

	m_ttc.Create(this);
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON1), L"选择");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON2), L"放大");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON3), L"拖动");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON4), L"选择左边");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON5), L"选择右边");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON6), L"全选");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON7), L"裁切");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON8), L"音量调节");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON9), L"淡入");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON10), L"淡出");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON11), L"反转");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON12), L"拉伸");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON13), L"回声");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON14), L"速度调节");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON15), L"音调调节");
	MP3image.create(1,1);
	MP3image.fill(profile.getAudioColor(4));

	StartThreadFunc(DrawPower, 0);
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
void CExParrotDlg::decodeAndPlay() {
	StartThreadFunc(DecodeAndPlay, 0);
}
void CExParrotDlg::draw(){
	if(rightBound - leftBound > 0){
		GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowText(L"左端:" + DoubleToCStr(0.001F*au.getTime(leftBound))+L"s");
		GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowText(L"右端:" + DoubleToCStr(0.001F*au.getTime(rightBound))+L"s");
	}else{
		GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowText(L"左端:" + DoubleToCStr(0.001F*au.getTime(0))+L"s");
		GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowText(L"右端:" + DoubleToCStr(0.001F*au.getLastTime())+L"s");
	}
	StartThreadFunc(Draw, 0);
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
void CExParrotDlg::adjustWindow(int w, int h){
	//调整窗口控件
	CHECK_VALID(w>=700);
	CHECK_VALID(h>=500);
	width = w;
	height = h;
	barWidth = (w-540);
	barPart1 = barWidth*30/45;
	barPart2 = barWidth*15/45;
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

	int delta = barPart1/15;
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
	GET_CTRL(CButton, IDC_TOOL_BUTTON14)->SetWindowPos(NULL,530+delta*13,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_TOOL_BUTTON15)->SetWindowPos(NULL, 530 + delta * 14, h - 10 - barHeight, delta, barHeight, SWP_NOZORDER);
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
void CExParrotDlg::updateSNDterm(int pos) {
	int li = no.checkLink(pos);
	if(li == pos) {
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(pos, 0, LVIF_IMAGE, NULL, getIconSND(no.SNDgetVersion(pos)), 0, 0, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(pos, 0, GetTail(StrToCStr(no.entry[pos].comment)));
	} else {
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(pos, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(pos, 0, GetTail(StrToCStr(no.entry[pos].comment)) + L"[" + GetTail(StrToCStr(no.entry[li].comment)) + L"]");
	}
}
void CExParrotDlg::updateInfo(){
	CString cstr;
	cstr = L"文件名："+GetTail(fileNPKname)+L"\r\n";
	cstr += L"大小："+NumToCStr(no.getSize())+L"字节\r\n";
	cstr += L"条目数："+NumToCStr(no.count);
	cstr += (crtSNDid  == -1) ? L"" : ( L"/"  + NumToCStr(crtSNDid));
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(cstr);
	cstr = SNDsaveAlert ? L"音效状态：已变动\r\n" : L"音效状态：未变动\r\n";
	cstr += L"声道数:" + NumToCStr(au.channel) + L"\r\n";
	cstr += L"采样频率:" + NumToCStr(au.sampleRate) + L"Hz\r\n";
	cstr += L"时长:" + DoubleToCStr(au.getLastTime() * 0.001f) + L"s";
	GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(cstr);
}
void CExParrotDlg::updateCommentInfo(const SNDversion &ver) {
	CString tempStr;
	switch(ver) {
	case SNDversion::VWAVE:
		tempStr = L"类别: WAV音频(PCM流)\r\n";
		break;
	case SNDversion::VVORBIS:
		tempStr = L"类别: Ogg音频\r\n编码器信息: \r\n" + StrToCStr(OGGcopyRight.vendorInfo) + L"\r\n";
		tempStr += L"其他信息:" + NumToCStr(OGGcopyRight.userInfo.size()) + L"条\r\n";
		if(OGGcopyRight.vendorInfo.size() > 0) {
			for(int i = 0; i < OGGcopyRight.userInfo.size(); i++) {
				CString userInfoStr = StrToCStr(OGGcopyRight.userInfo[i]);
				userInfoStr.Replace(L"=", L": ");
				tempStr += userInfoStr + L"\r\n";
			}
		}
		break;
	case SNDversion::VMP3:
		tempStr = L"类别: MP3\r\n";
		tempStr += L"MP3解码还没有写好喵。";
		break;
	case SNDversion::VIMAGE:
		tempStr = L"类别: IMG对象\r\n";
		tempStr += L"请使用恋恋のEx黑猫版打开这个对象喵。";
		break;
	default:
		tempStr = L"类别: 未识别\r\n";
		break;
	}
	GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(tempStr);
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
void CExParrotDlg::resetBound() {
	dispLeftBound = 0;
	dispRightBound = MAX(1, au.length - 1);
	leftBound = 0;
	rightBound = 0;
}
/////////////////////
DefineThreadFunc(CExParrotDlg, play, BOOL) {
	if((!para) || rightBound - leftBound <= 0) {
		player.play(au);
	} else {
		audio ad = au;
		ad.clip(leftBound, rightBound);
		player.play(ad);
	}
}
DefineThreadFunc(CExParrotDlg, RecordStart, BOOL) {
	recorder.initFormat(2, 16, 44100, 88200, 4, 0);
	if(!recorder.record()) {
		MessageBox(L"没找到录音设备喵！无法录音喵！", L"提示喵");
		return;
	}
	recording = true;
	GET_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowText(L"停止录音");
}
DefineThreadFunc(CExParrotDlg, RecordFinish, BOOL) {
	stream s;
	audio newAd;
	if(processing)
		return;
	processing = 1;
	recorder.stop();
	recorder.getData(s);
	newAd.create(s, 2, 44100);
	if(1/*如果录音过小·自动放大录音*/) {
		long maxEnergy = 0;
		for(int i = 0; i<newAd.length; i++) {
			long a1 = abs((long)newAd[i].value[0]);
			long a2 = abs((long)newAd[i].value[1]);
			if(a1 > maxEnergy)
				maxEnergy = a1;
			if(a2 > maxEnergy)
				maxEnergy = a2;
		}
		if(maxEnergy < 16384) {
			double powerup = 16384.f / maxEnergy;
			newAd.mult(powerup);
		}
	}
	recording = false;
	if(au.length == 0/*如果当前音效长度为0，即不存在，新建音效*/) {
		au.destory();
		au = newAd;
		stream sFile;
		setCopyRight(CRO_CREATE);
		encodeTo(sFile);
		no.push(sFile, "new_record.ogg");
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(no.count, L"new_record.ogg", getIconSND(checkAudioFormat(sFile)));
	} else if(rightBound - leftBound <= 0 /*未选择边界，默认替换完整音效*/) {
		au.destory();
		au = newAd;
		setCopyRight(CRO_CREATE);
	} else /*有选择边界，则替换选择边界内音效*/{
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
	MessageBox(L"录音完毕喵！", L"提示喵");
	updateModified();
	updateInfo();
	GET_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowText(L"录音");
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, ReplaceSound, BOOL) {
	if(rightBound - leftBound <= 0 && IDNO == MessageBox(L"当前未对音频段进行选择喵！如果继续的话，将会替换整个音频喵，确定喵？", L"提示喵"))
		return;
	CFileDialog dlg(true, L"支持的音效文件(*.WAV,*.OGG)|*.WAV;*.OGG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"支持的音效文件(*.WAV,*.OGG)|*.WAV;*.OGG|vorbis音效(*.OGG)|*.OGG||", this);
	if(IDOK != dlg.DoModal())
		return;
	CString fileName = dlg.GetPathName();
	stream sFile;
	if(!sFile.loadFile(CStrToStr(fileName))) {
		MessageBox(L"读取失败喵！", L"提示喵");
		return;
	}
	SNDversion sv = checkAudioFormat(sFile);
	audio newAd;
	OGGvorbis::OGGobject newOo;
	WAV::WAVobject newWo;
	switch(sv) {
	case VVORBIS:
		bar.show(4);
		bar.setInfo(L"正在解码喵……", 0);
		if(!newOo.decodeAndMake(sFile, newAd)) {
			bar.hide();
			MessageBox(L"解码失败喵！", L"提示喵");
			return;
		}
		bar.hide();
		break;
	case VMP3:
		MessageBox(L"暂不支持MP3解码喵！", L"提示喵");
		return;
	case VWAVE:
		bar.show(4);
		bar.setInfo(L"正在解码喵……", 0);
		if(!newWo.decodeAndMake(sFile, newAd)) {
			bar.hide();
			MessageBox(L"解码失败喵！", L"提示喵");
			return;
		}
		bar.hide();
		break;
	default:
		MessageBox(L"未能识别这个文件喵！", L"提示喵");
		return;
	}
	//识别完成开始插入
	if(rightBound - leftBound <= 0) {
		au.destory();
		au = newAd;
	} else {
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
	MessageBox(L"导入完毕喵！", L"提示喵");
	updateModified();
	updateInfo();
}
DefineThreadFunc(CExParrotDlg, Draw, BOOL) {
	int canw = width - 540;
	int canh = height - 50;
	image canvas;
	makeGraph(canvas, canw, canh);
	int i, j;
	CImage img;
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i = 0; i<canw; i++) {
		for(j = 0; j<canh; j++) {
			*(pst + pit*j + 4 * i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4 * i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4 * i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC, 530, 10);
	img.Destroy();
	ReleaseDC(pDC);
	canvas.destory();
}
DefineThreadFunc(CExParrotDlg, DrawPower, BOOL) {
	long power[16] = {0};	//功率谱
	long cur[2] = {0};		//左右声道当前能量
	while(1) {
		if(recording) {
			cur[0] = recorder.energyLeft * 100 / 32767;
			cur[1] = recorder.energyRight * 100 / 32767;
			for(int i = 0; i<16; i++) {
				power[i] = recorder.freq[i] * 100 / 10000;
				if(power[i] > 100)
					power[i] = 100;
			}
		} else if(player.idv != -1) {
			cur[0] = player.dv[player.idv].energyLeft * 100 / 32767;
			cur[1] = player.dv[player.idv].energyRight * 100 / 32767;
			for(int i = 0; i<16; i++) {
				power[i] = player.dv[player.idv].freq[i] * 100 / 10000;
				if(power[i] > 100)
					power[i] = 100;
			}
		}
		if(cur[0]>100)
			cur[0] = 100;
		if(cur[1]>100)
			cur[1] = 100;
		image mat;
		int canw = 520 - 170;
		int canh = height - 10 - 380;
		mat.create(canh, canw);
		mat.fill(color(0xFF, 0, 0, 0));
		for(int i = 0; i<16; i++) {
			colorHSV hsv = {i * 360 / 16, 1.0F, 1.0F};
			color clr;
			clr.useHSV(hsv);
			mat.filledRectangle(point(2 + 18 * i, canh - (canh - 5)*(power[i] + 2) / 100), point(17 + 18 * i, canh - 3), clr);
		}
		mat.filledRectangle(point(290, canh - (canh - 5)*(cur[0] + 2) / 100), point(290 + (canw - 296) / 2, canh - 3), profile.getAudioColor(3));
		mat.filledRectangle(point(293 + (canw - 296) / 2, canh - (canh - 5)*(cur[1] + 2) / 100), point(canw - 3, canh - 3), profile.getAudioColor(3));
		int i, j;
		CImage img;
		img.Create(canw, canh, 32);
		UCHAR* pst = (UCHAR*)img.GetBits();
		int pit = img.GetPitch();
		CDC *pDC = GetDC();
		for(i = 0; i<canw; i++) {
			for(j = 0; j<canh; j++) {
				*(pst + pit*j + 4 * i + 0) = mat[j][i].B;
				*(pst + pit*j + 4 * i + 1) = mat[j][i].G;
				*(pst + pit*j + 4 * i + 2) = mat[j][i].R;
			}
		}
		img.Draw(pDC->m_hDC, 170, 380);
		img.Destroy();
		ReleaseDC(pDC);
		//dlg->drawing = 0;
		mat.destory();
		Sleep(4);
	}
}
DefineThreadFunc(CExParrotDlg, DecodeAndPlay, BOOL) {
	int id = crtSNDid;
	stream s, sPCM;
	OGGvorbis::OGGobject oo;
	WAV::WAVobject wo;
	switch(no.SNDgetVersion(id)) {
	case VVORBIS:
		bar.show(4);
		bar.setInfo(L"正在解码喵……", 0);
		no.extract(crtSNDid, s);
		fileSNDname = StrToCStr(no.entry[id].comment);
		if(!oo.decodeAndMake(s, au)) {
			bar.hide();
			GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"该对象无法被解码喵！");
			updateCommentInfo(VSNDUKNOWN);
			MessageBox(L"解码失败喵！", L"提示喵");
			return;
		}
		OGGcopyRight = oo.comment;
		resetBound();
		updateInfo();
		updateCommentInfo(VVORBIS);
		bar.hide();
		draw();
		player.play(au);
		Sleep(10);
		return;
	case VMP3:
		GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"MP3解码还没写好喵！");
		updateCommentInfo(VMP3);
		return;
	case VWAVE:
		bar.show(4);
		bar.setInfo(L"正在解码喵……", 0);
		no.extract(crtSNDid, s);
		fileSNDname = StrToCStr(no.entry[id].comment);
		if(!wo.decodeAndMake(s, au)) {
			bar.hide();
			GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"该对象无法被解码喵！");
			updateCommentInfo(VSNDUKNOWN);
			MessageBox(L"解码失败喵！", L"提示喵");
			return;
		}
		resetBound();
		updateInfo();
		updateCommentInfo(VWAVE);
		bar.hide();
		draw();
		player.play(au);
		Sleep(10);
		return;
	default:
		GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"未能识别这个文件！");
		GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(L"类别:其他文件");
		return;
	}
}
/////////////////////
BOOL CExParrotDlg::setCopyRight(enumCopyRightOpera opera) {
	if(profile.artist.GetLength() == 0)
		return FALSE;
	if(profile.artist == L"noname")
		return FALSE;
	if(opera == CRO_NONE)
		return FALSE;
	if(opera == CRO_CLEAR) {
		OGGcopyRight.clearInfo();
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		OGGcopyRight.addInfo("created_date", localt);
	}
	if(opera == CRO_CREATE) {
		OGGcopyRight.clearInfo();
		str artist = CStrToStr(profile.artist);
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		OGGcopyRight.addInfo_author(artist, localt);
	}
	if(opera == CRO_MODIFIED) {
		str modifier = CStrToStr(profile.artist);
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		OGGcopyRight.addInfo_modifier(modifier, localt);
	}
	return TRUE;
}
BOOL CExParrotDlg::encodeTo(stream &dest) {
	return encodeTo(au, dest);
}
BOOL CExParrotDlg::encodeTo(const audio &newAd, stream &dest) {
	dest.release();
	if(profile.outputQuality == 0) {
		WAV::WAVobject wo;
		if(!wo.loadAndEncode(newAd, dest)) {
			MessageBox(L"无法将其转换为WAV喵！", L"提示喵");
			return FALSE;
		}
		return TRUE;
	} else if(profile.outputQuality <= 5) {
		OGGvorbis::OGGobject newOo;
		newOo.comment = OGGcopyRight;
		double dRate[5] = {-0.1, 0, 0.4, 0.7, 1};
		if(!newOo.loadAndEncode(newAd, dest,
			OGGvorbis::OGGencodeSetting('V', -1, dRate[profile.outputQuality - 1]))) {
			MessageBox(L"编码错误喵！\r\n" + StrToCStr(newOo.errorMessage), L"提示喵");
			return FALSE;
		}
		return TRUE;
	}
	MessageBox(L"无法从配置文件识别要转换的格式与品质喵！", L"提示喵");
	return FALSE;
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
std::vector<int> CExParrotDlg::getSelected(UINT listCtrlID, INT selectType) {
	std::vector<int> selected;
	CListCtrl *lc = GET_CTRL(CListCtrl, listCtrlID);
	switch(selectType) {
	case SINGLE_SELECT:
		if(listCtrlID == IDC_LIST_SND)
			selected.push_back(crtSNDid);
		return selected;
	case MULTI_SELECT:
		for(int k = 0; k<lc->GetItemCount(); k++)
			if(lc->GetCheck(k))
				selected.push_back(k);
		return selected;
	case ALL_SELECT:
		for(int k = 0; k<lc->GetItemCount(); k++)
			selected.push_back(k);
		return selected;
	}
	return selected;
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
	setCopyRight(CRO_MODIFIED);
	encodeTo(s);
	if(no.replace(crtSNDid, s)){
		MessageBox(L"音效修改完毕喵！",L"提示喵！");
		SNDsaveAlert = false;
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
	setCopyRight(CRO_CREATE);
	encodeTo(s);
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
			SNDsaveAlert = false;
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
			SNDsaveAlert = false;
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
	if(SNDsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_SND;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			SNDsaveAlert = FALSE;
			updateInfo();
			break;
		}
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
	if(SNDsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_SND;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			SNDsaveAlert = FALSE;
			updateInfo();
			break;
		}
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
	//切换OGG时提示保存
	if(SNDsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_SND;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			if(crtSNDid != row) {
				GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(crtSNDid, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
			}
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			SNDsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(row);
	if(row>=0){
		crtSNDid = row;
		fndSNDid = row;
		au.destory();
		decodeAndPlay();
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

void CExParrotDlg::OnBnClickedButtonControl1(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法播放喵！",L"提示喵");
		return;
	}
	StartThreadFunc(play, TRUE);
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
	StartThreadFunc(play, FALSE);
}

void CExParrotDlg::OnBnClickedButtonControl4(){
	// TODO: 在此添加控件通知处理程序代码
	if(!recording){
		StartThreadFunc(RecordStart, 0);
	}else{
		StartThreadFunc(RecordFinish, 0);
	}
}

void CExParrotDlg::OnBnClickedButtonControl5(){
	if(au.length == 0){
		MessageBox(L"当前没有音频喵！无法导入喵！",L"提示喵");
		return;
	}
	StartThreadFunc(ReplaceSound, 0);
}
//工具栏
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
	updateModified();
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
	updateModified();
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
	updateModified();
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
	updateModified();
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
	updateModified();
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
			rightBound = leftBound + au2.length;
		}else{
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
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
	updateModified();
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
void CExParrotDlg::updateModified() {
	SNDsaveAlert = TRUE;
	NPKsaveAlert = TRUE;
	updateInfo();
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
	ToolDownload(this).DoModal();
}


BOOL CExParrotDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_MOUSEMOVE){
		m_ttc.RelayEvent(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

DefineThreadFunc(CExParrotDlg, SoundInsertEmpty, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtSNDid;
	audio newAu(44100, 1, 44100);
	stream s;
	setCopyRight(CRO_CREATE);
	encodeTo(newAu, s);
	no.insert(insertPos, s, "new_sound.ogg");
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(insertPos, L"new_sound.ogg", getIconSND(checkAudioFormat(s)));
	s.release();
	newAu.destory();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundInsertSND, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtSNDid;
	CFileDialog dlg(true, L"音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3||", this);
	TinySetName dlgTiny(this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	dlgTiny.name = Slashing(GetTail(fileName));
	if(IDOK != dlgTiny.DoModal()) {
		processing = 0;
		return;
	}
	stream newStream;
	if(!newStream.loadFile(CStrToStr(fileName))) {
		MessageBox(L"这个文件无法打开喵！", L"提示喵");
		processing = 0;
		return;
	}
	no.insert(insertPos, newStream, CStrToStr(dlgTiny.name));
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(insertPos, GetTail(dlgTiny.name), getIconSND(no.SNDgetVersion(insertPos)));
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundInsertNPK, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtSNDid;
	int conflictMethod = 1;	// 0 替换 1 跳过(默认) 2 保留 3 保留并标记
	BOOL noAlarm = FALSE;		//不再提示
	CFileDialog dlg(true, L"NPK文件(*.NPK)|*.NPK", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"NPK文件(*.NPK)|*.NPK||", this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	NPKobject newNO;
	if(!newNO.loadFile(CStrToStr(fileName))) {
		MessageBox(L"这个NPK文件无法识别喵！", L"提示喵");
		processing = 0;
		return;
	}
	bar.show(newNO.count);
	int countFail = 0;
	int countSkip = 0;
	int countReplace = 0;
	int countSuccess = 0;
	int conflict = -1;		//查找冲突项
	for(int i = 0; i < newNO.count; i++) {
		bar.setInfo(L"当前插入" + GetTail(StrToCStr(newNO.entry[i].comment)) + L"喵……(成功" + NumToCStr(countSuccess) + L"个,跳过" + NumToCStr(countSkip) + L"个,替换" + NumToCStr(countReplace) + L"个,失败" + NumToCStr(countFail) + L"个)", i);
		stream newStream;
		if(!newNO.extract(i, newStream)) {
			countFail++;
			continue;
		}
		//检测冲突项
		if(TRUE) {
			conflict = -1;
			for(int j = 0; j<no.count; j++) {
				CString s1 = GetTail(StrToCStr(newNO.entry[i].comment));
				CString s2 = GetTail(StrToCStr(no.entry[j].comment));
				if(s1 == s2) {
					conflict = j;
					break;
				}
			}
		}
		if(!noAlarm && conflict > 0) {
			ModalConflictWarning dlgWarning(this);
			dlgWarning.conflictName = StrToCStr(newNO.entry[i].comment);
			dlgWarning.DoModal();
			noAlarm = dlgWarning.noAlarm;
			conflictMethod = dlgWarning.method;
		}
		if(conflict < 0) {
			no.insert(insertPos + countSuccess, newStream, newNO.entry[i].comment);
			countSuccess++;
		} else {
			switch(conflictMethod) {
			case 0:
				//替换
				no.replace(conflict, newStream);
				countReplace++;
				break;
			case 1:
				//跳过
				countSkip++;
				break;
			case 2:
				//保留
				no.insert(insertPos + countSuccess, newStream, newNO.entry[i].comment);
				countSuccess++;
				break;
			case 3:
				//保留并改名
				no.insert(insertPos + countSuccess, newStream, newNO.entry[i].comment + "(new)");
				countSuccess++;
				break;
			}
		}
	}
	MessageBox(L"导入完毕喵！总" + NumToCStr(newNO.count) + L"个,添加" + NumToCStr(countSuccess) + L"个,跳过" + NumToCStr(countSkip) + L"个,替换" + NumToCStr(countReplace) + L"个,失败" + NumToCStr(countFail) + L"个喵！", L"提示喵");
	bar.hide();
	updateSNDlist();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundInsertFolder, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtSNDid;
	CFileFind fileFind;
	std::vector<CString> fileList;
	std::vector<CString> pathList;
	CString folderName;
	CALL_FOLDER_DIALOG(folderName, L"选择文件夹喵", L"提示喵", L"并不是有效的文件夹喵");
	if(folderName.GetLength() == 0) {
		processing = 0;
		return;
	}
	folderName += L"\\*.*";
	BOOL ret = fileFind.FindFile(folderName);
	while(ret) {
		ret = fileFind.FindNextFile();
		fileList.push_back(fileFind.GetFileName());
		pathList.push_back(fileFind.GetFilePath());
	}
	NPKobject newNO;
	stream newStream;
	int countNPK = 0;
	int countNPKSND = 0;
	int countSND = 0;
	int totalSuccess = 0;
	int conflictMethod = 1;	// 0 替换 1 跳过(默认) 2 保留 3 保留并标记
	BOOL noAlarm = FALSE;		//不再提示
	bar.show(100);
	for(int fileID = 0; fileID<pathList.size(); fileID++) {
		if(fileList[fileID].Right(4) == L".npk" || fileList[fileID].Right(4) == L".NPK") {
			if(!newNO.loadFile(CStrToStr(pathList[fileID]))) {
				continue;
			}
			int countFail = 0;
			int countSkip = 0;
			int countReplace = 0;
			int countSuccess = 0;
			int conflict = -1;
			bar.setMax(newNO.count);
			for(int i = 0; i<newNO.count; i++) {
				bar.setInfo(L"当前插入" + fileList[fileID] +
							L"中的" + GetTail(StrToCStr(newNO.entry[i].comment)) +
							L"喵……(成功" + NumToCStr(countSuccess) +
							L"个,跳过" + NumToCStr(countSkip) +
							L"个,替换" + NumToCStr(countReplace) +
							L"个,失败" + NumToCStr(countFail) +
							L"个)", i);
				if(!newNO.extract(i, newStream)) {
					countFail++;
					continue;
				}
				if(TRUE) {
					conflict = -1;
					for(int j = 0; j<no.count; j++) {
						CString s1 = GetTail(StrToCStr(newNO.entry[i].comment));
						CString s2 = GetTail(StrToCStr(no.entry[j].comment));
						if(s1 == s2) {
							conflict = j;
							break;
						}
					}
				}
				if(!noAlarm && conflict > 0) {
					ModalConflictWarning dlgWarning(this);
					dlgWarning.conflictName = StrToCStr(newNO.entry[i].comment);
					dlgWarning.DoModal();
					noAlarm = dlgWarning.noAlarm;
					conflictMethod = dlgWarning.method;
				}
				if(conflict < 0) {
					no.insert(insertPos + totalSuccess, newStream, newNO.entry[i].comment);
					countSuccess++;
					totalSuccess++;
				} else {
					switch(conflictMethod) {
					case 0:
						//替换
						no.replace(conflict, newStream);
						countReplace++;
						break;
					case 1:
						//跳过
						countSkip++;
						break;
					case 2:
						//保留
						no.insert(insertPos + countSuccess, newStream, newNO.entry[i].comment);
						countSuccess++;
						totalSuccess++;
						break;
					case 3:
						//保留并改名
						no.insert(insertPos + countSuccess, newStream, newNO.entry[i].comment + "(new)");
						countSuccess++;
						totalSuccess++;
						break;
					}
				}
				newStream.release();
			}
			newNO.release();
			countNPK++;
			countNPKSND += countSuccess;
		}
		if(fileList[fileID].Right(4) == L".ogg" || fileList[fileID].Right(4) == L".OGG") {
			if(!newStream.loadFile(CStrToStr(pathList[fileID]))) {
				continue;
			}
			bar.setInfo(L"当前插入" + fileList[fileID] + L"喵……", 0);
			CString newPathName = Slashing(fileList[fileID]);
			no.insert(insertPos + totalSuccess, newStream, CStrToStr(newPathName));
			totalSuccess++;
			newStream.release();
			countSND++;
		}
	}
	MessageBox(L"导入完毕喵！成功导入了" + NumToCStr(countSND) + L"个外部SND对象喵，并从" + NumToCStr(countNPK) + L"个NPK文件中导入了" + NumToCStr(countNPKSND) + L"个SND对象喵。", L"提示喵");
	bar.hide();
	updateSNDlist();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundInsertOther, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtSNDid;
	CFileDialog dlg(true, L"所有文件(*.*)|*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"所有文件文件(*.*)|*.*||", this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	no.insert(insertPos, CStrToStr(fileName), CStrToStr(GetTail(fileName)));
	updateSNDlist();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundReplaceExtern, DWORD) {
	processing = 1;
	CFileDialog dlg(TRUE, L"音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3||", this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	stream s;
	if(!s.loadFile(CStrToStr(dlg.GetPathName()))) {
		MessageBox(L"无法读取的文件喵！", L"提示喵");
		processing = 0;
		return;
	}
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在替换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.replace(id, s);
		updateSNDterm(id);
	}
	MessageBox(L"替换完毕喵！");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundReplaceLocal, DWORD) {
	processing = 1;
	TinySNDSelect dlg;
	dlg.listStr.clear();
	dlg.defaultSelected = 0;
	for(int i = 0; i < no.count; i++)
		dlg.listStr.push_back(no.entry[i].comment);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	stream s;
	if(!no.extract(dlg.selected, s)) {
		MessageBox(L"无法提取的对象喵！", L"提示喵");
		processing = 0;
		return;
	}
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在替换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.replace2(id, s);
		updateSNDterm(id);
	}
	MessageBox(L"替换完毕喵！");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundReplaceQuote, DWORD) {
	processing = 1;
	TinySNDSelect dlg;
	dlg.listStr.clear();
	dlg.defaultSelected = 0;
	for(int i = 0; i < no.count; i++)
		dlg.listStr.push_back(no.entry[i].comment);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	stream s;
	if(!no.extract(dlg.selected, s)) {
		MessageBox(L"无法提取的对象喵！", L"提示喵");
		processing = 0;
		return;
	}
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在替换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.modifyLink(id, dlg.selected);
		updateSNDterm(id);
	}
	MessageBox(L"替换完毕喵！");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundRemove, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[targetList.size() - i - 1];
		bar.setInfo(L"正在删除" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.remove(id);
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->DeleteItem(id);
	}
	bar.hide();
	updateInfo();
	crtSNDid = -1;
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundExtract, DWORD) {
	processing = 1;
	CString filePath = profile.getOutputPath(fileNPKname);
	CString fileName;
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在提取" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		fileName = filePath + Underlining(StrToCStr(no.entry[id].comment));
		no.extract(id, CStrToStr(fileName));
	}
	MessageBox(L"全部提取完毕喵！已保存到" + profile.getOutputPath(fileNPKname) + L"了喵！", L"提示喵");
	bar.hide();
	updateInfo();
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundSaveAsNPK, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	CFileDialog dlg(FALSE, L"NPK文件(*.NPK)|*.NPK", L"newNPK.NPK", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"NPK文件(*.NPK)|*.NPK||", this);
	if(IDOK == dlg.DoModal()) {
		NPKobject newNo;
		newNo.create();
		bar.show(targetList.size() - 1);
		for(int i = 0; i<targetList.size(); i++) {
			int id = targetList[i];
			bar.setInfo(L"正在提取" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
			stream tempStr;
			no.extract(id, tempStr);
			newNo.push(tempStr, no.entry[id].comment);
		}
		newNo.saveFile(CStrToStr(dlg.GetPathName()));
		bar.hide();
		MessageBox(L"保存完毕喵！", L"提示喵");
	}
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundTransToWAV, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	int count = 0;
	int skip = 0;
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在转换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		stream sour, dest;
		if(no.SNDgetVersion(id) != VVORBIS) {
			skip++;
			continue;
		}
		no.extract(id, sour);
		audio aTemp;
		WAV::WAVobject wo;
		OGGvorbis::OGGobject oo;
		if(!oo.decodeAndMake(sour, aTemp))
			continue;
		if(!wo.loadAndEncode(aTemp, dest))
			continue;
		no.replace(id, dest);
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconSND(VWAVE), 0, 0, 0);
		count++;
	}
	bar.hide();
	NPKsaveAlert = true;
	processing = 0;
	MessageBox(L"尝试转换" + NumToCStr(targetList.size()) + L"个，成功" + NumToCStr(count) + L"个，跳过" + NumToCStr(skip) + L"个喵。", L"提示喵");
}
DefineThreadFunc(CExParrotDlg, SoundTransToOGG, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	int count = 0;
	int skip = 0;
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在转换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		stream sour,dest;
		if(no.SNDgetVersion(id) != VWAVE) {
			skip++;
			continue;
		}
		no.extract(id, sour);
		audio aTemp;
		WAV::WAVobject wo;
		OGGvorbis::OGGobject oo;
		if(!wo.decodeAndMake(sour, aTemp))
			continue;
		double dRate[6] = {0.4, -0.1, 0, 0.4, 0.7, 1};
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		oo.comment.addInfo("created_date", localt);
		if(!oo.loadAndEncode(aTemp, dest,
			OGGvorbis::OGGencodeSetting('V', -1, dRate[profile.outputQuality])))
			continue;
		no.replace(id, dest);
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconSND(VVORBIS), 0, 0, 0);
		count++;
	}
	bar.hide();
	NPKsaveAlert = true;
	processing = 0;
	MessageBox(L"尝试转换" + NumToCStr(targetList.size()) + L"个，成功" + NumToCStr(count) + L"个，跳过" + NumToCStr(skip) + L"个喵。", L"提示喵");
}
DefineThreadFunc(CExParrotDlg, SoundDequote, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在重新为" + GetTail(StrToCStr(no.entry[id].comment)) + L"分配数据喵……", i);
		if(no.delink(id)) {
			updateSNDterm(id);
		}
	}
	bar.hide();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExParrotDlg, SoundHide, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_SND, para);
	bar.show(targetList.size() - 1);
	audio emptyAu(1, 1);
	stream s;
	setCopyRight(CRO_MODIFIED);
	encodeTo(emptyAu, s);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[targetList.size() - 1 - i];
		bar.setInfo(L"正在隐藏" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.replace(id, s);
		updateSNDterm(id);
	}
	bar.hide();
	updateInfo();
	NPKsaveAlert = true;
	processing = 0;
}

void CExParrotDlg::OnMenuSoundInertEmpty() {
	StartThreadFunc(SoundInsertEmpty, 0);
}


void CExParrotDlg::OnMenuSoundInertSnd() {
	StartThreadFunc(SoundInsertSND, 0);
}


void CExParrotDlg::OnMenuSoundInertNPK() {
	StartThreadFunc(SoundInsertNPK, 0);
}


void CExParrotDlg::OnMenuSoundInertFolder() {
	StartThreadFunc(SoundInsertFolder, 0);
}


void CExParrotDlg::OnMenuSoundInertOther() {
	StartThreadFunc(SoundInsertOther, 0);
}


void CExParrotDlg::OnMenuSoundInertEmptyBlank() {
	StartThreadFunc(SoundInsertEmpty, 1);
}


void CExParrotDlg::OnMenuSoundInertSNDBlank() {
	StartThreadFunc(SoundInsertSND, 1);
}


void CExParrotDlg::OnMenuSoundInertNPKBlank() {
	StartThreadFunc(SoundInsertNPK, 1);
}


void CExParrotDlg::OnMenuSoundInertFolderBlank() {
	StartThreadFunc(SoundInsertFolder, 1);
}


void CExParrotDlg::OnMenuSoundInertOtherBlank() {
	StartThreadFunc(SoundInsertOther, 1);
}


void CExParrotDlg::OnMenuSoundReplaceSND() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundReplaceExtern, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceCopy() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundReplaceLocal, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceQuote() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundReplaceQuote, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundInsertSndPatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundReplaceExtern, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceCopyPatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundReplaceLocal, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceQuotePatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundReplaceQuote, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundRemove() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundRemove, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundRemovePatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundRemove, MULTI_SELECT);
}

void CExParrotDlg::OnMenuSoundExtract() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundExtract, SINGLE_SELECT);
}

void CExParrotDlg::OnMenuSoundExtractPatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundExtract, MULTI_SELECT);
}

void CExParrotDlg::OnMenuSoundSave() {
	CHECK_VALID(crtSNDid >= 0);
	CString defExt = _T("所有文件(*.*)|*.*");
	CString extFilter = _T("所有文件(*.*)|*.*||");
	CFileDialog dlg(false, defExt, Underlining(StrToCStr(no.entry[crtSNDid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		no.extract(crtSNDid, CStrToStr(dlg.GetPathName()));
		MessageBox(_T("保存完毕喵！"));
	}
}

void CExParrotDlg::OnMenuSoundSaveNPK() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundSaveAsNPK, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundSaveNPKPatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundSaveAsNPK, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundCopyResource() {
	CHECK_VALID(crtSNDid >= 0);
	stream sTemp;
	no.extract(crtSNDid, sTemp);
	no.insert(crtSNDid + 1, sTemp, no.entry[crtSNDid].comment + "(new)");
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(crtSNDid + 1, L"", getIconSND(0));
	updateSNDterm(crtSNDid + 1);
	NPKsaveAlert = true;
}


void CExParrotDlg::OnMenuSoundCopyQuote() {
	CHECK_VALID(crtSNDid >= 0);
	no.insertLink(crtSNDid + 1, crtSNDid, no.entry[crtSNDid].comment + "(new)");
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(crtSNDid + 1, L"", getIconSND(0));
	updateSNDterm(crtSNDid + 1);
	NPKsaveAlert = true;
}

void CExParrotDlg::OnMenuSoundRename() {
	CHECK_VALID(crtSNDid >= 0);
	ModalRename dlg;
	dlg.oldName = StrToCStr(no.entry[crtSNDid].comment);
	if(IDOK == dlg.DoModal()) {
		no.rename(crtSNDid, CStrToStr(dlg.newName));
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(crtSNDid, 0, GetTail(dlg.newName));
		fileSNDname = dlg.newName;
		NPKsaveAlert = true;
		updateInfo();
	}
}


void CExParrotDlg::OnMenuSoundDequote() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundDequote, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundDequotePatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundDequote, MULTI_SELECT);
}

void CExParrotDlg::OnMenuSoundHide() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundHide, SINGLE_SELECT);
}

void CExParrotDlg::OnMenuSoundHidePatch() {
	if(!getSelected(IDC_LIST_SND, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的音效对象喵！");
		return;
	}
	StartThreadFunc(SoundHide, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundSelectAll() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(); i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, TRUE);
}


void CExParrotDlg::OnMenuSoundSelectReverse() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(); i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, 1 - GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetCheck(i));
}


void CExParrotDlg::OnMenuSoundSelectHighline() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(); i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, TRUE);

}


void CExParrotDlg::OnMenuSoundMoveUp() {
	int row = crtSNDid;
	CHECK_VALID(row >= 1);
	NPKentry ne = no.entry[row];
	no.entry[row] = no.entry[row - 1];
	no.entry[row - 1] = ne;
	for(int i = 0; i <= 1; i++) {
		int id = row - i;
		int li = no.checkLink(id);
		if(li == id) {
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconSND(no.SNDgetVersion(id)), 0, 0, 0);
		} else {
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)
				+ L"[" + GetTail(StrToCStr(no.entry[li].comment)) + L"]"));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0);
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(row - 1);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
	crtSNDid = row - 1;
	NPKsaveAlert = true;
	updateInfo();
}


void CExParrotDlg::OnMenuSoundMoveDown() {
	int row = crtSNDid;
	CHECK_VALID(row >= 0);
	CHECK_VALID(row<no.count);
	NPKentry ne = no.entry[row];
	no.entry[row] = no.entry[row + 1];
	no.entry[row + 1] = ne;
	for(int i = 0; i <= 1; i++) {
		int id = row + i;
		int li = no.checkLink(id);
		if(li == id) {
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconSND(no.SNDgetVersion(id)), 0, 0, 0);
		} else {
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)
				+ L"[" + GetTail(StrToCStr(no.entry[li].comment)) + L"]"));
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItem(id, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0);
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(row + 1);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
	crtSNDid = row + 1;
	NPKsaveAlert = true;
	updateInfo();
}

void CExParrotDlg::OnClose() {
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if(NPKsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = SNDsaveAlert ? ModalSaveWarning::MODIFIED_SND_NPK : ModalSaveWarning::MODIFIED_NPK;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.saveFile(CStrToStr(fileNPKname));
			SNDsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		case ModalSaveWarning::RETURN_ALL_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			no.saveFile(CStrToStr(fileNPKname));
			SNDsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		}
	} else {

	}
	CDialogEx::OnClose();
}


void CExParrotDlg::OnDropFiles(HDROP hDropInfo) {
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// TODO: 外部文件拖入
	WCHAR szPath[MAX_PATH] = L"";
	UINT fileCount = ::DragQueryFile(hDropInfo, -1, NULL, NULL);		//获取拖进来的文件数
	UINT nChars = ::DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);		//获取拖进来的第一个文件
	CString fileName(szPath, nChars);									//获得we年明
	CString fmt = fileName.Right(4).MakeUpper();
	if(fmt == L".NPK") {
		if(fileCount > 1) {
			MessageBox(L"不可以拖动多个NPK进来喵！", L"提示喵");
			return;
		}
		if(NPKsaveAlert) {
			ModalSaveWarning ms;
			ms.alertType = SNDsaveAlert ? ModalSaveWarning::MODIFIED_SND_NPK : ModalSaveWarning::MODIFIED_NPK;
			ms.DoModal();
			switch(ms.returnType) {
			case ModalSaveWarning::RETURN_CANCEL:
				return;
			case ModalSaveWarning::RETURN_NO_SAVE:
				SNDsaveAlert = FALSE;
				NPKsaveAlert = FALSE;
				break;
			case ModalSaveWarning::RETURN_SAVE:
				no.saveFile(CStrToStr(fileNPKname));
				SNDsaveAlert = FALSE;
				NPKsaveAlert = FALSE;
				updateInfo();
				break;
			case ModalSaveWarning::RETURN_ALL_SAVE:
				stream s;
				au.make(s);
				no.replace(crtSNDid, s);
				no.saveFile(CStrToStr(fileNPKname));
				SNDsaveAlert = FALSE;
				NPKsaveAlert = FALSE;
				updateInfo();
				break;
			}
		}
		no.release();
		if(!no.loadFile(CStrToStr(fileName))) {
			MessageBox(L"读取失败喵！");
			return;
		}
		fileNPKname = fileName;
		updateSNDlist();
		if(no.count > 0) {
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(0);
			crtSNDid = 0;
		}
	} else if(fmt == L".OGG" || fmt == L".MP3" || fmt == L".WAV") {
		int success = 0;
		for(int i = 0; i<fileCount; i++) {
			if(i != 0) {
				memset(szPath, 0, MAX_PATH * sizeof(WCHAR));
				nChars = ::DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
				fileName = CString(szPath, nChars);
			}
			fmt = fileName.Right(4).MakeUpper();
			if(fmt == L".OGG" || fmt == L".MP3" || fmt == L".WAV") {
				stream sTemp;
				if(!sTemp.loadFile(CStrToStr(fileName)))
					continue;
				CString path = Slashing(GetTail(fileName));
				no.push(sTemp, CStrToStr(path));
				success++;
				GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->InsertItem(GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(), GetTail(path), getIconSND(no.SNDgetVersion(no.count - 1)));
				sTemp.release();
			}
			updateInfo();
		}
		MessageBox(L"已添加了" + NumToCStr(success) + L"个音效对象喵！", L"提示喵");
		NPKsaveAlert = TRUE;
	}
	CDialogEx::OnDropFiles(hDropInfo);
}


void CExParrotDlg::OnBnClickedToolButton14() {
	// TODO:  在此添加控件通知处理程序代码
	if(au.length == 0) {
		MessageBox(L"当前没有音频喵！无法调节喵！", L"提示喵");
		return;
	}
	if(rightBound - leftBound <= 0) {
		MessageBox(L"请选择一段音频喵！", L"提示喵");
		return;
	}
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length - 1);
	if(true) {
		TinyAdjustSpeed dlg;
		dlg.type = TinyAdjustSpeed::ADJUST_SPEED;
		long len = au2.length;
		if(dlg.DoModal() == IDOK) {
			au2.adjustSpeed(dlg.rate);
			rightBound = leftBound + au2.length;
		} else {
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}


void CExParrotDlg::OnBnClickedToolButton15() {
	// TODO:  在此添加控件通知处理程序代码
	if(au.length == 0) {
		MessageBox(L"当前没有音频喵！无法调节喵！", L"提示喵");
		return;
	}
	if(rightBound - leftBound <= 0) {
		MessageBox(L"请选择一段音频喵！", L"提示喵");
		return;
	}
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length - 1);
	if(true) {
		TinyAdjustSpeed dlg;
		dlg.type = TinyAdjustSpeed::ADJUST_PITCH;
		long len = au2.length;
		if(dlg.DoModal() == IDOK) {
			au2.adjustPitch(dlg.rate);
			rightBound = leftBound + au2.length;
		} else {
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}


void CExParrotDlg::OnToolsPiano() {
	// TODO:  在此添加命令处理程序代码
	ToolPiano dlg;
	dlg.DoModal();
}


void CExParrotDlg::OnMenuSoundTransformToWAV() {
	// TODO:  在此添加命令处理程序代码
	StartThreadFunc(SoundTransToWAV, 0);
}


void CExParrotDlg::OnMenuSoundTransformToOGG() {
	// TODO:  在此添加命令处理程序代码
	StartThreadFunc(SoundTransToOGG, 0);
}


void CExParrotDlg::OnMenuSoundTransformToWAVPatch() {
	// TODO:  在此添加命令处理程序代码
	StartThreadFunc(SoundTransToWAV, 1);
}


void CExParrotDlg::OnMenuSoundTransformToOGGPatch() {
	// TODO:  在此添加命令处理程序代码
	StartThreadFunc(SoundTransToOGG, 1);
}
