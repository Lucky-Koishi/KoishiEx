
// ExRabbitDlg.cpp : ʵ���ļ�
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

// CExRabbitDlg ��Ϣ�������

BOOL CExRabbitDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	//���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//////////////////////////////////
	SetWindowText(_T(VERSION_STR));
	SetWindowPos(NULL,0,0,width,height,SWP_NOZORDER|SWP_NOMOVE);
	CRect rc;
	GetClientRect(rc);
	adjustWindow(rc.Width(), rc.Height());
	// �ؼ���С����
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
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->EasyInsertColumn(L"IMG��,200");
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(L"������ʾNPK�ļ�����Ϣ");
	GET_CTRL(CEdit, IDC_EDIT_IMGINFO)->SetWindowText(L"������ʾIMG�ļ�����Ϣ");
	switchIMGver(V2);
	
	StartThreadFunc(Play, nullptr);
	StartThreadFunc(Lazy, nullptr);

	ioComp.create(V2);
	noClip.create();

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
	// ����֡�б�
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
					cstr += L"����"+NumToCStr(io.PICcontent[i].TEXusing)+L":"+PtToCStr(io.PICcontent[i].TEXpointLT)+L"-"+PtToCStr(io.PICcontent[i].TEXpointRB);
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
	//ֻ����pos
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
	//����������Ϣ��
	////////////////////////////////
	//NPK 
	CString cstr;
	cstr = L"�ļ�����"+GetTail(fileNPKname)+L"\r\n";
	cstr += L"��С��"+NumToCStr(no.getSize())+L"�ֽ�\r\n";
	cstr += L"��Ŀ����"+NumToCStr(no.count);
	cstr += (crtIMGid  == -1) ? L"" : ( L"/"  + NumToCStr(crtIMGid));
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(cstr);

	cstr = IMGsaveAlert ? L"IMG״̬���ѱ䶯\r\n" : L"IMG״̬��δ�䶯\r\n";
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
		if(no.IMGgetVersion(row) == V1 && IDYES == MessageBox(L"���IMG��V1������Ҫת��ΪV2����", L"��ʾ��", MB_YESNO)){
			KoishiExpand::IMGobjectV1 io1;
			stream s;
			no.extract(row, s);
			if(!io1.load(s)){
				MessageBox(L"ת��ʧ������", L"��ʾ��");
				switchIMGver(VUDEF);
				return;
			}
			if(!io1.make(io)){
				MessageBox(L"ת��ʧ������", L"��ʾ��");
				switchIMGver(VUDEF);
				return;
			}
			no.IMGreplace(row, io);
			GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->SetItem(row, 0, LVIF_IMAGE, NULL, getIconIMG(V2),0,0,0);
		}else{
			io.release();
			if(!no.IMGextract(row, io)) {
				MessageBox(L"���ǿ���ʶ���IMG��������");
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
	draw(TRUE);
	canvasOperatePara.oldMatrixEnable = FALSE;
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
	canvasOperatePara.oldMatrixEnable = FALSE;
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

void CExRabbitDlg::draw(BOOL isDDS){
	//����
	StartThreadFunc(Draw, isDDS);
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
	draw(TRUE);
	lazyTime = 5;
	*pResult = 0;
}

void CExRabbitDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ⲿ�ļ�����
	WCHAR szPath[MAX_PATH] = L"";
	UINT fileCount = ::DragQueryFile(hDropInfo, -1, NULL, NULL);		//��ȡ�Ͻ������ļ���
	UINT nChars = ::DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);		//��ȡ�Ͻ����ĵ�һ���ļ�
	CString fileName(szPath, nChars);									//���we����
	CString fmt = fileName.Right(4).MakeUpper();
	if(fmt == L".NPK") {
		if(fileCount > 1) {
			MessageBox(L"�������϶����NPK��������", L"��ʾ��");
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
			MessageBox(L"��ȡʧ������");
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
		MessageBox(L"�������" + NumToCStr(success) + L"��IMG��������", L"��ʾ��");
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
					MessageBox(L"δʶ���IMG�汾����");
					return;
				}
				success++;
				int itemCount = GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();
				GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->InsertItem(itemCount, L"", getIconPIC(pi));
				updatePICterm(itemCount);
			}
		}
		MessageBox(L"�������" + NumToCStr(success) + L"����ͼ����", L"��ʾ��");
		updateModified();
		if(crtPICid != -1) {
			draw();
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
/***********���水ť�����¼�*****************/
//////////////////////////////////////////////


void CExRabbitDlg::OnBnClickedButtonPalette()
{
	// TODO: �����ɫ����
	BOOL selected = FALSE;
	for(int i = 0;i<cl.size();i++){
		if(colorOperatePara.isChosen[i]){
			selected = TRUE;
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
				MessageBox(L"��ȡʧ������");
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
	// TODO: ����
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
		MessageBox(_T("NPK����ʧ������"),L"��ʾ��");
	}
}
void CExRabbitDlg::OnMain04()
{
	// TODO: ���Ϊ
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
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
	CFileDialog dlg(FALSE, defExt, GetTail(fileNPKname), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
		MessageBox(L"��������޸��������",L"��ʾ��");
		Invalidate();
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
/********IMG�޸�ȷ�ϲ˵������¼�*************/
//////////////////////////////////////////////


void CExRabbitDlg::OnModify01()
{
	// TODO: ȷ�ϵ�ǰ�޸�
	CHECK_VALID(crtIMGid>=0);
	no.IMGreplace(crtIMGid, io);
	MessageBox(L"IMG�ѱ����������",L"��ʾ����");
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
	// TODO: ȷ�ϵ�ǰ�޸Ĳ���IMG���Ϊ
	CHECK_VALID(crtIMGid>=0);
	OnModify01();
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(FALSE, defExt, Underlining(StrToCStr(no.entry[crtIMGid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
	image canvas; //����
	image content;	//����
	image tempMat;	//�м����
	color clr;
	if(io.version == V5 || io.version == V4)
		cbpro = 0;
	//����
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
	//������ɫ��

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
		//ѡ������ɫ�͵�ɫ����
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
		//��������б�
		if(texRow < 0) {
			drawing = 0;
			return;
		}
		io.TEXgetInfo(texRow, di);
		io.TEXextract(texRow, tempMat);		//��ȡ����
		tempMat.zoom(drawPara.zoomRate);					//���ź�ľ���
		KoishiExpand::KoishiMarkTool::ImagePSstyle(tempMat, content, clrCanvasBound, clrCanvasBack1, clrCanvasBack2);
		tempMat.destory();
		canvas.putFore(content, drawPara.mixMode, drawPara.basePoint);
	} else if(drawPara.entireTextureMode) {
		//ȫ֡��ʾ
		KoishiExpand::exhibit kex;
		kex.create(canvas.getWidth(), canvas.getHeight());
		bar.show(io.indexCount - 1 - picRow);
		for(i = picRow; i<io.indexCount; i++) {
			bar.setInfo(L"��ȡ��" + NumToCStr(i) + L"֡������", i - picRow);
			io.PICextract(i, content, cbpro);
			kex.putImage(content);
			content.destory();
		}
		bar.hide();
		canvas.putFore(kex.canvas);
		drawPara.entireTextureMode = FALSE;
	} else {
		//����ģʽ
		//����������
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
		//����IMG����
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
					//��ֹĳһ֡���쳣Ӱ������֡����ʾ
				}
			}
		}
		//IMG�Ա�ģʽ
		if(drawPara.compareMode && picRow >= 0) {
			int picRowComp = picRow;
			if(picRowComp < ioComp.indexSize) {
				//���ioTemp�д��ڴ�֡
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
				content.destory();	//���õģ�Ҫ��
			}
		}
		//����ͼ
		if(picRow >= 0) {
			io.PICgetInfo(picRow, po);
			if(po.format == LINK)
				picRow = io.linkFind(picRow);
			io.PICgetInfo(picRow, po);
			io.PICextract(picRow, tempMat, (long)cbpro);
			//��ˢԤ��
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
			//����ģʽ
			if(drawPara.indexMode && (io.version == V4 || io.version == V5 || io.version == V6)) {
				for(k = 0; k<cl.size(); k++) {
					//TODO������content���滻Ԫ�ء���ѡ�����滻Ϊ��ɫ
					int temp = 255 * k / cl.size();
					if(colorOperatePara.isChosen[k]) {
						tempMat.replace(cl[k], color(0xFF, 0, 0, 0xff));
					} else {
						tempMat.replace(cl[k], color(0xFF, temp, temp, temp));
					}
				}
			}
			//���ŵ���Ļ
			tempMat.zoom(drawPara.zoomRate);
			//�ǶԱ�ģʽ & ����ģʽ �����ƻ���
			if(drawPara.compareMode || playing == 1 || !drawPara.showCanvas) {
				content = tempMat;
			} else {
				KoishiExpand::KoishiMarkTool::ImagePSstyle(tempMat, content, clrCanvasBound, clrCanvasBack1, clrCanvasBack2);
			}
			tempMat.destory();
			//�ƶ�����
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
	//����ɫ��
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
	//����ǰ��ɫ
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
	//��ʱ�߳�
	while(m_hWnd) {
		Sleep(10);
		if(lazyTime>0)
			lazyTime--;
	}
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
	updateToolButtonStatus();
	draw();
}
void CExRabbitDlg::OnBnClickedToolButton3(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
    GetCursorPos(&myPoint); //���λ��  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}
void CExRabbitDlg::OnBnClickedToolButton5(){
	//TODO: ����
	canvasOperatePara.canvasOperation = CANVAS_SHOW;
	canvasOperatePara.oldMatrixEnable = FALSE;
	playing = !playing;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton6(){
	// TODO: �϶�
	canvasOperatePara.canvasOperation = CANVAS_DRAG;
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton7()
{	//TODO: ����
	canvasOperatePara.canvasOperation = CANVAS_ZOOM;
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
}
void CExRabbitDlg::OnBnClickedToolButton8(){
	// TODO: �ƶ�
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_MOVE;
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
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
	canvasOperatePara.oldMatrixEnable = FALSE;
	updateToolButtonStatus();
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	if(io.version == V5){
		MessageBox(L"���ܶ�V5�汾��IMG��ͼ���л���������",L"��ʾ��");
		return;
	}
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_DRAWLINE;
	updateToolButtonStatus();
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
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_DRAWRECT;
	updateToolButtonStatus();
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(playing){
		MessageBox(L"������ͣ��������", L"��ʾ��");
		return;
	}
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_PICK;
	updateToolButtonStatus();
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
	canvasOperatePara.oldMatrixEnable = FALSE;
	canvasOperatePara.canvasOperation = CANVAS_MARK;
	updateToolButtonStatus();
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
	point TRUEPt;
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
			canvasOperatePara.canvasOperating = TRUE;
			canvasOperatePara.oldBasePoint = drawPara.basePoint;	//��¼ԭ����ԭ������
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
		//�ƶ�����
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
		//ȡɫ
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
						//��������ͼδȡɫ���ֲ��䡤ʲôҲ����
					}else{
						if(colorOperatePara.v2Color.size() < 256){
							colorOperatePara.v2Color.push_back(clrMous);
							cl.push_back(clrMous);
							colorOperatePara.current = cl.size() - 1;
							colorOperatePara.isChosen[cl.size() - 1] = TRUE;
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
		//����
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
		//��ֱ��
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
		//������
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
		//���
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
		colorOperatePara.isChosen[i] = TRUE;
	}
	updateColorTable();
}


void CExRabbitDlg::OnMenuColorTableChooseNone(){
	// TODO: �ڴ���������������
	for(int i = 0;i<cl.size();i++){
		colorOperatePara.isChosen[i] = FALSE;
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
	BOOL selected = FALSE;
	for(int i = 0;i<cl.size();i++){
		if(colorOperatePara.isChosen[i]){
			selected = TRUE;
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
	// TODO: �ڴ���������������
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼɾ����ɫ����ɫ�ᵼ����ɫ���ң�ȷ������",L"��ʾ��",MB_YESNO)){
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
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act|CID��ɫ��(*.cid)|*.cid||");
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
	// TODO: �ڴ���������������
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act|CID��ɫ��(*.cid)|*.cid||");
	CFileDialog dlg(FALSE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
	updateModified();
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
	updateModified();
}


void CExRabbitDlg::OnMenuColorPaletteImport(){
	if(io.version != V6){
		MessageBox(L"ֻ��V6�汾���ܽ�����ɫ����������",L"��ʾ��");
		return;
	}
	colorList newCl;
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act|CID��ɫ��(*.cid)|*.cid||");
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
		updateModified();
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
		updateModified();
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	//ȷ������Ŀ��
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
	//�ж�����
	switch(para.type) {
	case 1:
		//ָ��֡�ж�
		pInfo.format = LINK;
		pInfo.linkTo = para.para[0];
		break;
	case 3:
		//��������
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
		//��ȡ��Դ
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
		//����ʽ
		colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
		if(!io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para.outputFormat])) {
			MessageBox(L"��Ӹ�ͼƬʱ�����˴���", L"����");
			processing = 0;
			return;
		}
		mPic.destory();
		break;
	}
	//����
	if(replacePos.size() > 0) {
		bar.show(replacePos.size() - 1);
		for(int i = 0; i<replacePos.size(); i++) {
			bar.setInfo(L"���ڲ����" + NumToCStr(i) + L"֡������", i);
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
	// TODO: �ڴ���������������
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
		//��PNG����
		bar.show(para.PNGcount - 1);
		for(int i = 0; i<para.PNGcount; i++) {
			bar.setInfo(L"�����" + NumToCStr(i) + L"֡������", i);
			CString fileName = para.filePath + NumToCStr(i) + L".PNG";
			if(i<io.indexCount) {
				//ԭ��֡����
				CHECK_VALID_CONTINUE(para.operate == 2);	//�滻֡����Ч
				CHECK_VALID_CONTINUE(KoishiImageTool::loadPNG(mPic, CStrToStr(fileName)));	//�ɹ���ȡ����Ч
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
				//׷��֡����
				if(!KoishiImageTool::loadPNG(mPic, CStrToStr(fileName))) {
					mPic.create(1, 1);
					mPic.fill(0);
				}
				colorFormat outputFormatByCtrl[5] = {COLOR_UDEF, INDEX_FMT_PALETTE, ARGB8888, ARGB4444, ARGB1555};
				if(!io.PICpreprocess(mPic, sPic, pInfo, outputFormatByCtrl[para.outputFormat])) {
					//ʧ����ʲôҲ����
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
		//��IMG����
		IMGobject targetIO;
		if(!targetIO.loadFile(CStrToStr(para.filePath))) {
			MessageBox(L"�޷�ʶ���IMG�ļ�����", L"��ʾ��");
			processing = 0;
			return;
		}
		bar.show(targetIO.indexCount - 1);
		for(int i = 0; i<targetIO.indexCount; i++) {
			bar.setInfo(L"�����" + NumToCStr(i) + L"֡������", i);
			if(i<io.indexCount) {
				//ԭ��֡����
				CHECK_VALID_CONTINUE(para.operate == 2);	//�滻֡����Ч
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
				//׷��֡����
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
	// TODO: ɾ��֡(&R)
	int i, row = crtPICid;
	io.PICremove(row);
	GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->DeleteItem(row);
	for(i=0;i<GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->GetItemCount();i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_PIC)->SetItemText(i,0,NumToCStr(i));//�������
	updateModified();
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
	updateModified();
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
		bar.setInfo(L"���ڴ����"+NumToCStr(id)+L"֡������",i);
		PICinfo pInfo;
		point newPt;
		size newSz;
		io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para.operate){
		case 1:
			//ƽ�ƻ�׼��
			newPt = pInfo.basePt + point(
				para.enable[0] ? para.para[0] : 0,
				para.enable[1] ? para.para[1] : 0);
			io.PICsetInfoPara(id, 1, &newPt);
			updatePICterm(id);
			break;
		case 2:
			//ͳһ��׼��
			newPt = point(
				para.enable[0] ? para.para[0] : pInfo.basePt.X,
				para.enable[1] ? para.para[1] : pInfo.basePt.Y);
			io.PICsetInfoPara(id, 1, &newPt);
			updatePICterm(id);
			break;
		case 3:
			//��������
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
		bar.setInfo(L"���ڴ����" + NumToCStr(id) + L"֡������", i);
		PICinfo pInfo;
		image mPic;
		stream sPic;
		io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para.operate) {
		case 1:
			//����
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
			//����
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
			//��������
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
			//����
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
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
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
		bar.setInfo(L"���ڴ����" + NumToCStr(id) + L"֡������", i);
		PICinfo pInfo;
		image mPic;
		stream sPic;
		io.PICgetInfo(id, pInfo);
		CHECK_VALID_CONTINUE(pInfo.format != LINK);
		switch(para.operate) {
		case 1:
			//��������
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
			//�������꣬������Ϊ0,0
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
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
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
			bar.setInfo(L"���ڴ����" + NumToCStr(j) + L"����ɫ������", j);
			clr = color::loseBlack(cl[j], para.gamma);
			io.CLRreplace(j, clr, GET_CTRL(CComboBox, IDC_COMBO_PRO)->GetCurSel());
			cl[j] = clr;
		}
	} else {
		bar.show(targetList.size() - 1);
		for(int i = 0; i<targetList.size(); i++) {
			int id = targetList[i];
			bar.setInfo(L"���ڴ����" + NumToCStr(id) + L"֡������", i);
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
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
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
			bar.setInfo(L"���ڴ����" + NumToCStr(id) + L"֡������", i);
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
			bar.setInfo(L"���ڴ����" + NumToCStr(i) + L"����ɫ������", i);
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
			StartThreadFunc(PictureColor, dlg.out);
		}
	}
}

DefineThreadFunc(CExRabbitDlg, PictureColor, ModalAdjustColor::OUTPUT) {
	processing = 1;
	std::vector<int> targetList;
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para.target - 1, targetList);
	//V2�����߳�
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"���ڴ����" + NumToCStr(id) + L"֡������", i);
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
	// TODO: �ڴ���������������
	if(io.version == V5){
		MessageBox(L"�˹��ܲ�������V5����",L"��ʾ��");
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
		bar.setInfo(L"���ڴ����" + NumToCStr(id) + L"֡������", i);
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
	// TODO: �ڴ���������������
	CHECK_VALID(crtPICid >= 0);
	StartThreadFunc(PictureGetPNG, SINGLE_SELECT);
}

void CExRabbitDlg::OnMenuPictureGetPngPatch(){
	// TODO: �ڴ���������������
	StartThreadFunc(PictureGetPNG, MULTI_SELECT);
}

DefineThreadFunc(CExRabbitDlg, PictureGetPNG, INT) {
	processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, para, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		bar.setInfo(L"������ȡ��" + NumToCStr(targetList[i]) + L"֡������", i);
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
	MessageBox(L"�ѱ��浽�ļ���" + profile.getOutputPath(fileNPKname, fileIMGname) + L"��������", L"��ʾ��");
	bar.hide();
}

void CExRabbitDlg::OnMenuPictureGetGIF(){
	StartThreadFunc(PictureGetGIF, nullptr);
}

DefineThreadFunc(CExRabbitDlg, PictureGetGIF, PVOID){
	processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_PIC), crtPICid, MULTI_SELECT, targetList);
	if(targetList.size() < 1){
		MessageBox(L"�빴ѡһЩ֡����",L"��ʾ��");
		processing = 0;
		return;
	}
	bar.show(targetList.size()-1);
	std::vector<image> matList;
	long imgX1, imgX2, imgY1, imgY2;
	io.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
	for(int i=0;i<targetList.size();i++){
		bar.setInfo(L"���ڴ����"+NumToCStr(targetList[i])+L"֡������",i);
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
	bar.setInfo(L"��������GIF������",targetList.size());
	KoishiImageTool::GIF::GIFobject go;
	go.input(matList, profile.miniSecPerFrame, no.entry[crtIMGid].comment, targetList);
	CString fileName = profile.getOutputPath(fileNPKname,fileIMGname)+NumToCStr(targetList[0])+L".GIF";
	go.makeFile(CStrToStr(fileName));
	processing = 0;
	MessageBox(L"�ѱ��浽�ļ���"+profile.getOutputPath(fileNPKname,fileIMGname)+L"��������",L"��ʾ��");
	bar.hide();
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
	dlg.in.firstInsert = FALSE;
	dlg.in.maxTEXcount = io.V5_TEXCount;
	io.TEXgetInfo(crtTEXid, dlg.in.ti);
	if(IDOK == dlg.DoModal()){
		StartThreadFunc(TextureInsert, dlg.out);
	}
}

void CExRabbitDlg::OnMenuTextureInsert2(){
	// TODO: �ڴ���������������
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
	//ȷ������Ŀ��
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
	//��ȡ��Դ
	if(para.inputFormat == 1 && para.outputFormat == 1) {
		//��������ļ�����Ч��DDS��ʽ������DDS��ʽ���Ҳ����κ�ת�������޸�TEXinfo
		stream sOrigin, sCompressed;
		sOrigin.loadFile(CStrToStr(para.fileName));
		sOrigin.ZLIBcompress(sCompressed);
		DDSHelper.load(sOrigin);
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
		//ת��ΪPNG�ٲ���
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
	// TODO: �ڴ���������������
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
	updateModified();
	updateInfo();
}
void CExRabbitDlg::OnMenuTextureGetPng(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtTEXid >= 0);
	StartThreadFunc(TextureGetPNG, SINGLE_SELECT);
}
void CExRabbitDlg::OnMenuTextureGetPngPatch(){
	// TODO: �ڴ���������������
	StartThreadFunc(TextureGetPNG, MULTI_SELECT);
}
void CExRabbitDlg::OnMenuTextureGetOrigin(){
	// TODO: �ڴ���������������
	CHECK_VALID(crtTEXid >= 0);
	StartThreadFunc(TextureGetOrigin, SINGLE_SELECT);
}
void CExRabbitDlg::OnMenuTextureGetOriginPatch(){
	// TODO: �ڴ���������������
	StartThreadFunc(TextureGetOrigin, MULTI_SELECT);
}
DefineThreadFunc(CExRabbitDlg, TextureGetPNG, INT) {
	processing = 1;
	std::vector<int> targetList;					//��ת��Ŀ���б�
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS), crtTEXid, para, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		bar.setInfo(L"������ȡ��" + NumToCStr(targetList[i]) + L"����������", i);
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
	std::vector<int> targetList;					//��ת��Ŀ���б�
	getSelected(GET_CTRL(CGoodListCtrl, IDC_LIST_DDS), crtTEXid, para, targetList);
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		bar.setInfo(L"������ȡ��" + NumToCStr(targetList[i]) + L"����������", i);
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
	MessageBox(L"�ѱ��浽�ļ���" + profile.getOutputPath(fileNPKname, fileIMGname) + L"���ˡ�", L"��ʾ��");
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
	MessageBox(L"���Ҽ����IMG�б��е�һ��IMG��Ȼ��ѡ������Ϊ�Ա�IMG������������������", L"��ʾ��");
}


void CExRabbitDlg::OnDrawSetCompare2(){
	// TODO: �ڴ���������������
	CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
	CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
	CFileDialog dlg(TRUE, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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
	drawPara.compareMode = TRUE;
	updateToolButtonStatus();
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
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
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
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
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
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
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
	// TODO: �ڴ���������������
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
			StartThreadFunc(PickColorFromFrame, nullptr);
		}
	}else{
		StartThreadFunc(PickColorFromFrame, nullptr);
	}
}


void CExRabbitDlg::OnMenuColorTableExtractAllFrame()
{
	// TODO: �ڴ���������������
	if(io.version == V4 || io.version == V5 || io.version == V6){
		if(IDYES == MessageBox(L"��������ͼ�޸ĵ�ɫ����ɫ�ᵼ����ɫ���ң�ȷ������", L"��ʾ��", MB_YESNO)){
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
		MessageBox(L"������ǰͼƬʧ������", L"��ʾ��");
		return;
	}
	bar.show(100);
	bar.setInfo(L"������ȡ��ɫ������", 0);
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
		bar.setInfo(L"���ڷ�����ɫ������", i);
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
	bar.setInfo(L"�������ɵ�ɫ��������", finalColorCount);
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
		bar.setInfo(L"������ȡ��"+NumToCStr(getFrame+1)+L"֡����ɫ������", getFrame);
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
		bar.setInfo(L"���ڷ�����ɫ������", i);
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
	bar.setInfo(L"�������ɵ�ɫ��������", finalColorCount);
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
	// TODO: �ڴ����ר�ô����/����û���
	
	if(pMsg->message==WM_MOUSEMOVE){
		m_ttc.RelayEvent(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CExRabbitDlg::OnClose() {
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	CFileDialog dlg(true, L"IMG�ļ�(*.IMG)|*.IMG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"IMG�ļ�(*.IMG)|*.IMG||", this);
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
		MessageBox(L"���IMG�ļ��޷�ʶ������", L"��ʾ��");
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
	int conflictMethod = 1;	// 0 �滻 1 ����(Ĭ��) 2 ���� 3 ���������
	BOOL noAlarm = FALSE;		//������ʾ
	CFileDialog dlg(true, L"NPK�ļ�(*.NPK)|*.NPK", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"NPK�ļ�(*.NPK)|*.NPK||", this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	NPKobject newNO;
	if(!newNO.loadFile(CStrToStr(fileName))) {
		MessageBox(L"���NPK�ļ��޷�ʶ������", L"��ʾ��");
		processing = 0;
		return;
	}
	bar.show(newNO.count);
	int countFail = 0;
	int countSkip = 0;
	int countReplace = 0;
	int countSuccess = 0;
	int conflict = -1;		//���ҳ�ͻ��
	for(int i = 0; i < newNO.count; i++) {
		bar.setInfo(L"��ǰ����" + GetTail(StrToCStr(newNO.entry[i].comment)) + L"������(�ɹ�" + NumToCStr(countSuccess) + L"��,����" + NumToCStr(countSkip) + L"��,�滻" + NumToCStr(countReplace) + L"��,ʧ��" + NumToCStr(countFail) + L"��)", i);
		IMGobject newIO;
		if(!newNO.IMGextract(i, newIO)) {
			countFail++;
			continue;
		}
		//����ͻ��
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
				//�滻
				no.IMGreplace(conflict, newIO);
				countReplace++;
				break;
			case 1:
				//����
				countSkip++;
				break;
			case 2:
				//����
				no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment);
				countSuccess++;
				break;
			case 3:
				//����������
				no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment + "(new)");
				countSuccess++;
				break;
			}
		}
	}
	MessageBox(L"�������������" + NumToCStr(newNO.count) + L"��,���" + NumToCStr(countSuccess) + L"��,����" + NumToCStr(countSkip) + L"��,�滻" + NumToCStr(countReplace) + L"��,ʧ��" + NumToCStr(countFail) + L"������", L"��ʾ��");
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
	CALL_FOLDER_DIALOG(folderName, L"ѡ���ļ�����", L"��ʾ��", L"��������Ч���ļ�����");
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
	int conflictMethod = 1;	// 0 �滻 1 ����(Ĭ��) 2 ���� 3 ���������
	BOOL noAlarm = FALSE;		//������ʾ
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
				bar.setInfo(L"��ǰ����" + fileList[fileID] +
							L"�е�" + GetTail(StrToCStr(newNO.entry[i].comment)) +
							L"������(�ɹ�" + NumToCStr(countSuccess) +
							L"��,����" + NumToCStr(countSkip) +
							L"��,�滻" + NumToCStr(countReplace) +
							L"��,ʧ��" + NumToCStr(countFail) +
							L"��)", i);
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
						//�滻
						no.IMGreplace(conflict, newIO);
						countReplace++;
						break;
					case 1:
						//����
						countSkip++;
						break;
					case 2:
						//����
						no.IMGinsert(insertPos + countSuccess, newIO, newNO.entry[i].comment);
						countSuccess++;
						totalSuccess++;
						break;
					case 3:
						//����������
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
			bar.setInfo(L"��ǰ����" + fileList[fileID] + L"������", 0);
			CString newPathName = Slashing(fileList[fileID]);
			no.IMGinsert(insertPos + totalSuccess, newIO, CStrToStr(newPathName));
			totalSuccess++;
			newIO.release();
			countIMG++;
		}
	}
	MessageBox(L"������������ɹ�������" + NumToCStr(countIMG) + L"���ⲿIMG������������" + NumToCStr(countNPK) + L"��NPK�ļ��е�����" + NumToCStr(countNPKIMG) + L"��IMG��������", L"��ʾ��");
	bar.hide();
	updateIMGlist();
	NPKsaveAlert = true;
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageInsertOther, DWORD) {
	processing = 1;
	int insertPos = (para) ? no.count : crtIMGid;
	CFileDialog dlg(true, L"�����ļ�(*.*)|*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"�����ļ��ļ�(*.*)|*.*||", this);
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
	CFileDialog dlg(TRUE, L"IMG�ļ�(*.IMG) | *.IMG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"IMG�ļ�(*.IMG)|*.IMG||", this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	stream s;
	if(!s.loadFile(CStrToStr(dlg.GetPathName()))) {
		MessageBox(L"�޷���ȡ���ļ�����", L"��ʾ��");
		processing = 0;
		return;
	}
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
		int id = targetList[i];
		bar.setInfo(L"�����滻" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
		no.replace(id, s);
		updateIMGterm(id);
	}
	MessageBox(L"�滻�������");
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
		MessageBox(L"�޷���ȡ�Ķ�������", L"��ʾ��");
		processing = 0;
		return;
	}
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
		int id = targetList[i];
		bar.setInfo(L"�����滻" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
		no.replace2(id, s);
		updateIMGterm(id);
	}
	MessageBox(L"�滻�������");
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
		MessageBox(L"�޷���ȡ�Ķ�������", L"��ʾ��");
		processing = 0;
		return;
	}
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i=0;i<targetList.size();i++) {
		int id = targetList[i];
		bar.setInfo(L"�����滻" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
		no.modifyLink(id, dlg.selected);
		updateIMGterm(id);
	}
	MessageBox(L"�滻�������");
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
		bar.setInfo(L"����ɾ��" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
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
		bar.setInfo(L"������ȡ" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
		fileName = filePath + Underlining(StrToCStr(no.entry[id].comment));
		no.extract(id, CStrToStr(fileName));
	}
	MessageBox(L"ȫ����ȡ��������ѱ��浽" + profile.getOutputPath(fileNPKname) + L"������", L"��ʾ��");
	bar.hide();
	updateInfo();
	processing = 0;
}


DefineThreadFunc(CExRabbitDlg, ImageMakeNPKandSavePatch, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	CFileDialog dlg(FALSE, L"NPK�ļ�(*.NPK)|*.NPK", L"newNPK.NPK", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"NPK�ļ�(*.NPK)|*.NPK||", this);
	if(IDOK == dlg.DoModal()) {
		NPKobject newNo;
		newNo.create();
		bar.show(targetList.size() - 1);
		for(int i = 0; i<targetList.size(); i++) {
			int id = targetList[i];
			bar.setInfo(L"������ȡ" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
			stream tempStr;
			no.extract(id, tempStr);
			newNo.push(tempStr, no.entry[id].comment);
		}
		newNo.saveFile(CStrToStr(dlg.GetPathName()));
		bar.hide();
		MessageBox(L"�����������", L"��ʾ��");
	}
	processing = 0;
}
DefineThreadFunc(CExRabbitDlg, ImageDequote, DWORD) {
	processing = 1;
	std::vector<int> targetList = getSelected(IDC_LIST_IMG, para);
	bar.show(targetList.size() - 1);
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"��������Ϊ" + GetTail(StrToCStr(no.entry[id].comment)) + L"��������������", i);
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
		bar.setInfo(L"��������" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
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
		bar.setInfo(L"����ת��" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
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
		bar.setInfo(L"����ת��" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
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
		bar.setInfo(L"����ת��" + GetTail(StrToCStr(no.entry[id].comment)) + L"������", i);
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
	//����ÿ��������Ȩ��
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
		//���ƽ���
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
		//�������
		if(IDstr.size() < 4) {
			wList1.push_back(1000);
			continue;
		}
		//ͼ����Ϣ������ʹ�ó���4���ַ���ʾ��mask����
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
	//��������
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
	std::vector<int> mixLayer = getSelected(IDC_LIST_IMG, MULTI_SELECT);						//��ѡͼ��
	imgCount = mixLayer.size();
	if(imgCount == 0) {
		MessageBox(L"û�й�ѡ�κ�ͼ����", L"��ʾ��");
		return;
	}
	bar.show(100);
	bar.setInfo(L"׼��ƴ��������", 0);
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
	point ptLT, ptRB, ptLTtemp, ptRBtemp;//���Ͻ����½ǵĵ㣬���½ǵĵ������ͼƬ��
	std::vector<int> mLeft, mTop, mRight, mBottom;
	bar.setMax(maxFrameCount);
	for(k = 0; k<maxFrameCount; k++) {
		bar.setInfo(L"����ƴ�ϵ�" + NumToCStr(k + 1) + L"֡��(��" + NumToCStr(maxFrameCount) + L"֡)����", k);
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
		//2.5��������������IMG��֡ȫ�յ�����
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
		//��ʼƴ�ϣ�����ӵײ㿪ʼƴ��
		for(i = imgCount - 1; i>=0; i--) {
			if(ioList[i].PICgetInfo(k, pi)) {
				int k1 = k;
				if(pi.format == LINK) {
					k1 = ioList[i].linkFind(k);
				}
				ioList[i].PICgetInfo(k1, pi);
				CHECK_VALID_CONTINUE(pi.picSize.area() > 1);
				ioList[i].PICextract(k1, mat);
				//Ԥ������
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
		MessageBox(L"û�й�ѡ��IMG��������");
		return;
	}
	StartThreadFunc(ImageReplaceExtern, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageReplaceCopyPatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ��IMG��������");
		return;
	}
	StartThreadFunc(ImageReplaceLocal, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageReplaceQuotePatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ��IMG��������");
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
		MessageBox(L"û�й�ѡ��IMG��������");
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
		MessageBox(L"û�й�ѡ��IMG��������");
		return;
	}
	StartThreadFunc(ImageExtract, MULTI_SELECT);
}

void CExRabbitDlg::OnMenuImageSave() {
	// TODO: �ڴ���������������
	CHECK_VALID(crtIMGid >= 0);
	CString defExt = _T("�����ļ�(*.*)|*.*");
	CString extFilter = _T("�����ļ�(*.*)|*.*||");
	CFileDialog dlg(FALSE, defExt, Underlining(StrToCStr(no.entry[crtIMGid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		no.extract(crtIMGid, CStrToStr(dlg.GetPathName()));
		MessageBox(_T("�����������"));
	}
}

void CExRabbitDlg::OnMenuImageSaveNPK() {
	// TODO:  �ڴ���������������
	CHECK_VALID(crtIMGid >= 0);
	StartThreadFunc(ImageMakeNPKandSavePatch, SINGLE_SELECT);
}


void CExRabbitDlg::OnMenuImageSaveNPKPatch() {
	// TODO:  �ڴ���������������
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ��IMG��������");
		return;
	}
	StartThreadFunc(ImageMakeNPKandSavePatch, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageCopyResource() {
	// TODO:  �ڴ���������������
	CHECK_VALID(crtIMGid >= 0);
	stream sTemp;
	no.extract(crtIMGid, sTemp);
	no.insert(crtIMGid + 1, sTemp, no.entry[crtIMGid].comment + "(new)");
	GET_CTRL(CGoodListCtrl, IDC_LIST_IMG)->InsertItem(crtIMGid + 1, L"", getIconIMG(V2));
	updateIMGterm(crtIMGid + 1);
	NPKsaveAlert = true;
}


void CExRabbitDlg::OnMenuImageCopyQuote() {
	// TODO:  �ڴ���������������
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
		MessageBox(L"û�й�ѡ��IMG��������");
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
		MessageBox(L"û�й�ѡ��IMG��������");
		return;
	}
	StartThreadFunc(ImageTransToV2, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageTransformTo4Patch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ��IMG��������");
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
		MessageBox(L"û�й�ѡ��IMG��������");
		return;
	}
	StartThreadFunc(ImageHide, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageHideContentPatch() {
	if(!getSelected(IDC_LIST_IMG, MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ��IMG��������");
		return;
	}
	StartThreadFunc(ImageHide, MULTI_SELECT);
}


void CExRabbitDlg::OnMenuImageClipboardCopy() {
	CHECK_VALID(crtIMGid >= 0);
	stream sTemp;
	if(no.extract(crtIMGid, sTemp)){
		noClip.push(sTemp, no.entry[crtIMGid].comment);
		MessageBox(L"�ѽ���IMG���뵽������������",L"��ʾ��");
	}else{
		MessageBox(L"�޷����������������",L"��ʾ��");
	}
}


void CExRabbitDlg::OnMenuImageClipboardInsert() {
	CHECK_VALID(crtIMGid >= 0);
	if(noClip.count == 0){
		MessageBox(L"�������ﻹû��IMG����",L"��ʾ��");
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
		MessageBox(L"�������ﻹû��IMG����",L"��ʾ��");
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
	MessageBox(L"���趨�Ա�IMG��",L"��ʾ��");
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
	// TODO:  �ڴ���������������
	if(getSelected(IDC_LIST_IMG, MULTI_SELECT).size() == 0) {
		MessageBox(L"û�й�ѡ�κ�ͼ����", L"��ʾ��");
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
	// TODO:  �ڴ���������������
	if(getSelected(IDC_LIST_IMG, MULTI_SELECT).size() == 0) {
		MessageBox(L"û�й�ѡ�κ�ͼ����", L"��ʾ��");
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
	// TODO:  �ڴ���������������
	StartThreadFunc(ImageAutoSort, nullptr);
}


void CExRabbitDlg::OnToolsStat() {
	// TODO:  �ڴ���������������
	ToolStat dlg;
	dlg.DoModal();
}
