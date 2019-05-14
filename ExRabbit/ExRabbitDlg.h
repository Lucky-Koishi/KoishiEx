
// ExRabbitDlg.h : 头文件
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "GoodListCtrl.h"
#include "DialogNew.h"
#include "DialogAbout.h"
#include "DlgBar.h"
#include "TinyBar.h"
#include "ToolIMGSearch.h"
#include "ToolAvatar.h"
#include "ToolDict.h"
#include "ToolSPK.h"
#include "ToolForceEx.h"
#include "AdjustColorDlg.h"

#include "ModalInsertPicture.h"
#include "ModalInsertPicturePatch.h"
#include "ModalAdjustCanvas.h"
#include "ModalPictureParameter.h"
#include "ModalClearPicture.h"
#include "ModalLoseBlackPicture.h"
#include "ModalAdjustColor.h"
#include "ModalAddMark.h"
#include "ModalGradient.h"
#include "ModalInsertTexture.h"
#include "ModalImageHide.h"
#include "ModalTransform.h"
#include "ModalRename.h"
#include "ModalInsertImage.h"
#include "Profile.h"
#include "ModalPreference.h"

#pragma once

#define DISC(x)

// CExRabbitDlg 对话框
using namespace Koishi;

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
public:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Profile profile;
public:
	//基础变量
	IMGobject io;			//主编辑IMG
	NPKobject no;			//主编辑NPK
	colorList cl;			//颜色表

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
	int width, height, barWidth;
	int barHeight, barPart1, barPart2;		//状态栏高，状态栏部分1宽度，部分2宽度
	
	//其他量
	//bool NPKsaveAlert;
	bool saveAlert;				//保存了IMG
	int crtIMGid;				//IMG列表当前高亮
	int fndIMGid;				//IMG列表当前寻找位置
	int crtPICid;				//帧列表当前高亮
	int crtTEXid;				//纹理集列表当前高亮
	//画布量
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
	void OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt);
	void OnMouseEventColor(enumCanvasMouseOperation mouseOperation, int selectColorID);
	struct structCanvasOperatePara{
		int currentCursor;						//当前光标
		bool canvasOperating;					//画布进行时
		enumCanvasOperation canvasOperation;    //画布操作
		enumCanvasPara canvasPara;				//画布参数
		int brushShape;							//画刷形状
		int brushSize;							//画刷大小
		point oldBasePoint;						//拖动时记录旧基准点坐标
		point startPoint;						//记录鼠标按住时的坐标（不一定是鼠标坐标）
		point movePoint;						//记录鼠标移动时的坐标
		point endPoint;							//记录鼠标移动后的坐标
		std::vector<point> drawnPoint;			//记录画刷/画擦按住经过的轨迹
		matrix oldMatrix;						//应用画刷时产生一个旧的矩阵用以撤销
	}canvasOperatePara;
	//颜色操作
	struct structColorOperatePara{
		int current;							//当前颜色ID
		bool isChosen[256];						//当前批量选色标记
		int tolerance;							//批量选色容差
		int layout;								//颜色表布局
		//布局：0 - 当颜色数<48时，每个标记25像素，分成4行，每行12项
		//布局：1 - 当颜色数<75时，每个标记20像素，分成5行，每行15项
		//布局：2 - 当颜色数<120时，每个标记15像素，分成6行，每行20项
		//布局：3 - 当颜色数<200时，每个标记12像素，分成8行，每行25项
		//布局：4 - 当颜色数>=200时，每个标记10像素，分成10行（实际只用了9行），每行30项
		colorList v2Color;						//V2时用的调色板
	}colorOperatePara;
	void setDefaultColor();						//设置默认颜色表
	void updateColorTable();					//更新颜色表
	BOOL getIDofCurrentPos(int &cid);			//鼠标点击颜色表时，获取当前的颜色ID
	static UINT threadDrawColor(PVOID para);	//画颜色表的线程
public:
	//辅助函数
	int getIconIMG(IMGversion iv);
	int getIconPIC(Koishi::colorFormat cf);
	enum enum_selectType{SINGLE_SELECT, MULTI_SELECT, ALL_SELECT};
	void getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected);
	void adjustWindow(int w, int h);
	void switchIMGver(IMGversion ver);
	void updateIMGlist();
	void updatePIClist();
	void updatePICterm(int pos);
	void updateTEXlist();
	void updateInfo();
	void updateCursorInfo();
	BOOL getMouseTrueAxis(point &pt);		//获得鼠标在画布内基于真实的坐标
	BOOL getMouseAxis(point &pt);			//获得鼠标基于画布的坐标
	CPoint getWinMouseAxis();				//获得鼠标的窗口内坐标
public:
	CDialogNew dNewFile;
	TinyBar bar;

	CBitmap m_logoPic;
	CBitmap m_buttonPic[25];
	CImageList i_lIMG,i_lPIC,i_lTEX;
	void draw(bool isTex = false);
public:
	//事件
	virtual void OnOK();
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnBnClickedButtonPalette();
	afx_msg void OnBnClickedButtonImgsearch();
	afx_msg void OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboPro();
	afx_msg void OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStnClickedLogo();
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint pt);

public:
	CToolIMGSearch toolIMGSearch;
	CToolAvatar toolAvatar;
	CToolDict toolDict;
	//第四个工具
	//去掉
	//第五个工具
	CToolSPK toolSPK;
	//第六个工具
	CToolForceEx toolForceEx;

	//CButton m_btnPalette;
	//菜单
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

	static UINT threadMix(PVOID para);

	static UINT threadDraw(PVOID para);
	struct structDrawPara{
		bool texture;			//点击纹理集列表浏览纹理集贴图时为true
		point basePoint;		//真实坐标显示时的0,0点的显示位置
		int zoom;				//缩放比例 (0-原尺寸，正数为n+1倍，负数为n+1分之一，-8到+8)
		double zoomRate;		//缩放比例
		double oldZoomRate;		//旧缩放比例
		bool showPalette;		//是否显示色表
		bool showAxis;			
		bool showCanvas;
		bool showBound;
		bool indexMode;			//索引模式
		bool entireTextureMode;	//纹理集引用模式
		bool compareMode;		//IMG比较模式
		colorMethod mixMode;//混合显示模式
	}drawPara;

	static UINT playThread(PVOID para);

	static UINT lazyThread(PVOID para);

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

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedToolButton14();
	afx_msg void OnBnClickedToolButton15();
	afx_msg void OnMenuColorTableChooseAll();
	afx_msg void OnMenuColorTableChooseNone();
	afx_msg void OnMenuColorTableInverseChoose();
	afx_msg void OnMenuColorTableChooseFamiliar();
	afx_msg void OnMenuColorTableDeleteOne();
	afx_msg void OnMenuColorTableDeleteAll();
	afx_msg void OnMenuPictureChooseAll();
	afx_msg void OnMenuPictureChooseInverse();
	afx_msg void OnMenuPictureChooseHighline();

	afx_msg void OnMenuPictureInsert();
	afx_msg void OnMenuPictureInsert2();
	static UINT ThreadPictureInsert(void*context);
	ModalInsertPicture::OUTPUT ParaPictureInsert;

	afx_msg void OnMenuPictureInsertPatch();
	afx_msg void OnMenuPictureInsertPatch2();
	static UINT ThreadPictureInsertPatch(void*context);
	ModalInsertPicturePatch::OUTPUT ParaPictureInsertPatch;

	afx_msg void OnMenuPictureDelete();
	afx_msg void OnMenuPictureDeletePatch();

	afx_msg void OnMenuPictureAxisModify();
	static UINT ThreadPictureAxisModify(void*context);
	ModalPictureParameter::OUTPUT ParaPictureAxisModify;

	afx_msg void OnMenuPictureCanvas();
	static UINT ThreadPictureCanvas(void*context);
	ModalAdjustCanvas::OUTPUT ParaPictureCanvas;

	afx_msg void OnMenuPictureClear();
	static UINT ThreadPictureClear(void*context);
	ModalClearPicture::OUTPUT ParaPictureClear;

	afx_msg void OnMenuPictureLoseblack();
	static UINT ThreadPictureLoseBlack(void*context);
	ModalLoseBlackPicture::OUTPUT ParaPictureLoseBlack;

	afx_msg void OnMenuPictureGradient();
	static UINT ThreadPictureGradient(void*context);
	ModalGradient::OUTPUT ParaPictureGradient;

	afx_msg void OnMenuPictureColor();
	static UINT ThreadPictureColor(void*context);
	ModalAdjustColor::OUTPUT ParaPictureColor;

	afx_msg void OnMenuPictureMark();
	static UINT ThreadPictureMark(void*context);
	ModalAddMark::OUTPUT ParaPictureMark;

	afx_msg void OnMenuPictureGetPng();
	afx_msg void OnMenuPictureGetPngPatch();
	static UINT ThreadPictureGetPNG(void*context);
	int ParaPictureGetPNG;
	afx_msg void OnMenuTextureChooseAll();
	afx_msg void OnMenuTextureChooseInverse();
	afx_msg void OnMenuTextureChooseHighline();
	afx_msg void OnMenuTextureInsert();
	static UINT ThreadTextureInsert(void*context);
	ModalInsertTexture::OUTPUT ParaTextureInsert;

	afx_msg void OnMenuTextureDelete();
	afx_msg void OnMenuTextureDeletePatch();
	afx_msg void OnMenuTextureGetPng();
	afx_msg void OnMenuTextureGetPngPatch();
	afx_msg void OnMenuTextureGetOrigin();
	afx_msg void OnMenuTextureGetOriginPatch();
	static UINT ThreadTextureGetPNG(void*context);
	int ParaTextureGetPNG;
	static UINT ThreadTextureGetOrigin(void*context);
	int ParaTextureGetOrigin;
	afx_msg void OnMenuTextureInsert2();

	afx_msg void OnMenuImageExtract();
	afx_msg void OnMenuImageExtractPatch();
	static UINT ThreadImageExtract(void*context);
	int ParaImageExtract;
	afx_msg void OnMenuImageSave();
	afx_msg void OnMenuImageInsert();
	static UINT ThreadImageInsert(void*context);
	ModalInsertImage::OUTPUT ParaImageInsert;
	afx_msg void OnMenuImageReplace();
	afx_msg void OnMenuImageDelete();
	afx_msg void OnMenuImageDeletePatch();
	static UINT ThreadImageDelete(void*context);
	int ParaImageDelete;
	afx_msg void OnMenuImageRename();

	afx_msg void OnMenuImageHide();
	static UINT ThreadImageHide(void*context);
	ModalImageHide::OUTPUT ParaImageHide;

	afx_msg void OnMenuImageTransform();
	static UINT ThreadImageTransform(void*context);
	ModalTransform::OUTPUT ParaImageTransform;

	afx_msg void OnMenuImageChooseAll();
	afx_msg void OnMenuImageChooseHighline();
	afx_msg void OnMenuImageChooseReverse();
	afx_msg void OnMenuImageMoveUp();
	afx_msg void OnMenuImageMoveDown();
	afx_msg void OnMenuImageAutoSort();
	static UINT ThreadImageAutoSort(void*context);
	afx_msg void OnMenuImageMix();
	afx_msg void OnMenuImageSetCompare();
	afx_msg void OnMenuImageInsert2();
	afx_msg void OnMenuColorTableImport();
	afx_msg void OnMenuColorTableExport();
	afx_msg void OnMenuColorPaletteNew();
	afx_msg void OnMenuColorPaletteCopy();
	afx_msg void OnMenuColorPaletteImport();
	afx_msg void OnMenuColorPaletteDelete();
	afx_msg void OnToolAvatar();
	afx_msg void OnToolNpkDict();
	afx_msg void OnToolImgSearch();
	afx_msg void OnToolDownload();
	afx_msg void OnToolForceExtract();
	afx_msg void OnToolOpenOutputFolder();
	afx_msg void OnDrawColorTable();
	afx_msg void OnDrawCanvas();
	afx_msg void OnDrawAxis();
	afx_msg void OnDrawBound();
	afx_msg void OnDrawSetCompare1();
	afx_msg void OnDrawSetCompare2();
	afx_msg void OnDrawCompareEnabled();
	afx_msg void OnDrawCompareDisabled();
};
