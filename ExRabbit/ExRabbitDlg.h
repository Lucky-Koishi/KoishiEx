
// ExRabbitDlg.h : 头文件
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiNeoplePack.h"

#include "DialogNew.h"
#include "DialogAbout.h"
#include "TinyBar.h"
#include "ToolAvatar.h"
#include "ToolForceEx.h"
#include "AdjustColorDlg.h"

#include "ModalInsertPicture.h"
#include "ModalInsertPicturePatch.h"
#include "ModalAdjustCanvas.h"
#include "ModalPictureStretch.h"
#include "ModalPictureParameter.h"
#include "ModalClearPicture.h"
#include "ModalLoseBlackPicture.h"
#include "ModalAdjustColor.h"
#include "ModalAddMark.h"
#include "ModalGradient.h"
#include "ModalInsertTexture.h"
#include "ModalTransform.h"
#include "ModalRename.h"
#include "ModalPreference.h"
#include "ModalAdvancedMix.h"
#include "ToolPatch.h"
#include "ToolNPKsource.h"

#pragma once

#define VERSION_STR "恋恋のEx黑猫版.5.2"

// CExRabbitDlg 对话框
using namespace Koishi;
using namespace KoishiNeoplePack;
using KoishiImageTool::DDS::DDSobject;
class CExRabbitDlg : public CDialogEx
{
// 构造
public:
	CExRabbitDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXRABBIT_DIALOG };

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	ProfileBlack profile;
public:
	//基础变量
	IMGobject io;			//主编辑IMG
	NPKobject no;			//主编辑NPK
	colorList cl;			//颜色表
	NPKobject noClip;		//剪贴板NPK
	IMGobject ioComp;		//对比用IMG
	CString fileNPKname;	//NPK名字（全称）
	CString fileIMGname;	//IMG名字（全称）
	//信号量
	volatile int drawing;		//绘制中
	volatile int drawingColor;	//绘制中
	volatile int processing;	//提取·转换·扩充·修正
	volatile int playing;		//播放中
	volatile int lazyTime;		//响应延时避免崩溃
	volatile int sizing;		//正在调整大小
	//布局量
	int width;			//宽度
	int height;			//高度
	int barWidth;		//状态栏总宽
	int barHeight;		//状态栏高度(30)
	int barPart1;		//状态栏部分1宽度
	int barPart2;		//状态栏部分2宽度
	//其他量
	BOOL NPKsaveAlert;			//保存了NPK
	BOOL IMGsaveAlert;			//保存了IMG
	int crtIMGid;				//IMG列表当前高亮
	int fndIMGid;				//IMG列表当前寻找位置
	int crtPICid;				//帧列表当前高亮
	int crtTEXid;				//纹理集列表当前高亮
	//绘制参数
	struct structDrawPara {
		BOOL texture;			//点击纹理集列表浏览纹理集贴图时为true
		point basePoint;		//真实坐标显示时的0,0点的显示位置
		int zoom;				//缩放比例 (0-原尺寸，正数为n+1倍，负数为n+1分之一，-8到+8)
		double zoomRate;		//缩放比例
		double oldZoomRate;		//旧缩放比例
		BOOL showPalette;		//是否显示色表
		BOOL showAxis;			//是否显示零点坐标
		BOOL showCanvas;		//是否显示画布范围
		BOOL showBound;			//是否显示IMG画布总范围
		BOOL indexMode;			//索引模式
		BOOL entireTextureMode;	//纹理集引用模式
		BOOL compareMode;		//IMG比较模式
		colorMethod mixMode;	//混合显示模式
	}drawPara;
	enum enumCanvasOperation{
		CANVAS_SHOW,		//单纯显示
		CANVAS_DRAG,		//拖动
		CANVAS_ZOOM,		//缩放
		CANVAS_MOVE,		//移动坐标
		CANVAS_CUT,			//扩充裁切
		CANVAS_BRUSH,		//画刷
		CANVAS_DRAWLINE,	//画直线
		CANVAS_DRAWRECT,	//画矩形
		CANVAS_ERASE,		//擦除
		CANVAS_PICK,		//取色
		CANVAS_MARK			//打上标志
	};
	enum enumCanvasPara{
		CANVAS_DEFAULT,
		CANVAS_RIGHT,
		CANVAS_BOTTOM,
		CANVAS_LEFT,
		CANVAS_TOP,
		CANVAS_TOPRIGHT,
		CANVAS_BOTTOMRIGHT,
		CANVAS_BOTTOMLEFT,
		CANVAS_TOPLEFT
	};
	enum enumCanvasMouseOperation{
		CANVAS_MOUSE_MOVE,
		CANVAS_MOUSE_LEFT_PRESS,
		CANVAS_MOUSE_LEFT_DRAG,
		CANVAS_MOUSE_LEFT_RELEASE,
		CANVAS_MOUSE_LEFT_DOUBLE,
		CANVAS_MOUSE_RIGHT_PRESS,
		CANVAS_MOUSE_RIGHT_RELEASE
	};
	struct structCanvasOperatePara{
		int currentCursor;						//当前光标
		BOOL canvasOperating;					//画布进行时
		enumCanvasOperation canvasOperation;    //画布操作
		enumCanvasPara canvasPara;				//画布参数
		int brushShape;							//画刷形状
		int brushSize;							//画刷大小
		point oldBasePoint;						//拖动时记录旧基准点坐标
		point startPoint;						//记录鼠标按住时的坐标（不一定是鼠标坐标）
		point movePoint;						//记录鼠标移动时的坐标
		point endPoint;							//记录鼠标移动后的坐标
		std::vector<point> drawnPoint;			//记录画刷/画擦按住经过的轨迹
		image oldMatrix;						//应用画刷时产生一个旧的矩阵用以撤销
		BOOL oldMatrixEnable;					//点击画刷左键的时候变为true，切换工具/帧的时候变为false
	}canvasOperatePara;
	struct structColorOperatePara{
		int current;							//当前颜色ID
		BOOL isChosen[256];						//当前批量选色标记
		int tolerance;							//批量选色容差
		int layout;								//颜色表布局
		//布局：0 - 当颜色数<48时，每个标记25像素，分成4行，每行12项
		//布局：1 - 当颜色数<75时，每个标记20像素，分成5行，每行15项
		//布局：2 - 当颜色数<120时，每个标记15像素，分成6行，每行20项
		//布局：3 - 当颜色数<200时，每个标记12像素，分成8行，每行25项
		//布局：4 - 当颜色数>=200时，每个标记10像素，分成10行（实际只用了9行），每行30项
		colorList v2Color;						//V2时用的调色板
	}colorOperatePara;
	void OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt);
	void OnMouseEventColor(enumCanvasMouseOperation mouseOperation, int selectColorID);
	void setDefaultColor();						//设置默认颜色表
	void updateColorTable();					//更新颜色表
	BOOL getIDofCurrentPos(int &cid);			//鼠标点击颜色表时，获取当前的颜色ID
public:
	//更新控件
	void adjustWindow(int w, int h);
	void switchIMGver(IMGversion ver);
public:
	//IMG列表方法
	void IMGloadList();				//读取IMG列表
	void IMGupdateList();			//更新所有IMG项
	void IMGupdateTerm(int pos);	//更新某一个IMG项
	void IMGaddTerm(int pos, IMGversion iv, CString comment);
	void IMGdeleteTerm(int pos);
	void IMGmodifyTerm(int pos, IMGversion iv, CString comment);
	void IMGmodifyIcon(int pos, IMGversion iv);
	void IMGsetHighLine(int pos);	//强制更改高亮行（以及当前选择标志）
	queue IMGgetChecked(enumSelectType selectType);
	UINT IMGiconID(IMGversion iv);
	//帧列表方法
	void PICloadList();				//读取帧列表
	void PICupdateList();			//更新所有的帧信息
	void PICupdateTerm(int pos);	//更新某一个帧信息
	void PICrenumber();				//重新为帧编号
	void PICaddTerm(int pos, PICinfo pi);
	void PICdeleteTerm(int pos);
	void PICmodifyTerm(int pos, PICinfo pi);
	void PICmodifyBasePoint(int pos);//更新某一帧的基准坐标信息
	void PICsetHighLine(int pos);
	queue PICgetChecked(enumSelectType selectType);
	UINT PICiconID(IMGversion iv, PICinfo pi);

	//void updateTEXlist();
	void TEXloadList();
	void TEXaddTerm(int pos, TEXinfo ti);
	void TEXmodifyTerm(int pos, TEXinfo ti);
	void TEXsetHighLine(int pos);
	queue TEXgetChecked(enumSelectType selectType);
	UINT TEXiconID(TEXinfo pi);
	//其他方法
	void updateInfo();
	void updateCursorInfo();
	void updateModified();
	BOOL getMouseTrueAxis(point &pt);		//获得鼠标在画布内基于真实的坐标
	BOOL getMouseAxis(point &pt);			//获得鼠标基于画布的坐标
	CPoint getWinMouseAxis();				//获得鼠标的窗口内坐标
public:
	//绘制线程函数
	DeclareThreadFunc(CExRabbitDlg, Draw, BOOL);				//画布线程
	DeclareThreadFunc(CExRabbitDlg, DrawColor, PVOID);		//画颜色表的线程
	DeclareThreadFunc(CExRabbitDlg, Play, PVOID);
	DeclareThreadFunc(CExRabbitDlg, Lazy, PVOID);
	void draw(BOOL isTex = false);
public:
	//需要的控件、对话框等
	CDialogNew dNewFile;
	TinyBar bar;
	CBitmap m_logoPic;
	CBitmap m_buttonPic[25];
	CBitmap m_buttonPicX[25];
	CImageList i_lIMG,i_lPIC,i_lTEX;
	CToolTipCtrl m_ttc;
public:
	ToolAvatar toolAvatar;
	CToolForceEx toolForceEx;
public:
	//按钮事件
	virtual void OnOK();
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnBnClickedButtonPalette();
	afx_msg void OnBnClickedButtonImgsearch();
	afx_msg void OnStnClickedLogo();
	afx_msg void OnClose();
	//列表右键菜单
	afx_msg void OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboPro();
	//列表键盘事件
	afx_msg void OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListTex(NMHDR *pNMHDR, LRESULT *pResult);
	//拖动文件事件
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//移动窗口事件
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//绘制、点击图像、颜色表区域
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//主菜单项
	afx_msg void OnMain01();
	afx_msg void OnMain02();
	afx_msg void OnMain03();
	afx_msg void OnMain04();
	afx_msg void OnMain05();
	afx_msg void OnMain06();
	afx_msg void OnMain07();
	afx_msg void OnMain08();
	afx_msg void OnModify01();
	afx_msg void OnModify02();
	//工具栏按钮
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void updateToolButtonStatus();
	afx_msg void OnBnClickedToolButton1();
	afx_msg void OnBnClickedToolButton2();
	afx_msg void OnBnClickedToolButton3();
	afx_msg void OnBnClickedToolButton4();
	afx_msg void OnBnClickedToolButton5();
	afx_msg void OnBnClickedToolButton6();
	afx_msg void OnBnClickedToolButton7();
	afx_msg void OnBnClickedToolButton8();
	afx_msg void OnBnClickedToolButton9();
	afx_msg void OnBnClickedToolButton10();
	afx_msg void OnBnClickedToolButton11();
	afx_msg void OnBnClickedToolButton12();
	afx_msg void OnBnClickedToolButton13();
	afx_msg void OnBnClickedToolButton14();
	afx_msg void OnBnClickedToolButton15();
	//颜色表减号菜单
	DeclareThreadFunc(CExRabbitDlg, PickColorFromFrame, PVOID);
	DeclareThreadFunc(CExRabbitDlg, PickColorFromImage, PVOID);
	afx_msg void OnMenuColorTableChooseAll();
	afx_msg void OnMenuColorTableChooseNone();
	afx_msg void OnMenuColorTableInverseChoose();
	afx_msg void OnMenuColorTableChooseFamiliar();
	afx_msg void OnMenuColorTableDeleteOne();
	afx_msg void OnMenuColorTableDeleteAll();
	afx_msg void OnMenuColorTableImport();
	afx_msg void OnMenuColorTableExport();
	afx_msg void OnMenuColorPaletteNew();
	afx_msg void OnMenuColorPaletteCopy();
	afx_msg void OnMenuColorPaletteImport();
	afx_msg void OnMenuColorPaletteDelete();
	afx_msg void OnMenuColorTableClassical();
	afx_msg void OnMenuColorTable16();
	afx_msg void OnMenuColorTable256();
	afx_msg void OnMenuColorTableExtractCurrent();
	afx_msg void OnMenuColorTableExtractAllFrame();
	//帧列表右键菜单
	DeclareThreadFunc(CExRabbitDlg, PictureInsert, ModalInsertPicture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureInsertPatch, ModalInsertPicturePatch::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureAxisModify, ModalPictureParameter::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureCanvas, ModalAdjustCanvas::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureStretch, ModalPictureStretch::__output);
	DeclareThreadFunc(CExRabbitDlg, PictureClear, ModalClearPicture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureLoseBlack, ModalLoseBlackPicture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureGradient, ModalGradient::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureColor, ModalAdjustColor::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureMark, ModalAddMark::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureGetPNG, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, PictureGetGIF, PVOID);
	afx_msg void OnMenuPictureChooseAll();
	afx_msg void OnMenuPictureChooseInverse();
	afx_msg void OnMenuPictureChooseHighline();
	afx_msg void OnMenuPictureInsert();
	afx_msg void OnMenuPictureInsert2();
	afx_msg void OnMenuPictureInsertPatch();
	afx_msg void OnMenuPictureInsertPatch2();
	afx_msg void OnMenuPictureDelete();
	afx_msg void OnMenuPictureDeletePatch();
	afx_msg void OnMenuPictureAxisModify();
	afx_msg void OnMenuPictureCanvas();
	afx_msg void OnMenuPictureStretch();
	afx_msg void OnMenuPictureClear();
	afx_msg void OnMenuPictureLoseblack();
	afx_msg void OnMenuPictureGradient();
	afx_msg void OnMenuPictureColor();
	afx_msg void OnMenuPictureMark();
	afx_msg void OnMenuPictureGetPng();
	afx_msg void OnMenuPictureGetPngPatch();
	afx_msg void OnMenuPictureGetGIF();
	//纹理集列表右键菜单
	DeclareThreadFunc(CExRabbitDlg, TextureInsert, ModalInsertTexture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, TextureGetPNG, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, TextureGetOrigin, enumSelectType);
	afx_msg void OnMenuTextureChooseAll();
	afx_msg void OnMenuTextureChooseInverse();
	afx_msg void OnMenuTextureChooseHighline();
	afx_msg void OnMenuTextureInsert();
	afx_msg void OnMenuTextureDelete();
	afx_msg void OnMenuTextureDeletePatch();
	afx_msg void OnMenuTextureGetPng();
	afx_msg void OnMenuTextureGetPngPatch();
	afx_msg void OnMenuTextureGetOrigin();
	afx_msg void OnMenuTextureGetOriginPatch();
	afx_msg void OnMenuTextureInsert2();
	//特殊工具菜单
	afx_msg void OnToolAvatar();
	afx_msg void OnToolNpkDict();
	afx_msg void OnToolDownload();
	afx_msg void OnToolForceExtract();
	afx_msg void OnToolOpenOutputFolder();
	afx_msg void OnToolsNpkLock();
	afx_msg void OnToolsPatchOperate();
	afx_msg void OnToolsAvatarMark();
	//工具栏右键菜单
	afx_msg void OnDrawColorTable();
	afx_msg void OnDrawCanvas();
	afx_msg void OnDrawAxis();
	afx_msg void OnDrawBound();
	afx_msg void OnDrawSetCompare1();
	afx_msg void OnDrawSetCompare2();
	afx_msg void OnDrawCompareEnabled();
	afx_msg void OnDrawCompareDisabled();
	//IMG列表右键菜单
	DeclareThreadFunc(CExRabbitDlg, ImageInsertEmpty, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertIMG, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertNPK, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertFolder, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertOther, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageReplaceExtern, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageReplaceLocal, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageReplaceQuote, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageRemove, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageExtract, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageMakeNPKandSavePatch, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageDequote, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageHide, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageTransToV2, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageV6TransToV4, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageTransform, ModalTransform::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, ImageAutoSort, PVOID);
	DeclareThreadFunc(CExRabbitDlg, ImageMix, ModalAdvancedMix::OUTPUT);
	afx_msg void OnMenuImageInertEmpty();
	afx_msg void OnMenuImageInertIMG();
	afx_msg void OnMenuImageInertNPK();
	afx_msg void OnMenuImageInertFolder();
	afx_msg void OnMenuImageInertOther();
	afx_msg void OnMenuImageReplaceIMG();
	afx_msg void OnMenuImageReplaceCopy();
	afx_msg void OnMenuImageReplaceQuote();
	afx_msg void OnMenuImageReplaceImgPatch();
	afx_msg void OnMenuImageReplaceCopyPatch();
	afx_msg void OnMenuImageReplaceQuotePatch();
	afx_msg void OnMenuImageRemove();
	afx_msg void OnMenuImageRemovePatch();
	afx_msg void OnMenuImageExtract();
	afx_msg void OnMenuImageExtractPatch();
	afx_msg void OnMenuImageSave();
	afx_msg void OnMenuImageSaveNPK();
	afx_msg void OnMenuImageSaveNPKPatch();
	afx_msg void OnMenuImageCopyResource();
	afx_msg void OnMenuImageCopyQuote();
	afx_msg void OnMenuImageRename();
	afx_msg void OnMenuImageDequote();
	afx_msg void OnMenuImageDequotePatch();
	afx_msg void OnMenuImageTransformTo2();
	afx_msg void OnMenuImageTransformTo4();
	afx_msg void OnMenuImageTransformTo2Patch();
	afx_msg void OnMenuImageTransformTo4Patch();
	afx_msg void OnMenuImageTransformAdvanced();
	afx_msg void OnMenuImageHide();
	afx_msg void OnMenuImageHideContent();
	afx_msg void OnMenuImageHidePatch();
	afx_msg void OnMenuImageHideContentPatch();
	afx_msg void OnMenuImageClipboardCopy();
	afx_msg void OnMenuImageClipboardInsert();
	afx_msg void OnMenuImageClipboardReplace();
	afx_msg void OnMenuImageSetCompare();
	afx_msg void OnMenuImageSelectAll();
	afx_msg void OnMenuImageSelectReverse();
	afx_msg void OnMenuImageSelectHighline();
	afx_msg void OnMenuImageMoveUp();
	afx_msg void OnMenuImageMoveDown();
	afx_msg void OnMenuImageMix();
	afx_msg void OnMenuImageMixAdvanced();
	afx_msg void OnMenuImageAutoSort();
	afx_msg void OnMenuImageInertEmptyBlank();
	afx_msg void OnMenuImageInertIMGBlank();
	afx_msg void OnMenuImageInertNPKBlank();
	afx_msg void OnMenuImageInertFolderBlank();
	afx_msg void OnMenuImageInertOtherBlank();
	afx_msg void OnToolsStat();
	afx_msg void OnToolsTeenSwitch();
};
