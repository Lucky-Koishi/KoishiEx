
// ExRabbitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "afxdialogex.h"
#include "Tinysetbrush.h"
#include "AdjustColorDlg.h"
#include "TinyAddMark.h"
#include "DictAvatar.h"
#include "ModalLock.h"
#include "ModalLockInput.h"
#include <locale.h>

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
#define TIC true
#define TOC true
#endif

CExRabbitDlg::CExRabbitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExRabbitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAIN);

	profile.loadProfile();
	width = 1210;
	height = 650;
	drawPara.texture = false;
	drawPara.showPalette = true;
	drawPara.showAxis = true;		
	drawPara.showCanvas = true;
	drawPara.showBound = true;
	drawPara.indexMode = false;
	drawPara.entireTextureMode = false;
	drawPara.compareMode = false;
	drawPara.mixMode = LAY;
	drawPara.zoom = 0;
	drawPara.zoomRate = 1.00;
	canvasOperatePara.canvasOperating = false;
	canvasOperatePara.canvasOperation = CANVAS_SHOW;
	canvasOperatePara.currentCursor = CANVAS_SHOW;
	canvasOperatePara.canvasPara = CANVAS_DEFAULT;
	canvasOperatePara.brushShape = 1;		
	canvasOperatePara.brushSize = 5;
	canvasOperatePara.oldMatrixEnable = false;
	fileNPKname = L"newNPK.npk";
	fileIMGname = L"newIMG.img";
	
	setDefaultColor();
	colorOperatePara.current = 1;
	colorOperatePara.tolerance = 10;
	for(int i = 0;i<256;i++){
		colorOperatePara.isChosen[i] = false;
	}
	colorOperatePara.layout = 0;
	setDefaultColor();
#if UGLY
	cl = colorOperatePara.v2Color;
#endif
	
	drawing = 0;
	drawingColor = 0;
	processing = 0;
	playing = 0;
	lazyTime = 0;
	sizing = 0;
	crtIMGid = -1;
	fndIMGid = -1;
	crtPICid = -1;
	crtTEXid = -1;
	saveAlert = false;
}

BEGIN_MESSAGE_MAP(CExRabbitDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_MENU, &CExRabbitDlg::OnBnClickedButtonMenu)
	ON_BN_CLICKED(IDC_BUTTON_MENU2, &CExRabbitDlg::OnBnClickedButtonMenu2)
	ON_BN_CLICKED(IDC_BUTTON_MENU3, &CExRabbitDlg::OnBnClickedButtonMenu3)
	ON_BN_CLICKED(IDC_BUTTON_PALETTE, &CExRabbitDlg::OnBnClickedButtonPalette)
	ON_BN_CLICKED(IDC_BUTTON_IMGSEARCH, &CExRabbitDlg::OnBnClickedButtonImgsearch)

	ON_NOTIFY(NM_CLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMClickListImg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMRClickListImg)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_IMG, &CExRabbitDlg::OnLvnKeydownListImg)

	ON_NOTIFY(NM_CLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMClickListTex)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMRClickListTex)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_DDS, &CExRabbitDlg::OnLvnKeydownListTex)

	ON_NOTIFY(NM_CLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMClickListPic)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMRClickListPic)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_PIC, &CExRabbitDlg::OnLvnKeydownListPic)

	ON_CBN_SELCHANGE(IDC_COMBO_PRO, &CExRabbitDlg::OnCbnSelchangeComboPro)
	ON_WM_MOUSEMOVE()

	ON_WM_DROPFILES()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_STN_CLICKED(IDC_LOGO, &CExRabbitDlg::OnStnClickedLogo)

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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_TOOL_BUTTON1, &CExRabbitDlg::OnBnClickedToolButton1)
	ON_BN_CLICKED(IDC_TOOL_BUTTON2, &CExRabbitDlg::OnBnClickedToolButton2)
	ON_BN_CLICKED(IDC_TOOL_BUTTON3, &CExRabbitDlg::OnBnClickedToolButton3)
	ON_BN_CLICKED(IDC_TOOL_BUTTON4, &CExRabbitDlg::OnBnClickedToolButton4)
	ON_BN_CLICKED(IDC_TOOL_BUTTON7, &CExRabbitDlg::OnBnClickedToolButton7)
	ON_BN_CLICKED(IDC_TOOL_BUTTON5, &CExRabbitDlg::OnBnClickedToolButton5)
	ON_BN_CLICKED(IDC_TOOL_BUTTON6, &CExRabbitDlg::OnBnClickedToolButton6)
	ON_BN_CLICKED(IDC_TOOL_BUTTON8, &CExRabbitDlg::OnBnClickedToolButton8)
	ON_BN_CLICKED(IDC_TOOL_BUTTON9, &CExRabbitDlg::OnBnClickedToolButton9)
	ON_BN_CLICKED(IDC_TOOL_BUTTON10, &CExRabbitDlg::OnBnClickedToolButton10)
	ON_BN_CLICKED(IDC_TOOL_BUTTON11, &CExRabbitDlg::OnBnClickedToolButton11)
	ON_BN_CLICKED(IDC_TOOL_BUTTON12, &CExRabbitDlg::OnBnClickedToolButton12)
	ON_BN_CLICKED(IDC_TOOL_BUTTON13, &CExRabbitDlg::OnBnClickedToolButton13)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_TOOL_BUTTON14, &CExRabbitDlg::OnBnClickedToolButton14)
	ON_BN_CLICKED(IDC_TOOL_BUTTON15, &CExRabbitDlg::OnBnClickedToolButton15)
	ON_COMMAND(ID_MENU_COLOR_TABLE_CHOOSE_ALL, &CExRabbitDlg::OnMenuColorTableChooseAll)
	ON_COMMAND(ID_MENU_COLOR_TABLE_CHOOSE_NONE, &CExRabbitDlg::OnMenuColorTableChooseNone)
	ON_COMMAND(ID_MENU_COLOR_TABLE_INVERSE_CHOOSE, &CExRabbitDlg::OnMenuColorTableInverseChoose)
	ON_COMMAND(ID_MENU_COLOR_TABLE_CHOOSE_FAMILIAR, &CExRabbitDlg::OnMenuColorTableChooseFamiliar)
	ON_COMMAND(ID_MENU_COLOR_TABLE_DELETE_ONE, &CExRabbitDlg::OnMenuColorTableDeleteOne)
	ON_COMMAND(ID_MENU_COLOR_TABLE_DELETE_ALL, &CExRabbitDlg::OnMenuColorTableDeleteAll)
	ON_COMMAND(ID_MENU_PICTURE_CHOOSE_ALL, &CExRabbitDlg::OnMenuPictureChooseAll)
	ON_COMMAND(ID_MENU_PICTURE_CHOOSE_INVERSE, &CExRabbitDlg::OnMenuPictureChooseInverse)
	ON_COMMAND(ID_MENU_PICTURE_CHOOSE_HIGHLINE, &CExRabbitDlg::OnMenuPictureChooseHighline)
	ON_COMMAND(ID_MENU_PICTURE_INSERT, &CExRabbitDlg::OnMenuPictureInsert)
	ON_COMMAND(ID_MENU_PICTURE_INSERT_PATCH, &CExRabbitDlg::OnMenuPictureInsertPatch)
	ON_COMMAND(ID_MENU_PICTURE_DELETE, &CExRabbitDlg::OnMenuPictureDelete)
	ON_COMMAND(ID_MENU_PICTURE_DELETE_PATCH, &CExRabbitDlg::OnMenuPictureDeletePatch)
	ON_COMMAND(ID_MENU_PICTURE_AXIS_MODIFY, &CExRabbitDlg::OnMenuPictureAxisModify)
	ON_COMMAND(ID_MENU_PICTURE_CANVAS, &CExRabbitDlg::OnMenuPictureCanvas)
	ON_COMMAND(ID_MENU_PICTURE_CLEAR, &CExRabbitDlg::OnMenuPictureClear)
	ON_COMMAND(ID_MENU_PICTURE_LOSEBLACK, &CExRabbitDlg::OnMenuPictureLoseblack)
	ON_COMMAND(ID_MENU_PICTURE_GRADIENT, &CExRabbitDlg::OnMenuPictureGradient)
	ON_COMMAND(ID_MENU_PICTURE_COLOR, &CExRabbitDlg::OnMenuPictureColor)
	ON_COMMAND(ID_MENU_PICTURE_MARK, &CExRabbitDlg::OnMenuPictureMark)
	ON_COMMAND(ID_MENU_PICTURE_GET_PNG, &CExRabbitDlg::OnMenuPictureGetPng)
	ON_COMMAND(ID_MENU_PICTURE_GET_PNG_PATCH, &CExRabbitDlg::OnMenuPictureGetPngPatch)
	ON_COMMAND(ID_MENU_TEXTURE_CHOOSE_ALL, &CExRabbitDlg::OnMenuTextureChooseAll)
	ON_COMMAND(ID_MENU_TEXTURE_CHOOSE_INVERSE, &CExRabbitDlg::OnMenuTextureChooseInverse)
	ON_COMMAND(ID_MENU_TEXTURE_CHOOSE_HIGHLINE, &CExRabbitDlg::OnMenuTextureChooseHighline)
	ON_COMMAND(ID_MENU_TEXTURE_INSERT, &CExRabbitDlg::OnMenuTextureInsert)
	ON_COMMAND(ID_MENU_TEXTURE_DELETE, &CExRabbitDlg::OnMenuTextureDelete)
	ON_COMMAND(ID_MENU_TEXTURE_DELETE_PATCH, &CExRabbitDlg::OnMenuTextureDeletePatch)
	ON_COMMAND(ID_MENU_TEXTURE_GET_PNG, &CExRabbitDlg::OnMenuTextureGetPng)
	ON_COMMAND(ID_MENU_TEXTURE_GET_PNG_PATCH, &CExRabbitDlg::OnMenuTextureGetPngPatch)
	ON_COMMAND(ID_MENU_TEXTURE_GET_ORIGIN, &CExRabbitDlg::OnMenuTextureGetOrigin)
	ON_COMMAND(ID_MENU_TEXTURE_GET_ORIGIN_PATCH, &CExRabbitDlg::OnMenuTextureGetOriginPatch)
	ON_COMMAND(ID_MENU_PICTURE_INSERT2, &CExRabbitDlg::OnMenuPictureInsert2)
	ON_COMMAND(ID_MENU_PICTURE_INSERT_PATCH2, &CExRabbitDlg::OnMenuPictureInsertPatch2)
	ON_COMMAND(ID_MENU_TEXTURE_INSERT2, &CExRabbitDlg::OnMenuTextureInsert2)
	ON_COMMAND(ID_MENU_IMAGE_EXTRACT, &CExRabbitDlg::OnMenuImageExtract)
	ON_COMMAND(ID_MENU_IMAGE_EXTRACT_PATCH, &CExRabbitDlg::OnMenuImageExtractPatch)
	ON_COMMAND(ID_MENU_IMAGE_SAVE, &CExRabbitDlg::OnMenuImageSave)
	ON_COMMAND(ID_MENU_IMAGE_INSERT, &CExRabbitDlg::OnMenuImageInsert)
	ON_COMMAND(ID_MENU_IMAGE_REPLACE, &CExRabbitDlg::OnMenuImageReplace)
	ON_COMMAND(ID_MENU_IMAGE_DELETE, &CExRabbitDlg::OnMenuImageDelete)
	ON_COMMAND(ID_MENU_IMAGE_DELETE_PATCH, &CExRabbitDlg::OnMenuImageDeletePatch)
	ON_COMMAND(ID_MENU_IMAGE_RENAME, &CExRabbitDlg::OnMenuImageRename)
	ON_COMMAND(ID_MENU_IMAGE_TRANSFORM, &CExRabbitDlg::OnMenuImageTransform)
	ON_COMMAND(ID_MENU_IMAGE_CHOOSE_ALL, &CExRabbitDlg::OnMenuImageChooseAll)
	ON_COMMAND(ID_MENU_IMAGE_CHOOSE_HIGHLINE, &CExRabbitDlg::OnMenuImageChooseHighline)
	ON_COMMAND(ID_MENU_IMAGE_CHOOSE_REVERSE, &CExRabbitDlg::OnMenuImageChooseReverse)
	ON_COMMAND(ID_MENU_IMAGE_MOVE_UP, &CExRabbitDlg::OnMenuImageMoveUp)
	ON_COMMAND(ID_MENU_IMAGE_MOVE_DOWN, &CExRabbitDlg::OnMenuImageMoveDown)
	ON_COMMAND(ID_MENU_IMAGE_AUTOSORT, &CExRabbitDlg::OnMenuImageAutoSort)
	ON_COMMAND(ID_MENU_IMAGE_MIX, &CExRabbitDlg::OnMenuImageMix)
	ON_COMMAND(ID_MENU_IMAGE_SET_COMPARE, &CExRabbitDlg::OnMenuImageSetCompare)
	ON_COMMAND(ID_MENU_IMAGE_INSERT2, &CExRabbitDlg::OnMenuImageInsert2)
	ON_COMMAND(ID_MENU_COLOR_TABLE_IMPORT, &CExRabbitDlg::OnMenuColorTableImport)
	ON_COMMAND(ID_MENU_COLOR_TABLE_EXPORT, &CExRabbitDlg::OnMenuColorTableExport)
	ON_COMMAND(ID_MENU_COLOR_PALETTE_NEW, &CExRabbitDlg::OnMenuColorPaletteNew)
	ON_COMMAND(ID_MENU_COLOR_PALETTE_COPY, &CExRabbitDlg::OnMenuColorPaletteCopy)
	ON_COMMAND(ID_MENU_COLOR_PALETTE_IMPORT, &CExRabbitDlg::OnMenuColorPaletteImport)
	ON_COMMAND(ID_MENU_COLOR_PALETTE_DELETE, &CExRabbitDlg::OnMenuColorPaletteDelete)
	ON_COMMAND(IDM_TOOL_AVATAR, &CExRabbitDlg::OnToolAvatar)
	ON_COMMAND(IDM_TOOL_NPK_DICT, &CExRabbitDlg::OnToolNpkDict)
	ON_COMMAND(IDM_TOOL_IMG_SEARCH, &CExRabbitDlg::OnToolImgSearch)
	ON_COMMAND(IDM_TOOL_DOWNLOAD, &CExRabbitDlg::OnToolDownload)
	ON_COMMAND(IDM_TOOL_FORCE_EXTRACT, &CExRabbitDlg::OnToolForceExtract)
	ON_COMMAND(IDM_TOOL_OPEN_OUTPUT_FOLDER, &CExRabbitDlg::OnToolOpenOutputFolder)
	ON_COMMAND(IDM_DRAW_COLORTABLE, &CExRabbitDlg::OnDrawColorTable)
	ON_COMMAND(IDM_DRAW_CANVAS, &CExRabbitDlg::OnDrawCanvas)
	ON_COMMAND(IDM_DRAW_AXIS, &CExRabbitDlg::OnDrawAxis)
	ON_COMMAND(IDM_DRAW_BOUND, &CExRabbitDlg::OnDrawBound)
	ON_COMMAND(IDM_DRAW_SET_COMPARE1, &CExRabbitDlg::OnDrawSetCompare1)
	ON_COMMAND(IDM_DRAW_SET_COMPARE2, &CExRabbitDlg::OnDrawSetCompare2)
	ON_COMMAND(IDM_DRAW_COMPARE_ENABLED, &CExRabbitDlg::OnDrawCompareEnabled)
	ON_COMMAND(IDM_DRAW_COMPARE_DISABLED, &CExRabbitDlg::OnDrawCompareDisabled)
	ON_COMMAND(ID_MENU_IMAGE_HIDE, &CExRabbitDlg::OnMenuImageHide)
	ON_COMMAND(ID_TOOLS_NPK_LOCK, &CExRabbitDlg::OnToolsNpkLock)
	ON_COMMAND(ID_MENU_PICTURE_GET_GIF, &CExRabbitDlg::OnMenuPictureGetGIF)
	ON_COMMAND(ID_MENU_COLOR_TABLE_CLASSICAL, &CExRabbitDlg::OnMenuColorTableClassical)
	ON_COMMAND(ID_MENU_COLOR_TABLE_16, &CExRabbitDlg::OnMenuColorTable16)
	ON_COMMAND(ID_MENU_COLOR_TABLE_256, &CExRabbitDlg::OnMenuColorTable256)
	ON_COMMAND(ID_MENU_COLOR_TABLE_EXTRACT_CURRENT, &CExRabbitDlg::OnMenuColorTableExtractCurrent)
	ON_COMMAND(ID_MENU_COLOR_TABLE_EXTRACT_ALL_FRAME, &CExRabbitDlg::OnMenuColorTableExtractAllFrame)
	ON_COMMAND(ID_MENU_IMAGE_INSERT_OTHER, &CExRabbitDlg::OnMenuImageInsertOther)
	ON_COMMAND(ID_MENU_IMAGE_INSERT_COPY, &CExRabbitDlg::OnMenuImageInsertCopy)
	ON_COMMAND(ID_MENU_IMAGE_INSERT_REF, &CExRabbitDlg::OnMenuImageInsertLink)
	ON_COMMAND(ID_MENU_IMAGE_DELINK, &CExRabbitDlg::OnMenuImageDelink)
	END_MESSAGE_MAP()
/////////

// CExRabbitDlg ��Ϣ�������

BOOL CExRabbitDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	//���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//////////////////////////////////
	SetWindowPos(NULL,0,0,width,height,SWP_NOZORDER|SWP_NOMOVE);
	CRect rc;
	GetClientRect(rc);
	adjustWindow(rc.Width(), rc.Height());
	// �ؼ���С����
	CREATEW(dNewFile,IDD_NEW_DIALOG);

	CREATEW(bar, IDD_TINY_PROGRESSBAR);
	CREATEW(toolIMGSearch,IDD_TOOL_IMGSEARCH);
	toolAvatar.profile = profile;
	CREATEW(toolAvatar,IDD_TOOL_AVATAR);
	CREATEW(toolDict,IDD_TOOL_DICT);
	CREATEW(toolSPK,IDD_TOOL_SPK);
	CREATEW(toolForceEx, IDD_TOOL_FORCEEXTRACT);
	

	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->EasyInsertColumn(L"IMG��,200");
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(L"������ʾNPK�ļ�����Ϣ");
	GET_CTRL(CEdit, IDC_EDIT_IMGINFO)->SetWindowText(L"������ʾIMG�ļ�����Ϣ");
	switchIMGver(V2);
	
	AfxBeginThread(lazyThread, this);
	AfxBeginThread(playThread, this);

	ioComp.create(V2);

	i_lIMG.Create(16,16, TRUE|ILC_COLOR24, 10, 1);
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_NUL));		//0����Դ����Ч
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_LINK));		//1����Դ��LINK
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_UNKNOWN));	//2����Դ
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_AUDIO));		//3����Դ
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON1));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON2));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON3));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON4));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON5));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON6));
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetImageList(&i_lIMG, LVSIL_SMALL);

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
	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetImageList(&i_lPIC, LVSIL_SMALL);
	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetImageList(&i_lPIC, LVSIL_SMALL);

	
#if UGLY
	m_buttonPic[0].LoadBitmap(IDB_TOOL_1);
	m_buttonPic[1].LoadBitmap(IDB_TOOL_2);
	m_buttonPic[2].LoadBitmap(IDB_TOOL_3);
	m_buttonPic[3].LoadBitmap(IDB_TOOL_4);
	m_buttonPic[4].LoadBitmap(IDB_TOOL_5);
	m_buttonPic[5].LoadBitmap(IDB_TOOL_6);
	m_buttonPic[6].LoadBitmap(IDB_TOOL_7);
	m_buttonPic[7].LoadBitmap(IDB_TOOL_8);
	m_buttonPic[8].LoadBitmap(IDB_TOOL_9);
	m_buttonPic[9].LoadBitmap(IDB_TOOL_10);
	m_buttonPic[10].LoadBitmap(IDB_TOOL_11);
	m_buttonPic[11].LoadBitmap(IDB_TOOL_12);
	m_buttonPic[12].LoadBitmap(IDB_TOOL_13);
	m_buttonPic[13].LoadBitmap(IDB_TOOL_14);
	m_buttonPic[14].LoadBitmap(IDB_TOOL_15);
	m_buttonPicX[0].LoadBitmap(IDB_TOOL_1);
	m_buttonPicX[1].LoadBitmap(IDB_TOOL_2X);
	m_buttonPicX[2].LoadBitmap(IDB_TOOL_3);
	m_buttonPicX[3].LoadBitmap(IDB_TOOL_4X);
	m_buttonPicX[4].LoadBitmap(IDB_TOOL_5X);
	m_buttonPicX[5].LoadBitmap(IDB_TOOL_6X);
	m_buttonPicX[6].LoadBitmap(IDB_TOOL_7X);
	m_buttonPicX[7].LoadBitmap(IDB_TOOL_8X);
	m_buttonPicX[8].LoadBitmap(IDB_TOOL_9X);
	m_buttonPicX[9].LoadBitmap(IDB_TOOL_10X);
	m_buttonPicX[10].LoadBitmap(IDB_TOOL_11X);
	m_buttonPicX[11].LoadBitmap(IDB_TOOL_12X);
	m_buttonPicX[12].LoadBitmap(IDB_TOOL_13X);
	m_buttonPicX[13].LoadBitmap(IDB_TOOL_14X);
	m_buttonPicX[14].LoadBitmap(IDB_TOOL_15X);
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
			m_logoPic.LoadBitmapW(IDB_BITMAP4);
	}
	
	GET_CTRL(CStatic, IDC_LOGO)->SetBitmap(m_logoPic);

#endif
	no.create();
	fileNPKname = L"newNPK.npk";
	updateIMGlist();

	m_ttc.Create(this);
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON1), L"��ʾѡ��");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON2), L"����ģʽ");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON3), L"ȫ֡��ʾ");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON4), L"IMG�Ա�ģʽ");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON5), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON6), L"�϶�����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON7), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON8), L"�ƶ�����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON9), L"�������");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON10), L"��ˢ");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON11), L"ֱ��");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON12), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON13), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON14), L"ȡɫ");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON15), L"��ӱ��");
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
		dc.FillSolidRect(rect,profile.mainColor); 
#endif
		CDialogEx::OnPaint();
		TRACE("1\n");
		draw(drawPara.texture);
		updateColorTable();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExRabbitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CExRabbitDlg::adjustWindow(int w, int h){
	//�������ڿؼ�
	CHECK_VALID(w>=700);
	CHECK_VALID(h>=500);
	width = w;
	height = h;
	barWidth = (w-540);
	barPart1 = barWidth*2/3;
	barPart2 = barWidth/3;
	barHeight = 30;
	GET_CTRL(CStatic, IDC_LOGO)->SetWindowPos(NULL,10,10,150,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU)->SetWindowPos(NULL,170,10,110,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU2)->SetWindowPos(NULL,290,10,110,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU3)->SetWindowPos(NULL,410,10,110,40,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_IMGSEARCH)->SetWindowPos(NULL,10,60,100,25,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_IMGSEARCH)->SetWindowPos(NULL,120,60,40,25,SWP_NOZORDER);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetWindowPos(NULL,10,95,150,h-115,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowPos(NULL,170,60,170,80,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_IMGINFO)->SetWindowPos(NULL,350,60,170,80,SWP_NOZORDER);
	
	GET_CTRL(CButton, IDC_BUTTON_PALETTE)->SetWindowPos(NULL,480,h-110,40,35,SWP_NOZORDER);
	//GET_CTRL(CButton, IDC_BUTTON_PALETTE2)->SetWindowPos(NULL,480,h-70,40,35,SWP_NOZORDER);
	GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetWindowPos(NULL,480,h-30,40,20,SWP_NOZORDER);

	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetWindowPos(NULL,170,150,350,(height-270)/2,SWP_NOZORDER);

	GET_CTRL(CEdit, IDC_EDIT_INFO2)->ShowWindow(SW_HIDE);
	GET_CTRL(CEdit, IDC_EDIT_INFO3)->ShowWindow(SW_HIDE);
	GET_CTRL(CEdit, IDC_EDIT_INFO4)->ShowWindow(SW_HIDE);
	GET_CTRL(CEdit, IDC_EDIT_INFO5)->ShowWindow(SW_HIDE);

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
	GET_CTRL(CButton, IDC_TOOL_BUTTON15)->SetWindowPos(NULL,530+delta*14,h-10-barHeight,delta,barHeight,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_INFO6)->SetWindowPos(NULL,530+barPart1+barPart2*0/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_INFO7)->SetWindowPos(NULL,530+barPart1+barPart2*2/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
	
	switch(io.version){
	case V5:
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetWindowPos(NULL,170,150+(height-270)/2+10,350,(height-270)/2,SWP_NOZORDER);
		break;
	default:
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetWindowPos(NULL,170,150,350,h-270,SWP_NOZORDER);
		break;
	}
}

void CExRabbitDlg::switchIMGver(IMGversion ver){
	//�л��汾����
	///////////////////////////////
	int i;
	switch(ver){
	case V2:
	case V4:
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetWindowPos(NULL,170,150,350,height-270,SWP_NOZORDER);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->ShowWindow(SW_HIDE);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ShowWindow(SW_SHOW);
		GET_CTRL(CButton, IDC_BUTTON_PALETTE)->ShowWindow(SW_SHOW);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ResetContent();
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->AddString(L"0");
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertColumn(L"֡��,64,��ɫ��ʽ,90,��׼����,80,�ߴ�,80,֡��ߴ�,80");
		break;
	case V5:
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetWindowPos(NULL,170,150+(height-280)/2+10,350,(height-280)/2,SWP_NOZORDER);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetWindowPos(NULL,170,150,350,(height-280)/2,SWP_NOZORDER);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ShowWindow(SW_SHOW);
		GET_CTRL(CButton, IDC_BUTTON_PALETTE)->ShowWindow(SW_SHOW);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->ShowWindow(SW_SHOW);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ShowWindow(SW_SHOW);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ResetContent();
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->AddString(L"0");
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertColumn(L"֡��,64,��ɫ��ʽ,90,��׼����,80,�ߴ�,80,֡��ߴ�,80,ʹ������,400");
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->EasyInsertColumn(L"����,64,��ɫ��ʽ,90,�ߴ�,80");
		//GET_CTRL(CGoodListCtrl, IDC_LIST_CLR)->EasyInsertColumn(L"ɫ��,64,RGBA����,70");
		break;
	case V6:
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetWindowPos(NULL,170,150,350,height-270,SWP_NOZORDER);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->ShowWindow(SW_HIDE);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ShowWindow(SW_SHOW);
		GET_CTRL(CButton, IDC_BUTTON_PALETTE)->ShowWindow(SW_SHOW);
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertColumn(L"֡��,64,��ɫ��ʽ,90,��׼����,80,�ߴ�,80,֡��ߴ�,80");
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ResetContent();
		for(i = 0;i<io.paletteData.getCount();i++)
			GET_CTRL(CComboBox, IDC_COMBO_PRO)->AddString(NumToCStr(i));
		if(io.paletteData.getCount()>=1){
			GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(0);
		}
		break;
	}
}

void CExRabbitDlg::updateIMGlist(){
	// ����IMG�б�
	/////////////////////////////
	updateInfo();
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->DeleteAllItems();
	for(int i = 0;i<no.count;i++){
		int li = no.checkLink(i);
		if(li == i){
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->EasyInsertItem(GetTail(StrToCStr(no.entry[i].comment)), getIconIMG((IMGversion)no.IMGgetVersion(i)));
		}else{
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->EasyInsertItem(GetTail(StrToCStr(no.entry[i].comment) + L"["+GetTail(StrToCStr(no.entry[li].comment))+L"]"), 1);
		}
	}
}

void CExRabbitDlg::updatePIClist(){
	// ����֡�б�
	////////////////////////////////
	CString cstr;
	int currentCount = GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();
	int i = 0;
	while(true){
		if(i < io.indexCount){
			if(i < currentCount){
				updatePICterm(i);
			}else{
				cstr = NumToCStr(i) + L",";
				cstr += FmtToCStr(io.PICcontent[i].format, io.version);
				if(io.PICcontent[i].format == LINK)
					cstr += NumToCStr(io.PICcontent[i].linkTo);
				cstr += L",";
				cstr += PtToCStr(io.PICcontent[i].basePt) + L",";
				cstr += SzToCStr(io.PICcontent[i].picSize)+L",";
				cstr += SzToCStr(io.PICcontent[i].frmSize)+L",";
				if(io.version == V5){
					cstr += L"����"+NumToCStr(io.PICcontent[i].TEXusing)+L":"+PtToCStr(io.PICcontent[i].TEXpointLT)+L"-"+PtToCStr(io.PICcontent[i].TEXpointRB);
				}
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertItem(cstr,getIconPIC(io.PICcontent[i].format));
			}
			i++;
		}else{
			if(i < currentCount){
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->DeleteItem(i);
				currentCount --;
			}else{
				break;
			}
		}
	}
	if(io.indexCount > 0){
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);   
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetSelectionMark(0);
		crtPICid = 0;
		draw();
	}
}
void CExRabbitDlg::updatePICterm(int pos){
	//ֻ����pos
	CHECK_VALID(pos>=0);
	CHECK_VALID(pos<io.indexCount);
	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItem(pos,0,LVIF_IMAGE,NULL,getIconPIC(io.PICcontent[pos].format),0,0,0);
	if(io.PICcontent[pos].format == LINK){
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 0, NumToCStr(pos));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 1, FmtToCStr(io.PICcontent[pos].format, io.version) + NumToCStr(io.PICcontent[pos].linkTo));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 2, L"");
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 3, L"");
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 4, L"");
		if(io.version == V5){
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 5, L"");
		}
	}else{
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 0, NumToCStr(pos));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 1, FmtToCStr(io.PICcontent[pos].format, io.version));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 2, PtToCStr(io.PICcontent[pos].basePt));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 3, SzToCStr(io.PICcontent[pos].picSize));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 4, SzToCStr(io.PICcontent[pos].frmSize));
		if(io.version == V5){
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 5, L"����"+NumToCStr(io.PICcontent[pos].TEXusing)+L":"+PtToCStr(io.PICcontent[pos].TEXpointLT)+L"-"+PtToCStr(io.PICcontent[pos].TEXpointRB));
		}
	}
}
void CExRabbitDlg::updateTEXlist(){
	//���������б�
	////////////////////////////////
	CString cstr;
	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->DeleteAllItems();
	for(int i=0;i<io.TEXcontent.size();i++){
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += FmtToCStr((colorFormat)(int)io.TEXcontent[i].format,V5)+L",";
		cstr += NumToCStr(io.TEXcontent[i].width)+L"��";
		cstr += NumToCStr(io.TEXcontent[i].height);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->EasyInsertItem(cstr,getIconPIC(io.TEXcontent[i].format));
	}
}
void CExRabbitDlg::setDefaultColor(){
	colorOperatePara.v2Color.clear();
	colorOperatePara.v2Color.push_back(color(0,0,0,0));
	colorOperatePara.v2Color.push_back(color(0xFF,0XFF,0XFF,0XFF));
	colorOperatePara.v2Color.push_back(color(0xFF,0XBB,0XBB,0XBB));
	colorOperatePara.v2Color.push_back(color(0xFF,0X77,0X77,0X77));
	colorOperatePara.v2Color.push_back(color(0xFF,0X33,0X33,0X33));
	colorOperatePara.v2Color.push_back(color(0xFF,0,0,0));
	colorHSV ch;
	for(int i=0;i<10;i++){
		color clr;
		clr.alpha = 0xFF;
		ch.H = (i*36+350)%360;
		ch.V = 1;
		ch.S = 0.33;
		clr.useHSV(ch);
		colorOperatePara.v2Color.push_back(clr);
		ch.S = 1;
		clr.useHSV(ch);
		colorOperatePara.v2Color.push_back(clr);
		ch.V = 0.66;
		clr.useHSV(ch);
		colorOperatePara.v2Color.push_back(clr);
	}
}
void CExRabbitDlg::updateColorTable(){
	if(io.version == V2 || io.version == VUDEF){
		cl = colorOperatePara.v2Color;
	}else if(io.version == V6){
		int curSel = GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel(); 
		if(curSel < 0)
			curSel = 0;
		if(curSel >= io.paletteData.getCount()){
			cl.clear();
		}else{
			cl = io.paletteData[curSel];
		}
	}else if(io.version == V4 || io.version == V5){
		cl = io.paletteData[0];
	}
	if(cl.size() <= 46){
		colorOperatePara.layout = 0;
	}else if(cl.size() <= 73){
		colorOperatePara.layout = 1;
	}else if(cl.size() <= 118){
		colorOperatePara.layout = 2;
	}else if(cl.size() <= 198){
		colorOperatePara.layout = 3;
	}else{
		colorOperatePara.layout = 4;
	}
	AfxBeginThread(threadDrawColor, this);
}
BOOL CExRabbitDlg::getIDofCurrentPos(int &cid){
	CPoint myPoint = getWinMouseAxis();
	point xy(myPoint.x-170, myPoint.y+110 - height);
	int enumCountPerRow[5] = {12, 15, 20, 25, 30};
	int enumBlockSize[5] = {25, 20, 15, 12, 10};
	int countPerRow = enumCountPerRow[colorOperatePara.layout];
	int blockSize = enumBlockSize[colorOperatePara.layout];
	cid = xy.Y /blockSize * countPerRow + xy.X / blockSize;
	return xy.X >= 0 && xy.Y >= 0 && xy.X < 300 && xy.Y < 100;
}
UINT CExRabbitDlg::threadDrawColor(PVOID para){
	CExRabbitDlg *dlg = (CExRabbitDlg *)para;
	CHECK_VALID_RETURN(!dlg->drawingColor);
	dlg->drawingColor = 1;
	structColorOperatePara *COP = &(dlg->colorOperatePara);
	int i,j;
	int enumCountPerRow[5] = {12, 15, 20, 25, 30};
	int enumMaxRow[5] = {4, 5, 6, 8, 10};
	int enumBlockSize[5] = {25, 20, 15, 12, 10};
	int countPerRow = enumCountPerRow[COP->layout];
	int maxRow = enumMaxRow[COP->layout];
	int blockSize = enumBlockSize[COP->layout];
	color clr;
	//����ɫ��
	matrix canvas(102, 302);
	matrix block1(blockSize-2, blockSize-2);
	matrix block2(blockSize-2, blockSize-2);
	canvas.fill(color(0xFF,
		((dlg->profile.mainColor >> 0) & 0xFF)/2, 
		((dlg->profile.mainColor >> 8) & 0xFF)/2, 
		((dlg->profile.mainColor >> 16) & 0xFF)/2
	));
	int index = 0;
	for(j=0;j<maxRow;j++){
		for(i=0;i<countPerRow;i++){
			if(index < dlg->cl.size()){
				clr = dlg->cl[index];
				block1.filledLattice(point(0,0),point(blockSize-3, blockSize-3), color(0xFF,0XFF,0XFF,0XFF),color(0xFF,0xCC,0xCC,0xCC),6);
				block2.fill(clr);
				block1.putFore(block2);
				if(COP->isChosen[index]){
					block1.rectangle(point(0,0),point(blockSize-3, blockSize-3), color(0xFF,0XFF,0XFF,0XFF));
					block1.rectangle(point(1,1),point(blockSize-4, blockSize-4), color(0xFF,0X77,0X77,0X77));
				}
				canvas.putFore(block1, LAY, point(blockSize*i+2, blockSize*j+2));
				index++;
			}else if(index == dlg->cl.size()){
				block1.fill(color(0xff,0xff,0x99,0xff));
				block1.filledRectangle(point((blockSize-2)/5, (blockSize-2)*2/5), point((blockSize-2)*4/5, (blockSize-2)*3/5), color(0xff,0xff,0xff,0x99));
				block1.filledRectangle(point((blockSize-2)*2/5, (blockSize-2)/5), point((blockSize-2)*3/5, (blockSize-2)*4/5), color(0xff,0xff,0xff,0x99));
				canvas.putFore(block1, LAY, point(blockSize*i+2, blockSize*j+2));
				index++;
			}else if(index == dlg->cl.size()+1){
				block1.fill(color(0xff,0x99,0xcc,0xff));
				block1.filledRectangle(point((blockSize-2)/5, (blockSize-2)*2/5), point((blockSize-2)*4/5, (blockSize-2)*3/5), color(0xff,0xff,0xff,0x99));
				canvas.putFore(block1, LAY, point(blockSize*i+2, blockSize*j+2));
				index++;
			}else{
				block1.filledLattice(point(0,0),point(blockSize-3, blockSize-3), color(0xFF,0XFF,0XFF,0XFF),color(0xFF,0xCC,0xCC,0xCC),2);
				canvas.putFore(block1, LAY, point(blockSize*i+2, blockSize*j+2));
			}
		}
	}
	CImage img;
	img.Create(302,102,32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for(i=0;i<302;i++){
		for(j=0;j<102;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	CDC *pDC = dlg->GetDC();
	img.Draw(pDC->m_hDC,169,dlg->height-111);
	img.Destroy();
	dlg->ReleaseDC(pDC);
	//����ǰ��ɫ
	matrix base1(35, 40);
	matrix base2(35, 40);
	base1.filledLattice(point(0,0),point(39, 34), color(0xFF,0XFF,0XFF,0XFF),color(0xFF,0xCC,0xCC,0xCC),6);
	base2.fill(COP->current >= dlg->cl.size() ? color(0,0,0,0):dlg->cl[COP->current]);
	base2.line(point(0,0),point(0, 34), color(0xFF,0XCC,0XCC,0XCC));
	base2.line(point(1,1),point(1, 33), color(0xFF,0XCC,0XCC,0XCC));
	base2.line(point(2,2),point(2, 32), color(0xFF,0x77,0x77,0x77));
	base2.line(point(0,0),point(39, 0), color(0xFF,0XEE,0XEE,0XEE));
	base2.line(point(1,1),point(38, 1), color(0xFF,0XEE,0XEE,0XEE));
	base2.line(point(2,2),point(37, 2), color(0xFF,0x33,0x33,0x33));
	base2.line(point(39,34),point(0, 34), color(0xFF,0x33,0x33,0x33));
	base2.line(point(38,33),point(1, 33), color(0xFF,0x33,0x33,0x33));
	base2.line(point(37,32),point(2, 32), color(0xFF,0XEE,0XEE,0XEE));
	base2.line(point(39,34),point(39, 0), color(0xFF,0x77,0x77,0x77));
	base2.line(point(38,33),point(38, 1), color(0xFF,0x77,0x77,0x77));
	base2.line(point(37,32),point(37, 2), color(0xFF,0XCC,0XCC,0XCC));
	base1.putFore(base2);
	img.Create(40,35,32);
	pst = (UCHAR*)img.GetBits();
	pit = img.GetPitch();
	for(i=0;i<40;i++){
		for(j=0;j<35;j++){
			*(pst + pit*j + 4*i + 0) = base1[j][i].B;
			*(pst + pit*j + 4*i + 1) = base1[j][i].G;
			*(pst + pit*j + 4*i + 2) = base1[j][i].R;
		}
	}
	pDC = dlg->GetDC();
	img.Draw(pDC->m_hDC,480,dlg->height-70);
	img.Destroy();
	dlg->ReleaseDC(pDC);
	dlg->drawingColor = 0;
	return 0;
}

void CExRabbitDlg::updateInfo(){
	//����������Ϣ��
	////////////////////////////////
	//NPK 
	CString cstr;
	cstr = L"�ļ�����"+GetTail(fileNPKname)+L"\r\n";
	cstr += L"��С��"+NumToCStr(no.getSize())+L"�ֽ�\r\n";
	cstr += L"��Ŀ����"+NumToCStr(no.count);
	cstr += (crtIMGid  == -1) ? L"" : ( L"/"  + NumToCStr(crtIMGid));
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(cstr);

	cstr = saveAlert ? L"IMG״̬���ѱ䶯\r\n" : L"IMG״̬��δ�䶯\r\n";
	cstr += L"�汾:"+NumToCStr(io.version)+L"\r\n";
	cstr += L"֡��:"+NumToCStr(io.indexCount);
	cstr += (crtPICid == -1) ? L"\r\n": (  L"/" + NumToCStr(crtPICid)+L"\r\n");
	switch(io.version){
	case V4:
		cstr += L"��ɫ����ɫ��:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V5:
		cstr += L"������:"+NumToCStr(io.TEXcontent.size());
		cstr += (crtTEXid == -1) ? L"\r\n": (  L"/" + NumToCStr(crtTEXid)+L"\r\n");
		cstr += L"��ɫ����ɫ��:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V6:
		cstr += L"��ɫ�巽����:"+NumToCStr(io.paletteData.getCount());
		if(GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel() >= 0){
			cstr += L"/"+NumToCStr(io.paletteData[GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()].size())+L"\r\n";
		}
		break;
	}
	GET_CTRL(CEdit, IDC_EDIT_IMGINFO)->SetWindowText(cstr);
}
BOOL CExRabbitDlg::getMouseTrueAxis(point &pt){ 
	CPoint myPoint = getWinMouseAxis();
	point xy(myPoint.x-530, myPoint.y-10);
	pt = (xy - drawPara.basePoint)/drawPara.zoomRate;
	return xy.X>0 && xy.Y>0;
}

BOOL CExRabbitDlg::getMouseAxis(point &pt){
	CPoint myPoint = getWinMouseAxis();
	point xy(myPoint.x-530, myPoint.y-10);
	pt = xy;
	return myPoint.x >= 530 && myPoint.y >= 10 && myPoint.x <= width - 10 && myPoint.y <= height - 40;
}
CPoint CExRabbitDlg::getWinMouseAxis(){
	CPoint myPoint;
    GetCursorPos(&myPoint); //���λ��
	ScreenToClient(&myPoint);
	return myPoint;
}
void CExRabbitDlg::updateCursorInfo(){
	//����ָ����������ɫ
	CPoint myPoint  = getWinMouseAxis();   
	int x = myPoint.x-530;
	int y = myPoint.y-10;
	CString str1;
	GET_CTRL(CEdit, IDC_EDIT_INFO6)->SetWindowText(L"x:"+NumToCStr((x-drawPara.basePoint.X)/drawPara.zoomRate)+L" y:"+NumToCStr((y-drawPara.basePoint.Y)/drawPara.zoomRate));
	CDC *pDC = this->GetDC();
	COLORREF clrr = GetPixel(pDC->m_hDC, myPoint.x, myPoint.y);
	str1.Format(L"#%02X%02X%02X",GetRValue(clrr),GetGValue(clrr),GetBValue(clrr));
	GET_CTRL(CEdit, IDC_EDIT_INFO7)->SetWindowText(str1);

	CImage img;
	int i,j;
	img.Create(barPart2/3, barHeight, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();

	for(i=0;i<barPart2/3;i++){
		for(j=0;j<barHeight;j++){
			if(i==0||j==0){
				*(pst + pit*j + 4*i + 0) = 0xB0;
				*(pst + pit*j + 4*i + 1) = 0xB0;
				*(pst + pit*j + 4*i + 2) = 0xB0;
			}else if(i==barPart2/3-1||j==barHeight-1){
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
	img.Draw(pDC->m_hDC,530+barPart1+barPart2/3,height-10-barHeight);
	img.Destroy();
	ReleaseDC(pDC);
}

//////////////////////////////////////////////////
/**************����ť�¼�************************/
//////////////////////////////////////////////////
void CExRabbitDlg::OnBnClickedButtonMenu()
{
	// TODO: ����˵���ť
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ��  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}

void CExRabbitDlg::OnBnClickedButtonMenu2()
{
	// TODO: ���⹤��
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_TOOL);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ��  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}

void CExRabbitDlg::OnBnClickedButtonMenu3()
{
	// TODO: IMG�Ķ�
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(1);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ��  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}

//////////////////////////////////////////////////
/**************��ͷ�¼�**************************/
//////////////////////////////////////////////////
void CExRabbitDlg::OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ������IMG�б�
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	playing = 0;
	////////////////////////////
	//�л�IMGʱ��ʾ����
	if(saveAlert){
		switch(MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������",L"��ʾ��",MB_YESNOCANCEL)){
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
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(row);
	if(row>=0){
		crtIMGid = row;
		fndIMGid = row;
		if(no.IMGgetVersion(row) == V1 && IDYES == MessageBox(L"���IMG��V1������Ҫת��ΪV2����", L"��ʾ��", MB_YESNO)){
			KoishiExpand::IMGobjectV1 io1;
			stream s;
			no.extract(row, s);
			if(!io1.load(s)){
				MessageBox(L"ת��ʧ������", L"��ʾ��");
				return;
			}
			if(!io1.make(io)){
				MessageBox(L"ת��ʧ������", L"��ʾ��");
				return;
			}
			no.IMGreplace(row, io);
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(row, 0, LVIF_IMAGE, NULL, getIconIMG(V2),0,0,0);
		}else{
			io.release();
			no.IMGextract(row, io);
		}
		fileIMGname = StrToCStr(no.entry[row].comment);
		switchIMGver(io.version);
		updatePIClist();
		updateTEXlist();
		updateColorTable();
	}
	updateInfo();
	canvasOperatePara.oldMatrixEnable = false;
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �Ҽ����IMG�б�����˵�
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListImg(pNMHDR, pResult);
	/////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //���λ��
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_IMAGE);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}

void CExRabbitDlg::OnNMClickListTex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �����������б�
	playing = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CHECK_VALID(pNMListView->iItem >= 0);
	crtTEXid = pNMListView->iItem;
	updateInfo();
	draw(true);
	canvasOperatePara.oldMatrixEnable = false;
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListTex(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �Ҽ���������б�����˵�
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListTex(pNMHDR, pResult);
	//////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //���λ��  
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_TEXTURE);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}

void CExRabbitDlg::OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ������֡�б�
	playing = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CHECK_VALID(pNMListView->iItem >= 0);
	crtPICid = pNMListView->iItem;
	updateInfo();
	draw();
	canvasOperatePara.oldMatrixEnable = false;
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �Ҽ����֡�б�����˵�
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListPic(pNMHDR, pResult);
	if(crtIMGid == -1){
		MessageBox(L"��û��ѡ��IMG��������",L"��ʾ��");
		return;
	}
	//////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //���λ��  
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_PICTURE);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}

void CExRabbitDlg::OnCbnSelchangeComboPro(){
	// TODO: ���ĵ�ɫ��
	CHECK_VALID(io.version == V6);
	int curSel = GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel();
	CHECK_VALID(curSel >= 0);
	cl = io.paletteData[curSel];
	updateColorTable();
	draw();
}

void CExRabbitDlg::draw(bool isDDS){
	//����
	drawPara.texture = isDDS;
	AfxBeginThread(threadDraw, (LPVOID)this);
}

UINT CExRabbitDlg::lazyThread(PVOID para){
	//��ʱ�߳�
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	while(dlg->m_hWnd){
		Sleep(10);
		if(dlg->lazyTime>0)
			dlg->lazyTime--;
	}
	return 0;
}

void CExRabbitDlg::OnOK()
{
	// TODO: ���ܰ��س�
	MessageBox(L"�����س�����",L"��ʾ��");
}

void CExRabbitDlg::OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	playing = 0;
	int row = GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//�޹ذ�������Ӧ
		*pResult = 0;
		return;
	}
	if(pLVKeyDow->wVKey == VK_UP){
		if(row>0){
			row --;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(pLVKeyDow->wVKey == VK_DOWN){
		if(row<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount()-1){
			row ++;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(saveAlert){
		switch(MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������",L"��ʾ��",MB_YESNO)){
		case IDYES:
			OnModify01();
			break;
		case IDNO:
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
		fileIMGname = StrToCStr(no.entry[row].comment);
		switchIMGver(io.version);
		updatePIClist();
		updateTEXlist();
		updateColorTable();
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
	playing = 0;
	int row = GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//�޹ذ�������Ӧ
		*pResult = 0;
		return;
	}
	if(pLVKeyDow->wVKey == VK_UP){
		if(row>0){
			row --;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(pLVKeyDow->wVKey == VK_DOWN){
		if(row<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount()-1){
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

void CExRabbitDlg::OnLvnKeydownListTex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	playing = 0;
	int row = GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//�޹ذ�������Ӧ
		*pResult = 0;
		return;
	}
	if(pLVKeyDow->wVKey == VK_UP){
		if(row>0){
			row --;
		}else{
			*pResult = 0;
			return;
		}
	}
	if(pLVKeyDow->wVKey == VK_DOWN){
		if(row<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount()-1){
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
	// TODO: �ⲿ�ļ�����
	WCHAR szPath[MAX_PATH] = L"" ;
	UINT nChars=::DragQueryFile(hDropInfo,0,szPath ,MAX_PATH);    
	CString fileName(szPath,nChars) ; 
	CString path;
	//str fn;
	CString fmt = fileName.Right(4);
	if(fmt == L".NPK" || fmt == L".npk"){
		if(1){
			if(KoishiExpand::authorLock::checkLock(CStrToStr(fileName), "") == 0){
				ModalLockInput dlg;
				dlg.fileCheckName = fileName;
				if(IDCANCEL == dlg.DoModal())
					return;
			}
			no.release();
			//CStrToStr(fileName, fn);
			if(no.loadFile(CStrToStr(fileName))){
				//MessageBox(L"��ȡ�������");
			}else{
				MessageBox(L"��ȡʧ������");
				return;
			}
			fileNPKname = fileName;
			updateIMGlist();
			if(no.count>0){
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
	}
	if(fmt == L".IMG" || fmt == L".img"){
		UINT fileCount = ::DragQueryFile(hDropInfo, -1, NULL, NULL);
		if(fileCount == 1){
			if(1){
				//CStrToStr(fileName, fn);
				IMGobject ioTemp(CStrToStr(fileName));
				path = Slashing(GetTail(fileName));
				//CStrToStr(path, fn);
				if(no.IMGpush(ioTemp, CStrToStr(path))){
					GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount(), GetTail(path),getIconIMG(ioTemp.version));
				}else{
					MessageBox(L"����ʧ������");
				}
				ioTemp.release();
				updateInfo();
			}
		}else if(fileCount > 1){
			if(1){
				for(int i=0;i<fileCount;i++){
					WCHAR szPath[MAX_PATH] = L"" ;
					nChars=::DragQueryFile(hDropInfo,i,szPath ,MAX_PATH);    
					fileName = CString(szPath,nChars) ; 
					//str fn;
					fmt = fileName.Right(4);
					//CStrToStr(fileName, fn);
					if((fmt == L".IMG" || fmt == L".img")){
						IMGobject ioTemp;
						if(ioTemp.loadFile(CStrToStr(fileName))){
							path = Slashing(GetTail(fileName));
							no.IMGpush(ioTemp, CStrToStr(path));
							GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount(), GetTail(path),getIconIMG(ioTemp.version));
						}
						ioTemp.release();
					}
					updateInfo();
				}
			}
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
}


void CExRabbitDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//�������
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
}


void CExRabbitDlg::OnSize(UINT nType, int cx, int cy)
{
	// TODO: �������
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
}


void CExRabbitDlg::OnStnClickedLogo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime t = CTime::GetTickCount();
	CString wk[7] = {L"������",L"����һ",L"���ڶ�",L"������",L"������",L"������",L"������"};
	CString hr[24] = {L"��ҹ",L"��ҹ",L"��ҹ",L"��ҹ",L"�賿",L"�賿",L"�賿",
	L"����",L"����",L"����",L"����",L"����",L"����",L"����",L"����",L"����",L"����",
	L"����",L"���",L"���",L"���",L"���",L"���",L"���"};
	CString s1 = t.Format(L"������%Y��%m��%d�գ�");
	CString s4 = t.Format(L"%Iʱ%M������");
	CString s2 = wk[t.GetDayOfWeek()%7]+L"��";
	CString s3 = hr[t.GetHour()%24];
	MessageBox(s1+s2+s3+s4,L"��ʾ����");
}

int CExRabbitDlg::getIconIMG(IMGversion iv){
	if(iv == VUDEF)
		return 0;
	if(iv == VUKNOWN)
		return 2;
	if(iv == VSOUND)
		return 3;
	if(iv <= 6){
		TRACE(NumToCStr(iv));
		return iv + 3;
	}
	return 0;
}
int CExRabbitDlg::getIconPIC(colorFormat cf){
	int iconList[21] = {0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 3, 2, 1, 4, 6, 7, 8};
	if(io.version == V4 || io.version == V5 ||io.version == V6){
		if(cf == ARGB1555){
			return 5;
		}
	}
	return iconList[cf%21];
}
void CExRabbitDlg::getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected){
	selected.clear();
	int k;
	switch(targetPara){
	case SINGLE_SELECT:
		//��ѡ
		selected.push_back(highLine);
		break;
	case MULTI_SELECT:
		//��ѡ
		for(k=0;k<listCtrl->GetItemCount();k++)
			if(listCtrl->GetCheck(k))
				selected.push_back(k);
		break;
	default:
		//ȫѡ
		for(k=0;k<listCtrl->GetItemCount();k++)
			selected.push_back(k);
		break;
	}
}

//////////////////////////////////////////////
/***********���水ť�����¼�*****************/
//////////////////////////////////////////////


void CExRabbitDlg::OnBnClickedButtonPalette()
{
	// TODO: �����ɫ����
	bool selected = false;
	for(int i = 0;i<cl.size();i++){
		if(colorOperatePara.isChosen[i]){
			selected = true;
			break;
		}
	}
	if(!selected){
		MessageBox(L"ûѡ����ɫ����", L"��ʾ��");
		return;
	}
	CAdjustColorDlg acd;
	acd.oldCl = cl;
	if(io.version == V2){
		CHECK_VALID(crtPICid>=0);
		io.PICextract(crtPICid, acd.oldV2matrix);
	}
	acd.DoModal();
}
void CExRabbitDlg::OnBnClickedButtonImgsearch()
{
	// TODO: ��ѯ·����
	CString str1,str2;
	GET_CTRL(CEdit, IDC_EDIT_IMGSEARCH)->GetWindowText(str1);
	int i;
	for (i = fndIMGid;i<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount();i++){
		str2 = GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndIMGid = i;
			int nItem = GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetTopIndex(); 
			CRect rc;
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndIMGid - nItem)*rc.Height());
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->Scroll(sz);
			return;
		}
	}
	for (i = 0;i<fndIMGid;i++){
		str2 = GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndIMGid = i;
			int nItem = GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetTopIndex(); 
			CRect rc;
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndIMGid - nItem)*rc.Height());
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->Scroll(sz);
			return;
		}
	}
	MessageBox(L"û���ҵ�·����������"+str1+"����IMG����",L"��ʾ��");
}
//////////////////////////////////////////////
/***********Main�˵������¼�*****************/
//////////////////////////////////////////////
void CExRabbitDlg::OnMain01()
{
	// TODO: �½�
	MOVEW(dNewFile);
	dNewFile.OnBnClickedCheck1();
	dNewFile.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnMain02()
{
	// TODO: ��
	CString defExt = _T("��Դ�ļ�(*.NPK,*.IMG)|*.NPK;*.IMG");
	CString extFilter = _T("��Դ�ļ�(*.NPK,*.IMG)|*.NPK;*.IMG|NPK�ļ�(*.NPK)|*.NPK|IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		fmt = fileName.Right(1);
		CStrToStr(fileName, fn);
		if(fmt == L"K" || fmt == L"k"){
			if(KoishiExpand::authorLock::checkLock(CStrToStr(fileName), "") == 0){
				ModalLockInput dlg;
				dlg.fileCheckName = fileName;
				if(IDCANCEL == dlg.DoModal())
					return;
			}
			no.release();
			if(no.loadFile(fn)){
			}else{
				MessageBox(L"��ȡʧ������");
				return;
			}
			fileNPKname = fileName;
			saveAlert = false;
			updateIMGlist();
			if(no.count>0){
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
		if(fmt == L"G" || fmt == L"g"){
			io.release();
			if(io.loadFile(fn)){
			}else{
				KoishiExpand::IMGobjectV1 io1;
				if(!io1.load(fn)){
					MessageBox(L"��ȡʧ������", L"��ʾ��");
					return;
				}
				if(!io1.make(io)){
					MessageBox(L"��ȡʧ������", L"��ʾ��");
					return;
				}
				if(IDNO== MessageBox(L"��IMGΪ�ɰ汾(V1)����Ҫ����ת��ΪV2���ܴ򿪡�Ҫ�������", L"��ʾ��", MB_YESNO)){
					return;
				}
			}
			no.release();
			no.create();
			fileIMGname = fileName;
			fileNPKname = L"newNPK.npk";
			saveAlert = false;
			fileName = GetTail(fileName);
			CStrToStr(Slashing(fileName), fn);
			no.IMGpush(io, fn);
			switchIMGver(io.version);
			updateIMGlist();
			updatePIClist();
			updateTEXlist();
			updateColorTable();
			updateInfo();
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(0);
			crtIMGid = 0;
		}
	}
}
void CExRabbitDlg::OnMain03()
{
	// TODO: ����
	if(saveAlert){
		if(IDYES == MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������",L"��ʾ��",MB_YESNO)){
			OnModify01();
		}
	}
	str fn;
	CString fileName;
	fileName = fileNPKname;
	CStrToStr(fileName, fn);
	if(no.saveFile(fn)){
		MessageBox(_T("NPK�����������"),L"��ʾ��");
	}else{
		MessageBox(_T("NPK����ʧ������"),L"��ʾ��");
	}
}
void CExRabbitDlg::OnMain04()
{
	// TODO: ���Ϊ
	if(saveAlert){
		if(IDYES == MessageBox(L"���IMG�Ѿ�����Ķ�������Ҫ��������",L"��ʾ��",MB_YESNO))
			OnModify01();
	}
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
	CFileDialog dlg(false, defExt, GetTail(fileNPKname), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if(no.saveFile(fn)){
			MessageBox(_T("NPK�����������"),L"��ʾ��");
			fileNPKname = fileName;
			fmt = fileName.Right(1);
			updateInfo();
		}else{
			MessageBox(_T("NPK����ʧ������"),L"��ʾ��");
		}
	}
}
void CExRabbitDlg::OnMain05(){
	// TODO: ����
	ModalPreference dlg;
	dlg.modifiedProfile = profile;
	if(IDOK == dlg.DoModal()){
		profile = dlg.modifiedProfile;
		MessageBox(L"������ñ��޸���������������Ч��",L"��ʾ��");
	}
}
void CExRabbitDlg::OnMain06()
{
	// TODO: ����
	CDialogAbout dlg;
	dlg.DoModal();
}
void CExRabbitDlg::OnMain07()
{
	// TODO: WIKI
	ShellExecute(NULL, L"open",L"https://github.com/Lucky-Koishi/KoishiExAPI/wiki/%E6%81%8B%E6%81%8B%E3%81%AEEx%E5%85%94%E5%AD%90%E7%89%88", NULL, NULL, SW_MAXIMIZE); 
}
void CExRabbitDlg::OnMain08()
{
	// TODO: �ر�
	CDialogEx::OnCancel();
}

//////////////////////////////////////////////
/********IMG�޸�ȷ�ϲ˵������¼�*************/
//////////////////////////////////////////////


void CExRabbitDlg::OnModify01()
{
	// TODO: ȷ�ϵ�ǰ�޸�
	CHECK_VALID(crtIMGid>=0);
	no.IMGreplace(crtIMGid, io);
	MessageBox(L"IMG�ѱ����������",L"��ʾ����");
	saveAlert = false;
	updateInfo();
	updateIMGlist();
	updatePIClist();
	updateTEXlist();
	updateColorTable();
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(crtIMGid);
}
void CExRabbitDlg::OnModify02()
{
	// TODO: ȷ�ϵ�ǰ�޸Ĳ���IMG���Ϊ
	CHECK_VALID(crtIMGid>=0);
	OnModify01();
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(false, defExt, Underlining(StrToCStr(no.entry[crtIMGid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName1;
	if(dlg.DoModal() == IDOK){
		fileName1 = dlg.GetPathName();
		if(no.extract(crtIMGid, CStrToStr(fileName1))){
			MessageBox(_T("�����������"),L"��ʾ��");
		}else{
			MessageBox(_T("����ʧ������"),L"��ʾ��");
		}
	}
}

UINT CExRabbitDlg::threadMix(PVOID para){
	CExRabbitDlg *dlg =  (CExRabbitDlg *)para;
	NPKobject *nop = &(dlg->no);
	int i, k;
	int imgCount = 0;
	int totalCount = GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount();
	std::vector<int> mixLayer;						//��ѡͼ��
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG), 0, MULTI_SELECT, mixLayer);
	imgCount = mixLayer.size();
	if(imgCount == 0)
		return 0;
	dlg->bar.show(100);
	dlg->bar.setInfo(L"׼��ƴ��������", 0);
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
	point ptLT, ptRB, ptLTtemp, ptRBtemp;//���Ͻ����½ǵĵ㣬���½ǵĵ������ͼƬ��
	std::vector<int> mLeft, mTop, mRight, mBottom;
	dlg->bar.setMax(maxFrameCount);
	for(k=0;k<maxFrameCount;k++){
		dlg->bar.setInfo(L"����ƴ�ϵ�"+NumToCStr(k+1)+L"֡��(��"+NumToCStr(maxFrameCount)+L"֡)����", k);
		mLeft.clear();
		mTop.clear();
		mRight.clear();
		mBottom.clear();
		for(i=0;i<imgCount;i++){
			if(ioList[i].PICgetInfo(k, pi)){
				int k1 = k;
				if(pi.format == LINK){
					k1 = ioList[i].linkFind(k);
				}
				ioList[i].PICgetInfo(k1, pi);
				CHECK_VALID_CONTINUE(pi.picSize.area() > 1);
				mLeft.push_back(pi.basePt.X);
				mTop.push_back(pi.basePt.Y);
				mRight.push_back(pi.basePt.X+pi.picSize.W-1);
				mBottom.push_back(pi.basePt.Y+pi.picSize.H-1);
			}
		}
		//2.5��������������IMG��֡ȫ�յ�����
		if(mLeft.size() == 0){
			pi.basePt = point(0,0);
			pi.comp = COMP_NONE;
			pi.format = ARGB8888;
			pi.dataSize = 4;
			pi.picSize = size(1,1);
			pi.frmSize = size(1,1);
			s.allocate(4);
			s.pushDWord(0);
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
		ptLT = point(tLeft, tTop);
		ptRB = point(tRight, tBottom);
		matf.create(tBottom-tTop+1, tRight-tLeft+1);
		for(i=0;i<imgCount;i++){
			if(ioList[i].PICgetInfo(k, pi)){
				int k1 = k;
				if(pi.format == LINK){
					k1 = ioList[i].linkFind(k);
				}
				ioList[i].PICgetInfo(k1, pi);
				CHECK_VALID_CONTINUE(pi.picSize.area() > 1);
				ioList[i].PICextract(k1, mat);
				mat2.create(
					pi.basePt.Y-ptLT.Y+pi.picSize.H+10,
					pi.basePt.X-ptLT.X+pi.picSize.W+10
				);
				mat2.putFore(mat);
				mat2.moveHonz(pi.basePt.X-ptLT.X);
				mat2.moveVert(pi.basePt.Y-ptLT.Y);
				matf.putFore(mat2);
				mat.destory();
				mat2.destory();
			}
		}
		newIO.PICpreprocess(matf, s, pi);
		pi.basePt = ptLT;
		newIO.PICpush(pi, s);
		matf.destory();
		s.release();
	}
	nop->IMGpush(newIO,"mixed.img");
	GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(imgCount, L"mixed.img",dlg->getIconIMG(newIO.version));
	dlg->bar.hide();
	dlg->updateInfo();
	dlg->updateIMGlist();
	delete[] ioList;
	return 0;
}

UINT CExRabbitDlg::threadDraw(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if(dlg->drawing)
		return 0;
	//TRACE("draw\n");
	dlg->drawing = 1;
	structDrawPara SDP = dlg->drawPara;
	int picRow = dlg->crtPICid;
	int texRow = dlg->crtTEXid;
	int clrRow = dlg->colorOperatePara.current;/*GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_CLR)->GetSelectionMark()*/
	int cbpro = GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel();
	int i,j,k,m,n,tx,ty;
	int canw = dlg->width - 540;
	int canh = dlg->height - 50;
	int clrBlockSize = 10;
	int clct,cp;

	color clrNoCanvas = color(0xff, GetRValue(dlg->profile.canvasColor0), GetGValue(dlg->profile.canvasColor0), GetBValue(dlg->profile.canvasColor0));
	color clrCanvasBound = color(0xff, GetRValue(dlg->profile.canvasColor1), GetGValue(dlg->profile.canvasColor1), GetBValue(dlg->profile.canvasColor1));
	color clrCanvasBack1 = color(0xff, GetRValue(dlg->profile.canvasColor2), GetGValue(dlg->profile.canvasColor2), GetBValue(dlg->profile.canvasColor2));
	color clrCanvasBack2 = color(0xff, GetRValue(dlg->profile.canvasColor1), GetGValue(dlg->profile.canvasColor1), GetBValue(dlg->profile.canvasColor1));
	color clrEnclosingBound = color(0x33, 0x77, 0x77, 0x77);
	color clrZeroAxis = color(0xff, 0xff, 0x00, 0x00);
	color clrZeroNoAxis = color(0xff, 0x77, 0x00, 0x00);
	color clrCutMark = color(0xff, 0xff, 0xff, 0x00);
	IMGobject *io = &(dlg->io);
	PICinfo po;
	TEXinfo di;
	CImage img;
	matrix canvas; //����
	matrix content;	//����
	matrix tempMat;	//�м����
	color clr;
	if(io->version == V5 || io->version == V4)
		cbpro = 0;
	//����
	canvas.create(canh,canw);
	canvas.fill(clrNoCanvas);

	if(KoishiImageTool::loadPNG(content, CStrToStr(dlg->profile.getSupportPath() + L"back.png"))){
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
		canvas.putFore(content, LAY, point(canw - content.getWidth(), canh - content.getHeight()));
	}
	content.destory();
	//������ɫ��

	if(SDP.showPalette && (io->version == V4 || io->version == V5 || io->version == V6)){
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
		//ѡ������ɫ�͵�ɫ����
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
		//��������б�
		if(texRow < 0){
			dlg->drawing = 0;
			return 0;
		}
		io->TEXgetInfo(texRow, di);
		io->TEXextract(texRow, tempMat);		//��ȡ����
		tempMat.zoom(SDP.zoomRate);					//���ź�ľ���
		KoishiExpand::KoishiMarkTool::MatrixPSstyle(tempMat, content, clrCanvasBound, clrCanvasBack1,clrCanvasBack2);
		tempMat.destory();
		canvas.putFore(content, SDP.mixMode, SDP.basePoint);
	}else if(SDP.entireTextureMode){
		//ȫ֡��ʾ
		KoishiExpand::exhibit kex;
		kex.create(canvas.getWidth(), canvas.getHeight());
		dlg->bar.show(io->indexCount-1-picRow);
		for(i = picRow;i<io->indexCount;i++){
			dlg->bar.setInfo(L"��ȡ��"+NumToCStr(i)+L"֡������", i-picRow);
			io->PICextract(i, content, cbpro);
			kex.putMatrix(content);
			content.destory();
		}
		dlg->bar.hide();
		canvas.putFore(kex.canvas);
		dlg->drawPara.entireTextureMode = false;
	}else{
		//����ģʽ
		//����������
		if(SDP.showAxis){
			if(SDP.basePoint.X < 0){
				canvas.line(point(0,0),point(0,canh-1), clrZeroNoAxis);
			}else if(SDP.basePoint.X >= canw){
				canvas.line(point(canw-1,0),point(canw-1,canh-1), clrZeroNoAxis);
			}else{
				canvas.line(point(SDP.basePoint.X,0),point(SDP.basePoint.X,canh-1), clrZeroAxis);
			}
			if(SDP.basePoint.Y < 0){
				canvas.line(point(0,0),point(canw-1,0), clrZeroNoAxis);
			}else if(SDP.basePoint.Y >= canh){
				canvas.line(point(0,canh-1),point(canw-1,canh-1), clrZeroNoAxis);
			}else{
				canvas.line(point(0,SDP.basePoint.Y),point(canw-1,SDP.basePoint.Y), clrZeroAxis);
			}
		}
		//����IMG����
		if(SDP.showBound){
			long x1,x2,y1,y2;
			if(io->PICgetTotalBound(x1,x2,y1,y2)){
				x1 = SDP.basePoint.X+x1*SDP.zoomRate;
				x2 = SDP.basePoint.X+x2*SDP.zoomRate;
				y1 = SDP.basePoint.Y+(y1+1)*SDP.zoomRate-1;
				y2 = SDP.basePoint.Y+(y2+1)*SDP.zoomRate-1;
				canvas.rectangle(point(x1,y1),point(x2,y2),clrEnclosingBound);
				canvas.rectangle(point(x1+1,y1+1),point(x2-1,y2-1),clrEnclosingBound);
			}
		}
		//IMG�Ա�ģʽ
		if(SDP.compareMode && picRow >= 0){
			int picRowComp = picRow;
			IMGobject *ioComp = &dlg->ioComp;
			if(picRowComp < ioComp->indexSize){
				//���ioTemp�д��ڴ�֡
				ioComp->PICgetInfo(picRowComp, po);
				if(po.format == LINK)
					picRowComp = ioComp->linkFind(picRowComp);
				ioComp->PICgetInfo(picRowComp, po);
				ioComp->PICextract(picRowComp, content, 0);
				content.zoom(SDP.zoomRate);
				for(i = 0;i<content.getElemCount();i++){
					color clr = content.getElem(i);
					clr.alpha /= 2;
					content.setElem(i, clr);
				}
				canvas.putFore(content, SDP.mixMode, po.basePt*SDP.zoomRate+SDP.basePoint);
				content.destory();	//���õģ�Ҫ��
			}
		}
		//����ͼ
		if(picRow >= 0){
			io->PICgetInfo(picRow, po);
			if(po.format == LINK)
				picRow = io->linkFind(picRow);
			io->PICgetInfo(picRow, po);
			io->PICextract(picRow, tempMat, (long)cbpro);
			//��ˢԤ��
			if(dlg->canvasOperatePara.canvasOperating){
				switch(dlg->canvasOperatePara.canvasOperation){
				case CANVAS_BRUSH:
					for(int i = 0;i<dlg->canvasOperatePara.drawnPoint.size();i++){
						tempMat.setElem((dlg->canvasOperatePara.drawnPoint[i] - po.basePt).Y,(dlg->canvasOperatePara.drawnPoint[i] - po.basePt).X,dlg->cl[clrRow]);
					}
					break;
				case CANVAS_ERASE:
					for(int i = 0;i<dlg->canvasOperatePara.drawnPoint.size();i++){
						tempMat.setElem((dlg->canvasOperatePara.drawnPoint[i] - po.basePt).Y,(dlg->canvasOperatePara.drawnPoint[i] - po.basePt).X,color(0,0,0,0));
					}
					break;
				case CANVAS_DRAWLINE:
					tempMat.line(dlg->canvasOperatePara.startPoint-po.basePt, dlg->canvasOperatePara.movePoint-po.basePt,dlg->cl[clrRow]);
					break;
				case CANVAS_DRAWRECT:
					tempMat.rectangle(dlg->canvasOperatePara.startPoint-po.basePt, dlg->canvasOperatePara.movePoint-po.basePt,dlg->cl[clrRow]);
					break;
				}
			}
			//����ģʽ
			if(SDP.indexMode && (io->version == V4 || io->version == V5 || io->version == V6)){
				for(k=0;k<dlg->cl.size();k++){
					//TODO������content���滻Ԫ�ء���ѡ�����滻Ϊ��ɫ
					int temp = 255*k/dlg->cl.size();
					if(dlg->colorOperatePara.isChosen[k]){
						tempMat.replace(dlg->cl[k], color(0xFF, 0, 0, 0xff));
					}else{
						tempMat.replace(dlg->cl[k], color(0xFF, temp, temp, temp));
					}
				}
			}
			//���ŵ���Ļ
			tempMat.zoom(SDP.zoomRate);
			//�ǶԱ�ģʽ & ����ģʽ �����ƻ���
			if(SDP.compareMode || dlg->playing == 1 || !SDP.showCanvas){
				content = tempMat;
			}else{
				KoishiExpand::KoishiMarkTool::MatrixPSstyle(tempMat, content, clrCanvasBound, clrCanvasBack1,clrCanvasBack2);
			}
			tempMat.destory();
			//�ƶ�����
			canvas.putFore(content, SDP.mixMode, po.basePt*SDP.zoomRate+SDP.basePoint);	
		}
	}
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
	content.destory();
	dlg->ReleaseDC(pDC);
	dlg->drawing = 0;
	canvas.destory();
	return 0;
}

UINT CExRabbitDlg::playThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	int localFrame = 0;
	while(true){
		if(dlg->playing){
			std::vector<int> frameList;
			dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), 0, MULTI_SELECT, frameList);
			if(frameList.size() == 0){
				dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), 0, ALL_SELECT, frameList);
			}
			for(localFrame = 0;localFrame<frameList.size();localFrame++){
				int row = frameList[localFrame];
				if(row >= dlg->io.indexCount)
					break;
				GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemState(row-1, 0, LVIS_FOCUSED | LVIS_SELECTED);
				GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemState(row, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);
				GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetSelectionMark(row);
				dlg->crtPICid = row;
				dlg->updateInfo();
				dlg->draw();
				
				Sleep(100);
				if(dlg->playing == 0){
					break;
				}
			}
		}
		Sleep(10);
	}
	return 0;
}

/////////////////////////////////////////////////////////////
//��������ť
//////////////////////////////////////////////////////////////
void CExRabbitDlg::OnBnClickedToolButton1(){
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_DRAW);  
    pPopup = menu.GetSubMenu(0); 
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ��
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}
void CExRabbitDlg::OnBnClickedToolButton2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	drawPara.indexMode = !drawPara.indexMode;
	changeToolButtonStatus();
	draw();
}
void CExRabbitDlg::OnBnClickedToolButton3(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	drawPara.entireTextureMode = !drawPara.entireTextureMode;
	canvasOperatePara.canvasOperation = CANVAS_SHOW;
	canvasOperatePara.oldMatrixEnable = false;
	draw();
}
void CExRabbitDlg::OnBnClickedToolButton4(){
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_DRAW);  
    pPopup = menu.GetSubMenu(1);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ��  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}
void CExRabbitDlg::OnBnClickedToolButton5(){
	//TODO: ����
	canvasOperatePara.canvasOperation = CANVAS_SHOW;
	canvasOperatePara.oldMatrixEnable = false;
	playing = !playing;
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton6(){
	// TODO: �϶�
	canvasOperatePara.canvasOperation = CANVAS_DRAG;
	canvasOperatePara.oldMatrixEnable = false;
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton7()
{	//TODO: ����
	canvasOperatePara.canvasOperation = CANVAS_ZOOM;
	canvasOperatePara.oldMatrixEnable = false;
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton8(){
	// TODO: �ƶ�
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_MOVE;
	canvasOperatePara.oldMatrixEnable = false;
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton9(){
	// TODO: ����
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	if(io.version == V5){
		MessageBox(L"���ܶ�V5�汾��IMG��ͼ��������/��������",L"��ʾ��");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_CUT;
	canvasOperatePara.oldMatrixEnable = false;
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton10(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	if(io.version == V5){
		MessageBox(L"���ܶ�V5�汾��IMG��ͼ���л�ˢ����",L"��ʾ��");
		return;
	}
	if(canvasOperatePara.canvasOperation != CANVAS_BRUSH){
		canvasOperatePara.canvasOperation = CANVAS_BRUSH;
		canvasOperatePara.oldMatrixEnable = false;
	}else{
		TinySetBrush dlg;
		dlg.size = canvasOperatePara.brushSize;
		dlg.shape = canvasOperatePara.brushShape;
		if(dlg.DoModal() == IDOK){
			canvasOperatePara.brushSize = dlg.size;
			canvasOperatePara.brushShape = dlg.shape;
		}
	}
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton11(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	if(io.version == V5){
		MessageBox(L"���ܶ�V5�汾��IMG��ͼ���л���������",L"��ʾ��");
		return;
	}
	canvasOperatePara.oldMatrixEnable = false;
	canvasOperatePara.canvasOperation = CANVAS_DRAWLINE;
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton12(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	if(io.version == V5){
		MessageBox(L"���ܶ�V5�汾��IMG��ͼ���л���������",L"��ʾ��");
		return;
	}
	canvasOperatePara.oldMatrixEnable = false;
	canvasOperatePara.canvasOperation = CANVAS_DRAWRECT;
	changeToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton13(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	if(io.version == V5){
		MessageBox(L"���ܶ�V5�汾��IMG��ͼ���в�������",L"��ʾ��");
		return;
	}
	if(canvasOperatePara.canvasOperation != CANVAS_ERASE){
		canvasOperatePara.oldMatrixEnable = false;
		canvasOperatePara.canvasOperation = CANVAS_ERASE;
	}else{
		TinySetBrush dlg;
		dlg.size = canvasOperatePara.brushSize;
		dlg.shape = canvasOperatePara.brushShape;
		if(dlg.DoModal() == IDOK){
			canvasOperatePara.brushSize = dlg.size;
			canvasOperatePara.brushShape = dlg.shape;
		}
	}
	changeToolButtonStatus();
}
void CExRabbitDlg::changeToolButtonStatus(){
	GET_CTRL(CButton, IDC_TOOL_BUTTON2)->SetBitmap(1[drawPara.indexMode?m_buttonPicX:m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON4)->SetBitmap(3[drawPara.compareMode?m_buttonPicX:m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON5)->SetBitmap(4[playing?m_buttonPicX:m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON6)->SetBitmap(5[canvasOperatePara.canvasOperation == CANVAS_DRAG ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON7)->SetBitmap(6[canvasOperatePara.canvasOperation == CANVAS_ZOOM ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON8)->SetBitmap(7[canvasOperatePara.canvasOperation == CANVAS_MOVE ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON9)->SetBitmap(8[canvasOperatePara.canvasOperation == CANVAS_CUT ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON10)->SetBitmap(9[canvasOperatePara.canvasOperation == CANVAS_BRUSH ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON11)->SetBitmap(10[canvasOperatePara.canvasOperation == CANVAS_DRAWLINE ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON12)->SetBitmap(11[canvasOperatePara.canvasOperation == CANVAS_DRAWRECT ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON13)->SetBitmap(12[canvasOperatePara.canvasOperation == CANVAS_ERASE ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON14)->SetBitmap(13[canvasOperatePara.canvasOperation == CANVAS_PICK ? m_buttonPicX : m_buttonPic]);
	GET_CTRL(CButton, IDC_TOOL_BUTTON15)->SetBitmap(14[canvasOperatePara.canvasOperation == CANVAS_MARK ? m_buttonPicX : m_buttonPic]);
}
void CExRabbitDlg::OnBnClickedToolButton14(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	canvasOperatePara.oldMatrixEnable = false;
	canvasOperatePara.canvasOperation = CANVAS_PICK;
	changeToolButtonStatus();
}


void CExRabbitDlg::OnBnClickedToolButton15(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	if(io.version == V5){
		MessageBox(L"���ܶ�V5�汾��IMG��ͼ���д������",L"��ʾ��");
		return;
	}
	canvasOperatePara.oldMatrixEnable = false;
	canvasOperatePara.canvasOperation = CANVAS_MARK;
	changeToolButtonStatus();
}

void CExRabbitDlg::OnRButtonDown(UINT nFlags, CPoint pt){
	// TODO: �Ҽ�����
	CDialogEx::OnRButtonDown(nFlags, pt);
	point mousePt;
	int selectColorID;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_RIGHT_PRESS, mousePt);
	}
	if(getIDofCurrentPos(selectColorID)){
		OnMouseEventColor(CANVAS_MOUSE_RIGHT_PRESS, selectColorID);
	}
}
void CExRabbitDlg::OnRButtonUp(UINT nFlags, CPoint pt){
	// TODO: �Ҽ��ͷ�
	CDialogEx::OnRButtonUp(nFlags, pt);
}
void CExRabbitDlg::OnLButtonDown(UINT nFlags, CPoint pt){
	// TODO: ����������
	CDialogEx::OnLButtonDown(nFlags, pt);
	point mousePt;
	int selectColorID;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_LEFT_PRESS, mousePt);
	}
	if(getIDofCurrentPos(selectColorID)){
		OnMouseEventColor(CANVAS_MOUSE_LEFT_PRESS, selectColorID);
	}
}
void CExRabbitDlg::OnLButtonUp(UINT nFlags, CPoint pt){
	// TODO: �������ͷ�
	CDialogEx::OnLButtonUp(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_LEFT_RELEASE, mousePt);
	}
}
void CExRabbitDlg::OnLButtonDblClk(UINT nFlags, CPoint point){
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnLButtonDblClk(nFlags, point);
	int selectColorID;
	if(getIDofCurrentPos(selectColorID)){
		OnMouseEventColor(CANVAS_MOUSE_LEFT_DOUBLE, selectColorID);
	}
}

void CExRabbitDlg::OnMouseMove(UINT nFlags, CPoint pt){
	// TODO: �ƶ����
	CDialogEx::OnMouseMove(nFlags, pt);
	updateCursorInfo();
	point mousePt;
	if(getMouseAxis(mousePt)){
		//��Ӧ��������
		OnMouseEventCanvas(canvasOperatePara.canvasOperating ? CANVAS_MOUSE_LEFT_DRAG : CANVAS_MOUSE_MOVE, mousePt);
	}
}
void CExRabbitDlg::OnMouseEventColor(enumCanvasMouseOperation mouseOperation, int selectColorID){
	CHECK_VALID(selectColorID >= 0);
	CHECK_VALID(selectColorID <= cl.size()+1);
	switch(mouseOperation){
	case CANVAS_MOUSE_LEFT_PRESS:
		//������ɫ��
		//�����Ӻţ������ɫ��
		//�������ţ������˵���
		//������ɫ��ѡ����ɫ
		if(selectColorID == cl.size()){
			COLORREF sclr = 0;
			CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
			if(cdlg.DoModal() == IDOK){
				sclr = cdlg.GetColor();
				if(io.version == V4 || io.version == V5 || io.version == V6){
					io.CLRpush(color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)), GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
					cl.push_back(color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)));
				}else{
					colorOperatePara.v2Color.push_back(color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)));
					cl.push_back(color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)));
				}
			}
		}else if(selectColorID == cl.size()+1){
			CMenu menu, *pPopup;  
			menu.LoadMenu(IDR_MENU_COLOR);  
			pPopup = menu.GetSubMenu(1);  
			CPoint myPoint; 
			ClientToScreen(&myPoint);  
			GetCursorPos(&myPoint); //���λ��  
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
		}else{
			colorOperatePara.current = selectColorID;
			updateInfo();
			updateColorTable();
			draw();
		}
		break;
	case CANVAS_MOUSE_LEFT_DOUBLE:
		//˫����ɫ��
		//˫����ɫ������ɫ�����޸�
		if(selectColorID < cl.size()){
			COLORREF sclr = RGB(cl[selectColorID].R, cl[selectColorID].G, cl[selectColorID].B);
			CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
			if(cdlg.DoModal() == IDOK){
				sclr = cdlg.GetColor();
				if(io.version == V4 || io.version == V5 || io.version == V6){
					io.CLRreplace(selectColorID, color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)), GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
					cl[selectColorID] = color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr));
				}else{
					colorOperatePara.v2Color.push_back(color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)));
					cl[selectColorID] = color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr));
				}
			}
		}
		updateInfo();
		updateColorTable();
		draw();
		break;
	case CANVAS_MOUSE_RIGHT_PRESS:
		//�Ҽ�������ɫ��
		//�Ҽ�������ɫ��ѡ����ɫ + �����Ҽ��˵�
		if(selectColorID < cl.size()){
			colorOperatePara.isChosen[selectColorID] = !colorOperatePara.isChosen[selectColorID];
			updateInfo();
			updateColorTable();
			draw();
		}
		break;
	}
}
void CExRabbitDlg::OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt){
	CHECK_VALID(crtPICid >= 0);
	point truePt;
	switch(canvasOperatePara.canvasOperation){
	case CANVAS_SHOW:
		//��ʾ
		break;
	case CANVAS_DRAG:
		//�϶�����
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 1;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.oldBasePoint = drawPara.basePoint;	//��¼ԭ����ԭ������
			canvasOperatePara.startPoint = mousePt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 1;
			drawPara.basePoint = canvasOperatePara.oldBasePoint + mousePt - canvasOperatePara.startPoint;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			drawPara.basePoint = mousePt - io.PICcontent[crtPICid].basePt * drawPara.zoomRate;
			draw();
			break;
		}
		break;
	case CANVAS_MOVE:
		//�ƶ�����
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.oldBasePoint = io.PICcontent[crtPICid].basePt;
			canvasOperatePara.startPoint = mousePt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 2;
			canvasOperatePara.endPoint = canvasOperatePara.oldBasePoint + (mousePt - canvasOperatePara.startPoint)/drawPara.zoomRate;
			io.PICsetInfoPara(crtPICid, 1, &canvasOperatePara.endPoint);
			updatePICterm(crtPICid);
			saveAlert = true;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			canvasOperatePara.endPoint= mousePt - drawPara.basePoint/drawPara.zoomRate;
			io.PICsetInfoPara(crtPICid, 1, &canvasOperatePara.endPoint);
			updatePICterm(crtPICid);
			saveAlert = true;
			draw();
			break;
		}
		break;
	case CANVAS_ZOOM:
		//����
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 3;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			if(drawPara.zoom > 9)
				return;
			drawPara.zoom ++;
			drawPara.oldZoomRate = drawPara.zoomRate;
			drawPara.zoomRate = 1;
			if(drawPara.zoom>=0){
				drawPara.zoomRate = drawPara.zoom+1;
			}else{
				drawPara.zoomRate = 1.00/(-drawPara.zoom+1);
			}
			drawPara.basePoint = mousePt - (mousePt - drawPara.basePoint)/drawPara.oldZoomRate*drawPara.zoomRate;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 3;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(drawPara.zoom < -9)
				return;
			drawPara.zoom --;
			drawPara.oldZoomRate = drawPara.zoomRate;
			drawPara.zoomRate = 1;
			if(drawPara.zoom>=0){
				drawPara.zoomRate = drawPara.zoom+1;
			}else{
				drawPara.zoomRate = 1.00/(-drawPara.zoom+1);
			}
			drawPara.basePoint = mousePt - (mousePt - drawPara.basePoint)/drawPara.oldZoomRate*drawPara.zoomRate;
			draw();
			break;
		}
		break;
	case CANVAS_CUT:
		//����
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			if(1){
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				CHECK_VALID(pi.format != LINK);
				CHECK_VALID(pi.picSize.area() > 1);
				getMouseTrueAxis(truePt);
				long left = pi.basePt.X;
				long right = pi.basePt.X + pi.picSize.W - 1;
				long top = pi.basePt.Y;
				long bottom = pi.basePt.Y + pi.picSize.H - 1;
				
				bool nearLeft = truePt.X > left - 5 && truePt.X < left + 5 && truePt.Y > top - 5  && truePt.Y < bottom + 5 ;
				bool nearRight = truePt.X > right - 5 && truePt.X < right + 5 && truePt.Y > top - 5  && truePt.Y < bottom + 5 ;
				bool nearTop = truePt.X > left - 5 && truePt.X < right + 5 && truePt.Y > top - 5  && truePt.Y < top + 5 ;
				bool nearBottom = truePt.X > left - 5 && truePt.X < right + 5 && truePt.Y > bottom - 5  && truePt.Y < bottom + 5 ;
				if(nearLeft){
					if(nearTop){
						canvasOperatePara.currentCursor = 6;
						canvasOperatePara.canvasPara = CANVAS_TOPLEFT;
					}else if(nearBottom){
						canvasOperatePara.currentCursor = 7;
						canvasOperatePara.canvasPara = CANVAS_BOTTOMLEFT;
					}else{
						canvasOperatePara.currentCursor = 4;
						canvasOperatePara.canvasPara = CANVAS_LEFT;
					}
				}else if(nearRight){
					if(nearTop){
						canvasOperatePara.currentCursor = 7;
						canvasOperatePara.canvasPara = CANVAS_TOPRIGHT;
					}else if(nearBottom){
						canvasOperatePara.currentCursor = 6;
						canvasOperatePara.canvasPara = CANVAS_BOTTOMRIGHT;
					}else{
						canvasOperatePara.currentCursor = 4;
						canvasOperatePara.canvasPara = CANVAS_RIGHT;
					}
				}else if(nearTop){
					canvasOperatePara.currentCursor = 5;
					canvasOperatePara.canvasPara = CANVAS_TOP;
				}else if(nearBottom){
					canvasOperatePara.currentCursor = 5;
					canvasOperatePara.canvasPara = CANVAS_BOTTOM;
				}else{
					canvasOperatePara.currentCursor = 0;
					canvasOperatePara.canvasPara = CANVAS_DEFAULT;
				}
			}
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			getMouseTrueAxis(truePt);
			canvasOperatePara.startPoint = truePt;
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = false;
				getMouseTrueAxis(truePt);
				matrix matOld, matNew;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				int x1old = pi.basePt.X;
				int y1old = pi.basePt.Y;
				int x2old = pi.basePt.X+pi.picSize.W-1;
				int y2old = pi.basePt.Y+pi.picSize.H-1;	
				int x1new = pi.basePt.X;
				int y1new = pi.basePt.Y;
				int x2new = pi.basePt.X+pi.picSize.W-1;
				int y2new = pi.basePt.Y+pi.picSize.H-1;	
				switch(canvasOperatePara.canvasPara){
				case CANVAS_TOP:
					y1new = truePt.Y;
					break;
				case CANVAS_TOPRIGHT:
					y1new = truePt.Y;
					x2new = truePt.X;
					break;
				case CANVAS_RIGHT:
					x2new = truePt.X;
					break;
				case CANVAS_BOTTOMRIGHT:
					y2new = truePt.Y;
					x2new = truePt.X;
					break;
				case CANVAS_BOTTOM:
					y2new = truePt.Y;
					break;
				case CANVAS_BOTTOMLEFT:
					x1new = truePt.X;
					y2new = truePt.Y;
					break;
				case CANVAS_LEFT:
					x1new = truePt.X;
					break;
				case CANVAS_TOPLEFT:
					x1new = truePt.X;
					y1new = truePt.Y;
					break;
				default:
					return;
				}
				if(x1new > x2old - 1){
					x1new = x2old - 1;
				}
				if(x2new < x1old + 1){
					x2new = x1old + 1;
				}
				if(y1new > y2old - 1){
					y1new = y2old - 1;
				}
				if(y2new < y1old + 1){
					y2new = y1old + 1;
				}
				if(io.version == V2){
					io.PICextract(crtPICid, matOld);
				}else{
					io.PICextractIndexMatrix(crtPICid, matOld);
				}
				int x1 = min(x1old,x1new);
				int x2 = max(x2old,x2new);
				int y1 = min(y1old,y1new);
				int y2 = max(y2old,y2new);

				matNew.create(y2-y1+1,x2-x1+1);
				matNew.putFore(matOld, LAY, point(x1old-x1, y1old-y1));
				matNew.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
				if(io.version == V2){
					io.PICpreprocess(matNew, s, pi, pi.format);
				}else{
					io.PICpreprocessIndexMatrix(matNew, s, pi);
				}
				pi.basePt = point(x1new, y1new);
				io.PICreplace(crtPICid, pi, s);
				updatePICterm(crtPICid);
				s.release();
				matNew.destory();
				matOld.destory();
				draw();
				saveAlert = true;
			}
			break;
		}
		break;
	case CANVAS_PICK:
		//ȡɫ
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 10;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			if(true){
				CPoint myPoint  = getWinMouseAxis();   
				CDC *pDC = this->GetDC();
				COLORREF clrr = GetPixel(pDC->m_hDC, myPoint.x, myPoint.y);
				this->ReleaseDC(pDC);
				color clrMous = color(0xFF, GetRValue(clrr), GetGValue(clrr), GetBValue(clrr));
				int ID;
				bool found = false;
				for(int i = 0;i<cl.size();i++){
					if(cl[i] == clrMous){
						ID = i;
						found = true;
						break;
					}
				}
				if(found){
					colorOperatePara.current = ID;
					colorOperatePara.isChosen[ID] = true;
				}else{
					if(io.version == V4 || io.version == V5 || io.version == V6){
						//��������ͼδȡɫ���ֲ��䡤ʲôҲ����
					}else{
						if(colorOperatePara.v2Color.size() < 256){
							colorOperatePara.v2Color.push_back(clrMous);
							cl.push_back(clrMous);
							colorOperatePara.current = cl.size() - 1;
							colorOperatePara.isChosen[cl.size() - 1] = true;
						}else{
							MessageBox(L"��ɫ�������Ѵﵽ�������",L"��ʾ��");
						}
					}
				}
				draw();
				updateColorTable();
			}
			break;
		}
		break;
	case CANVAS_BRUSH:
		//��ˢ
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 8;
			getMouseTrueAxis(truePt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(truePt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(truePt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 8;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(truePt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = false;
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					for(int i = 0;i<canvasOperatePara.drawnPoint.size();i++){
						mat.setElem((canvasOperatePara.drawnPoint[i] - pi.basePt).Y,(canvasOperatePara.drawnPoint[i] - pi.basePt).X,cl[colorOperatePara.current]);
					}
					io.PICpreprocess(mat, s, pi, pi.format);
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					for(int i = 0;i<canvasOperatePara.drawnPoint.size();i++){
						mat.setElem((canvasOperatePara.drawnPoint[i] - pi.basePt).Y,(canvasOperatePara.drawnPoint[i] - pi.basePt).X,color(colorOperatePara.current,0,0,0));
					}
					io.PICpreprocessIndexMatrix(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					io.PICpreprocessIndexMatrix(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_ERASE:
		//����
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 9;
			getMouseTrueAxis(truePt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(truePt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(truePt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 9;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(truePt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = false;
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					for(int i = 0;i<canvasOperatePara.drawnPoint.size();i++){
						mat.setElem((canvasOperatePara.drawnPoint[i] - pi.basePt).Y,(canvasOperatePara.drawnPoint[i] - pi.basePt).X,color(0,0,0,0));
					}
					io.PICpreprocess(mat, s, pi, pi.format);
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					uchar emptyID = 0;
					for(int i = 0;i<cl.size();i++){
						if(cl[i].alpha == 0){
							emptyID = i;
						}
					}
					for(int i = 0;i<canvasOperatePara.drawnPoint.size();i++){
						mat.setElem((canvasOperatePara.drawnPoint[i] - pi.basePt).Y,(canvasOperatePara.drawnPoint[i] - pi.basePt).X,color(emptyID,0,0,0));
					}
					io.PICpreprocessIndexMatrix(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					io.PICpreprocessIndexMatrix(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_DRAWLINE:
		//��ֱ��
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			canvasOperatePara.startPoint = truePt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 2;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			canvasOperatePara.movePoint = truePt;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = false;
				getMouseTrueAxis(truePt);
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.line(canvasOperatePara.startPoint-pi.basePt, truePt-pi.basePt, cl[colorOperatePara.current]);
					io.PICpreprocess(mat, s, pi, pi.format);
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.line(canvasOperatePara.startPoint-pi.basePt, truePt-pi.basePt, color(colorOperatePara.current,0,0,0));
					io.PICpreprocessIndexMatrix(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					io.PICpreprocessIndexMatrix(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_DRAWRECT:
		//������
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			canvasOperatePara.startPoint = truePt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 2;
			canvasOperatePara.oldMatrixEnable = true;
			getMouseTrueAxis(truePt);
			canvasOperatePara.movePoint = truePt;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = false;
				getMouseTrueAxis(truePt);
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.rectangle(canvasOperatePara.startPoint-pi.basePt, truePt-pi.basePt, cl[colorOperatePara.current]);
					io.PICpreprocess(mat, s, pi, pi.format);
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.rectangle(canvasOperatePara.startPoint-pi.basePt, truePt-pi.basePt, color(colorOperatePara.current,0,0,0));
					io.PICpreprocessIndexMatrix(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					io.PICpreprocessIndexMatrix(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_MARK:
		//���
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			{
				getMouseTrueAxis(truePt);
				TinyAddMark dlg;
				if(IDOK == dlg.DoModal()){
					canvasOperatePara.oldMatrixEnable = true;
					str markText = dlg.text;
					matrix mat;
					stream s;
					PICinfo pi;
					if(io.version == V2){
						canvasOperatePara.oldMatrix.destory();
						io.PICextract(crtPICid, canvasOperatePara.oldMatrix);
						io.PICgetInfo(crtPICid, pi);
						KoishiExpand::KoishiMarkTool::MatrixMarking(canvasOperatePara.oldMatrix, mat, markText, truePt - pi.basePt, cl[colorOperatePara.current]);
						if(truePt.X<pi.basePt.X){
							pi.basePt.X = truePt.X;
						}
						if(truePt.Y<pi.basePt.Y){
							pi.basePt.Y = truePt.Y;
						}
						io.PICpreprocess(mat, s, pi, pi.format);
					}else{
						canvasOperatePara.oldMatrix.destory();
						io.PICextractIndexMatrix(crtPICid, canvasOperatePara.oldMatrix);
						io.PICgetInfo(crtPICid, pi);
						KoishiExpand::KoishiMarkTool::MatrixMarking(canvasOperatePara.oldMatrix, mat, markText, truePt - pi.basePt, color(colorOperatePara.current,0,0,0));
						if(truePt.X<pi.basePt.X){
							pi.basePt.X = truePt.X;
						}
						if(truePt.Y<pi.basePt.Y){
							pi.basePt.Y = truePt.Y;
						}
						io.PICpreprocessIndexMatrix(mat, s, pi);
					}
					io.PICreplace(crtPICid, pi, s);
					updatePICterm(crtPICid);
					s.release();
					mat.destory();
					draw();
				}
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				matrix mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexMatrix(crtPICid, mat);
					io.PICpreprocessIndexMatrix(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				saveAlert = true;
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	}
}
BOOL CExRabbitDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message){
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	point mousePt;
	//TRACE(NumToCStr(canvasOperatePara.currentCursor)+L"\n");
	BOOL isOK = getMouseAxis(mousePt);
	if(isOK){
		switch(canvasOperatePara.currentCursor){
		case 0:
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			break;
		case 1:
			SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR2)));
			break;
		case 2:
			SetCursor(LoadCursor(NULL, IDC_CROSS));
			break;
		case 3:
			SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1)));
			break;
		case 4:
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			break;
		case 5:
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			break;
		case 6:
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
			break;
		case 7:
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
			break;
		case 8:
			SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR3)));
			break;
		case 9:
			SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR4)));
			break;
		case 10:
			SetCursor(LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR5)));
			break;
		default:
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			break;
		}
		return TRUE;
	}
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

void CExRabbitDlg::OnMenuColorTableChooseAll(){
	// TODO: �ڴ���������������
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = true;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableChooseNone(){
	// TODO: �ڴ���������������
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = false;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableInverseChoose(){
	// TODO: �ڴ���������������
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = !colorOperatePara.isChosen[i];
	}
	updateColorTable();
}

void CExRabbitDlg::OnMenuColorTableChooseFamiliar(){
	// TODO: �ڴ���������������
	for(int i = 0;i<cl.size();i++){
		colorHSV HSV1, HSV2;
		cl[colorOperatePara.current].getHSV(HSV1);
		cl[i].getHSV(HSV2);
		colorOperatePara.isChosen[i] = (abs(HSV1.H - HSV2.H) <= colorOperatePara.tolerance);
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableDeleteOne(){
	// TODO: �ڴ���������������
	bool selected = false;
	for(int i = 0;i<cl.size();i++){
		if(colorOperatePara.isChosen[i]){
			selected = true;
			break;
		}
	}
	if(!selected){
		MessageBox(L"ûѡ����ɫ�������Ҽ�����ѡ��һЩ��ɫ����ɾ������");
		return;
	}
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼɾ����ɫ����ɫ�ᵼ����ɫ���ң�ȷ������",L"��ʾ��",MB_YESNO)){
			for(int i = 0;i<cl.size();i++){
				int id = cl.size() - 1 - i;
				if(colorOperatePara.isChosen[id]){
					io.CLRremove(id,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
					cl.erase(cl.begin() + id);
				}
			}
			saveAlert = true;
			draw();
		}
	}else{
		for(int i = 0;i<cl.size();i++){
			int id = cl.size() - 1 - i;
			if(colorOperatePara.isChosen[id]){
				colorOperatePara.v2Color.erase(colorOperatePara.v2Color.begin() + id);
				cl.erase(cl.begin() + id);
			}
		}
	}
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = false;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableDeleteAll(){
	// TODO: �ڴ���������������
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼɾ����ɫ����ɫ�ᵼ����ɫ���ң�ȷ������",L"��ʾ��",MB_YESNO)){
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			cl.clear();
			saveAlert = true;
			draw();
		}
	}else{
		colorOperatePara.v2Color.clear();
		cl.clear();
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableImport(){
	colorList newCl;
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act|CID��ɫ��(*.cid)|*.cid||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(fileName.Right(1) == L"t" || fileName.Right(1) == L"T" ){
			if(!palette::loadACT(CStrToStr(fileName), newCl)){
				MessageBox(L"δʶ��ĵ�ɫ���ļ�����",L"��ʾ��");
				return;
			}
		}
		if(fileName.Right(1) == L"D" || fileName.Right(1) == L"d" ){
			if(!palette::loadCID(CStrToStr(fileName), newCl)){
				MessageBox(L"δʶ��ĵ�ɫ���ļ�����",L"��ʾ��");
				return;
			}
		}
		if(io.version == V4 || io.version == V5 || io.version == V6){
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			cl.clear();
			for(int i = 0;i<newCl.size();i++){
				io.CLRpush(newCl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
				cl.push_back(newCl[i]);
			}
			saveAlert = true;
			draw();
		}else{
			colorOperatePara.v2Color.clear();
			cl.clear();
			for(int i = 0;i<newCl.size();i++){
				colorOperatePara.v2Color.push_back(newCl[i]);
				cl.push_back(newCl[i]);
			}
		}
		updateColorTable();
	}
}


void CExRabbitDlg::OnMenuColorTableExport(){
	// TODO: �ڴ���������������
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act|CID��ɫ��(*.cid)|*.cid||");
	CFileDialog dlg(false, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(fileName.Right(1) == L"t" || fileName.Right(1) == L"T" ){
			palette::makeACT(CStrToStr(fileName), cl);
			MessageBox(L"�����������",L"��ʾ��");
		}
		if(fileName.Right(1) == L"D" || fileName.Right(1) == L"d" ){
			palette::makeCID(CStrToStr(fileName), cl);
			MessageBox(L"�����������",L"��ʾ��");
		}
	}
}


void CExRabbitDlg::OnMenuColorPaletteNew(){
	if(io.version != V6){
		MessageBox(L"ֻ��V6�汾���ܽ�����ɫ����������",L"��ʾ��");
		return;
	}
	io.CLRnewPalette();
	long lastPaletteID = io.paletteData.getCount()-1;
	GET_CTRL(CComboBox, IDC_COMBO_PRO)->AddString(NumToCStr(lastPaletteID));
	GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(lastPaletteID);
	cl.clear();
	draw();
	updateInfo();
	updateColorTable();
	saveAlert = true;
}


void CExRabbitDlg::OnMenuColorPaletteCopy(){
	if(io.version != V6){
		MessageBox(L"ֻ��V6�汾���ܽ�����ɫ����������",L"��ʾ��");
		return;
	}
	colorList newCl = cl;
	io.CLRnewPalette();
	long lastPaletteID = io.paletteData.getCount()-1;
	GET_CTRL(CComboBox, IDC_COMBO_PRO)->AddString(NumToCStr(io.paletteData.getCount()-1));
	GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(io.paletteData.getCount()-1);
	cl.clear();
	for(int i = 0;i<newCl.size();i++){
		io.CLRpush(newCl[i], lastPaletteID);
		cl.push_back(newCl[i]);
	}
	draw();
	updateInfo();
	updateColorTable();
	saveAlert = true;
}


void CExRabbitDlg::OnMenuColorPaletteImport(){
	if(io.version != V6){
		MessageBox(L"ֻ��V6�汾���ܽ�����ɫ����������",L"��ʾ��");
		return;
	}
	colorList newCl;
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act|CID��ɫ��(*.cid)|*.cid||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(fileName.Right(1) == L"t" || fileName.Right(1) == L"T" ){
			if(!palette::loadACT(CStrToStr(fileName), newCl)){
				MessageBox(L"δʶ��ĵ�ɫ���ļ�����",L"��ʾ��");
				return;
			}
		}
		if(fileName.Right(1) == L"D" || fileName.Right(1) == L"d" ){
			if(!palette::loadCID(CStrToStr(fileName), newCl)){
				MessageBox(L"δʶ��ĵ�ɫ���ļ�����",L"��ʾ��");
				return;
			}
		}
		io.CLRnewPalette();
		long lastPaletteID = io.paletteData.getCount()-1;
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->AddString(NumToCStr(io.paletteData.getCount()-1));
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(io.paletteData.getCount()-1);
		cl.clear();
		for(int i = 0;i<newCl.size();i++){
			io.CLRpush(newCl[i], lastPaletteID);
			cl.push_back(newCl[i]);
		}
		draw();
		updateInfo();
		updateColorTable();
		saveAlert = true;
	}
}


void CExRabbitDlg::OnMenuColorPaletteDelete(){
	if(io.version != V6){
		MessageBox(L"ֻ��V6�汾���ܽ�����ɫ����������",L"��ʾ��");
		return;
	}
	long paletteID = GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel();
	if(paletteID >= 0){
		io.CLRdeletePalette(paletteID);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ResetContent();
		for(int i = 0;i<io.paletteData.getCount();i++)
			GET_CTRL(CComboBox, IDC_COMBO_PRO)->AddString(NumToCStr(i));
		if(paletteID >= io.paletteData.getCount()){
			GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(io.paletteData.getCount() - 1);
		}else{
			GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(paletteID);
		}
		draw();
		updateInfo();
		updateColorTable();
		saveAlert = true;
	}
}

void CExRabbitDlg::OnMenuPictureChooseAll(){
	// TODO: ȫѡ
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetCheck(i, TRUE);
}

void CExRabbitDlg::OnMenuPictureChooseInverse(){
	//��ѡ
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetCheck(i, 1-GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetCheck(i));
}

void CExRabbitDlg::OnMenuPictureChooseHighline(){
	//ѡ�����
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetCheck(i,TRUE);
}


void CExRabbitDlg::OnMenuPictureInsert(){
	// TODO: �ڴ���������������
	ModalInsertPicture dlg;
	dlg.in.firstInsert = false;
	dlg.in.version = io.version;
	dlg.in.maxPICcount = io.indexCount;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.PICgetInfo(crtPICid, dlg.in.pi);
	if(IDOK == dlg.DoModal()){
		ParaPictureInsert = dlg.out;
		AfxBeginThread(ThreadPictureInsert, this);
	}
}
void CExRabbitDlg::OnMenuPictureInsert2(){
	// TODO: �ڴ���������������
	ModalInsertPicture dlg;
	dlg.in.firstInsert = true;
	dlg.in.version = io.version;
	dlg.in.maxPICcount = io.indexCount;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.PICgetInfo(crtPICid, dlg.in.pi);
	if(IDOK == dlg.DoModal()){
		ParaPictureInsert = dlg.out;
		AfxBeginThread(ThreadPictureInsert, this);
	}
}
void CExRabbitDlg::OnMenuPictureInsertPatch2(){
	// TODO: �ڴ���������������
	OnMenuPictureInsertPatch();
}
UINT CExRabbitDlg::ThreadPictureInsert(void*context){
	CExRabbitDlg*dlg = (CExRabbitDlg*)context;
	ModalInsertPicture::OUTPUT *para = &dlg->ParaPictureInsert;
	dlg->processing = 1;
	int insertPos;
	std::vector<int> replacePos;
	matrix mPic;
	stream sPic;
	PICinfo pInfo;
	DDSobject DDSHelper;
	//ȷ������Ŀ��
	switch(para->operate){
	case 1:
		replacePos.push_back(dlg->crtPICid);
		break;
	case 2:
		dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), 0, MULTI_SELECT, replacePos);
		break;
	case 3:
		insertPos = dlg->crtPICid;
		break;
	case 4:
		insertPos = dlg->crtPICid + 1;
		break;
	case 5:
		insertPos = dlg->io.indexCount;
		break;
	}
	if(dlg->crtPICid < 0){
		para->operate = 5;
		insertPos = 0;
	}
	//�ж�����
	switch(para->type){
	case 1:
		//ָ��֡�ж�
		pInfo.format = LINK;
		pInfo.linkTo = para->para[0];
		break;
	case 3:
		//��������
		pInfo.format = dlg->io.TEXcontent[para->para[5]].format;
		pInfo.comp = COMP_ZLIB_DUAL;
		pInfo.dataSize = 0;
		pInfo.basePt = point(para->para[1], para->para[2]);
		pInfo.picSize = size(para->para[8] - para->para[6], para->para[9] - para->para[7]);
		pInfo.frmSize = size(para->para[3], para->para[4]);
		pInfo.TEXusing = para->para[5];
		pInfo.TEXpointLT = point(para->para[6], para->para[7]);
		pInfo.TEXpointRB = point(para->para[8], para->para[9]);
		break;
	case 2:
		//��ȡ��Դ
		switch(para->inputFormat){
		case 0:
			mPic.create(1, 1);
			mPic.fill(0);
			break;
		case 1:
			KoishiImageTool::loadPNG(mPic, CStrToStr(para->fileName));
			break;
		case 2:
			DDSHelper.loadFile(CStrToStr(para->fileName));
			DDSHelper.uncompress(mPic);
			break;
		}
		//����ʽ
		colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
		if(!dlg->io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para->outputFormat])){
			dlg->MessageBox(L"��Ӹ�ͼƬʱ�����˴���",L"����");
			dlg->processing = 0;
			return 0;
		}
		mPic.destory();
		break;
	}
	//����
	if(replacePos.size() > 0){
		dlg->bar.show(replacePos.size()-1);
		for(int i = 0;i<replacePos.size();i++){
			dlg->bar.setInfo(L"���ڲ����"+NumToCStr(i)+L"֡������",i);
			dlg->bar.setMax(replacePos.size()-1);
			dlg->io.PICreplace(replacePos[i], pInfo, sPic);
			dlg->updatePICterm(replacePos[i]);
		}
		dlg->bar.hide();
	}else{
		dlg->io.PICinsert(insertPos, pInfo, sPic);
		dlg->updatePIClist();
	}
	sPic.release();
	mPic.destory();
	dlg->saveAlert = true;
	dlg->updateInfo();
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}

void CExRabbitDlg::OnMenuPictureInsertPatch(){
	// TODO: �ڴ���������������
	ModalInsertPicturePatch dlg;
	dlg.in.version = io.version;
	dlg.in.maxPICcount = io.indexCount;
	if(IDOK == dlg.DoModal()){
		ParaPictureInsertPatch = dlg.out;
		AfxBeginThread(ThreadPictureInsertPatch, this);
	}
}

UINT CExRabbitDlg::ThreadPictureInsertPatch(void*context){
	CExRabbitDlg*dlg = (CExRabbitDlg*)context;
	ModalInsertPicturePatch::OUTPUT *para = &dlg->ParaPictureInsertPatch;
	dlg->processing = 1;
	matrix mPic;
	stream sPic;
	PICinfo pInfo;
	if(para->inputFormat == 1){
		//��PNG����
		dlg->bar.show(para->PNGcount-1);
		for(int i = 0;i<para->PNGcount;i++){
			dlg->bar.setInfo(L"�����"+NumToCStr(i)+L"֡������",i);
			CString fileName = para->filePath + NumToCStr(i) + L".PNG";
			if(i<dlg->io.indexCount){
				//ԭ��֡����
				CHECK_VALID_CONTINUE(para->operate == 2);	//�滻֡����Ч
				CHECK_VALID_CONTINUE(KoishiImageTool::loadPNG(mPic, CStrToStr(fileName)));	//�ɹ���ȡ����Ч
				if(para->holdCoordinate)
					dlg->io.PICgetInfo(dlg->io.linkFind(i), pInfo);
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!dlg->io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para->outputFormat])){
					mPic.destory();
					sPic.release();
					continue;
				}
				dlg->io.PICreplace(i, pInfo, sPic);
			}else{
				//׷��֡����
				if(!KoishiImageTool::loadPNG(mPic, CStrToStr(fileName))){
					mPic.create(1,1);
					mPic.fill(0);
				}
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!dlg->io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para->outputFormat])){
					//ʧ����ʲôҲ����
					mPic.destory();
					sPic.release();
					continue;
				}
				dlg->io.PICpush(pInfo, sPic);
			}
			mPic.destory();
			sPic.release();
		}
		dlg->bar.hide();
	}else{
		//��IMG����
		IMGobject targetIO;
		if(!targetIO.loadFile(CStrToStr(para->filePath))){
			dlg->MessageBox(L"�޷�ʶ���IMG�ļ�����",L"��ʾ��");
			dlg->processing = 0;
			return 0;
		}
		dlg->bar.show(targetIO.indexCount-1);
		for(int i = 0;i<targetIO.indexCount;i++){
			dlg->bar.setInfo(L"�����"+NumToCStr(i)+L"֡������",i);
			if(i<dlg->io.indexCount){
				//ԭ��֡����
				CHECK_VALID_CONTINUE(para->operate == 2);	//�滻֡����Ч
				targetIO.PICextract(i, mPic);
				targetIO.PICgetInfo(targetIO.linkFind(i), pInfo);
				if(para->holdCoordinate){
					dlg->io.PICgetInfo(dlg->io.linkFind(i), pInfo);
				}
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!dlg->io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para->outputFormat])){
					mPic.destory();
					sPic.release();
					continue;
				}
				dlg->io.PICreplace(i, pInfo, sPic);
			}else{
				//׷��֡����
				targetIO.PICextract(i, mPic);
				targetIO.PICgetInfo(targetIO.linkFind(i), pInfo);
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!dlg->io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para->outputFormat])){
					mPic.destory();
					sPic.release();
					continue;
				}
				dlg->io.PICpush(pInfo, sPic);
			}
			mPic.destory();
			sPic.release();
		}
		dlg->bar.hide();
	}
	dlg->updatePIClist();
	dlg->processing = 0;
	dlg->bar.hide();
	dlg->updateInfo();
	dlg->saveAlert = true;
	dlg->draw();
	return 0U;
}

void CExRabbitDlg::OnMenuPictureDelete(){
	// TODO: ɾ��֡(&R)
	int i, row = crtPICid;
	io.PICremove(row);
	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->DeleteItem(row);
	for(i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(i,0,NumToCStr(i));//�������
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnMenuPictureDeletePatch(){
	// TODO: �ڴ���������������
	int i = 0;
	for(i=io.indexCount-1;i>=0;i--){
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetCheck(i)){
			io.PICremove(i);
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->DeleteItem(i);
		}
	}
	for(i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(i,0,NumToCStr(i));//�������
	saveAlert = true;
	updateInfo();
}


void CExRabbitDlg::OnMenuPictureAxisModify(){
	// TODO: �ڴ���������������
	ModalPictureParameter dlg;
	PICinfo pi;
	io.PICgetInfo(io.linkFind(crtPICid), pi);
	dlg.in.curBX = pi.basePt.X;
	dlg.in.curBY = pi.basePt.Y;
	dlg.in.curFW = pi.frmSize.W;
	dlg.in.curFH = pi.frmSize.H;
	if(IDOK == dlg.DoModal()){
		ParaPictureAxisModify = dlg.out;
		AfxBeginThread(ThreadPictureAxisModify, this);
	}
}

UINT CExRabbitDlg::ThreadPictureAxisModify(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	ModalPictureParameter::OUTPUT *para = &dlg->ParaPictureAxisModify;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, para->target - 1, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i = 0;i<targetList.size();i++){
		int id = targetList[i];
		dlg->bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
		PICinfo pInfo;
		point newPt;
		size newSz;
		dlg->io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para->operate){
		case 1:
			//ƽ�ƻ�׼��
			newPt = pInfo.basePt + point(
				para->enable[0] ? para->para[0] : 0,
				para->enable[1] ? para->para[1] : 0);
			dlg->io.PICsetInfoPara(id, 1, &newPt);
			dlg->updatePICterm(id);
			break;
		case 2:
			//ͳһ��׼��
			newPt = point(
				para->enable[0] ? para->para[0] : pInfo.basePt.X,
				para->enable[1] ? para->para[1] : pInfo.basePt.Y);
			dlg->io.PICsetInfoPara(id, 1, &newPt);
			dlg->updatePICterm(id);
			break;
		case 3:
			//��������
			newSz = size(
				para->enable[0] ? para->para[0] : pInfo.frmSize.W,
				para->enable[1] ? para->para[1] : pInfo.frmSize.H);
			dlg->io.PICsetInfoPara(id, 2, &newSz);
			dlg->updatePICterm(id);
			break;
		}
	}
	dlg->saveAlert = true;
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}


void CExRabbitDlg::OnMenuPictureCanvas(){
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
		return;
	}
	ModalAdjustCanvas dlg;
	PICinfo pi;
	io.PICgetTotalBound(dlg.in.imgX1, dlg.in.imgX2, dlg.in.imgY1, dlg.in.imgY2);
	io.PICgetInfo(io.linkFind(crtPICid), pi);
	dlg.in.curX1 = pi.basePt.X;
	dlg.in.curX2 = pi.basePt.X + pi.picSize.W - 1;
	dlg.in.curY1 = pi.basePt.Y;
	dlg.in.curY2 = pi.basePt.Y + pi.picSize.H - 1;
	if(IDOK == dlg.DoModal()){
		ParaPictureCanvas = dlg.out;
		AfxBeginThread(ThreadPictureCanvas, this);
	}
}

UINT CExRabbitDlg::ThreadPictureCanvas(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	ModalAdjustCanvas::OUTPUT *para = &dlg->ParaPictureCanvas;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, para->target - 1, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i = 0;i<targetList.size();i++){
		int id = targetList[i];
		dlg->bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
		PICinfo pInfo;
		matrix mPic;
		stream sPic;
		dlg->io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para->operate){
		case 1:
			//����
			if(dlg->io.version == V4 || dlg->io.version == V6){
				dlg->io.PICextractIndexMatrix(id, mPic);
				mPic.expand(
					para->enable[1] ? para->para[1] : 0,
					para->enable[3] ? para->para[3] : 0,
					para->enable[0] ? para->para[0] : 0,
					para->enable[2] ? para->para[2] : 0);
				pInfo.basePt = pInfo.basePt - point(
					para->enable[0] ? para->para[0] : 0, 
					para->enable[1] ? para->para[1] : 0);
				dlg->io.PICpreprocessIndexMatrix(mPic, sPic, pInfo);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}else{
				dlg->io.PICextract(id, mPic);
				mPic.expand(
					para->enable[1] ? para->para[1] : 0,
					para->enable[3] ? para->para[3] : 0,
					para->enable[0] ? para->para[0] : 0,
					para->enable[2] ? para->para[2] : 0);
				pInfo.basePt = pInfo.basePt - point(
					para->enable[0] ? para->para[0] : 0, 
					para->enable[1] ? para->para[1] : 0);
				dlg->io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			dlg->updatePICterm(id);
			break;
		case 2:
			//����
			if(dlg->io.version == V4 || dlg->io.version == V6){
				dlg->io.PICextractIndexMatrix(id, mPic);
				mPic.clip(
					para->enable[1] ? para->para[1]:0,
					-(para->enable[3] ? para->para[3]:0) + pInfo.picSize.H - 1,
					para->enable[0] ? para->para[0]:0,
					-(para->enable[2] ? para->para[2]:0) + pInfo.picSize.W - 1);
				pInfo.basePt = pInfo.basePt + point(
					para->enable[0] ? para->para[0] : 0, 
					para->enable[1] ? para->para[1] : 0);
				dlg->io.PICpreprocessIndexMatrix(mPic, sPic, pInfo);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}else{
				dlg->io.PICextract(id, mPic);
				mPic.clip(
					para->enable[1] ? para->para[1]:0,
					-(para->enable[3] ? para->para[3]:0) + pInfo.picSize.H - 1,
					para->enable[0] ? para->para[0]:0,
					-(para->enable[2] ? para->para[2]:0) + pInfo.picSize.W - 1);
				pInfo.basePt = pInfo.basePt + point(
					para->enable[0] ? para->para[0] : 0, 
					para->enable[1] ? para->para[1] : 0);
				dlg->io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			dlg->updatePICterm(id);
			break;
		case 3:
			//��������
			if(dlg->io.version == V4 || dlg->io.version == V6){
				matrix mNew;
				int x1old = pInfo.basePt.X;
				int y1old = pInfo.basePt.Y;
				int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
				int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
				int x1new = para->enable[0] ? para->para[0] : x1old;
				int y1new = para->enable[1] ? para->para[1] : y1old;
				int x2new = para->enable[2] ? para->para[2] : x2old;
				int y2new = para->enable[3] ? para->para[3] : y2old;
				int x1 = min(x1old,x1new);
				int x2 = max(x2old,x2new);
				int y1 = min(y1old,y1new);
				int y2 = max(y2old,y2new);
				dlg->io.PICextractIndexMatrix(id, mPic);
				mNew.create(y2-y1+1,x2-x1+1);
				mNew.putFore(mPic, LAY, point(x1old-x1, y1old-y1));
				mNew.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
				pInfo.basePt = point(x1new, y1new);
				dlg->io.PICpreprocessIndexMatrix(mNew, sPic, pInfo);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				mNew.destory();
				sPic.release();
			}else{
				matrix mNew;
				int x1old = pInfo.basePt.X;
				int y1old = pInfo.basePt.Y;
				int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
				int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
				int x1new = para->enable[0] ? para->para[0] : x1old;
				int y1new = para->enable[1] ? para->para[1] : y1old;
				int x2new = para->enable[2] ? para->para[2] : x2old;
				int y2new = para->enable[3] ? para->para[3] : y2old;
				int x1 = min(x1old,x1new);
				int x2 = max(x2old,x2new);
				int y1 = min(y1old,y1new);
				int y2 = max(y2old,y2new);
				dlg->io.PICextract(id, mPic);
				mNew.create(y2-y1+1,x2-x1+1);
				mNew.putFore(mPic, LAY, point(x1old-x1, y1old-y1));
				mNew.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
				pInfo.basePt = point(x1new, y1new);
				dlg->io.PICpreprocess(mNew, sPic, pInfo, pInfo.format);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				mNew.destory();
				sPic.release();
			}
			dlg->updatePICterm(id);
			break;
		case 4:
			//����
			if(dlg->io.version == V4 || dlg->io.version == V6){
				dlg->io.PICextractIndexMatrix(id, mPic);
				dword x1, x2, y1, y2;
				mPic.getElemHonzBound(x1, x2);
				mPic.getElemVertBound(y1, y2);
				x1 = para->enable[0] ? x1:0;
				x2 = para->enable[2] ? x2:(pInfo.picSize.W - 1);
				y1 = para->enable[1] ? y1:0;
				y2 = para->enable[3] ? y2:(pInfo.picSize.H - 1);
				if(x1<x2){
					mPic.clip(y1, y2+1, x1, x2+1);
					pInfo.basePt = pInfo.basePt + point(x1, y1);
					dlg->io.PICpreprocessIndexMatrix(mPic, sPic, pInfo);
					dlg->io.PICreplace(id, pInfo, sPic);
				}
				mPic.destory();
				sPic.release();
			}else{
				dlg->io.PICextract(id, mPic);
				dword x1, x2, y1, y2;
				mPic.getElemHonzBound(x1, x2);
				mPic.getElemVertBound(y1, y2);
				x1 = para->enable[0] ? x1:0;
				x2 = para->enable[2] ? x2:(pInfo.picSize.W - 1);
				y1 = para->enable[1] ? y1:0;
				y2 = para->enable[3] ? y2:(pInfo.picSize.H - 1);
				if(x1<x2){
					mPic.clip(y1, y2+1, x1, x2+1);
					pInfo.basePt = pInfo.basePt + point(x1, y1);
					dlg->io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
					dlg->io.PICreplace(id, pInfo, sPic);
				}
				mPic.destory();
				sPic.release();
			}
			dlg->updatePICterm(id);
			break;
		}
	}
	dlg->saveAlert = true;
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}


void CExRabbitDlg::OnMenuPictureClear(){
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
		return;
	}
	ModalClearPicture dlg;
	if(IDOK == dlg.DoModal()){
		ParaPictureClear = dlg.out;
		AfxBeginThread(ThreadPictureClear, this);
	}
}

UINT CExRabbitDlg::ThreadPictureClear(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	ModalClearPicture::OUTPUT *para = &dlg->ParaPictureClear;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, para->target - 1, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i = 0;i<targetList.size();i++){
		int id = targetList[i];
		dlg->bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
		PICinfo pInfo;
		matrix mPic;
		stream sPic;
		dlg->io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para->operate){
		case 1:
			//��������
			if(dlg->io.version == V4 || dlg->io.version == V6){
				mPic.create(pInfo.picSize);
				dlg->io.PICpreprocessIndexMatrix(mPic, sPic, pInfo);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}else{
				mPic.create(pInfo.picSize);
				dlg->io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			dlg->updatePICterm(id);
			break;
		case 2:
			//�������꣬������Ϊ0,0
			if(dlg->io.version == V4 || dlg->io.version == V6){
				mPic.create(1,1);
				dlg->io.PICpreprocessIndexMatrix(mPic, sPic, pInfo);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}else{
				mPic.create(1,1);
				dlg->io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				dlg->io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			dlg->updatePICterm(id);
			break;
		}
	}
	dlg->saveAlert = true;
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}

void CExRabbitDlg::OnMenuPictureLoseblack(){
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
		return;
	}
	ModalLoseBlackPicture dlg;
	if(IDOK == dlg.DoModal()){
		ParaPictureLoseBlack = dlg.out;
		AfxBeginThread(ThreadPictureLoseBlack, this);
	}
}
UINT CExRabbitDlg::ThreadPictureLoseBlack(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	ModalLoseBlackPicture::OUTPUT *para = &dlg->ParaPictureLoseBlack;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, para->target - 1, targetList);
	if(dlg->io.version == V4 || dlg->io.version == V6){
		color clr;
		dlg->bar.show(targetList.size()-1);
		for(int j = 0;j<dlg->cl.size();j++){
			dlg->bar.setInfo(L"���ڴ����"+NumToCStr(j)+L"����ɫ������",j);
			clr = color::loseBlack(dlg->cl[j], para->gamma);
			dlg->io.CLRreplace(j, clr, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			dlg->cl[j] = clr;
		}
	}else{
		dlg->bar.show(targetList.size()-1);
		for(int i = 0;i<targetList.size();i++){
			int id = targetList[i];
			dlg->bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
			PICinfo pInfo;
			matrix mPic;
			stream sPic;
			dlg->io.PICgetInfo(id, pInfo);
			CHECK_VALID_CONTINUE(pInfo.format != LINK);
			switch(1){
			case 1:
				dlg->io.PICextract(id, mPic);
				mPic.loseBlack(para->gamma);
				dlg->io.PICpreprocess(mPic, sPic, pInfo, ARGB8888);
				dlg->io.PICreplace(id, pInfo, sPic);
				sPic.release();
				mPic.destory();
				break;
			}
		}
	}
	dlg->saveAlert = true;
	dlg->updateColorTable();
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}
void CExRabbitDlg::OnMenuPictureGradient(){
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
		return;
	}
	ModalGradient dlg;
	if(IDOK == dlg.DoModal()){
		ParaPictureGradient = dlg.out;
		AfxBeginThread(ThreadPictureGradient, this);
	}
}
UINT CExRabbitDlg::ThreadPictureGradient(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	ModalGradient::OUTPUT *para = &dlg->ParaPictureGradient;
	dlg->processing = 1;
	colorList keyColorList;
	keyColorList.push_back(para->keyColor2);
	keyColorList.push_back(para->keyColor1);
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, para->target - 1, targetList);
	if(dlg->io.version == V2){
		dlg->bar.show(targetList.size()-1);
		for(int i = 0;i<targetList.size();i++){
			int id = targetList[i];
			dlg->bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
			PICinfo pInfo;
			matrix mPic;
			stream sPic;
			CHECK_VALID_CONTINUE(pInfo.format != LINK);
			//CHECK_VALID_CONTINUE(id != dlg->crtPICid);
			dlg->io.PICgetInfo(id, pInfo);
			dlg->io.PICextract(id, mPic);
			for(int n = 0;n<mPic.getElemCount();n++){
				color clr = mPic.getElem(n);
				color newClr = KoishiImageTool::gradient(clr, keyColorList, para->useProperty);
				if(para->remainAlpha){
					newClr.alpha = clr.alpha;
				}
				mPic.setElem(n, newClr);
			}
			dlg->io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
			dlg->io.PICreplace(id, pInfo, sPic);
			sPic.release();
			mPic.destory();
			TRACE(NumToCStr(i)+L"\n");
		}
	}else{
		dlg->bar.show(dlg->cl.size()-1);
		for(int i = 0;i<dlg->cl.size();i++){
			dlg->bar.setInfo(L"���ڴ����"+NumToCStr(i)+L"����ɫ������",i);
			color clr = dlg->cl[i];
			color newClr = KoishiImageTool::gradient(clr, keyColorList, para->useProperty);
			if(para->remainAlpha){
				newClr.alpha = clr.alpha;
			}
			dlg->cl[i] = newClr;
			dlg->io.CLRreplace(i, newClr, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
		}
	}
	dlg->saveAlert = true;
	dlg->updateColorTable();
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}
void CExRabbitDlg::OnMenuPictureColor(){
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
		return;
	}
	ModalAdjustColor dlg;
	dlg.in.version = io.version;
	dlg.in.oldCl = cl;
	if(io.version == V2){
		io.PICextract(crtPICid, dlg.in.oldV2matrix);
	}
	if(IDOK == dlg.DoModal()){
		if(io.version == V2){
			ParaPictureColor = dlg.out;
			AfxBeginThread(ThreadPictureColor, this);
		}
	}
}
UINT CExRabbitDlg::ThreadPictureColor(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	ModalAdjustColor::OUTPUT *para = &dlg->ParaPictureColor;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, para->target - 1, targetList);
	//V2�����߳�
	dlg->bar.show(targetList.size()-1);
	for(int i = 0;i<targetList.size();i++){
		int id = targetList[i];
		dlg->bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
		PICinfo pInfo;
		matrix mPic;
		stream sPic;
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		CHECK_VALID_CONTINUE(id != dlg->crtPICid);
		dlg->io.PICgetInfo(id, pInfo);
		dlg->io.PICextract(id, mPic);
		for(int n = 0;n<mPic.getElemCount();n++){
			color clr = mPic.getElem(n);
			colorHSV ch;
			clr.getHSV(ch);
			clr.moveH(para->H*180/100);
			clr.moveS((para->S>=0)?(double)para->S/100*(1-ch.S):(double)para->S/100*ch.S);
			clr.moveV((para->V>=0)?(double)para->V/100*(1-ch.V):(double)para->V/100*ch.V);
			clr.moveR((para->R>=0)?para->R*(0xff-clr.R)/100:para->R*clr.R/100);
			clr.moveG((para->R>=0)?para->G*(0xff-clr.G)/100:para->G*clr.G/100);
			clr.moveB((para->R>=0)?para->B*(0xff-clr.B)/100:para->B*clr.B/100);
			clr.moveA((para->a>=0)?para->a*(0xff-clr.alpha)/100:para->a*clr.alpha/100);
			mPic.setElem(n, clr);
		}
		dlg->io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
		dlg->io.PICreplace(id, pInfo, sPic);
		sPic.release();
		mPic.destory();
		TRACE(NumToCStr(i)+L"\n");
	}
	dlg->saveAlert = true;
	dlg->updateColorTable();
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}
void CExRabbitDlg::OnMenuPictureMark(){
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
		return;
	}
	ModalAddMark dlg;
	dlg.in.version = io.version;
	dlg.in.list = cl;
	if(IDOK == dlg.DoModal()){
		ParaPictureMark = dlg.out;
		AfxBeginThread(ThreadPictureMark, this);
	}
}

UINT CExRabbitDlg::ThreadPictureMark(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg*)context;
	ModalAddMark::OUTPUT *para = &dlg->ParaPictureMark;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, para->target - 1, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i = 0;i<targetList.size();i++){
		int id = targetList[i];
		dlg->bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
		PICinfo pInfo;
		matrix oldPic, newPic;
		stream sPic;
		point markPoint;
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		dlg->io.PICgetInfo(id, pInfo);
		switch(para->operate){
		case 1:
			markPoint = point(para->xDelta, para->yDelta) - pInfo.basePt;
			break;
		case 2:
			markPoint = point(para->xDelta, para->yDelta);
			break;
		case 3:
			markPoint = point(para->xDelta + pInfo.picSize.W, para->yDelta);
			break;
		case 4:
			markPoint = point(para->xDelta, para->yDelta + pInfo.picSize.H);
			break;
		case 5:
			markPoint = point(para->xDelta + pInfo.picSize.W, para->yDelta + pInfo.picSize.H);
			break;
		}
		CString fullString = para->text;
		CString subString;
		CString markString = L"";
		int findLeftBracket, findRightBracket;
		while(1){
			findLeftBracket = fullString.Find('[');
			findRightBracket = fullString.Find(']');
			if(findLeftBracket < 0 || findRightBracket < 0 ||findRightBracket < findLeftBracket){
				markString += fullString;
				break;
			}
			AfxExtractSubString(subString, fullString, 0, '[');
			markString += subString;
			AfxExtractSubString(subString, fullString, 1, '[');
			if(subString.Left(1) == L"F"){
				markString += NumToCStr(id);
			}
			if(subString.Left(1) == L"I"){
				markString += GetTail(StrToCStr(dlg->no.entry[dlg->crtIMGid].comment));
			}
			if(subString.Left(1) == L"X"){
				markString += NumToCStr(pInfo.basePt.X);
			}
			if(subString.Left(1) == L"Y"){
				markString += NumToCStr(pInfo.basePt.Y);
			}
			subString = fullString.Right(fullString.GetLength() - findRightBracket - 1);
			fullString = subString;
		}

		if(dlg->io.version == V2){
			dlg->io.PICextract(id, oldPic);
			KoishiExpand::KoishiMarkTool::MatrixMarking(
				oldPic, newPic, CStrToStr(markString), markPoint, para->useColor);
			if(markPoint.X < 0){
				pInfo.basePt.X += markPoint.X;
			}
			if(markPoint.Y < 0){
				pInfo.basePt.Y += markPoint.Y;
			}
			dlg->io.PICpreprocess(newPic, sPic, pInfo, pInfo.format);
		}else{
			dlg->io.PICextractIndexMatrix(id, oldPic);
			KoishiExpand::KoishiMarkTool::MatrixMarking(
				oldPic, newPic, CStrToStr(markString), markPoint, color(para->useColorID,0,0,0));
			if(markPoint.X < 0){
				pInfo.basePt.X += markPoint.X;
			}
			if(markPoint.Y < 0){
				pInfo.basePt.Y += markPoint.Y;
			}
			dlg->io.PICpreprocessIndexMatrix(newPic, sPic, pInfo);
		}
		dlg->io.PICreplace(id, pInfo, sPic);
		oldPic.destory();
		newPic.destory();
		sPic.release();
		dlg->updatePICterm(id);
	}
	dlg->saveAlert = true;
	dlg->updateColorTable();
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}
void CExRabbitDlg::OnMenuPictureGetPng(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtPICid >= 0);
	ParaPictureGetPNG = SINGLE_SELECT;
	AfxBeginThread(ThreadPictureGetPNG, this);
}
void CExRabbitDlg::OnMenuPictureGetPngPatch(){
	// TODO: �ڴ���������������
	ParaPictureGetPNG = MULTI_SELECT;
	AfxBeginThread(ThreadPictureGetPNG, this);
}
UINT CExRabbitDlg::ThreadPictureGetPNG(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
	dlg->processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, dlg->ParaPictureGetPNG, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i=0;i<targetList.size();i++){
		dlg->bar.setInfo(L"������ȡ��"+NumToCStr(targetList[i])+L"֡������",i);
		CString fileName;
		matrix mPic;
		if(dlg->io.version == V6){
			fileName = dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname,GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel())+NumToCStr(targetList[i])+L".PNG";
		}else{
			fileName = dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+NumToCStr(targetList[i])+L".PNG";
		}
		dlg->io.PICextract(targetList[i], mPic, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
		KoishiImageTool::makePNG(mPic, CStrToStr(fileName));
		mPic.destory();
	}
	dlg->processing = 0;
	dlg->MessageBox(L"�ѱ��浽�ļ���"+dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+L"��������",L"��ʾ��");
	dlg->bar.hide();
	return 0U;
}
void CExRabbitDlg::OnMenuPictureGetGIF(){
	AfxBeginThread(ThreadPictureGetGIF, this);
}
UINT CExRabbitDlg::ThreadPictureGetGIF(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
	dlg->processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), dlg->crtPICid, MULTI_SELECT, targetList);
	if(targetList.size() < 1){
		dlg->MessageBox(L"�빴ѡһЩ֡����",L"��ʾ��");
		dlg->processing = 0;
		return 0U;
	}
	dlg->bar.show(targetList.size()-1);
	std::vector<matrix> matList;
	long imgX1, imgX2, imgY1, imgY2;
	dlg->io.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
	for(int i=0;i<targetList.size();i++){
		dlg->bar.setInfo(L"���ڴ����"+NumToCStr(targetList[i])+L"֡������",i);
		matrix mOrigin, mExpanded;
		PICinfo pInfo;
		dlg->io.PICgetInfo(dlg->io.linkFind(targetList[i]), pInfo); 
		dlg->io.PICextract(dlg->io.linkFind(targetList[i]), mOrigin, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
		int x1old = pInfo.basePt.X;
		int y1old = pInfo.basePt.Y;
		int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
		int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
		int x1new = imgX1;
		int y1new = imgY1;
		int x2new = imgX2;
		int y2new = imgY2;
		int x1 = min(x1old,x1new);
		int x2 = max(x2old,x2new);
		int y1 = min(y1old,y1new);
		int y2 = max(y2old,y2new);
		mExpanded.create(y2-y1+1,x2-x1+1);
		mExpanded.putFore(mOrigin, LAY, point(x1old-x1, y1old-y1));
		mExpanded.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
		matList.push_back(mExpanded);
		mOrigin.destory();
		mExpanded.destory();
	}
	dlg->bar.setInfo(L"��������GIF������",targetList.size());
	KoishiImageTool::GIF::GIFobject go;
	go.input(matList, dlg->profile.miniSecPerFrame, dlg->no.entry[dlg->crtIMGid].comment, targetList);
	CString fileName = dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+NumToCStr(targetList[0])+L".GIF";
	go.makeFile(CStrToStr(fileName));
	dlg->processing = 0;
	dlg->MessageBox(L"�ѱ��浽�ļ���"+dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+L"��������",L"��ʾ��");
	dlg->bar.hide();
	return 0U;
}
void CExRabbitDlg::OnMenuTextureChooseAll(){
	// TODO: �ڴ���������������
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetCheck(i, TRUE);
}
void CExRabbitDlg::OnMenuTextureChooseInverse(){
	// TODO: �ڴ���������������
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetCheck(i, 1-GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetCheck(i));
}
void CExRabbitDlg::OnMenuTextureChooseHighline(){
	// TODO: �ڴ���������������
	for(int i=0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount(); i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetCheck(i,TRUE);
}
void CExRabbitDlg::OnMenuTextureInsert(){
	// TODO: �ڴ���������������
	ModalInsertTexture dlg;
	dlg.in.firstInsert = false;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.TEXgetInfo(crtTEXid, dlg.in.ti);
	if(IDOK == dlg.DoModal()){
		ParaTextureInsert = dlg.out;
		AfxBeginThread(ThreadTextureInsert, this);
	}
}
void CExRabbitDlg::OnMenuTextureInsert2(){
	// TODO: �ڴ���������������
	ModalInsertTexture dlg;
	dlg.in.firstInsert = true;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.TEXgetInfo(crtTEXid, dlg.in.ti);
	if(IDOK == dlg.DoModal()){
		ParaTextureInsert = dlg.out;
		AfxBeginThread(ThreadTextureInsert, this);
	}
}

UINT CExRabbitDlg::ThreadTextureInsert(void*context){
	CExRabbitDlg*dlg = (CExRabbitDlg*)context;
	ModalInsertTexture::OUTPUT *para = &dlg->ParaTextureInsert;
	dlg->processing = 1;
	int insertPos;
	int replacePos;
	matrix mPic;
	stream sPic;
	TEXinfo tInfo;
	DDSobject DDSHelper;
	//ȷ������Ŀ��
	switch(para->operate){
	case 1:
		replacePos = dlg->crtTEXid;;
		break;
	case 2:
		insertPos = dlg->crtTEXid;
		break;
	case 3:
		insertPos = dlg->crtTEXid + 1;
		break;
	case 4:
		insertPos = dlg->io.V5_TEXCount;
		break;
	}
	if(dlg->crtTEXid < 0){
		para->operate = 4;
		insertPos = 0;
	}
	//��ȡ��Դ
	if(para->inputFormat == 1 && para->outputFormat == 1){
		//��������ļ�����Ч��DDS��ʽ������DDS��ʽ���Ҳ����κ�ת�������޸�TEXinfo
		stream sOrigin, sCompressed;
		sOrigin.loadFile(CStrToStr(para->fileName));
		sOrigin.ZLIBcompress(sCompressed);
		DDSHelper.load(sOrigin);
		tInfo.dataLength = sOrigin.length;
		tInfo.compressedLength = sCompressed.length;
		tInfo.format = (colorFormat)(DDS_DXT1 + ((DDSHelper.getHeader()->pixelFormat.fourCC - 0x31545844) >> 25));
		tInfo.height = DDSHelper.getHeader()->height;
		tInfo.width = DDSHelper.getHeader()->width;
		tInfo.reserved = 1;
		if(para->operate == 1){
			tInfo.ID = replacePos;
			dlg->io.TEXreplace(replacePos, tInfo, sCompressed);
		}else{
			tInfo.ID = insertPos;
			dlg->io.TEXinsert(insertPos, tInfo, sCompressed);
		}
		sOrigin.release();
		sCompressed.release();
		dlg->updateTEXlist();
	}else{
		//ת��ΪPNG�ٲ���
		switch(para->inputFormat){
		case 0:
			mPic.create(1, 1);
			mPic.fill(0);
			break;
		case 1:
			KoishiImageTool::loadPNG(mPic, CStrToStr(para->fileName));
			break;
		case 2:
			DDSHelper.loadFile(CStrToStr(para->fileName));
			DDSHelper.uncompress(mPic);
			break;
		}
		colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, DDS_DXT5, ARGB8888, ARGB4444, ARGB1555};
		dlg->io.TEXpreprocess(mPic, sPic, tInfo, outputFormatByCtrl[para->outputFormat]);
		mPic.destory();
		if(para->operate == 1){
			tInfo.ID = replacePos;
			dlg->io.TEXreplace(replacePos, tInfo, sPic);
		}else{
			tInfo.ID = insertPos;
			dlg->io.TEXinsert(insertPos, tInfo, sPic);
		}
		dlg->updateTEXlist();
	}
	sPic.release();
	mPic.destory();
	dlg->saveAlert = true;
	dlg->updateInfo();
	dlg->draw();
	dlg->processing = 0;
	dlg->bar.hide();
	return 0U;
}
void CExRabbitDlg::OnMenuTextureDelete(){
	// TODO: �ڴ���������������
	int i, row = crtTEXid;
	io.TEXremove(row);
	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->DeleteItem(row);
	for(i=0;i<io.V5_TEXCount;i++){
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetItemText(i,0,NumToCStr(i));
	}
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnMenuTextureDeletePatch(){
	// TODO: �ڴ���������������
	int i = 0;
	for(i=io.V5_TEXCount-1;i>=0;i--){
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetCheck(i)){
			io.PICremove(i);
			GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->DeleteItem(i);
		}
	}
	for(i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetItemText(i,0,NumToCStr(i));//�������
	saveAlert = true;
	updateInfo();
}
void CExRabbitDlg::OnMenuTextureGetPng(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtTEXid >= 0);
	ParaTextureGetPNG = SINGLE_SELECT;
	AfxBeginThread(ThreadTextureGetPNG, this);
}
void CExRabbitDlg::OnMenuTextureGetPngPatch(){
	// TODO: �ڴ���������������
	ParaTextureGetPNG = MULTI_SELECT;
	AfxBeginThread(ThreadTextureGetPNG, this);
}
void CExRabbitDlg::OnMenuTextureGetOrigin(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtTEXid >= 0);
	ParaTextureGetOrigin = SINGLE_SELECT;
	AfxBeginThread(ThreadTextureGetOrigin, this);
}
void CExRabbitDlg::OnMenuTextureGetOriginPatch(){
	// TODO: �ڴ���������������
	ParaTextureGetOrigin = MULTI_SELECT;
	AfxBeginThread(ThreadTextureGetOrigin, this);
}
UINT CExRabbitDlg::ThreadTextureGetPNG(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
	dlg->processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_DDS), dlg->crtTEXid, dlg->ParaTextureGetPNG, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i=0;i<targetList.size();i++){
		dlg->bar.setInfo(L"������ȡ��"+NumToCStr(targetList[i])+L"����������",i);
		CString fileName;
		matrix mPic;
		fileName = dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+L"Texture-"+NumToCStr(targetList[i])+L".PNG";
		dlg->io.TEXextract(targetList[i], mPic);
		KoishiImageTool::makePNG(mPic, CStrToStr(fileName));
		mPic.destory();
	}
	dlg->processing = 0;
	dlg->bar.hide();
	dlg->MessageBox(L"�ѱ��浽�ļ���"+dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+L"���ˡ�",L"��ʾ��");
	return 0U;
}

UINT CExRabbitDlg::ThreadTextureGetOrigin(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
	dlg->processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_DDS), dlg->crtTEXid, dlg->ParaTextureGetPNG, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i=0;i<targetList.size();i++){
		dlg->bar.setInfo(L"������ȡ��"+NumToCStr(targetList[i])+L"����������",i);
		CString fileName;
		stream sCompressed, sDDS;
		fileName = dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+L"Texture-"+NumToCStr(targetList[i])+L".dds";
		dlg->io.TEXgetData(targetList[i], sCompressed);
		sCompressed.ZLIBuncompress(sDDS);
		sDDS.makeFile(CStrToStr(fileName));
		sDDS.release();
		sCompressed.release();
	}
	dlg->processing = 0;
	dlg->bar.hide();
	dlg->MessageBox(L"�ѱ��浽�ļ���"+dlg->profile.getOutputPath(dlg->fileNPKname,dlg->fileIMGname)+L"���ˡ�",L"��ʾ��");
	return 0U;
}


void CExRabbitDlg::OnMenuImageExtract(){
	CHECK_VALID(crtIMGid >= 0);
	ParaImageExtract = SINGLE_SELECT;
	AfxBeginThread(ThreadImageExtract, this);
}


void CExRabbitDlg::OnMenuImageExtractPatch(){
	ParaImageExtract = MULTI_SELECT;
	AfxBeginThread(ThreadImageExtract, this);
}

UINT CExRabbitDlg::ThreadImageExtract(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
	dlg->processing = 1;
	CString filePath = dlg->profile.getOutputPath(dlg->fileNPKname);
	CString fileName;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG), dlg->crtIMGid, dlg->ParaImageExtract, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i=0;i<targetList.size();i++){
		int id = targetList[i];
		dlg->bar.setInfo(L"������ȡ"+GetTail(StrToCStr(dlg->no.entry[id].comment))+L"������", i);
		fileName = filePath+Underlining(StrToCStr(dlg->no.entry[id].comment));
		dlg->no.extract(id, CStrToStr(fileName));
	}
	dlg->MessageBox(L"ȫ����ȡ��������ѱ��浽"+dlg->profile.getOutputPath(dlg->fileNPKname)+L"������",L"��ʾ��");
	dlg->bar.hide();
	dlg->processing = 0;
	return 0U;
}

void CExRabbitDlg::OnMenuImageSave(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtIMGid >= 0);
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(false, defExt, Underlining(StrToCStr(no.entry[crtIMGid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		no.extract(crtIMGid, CStrToStr(dlg.GetPathName()));
		MessageBox(_T("�����������"));
	}
}

void CExRabbitDlg::OnMenuImageInsertOther(){
	// TODO: �ڴ���������������
	CString defExt = _T("�����ļ�(*.*)|*.*");
	CString extFilter = _T("�����ļ�(*.*)|*.*||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK){
		no.insert(crtIMGid, CStrToStr(dlg.GetPathName()),shorten(CStrToStr(dlg.GetPathName())));
		updateIMGlist();
	}
}


void CExRabbitDlg::OnMenuImageInsert(){
	// TODO: �ڴ���������������
	ModalInsertImage dlg;
	dlg.in.firstInsert = false;
	if(IDOK == dlg.DoModal()){
		ParaImageInsert = dlg.out;
		AfxBeginThread(ThreadImageInsert, this);
	}
}

void CExRabbitDlg::OnMenuImageInsert2()
{
	ModalInsertImage dlg;
	dlg.in.firstInsert = true;
	if(IDOK == dlg.DoModal()){
		ParaImageInsert = dlg.out;
		AfxBeginThread(ThreadImageInsert, this);
	}
}


UINT CExRabbitDlg::ThreadImageInsert(void*context){
	CExRabbitDlg*dlg = (CExRabbitDlg*)context;
	ModalInsertImage::OUTPUT *para = &dlg->ParaImageInsert;
	dlg->processing = 1;
	int insertPos;
	switch(para->operate){
	case 1:
		insertPos = dlg->crtIMGid;
		break;
	case 2:
		insertPos = dlg->crtIMGid + 1;
		break;
	case 3:
		insertPos = dlg->no.count;
		break;
	}
	switch(para->type){
	case 1:
		if(true){
			IMGobject newIO;
			newIO.create(para->newVersion);
			dlg->no.IMGinsert(insertPos, newIO, CStrToStr(para->pathName));
			GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(insertPos,GetTail(para->pathName),dlg->getIconIMG(para->newVersion));
			newIO.release();
		}
		break;
	case 2:
		if(true){
			IMGobject newIO;
			newIO.loadFile(CStrToStr(para->fileName));
			dlg->no.IMGinsert(insertPos, newIO, CStrToStr(para->pathName));
			GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(insertPos,GetTail(para->pathName),dlg->getIconIMG(para->newVersion));
			newIO.release();
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
				dlg->bar.setInfo(L"��ǰ����"+GetTail(StrToCStr(newNO.entry[i].comment))+
					L"������(�ɹ�"+NumToCStr(countSuccess)+
					L"��,����"+NumToCStr(countSkip)+
					L"��,�滻"+NumToCStr(countReplace)+
					L"��,ʧ��"+NumToCStr(countFail)+
					L"��)", i);
				IMGobject newIO;
				if(!newNO.IMGextract(i, newIO)){
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
					dlg->no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment);
					countSuccess ++;
				}else{
					//��ͻ����
					switch(para->conflict){
					case 1:
						countSkip ++;
						break;
					case 2:
						dlg->no.IMGreplace(conflict, newIO);
						countReplace ++;
						break;
					case 3:
						dlg->no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment+"(new)");
						countSuccess ++;
						break;
					}
				}
				newIO.release();
			}
			dlg->MessageBox(L"�������������"+NumToCStr(newNO.count)+
					L"��,�ɹ�"+NumToCStr(countSuccess)+
					L"��,����"+NumToCStr(countSkip)+
					L"��,�滻"+NumToCStr(countReplace)+
					L"��,ʧ��"+NumToCStr(countFail)+
					L"������",L"��ʾ��");
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
			IMGobject newIO;
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
						dlg->bar.setInfo(L"��ǰ����"+fileList[fileID] +
							L"�е�" + GetTail(StrToCStr(newNO.entry[i].comment))+
							L"������(�ɹ�"+NumToCStr(countSuccess)+
							L"��,����"+NumToCStr(countSkip)+
							L"��,�滻"+NumToCStr(countReplace)+
							L"��,ʧ��"+NumToCStr(countFail)+
							L"��)", i);
						if(!newNO.IMGextract(i, newIO)){
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
							dlg->no.IMGinsert(insertPos + totalSuccess, newIO, newNO.entry[i].comment);
							countSuccess ++;
							totalSuccess ++;
						}else{
							//��ͻ����
							switch(para->conflict){
							case 1:
								countSkip ++;
								break;
							case 2:
								dlg->no.IMGreplace(conflict, newIO);
								countReplace ++;
								break;
							case 3:
								dlg->no.IMGinsert(insertPos + totalSuccess, newIO, newNO.entry[i].comment+"(new)");
								countSuccess ++;
								totalSuccess ++;
								break;
							}
						}
						newIO.release();
					}
					newNO.release();
					countNPK ++;
					countNPKIMG += countSuccess;
				}
				if(fileList[fileID].Right(4) == L".img" || fileList[fileID].Right(4) == L".IMG" ){
					if(!newIO.loadFile(CStrToStr(pathList[fileID]))){
						continue;
					}
					dlg->bar.setInfo(L"��ǰ����"+fileList[fileID] +	L"������", 0);
					CString newPathName = Slashing(fileList[fileID]);
					dlg->no.IMGinsert(insertPos + totalSuccess, newIO, CStrToStr(newPathName));
					totalSuccess ++;
					newIO.release();
					countIMG ++;
				}
			}
			dlg->MessageBox(L"������������ɹ�������"+NumToCStr(countIMG)+L"���ⲿIMG������������"+NumToCStr(countNPK)+L"��NPK�ļ��е�����"+NumToCStr(countNPKIMG)+L"��IMG��������",L"��ʾ��");
			dlg->bar.hide();
		}
		break;
	}
	dlg->updateIMGlist();
	return 0U;
}

void CExRabbitDlg::OnMenuImageReplace(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtIMGid>=0);
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		IMGobject newIO;
		newIO.loadFile(CStrToStr(dlg.GetPathName()));
		no.IMGreplace(crtIMGid,newIO);
		MessageBox(L"�滻�������");
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(crtIMGid, 0, LVIF_IMAGE, NULL, getIconIMG(newIO.version),0,0,0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(crtIMGid);
		newIO.release();
	}
}


void CExRabbitDlg::OnMenuImageDelete(){
	CHECK_VALID(crtIMGid >= 0);
	ParaImageDelete = SINGLE_SELECT;
	AfxBeginThread(ThreadImageDelete, this);
}


void CExRabbitDlg::OnMenuImageDeletePatch(){
	ParaImageDelete = MULTI_SELECT;
	AfxBeginThread(ThreadImageDelete, this);
}

UINT CExRabbitDlg::ThreadImageDelete(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
	dlg->processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG), dlg->crtIMGid, dlg->ParaImageDelete, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i=0;i<targetList.size();i++){
		int id = targetList[targetList.size()-i-1];
		dlg->bar.setInfo(L"����ɾ��"+GetTail(StrToCStr(dlg->no.entry[id].comment))+L"������", i);
		dlg->no.IMGremove(id);
	}
	dlg->bar.hide();
	dlg->updateIMGlist();
	dlg->processing = 0;
	dlg->crtIMGid = -1;
	return 0U;
}

void CExRabbitDlg::OnMenuImageRename(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtIMGid>=0);
	ModalRename dlg;
	dlg.oldName = StrToCStr(no.entry[crtIMGid].comment);
	if(IDOK == dlg.DoModal()){
		no.rename(crtIMGid,  CStrToStr(dlg.newName));
		updateInfo();
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(crtIMGid, 0, GetTail(dlg.newName));
		fileIMGname = dlg.newName;
	}
}

void CExRabbitDlg::OnMenuImageInsertCopy(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtIMGid>=0);
	stream sr;
	str newComment = no.entry[crtIMGid].comment;
	if(newComment.size() > 4 && newComment[newComment.size() - 4 ] == '.'){
		newComment.insert(newComment.end() - 4, '2');
	}else{
		newComment.push_back('2');
	}
	no.extract(crtIMGid, sr);
	no.insert(crtIMGid + 1, sr, newComment);
	updateIMGlist();
}


void CExRabbitDlg::OnMenuImageInsertLink(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtIMGid>=0);
	str newComment = no.entry[crtIMGid].comment;
	if(newComment.size() > 4 && newComment[newComment.size() - 4 ] == '.'){
		newComment.insert(newComment.end() - 4, '2');
	}else{
		newComment.push_back('2');
	}
	no.insertLink(crtIMGid + 1, crtIMGid, newComment); 
	updateIMGlist();
}


void CExRabbitDlg::OnMenuImageDelink(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtIMGid>=0);
	if(no.delink(crtIMGid)){
		updateIMGlist();
	}else{
		MessageBox(L"����������IMG����");
	}
}

void CExRabbitDlg::OnMenuImageHide(){
	// TODO: �ڴ���������������
	ModalImageHide dlg;
	if(IDOK == dlg.DoModal()){
		ParaImageHide = dlg.out;
		AfxBeginThread(ThreadImageHide, this);
	}
}

UINT CExRabbitDlg::ThreadImageHide(void*context){
	CExRabbitDlg*dlg=(CExRabbitDlg*)context;
	ModalImageHide::OUTPUT para = dlg->ParaImageHide;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG), dlg->crtIMGid, para.operate-1, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i = 0; i<targetList.size();i++){
		int id = targetList[targetList.size() - 1 - i];
		dlg->bar.setInfo(L"��������"+GetTail(StrToCStr(dlg->no.entry[id].comment))+L"������", i);
		IMGobject oldIO, newIO;
		if(!dlg->no.IMGextract(id, oldIO)){
			continue;
		}
		IMGobject::makeEmpty(newIO, oldIO.indexCount);
		dlg->no.IMGreplace(id, newIO);
	}
	dlg->bar.hide();
	dlg->updateIMGlist();
	dlg->updateInfo();
	dlg->processing = 0;
	return 0U;
}

void CExRabbitDlg::OnMenuImageTransform(){
	// TODO: ���ת���汾
	ModalTransform dlg;
	dlg.in.contextIO = &io;
	dlg.in.contextColorList = cl;
	dlg.in.currentFrame = crtPICid;
	dlg.in.currentPalette = GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel();
	if(IDOK == dlg.DoModal()){
		ParaImageTransform = dlg.out;
		AfxBeginThread(ThreadImageTransform, this);
	}
}

UINT CExRabbitDlg::ThreadImageTransform(void*context){
	CExRabbitDlg*dlg=(CExRabbitDlg*)context;
	ModalTransform::OUTPUT para = dlg->ParaImageTransform;
	dlg->processing = 1;
	std::vector<int> targetList;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG), dlg->crtIMGid, para.target-1, targetList);
	dlg->bar.show(targetList.size()-1);
	for(int i = 0; i<targetList.size();i++){
		int id = targetList[targetList.size() - 1 - i];
		dlg->bar.setInfo(L"����ת��"+GetTail(StrToCStr(dlg->no.entry[id].comment))+L"������", i);
		std::vector<IMGobject> ioOutList;
		IMGobject ioIn;
		if(!dlg->no.IMGextract(id, ioIn)){
			continue;
		}
		switch(para.version){
		case V2:
			ioIn.convertToV2(ioOutList, para.outputFormat);
			break;
		case V4:
			ioIn.convertToV4(ioOutList, para.useColorPalette[0], !para.useNewPalette);
			break;
		case V5:
			ioIn.convertToV5(ioOutList, para.outputFormat, para.useColorPalette[0], para.makeTexture);
			break;
		case V6:
			ioIn.convertToV6(ioOutList, para.useColorPalette, !para.useNewPalette);
			break;
		}
		for(int p = 0;p<ioOutList.size();p++){
			if(p == 0){
				dlg->no.IMGreplace(id, ioOutList[p]);
				GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, dlg->getIconIMG(para.version),0,0,0);
			}else{
				str newName = KoishiAvatar::imgAddV4Num(dlg->no.entry[id].comment, p);
				dlg->no.IMGinsert(id + p, ioOutList[p], newName);
				GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(id+p, GetTail(StrToCStr(newName)),dlg->getIconIMG(para.version));
			}
		}
	}
	dlg->bar.hide();
	dlg->io.release();
	dlg->no.IMGextract(dlg->crtIMGid, dlg->io);
	dlg->switchIMGver(dlg->io.version);
	dlg->updatePIClist();
	dlg->updateTEXlist();
	if(para.version == V4 || para.version == V5 || para.version == V6){
		GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(0);
		dlg->updateColorTable();
	}
	dlg->updateInfo();
	dlg->processing = 0;
	return 0U;
}

void CExRabbitDlg::OnMenuImageChooseAll(){
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetCheck(i, TRUE);
}

void CExRabbitDlg::OnMenuImageChooseHighline(){
	for(int i=0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount(); i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetCheck(i,TRUE);
}

void CExRabbitDlg::OnMenuImageChooseReverse(){
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetCheck(i, 1-GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetCheck(i));
}

void CExRabbitDlg::OnMenuImageMoveUp(){
	int row = crtIMGid;
	CHECK_VALID(row>=1);
	NPKentry ne = no.entry[row];
	no.entry[row] = no.entry[row - 1];
	no.entry[row - 1] = ne;
	for(int i = 0;i<=1;i++){
		int id = row - i;
		int li = no.checkLink(id);
		if(li == id){
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)));
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconIMG((IMGversion)no.IMGgetVersion(id)),0,0,0);
		}else{
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)
				+ L"["+GetTail(StrToCStr(no.entry[li].comment))+L"]"));
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, 1, 0,0,0);
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(row - 1);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(row - 1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(row ,0, LVIS_SELECTED|LVIS_FOCUSED);
	crtIMGid = row - 1;
	updateInfo();
}

void CExRabbitDlg::OnMenuImageMoveDown(){
	int row = crtIMGid;
	CHECK_VALID(row>=0);
	CHECK_VALID(row<no.count);
	NPKentry ne = no.entry[row];
	no.entry[row] = no.entry[row + 1];
	no.entry[row + 1] = ne;
	for(int i = 0;i<=1;i++){
		int id = row + i;
		int li = no.checkLink(id);
		if(li == id){
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)));
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconIMG((IMGversion)no.IMGgetVersion(id)),0,0,0);
		}else{
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(id, 0, GetTail(StrToCStr(no.entry[id].comment)
				+ L"["+GetTail(StrToCStr(no.entry[li].comment))+L"]"));
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, 1, 0,0,0);
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(row + 1);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(row + 1,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(row ,0, LVIS_SELECTED|LVIS_FOCUSED);
	crtIMGid = row + 1;
	updateInfo();
}

void CExRabbitDlg::OnMenuImageAutoSort(){
	// TODO: �ڴ���������������
	AfxBeginThread(ThreadImageAutoSort, this);
}

UINT CExRabbitDlg::ThreadImageAutoSort(void*context){
	CExRabbitDlg *dlg = (CExRabbitDlg *)context;
	int i,j;
	queue wList1, wList2, qList;
	std::vector<NPKentry> oldEntry = dlg->no.entry;
	//����ÿ��������Ȩ��
	for(i=0;i<dlg->no.count;i++){
		avatar av;
		avatarLayer al = ALAYER_UD;
		parseAvatarName(KoishiAvatar::shorten(dlg->no.entry[i].comment), av, al);
		//����WEIGHT
		int weight = 0;
		for(j=0;j<TOTAL_LAYER_COUNT;j++){
			avatarPart pt;
			avatarLayer ly;
			getMQData(j, pt, ly);
			if(av.part == pt && ly == al){
				weight = TOTAL_LAYER_COUNT - 1 - j;
				break;
			}
		}
		wList1.push_back(weight);
	}
	//��������
	for(i = 0;i<wList1.size();i++){
		j = 0;
		while(j<wList2.size()){
			if(wList1[i] < wList2[j]){
				j ++;
			}else{
				break;
			}
		}
		if(j < wList2.size()){
			wList2.insert(wList2.begin() + j, wList1[i]);
			qList.insert(qList.begin() + j, i);
		}else{
			wList2.push_back(wList1[i]);
			qList.push_back(i);
		}
	}
	for(i = 0;i<qList.size();i++)
		dlg->no.entry[i] = oldEntry[qList[qList.size() - 1 - i]];
	dlg->updateIMGlist();
	dlg->updateInfo();
	return 0;
}

void CExRabbitDlg::OnMenuImageMix(){
	// TODO: �ڴ���������������
	AfxBeginThread(threadMix, this);
}


void CExRabbitDlg::OnMenuImageSetCompare(){
	CHECK_VALID(crtIMGid >= 0);
	ioComp.release();
	no.IMGextract(crtIMGid, ioComp);
	MessageBox(L"���趨�Ա�IMG��",L"��ʾ��");
	drawPara.compareMode = true;
	changeToolButtonStatus();
}



void CExRabbitDlg::OnToolAvatar(){
	MOVEW(toolAvatar);
	toolAvatar.ShowWindow(SW_SHOW);
	toolAvatar.changeThumbnailSize(profile.avatarThumbSize);
}


void CExRabbitDlg::OnToolNpkDict(){
	MOVEW(toolDict);
	toolDict.ShowWindow(SW_SHOW);
	toolDict.contentDir = profile.getSupportPath();
	toolDict.resourceDir = profile.getNPKdictPath();
}


void CExRabbitDlg::OnToolImgSearch(){
	MOVEW(toolIMGSearch);
	toolIMGSearch.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnToolDownload(){
	MOVEW(toolSPK);
	toolSPK.localAddr = profile.getDownloadPath();
	toolSPK.OnCbnSelchangeCombo2();
	toolSPK.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnToolForceExtract(){
	MOVEW(toolForceEx);
	toolForceEx.ShowWindow(SW_SHOW);
	toolForceEx.m_pProc.SetRange32(0,100);
}

void CExRabbitDlg::OnToolOpenOutputFolder(){
	ShellExecute(NULL, L"open", profile.getOutputPath(), NULL, NULL, SW_SHOWNORMAL);
}


void CExRabbitDlg::OnDrawColorTable(){
	drawPara.showPalette = !drawPara.showPalette;
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawCanvas(){
	drawPara.showCanvas = !drawPara.showCanvas;
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawAxis(){
	drawPara.showAxis = !drawPara.showAxis;
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawBound(){
	drawPara.showBound = !drawPara.showBound;
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawSetCompare1(){
	MessageBox(L"���Ҽ����IMG�б��е�һ��IMG��Ȼ��ѡ������Ϊ�Ա�IMG������������������", L"��ʾ��");
}


void CExRabbitDlg::OnDrawSetCompare2(){
	// TODO: �ڴ���������������
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		ioComp.release();
		if(ioComp.loadFile(CStrToStr(fileName))){
			MessageBox(L"�����������");
		}else{
			MessageBox(L"��ȡʧ������");
			return;
		}
	}
	drawPara.compareMode = true;
	changeToolButtonStatus();
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawCompareEnabled(){
	if(ioComp.version == 0){
		if(IDYES == MessageBox(L"��û�����öԱ�IMG��Ҫ��������",L"��ʾ��", MB_YESNO)){
			OnDrawSetCompare2();
		}
		return;
	}
	drawPara.compareMode = true;
	changeToolButtonStatus();
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawCompareDisabled(){
	drawPara.compareMode = false;
	changeToolButtonStatus();
	if(!playing)
		draw();
}



void CExRabbitDlg::OnToolsNpkLock(){
	ModalLock ml;
	ml.DoModal();
}



void CExRabbitDlg::OnMenuColorTableClassical(){
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
			setDefaultColor();
			cl = colorOperatePara.v2Color;
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			for(int i = 0;i<cl.size();i++)
				io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			saveAlert = true;
			draw();
		}
	}else{
		setDefaultColor();
		cl = colorOperatePara.v2Color;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTable16(){
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
			cl = palette::palette16();
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			for(int i = 0;i<cl.size();i++)
				io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			saveAlert = true;
			draw();
		}
	}else{
		colorOperatePara.v2Color = palette::palette16();
		cl = colorOperatePara.v2Color;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTable256()
{
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
			cl = palette::palette256();
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			for(int i = 0;i<cl.size();i++)
				io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			saveAlert = true;
			draw();
		}
	}else{
		colorOperatePara.v2Color = palette::palette256();
		cl = colorOperatePara.v2Color;
	}
	//int p = 1/0;
	//MessageBox(L"123");
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableExtractCurrent()
{
	// TODO: �ڴ���������������
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
			AfxBeginThread(pickColorFrame, this);
		}
	}else{
		AfxBeginThread(pickColorFrame, this);
	}
}


void CExRabbitDlg::OnMenuColorTableExtractAllFrame()
{
	// TODO: �ڴ���������������
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
			AfxBeginThread(pickColorImage, this);
		}
	}else{
		AfxBeginThread(pickColorImage, this);
	}
}


UINT CExRabbitDlg::pickColorFrame(void*context){
	CExRabbitDlg*dlg = (CExRabbitDlg*)context;
	IMGobject *ptrIO = &(dlg->io);
	matrix mat;
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	if(!ptrIO->PICextract(dlg->crtPICid, mat, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel())){
		dlg->MessageBox(L"������ǰͼƬʧ������",L"��ʾ��");
		return 0U;
	}
	dlg->bar.show(100);
	dlg->bar.setInfo(L"������ȡ��ɫ������", 0);
	for(int i = 0;i<mat.getElemCount();i++){
		color clr = mat.getElem(i);
		long clrPos = pal.findColor(clr,0);
		if(clrPos == -1){
			pal[0].push_back(clr);
			clrCount.push_back(1);
		}else{
			clrCount[clrPos] ++;
		}
	}
	clrList = pal[0];
	long finalColorCount = MIN(0xFE, pal.getColorCount(0));
	colorList finalColorList;
	dlg->bar.show(finalColorCount);
	for(int i = 0;i<finalColorCount; i++){
		dlg->bar.setInfo(L"���ڷ�����ɫ������", i);
		long maxCount = 0;
		long maxID = -1;
		for(int j = 0;j<clrCount.size();j++){
			if(clrCount[j] > maxCount){
				maxCount =clrCount[j];
				maxID = j;
			}
		}
		finalColorList.push_back(clrList[maxID]);
		clrList.erase(clrList.begin() + maxID);
		clrCount.erase(clrCount.begin() + maxID);
	}
	dlg->bar.setInfo(L"�������ɵ�ɫ��������", finalColorCount);
	if(dlg->io.version == V4 || dlg->io.version == V5 || dlg->io.version == V6){
		dlg->cl = KoishiImageTool::nearbySort(finalColorList);
		dlg->cl.insert(dlg->cl.begin(), color(0,0,0,0));
		while(dlg->io.CLRremove(0,  GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
		for(int i = 0;i<dlg->cl.size();i++)
			dlg->io.CLRpush(dlg->cl[i], GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			dlg->saveAlert = true;
			dlg->draw();

	}else{
		dlg->cl = KoishiImageTool::nearbySort(finalColorList);
		dlg->cl.insert(dlg->cl.begin(), color(0,0,0,0));
		dlg->colorOperatePara.v2Color = dlg->cl;
	}
	dlg->updateColorTable();
	dlg->bar.hide();
	return 0U;
}
UINT CExRabbitDlg::pickColorImage(void*context){
	CExRabbitDlg*dlg = (CExRabbitDlg*)context;
	IMGobject *ptrIO = &(dlg->io);
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	dlg->bar.show(ptrIO->indexCount);
	for(long getFrame = 0;getFrame<ptrIO->indexCount;getFrame ++){
		dlg->bar.setInfo(L"������ȡ��"+NumToCStr(getFrame+1)+L"֡����ɫ������", getFrame);
		matrix mat;
		if(!ptrIO->PICextract(getFrame, mat, GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel())){
			continue;
		}
		for(int i = 0;i<mat.getElemCount();i++){
			color clr = mat.getElem(i);
			long clrPos = pal.findColor(clr,0);
			if(clrPos == -1){
				pal[0].push_back(clr);
				clrCount.push_back(1);
			}else{
				clrCount[clrPos] ++;
			}
		}
		mat.destory();
	}
	clrList = pal[0];
	long finalColorCount = MIN(0xFE, pal.getColorCount(0));
	colorList finalColorList;
	dlg->bar.show(finalColorCount);
	for(int i = 0;i<finalColorCount; i++){
		dlg->bar.setInfo(L"���ڷ�����ɫ������", i);
		long maxCount = 0;
		long maxID = -1;
		for(int j = 0;j<clrCount.size();j++){
			if(clrCount[j] > maxCount){
				maxCount =clrCount[j];
				maxID = j;
			}
		}
		finalColorList.push_back(clrList[maxID]);
		clrList.erase(clrList.begin() + maxID);
		clrCount.erase(clrCount.begin() + maxID);
	}
	dlg->bar.setInfo(L"�������ɵ�ɫ��������", finalColorCount);
	if(dlg->io.version == V4 || dlg->io.version == V5 || dlg->io.version == V6){
		dlg->cl = KoishiImageTool::nearbySort(finalColorList);
		dlg->cl.insert(dlg->cl.begin(), color(0,0,0,0));
		while(dlg->io.CLRremove(0,  GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
		for(int i = 0;i<dlg->cl.size();i++)
			dlg->io.CLRpush(dlg->cl[i], GET_DLG_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			dlg->saveAlert = true;
			dlg->draw();
	}else{
		dlg->cl = KoishiImageTool::nearbySort(finalColorList);
		dlg->cl.insert(dlg->cl.begin(), color(0,0,0,0));
		dlg->colorOperatePara.v2Color = dlg->cl;
	}
	dlg->updateColorTable();
	dlg->bar.hide();
	return 0U;
}
BOOL CExRabbitDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	if(pMsg->message==WM_MOUSEMOVE){
		m_ttc.RelayEvent(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

