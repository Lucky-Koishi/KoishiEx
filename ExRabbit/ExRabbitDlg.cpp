
// ExRabbitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "afxdialogex.h"
#include "Tinysetbrush.h"
#include "TinyClipBoard.h"
#include "TinySetName.h"
#include "TinyIMGSelect.h"
#include "AdjustColorDlg.h"
#include "TinyAddMark.h"
#include "ModalLock.h"
#include "ModalLockInput.h"
#include "ModalConflictWarning.h"
#include <locale.h>
#include <thread>
#include "ToolAvatarMark.h"
#include "ToolAvatarLocalizer.h"
#include "ToolAvatarCharacterSelection.h"
#include "ToolStat.h"
#include "ModalAdvancedMix.h"
#include "ModalSaveWarning.h"

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
#define TIC TRUE
#define TOC TRUE
#endif

CExRabbitDlg::CExRabbitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExRabbitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAIN);

	profile.loadProfile();
	width = 1210;
	height = 650;
	drawPara.texture = FALSE;
	drawPara.showPalette = TRUE;
	drawPara.showAxis = TRUE;
	drawPara.showCanvas = TRUE;
	drawPara.showBound = TRUE;
	drawPara.indexMode = FALSE;
	drawPara.entireTextureMode = FALSE;
	drawPara.compareMode = FALSE;
	drawPara.mixMode = LAY;
	drawPara.zoom = 0;
	drawPara.zoomRate = 1.00;
	canvasOperatePara.canvasOperating = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_SHOW;
	canvasOperatePara.currentCursor = CANVAS_SHOW;
	canvasOperatePara.canvasPara = CANVAS_DEFAULT;
	canvasOperatePara.brushShape = 1;		
	canvasOperatePara.brushSize = 5;
	canvasOperatePara.oldMatrixEnable = FALSE;
	fileNPKname = L"newNPK.npk";
	fileIMGname = L"newIMG.img";
	
	setDefaultColor();
	colorOperatePara.current = 1;
	colorOperatePara.tolerance = 10;
	for(int i = 0;i<256;i++){
		colorOperatePara.isChosen[i] = FALSE;
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
	NPKsaveAlert = FALSE;
	IMGsaveAlert = FALSE;
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
	/*ON_COMMAND(ID_MENU_IMAGE_SAVE, &CExRabbitDlg::OnMenuImageSave)
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
	ON_COMMAND(ID_MENU_IMAGE_INSERT2, &CExRabbitDlg::OnMenuImageInsert2)*/
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
	ON_COMMAND(ID_TOOLS_NPK_LOCK, &CExRabbitDlg::OnToolsNpkLock)
	ON_COMMAND(ID_MENU_PICTURE_GET_GIF, &CExRabbitDlg::OnMenuPictureGetGIF)
	ON_COMMAND(ID_MENU_COLOR_TABLE_CLASSICAL, &CExRabbitDlg::OnMenuColorTableClassical)
	ON_COMMAND(ID_MENU_COLOR_TABLE_16, &CExRabbitDlg::OnMenuColorTable16)
	ON_COMMAND(ID_MENU_COLOR_TABLE_256, &CExRabbitDlg::OnMenuColorTable256)
	ON_COMMAND(ID_MENU_COLOR_TABLE_EXTRACT_CURRENT, &CExRabbitDlg::OnMenuColorTableExtractCurrent)
	ON_COMMAND(ID_MENU_COLOR_TABLE_EXTRACT_ALL_FRAME, &CExRabbitDlg::OnMenuColorTableExtractAllFrame)
	ON_COMMAND(ID_TOOLS_PATCH_OPERATE, &CExRabbitDlg::OnToolsPatchOperate)
	ON_COMMAND(ID_TOOLS_AVATAR_MARK, &CExRabbitDlg::OnToolsAvatarMark)
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENU_IMAGE_INERT_EMPTY, &CExRabbitDlg::OnMenuImageInertEmpty)
	ON_COMMAND(ID_MENU_IMAGE_INERT_IMG, &CExRabbitDlg::OnMenuImageInertIMG)
	ON_COMMAND(ID_MENU_IMAGE_INERT_NPK, &CExRabbitDlg::OnMenuImageInertNPK)
	ON_COMMAND(ID_MENU_IMAGE_INERT_FOLDER, &CExRabbitDlg::OnMenuImageInertFolder)
	ON_COMMAND(ID_MENU_IMAGE_INERT_OTHER, &CExRabbitDlg::OnMenuImageInertOther)
	ON_COMMAND(ID_MENU_IMAGE_REPLACE_IMG, &CExRabbitDlg::OnMenuImageReplaceIMG)
	ON_COMMAND(ID_MENU_IMAGE_REPLACE_COPY, &CExRabbitDlg::OnMenuImageReplaceCopy)
	ON_COMMAND(ID_MENU_IMAGE_REPLACE_QUOTE, &CExRabbitDlg::OnMenuImageReplaceQuote)
	ON_COMMAND(ID_MENU_IMAGE_REPLACE_IMG_PATCH, &CExRabbitDlg::OnMenuImageReplaceImgPatch)
	ON_COMMAND(ID_MENU_IMAGE_REPLACE_COPY_PATCH, &CExRabbitDlg::OnMenuImageReplaceCopyPatch)
	ON_COMMAND(ID_MENU_IMAGE_REPLACE_QUOTE_PATCH, &CExRabbitDlg::OnMenuImageReplaceQuotePatch)
	ON_COMMAND(ID_MENU_IMAGE_REMOVE, &CExRabbitDlg::OnMenuImageRemove)
	ON_COMMAND(ID_MENU_IMAGE_REMOVE_PATCH, &CExRabbitDlg::OnMenuImageRemovePatch)
	ON_COMMAND(ID_MENU_IMAGE_EXTRACT, &CExRabbitDlg::OnMenuImageExtract)
	ON_COMMAND(ID_MENU_IMAGE_EXTRACT_PATCH, &CExRabbitDlg::OnMenuImageExtractPatch)
	ON_COMMAND(ID_MENU_IMAGE_SAVE, &CExRabbitDlg::OnMenuImageSave)
	ON_COMMAND(ID_MENU_IMAGE_SAVE_NPK, &CExRabbitDlg::OnMenuImageSaveNPK)
	ON_COMMAND(ID_MENU_IMAGE_SAVE_NPK_PATCH, &CExRabbitDlg::OnMenuImageSaveNPKPatch)
	ON_COMMAND(ID_MENU_IMAGE_COPY_RESOURCE, &CExRabbitDlg::OnMenuImageCopyResource)
	ON_COMMAND(ID_MENU_IMAGE_COPY_QUOTE, &CExRabbitDlg::OnMenuImageCopyQuote)
	ON_COMMAND(ID_MENU_IMAGE_RENAME, &CExRabbitDlg::OnMenuImageRename)
	ON_COMMAND(ID_MENU_IMAGE_DEQUOTE, &CExRabbitDlg::OnMenuImageDequote)
	ON_COMMAND(ID_MENU_IMAGE_DEQUOTE_PATCH, &CExRabbitDlg::OnMenuImageDequotePatch)
	ON_COMMAND(ID_MENU_IMAGE_TRANSFORM_TO2, &CExRabbitDlg::OnMenuImageTransformTo2)
	ON_COMMAND(ID_MENU_IMAGE_TRANSFORM_TO4, &CExRabbitDlg::OnMenuImageTransformTo4)
	ON_COMMAND(ID_MENU_IMAGE_TRANSFORM__TO2_PATCH, &CExRabbitDlg::OnMenuImageTransformTo2Patch)
	ON_COMMAND(ID_MENU_IMAGE_TRANSFORM_TO4_PATCH, &CExRabbitDlg::OnMenuImageTransformTo4Patch)
	ON_COMMAND(ID_MENU_IMAGE_TRANSFORM_ADVANCED, &CExRabbitDlg::OnMenuImageTransformAdvanced)
	ON_COMMAND(ID_MENU_IMAGE_HIDE, &CExRabbitDlg::OnMenuImageHide)
	ON_COMMAND(ID_MENU_IMAGE_HIDE_CONTENT, &CExRabbitDlg::OnMenuImageHideContent)
	ON_COMMAND(ID_MENU_IMAGE_HIDE_PATCH, &CExRabbitDlg::OnMenuImageHidePatch)
	ON_COMMAND(ID_MENU_IMAGE_HIDE_CONTENT_PATCH, &CExRabbitDlg::OnMenuImageHideContentPatch)
	ON_COMMAND(ID_MENU_IMAGE_CLIPBOARD_COPY, &CExRabbitDlg::OnMenuImageClipboardCopy)
	ON_COMMAND(ID_MENU_IMAGE_CLIPBOARD_INSERT, &CExRabbitDlg::OnMenuImageClipboardInsert)
	ON_COMMAND(ID_MENU_IMAGE_CLIPBOARD_REPLACE, &CExRabbitDlg::OnMenuImageClipboardReplace)
	ON_COMMAND(ID_MENU_IMAGE_SET_COMPARE, &CExRabbitDlg::OnMenuImageSetCompare)
	ON_COMMAND(ID_MENU_IMAGE_SELECT_ALL, &CExRabbitDlg::OnMenuImageSelectAll)
	ON_COMMAND(ID_MENU_IMAGE_SELECT_REVERSE, &CExRabbitDlg::OnMenuImageSelectReverse)
	ON_COMMAND(ID_MENU_IMAGE_SELECT_HIGHLINE, &CExRabbitDlg::OnMenuImageSelectHighline)
	ON_COMMAND(ID_MENU_IMAGE_MOVE_UP, &CExRabbitDlg::OnMenuImageMoveUp)
	ON_COMMAND(ID_MENU_IMAGE_MOVE_DOWN, &CExRabbitDlg::OnMenuImageMoveDown)
	ON_COMMAND(ID_MENU_IMAGE_MIX, &CExRabbitDlg::OnMenuImageMix)
	ON_COMMAND(ID_MENU_IMAGE_MIX_ADVANCED, &CExRabbitDlg::OnMenuImageMixAdvanced)
	ON_COMMAND(ID_MENU_IMAGE_AUTO_SORT, &CExRabbitDlg::OnMenuImageAutoSort)
	ON_COMMAND(ID_MENU_IMAGE_INERT_EMPTY_BLANK, &CExRabbitDlg::OnMenuImageInertEmptyBlank)
	ON_COMMAND(ID_MENU_IMAGE_INERT_IMG_BLANK, &CExRabbitDlg::OnMenuImageInertIMGBlank)
	ON_COMMAND(ID_MENU_IMAGE_INERT_NPK_BLANK, &CExRabbitDlg::OnMenuImageInertNPKBlank)
	ON_COMMAND(ID_MENU_IMAGE_INERT_FOLDER_BLANK, &CExRabbitDlg::OnMenuImageInertFolderBlank)
	ON_COMMAND(ID_MENU_IMAGE_INERT_OTHER_BLANK, &CExRabbitDlg::OnMenuImageInertOtherBlank)
	ON_COMMAND(ID_TOOLS_STAT, &CExRabbitDlg::OnToolsStat)
	END_MESSAGE_MAP()
/////////

// CExRabbitDlg 消息处理程序

BOOL CExRabbitDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	//设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// TODO: 在此添加额外的初始化代码
	//////////////////////////////////
	SetWindowText(_T(VERSION_STR));
	SetWindowPos(NULL,0,0,width,height,SWP_NOZORDER|SWP_NOMOVE);
	CRect rc;
	GetClientRect(rc);
	adjustWindow(rc.Width(), rc.Height());
	// 控件大小调整
	CREATEW(dNewFile,IDD_NEW_DIALOG);

	CREATEW(bar, IDD_TINY_PROGRESSBAR);
	CREATEW(toolIMGSearch,IDD_TOOL_IMGSEARCH);
	CREATEW(toolAvatar,IDD_TOOL_AVATAR);
	toolAvatar.context = this;
	CREATEW(toolDict,IDD_TOOL_DICT);
	CREATEW(toolForceEx, IDD_TOOL_FORCEEXTRACT);
	

	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->EasyInsertColumn(L"IMG名,200");
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(L"这里显示NPK文件的信息");
	GET_CTRL(CEdit, IDC_EDIT_IMGINFO)->SetWindowText(L"这里显示IMG文件的信息");
	switchIMGver(V2);
	
	StartThreadFunc(Play, nullptr);
	StartThreadFunc(Lazy, nullptr);

	ioComp.create(V2);
	noClip.create();

	i_lIMG.Create(16,16, TRUE|ILC_COLOR24, 10, 1);
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_NUL));		//0号资源·无效
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_LINK));		//1号资源·LINK
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_UNKNOWN));	//2号资源
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON_AUDIO));		//3号资源
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON1));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON2));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON3));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON4));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON5));
	i_lIMG.Add(AfxGetApp()->LoadIconW(IDI_ICON6));
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetImageList(&i_lIMG, LVSIL_SMALL);

	i_lPIC.Create(16,16, TRUE|ILC_COLOR24, 10, 1);
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON9));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON1));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON2));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON3));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON4));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON5));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON6));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON7));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON8));
	i_lPIC.Add(AfxGetApp()->LoadIconW(IDI_PIC_ICON10));
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
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON1), L"显示选项");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON2), L"索引模式");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON3), L"全帧显示");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON4), L"IMG对比模式");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON5), L"播放");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON6), L"拖动画布");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON7), L"缩放");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON8), L"移动坐标");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON9), L"扩充裁切");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON10), L"画刷");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON11), L"直线");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON12), L"矩形");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON13), L"画擦");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON14), L"取色");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON15), L"添加标记");
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
		dc.FillSolidRect(rect,profile.mainColor); 
#endif
		CDialogEx::OnPaint();
		TRACE("1\n");
		draw(drawPara.texture);
		updateColorTable();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExRabbitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CExRabbitDlg::adjustWindow(int w, int h){
	//调整窗口控件
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
	//切换版本界面
	///////////////////////////////
	int i;
	if(ver == VUDEF) {
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EnableWindow(FALSE);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->EnableWindow(FALSE);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->EnableWindow(FALSE);
	} else {
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EnableWindow(TRUE);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->EnableWindow(TRUE);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->EnableWindow(TRUE);
	}
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
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertColumn(L"帧号,64,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
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
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertColumn(L"帧号,64,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80,使用纹理集,400");
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->EasyInsertColumn(L"纹理集,64,颜色格式,90,尺寸,80");
		//GET_CTRL(CGoodListCtrl, IDC_LIST_CLR)->EasyInsertColumn(L"色号,64,RGBA数据,70");
		break;
	case V6:
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetWindowPos(NULL,170,150,350,height-270,SWP_NOZORDER);
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->ShowWindow(SW_HIDE);
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->ShowWindow(SW_SHOW);
		GET_CTRL(CButton, IDC_BUTTON_PALETTE)->ShowWindow(SW_SHOW);
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertColumn(L"帧号,64,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
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
	// 更新IMG列表
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
void CExRabbitDlg::updateIMGterm(int pos) {
	int li = no.checkLink(pos);
	if(li == pos) {
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(pos, 0, LVIF_IMAGE, NULL, getIconIMG((IMGversion)no.IMGgetVersion(pos)), 0, 0, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(pos, 0, GetTail(StrToCStr(no.entry[pos].comment)));
	} else {
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(pos, 0, LVIF_IMAGE, NULL, 1, 0, 0, 0);
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(pos, 0, GetTail(StrToCStr(no.entry[pos].comment)) + L"[" + GetTail(StrToCStr(no.entry[li].comment)) + L"]");
	}
}
void CExRabbitDlg::updatePIClist(){
	// 更新帧列表
	////////////////////////////////
	CString cstr;
	int currentCount = GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();
	int i = 0;
	while(TRUE){
		if(i < io.indexCount){
			if(i < currentCount){
				updatePICterm(i);
			}else{
				cstr = NumToCStr(i) + L",";
				cstr += FmtToCStr(io.PICcontent[i], io.version);
				if(io.PICcontent[i].format == LINK)
					cstr += NumToCStr(io.PICcontent[i].linkTo);
				cstr += L",";
				cstr += PtToCStr(io.PICcontent[i].basePt) + L",";
				cstr += SzToCStr(io.PICcontent[i].picSize)+L",";
				cstr += SzToCStr(io.PICcontent[i].frmSize)+L",";
				if(io.version == V5){
					cstr += L"纹理集"+NumToCStr(io.PICcontent[i].TEXusing)+L":"+PtToCStr(io.PICcontent[i].TEXpointLT)+L"-"+PtToCStr(io.PICcontent[i].TEXpointRB);
				}
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->EasyInsertItem(cstr,getIconPIC(io.PICcontent[i]));
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
	//只更新pos
	CHECK_VALID(pos>=0);
	CHECK_VALID(pos<io.indexCount);
	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItem(pos,0,LVIF_IMAGE,NULL,getIconPIC(io.PICcontent[pos]),0,0,0);
	if(io.PICcontent[pos].format == LINK){
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 0, NumToCStr(pos));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 1, FmtToCStr(io.PICcontent[pos], io.version) + NumToCStr(io.PICcontent[pos].linkTo));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 2, L"");
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 3, L"");
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 4, L"");
		if(io.version == V5){
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 5, L"");
		}
	}else{
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 0, NumToCStr(pos));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 1, FmtToCStr(io.PICcontent[pos], io.version));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 2, PtToCStr(io.PICcontent[pos].basePt));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 3, SzToCStr(io.PICcontent[pos].picSize));
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 4, SzToCStr(io.PICcontent[pos].frmSize));
		if(io.version == V5){
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(pos, 5, L"纹理集"+NumToCStr(io.PICcontent[pos].TEXusing)+L":"+PtToCStr(io.PICcontent[pos].TEXpointLT)+L"-"+PtToCStr(io.PICcontent[pos].TEXpointRB));
		}
	}
}
void CExRabbitDlg::updateTEXlist(){
	//更新纹理集列表
	////////////////////////////////
	CString cstr;
	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->DeleteAllItems();
	for(int i=0;i<io.TEXcontent.size();i++){
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += FmtToCStr((colorFormat)(int)io.TEXcontent[i].format,V5)+L",";
		cstr += NumToCStr(io.TEXcontent[i].width)+L"×";
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
	StartThreadFunc(DrawColor, nullptr);
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

void CExRabbitDlg::updateInfo(){
	//更新两个信息栏
	////////////////////////////////
	//NPK 
	CString cstr;
	cstr = L"文件名："+GetTail(fileNPKname)+L"\r\n";
	cstr += L"大小："+NumToCStr(no.getSize())+L"字节\r\n";
	cstr += L"条目数："+NumToCStr(no.count);
	cstr += (crtIMGid  == -1) ? L"" : ( L"/"  + NumToCStr(crtIMGid));
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(cstr);

	cstr = IMGsaveAlert ? L"IMG状态：已变动\r\n" : L"IMG状态：未变动\r\n";
	cstr += L"版本:"+NumToCStr(io.version)+L"\r\n";
	cstr += L"帧数:"+NumToCStr(io.indexCount);
	cstr += (crtPICid == -1) ? L"\r\n": (  L"/" + NumToCStr(crtPICid)+L"\r\n");
	switch(io.version){
	case V4:
		cstr += L"调色板颜色项:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V5:
		cstr += L"纹理集数:"+NumToCStr(io.TEXcontent.size());
		cstr += (crtTEXid == -1) ? L"\r\n": (  L"/" + NumToCStr(crtTEXid)+L"\r\n");
		cstr += L"调色板颜色项:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V6:
		cstr += L"调色板方案数:"+NumToCStr(io.paletteData.getCount());
		if(GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel() >= 0){
			cstr += L"/"+NumToCStr(io.paletteData[GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()].size())+L"\r\n";
		}
		break;
	}
	GET_CTRL(CEdit, IDC_EDIT_IMGINFO)->SetWindowText(cstr);
}
void CExRabbitDlg::updateModified() {
	IMGsaveAlert = TRUE;
	NPKsaveAlert = TRUE;
	updateInfo();
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
    GetCursorPos(&myPoint); //鼠标位置
	ScreenToClient(&myPoint);
	return myPoint;
}
void CExRabbitDlg::updateCursorInfo(){
	//更新指针坐标与颜色
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
/**************主按钮事件************************/
//////////////////////////////////////////////////
void CExRabbitDlg::OnBnClickedButtonMenu()
{
	// TODO: 点击菜单按钮
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
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_TOOL);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}

void CExRabbitDlg::OnBnClickedButtonMenu3()
{
	// TODO: IMG改动
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(1);  
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
	playing = 0;
	////////////////////////////
	//切换IMG时提示保存
	if(IMGsaveAlert){
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_IMG;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			if(crtIMGid != row) {
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(crtIMGid, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
			}
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			IMGsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.IMGreplace(crtIMGid, io);
			IMGsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(row);
	if(row>=0){
		crtIMGid = row;
		fndIMGid = row;
		if(no.IMGgetVersion(row) == V1 && IDYES == MessageBox(L"这个IMG是V1喵，需要转化为V2喵？", L"提示喵", MB_YESNO)){
			KoishiExpand::IMGobjectV1 io1;
			stream s;
			no.extract(row, s);
			if(!io1.load(s)){
				MessageBox(L"转换失败喵！", L"提示喵");
				switchIMGver(VUDEF);
				return;
			}
			if(!io1.make(io)){
				MessageBox(L"转换失败喵！", L"提示喵");
				switchIMGver(VUDEF);
				return;
			}
			no.IMGreplace(row, io);
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(row, 0, LVIF_IMAGE, NULL, getIconIMG(V2),0,0,0);
		}else{
			io.release();
			if(!no.IMGextract(row, io)) {
				MessageBox(L"不是可以识别的IMG对象喵！");
				switchIMGver(VUDEF);
				return;
			}
		}
		fileIMGname = StrToCStr(no.entry[row].comment);
		switchIMGver(io.version);
		updatePIClist();
		updateTEXlist();
		updateColorTable();
	}
	updateInfo();
	canvasOperatePara.oldMatrixEnable = FALSE;
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击IMG列表呼出菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListImg(pNMHDR, pResult);
	/////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_IMAGE);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}

void CExRabbitDlg::OnNMClickListTex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 左键点击纹理集列表
	playing = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CHECK_VALID(pNMListView->iItem >= 0);
	crtTEXid = pNMListView->iItem;
	updateInfo();
	draw(TRUE);
	canvasOperatePara.oldMatrixEnable = FALSE;
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListTex(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击纹理集列表呼出菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListTex(pNMHDR, pResult);
	//////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_TEXTURE);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
	*pResult = 0;
}

void CExRabbitDlg::OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 左键点击帧列表
	playing = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CHECK_VALID(pNMListView->iItem >= 0);
	crtPICid = pNMListView->iItem;
	updateInfo();
	draw();
	canvasOperatePara.oldMatrixEnable = FALSE;
	*pResult = 0;
}

void CExRabbitDlg::OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击帧列表呼出菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListPic(pNMHDR, pResult);
	if(crtIMGid == -1){
		MessageBox(L"还没有选择IMG对象喵。",L"提示喵");
		return;
	}
	//////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_PICTURE);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}

void CExRabbitDlg::OnCbnSelchangeComboPro(){
	// TODO: 更改调色板
	CHECK_VALID(io.version == V6);
	int curSel = GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel();
	CHECK_VALID(curSel >= 0);
	cl = io.paletteData[curSel];
	updateColorTable();
	draw();
}

void CExRabbitDlg::draw(BOOL isDDS){
	//绘制
	StartThreadFunc(Draw, isDDS);
}


void CExRabbitDlg::OnOK()
{
	// TODO: 不能按回车
	MessageBox(L"不许按回车喵！",L"提示喵");
}

void CExRabbitDlg::OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	playing = 0;
	int row = GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//无关按键不响应
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
	if(IMGsaveAlert){
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_IMG;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			if(crtIMGid != row) {
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(crtIMGid, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
			}
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			IMGsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.IMGreplace(crtIMGid, io);
			IMGsaveAlert = FALSE;
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
	// TODO: 在此添加控件通知处理程序代码
	playing = 0;
	int row = GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//无关按键不响应
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
	// TODO: 在此添加控件通知处理程序代码
	playing = 0;
	int row = GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetSelectionMark();
	if(pLVKeyDow->wVKey != VK_UP && pLVKeyDow->wVKey != VK_DOWN){
		//无关按键不响应
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
	draw(TRUE);
	lazyTime = 5;
	*pResult = 0;
}

void CExRabbitDlg::OnDropFiles(HDROP hDropInfo)
{
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
		if(KoishiExpand::authorLock::checkLock(CStrToStr(fileName), "") == 0) {
			ModalLockInput dlg;
			dlg.fileCheckName = fileName;
			if(IDCANCEL == dlg.DoModal())
				return;
		}
		if(NPKsaveAlert) {
			ModalSaveWarning ms;
			ms.alertType = IMGsaveAlert ? ModalSaveWarning::MODIFIED_IMG_NPK : ModalSaveWarning::MODIFIED_NPK;
			ms.DoModal();
			switch(ms.returnType) {
			case ModalSaveWarning::RETURN_CANCEL:
				return;
			case ModalSaveWarning::RETURN_NO_SAVE:
				IMGsaveAlert = FALSE;
				NPKsaveAlert = FALSE;
				break;
			case ModalSaveWarning::RETURN_SAVE:
				no.saveFile(CStrToStr(fileNPKname));
				IMGsaveAlert = FALSE;
				NPKsaveAlert = FALSE;
				updateInfo();
				break;
			case ModalSaveWarning::RETURN_ALL_SAVE:
				no.IMGreplace(crtIMGid, io);
				no.saveFile(CStrToStr(fileNPKname));
				IMGsaveAlert = FALSE;
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
		updateIMGlist();
		if(no.count > 0) {
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(0);
			crtIMGid = 0;
		}
	} else if(fmt == L".IMG") {
		int success = 0;
		for(int i = 0; i<fileCount; i++) {
			if(i != 0) {
				memset(szPath, 0, MAX_PATH * sizeof(WCHAR));
				nChars = ::DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
				fileName = CString(szPath, nChars);
			}
			fmt = fileName.Right(4).MakeUpper();
			if(fmt == L".IMG") {
				IMGobject ioTemp;
				if(!ioTemp.loadFile(CStrToStr(fileName)))
					continue;
				CString path = Slashing(GetTail(fileName));
				no.IMGpush(ioTemp, CStrToStr(path));
				success++;
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount(), GetTail(path), getIconIMG(ioTemp.version));
				ioTemp.release();
			}
			updateInfo();
		}
		MessageBox(L"已添加了" + NumToCStr(success) + L"个IMG对象喵！", L"提示喵");
		NPKsaveAlert = TRUE;
	} else if(fmt == L".PNG") {
		IMGobject ioNew;
		ioNew.create(V2);
		if(crtIMGid == -1) {
			int id = no.count;
			no.IMGpush(ioNew, "new_img.img");
			io = ioNew;
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(id, L"new_img.img", getIconIMG(V2));
			crtIMGid = id;
		}
		int success = 0;
		for(int i = 0; i<fileCount; i++) {
			if(i != 0) {
				memset(szPath, 0, MAX_PATH * sizeof(WCHAR));
				nChars = ::DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
				fileName = CString(szPath, nChars);
			}
			fmt = fileName.Right(4).MakeUpper();
			if(fmt == L".PNG") {
				image imTemp;
				if(!loadPNG(imTemp, CStrToStr(fileName)))
					continue;
				if(imTemp.getElemCount() == 0)
					continue;
				stream sTemp;
				PICinfo pi;
				switch(io.version) {
				case V2:
					io.PICpreprocess(imTemp, sTemp, pi, ARGB8888);
					io.PICpush(pi, sTemp);
					break;
				case V4:
					io.PICpreprocess(imTemp, sTemp, pi, INDEX_FMT_PALETTE);
					io.PICpush(pi, sTemp);
					break;
				case V5:
					io.PICpreprocess(imTemp, sTemp, pi, ARGB8888);
					io.PICpush(pi, sTemp);
					break;
				case V6:
					io.PICpreprocess(imTemp, sTemp, pi, INDEX_FMT_PALETTE, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
					io.PICpush(pi, sTemp);
					break;
				default:
					MessageBox(L"未识别的IMG版本喵。");
					return;
				}
				success++;
				int itemCount = GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->InsertItem(itemCount, L"", getIconPIC(pi));
				updatePICterm(itemCount);
			}
		}
		MessageBox(L"已添加了" + NumToCStr(success) + L"个贴图喵！", L"提示喵");
		updateModified();
		if(crtPICid != -1) {
			draw();
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
int CExRabbitDlg::getIconPIC(const PICinfo &pi){
	int iconList[21] = {0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 3, 2, 1, 4, 6, 7, 8};
	if(io.version == V4 || io.version == V5 ||io.version == V6){
		if(pi.format == ARGB4444){
			return 9;
		}
		if(pi.format == ARGB1555){
			if(pi.comp == COMP_NONE && 2 * pi.picSize.area() == pi.dataSize){
				return iconList[ARGB1555 % 21];
			}
			return 5;
		}
	}
	return iconList[pi.format%21];
}
void CExRabbitDlg::getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected){
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
std::vector<int> CExRabbitDlg::getSelected(CGoodListCtrl *listCtrl) {
	std::vector<int> selected;
	for(int k = 0; k<listCtrl->GetItemCount(); k++)
		if(listCtrl->GetCheck(k))
			selected.push_back(k);
	return selected;
}
std::vector<int> CExRabbitDlg::getSelected(UINT listCtrlID, INT selectType) {
	std::vector<int> selected;
	CListCtrl *lc = GET_CTRL(CListCtrl, listCtrlID);
	switch(selectType) {
	case SINGLE_SELECT:
		if(listCtrlID == IDC_LIST_IMG)
			selected.push_back(crtIMGid);
		if(listCtrlID == IDC_LIST_PIC)
			selected.push_back(crtPICid);
		if(listCtrlID == IDC_LIST_DDS)
			selected.push_back(crtTEXid);
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
//////////////////////////////////////////////
/***********界面按钮处理事件*****************/
//////////////////////////////////////////////


void CExRabbitDlg::OnBnClickedButtonPalette()
{
	// TODO: 点击颜色调整
	BOOL selected = FALSE;
	for(int i = 0;i<cl.size();i++){
		if(colorOperatePara.isChosen[i]){
			selected = TRUE;
			break;
		}
	}
	if(!selected){
		MessageBox(L"没选定颜色喵。", L"提示喵");
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
	// TODO: 查询路径名
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
	MessageBox(L"没有找到路径名包含“"+str1+"”的IMG喵！",L"提示喵");
}
//////////////////////////////////////////////
/***********Main菜单处理事件*****************/
//////////////////////////////////////////////
void CExRabbitDlg::OnMain01()
{
	// TODO: 新建
	MOVEW(dNewFile);
	dNewFile.OnBnClickedCheck1();
	dNewFile.ShowWindow(SW_SHOW);
}
void CExRabbitDlg::OnMain02()
{
	// TODO: 打开
	CString defExt = _T("资源文件(*.NPK,*.IMG)|*.NPK;*.IMG");
	CString extFilter = _T("资源文件(*.NPK,*.IMG)|*.NPK;*.IMG|NPK文件(*.NPK)|*.NPK|IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
				MessageBox(L"读取失败喵！");
				return;
			}
			fileNPKname = fileName;
			IMGsaveAlert = FALSE;
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
					MessageBox(L"读取失败喵！", L"提示喵");
					return;
				}
				if(!io1.make(io)){
					MessageBox(L"读取失败喵！", L"提示喵");
					return;
				}
				if(IDNO== MessageBox(L"该IMG为旧版本(V1)，需要将其转化为V2才能打开。要这样做嘛？", L"提示喵", MB_YESNO)){
					return;
				}
			}
			no.release();
			no.create();
			fileIMGname = fileName;
			fileNPKname = L"newNPK.npk";
			IMGsaveAlert = FALSE;
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
	// TODO: 保存
	if(IMGsaveAlert){
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_IMG;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			IMGsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.IMGreplace(crtIMGid, io);
			IMGsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	str fn;
	CString fileName;
	fileName = fileNPKname;
	CStrToStr(fileName, fn);
	if(no.saveFile(fn)){
		NPKsaveAlert = FALSE;
	}else{
		MessageBox(_T("NPK保存失败喵！"),L"提示喵");
	}
}
void CExRabbitDlg::OnMain04()
{
	// TODO: 另存为
	if(IMGsaveAlert){
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_IMG;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			IMGsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.IMGreplace(crtIMGid, io);
			IMGsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(FALSE, defExt, GetTail(fileNPKname), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
void CExRabbitDlg::OnMain05(){
	// TODO: 设置
	ModalPreference dlg;
	dlg.modifiedProfile = profile;
	if(IDOK == dlg.DoModal()){
		profile = dlg.modifiedProfile;
		MessageBox(L"软件配置修改完毕喵。",L"提示喵");
		Invalidate();
	}
}
void CExRabbitDlg::OnMain06()
{
	// TODO: 关于
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
	// TODO: 关闭
	if(NPKsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = IMGsaveAlert ? ModalSaveWarning::MODIFIED_IMG_NPK : ModalSaveWarning::MODIFIED_NPK;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			IMGsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.saveFile(CStrToStr(fileNPKname));
			IMGsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		case ModalSaveWarning::RETURN_ALL_SAVE:
			no.IMGreplace(crtIMGid, io);
			no.saveFile(CStrToStr(fileNPKname));
			IMGsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	CDialogEx::OnCancel();
}

//////////////////////////////////////////////
/********IMG修改确认菜单处理事件*************/
//////////////////////////////////////////////


void CExRabbitDlg::OnModify01()
{
	// TODO: 确认当前修改
	CHECK_VALID(crtIMGid>=0);
	no.IMGreplace(crtIMGid, io);
	MessageBox(L"IMG已保存完毕喵！",L"提示喵！");
	IMGsaveAlert = FALSE;
	updateInfo();
	updateIMGlist();
	updatePIClist();
	updateTEXlist();
	updateColorTable();
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetSelectionMark(crtIMGid);
}
void CExRabbitDlg::OnModify02()
{
	// TODO: 确认当前修改并将IMG另存为
	CHECK_VALID(crtIMGid>=0);
	OnModify01();
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(FALSE, defExt, Underlining(StrToCStr(no.entry[crtIMGid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName1;
	if(dlg.DoModal() == IDOK){
		fileName1 = dlg.GetPathName();
		if(no.extract(crtIMGid, CStrToStr(fileName1))){
			MessageBox(_T("保存完毕喵！"),L"提示喵");
		}else{
			MessageBox(_T("保存失败喵！"),L"提示喵");
		}
	}
}

DefineThreadFunc(CExRabbitDlg, Draw, BOOL) {
	if(drawing)
		return;
	//TRACE("draw\n");
	drawing = 1;
	drawPara.texture = para;
	int picRow = crtPICid;
	int texRow = crtTEXid;
	int clrRow = colorOperatePara.current;
	int cbpro = GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel();
	int i, j, k, m, n, tx, ty;
	int canw = width - 540;
	int canh = height - 50;
	int clrBlockSize = 10;
	int clct, cp;

	color clrNoCanvas = color(0xff, GetRValue(profile.canvasColor0), GetGValue(profile.canvasColor0), GetBValue(profile.canvasColor0));
	color clrCanvasBound = color(0xff, GetRValue(profile.canvasColor1), GetGValue(profile.canvasColor1), GetBValue(profile.canvasColor1));
	color clrCanvasBack1 = color(0xff, GetRValue(profile.canvasColor2), GetGValue(profile.canvasColor2), GetBValue(profile.canvasColor2));
	color clrCanvasBack2 = color(0xff, GetRValue(profile.canvasColor1), GetGValue(profile.canvasColor1), GetBValue(profile.canvasColor1));
	color clrEnclosingBound = color(0x33, 0x77, 0x77, 0x77);
	color clrZeroAxis = color(0xff, 0xff, 0x00, 0x00);
	color clrZeroNoAxis = color(0xff, 0x77, 0x00, 0x00);
	color clrCutMark = color(0xff, 0xff, 0xff, 0x00);
	PICinfo po;
	TEXinfo di;
	CImage img;
	image canvas; //画布
	image content;	//内容
	image tempMat;	//中间矩阵
	color clr;
	if(io.version == V5 || io.version == V4)
		cbpro = 0;
	//背景
	canvas.create(canh, canw);
	canvas.fill(clrNoCanvas);

	if(KoishiImageTool::loadPNG(content, CStrToStr(profile.getSupportPath() + L"back.png"))) {
		for(i = 0; i<content.getWidth(); i++) {
			for(j = 0; j<content.getHeight(); j++) {
				color clr = content.getElem(j, i);
				if(i<content.getWidth()*0.3 || j < content.getHeight()*0.3) {
					clr.alpha = MIN(0xB0 * j / (0.3*content.getHeight()), 0xB0 * i / (0.3*content.getWidth()));
				} else {
					clr.alpha = 0xB0;
				}
				content.setElem(j, i, clr);
			}
		}
		canvas.putFore(content, LAY, point(canw - content.getWidth(), canh - content.getHeight()));
	}
	content.destory();
	//绘制颜色表

	if(drawPara.showPalette && (io.version == V4 || io.version == V5 || io.version == V6)) {
		cp = io.paletteData.getCount();
		if(cp>0) {
			clct = io.paletteData[0].size();
			if(clct>0) {
				clrBlockSize = canw / clct;
			}
		} else {
			clct = 0;
		}
		if(clrBlockSize>10)
			clrBlockSize = 10;
		for(i = 0; i<cp; i++) {
			clct = io.paletteData[i].size();
			for(j = 0; j<clct; j++) {
				for(m = 0; m<clrBlockSize; m++) {
					for(n = 0; n<clrBlockSize; n++) {
						canvas.setElem(canh - clrBlockSize*cp + clrBlockSize*i + m, canw - clrBlockSize*clct + clrBlockSize*j + n, io.paletteData[i][j]);
					}
				}
			}
		}
		//选定的颜色和调色方案
		tx = canw - clrBlockSize*clct + clrBlockSize*clrRow;
		ty = canh - clrBlockSize*cp + clrBlockSize*cbpro;

		for(m = 0; m<clrBlockSize; m++) {
			canvas.setElem(ty + m, tx, color(0xff, 0xff, 0xff, 0xff));
			canvas.setElem(ty, tx + m, color(0xff, 0xff, 0xff, 0xff));
			canvas.setElem(ty + clrBlockSize - 1, tx + m, color(0xff, 0xff, 0xff, 0xff));
			canvas.setElem(ty + m, tx + clrBlockSize - 1, color(0xff, 0xff, 0xff, 0xff));
		}
	}
	if(drawPara.texture) {
		//点击纹理集列表
		if(texRow < 0) {
			drawing = 0;
			return;
		}
		io.TEXgetInfo(texRow, di);
		io.TEXextract(texRow, tempMat);		//提取矩阵
		tempMat.zoom(drawPara.zoomRate);					//缩放后的矩阵
		KoishiExpand::KoishiMarkTool::ImagePSstyle(tempMat, content, clrCanvasBound, clrCanvasBack1, clrCanvasBack2);
		tempMat.destory();
		canvas.putFore(content, drawPara.mixMode, drawPara.basePoint);
	} else if(drawPara.entireTextureMode) {
		//全帧显示
		KoishiExpand::exhibit kex;
		kex.create(canvas.getWidth(), canvas.getHeight());
		bar.show(io.indexCount - 1 - picRow);
		for(i = picRow; i<io.indexCount; i++) {
			bar.setInfo(L"提取第" + NumToCStr(i) + L"帧喵……", i - picRow);
			io.PICextract(i, content, cbpro);
			kex.putImage(content);
			content.destory();
		}
		bar.hide();
		canvas.putFore(kex.canvas);
		drawPara.entireTextureMode = FALSE;
	} else {
		//其他模式
		//绘制网格线
		if(drawPara.showAxis) {
			if(drawPara.basePoint.X < 0) {
				canvas.line(point(0, 0), point(0, canh - 1), clrZeroNoAxis);
			} else if(drawPara.basePoint.X >= canw) {
				canvas.line(point(canw - 1, 0), point(canw - 1, canh - 1), clrZeroNoAxis);
			} else {
				canvas.line(point(drawPara.basePoint.X, 0), point(drawPara.basePoint.X, canh - 1), clrZeroAxis);
			}
			if(drawPara.basePoint.Y < 0) {
				canvas.line(point(0, 0), point(canw - 1, 0), clrZeroNoAxis);
			} else if(drawPara.basePoint.Y >= canh) {
				canvas.line(point(0, canh - 1), point(canw - 1, canh - 1), clrZeroNoAxis);
			} else {
				canvas.line(point(0, drawPara.basePoint.Y), point(canw - 1, drawPara.basePoint.Y), clrZeroAxis);
			}
		}
		//绘制IMG矩形
		if(drawPara.showBound) {
			long x1, x2, y1, y2;
			if(io.PICgetTotalBound(x1, x2, y1, y2)) {
				if(x2 - x1 < 0x3FFF && y2 - y1 < 0x3FFF) {
					x1 = drawPara.basePoint.X + x1*drawPara.zoomRate;
					x2 = drawPara.basePoint.X + x2*drawPara.zoomRate;
					y1 = drawPara.basePoint.Y + (y1 + 1)*drawPara.zoomRate - 1;
					y2 = drawPara.basePoint.Y + (y2 + 1)*drawPara.zoomRate - 1;
					canvas.rectangle(point(x1, y1), point(x2, y2), clrEnclosingBound);
					canvas.rectangle(point(x1 + 1, y1 + 1), point(x2 - 1, y2 - 1), clrEnclosingBound);
				}else{
					//防止某一帧的异常影响其他帧的显示
				}
			}
		}
		//IMG对比模式
		if(drawPara.compareMode && picRow >= 0) {
			int picRowComp = picRow;
			if(picRowComp < ioComp.indexSize) {
				//如果ioTemp中存在此帧
				ioComp.PICgetInfo(picRowComp, po);
				if(po.format == LINK)
					picRowComp = ioComp.linkFind(picRowComp);
				ioComp.PICgetInfo(picRowComp, po);
				ioComp.PICextract(picRowComp, content, 0);
				content.zoom(drawPara.zoomRate);
				for(i = 0; i<content.getElemCount(); i++) {
					color clr = content.getElem(i);
					clr.alpha /= 2;
					content.setElem(i, clr);
				}
				canvas.putFore(content, drawPara.mixMode, po.basePt*drawPara.zoomRate + drawPara.basePoint);
				content.destory();	//借用的，要还
			}
		}
		//正常图
		if(picRow >= 0) {
			io.PICgetInfo(picRow, po);
			if(po.format == LINK)
				picRow = io.linkFind(picRow);
			io.PICgetInfo(picRow, po);
			io.PICextract(picRow, tempMat, (long)cbpro);
			//画刷预览
			if(canvasOperatePara.canvasOperating) {
				switch(canvasOperatePara.canvasOperation) {
				case CANVAS_BRUSH:
					for(int i = 0; i<canvasOperatePara.drawnPoint.size(); i++) {
						tempMat.setElem((canvasOperatePara.drawnPoint[i] - po.basePt).Y, (canvasOperatePara.drawnPoint[i] - po.basePt).X, cl[clrRow]);
					}
					break;
				case CANVAS_ERASE:
					for(int i = 0; i<canvasOperatePara.drawnPoint.size(); i++) {
						tempMat.setElem((canvasOperatePara.drawnPoint[i] - po.basePt).Y, (canvasOperatePara.drawnPoint[i] - po.basePt).X, color(0, 0, 0, 0));
					}
					break;
				case CANVAS_DRAWLINE:
					tempMat.line(canvasOperatePara.startPoint - po.basePt, canvasOperatePara.movePoint - po.basePt, cl[clrRow]);
					break;
				case CANVAS_DRAWRECT:
					tempMat.rectangle(canvasOperatePara.startPoint - po.basePt, canvasOperatePara.movePoint - po.basePt, cl[clrRow]);
					break;
				}
			}
			//索引模式
			if(drawPara.indexMode && (io.version == V4 || io.version == V5 || io.version == V6)) {
				for(k = 0; k<cl.size(); k++) {
					//TODO：矩阵content里替换元素·被选定的替换为蓝色
					int temp = 255 * k / cl.size();
					if(colorOperatePara.isChosen[k]) {
						tempMat.replace(cl[k], color(0xFF, 0, 0, 0xff));
					} else {
						tempMat.replace(cl[k], color(0xFF, temp, temp, temp));
					}
				}
			}
			//缩放到屏幕
			tempMat.zoom(drawPara.zoomRate);
			//非对比模式 & 播放模式 不绘制画布
			if(drawPara.compareMode || playing == 1 || !drawPara.showCanvas) {
				content = tempMat;
			} else {
				KoishiExpand::KoishiMarkTool::ImagePSstyle(tempMat, content, clrCanvasBound, clrCanvasBack1, clrCanvasBack2);
			}
			tempMat.destory();
			//移动坐标
			canvas.putFore(content, drawPara.mixMode, po.basePt*drawPara.zoomRate + drawPara.basePoint);
		}
	}
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
	content.destory();
	ReleaseDC(pDC);
	drawing = 0;
	canvas.destory();
}

DefineThreadFunc(CExRabbitDlg, DrawColor, PVOID) {
	CHECK_VALID(!drawingColor);
	drawingColor = 1;
	int i, j;
	int enumCountPerRow[5] = {12, 15, 20, 25, 30};
	int enumMaxRow[5] = {4, 5, 6, 8, 10};
	int enumBlockSize[5] = {25, 20, 15, 12, 10};
	int countPerRow = enumCountPerRow[colorOperatePara.layout];
	int maxRow = enumMaxRow[colorOperatePara.layout];
	int blockSize = enumBlockSize[colorOperatePara.layout];
	color clr;
	//画调色板
	image canvas(102, 302);
	image block1(blockSize - 2, blockSize - 2);
	image block2(blockSize - 2, blockSize - 2);
	canvas.fill(color(0xFF,
		((profile.mainColor >> 0) & 0xFF) / 2,
		((profile.mainColor >> 8) & 0xFF) / 2,
		((profile.mainColor >> 16) & 0xFF) / 2
		));
	int index = 0;
	for(j = 0; j<maxRow; j++) {
		for(i = 0; i<countPerRow; i++) {
			if(index < cl.size()) {
				clr = cl[index];
				block1.filledLattice(point(0, 0), point(blockSize - 3, blockSize - 3), color(0xFF, 0XFF, 0XFF, 0XFF), color(0xFF, 0xCC, 0xCC, 0xCC), 6);
				block2.fill(clr);
				block1.putFore(block2);
				if(colorOperatePara.isChosen[index]) {
					block1.rectangle(point(0, 0), point(blockSize - 3, blockSize - 3), color(0xFF, 0XFF, 0XFF, 0XFF));
					block1.rectangle(point(1, 1), point(blockSize - 4, blockSize - 4), color(0xFF, 0X77, 0X77, 0X77));
				}
				canvas.putFore(block1, LAY, point(blockSize*i + 2, blockSize*j + 2));
				index++;
			} else if(index == cl.size()) {
				block1.fill(color(0xff, 0xff, 0x99, 0xff));
				block1.filledRectangle(point((blockSize - 2) / 5, (blockSize - 2) * 2 / 5), point((blockSize - 2) * 4 / 5, (blockSize - 2) * 3 / 5), color(0xff, 0xff, 0xff, 0x99));
				block1.filledRectangle(point((blockSize - 2) * 2 / 5, (blockSize - 2) / 5), point((blockSize - 2) * 3 / 5, (blockSize - 2) * 4 / 5), color(0xff, 0xff, 0xff, 0x99));
				canvas.putFore(block1, LAY, point(blockSize*i + 2, blockSize*j + 2));
				index++;
			} else if(index == cl.size() + 1) {
				block1.fill(color(0xff, 0x99, 0xcc, 0xff));
				block1.filledRectangle(point((blockSize - 2) / 5, (blockSize - 2) * 2 / 5), point((blockSize - 2) * 4 / 5, (blockSize - 2) * 3 / 5), color(0xff, 0xff, 0xff, 0x99));
				canvas.putFore(block1, LAY, point(blockSize*i + 2, blockSize*j + 2));
				index++;
			} else {
				block1.filledLattice(point(0, 0), point(blockSize - 3, blockSize - 3), color(0xFF, 0XFF, 0XFF, 0XFF), color(0xFF, 0xCC, 0xCC, 0xCC), 2);
				canvas.putFore(block1, LAY, point(blockSize*i + 2, blockSize*j + 2));
			}
		}
	}
	CImage img;
	img.Create(302, 102, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for(i = 0; i<302; i++) {
		for(j = 0; j<102; j++) {
			*(pst + pit*j + 4 * i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4 * i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4 * i + 2) = canvas[j][i].R;
		}
	}
	CDC *pDC = GetDC();
	img.Draw(pDC->m_hDC, 169, height - 111);
	img.Destroy();
	ReleaseDC(pDC);
	//画当前颜色
	image base1(35, 40);
	image base2(35, 40);
	base1.filledLattice(point(0, 0), point(39, 34), color(0xFF, 0XFF, 0XFF, 0XFF), color(0xFF, 0xCC, 0xCC, 0xCC), 6);
	base2.fill(colorOperatePara.current >= cl.size() ? color(0, 0, 0, 0) : cl[colorOperatePara.current]);
	base2.line(point(0, 0), point(0, 34), color(0xFF, 0XCC, 0XCC, 0XCC));
	base2.line(point(1, 1), point(1, 33), color(0xFF, 0XCC, 0XCC, 0XCC));
	base2.line(point(2, 2), point(2, 32), color(0xFF, 0x77, 0x77, 0x77));
	base2.line(point(0, 0), point(39, 0), color(0xFF, 0XEE, 0XEE, 0XEE));
	base2.line(point(1, 1), point(38, 1), color(0xFF, 0XEE, 0XEE, 0XEE));
	base2.line(point(2, 2), point(37, 2), color(0xFF, 0x33, 0x33, 0x33));
	base2.line(point(39, 34), point(0, 34), color(0xFF, 0x33, 0x33, 0x33));
	base2.line(point(38, 33), point(1, 33), color(0xFF, 0x33, 0x33, 0x33));
	base2.line(point(37, 32), point(2, 32), color(0xFF, 0XEE, 0XEE, 0XEE));
	base2.line(point(39, 34), point(39, 0), color(0xFF, 0x77, 0x77, 0x77));
	base2.line(point(38, 33), point(38, 1), color(0xFF, 0x77, 0x77, 0x77));
	base2.line(point(37, 32), point(37, 2), color(0xFF, 0XCC, 0XCC, 0XCC));
	base1.putFore(base2);
	img.Create(40, 35, 32);
	pst = (UCHAR*)img.GetBits();
	pit = img.GetPitch();
	for(i = 0; i<40; i++) {
		for(j = 0; j<35; j++) {
			*(pst + pit*j + 4 * i + 0) = base1[j][i].B;
			*(pst + pit*j + 4 * i + 1) = base1[j][i].G;
			*(pst + pit*j + 4 * i + 2) = base1[j][i].R;
		}
	}
	pDC = GetDC();
	img.Draw(pDC->m_hDC, 480, height - 70);
	img.Destroy();
	ReleaseDC(pDC);
	drawingColor = 0;
}
DefineThreadFunc(CExRabbitDlg, Play, PVOID) {
	int localFrame = 0;
	while(TRUE) {
		if(playing) {
			std::vector<int> frameList;
			getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), 0, MULTI_SELECT, frameList);
			if(frameList.size() == 0) {
				getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), 0, ALL_SELECT, frameList);
			}
			for(localFrame = 0; localFrame<frameList.size(); localFrame++) {
				int row = frameList[localFrame];
				if(row >= io.indexCount)
					break;
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemState(row - 1, 0, LVIS_FOCUSED | LVIS_SELECTED);
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemState(row, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetSelectionMark(row);
				crtPICid = row;
				updateInfo();
				draw();
				Sleep(100);
				if(playing == 0) {
					break;
				}
			}
		}
		Sleep(10);
	}
}
DefineThreadFunc(CExRabbitDlg, Lazy, PVOID) {
	//延时线程
	while(m_hWnd) {
		Sleep(10);
		if(lazyTime>0)
			lazyTime--;
	}
}
/////////////////////////////////////////////////////////////
//工具栏按钮
//////////////////////////////////////////////////////////////
void CExRabbitDlg::OnBnClickedToolButton1(){
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_DRAW);  
    pPopup = menu.GetSubMenu(0); 
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}
void CExRabbitDlg::OnBnClickedToolButton2(){
	// TODO: 在此添加控件通知处理程序代码
	drawPara.indexMode = !drawPara.indexMode;
	updateToolButtonStatus();
	draw();
}
void CExRabbitDlg::OnBnClickedToolButton3(){
	// TODO: 在此添加控件通知处理程序代码
	drawPara.entireTextureMode = !drawPara.entireTextureMode;
	canvasOperatePara.canvasOperation = CANVAS_SHOW;
	canvasOperatePara.oldMatrixEnable = FALSE;
	draw();
}
void CExRabbitDlg::OnBnClickedToolButton4(){
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_DRAW);  
    pPopup = menu.GetSubMenu(1);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}
void CExRabbitDlg::OnBnClickedToolButton5(){
	//TODO: 播放
	canvasOperatePara.canvasOperation = CANVAS_SHOW;
	canvasOperatePara.oldMatrixEnable = FALSE;
	playing = !playing;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton6(){
	// TODO: 拖动
	canvasOperatePara.canvasOperation = CANVAS_DRAG;
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton7()
{	//TODO: 缩放
	canvasOperatePara.canvasOperation = CANVAS_ZOOM;
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton8(){
	// TODO: 移动
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_MOVE;
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton9(){
	// TODO: 裁切
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	if(io.version == V5){
		MessageBox(L"不能对V5版本的IMG贴图进行扩充/裁切喵！",L"提示喵");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_CUT;
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton10(){
	// TODO: 在此添加控件通知处理程序代码
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	if(io.version == V5){
		MessageBox(L"不能对V5版本的IMG贴图进行画刷喵！",L"提示喵");
		return;
	}
	if(canvasOperatePara.canvasOperation != CANVAS_BRUSH){
		canvasOperatePara.canvasOperation = CANVAS_BRUSH;
		canvasOperatePara.oldMatrixEnable = FALSE;
	}else{
		TinySetBrush dlg;
		dlg.size = canvasOperatePara.brushSize;
		dlg.shape = canvasOperatePara.brushShape;
		if(dlg.DoModal() == IDOK){
			canvasOperatePara.brushSize = dlg.size;
			canvasOperatePara.brushShape = dlg.shape;
		}
	}
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton11(){
	// TODO: 在此添加控件通知处理程序代码
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	if(io.version == V5){
		MessageBox(L"不能对V5版本的IMG贴图进行画线条喵！",L"提示喵");
		return;
	}
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_DRAWLINE;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton12(){
	// TODO: 在此添加控件通知处理程序代码
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	if(io.version == V5){
		MessageBox(L"不能对V5版本的IMG贴图进行画矩形喵！",L"提示喵");
		return;
	}
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_DRAWRECT;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton13(){
	// TODO: 在此添加控件通知处理程序代码
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	if(io.version == V5){
		MessageBox(L"不能对V5版本的IMG贴图进行擦除喵！",L"提示喵");
		return;
	}
	if(canvasOperatePara.canvasOperation != CANVAS_ERASE){
		canvasOperatePara.oldMatrixEnable = FALSE;
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
	updateToolButtonStatus();
}
void CExRabbitDlg::updateToolButtonStatus(){
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
	// TODO: 在此添加控件通知处理程序代码
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_PICK;
	updateToolButtonStatus();
}


void CExRabbitDlg::OnBnClickedToolButton15(){
	// TODO: 在此添加控件通知处理程序代码
	if(playing){
		MessageBox(L"请先暂停播放喵！", L"提示喵");
		return;
	}
	if(io.version == V5){
		MessageBox(L"不能对V5版本的IMG贴图进行打标喵！",L"提示喵");
		return;
	}
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_MARK;
	updateToolButtonStatus();
}

void CExRabbitDlg::OnRButtonDown(UINT nFlags, CPoint pt){
	// TODO: 右键按下
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
	// TODO: 右键释放
	CDialogEx::OnRButtonUp(nFlags, pt);
}
void CExRabbitDlg::OnLButtonDown(UINT nFlags, CPoint pt){
	// TODO: 鼠标左键按下
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
	// TODO: 鼠标左键释放
	CDialogEx::OnLButtonUp(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_LEFT_RELEASE, mousePt);
	}
}
void CExRabbitDlg::OnLButtonDblClk(UINT nFlags, CPoint point){
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnLButtonDblClk(nFlags, point);
	int selectColorID;
	if(getIDofCurrentPos(selectColorID)){
		OnMouseEventColor(CANVAS_MOUSE_LEFT_DOUBLE, selectColorID);
	}
}

void CExRabbitDlg::OnMouseMove(UINT nFlags, CPoint pt){
	// TODO: 移动鼠标
	CDialogEx::OnMouseMove(nFlags, pt);
	updateCursorInfo();
	point mousePt;
	if(getMouseAxis(mousePt)){
		//响应画布操作
		OnMouseEventCanvas(canvasOperatePara.canvasOperating ? CANVAS_MOUSE_LEFT_DRAG : CANVAS_MOUSE_MOVE, mousePt);
	}
}
void CExRabbitDlg::OnMouseEventColor(enumCanvasMouseOperation mouseOperation, int selectColorID){
	CHECK_VALID(selectColorID >= 0);
	CHECK_VALID(selectColorID <= cl.size()+1);
	switch(mouseOperation){
	case CANVAS_MOUSE_LEFT_PRESS:
		//单击颜色表
		//单击加号，添加颜色；
		//单击减号，呼出菜单；
		//单击颜色，选择颜色
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
				updateInfo();
				updateColorTable();
				draw();
			}
		}else if(selectColorID == cl.size()+1){
			CMenu menu, *pPopup;  
			menu.LoadMenu(IDR_MENU_COLOR);  
			pPopup = menu.GetSubMenu(1);  
			CPoint myPoint; 
			ClientToScreen(&myPoint);  
			GetCursorPos(&myPoint); //鼠标位置  
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
		}else{
			colorOperatePara.current = selectColorID;
			updateInfo();
			updateColorTable();
			draw();
		}
		break;
	case CANVAS_MOUSE_LEFT_DOUBLE:
		//双击颜色表
		//双击颜色，对颜色进行修改
		if(selectColorID < cl.size()){
			COLORREF sclr = RGB(cl[selectColorID].R, cl[selectColorID].G, cl[selectColorID].B);
			CColorDialog cdlg(sclr, CC_FULLOPEN | CC_RGBINIT, this);
			if(cdlg.DoModal() == IDOK){
				sclr = cdlg.GetColor();
				if(io.version == V4 || io.version == V5 || io.version == V6){
					io.CLRreplace(selectColorID, color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)), GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
					cl[selectColorID] = color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr));
				}else{
					colorOperatePara.v2Color[selectColorID] = (color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr)));
					cl[selectColorID] = color(GetRValue(sclr),GetGValue(sclr),GetBValue(sclr));
				}
			}
		}
		updateInfo();
		updateColorTable();
		draw();
		break;
	case CANVAS_MOUSE_RIGHT_PRESS:
		//右键单击颜色表
		//右键单击颜色：选择颜色 + 呼出右键菜单
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
	point TRUEPt;
	switch(canvasOperatePara.canvasOperation){
	case CANVAS_SHOW:
		//显示
		break;
	case CANVAS_DRAG:
		//拖动操作
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 1;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = TRUE;
			canvasOperatePara.oldBasePoint = drawPara.basePoint;	//记录原画布原点坐标
			canvasOperatePara.startPoint = mousePt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 1;
			drawPara.basePoint = canvasOperatePara.oldBasePoint + mousePt - canvasOperatePara.startPoint;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = FALSE;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			drawPara.basePoint = mousePt - io.PICcontent[crtPICid].basePt * drawPara.zoomRate;
			draw();
			break;
		}
		break;
	case CANVAS_MOVE:
		//移动坐标
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = TRUE;
			canvasOperatePara.oldBasePoint = io.PICcontent[crtPICid].basePt;
			canvasOperatePara.startPoint = mousePt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 2;
			canvasOperatePara.endPoint = canvasOperatePara.oldBasePoint + (mousePt - canvasOperatePara.startPoint)/drawPara.zoomRate;
			io.PICsetInfoPara(crtPICid, 1, &canvasOperatePara.endPoint);
			updatePICterm(crtPICid);
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = FALSE;
			updateModified();
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			canvasOperatePara.endPoint= mousePt - drawPara.basePoint/drawPara.zoomRate;
			io.PICsetInfoPara(crtPICid, 1, &canvasOperatePara.endPoint);
			updatePICterm(crtPICid);
			updateModified();
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
		//裁切
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			if(1){
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				CHECK_VALID(pi.format != LINK);
				CHECK_VALID(pi.picSize.area() > 1);
				getMouseTrueAxis(TRUEPt);
				long left = pi.basePt.X;
				long right = pi.basePt.X + pi.picSize.W - 1;
				long top = pi.basePt.Y;
				long bottom = pi.basePt.Y + pi.picSize.H - 1;
				
				BOOL nearLeft = TRUEPt.X > left - 5 && TRUEPt.X < left + 5 && TRUEPt.Y > top - 5  && TRUEPt.Y < bottom + 5 ;
				BOOL nearRight = TRUEPt.X > right - 5 && TRUEPt.X < right + 5 && TRUEPt.Y > top - 5 && TRUEPt.Y < bottom + 5;
				BOOL nearTop = TRUEPt.X > left - 5 && TRUEPt.X < right + 5 && TRUEPt.Y > top - 5 && TRUEPt.Y < top + 5;
				BOOL nearBottom = TRUEPt.X > left - 5 && TRUEPt.X < right + 5 && TRUEPt.Y > bottom - 5 && TRUEPt.Y < bottom + 5;
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
			canvasOperatePara.canvasOperating = TRUE;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.startPoint = TRUEPt;
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = FALSE;
				getMouseTrueAxis(TRUEPt);
				image matOld, matNew;
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
					y1new = TRUEPt.Y;
					break;
				case CANVAS_TOPRIGHT:
					y1new = TRUEPt.Y;
					x2new = TRUEPt.X;
					break;
				case CANVAS_RIGHT:
					x2new = TRUEPt.X;
					break;
				case CANVAS_BOTTOMRIGHT:
					y2new = TRUEPt.Y;
					x2new = TRUEPt.X;
					break;
				case CANVAS_BOTTOM:
					y2new = TRUEPt.Y;
					break;
				case CANVAS_BOTTOMLEFT:
					x1new = TRUEPt.X;
					y2new = TRUEPt.Y;
					break;
				case CANVAS_LEFT:
					x1new = TRUEPt.X;
					break;
				case CANVAS_TOPLEFT:
					x1new = TRUEPt.X;
					y1new = TRUEPt.Y;
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
					io.PICextractIndexImage(crtPICid, matOld);
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
					io.PICpreprocessIndexImage(matNew, s, pi);
				}
				pi.basePt = point(x1new, y1new);
				io.PICreplace(crtPICid, pi, s);
				updatePICterm(crtPICid);
				s.release();
				matNew.destory();
				matOld.destory();
				draw();
				updateModified();
			}
			break;
		}
		break;
	case CANVAS_PICK:
		//取色
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 10;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			if(TRUE){
				CPoint myPoint  = getWinMouseAxis();   
				CDC *pDC = this->GetDC();
				COLORREF clrr = GetPixel(pDC->m_hDC, myPoint.x, myPoint.y);
				this->ReleaseDC(pDC);
				color clrMous = color(0xFF, GetRValue(clrr), GetGValue(clrr), GetBValue(clrr));
				int ID;
				BOOL found = FALSE;
				for(int i = 0;i<cl.size();i++){
					if(cl[i] == clrMous){
						ID = i;
						found = TRUE;
						break;
					}
				}
				if(found){
					colorOperatePara.current = ID;
					colorOperatePara.isChosen[ID] = TRUE;
				}else{
					if(io.version == V4 || io.version == V5 || io.version == V6){
						//对索引贴图未取色保持不变·什么也不做
					}else{
						if(colorOperatePara.v2Color.size() < 256){
							colorOperatePara.v2Color.push_back(clrMous);
							cl.push_back(clrMous);
							colorOperatePara.current = cl.size() - 1;
							colorOperatePara.isChosen[cl.size() - 1] = TRUE;
						}else{
							MessageBox(L"颜色表容量已达到最大喵！",L"提示喵");
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
		//画刷
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 8;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(TRUEPt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = TRUE;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(TRUEPt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 8;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(TRUEPt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = FALSE;
				image mat;
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
					io.PICextractIndexImage(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					for(int i = 0;i<canvasOperatePara.drawnPoint.size();i++){
						mat.setElem((canvasOperatePara.drawnPoint[i] - pi.basePt).Y,(canvasOperatePara.drawnPoint[i] - pi.basePt).X,color(colorOperatePara.current,0,0,0));
					}
					io.PICpreprocessIndexImage(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				image mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexImage(crtPICid, mat);
					io.PICpreprocessIndexImage(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_ERASE:
		//擦除
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 9;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(TRUEPt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = TRUE;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.drawnPoint.clear();
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(TRUEPt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 9;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			{
				int size = canvasOperatePara.brushSize;
				int shape = canvasOperatePara.brushShape;
				for(int i = 0;i<size;i++){
					for(int j = 0;j<size;j++){
						if(shape == 2 || (size/2-i)*(size/2-i)+(size/2-j)*(size/2-j) <= size*size/4){
							canvasOperatePara.drawnPoint.push_back(TRUEPt+point(i-size/2, j-size/2));
						}
					}
				}
			}
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = FALSE;
				image mat;
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
					io.PICextractIndexImage(crtPICid, mat);
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
					io.PICpreprocessIndexImage(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				image mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexImage(crtPICid, mat);
					io.PICpreprocessIndexImage(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_DRAWLINE:
		//画直线
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = TRUE;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.startPoint = TRUEPt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 2;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.movePoint = TRUEPt;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = FALSE;
				getMouseTrueAxis(TRUEPt);
				image mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.line(canvasOperatePara.startPoint-pi.basePt, TRUEPt-pi.basePt, cl[colorOperatePara.current]);
					io.PICpreprocess(mat, s, pi, pi.format);
				}else{
					io.PICextractIndexImage(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.line(canvasOperatePara.startPoint-pi.basePt, TRUEPt-pi.basePt, color(colorOperatePara.current,0,0,0));
					io.PICpreprocessIndexImage(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				image mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexImage(crtPICid, mat);
					io.PICpreprocessIndexImage(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_DRAWRECT:
		//画矩形
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = TRUE;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.startPoint = TRUEPt;
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			canvasOperatePara.currentCursor = 2;
			canvasOperatePara.oldMatrixEnable = TRUE;
			getMouseTrueAxis(TRUEPt);
			canvasOperatePara.movePoint = TRUEPt;
			draw();
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			if(canvasOperatePara.canvasOperating){
				canvasOperatePara.canvasOperating = FALSE;
				getMouseTrueAxis(TRUEPt);
				image mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.rectangle(canvasOperatePara.startPoint-pi.basePt, TRUEPt-pi.basePt, cl[colorOperatePara.current]);
					io.PICpreprocess(mat, s, pi, pi.format);
				}else{
					io.PICextractIndexImage(crtPICid, mat);
					canvasOperatePara.oldMatrix = mat;
					mat.rectangle(canvasOperatePara.startPoint-pi.basePt, TRUEPt-pi.basePt, color(colorOperatePara.current,0,0,0));
					io.PICpreprocessIndexImage(mat, s, pi);
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			if(!canvasOperatePara.canvasOperating){
				if(!canvasOperatePara.oldMatrixEnable)
					break;
				image mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexImage(crtPICid, mat);
					io.PICpreprocessIndexImage(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	case CANVAS_MARK:
		//打标
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			{
				getMouseTrueAxis(TRUEPt);
				TinyAddMark dlg;
				if(IDOK == dlg.DoModal()){
					canvasOperatePara.oldMatrixEnable = TRUE;
					str markText = dlg.text;
					image mat;
					stream s;
					PICinfo pi;
					if(io.version == V2){
						canvasOperatePara.oldMatrix.destory();
						io.PICextract(crtPICid, canvasOperatePara.oldMatrix);
						io.PICgetInfo(crtPICid, pi);
						KoishiExpand::KoishiMarkTool::ImageMarking(canvasOperatePara.oldMatrix, mat, markText, TRUEPt - pi.basePt, cl[colorOperatePara.current]);
						if(TRUEPt.X<pi.basePt.X){
							pi.basePt.X = TRUEPt.X;
						}
						if(TRUEPt.Y<pi.basePt.Y){
							pi.basePt.Y = TRUEPt.Y;
						}
						io.PICpreprocess(mat, s, pi, pi.format);
					}else{
						canvasOperatePara.oldMatrix.destory();
						io.PICextractIndexImage(crtPICid, canvasOperatePara.oldMatrix);
						io.PICgetInfo(crtPICid, pi);
						KoishiExpand::KoishiMarkTool::ImageMarking(canvasOperatePara.oldMatrix, mat, markText, TRUEPt - pi.basePt, color(colorOperatePara.current,0,0,0));
						if(TRUEPt.X<pi.basePt.X){
							pi.basePt.X = TRUEPt.X;
						}
						if(TRUEPt.Y<pi.basePt.Y){
							pi.basePt.Y = TRUEPt.Y;
						}
						io.PICpreprocessIndexImage(mat, s, pi);
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
				image mat;
				stream s;
				PICinfo pi;
				io.PICgetInfo(crtPICid, pi);
				if(io.version == V2){
					io.PICextract(crtPICid, mat);
					io.PICpreprocess(canvasOperatePara.oldMatrix, s, pi, pi.format);
					canvasOperatePara.oldMatrix = mat;
				}else{
					io.PICextractIndexImage(crtPICid, mat);
					io.PICpreprocessIndexImage(canvasOperatePara.oldMatrix, s, pi);
					canvasOperatePara.oldMatrix = mat;
				}
				io.PICreplace(crtPICid, pi, s);
				s.release();
				mat.destory();
				draw();
				updateModified();
				canvasOperatePara.drawnPoint.clear();
			}
			break;
		}
		break;
	}
}
BOOL CExRabbitDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message){
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加命令处理程序代码
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = TRUE;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableChooseNone(){
	// TODO: 在此添加命令处理程序代码
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = FALSE;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableInverseChoose(){
	// TODO: 在此添加命令处理程序代码
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = !colorOperatePara.isChosen[i];
	}
	updateColorTable();
}

void CExRabbitDlg::OnMenuColorTableChooseFamiliar(){
	// TODO: 在此添加命令处理程序代码
	for(int i = 0;i<cl.size();i++){
		colorHSV HSV1, HSV2;
		cl[colorOperatePara.current].getHSV(HSV1);
		cl[i].getHSV(HSV2);
		colorOperatePara.isChosen[i] = (abs(HSV1.H - HSV2.H) <= colorOperatePara.tolerance);
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableDeleteOne(){
	// TODO: 在此添加命令处理程序代码
	BOOL selected = FALSE;
	for(int i = 0;i<cl.size();i++){
		if(colorOperatePara.isChosen[i]){
			selected = TRUE;
			break;
		}
	}
	if(!selected){
		MessageBox(L"没选定颜色喵，请右键批量选择一些颜色再来删除喵！");
		return;
	}
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"对索引贴图删除调色板颜色会导致颜色混乱，确定喵？",L"提示喵",MB_YESNO)){
			for(int i = 0;i<cl.size();i++){
				int id = cl.size() - 1 - i;
				if(colorOperatePara.isChosen[id]){
					io.CLRremove(id,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
					cl.erase(cl.begin() + id);
				}
			}
			updateModified();
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
		colorOperatePara.isChosen[i] = FALSE;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableDeleteAll(){
	// TODO: 在此添加命令处理程序代码
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"对索引贴图删除调色板颜色会导致颜色混乱，确定喵？",L"提示喵",MB_YESNO)){
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			cl.clear();
			updateModified();
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
	CString defExt = _T("Photoshop颜色表(*.act)|*.act");
	CString extFilter = _T("Photoshop颜色表(*.act)|*.act|CID颜色表(*.cid)|*.cid||");
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(fileName.Right(1) == L"t" || fileName.Right(1) == L"T" ){
			if(!palette::loadACT(CStrToStr(fileName), newCl)){
				MessageBox(L"未识别的调色板文件喵！",L"提示喵");
				return;
			}
		}
		if(fileName.Right(1) == L"D" || fileName.Right(1) == L"d" ){
			if(!palette::loadCID(CStrToStr(fileName), newCl)){
				MessageBox(L"未识别的调色板文件喵！",L"提示喵");
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
			updateModified();
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
	// TODO: 在此添加命令处理程序代码
	CString defExt = _T("Photoshop颜色表(*.act)|*.act");
	CString extFilter = _T("Photoshop颜色表(*.act)|*.act|CID颜色表(*.cid)|*.cid||");
	CFileDialog dlg(FALSE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(fileName.Right(1) == L"t" || fileName.Right(1) == L"T" ){
			palette::makeACT(CStrToStr(fileName), cl);
			MessageBox(L"保存完毕喵！",L"提示喵");
		}
		if(fileName.Right(1) == L"D" || fileName.Right(1) == L"d" ){
			palette::makeCID(CStrToStr(fileName), cl);
			MessageBox(L"保存完毕喵！",L"提示喵");
		}
	}
}


void CExRabbitDlg::OnMenuColorPaletteNew(){
	if(io.version != V6){
		MessageBox(L"只有V6版本才能进行颜色方案操作喵",L"提示喵");
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
	updateModified();
}


void CExRabbitDlg::OnMenuColorPaletteCopy(){
	if(io.version != V6){
		MessageBox(L"只有V6版本才能进行颜色方案操作喵",L"提示喵");
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
	updateModified();
}


void CExRabbitDlg::OnMenuColorPaletteImport(){
	if(io.version != V6){
		MessageBox(L"只有V6版本才能进行颜色方案操作喵",L"提示喵");
		return;
	}
	colorList newCl;
	CString defExt = _T("Photoshop颜色表(*.act)|*.act");
	CString extFilter = _T("Photoshop颜色表(*.act)|*.act|CID颜色表(*.cid)|*.cid||");
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(fileName.Right(1) == L"t" || fileName.Right(1) == L"T" ){
			if(!palette::loadACT(CStrToStr(fileName), newCl)){
				MessageBox(L"未识别的调色板文件喵！",L"提示喵");
				return;
			}
		}
		if(fileName.Right(1) == L"D" || fileName.Right(1) == L"d" ){
			if(!palette::loadCID(CStrToStr(fileName), newCl)){
				MessageBox(L"未识别的调色板文件喵！",L"提示喵");
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
		updateModified();
	}
}


void CExRabbitDlg::OnMenuColorPaletteDelete(){
	if(io.version != V6){
		MessageBox(L"只有V6版本才能进行颜色方案操作喵",L"提示喵");
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
		updateModified();
	}
}

void CExRabbitDlg::OnMenuPictureChooseAll(){
	// TODO: 全选
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetCheck(i, TRUE);
}

void CExRabbitDlg::OnMenuPictureChooseInverse(){
	//反选
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetCheck(i, 1-GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetCheck(i));
}

void CExRabbitDlg::OnMenuPictureChooseHighline(){
	//选择高亮
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetCheck(i,TRUE);
}


void CExRabbitDlg::OnMenuPictureInsert(){
	// TODO: 在此添加命令处理程序代码
	ModalInsertPicture dlg;
	dlg.in.firstInsert = FALSE;
	dlg.in.version = io.version;
	dlg.in.maxPICcount = io.indexCount;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.PICgetInfo(crtPICid, dlg.in.pi);
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureInsert, dlg.out);
	}
}
void CExRabbitDlg::OnMenuPictureInsert2(){
	// TODO: 在此添加命令处理程序代码
	ModalInsertPicture dlg;
	dlg.in.firstInsert = TRUE;
	dlg.in.version = io.version;
	dlg.in.maxPICcount = io.indexCount;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.PICgetInfo(crtPICid, dlg.in.pi);
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureInsert, dlg.out);
	}
}
void CExRabbitDlg::OnMenuPictureInsertPatch2(){
	// TODO: 在此添加命令处理程序代码
	OnMenuPictureInsertPatch();
}
DefineThreadFunc(CExRabbitDlg, PictureInsert, ModalInsertPicture::OUTPUT) {
	processing = 1;
	int insertPos;
	std::vector<int> replacePos;
	image mPic;
	stream sPic;
	PICinfo pInfo;
	DDSobject DDSHelper;
	//确定处理目标
	switch(para.operate) {
	case 1:
		replacePos.push_back(crtPICid);
		break;
	case 2:
		getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), 0, MULTI_SELECT, replacePos);
		break;
	case 3:
		insertPos = crtPICid;
		break;
	case 4:
		insertPos = crtPICid + 1;
		break;
	case 5:
		insertPos = io.indexCount;
		break;
	}
	if(crtPICid < 0) {
		para.operate = 5;
		insertPos = 0;
	}
	//判断类型
	switch(para.type) {
	case 1:
		//指向帧判断
		pInfo.format = LINK;
		pInfo.linkTo = para.para[0];
		break;
	case 3:
		//纹理集引用
		pInfo.format = io.TEXcontent[para.para[5]].format;
		pInfo.comp = COMP_ZLIB_DUAL;
		pInfo.dataSize = 0;
		pInfo.basePt = point(para.para[1], para.para[2]);
		pInfo.picSize = size(para.para[8] - para.para[6], para.para[9] - para.para[7]);
		pInfo.frmSize = size(para.para[3], para.para[4]);
		pInfo.TEXusing = para.para[5];
		pInfo.TEXpointLT = point(para.para[6], para.para[7]);
		pInfo.TEXpointRB = point(para.para[8], para.para[9]);
		break;
	case 2:
		//读取资源
		switch(para.inputFormat) {
		case 0:
			mPic.create(200, 200);
			mPic.fill(0);
			break;
		case 1:
			KoishiImageTool::loadPNG(mPic, CStrToStr(para.fileName));
			break;
		case 2:
			DDSHelper.loadFile(CStrToStr(para.fileName));
			DDSHelper.uncompress(mPic);
			break;
		}
		//处理方式
		colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
		if(!io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para.outputFormat])) {
			MessageBox(L"添加该图片时遇到了错误。", L"错误。");
			processing = 0;
			return;
		}
		mPic.destory();
		break;
	}
	//处理
	if(replacePos.size() > 0) {
		bar.show(replacePos.size() - 1);
		for(int i = 0; i<replacePos.size(); i++) {
			bar.setInfo(L"正在插入第" + NumToCStr(i) + L"帧喵……", i);
			bar.setMax(replacePos.size() - 1);
			io.PICreplace(replacePos[i], pInfo, sPic);
			updatePICterm(replacePos[i]);
		}
		bar.hide();
	} else {
		io.PICinsert(insertPos, pInfo, sPic);
		updatePIClist();
	}
	sPic.release();
	mPic.destory();
	updateModified();
	updateInfo();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureInsertPatch(){
	// TODO: 在此添加命令处理程序代码
	ModalInsertPicturePatch dlg;
	dlg.in.version = io.version;
	dlg.in.maxPICcount = io.indexCount;
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureInsertPatch, dlg.out);
	}
}
DefineThreadFunc(CExRabbitDlg, PictureInsertPatch, ModalInsertPicturePatch::OUTPUT) {
	processing = 1;
	image mPic;
	stream sPic;
	PICinfo pInfo;
	if(para.inputFormat == 1) {
		//从PNG读入
		bar.show(para.PNGcount - 1);
		for(int i = 0; i<para.PNGcount; i++) {
			bar.setInfo(L"读入第" + NumToCStr(i) + L"帧喵……", i);
			CString fileName = para.filePath + NumToCStr(i) + L".PNG";
			if(i<io.indexCount) {
				//原有帧处理
				CHECK_VALID_CONTINUE(para.operate == 2);	//替换帧才有效
				CHECK_VALID_CONTINUE(KoishiImageTool::loadPNG(mPic, CStrToStr(fileName)));	//成功读取才有效
				if(para.holdCoordinate)
					io.PICgetInfo(io.linkFind(i), pInfo);
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para.outputFormat])) {
					mPic.destory();
					sPic.release();
					continue;
				}
				io.PICreplace(i, pInfo, sPic);
			} else {
				//追加帧处理
				if(!KoishiImageTool::loadPNG(mPic, CStrToStr(fileName))) {
					mPic.create(1, 1);
					mPic.fill(0);
				}
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para.outputFormat])) {
					//失败了什么也不做
					mPic.destory();
					sPic.release();
					continue;
				}
				io.PICpush(pInfo, sPic);
			}
			mPic.destory();
			sPic.release();
		}
		bar.hide();
	} else {
		//从IMG读入
		IMGobject targetIO;
		if(!targetIO.loadFile(CStrToStr(para.filePath))) {
			MessageBox(L"无法识别的IMG文件喵。", L"提示喵");
			processing = 0;
			return;
		}
		bar.show(targetIO.indexCount - 1);
		for(int i = 0; i<targetIO.indexCount; i++) {
			bar.setInfo(L"读入第" + NumToCStr(i) + L"帧喵……", i);
			if(i<io.indexCount) {
				//原有帧处理
				CHECK_VALID_CONTINUE(para.operate == 2);	//替换帧才有效
				targetIO.PICextract(i, mPic);
				targetIO.PICgetInfo(targetIO.linkFind(i), pInfo);
				if(para.holdCoordinate) {
					io.PICgetInfo(io.linkFind(i), pInfo);
				}
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para.outputFormat])) {
					mPic.destory();
					sPic.release();
					continue;
				}
				io.PICreplace(i, pInfo, sPic);
			} else {
				//追加帧处理
				targetIO.PICextract(i, mPic);
				targetIO.PICgetInfo(targetIO.linkFind(i), pInfo);
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para.outputFormat])) {
					mPic.destory();
					sPic.release();
					continue;
				}
				io.PICpush(pInfo, sPic);
			}
			mPic.destory();
			sPic.release();
		}
		bar.hide();
	}
	updatePIClist();
	processing = 0;
	bar.hide();
	updateInfo();
	updateModified();
	draw();
}

void CExRabbitDlg::OnMenuPictureDelete(){
	// TODO: 删除帧(&R)
	int i, row = crtPICid;
	io.PICremove(row);
	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->DeleteItem(row);
	for(i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(i,0,NumToCStr(i));//更新序号
	updateModified();
	updateInfo();
}


void CExRabbitDlg::OnMenuPictureDeletePatch(){
	// TODO: 在此添加命令处理程序代码
	int i = 0;
	for(i=io.indexCount-1;i>=0;i--){
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetCheck(i)){
			io.PICremove(i);
			GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->DeleteItem(i);
		}
	}
	for(i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(i,0,NumToCStr(i));//更新序号
	updateModified();
	updateInfo();
}


void CExRabbitDlg::OnMenuPictureAxisModify(){
	// TODO: 在此添加命令处理程序代码
	ModalPictureParameter dlg;
	PICinfo pi;
	io.PICgetInfo(io.linkFind(crtPICid), pi);
	dlg.in.curBX = pi.basePt.X;
	dlg.in.curBY = pi.basePt.Y;
	dlg.in.curFW = pi.frmSize.W;
	dlg.in.curFH = pi.frmSize.H;
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureAxisModify, dlg.out);
	}
}
DefineThreadFunc(CExRabbitDlg, PictureAxisModify, ModalPictureParameter::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	bar.show(targetList.size()-1);
	for(int i = 0;i<targetList.size();i++){
		int id = targetList[i];
		bar.setInfo(L"正在处理第"+NumToCStr(id)+L"帧喵……",i);
		PICinfo pInfo;
		point newPt;
		size newSz;
		io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para.operate){
		case 1:
			//平移基准点
			newPt = pInfo.basePt + point(
				para.enable[0] ? para.para[0] : 0,
				para.enable[1] ? para.para[1] : 0);
			io.PICsetInfoPara(id, 1, &newPt);
			updatePICterm(id);
			break;
		case 2:
			//统一基准点
			newPt = point(
				para.enable[0] ? para.para[0] : pInfo.basePt.X,
				para.enable[1] ? para.para[1] : pInfo.basePt.Y);
			io.PICsetInfoPara(id, 1, &newPt);
			updatePICterm(id);
			break;
		case 3:
			//对齐坐标
			newSz = size(
				para.enable[0] ? para.para[0] : pInfo.frmSize.W,
				para.enable[1] ? para.para[1] : pInfo.frmSize.H);
			io.PICsetInfoPara(id, 2, &newSz);
			updatePICterm(id);
			break;
		}
	}
	updateModified();
	draw();
	processing = 0;
	bar.hide();
}


void CExRabbitDlg::OnMenuPictureCanvas(){
	// TODO: 在此添加命令处理程序代码
	if(io.version == V5){
		MessageBox(L"此功能不适用于V5喵！",L"提示喵");
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
		StartThreadFunc(PictureCanvas, dlg.out);
	}
}

DefineThreadFunc(CExRabbitDlg, PictureCanvas, ModalAdjustCanvas::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在处理第" + NumToCStr(id) + L"帧喵……", i);
		PICinfo pInfo;
		image mPic;
		stream sPic;
		io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para.operate) {
		case 1:
			//扩充
			if(io.version == V4 || io.version == V6) {
				io.PICextractIndexImage(id, mPic);
				mPic.expand(
					para.enable[1] ? para.para[1] : 0,
					para.enable[3] ? para.para[3] : 0,
					para.enable[0] ? para.para[0] : 0,
					para.enable[2] ? para.para[2] : 0);
				pInfo.basePt = pInfo.basePt - point(
					para.enable[0] ? para.para[0] : 0,
					para.enable[1] ? para.para[1] : 0);
				io.PICpreprocessIndexImage(mPic, sPic, pInfo);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			} else {
				io.PICextract(id, mPic);
				mPic.expand(
					para.enable[1] ? para.para[1] : 0,
					para.enable[3] ? para.para[3] : 0,
					para.enable[0] ? para.para[0] : 0,
					para.enable[2] ? para.para[2] : 0);
				pInfo.basePt = pInfo.basePt - point(
					para.enable[0] ? para.para[0] : 0,
					para.enable[1] ? para.para[1] : 0);
				io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			updatePICterm(id);
			break;
		case 2:
			//裁切
			if(io.version == V4 || io.version == V6) {
				io.PICextractIndexImage(id, mPic);
				mPic.clip(
					para.enable[1] ? para.para[1] : 0,
					-(para.enable[3] ? para.para[3] : 0) + pInfo.picSize.H - 1,
					para.enable[0] ? para.para[0] : 0,
					-(para.enable[2] ? para.para[2] : 0) + pInfo.picSize.W - 1);
				pInfo.basePt = pInfo.basePt + point(
					para.enable[0] ? para.para[0] : 0,
					para.enable[1] ? para.para[1] : 0);
				io.PICpreprocessIndexImage(mPic, sPic, pInfo);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			} else {
				io.PICextract(id, mPic);
				mPic.clip(
					para.enable[1] ? para.para[1] : 0,
					-(para.enable[3] ? para.para[3] : 0) + pInfo.picSize.H - 1,
					para.enable[0] ? para.para[0] : 0,
					-(para.enable[2] ? para.para[2] : 0) + pInfo.picSize.W - 1);
				pInfo.basePt = pInfo.basePt + point(
					para.enable[0] ? para.para[0] : 0,
					para.enable[1] ? para.para[1] : 0);
				io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			updatePICterm(id);
			break;
		case 3:
			//对齐坐标
			if(io.version == V4 || io.version == V6) {
				image mNew;
				int x1old = pInfo.basePt.X;
				int y1old = pInfo.basePt.Y;
				int x2old = pInfo.basePt.X + pInfo.picSize.W - 1;
				int y2old = pInfo.basePt.Y + pInfo.picSize.H - 1;
				int x1new = para.enable[0] ? para.para[0] : x1old;
				int y1new = para.enable[1] ? para.para[1] : y1old;
				int x2new = para.enable[2] ? para.para[2] : x2old;
				int y2new = para.enable[3] ? para.para[3] : y2old;
				int x1 = min(x1old, x1new);
				int x2 = max(x2old, x2new);
				int y1 = min(y1old, y1new);
				int y2 = max(y2old, y2new);
				io.PICextractIndexImage(id, mPic);
				mNew.create(y2 - y1 + 1, x2 - x1 + 1);
				mNew.putFore(mPic, LAY, point(x1old - x1, y1old - y1));
				mNew.clip(y1new - y1, y2new - y1 + 1, x1new - x1, x2new - x1 + 1);
				pInfo.basePt = point(x1new, y1new);
				io.PICpreprocessIndexImage(mNew, sPic, pInfo);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				mNew.destory();
				sPic.release();
			} else {
				image mNew;
				int x1old = pInfo.basePt.X;
				int y1old = pInfo.basePt.Y;
				int x2old = pInfo.basePt.X + pInfo.picSize.W - 1;
				int y2old = pInfo.basePt.Y + pInfo.picSize.H - 1;
				int x1new = para.enable[0] ? para.para[0] : x1old;
				int y1new = para.enable[1] ? para.para[1] : y1old;
				int x2new = para.enable[2] ? para.para[2] : x2old;
				int y2new = para.enable[3] ? para.para[3] : y2old;
				int x1 = min(x1old, x1new);
				int x2 = max(x2old, x2new);
				int y1 = min(y1old, y1new);
				int y2 = max(y2old, y2new);
				io.PICextract(id, mPic);
				mNew.create(y2 - y1 + 1, x2 - x1 + 1);
				mNew.putFore(mPic, LAY, point(x1old - x1, y1old - y1));
				mNew.clip(y1new - y1, y2new - y1 + 1, x1new - x1, x2new - x1 + 1);
				pInfo.basePt = point(x1new, y1new);
				io.PICpreprocess(mNew, sPic, pInfo, pInfo.format);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				mNew.destory();
				sPic.release();
			}
			updatePICterm(id);
			break;
		case 4:
			//修整
			if(io.version == V4 || io.version == V6) {
				io.PICextractIndexImage(id, mPic);
				dword x1, x2, y1, y2;
				mPic.getElemHonzBound(x1, x2);
				mPic.getElemVertBound(y1, y2);
				x1 = para.enable[0] ? x1 : 0;
				x2 = para.enable[2] ? x2 : (pInfo.picSize.W - 1);
				y1 = para.enable[1] ? y1 : 0;
				y2 = para.enable[3] ? y2 : (pInfo.picSize.H - 1);
				if(x1 <= x2) {
					mPic.clip(y1, y2 + 1, x1, x2 + 1);
					pInfo.basePt = pInfo.basePt + point(x1, y1);
					io.PICpreprocessIndexImage(mPic, sPic, pInfo);
					io.PICreplace(id, pInfo, sPic);
				}
				mPic.destory();
				sPic.release();
			} else {
				io.PICextract(id, mPic);
				dword x1, x2, y1, y2;
				mPic.getElemHonzBound(x1, x2);
				mPic.getElemVertBound(y1, y2);
				x1 = para.enable[0] ? x1 : 0;
				x2 = para.enable[2] ? x2 : (pInfo.picSize.W - 1);
				y1 = para.enable[1] ? y1 : 0;
				y2 = para.enable[3] ? y2 : (pInfo.picSize.H - 1);
				if(x1 <= x2) {
					mPic.clip(y1, y2 + 1, x1, x2 + 1);
					pInfo.basePt = pInfo.basePt + point(x1, y1);
					io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
					io.PICreplace(id, pInfo, sPic);
				}
				mPic.destory();
				sPic.release();
			}
			updatePICterm(id);
			break;
		}
	}
	updateModified();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureClear(){
	// TODO: 在此添加命令处理程序代码
	if(io.version == V5){
		MessageBox(L"此功能不适用于V5喵！",L"提示喵");
		return;
	}
	ModalClearPicture dlg;
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureClear, dlg.out);
	}
}

DefineThreadFunc(CExRabbitDlg, PictureClear, ModalClearPicture::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在处理第" + NumToCStr(id) + L"帧喵……", i);
		PICinfo pInfo;
		image mPic;
		stream sPic;
		io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para.operate) {
		case 1:
			//保留画布
			if(io.version == V4 || io.version == V6) {
				mPic.create(pInfo.picSize);
				io.PICpreprocessIndexImage(mPic, sPic, pInfo);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			} else {
				mPic.create(pInfo.picSize);
				io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			updatePICterm(id);
			break;
		case 2:
			//保留坐标，画布缩为0,0
			if(io.version == V4 || io.version == V6) {
				mPic.create(1, 1);
				io.PICpreprocessIndexImage(mPic, sPic, pInfo);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			} else {
				mPic.create(1, 1);
				io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
				io.PICreplace(id, pInfo, sPic);
				mPic.destory();
				sPic.release();
			}
			updatePICterm(id);
			break;
		}
	}
	updateModified();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureLoseblack(){
	// TODO: 在此添加命令处理程序代码
	if(io.version == V5){
		MessageBox(L"此功能不适用于V5喵！",L"提示喵");
		return;
	}
	ModalLoseBlackPicture dlg;
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureLoseBlack, dlg.out);
	}
}
DefineThreadFunc(CExRabbitDlg, PictureLoseBlack, ModalLoseBlackPicture::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	if(io.version == V4 || io.version == V6) {
		color clr;
		bar.show(targetList.size() - 1);
		for(int j = 0; j<cl.size(); j++) {
			bar.setInfo(L"正在处理第" + NumToCStr(j) + L"个颜色喵……", j);
			clr = color::loseBlack(cl[j], para.gamma);
			io.CLRreplace(j, clr, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			cl[j] = clr;
		}
	} else {
		bar.show(targetList.size() - 1);
		for(int i = 0; i<targetList.size(); i++) {
			int id = targetList[i];
			bar.setInfo(L"正在处理第" + NumToCStr(id) + L"帧喵……", i);
			PICinfo pInfo;
			image mPic;
			stream sPic;
			io.PICgetInfo(id, pInfo);
			CHECK_VALID_CONTINUE(pInfo.format != LINK);
			switch(1) {
			case 1:
				io.PICextract(id, mPic);
				mPic.loseBlack(para.gamma);
				io.PICpreprocess(mPic, sPic, pInfo, ARGB8888);
				io.PICreplace(id, pInfo, sPic);
				sPic.release();
				mPic.destory();
				break;
			}
		}
	}
	updateModified();
	updateColorTable();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureGradient(){
	// TODO: 在此添加命令处理程序代码
	if(io.version == V5){
		MessageBox(L"此功能不适用于V5喵！",L"提示喵");
		return;
	}
	ModalGradient dlg;
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureGradient, dlg.out);
	}
}

DefineThreadFunc(CExRabbitDlg, PictureGradient, ModalGradient::OUTPUT) {
	processing = 1;
	colorList keyColorList;
	keyColorList.push_back(para.keyColor2);
	keyColorList.push_back(para.keyColor1);
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	if(io.version == V2) {
		bar.show(targetList.size() - 1);
		for(int i = 0; i<targetList.size(); i++) {
			int id = targetList[i];
			bar.setInfo(L"正在处理第" + NumToCStr(id) + L"帧喵……", i);
			PICinfo pInfo;
			image mPic;
			stream sPic;
			CHECK_VALID_CONTINUE(pInfo.format != LINK);
			io.PICgetInfo(id, pInfo);
			io.PICextract(id, mPic);
			for(int n = 0; n<mPic.getElemCount(); n++) {
				color clr = mPic.getElem(n);
				color newClr = KoishiImageTool::gradient(clr, keyColorList, para.useProperty);
				if(para.remainAlpha) {
					newClr.alpha = clr.alpha;
				}
				mPic.setElem(n, newClr);
			}
			io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
			io.PICreplace(id, pInfo, sPic);
			sPic.release();
			mPic.destory();
			TRACE(NumToCStr(i) + L"\n");
		}
	} else {
		bar.show(cl.size() - 1);
		for(int i = 0; i<cl.size(); i++) {
			bar.setInfo(L"正在处理第" + NumToCStr(i) + L"个颜色喵……", i);
			color clr = cl[i];
			color newClr = KoishiImageTool::gradient(clr, keyColorList, para.useProperty);
			if(para.remainAlpha) {
				newClr.alpha = clr.alpha;
			}
			cl[i] = newClr;
			io.CLRreplace(i, newClr, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
		}
	}
	updateModified();
	updateColorTable();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureColor(){
	// TODO: 在此添加命令处理程序代码
	if(io.version == V5){
		MessageBox(L"此功能不适用于V5喵！",L"提示喵");
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
			StartThreadFunc(PictureColor, dlg.out);
		}
	}
}

DefineThreadFunc(CExRabbitDlg, PictureColor, ModalAdjustColor::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	//V2处理线程
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在处理第" + NumToCStr(id) + L"帧喵……", i);
		PICinfo pInfo;
		image mPic;
		stream sPic;
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		CHECK_VALID_CONTINUE(id != crtPICid);
		io.PICgetInfo(id, pInfo);
		io.PICextract(id, mPic);
		for(int n = 0; n<mPic.getElemCount(); n++) {
			color clr = mPic.getElem(n);
			colorHSV ch;
			clr.getHSV(ch);
			clr.moveH(para.H * 180 / 100);
			clr.moveS((para.S >= 0) ? (double)para.S / 100 * (1 - ch.S) : (double)para.S / 100 * ch.S);
			clr.moveV((para.V >= 0) ? (double)para.V / 100 * (1 - ch.V) : (double)para.V / 100 * ch.V);
			clr.moveR((para.R >= 0) ? para.R*(0xff - clr.R) / 100 : para.R*clr.R / 100);
			clr.moveG((para.R >= 0) ? para.G*(0xff - clr.G) / 100 : para.G*clr.G / 100);
			clr.moveB((para.R >= 0) ? para.B*(0xff - clr.B) / 100 : para.B*clr.B / 100);
			clr.moveA((para.a >= 0) ? para.a*(0xff - clr.alpha) / 100 : para.a*clr.alpha / 100);
			mPic.setElem(n, clr);
		}
		io.PICpreprocess(mPic, sPic, pInfo, pInfo.format);
		io.PICreplace(id, pInfo, sPic);
		sPic.release();
		mPic.destory();
		TRACE(NumToCStr(i) + L"\n");
	}
	updateModified();
	updateColorTable();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureMark(){
	// TODO: 在此添加命令处理程序代码
	if(io.version == V5){
		MessageBox(L"此功能不适用于V5喵！",L"提示喵");
		return;
	}
	ModalAddMark dlg;
	dlg.in.version = io.version;
	dlg.in.list = cl;
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(PictureMark, dlg.out);
	}
}

DefineThreadFunc(CExRabbitDlg, PictureMark, ModalAddMark::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在处理第" + NumToCStr(id) + L"帧喵……", i);
		PICinfo pInfo;
		image oldPic, newPic;
		stream sPic;
		point markPoint;
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		io.PICgetInfo(id, pInfo);
		switch(para.operate) {
		case 1:
			markPoint = point(para.xDelta, para.yDelta) - pInfo.basePt;
			break;
		case 2:
			markPoint = point(para.xDelta, para.yDelta);
			break;
		case 3:
			markPoint = point(para.xDelta + pInfo.picSize.W, para.yDelta);
			break;
		case 4:
			markPoint = point(para.xDelta, para.yDelta + pInfo.picSize.H);
			break;
		case 5:
			markPoint = point(para.xDelta + pInfo.picSize.W, para.yDelta + pInfo.picSize.H);
			break;
		}
		CString fullString = para.text;
		CString subString;
		CString markString = L"";
		int findLeftBracket, findRightBracket;
		while(1) {
			findLeftBracket = fullString.Find('[');
			findRightBracket = fullString.Find(']');
			if(findLeftBracket < 0 || findRightBracket < 0 || findRightBracket < findLeftBracket) {
				markString += fullString;
				break;
			}
			AfxExtractSubString(subString, fullString, 0, '[');
			markString += subString;
			AfxExtractSubString(subString, fullString, 1, '[');
			if(subString.Left(1) == L"F") {
				markString += NumToCStr(id);
			}
			if(subString.Left(1) == L"I") {
				markString += GetTail(StrToCStr(no.entry[crtIMGid].comment));
			}
			if(subString.Left(1) == L"X") {
				markString += NumToCStr(pInfo.basePt.X);
			}
			if(subString.Left(1) == L"Y") {
				markString += NumToCStr(pInfo.basePt.Y);
			}
			subString = fullString.Right(fullString.GetLength() - findRightBracket - 1);
			fullString = subString;
		}

		if(io.version == V2) {
			io.PICextract(id, oldPic);
			KoishiExpand::KoishiMarkTool::ImageMarking(
				oldPic, newPic, CStrToStr(markString), markPoint, para.useColor);
			if(markPoint.X < 0) {
				pInfo.basePt.X += markPoint.X;
			}
			if(markPoint.Y < 0) {
				pInfo.basePt.Y += markPoint.Y;
			}
			io.PICpreprocess(newPic, sPic, pInfo, pInfo.format);
		} else {
			io.PICextractIndexImage(id, oldPic);
			KoishiExpand::KoishiMarkTool::ImageMarking(
				oldPic, newPic, CStrToStr(markString), markPoint, color(para.useColorID, 0, 0, 0));
			if(markPoint.X < 0) {
				pInfo.basePt.X += markPoint.X;
			}
			if(markPoint.Y < 0) {
				pInfo.basePt.Y += markPoint.Y;
			}
			io.PICpreprocessIndexImage(newPic, sPic, pInfo);
		}
		io.PICreplace(id, pInfo, sPic);
		oldPic.destory();
		newPic.destory();
		sPic.release();
		updatePICterm(id);
	}
	updateModified();
	updateColorTable();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureGetPng(){
	// TODO: 在此添加命令处理程序代码
	CHECK_VALID(crtPICid >= 0);
	StartThreadFunc(PictureGetPNG, SINGLE_SELECT);
}

void CExRabbitDlg::OnMenuPictureGetPngPatch(){
	// TODO: 在此添加命令处理程序代码
	StartThreadFunc(PictureGetPNG, MULTI_SELECT);
}

DefineThreadFunc(CExRabbitDlg, PictureGetPNG, INT) {
	processing = 1;
	std::vector<int> targetList;					//待转换目标列表
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		bar.setInfo(L"正在提取第" + NumToCStr(targetList[i]) + L"帧喵……", i);
		CString fileName;
		image mPic;
		if(io.version == V6) {
			fileName = profile.getOutputPath(fileNPKname, fileIMGname, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()) + NumToCStr(targetList[i]) + L".PNG";
		} else {
			fileName = profile.getOutputPath(fileNPKname, fileIMGname) + NumToCStr(targetList[i]) + L".PNG";
		}
		io.PICextract(targetList[i], mPic, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
		KoishiImageTool::makePNG(mPic, CStrToStr(fileName));
		mPic.destory();
	}
	processing = 0;
	MessageBox(L"已保存到文件夹" + profile.getOutputPath(fileNPKname, fileIMGname) + L"里了喵。", L"提示喵");
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureGetGIF(){
	StartThreadFunc(PictureGetGIF, nullptr);
}

DefineThreadFunc(CExRabbitDlg, PictureGetGIF, PVOID){
	processing = 1;
	std::vector<int> targetList;					//待转换目标列表
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, MULTI_SELECT, targetList);
	if(targetList.size() < 1){
		MessageBox(L"请勾选一些帧喵。",L"提示喵");
		processing = 0;
		return;
	}
	bar.show(targetList.size()-1);
	std::vector<image> matList;
	long imgX1, imgX2, imgY1, imgY2;
	io.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
	for(int i=0;i<targetList.size();i++){
		bar.setInfo(L"正在处理第"+NumToCStr(targetList[i])+L"帧喵……",i);
		image mOrigin, mExpanded;
		PICinfo pInfo;
		io.PICgetInfo(io.linkFind(targetList[i]), pInfo); 
		io.PICextract(io.linkFind(targetList[i]), mOrigin, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
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
	bar.setInfo(L"正在生成GIF喵……",targetList.size());
	KoishiImageTool::GIF::GIFobject go;
	go.input(matList, profile.miniSecPerFrame, no.entry[crtIMGid].comment, targetList);
	CString fileName = profile.getOutputPath(fileNPKname,fileIMGname)+NumToCStr(targetList[0])+L".GIF";
	go.makeFile(CStrToStr(fileName));
	processing = 0;
	MessageBox(L"已保存到文件夹"+profile.getOutputPath(fileNPKname,fileIMGname)+L"里了喵。",L"提示喵");
	bar.hide();
}

void CExRabbitDlg::OnMenuTextureChooseAll(){
	// TODO: 在此添加命令处理程序代码
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetCheck(i, TRUE);
}

void CExRabbitDlg::OnMenuTextureChooseInverse(){
	// TODO: 在此添加命令处理程序代码
	for(int i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetCheck(i, 1-GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetCheck(i));
}

void CExRabbitDlg::OnMenuTextureChooseHighline(){
	// TODO: 在此添加命令处理程序代码
	for(int i=0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount(); i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetCheck(i,TRUE);
}

void CExRabbitDlg::OnMenuTextureInsert(){
	// TODO: 在此添加命令处理程序代码
	ModalInsertTexture dlg;
	dlg.in.firstInsert = FALSE;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.TEXgetInfo(crtTEXid, dlg.in.ti);
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(TextureInsert, dlg.out);
	}
}

void CExRabbitDlg::OnMenuTextureInsert2(){
	// TODO: 在此添加命令处理程序代码
	ModalInsertTexture dlg;
	dlg.in.firstInsert = TRUE;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.TEXgetInfo(crtTEXid, dlg.in.ti);
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(TextureInsert, dlg.out);
	}
}

DefineThreadFunc(CExRabbitDlg, TextureInsert, ModalInsertTexture::OUTPUT) {
	processing = 1;
	int insertPos;
	int replacePos;
	image mPic;
	stream sPic;
	TEXinfo tInfo;
	DDSobject DDSHelper;
	//确定处理目标
	switch(para.operate) {
	case 1:
		replacePos = crtTEXid;;
		break;
	case 2:
		insertPos = crtTEXid;
		break;
	case 3:
		insertPos = crtTEXid + 1;
		break;
	case 4:
		insertPos = io.V5_TEXCount;
		break;
	}
	if(crtTEXid < 0) {
		para.operate = 4;
		insertPos = 0;
	}
	//读取资源
	if(para.inputFormat == 1 && para.outputFormat == 1) {
		//如果输入文件是有效的DDS格式，则保留DDS格式并且不做任何转换，仅修改TEXinfo
		stream sOrigin, sCompressed;
		sOrigin.loadFile(CStrToStr(para.fileName));
		sOrigin.ZLIBcompress(sCompressed);
		if(!DDSHelper.load(sOrigin)) {
			MessageBox(L"不是有效的DDS文件喵！");
			return;
		}
		tInfo.dataLength = sOrigin.length;
		tInfo.compressedLength = sCompressed.length;
		tInfo.format = (colorFormat)(DDS_DXT1 + ((DDSHelper.getHeader()->pixelFormat.fourCC - 0x31545844) >> 25));
		tInfo.height = DDSHelper.getHeader()->height;
		tInfo.width = DDSHelper.getHeader()->width;
		tInfo.reserved = 1;
		if(para.operate == 1) {
			tInfo.ID = replacePos;
			io.TEXreplace(replacePos, tInfo, sCompressed);
		} else {
			tInfo.ID = insertPos;
			io.TEXinsert(insertPos, tInfo, sCompressed);
		}
		sOrigin.release();
		sCompressed.release();
		updateTEXlist();
	} else {
		//转化为PNG再插入
		switch(para.inputFormat) {
		case 0:
			mPic.create(1, 1);
			mPic.fill(0);
			break;
		case 1:
			KoishiImageTool::loadPNG(mPic, CStrToStr(para.fileName));
			break;
		case 2:
			DDSHelper.loadFile(CStrToStr(para.fileName));
			DDSHelper.uncompress(mPic);
			break;
		}
		colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, DDS_DXT5, ARGB8888, ARGB4444, ARGB1555};
		io.TEXpreprocess(mPic, sPic, tInfo, outputFormatByCtrl[para.outputFormat]);
		mPic.destory();
		if(para.operate == 1) {
			tInfo.ID = replacePos;
			io.TEXreplace(replacePos, tInfo, sPic);
		} else {
			tInfo.ID = insertPos;
			io.TEXinsert(insertPos, tInfo, sPic);
		}
		updateTEXlist();
	}
	sPic.release();
	mPic.destory();
	updateModified();
	updateInfo();
	draw();
	processing = 0;
	bar.hide();
}

void CExRabbitDlg::OnMenuTextureDelete(){
	// TODO: 在此添加命令处理程序代码
	int i, row = crtTEXid;
	io.TEXremove(row);
	GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->DeleteItem(row);
	for(i=0;i<io.V5_TEXCount;i++){
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetItemText(i,0,NumToCStr(i));
	}
	updateModified();
	updateInfo();
}
void CExRabbitDlg::OnMenuTextureDeletePatch(){
	// TODO: 在此添加命令处理程序代码
	int i = 0;
	for(i=io.V5_TEXCount-1;i>=0;i--){
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetCheck(i)){
			io.PICremove(i);
			GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->DeleteItem(i);
		}
	}
	for(i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_DDS)->SetItemText(i,0,NumToCStr(i));//更新序号
	updateModified();
	updateInfo();
}
void CExRabbitDlg::OnMenuTextureGetPng(){
	// TODO: 在此添加命令处理程序代码
	CHECK_VALID(crtTEXid >= 0);
	StartThreadFunc(TextureGetPNG, SINGLE_SELECT);
}
void CExRabbitDlg::OnMenuTextureGetPngPatch(){
	// TODO: 在此添加命令处理程序代码
	StartThreadFunc(TextureGetPNG, MULTI_SELECT);
}
void CExRabbitDlg::OnMenuTextureGetOrigin(){
	// TODO: 在此添加命令处理程序代码
	CHECK_VALID(crtTEXid >= 0);
	StartThreadFunc(TextureGetOrigin, SINGLE_SELECT);
}
void CExRabbitDlg::OnMenuTextureGetOriginPatch(){
	// TODO: 在此添加命令处理程序代码
	StartThreadFunc(TextureGetOrigin, MULTI_SELECT);
}
DefineThreadFunc(CExRabbitDlg, TextureGetPNG, INT) {
	processing = 1;
	std::vector<int> targetList;					//待转换目标列表
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS), crtTEXid, para, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		bar.setInfo(L"正在提取第" + NumToCStr(targetList[i]) + L"纹理集喵……", i);
		CString fileName;
		image mPic;
		fileName = profile.getOutputPath(fileNPKname, fileIMGname) + L"Texture-" + NumToCStr(targetList[i]) + L".PNG";
		io.TEXextract(targetList[i], mPic);
		KoishiImageTool::makePNG(mPic, CStrToStr(fileName));
		mPic.destory();
	}
	processing = 0;
	bar.hide();
}

DefineThreadFunc(CExRabbitDlg, TextureGetOrigin, INT) {
	processing = 1;
	std::vector<int> targetList;					//待转换目标列表
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS), crtTEXid, para, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		bar.setInfo(L"正在提取第" + NumToCStr(targetList[i]) + L"纹理集喵……", i);
		CString fileName;
		stream sCompressed, sDDS;
		fileName = profile.getOutputPath(fileNPKname, fileIMGname) + L"Texture-" + NumToCStr(targetList[i]) + L".dds";
		io.TEXgetData(targetList[i], sCompressed);
		sCompressed.ZLIBuncompress(sDDS);
		sDDS.makeFile(CStrToStr(fileName));
		sDDS.release();
		sCompressed.release();
	}
	processing = 0;
	bar.hide();
	MessageBox(L"已保存到文件夹" + profile.getOutputPath(fileNPKname, fileIMGname) + L"里了。", L"提示喵");
}


void CExRabbitDlg::OnToolAvatar(){
	if(toolAvatar.loading)
		return;
	ToolAvatarCharacterSelection mySelection;
	if(IDOK == mySelection.DoModal()){
		MOVEW(toolAvatar);
		toolAvatar.ShowWindow(SW_SHOW);
		toolAvatar.chooseCharacter((AvatarCharacter)mySelection.output);
	}
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
	ToolDownload(this).DoModal();
}


void CExRabbitDlg::OnToolForceExtract(){
	MOVEW(toolForceEx);
	toolForceEx.ShowWindow(SW_SHOW);
	toolForceEx.m_pProc.SetRange32(0,100);
}

void CExRabbitDlg::OnToolOpenOutputFolder(){
	ShellExecute(NULL, L"open", profile.getOutputPath(), NULL, NULL, SW_SHOWNORMAL);
}

void CExRabbitDlg::OnToolsPatchOperate(){
	ToolPatch dlg;
	dlg.p = &profile;
	dlg.DoModal();
}

void CExRabbitDlg::OnToolsAvatarMark(){
	ToolAvatarMark dlg;
	dlg.DoModal();
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
	MessageBox(L"请右键点击IMG列表中的一个IMG，然后选择“设置为对比IMG对象”来进行设置喵！", L"提示喵");
}


void CExRabbitDlg::OnDrawSetCompare2(){
	// TODO: 在此添加命令处理程序代码
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		ioComp.release();
		if(ioComp.loadFile(CStrToStr(fileName))){
			MessageBox(L"设置完毕喵！");
		}else{
			MessageBox(L"读取失败喵！");
			return;
		}
	}
	drawPara.compareMode = TRUE;
	updateToolButtonStatus();
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawCompareEnabled(){
	if(ioComp.version == 0){
		if(IDYES == MessageBox(L"还没有设置对比IMG，要设置喵？",L"提示喵", MB_YESNO)){
			OnDrawSetCompare2();
		}
		return;
	}
	drawPara.compareMode = TRUE;
	updateToolButtonStatus();
	if(!playing)
		draw();
}


void CExRabbitDlg::OnDrawCompareDisabled(){
	drawPara.compareMode = FALSE;
	updateToolButtonStatus();
	if(!playing)
		draw();
}



void CExRabbitDlg::OnToolsNpkLock(){
	ModalLock ml;
	ml.DoModal();
}



void CExRabbitDlg::OnMenuColorTableClassical(){
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"对索引贴图修改调色板颜色会导致颜色混乱，确定喵？", L"提示喵", MB_YESNO)){
			setDefaultColor();
			cl = colorOperatePara.v2Color;
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			for(int i = 0;i<cl.size();i++)
				io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			updateModified();
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
		if(IDYES == MessageBox(L"对索引贴图修改调色板颜色会导致颜色混乱，确定喵？", L"提示喵", MB_YESNO)){
			cl = palette::palette16();
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			for(int i = 0;i<cl.size();i++)
				io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			updateModified();
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
		if(IDYES == MessageBox(L"对索引贴图修改调色板颜色会导致颜色混乱，确定喵？", L"提示喵", MB_YESNO)){
			cl = palette::palette256();
			while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
			for(int i = 0;i<cl.size();i++)
				io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			updateModified();
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
	// TODO: 在此添加命令处理程序代码
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"对索引贴图修改调色板颜色会导致颜色混乱，确定喵？", L"提示喵", MB_YESNO)){
			StartThreadFunc(PickColorFromFrame, nullptr);
		}
	}else{
		StartThreadFunc(PickColorFromFrame, nullptr);
	}
}


void CExRabbitDlg::OnMenuColorTableExtractAllFrame()
{
	// TODO: 在此添加命令处理程序代码
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"对索引贴图修改调色板颜色会导致颜色混乱，确定喵？", L"提示喵", MB_YESNO)){
			StartThreadFunc(PickColorFromImage, nullptr);
		}
	}else{
		StartThreadFunc(PickColorFromImage, nullptr);
	}
}

DefineThreadFunc(CExRabbitDlg, PickColorFromFrame, PVOID) {
	image mat;
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	if(!io.PICextract(crtPICid, mat, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel())) {
		MessageBox(L"解析当前图片失败喵！", L"提示喵");
		return;
	}
	bar.show(100);
	bar.setInfo(L"正在提取颜色喵……", 0);
	for(int i = 0; i<mat.getElemCount(); i++) {
		color clr = mat.getElem(i);
		long clrPos = pal.findColor(clr, 0);
		if(clrPos == -1) {
			pal[0].push_back(clr);
			clrCount.push_back(1);
		} else {
			clrCount[clrPos] ++;
		}
	}
	clrList = pal[0];
	long finalColorCount = MIN(0xFE, pal.getColorCount(0));
	colorList finalColorList;
	bar.show(finalColorCount);
	for(int i = 0; i<finalColorCount; i++) {
		bar.setInfo(L"正在分析颜色喵……", i);
		long maxCount = 0;
		long maxID = -1;
		for(int j = 0; j<clrCount.size(); j++) {
			if(clrCount[j] > maxCount) {
				maxCount = clrCount[j];
				maxID = j;
			}
		}
		finalColorList.push_back(clrList[maxID]);
		clrList.erase(clrList.begin() + maxID);
		clrCount.erase(clrCount.begin() + maxID);
	}
	bar.setInfo(L"正在生成调色板喵……", finalColorCount);
	if(io.version == V4 || io.version == V5 || io.version == V6) {
		cl = KoishiImageTool::nearbySort(finalColorList);
		cl.insert(cl.begin(), color(0, 0, 0, 0));
		while(io.CLRremove(0, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
		for(int i = 0; i<cl.size(); i++)
			io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
		updateModified();
		draw();

	} else {
		cl = KoishiImageTool::nearbySort(finalColorList);
		cl.insert(cl.begin(), color(0, 0, 0, 0));
		colorOperatePara.v2Color = cl;
	}
	updateColorTable();
	bar.hide();
}

DefineThreadFunc(CExRabbitDlg, PickColorFromImage, PVOID){
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	bar.show(io.indexCount);
	for(long getFrame = 0;getFrame<io.indexCount;getFrame ++){
		bar.setInfo(L"正在提取第"+NumToCStr(getFrame+1)+L"帧的颜色喵……", getFrame);
		image mat;
		if(!io.PICextract(getFrame, mat, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel())){
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
	bar.show(finalColorCount);
	for(int i = 0;i<finalColorCount; i++){
		bar.setInfo(L"正在分析颜色喵……", i);
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
	bar.setInfo(L"正在生成调色板喵……", finalColorCount);
	if(io.version == V4 || io.version == V5 || io.version == V6){
		cl = KoishiImageTool::nearbySort(finalColorList);
		cl.insert(cl.begin(), color(0,0,0,0));
		while(io.CLRremove(0,  GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel()));
		for(int i = 0;i<cl.size();i++)
			io.CLRpush(cl[i], GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			updateModified();
			draw();
	}else{
		cl = KoishiImageTool::nearbySort(finalColorList);
		cl.insert(cl.begin(), color(0,0,0,0));
		colorOperatePara.v2Color = cl;
	}
	updateColorTable();
	bar.hide();
}

BOOL CExRabbitDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	if(pMsg->message==WM_MOUSEMOVE){
		m_ttc.RelayEvent(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CExRabbitDlg::OnClose() {
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if(NPKsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = IMGsaveAlert ? ModalSaveWarning::MODIFIED_IMG_NPK : ModalSaveWarning::MODIFIED_NPK;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			IMGsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.saveFile(CStrToStr(fileNPKname));
			IMGsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		case ModalSaveWarning::RETURN_ALL_SAVE:
			no.IMGreplace(crtIMGid, io);
			no.saveFile(CStrToStr(fileNPKname));
			IMGsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		}
	} else {
		
	}
	CDialogEx::OnClose();
}

DefineThreadFunc(CExRabbitDlg, ImageInsertEmpty, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtIMGid;
	IMGobject newIO;
	newIO.create(V2);
	no.IMGinsert(insertPos, newIO, "new_img.img");
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(insertPos, L"new_img.img", getIconIMG(V2));
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageInsertIMG, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtIMGid;
	CFileDialog dlg(true, L"IMG文件(*.IMG)|*.IMG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"IMG文件(*.IMG)|*.IMG||", this);
	TinySetName dlgTiny(this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	dlgTiny.name = Slashing(GetTail(fileName));
	if(IDOK != dlgTiny.DoModal()){
		processing = 0;
		return;
	}
	IMGobject newIO;
	if(!newIO.loadFile(CStrToStr(fileName))) {
		MessageBox(L"这个IMG文件无法识别喵！", L"提示喵");
		processing = 0;
		return;
	}
	no.IMGinsert(insertPos, newIO, CStrToStr(dlgTiny.name));
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(insertPos, GetTail(dlgTiny.name), getIconIMG(newIO.version));
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageInsertNPK, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtIMGid;
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
		IMGobject newIO;
		if(!newNO.IMGextract(i, newIO)) {
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
			no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment);
			countSuccess++;
		} else {
			switch(conflictMethod) {
			case 0:
				//替换
				no.IMGreplace(conflict, newIO);
				countReplace++;
				break;
			case 1:
				//跳过
				countSkip++;
				break;
			case 2:
				//保留
				no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment);
				countSuccess++;
				break;
			case 3:
				//保留并改名
				no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment + "(new)");
				countSuccess++;
				break;
			}
		}
	}
	MessageBox(L"导入完毕喵！总" + NumToCStr(newNO.count) + L"个,添加" + NumToCStr(countSuccess) + L"个,跳过" + NumToCStr(countSkip) + L"个,替换" + NumToCStr(countReplace) + L"个,失败" + NumToCStr(countFail) + L"个喵！", L"提示喵");
	bar.hide();
	updateIMGlist();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageInsertFolder, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtIMGid;
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
	IMGobject newIO;
	int countNPK = 0;
	int countNPKIMG = 0;
	int countIMG = 0;
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
				if(!newNO.IMGextract(i, newIO)) {
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
					no.IMGinsert(insertPos + totalSuccess, newIO, newNO.entry[i].comment);
					countSuccess++;
					totalSuccess++;
				} else {
					switch(conflictMethod) {
					case 0:
						//替换
						no.IMGreplace(conflict, newIO);
						countReplace++;
						break;
					case 1:
						//跳过
						countSkip++;
						break;
					case 2:
						//保留
						no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment);
						countSuccess++;
						totalSuccess++;
						break;
					case 3:
						//保留并改名
						no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment + "(new)");
						countSuccess++;
						totalSuccess++;
						break;
					}
				}
				newIO.release();
			}
			newNO.release();
			countNPK++;
			countNPKIMG += countSuccess;
		}
		if(fileList[fileID].Right(4) == L".img" || fileList[fileID].Right(4) == L".IMG") {
			if(!newIO.loadFile(CStrToStr(pathList[fileID]))) {
				continue;
			}
			bar.setInfo(L"当前插入" + fileList[fileID] + L"喵……", 0);
			CString newPathName = Slashing(fileList[fileID]);
			no.IMGinsert(insertPos + totalSuccess, newIO, CStrToStr(newPathName));
			totalSuccess++;
			newIO.release();
			countIMG++;
		}
	}
	MessageBox(L"导入完毕喵！成功导入了" + NumToCStr(countIMG) + L"个外部IMG对象喵，并从" + NumToCStr(countNPK) + L"个NPK文件中导入了" + NumToCStr(countNPKIMG) + L"个IMG对象喵。", L"提示喵");
	bar.hide();
	updateIMGlist();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageInsertOther, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtIMGid;
	CFileDialog dlg(true, L"所有文件(*.*)|*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"所有文件文件(*.*)|*.*||", this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	no.insert(insertPos, CStrToStr(fileName), CStrToStr(GetTail(fileName)));
	updateIMGlist();
	NPKsaveAlert = true;
	processing = 0;
}

DefineThreadFunc(CExRabbitDlg, ImageReplaceExtern, DWORD) {
	processing = 1;
	CFileDialog dlg(TRUE, L"IMG文件(*.IMG) | *.IMG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"IMG文件(*.IMG)|*.IMG||", this);
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
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
		int id = targetList[i];
		bar.setInfo(L"正在替换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.replace(id, s);
		updateIMGterm(id);
	}
	MessageBox(L"替换完毕喵！");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageReplaceLocal, DWORD) {
	processing = 1;
	TinyIMGSelect dlg;
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
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
		int id = targetList[i];
		bar.setInfo(L"正在替换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.replace2(id, s);
		updateIMGterm(id);
	}
	MessageBox(L"替换完毕喵！");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageReplaceQuote, DWORD) {
	processing = 1;
	TinyIMGSelect dlg;
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
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
		int id = targetList[i];
		bar.setInfo(L"正在替换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.modifyLink(id, dlg.selected);
		updateIMGterm(id);
	}
	MessageBox(L"替换完毕喵！");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}

DefineThreadFunc(CExRabbitDlg, ImageRemove, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
		int id = targetList[targetList.size() - i - 1];
		bar.setInfo(L"正在删除" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		no.IMGremove(id);
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->DeleteItem(id);
	}
	bar.hide();
	updateInfo();
	crtIMGid = -1;
	draw();
	NPKsaveAlert = true;
	processing = 0;
}

DefineThreadFunc(CExRabbitDlg, ImageExtract, DWORD) {
	processing = 1;
	CString filePath = profile.getOutputPath(fileNPKname);
	CString fileName;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
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


DefineThreadFunc(CExRabbitDlg, ImageMakeNPKandSavePatch, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
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
DefineThreadFunc(CExRabbitDlg, ImageDequote, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"正在重新为" + GetTail(StrToCStr(no.entry[id].comment)) + L"分配数据喵……", i);
		if(no.delink(id)) {
			updateIMGterm(id);
		}
	}
	bar.hide();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageHide, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[targetList.size() - 1 - i];
		bar.setInfo(L"正在隐藏" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		IMGobject oldIO, newIO;
		if(!no.IMGextract(id, oldIO)) {
			continue;
		}
		IMGobject::makeEmpty(newIO, oldIO.indexCount);
		no.IMGreplace(id, newIO);
	}
	bar.hide();
	updateInfo();
	NPKsaveAlert = true;
	processing = 0;
}

DefineThreadFunc(CExRabbitDlg, ImageTransToV2, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[targetList.size() - 1 - i];
		bar.setInfo(L"正在转换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		std::vector<IMGobject> ioOutList;
		IMGobject ioIn;
		if(!no.IMGextract(id, ioIn))
			continue;
		ioIn.convertToV2(ioOutList, ARGB8888);
		for(int p = 0; p < ioOutList.size(); p++) {
			if(p == 0) {
				no.IMGreplace(id, ioOutList[p]);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconIMG(V2), 0, 0, 0);
			} else {
				str newName = KoishiAvatar::formatAvatarIDplusBy(no.entry[id].comment, p);
				no.IMGinsert(id + p, ioOutList[p], newName);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(id + p, GetTail(StrToCStr(newName)), getIconIMG(V2));
			}
		}
	}
	bar.hide();
	io.release();
	no.IMGextract(crtIMGid, io);
	switchIMGver(io.version);
	updatePIClist();
	updateInfo();
	NPKsaveAlert = true;
	processing = 0;
}

DefineThreadFunc(CExRabbitDlg, ImageV6TransToV4, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[targetList.size() - 1 - i];
		bar.setInfo(L"正在转换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		std::vector<IMGobject> ioOutList;
		IMGobject ioIn;
		if(!no.IMGextract(id, ioIn))
			continue;
		if(ioIn.version != V6)
			continue;
		ioIn.convertToV4(ioOutList, colorList(), true);
		for(int p = 0; p < ioOutList.size(); p++) {
			if(p == 0) {
				no.IMGreplace(id, ioOutList[p]);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconIMG(V4), 0, 0, 0);
			} else {
				str newName = KoishiAvatar::formatAvatarIDplusBy(no.entry[id].comment, p);
				no.IMGinsert(id + p, ioOutList[p], newName);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(id + p, GetTail(StrToCStr(newName)), getIconIMG(V4));
			}
		}
	}
	bar.hide();
	io.release();
	no.IMGextract(crtIMGid, io);
	switchIMGver(io.version);
	updatePIClist();
	GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(0);
	updateColorTable();
	updateInfo();
	NPKsaveAlert = true;
	processing = 0;
}

DefineThreadFunc(CExRabbitDlg, ImageTransform, ModalTransform::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG), crtIMGid, para.target - 1, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[targetList.size() - 1 - i];
		bar.setInfo(L"正在转换" + GetTail(StrToCStr(no.entry[id].comment)) + L"喵……", i);
		std::vector<IMGobject> ioOutList;
		IMGobject ioIn;
		if(!no.IMGextract(id, ioIn)) {
			continue;
		}
		switch(para.version) {
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
		for(int p = 0; p < ioOutList.size(); p++) {
			if(p == 0) {
				no.IMGreplace(id, ioOutList[p]);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(id, 0, LVIF_IMAGE, NULL, getIconIMG(para.version), 0, 0, 0);
			} else {
				str newName = KoishiAvatar::formatAvatarIDplusBy(no.entry[id].comment, p);
				no.IMGinsert(id + p, ioOutList[p], newName);
				GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(id + p, GetTail(StrToCStr(newName)), getIconIMG(para.version));
			}
		}
	}
	bar.hide();
	io.release();
	no.IMGextract(crtIMGid, io);
	switchIMGver(io.version);
	updatePIClist();
	updateTEXlist();
	if(para.version == V4 || para.version == V5 || para.version == V6) {
		GET_CTRL(CComboBox, IDC_COMBO_PRO)->SetCurSel(0);
		updateColorTable();
	}
	updateInfo();
	NPKsaveAlert = true;
	processing = 0;
}

DefineThreadFunc(CExRabbitDlg, ImageAutoSort, PVOID) {
	int i, j;
	queue wList1, wList2, qList;
	std::vector<NPKentry> oldEntry = no.entry;
	//计算每个部件的权重
	extern dword layerSequence[100][2];
	for(i = 0; i<no.count; i++) {
		AvatarPart ap;
		AvatarLayerFlag layer;
		str IMGpath = no.entry[i].comment;
		str::size_type st = IMGpath.find_last_of('/');
		str IMGname = (st == str::npos) ? IMGpath : IMGpath.substr(st + 1);
		if(IMGname.size() < 6) {
			wList1.push_back(1000);
			continue;
		}
		if(IMGname.find("awake") != str::npos) {
			wList1.push_back(1000);
			continue;
		}
		if(IMGname.find("mask") != str::npos) {
			wList1.push_back(1000);
			continue;
		}
		if(IMGname.find(".img") == str::npos) {
			wList1.push_back(1000);
			continue;
		}
		//名称解析
		long ID = 0;
		BOOL isTN = FALSE;
		BOOL isFlow = FALSE;
		str mainStr;
		str IDstr;
		str layStr;
		str::size_type is = 0;
		if(IMGname.substr(0, 4) == "(tn)") {
			isTN = TRUE;
			is += 4;
		}
		while(is < IMGname.size() && (IMGname[is] < '0' || IMGname[is] > '9')) {
			mainStr.push_back(IMGname[is]);
			is++;
		}
		while(is < IMGname.size() && IMGname[is] >= '0' && IMGname[is] <= '9') {
			IDstr.push_back(IMGname[is]);
			is++;
		}
		while(is < IMGname.size() && IMGname[is] != '.') {
			layStr.push_back(IMGname[is]);
			is++;
		}
		//主域解析
		if(IDstr.size() < 4) {
			wList1.push_back(1000);
			continue;
		}
		//图层信息不可能使用超过4个字符表示，mask除外
		if(layStr.size() > 4) {
			wList1.push_back(1000);
			continue;
		}
		if(mainStr.find("coat") != str::npos) {
			ap = APART_COAT;
		} else if(mainStr.find("pants") != str::npos) {
			ap = APART_PANTS;
		} else if(mainStr.find("cap") != str::npos) {
			ap = APART_CAP;
		} else if(mainStr.find("hair") != str::npos) {
			ap = APART_HAIR;
		} else if(mainStr.find("shoes") != str::npos) {
			ap = APART_SHOES;
		} else if(mainStr.find("belt") != str::npos) {
			ap = APART_BELT;
		} else if(mainStr.find("face") != str::npos) {
			ap = APART_FACE;
		} else if(mainStr.find("neck") != str::npos) {
			ap = APART_NECK;
		} else if(mainStr.find("body") != str::npos) {
			ap = APART_BODY;
		} else {
			ap = APART_WEAPON;
		}
		if(ap == APART_BODY) {
			wList1.push_back(999);
			continue;
		}
		memset(layer, 0, sizeof(AvatarLayerFlag));
		memcpy(layer, layStr.data(), layStr.size());
		for(int li = 0; li < 100; li++) {
			if(layerSequence[li][0] == APART_BODY) {
				wList1.push_back(1000);
				break;
			}
			if(ap == layerSequence[li][0] && *(dword*)layer == layerSequence[li][1]) {
				wList1.push_back(li);
				break;
			}
		}
	}
	//插入排序
	for(i = 0; i<wList1.size(); i++) {
		j = 0;
		while(j<wList2.size()) {
			if(wList1[i] < wList2[j]) {
				j++;
			} else {
				break;
			}
		}
		if(j < wList2.size()) {
			wList2.insert(wList2.begin() + j, wList1[i]);
			qList.insert(qList.begin() + j, i);
		} else {
			wList2.push_back(wList1[i]);
			qList.push_back(i);
		}
	}
	for(i = 0; i<qList.size(); i++)
		no.entry[i] = oldEntry[qList[qList.size() - 1 - i]];
	updateIMGlist();
	updateInfo();
	NPKsaveAlert = true;
}

DefineThreadFunc(CExRabbitDlg, ImageMix, ModalAdvancedMix::OUTPUT) {
	int i, k;
	int imgCount = 0;
	std::vector<int> mixLayer = getSelected(IDC_LIST_IMG, MULTI_SELECT);						//勾选图层
	imgCount = mixLayer.size();
	if(imgCount == 0) {
		MessageBox(L"没有勾选任何图层喵", L"提示喵");
		return;
	}
	bar.show(100);
	bar.setInfo(L"准备拼合喵……", 0);
	IMGobject *ioList = new IMGobject[imgCount];
	IMGobject newIO;
	newIO.create(V2);
	for(i = 0; i<imgCount; i++) {
		no.IMGextract(mixLayer[i], ioList[i]);
	}
	int maxFrameCount = 0;
	for(i = 0; i<imgCount; i++) {
		if(ioList[i].indexCount> maxFrameCount)
			maxFrameCount = ioList[i].indexCount;
	}
	image mat, mat2, matf;
	stream s;
	PICinfo pi;
	point ptLT, ptRB, ptLTtemp, ptRBtemp;//左上角右下角的点，右下角的点包含在图片内
	std::vector<int> mLeft, mTop, mRight, mBottom;
	bar.setMax(maxFrameCount);
	for(k = 0; k<maxFrameCount; k++) {
		bar.setInfo(L"正在拼合第" + NumToCStr(k + 1) + L"帧喵(总" + NumToCStr(maxFrameCount) + L"帧)……", k);
		mLeft.clear();
		mTop.clear();
		mRight.clear();
		mBottom.clear();
		for(i = 0; i<imgCount; i++) {
			if(ioList[i].PICgetInfo(k, pi)) {
				int k1 = k;
				if(pi.format == LINK) {
					k1 = ioList[i].linkFind(k);
				}
				ioList[i].PICgetInfo(k1, pi);
				CHECK_VALID_CONTINUE(pi.picSize.area() > 1);
				mLeft.push_back(pi.basePt.X);
				mTop.push_back(pi.basePt.Y);
				mRight.push_back(pi.basePt.X + pi.picSize.W - 1);
				mBottom.push_back(pi.basePt.Y + pi.picSize.H - 1);
			}
		}
		//2.5新增：考虑所有IMG内帧全空的情形
		if(mLeft.size() == 0) {
			pi.basePt = point(0, 0);
			pi.comp = COMP_NONE;
			pi.format = ARGB8888;
			pi.dataSize = 4;
			pi.picSize = size(1, 1);
			pi.frmSize = size(1, 1);
			s.allocate(4);
			s.pushDWord(0);
			newIO.PICpush(pi, s);
			s.release();
			continue;
		}
		int tLeft = 100000;
		int tTop = 100000;
		int tRight = -100000;
		int tBottom = -100000;
		for(i = 0; i<mLeft.size(); i++) {
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
		matf.create(tBottom - tTop + 1, tRight - tLeft + 1);
		//开始拼合，必须从底层开始拼合
		for(i = imgCount - 1; i>=0; i--) {
			if(ioList[i].PICgetInfo(k, pi)) {
				int k1 = k;
				if(pi.format == LINK) {
					k1 = ioList[i].linkFind(k);
				}
				ioList[i].PICgetInfo(k1, pi);
				CHECK_VALID_CONTINUE(pi.picSize.area() > 1);
				ioList[i].PICextract(k1, mat);
				//预处理步骤
				switch(para.preprocessing[i]) {
				case 1:
					mat.loseBlack(5);
					break;
				case 2:
					mat.turnGray();
					break;
				case 3:
					mat.getTransparented();
					break;
				case 4:
					mat.getDarken();
					break;
				case 5:
					mat.getBrighten();
					break;
				}
				mat2.create(
					pi.basePt.Y - ptLT.Y + pi.picSize.H + 10,
					pi.basePt.X - ptLT.X + pi.picSize.W + 10
					);
				mat2.putFore(mat);
				mat2.moveHonz(pi.basePt.X - ptLT.X);
				mat2.moveVert(pi.basePt.Y - ptLT.Y);
				colorMethod cm = LAY;
				switch(para.mixMethod[i]) {
				case 1:
					cm = DARKEN;
					break;
				case 2:
					cm = MULTIPLY;
					break;
				case 3:
					cm = COLORBURN;
					break;
				case 4:
					cm = LINEARBURN;
					break;
				case 5:
					cm = LIGHTEN;
					break;
				case 6:
					cm = SCREEN;
					break;
				case 7:
					cm = COLORDODGE;
					break;
				case 8:
					cm = LINEARDODGE;
					break;
				}
				matf.putFore(mat2, cm);
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
	no.IMGpush(newIO, "mixed.img");
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(imgCount, L"mixed.img", getIconIMG(newIO.version));
	bar.hide();
	updateInfo();
	updateIMGlist();
	NPKsaveAlert = true;
	delete[] ioList;
}
void CExRabbitDlg::OnMenuImageInertEmpty() {
	StartThreadFunc(ImageInsertEmpty, 0);
}

void CExRabbitDlg::OnMenuImageInertIMG() {
	StartThreadFunc(ImageInsertIMG, 0);
}

void CExRabbitDlg::OnMenuImageInertNPK() {
	StartThreadFunc(ImageInsertNPK, 0);
}

void CExRabbitDlg::OnMenuImageInertFolder() {
	StartThreadFunc(ImageInsertFolder, 0);
}

void CExRabbitDlg::OnMenuImageInertOther() {
	StartThreadFunc(ImageInsertOther, 0);
}


void CExRabbitDlg::OnMenuImageInertEmptyBlank() {
	StartThreadFunc(ImageInsertEmpty, 1);
}


void CExRabbitDlg::OnMenuImageInertIMGBlank() {
	StartThreadFunc(ImageInsertIMG, 1);
}


void CExRabbitDlg::OnMenuImageInertNPKBlank() {
	StartThreadFunc(ImageInsertNPK, 1);
}


void CExRabbitDlg::OnMenuImageInertFolderBlank() {
	StartThreadFunc(ImageInsertFolder, 1);
}


void CExRabbitDlg::OnMenuImageInertOtherBlank() {
	StartThreadFunc(ImageInsertOther, 1);
}


void CExRabbitDlg::OnMenuImageReplaceIMG() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageReplaceExtern, SINGLE_SELECT);
}

void CExRabbitDlg::OnMenuImageReplaceCopy() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageReplaceLocal, SINGLE_SELECT);
}

void CExRabbitDlg::OnMenuImageReplaceQuote() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageReplaceQuote, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageReplaceImgPatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageReplaceExtern, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageReplaceCopyPatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageReplaceLocal, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageReplaceQuotePatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageReplaceQuote, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageRemove() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageRemove, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageRemovePatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageRemove, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageExtract() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageExtract, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageExtractPatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageExtract, MULTI_SELECT);
}

void CExRabbitDlg::OnMenuImageSave() {
	// TODO: 在此添加命令处理程序代码
	CHECK_VALID(crtIMGid >= 0);
	CString defExt = _T("所有文件(*.*)|*.*");
	CString extFilter = _T("所有文件(*.*)|*.*||");
	CFileDialog dlg(FALSE, defExt, Underlining(StrToCStr(no.entry[crtIMGid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		no.extract(crtIMGid, CStrToStr(dlg.GetPathName()));
		MessageBox(_T("保存完毕喵！"));
	}
}

void CExRabbitDlg::OnMenuImageSaveNPK() {
	// TODO:  在此添加命令处理程序代码
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageMakeNPKandSavePatch, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageSaveNPKPatch() {
	// TODO:  在此添加命令处理程序代码
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageMakeNPKandSavePatch, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageCopyResource() {
	// TODO:  在此添加命令处理程序代码
	CHECK_VALID(crtIMGid >= 0);
	stream sTemp;
	no.extract(crtIMGid, sTemp);
	no.insert(crtIMGid + 1, sTemp, no.entry[crtIMGid].comment + "(new)");
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(crtIMGid + 1, L"", getIconIMG(V2));
	updateIMGterm(crtIMGid + 1);
	NPKsaveAlert = true;
}


void CExRabbitDlg::OnMenuImageCopyQuote() {
	// TODO:  在此添加命令处理程序代码
	CHECK_VALID(crtIMGid >= 0);
	no.insertLink(crtIMGid + 1, crtIMGid, no.entry[crtIMGid].comment + "(new)");
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(crtIMGid + 1, L"", getIconIMG(V2));
	updateIMGterm(crtIMGid + 1);
	NPKsaveAlert = true;
}


void CExRabbitDlg::OnMenuImageRename() {
	CHECK_VALID(crtIMGid >= 0);
	ModalRename dlg;
	dlg.oldName = StrToCStr(no.entry[crtIMGid].comment);
	if(IDOK == dlg.DoModal()){
		no.rename(crtIMGid,  CStrToStr(dlg.newName));
		updateInfo();
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItemText(crtIMGid, 0, GetTail(dlg.newName));
		fileIMGname = dlg.newName;
		NPKsaveAlert = true;
	}
}


void CExRabbitDlg::OnMenuImageDequote() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageDequote, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageDequotePatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageDequote, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageTransformTo2() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageTransToV2, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageTransformTo4() {
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageV6TransToV4, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageTransformTo2Patch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageTransToV2, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageTransformTo4Patch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageV6TransToV4, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageTransformAdvanced() {
	ModalTransform dlg;
	dlg.in.contextIO = &io;
	dlg.in.contextColorList = cl;
	dlg.in.currentFrame = crtPICid;
	dlg.in.currentPalette = GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel();
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(ImageTransform, dlg.out);
	}
}


void CExRabbitDlg::OnMenuImageHide() {
	StartThreadFunc(ImageHide, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageHideContent() {
	StartThreadFunc(ImageHide, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageHidePatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageHide, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageHideContentPatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"没有勾选的IMG对象喵！");
		return;
	}
	StartThreadFunc(ImageHide, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageClipboardCopy() {
	CHECK_VALID(crtIMGid >= 0);
	stream sTemp;
	if(no.extract(crtIMGid, sTemp)){
		noClip.push(sTemp, no.entry[crtIMGid].comment);
		MessageBox(L"已将该IMG插入到剪辑库中喵！",L"提示喵");
	}else{
		MessageBox(L"无法插入剪辑库中喵！",L"提示喵");
	}
}


void CExRabbitDlg::OnMenuImageClipboardInsert() {
	CHECK_VALID(crtIMGid >= 0);
	if(noClip.count == 0){
		MessageBox(L"剪辑库里还没有IMG喵！",L"提示喵");
		return;
	}
	stream sTemp;
	TinyClipBoard dlg;
	dlg.ptrClipNo = &noClip;
	if(IDOK == dlg.DoModal()){
		noClip.extract(dlg.selectID, sTemp);
		no.insert(crtIMGid, sTemp, noClip.entry[dlg.selectID].comment);
		updateIMGlist();
		NPKsaveAlert = true;
	}
}


void CExRabbitDlg::OnMenuImageClipboardReplace() {
	CHECK_VALID(crtIMGid >= 0);
	if(noClip.count == 0){
		MessageBox(L"剪辑库里还没有IMG喵！",L"提示喵");
		return;
	}
	stream sTemp;
	TinyClipBoard dlg;
	dlg.ptrClipNo = &noClip;
	if(IDOK == dlg.DoModal()){
		noClip.extract(dlg.selectID, sTemp);
		no.replace(crtIMGid, sTemp);
		NPKsaveAlert = true;
	}
}


void CExRabbitDlg::OnMenuImageSetCompare() {
	CHECK_VALID(crtIMGid >= 0);
	ioComp.release();
	no.IMGextract(crtIMGid, ioComp);
	MessageBox(L"已设定对比IMG。",L"提示喵");
	drawPara.compareMode = TRUE;
	updateToolButtonStatus();
}

void CExRabbitDlg::OnMenuImageSelectAll() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount(); i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetCheck(i, TRUE);
}


void CExRabbitDlg::OnMenuImageSelectReverse() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount(); i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetCheck(i, 1-GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetCheck(i));
}


void CExRabbitDlg::OnMenuImageSelectHighline() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemCount(); i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetCheck(i,TRUE);
}


void CExRabbitDlg::OnMenuImageMoveUp() {
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
	NPKsaveAlert = true;
}


void CExRabbitDlg::OnMenuImageMoveDown() {
	int row = crtIMGid;
	CHECK_VALID(row>=0);
	CHECK_VALID(row<no.count - 1);
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
	NPKsaveAlert = true;
}


void CExRabbitDlg::OnMenuImageMix() {
	// TODO:  在此添加命令处理程序代码
	if(getSelected(IDC_LIST_IMG, MULTI_SELECT).size() == 0) {
		MessageBox(L"没有勾选任何图层喵", L"提示喵");
		return;
	};
	ModalAdvancedMix::OUTPUT para;
	for(int i = 0; i < no.count; i++) {
		if(GET_CTRL(CListCtrl, IDC_LIST_IMG)->GetCheck(i)) {
			para.mixMethod.push_back(0);
			para.preprocessing.push_back(0);
		}
	}
	StartThreadFunc(ImageMix, para);
}


void CExRabbitDlg::OnMenuImageMixAdvanced() {
	// TODO:  在此添加命令处理程序代码
	if(getSelected(IDC_LIST_IMG, MULTI_SELECT).size() == 0) {
		MessageBox(L"没有勾选任何图层喵", L"提示喵");
		return;
	};
	ModalAdvancedMix dlg;
	for(int i = 0; i < no.count; i++) {
		if(GET_CTRL(CListCtrl, IDC_LIST_IMG)->GetCheck(i)) {
			dlg.in.layerName.push_back(no.entry[i].comment);
		}
	}
	if(IDOK == dlg.DoModal()) {
		StartThreadFunc(ImageMix, dlg.out);
	}
}


void CExRabbitDlg::OnMenuImageAutoSort() {
	// TODO:  在此添加命令处理程序代码
	StartThreadFunc(ImageAutoSort, nullptr);
}


void CExRabbitDlg::OnToolsStat() {
	// TODO:  在此添加命令处理程序代码
	ToolStat dlg;
	dlg.DoModal();
}
