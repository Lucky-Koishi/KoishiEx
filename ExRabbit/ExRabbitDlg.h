
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
	CString fileNPKname;
	CString fileIMGname;
	point basePoint;		//相对坐标
	bool useBasePt;			//使用相对坐标
	bool fileOpen;			//打开文件
	bool mixMode;			//拼合模式（否则为NPK模式）
	bool dispModeAbs;
	bool dispModeIndex;
	bool dispModeDds;
	bool dispModeShowAll;
	volatile int drawing;	//绘制中
	volatile int drawDDS;	//绘制DDS中
	volatile int extracting;	//提取中
	volatile int converting;	//转换中
	volatile int lazyTime;		//响应延时
	bool saveAlert;
	int crtIMGid;
	int crtPICid;
	int crtCLRDDSid;
	volatile IMGversion to_ver;	//转换版本用到的参数
public:
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
	CEdit m_edInfo;
	CEdit m_edNPK;
	CGoodListCtrl m_lIMG;
	CProgressCtrl m_pgInfo;
	CDlgInsert dlgInsert;
	CDlgRename dlgRename;
	CDlgTrasform dlgTrasform;
	CDialogNew dlgNew;
	CDlgInsert2 dlgInsert2;
	CDlgSetpara dlgSetpara;
	CDlgInsert3 dlgInsert3;
	CDlgInsert4 dlgInsert4;
	CDlgHSV dlgHSV;
	CStatic m_logo;
	CBitmap m_logoPic;
	CImageList m_icon;
	//CButton m_chAxis;
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
	afx_msg void OnMainmenuQuit();
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
	afx_msg void OnClrmenuRemove();
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
	afx_msg void OnClrmenuLoadpalette();
	afx_msg void OnClrmenuNewpalette();
	afx_msg void OnClrmenu2Loadpalette();
	afx_msg void OnClrmenu2Newpalette();
	afx_msg void OnMenuhsv();
	CEdit m_edInfo2;
	CEdit m_edInfo3;
	CEdit m_edInfo4;
	CEdit m_edInfo5;
	CEdit m_edInfo6;
	CEdit m_edInfo7;
	CEdit m_edInfo8;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnImgmenuSelectall();
	afx_msg void OnImgmenuSelectother();
	afx_msg void OnImgmenuRemoveallselected();
	afx_msg void OnImgmenuHideallselected();
	afx_msg void OnImgmenuExtractallselected();
	afx_msg void OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListClr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListDds(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnImgMenuAddtomixed();
	afx_msg void OnDisplaymenu2Showall();
	afx_msg void OnDisplaymenu2Autofind();
	afx_msg void OnDisplaymenu2SwitchAbs();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

UINT transformThread(PVOID para);
UINT extractThread(PVOID para);
UINT extractPIDThread(PVOID para);
UINT extractDDSThread(PVOID para);
UINT extractDDSPNGThread(PVOID para);
UINT drawThread(PVOID para);
UINT lazyThread(PVOID para);
UINT mixThread(PVOID para);