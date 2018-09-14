
// ExRabbitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "afxdialogex.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define DEBUG_CLOCK
// CExRabbitDlg 对话框
#ifdef DEBUG
#define UGLY			0
#define trace(x)		TRACE(L##x)
#else
#define UGLY 1
#define trace(x)
#endif

#ifdef DEBUG_CLOCK
#include <time.h>
clock_t start, end;
#define TIC start = clock()
#define TOC end = clock();TRACE(NumToCStr(end-start)+L"miniseconds.\n")
#else
#define TIC
#define TOC
#endif

CExRabbitDlg::CExRabbitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExRabbitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	width = 1200;
	height = 650;
	drawPara.texture = false;
	drawPara.realAxis = false;
	drawPara.indexMode = false;
	drawPara.entireTextureMode = false;
	drawPara.compareMode = false;
	drawPara.mixMode = LAY;
	useColorTable = false;//使用LIST并非TABLE
	useLog = false;
	fileNPKname = L"newNPK.npk";
	fileIMGname = L"newIMG.img";
	drawing = 0;
	extracting = 0;	//提取中
	converting = 0;	//转换中
	expanding = 0; //扩充中
	playing = 0; //播放中
	lazyTime = 0;
	sizing = 0;
	crtIMGid = -1;
	fndIMGid = -1;
	crtPICid = -1;
	crtTEXid = -1;
	saveAlert = false;
	bgColor = 0xFFCCBB;
	logFileName = CTime::GetTickCount().Format(L"操作日志_%Y年%m月%d日_%H小时%M分%S秒.txt");
	loadProfile();
}

void CExRabbitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnMenu);
	DDX_Control(pDX, IDC_EDIT_NPK, m_edNPKinfo);
	DDX_Control(pDX, IDC_LIST_IMG, m_lIMG);
	DDX_Control(pDX, IDC_COMBO_PRO, m_cbPro);
	DDX_Control(pDX, IDC_EDIT_BASEX, m_edX);
	DDX_Control(pDX, IDC_EDIT_BASEY, m_edY);
	DDX_Control(pDX, IDC_EDIT_IMGINFO, m_edIMGinfo);
	DDX_Control(pDX, IDC_LIST_CLR, m_lColor);
	DDX_Control(pDX, IDC_LIST_PIC, m_lPicture);
	DDX_Control(pDX, IDC_SPIN_X, m_spX);
	DDX_Control(pDX, IDC_SPIN_Y, m_spY);
	DDX_Control(pDX, IDC_LIST_DDS, m_lTexture);
	DDX_Control(pDX, IDC_LOGO, m_logo);
	DDX_Control(pDX, IDC_EDIT_INFO2, m_edInfo2);
	DDX_Control(pDX, IDC_EDIT_INFO3, m_edInfo3);
	DDX_Control(pDX, IDC_EDIT_INFO4, m_edInfo4);
	DDX_Control(pDX, IDC_EDIT_INFO5, m_edInfo5);
	DDX_Control(pDX, IDC_EDIT_INFO6, m_edInfo6);
	DDX_Control(pDX, IDC_EDIT_INFO7, m_edInfo7);
	DDX_Control(pDX, IDC_EDIT_INFO8, m_edInfo8);
	DDX_Control(pDX, IDC_EDIT_IMGSEARCH, m_edIMGsearch);
	DDX_Control(pDX, IDC_BUTTON_PALETTE, m_btnPalette);
}

BEGIN_MESSAGE_MAP(CExRabbitDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MENU, &CExRabbitDlg::OnBnClickedButtonMenu)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMClickListImg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMRClickListImg)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CLR, &CExRabbitDlg::OnNMClickListClr)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CLR, &CExRabbitDlg::OnNMRClickListClr)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMClickListTex)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMRClickListTex)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMClickListPic)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMRClickListPic)
	ON_CBN_SELCHANGE(IDC_COMBO_PRO, &CExRabbitDlg::OnCbnSelchangeComboPro)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_X, &CExRabbitDlg::OnDeltaposSpinX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_Y, &CExRabbitDlg::OnDeltaposSpinY)
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_MENU2, &CExRabbitDlg::OnBnClickedButtonMenu2)
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_IMG, &CExRabbitDlg::OnLvnKeydownListImg)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_PIC, &CExRabbitDlg::OnLvnKeydownListPic)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CLR, &CExRabbitDlg::OnLvnKeydownListClr)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_DDS, &CExRabbitDlg::OnLvnKeydownListTex)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_MIX_0, &CExRabbitDlg::OnMix0)
	ON_COMMAND(ID_MIX_1, &CExRabbitDlg::OnMix1)
	ON_COMMAND(ID_MIX_2, &CExRabbitDlg::OnMix2)
	ON_COMMAND(ID_MIX_3, &CExRabbitDlg::OnMix3)
	ON_COMMAND(ID_MIX_4, &CExRabbitDlg::OnMix4)
	ON_COMMAND(ID_MIX_5, &CExRabbitDlg::OnMix5)
	ON_COMMAND(ID_MIX_6, &CExRabbitDlg::OnMix6)
	ON_COMMAND(ID_MIX_7, &CExRabbitDlg::OnMix7)
	ON_COMMAND(ID_MIX_8, &CExRabbitDlg::OnMix8)
	ON_COMMAND(ID_MIX_9, &CExRabbitDlg::OnMix9)
	ON_COMMAND(ID_MIX_10, &CExRabbitDlg::OnMix10)
	ON_COMMAND(ID_MIX_11, &CExRabbitDlg::OnMix11)
	ON_COMMAND(ID_MIX_12, &CExRabbitDlg::OnMix12)
	ON_COMMAND(ID_MIX_13, &CExRabbitDlg::OnMix13)
	ON_COMMAND(ID_MIX_14, &CExRabbitDlg::OnMix14)
	ON_COMMAND(ID_MIX_15, &CExRabbitDlg::OnMix15)
	ON_COMMAND(ID_MIX_16, &CExRabbitDlg::OnMix16)
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_STN_CLICKED(IDC_LOGO, &CExRabbitDlg::OnStnClickedLogo)
	ON_BN_CLICKED(IDC_BUTTON_MENU3, &CExRabbitDlg::OnBnClickedButtonMenu3)
	ON_BN_CLICKED(IDC_BUTTON_PALETTE, &CExRabbitDlg::OnBnClickedButtonPalette)
	ON_BN_CLICKED(IDC_BUTTON_IMGSEARCH, &CExRabbitDlg::OnBnClickedButtonImgsearch)
	ON_COMMAND(IDM_MAIN_01, &CExRabbitDlg::OnMain01)
	ON_COMMAND(IDM_MAIN_02, &CExRabbitDlg::OnMain02)
	ON_COMMAND(IDM_MAIN_03, &CExRabbitDlg::OnMain03)
	ON_COMMAND(IDM_MAIN_04, &CExRabbitDlg::OnMain04)
	ON_COMMAND(IDM_MAIN_05, &CExRabbitDlg::OnMain05)
	ON_COMMAND(IDM_MAIN_06, &CExRabbitDlg::OnMain06)
	ON_COMMAND(IDM_MAIN_07, &CExRabbitDlg::OnMain07)
	ON_COMMAND(IDM_MAIN_08, &CExRabbitDlg::OnMain08)
	ON_COMMAND(IDM_MODIFY_01, &CExRabbitDlg::OnModify01)
	ON_COMMAND(IDM_MODIFY_02, &CExRabbitDlg::OnModify02)
	ON_COMMAND(IDM_TOOL_01, &CExRabbitDlg::OnTool01)
	ON_COMMAND(IDM_TOOL_02, &CExRabbitDlg::OnTool02)
	ON_COMMAND(IDM_TOOL_03, &CExRabbitDlg::OnTool03)
	ON_COMMAND(IDM_TOOL_04, &CExRabbitDlg::OnTool04)
	ON_COMMAND(IDM_IMG_01, &CExRabbitDlg::OnIMG01)
	ON_COMMAND(IDM_IMG_02, &CExRabbitDlg::OnIMG02)
	ON_COMMAND(IDM_IMG_03, &CExRabbitDlg::OnIMG03)
	ON_COMMAND(IDM_IMG_04, &CExRabbitDlg::OnIMG04)
	ON_COMMAND(IDM_IMG_05, &CExRabbitDlg::OnIMG05)
	ON_COMMAND(IDM_IMG_06, &CExRabbitDlg::OnIMG06)
	ON_COMMAND(IDM_IMG_07, &CExRabbitDlg::OnIMG07)
	ON_COMMAND(IDM_IMG_08, &CExRabbitDlg::OnIMG08)
	ON_COMMAND(IDM_IMG_09, &CExRabbitDlg::OnIMG09)
	ON_COMMAND(IDM_IMG_10, &CExRabbitDlg::OnIMG10)
	ON_COMMAND(IDM_IMG_11, &CExRabbitDlg::OnIMG11)
	ON_COMMAND(IDM_IMG_12, &CExRabbitDlg::OnIMG12)
	ON_COMMAND(IDM_IMG_13, &CExRabbitDlg::OnIMG13)
	ON_COMMAND(IDM_IMG_14, &CExRabbitDlg::OnIMG14)
	ON_COMMAND(IDM_IMG_15, &CExRabbitDlg::OnIMG15)
	ON_COMMAND(IDM_IMG_16, &CExRabbitDlg::OnIMG16)
	ON_COMMAND(IDM_IMG_17, &CExRabbitDlg::OnIMG17)
	ON_COMMAND(IDM_IMG_18, &CExRabbitDlg::OnIMG18)
	ON_COMMAND(IDM_IMG_19, &CExRabbitDlg::OnIMG19)
	ON_COMMAND(IDMR_IMG_01, &CExRabbitDlg::OnIMGR01)
	ON_COMMAND(IDM_FRM_01, &CExRabbitDlg::OnFRM01)
	ON_COMMAND(IDM_FRM_02, &CExRabbitDlg::OnFRM02)
	ON_COMMAND(IDM_FRM_03, &CExRabbitDlg::OnFRM03)
	ON_COMMAND(IDM_FRM_04, &CExRabbitDlg::OnFRM04)
	ON_COMMAND(IDM_FRM_05, &CExRabbitDlg::OnFRM05)
	ON_COMMAND(IDM_FRM_06, &CExRabbitDlg::OnFRM06)
	ON_COMMAND(IDM_FRM_07, &CExRabbitDlg::OnFRM07)
	ON_COMMAND(IDM_FRM_08, &CExRabbitDlg::OnFRM08)
	ON_COMMAND(IDM_FRM_09, &CExRabbitDlg::OnFRM09)
	ON_COMMAND(IDM_FRM_10, &CExRabbitDlg::OnFRM10)
	ON_COMMAND(IDM_FRM_11, &CExRabbitDlg::OnFRM11)
	ON_COMMAND(IDM_FRM_12, &CExRabbitDlg::OnFRM12)
	ON_COMMAND(IDM_FRM_13, &CExRabbitDlg::OnFRM13)
	ON_COMMAND(IDM_FRM_14, &CExRabbitDlg::OnFRM14)
	ON_COMMAND(IDM_FRM_15, &CExRabbitDlg::OnFRM15)
	ON_COMMAND(IDM_FRM_16, &CExRabbitDlg::OnFRM16)
	ON_COMMAND(IMDR_FRM01, &CExRabbitDlg::OnFRMR01)
	ON_COMMAND(IDMR_FRM02, &CExRabbitDlg::OnFRMR02)
	ON_COMMAND(IDM_TEX_01, &CExRabbitDlg::OnTEX01)
	ON_COMMAND(IDM_TEX_02, &CExRabbitDlg::OnTEX02)
	ON_COMMAND(IDM_TEX_03, &CExRabbitDlg::OnTEX03)
	ON_COMMAND(IDM_TEX_04, &CExRabbitDlg::OnTEX04)
	ON_COMMAND(IDM_TEX_05, &CExRabbitDlg::OnTEX05)
	ON_COMMAND(IDM_TEX_06, &CExRabbitDlg::OnTEX06)
	ON_COMMAND(IDM_TEX_07, &CExRabbitDlg::OnTEX07)
	ON_COMMAND(IDM_TEX_08, &CExRabbitDlg::OnTEX08)
	ON_COMMAND(IDM_TEX_09, &CExRabbitDlg::OnTEX09)
	ON_COMMAND(IDM_TEX_10, &CExRabbitDlg::OnTEX10)
	ON_COMMAND(IDMR_TEX_01, &CExRabbitDlg::OnTEXR01)
	ON_COMMAND(IDM_CLR_01, &CExRabbitDlg::OnCLR01)
	ON_COMMAND(IDM_CLR_02, &CExRabbitDlg::OnCLR02)
	ON_COMMAND(IDM_CLR_03, &CExRabbitDlg::OnCLR03)
	ON_COMMAND(IDM_CLR_04, &CExRabbitDlg::OnCLR04)
	ON_COMMAND(IDM_CLR_05, &CExRabbitDlg::OnCLR05)
	ON_COMMAND(IDM_CLR_06, &CExRabbitDlg::OnCLR06)
	ON_COMMAND(IDM_CLR_07, &CExRabbitDlg::OnCLR07)
	ON_COMMAND(IDM_CLR_08, &CExRabbitDlg::OnCLR08)
	ON_COMMAND(IDM_CLR_09, &CExRabbitDlg::OnCLR09)
	ON_COMMAND(IDM_CLR_10, &CExRabbitDlg::OnCLR10)
	ON_COMMAND(IDMR_CLR01, &CExRabbitDlg::OnCLRR01)
	ON_COMMAND(IDMR_CLR02, &CExRabbitDlg::OnCLRR02)
	ON_COMMAND(IDMR_CLR03, &CExRabbitDlg::OnCLRR03)
	ON_COMMAND(IDM_DISPLAY_01, &CExRabbitDlg::OnDisplay01)
	ON_COMMAND(IDM_DISPLAY_02, &CExRabbitDlg::OnDisplay02)
	ON_COMMAND(IDM_DISPLAY_03, &CExRabbitDlg::OnDisplay03)
	ON_COMMAND(IDM_DISPLAY_04, &CExRabbitDlg::OnDisplay04)
	ON_COMMAND(IDM_DISPLAY_05, &CExRabbitDlg::OnDisplay05)
	ON_COMMAND(IDM_DISPLAY_06, &CExRabbitDlg::OnDisplay06)
	ON_COMMAND(IDM_DISPLAY_07, &CExRabbitDlg::OnDisplay07)
	ON_COMMAND(IDM_TOOL_05, &CExRabbitDlg::OnTool05)
	ON_COMMAND(IDM_TOOL_06, &CExRabbitDlg::OnTool06)
	ON_COMMAND(IDM_IMG_0801, &CExRabbitDlg::OnIMG0801)
	ON_COMMAND(IDM_TOOL_07, &CExRabbitDlg::OnTool07)
	END_MESSAGE_MAP()
/////////

// CExRabbitDlg 消息处理程序


#define MOVEW(x) CRect rect;GetClientRect(&rect);ClientToScreen(&rect);x.SetWindowPos(this, rect.left+100, rect.top+100, 0, 0 , SWP_NOSIZE)
#define CREATEW(x,y) x.Create(y,this);x.ShowWindow(SW_HIDE)

BOOL CExRabbitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//////////////////////////////////
	SetWindowPos(NULL,0,0,width,height,SWP_NOZORDER|SWP_NOMOVE);
	CRect rc;
	GetClientRect(rc);
	adjustWindow(rc.Width(), rc.Height());
	// 控件大小调整
	CREATEW(dlgInsert,IDD_INSERT_DIALOG);
	CREATEW(dlgRename,IDD_RENAME_DIALOG);
	CREATEW(dlgTrasform,IDD_TRASFORM_DIALOG);
	CREATEW(dlgNew,IDD_NEW_DIALOG);
	CREATEW(dlgImportFrame, IDD_IMPORT_PNG_DIALOG);
	CREATEW(dlgAbout, IDD_ABOUT_DIALOG);
	CREATEW(dlgInsert2,IDD_INSERT2_DIALOG);
	CREATEW(dlgSetpara,IDD_SERPARA_DIALOG);
	CREATEW(dlgInsert3,IDD_INSERT3_DIALOG);
	CREATEW(dlgInsert4,IDD_INSERT4_DIALOG);
	CREATEW(dlgSetXY,IDD_SERXY_DIALOG);
	CREATEW(dlgExpand,IDD_EXPAND_DIALOG);
	CREATEW(dlgColor,IDD_COLOR_DIALOG);
	CREATEW(dlgSet,IDD_SET_DIALOG);
	CREATEW(dlgLoseBlack,IDD_LOSEBLACK_DIALOG);
	CREATEW(dlgBar,IDD_BAR_DIALOG);
	dlgBar.SetWindowPos(NULL, GetSystemMetrics(SM_CXSCREEN)/2-100, GetSystemMetrics(SM_CYSCREEN)/2-100,0,0,SWP_NOZORDER|SWP_NOSIZE);
	CREATEW(toolIMGSearch,IDD_TOOL_IMGSEARCH);
	CREATEW(toolAvatar,IDD_TOOL_AVATAR);
	CREATEW(toolDict,IDD_TOOL_DICT);
	CREATEW(toolIndexing,IDD_TOOL_INDEXING);
	CREATEW(toolSPK,IDD_TOOL_SPK);
	CREATEW(toolForceEx, IDD_TOOL_FORCEEXTRACT);

	m_lPicture.SetExtendedStyle(m_lPicture.GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_lColor.SetExtendedStyle(m_lColor.GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_lTexture.SetExtendedStyle(m_lTexture.GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_lIMG.SetExtendedStyle(m_lIMG.GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	
	m_lIMG.EasyInsertColumn(L"IMG名,200");
	m_edNPKinfo.SetWindowText(L"这里显示NPK文件的信息");
	m_edIMGinfo.SetWindowText(L"这里显示IMG文件的信息");
	m_edX.SetWindowText(L"0");
	m_edY.SetWindowText(L"0");
	m_edInfo8.SetWindowText(L"覆盖");
	switchIMGver(V2);
	
	AfxBeginThread(lazyThread, (PVOID)this);

	ioComp.create(V2);

	i_lIMG.Create(16,16, TRUE|ILC_COLOR24, 6, 1);
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON7));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON2));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON4));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON5));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON6));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON1));
	m_lIMG.SetImageList(&i_lIMG, LVSIL_SMALL);

	i_lPIC.Create(16,16, TRUE|ILC_COLOR24, 9, 1);
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON9));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON1));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON2));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON3));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON4));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON5));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON6));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON7));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON8));
	m_lPicture.SetImageList(&i_lPIC, LVSIL_SMALL);
	m_lTexture.SetImageList(&i_lPIC, LVSIL_SMALL);

	i_lCLR.Create(16,16, TRUE|ILC_COLOR24, 2, 1);
	i_lCLR.Add(AfxGetApp()->LoadIconW(IDI_CLR_ICON1));
	i_lCLR.Add(AfxGetApp()->LoadIconW(IDI_CLR_ICON2));
	m_lColor.SetImageList(&i_lCLR, LVSIL_SMALL);

#if UGLY
	m_logoPic.LoadBitmap(IDB_BITMAP1);
	m_logo.SetBitmap(m_logoPic);
	//updateRandomTitle();
#endif

	no.create();
	fileNPKname = L"newNPK.npk";
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExRabbitDlg::OnPaint()
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
		dc.FillSolidRect(rect,bgColor); 
#endif
		CDialogEx::OnPaint();
		draw(drawPara.texture);
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExRabbitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL CExRabbitDlg::adjustWindow(int w, int h){
	//调整窗口控件
	if(w<700 || h<500)
		return -1;
	width = w;
	height = h;
	m_logo.SetWindowPos(NULL,10,10,150,40,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU)->SetWindowPos(NULL,170,10,110,40,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU2)->SetWindowPos(NULL,290,10,110,40,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU3)->SetWindowPos(NULL,410,10,110,40,SWP_NOZORDER);
	m_edIMGsearch.SetWindowPos(NULL,10,60,100,25,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_IMGSEARCH)->SetWindowPos(NULL,120,60,40,25,SWP_NOZORDER);
	m_lIMG.SetWindowPos(NULL,10,95,150,h-105,SWP_NOZORDER);
	m_edNPKinfo.SetWindowPos(NULL,170,60,170,80,SWP_NOZORDER);
	m_edIMGinfo.SetWindowPos(NULL,350,60,170,80,SWP_NOZORDER);
	
	m_lColor.SetWindowPos(NULL,170,h-100,220,90,SWP_NOZORDER);
	m_btnPalette.SetWindowPos(NULL,400,h-100,120,60,SWP_NOZORDER);
	m_cbPro.SetWindowPos(NULL,400,h-30,120,20,SWP_NOZORDER);

	m_lTexture.SetWindowPos(NULL,170,150,350,(height-270)/2,SWP_NOZORDER);

	m_edInfo2.SetWindowPos(NULL,530,h-30,(w-540)/10,20,SWP_NOZORDER);
	m_edInfo3.SetWindowPos(NULL,530+(w-540)/10,h-30,(w-540)/10,20,SWP_NOZORDER);
	m_edInfo4.SetWindowPos(NULL,530+(w-540)*2/10,h-30,(w-540)/10,20,SWP_NOZORDER);
	m_edInfo5.SetWindowPos(NULL,530+(w-540)*3/10,h-30,(w-540)/10,20,SWP_NOZORDER);
	m_edInfo6.SetWindowPos(NULL,530+(w-540)*4/10,h-30,(w-540)/10+15,20,SWP_NOZORDER);
	m_edInfo7.SetWindowPos(NULL,530+(w-540)*5/10+15,h-30,(w-540)/10+15,20,SWP_NOZORDER);
	m_edInfo8.SetWindowPos(NULL,530+(w-540)*7/10+30,h-30,(w-540)/10,20,SWP_NOZORDER);
	m_edX.SetWindowPos(NULL,530+(w-540)*8/10+30,h-30,(w-540)/10-25,20,SWP_NOZORDER);
	m_edY.SetWindowPos(NULL,530+(w-540)*9/10+15,h-30,(w-540)/10-25,20,SWP_NOZORDER);
	m_spX.SetWindowPos(NULL,530+(w-540)*9/10+5,h-30,10,20,SWP_NOZORDER);
	m_spY.SetWindowPos(NULL,530+(w-540)-10,h-30,10,20,SWP_NOZORDER);
	switch(io.version){
	case V2:
		m_lPicture.SetWindowPos(NULL,170,150,350,h-160,SWP_NOZORDER);
		break;
	case V4:
		m_lPicture.SetWindowPos(NULL,170,150,350,h-260,SWP_NOZORDER);
		break;
	case V5:
		m_lPicture.SetWindowPos(NULL,170,150+(height-270)/2+10,350,(height-270)/2,SWP_NOZORDER);
		break;
	case V6:
		m_lPicture.SetWindowPos(NULL,170,150,350,h-260,SWP_NOZORDER);
		break;
	default:
		m_lPicture.SetWindowPos(NULL,170,150,350,h-160,SWP_NOZORDER);
		break;
	}
	return 0;
}

BOOL CExRabbitDlg::switchIMGver(IMGversion ver){
	//切换版本界面
	///////////////////////////////
	int i;
	switch(ver){
	case V2:
		m_lPicture.SetWindowPos(NULL,170,150,350,height-160,SWP_NOZORDER);
		m_lColor.ShowWindow(SW_HIDE);
		useColorTable = false;
		dlgColor.ShowWindow(SW_HIDE);
		m_lTexture.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_HIDE);
		m_btnPalette.ShowWindow(SW_HIDE);
		m_cbPro.ResetContent();
		m_cbPro.AddString(L"调色板方案0");
		m_cbPro.SetCurSel(0);
		m_lPicture.EasyInsertColumn(L"帧号,64,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
		break;
	case V4:
		m_lPicture.SetWindowPos(NULL,170,150,350,height-260,SWP_NOZORDER);
		m_lColor.ShowWindow(SW_SHOW);
		m_lTexture.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_SHOW);
		m_btnPalette.ShowWindow(SW_SHOW);
		m_cbPro.ResetContent();
		m_cbPro.AddString(L"调色板方案0");
		m_cbPro.SetCurSel(0);
		m_lPicture.EasyInsertColumn(L"帧号,64,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
		m_lColor.EasyInsertColumn(L"色号,64,RGBA数据,70");
		break;
	case V5:
		m_lPicture.SetWindowPos(NULL,170,150+(height-270)/2+10,350,(height-270)/2,SWP_NOZORDER);
		m_lTexture.SetWindowPos(NULL,170,150,350,(height-270)/2,SWP_NOZORDER);
		m_lColor.ShowWindow(SW_SHOW);
		m_cbPro.ShowWindow(SW_SHOW);
		m_btnPalette.ShowWindow(SW_SHOW);
		m_lTexture.ShowWindow(SW_SHOW);
		useColorTable = false;
		dlgColor.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_SHOW);
		m_cbPro.ResetContent();
		m_cbPro.AddString(L"调色板方案0");
		m_cbPro.SetCurSel(0);
		m_lPicture.EasyInsertColumn(L"帧号,64,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80,使用纹理集,400");
		m_lTexture.EasyInsertColumn(L"纹理集,64,颜色格式,90,尺寸,80");
		m_lColor.EasyInsertColumn(L"色号,64,RGBA数据,70");
		break;
	case V6:
		m_lPicture.SetWindowPos(NULL,170,150,350,height-260,SWP_NOZORDER);
		m_lColor.ShowWindow(SW_SHOW);
		m_lTexture.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_SHOW);
		m_btnPalette.ShowWindow(SW_SHOW);
		m_lPicture.EasyInsertColumn(L"帧号,64,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
		m_lColor.EasyInsertColumn(L"色号,64,RGBA数据,70");
		m_cbPro.ResetContent();
		for(i = 0;i<io.paletteData.getCount();i++)
			m_cbPro.AddString(L"调色板方案"+NumToCStr(i));
		if(io.paletteData.getCount()>0){
			m_cbPro.SetCurSel(0);
		}
		break;
	}
	return 0;
}

BOOL CExRabbitDlg::updateIMGlist(){
	// 更新IMG列表
	/////////////////////////////
	updateNPKInfo();
	m_lIMG.DeleteAllItems();
	for(int i = 0;i<no.count;i++){
		m_lIMG.EasyInsertItem(shorten(StrToCStr(no.content[i].get_imgname())), getIconIMG((IMGversion)no.getVersion(i)));
	}
	return 0;
}

BOOL CExRabbitDlg::updatePIClist(){
	// 更新帧列表
	////////////////////////////////
	CString cstr;
	m_lPicture.DeleteAllItems();
	for(int i=0;i<io.indexCount;i++){
		cstr = NumToCStr(i) + L",";
		cstr += FmtToCStr(io.PICcontent[i].get_format(), io.version);
		if(io.PICcontent[i].get_format() == LINK){
			cstr += NumToCStr(io.PICcontent[i].get_linkTo());
		}
		cstr += L",";
		cstr += PtToCStr(io.PICcontent[i].get_basePt()) + L",";
		cstr += SzToCStr(io.PICcontent[i].get_picSize())+L",";
		cstr += SzToCStr(io.PICcontent[i].get_frmSize())+L",";
		if(io.version == V5){
			cstr += L"纹理集"+NumToCStr(io.PICcontent[i].get_TEXusing())+L":"+PtToCStr(io.PICcontent[i].get_TEXpointLT())+L"-"+PtToCStr(io.PICcontent[i].get_TEXpointRB());
		}
		m_lPicture.EasyInsertItem(cstr,getIconPIC(io.PICcontent[i].get_format()));
	}
	if(io.indexCount > 0){
		m_lPicture.SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);   
		m_lPicture.SetSelectionMark(0);
		crtPICid = 0;
		draw();
	}
	return 0;
}

BOOL CExRabbitDlg::updateCLRlist(){
	//更新颜色列表
	//////////////////////////////
	CString cstr;
	m_lColor.DeleteAllItems();
	int pro = m_cbPro.GetCurSel();
	if(io.version == V4 || io.version == V5){
		pro = 0;
	}
	if(pro<0 || pro>io.paletteData.getCount()-1)
		return 0;
	for(int i=0;i<io.paletteData[pro].size();i++){
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += ClrToCStr(io.paletteData[pro][i]);
		m_lColor.EasyInsertItem(cstr,getIconCLR(io.paletteData[pro][i]));
	}
	return 0;
}

BOOL CExRabbitDlg::updateTEXlist(){
	//更新纹理集列表
	////////////////////////////////
	CString cstr;
	m_lTexture.DeleteAllItems();
	for(int i=0;i<io.TEXcontent.size();i++){
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += FmtToCStr((colorFormat)(int)io.TEXcontent[i].get_format(),V5)+L",";
		cstr += NumToCStr(io.TEXcontent[i].get_width())+L"×";
		cstr += NumToCStr(io.TEXcontent[i].get_height());
		m_lTexture.EasyInsertItem(cstr,getIconPIC(io.TEXcontent[i].get_format()));
	}
	return 0;
}

BOOL CExRabbitDlg::updateNPKInfo(){
	//更新NPK信息（左信息栏）
	/////////////////////////////////////
	CString cstr;
	cstr = L"文件名："+shorten(fileNPKname)+L"\r\n";
	cstr += L"大小："+NumToCStr(no.getSize())+L"\r\n";
	cstr += L"IMG数："+NumToCStr(no.count);
	m_edNPKinfo.SetWindowText(cstr);
	return 0;
}

BOOL CExRabbitDlg::updateInfo(){
	//更新系统信息（底层信息栏）
	////////////////////////////////
	m_edInfo2.SetWindowText(saveAlert?L"IMG未保存":L"IMG已保存");
	m_edInfo3.SetWindowText(crtIMGid<0?L"IMG:未选":L"IMG:"+NumToCStr(crtIMGid));
	m_edInfo4.SetWindowText(crtPICid<0?L"帧号未选":L"第"+NumToCStr(crtPICid)+L"帧");
	m_edInfo5.SetWindowText(crtTEXid<0?L"纹理集未选":L"纹理集:"+NumToCStr(crtPICid));
	return 0;
}

BOOL CExRabbitDlg::updatePICInfo(){
	//更新IMG信息（右信息栏）
	/////////////////////////////////////
	CString cstr;
	int i;
	cstr = L"版本:"+NumToCStr(io.version)+L"\r\n";
	cstr += L"帧数:"+NumToCStr(io.indexCount)+L"\r\n";
	switch(io.version){
	case V4:
		cstr += L"调色板颜色项:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V5:
		cstr += L"纹理集数:"+NumToCStr(io.TEXcontent.size())+L"\r\n";
		cstr += L"调色板颜色项:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V6:
		cstr += L"调色板方案数:"+NumToCStr(io.paletteData.getCount())+L"\r\n";
		if((i = m_cbPro.GetCurSel()) >= 0){
			cstr += L"当前方案颜色项:"+NumToCStr(io.paletteData[i].size())+L"\r\n";
		}
		break;
	}
	m_edIMGinfo.SetWindowText(cstr);
	return 0;
}

//////////////////////////////////////////////////
/**************主按钮事件************************/
//////////////////////////////////////////////////
void CExRabbitDlg::OnBnClickedButtonMenu()
{
	// TODO: 点击菜单按钮
	writeLog(L"点击按钮",L"主菜单");
	///////////////////////////////
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}

void CExRabbitDlg::OnBnClickedButtonMenu2()
{
	// TODO: 特殊工具
	writeLog(L"点击按钮",L"特殊工具");
	//////////////////////////////////
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(11);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}

void CExRabbitDlg::OnBnClickedButtonMenu3()
{
	// TODO: IMG改动
	writeLog(L"点击按钮",L"确定IMG修改");
	/////////////////////////////////////
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(10);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}

//////////////////////////////////////////////////
/**************表头事件**************************/
//////////////////////////////////////////////////
void CExRabbitDlg::OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 左键点击IMG列表
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	////////////////////////////
	writeLog(L"点击IMG列表",row);
	////////////////////////////
	//切换IMG时提示保存
	if(saveAlert){
		switch(MessageBox(L"这个IMG已经被你改动了喵，要保存喵？",L"提示喵",MB_YESNOCANCEL)){
		case IDYES:
			OnModify01();
			break;
		case IDNO:
			saveAlert = false;
			break;
		default:
			return;
		}
	}
	m_lIMG.SetSelectionMark(row);
	if(row>=0){
		crtIMGid = row;
		fndIMGid = row;
		io.release();
		no.IMGextract(row, io);
		fileIMGname = StrToCStr(no.content[row].get_imgname());
		switchIMGver(io.version);
		updatePIClist();
		updateCLRlist();
		updateTEXlist();
		updatePICInfo();
	}
	updateInfo();
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击IMG列表呼出菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListImg(pNMHDR, pResult);
	int row = pNMListView->iItem;
	/////////////////////////////////
	writeLog(L"右键点击IMG列表",row);
	/////////////////////////////////
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?1:2);
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}

void CExRabbitDlg::OnNMClickListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 左键点击颜色列表
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	////////////////////////////
	writeLog(L"点击颜色列表",row);
	////////////////////////////
	updateInfo();
	draw();
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击颜色列表呼出菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListClr(pNMHDR, pResult);
	int row = pNMListView->iItem;
	/////////////////////////////////
	writeLog(L"右键点击颜色列表",row);
	/////////////////////////////////
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?7:8);
	if(row>=0 && io.version == V4){
		pPopup->EnableMenuItem(IDM_CLR_08, MF_DISABLED|MF_GRAYED);
		pPopup->EnableMenuItem(IDM_CLR_09, MF_DISABLED|MF_GRAYED);
		pPopup->EnableMenuItem(IDM_CLR_10, MF_DISABLED|MF_GRAYED);
	}
	if(row<0 && io.version == V4){
		pPopup->EnableMenuItem(IDMR_CLR03, MF_DISABLED|MF_GRAYED);
	}
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}

void CExRabbitDlg::OnNMClickListTex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 左键点击纹理集列表
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	////////////////////////////
	writeLog(L"点击纹理集列表",row);
	////////////////////////////
	if(row<0)
		return;
	//绘制
	crtTEXid = row;
	updateInfo();
	draw(true);
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListTex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击纹理集列表呼出菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListTex(pNMHDR, pResult);
	int row = pNMListView->iItem;
	/////////////////////////////////
	writeLog(L"右键点击纹理集列表",row);
	/////////////////////////////////
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?5:6);  
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}

void CExRabbitDlg::OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 左键点击帧列表
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	////////////////////////////
	writeLog(L"点击帧列表",row);
	////////////////////////////
	if(row<0)
		return;
	crtPICid = row;
	updateInfo();
	//更新快速修改基准点工具栏内数据
	PICinfo pi;
	io.PICgetInfo(row, pi);
	dlgSetXY.m_e1.SetWindowText(NumToCStr(pi.get_basePt().get_X())+L","+NumToCStr(pi.get_basePt().get_Y()));
	//绘制浏览
	draw();
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击帧列表呼出菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListPic(pNMHDR, pResult);
	int row = pNMListView->iItem;
	////////////////////////////
	writeLog(L"右键点击帧列表",row);
	////////////////////////////
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?3:4);  
	//非v4v6不能提取索引表
	if(row>=0 && !(io.version == V4 || io.version == V6)){
		pPopup->EnableMenuItem(IDM_FRM_03, MF_DISABLED|MF_GRAYED);
		pPopup->EnableMenuItem(IDM_FRM_04, MF_DISABLED|MF_GRAYED);
	}
	if(row>=0 && io.PICcontent[row].get_format() == LINK){
		pPopup->EnableMenuItem(IDM_FRM_03, MF_DISABLED|MF_GRAYED);
		pPopup->EnableMenuItem(IDM_FRM_14, MF_DISABLED|MF_GRAYED);
	}
	if(row>=0 && (io.version == V5 || io.version == V6 || io.PICcontent[row].get_format() == LINK)){
		pPopup->EnableMenuItem(IDM_FRM_16, MF_DISABLED|MF_GRAYED);
	}
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}
void CExRabbitDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 移动鼠标，更新鼠标位置的坐标和颜色值
	int x = point.x-530;
	int y = point.y-10;
	COLORREF clrr;
	CString str1;
	if(point.x>0 && point.y>0){
		m_edInfo6.SetWindowText(L"x:"+NumToCStr(x-drawPara.basePoint.get_X())+L" y:"+NumToCStr(y-drawPara.basePoint.get_Y()));
		CDC *pDC = this->GetDC();
		clrr = GetPixel(pDC->m_hDC, point.x, point.y);
		str1.Format(L"#%02X%02X%02X",GetRValue(clrr),GetGValue(clrr),GetBValue(clrr));
		m_edInfo7.SetWindowText(str1);

		CImage img;
		int i,j;
		img.Create((width-540)/10, 20, 32);
		UCHAR* pst = (UCHAR*)img.GetBits();
		int pit = img.GetPitch();

		for(i=0;i<(width-540)/10;i++){
			for(j=0;j<20;j++){
				if(i==0||j==0){
					*(pst + pit*j + 4*i + 0) = 0xB0;
					*(pst + pit*j + 4*i + 1) = 0xB0;
					*(pst + pit*j + 4*i + 2) = 0xB0;
				}else if(i==(width-540)/10-1||j==19){
					*(pst + pit*j + 4*i + 0) = 0xFF;
					*(pst + pit*j + 4*i + 1) = 0xFF;
					*(pst + pit*j + 4*i + 2) = 0xFF;
				}else{
				*(pst + pit*j + 4*i + 0) = GetBValue(clrr);
				*(pst + pit*j + 4*i + 1) = GetGValue(clrr);
				*(pst + pit*j + 4*i + 2) = GetRValue(clrr);
				}
			}
		}
		img.Draw(pDC->m_hDC,530+(width-540)*6/10+30,height-30);
		img.Destroy();
		ReleaseDC(pDC);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CExRabbitDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 右键点击图片区域
	if(point.x>520 && point.y>0){
		writeLog(L"右键点击贴图",L"");
		///////////////////////////////
		CMenu menu, *pPopup;  
		menu.LoadMenu(IDR_MENU);  
		pPopup = menu.GetSubMenu(9);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCH_ABS, drawPara.realAxis?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCHINDEX, drawPara.indexMode?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCHDDS, drawPara.entireTextureMode?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SHOWCOMPARE, drawPara.compareMode?MF_CHECKED:MF_UNCHECKED);
		CPoint myPoint;  
		ClientToScreen(&myPoint);  
		GetCursorPos(&myPoint); //鼠标位置  
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	}
	CDialogEx::OnRButtonUp(nFlags, point);
}

void CExRabbitDlg::OnDeltaposSpinX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 调整显示位置
	writeLog(L"调整显示水平位置",pNMUpDown->iDelta);
	///////////////////////////////
	drawPara.basePoint.set_X(drawPara.basePoint.get_X()+pNMUpDown->iDelta);
	m_edX.SetWindowText(NumToCStr(drawPara.basePoint.get_X()));
	draw();
	*pResult = 0;
}

void CExRabbitDlg::OnDeltaposSpinY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 调整显示位置
	writeLog(L"调整显示垂直位置",pNMUpDown->iDelta);
	///////////////////////////////
	drawPara.basePoint.set_Y(drawPara.basePoint.get_Y()+pNMUpDown->iDelta);
	m_edY.SetWindowText(NumToCStr(drawPara.basePoint.get_Y()));
	draw();
	*pResult = 0;
}

void CExRabbitDlg::OnCbnSelchangeComboPro()
{
	// TODO: 更改调色板
	writeLog(L"切换调色板",m_cbPro.GetCurSel());
	///////////////////////////////
	updateCLRlist();
	dlgColor.setClr(&io.paletteData[m_cbPro.GetCurSel()]);
	dlgColor.draw();
	draw();
}

void CExRabbitDlg::draw(bool isDDS){
	//绘制
	writeLog(L"（自动）绘制",isDDS?L"纹理集":L"帧");
	///////////////////////////////
	drawPara.texture = isDDS;
	AfxBeginThread(threadDraw, (LPVOID)this);
}

UINT lazyThread(PVOID para){
	//延时线程
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	while(dlg->m_hWnd){
		Sleep(10);
		if(dlg->lazyTime>0){
			dlg->lazyTime--;
		}
	}
	return 0;
}

UINT canvasThread(PVOID para){
	CExRabbitDlg * dlg = (CExRabbitDlg *)para;
	dlg->writeLog(L"（自动）扩充/裁切",L"线程开始");
	if(dlg->expanding){
		dlg->MessageBox(L"上一个扩充/裁切操作进行中。",L"提示喵");
		dlg->writeLog(L"（自动）扩充/裁切",L"线程被打断");
		return 0;
	}
	dlg->expanding = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(L"处理中");
	int x1 = dlg->canvasPara.x1;
	int y1 = dlg->canvasPara.y1;
	int x2 = dlg->canvasPara.x2;
	int y2 = dlg->canvasPara.y2;
	for(int i = 0;i<dlg->io.indexCount;i++){
		matrix mat,mat2,mat3;
		stream s;
		PICinfo pi;
		dlg->io.PICgetInfo(i, pi);
		if(pi.get_format() == LINK)
			continue;
		dlg->io.PICextract(i, mat, 0);
		int x10 = pi.get_basePt().get_X();
		int y10 = pi.get_basePt().get_Y();
		int x20 = pi.get_basePt().get_X()+pi.get_picSize().get_W()-1;
		int y20 = pi.get_basePt().get_Y()+pi.get_picSize().get_H()-1;
		int x1_ = min(x1,x10);
		int x2_ = max(x2,x20);
		int y1_ = min(y1,y10);
		int y2_ = max(y2,y20);
		mat2.allocate(y2_-y1_+1,x2_-x1_+1);
		mat2.putFore(mat, LAY);
		mat2.elemMoveHonz(x10-x1_);
		mat2.elemMoveVert(y10-y1_);
		mat2.getSubMatrix(mat3,y1-y1_,y2-y1_+1,x1-x1_,x2-x1_+1);
		dlg->io.PICpreprocess(mat3, s, pi);
		point newPt(x1,y1);
		pi.set_basePt(newPt);
		dlg->io.PICreplace(i, pi, s);
		{
			dlg->m_lPicture.SetItemText(i, 1, FmtToCStr(dlg->io.PICcontent[i].get_format(), dlg->io.version));
			dlg->m_lPicture.SetItemText(i, 2, PtToCStr(dlg->io.PICcontent[i].get_basePt()));
			dlg->m_lPicture.SetItemText(i, 3, SzToCStr(dlg->io.PICcontent[i].get_picSize()));
			dlg->m_lPicture.SetItemText(i, 4, SzToCStr(dlg->io.PICcontent[i].get_frmSize()));
		}
		dlg->dlgBar.setInfo(L"正在处理第"+NumToCStr(i+1)+L"帧,总"+NumToCStr(dlg->io.indexCount)+L"帧");
		dlg->dlgBar.setPosi((i+1)*1000/dlg->io.indexCount);
		s.release();
		mat.release();
		mat2.release();
		mat3.release();
	}
	dlg->MessageBox(L"处理完成了喵！",L"提示喵");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->expanding = 0;
	dlg->writeLog(L"（自动）扩充/裁切",L"线程结束");
	return 0;
}

UINT uncanvasThread(PVOID para){
	CExRabbitDlg * dlg = (CExRabbitDlg *)para;
	dlg->writeLog(L"（自动）修整",L"线程开始");
	if(dlg->expanding){
		dlg->MessageBox(L"上一个扩充/裁切操作进行中。",L"提示喵");
		dlg->writeLog(L"（自动）修整",L"线程被打断");
		return 0;
	}
	bool emptyWarn = false;
	dlg->expanding = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(L"修整中");
	for(int i = 0;i<dlg->io.indexCount;i++){
		matrix mat,mat2;
		stream s;
		PICinfo pi;
		dlg->io.PICgetInfo(i,pi);
		if(pi.get_format() == LINK)
			continue;
		dlg->io.PICextract(i,mat,0);
		b32 x1_,y1_,x2_,y2_;
		mat.getElemHonzBound(x1_,x2_);
		mat.getElemVertBound(y1_,y2_);
		if(x1_>=x2_){
			//完全空
			emptyWarn = true;
		}else{
			mat.getSubMatrix(mat2, y1_, y2_+1, x1_, x2_+1);
			dlg->io.PICpreprocess(mat2, s, pi);
			point newPt(pi.get_basePt().get_X()+x1_,pi.get_basePt().get_Y()+y1_);
			pi.set_basePt(newPt);
			dlg->io.PICreplace(i, pi, s);
			{
				dlg->m_lPicture.SetItemText(i, 1, FmtToCStr(dlg->io.PICcontent[i].get_format(), dlg->io.version));
				dlg->m_lPicture.SetItemText(i, 2, PtToCStr(dlg->io.PICcontent[i].get_basePt()));
				dlg->m_lPicture.SetItemText(i, 3, SzToCStr(dlg->io.PICcontent[i].get_picSize()));
				dlg->m_lPicture.SetItemText(i, 4, SzToCStr(dlg->io.PICcontent[i].get_frmSize()));
			}
		}
		dlg->dlgBar.setInfo(L"正在修整第"+NumToCStr(i+1)+L"帧,总"+NumToCStr(dlg->io.indexCount)+L"帧");
		dlg->dlgBar.setPosi((i+1)*1000/dlg->io.indexCount);
		s.release();
		mat.release();
		mat2.release();
	}
	if(emptyWarn){
		dlg->MessageBox(L"修整完成了喵！\r\n但是存在不能进行修整的空帧，请您自己去处理喵！",L"提示喵");
	}else{
		dlg->MessageBox(L"修整完成了喵！",L"提示喵");
	}
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->expanding = 0;
	dlg->writeLog(L"（自动）批量修整",L"结束");
	return 0;
}

void CExRabbitDlg::OnOK()
{
	// TODO: 不能按回车
	MessageBox(L"不许按回车喵！",L"提示喵");
	writeLog(L"点击回车",L"");
}


void CExRabbitDlg::OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int row = m_lIMG.GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//无关按键不响应
		*pResult = 0;
		return;
	}
	if(pLVKeyDow->wVKey == VK_UP){
		writeLog(L"IMG列表键盘响应",L"上");
		if(row>0){
			row --;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(pLVKeyDow->wVKey == VK_DOWN){
		writeLog(L"IMG列表键盘响应",L"下");
		if(row<m_lIMG.GetItemCount()-1){
			row ++;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(saveAlert){
		writeLog(L"询问确定改动IMG",L"");
		switch(MessageBox(L"这个IMG已经被你改动了喵，要保存喵？",L"提示喵",MB_YESNO)){
		case IDYES:
			writeLog(L"点击",L"是");
			OnModify01();
			break;
		case IDNO:
			writeLog(L"点击",L"否");
			saveAlert = false;
			updateInfo();
			break;
		}
	}
	if(lazyTime>0){
		*pResult = 0;
		return;
	}
	crtIMGid = row;
	fndIMGid = row;
	if(row>=0){
		io.release();
		no.IMGextract(row, io);
		fileIMGname = StrToCStr(no.content[row].get_imgname());
		switchIMGver(io.version);
		updatePIClist();
		updateCLRlist();
		updateTEXlist();
		
		updatePICInfo();
	}
	updateInfo();
	draw();
	lazyTime = 10;
	*pResult = 0;
}

void CExRabbitDlg::OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int row = m_lPicture.GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//无关按键不响应
		*pResult = 0;
		return;
	}
	if(pLVKeyDow->wVKey == VK_UP){
		writeLog(L"帧列表键盘响应",L"上");
		if(row>0){
			row --;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(pLVKeyDow->wVKey == VK_DOWN){
		writeLog(L"帧列表键盘响应",L"上");
		if(row<m_lPicture.GetItemCount()-1){
			row ++;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(lazyTime>0){
		*pResult = 0;
		return;
	}
	crtPICid = row;
	updateInfo();
	draw();
	lazyTime = 5;
	*pResult = 0;
}


void CExRabbitDlg::OnLvnKeydownListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int row = m_lColor.GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//无关按键不响应
		*pResult = 0;
		return;
	}
	if(pLVKeyDow->wVKey == VK_UP){
		writeLog(L"颜色列表键盘响应",L"上");
		if(row>0){
			row --;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(pLVKeyDow->wVKey == VK_DOWN){
		writeLog(L"颜色列表键盘响应",L"下");
		if(row<m_lColor.GetItemCount()-1){
			row ++;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(lazyTime>0){
		*pResult = 0;
		return;
	}
	updateInfo();
	draw();
	lazyTime = 5;
	*pResult = 0;
}

void CExRabbitDlg::OnLvnKeydownListTex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int row = m_lTexture.GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//无关按键不响应
		*pResult = 0;
		return;
	}
	if(pLVKeyDow->wVKey == VK_UP){
		writeLog(L"纹理集列表键盘响应",L"上");
		if(row>0){
			row --;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(pLVKeyDow->wVKey == VK_DOWN){
		writeLog(L"纹理集列表键盘响应",L"下");
		if(row<m_lTexture.GetItemCount()-1){
			row ++;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(lazyTime>0){
		*pResult = 0;
		return;
	}
	crtTEXid = row;
	updateInfo();
	draw(true);
	lazyTime = 5;
	*pResult = 0;
}

void CExRabbitDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 外部文件拖入
	WCHAR szPath[MAX_PATH] = L"" ;
	UINT nChars=::DragQueryFile(hDropInfo,0,szPath ,MAX_PATH);    
	CString fileName(szPath,nChars) ; 
	CString path;
	str fn;
	CString fmt = fileName.Right(4);
	writeLog(L"拖入了文件",L"");
	if(fmt == L".NPK" || fmt == L".npk"){
		writeLog(L"拖入了NPK文件",fileName);
		if(IDOK == MessageBox(L"打开"+fileName+L"喵？",L"拖曳提示喵")){
			writeLog(L"打开了NPK文件",fileName);
			no.release();
			CStrToStr(fileName, fn);
			if(no.loadFile(fn)){
				//MessageBox(L"读取完毕喵！");
			}else{
				MessageBox(L"读取失败喵！");
				return;
			}
			fileNPKname = fileName;
			updateIMGlist();
			if(no.count>0){
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
	}
	if(fmt == L".IMG" || fmt == L".img"){
		writeLog(L"拖入了IMG文件",fileName);
		UINT fileCount = ::DragQueryFile(hDropInfo, -1, NULL, NULL);
		if(fileCount == 1){
			if(IDOK == MessageBox(L"将"+fileName+L"添加至IMG列表喵？",L"拖曳提示喵")){
				writeLog(L"将IMG文件加入",fileName);
				CStrToStr(fileName, fn);
				IMGobject ioTemp(fn);
				path = toSl(shorten(fileName));
				CStrToStr(path, fn);
				if(no.IMGpush(ioTemp, fn)){
					//MessageBox(L"插入完毕喵！");
					{
						m_lIMG.InsertItem(m_lIMG.GetItemCount(), shorten(path),getIconIMG(ioTemp.version));
					}
				}else{
					MessageBox(L"插入失败喵！");
				}
				ioTemp.release();
				updateNPKInfo();
			}
		}else if(fileCount > 1){
			if(IDOK == MessageBox(L"将这些文件添加至IMG列表喵？",L"拖曳提示喵")){
				for(int i=0;i<fileCount;i++){
					WCHAR szPath[MAX_PATH] = L"" ;
					nChars=::DragQueryFile(hDropInfo,i,szPath ,MAX_PATH);    
					fileName = CString(szPath,nChars) ; 
					str fn;
					fmt = fileName.Right(4);
					CStrToStr(fileName, fn);
					writeLog(L"将IMG文件加入",fileName);
					if((fmt == L".IMG" || fmt == L".img")){
						IMGobject ioTemp;
						if(ioTemp.loadFile(fn)){
							path = toSl(shorten(fileName));
							CStrToStr(path, fn);
							no.IMGpush(ioTemp, fn);
							{
								m_lIMG.InsertItem(m_lIMG.GetItemCount(), shorten(path),getIconIMG(ioTemp.version));
							}
						}
						ioTemp.release();
					}
					updateNPKInfo();
				}
				//MessageBox(L"插入完毕喵！");
			}
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
}


void CExRabbitDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//横向调整
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


void CExRabbitDlg::OnSize(UINT nType, int cx, int cy)
{
	// TODO: 反向调整
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


void CExRabbitDlg::OnStnClickedLogo()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime t = CTime::GetTickCount();
	CString wk[7] = {L"星期日",L"星期一",L"星期二",L"星期三",L"星期四",L"星期五",L"星期六"};
	CString hr[24] = {L"半夜",L"半夜",L"半夜",L"半夜",L"凌晨",L"凌晨",L"凌晨",
	L"早上",L"早上",L"上午",L"上午",L"上午",L"中午",L"中午",L"下午",L"下午",L"下午",
	L"下午",L"晚间",L"晚间",L"晚间",L"晚间",L"晚间",L"晚间"};
	CString s1 = t.Format(L"现在是%Y年%m月%d日，");
	CString s4 = t.Format(L"%I时%M分喵！");
	CString s2 = wk[t.GetDayOfWeek()%7]+L"，";
	CString s3 = hr[t.GetHour()%24];
	MessageBox(s1+s2+s3+s4,L"提示喵！");
	writeLog(L"点击恋恋",L"");
}


BOOL CExRabbitDlg::loadProfile(){
	CStdioFile file;
	CString s1,s2,s3;
	file.Open(L"profile.ini", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	if(file.GetLength() == 0){
		s1 = outputDir = getCurDir()+L"output";
		s2 = imPack2Dir = L"D:\\地下城与勇士\\ImagePacks2";
		s3 = L"16764091";
		bgColor = 16764091;
		file.WriteString(s1+L"\n");
		file.WriteString(s2+L"\n");
		file.WriteString(s3+L"\n");
	}else{
		file.ReadString(outputDir);
		file.ReadString(imPack2Dir);
		file.ReadString(s3);
		bgColor = _ttoi(s3);
		if(s3.GetLength() == 0){
			bgColor = 16764091;
		}
	}
	if(outputDir.GetLength() == 0)
		outputDir = getCurDir()+L"output";
	if(imPack2Dir.GetLength() == 0)
		imPack2Dir = L"D:\\地下城与勇士\\ImagePacks2";
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
	return 0;
}

CString CExRabbitDlg::getOutPutDir(){
	CString savePathStr = outputDir;
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString CExRabbitDlg::getOutPutDir(CString npkName){
	CString savePathStr = outputDir;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\(NPK)"+shorten(npkName);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString CExRabbitDlg::getOutPutDir(CString npkName, CString imgName){
	CString savePathStr = outputDir;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\(NPK)"+shorten(npkName);
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\(IMG)"+shorten(imgName);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString CExRabbitDlg::getOutPutDir(CString npkName, CString imgName, int clPro){
	CString savePathStr = outputDir;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\(NPK)"+shorten(npkName);
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\(IMG)"+shorten(imgName);
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\(CID)Palette"+NumToCStr(clPro);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}

int CExRabbitDlg::getIconIMG(IMGversion iv){
	switch(iv){
	case V2:
		return 1;
	case V4:
		return 2;
	case V5:
		return 3;
	case V6:
		return 4;
	case V1:
		return 5;
	default:
		return 0;
	}
}
int CExRabbitDlg::getIconPIC(colorFormat cf){
	switch(cf){
	case ARGB1555:
		return 4;
	case ARGB4444:
		return 3;
	case ARGB8888:
		return 2;
	case DDS_DXT1:
		return 6;
	case DDS_DXT3:
		return 7;
	case DDS_DXT5:
		return 8;
	case LINK:
		return 1;
	case INDEX_FMT_PALETTE:
		return 5;
	default:
		return 0;
	}
}
int CExRabbitDlg::getIconCLR(Koishi::color clr){
	if(clr.get_A() <= 0x7f){
		return 0;
	}
	return 1;
}
void CExRabbitDlg::getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected){
	selected.clear();
	int k;
	switch(targetPara){
	case 0:
		//单选
		selected.push_back(highLine);
		break;
	case 1:
		//多选
		for(k=0;k<listCtrl->GetItemCount();k++){
			if(listCtrl->GetCheck(k)){
				selected.push_back(k);
			}
		}
		break;
	default:
		//全选
		for(k=0;k<listCtrl->GetItemCount();k++){
			selected.push_back(k);
		}
		break;
	}
}
UINT indexingThread(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg*)para;
	IMGobject io;
	dlg->writeLog(L"（自动）强制索引化",L"开始");
	dlg->indexing.input(dlg->io);
	dlg->indexing.output(io);
	dlg->no.IMGreplace(dlg->crtIMGid, io);
	dlg->m_lIMG.SetItem(dlg->crtIMGid, 0, LVIF_IMAGE, NULL, dlg->getIconIMG(V4),0,0,0);
	io.release();
	dlg->MessageBox(L"转换完毕喵。");
	dlg->writeLog(L"（自动）强制索引化",L"结束");
	return 0;
}
UINT indexingExternThread(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg*)para;
	CString fileName2 = dlg->toolIndexing.fileName.Left(dlg->toolIndexing.fileName.GetLength()-4)+L"(V4).img";
	str s1,s2;
	CStrToStr(dlg->toolIndexing.fileName, s1);
	CStrToStr(fileName2, s2);
	dlg->writeLog(L"（自动）强制索引化外部文件",L"开始");
	dlg->indexing.input(s1);
	dlg->indexing.output(s2);
	dlg->MessageBox(L"转换完毕喵，已存为"+fileName2+L"喵。");
	dlg->writeLog(L"（自动）强制索引化外部文件",L"结束");
	return 0;
}

UINT indexingProcessThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	while(dlg->indexing.millages < 1000){
		dlg->toolIndexing.m_p.SetPos(dlg->indexing.millages);
		if(dlg->indexing.millages > 0 && dlg->indexing.millages < 500){
			dlg->toolIndexing.m_e1.SetWindowText(L"正在重建颜色表……");
		}
		if(dlg->indexing.millages > 500 && dlg->indexing.millages < 1000){
			dlg->toolIndexing.m_e1.SetWindowText(L"正在填充索引……");
		}
		Sleep(5);
	}
	dlg->toolIndexing.m_e1.SetWindowText(L"转换完毕喵。");
	return 0;
}

//////////////////////////////////////////////
/***********界面按钮处理事件*****************/
//////////////////////////////////////////////


void CExRabbitDlg::OnBnClickedButtonPalette()
{
	// TODO: 点击调色板
	dlgColor.ShowWindow(true);
	dlgColor.setClr(&io.paletteData[m_cbPro.GetCurSel()]);
	dlgColor.draw();
	useColorTable = true;
	MOVEW(m_lColor);
	m_lColor.EnableWindow(false);
	writeLog(L"点击按钮",L"调色板");
}
void CExRabbitDlg::OnBnClickedButtonImgsearch()
{
	// TODO: 查询路径名
	CString str1,str2;
	m_edIMGsearch.GetWindowText(str1);
	int i;
	writeLog(L"点击按钮",L"查询");
	for (i = fndIMGid;i<m_lIMG.GetItemCount();i++){
		str2 = m_lIMG.GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndIMGid = i;
			int nItem = m_lIMG.GetTopIndex(); 
			CRect rc;
			m_lIMG.GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndIMGid - nItem)*rc.Height());
			m_lIMG.Scroll(sz);
			return;
		}
	}
	for (i = 0;i<fndIMGid;i++){
		str2 = m_lIMG.GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndIMGid = i;
			int nItem = m_lIMG.GetTopIndex(); 
			CRect rc;
			m_lIMG.GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndIMGid - nItem)*rc.Height());
			m_lIMG.Scroll(sz);
			return;
		}
	}
	MessageBox(L"没有找到路径名包含“"+str1+"”的IMG喵！",L"提示喵");
}

//////////////////////////////////////////////
/***********Main菜单处理事件*****************/
//////////////////////////////////////////////

void CExRabbitDlg::OnMain01()
{
	// TODO: 新建
	MOVEW(dlgNew);
	dlgNew.OnBnClickedCheck1();
	dlgNew.ShowWindow(SW_SHOW);
	writeLog(L"点击菜单项",L"主菜单-新建");
}
void CExRabbitDlg::OnMain02()
{
	// TODO: 打开
	writeLog(L"点击菜单项",L"主菜单-打开");
	CString defExt = _T("资源文件(*.NPK,*.IMG)|*.NPK;*.IMG");
	CString extFilter = _T("资源文件(*.NPK,*.IMG)|*.NPK;*.IMG|NPK文件(*.NPK)|*.NPK|IMG文件(*.IMG)|*.IMG||");
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
				//MessageBox(L"读取完毕喵！");
			}else{
				MessageBox(L"读取失败喵！");
				return;
			}
			fileNPKname = fileName;
			saveAlert = false;
			updateIMGlist();
			if(no.count>0){
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
			writeLog(L"打开",fileName);
		}
		if(fmt == L"G" || fmt == L"g"){
			io.release();
			if(io.loadFile(fn)){
				//MessageBox(L"读取完毕喵！");
			}else{
				MessageBox(L"读取失败喵！");
				return;
			}
			no.release();
			no.create();
			fileIMGname = fileName;
			fileNPKname = L"newNPK.npk";
			saveAlert = false;
			fileName = shorten(fileName);
			CStrToStr(toSl(fileName), fn);
			no.IMGpush(io, fn);
			switchIMGver(io.version);
			updateIMGlist();
			updatePIClist();
			updateCLRlist();
			updateTEXlist();
			updateNPKInfo();
			updatePICInfo();
			m_lIMG.SetSelectionMark(0);
			crtIMGid = 0;
			writeLog(L"打开",fileName);
		}
	}
}
void CExRabbitDlg::OnMain03()
{
	// TODO: 保存
	writeLog(L"点击菜单项",L"主菜单-保存");
	if(saveAlert){
		if(IDYES == MessageBox(L"这个IMG已经被你改动了喵，要保存喵？",L"提示喵",MB_YESNO)){
			OnModify01();
		}
	}
	str fn;
	CString fileName;
	fileName = fileNPKname;
	CStrToStr(fileName, fn);
	if(no.saveFile(fn)){
		MessageBox(_T("NPK保存完毕喵！"));
	}else{
		MessageBox(_T("NPK保存失败喵！"));
	}
}
void CExRabbitDlg::OnMain04()
{
	// TODO: 另存为
	writeLog(L"点击菜单项",L"主菜单-另存为");
	if(saveAlert){
		if(IDYES == MessageBox(L"这个IMG已经被你改动了喵，要保存喵？",L"提示喵",MB_YESNO))
			OnModify01();
	}
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(false, defExt, shorten(fileNPKname), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if(no.saveFile(fn)){
			MessageBox(_T("NPK保存完毕喵！"));
			fileNPKname = fileName;
			fmt = fileName.Right(1);
			updateNPKInfo();
		}else{
			MessageBox(_T("NPK保存失败喵！"));
		}
	}
}
void CExRabbitDlg::OnMain05()
{
	// TODO: 设置
	writeLog(L"点击菜单项",L"主菜单-设置");
	MOVEW(dlgSet);
	dlgSet.ShowWindow(SW_SHOW);
	dlgSet.m_e1.SetWindowText(outputDir);
	dlgSet.m_e2.SetWindowText(imPack2Dir);
	dlgSet.m_e3.SetWindowText(NumToCStr(bgColor));
}
void CExRabbitDlg::OnMain06()
{
	// TODO: 关于
	writeLog(L"点击菜单项",L"主菜单-关于");
	MOVEW(dlgAbout);
	dlgAbout.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnMain07()
{
	// TODO: WIKI
	writeLog(L"点击菜单项",L"主菜单-WIKI");
	ShellExecute(NULL, L"open",L"https://github.com/Lucky-Koishi/KoishiExAPI/wiki/%E6%81%8B%E6%81%8B%E3%81%AEEx%E5%85%94%E5%AD%90%E7%89%88", NULL, NULL, SW_MAXIMIZE); 
}
void CExRabbitDlg::OnMain08()
{
	// TODO: 关闭
	writeLog(L"点击菜单项",L"主菜单-退出");
	CDialogEx::OnCancel();
}

//////////////////////////////////////////////
/********IMG修改确认菜单处理事件*************/
//////////////////////////////////////////////


void CExRabbitDlg::OnModify01()
{
	// TODO: 确认当前修改
	writeLog(L"点击菜单项",L"确认修改");
	int row;
	if((row = crtIMGid) >= 0){
		no.IMGreplace(row, io);
		MessageBox(L"IMG已保存完毕喵！",L"提示喵！");
		saveAlert = false;
		updateIMGlist();
		updatePIClist();
		updateCLRlist();
		updateTEXlist();
		updateNPKInfo();
		
		updatePICInfo();
		updateInfo();
		m_lIMG.SetSelectionMark(row);
	}
}
void CExRabbitDlg::OnModify02()
{
	// TODO: 确认当前修改并将IMG另存为
	writeLog(L"点击菜单项",L"确认修改并将IMG另存为");
	OnModify01();
	int row = crtIMGid;
	if(row<0)
		return;
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(false, defExt, to_(StrToCStr(no.content[crtIMGid].get_imgname())), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName1;
	str fn;
	if(dlg.DoModal() == IDOK){
		fileName1 = dlg.GetPathName();
		CStrToStr(fileName1, fn);
		if(no.extractIMGFile(row, fn)){
			MessageBox(_T("保存完毕喵！"));
		}else{
			MessageBox(_T("保存失败喵！"));
		}
	}
}

//////////////////////////////////////////////
/**********特殊工具菜单处理事件**************/
//////////////////////////////////////////////

void CExRabbitDlg::OnTool01()
{
	// TODO: IMG定位器
	writeLog(L"点击菜单项",L"IMG定位器");
	MOVEW(toolIMGSearch);
	toolIMGSearch.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnTool02()
{
	// TODO: 试衣间
	writeLog(L"点击菜单项",L"肥猫的试衣间");
	MOVEW(toolAvatar);
	toolAvatar.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnTool03()
{
	// TODO: NPK辞典
	writeLog(L"点击菜单项",L"NPK辞典");
	MOVEW(toolDict);
	toolDict.ShowWindow(SW_SHOW);
	toolDict.dictDir = getOutPutDir();
}
void CExRabbitDlg::OnTool04()
{
	// TODO: 转化为索引IMG
	writeLog(L"点击菜单项",L"索引工具");
	MOVEW(toolIndexing);
	toolIndexing.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnTool05()
{
	// TODO: 在此添加命令处理程序代码
	writeLog(L"点击菜单项",L"SPK工具");
	MOVEW(toolSPK);
	toolSPK.localAddr = getOutPutDir();
	toolSPK.OnCbnSelchangeCombo2();
	toolSPK.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnTool06()
{
	// TODO: 在此添加命令处理程序代码
	//useLog = true;
	//MessageBox(L"已经开始记录操作步骤，软件关闭之前有效喵！\n软件关闭后可以在输出目录查看喵！",L"提示喵");
	//logFileName = CTime::GetTickCount().Format(L"操作记录(%Y年%m月%d日-%H小时%M分%S秒).txt");
	//writeLog(L"生成日志",logFileName);
	writeLog(L"点击菜单项",L"强制提取工具");
	MOVEW(toolForceEx);
	toolForceEx.ShowWindow(SW_SHOW);
	toolForceEx.m_pProc.SetRange32(0,100);
}
void CExRabbitDlg::OnTool07()
{
	// TODO: 在此添加命令处理程序代码
	//V1转换V2
	CString defExt = _T("V1资源文件(*.IMG)|*.IMG");
	CString extFilter = _T("V1资源文件(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		fmt = fileName.Right(1);
		CStrToStr(fileName, fn);
		if(fmt == L"G" || fmt == L"g"){
			io.release();
			KoishiExpand::OldIMGobject oio;
			if(!oio.load(fn)){
				MessageBox(L"不是有效的IMGV1文件喵！");
				return;
			}
			if(!oio.make(io)){
				MessageBox(L"该IMGV1文件无法转化喵！");
				return;
			}
			no.release();
			no.create();
			fileIMGname = fileName;
			fileNPKname = L"newNPK.npk";
			saveAlert = false;
			fileName = shorten(fileName);
			CStrToStr(toSl(fileName), fn);
			no.IMGpush(io, fn);
			switchIMGver(io.version);
			updateIMGlist();
			updatePIClist();
			updateCLRlist();
			updateTEXlist();
			updateNPKInfo();
			updatePICInfo();
			m_lIMG.SetSelectionMark(0);
			crtIMGid = 0;
			writeLog(L"打开",fileName);
		}
	}
}

//////////////////////////////////////////////
/***********IMG右键菜单处理事件**************/
//////////////////////////////////////////////


void CExRabbitDlg::OnIMG01()
{
	// TODO: IMG对象另存为
	writeLog(L"点击菜单项",L"IMG对象另存为");
	int row = crtIMGid;
	if(row<0)
		return;
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(false, defExt, to_(StrToCStr(no.content[crtIMGid].get_imgname())), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName1;
	str fn;
	if(dlg.DoModal() == IDOK){
		fileName1 = dlg.GetPathName();
		CStrToStr(fileName1, fn);
		if(no.extractIMGFile(row, fn)){
			MessageBox(_T("保存完毕喵！"));
		}else{
			MessageBox(_T("保存失败喵！"));
		}
	}
}
void CExRabbitDlg::OnIMG02()
{
	// TODO: 提取IMG对象
	writeLog(L"点击菜单项",L"IMG对象提取");
	int row = crtIMGid;
	if(row<0)
		return;
	str fn;
	CString filePath = getOutPutDir(fileNPKname);
	CString fileName = filePath + to_(StrToCStr(no.content[row].get_imgname()));
	CStrToStr(fileName, fn);
	no.extractIMGFile(row, fn);
	MessageBox(L"已保存为"+fileName+L"了喵！",L"提示");
}
void CExRabbitDlg::OnIMG03()
{
	// TODO: 提取勾选IMG对象
	writeLog(L"点击菜单项",L"IMG对象勾选提取");
	int i;
	str fn;
	CString filePath = getOutPutDir(fileNPKname);
	CString fileName;
	for(i=0;i<m_lIMG.GetItemCount();i++){
		if(m_lIMG.GetCheck(i)){
			fileName = filePath+to_(StrToCStr(no.content[i].get_imgname()));
			CStrToStr(fileName, fn);
			no.extractIMGFile(i, fn);
		}
	}
	MessageBox(L"全部提取完毕喵！已保存到"+getOutPutDir(fileNPKname)+L"了喵！",L"提示喵");
}
void CExRabbitDlg::OnIMG04()
{
	// TODO: 插入IMG对象
	writeLog(L"点击菜单项",L"IMG对象插入");
	int row = crtIMGid;
	if(row<0){
		dlgInsert.m_ch1.EnableWindow(false);
		dlgInsert.m_ch2.EnableWindow(false);
		dlgInsert.m_ch1.SetCheck(0);
		dlgInsert.m_ch2.SetCheck(0);
		dlgInsert.m_ch3.SetCheck(1);
	}else{
		dlgInsert.m_ch1.EnableWindow(true);
		dlgInsert.m_ch2.EnableWindow(true);
	}
	dlgInsert.m_e1.SetWindowText(L"newIMG.img");
	dlgInsert.m_e3.SetWindowText(L"newIMG.img");
	MOVEW(dlgInsert);
	dlgInsert.OnCbnSelchangeCombo1();
	dlgInsert.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnIMG05()
{
	// TODO: 替换IMG对象
	writeLog(L"点击菜单项",L"IMG对象替换");
	int row = crtIMGid;
	if(row<0){
		return;
	}
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	str fn;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		IMGobject _io;
		_io.loadFile(fn);
		if(no.IMGreplace(row,_io)){
			MessageBox(L"替换完毕喵！");
		}else{
			MessageBox(L"替换失败喵！");
		}
		_io.release();
		m_lIMG.SetSelectionMark(row);
	}
}
void CExRabbitDlg::OnIMG06()
{
	// TODO: 删除IMG对象
	writeLog(L"点击菜单项",L"IMG对象删除");
	int row = crtIMGid;
	if(row<0){
		return;
	}
	if(no.IMGremove(row)){
		MessageBox(L"删除完毕喵！");
	}else{
		MessageBox(L"删除失败喵！");
	}
	updateIMGlist();
	m_lIMG.SetItemState(row-1, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);   
	m_lIMG.SetSelectionMark(row-1);
}
void CExRabbitDlg::OnIMG07()
{
	// TODO: 删除勾选IMG对象
	writeLog(L"点击菜单项",L"IMG对象删除勾选");
	int i;
	for(i=m_lIMG.GetItemCount()-1;i>=0;i--){
		if(m_lIMG.GetCheck(i)){
			no.IMGremove(i);
		}
	}
	MessageBox(L"全部删除完毕喵！",L"提示喵");
	updateIMGlist();
	m_lIMG.SetSelectionMark(-1);
}
void CExRabbitDlg::OnIMG08()
{
	// TODO: 重设IMG对象全路径
	writeLog(L"点击菜单项",L"IMG对象重设全路径");
	int row = crtIMGid;
	if(row<0){
		return;
	}
	dlgRename.m_ed1.SetWindowText(StrToCStr(no.content[row].get_imgname()));
	dlgRename.m_ed2.SetWindowText(StrToCStr(no.content[row].get_imgname()));
	MOVEW(dlgRename);
	dlgRename.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnIMG0801()
{
	// TODO: 去黑底
	MOVEW(dlgLoseBlack);
	dlgLoseBlack.ShowWindow(SW_SHOW);
	dlgLoseBlack.m_eGamma.SetWindowText(L"3");
}

void CExRabbitDlg::OnIMG09()
{
	// TODO: 隐藏IMG对象贴图
	writeLog(L"点击菜单项",L"IMG对象贴图隐藏");
	int i;
	int row = crtIMGid;
	if(row<0){
		return;
	}
	IMGobject ioTemp;
	PICinfo piTemp;
	stream sTemp;
	no.IMGextract(row, ioTemp);
	for(i = 0;i<ioTemp.indexCount;i++){
		ioTemp.PICgetInfo(i,piTemp);
		ioTemp.PICempty(sTemp, piTemp);
		ioTemp.PICreplace(i, piTemp, sTemp);
		sTemp.release();
	}
	no.IMGreplace(row, ioTemp);
	MessageBox(L"已隐藏该IMG内所有贴图喵！",L"提示喵");
	updatePIClist();
}
void CExRabbitDlg::OnIMG10()
{
	// TODO: 隐藏勾选IMG对象贴图
	writeLog(L"点击菜单项",L"IMG对象贴图隐藏勾选");
	int i;
	for(i=0;i<m_lIMG.GetItemCount();i++){
		if(m_lIMG.GetCheck(i)){
			IMGobject ioTemp;
			PICinfo piTemp;
			stream sTemp;
			no.IMGextract(i, ioTemp);
			for(int j = 0;j<ioTemp.indexCount;j++){
				ioTemp.PICgetInfo(j,piTemp);
				ioTemp.PICempty(sTemp, piTemp);
				ioTemp.PICreplace(j, piTemp, sTemp);
				sTemp.release();
			}
			no.IMGreplace(i, ioTemp);
			ioTemp.release();
		}
	}
	MessageBox(L"全部隐藏完毕喵！",L"提示喵");
	updatePIClist();
}
void CExRabbitDlg::OnIMG11()
{
	// TODO: 转换IMG版本
	writeLog(L"点击菜单项",L"IMG对象版本转换");
	int row = crtIMGid;
	if(row<0){
		return;
	}
	dlgTrasform.m_ch1.SetCheck(true);
	dlgTrasform.m_ch2.SetCheck(false);
	dlgTrasform.m_ch3.SetCheck(false);
	dlgTrasform.m_ch4.SetCheck(true);
	dlgTrasform.m_ch5.SetCheck(false);
	dlgTrasform.m_c1.ResetContent();
	dlgTrasform.m_c1.AddString(L"V2");
	dlgTrasform.m_c1.AddString(L"V4");
	dlgTrasform.m_c1.AddString(L"V5");
	dlgTrasform.m_c1.AddString(L"V6");
	dlgTrasform.m_c1.SetCurSel(0);
	dlgTrasform.m_e1.SetWindowText(L"1");
	dlgTrasform.m_e2.SetWindowText(L"0");
	dlgTrasform.OnCbnSelchangeCombo1();
	MOVEW(dlgTrasform);
	dlgTrasform.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnIMG12()
{
	// TODO: 转换勾选IMG版本
	writeLog(L"点击菜单项",L"IMG对象版本转换勾选");
	int row = crtIMGid;
	if(row<0){
		return;
	}
	dlgTrasform.m_ch1.SetCheck(false);
	dlgTrasform.m_ch2.SetCheck(true);
	dlgTrasform.m_ch3.SetCheck(false);
	dlgTrasform.m_ch4.SetCheck(true);
	dlgTrasform.m_ch5.SetCheck(false);
	dlgTrasform.m_c1.ResetContent();
	dlgTrasform.m_c1.AddString(L"V2");
	dlgTrasform.m_c1.AddString(L"V4");
	dlgTrasform.m_c1.AddString(L"V5");
	dlgTrasform.m_c1.AddString(L"V6");
	dlgTrasform.m_c1.SetCurSel(0);
	dlgTrasform.m_e1.SetWindowText(L"2");
	dlgTrasform.m_e2.SetWindowText(L"1");
	dlgTrasform.OnCbnSelchangeCombo1();
	MOVEW(dlgTrasform);
	dlgTrasform.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnIMG13()
{
	// TODO: IMG对象上移
	writeLog(L"点击菜单项",L"IMG对象上移");
	int row = crtIMGid;
	if(row<1){
		return;
	}
	IMGobject ioTemp;
	no.IMGextract(row, ioTemp);
	str fn = no.content[row].get_imgname();
	no.IMGremove(row);
	no.IMGinsert(row-1, ioTemp, fn);
	ioTemp.release();
	updateNPKInfo();
	{
		CString s1,s2;
		s1 = m_lIMG.GetItemText(row, 0);
		s2 = m_lIMG.GetItemText(row-1, 0);
		m_lIMG.SetItemText(row,0,s2);
		m_lIMG.SetItemText(row-1,0,s1);
		m_lIMG.SetSelectionMark(row - 1);
		m_lIMG.SetItemState(row - 1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lIMG.SetItemState(row ,0, LVIS_SELECTED|LVIS_FOCUSED);
		m_lIMG.SetItem(row-1, 0, LVIF_IMAGE, NULL, getIconIMG((IMGversion)no.getVersion(row-1)),0,0,0);
		m_lIMG.SetItem(row, 0, LVIF_IMAGE, NULL, getIconIMG((IMGversion)no.getVersion(row)),0,0,0);
		crtIMGid = row - 1;
		updateInfo();
	}
}
void CExRabbitDlg::OnIMG14()
{
	// TODO: IMG对象下移
	writeLog(L"点击菜单项",L"IMG对象下移");
	int row = crtIMGid;
	if(row<0){
		return;
	}
	if(row == no.count - 1){
		return;
	}
	IMGobject ioTemp;
	no.IMGextract(row, ioTemp);
	str fn = no.content[row].get_imgname();
	no.IMGremove(row);
	no.IMGinsert(row+1, ioTemp, fn);
	ioTemp.release();
	updateNPKInfo();
	{
		CString s1,s2;
		s1 = m_lIMG.GetItemText(row, 0);
		s2 = m_lIMG.GetItemText(row+1, 0);
		m_lIMG.SetItemText(row,0,s2);
		m_lIMG.SetItemText(row+1,0,s1);
		m_lIMG.SetSelectionMark(row + 1);
		m_lIMG.SetItemState(row+1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lIMG.SetItemState(row ,0, LVIS_SELECTED|LVIS_FOCUSED);
		m_lIMG.SetItem(row+1, 0, LVIF_IMAGE, NULL, getIconIMG((IMGversion)no.getVersion(row+1)),0,0,0);
		m_lIMG.SetItem(row, 0, LVIF_IMAGE, NULL, getIconIMG((IMGversion)no.getVersion(row)),0,0,0);
		crtIMGid = row + 1;
		updateInfo();
	}
}
void CExRabbitDlg::OnIMG15()
{
	// TODO: 全选
	writeLog(L"点击菜单项",L"IMG对象全选");
	int i;
	for(i=0;i<m_lIMG.GetItemCount();i++)
		m_lIMG.SetCheck(i, TRUE);
}
void CExRabbitDlg::OnIMG16()
{
	// TODO: 反选
	writeLog(L"点击菜单项",L"IMG对象反选");
	int i;
	for(i=0;i<m_lIMG.GetItemCount();i++)
		m_lIMG.SetCheck(i, 1-m_lIMG.GetCheck(i));
}
void CExRabbitDlg::OnIMG17()
{
	// TODO: 按装扮名称自动排序
	writeLog(L"点击菜单项",L"IMG对象自动排序");
	AfxBeginThread(threadAutoSort, (PVOID)this);
}
void CExRabbitDlg::OnIMG18()
{
	// TODO: 勾选IMG拼合
	writeLog(L"点击菜单项",L"IMG对象拼合");
	AfxBeginThread(threadMix, PVOID(this));
}
void CExRabbitDlg::OnIMG19()
{
	// TODO: 将IMG对象对比
	writeLog(L"点击菜单项",L"IMG对象设置对比");
	int row = crtIMGid;
	if(row<0){
		return;
	}
	ioComp.release();
	no.IMGextract(row, ioComp);
	MessageBox(L"已经将此IMG作为对比IMG了喵！\r\b通过“IMG对比模式”查看喵！",L"提示喵");

}
void CExRabbitDlg::OnIMGR01()
{
	// TODO: 在此添加命令处理程序代码
	OnIMG04();
}

//////////////////////////////////////////////
/***********frm右键菜单处理事件**************/
//////////////////////////////////////////////


void CExRabbitDlg::OnFRM01()
{
	// TODO: 提取为PNG图像(&E)
	writeLog(L"点击菜单项",L"提取帧为PNG");
	extractPara.target = 1;
	extractPara.texture = false;
	extractPara.toPNG = true;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnFRM02()
{
	// TODO: 提取勾选帧为PNG图像(&X)
	writeLog(L"点击菜单项",L"提取勾选帧为PNG");
	extractPara.target = 2;
	extractPara.texture = false;
	extractPara.toPNG = true;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnFRM03()
{
	// TODO: 提取为索引数据(&N)
	writeLog(L"点击菜单项",L"提取帧为索引");
	extractPara.target = 1;
	extractPara.texture = false;
	extractPara.toPNG = false;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnFRM04()
{
	// TODO: 提取勾选帧为索引数据(&D)
	writeLog(L"点击菜单项",L"提取勾选帧为索引");
	extractPara.target = 2;
	extractPara.texture = false;
	extractPara.toPNG = false;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnFRM05()
{
	// TODO: 添加帧(&I)...
	writeLog(L"点击菜单项",L"插入帧");
	if(io.version == VUDEF){
		MessageBox(L"还没有IMG喵！请选择或打开一个IMG喵！",L"提示喵");
		return;
	}
	dlgInsert2.SetWindowText(L"插入帧");
	dlgInsert2.iORr = CDlgInsertPicture::__INSERT;
	dlgInsert2.ver = io.version;
	dlgInsert2.m_cb1.ResetContent();
	dlgInsert2.m_cb1.AddString(L"插入空图片帧");
	dlgInsert2.m_cb1.AddString(L"插入图片帧");
	dlgInsert2.m_cb1.AddString(L"插入指向帧");
	if(io.version == V5){
		dlgInsert2.m_cb1.AddString(L"插入纹理集引用帧");
	}
	if(m_lPicture.GetSelectionMark()<0){
		dlgInsert2.m_ch1.SetCheck(0);
		dlgInsert2.m_ch2.SetCheck(0);
		dlgInsert2.m_ch3.SetCheck(1);
		dlgInsert2.m_ch1.EnableWindow(false);
		dlgInsert2.m_ch2.EnableWindow(false);
		dlgInsert2.m_ch3.EnableWindow(true);
	}else{
		dlgInsert2.m_ch1.SetCheck(1);
		dlgInsert2.m_ch2.SetCheck(0);
		dlgInsert2.m_ch3.SetCheck(0);
		dlgInsert2.m_ch1.EnableWindow(true);
		dlgInsert2.m_ch2.EnableWindow(true);
		dlgInsert2.m_ch3.EnableWindow(true);
	}
	dlgInsert2.m_cb2.ResetContent();
	switch(io.version){
	case V2:
		dlgInsert2.m_cb2.AddString(L"点阵图像(PNG图像)");
		dlgInsert2.m_cb2.AddString(L"DXTn格式(DDS文件)");
		break;
	case V4:
		dlgInsert2.m_cb2.AddString(L"点阵图像(PNG图像)");
		dlgInsert2.m_cb2.AddString(L"索引数据(PID文件)");
		break;
	case V5:
		dlgInsert2.m_cb2.AddString(L"点阵图像(PNG图像)");
		dlgInsert2.m_cb2.AddString(L"DXTn格式(DDS文件)");
		dlgInsert2.m_cb2.AddString(L"索引数据(PID文件)");
		break;
	case V6:
		dlgInsert2.m_cb2.AddString(L"索引数据(PID文件)");
		break;
	}
	/////////////////
	dlgInsert2.m_cb1.SetCurSel(1);
	dlgInsert2.OnCbnSelchangeCombo1();
	dlgInsert2.m_cb2.SetCurSel(0);
	dlgInsert2.OnCbnSelchangeCombo8();
	/////////////////
	MOVEW(dlgInsert2);
	dlgInsert2.ShowWindow(SW_SHOW);
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnFRM06()
{
	// TODO: 替换帧(&P)...
	writeLog(L"点击菜单项",L"替换帧");
	dlgInsert2.SetWindowText(L"替换帧");
	dlgInsert2.iORr = CDlgInsertPicture::__REPLACE;
	dlgInsert2.ver = io.version;
	dlgInsert2.m_cb1.ResetContent();
	dlgInsert2.m_cb1.AddString(L"替换为空图片帧");
	dlgInsert2.m_cb1.AddString(L"替换为图片帧");
	dlgInsert2.m_cb1.AddString(L"替换为指向帧");
	if(io.version == V5){
		dlgInsert2.m_cb1.AddString(L"替换为纹理集引用帧");
	}
	if(m_lPicture.GetSelectionMark()<0){
		dlgInsert2.m_ch1.SetCheck(0);
		dlgInsert2.m_ch2.SetCheck(0);
		dlgInsert2.m_ch3.SetCheck(1);
		dlgInsert2.m_ch1.EnableWindow(false);
		dlgInsert2.m_ch2.EnableWindow(false);
		dlgInsert2.m_ch3.EnableWindow(true);
	}else{
		dlgInsert2.m_ch1.SetCheck(1);
		dlgInsert2.m_ch2.SetCheck(0);
		dlgInsert2.m_ch3.SetCheck(0);
		dlgInsert2.m_ch1.EnableWindow(true);
		dlgInsert2.m_ch2.EnableWindow(true);
		dlgInsert2.m_ch3.EnableWindow(true);
	}
	dlgInsert2.m_cb2.ResetContent();
	switch(io.version){
	case V2:
		dlgInsert2.m_cb2.AddString(L"点阵图像(PNG图像)");
		dlgInsert2.m_cb2.AddString(L"DXTn格式(DDS文件)");
		dlgInsert2.m_cb2.SetCurSel(0);
		break;
	case V4:
		dlgInsert2.m_cb2.AddString(L"点阵图像(PNG图像)");
		dlgInsert2.m_cb2.AddString(L"索引数据(PID文件)");
		dlgInsert2.m_cb2.SetCurSel(0);
		break;
	case V5:
		dlgInsert2.m_cb2.AddString(L"点阵图像(PNG图像)");
		dlgInsert2.m_cb2.AddString(L"DXTn格式(DDS文件)");
		dlgInsert2.m_cb2.AddString(L"索引数据(PID文件)");
		dlgInsert2.m_cb2.SetCurSel(0);
		break;
	case V6:
		dlgInsert2.m_cb2.AddString(L"索引数据(PID文件)");
		dlgInsert2.m_cb2.SetCurSel(0);
		break;
	}
	/////////////////
	dlgInsert2.m_cb1.SetCurSel(1);
	dlgInsert2.OnCbnSelchangeCombo1();
	dlgInsert2.m_cb2.SetCurSel(0);
	dlgInsert2.OnCbnSelchangeCombo8();
	///////////////////////////
	MOVEW(dlgInsert2);
	dlgInsert2.ShowWindow(SW_SHOW);
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnFRM07()
{
	// TODO: 删除帧(&R)
	writeLog(L"点击菜单项",L"删除帧");
	int i = 0;
	int row = crtPICid;
	io.PICremove(row);
	m_lPicture.DeleteItem(row);
	m_lPicture.SetSelectionMark(row-1);
	MessageBox(L"已将这个贴图删掉了喵！",L"提示喵！");
	for(i=0;i<m_lPicture.GetItemCount();i++){
		m_lPicture.SetItemText(i,0,NumToCStr(i));
	}
	updateNPKInfo();
	updatePICInfo();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnFRM08()
{
	// TODO: 删除勾选帧(&O)
	writeLog(L"点击菜单项",L"删除勾选帧");
	int i = 0;
	for(i=m_lPicture.GetItemCount()-1;i>=0;i--){
		if(m_lPicture.GetCheck(i)){
			io.PICremove(i);
			m_lPicture.DeleteItem(i);
		}
	}
	m_lPicture.SetSelectionMark(-1);
	MessageBox(L"已将所有勾选贴图删掉了喵！",L"提示喵！");
	for(i=0;i<m_lPicture.GetItemCount();i++){
		m_lPicture.SetItemText(i,0,NumToCStr(i));
	}
	updateNPKInfo();
	updatePICInfo();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnFRM09()
{
	// TODO: 清空帧内图像(&H)
	writeLog(L"点击菜单项",L"清空帧图像");
	int row = crtPICid;
	PICinfo pi;
	stream s;
	io.PICempty(s, pi);
	io.PICreplace(row, pi, s);
	s.release();
	m_lPicture.SetItemText(row, 1, FmtToCStr(io.PICcontent[row].get_format(), io.version));
	m_lPicture.SetItemText(row, 2, PtToCStr(io.PICcontent[row].get_basePt()));
	m_lPicture.SetItemText(row, 3, SzToCStr(io.PICcontent[row].get_picSize()));
	m_lPicture.SetItemText(row, 4, SzToCStr(io.PICcontent[row].get_frmSize()));
	if(io.version == V5){
		m_lPicture.SetItemText(row, 5, L"纹理集"+NumToCStr(io.PICcontent[row].get_TEXusing())+L":"+PtToCStr(io.PICcontent[row].get_TEXpointLT())+L"-"+PtToCStr(io.PICcontent[row].get_TEXpointRB()));
	}
	MessageBox(L"已将选定贴图隐藏喵！",L"提示喵");
	updateNPKInfo();
	updatePICInfo();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnFRM10()
{
	// TODO: 清空勾选帧内图像(&I)
	writeLog(L"点击菜单项",L"清除勾选帧图像");
	int i = 0;
	PICinfo pi;
	stream s;
	io.PICempty(s, pi);
	for(i=0;i<m_lPicture.GetItemCount();i++){
		if(m_lPicture.GetCheck(i)){
			io.PICreplace(i,pi,s);
			m_lPicture.SetItemText(i, 1, FmtToCStr(io.PICcontent[i].get_format(), io.version));
			m_lPicture.SetItemText(i, 2, PtToCStr(io.PICcontent[i].get_basePt()));
			m_lPicture.SetItemText(i, 3, SzToCStr(io.PICcontent[i].get_picSize()));
			m_lPicture.SetItemText(i, 4, SzToCStr(io.PICcontent[i].get_frmSize()));
			if(io.version == V5){
				m_lPicture.SetItemText(i, 5, L"纹理集"+NumToCStr(io.PICcontent[i].get_TEXusing())+L":"+PtToCStr(io.PICcontent[i].get_TEXpointLT())+L"-"+PtToCStr(io.PICcontent[i].get_TEXpointRB()));
			}
		}
	}
	s.release();
	MessageBox(L"已将所有勾选贴图隐藏了喵！",L"提示喵！");
	updateNPKInfo();
	updatePICInfo();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnFRM11()
{
	// TODO: 批量导入帧(&S)...
	writeLog(L"点击菜单项",L"批量导入帧");
	if(io.version == VUDEF){
		MessageBox(L"还没有IMG喵！请选择或打开一个IMG喵！",L"提示喵");
		return;
	}
	MOVEW(dlgImportFrame);
	dlgImportFrame.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnFRM12()
{
	// TODO: 全选
	writeLog(L"点击菜单项",L"全选帧");
	int i;
	for(i=0;i<m_lPicture.GetItemCount();i++)
		m_lPicture.SetCheck(i, TRUE);
}
void CExRabbitDlg::OnFRM13()
{
	// TODO: 反选
	writeLog(L"点击菜单项",L"反选帧");
	int i;
	for(i=0;i<m_lPicture.GetItemCount();i++)
		m_lPicture.SetCheck(i, 1-m_lPicture.GetCheck(i));
}
void CExRabbitDlg::OnFRM14()
{
	// TODO: 修改基准点和帧域(&M)...
	writeLog(L"点击菜单项",L"修改帧基准点坐标和帧域");
	int pos = m_lPicture.GetSelectionMark();
	PICinfo pi;
	io.PICgetInfo(pos,pi);
	dlgSetpara.m_c1.SetCheck(1);
	dlgSetpara.m_c2.SetCheck(0);
	dlgSetpara.m_c3.SetCheck(0);
	dlgSetpara.m_c4.SetCheck(0);
	dlgSetpara.m_e1.SetWindowText(NumToCStr(pi.get_basePt().get_X()));
	dlgSetpara.m_e2.SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
	dlgSetpara.m_e3.SetWindowText(NumToCStr(pi.get_frmSize().get_W()));
	dlgSetpara.m_e4.SetWindowText(NumToCStr(pi.get_frmSize().get_H()));
	MOVEW(dlgSetpara);
	dlgSetpara.ShowWindow(SW_SHOW);
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnFRM15()
{
	// TODO: 快速修改基准点坐标(&A)...
	writeLog(L"点击菜单项",L"快速修改帧基准点坐标");
	if(!drawPara.realAxis){
		MessageBox(L"请将显示模式调整为“相对坐标显示”，\r\n否则将看不到调整基准点后的效果。",L"提示喵");
	}
	MOVEW(dlgSetXY);
	dlgSetXY.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnFRM16()
{
	// TODO: 扩充、裁切和修正
	writeLog(L"点击菜单项",L"帧扩充、裁切和修正");
	point allPt1(10000, 10000);
	point allPt2(-10000, -10000);
	PICinfo pi;
	for(int i = 0;i<io.indexCount;i++){
		io.PICgetInfo(i, pi);
		if(pi.get_format() != LINK){
			if(allPt1.get_X()>pi.get_basePt().get_X()){
				allPt1.set_X(pi.get_basePt().get_X());
			}
			if(allPt1.get_Y()>pi.get_basePt().get_Y()){
				allPt1.set_Y(pi.get_basePt().get_Y());
			}
			if(allPt2.get_X()<pi.get_basePt().get_X()+pi.get_picSize().get_W()-1){
				allPt2.set_X(pi.get_basePt().get_X()+pi.get_picSize().get_W()-1);
			}
			if(allPt2.get_Y()<pi.get_basePt().get_Y()+pi.get_picSize().get_H()-1){
				allPt2.set_Y(pi.get_basePt().get_Y()+pi.get_picSize().get_H()-1);
			}
		}
	}
	int row = m_lPicture.GetSelectionMark();
	if(row<0)
		return ;
	io.PICgetInfo(row, pi);
	dlgExpand.m_a1.SetWindowText(NumToCStr(pi.get_basePt().get_X()));
	dlgExpand.m_a2.SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
	dlgExpand.m_a3.SetWindowText(NumToCStr(pi.get_basePt().get_X()+pi.get_picSize().get_W()-1));
	dlgExpand.m_a4.SetWindowText(NumToCStr(pi.get_basePt().get_Y()+pi.get_picSize().get_H()-1));
	dlgExpand.m_a5.SetWindowText(NumToCStr(pi.get_picSize().get_W()));
	dlgExpand.m_a6.SetWindowText(NumToCStr(pi.get_picSize().get_H()));
	dlgExpand.m_b1.SetWindowText(NumToCStr(allPt1.get_X()));
	dlgExpand.m_b2.SetWindowText(NumToCStr(allPt1.get_Y()));
	dlgExpand.m_b3.SetWindowText(NumToCStr(allPt2.get_X()));
	dlgExpand.m_b4.SetWindowText(NumToCStr(allPt2.get_Y()));
	dlgExpand.m_b5.SetWindowText(NumToCStr(allPt2.get_X()-allPt1.get_X()+1));
	dlgExpand.m_b6.SetWindowText(NumToCStr(allPt2.get_Y()-allPt1.get_Y()+1));
	dlgExpand.m_c1.SetWindowText(L"0");
	dlgExpand.m_c2.SetWindowText(L"0");
	dlgExpand.m_c3.SetWindowText(L"0");
	dlgExpand.m_c4.SetWindowText(L"0");
	dlgExpand.ShowWindow(SW_SHOW);
	MOVEW(dlgExpand);
	dlgExpand.m_cb.SetCurSel(0);
	dlgExpand.OnCbnSelchangeCombo2();
}
void CExRabbitDlg::OnFRMR01()
{
	// TODO: 添加帧
	OnFRM05();
}
void CExRabbitDlg::OnFRMR02()
{
	// TODO: 批量导入帧
	OnFRM11();
}

//////////////////////////////////////////////
/*********纹理集右键菜单处理事件*************/
//////////////////////////////////////////////

void CExRabbitDlg::OnTEX01()
{
	// TODO: 提取为PNG图像
	writeLog(L"点击菜单项",L"提取纹理集为PNG");
	extractPara.target = 1;
	extractPara.texture = true;
	extractPara.toPNG = true;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnTEX02()
{
	// TODO: 提取勾选纹理集为PNG图像
	writeLog(L"点击菜单项",L"提取勾选纹理集为PNG");
	extractPara.target = 2;
	extractPara.texture = true;
	extractPara.toPNG = true;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnTEX03()
{
	// TODO: 提取源数据
	writeLog(L"点击菜单项",L"提取纹理集为源数据");
	extractPara.target = 1;
	extractPara.texture = true;
	extractPara.toPNG = false;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnTEX04()
{
	// TODO: 提取勾选纹理集源数据
	writeLog(L"点击菜单项",L"提取勾选纹理集为源数据");
	extractPara.target = 2;
	extractPara.texture = true;
	extractPara.toPNG = false;
	AfxBeginThread(threadExtract, (LPVOID)this);
}
void CExRabbitDlg::OnTEX05()
{
	// TODO: 添加纹理集...
	writeLog(L"点击菜单项",L"插入纹理集");
	dlgInsert3.SetWindowText(L"插入纹理集");
	dlgInsert3.iORr = CDlgInsertPicture::__INSERT;
	dlgInsert3.m_cb1.ResetContent();
	dlgInsert3.m_cb1.AddString(L"DXTn格式(DDS文件)");
	dlgInsert3.m_cb1.AddString(L"点阵图像(PNG图像)");
	dlgInsert3.m_cb1.SetCurSel(0);
	dlgInsert3.ver = io.version;
	dlgInsert3.OnCbnSelchangeCombo1();
	dlgInsert3.m_c1.SetCheck(1);
	dlgInsert3.m_c2.SetCheck(0);
	dlgInsert3.m_c3.SetCheck(0);
	dlgInsert3.m_c1.EnableWindow(true);
	dlgInsert3.m_c2.EnableWindow(true);
	dlgInsert3.m_c3.EnableWindow(true);
	dlgInsert3.m_cb1.SetCurSel(0);
	MOVEW(dlgInsert3);
	dlgInsert3.ShowWindow(SW_SHOW);
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnTEX06()
{
	// TODO: 替换纹理集...
	writeLog(L"点击菜单项",L"替换纹理集");
	dlgInsert3.SetWindowText(L"替换纹理集");
	dlgInsert3.iORr = CDlgInsertPicture::__REPLACE;
	dlgInsert3.m_cb1.ResetContent();
	dlgInsert3.m_cb1.AddString(L"DXTn格式(DDS文件)");
	dlgInsert3.m_cb1.AddString(L"点阵图像(PNG图像)");
	dlgInsert3.m_cb1.SetCurSel(0);
	dlgInsert3.ver = io.version;
	dlgInsert3.OnCbnSelchangeCombo1();
	dlgInsert3.m_c1.SetCheck(1);
	dlgInsert3.m_c2.SetCheck(0);
	dlgInsert3.m_c3.SetCheck(0);
	dlgInsert3.m_c1.EnableWindow(false);
	dlgInsert3.m_c2.EnableWindow(false);
	dlgInsert3.m_c3.EnableWindow(false);
	dlgInsert3.m_cb1.SetCurSel(0);
	MOVEW(dlgInsert3);
	dlgInsert3.ShowWindow(SW_SHOW);
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnTEX07()
{
	// TODO: 删除纹理集
	writeLog(L"点击菜单项",L"删除纹理集");
	int row = m_lTexture.GetSelectionMark();
	io.TEXremove(row);
	m_lTexture.SetSelectionMark(row-1);
	MessageBox(L"已将这个纹理集删掉了喵！",L"提示喵！");
	for(int i=0;i<m_lTexture.GetItemCount();i++){
		m_lTexture.SetItemText(i,0,NumToCStr(i));
	}
	updateNPKInfo();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnTEX08()
{
	// TODO: 删除勾选纹理集
	writeLog(L"点击菜单项",L"删除勾选纹理集");
	int i = 0;
	for(i=m_lTexture.GetItemCount()-1;i>=0;i--){
		if(m_lTexture.GetCheck(i)){
			io.TEXremove(i);
			m_lTexture.DeleteItem(i);
		}
	}
	m_lTexture.SetSelectionMark(-1);
	MessageBox(L"已将所有勾选纹理集删掉了喵！",L"提示喵！");
	for(i=0;i<m_lTexture.GetItemCount();i++){
		m_lTexture.SetItemText(i,0,NumToCStr(i));
	}
	updateNPKInfo();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnTEX09()
{
	// TODO: 全选
	writeLog(L"点击菜单项",L"纹理集全选");
	int i;
	for(i=0;i<m_lTexture.GetItemCount();i++)
		m_lTexture.SetCheck(i, TRUE);
}
void CExRabbitDlg::OnTEX10()
{
	// TODO: 反选
	writeLog(L"点击菜单项",L"纹理集反选");
	int i;
	for(i=0;i<m_lTexture.GetItemCount();i++)
		m_lTexture.SetCheck(i, 1-m_lTexture.GetCheck(i));
}
void CExRabbitDlg::OnTEXR01()
{
	// TODO: 添加纹理集...
	OnTEX05();
}

//////////////////////////////////////////////
/*********颜色表右键菜单处理事件*************/
//////////////////////////////////////////////

void CExRabbitDlg::OnCLR01()
{
	// TODO: 插入颜色
	writeLog(L"点击菜单项",L"插入颜色");
	dlgInsert4.SetWindowText(L"插入颜色");
	dlgInsert4.iORr = CDlgInsertColor::__INSERT;
	dlgInsert4.m_c1.SetCheck(1);
	dlgInsert4.m_c2.SetCheck(0);
	dlgInsert4.m_c3.SetCheck(0);
	dlgInsert4.m_c1.EnableWindow(true);
	dlgInsert4.m_c2.EnableWindow(true);
	dlgInsert4.m_c3.EnableWindow(true);
	dlgInsert4.m_e1.SetWindowText(L"255");
	dlgInsert4.m_e2.SetWindowText(L"0");
	dlgInsert4.m_e3.SetWindowText(L"0");
	dlgInsert4.m_e4.SetWindowText(L"0");
	MOVEW(dlgInsert4);
	dlgInsert4.ShowWindow(SW_SHOW);
	dlgInsert4.draw();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnCLR02()
{
	// TODO: 替换颜色...
	writeLog(L"点击菜单项",L"替换颜色");
	dlgInsert4.SetWindowText(L"替换颜色");
	dlgInsert4.iORr = CDlgInsertColor::__REPLACE;
	dlgInsert4.m_c1.SetCheck(1);
	dlgInsert4.m_c2.SetCheck(0);
	dlgInsert4.m_c3.SetCheck(0);
	dlgInsert4.m_c1.EnableWindow(false);
	dlgInsert4.m_c2.EnableWindow(false);
	dlgInsert4.m_c3.EnableWindow(false);
	int pos = m_lColor.GetSelectionMark();
	int clrID = m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	if(pos<0)
		return;
	io.paletteData[clrID][pos].get_B();
	io.paletteData[clrID][pos].get_G();
	io.paletteData[clrID][pos].get_R();
	dlgInsert4.m_e1.SetWindowText(NumToCStr(io.paletteData[clrID][pos].get_A()));
	dlgInsert4.m_e2.SetWindowText(NumToCStr(io.paletteData[clrID][pos].get_R()));
	dlgInsert4.m_e3.SetWindowText(NumToCStr(io.paletteData[clrID][pos].get_G()));
	dlgInsert4.m_e4.SetWindowText(NumToCStr(io.paletteData[clrID][pos].get_B()));
	MOVEW(dlgInsert4);
	dlgInsert4.ShowWindow(SW_SHOW);
	dlgInsert4.draw();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnCLR03()
{
	// TODO: 删除颜色
	writeLog(L"点击菜单项",L"删除颜色");
	int pos = m_lColor.GetSelectionMark();
	int clrID = m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	if(pos<0)
		return;
	io.CLRremove(pos, clrID);
	MessageBox(L"删除颜色完毕喵！",L"提示喵");
	updateCLRlist();
	updateNPKInfo();
	
	updatePICInfo();
	draw();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnCLR04()
{
	// TODO: 导入调色板信息...
	writeLog(L"点击菜单项",L"导入CID");
	int clrID = m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	CString defExt = _T("V4调色板(*.cid)|*.cid");
	CString extFilter = _T("V4调色板(*.cid)|*.cid||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	str fn;
	stream s;
	i32 i,j,k;
	b8 b;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if(!s.loadFile(fn)){
			MessageBox(L"无法读取文件喵！",L"提示喵");
			return;
		}
		s.read(i);
		if((b32)i != 0x6F436F4B){
			MessageBox(L"该调色板未能识别喵！",L"提示喵！");
			return;
		}
		s.read(i);
		s.read(i);
		k = io.paletteData[clrID].size();
		for(j=0;j<k;j++)
			io.CLRremove(0, clrID);
		for(j=0;j<i;j++){
			color clr;
			s.read(b);
			clr.set_A(b);
			s.read(b);
			clr.set_R(b);
			s.read(b);
			clr.set_G(b);
			s.read(b);
			clr.set_B(b);
			io.CLRpush(clr, clrID);
		}
		MessageBox(L"读取调色板完毕喵！",L"提示喵");
		updateCLRlist();
		updateNPKInfo();
		
		updatePICInfo();
		saveAlert = true;
		updateInfo();
		draw();
	}
}
void CExRabbitDlg::OnCLR05()
{
	// TODO: 存储调色板信息
	writeLog(L"点击菜单项",L"保存CID");
	int clrID = m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	str fn;
	CString fileName = getOutPutDir(fileNPKname,fileIMGname) + L"Palette"+NumToCStr(clrID)+L".CID";
	CStrToStr(fileName, fn);
	stream s,sHead;
	sHead.allocate(12);
	sHead.push((b32)0x6F436F4B);
	sHead.push((b32)0x72756F6C);
	sHead.push((b32)io.paletteData[clrID].size());
	s.allocate(12+4*io.paletteData[clrID].size()+100);		//2.5:忘记×4了
	s.pushStream(sHead,12);
	for(int i = 0;i<io.paletteData[clrID].size();i++){
		s.push(io.paletteData[clrID][i].get_A());
		s.push(io.paletteData[clrID][i].get_R());
		s.push(io.paletteData[clrID][i].get_G());
		s.push(io.paletteData[clrID][i].get_B());
	}
	s.makeFile(fn);
	s.release();
	sHead.release();
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}
void CExRabbitDlg::OnCLR06()
{
	// TODO: 导入ACT...
	writeLog(L"点击菜单项",L"导入ACT");
	int clrID = m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	CString defExt = _T("Photoshop颜色表(*.act)|*.act");
	CString extFilter = _T("Photoshop颜色表(*.act)|*.act||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	str fn;
	int i,k;
	lcolor lc;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if(!palette::loadACT(fn, lc)){
			MessageBox(L"未识别的调色板文件喵！",L"提示喵");
			return;
		}
		k = io.paletteData[clrID].size();
		for(i=0;i<k;i++)
			io.CLRremove(0, clrID);
		for(i=0;i<lc.size();i++){
			io.CLRpush(lc[i], clrID);
		}
		saveAlert = true;
		MessageBox(L"读取完毕喵！",L"提示喵");
		updateInfo();
		updateCLRlist();
		updateNPKInfo();
		
		updatePICInfo();
		saveAlert = true;
		draw();
	}
}
void CExRabbitDlg::OnCLR07()
{
	// TODO: 导出ACT
	writeLog(L"点击菜单项",L"导出ACT");
	int clrID = m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	str fn;
	CString fileName =  getOutPutDir(fileNPKname,fileIMGname) + L"Palette"+NumToCStr(clrID)+L".ACT";
	CStrToStr(fileName, fn);
	palette::makeACT(fn, io.paletteData[clrID]);
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}
void CExRabbitDlg::OnCLR08()
{
	// TODO: 存储所有颜色方案
	writeLog(L"点击菜单项",L"导出所有颜色方案CID");
	str fn;
	CString fileName;
	stream s,sHead;
	for(int j = 0;j<io.paletteData.getCount();j++){
		fileName =  getOutPutDir(fileNPKname,fileIMGname) + L"Palette"+NumToCStr(j)+L".CID";
		CStrToStr(fileName, fn);
		sHead.allocate(12);
		sHead.push((b32)0x6F436F4B);
		sHead.push((b32)0x34726F6C);
		sHead.push((b32)io.paletteData[j].size());
		s.allocate(12+io.paletteData[j].size()+100);
		s.pushStream(sHead,12);
		for(int i = 0;i<io.paletteData[j].size();i++){
			s.push(io.paletteData[j][i].get_A());
			s.push(io.paletteData[j][i].get_R());
			s.push(io.paletteData[j][i].get_G());
			s.push(io.paletteData[j][i].get_B());
		}
		s.makeFile(fn);
		s.release();
		sHead.release();
	}
	MessageBox(L"已保存到"+getOutPutDir(fileNPKname,fileIMGname)+L"了喵。",L"提示喵");

}
void CExRabbitDlg::OnCLR09()
{
	// TODO: 新建一个颜色方案
	writeLog(L"点击菜单项",L"新建颜色方案");
	io.CLRnewPalette();
	m_cbPro.ResetContent();
	for(int i = 0;i<io.paletteData.getCount();i++)
		m_cbPro.AddString(L"调色板方案"+NumToCStr(i));
	m_cbPro.SetCurSel(io.paletteData.getCount()-1);
	updateCLRlist();
	updateNPKInfo();
	
	updatePICInfo();
	draw();
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnCLR10()
{
	// TODO: 新建并导入一个颜色方案
	writeLog(L"点击菜单项",L"新建并导入CID为颜色方案");
	int clrID = m_cbPro.GetCurSel();
	if(clrID<0)
		clrID = 0;
	CString defExt = _T("V4调色板(*.cid)|*.cid");
	CString extFilter = _T("V4调色板(*.cid)|*.cid||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	str fn;
	stream s;
	i32 i,j;
	b8 b;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if(!s.loadFile(fn)){
			MessageBox(L"无法读取文件喵！",L"提示喵");
			return;
		}
		s.read(i);
		if((b32)i != 0x6F436F4B){
			MessageBox(L"该调色板未能识别喵！",L"提示喵！");
			return;
		}
		io.CLRnewPalette();
		m_cbPro.ResetContent();
		for(i= 0;i<io.paletteData.getCount();i++)
			m_cbPro.AddString(L"调色板方案"+NumToCStr(i));
		m_cbPro.SetCurSel(io.paletteData.getCount()-1);
		clrID = io.paletteData.getCount()-1;
		s.read(i);
		s.read(i);
		for(j=0;j<i;j++){
			color clr;
			s.read(b);
			clr.set_A(b);
			s.read(b);
			clr.set_R(b);
			s.read(b);
			clr.set_G(b);
			s.read(b);
			clr.set_B(b);
			io.CLRpush(clr, clrID);
		}
		MessageBox(L"读取调色板完毕喵！",L"提示喵");
		updateCLRlist();
		updateNPKInfo();
		
		updatePICInfo();
		saveAlert = true;
		updateInfo();
		draw();
	}
}
void CExRabbitDlg::OnCLRR01()
{
	// TODO: 插入颜色
	OnCLR01();
}
void CExRabbitDlg::OnCLRR02()
{
	// TODO: 导入调色板信息
	OnCLR04();
}
void CExRabbitDlg::OnCLRR03()
{
	// TODO: 新建颜色方案
	OnCLR09();
}

//////////////////////////////////////////////
/*********颜色表右键菜单处理事件*************/
//////////////////////////////////////////////

void CExRabbitDlg::OnDisplay01()
{
	// TODO: 实际坐标模式
	writeLog(L"点击菜单项",L"切换实际坐标模式");
	drawPara.realAxis = !drawPara.realAxis;
	draw();
}
void CExRabbitDlg::OnDisplay02()
{
	// TODO: 自动调整显示坐标
	writeLog(L"点击菜单项",L"自动调整实际坐标");
	int row = m_lPicture.GetSelectionMark();
	if(row<0)
		return;
	switch(drawPara.realAxis){
	case true:
		drawPara.basePoint.set_X(-io.PICcontent[row].get_basePt().get_X());
		drawPara.basePoint.set_Y(-io.PICcontent[row].get_basePt().get_Y());
		m_edX.SetWindowText(NumToCStr(drawPara.basePoint.get_X()));
		m_edY.SetWindowText(NumToCStr(drawPara.basePoint.get_Y()));
		break;
	default:
		break;
	}
	draw();
}
void CExRabbitDlg::OnDisplay03()
{
	// TODO: 索引模式
	writeLog(L"点击菜单项",L"切换索引模式");
	drawPara.indexMode = !drawPara.indexMode;
	draw();
}
void CExRabbitDlg::OnDisplay04()
{
	// TODO: 纹理集引用模式
	writeLog(L"点击菜单项",L"切换纹理集引用模式");
	drawPara.entireTextureMode = !drawPara.entireTextureMode;
	draw();
}
void CExRabbitDlg::OnDisplay05()
{
	// TODO: IMG对比模式
	writeLog(L"点击菜单项",L"切换IMG对比模式");
	drawPara.compareMode = !drawPara.compareMode;
	if(drawPara.compareMode)
		drawPara.realAxis = true;
	draw();
}
void CExRabbitDlg::OnDisplay06()
{
	// TODO: 设置对比IMG文件
	writeLog(L"点击菜单项",L"设置IMG对比文件");
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		ioComp.release();
		if(ioComp.loadFile(fn)){
			MessageBox(L"设置完毕喵！");
		}else{
			MessageBox(L"读取失败喵！");
			return;
		}
	}
}
void CExRabbitDlg::OnDisplay07()
{
	// TODO: 播放帧
	writeLog(L"点击菜单项",L"播放动画");
	AfxBeginThread(playThread, (LPVOID)this);
}

void CExRabbitDlg::OnMix0()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = LAY;
	writeLog(L"切换混合模式",L"覆盖");
	m_edInfo8.SetWindowText(L"覆盖");
	draw();
}
void CExRabbitDlg::OnMix1()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = DARKEN;
	writeLog(L"切换混合模式",L"变暗");
	m_edInfo8.SetWindowText(L"变暗");
	draw();
}
void CExRabbitDlg::OnMix2()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = MULTIPLY;
	writeLog(L"切换混合模式",L"正片叠底");
	m_edInfo8.SetWindowText(L"正片叠底");
	draw();
}
void CExRabbitDlg::OnMix3()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = COLORBURN;
	writeLog(L"切换混合模式",L"颜色加深");
	m_edInfo8.SetWindowText(L"颜色加深");
	draw();
}
void CExRabbitDlg::OnMix4()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = LINEARBURN;
	writeLog(L"切换混合模式",L"线性加深");
	m_edInfo8.SetWindowText(L"线性加深");
	draw();
}
void CExRabbitDlg::OnMix5()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = LIGHTEN;
	writeLog(L"切换混合模式",L"变亮");
	m_edInfo8.SetWindowText(L"变亮");
	draw();
}
void CExRabbitDlg::OnMix6()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = SCREEN;
	writeLog(L"切换混合模式",L"滤色");
	m_edInfo8.SetWindowText(L"滤色");
	draw();
}
void CExRabbitDlg::OnMix7()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = COLORDODGE;
	writeLog(L"切换混合模式",L"颜色减淡");
	m_edInfo8.SetWindowText(L"颜色减淡");
	draw();
}
void CExRabbitDlg::OnMix8()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = LINEARDODGE;
	writeLog(L"切换混合模式",L"线性减淡");
	m_edInfo8.SetWindowText(L"线性减淡");
	draw();
}
void CExRabbitDlg::OnMix9()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = OVERLAY;
	writeLog(L"切换混合模式",L"重叠");
	m_edInfo8.SetWindowText(L"重叠");
	draw();
}
void CExRabbitDlg::OnMix10()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = HARDLIGHT;
	writeLog(L"切换混合模式",L"强光");
	m_edInfo8.SetWindowText(L"强光");
	draw();
}
void CExRabbitDlg::OnMix11()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = SOFTLIGHT;
	writeLog(L"切换混合模式",L"柔光");
	m_edInfo8.SetWindowText(L"柔光");
	draw();
}
void CExRabbitDlg::OnMix12()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = VIVIDLIGHT;
	writeLog(L"切换混合模式",L"亮光");
	m_edInfo8.SetWindowText(L"亮光");
	draw();
}
void CExRabbitDlg::OnMix13()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = LINEARLIGHT;
	writeLog(L"切换混合模式",L"线性光");
	m_edInfo8.SetWindowText(L"线性光");
	draw();
}
void CExRabbitDlg::OnMix14()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = PINLIGHT;
	writeLog(L"切换混合模式",L"点光");
	m_edInfo8.SetWindowText(L"点光");
	draw();
}
void CExRabbitDlg::OnMix15()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = HARDMIX;
	writeLog(L"切换混合模式",L"实色混合");
	m_edInfo8.SetWindowText(L"实色混合");
	draw();
}
void CExRabbitDlg::OnMix16()
{
	// TODO: 在此添加命令处理程序代码
	drawPara.mixMode = DIFFER;
	writeLog(L"切换混合模式",L"差值");
	m_edInfo8.SetWindowText(L"差值");
	draw();
}

UINT CExRabbitDlg::threadTransform(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg *)para;
	if(dlg->converting){
		dlg->MessageBox(L"上一个转换操作进行中。",L"提示喵");
		return 0;
	}
	dlg->writeLog(L"（自动）IMG版本转换",L"开始");
	dlg->converting = 1;							//置转换中信号有效
	structTransformPara TFP = dlg->transformPara;	//转换参数
	std::vector<int> targetList;					//待转换目标列表
	dlg->getSelected(&dlg->m_lIMG, dlg->crtIMGid, TFP.target-1, targetList);
	//叫出等待条
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(L"转换中");
	int i,p;
	int total = targetList.size();
	int finished = 0;
	int pos;
	str fn, fn2;
	IMGobject ioIn, ioOut;

	for(i=total-1;i>=0;i--){
		dlg->dlgBar.setInfo(L"第"+NumToCStr(total-i)+L"转换中,总"+NumToCStr(total)+L"个");
		pos = targetList[i];
		dlg->no.IMGextract(pos, ioIn);
		if(ioIn.version == V6){
			//V6版本按调色板分拆
			if(ioIn.paletteData.getCount() == 0){
				ioIn.release();
				continue;
			}
			fn = dlg->no.content[pos].get_imgname();
			dlg->no.IMGremove(pos);
			dlg->m_lIMG.DeleteItem(pos);
			for(p=0;p<ioIn.paletteData.getCount();p++){
				dlg->dlgBar.setInfo(L"第"+NumToCStr(total-i)+L"转换中,处理"+NumToCStr(p+1)+L"号调色方案");
				ioIn.convertTo(ioOut, (IMGversion)TFP.verPara, (colorFormat)TFP.fmtPara, p, TFP.bitMode ? 0x80 | TFP.bitPara : TFP.bitPara, TFP.makeTexture);
				fn2 = KoishiTitle::imgAddV4Num(fn,p);
				dlg->no.IMGinsert(pos+p, ioOut, fn2);
				dlg->m_lIMG.InsertItem(pos+p, shorten(StrToCStr(fn2)),dlg->getIconIMG(ioOut.version));
				ioOut.release();
				dlg->dlgBar.setPosi((total-i-1)*1000/total+(p+1)*1000/total/ioIn.paletteData.getCount());
			}
			finished ++;
		}else{
			//非V6版本用传统转换
			if(ioIn.convertTo(ioOut, (IMGversion)TFP.verPara, (colorFormat)TFP.fmtPara, 0, 
				TFP.bitMode ? 0x80 | TFP.bitPara : TFP.bitPara, TFP.makeTexture)){
				dlg->no.IMGreplace(pos, ioOut);
				dlg->m_lIMG.SetItem(pos, 0, LVIF_IMAGE, NULL, dlg->getIconIMG(ioOut.version),0,0,0);
				finished++;
			}
			ioOut.release();
		}
		ioIn.release();
		dlg->dlgBar.setPosi((total-i)*1000/total);
	}
	dlg->io.release();
	dlg->no.IMGextract(dlg->crtIMGid, dlg->io);
	dlg->MessageBox(L"转换完毕喵！\r\n总"+NumToCStr(total)+L"个,成功"+NumToCStr(finished)+L"个喵。",L"提示喵");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->switchIMGver(dlg->io.version);
	dlg->updatePIClist();
	dlg->updateTEXlist();
	dlg->updateCLRlist();
	dlg->updateNPKInfo();
	dlg->updatePICInfo();
	dlg->converting = 0;
	dlg->writeLog(L"（自动）IMG版本转换",L"结束");
	return 0;
}
UINT CExRabbitDlg::threadImportNPK(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg *)para;
	structImportNPKPara INP = dlg->importNPKPara;	//转换参数
	NPKobject noTemp;
	if(!noTemp.loadFile(INP.fileName)){
		dlg->MessageBox(L"读取NPK失败",L"提示");
		return 0;
	}
	//叫出等待条
	dlg->writeLog(L"（自动）IMG导入从NPK",L"开始");
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(L"导入IMG中");

	int i,j;
	int total = noTemp.count;		//统计总数
	int fail = 0;					//统计失败数
	int conflict = 0;				//统计冲突数
	str fn1, fn2;
	int posConflict = 0;			//冲突位置
	bool isConflict = false;		//是否冲突
	IMGobject ioTemp;
	for(i=0;i<noTemp.count;i++){
		if(!noTemp.IMGextract(i, ioTemp)){
			ioTemp.release();
			fail ++;
			continue;
		}
		for(j=0;j<dlg->no.count;j++){
			fn1 = dlg->no.content[j].get_imgname();	//源NPK内各IMG路径名
			fn2 = noTemp.content[i].get_imgname(); //待导入NPK内IMG的路径名
			if(shorten(StrToCStr(fn1)) == shorten(StrToCStr(fn2))){
				isConflict = true;
				posConflict = j;
				break;
			}
		}
		if(isConflict){
			switch(INP.conflictPara){
			case 0:
				//不检测冲突
				fn2 = noTemp.content[i].get_imgname();
				dlg->no.IMGpush(ioTemp, fn2);
				dlg->m_lIMG.EasyInsertItem(shorten(StrToCStr(fn2)),dlg->getIconIMG(ioTemp.version));
				break;
			case 1:
				conflict ++;
				break;
			case 2:
				dlg->no.IMGreplace(posConflict, ioTemp);
				dlg->m_lIMG.SetItem(posConflict, 0, LVIF_IMAGE, NULL, dlg->getIconIMG(ioTemp.version),0,0,0);
				conflict ++;
				break;
			default:
				fail ++;
				break;
			}
		}else{
			fn2 = noTemp.content[i].get_imgname();
			dlg->no.IMGpush(ioTemp, fn2);
			dlg->m_lIMG.EasyInsertItem(shorten(StrToCStr(fn2)),dlg->getIconIMG(ioTemp.version));
		}
		ioTemp.release();
		dlg->dlgBar.setPosi((i+1)*1000/noTemp.count);
	}
	noTemp.release();
	switch(INP.conflictPara){
	case 1:
		dlg->MessageBox(L"导入完毕喵！\r\n总"+NumToCStr(total)+L"个,跳过"+NumToCStr(conflict)+L"个喵,失败"+NumToCStr(fail)+L"个喵。",L"提示喵");
		break;
	case 2:
		dlg->MessageBox(L"导入完毕喵！\r\n总"+NumToCStr(total)+L"个,替换"+NumToCStr(conflict)+L"个喵,失败"+NumToCStr(fail)+L"个喵。",L"提示喵");
		break;
	case 0:
		dlg->MessageBox(L"导入完毕喵！\r\n总"+NumToCStr(total)+L"个,失败"+NumToCStr(fail)+L"个喵。",L"提示喵");
		break;
	}
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->updateNPKInfo();
	dlg->updatePICInfo();
	dlg->writeLog(L"（自动）IMG导入从NPK",L"结束");
	return 0;
}
UINT CExRabbitDlg::threadImportFrame(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg *)para;
	structImportFramePara IFP = dlg->importFramePara;	//导入帧参数
	if(dlg->io.version != V2){
		dlg->MessageBox(L"仅V2有效喵！",L"提示喵");
		return 0;
	}
	//叫出等待条
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(L"批量导入帧中");
	dlg->writeLog(L"（自动）批量帧导入",L"开始");
	int i,j;
	int total = IFP.maxFrame;
	PICinfo pi;
	matrix mat;
	stream s;
	str fn;
	for(i=0;i<total;i++){
		dlg->dlgBar.setInfo(L"正在导入第"+NumToCStr(i+1)+L"帧,总"+NumToCStr(total)+L"帧");
		fn = IFP.filePath;
		fn += std::to_string((long long)i);
		fn += ".png";
		if(!mat.loadPNG(fn)){
			mat.release();
			continue;
		}
		if(i<dlg->io.indexCount){
			//替换
			if(IFP.oldFramePara == 0){
				dlg->io.PICpreprocess(mat, s, pi, ARGB8888);
				if(IFP.scalePara == 1){
					pi.set_basePt(dlg->io.PICcontent[i].get_basePt());
					pi.set_frmSize(dlg->io.PICcontent[i].get_frmSize());
				}
				dlg->io.PICreplace(i, pi, s);
				s.release();
			}
		}else{
			dlg->io.PICpreprocess(mat, s, pi, ARGB8888);
			dlg->io.PICpush(pi, s);
			s.release();
		}
		mat.release();
		dlg->dlgBar.setPosi((i+1)*1000/total);
	}
	dlg->MessageBox(L"添加完毕喵！",L"提示喵");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	
	dlg->updateNPKInfo();
	dlg->updatePICInfo();
	dlg->updatePIClist();
	dlg->writeLog(L"（自动）批量帧导入",L"结束");
	return 0;
}
UINT CExRabbitDlg::threadMix(PVOID para){
	//待修改：只拼合勾选帧
	CExRabbitDlg *dlg =  (CExRabbitDlg *)para;
	NPKobject *nop = &(dlg->no);
	dlg->writeLog(L"（自动）拼合",L"开始");
	int i, k;
	int imgCount = 0;
	int totalCount = dlg->m_lIMG.GetItemCount();
	std::vector<int> mixLayer;						//勾选图层
	dlg->getSelected(&dlg->m_lIMG, 0, 1, mixLayer);
	imgCount = mixLayer.size();
	if(imgCount == 0)
		return 0;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(L"拼合中");
	IMGobject *ioList = new IMGobject[imgCount];
	IMGobject newIO;
	newIO.create(V2);
	for(i=0;i<imgCount;i++){
		nop->IMGextract(mixLayer[i], ioList[i]);
	}
	int maxFrameCount = 0;
	for(i=0;i<imgCount;i++){
		if(ioList[i].indexCount> maxFrameCount)
			maxFrameCount = ioList[i].indexCount;
	}
	matrix mat,mat2,matf;
	stream s;
	PICinfo pi;
	point ptLT, ptRB, ptLTtemp, ptRBtemp;//左上角右下角的点，右下角的点包含在图片内
	std::vector<int> mLeft, mTop, mRight, mBottom;
	for(k=0;k<maxFrameCount;k++){
		dlg->dlgBar.setInfo(L"正在拼合第"+NumToCStr(k+1)+L"帧,总"+NumToCStr(maxFrameCount)+L"帧");
		mLeft.clear();
		mTop.clear();
		mRight.clear();
		mBottom.clear();
		for(i=0;i<imgCount;i++){
			if(ioList[i].PICgetInfo(k, pi)){
				int k1 = k;
				if(pi.get_format() == LINK){
					k1 = ioList[i].linkFind(k);
				}
				ioList[i].PICgetInfo(k1, pi);
				if(pi.get_picSize().area() <= 1){
					continue;
				}
				mLeft.push_back(pi.get_basePt().get_X());
				mTop.push_back(pi.get_basePt().get_Y());
				mRight.push_back(pi.get_basePt().get_X()+pi.get_picSize().get_W()-1);
				mBottom.push_back(pi.get_basePt().get_Y()+pi.get_picSize().get_H()-1);
			}
		}
		//2.5新增：考虑全空的情形
		if(mLeft.size() == 0){
			pi.set_basePt(point(0,0));
			pi.set_comp(COMP_NONE);
			pi.set_format(ARGB8888);
			pi.set_dataSize(4);
			pi.set_picSize(size(1,1));
			pi.set_frmSize(size(1,1));
			s.allocate(4);
			s.push((b8)0);
			s.push((b8)0);
			s.push((b8)0);
			s.push((b8)0);
			newIO.PICpush(pi, s);
			s.release();
			continue;
		}
		int tLeft = 100000;
		int tTop = 100000;
		int tRight= -100000;
		int tBottom = -100000;
		for(i=0;i<mLeft.size();i++){
			if(mLeft[i]<tLeft)
				tLeft = mLeft[i];
			if(mRight[i]>tRight)
				tRight = mRight[i];
			if(mTop[i]<tTop)
				tTop = mTop[i];
			if(mBottom[i]>tBottom)
				tBottom = mBottom[i];
		}
		ptLT.set(tLeft, tTop);
		ptRB.set(tRight, tBottom);
		matf.allocate(tBottom-tTop+1, tRight-tLeft+1);
		for(i=0;i<imgCount;i++){
			if(ioList[i].PICgetInfo(k, pi)){
				int k1 = k;
				if(pi.get_format() == LINK){
					k1 = ioList[i].linkFind(k);
				}
				ioList[i].PICgetInfo(k1, pi);
				if(pi.get_picSize().area() <= 1){
					continue;
				}
				ioList[i].PICextract(k1, mat);
				mat2.allocate(
					pi.get_basePt().get_Y()-ptLT.get_Y()+pi.get_picSize().get_H()+10,
					pi.get_basePt().get_X()-ptLT.get_X()+pi.get_picSize().get_W()+10
				);
				mat2.putFore(mat);
				mat2.elemMoveHonz(pi.get_basePt().get_X()-ptLT.get_X());
				mat2.elemMoveVert(pi.get_basePt().get_Y()-ptLT.get_Y());
				matf.putFore(mat2);
				mat.release();
				mat2.release();
			}
		}
		newIO.PICpreprocess(matf, s, pi);
		pi.set_basePt(ptLT);
		newIO.PICpush(pi, s);
		matf.release();
		s.release();
		dlg->dlgBar.setPosi((k+1)*1000/maxFrameCount);
	}
	nop->IMGpush(newIO,"mixed.img");
	dlg->m_lIMG.InsertItem(imgCount, L"mixed.img",dlg->getIconIMG(newIO.version));
	dlg->updateNPKInfo();
	dlg->updateIMGlist();
	delete[] ioList;
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->writeLog(L"（自动）拼合",L"结束");
	return 0;
}
UINT CExRabbitDlg::threadAutoSort(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg *)para;
	dlg->writeLog(L"（自动）自动排序",L"开始");
	int i,j;
	KoishiTitle::avatar av;
	std::vector<KoishiTitle::avatar> avList;
	std::vector<int> iList;
	std::vector<int> newQueue;
	avList.clear();
	iList.clear();
	for(i=0;i<dlg->no.count;i++){
		av.useName(KoishiTitle::shorten(dlg->no.content[i].get_imgname()));
		avList.push_back(av);
		iList.push_back(av.getWeight());
	}
	newQueue.clear();
	for(i=0;i<=3000;i+=5){
		for(j=0;j<iList.size();j++){
			if(iList[j] == i){
				newQueue.push_back(j);
			}
		}
	}
	IMGobject io;
	for(i=0;i<newQueue.size();i++){
		dlg->no.IMGextract(newQueue[i], io);
		dlg->no.IMGpush(io, dlg->no.content[newQueue[i]].get_imgname());
		io.release();
	}
	for(i=0;i<newQueue.size();i++){
		dlg->no.IMGremove(0);
	}
	dlg->updateIMGlist();
	dlg->updateNPKInfo();
	dlg->writeLog(L"（自动）自动排序",L"结束");
	return 0;
}

UINT CExRabbitDlg::threadExtract(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg *)para;
	if(dlg->extracting){
		dlg->MessageBox(L"上一个提取操作进行中。",L"提示喵");
		return 0;
	}
	dlg->extracting = 1;
	dlg->writeLog(L"（自动）提取",L"开始");
	structExtractPara SEP = dlg->extractPara;
	std::vector<int> targetList;					//待转换目标列表
	int count, i;
	if(!SEP.texture){
		//提取普通贴图
		dlg->dlgBar.ShowWindow(SW_SHOW);
		dlg->dlgBar.setTitle(L"提取中");
		dlg->getSelected(&dlg->m_lPicture, dlg->crtPICid, SEP.target-1, targetList);
		count = targetList.size();
		for(i=0;i<count;i++){
			dlg->dlgBar.setInfo(L"正在提取第"+NumToCStr(i+1)+L"帧,总"+NumToCStr(count)+L"帧");
			CString fileName;
			str fn;
			if(SEP.toPNG){
				//提取为PNG
				matrix mat;
				if(dlg->io.version == V6){
					fileName = dlg->getOutPutDir(dlg->fileNPKname,dlg->fileIMGname,dlg->m_cbPro.GetCurSel())+NumToCStr(targetList[i])+L".PNG";
				}else{
					fileName = dlg->getOutPutDir(dlg->fileNPKname,dlg->fileIMGname)+NumToCStr(targetList[i])+L".PNG";
				}
				CStrToStr(fileName, fn);
				dlg->io.PICextract(targetList[i], mat, dlg->m_cbPro.GetCurSel());
				mat.makePNG(fn);
				mat.release();
			}else{
				//提取为索引
				stream s,sComp,sHead;
				PICinfo pi;
				fileName =  dlg->getOutPutDir(dlg->fileNPKname,dlg->fileIMGname) +NumToCStr(targetList[i])+L".PID";
				CStrToStr(fileName, fn);
				dlg->io.PICgetInfo(targetList[i],pi);
				dlg->io.PICgetData(targetList[i],s);
				if(pi.get_format() == ARGB1555){
					s.uncompressData(sComp, pi.get_comp());
					sHead.allocate(16);
					sHead.push((b32)0x73696F4B);
					sHead.push((b32)0x78456968);
					sHead.push(pi.get_picSize().get_W());
					sHead.push(pi.get_picSize().get_H());
					sComp.insertStream(sHead, 16, 0);
					sComp.makeFile(fn);
				}
				s.release();
				sComp.release();
				sHead.release();
			}
			dlg->dlgBar.setPosi((i+1)*1000/count);
		}
	}else{
		//提取纹理集
		dlg->dlgBar.ShowWindow(SW_SHOW);
		dlg->dlgBar.setTitle(L"提取中");
		dlg->getSelected(&dlg->m_lTexture, dlg->crtTEXid, SEP.target-1, targetList);
		count = targetList.size();
		for(i=0;i<count;i++){
			dlg->dlgBar.setInfo(L"正在提取第"+NumToCStr(i+1)+L"个,总"+NumToCStr(count)+L"个");
			CString fileName;
			str fn;
			if(SEP.toPNG){
				matrix mat;
				fileName = dlg->getOutPutDir(dlg->fileNPKname,dlg->fileIMGname)+L"Texture"+NumToCStr(targetList[i])+L".PNG";
				CStrToStr(fileName, fn);
				dlg->io.TEXextract(targetList[i], mat);
				mat.makePNG(fn);
				mat.release();
			}else{
				stream s,sComp;
				fileName = dlg->getOutPutDir(dlg->fileNPKname,dlg->fileIMGname)+L"Texture"+NumToCStr(targetList[i])+L".dat";
				CStrToStr(fileName, fn);
				dlg->io.TEXgetData(targetList[i], s);
				s.uncompressData(sComp, COMP_ZLIB);
				sComp.makeFile(fn);
				sComp.release();
				s.release();
			}
			dlg->dlgBar.setPosi((i+1)*1000/count);
		}
	}
	dlg->MessageBox(L"已保存到文件夹"+dlg->getOutPutDir(dlg->fileNPKname,dlg->fileIMGname)+L"里了。",L"提示喵");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->extracting = 0;
	dlg->writeLog(L"（自动）提取",L"结束");
	return 0;
}

UINT CExRabbitDlg::threadDraw(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if(dlg->drawing)
		return 0;
	dlg->drawing = 1;
	structDrawPara SDP = dlg->drawPara;
	int picRow = dlg->crtPICid;
	int texRow = dlg->crtTEXid;
	int clrRow = dlg->m_lColor.GetSelectionMark();
	int cbpro = dlg->m_cbPro.GetCurSel();
	int i,j,k,m,n,tx,ty;
	int canw = dlg->width - 540;
	int canh = dlg->height - 50;
	int clrBlockSize = 10;
	int clct,cp;
	IMGobject *io = &(dlg->io);
	PICinfo po;
	TEXinfo di;
	CImage img;
	matrix canvas, mat;
	color clr;
	if(io->version == V5 || io->version == V4)
		cbpro = 0;
	//背景
	canvas.allocate(canh,canw);
	canvas.fill(color(0xff,0xCC,0xCC,0xCC));
	//绘制颜色表
	if(io->version == V4 || io->version == V5 || io->version == V6){
		cp = io->paletteData.getCount();
		if(cp>0){
			clct = io->paletteData[0].size();
			if(clct>0){
				clrBlockSize = canw/clct;
			}
		}else{
			clct = 0;
		}
		if(clrBlockSize>10)
			clrBlockSize = 10;
		for(i=0;i<cp;i++){
			clct = io->paletteData[i].size();
			for(j=0;j<clct;j++){
				for(m = 0;m<clrBlockSize;m++){
					for(n=0;n<clrBlockSize;n++){
						canvas.setElem(canh-clrBlockSize*cp+clrBlockSize*i+m, canw-clrBlockSize*clct+clrBlockSize*j+n, io->paletteData[i][j]);
					}
				}
			}
		}
		tx = canw-clrBlockSize*clct+clrBlockSize*clrRow;
		ty = canh-clrBlockSize*cp+clrBlockSize*cbpro;
		
		for(m=0;m<clrBlockSize;m++){
			canvas.setElem(ty+m,tx,color(0xff,0xff,0xff,0xff));
			canvas.setElem(ty,tx+m,color(0xff,0xff,0xff,0xff));
			canvas.setElem(ty+clrBlockSize-1,tx+m,color(0xff,0xff,0xff,0xff));
			canvas.setElem(ty+m,tx+clrBlockSize-1,color(0xff,0xff,0xff,0xff));
		}
	}
	if(SDP.texture){
		//点击纹理集列表
		if(texRow < 0){
			dlg->drawing = 0;
			return 0;
		}
		io->TEXgetInfo(texRow, di);
		io->TEXextract(texRow, mat);
		for(i=0;i<canh;i++){
			for(j=0;j<canw;j++){
				if(SDP.realAxis){//坐标加权
					tx = i-SDP.basePoint.get_Y();	//真实坐标
					ty = j-SDP.basePoint.get_X();	//真是坐标
				}else{//绝对坐标
					tx = i;
					ty = j;
				}
				if(tx<mat.getRowCount() && ty<mat.getColumnCount()){
					clr = mat.getElem(tx,ty);
					clr.mixWith(canvas.getElem(i,j),SDP.mixMode);
					canvas.setElem(i, j, clr);
				}
			}
		}
	}else if(SDP.entireTextureMode && io->version == V5){
		//V5状态下的全纹理集引用模式
		if(picRow < 0){
			dlg->drawing = 0;
			return 0;
		}
		io->PICgetInfo(picRow, po);
		if(po.get_comp() != COMP_ZLIB2){
			dlg->MessageBox(L"选定帧不属于任何纹理集喵！",L"提示喵");
			dlg->drawPara.entireTextureMode = false;
			dlg->drawing = 0;
			return 0;
		}
		io->TEXgetInfo(po.get_TEXusing(), di);
		io->TEXextract(po.get_TEXusing(), mat);
		for(i=0;i<canh;i++){
			for(j=0;j<canw;j++){
				if(SDP.realAxis){
					tx = i-SDP.basePoint.get_Y();	//真实坐标
					ty = j-SDP.basePoint.get_X();	//真实坐标
				}else{
					tx = i;	//真实坐标
					ty = j;	//真实坐标
				}
				if(tx<mat.getRowCount() && ty<mat.getColumnCount()){
					clr = mat.getElem(tx,ty);
					if(ty<po.get_TEXpointLT().get_X() || tx<po.get_TEXpointLT().get_Y() || ty>=po.get_TEXpointRB().get_X() || tx>=po.get_TEXpointRB().get_Y())
						clr.set_A(clr.get_A()/4);
					clr.mixWith(canvas.getElem(i,j),SDP.mixMode);
					canvas.setElem(i, j, clr);
				}
			}
		}
	}else{
		//其他模式
		if(picRow < 0){
			dlg->drawing = 0;
			return 0;
		}
		//IMG对比模式
		if(SDP.compareMode && SDP.realAxis){
			int picRowComp = picRow;
			IMGobject *ioComp = &dlg->ioComp;
			if(picRowComp < ioComp->indexSize){
				//如果ioTemp中存在此帧
				ioComp->PICgetInfo(picRowComp, po);
				if(po.get_format() == LINK)
					picRowComp = ioComp->linkFind(picRowComp);
				ioComp->PICgetInfo(picRowComp, po);
				ioComp->PICextract(picRowComp, mat, 0);
				for(i=0;i<canh;i++){
					for(j=0;j<canw;j++){
						tx = i-po.get_basePt().get_Y()-SDP.basePoint.get_Y();	//真实坐标
						ty = j-po.get_basePt().get_X()-SDP.basePoint.get_X();	//真是坐标
						if(tx<mat.getRowCount() && ty<mat.getColumnCount()){
							clr = mat.getElem(tx,ty);
							if(clr.get_A()>0x7f)
								clr.set_A(0x4f);
							clr.mixWith(canvas.getElem(i,j),SDP.mixMode);
							canvas.setElem(i, j, clr);
						}
					}
				}
				mat.release();	//借用的，要还
			}
		}
		//正常图
		io->PICgetInfo(picRow, po);
		if(po.get_format() == LINK)
			picRow = io->linkFind(picRow);
		io->PICgetInfo(picRow, po);
		io->PICextract(picRow, mat, (i32)cbpro);
		//索引模式
		if(SDP.indexMode && (io->version == V4 || io->version == V5 || io->version == V6)){
			b8 temp = 0xff;
			for(k=0;k<io->paletteData[cbpro].size();k++){
				if(dlg->useColorTable){
					mat.elemReplace(
						io->paletteData[cbpro][k], 
						dlg->dlgColor.chosenClr[k]?color(0,0,0xff):color(temp,temp,temp)
					);
				}else{
					mat.elemReplace(
						io->paletteData[cbpro][k], 
						dlg->m_lColor.GetItemState(k, LVIS_SELECTED)== LVIS_SELECTED?color(0,0,0xff):color(temp,temp,temp)
					);
				}
				temp -= 155/io->paletteData[cbpro].size();
			}
		}
		//移动坐标
		for(i=0;i<canh;i++){
			for(j=0;j<canw;j++){
				if(SDP.realAxis){
					tx = i-po.get_basePt().get_Y()-SDP.basePoint.get_Y();	//真实坐标
					ty = j-po.get_basePt().get_X()-SDP.basePoint.get_X();	//真是坐标
				}else{
					tx = i;
					ty = j;
				}
				if(tx<mat.getRowCount() && ty<mat.getColumnCount()){
					clr = mat.getElem(tx,ty);
					clr.mixWith(canvas.getElem(i,j),SDP.mixMode);
					canvas.setElem(i, j, clr);
				}
			}
		}
	}
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = dlg->GetDC();
	for(i=0;i<canw;i++){
		for(j=0;j<canh;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].get_B();
			*(pst + pit*j + 4*i + 1) = canvas[j][i].get_G();
			*(pst + pit*j + 4*i + 2) = canvas[j][i].get_R();
		}
	}
	img.Draw(pDC->m_hDC,530,10);
	img.Destroy();
	mat.release();
	dlg->ReleaseDC(pDC);
	dlg->drawing = 0;
	canvas.release();
	return 0;
}

UINT CExRabbitDlg::playThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if(dlg->playing){
		return 0;
	}
	int row = dlg->m_lPicture.GetSelectionMark();
	if(row<0)
		return 0;
	dlg->playing = 1;
	while(row<dlg->m_lPicture.GetItemCount()){
		if(row>0){
			dlg->m_lPicture.SetItemState(row-1, 0, LVIS_FOCUSED | LVIS_SELECTED);
		}
		dlg->m_lPicture.SetItemState(row, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);
		dlg->m_lPicture.SetSelectionMark(row);
		dlg->crtPICid = row;
		dlg->draw();
		row ++;
		Sleep(100);
		if(dlg->playing == 0){
			break;
		}
	}
	dlg->playing = 0;
	return 0;
}

UINT CExRabbitDlg::threadLoseBlack(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	structLoseBlackPara SLBP = dlg->loseBlackPara;
	
	//叫出等待条
	//dlg->dlgBar.ShowWindow(SW_SHOW);
	//dlg->dlgBar.setTitle(L"转换中");
	int i;
	int row = dlg->crtIMGid;
	if(row<0){
		return 0;
	}
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(L"去除中");
	IMGobject ioTemp, ioTemp2;
	PICinfo piTemp;
	matrix mat;
	stream s;
	dlg->no.IMGextract(row, ioTemp2);
	ioTemp2.convertTo(ioTemp, V2, ARGB8888);
	for(i = 0;i<ioTemp.indexCount;i++){
		dlg->dlgBar.setPosi((i+1)*1000/ioTemp.indexCount);
		ioTemp.PICgetInfo(i,piTemp);
		if(piTemp.get_format() == LINK)
			continue;
		ioTemp.PICextract(i, mat);
		mat.loseBlack(SLBP.gamma);
		ioTemp.PICpreprocess(mat, s, piTemp, ARGB8888);
		ioTemp.PICreplace(i, piTemp, s);
		s.release();
		mat.release();
	}
	dlg->no.IMGreplace(row, ioTemp);
	dlg->m_lIMG.SetItem(row, 0, LVIF_IMAGE, NULL, dlg->getIconIMG(ioTemp.version),0,0,0);
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->MessageBox(L"已将该IMG内的黑色背景去除了喵！",L"提示喵");
	ioTemp.release();
	ioTemp2.release();
	return 0;
}
////////////////////////////////////////////
//日志
////////////////////////////////////////////
void CExRabbitDlg::writeLog(const CString str){
	if(!useLog)
		return;
	CStdioFile file;
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	file.Open(getOutPutDir()+logFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	file.SeekToEnd();
	file.WriteString(CTime::GetTickCount().Format(L"【%H:%M:%S】")+str+ L"\n");
	file.Close();
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);

}
void CExRabbitDlg::writeLog(const CString operation, const CString remark){
	writeLog(L"【"+operation+L"】"+remark);
}
void CExRabbitDlg::writeLog(const CString operation, const str remark){
	writeLog(L"【"+operation+L"】"+StrToCStr(remark));
}
void CExRabbitDlg::writeLog(const CString operation, int num){
	writeLog(L"【"+operation+L"】"+NumToCStr(num));
}

