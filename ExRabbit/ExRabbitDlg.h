
// ExRabbitDlg.h : 头文件
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "GoodListCtrl.h"
#include "DlgInsert.h"
#include "DlgRename.h"
#include "DlgTrasform.h"
#include "DialogNew.h"
#include "DlgInsert2.h"
#include "DlgSetpara.h"
#include "DlgInsert3.h"
#include "DlgInsert4.h"
#include "DlgHSV.h"
#include "DlgSetXY.h"
#include "DlgExpand.h"
#include "DlgColor.h"
#include "DlgBar.h"
#include "DlgCanvas.h"
#include "ToolIMGSearch.h"
#include "ToolAvatar.h"

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

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	NPKobject no;
	IMGobject io;
	IMGobject ioComp;
	CString fileNPKname;	//NPK名字（全称）
	CString fileIMGname;	//IMG名字（全称）
	point basePoint;		//相对坐标
	bool useBasePt;			//使用相对坐标
	bool fileOpen;			//打开文件
	bool mixMode;			//拼合模式（否则为NPK模式）
	bool dispModeAbs;
	bool dispModeIndex;
	bool dispModeDds;
	bool dispModeShowAll;
	bool dispModeCompare;
	bool useColorTable;
	colorMethod dispMixMode;
	volatile int drawing;	//绘制中
	volatile int drawDDS;	//绘制DDS中
	volatile int extracting;	//提取中
	volatile int converting;	//转换中
	volatile int expanding;		//转换中
	volatile int playing;		//播放中
	volatile int lazyTime;		//响应延时避免崩溃
	volatile int sizing;		//正在调整大小
	bool saveAlert;				//保存了IMG
	int crtIMGid;
	int crtPICid;
	int crtCLRDDSid;
	volatile IMGversion to_ver;	//转换版本用到的参数
	struct canvasThreadPara{
		int x1,y1,x2,y2;
	}canvasPara;
public:
	int width,height;
	BOOL adjustWindow(int w, int h);
	BOOL switchIMGver(IMGversion ver);
	BOOL updateIMGlist();
	BOOL updatePIClist();
	BOOL updateCLRlist();
	BOOL updateDDSlist();
	BOOL updatePICInfo();
	BOOL updateIMGInfo();
	BOOL updateNPKInfo();
	BOOL updateInfo();
public:
	CButton m_btnMenu;
	CEdit m_edNPK;
	CGoodListCtrl m_lIMG;
	CDlgInsert dlgInsert;
	CDlgRename dlgRename;
	CDlgTrasform dlgTrasform;
	CDialogNew dlgNew;
	CDlgInsert2 dlgInsert2;
	CDlgSetpara dlgSetpara;
	CDlgInsert3 dlgInsert3;
	CDlgInsert4 dlgInsert4;
	CDlgHSV dlgHSV;
	CDlgSetXY dlgSetXY;
	CDlgExpand dlgExpand;
	CDlgColor dlgColor;
	CDlgBar dlgBar;
	CDlgCanvas dlgCanvas;
	CStatic m_logo;
	CBitmap m_logoPic;
	CImageList m_icon;
	CComboBox m_cbPro;
	CEdit m_edX;
	CEdit m_edY;
	CEdit m_edIMGinfo;
	CEdit m_edIMGname;
	CGoodListCtrl m_lColor;
	CGoodListCtrl m_lPicture;
	CSpinButtonCtrl m_spX;
	CSpinButtonCtrl m_spY;
	CGoodListCtrl m_lDDS;
	void draw(bool isDDS = false);
	void transform(IMGversion vers);
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListClr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListClr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListDds(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListDds(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnCbnSelchangeComboPro();
	afx_msg void OnDeltaposSpinX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMainMenuNew();
	afx_msg void OnMainMenuOpen();
	afx_msg void OnMainMenuSave();
	afx_msg void OnMainMenuAbout();
	afx_msg void OnMainMenuQuit();
	afx_msg void OnImgMenuExtract();
	afx_msg void OnImgMenuInsert();
	afx_msg void OnImgMenuRemove();
	afx_msg void OnImgMenuReplace();
	afx_msg void OnImgMenuRename();
	afx_msg void OnImgMenuMoveUp();
	afx_msg void OnImgMenuMoveDown();
	afx_msg void OnImgMenuHide();
	afx_msg void OnImgMenuConvert();
	afx_msg void OnImgMenu2Insert();
	afx_msg void OnPicMenuExtractPng();
	afx_msg void OnPicMenuExtractAllPng();
	afx_msg void OnPicMenuExtractIndex();
	afx_msg void OnPicMenuExtractAllIndex();
	afx_msg void OnPicMenuInsert();
	afx_msg void OnPicMenuRemove();
	afx_msg void OnPicMenuReplace();
	afx_msg void OnPicMenuSetPara();
	afx_msg void OnPicMenuHide();
	afx_msg void OnPicMenu2Insert();
	afx_msg void OnDdsMenuExtractPng();
	afx_msg void OnDdsMenuExtractAllPng();
	afx_msg void OnDdsMenuExtractDds();
	afx_msg void OnDdsMenuExtractAllDds();
	afx_msg void OnDdsMenuInsert();
	afx_msg void OnDdsMenuRemove();
	afx_msg void OnDdsMenuReplace();
	afx_msg void OnDdsMenu2Insert();
	afx_msg void OnClrMenuInsert();
	afx_msg void OnClrMenuRemove();
	afx_msg void OnClrMenuReplace();
	afx_msg void OnClrMenuExtractPalette();
	afx_msg void OnClrMenuExtractAllPalette();
	afx_msg void OnClrMenu2Insert();
	afx_msg void OnDisplayMenuSwitchAbs();
	afx_msg void OnDisplayMenuAutoFind();
	afx_msg void OnDisplayMenuSwitchIndex();
	afx_msg void OnDisplayMenuSwitchDds();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonMenu2();
	virtual void OnOK();
	afx_msg void OnClrMenuLoadPalette();
	afx_msg void OnClrMenuNewPalette();
	afx_msg void OnClrMenu2LoadPalette();
	afx_msg void OnClrMenu2NewPalette();
	afx_msg void OnClrMenuHSV();
	CEdit m_edInfo2;
	CEdit m_edInfo3;
	CEdit m_edInfo4;
	CEdit m_edInfo5;
	CEdit m_edInfo6;
	CEdit m_edInfo7;
	CEdit m_edInfo8;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnImgMenuSelectAll();
	afx_msg void OnImgMenuSelectOther();
	afx_msg void OnImgMenuRemoveAllSelected();
	afx_msg void OnImgMenuHideAllSelected();
	afx_msg void OnImgMenuExtractAllSelected();
	afx_msg void OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListClr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListDds(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnImgMenuAddToMixed();
	afx_msg void OnDisplayMenu2ShowAll();
	afx_msg void OnDisplayMenu2AutoFind();
	afx_msg void OnDisplayMenu2SwitchAbs();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnMainMenuSaveAs();
	afx_msg void OnPicMenuSetXY();
	afx_msg void OnDisplayMenuShowCompare();
	afx_msg void OnDisplayMenuSetCompare();
	afx_msg void OnImgMenuCompareAs();
	afx_msg void OnClrMenuLoadAct();
	afx_msg void OnClrMenuExportAct();
	afx_msg void OnPicMenuExpand();
	afx_msg void OnMix0();
	afx_msg void OnMix1();
	afx_msg void OnMix2();
	afx_msg void OnMix3();
	afx_msg void OnMix4();
	afx_msg void OnMix5();
	afx_msg void OnMix6();
	afx_msg void OnMix7();
	afx_msg void OnMix8();
	afx_msg void OnMix9();
	afx_msg void OnMix10();
	afx_msg void OnMix11();
	afx_msg void OnMix12();
	afx_msg void OnMix13();
	afx_msg void OnMix14();
	afx_msg void OnMix15();
	afx_msg void OnMix16();
	afx_msg void OnDisplayMenuPlay();
	afx_msg void OnClrMenuWin();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStnClickedLogo();

	CToolIMGSearch toolIMGSearch;
	afx_msg void OnTool1();
	afx_msg void OnTool2();
	CToolAvatar toolAvatar;
};

UINT transformThread(PVOID para);
UINT extractThread(PVOID para);
UINT extractPIDThread(PVOID para);
UINT extractDDSThread(PVOID para);
UINT extractDDSPNGThread(PVOID para);
UINT drawThread(PVOID para);
UINT drawDDSThread(PVOID para);
UINT drawThread2(PVOID para);
UINT drawThread_bg(PVOID para);
UINT drawThread_fg(PVOID para);
UINT lazyThread(PVOID para);
UINT mixThread(PVOID para);
UINT canvasThread(PVOID para);
UINT uncanvasThread(PVOID para);
UINT playThread(PVOID para);