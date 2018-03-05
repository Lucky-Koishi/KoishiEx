
// ExRabbitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define DEBUG_CLOCK
// CExRabbitDlg �Ի���
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

	width = 800;
	height = 600;
	fileOpen = false;
	dispModeAbs = false;
	dispModeIndex = false;
	dispModeDds = false;
	dispModeShowAll = false;
	dispModeCompare = false;
	dispMixMode = LAY;
	useColorTable = false;//ʹ��LIST����TABLE
	fileNPKname = L"newNPK.npk";
	fileIMGname = L"newIMG.img";
	drawing = 0;
	to_ver = V2;
	drawDDS = 0;
	extracting = 0;	//��ȡ��
	converting = 0;	//ת����
	expanding = 0; //������
	playing = 0; //������
	lazyTime = 0;
	sizing = 0;
	crtIMGid = -1;
	crtPICid = -1;
	crtCLRDDSid = -1;
	saveAlert = false;
}

void CExRabbitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnMenu);
	DDX_Control(pDX, IDC_EDIT_NPK, m_edNPK);
	DDX_Control(pDX, IDC_LIST_IMG, m_lIMG);
	DDX_Control(pDX, IDC_COMBO_PRO, m_cbPro);
	DDX_Control(pDX, IDC_EDIT_BASEX, m_edX);
	DDX_Control(pDX, IDC_EDIT_BASEY, m_edY);
	DDX_Control(pDX, IDC_EDIT_IMGINFO, m_edIMGinfo);
	DDX_Control(pDX, IDC_EDIT_IMGNAME, m_edIMGname);
	DDX_Control(pDX, IDC_LIST_CLR, m_lColor);
	DDX_Control(pDX, IDC_LIST_PIC, m_lPicture);
	DDX_Control(pDX, IDC_SPIN_X, m_spX);
	DDX_Control(pDX, IDC_SPIN_Y, m_spY);
	DDX_Control(pDX, IDC_LIST_DDS, m_lDDS);
	DDX_Control(pDX, IDC_LOGO, m_logo);
	DDX_Control(pDX, IDC_EDIT_INFO2, m_edInfo2);
	DDX_Control(pDX, IDC_EDIT_INFO3, m_edInfo3);
	DDX_Control(pDX, IDC_EDIT_INFO4, m_edInfo4);
	DDX_Control(pDX, IDC_EDIT_INFO5, m_edInfo5);
	DDX_Control(pDX, IDC_EDIT_INFO6, m_edInfo6);
	DDX_Control(pDX, IDC_EDIT_INFO7, m_edInfo7);
	DDX_Control(pDX, IDC_EDIT_INFO8, m_edInfo8);
}

BEGIN_MESSAGE_MAP(CExRabbitDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MENU, &CExRabbitDlg::OnBnClickedButtonMenu)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMClickListImg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMRClickListImg)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CLR, &CExRabbitDlg::OnNMClickListClr)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CLR, &CExRabbitDlg::OnNMRClickListClr)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMClickListDds)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMRClickListDds)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMClickListPic)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMRClickListPic)
	ON_CBN_SELCHANGE(IDC_COMBO_PRO, &CExRabbitDlg::OnCbnSelchangeComboPro)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_X, &CExRabbitDlg::OnDeltaposSpinX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_Y, &CExRabbitDlg::OnDeltaposSpinY)
	ON_COMMAND(ID_MAINMENU_NEW, &CExRabbitDlg::OnMainMenuNew)
	ON_COMMAND(ID_MAINMENU_OPEN, &CExRabbitDlg::OnMainMenuOpen)
	ON_COMMAND(ID_MAINMENU_SAVE, &CExRabbitDlg::OnMainMenuSave)
	ON_COMMAND(ID_MAINMENU_ABOUT, &CExRabbitDlg::OnMainMenuAbout)
	ON_COMMAND(ID_MAINMENU_QUIT, &CExRabbitDlg::OnMainMenuQuit)
	ON_COMMAND(ID_IMGMENU_EXTRACT, &CExRabbitDlg::OnImgMenuExtract)
	ON_COMMAND(ID_IMGMENU_INSERT, &CExRabbitDlg::OnImgMenuInsert)
	ON_COMMAND(ID_IMGMENU_REMOVE, &CExRabbitDlg::OnImgMenuRemove)
	ON_COMMAND(ID_IMGMENU_REPLACE, &CExRabbitDlg::OnImgMenuReplace)
	ON_COMMAND(ID_IMGMENU_RENAME, &CExRabbitDlg::OnImgMenuRename)
	ON_COMMAND(ID_IMGMENU_MOVEUP, &CExRabbitDlg::OnImgMenuMoveUp)
	ON_COMMAND(ID_IMGMENU_MOVEDOWN, &CExRabbitDlg::OnImgMenuMoveDown)
	ON_COMMAND(ID_IMGMENU_HIDE, &CExRabbitDlg::OnImgMenuHide)
	ON_COMMAND(ID_IMGMENU_CONVERT, &CExRabbitDlg::OnImgMenuConvert)
	ON_COMMAND(ID_IMGMENU2_INSERT, &CExRabbitDlg::OnImgMenu2Insert)
	ON_COMMAND(ID_PICMENU_EXTRACTPNG, &CExRabbitDlg::OnPicMenuExtractPng)
	ON_COMMAND(ID_PICMENU_EXTRACTALLPNG, &CExRabbitDlg::OnPicMenuExtractAllPng)
	ON_COMMAND(ID_PICMENU_EXTRACTINDEX, &CExRabbitDlg::OnPicMenuExtractIndex)
	ON_COMMAND(ID_PICMENU_EXTRACTALLINDEX, &CExRabbitDlg::OnPicMenuExtractAllIndex)
	ON_COMMAND(ID_PICMENU_INSERT, &CExRabbitDlg::OnPicMenuInsert)
	ON_COMMAND(ID_PICMENU_REMOVE, &CExRabbitDlg::OnPicMenuRemove)
	ON_COMMAND(ID_PICMENU_REPLACE, &CExRabbitDlg::OnPicMenuReplace)
	ON_COMMAND(ID_PICMENU_SETPARA, &CExRabbitDlg::OnPicMenuSetPara)
	ON_COMMAND(ID_PICMENU_HIDE, &CExRabbitDlg::OnPicMenuHide)
	ON_COMMAND(ID_PICMENU2_INSERT, &CExRabbitDlg::OnPicMenu2Insert)
	ON_COMMAND(ID_DDSMENU_EXTRACTPNG, &CExRabbitDlg::OnDdsMenuExtractPng)
	ON_COMMAND(ID_DDSMENU_EXTRACTALLPNG, &CExRabbitDlg::OnDdsMenuExtractAllPng)
	ON_COMMAND(ID_DDSMENU_EXTRACTDDS, &CExRabbitDlg::OnDdsMenuExtractDds)
	ON_COMMAND(ID_DDSMENU_EXTRACTALLDDS, &CExRabbitDlg::OnDdsMenuExtractAllDds)
	ON_COMMAND(ID_DDSMENU_INSERT, &CExRabbitDlg::OnDdsMenuInsert)
	ON_COMMAND(ID_DDSMENU_REMOVE, &CExRabbitDlg::OnDdsMenuRemove)
	ON_COMMAND(ID_DDSMENU_REPLACE, &CExRabbitDlg::OnDdsMenuReplace)
	ON_COMMAND(ID_DDSMENU2_INSERT, &CExRabbitDlg::OnDdsMenu2Insert)
	ON_COMMAND(ID_CLRMENU_INSERT, &CExRabbitDlg::OnClrMenuInsert)
	ON_COMMAND(ID_CLRMENU_REMOVE, &CExRabbitDlg::OnClrMenuRemove)
	ON_COMMAND(ID_CLRMENU_REPLACE, &CExRabbitDlg::OnClrMenuReplace)
	ON_COMMAND(ID_CLRMENU_EXTRACTPALETTE, &CExRabbitDlg::OnClrMenuExtractPalette)
	ON_COMMAND(ID_CLRMENU_EXTRACTALLPALETTE, &CExRabbitDlg::OnClrMenuExtractAllPalette)
	ON_COMMAND(ID_CLRMENU2_INSERT, &CExRabbitDlg::OnClrMenu2Insert)
	ON_COMMAND(ID_DISPLAYMENU_SWITCH_ABS, &CExRabbitDlg::OnDisplayMenuSwitchAbs)
	ON_COMMAND(ID_DISPLAYMENU_AUTOFIND, &CExRabbitDlg::OnDisplayMenuAutoFind)
	ON_COMMAND(ID_DISPLAYMENU_SWITCHINDEX, &CExRabbitDlg::OnDisplayMenuSwitchIndex)
	ON_COMMAND(ID_DISPLAYMENU_SWITCHDDS, &CExRabbitDlg::OnDisplayMenuSwitchDds)
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_MENU2, &CExRabbitDlg::OnBnClickedButtonMenu2)
	ON_COMMAND(ID_CLRMENU_LOADPALETTE, &CExRabbitDlg::OnClrMenuLoadPalette)
	ON_COMMAND(ID_CLRMENU_NEWPALETTE, &CExRabbitDlg::OnClrMenuNewPalette)
	ON_COMMAND(ID_CLRMENU2_LOADPALETTE, &CExRabbitDlg::OnClrMenu2LoadPalette)
	ON_COMMAND(ID_CLRMENU2_NEWPALETTE, &CExRabbitDlg::OnClrMenu2NewPalette)
	ON_COMMAND(ID_MENUHSV, &CExRabbitDlg::OnClrMenuHSV)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_IMGMENU_SELECTALL, &CExRabbitDlg::OnImgMenuSelectAll)
	ON_COMMAND(ID_IMGMENU_SELECTOTHER, &CExRabbitDlg::OnImgMenuSelectOther)
	ON_COMMAND(ID_IMGMENU_REMOVEALLSELECTED, &CExRabbitDlg::OnImgMenuRemoveAllSelected)
	ON_COMMAND(ID_IMGMENU_HIDEALLSELECTED, &CExRabbitDlg::OnImgMenuHideAllSelected)
	ON_COMMAND(ID_IMGMENU_EXTRACTALLSELECTED, &CExRabbitDlg::OnImgMenuExtractAllSelected)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_IMG, &CExRabbitDlg::OnLvnKeydownListImg)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_PIC, &CExRabbitDlg::OnLvnKeydownListPic)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CLR, &CExRabbitDlg::OnLvnKeydownListClr)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_DDS, &CExRabbitDlg::OnLvnKeydownListDds)
	ON_COMMAND(ID_IMG_MENU_ADDTOMIXED, &CExRabbitDlg::OnImgMenuAddToMixed)
	ON_COMMAND(ID_DISPLAYMENU2_SHOWALL, &CExRabbitDlg::OnDisplayMenu2ShowAll)
	ON_COMMAND(ID_DISPLAYMENU2_AUTOFIND, &CExRabbitDlg::OnDisplayMenu2AutoFind)
	ON_COMMAND(ID_DISPLAYMENU2_SWITCH_ABS, &CExRabbitDlg::OnDisplayMenu2SwitchAbs)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_MAINMENU_SAVEAS, &CExRabbitDlg::OnMainMenuSaveAs)
	ON_COMMAND(ID_PICMENU_SETXY, &CExRabbitDlg::OnPicMenuSetXY)
	ON_COMMAND(ID_DISPLAYMENU_SHOWCOMPARE, &CExRabbitDlg::OnDisplayMenuShowCompare)
	ON_COMMAND(ID_DISPLAYMENU_SETCOMPARE, &CExRabbitDlg::OnDisplayMenuSetCompare)
	ON_COMMAND(ID_IMGMENU_COMPAREAS, &CExRabbitDlg::OnImgMenuCompareAs)
	ON_COMMAND(ID_CLRMENU_LOADACT, &CExRabbitDlg::OnClrMenuLoadAct)
	ON_COMMAND(ID_CLRMENU_EXPORTACT, &CExRabbitDlg::OnClrMenuExportAct)
	ON_COMMAND(ID_PICMENU_EXPAND, &CExRabbitDlg::OnPicMenuExpand)
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
	ON_COMMAND(ID_DISPLAYMENU_PLAY, &CExRabbitDlg::OnDisplayMenuPlay)
	ON_COMMAND(ID_CLRMENU_WIN, &CExRabbitDlg::OnClrMenuWin)
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_STN_CLICKED(IDC_LOGO, &CExRabbitDlg::OnStnClickedLogo)
	ON_COMMAND(ID_33072, &CExRabbitDlg::OnTool1)
	ON_COMMAND(ID_33073, &CExRabbitDlg::OnTool2)
END_MESSAGE_MAP()
/////////

// CExRabbitDlg ��Ϣ�������

BOOL CExRabbitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString IMGName, NPKInfo, IMGInfo, Override;

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowPos(NULL, 0, 0, 820, 640, SWP_NOZORDER | SWP_NOMOVE);
	adjustWindow(width, height);
	// �ؼ���С����
	dlgInsert.Create(IDD_INSERT_DIALOG, this);
	dlgInsert.ShowWindow(SW_HIDE);
	dlgRename.Create(IDD_RENAME_DIALOG, this);
	dlgRename.ShowWindow(SW_HIDE);
	dlgTrasform.Create(IDD_TRASFORM_DIALOG, this);
	dlgTrasform.ShowWindow(SW_HIDE);
	dlgNew.Create(IDD_NEW_DIALOG, this);
	dlgNew.ShowWindow(SW_HIDE);
	dlgInsert2.Create(IDD_INSERT2_DIALOG, this);
	dlgInsert2.ShowWindow(SW_HIDE);
	dlgSetpara.Create(IDD_SERPARA_DIALOG, this);
	dlgSetpara.ShowWindow(SW_HIDE);
	dlgInsert3.Create(IDD_INSERT3_DIALOG, this);
	dlgInsert3.ShowWindow(SW_HIDE);
	dlgInsert4.Create(IDD_INSERT4_DIALOG, this);
	dlgInsert4.ShowWindow(SW_HIDE);
	dlgHSV.Create(IDD_HSV_DIALOG, this);
	dlgHSV.ShowWindow(SW_HIDE);
	dlgSetXY.Create(IDD_SERXY_DIALOG, this);
	dlgSetXY.ShowWindow(SW_HIDE);
	dlgExpand.Create(IDD_EXPAND_DIALOG, this);
	dlgExpand.ShowWindow(SW_HIDE);
	dlgColor.Create(IDD_COLOR_DIALOG, this);
	dlgColor.ShowWindow(SW_HIDE);
	dlgBar.Create(IDD_BAR_DIALOG, this);
	dlgBar.ShowWindow(SW_HIDE);
	{
		dlgBar.SetWindowPos(NULL, GetSystemMetrics(SM_CXSCREEN) / 2 - 100, GetSystemMetrics(SM_CYSCREEN) / 2 - 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	toolIMGSearch.Create(IDD_TOOL_IMGSEARCH, this);
	toolIMGSearch.ShowWindow(SW_HIDE);
	toolAvatar.Create(IDD_TOOL_AVATAR, this);
	toolAvatar.ShowWindow(SW_HIDE);
	//dlgCanvas.Create(IDD_CANVAS_DIALOG, this);
	//dlgCanvas.MoveWindow(170,200,width - 180,height - 240);
	//dlgCanvas.ShowWindow(SW_SHOW);
	m_lPicture.SetExtendedStyle(m_lPicture.GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT);
	m_lColor.SetExtendedStyle(m_lColor.GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT);
	m_lDDS.SetExtendedStyle(m_lDDS.GetExtendedStyle() | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT);
	IMGName.LoadStringW(IDS_STRING_IMGNAME);
	//m_lIMG.EasyInsertColumn(L"IMG��,145");
	m_lIMG.EasyInsertColumn(IMGName);
	NPKInfo.LoadStringW(IDS_STRING_NPKINFOTIP);
	m_edNPK.SetWindowText(NPKInfo);
	//m_edNPK.SetWindowText(L"������ʾNPK�ļ�����Ϣ");
	IMGInfo.LoadStringW(IDS_STRING_IMGINFOTIP);
	m_edIMGinfo.SetWindowText(IMGInfo);
	//m_edIMGinfo.SetWindowText(L"������ʾIMG�ļ�����Ϣ");
	m_edX.SetWindowText(L"0");
	m_edY.SetWindowText(L"0");
	Override.LoadStringW(IDS_STRING_OVERRIDE);
	//m_edInfo8.SetWindowText(L"����");
	switchIMGver(V2);

	AfxBeginThread(lazyThread, (PVOID)this);

	ioComp.Create(V2);

#define MOVEW(x) CRect rect;GetClientRect(&rect);ClientToScreen(&rect);x.SetWindowPos(this, rect.left+100, rect.top+100, 0, 0 , SWP_NOSIZE)

#if UGLY
	m_logoPic.LoadBitmap(IDB_BITMAP1);
	m_logo.SetBitmap(m_logoPic);
#endif
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExRabbitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
#if UGLY
		CPaintDC dc(this);
		CRect   rect;
		GetClientRect(rect);
		dc.FillSolidRect(rect, 0XCCCCFF);
#endif
		CDialogEx::OnPaint();
		draw(drawDDS == 1);
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExRabbitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CExRabbitDlg::adjustWindow(int w, int h) {
	if (w < 700 || h < 500)
		return -1;
	width = w;
	height = h;
	m_logo.SetWindowPos(NULL, 10, 10, 150, 40, SWP_NOZORDER);
	m_btnMenu.SetWindowPos(NULL, 10, 60, 70, 35, SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU2)->SetWindowPos(NULL, 90, 60, 70, 35, SWP_NOZORDER);
	m_edNPK.SetWindowPos(NULL, 10, 105, 150, 85, SWP_NOZORDER);
	m_lIMG.SetWindowPos(NULL, 10, 200, 150, h - 210, SWP_NOZORDER);
	m_edIMGname.SetWindowPos(NULL, 170, 10, w - 180, 30, SWP_NOZORDER);
	m_edIMGinfo.SetWindowPos(NULL, w - 120, 50, 110, 140, SWP_NOZORDER);
	m_cbPro.SetWindowPos(NULL, w - 120, 170, 100, 20, SWP_NOZORDER);
	m_lDDS.SetWindowPos(NULL, w - 300, 50, 170, 140, SWP_NOZORDER);
	m_lColor.SetWindowPos(NULL, w - 300, 50, 170, 140, SWP_NOZORDER);
	m_lPicture.SetWindowPos(NULL, 170, 50, w - 300, 140, SWP_NOZORDER);
	m_edInfo2.SetWindowPos(NULL, 170, h - 30, (w - 180) / 10, 20, SWP_NOZORDER);
	m_edInfo3.SetWindowPos(NULL, 170 + (w - 180) / 10, h - 30, (w - 180) / 10, 20, SWP_NOZORDER);
	m_edInfo4.SetWindowPos(NULL, 170 + (w - 180) * 2 / 10, h - 30, (w - 180) / 10, 20, SWP_NOZORDER);
	m_edInfo5.SetWindowPos(NULL, 170 + (w - 180) * 3 / 10, h - 30, (w - 180) / 10, 20, SWP_NOZORDER);
	m_edInfo6.SetWindowPos(NULL, 170 + (w - 180) * 4 / 10, h - 30, (w - 180) / 10 + 15, 20, SWP_NOZORDER);
	m_edInfo7.SetWindowPos(NULL, 170 + (w - 180) * 5 / 10 + 15, h - 30, (w - 180) / 10 + 15, 20, SWP_NOZORDER);
	m_edInfo8.SetWindowPos(NULL, 170 + (w - 180) * 7 / 10 + 30, h - 30, (w - 180) / 10, 20, SWP_NOZORDER);
	m_edX.SetWindowPos(NULL, 170 + (w - 180) * 8 / 10 + 30, h - 30, (w - 180) / 10 - 25, 20, SWP_NOZORDER);
	m_edY.SetWindowPos(NULL, 170 + (w - 180) * 9 / 10 + 15, h - 30, (w - 180) / 10 - 25, 20, SWP_NOZORDER);
	m_spX.SetWindowPos(NULL, 170 + (w - 180) * 9 / 10 + 5, h - 30, 10, 20, SWP_NOZORDER);
	m_spY.SetWindowPos(NULL, 170 + (w - 180) - 10, h - 30, 10, 20, SWP_NOZORDER);
	//dlgCanvas.MoveWindow(170,200,w - 180,h - 240);
	switch (io.version) {
	case V2:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 300, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 140, SWP_NOZORDER);
		break;
	case V4:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 480, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 140, SWP_NOZORDER);
		break;
	case V5:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 480, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 140, SWP_NOZORDER);
		break;
	case V6:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 480, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 110, SWP_NOZORDER);
		break;
	}
	return 0;
}

BOOL CExRabbitDlg::switchIMGver(IMGversion ver) {
	int i;
	CString PaletteMethod, SpriteColumn, ColorColumn;
	switch (ver) {
	case V2:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 300, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 140, SWP_NOZORDER);
		m_lColor.ShowWindow(SW_HIDE);
		useColorTable = false;
		dlgColor.ShowWindow(SW_HIDE);
		m_lDDS.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_HIDE);
		m_cbPro.ResetContent();
		PaletteMethod.LoadStringW(IDS_STRING_PALETTE0);
		m_cbPro.AddString(PaletteMethod);
		//m_cbPro.AddString(L"��ɫ�巽��0");
		m_cbPro.SetCurSel(0);
		SpriteColumn.LoadStringW(IDS_STRING_SPRITECOLUMN);
		m_lPicture.EasyInsertColumn(SpriteColumn);
		//m_lPicture.EasyInsertColumn(L"֡��,40,��ɫ��ʽ,90,��׼����,80,�ߴ�,80,֡��ߴ�,80");
		break;
	case V4:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 480, 140, SWP_NOZORDER);
		m_lColor.SetWindowPos(NULL, width - 300, 50, 170, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 140, SWP_NOZORDER);
		m_lColor.ShowWindow(SW_SHOW);
		m_lDDS.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_HIDE);
		m_cbPro.ResetContent();
		PaletteMethod.LoadStringW(IDS_STRING_PALETTE0);
		m_cbPro.AddString(PaletteMethod);
		//m_cbPro.AddString(L"��ɫ�巽��0");
		m_cbPro.SetCurSel(0);
		SpriteColumn.LoadStringW(IDS_STRING_SPRITECOLUMN);
		m_lPicture.EasyInsertColumn(SpriteColumn);
		//m_lPicture.EasyInsertColumn(L"֡��,40,��ɫ��ʽ,90,��׼����,80,�ߴ�,80,֡��ߴ�,80");
		ColorColumn.LoadStringW(IDS_STRING_COLORCOLUMN);
		m_lColor.EasyInsertColumn(ColorColumn);
		//m_lColor.EasyInsertColumn(L"ɫ��,40,RGBA����,70");
		break;
	case V5:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 480, 140, SWP_NOZORDER);
		m_lDDS.SetWindowPos(NULL, width - 300, 50, 170, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 140, SWP_NOZORDER);
		m_lColor.ShowWindow(SW_HIDE);
		useColorTable = false;
		dlgColor.ShowWindow(SW_HIDE);
		m_lDDS.ShowWindow(SW_SHOW);
		m_cbPro.ShowWindow(SW_HIDE);
		m_cbPro.ResetContent();
		PaletteMethod.LoadStringW(IDS_STRING_PALETTE0);
		m_cbPro.AddString(PaletteMethod);
		//m_cbPro.AddString(L"��ɫ�巽��0");
		m_cbPro.SetCurSel(0);
		SpriteColumn.LoadStringW(IDS_STRING_DDSCOLUMN);
		m_lPicture.EasyInsertColumn(SpriteColumn);
		//m_lPicture.EasyInsertColumn(L"֡��,40,��ɫ��ʽ,90,��׼����,80,�ߴ�,80,֡��ߴ�,80,ʹ��DDS״̬,400");
		ColorColumn.LoadStringW(IDS_STRING_DDSCOLUMN2);
		m_lDDS.EasyInsertColumn(ColorColumn);
		//m_lDDS.EasyInsertColumn(L"���,40,��ɫ��ʽ,90,�ߴ�,80");
		break;
	case V6:
		m_lPicture.SetWindowPos(NULL, 170, 50, width - 480, 140, SWP_NOZORDER);
		m_lColor.SetWindowPos(NULL, width - 300, 50, 170, 140, SWP_NOZORDER);
		m_edIMGinfo.SetWindowPos(NULL, width - 120, 50, 110, 110, SWP_NOZORDER);
		m_lColor.ShowWindow(SW_SHOW);
		m_lDDS.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_SHOW);
		SpriteColumn.LoadStringW(IDS_STRING_SPRITECOLUMN);
		m_lPicture.EasyInsertColumn(SpriteColumn);
		//m_lPicture.EasyInsertColumn(L"֡��,40,��ɫ��ʽ,90,��׼����,80,�ߴ�,80,֡��ߴ�,80");
		ColorColumn.LoadStringW(IDS_STRING_COLORCOLUMN);
		m_lColor.EasyInsertColumn(ColorColumn);
		//m_lColor.EasyInsertColumn(L"ɫ��,40,RGBA����,70");
		m_cbPro.ResetContent();
		for (i = 0; i < io.paletteData.getCount(); i++) {
			PaletteMethod.LoadStringW(IDS_STRING_PALETTEMETHODNUM);
			m_cbPro.AddString(PaletteMethod + NumToCStr(i));
			//m_cbPro.AddString(L"��ɫ�巽��" + NumToCStr(i));
		}
		if (io.paletteData.getCount() > 0) {
			m_cbPro.SetCurSel(0);
		}
		break;
	}
	return 0;
}

BOOL CExRabbitDlg::updateIMGlist() {
	// ����IMG�б�
	updateNPKInfo();
	m_lIMG.DeleteAllItems();
	for (int i = 0; i < no.count; i++) {
		m_lIMG.EasyInsertItem(shorten(StrToCStr(no.content[i].get_imgname())));
	}
	return 0;
}

BOOL CExRabbitDlg::updatePIClist() {
	// ����IMG�б�
	CString cstr;
	m_lPicture.DeleteAllItems();
	for (int i = 0; i < io.indexCount; i++) {
		cstr = NumToCStr(i) + L",";
		cstr += FmtToCStr(io.PICcontent[i].get_format(), io.version);
		if (io.PICcontent[i].get_format() == LINK) {
			cstr += NumToCStr(io.PICcontent[i].get_linkTo());
		}
		cstr += L",";
		cstr += PtToCStr(io.PICcontent[i].get_basePt()) + L",";
		cstr += SzToCStr(io.PICcontent[i].get_picSize()) + L",";
		cstr += SzToCStr(io.PICcontent[i].get_frmSize()) + L",";
		if (io.version == V5) {
			cstr += L"DDS" + NumToCStr(io.PICcontent[i].get_DDSIDused()) + L":" + PtToCStr(io.PICcontent[i].get_DDSpointLT()) + L"-" + PtToCStr(io.PICcontent[i].get_DDSpointRB());
		}
		m_lPicture.EasyInsertItem(cstr);
	}
	if (io.indexCount > 0) {
		m_lPicture.SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
		m_lPicture.SetSelectionMark(0);
		draw();
	}
	return 0;
}

BOOL CExRabbitDlg::updateCLRlist() {
	//������ɫ�б�
	CString cstr;
	m_lColor.DeleteAllItems();
	int pro = m_cbPro.GetCurSel();
	if (io.version == V4) {
		pro = 0;
	}
	if (pro<0 || pro>io.paletteData.getCount() - 1)
		return 1;
	for (int i = 0; i < io.paletteData[pro].size(); i++) {
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += ClrToCStr(io.paletteData[pro][i]);
		m_lColor.EasyInsertItem(cstr);
	}
	return 0;
}

BOOL CExRabbitDlg::updateDDSlist() {
	//������ɫ�б�
	CString cstr;
	m_lDDS.DeleteAllItems();
	for (int i = 0; i < io.DDScontent.size(); i++) {
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += FmtToCStr((colorFormat)(int)io.DDScontent[i].get_fourCCID(), V5) + L",";
		cstr += NumToCStr(io.DDScontent[i].get_width()) + L"��";
		cstr += NumToCStr(io.DDScontent[i].get_height());
		m_lDDS.EasyInsertItem(cstr);
	}
	return 0;
}
BOOL CExRabbitDlg::updateNPKInfo() {
	CString cstr, FileName, Size, IMGN;
	/*
	cstr = L"�ļ�����"+shorten(fileNPKname)+L"\r\n";
	cstr += L"��С��"+NumToCStr(no.getSize())+L"\r\n";
	cstr += L"IMG����"+NumToCStr(no.count);
	*/
	FileName.LoadStringW(IDS_STRING_FILENAME);
	Size.LoadStringW(IDS_STRING_SIZE);
	IMGN.LoadStringW(IDS_STRING_IMGN);
	cstr = FileName + shorten(fileNPKname) + L"\r\n";
	cstr += Size + NumToCStr(no.getSize()) + L"\r\n";
	cstr += IMGN + NumToCStr(no.count);
	m_edNPK.SetWindowText(cstr);
	return 0;
}
BOOL CExRabbitDlg::updateInfo() {
	CString Translator1, Translator2;
	Translator1.LoadStringW(IDS_STRING_IMGNOTSAVED);
	Translator2.LoadStringW(IDS_STRING_IMGSAVED);
	m_edInfo2.SetWindowText(saveAlert ? Translator1 : Translator2);
	Translator1.LoadStringW(IDS_STRING_IMGNOTSELECTED);
	m_edInfo3.SetWindowText(crtIMGid < 0 ? Translator1 : L"IMG:" + NumToCStr(crtIMGid));
	Translator1.LoadStringW(IDS_STRING_PICNOTSELECTED);
	m_edInfo4.SetWindowText(crtPICid < 0 ? Translator1 : L"PIC:" + NumToCStr(crtPICid));
	//m_edInfo2.SetWindowText(saveAlert?L"IMGδ����":L"IMG�ѱ���");
	//m_edInfo3.SetWindowText(crtIMGid<0?L"IMG:δѡ":L"IMG:"+NumToCStr(crtIMGid));
	//m_edInfo4.SetWindowText(crtPICid<0?L"PIC:δѡ":L"PIC:"+NumToCStr(crtPICid));
	if (io.version == V4 || io.version == V6) {
		Translator1.LoadStringW(IDS_STRING_CLRNOTSELECTED);
		m_edInfo5.SetWindowText(crtCLRDDSid < 0 ? Translator1 : L"CLR:" + NumToCStr(crtCLRDDSid));
		//m_edInfo5.SetWindowText(crtCLRDDSid<0?L"CLR:δѡ":L"CLR:"+NumToCStr(crtCLRDDSid));
	}
	else if (io.version == V5) {
		Translator1.LoadStringW(IDS_STRING_DDSNOTSELECTED);
		m_edInfo5.SetWindowText(crtCLRDDSid < 0 ? Translator1 : L"DDS:" + NumToCStr(crtCLRDDSid));
		//m_edInfo5.SetWindowText(crtCLRDDSid<0?L"DDS:δѡ":L"DDS:"+NumToCStr(crtCLRDDSid));
	}
	else {
		Translator1.LoadStringW(IDS_STRING_CLRINVALID);
		m_edInfo5.SetWindowText(Translator1);
		//m_edInfo5.SetWindowText(L"CLR:��Ч");
	}
	return 0;
}
BOOL CExRabbitDlg::updateIMGInfo() {
	CString cstr, t;
	cstr = fileIMGname;
	t.LoadStringW(IDS_STRING_WORDIN);
	cstr += t + fileNPKname;
	//cstr += L"\"��\""+fileNPKname;
	//cstr += L"\"��";
	m_edIMGname.SetWindowText(cstr);
	return 0;
}
BOOL CExRabbitDlg::updatePICInfo() {
	CString cstr, t;
	int i;
	t.LoadStringW(IDS_STRING_VERSION);
	cstr = t + NumToCStr(io.version) + L"\r\n";
	//cstr = L"�汾:"+NumToCStr(io.version)+L"\r\n";
	t.LoadStringW(IDS_STRING_FRAMECOUNT);
	cstr += t + NumToCStr(io.indexCount) + L"\r\n";
	//cstr += L"֡��:"+NumToCStr(io.indexCount)+L"\r\n";
	switch (io.version) {
	case V4:
		t.LoadStringW(IDS_STRING_COLORCOUNT);
		cstr += t + NumToCStr(io.paletteData[0].size()) + L"\r\n";
		//cstr += L"��ɫ����ɫ��:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V5:
		t.LoadStringW(IDS_STRING_DDSLARGECOUNT);
		cstr += t + NumToCStr(io.DDScontent.size()) + L"\r\n";
		//cstr += L"DDS��ͼ����:"+NumToCStr(io.DDScontent.size())+L"\r\n";
		t.LoadStringW(IDS_STRING_COLORCOUNT);
		cstr += t + NumToCStr(io.paletteData[0].size()) + L"\r\n";
		//cstr += L"��ɫ����ɫ��:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V6:
		t.LoadStringW(IDS_STRING_PALETTECOUNT);
		cstr += t + NumToCStr(io.paletteData.getCount()) + L"\r\n";
		//cstr += L"��ɫ�巽����:"+NumToCStr(io.paletteData.getCount())+L"\r\n";
		if ((i = m_cbPro.GetCurSel()) >= 0) {
			t.LoadStringW(IDS_STRING_CURRENTCOLORCOUNT);
			cstr += t + NumToCStr(io.paletteData[i].size()) + L"\r\n";
			//cstr += L"��ǰ������ɫ��:"+NumToCStr(io.paletteData[i].size())+L"\r\n";
		}
		break;
	}
	m_edIMGinfo.SetWindowText(cstr);
	return 0;
}
//����˵���ť
void CExRabbitDlg::OnBnClickedButtonMenu()
{
	// TODO: ����˵���ť
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU);
	pPopup = menu.GetSubMenu(0);
	if (!fileOpen) {
		pPopup->EnableMenuItem(ID_MAINMENU_SAVE, MF_GRAYED | MF_DISABLED);
	}
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}
void CExRabbitDlg::OnBnClickedButtonMenu2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int row;
	CString info, title;
	if ((row = crtIMGid) >= 0) {
		no.IMGreplace(row, io);
		info.LoadStringW(IDS_STRING_IMGSAVEFINISHED);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		MessageBox(info, title);
		//MessageBox(L"IMG�ѱ����������",L"��ʾ����");
		saveAlert = false;
		updateIMGlist();
		updatePIClist();
		updateCLRlist();
		updateDDSlist();
		updateNPKInfo();
		updateIMGInfo();
		updatePICInfo();
		updateInfo();
		m_lIMG.SetSelectionMark(row);
	}
}

//////////////////////////////////////////////////
/////////////////��ͷ�¼�/////////////////////////
//////////////////////////////////////////////////
void CExRabbitDlg::OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	CString info, title;
	if (saveAlert) {
		//switch (MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������", L"��ʾ��", MB_YESNO)) {
		info.LoadStringW(IDS_STRING_IMGCONFIRMSAVE);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		switch (MessageBox(info, title, MB_YESNO)) {
		case IDYES:
			OnBnClickedButtonMenu2();
			m_lIMG.SetSelectionMark(row);
			break;
		case IDNO:
			m_lIMG.SetSelectionMark(row);
			saveAlert = false;
			updateInfo();
			break;
		}
	}
	crtIMGid = row;
	if (row >= 0) {
		io.Release();
		no.IMGextract(row, io);
		fileIMGname = StrToCStr(no.content[row].get_imgname());
		switchIMGver(io.version);
		updatePIClist();
		updateCLRlist();
		updateDDSlist();
		updateIMGInfo();
		updatePICInfo();
	}
	updateInfo();
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListImg(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU);
	pPopup = menu.GetSubMenu(row >= 0 ? 1 : 2);
	if (row < 0 && !fileOpen) {
		pPopup->EnableMenuItem(ID_IMGMENU2_INSERT, MF_GRAYED | MF_DISABLED);
	}
	if (!mixMode) {
		pPopup->EnableMenuItem(ID_IMG_MENU_ADDTOMIXED, MF_GRAYED | MF_DISABLED);
	}
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}


void CExRabbitDlg::OnNMClickListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	crtCLRDDSid = row;
	updateInfo();
	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �Ҽ������ɫ�˵�
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListClr(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU);
	pPopup = menu.GetSubMenu(row >= 0 ? 7 : 8);
	if (row < 0 && !fileOpen) {
		pPopup->EnableMenuItem(ID_CLRMENU2_INSERT, MF_GRAYED | MF_DISABLED);
		pPopup->EnableMenuItem(ID_CLRMENU2_LOADPALETTE, MF_GRAYED | MF_DISABLED);
		pPopup->EnableMenuItem(ID_CLRMENU2_NEWPALETTE, MF_GRAYED | MF_DISABLED);
	}
	if (row >= 0 && io.version == V4) {
		pPopup->EnableMenuItem(ID_CLRMENU_EXTRACTALLPALETTE, MF_DISABLED | MF_GRAYED);
		pPopup->EnableMenuItem(ID_CLRMENU_NEWPALETTE, MF_DISABLED | MF_GRAYED);
	}
	if (row < 0 && io.version == V4) {
		pPopup->EnableMenuItem(ID_CLRMENU2_NEWPALETTE, MF_DISABLED | MF_GRAYED);
	}
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}


void CExRabbitDlg::OnNMClickListDds(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	crtCLRDDSid = row;
	updateInfo();
	draw(true);
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListDds(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListDds(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU);
	pPopup = menu.GetSubMenu(row >= 0 ? 5 : 6);
	if (row < 0 && !fileOpen) {
		pPopup->EnableMenuItem(ID_DDSMENU2_INSERT, MF_GRAYED | MF_DISABLED);
	}
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}


void CExRabbitDlg::OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	crtPICid = row;
	updateInfo();

	if (row < 0)
		return;
	PICinfo pi;
	io.GetPICInfo(row, pi);
	dlgSetXY.m_e1.SetWindowText(NumToCStr(pi.get_basePt().get_X()) + L"," + NumToCStr(pi.get_basePt().get_Y()));

	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListPic(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU);
	pPopup = menu.GetSubMenu(row >= 0 ? 3 : 4);
	//��v4v6������ȡ������
	if (row < 0 && !fileOpen) {
		pPopup->EnableMenuItem(ID_PICMENU2_INSERT, MF_GRAYED | MF_DISABLED);
	}
	if (row >= 0 && !(io.version == V4 || io.version == V6)) {
		pPopup->EnableMenuItem(ID_PICMENU_EXTRACTALLINDEX, MF_DISABLED | MF_GRAYED);
		pPopup->EnableMenuItem(ID_PICMENU_EXTRACTINDEX, MF_DISABLED | MF_GRAYED);
	}
	if (row >= 0 && io.PICcontent[row].get_format() == LINK) {
		pPopup->EnableMenuItem(ID_PICMENU_EXTRACTINDEX, MF_DISABLED | MF_GRAYED);
		pPopup->EnableMenuItem(ID_PICMENU_SETPARA, MF_DISABLED | MF_GRAYED);
	}
	if (row >= 0 && (io.version == V5 || io.PICcontent[row].get_format() == LINK)) {
		pPopup->EnableMenuItem(ID_PICMENU_EXPAND, MF_DISABLED | MF_GRAYED);
	}
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}

void CExRabbitDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x = point.x - 170;
	int y = point.y - 190;
	COLORREF clrr;
	CString str1;
	if (point.x > 0 && point.y > 0) {
		m_edInfo6.SetWindowText(L"x:" + NumToCStr(x - basePoint.get_X()) + L" y:" + NumToCStr(y - basePoint.get_Y()));
		clrr = GetPixel(this->GetDC()->m_hDC, point.x, point.y);
		str1.Format(L"0x%02X%02X%02X", GetRValue(clrr), GetGValue(clrr), GetBValue(clrr));
		m_edInfo7.SetWindowText(str1);

		CImage img;
		int i, j;
		img.Create((width - 180) / 10, 20, 32);
		UCHAR* pst = (UCHAR*)img.GetBits();
		int pit = img.GetPitch();

		for (i = 0; i < (width - 180) / 10; i++) {
			for (j = 0; j < 20; j++) {
				if (i == 0 || j == 0) {
					*(pst + pit*j + 4 * i + 0) = 0xB0;
					*(pst + pit*j + 4 * i + 1) = 0xB0;
					*(pst + pit*j + 4 * i + 2) = 0xB0;
				}
				else if (i == (width - 180) / 10 - 1 || j == 19) {
					*(pst + pit*j + 4 * i + 0) = 0xFF;
					*(pst + pit*j + 4 * i + 1) = 0xFF;
					*(pst + pit*j + 4 * i + 2) = 0xFF;
				}
				else {
					*(pst + pit*j + 4 * i + 0) = GetBValue(clrr);
					*(pst + pit*j + 4 * i + 1) = GetGValue(clrr);
					*(pst + pit*j + 4 * i + 2) = GetRValue(clrr);
				}
			}
		}
		img.Draw(this->GetDC()->m_hDC, 170 + (width - 180) * 6 / 10 + 30, height - 30);
		img.Destroy();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CExRabbitDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.x > 170 && point.y > 200) {
		CMenu menu, *pPopup;
		menu.LoadMenu(IDR_MENU);
		pPopup = menu.GetSubMenu(mixMode ? 10 : 9);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCH_ABS, dispModeAbs ? MF_CHECKED : MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCHINDEX, dispModeIndex ? MF_CHECKED : MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCHDDS, dispModeDds ? MF_CHECKED : MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU2_SWITCH_ABS, dispModeAbs ? MF_CHECKED : MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU2_SHOWALL, dispModeShowAll ? MF_CHECKED : MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SHOWCOMPARE, dispModeCompare ? MF_CHECKED : MF_UNCHECKED);
		CPoint myPoint;
		ClientToScreen(&myPoint);
		GetCursorPos(&myPoint); //���λ��  
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	}
	CDialogEx::OnRButtonUp(nFlags, point);
}


void CExRabbitDlg::OnDeltaposSpinX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	basePoint.set_X(basePoint.get_X() + pNMUpDown->iDelta);
	m_edX.SetWindowText(NumToCStr(basePoint.get_X()));
	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnDeltaposSpinY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	basePoint.set_Y(basePoint.get_Y() + pNMUpDown->iDelta);
	m_edY.SetWindowText(NumToCStr(basePoint.get_Y()));
	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnCbnSelchangeComboPro()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	updateCLRlist();
	dlgColor.setClr(&io.paletteData[m_cbPro.GetCurSel()]);
	dlgColor.draw();
	draw();
}

void CExRabbitDlg::draw(bool isDDS) {
	drawDDS = isDDS;
	if (dispModeShowAll) {
		AfxBeginThread(drawThread2, (LPVOID)this);
	}
	else if (drawDDS) {
		AfxBeginThread(drawDDSThread, (LPVOID)this);
	}
	else {
		AfxBeginThread(drawThread, (LPVOID)this);
	}
}
void CExRabbitDlg::transform(IMGversion vers) {
	to_ver = vers;
	AfxBeginThread(transformThread, (LPVOID)this);
}
UINT lazyThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	while (dlg->m_hWnd) {
		Sleep(10);
		if (dlg->lazyTime > 0) {
			dlg->lazyTime--;
		}
	}
	return 0;
}
UINT drawThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if (dlg->drawing)
		return 0;
	dlg->drawing = 1;
	int row = dlg->m_lPicture.GetSelectionMark();
	int clrRow = dlg->m_lColor.GetSelectionMark();
	int ddsRow = dlg->m_lDDS.GetSelectionMark();
	int cbpro = dlg->m_cbPro.GetCurSel();
	int i, j, k;
	int tx, ty;
	int canw = dlg->width - 180;
	int canh = dlg->height - 240;
	int clrBlockSize = 10;
	int clct, cp;
	int m, n;
	IMGobject *io = &(dlg->io);
	PICinfo po;
	DDSinfo di;
	CImage img;
	matrix mat, canvas;
	color clr;
	if (io->version == V5 || io->version == V4)
		cbpro = 0;
	//���ƻ�������
	canvas.allocate(canh, canw);
	canvas.fill(color(0xff, 0x33, 0x33, 0x33));
	//������ɫ��
	if (io->version == V4 || io->version == V6) {
		cp = io->paletteData.getCount();
		if (cp > 0) {
			clct = io->paletteData[0].size();
			if (clct > 0) {
				clrBlockSize = canw / clct;
			}
		}
		if (clrBlockSize > 10)
			clrBlockSize = 10;
		for (i = 0; i < cp; i++) {
			clct = io->paletteData[i].size();
			for (j = 0; j < clct; j++) {
				for (m = 0; m < clrBlockSize; m++) {
					for (n = 0; n < clrBlockSize; n++) {
						canvas.setElem(canh - clrBlockSize*cp + clrBlockSize*i + m, canw - clrBlockSize*clct + clrBlockSize*j + n, io->paletteData[i][j]);
					}
				}
			}
		}
		tx = canw - clrBlockSize*clct + clrBlockSize*clrRow;
		ty = canh - clrBlockSize*cp + clrBlockSize*cbpro;

		for (m = 0; m < clrBlockSize; m++) {
			canvas.setElem(ty + m, tx, color(0xff, 0xff, 0xff, 0xff));
			canvas.setElem(ty, tx + m, color(0xff, 0xff, 0xff, 0xff));
			canvas.setElem(ty + clrBlockSize - 1, tx + m, color(0xff, 0xff, 0xff, 0xff));
			canvas.setElem(ty + m, tx + clrBlockSize - 1, color(0xff, 0xff, 0xff, 0xff));
		}
	}
	if (dlg->dispModeDds && io->version == V5) {
		//��ͨ��ͼ���ơ�V5ddsģʽ
		if (row == -1) {
			dlg->drawing = 0;
			return 0;
		}
		io->GetPICInfo(row, po);
		io->GetDDSInfo(po.get_DDSIDused(), di);
		io->DDSextract(po.get_DDSIDused(), mat);
		for (i = 0; i < canh; i++) {
			for (j = 0; j < canw; j++) {
				if (dlg->dispModeAbs) {
					tx = i - dlg->basePoint.get_Y();	//��ʵ����
					ty = j - dlg->basePoint.get_X();	//��ʵ����
				}
				else {
					tx = i;	//��ʵ����
					ty = j;	//��ʵ����
				}
				if (tx < mat.getRowCount() && ty < mat.getColumnCount()) {
					clr = mat.getElem(tx, ty);
					if (ty < po.get_DDSpointLT().get_X() || tx < po.get_DDSpointLT().get_Y() || ty >= po.get_DDSpointRB().get_X() || tx >= po.get_DDSpointRB().get_Y())
						clr.set_A(clr.get_A() / 4);
					clr.mixWith(canvas.getElem(i, j), dlg->dispMixMode);
					canvas.setElem(i, j, clr);
				}
			}
		}
	}
	else {
		//������ͨ��ͼ
		if (row == -1) {
			dlg->drawing = 0;
			return 0;
		}
		//���ƶԱ�ͼ
		if (dlg->dispModeCompare && dlg->dispModeAbs) {
			int row1 = row;
			IMGobject *ioComp = &dlg->ioComp;
			if (row1 < ioComp->indexSize) {
				//���ioTemp�д��ڴ�֡
				ioComp->GetPICInfo(row1, po);
				if (po.get_format() == LINK)
					row1 = ioComp->linkFind(row1);
				ioComp->GetPICInfo(row1, po);
				ioComp->PICextract(row1, mat, 0);
				for (i = 0; i < canh; i++) {
					for (j = 0; j < canw; j++) {
						tx = i - po.get_basePt().get_Y() - dlg->basePoint.get_Y();	//��ʵ����
						ty = j - po.get_basePt().get_X() - dlg->basePoint.get_X();	//��������
						if (tx < mat.getRowCount() && ty < mat.getColumnCount()) {
							clr = mat.getElem(tx, ty);
							if (clr.get_A() > 0x7f)
								clr.set_A(0x4f);
							clr.mixWith(canvas.getElem(i, j), dlg->dispMixMode);
							canvas.setElem(i, j, clr);
						}
					}
				}
				mat.release();	//���õģ�Ҫ��
			}
		}
		//����ͼ
		io->GetPICInfo(row, po);
		if (po.get_format() == LINK)
			row = io->linkFind(row);
		io->GetPICInfo(row, po);
		io->PICextract(row, mat, (i32)cbpro);
		//V4V6�滻��ɫ
		if (dlg->dispModeIndex && (io->version == V4 || io->version == V6)) {
			//V4\V6��������ͼģʽ
			b8 temp = 0xff;
			for (k = 0; k < io->paletteData[cbpro].size(); k++) {
				if (dlg->useColorTable) {
					mat.elemReplace(
						io->paletteData[cbpro][k],
						dlg->dlgColor.chosenClr[k] ? color(0, 0, 0xff) : color(temp, temp, temp)
					);
				}
				else {
					mat.elemReplace(
						io->paletteData[cbpro][k],
						dlg->m_lColor.GetItemState(k, LVIS_SELECTED) == LVIS_SELECTED ? color(0, 0, 0xff) : color(temp, temp, temp)
					);
				}
				temp -= 155 / io->paletteData[cbpro].size();
			}
		}

		for (i = 0; i < canh; i++) {
			for (j = 0; j < canw; j++) {
				if (dlg->dispModeAbs) {
					tx = i - po.get_basePt().get_Y() - dlg->basePoint.get_Y();	//��ʵ����
					ty = j - po.get_basePt().get_X() - dlg->basePoint.get_X();	//��������
				}
				else {
					tx = i;
					ty = j;
				}
				if (tx < mat.getRowCount() && ty < mat.getColumnCount()) {
					clr = mat.getElem(tx, ty);
					clr.mixWith(canvas.getElem(i, j), dlg->dispMixMode);
					canvas.setElem(i, j, clr);
				}
			}
		}
	}
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();

	for (i = 0; i < canw; i++) {
		for (j = 0; j < canh; j++) {
			*(pst + pit*j + 4 * i + 0) = canvas[j][i].get_B();
			*(pst + pit*j + 4 * i + 1) = canvas[j][i].get_G();
			*(pst + pit*j + 4 * i + 2) = canvas[j][i].get_R();
		}
	}
	img.Draw(dlg->GetDC()->m_hDC, 170, 200);
	img.Destroy();
	mat.release();
	dlg->drawing = 0;
	canvas.release();
	return 0;
}
UINT drawDDSThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if (dlg->drawing)
		return 0;
	dlg->drawing = 1;
	int ddsRow = dlg->m_lDDS.GetSelectionMark();
	int i, j;
	int tx, ty;
	int canw = dlg->width - 180;
	int canh = dlg->height - 240;
	int clrBlockSize = 10;
	IMGobject *io = &(dlg->io);
	PICinfo po;
	DDSinfo di;
	CImage img;
	matrix mat, canvas;
	color clr;
	//���ƻ�������
	canvas.allocate(canh, canw);
	canvas.fill(color(0xff, 0x33, 0x33, 0x33));
	//DDS��ͼ����
	if (ddsRow == -1) {
		dlg->drawing = 0;
		return 0;
	}
	io->GetDDSInfo(ddsRow, di);
	io->DDSextract(ddsRow, mat);
	for (i = 0; i < canh; i++) {
		for (j = 0; j < canw; j++) {
			if (dlg->dispModeAbs) {//�����Ȩ
				tx = i - dlg->basePoint.get_Y();	//��ʵ����
				ty = j - dlg->basePoint.get_X();	//��������
			}
			else {//��������
				tx = i;
				ty = j;
			}
			if (tx < mat.getRowCount() && ty < mat.getColumnCount()) {
				clr = mat.getElem(tx, ty);
				clr.mixWith(canvas.getElem(i, j), dlg->dispMixMode);
				canvas.setElem(i, j, clr);
			}
		}
	}
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for (i = 0; i < canw; i++) {
		for (j = 0; j < canh; j++) {
			*(pst + pit*j + 4 * i + 0) = canvas[j][i].get_B();
			*(pst + pit*j + 4 * i + 1) = canvas[j][i].get_G();
			*(pst + pit*j + 4 * i + 2) = canvas[j][i].get_R();
		}
	}
	img.Draw(dlg->GetDC()->m_hDC, 170, 200);
	img.Destroy();
	mat.release();
	dlg->drawing = 0;
	canvas.release();
	return 0;
}
UINT drawThread2(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if (dlg->drawing) {
		return 0;
	}
	dlg->drawing = 1;
	int k;
	int canw = dlg->width - 180;
	int canh = dlg->height - 240;
	NPKobject *no = &dlg->no;
	IMGobject *ioList = new IMGobject[no->count];
	void* list[3] = { para, NULL, NULL };
	AfxBeginThread(drawThread_bg, para);
	int lll[2] = { 10,20 };
	for (k = 0; k < no->count; k++) {
		if (!no->IMGextract(k, ioList[k])) {
			continue;
		}
		list[1] = (void*)&ioList[k];
		list[2] = (void*)&lll[k % 2];
		AfxBeginThread(drawThread_fg, (void*)list);
		Sleep(3);//����ʱ����thread��ȫ���յ����������ͷ�`3���뼴��
		ioList[k].Release();
	}
	delete[] ioList;
	dlg->drawing = 0;
	return 0;
}
UINT drawThread_bg(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	int i, j, canw, canh;
	CImage img;
	matrix canvas;
	color clr;
	//���ƻ�������
	canw = dlg->width - 180;
	canh = dlg->height - 240;
	canvas.allocate(canh, canw);
	canvas.fill(color(0xff, 0x33, 0x33, 0x33));
	img.Create(canw, canh, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for (i = 0; i < canw; i++) {
		for (j = 0; j < canh; j++) {
			*(pst + pit*j + 4 * i + 0) = canvas[j][i].get_B();
			*(pst + pit*j + 4 * i + 1) = canvas[j][i].get_G();
			*(pst + pit*j + 4 * i + 2) = canvas[j][i].get_R();
		}
	}
	img.Draw(dlg->GetDC()->m_hDC, 170, 200);
	img.Destroy();
	canvas.release();
	return 0;
}
UINT drawThread_fg(PVOID para) {
	PVOID *pptr = (PVOID *)para;
	void* plist[3] = { pptr[0], pptr[1], pptr[2] };
	CExRabbitDlg* dlg = (CExRabbitDlg*)pptr[0];
	IMGobject io = *(IMGobject *)pptr[1];
	int iii = *(int *)pptr[2];
	int row = dlg->m_lPicture.GetSelectionMark();
	int clrRow = dlg->m_lColor.GetSelectionMark();
	int cbpro = dlg->m_cbPro.GetCurSel();
	if (row == -1) {
		dlg->drawing = 0;
		return 0;
	}
	PICinfo po;
	int i, j, k, tx, ty;
	CImage img;
	matrix mat, canvas;
	color clr;
	//����ǰ��
	int canw = dlg->width - 180;
	int canh = dlg->height - 240;
	canvas.allocate(canh, canw);
	//����ͼ
	io.GetPICInfo(row, po);
	if (po.get_format() == LINK)
		row = io.linkFind(row);
	io.GetPICInfo(row, po);
	if (io.version == V5 || io.version == V4)
		cbpro = 0;
	io.PICextract(row, mat, (i32)cbpro);
	for (i = 0; i < canh; i++) {
		for (j = 0; j < canw; j++) {
			if (dlg->dispModeAbs) {
				tx = i - po.get_basePt().get_Y() - dlg->basePoint.get_Y();	//��ʵ����
				ty = j - po.get_basePt().get_X() - dlg->basePoint.get_X();	//��������
			}
			else {
				tx = i;
				ty = j;
			}
			if (tx < mat.getRowCount() && ty < mat.getColumnCount()) {
				clr = mat.getElem(tx, ty);
				clr.mixWith(canvas.getElem(i, j), dlg->dispMixMode);
				canvas.setElem(i, j, clr);
			}
		}
	}
	img.Create(canw, canh, 32);
	img.SetHasAlphaChannel(true);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for (i = 0; i < canw; i++) {
		for (j = 0; j < canh; j++) {
			*(pst + pit*j + 4 * i + 0) = canvas[j][i].get_B()*canvas[j][i].get_A() / 0xff;
			*(pst + pit*j + 4 * i + 1) = canvas[j][i].get_G()*canvas[j][i].get_A() / 0xff;
			*(pst + pit*j + 4 * i + 2) = canvas[j][i].get_R()*canvas[j][i].get_A() / 0xff;
			*(pst + pit*j + 4 * i + 3) = canvas[j][i].get_A();
		}
	}
	img.Draw(dlg->GetDC()->m_hDC, 170, 200);
	img.Destroy();
	mat.release();
	canvas.release();
	io.Release();
	return 0;
}


UINT playThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if (dlg->playing) {
		return 0;
	}
	int row = dlg->m_lPicture.GetSelectionMark();
	if (row < 0)
		return 0;
	dlg->playing = 1;
	while (row < dlg->m_lPicture.GetItemCount()) {
		if (row > 0) {
			dlg->m_lPicture.SetItemState(row - 1, 0, LVIS_FOCUSED | LVIS_SELECTED);
		}
		dlg->m_lPicture.SetItemState(row, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
		dlg->m_lPicture.SetSelectionMark(row);
		dlg->draw();
		row++;
		Sleep(100);
		if (dlg->playing == 0) {
			break;
		}
	}
	dlg->playing = 0;
	return 0;
}

UINT transformThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	CString info, title, tmp;
	if (dlg->converting) {
		info.LoadStringW(IDS_STRING_LASTCONVERTOPERATIONPERFORMING);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"��һ��ת�����������С�", L"��ʾ��");
		return 0;
	}
	dlg->converting = 1;
	int row = dlg->crtIMGid;
	int p;
	str fn, ser;
	IMGobject io, _io;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	info.LoadStringW(IDS_STRING_CONVERTING);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->dlgBar.setTitle(info);
	//dlg->dlgBar.setTitle(L"ת����");
	dlg->no.IMGextract(row, io);
	if (io.version == V6) {
		if (io.paletteData.getCount() <= 0) {
			info.LoadStringW(IDS_STRING_NOPALETTEDATA);
			dlg->MessageBox(info, title);
			//dlg->MessageBox(L"ת��ʧ�ܣ�û�е�ɫ�����ݣ�", L"��ʾ");
			dlg->dlgBar.ShowWindow(SW_HIDE);
			dlg->converting = 0;
			return 0;
		}
		fn = dlg->no.content[row].get_imgname();
		dlg->no.IMGremove(row);
		{
			dlg->m_lIMG.DeleteItem(row);
		}
		for (p = 0; p < io.paletteData.getCount(); p++) {
			tmp.LoadStringW(IDS_STRING_PERFORMINGPALETTENUM);
			info.Format(tmp, NumToCStr(p + 1), NumToCStr(io.paletteData.getCount()));
			dlg->dlgBar.setInfo(info);
			//dlg->dlgBar.setInfo(L"���ڴ����" + NumToCStr(p + 1) + L"����ɫ����,��" + NumToCStr(io.paletteData.getCount()) + L"��");
			dlg->dlgBar.setPosi((p + 1) * 1000 / io.paletteData.getCount());
			io.ConvertTo(_io, dlg->to_ver, p);
			dlg->no.IMGinsert(row + p, _io, KoishiTitle::imgAddV4Num(fn, p));
			{
				dlg->m_lIMG.InsertItem(row + p, shorten(StrToCStr(KoishiTitle::imgAddV4Num(fn, p))));
			}
			_io.Release();
		}
	}
	else {
		if (io.ConvertTo(_io, dlg->to_ver)) {
			dlg->no.IMGreplace(row, _io);
		}
		else {
			info.LoadStringW(IDS_STRING_PALETTEOVERFLOW);
			dlg->MessageBox(info, title);
			//dlg->MessageBox(L"ת��ʧ�ܣ���ɫ�������", L"��ʾ");
			dlg->dlgBar.ShowWindow(SW_HIDE);
			dlg->converting = 0;
			return 0;
		}
	}
	dlg->io.Release();
	dlg->no.IMGextract(row, dlg->io);
	info.LoadStringW(IDS_STRING_CONVERTFINISHED);
	dlg->MessageBox(info, title);
	//dlg->MessageBox(L"ת����ϣ�", L"��ʾ��");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->switchIMGver(dlg->to_ver);
	dlg->updatePIClist();
	dlg->updateDDSlist();
	dlg->updateNPKInfo();
	dlg->updateCLRlist();
	dlg->updateIMGInfo();
	dlg->converting = 0;
	return 0;
}

UINT extractThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	CString info, title, tmp;
	if (dlg->extracting) {
		info.LoadStringW(IDS_STRING_LASTEXTRACTINGINPROGRESS);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"��һ����ȡ���������С�", L"��ʾ��");
		return 0;
	}
	dlg->extracting = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	info.LoadStringW(IDS_STRING_EXTRACTING);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->dlgBar.setTitle(info);
	//dlg->dlgBar.setTitle(L"��ȡ��");
	for (int i = 0; i < dlg->io.indexCount; i++) {
		str fn;
		CString filePath;
		CString fileName;
		matrix mat;
		tmp.LoadStringW(IDS_STRING_PERFORMINGFRAMENUM);
		info.Format(tmp, NumToCStr(i + 1), NumToCStr(dlg->io.indexCount));
		dlg->dlgBar.setInfo(info);
		//dlg->dlgBar.setInfo(L"������ȡ��" + NumToCStr(i + 1) + L"��,��" + NumToCStr(dlg->io.indexCount) + L"��");
		dlg->dlgBar.setPosi((i + 1) * 1000 / dlg->io.indexCount);
		if (dlg->io.version == V6) {
			fileName = getOutPutDir(dlg->fileNPKname, dlg->fileIMGname, dlg->m_cbPro.GetCurSel()) + L"֡��" + NumToCStr(i) + L".PNG";
		}
		else {
			fileName = getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"֡��" + NumToCStr(i) + L".PNG";
		}
		CStrToStr(fileName, fn);
		dlg->io.PICextract(i, mat, dlg->m_cbPro.GetCurSel());
		mat.makePNG(fn);
		mat.release();
	}
	info.LoadStringW(IDS_STRING_SAVEDTOFOLDER);
	dlg->MessageBox(info + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname), title);
	//dlg->MessageBox(L"�ѱ��浽�ļ���" + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"���ˡ�", L"��ʾ��");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->extracting = 0;
	return 0;
}

UINT extractDDSPNGThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	CString info, title, tmp;
	if (dlg->extracting) {
		info.LoadStringW(IDS_STRING_LASTEXTRACTINGINPROGRESS);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"��һ����ȡ���������С�", L"��ʾ��");
		return 0;
	}
	dlg->extracting = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	info.LoadStringW(IDS_STRING_EXTRACTING);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->dlgBar.setTitle(info);
	//dlg->dlgBar.setTitle(L"��ȡ��");
	for (int i = 0; i < dlg->io.V5_DDSCount; i++) {
		str fn;
		CString filePath;
		CString fileName;
		matrix mat;
		tmp.LoadStringW(IDS_STRING_PERFORMINGFRAMENUM);
		info.Format(tmp, NumToCStr(i + 1), NumToCStr(dlg->io.V5_DDSCount));
		dlg->dlgBar.setInfo(info);
		//dlg->dlgBar.setInfo(L"������ȡ��" + NumToCStr(i + 1) + L"��,��" + NumToCStr(dlg->io.V5_DDSCount) + L"��");
		dlg->dlgBar.setPosi((i + 1) * 1000 / dlg->io.V5_DDSCount);
		fileName = getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"DDS" + NumToCStr(i) + L".PNG";
		CStrToStr(fileName, fn);
		dlg->io.DDSextract(i, mat);
		mat.makePNG(fn);
		mat.release();
	}
	info.LoadStringW(IDS_STRING_SAVEDTOFOLDER);
	dlg->MessageBox(info + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname), title);
	//dlg->MessageBox(L"�ѱ��浽�ļ���" + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"���ˡ�", L"��ʾ��");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->extracting = 0;
	return 0;
}
UINT extractDDSThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	CString info, title, tmp;
	if (dlg->extracting) {
		info.LoadStringW(IDS_STRING_LASTEXTRACTINGINPROGRESS);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"��һ����ȡ���������С�", L"��ʾ��");
		return 0;
	}
	dlg->extracting = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	info.LoadStringW(IDS_STRING_EXTRACTING);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->dlgBar.setTitle(info);
	//dlg->dlgBar.setTitle(L"��ȡ��");
	for (int i = 0; i < dlg->io.V5_DDSCount; i++) {
		str fn;
		CString filePath;
		CString fileName;
		stream s, s1;
		tmp.LoadStringW(IDS_STRING_PERFORMINGFRAMENUM);
		info.Format(tmp, NumToCStr(i + 1), NumToCStr(dlg->io.V5_DDSCount));
		dlg->dlgBar.setInfo(info);
		//dlg->dlgBar.setInfo(L"������ȡ��" + NumToCStr(i + 1) + L"��,��" + NumToCStr(dlg->io.V5_DDSCount) + L"��");
		dlg->dlgBar.setPosi((i + 1) * 1000 / dlg->io.V5_DDSCount);
		fileName = getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"DDS��ͼ" + NumToCStr(i) + L".dds";
		CStrToStr(fileName, fn);
		dlg->io.GetDDSData(i, s);
		s.uncompressData(s1, COMP_ZLIB2);
		s1.makeFile(fn);
		s.release();
		s.release();
	}
	info.LoadStringW(IDS_STRING_SAVEDTOFOLDER);
	dlg->MessageBox(info + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname), title);
	//dlg->MessageBox(L"�ѱ��浽�ļ���" + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"���ˡ�", L"��ʾ��");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->extracting = 0;
	return 0;
}
UINT extractPIDThread(PVOID para) {
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	CString info, title, tmp;
	if (dlg->extracting) {
		info.LoadStringW(IDS_STRING_LASTEXTRACTINGINPROGRESS);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"��һ����ȡ���������С�", L"��ʾ��");
		return 0;
	}
	dlg->extracting = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	info.LoadStringW(IDS_STRING_EXTRACTING);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->dlgBar.setTitle(info);
	//dlg->dlgBar.setTitle(L"��ȡ��");
	for (int i = 0; i < dlg->io.indexCount; i++) {
		str fn;
		CString fileName = getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"֡��" + NumToCStr(i) + L".PID";
		CStrToStr(fileName, fn);
		stream s, s1, sHead;
		PICinfo pi;
		tmp.LoadStringW(IDS_STRING_PERFORMINGFRAMENUM);
		info.Format(tmp, NumToCStr(i + 1), NumToCStr(dlg->io.indexCount));
		dlg->dlgBar.setInfo(info);
		//dlg->dlgBar.setInfo(L"������ȡ��" + NumToCStr(i + 1) + L"��,��" + NumToCStr(dlg->io.indexCount) + L"��");
		dlg->dlgBar.setPosi((i + 1) * 1000 / dlg->io.indexCount);
		dlg->io.GetPICInfo(i, pi);
		dlg->io.GetPICData(i, s);
		if (pi.get_format() == ARGB1555) {
			s.uncompressData(s1, pi.get_comp());
			sHead.allocate(16);
			sHead.push((b32)0x73696F4B);
			sHead.push((b32)0x78456968);
			sHead.push(pi.get_picSize().get_W());
			sHead.push(pi.get_picSize().get_H());
			s1.insertStream(sHead, 16, 0);
			s1.makeFile(fn);
		}
		s.release();
		s1.release();
		sHead.release();
	}
	info.LoadStringW(IDS_STRING_SAVEDTOFOLDER);
	dlg->MessageBox(info + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname), title);
	//dlg->MessageBox(L"�ѱ��浽�ļ���" + getOutPutDir(dlg->fileNPKname, dlg->fileIMGname) + L"���ˡ�", L"��ʾ��");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->extracting = 0;
	return 0;
}
UINT canvasThread(PVOID para) {
	CExRabbitDlg * dlg = (CExRabbitDlg *)para;
	CString info, title, tmp;
	if (dlg->expanding) {
		info.LoadStringW(IDS_STRING_LASTEXPANDCROPINPROGRESS);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"��һ������/���в��������С�", L"��ʾ��");
		return 0;
	}
	dlg->expanding = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	info.LoadStringW(IDS_STRING_PERFORMING);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->dlgBar.setTitle(info);
	//dlg->dlgBar.setTitle(L"������");
	int x1 = dlg->canvasPara.x1;
	int y1 = dlg->canvasPara.y1;
	int x2 = dlg->canvasPara.x2;
	int y2 = dlg->canvasPara.y2;
	for (int i = 0; i < dlg->io.indexCount; i++) {
		matrix mat, mat2, mat3;
		stream s;
		PICinfo pi;
		dlg->io.GetPICInfo(i, pi);
		if (pi.get_format() == LINK)
			continue;
		dlg->io.PICextract(i, mat, 0);
		int x10 = pi.get_basePt().get_X();
		int y10 = pi.get_basePt().get_Y();
		int x20 = pi.get_basePt().get_X() + pi.get_picSize().get_W() - 1;
		int y20 = pi.get_basePt().get_Y() + pi.get_picSize().get_H() - 1;
		int x1_ = min(x1, x10);
		int x2_ = max(x2, x20);
		int y1_ = min(y1, y10);
		int y2_ = max(y2, y20);
		mat2.allocate(y2_ - y1_ + 1, x2_ - x1_ + 1);
		mat2.putFore(mat, LAY);
		mat2.elemMoveHonz(x10 - x1_);
		mat2.elemMoveVert(y10 - y1_);
		mat2.getSubMatrix(mat3, y1 - y1_, y2 - y1_ + 1, x1 - x1_, x2 - x1_ + 1);
		dlg->io.PICpreprocess(mat3, s, pi);
		point newPt(x1, y1);
		pi.set_basePt(newPt);
		dlg->io.PICreplace(i, pi, s);
		{
			dlg->m_lPicture.SetItemText(i, 1, FmtToCStr(dlg->io.PICcontent[i].get_format(), dlg->io.version));
			dlg->m_lPicture.SetItemText(i, 2, PtToCStr(dlg->io.PICcontent[i].get_basePt()));
			dlg->m_lPicture.SetItemText(i, 3, SzToCStr(dlg->io.PICcontent[i].get_picSize()));
			dlg->m_lPicture.SetItemText(i, 4, SzToCStr(dlg->io.PICcontent[i].get_frmSize()));
		}
		tmp.LoadStringW(IDS_STRING_PERFORMINGFRAMENUM);
		info.Format(tmp, NumToCStr(i + 1), NumToCStr(dlg->io.indexCount));
		dlg->dlgBar.setInfo(info);
		//dlg->dlgBar.setInfo(L"���ڴ����" + NumToCStr(i + 1) + L"֡,��" + NumToCStr(dlg->io.indexCount) + L"֡");
		dlg->dlgBar.setPosi((i + 1) * 1000 / dlg->io.indexCount);
		s.release();
		mat.release();
		mat2.release();
		mat3.release();
	}
	info.LoadStringW(IDS_STRING_WORKINGFINISHED);
	dlg->MessageBox(info, title);
	//dlg->MessageBox(L"�������������", L"��ʾ��");
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->expanding = 0;
	return 0;
}
UINT uncanvasThread(PVOID para) {
	CExRabbitDlg * dlg = (CExRabbitDlg *)para;
	CString info, title, tmp;
	if (dlg->expanding) {
		info.LoadStringW(IDS_STRING_LASTEXPANDCROPINPROGRESS);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"��һ������/���в��������С�", L"��ʾ��");
		return 0;
	}
	bool emptyWarn = false;
	dlg->expanding = 1;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	info.LoadStringW(IDS_STRING_PERFORMING);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->dlgBar.setTitle(info);
	//dlg->dlgBar.setTitle(L"������");
	for (int i = 0; i < dlg->io.indexCount; i++) {
		matrix mat, mat2;
		stream s;
		PICinfo pi;
		dlg->io.GetPICInfo(i, pi);
		if (pi.get_format() == LINK)
			continue;
		dlg->io.PICextract(i, mat, 0);
		b32 x1_, y1_, x2_, y2_;
		mat.getElemHonzBound(x1_, x2_);
		mat.getElemVertBound(y1_, y2_);
		if (x1_ >= x2_) {
			//��ȫ��
			emptyWarn = true;
		}
		else {
			mat.getSubMatrix(mat2, y1_, y2_ + 1, x1_, x2_ + 1);
			dlg->io.PICpreprocess(mat2, s, pi);
			point newPt(pi.get_basePt().get_X() + x1_, pi.get_basePt().get_Y() + y1_);
			pi.set_basePt(newPt);
			dlg->io.PICreplace(i, pi, s);
			{
				dlg->m_lPicture.SetItemText(i, 1, FmtToCStr(dlg->io.PICcontent[i].get_format(), dlg->io.version));
				dlg->m_lPicture.SetItemText(i, 2, PtToCStr(dlg->io.PICcontent[i].get_basePt()));
				dlg->m_lPicture.SetItemText(i, 3, SzToCStr(dlg->io.PICcontent[i].get_picSize()));
				dlg->m_lPicture.SetItemText(i, 4, SzToCStr(dlg->io.PICcontent[i].get_frmSize()));
			}
		}
		tmp.LoadStringW(IDS_STRING_PERFORMINGFRAMENUM);
		info.Format(tmp, NumToCStr(i + 1), NumToCStr(dlg->io.indexCount));
		dlg->dlgBar.setInfo(info);
		//dlg->dlgBar.setInfo(L"����������" + NumToCStr(i + 1) + L"֡,��" + NumToCStr(dlg->io.indexCount) + L"֡");
		dlg->dlgBar.setPosi((i + 1) * 1000 / dlg->io.indexCount);
		s.release();
		mat.release();
		mat2.release();
	}
	if (emptyWarn) {
		info.LoadStringW(IDS_STRING_EMPTYFRAMEEXISTS);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"�������������\r\n���Ǵ��ڲ��ܽ��������Ŀ�֡�������Լ�ȥ��������", L"��ʾ��");
	}
	else {
		info.LoadStringW(IDS_STRING_WORKINGFINISHED);
		dlg->MessageBox(info, title);
		//dlg->MessageBox(L"�������������", L"��ʾ��");
	}
	dlg->dlgBar.ShowWindow(SW_HIDE);
	dlg->expanding = 0;
	return 0;
}
//////////////////////////////////////////////
/*************�˵������¼�*******************/
//////////////////////////////////////////////
void CExRabbitDlg::OnMainMenuNew()
{
	// TODO: �ڴ���������������
	dlgNew.OnBnClickedCheck1();
	MOVEW(dlgNew);
	dlgNew.ShowWindow(SW_SHOW);
}

void CExRabbitDlg::OnMainMenuOpen()
{
	// TODO: �ڴ���������������
	// TODO: ���ļ�
	CString defExt = _T("��Դ�ļ�(*.NPK,*.IMG,*.MPL)|*.NPK;*.IMG;*.MPL");
	CString extFilter = _T("��Դ�ļ�(*.NPK,*.IMG,*.MPL)|*.NPK;*.IMG;*.MPL|NPK�ļ�(*.NPK)|*.NPK|IMG�ļ�(*.IMG)|*.IMG|ƴ�Ϸ���(*.MPL)|*.MPL||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	str fn;
	CString fileName, fmt;
	CString info, title;
	defExt.LoadStringW(IDS_STRING_RESOURCEFILE);
	extFilter.LoadStringW(IDS_STRING_RESOURCEFILES2);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (dlg.DoModal() == IDOK) {
		fileName = dlg.GetPathName();
		fmt = fileName.Right(1);
		CStrToStr(fileName, fn);
		if (fmt == L"K" || fmt == L"k") {
			no.release();
			if (no.loadFile(fn)) {
				info.LoadStringW(IDS_STRING_READFINISHED);
				MessageBox(info, title);
				//MessageBox(L"��ȡ��ϣ�");
			}
			else {
				info.LoadStringW(IDS_STRING_READFAILED);
				MessageBox(info, title);
				//MessageBox(L"��ȡʧ�ܣ�");
				return;
			}
			fileNPKname = fileName;
			fileOpen = true;
			mixMode = false;
			saveAlert = false;
			dispModeShowAll = false;
			updateIMGlist();
			if (no.count > 0) {
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
		if (fmt == L"L" || fmt == L"l") {
			no.release();
			if (no.loadFile(fn)) {
				info.LoadStringW(IDS_STRING_READFINISHED);
				MessageBox(info, title);
				//MessageBox(L"��ȡ��ϣ�");
			}
			else {
				info.LoadStringW(IDS_STRING_READFAILED);
				MessageBox(info, title);
				//MessageBox(L"��ȡʧ�ܣ�");
				return;
			}
			fileNPKname = fileName;
			fileOpen = true;
			mixMode = true;
			saveAlert = false;
			dispModeShowAll = false;
			updateIMGlist();
			if (no.count > 0) {
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
		if (fmt == L"G" || fmt == L"g") {
			io.Release();
			if (io.LoadFile(fn)) {
				info.LoadStringW(IDS_STRING_READFINISHED);
				MessageBox(info, title);
				//MessageBox(L"��ȡ��ϣ�");
			}
			else {
				info.LoadStringW(IDS_STRING_READFAILED);
				MessageBox(info, title);
				//MessageBox(L"��ȡʧ�ܣ�");
				return;
			}
			no.release();
			no.create();
			fileIMGname = fileName;
			fileNPKname = L"newNPK.npk";
			fileOpen = true;
			mixMode = false;
			saveAlert = false;
			dispModeShowAll = false;
			fileName = shorten(fileName);
			CStrToStr(toSl(fileName), fn);
			no.IMGpush(io, fn);
			switchIMGver(io.version);
			updateIMGlist();
			updatePIClist();
			updateCLRlist();
			updateDDSlist();
			updateNPKInfo();
			updateIMGInfo();
			updatePICInfo();
			m_lIMG.SetSelectionMark(0);
			crtIMGid = 0;
		}
	}
}

void CExRabbitDlg::OnMainMenuSave()
{
	// TODO: �ڴ���������������
	// TODO: ����NPK
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (saveAlert) {
		info.LoadStringW(IDS_STRING_IMGSAVEPROMPT);
		if (IDYES == MessageBox(info, title, MB_YESNO))
		//if (IDYES == MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������", L"��ʾ��", MB_YESNO))
			OnBnClickedButtonMenu2();
	}
	str fn;
	CString fileName;
	fileName = fileNPKname;
	CStrToStr(fileName, fn);
	if (no.saveFile(fn)) {
		info.LoadStringW(IDS_STRING_NPKSAVEFINISHED);
		MessageBox(info, title);
		//MessageBox(_T("NPK�����������"));
	}
	else {
		info.LoadStringW(IDS_STRING_NPKSAVEFAILED);
		MessageBox(info, title);
		//MessageBox(_T("NPK����ʧ������"));
	}
}

void CExRabbitDlg::OnMainMenuSaveAs()
{
	// TODO: �ڴ���������������
	// TODO: ����NPK
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (saveAlert) {
		info.LoadStringW(IDS_STRING_IMGSAVEPROMPT);
		if (IDYES == MessageBox(info, title, MB_YESNO))
		//if (IDYES == MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������", L"��ʾ��", MB_YESNO))
			OnBnClickedButtonMenu2();
	}
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
	defExt.LoadStringW(IDS_STRING_NPKFILETYPE);
	extFilter.LoadStringW(IDS_STRING_NPKFILETYPE2);
	if (mixMode) {
		defExt = _T("ƴ�Ϸ���(*.MPL)|*.MPL");
		extFilter = _T("ƴ�Ϸ���(*.MPL)|*.MPL||");
		defExt.LoadStringW(IDS_STRING_MERGESCHEME);
		extFilter.LoadStringW(IDS_STRING_MERGESCHEME2);
	}
	CFileDialog dlg(false, defExt, shorten(fileNPKname), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	str fn;
	CString fileName;
	if (dlg.DoModal() == IDOK) {
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if (no.saveFile(fn)) {
			info.LoadStringW(IDS_STRING_NPKSAVEFINISHED);
			MessageBox(info, title);
			//MessageBox(_T("NPK�����������"));
			fileNPKname = fileName;
			updateNPKInfo();
		}
		else {
			info.LoadStringW(IDS_STRING_NPKSAVEFAILED);
			MessageBox(info, title);
			//MessageBox(_T("NPK����ʧ������"));
		}
	}
}

void CExRabbitDlg::OnMainMenuAbout()
{
	// TODO: �ڴ���������������
	CString info;
	info.LoadStringW(IDS_STRING_ABOUTBOXINFO);
	MessageBox(info);
	//MessageBox(L"Ex���Ӱ�\r\n           --by���Ÿ����ĳ��");
}

void CExRabbitDlg::OnMainMenuQuit()
{
	// TODO: �ڴ���������������
	CDialogEx::OnCancel();
}

void CExRabbitDlg::OnImgMenuExtract()
{
	// TODO: �ڴ���������������
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	int row = crtIMGid;
	if (row < 0)
		return;
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	defExt.LoadStringW(IDS_STRING_IMGFILETYPE);
	extFilter.LoadStringW(IDS_STRING_IMGFILETYPE2);
	CFileDialog dlg(false, defExt, to_(StrToCStr(no.content[crtIMGid].get_imgname())), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	CString fileName1;
	str fn;
	if (dlg.DoModal() == IDOK) {
		fileName1 = dlg.GetPathName();
		CStrToStr(fileName1, fn);
		if (no.extractIMGFile(row, fn)) {
			info.LoadStringW(IDS_STRING_IMGSAVEFINISHED);
			MessageBox(info, title);
			//MessageBox(_T("������ϣ�"));
		}
		else {
			info.LoadStringW(IDS_STRING_IMGSAVEFAILED);
			MessageBox(info, title);
			//MessageBox(_T("����ʧ�ܣ�"));
		}
	}
}

void CExRabbitDlg::OnImgMenuInsert()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	if (row < 0) {
		dlgInsert.m_ch1.EnableWindow(false);
		dlgInsert.m_ch2.EnableWindow(false);
		dlgInsert.m_ch1.SetCheck(0);
		dlgInsert.m_ch2.SetCheck(0);
		dlgInsert.m_ch3.SetCheck(1);
		dlgInsert.m_ch4.SetCheck(0);
	}
	else {
		dlgInsert.m_ch1.EnableWindow(true);
		dlgInsert.m_ch2.EnableWindow(true);
	}
	dlgInsert.m_ed3.SetWindowText(L"newIMG.img");
	MOVEW(dlgInsert);
	dlgInsert.ShowWindow(SW_SHOW);
}

void CExRabbitDlg::OnImgMenuRemove()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (row < 0) {
		return;
	}
	if (no.IMGremove(row)) {
		info.LoadStringW(IDS_STRING_DELETEFINISHED);
		MessageBox(info, title);
		//MessageBox(L"ɾ����ϣ�");
	}
	else {
		info.LoadStringW(IDS_STRING_DELETEFAILED);
		MessageBox(info, title);
		//MessageBox(L"ɾ��ʧ�ܣ�");
	}
	updateIMGlist();
	m_lIMG.SetItemState(row - 1, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_lIMG.SetSelectionMark(row - 1);
}

void CExRabbitDlg::OnImgMenuReplace()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	if (row < 0) {
		return;
	}
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	defExt.LoadStringW(IDS_STRING_IMGFILETYPE);
	extFilter.LoadStringW(IDS_STRING_IMGFILETYPE2);
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	CString fileName;
	str fn;
	if (dlg.DoModal() == IDOK) {
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		IMGobject _io;
		_io.LoadFile(fn);
		if (no.IMGreplace(row, _io)) {
			info.LoadStringW(IDS_STRING_REPLACEFINISHED);
			MessageBox(info, title);
			//MessageBox(L"�滻��ϣ�");
		}
		else {
			info.LoadStringW(IDS_STRING_REPLACEFAILED);
			MessageBox(info, title);
			//MessageBox(L"�滻ʧ�ܣ�");
		}
		_io.Release();
		m_lIMG.SetSelectionMark(row);
	}
}

void CExRabbitDlg::OnImgMenuRename()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	if (row < 0) {
		return;
	}
	dlgRename.m_ed1.SetWindowText(StrToCStr(no.content[row].get_imgname()));
	dlgRename.m_ed2.SetWindowText(StrToCStr(no.content[row].get_imgname()));
	MOVEW(dlgRename);
	dlgRename.ShowWindow(SW_SHOW);
}

void CExRabbitDlg::OnImgMenuMoveUp()
{
	// TODO: �ڴ���������������
	// TODO������
	int row = crtIMGid;
	if (row < 1) {
		return;
	}
	IMGobject _io;
	no.IMGextract(row, _io);
	str fn = no.content[row].get_imgname();
	no.IMGremove(row);
	no.IMGinsert(row - 1, _io, fn);
	_io.Release();
	updateNPKInfo();
	{
		CString s1, s2;
		s1 = m_lIMG.GetItemText(row, 0);
		s2 = m_lIMG.GetItemText(row - 1, 0);
		m_lIMG.SetItemText(row, 0, s2);
		m_lIMG.SetItemText(row - 1, 0, s1);
		m_lIMG.SetSelectionMark(row - 1);
		m_lIMG.SetItemState(row - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_lIMG.SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
		crtIMGid = row - 1;
		updateInfo();
	}
}

void CExRabbitDlg::OnImgMenuMoveDown()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	if (row < 0) {
		return;
	}
	if (row == no.count - 1) {
		return;
	}
	IMGobject _io;
	no.IMGextract(row, _io);
	str fn = no.content[row].get_imgname();
	no.IMGremove(row);
	no.IMGinsert(row + 1, _io, fn);
	_io.Release();
	updateNPKInfo();
	{
		CString s1, s2;
		s1 = m_lIMG.GetItemText(row, 0);
		s2 = m_lIMG.GetItemText(row + 1, 0);
		m_lIMG.SetItemText(row, 0, s2);
		m_lIMG.SetItemText(row + 1, 0, s1);
		m_lIMG.SetSelectionMark(row + 1);
		m_lIMG.SetItemState(row + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_lIMG.SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
		crtIMGid = row + 1;
		updateInfo();
	}
}

void CExRabbitDlg::OnImgMenuHide()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	if (row < 0) {
		return;
	}
	IMGobject _io;
	PICinfo _pi;
	stream _s;
	no.IMGextract(row, _io);
	for (int i = 0; i < _io.indexCount; i++) {
		_io.GetPICInfo(i, _pi);
		_io.PICempty(_s, _pi);
		_io.PICreplace(i, _pi, _s);
		_s.release();
	}
	no.IMGreplace(row, _io);
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_ALLHIDED);
	MessageBox(info, title);
	//MessageBox(L"�����ظ�IMG��������ͼ��", L"��ʾ��");
	updatePIClist();
}

void CExRabbitDlg::OnImgMenuConvert()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	if (row < 0) {
		return;
	}
	IMGobject _io;
	CString info, title;
	no.IMGextract(row, _io);
	dlgTrasform.m_ch1.EnableWindow(true);
	dlgTrasform.m_ch2.EnableWindow(true);
	dlgTrasform.m_ch3.EnableWindow(true);
	dlgTrasform.m_ch4.EnableWindow(true);
	dlgTrasform.m_ch1.SetCheck(false);
	dlgTrasform.m_ch2.SetCheck(false);
	dlgTrasform.m_ch3.SetCheck(false);
	dlgTrasform.m_ch4.SetCheck(false);
	switch (_io.version) {
	case V2:
		dlgTrasform.m_ch1.EnableWindow(false);
		dlgTrasform.m_ch2.SetCheck(1);
		break;
	case V4:
		dlgTrasform.m_ch2.EnableWindow(false);
		dlgTrasform.m_ch1.SetCheck(1);
		break;
	case V5:
		dlgTrasform.m_ch3.EnableWindow(false);
		dlgTrasform.m_ch1.SetCheck(1);
		break;
	case V6:
		dlgTrasform.m_ch4.EnableWindow(false);
		dlgTrasform.m_ch1.SetCheck(1);
		break;
	default:
		title.LoadStringW(IDS_MESSAGE_TITLE);
		info.LoadStringW(IDS_STRING_NOTRECOGNIZEDVERSION);
		MessageBox(info, title);
		//MessageBox(L"δʶ��İ汾����", L"��ʾ");
		break;
	}
	MOVEW(dlgTrasform);
	dlgTrasform.ShowWindow(SW_SHOW);
}

void CExRabbitDlg::OnImgMenuSelectAll()
{
	// TODO: �ڴ���������������
	for (int i = 0; i < m_lIMG.GetItemCount(); i++)
		m_lIMG.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}

void CExRabbitDlg::OnImgMenuSelectOther()
{
	// TODO: �ڴ���������������
	for (int i = 0; i < m_lIMG.GetItemCount(); i++) {
		if (LVIS_SELECTED == m_lIMG.GetItemState(i, LVIS_SELECTED)) {
			m_lIMG.SetItemState(i, 0, LVIS_SELECTED | LVIS_FOCUSED);
		}
		else {
			m_lIMG.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		}
	}
}

void CExRabbitDlg::OnImgMenuRemoveAllSelected()
{
	// TODO: �ڴ���������������
	POSITION pos = m_lIMG.GetFirstSelectedItemPosition();
	std::vector<int> listID;
	listID.clear();
	CString info, title;
	info.LoadStringW(IDS_MESSAGE_TITLE);
	if (pos != NULL) {
		while (pos) {
			int nItem = m_lIMG.GetNextSelectedItem(pos);
			listID.push_back(nItem);
		}
	}
	for (int i = listID.size() - 1; i >= 0; i--) {
		no.IMGremove(listID[i]);
	}
	info.LoadStringW(IDS_STRING_ALLDELETEFINISHED);
	MessageBox(info, title);
	//MessageBox(L"ȫ��ɾ����ϣ�", L"��ʾ��");
	updateIMGlist();
	m_lIMG.SetSelectionMark(-1);
}

void CExRabbitDlg::OnImgMenuHideAllSelected()
{
	// TODO: �ڴ���������������
	POSITION pos = m_lIMG.GetFirstSelectedItemPosition();
	std::vector<int> listID;
	listID.clear();
	if (pos != NULL) {
		while (pos) {
			int nItem = m_lIMG.GetNextSelectedItem(pos);
			listID.push_back(nItem);
		}
	}
	for (int i = listID.size() - 1; i >= 0; i--) {
		IMGobject _io;
		PICinfo _pi;
		stream _s;
		no.IMGextract(listID[i], _io);
		for (int j = 0; j < _io.indexCount; j++) {
			_io.GetPICInfo(j, _pi);
			_io.PICempty(_s, _pi);
			_io.PICreplace(j, _pi, _s);
			_s.release();
		}
		no.IMGreplace(listID[i], _io);
	}
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_ALLHIDED);
	MessageBox(info, title);
	//MessageBox(L"ȫ��������ϣ�", L"��ʾ��");
	updatePIClist();
}

void CExRabbitDlg::OnImgMenuExtractAllSelected()
{
	// TODO: �ڴ���������������
	POSITION pos = m_lIMG.GetFirstSelectedItemPosition();
	std::vector<int> listID;
	listID.clear();
	if (pos != NULL) {
		while (pos) {
			int nItem = m_lIMG.GetNextSelectedItem(pos);
			listID.push_back(nItem);
		}
	}
	for (int i = listID.size() - 1; i >= 0; i--) {
		CString fileName = getOutPutDir(fileNPKname) + to_(StrToCStr(no.content[listID[i]].get_imgname()));
		str fn;
		CStrToStr(fileName, fn);
		no.extractIMGFile(listID[i], fn);
	}
	CString info, title, tmp;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	tmp.LoadStringW(IDS_STRING_ALLEXTRACTED);
	info.Format(tmp, getOutPutDir(fileNPKname));
	MessageBox(info, title);
	//MessageBox(L"ȫ����ȡ��ϣ��ѱ��浽" + getOutPutDir(fileNPKname) + L"������", L"��ʾ��");
}

void CExRabbitDlg::OnImgMenu2Insert()
{
	// TODO: �ڴ���������������
	OnImgMenuInsert();
}

void CExRabbitDlg::OnPicMenuExtractPng()
{
	// TODO: �ڴ���������������
	int row = m_lPicture.GetSelectionMark();
	if (row == -1) {
		return;
	}
	str fn;
	CString fileName;
	CString info, title, tmp;
	tmp.LoadStringW(IDS_STRING_WORDFRAME);
	if (io.version == V6) {
		fileName = getOutPutDir(fileNPKname, fileIMGname, m_cbPro.GetCurSel()) + tmp + NumToCStr(row) + L".PNG";
		//fileName = getOutPutDir(fileNPKname, fileIMGname, m_cbPro.GetCurSel()) + L"֡��" + NumToCStr(row) + L".PNG";
	}
	else {
		fileName = getOutPutDir(fileNPKname, fileIMGname) + tmp + NumToCStr(row) + L".PNG";
		//fileName = getOutPutDir(fileNPKname, fileIMGname) + L"֡��" + NumToCStr(row) + L".PNG";
	}
	CStrToStr(fileName, fn);
	matrix mat;
	io.PICextract(row, mat, m_cbPro.GetCurSel());
	mat.makePNG(fn);
	mat.release();
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_FILESAVEDAS);
	MessageBox(info + fileName, title);
	//MessageBox(L"�ѱ���Ϊ" + fileName + L"��", L"��ʾ��");
}

void CExRabbitDlg::OnPicMenuExtractAllPng()
{
	// TODO: �ڴ���������������
	AfxBeginThread(extractThread, (LPVOID)this);
}

void CExRabbitDlg::OnPicMenuExtractIndex()
{
	// TODO: �ڴ���������������
	int row = m_lPicture.GetSelectionMark();
	if (row == -1) {
		return;
	}
	str fn;
	CString info, title, tmp;
	tmp.LoadStringW(IDS_STRING_WORDFRAME);
	CString fileName = getOutPutDir(fileNPKname, fileIMGname) + tmp + NumToCStr(row) + L".PID";
	//CString fileName = getOutPutDir(fileNPKname, fileIMGname) + L"֡��" + NumToCStr(row) + L".PID";
	CStrToStr(fileName, fn);
	stream s, s1, sHead;
	PICinfo pi;
	io.GetPICInfo(row, pi);
	io.GetPICData(row, s);
	s.uncompressData(s1, pi.get_comp());
	sHead.allocate(16);
	sHead.push((b32)0x73696F4B);
	sHead.push((b32)0x78456968);
	sHead.push(pi.get_picSize().get_W());
	sHead.push(pi.get_picSize().get_H());
	s1.insertStream(sHead, 16, 0);
	s1.makeFile(fn);
	s.release();
	s1.release();
	sHead.release();
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_FILESAVEDAS);
	MessageBox(info + fileName, title);
	//MessageBox(L"�ѱ���Ϊ" + fileName + L"��", L"��ʾ��");
}

void CExRabbitDlg::OnPicMenuExtractAllIndex()
{
	// TODO: �ڴ���������������
	AfxBeginThread(extractPIDThread, (LPVOID)this);
}

void CExRabbitDlg::OnPicMenuInsert()
{
	// TODO: �ڴ���������������
	CString tra;
	tra.LoadStringW(IDS_STRING_INSERTSPRITE);
	dlgInsert2.SetWindowText(tra);
	//dlgInsert2.SetWindowText(L"������ͼ");
	dlgInsert2.iORr = CDlgInsert2::__INSERT;
	dlgInsert2.ver = io.version;
	switch (io.version) {
	case V2:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_INSERTLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ָ����������");
		tra.LoadStringW(IDS_STRING_INSERTIMAGEINDEXBASEDONPNG);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ͼƬ��������(����PNG�ļ�)");
		break;
	case V4:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_INSERTLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ָ����������");
		tra.LoadStringW(IDS_STRING_INSERTIMAGEINDEXBASEDONINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ͼƬ��������(��������)");
		tra.LoadStringW(IDS_STRING_INSERTIMAGEINDEXBASEDONPNG);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ͼƬ��������(����PNG�ļ�)");
		break;
	case V5:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_INSERTLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ָ����������");
		tra.LoadStringW(IDS_STRING_INSERTIMAGEINDEXBASEDONDDSREFERENCE);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����DDSͼƬ��������(������֪DDS����)");
		tra.LoadStringW(IDS_STRING_INSERTIMAGEINDEXBASEDONPNG);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����DDSͼƬ��������(����PNG�ļ�)");
		break;
	case V6:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_INSERTLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ָ����������");
		tra.LoadStringW(IDS_STRING_INSERTIMAGEINDEXBASEDONINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"����ͼƬ��������(��������)");
		break;
	}
	if (m_lPicture.GetSelectionMark() < 0) {
		dlgInsert2.m_ch1.SetCheck(0);
		dlgInsert2.m_ch2.SetCheck(0);
		dlgInsert2.m_ch3.SetCheck(1);
		dlgInsert2.m_ch1.EnableWindow(false);
		dlgInsert2.m_ch2.EnableWindow(false);
		dlgInsert2.m_ch3.EnableWindow(true);
	}
	else if (m_lPicture.GetSelectionMark() == 0) {
		dlgInsert2.m_ch1.SetCheck(0);
		dlgInsert2.m_ch2.SetCheck(1);
		dlgInsert2.m_ch3.SetCheck(0);
		dlgInsert2.m_ch1.EnableWindow(false);
		dlgInsert2.m_ch2.EnableWindow(true);
		dlgInsert2.m_ch3.EnableWindow(true);
	}
	else {
		dlgInsert2.m_ch1.SetCheck(1);
		dlgInsert2.m_ch2.SetCheck(0);
		dlgInsert2.m_ch3.SetCheck(0);
		dlgInsert2.m_ch1.EnableWindow(true);
		dlgInsert2.m_ch2.EnableWindow(true);
		if (m_lPicture.GetSelectionMark() == io.indexCount - 1) {
			dlgInsert2.m_ch2.EnableWindow(false);
		}
		dlgInsert2.m_ch3.EnableWindow(true);
	}
	/////////////////
	dlgInsert2.m_cb1.SetCurSel(1);
	dlgInsert2.OnCbnSelchangeCombo1();
	/////////////////
	MOVEW(dlgInsert2);
	dlgInsert2.ShowWindow(SW_SHOW);
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnPicMenuRemove()
{
	// TODO: �ڴ���������������
	int row = m_lPicture.GetSelectionMark();
	CString info, title;
	io.PICremove(row);
	m_lPicture.SetSelectionMark(row - 1);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_THISSPRITEHASBEENDELETED);
	MessageBox(info, title);
	//MessageBox(L"�ѽ������ͼɾ��������", L"��ʾ����");
	{
		m_lPicture.DeleteItem(row);
	}
	updateNPKInfo();
	updateIMGInfo();
	updatePICInfo();
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnPicMenuReplace()
{
	// TODO: �ڴ���������������
	CString tra;
	tra.LoadStringW(IDS_STRING_REPLACESPRITE);
	dlgInsert2.SetWindowText(tra);
	//dlgInsert2.SetWindowText(L"�滻��ͼ");
	dlgInsert2.iORr = CDlgInsert2::__REPLACE;
	dlgInsert2.ver = io.version;
	switch (io.version) {
	case V2:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_REPLACEASLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻Ϊָ����������");
		tra.LoadStringW(IDS_STRING_REPLACEASIMAGEINDEXBASEDONPNG2);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻ΪͼƬ��������(����PNG�ļ�)");
		break;
	case V4:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_REPLACEASLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻Ϊָ����������");
		tra.LoadStringW(IDS_STRING_REPLACEASIMAGEINDEXBASEDONINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻ΪͼƬ��������(��������)");
		tra.LoadStringW(IDS_STRING_REPLACEASIMAGEINDEXBASEDONPNG2);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻ΪͼƬ��������(����PNG�ļ�)");
		break;
	case V5:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_REPLACEASLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻Ϊָ����������");
		tra.LoadStringW(IDS_STRING_REPLACEASIMAGEINDEXBASEDONDDSREFERENCE2);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻ΪDDSͼƬ��������(������֪DDS����)");
		tra.LoadStringW(IDS_STRING_REPLACEASIMAGEINDEXBASEDONPNG2);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻ΪDDSͼƬ��������(����PNG�ļ�)");
		break;
	case V6:
		dlgInsert2.m_cb1.ResetContent();
		tra.LoadStringW(IDS_STRING_REPLACEASLINKEDINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻Ϊָ����������");
		tra.LoadStringW(IDS_STRING_REPLACEASIMAGEINDEXBASEDONINDEX);
		dlgInsert2.m_cb1.AddString(tra);
		//dlgInsert2.m_cb1.AddString(L"�滻ΪͼƬ��������(��������)");
		break;
	}
	dlgInsert2.m_ch1.SetCheck(1);
	dlgInsert2.m_ch2.SetCheck(0);
	dlgInsert2.m_ch3.SetCheck(0);
	dlgInsert2.m_ch1.EnableWindow(false);
	dlgInsert2.m_ch2.EnableWindow(false);
	dlgInsert2.m_ch3.EnableWindow(false);
	///////////////////////////
	int pos = m_lPicture.GetSelectionMark();
	PICinfo pi;
	io.GetPICInfo(pos, pi);
	if (pi.get_format() == LINK) {
		dlgInsert2.m_cb1.SetCurSel(0);
	}
	else {
		dlgInsert2.m_cb1.SetCurSel(1);
	}
	dlgInsert2.OnCbnSelchangeCombo1();
	///////////////////////////
	MOVEW(dlgInsert2);
	dlgInsert2.ShowWindow(SW_SHOW);
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnPicMenuSetPara()
{
	// TODO: �ڴ���������������
	int pos = m_lPicture.GetSelectionMark();
	PICinfo pi;
	io.GetPICInfo(pos, pi);
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


void CExRabbitDlg::OnPicMenuHide()
{
	// TODO: �ڴ���������������
	int pos = m_lPicture.GetSelectionMark();
	PICinfo pi;
	stream s;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_HIDEDSELECTEDSPRITES);
	io.PICempty(s, pi);
	io.PICreplace(pos, pi, s);
	MessageBox(info, title);
	//MessageBox(L"�ѽ�ѡ����ͼ���أ�", L"��ʾ��");
	{
		m_lPicture.SetItemText(pos, 1, FmtToCStr(io.PICcontent[pos].get_format(), io.version));
		m_lPicture.SetItemText(pos, 2, PtToCStr(io.PICcontent[pos].get_basePt()));
		m_lPicture.SetItemText(pos, 3, SzToCStr(io.PICcontent[pos].get_picSize()));
		m_lPicture.SetItemText(pos, 4, SzToCStr(io.PICcontent[pos].get_frmSize()));
		if (io.version == V5) {
			m_lPicture.SetItemText(pos, 5, L"DDS" + NumToCStr(io.PICcontent[pos].get_DDSIDused()) + L":" + PtToCStr(io.PICcontent[pos].get_DDSpointLT()) + L"-" + PtToCStr(io.PICcontent[pos].get_DDSpointRB()));
		}
	}
	updateNPKInfo();
	updateIMGInfo();
	updatePICInfo();
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnPicMenu2Insert()
{
	// TODO: �ڴ���������������
	OnPicMenuInsert();
}


void CExRabbitDlg::OnDdsMenuExtractPng()
{
	// TODO: �ڴ���������������
	int row = m_lDDS.GetSelectionMark();
	if (row == -1) {
		return;
	}
	str fn;
	CString fileName;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	fileName = getOutPutDir(fileNPKname, fileIMGname) + L"DDS��ͼ" + NumToCStr(row) + L".PNG";
	CStrToStr(fileName, fn);
	matrix mat;
	io.DDSextract(row, mat);
	mat.makePNG(fn);
	mat.release();
	info.LoadStringW(IDS_STRING_FILESAVEDAS);
	MessageBox(info + fileName, title);
	//MessageBox(L"�ѱ���Ϊ" + fileName + L"��", L"��ʾ��");
}


void CExRabbitDlg::OnDdsMenuExtractAllPng()
{
	// TODO: �ڴ���������������
	AfxBeginThread(extractDDSPNGThread, (PVOID)this);
}


void CExRabbitDlg::OnDdsMenuExtractDds()
{
	// TODO: �ڴ���������������
	int row = m_lDDS.GetSelectionMark();
	if (row == -1) {
		return;
	}
	str fn;
	CString fileName;
	CString info, title;
	fileName = getOutPutDir(fileNPKname, fileIMGname) + L"DDS��ͼ" + NumToCStr(row) + L".dds";
	CStrToStr(fileName, fn);
	stream s, s1;
	io.GetDDSData(row, s);
	s.uncompressData(s1, COMP_ZLIB2);
	s1.makeFile(fn);
	s.release();
	s.release();
	info.LoadStringW(IDS_STRING_FILESAVEDAS);
	MessageBox(info + fileName, title);
	//MessageBox(L"�ѱ���Ϊ" + fileName + L"��", L"��ʾ��");
}


void CExRabbitDlg::OnDdsMenuExtractAllDds()
{
	// TODO: �ڴ���������������
	AfxBeginThread(extractDDSThread, (PVOID)this);
}


void CExRabbitDlg::OnDdsMenuInsert()
{
	// TODO: �ڴ���������������
	CString tra;
	tra.LoadStringW(IDS_STRING_INSERTDDSSPRITE);
	dlgInsert3.SetWindowText(tra);
	//dlgInsert3.SetWindowText(L"����DDS��ͼ");
	dlgInsert3.iORr = CDlgInsert2::__INSERT;
	dlgInsert3.m_cb1.ResetContent();
	tra.LoadStringW(IDS_STRING_BASEDONDDSFILE);
	dlgInsert3.m_cb1.AddString(tra);
	//dlgInsert3.m_cb1.AddString(L"����DDS�ļ�");
	tra.LoadStringW(IDS_STRING_BASEDONPNGFILE);
	dlgInsert3.m_cb1.AddString(tra);
	//dlgInsert3.m_cb1.AddString(L"����PNG�ļ�");
	dlgInsert3.m_cb1.SetCurSel(0);
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


void CExRabbitDlg::OnDdsMenuRemove()
{
	// TODO: �ڴ���������������
	int row = m_lDDS.GetSelectionMark();
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	io.DDSremove(row);
	m_lDDS.SetSelectionMark(row - 1);
	info.LoadStringW(IDS_STRING_DELETEDTHISDDSSPRITE);
	MessageBox(info, title);
	//MessageBox(L"�ѽ����DDS��ͼɾ��������", L"��ʾ����");
	updateDDSlist();
	updateNPKInfo();
	updateIMGInfo();
	updatePICInfo();
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnDdsMenuReplace()
{
	// TODO: �ڴ���������������
	CString tra;
	tra.LoadStringW(IDS_STRING_INSERTDDSSPRITE);
	dlgInsert3.SetWindowText(tra);
	//dlgInsert3.SetWindowText(L"����DDS��ͼ");
	dlgInsert3.iORr = CDlgInsert2::__REPLACE;
	dlgInsert3.m_cb1.ResetContent();
	tra.LoadStringW(IDS_STRING_BASEDONDDSFILE);
	dlgInsert3.m_cb1.AddString(tra);
	//dlgInsert3.m_cb1.AddString(L"����DDS�ļ�");
	tra.LoadStringW(IDS_STRING_BASEDONPNGFILE);
	dlgInsert3.m_cb1.AddString(tra);
	//dlgInsert3.m_cb1.AddString(L"����PNG�ļ�");
	dlgInsert3.m_cb1.SetCurSel(0);
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

void CExRabbitDlg::OnDdsMenu2Insert()
{
	// TODO: �ڴ���������������
	OnDdsMenuInsert();
}


void CExRabbitDlg::OnClrMenuInsert()
{
	// TODO: �ڴ���������������
	CString tra;
	tra.LoadStringW(IDS_STRING_INSERTCOLOR);
	dlgInsert4.SetWindowText(tra);
	//dlgInsert4.SetWindowText(L"������ɫ");
	dlgInsert4.iORr = CDlgInsert4::__INSERT;
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


void CExRabbitDlg::OnClrMenuRemove()
{
	// TODO: �ڴ���������������
	int pos = m_lColor.GetSelectionMark();
	int clrID = m_cbPro.GetCurSel();
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (clrID < 0)
		clrID = 0;
	if (pos < 0)
		return;
	io.CLRremove(pos, clrID);
	info.LoadStringW(IDS_STRING_DELETEDSELECTEDCOLOR);
	MessageBox(info, title);
	//MessageBox(L"ɾ����ɫ��ϣ�", L"��ʾ��");
	updateCLRlist();
	updateNPKInfo();
	updateIMGInfo();
	updatePICInfo();
	draw();
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnClrMenuReplace()
{
	// TODO: �ڴ���������������
	CString tra;
	tra.LoadStringW(IDS_STRING_REPLACECOLOR);
	dlgInsert4.SetWindowText(tra);
	//dlgInsert4.SetWindowText(L"�滻��ɫ");
	dlgInsert4.iORr = CDlgInsert4::__REPLACE;
	dlgInsert4.m_c1.SetCheck(1);
	dlgInsert4.m_c2.SetCheck(0);
	dlgInsert4.m_c3.SetCheck(0);
	dlgInsert4.m_c1.EnableWindow(false);
	dlgInsert4.m_c2.EnableWindow(false);
	dlgInsert4.m_c3.EnableWindow(false);

	int pos = m_lColor.GetSelectionMark();
	int clrID = m_cbPro.GetCurSel();
	if (clrID < 0)
		clrID = 0;
	if (pos < 0)
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


void CExRabbitDlg::OnClrMenuExtractPalette()
{
	// TODO: �ڴ���������������
	int clrID = m_cbPro.GetCurSel();
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (clrID < 0)
		clrID = 0;
	str fn;
	CString fileName = getOutPutDir(fileNPKname, fileIMGname) + L"Palette" + NumToCStr(clrID) + L".CID";
	CStrToStr(fileName, fn);
	stream s, sHead;
	sHead.allocate(12);
	sHead.push((b32)0x6F436F4B);
	sHead.push((b32)0x72756F6C);
	sHead.push((b32)io.paletteData[clrID].size());
	s.allocate(12 + io.paletteData[clrID].size() + 100);
	s.pushStream(sHead, 12);
	for (int i = 0; i < io.paletteData[clrID].size(); i++) {
		s.push(io.paletteData[clrID][i].get_A());
		s.push(io.paletteData[clrID][i].get_R());
		s.push(io.paletteData[clrID][i].get_G());
		s.push(io.paletteData[clrID][i].get_B());
	}
	s.makeFile(fn);
	s.release();
	sHead.release();
	info.LoadStringW(IDS_STRING_FILESAVEDAS);
	MessageBox(info + fileName, title);
	//MessageBox(L"�ѱ���Ϊ" + fileName + L"��", L"��ʾ��");
}


void CExRabbitDlg::OnClrMenuExtractAllPalette()
{
	// TODO: �ڴ���������������
	str fn;
	CString fileName;
	CString info, title;
	stream s, sHead;
	for (int j = 0; j < io.paletteData.getCount(); j++) {
		fileName = getOutPutDir(fileNPKname, fileIMGname) + L"Palette" + NumToCStr(j) + L".CID";
		CStrToStr(fileName, fn);
		sHead.allocate(12);
		sHead.push((b32)0x6F436F4B);
		sHead.push((b32)0x34726F6C);
		sHead.push((b32)io.paletteData[j].size());
		s.allocate(12 + io.paletteData[j].size() + 100);
		s.pushStream(sHead, 12);
		for (int i = 0; i < io.paletteData[j].size(); i++) {
			s.push(io.paletteData[j][i].get_A());
			s.push(io.paletteData[j][i].get_R());
			s.push(io.paletteData[j][i].get_G());
			s.push(io.paletteData[j][i].get_B());
		}
		s.makeFile(fn);
		s.release();
		sHead.release();
	}
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_SAVEDTOFOLDER);
	MessageBox(info + getOutPutDir(fileNPKname, fileIMGname), title);
	//MessageBox(L"�ѱ��浽" + getOutPutDir(fileNPKname, fileIMGname) + L"������", L"��ʾ��");
}

void CExRabbitDlg::OnClrMenuLoadPalette()
{
	// TODO: �ڴ���������������
	int clrID = m_cbPro.GetCurSel();
	if (clrID < 0)
		clrID = 0;
	CString defExt = _T("V4��ɫ��(*.cid)|*.cid");
	CString extFilter = _T("V4��ɫ��(*.cid)|*.cid||");
	defExt.LoadStringW(IDS_STRING_V4PALETTE);
	extFilter.LoadStringW(IDS_STRING_V4PALETTE2);
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	CString fileName;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	str fn;
	stream s;
	i32 i, j, k;
	b8 b;
	if (dlg.DoModal() == IDOK) {
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if (!s.loadFile(fn)) {
			info.LoadStringW(IDS_STRING_UNABLETOREAD);
			MessageBox(info, title);
			//MessageBox(L"�޷���ȡ�ļ�����", L"��ʾ��");
			return;
		}
		s.read(i);
		if ((b32)i != 0x6F436F4B) {
			info.LoadStringW(IDS_STRING_NOTRECOGNIZEDPALETTE);
			MessageBox(info, title);
			//MessageBox(L"�õ�ɫ��δ��ʶ������", L"��ʾ����");
			return;
		}
		s.read(i);
		s.read(i);
		k = io.paletteData[clrID].size();
		for (j = 0; j < k; j++)
			io.CLRremove(0, clrID);
		for (j = 0; j < i; j++) {
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
		info.LoadStringW(IDS_STRING_READFINISHED);
		MessageBox(info, title);
		//MessageBox(L"��ȡ��ɫ���������", L"��ʾ��");
		updateCLRlist();
		updateNPKInfo();
		updateIMGInfo();
		updatePICInfo();
		saveAlert = true;
		updateInfo();
		draw();
	}
}


void CExRabbitDlg::OnClrMenuNewPalette()
{
	// TODO: �ڴ���������������
	CString palettenum;
	palettenum.LoadStringW(IDS_STRING_PALETTEMETHODNUM);
	io.CLRnewPalette();
	m_cbPro.ResetContent();
	for (int i = 0; i < io.paletteData.getCount(); i++)
		//m_cbPro.AddString(L"��ɫ�巽��" + NumToCStr(i));
		m_cbPro.AddString(palettenum + NumToCStr(i));
	m_cbPro.SetCurSel(io.paletteData.getCount() - 1);
	updateCLRlist();
	updateNPKInfo();
	updateIMGInfo();
	updatePICInfo();
	draw();
	saveAlert = true;
	updateInfo();
}



void CExRabbitDlg::OnClrMenu2Insert()
{
	// TODO: �ڴ���������������
	OnClrMenuInsert();
}

void CExRabbitDlg::OnClrMenu2LoadPalette()
{
	// TODO: �ڴ���������������
	OnClrMenuLoadPalette();
}


void CExRabbitDlg::OnClrMenu2NewPalette()
{
	// TODO: �ڴ���������������
	OnClrMenuNewPalette();
}


void CExRabbitDlg::OnDisplayMenuSwitchAbs()
{
	// TODO: �ڴ���������������
	dispModeAbs = !dispModeAbs;
	draw();
}


void CExRabbitDlg::OnDisplayMenuAutoFind()
{
	// TODO: �ڴ���������������
	int row = m_lPicture.GetSelectionMark();
	if (row < 0)
		return;
	switch (dispModeAbs) {
	case true:
		basePoint.set_X(-io.PICcontent[row].get_basePt().get_X());
		basePoint.set_Y(-io.PICcontent[row].get_basePt().get_Y());
		m_edX.SetWindowText(NumToCStr(basePoint.get_X()));
		m_edY.SetWindowText(NumToCStr(basePoint.get_Y()));
		break;
	default:
		break;
	}
	draw();
}

void CExRabbitDlg::OnDisplayMenuPlay()
{
	// TODO: �ڴ���������������
	AfxBeginThread(playThread, (LPVOID)this);
}


void CExRabbitDlg::OnDisplayMenuSwitchIndex()
{
	// TODO: �ڴ���������������
	dispModeIndex = !dispModeIndex;
	draw();
}


void CExRabbitDlg::OnDisplayMenuSwitchDds()
{
	// TODO: �ڴ���������������
	dispModeDds = !dispModeDds;
	draw();
}


void CExRabbitDlg::OnDisplayMenu2ShowAll()
{
	// TODO: �ڴ���������������
	/*MessageBox(L"��Ůʩ���С���",L"��ʾ��");
	return;*/
	dispModeShowAll = !dispModeShowAll;
	if (dispModeShowAll) {
		dispModeAbs = true;
		OnDisplayMenu2AutoFind();
	}
	draw();
}


void CExRabbitDlg::OnDisplayMenu2AutoFind()
{
	// TODO: �ڴ���������������
	OnDisplayMenuAutoFind();
}


void CExRabbitDlg::OnDisplayMenu2SwitchAbs()
{
	// TODO: �ڴ���������������
	OnDisplayMenuSwitchAbs();
}


void CExRabbitDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CString info, title;
	info.LoadStringW(IDS_STRING_DONOTPRESSENTER);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	MessageBox(info, title);
	//MessageBox(L"�����س�����", L"��ʾ��");
}


void CExRabbitDlg::OnClrMenuHSV()
{
	// TODO: �ڴ���������������
	int clrID = m_cbPro.GetCurSel();
	CString wordcolor;
	wordcolor.LoadStringW(IDS_STRING_WORDCOLOR);
	if (clrID < 0)
		clrID = 0;
	dlgHSV.m_list.ResetContent();
	dlgHSV.oldClrList.clear();
	dlgHSV.midClrList.clear();
	dlgHSV.newClrList.clear();
	for (int i = 0; i < io.paletteData[clrID].size(); i++) {
		dlgHSV.m_list.AddString(wordcolor + NumToCStr(i));
		//dlgHSV.m_list.AddString(L"��ɫ" + NumToCStr(i));
		dlgHSV.oldClrList.push_back(io.paletteData[clrID][i]);
		dlgHSV.midClrList.push_back(io.paletteData[clrID][i]);
		dlgHSV.newClrList.push_back(io.paletteData[clrID][i]);
	}
	dlgHSV.m_chHSV.SetCheck(1);
	dlgHSV.m_chRGB.SetCheck(0);
	dlgHSV.m_e1.SetWindowText(L"H:0");
	dlgHSV.m_e2.SetWindowText(L"S:0");
	dlgHSV.m_e3.SetWindowText(L"V:0");
	dlgHSV.m_s1.SetRange(0, 360);
	dlgHSV.m_s2.SetRange(-100, 100);
	dlgHSV.m_s3.SetRange(-100, 100);
	dlgHSV.m_s1.SetTic(360);
	dlgHSV.m_s2.SetTic(200);
	dlgHSV.m_s3.SetTic(200);
	dlgHSV.m_s1.SetTicFreq(30);
	dlgHSV.m_s2.SetTicFreq(20);
	dlgHSV.m_s3.SetTicFreq(20);
	dlgHSV.m_s1.SetPos(0);
	dlgHSV.m_s2.SetPos(0);
	dlgHSV.m_s3.SetPos(0);
	dlgHSV.firstpos = 0;
	MOVEW(dlgHSV);
	dlgHSV.ShowWindow(SW_SHOW);
	dlgHSV.draw();
	saveAlert = true;
	updateInfo();
}

void CExRabbitDlg::OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int row = m_lIMG.GetSelectionMark();
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_IMGCONFIRMSAVE);
	if (pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN) {
		//�޹ذ�������Ӧ
		*pResult = 0;
		return;
	}
	if (pLVKeyDow->wVKey == VK_UP) {
		if (row > 0) {
			row--;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (pLVKeyDow->wVKey == VK_DOWN) {
		if (row < m_lIMG.GetItemCount() - 1) {
			row++;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (saveAlert) {
		switch (MessageBox(info, title, MB_YESNO)) {
		//switch (MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������", L"��ʾ��", MB_YESNO)) {
		case IDYES:
			OnBnClickedButtonMenu2();
			break;
		case IDNO:
			saveAlert = false;
			updateInfo();
			break;
		}
	}
	if (lazyTime > 0) {
		*pResult = 0;
		return;
	}
	crtIMGid = row;
	if (row >= 0) {
		io.Release();
		no.IMGextract(row, io);
		fileIMGname = StrToCStr(no.content[row].get_imgname());
		switchIMGver(io.version);
		updatePIClist();
		updateCLRlist();
		updateDDSlist();
		updateIMGInfo();
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int row = m_lPicture.GetSelectionMark();
	if (pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN) {
		//�޹ذ�������Ӧ
		*pResult = 0;
		return;
	}
	if (pLVKeyDow->wVKey == VK_UP) {
		if (row > 0) {
			row--;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (pLVKeyDow->wVKey == VK_DOWN) {
		if (row < m_lPicture.GetItemCount() - 1) {
			row++;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (lazyTime > 0) {
		*pResult = 0;
		return;
	}
	crtCLRDDSid = row;
	updateInfo();
	draw();
	lazyTime = 5;
	*pResult = 0;
}


void CExRabbitDlg::OnLvnKeydownListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int row = m_lColor.GetSelectionMark();
	if (pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN) {
		//�޹ذ�������Ӧ
		*pResult = 0;
		return;
	}
	if (pLVKeyDow->wVKey == VK_UP) {
		if (row > 0) {
			row--;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (pLVKeyDow->wVKey == VK_DOWN) {
		if (row < m_lColor.GetItemCount() - 1) {
			row++;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (lazyTime > 0) {
		*pResult = 0;
		return;
	}
	crtCLRDDSid = row;
	updateInfo();
	draw();
	lazyTime = 5;
	*pResult = 0;
}


void CExRabbitDlg::OnLvnKeydownListDds(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int row = m_lDDS.GetSelectionMark();
	if (pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN) {
		//�޹ذ�������Ӧ
		*pResult = 0;
		return;
	}
	if (pLVKeyDow->wVKey == VK_UP) {
		if (row > 0) {
			row--;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (pLVKeyDow->wVKey == VK_DOWN) {
		if (row < m_lDDS.GetItemCount() - 1) {
			row++;
		}
		else {
			*pResult = 0;
			return;
		}
	}
	if (lazyTime > 0) {
		*pResult = 0;
		return;
	}
	crtCLRDDSid = row;
	updateInfo();
	draw(true);
	lazyTime = 5;
	*pResult = 0;
}


void CExRabbitDlg::OnImgMenuAddToMixed()
{
	// TODO: ִ��ƴ��
	AfxBeginThread(mixThread, PVOID(this));

}

UINT mixThread(PVOID para) {
	CExRabbitDlg *dlg = (CExRabbitDlg *)para;
	NPKobject *nop = &(dlg->no);
	int imgCount = nop->count;
	CString tra, tmp;
	tra.LoadStringW(IDS_STRING_MERGING);
	if (imgCount == 0)
		return 0;
	dlg->dlgBar.ShowWindow(SW_SHOW);
	dlg->dlgBar.setTitle(tra);
	//dlg->dlgBar.setTitle(L"ƴ����");
	IMGobject *ioList = new IMGobject[imgCount];
	IMGobject newIO;
	newIO.Create(V2);
	int i, k;
	for (i = 0; i < imgCount; i++) {
		nop->IMGextract(i, ioList[i]);
	}
	int maxFrameCount = 0;
	for (i = 0; i < imgCount; i++) {
		if (ioList[i].indexCount > maxFrameCount)
			maxFrameCount = ioList[i].indexCount;
	}
	matrix mat, mat2, matf;
	stream s;
	PICinfo pi;
	point ptLT, ptRB, ptLTtemp, ptRBtemp;//���Ͻ����½ǵĵ㣬���½ǵĵ������ͼƬ��
	std::vector<int> mLeft, mTop, mRight, mBottom;
	for (k = 0; k < maxFrameCount; k++) {
		tmp.LoadStringW(IDS_STRING_MERGINGPROGRESS);
		tra.Format(tmp, NumToCStr(k + 1), NumToCStr(maxFrameCount));
		dlg->dlgBar.setInfo(tra);
		//dlg->dlgBar.setInfo(L"����ƴ�ϵ�" + NumToCStr(k + 1) + L"֡,��" + NumToCStr(maxFrameCount) + L"֡");
		mLeft.clear();
		mTop.clear();
		mRight.clear();
		mBottom.clear();
		for (i = 0; i < imgCount; i++) {
			if (ioList[i].GetPICInfo(k, pi)) {
				if (pi.get_format() == LINK) {
					ioList[i].linkFind(k);
				}
				ioList[i].GetPICInfo(k, pi);
				if (pi.get_picSize().area() <= 1) {
					continue;
				}
				mLeft.push_back(pi.get_basePt().get_X());
				mTop.push_back(pi.get_basePt().get_Y());
				mRight.push_back(pi.get_basePt().get_X() + pi.get_picSize().get_W() - 1);
				mBottom.push_back(pi.get_basePt().get_Y() + pi.get_picSize().get_H() - 1);
			}
		}
		int tLeft = 100000;
		int tTop = 100000;
		int tRight = -100000;
		int tBottom = -100000;
		for (i = 0; i < mLeft.size(); i++) {
			if (mLeft[i] < tLeft)
				tLeft = mLeft[i];
			if (mRight[i] > tRight)
				tRight = mRight[i];
			if (mTop[i] < tTop)
				tTop = mTop[i];
			if (mBottom[i] > tBottom)
				tBottom = mBottom[i];
		}
		ptLT.set(tLeft, tTop);
		ptRB.set(tRight, tBottom);
		matf.allocate(tBottom - tTop + 1, tRight - tLeft + 1);
		for (i = 0; i < imgCount; i++) {
			if (ioList[i].GetPICInfo(k, pi)) {
				if (pi.get_format() == LINK) {
					ioList[i].linkFind(k);
				}
				ioList[i].GetPICInfo(k, pi);
				if (pi.get_picSize().area() <= 1) {
					continue;
				}
				ioList[i].PICextract(k, mat);
				mat2.allocate(
					pi.get_basePt().get_Y() - ptLT.get_Y() + pi.get_picSize().get_H() + 10,
					pi.get_basePt().get_X() - ptLT.get_X() + pi.get_picSize().get_W() + 10
				);
				mat2.putFore(mat);
				mat2.elemMoveHonz(pi.get_basePt().get_X() - ptLT.get_X());
				mat2.elemMoveVert(pi.get_basePt().get_Y() - ptLT.get_Y());
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
		dlg->dlgBar.setPosi((k + 1) * 1000 / maxFrameCount);
	}
	nop->IMGpush(newIO, "mixed.img");
	dlg->m_lIMG.InsertItem(imgCount, L"mixed.img");
	dlg->updateNPKInfo();
	dlg->updateIMGlist();
	delete[] ioList;
	dlg->dlgBar.ShowWindow(SW_HIDE);
	return 0;
}

void CExRabbitDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	WCHAR szPath[MAX_PATH] = L"";
	UINT nChars = ::DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);
	CString fileName(szPath, nChars);
	str fn;
	CString fmt = fileName.Right(4);
	CString info, title, tmp;
	tmp.LoadStringW(IDS_STRING_OPENCONFIRM);
	info.Format(tmp, fileName);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (fmt == L".NPK" || fmt == L".npk") {
		if (IDOK == MessageBox(info, title)) {
		//if (IDOK == MessageBox(L"��" + fileName + L"����", L"��ҷ��ʾ��")) {
			no.release();
			CStrToStr(fileName, fn);
			if (no.loadFile(fn)) {
				info.LoadStringW(IDS_STRING_READFINISHED);
				MessageBox(info, title);
				//MessageBox(L"��ȡ�������");
			}
			else {
				info.LoadStringW(IDS_STRING_READFAILED);
				MessageBox(info, title);
				//MessageBox(L"��ȡʧ������");
				return;
			}
			fileNPKname = fileName;
			fileOpen = true;
			mixMode = false;
			updateIMGlist();
			if (no.count > 0) {
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
	}
	if (fmt == L".MPL" || fmt == L".mpl") {
		if (IDOK == MessageBox(info, title)) {
		//if (IDOK == MessageBox(L"��" + fileName + L"����", L"��ҷ��ʾ��")) {
			no.release();
			CStrToStr(fileName, fn);
			if (no.loadFile(fn)) {
				info.LoadStringW(IDS_STRING_READFINISHED);
				MessageBox(info, title);
				//MessageBox(L"��ȡ�������");
			}
			else {
				info.LoadStringW(IDS_STRING_READFAILED);
				MessageBox(info, title);
				//MessageBox(L"��ȡʧ������");
				return;
			}
			fileNPKname = fileName;
			fileOpen = true;
			mixMode = true;
			updateIMGlist();
			if (no.count > 0) {
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
	}
	if (fmt == L".IMG" || fmt == L".img") {
		if (!fileOpen) {
			if (IDOK == MessageBox(info, title)) {
			//if (IDOK == MessageBox(L"��" + fileName + L"����", L"��ҷ��ʾ��")) {
				io.Release();
				CStrToStr(fileName, fn);
				if (io.LoadFile(fn)) {
					info.LoadStringW(IDS_STRING_READFINISHED);
					MessageBox(info, title);
					//MessageBox(L"��ȡ�������");
				}
				else {
					info.LoadStringW(IDS_STRING_READFAILED);
					MessageBox(info, title);
					//MessageBox(L"��ȡʧ������");
					return;
				}
				no.release();
				no.create();
				fileIMGname = fileName;
				fileNPKname = L"newNPK.npk";
				fileOpen = true;
				mixMode = false;
				fileName = shorten(fileName);
				CStrToStr(toSl(fileName), fn);
				no.IMGpush(io, fn);
				switchIMGver(io.version);
				updateIMGlist();
				updatePIClist();
				updateCLRlist();
				updateDDSlist();
				updateNPKInfo();
				updateIMGInfo();
				updatePICInfo();
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
		else {
			UINT fileCount = ::DragQueryFile(hDropInfo, -1, NULL, NULL);
			if (fileCount == 1) {
				tmp.LoadStringW(IDS_STRING_INSERTINFOLISTCONFIRM);
				info.Format(tmp, fileName);
				if (IDOK == MessageBox(info, title)) {
				//if (IDOK == MessageBox(L"��" + fileName + L"�����IMG�б�����", L"��ҷ��ʾ��")) {
					CStrToStr(fileName, fn);
					IMGobject io(fn);
					if (no.IMGpush(io, fn)) {
						info.LoadStringW(IDS_STRING_INSERTFINISHED);
						MessageBox(info, title);
						//MessageBox(L"�����������");
						{
							m_lIMG.InsertItem(m_lIMG.GetItemCount(), shorten(toSl(shorten(fileName))));
						}
					}
					else {
						info.LoadStringW(IDS_STRING_INSERTFAILED);
						MessageBox(info, title);
						//MessageBox(L"����ʧ������");
					}
					io.Release();
					updateNPKInfo();
				}
			}
			else if (fileCount > 1) {
				tmp.LoadStringW(IDS_STRING_INSERTINFOLISTCONFIRM2);
				info.Format(tmp, fileName);
				if (IDOK == MessageBox(info, title)) {
				//if (IDOK == MessageBox(L"����Щ�ļ������IMG�б�����", L"��ҷ��ʾ��")) {
					for (int i = 0; i < fileCount; i++) {
						WCHAR szPath[MAX_PATH] = L"";
						nChars = ::DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
						fileName = CString(szPath, nChars);
						str fn;
						fmt = fileName.Right(4);
						CStrToStr(fileName, fn);
						if ((fmt == L".IMG" || fmt == L".img")) {
							IMGobject io;
							if (io.LoadFile(fn)) {
								no.IMGpush(io, fn);
								{
									m_lIMG.InsertItem(m_lIMG.GetItemCount(), shorten(toSl(shorten(fileName))));
								}
							}
							io.Release();
						}
						updateNPKInfo();
					}
					info.LoadStringW(IDS_STRING_INSERTFINISHED);
					MessageBox(info, title);
					//MessageBox(L"�����������");
				}
			}
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
}



void CExRabbitDlg::OnPicMenuSetXY()
{
	// TODO: �ڴ���������������
	if (!dispModeAbs) {
		CString info, title;
		title.LoadStringW(IDS_MESSAGE_TITLE);
		info.LoadStringW(IDS_STRING_SETRELATIVECOORDINATESMODE);
		MessageBox(info, title);
		//MessageBox(L"�뽫��ʾģʽ����Ϊ�����������ʾ����\r\n���򽫿�����������׼����Ч����", L"��ʾ��");
	}
	MOVEW(dlgSetXY);
	dlgSetXY.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnDisplayMenuShowCompare()
{
	// TODO: �ڴ���������������
	dispModeCompare = !dispModeCompare;
	if (dispModeCompare)
		dispModeAbs = true;
	draw();
}


void CExRabbitDlg::OnDisplayMenuSetCompare()
{
	// TODO: �ڴ���������������
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	defExt.LoadStringW(IDS_STRING_V4PALETTE);
	extFilter.LoadStringW(IDS_STRING_V4PALETTE2);
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	str fn;
	CString fileName;
	if (dlg.DoModal() == IDOK) {
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		ioComp.Release();
		if (ioComp.LoadFile(fn)) {
			info.LoadStringW(IDS_STRING_READFINISHED);
			MessageBox(info, title);
			//MessageBox(L"��ȡ��ϣ�");
		}
		else {
			info.LoadStringW(IDS_STRING_READFAILED);
			MessageBox(info, title);
			//MessageBox(L"��ȡʧ�ܣ�");
			return;
		}
	}
}


void CExRabbitDlg::OnImgMenuCompareAs()
{
	// TODO: �ڴ���������������
	int row = crtIMGid;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if (row < 0) {
		return;
	}
	ioComp.Release();
	no.IMGextract(row, ioComp);
	info.LoadStringW(IDS_STRING_ALREADYSETTOCOMPAREDIMG);
	MessageBox(info, title);
	MessageBox(L"�Ѿ�����IMG��Ϊ�Ա�IMG������\r\bͨ����IMG�Ա�ģʽ���鿴����", L"��ʾ��");
}


void CExRabbitDlg::OnClrMenuLoadAct()
{
	// TODO: �ڴ���������������
	int clrID = m_cbPro.GetCurSel();
	if (clrID < 0)
		clrID = 0;
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act||");
	defExt.LoadStringW(IDS_STRING_PHOTOSHOPPALETTE); 
	extFilter.LoadStringW(IDS_STRING_PHOTOSHOPPALETTE2);
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	CString fileName;
	str fn;
	int i, k;
	lcolor lc;
	if (dlg.DoModal() == IDOK) {
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if (!palette::loadACT(fn, lc)) {
			info.LoadStringW(IDS_STRING_NOTRECOGNIZEDPALETTE);
			MessageBox(info, title);
			//MessageBox(L"δʶ��ĵ�ɫ���ļ�����", L"��ʾ��");
			return;
		}
		k = io.paletteData[clrID].size();
		for (i = 0; i < k; i++)
			io.CLRremove(0, clrID);
		for (i = 0; i < lc.size(); i++) {
			io.CLRpush(lc[i], clrID);
		}
		saveAlert = true;
		info.LoadStringW(IDS_STRING_READFINISHED);
		MessageBox(info, title);
		//MessageBox(L"��ȡ�������", L"��ʾ��");
		updateInfo();
		updateCLRlist();
		updateNPKInfo();
		updateIMGInfo();
		updatePICInfo();
		saveAlert = true;
		draw();
	}
}


void CExRabbitDlg::OnClrMenuExportAct()
{
	// TODO: �ڴ���������������
	int clrID = m_cbPro.GetCurSel();
	if (clrID < 0)
		clrID = 0;
	str fn;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	CString fileName = getOutPutDir(fileNPKname, fileIMGname) + L"Palette" + NumToCStr(clrID) + L".ACT";
	CStrToStr(fileName, fn);
	palette::makeACT(fn, io.paletteData[clrID]);
	info.LoadStringW(IDS_STRING_FILESAVEDAS);
	MessageBox(info + fileName, title);
	//MessageBox(L"�ѱ���Ϊ" + fileName + L"��", L"��ʾ��");
}


void CExRabbitDlg::OnPicMenuExpand()
{
	// TODO: �ڴ���������������
	point allPt1(10000, 10000);
	point allPt2(-10000, -10000);
	PICinfo pi;
	for (int i = 0; i < io.indexCount; i++) {
		io.GetPICInfo(i, pi);
		if (pi.get_format() != LINK) {
			if (allPt1.get_X() > pi.get_basePt().get_X()) {
				allPt1.set_X(pi.get_basePt().get_X());
			}
			if (allPt1.get_Y() > pi.get_basePt().get_Y()) {
				allPt1.set_Y(pi.get_basePt().get_Y());
			}
			if (allPt2.get_X() < pi.get_basePt().get_X() + pi.get_picSize().get_W() - 1) {
				allPt2.set_X(pi.get_basePt().get_X() + pi.get_picSize().get_W() - 1);
			}
			if (allPt2.get_Y() < pi.get_basePt().get_Y() + pi.get_picSize().get_H() - 1) {
				allPt2.set_Y(pi.get_basePt().get_Y() + pi.get_picSize().get_H() - 1);
			}
		}
	}
	int row = m_lPicture.GetSelectionMark();
	if (row < 0)
		return;
	io.GetPICInfo(row, pi);
	dlgExpand.m_a1.SetWindowText(NumToCStr(pi.get_basePt().get_X()));
	dlgExpand.m_a2.SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
	dlgExpand.m_a3.SetWindowText(NumToCStr(pi.get_basePt().get_X() + pi.get_picSize().get_W() - 1));
	dlgExpand.m_a4.SetWindowText(NumToCStr(pi.get_basePt().get_Y() + pi.get_picSize().get_H() - 1));
	dlgExpand.m_a5.SetWindowText(NumToCStr(pi.get_picSize().get_W()));
	dlgExpand.m_a6.SetWindowText(NumToCStr(pi.get_picSize().get_H()));
	dlgExpand.m_b1.SetWindowText(NumToCStr(allPt1.get_X()));
	dlgExpand.m_b2.SetWindowText(NumToCStr(allPt1.get_Y()));
	dlgExpand.m_b3.SetWindowText(NumToCStr(allPt2.get_X()));
	dlgExpand.m_b4.SetWindowText(NumToCStr(allPt2.get_Y()));
	dlgExpand.m_b5.SetWindowText(NumToCStr(allPt2.get_X() - allPt1.get_X() + 1));
	dlgExpand.m_b6.SetWindowText(NumToCStr(allPt2.get_Y() - allPt1.get_Y() + 1));
	dlgExpand.m_c1.SetWindowText(L"0");
	dlgExpand.m_c2.SetWindowText(L"0");
	dlgExpand.m_c3.SetWindowText(L"0");
	dlgExpand.m_c4.SetWindowText(L"0");
	dlgExpand.ShowWindow(SW_SHOW);
	MOVEW(dlgExpand);
	dlgExpand.m_cb.SetCurSel(0);
	dlgExpand.OnCbnSelchangeCombo2();
}


void CExRabbitDlg::OnMix0()
{
	// TODO: �ڴ���������������
	dispMixMode = LAY;
	CString tra; 
	tra.LoadStringW(IDS_STRING_LAY);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"����");
	draw();
}


void CExRabbitDlg::OnMix1()
{
	// TODO: �ڴ���������������
	dispMixMode = DARKEN;
	CString tra;
	tra.LoadStringW(IDS_STRING_DARKEN);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"�䰵");
	draw();
}


void CExRabbitDlg::OnMix2()
{
	// TODO: �ڴ���������������
	dispMixMode = MULTIPLY;
	CString tra;
	tra.LoadStringW(IDS_STRING_MULTIPLY);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"��Ƭ����");
	draw();
}


void CExRabbitDlg::OnMix3()
{
	// TODO: �ڴ���������������
	dispMixMode = COLORBURN;
	CString tra;
	tra.LoadStringW(IDS_STRING_COLORBURN);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"��ɫ����");
	draw();
}


void CExRabbitDlg::OnMix4()
{
	// TODO: �ڴ���������������
	dispMixMode = LINEARBURN;
	CString tra;
	tra.LoadStringW(IDS_STRING_LINEARBURN);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"���Լ���");
	draw();
}


void CExRabbitDlg::OnMix5()
{
	// TODO: �ڴ���������������
	dispMixMode = LIGHTEN;
	CString tra;
	tra.LoadStringW(IDS_STRING_LIGHTEN);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"����");
	draw();
}


void CExRabbitDlg::OnMix6()
{
	// TODO: �ڴ���������������
	dispMixMode = SCREEN;
	CString tra;
	tra.LoadStringW(IDS_STRING_SCREEN);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"��ɫ");
	draw();
}


void CExRabbitDlg::OnMix7()
{
	// TODO: �ڴ���������������
	dispMixMode = COLORDODGE;
	CString tra;
	tra.LoadStringW(IDS_STRING_COLORDODGE);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"��ɫ����");
	draw();
}


void CExRabbitDlg::OnMix8()
{
	// TODO: �ڴ���������������
	dispMixMode = LINEARDODGE;
	CString tra;
	tra.LoadStringW(IDS_STRING_LINEARDODGE);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"���Լ���");
	draw();
}


void CExRabbitDlg::OnMix9()
{
	// TODO: �ڴ���������������
	dispMixMode = OVERLAY;
	CString tra;
	tra.LoadStringW(IDS_STRING_OVERLAY);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"�ص�");
	draw();
}


void CExRabbitDlg::OnMix10()
{
	// TODO: �ڴ���������������
	dispMixMode = HARDLIGHT;
	CString tra;
	tra.LoadStringW(IDS_STRING_HARDLIGHT);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"ǿ��");
	draw();
}


void CExRabbitDlg::OnMix11()
{
	// TODO: �ڴ���������������
	dispMixMode = SOFTLIGHT;
	CString tra;
	tra.LoadStringW(IDS_STRING_SOFTLIGHT);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"���");
	draw();
}


void CExRabbitDlg::OnMix12()
{
	// TODO: �ڴ���������������
	dispMixMode = VIVIDLIGHT;
	CString tra;
	tra.LoadStringW(IDS_STRING_VIVIDLIGHT);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"����");
	draw();
}


void CExRabbitDlg::OnMix13()
{
	// TODO: �ڴ���������������
	dispMixMode = LINEARLIGHT;
	CString tra;
	tra.LoadStringW(IDS_STRING_LINEARLIGHT);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"���Թ�");
	draw();
}


void CExRabbitDlg::OnMix14()
{
	// TODO: �ڴ���������������
	dispMixMode = PINLIGHT;
	CString tra;
	tra.LoadStringW(IDS_STRING_PINLIGHT);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"���");
	draw();
}


void CExRabbitDlg::OnMix15()
{
	// TODO: �ڴ���������������
	dispMixMode = HARDMIX;
	CString tra;
	tra.LoadStringW(IDS_STRING_HARDMIX);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"ʵɫ���");
	draw();
}


void CExRabbitDlg::OnMix16()
{
	// TODO: �ڴ���������������
	dispMixMode = DIFFER;
	CString tra;
	tra.LoadStringW(IDS_STRING_DIFFER);
	m_edInfo8.SetWindowText(tra);
	//m_edInfo8.SetWindowText(L"��ֵ");
	draw();
}


void CExRabbitDlg::OnClrMenuWin()
{
	// TODO: �ڴ���������������
	dlgColor.ShowWindow(true);
	dlgColor.setClr(&io.paletteData[m_cbPro.GetCurSel()]);
	dlgColor.draw();
	useColorTable = true;
	MOVEW(m_lColor);
	m_lColor.EnableWindow(false);
}



void CExRabbitDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//�������
	if (fwSide == WMSZ_LEFT || fwSide == WMSZ_TOPLEFT || fwSide == WMSZ_BOTTOMLEFT) {
		if (pRect->right - pRect->left <= 820) {
			pRect->left = pRect->right - 820;
		}
	}
	else {
		if (pRect->right - pRect->left <= 820) {
			pRect->right = pRect->left + 820;
		}
	}
	if (fwSide == WMSZ_TOP || fwSide == WMSZ_TOPLEFT || fwSide == WMSZ_TOPRIGHT) {
		if (pRect->bottom - pRect->top <= 640) {
			pRect->top = pRect->bottom - 640;
		}
	}
	else {
		if (pRect->bottom - pRect->top <= 640) {
			pRect->bottom = pRect->top + 640;
		}
	}
	sizing = 1;
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
}


void CExRabbitDlg::OnSize(UINT nType, int cx, int cy)
{
	TRACE(L"ONSIZE\n");
	CDialogEx::OnSize(nType, cx, cy);
	CRect rc;
	GetClientRect(rc);
	if (sizing) {
		adjustWindow(rc.Width(), rc.Height());
		draw();
		OnMouseMove(0, CPoint(0, 0));
		Invalidate();
		sizing = 0;
		TRACE(L"SIZED\n");
	}
	// TODO: �ڴ˴������Ϣ����������
}


void CExRabbitDlg::OnStnClickedLogo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString info, title;
	info.LoadStringW(IDS_STRING_DONOTCLICK);
	title.LoadStringW(IDS_MESSAGE_TITLE);
	MessageBox(info, title);
	//MessageBox(L"�������><��",L"��ʾ����");
}


void CExRabbitDlg::OnTool1()
{
	// TODO: �ڴ���������������
	MOVEW(toolIMGSearch);
	toolIMGSearch.ShowWindow(TRUE);
}


void CExRabbitDlg::OnTool2()
{
	// TODO: �ڴ���������������
	MOVEW(toolAvatar);
	toolAvatar.ShowWindow(TRUE);
}
