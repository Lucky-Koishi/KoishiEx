
// ExRabbitDlg.h : 头文件
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "GoodListCtrl.h"
#include "DlgInsertIMG.h"
#include "DlgRename.h"
#include "DlgTrasform.h"
#include "DialogNew.h"
#include "DialogImportFrame.h"
#include "DialogAbout.h"
#include "DlgInsertPicture.h"
#include "DlgSetpara.h"
#include "DlgInsertTexture.h"
#include "DlgInsertColor.h"
#include "DlgSetXY.h"
#include "DlgExpand.h"
#include "DlgColor.h"
#include "DlgBar.h"
#include "DlgSetting.h"
#include "DlgLoseBlack.h"
#include "ToolIMGSearch.h"
#include "ToolAvatar.h"
#include "ToolDict.h"
#include "ToolIndexing.h"
#include "ToolSPK.h"
#include "ToolForceEx.h"
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
public:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	IMGobject io;			//主编辑IMG
	NPKobject no;			//主编辑NPK
	
	IMGobject ioComp;		//对比用IMG
	CString fileNPKname;	//NPK名字（全称）
	CString fileIMGname;	//IMG名字（全称）
	

	//信号量
	volatile int drawing;		//绘制中
	volatile int extracting;	//提取中
	volatile int converting;	//转换中
	volatile int expanding;		//转换中
	volatile int playing;		//播放中
	volatile int lazyTime;		//响应延时避免崩溃
	volatile int sizing;		//正在调整大小
	//其他量
	bool useColorTable;		//使用颜色表(同时禁止使用颜色列表)
	bool saveAlert;				//保存了IMG
	int crtIMGid;				//IMG列表当前高亮
	int fndIMGid;				//IMG列表当前寻找位置
	int crtPICid;				//帧列表当前高亮
	int crtTEXid;				//纹理集列表当前高亮
	struct canvasThreadPara{
		int x1,y1,x2,y2;
	}canvasPara;
	//设置
	CString outputDir;
	CString imPack2Dir;
	CString getOutPutDir();
	CString getOutPutDir(CString npkName);
	CString getOutPutDir(CString npkName, CString imgName);
	CString getOutPutDir(CString npkName, CString imgName, int clPro);
	DWORD bgColor;
	//辅助
	int getIconIMG(IMGversion iv);
	int getIconPIC(Koishi::colorFormat cf);
	int getIconCLR(Koishi::color clr);
	void getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected);
public:
	int width,height;
	BOOL adjustWindow(int w, int h);
	BOOL switchIMGver(IMGversion ver);
	BOOL updateIMGlist();
	BOOL updatePIClist();
	BOOL updateCLRlist();
	BOOL updateTEXlist();
	BOOL updatePICInfo();
	BOOL updateNPKInfo();
	BOOL updateInfo();
	BOOL loadProfile();
	BOOL updateRandomTitle();
public:
	CButton m_btnMenu;
	CEdit m_edNPKinfo;
	CGoodListCtrl m_lIMG;
	CDlgInsertIMG dlgInsert;
	CDlgRename dlgRename;
	CDlgTrasform dlgTrasform;
	CDialogNew dlgNew;
	CDialogImportFrame dlgImportFrame;
	CDialogAbout dlgAbout;
	CDlgInsertPicture dlgInsert2;
	CDlgSetpara dlgSetpara;
	CDlgInsertTexture dlgInsert3;
	CDlgInsertColor dlgInsert4;
	CDlgSetXY dlgSetXY;
	CDlgExpand dlgExpand;
	CDlgColor dlgColor;
	CDlgBar dlgBar;
	CDlgSetting dlgSet;
	CDlgLoseBlack dlgLoseBlack;
	CStatic m_logo;
	CBitmap m_logoPic;
	CImageList m_icon;
	CComboBox m_cbPro;
	CEdit m_edX;
	CEdit m_edY;
	CEdit m_edIMGinfo;
	CGoodListCtrl m_lColor;
	CGoodListCtrl m_lPicture;
	CSpinButtonCtrl m_spX;
	CSpinButtonCtrl m_spY;
	CGoodListCtrl m_lTexture;
	CImageList i_lIMG,i_lPIC,i_lTEX,i_lCLR;
	void draw(bool isTex = false);
public:
	//事件
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnBnClickedButtonPalette();
	afx_msg void OnBnClickedButtonImgsearch();
	afx_msg void OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListClr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListClr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnCbnSelchangeComboPro();
	afx_msg void OnDeltaposSpinX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnOK();

	CEdit m_edInfo2;
	CEdit m_edInfo3;
	CEdit m_edInfo4;
	CEdit m_edInfo5;
	CEdit m_edInfo6;
	CEdit m_edInfo7;
	CEdit m_edInfo8;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListClr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStnClickedLogo();

	CToolIMGSearch toolIMGSearch;
	CToolAvatar toolAvatar;
	CToolDict toolDict;
	//第四个工具
	CToolIndexing toolIndexing;
	KoishiExpand::Indexing indexing;
	//第五个工具
	CToolSPK toolSPK;
	//第六个工具
	CToolForceEx toolForceEx;

	CEdit m_edIMGsearch;
	CButton m_btnPalette;
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
	afx_msg void OnTool01();
	afx_msg void OnTool02();
	afx_msg void OnTool03();
	afx_msg void OnTool04();
	afx_msg void OnTool05();
	afx_msg void OnIMG01();
	afx_msg void OnIMG02();
	afx_msg void OnIMG03();
	afx_msg void OnIMG04();
	afx_msg void OnIMG05();
	afx_msg void OnIMG06();
	afx_msg void OnIMG07();
	afx_msg void OnIMG08();
	afx_msg void OnIMG09();
	afx_msg void OnIMG10();
	afx_msg void OnIMG11();
	afx_msg void OnIMG12();
	afx_msg void OnIMG13();
	afx_msg void OnIMG14();
	afx_msg void OnIMG15();
	afx_msg void OnIMG16();
	afx_msg void OnIMG17();
	afx_msg void OnIMG18();
	afx_msg void OnIMG19();
	afx_msg void OnIMGR01();
	afx_msg void OnFRM01();
	afx_msg void OnFRM02();
	afx_msg void OnFRM03();
	afx_msg void OnFRM04();
	afx_msg void OnFRM05();
	afx_msg void OnFRM06();
	afx_msg void OnFRM07();
	afx_msg void OnFRM08();
	afx_msg void OnFRM09();
	afx_msg void OnFRM10();
	afx_msg void OnFRM11();
	afx_msg void OnFRM12();
	afx_msg void OnFRM13();
	afx_msg void OnFRM14();
	afx_msg void OnFRM15();
	afx_msg void OnFRM16();
	afx_msg void OnFRMR01();
	afx_msg void OnFRMR02();
	afx_msg void OnTEX01();
	afx_msg void OnTEX02();
	afx_msg void OnTEX03();
	afx_msg void OnTEX04();
	afx_msg void OnTEX05();
	afx_msg void OnTEX06();
	afx_msg void OnTEX07();
	afx_msg void OnTEX08();
	afx_msg void OnTEX09();
	afx_msg void OnTEX10();
	afx_msg void OnTEXR01();
	afx_msg void OnCLR01();
	afx_msg void OnCLR02();
	afx_msg void OnCLR03();
	afx_msg void OnCLR04();
	afx_msg void OnCLR05();
	afx_msg void OnCLR06();
	afx_msg void OnCLR07();
	afx_msg void OnCLR08();
	afx_msg void OnCLR09();
	afx_msg void OnCLR10();
	afx_msg void OnCLRR01();
	afx_msg void OnCLRR02();
	afx_msg void OnCLRR03();
	afx_msg void OnDisplay01();
	afx_msg void OnDisplay02();
	afx_msg void OnDisplay03();
	afx_msg void OnDisplay04();
	afx_msg void OnDisplay05();
	afx_msg void OnDisplay06();
	afx_msg void OnDisplay07();
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

	static UINT threadTransform(PVOID para);
	struct structTransformPara{
		int target;			//目标集合
		IMGversion verPara;	//转换版本
		colorFormat fmtPara;//转换格式
		bool bitMode;		//量化选项
		int bitPara;		//量化参数
		bool makeTexture;	//是否制作纹理集
	}transformPara;

	static UINT threadImportNPK(PVOID para);
	struct structImportNPKPara{
		str fileName;		//文件名
		int conflictPara;	//冲突检测
	}importNPKPara;

	static UINT threadImportFrame(PVOID para);
	struct structImportFramePara{
		str filePath;	//文件路径
		int maxFrame;		//最大帧号
		int oldFramePara;	//处理原有帧方式
		int scalePara;		//处理坐标和帧域方式
	}importFramePara;

	static UINT threadMix(PVOID para);
	struct structMixPara {
	}mixPara;

	static UINT threadAutoSort(PVOID para);
	struct structAutoSortPara {
	}autoSortPara;

	static UINT threadExtract(PVOID para);
	struct structExtractPara{
		int target;		//目标集合
		bool texture;	//是否取纹理集（false为取一般帧贴图）
		bool toPNG;		//是否转化为PNG（若为否，则索引转化为PID，DDS转化为DDS）
	}extractPara;

	static UINT threadDraw(PVOID para);
	struct structDrawPara{
		bool texture;			//点击纹理集列表浏览纹理集贴图时为true
		point basePoint;		//真实坐标显示时的0,0点的显示位置
		bool realAxis;			//真实坐标显示
		bool indexMode;			//索引模式
		bool entireTextureMode;	//纹理集引用模式
		bool compareMode;		//IMG比较模式
		colorMethod mixMode;//混合显示模式
	}drawPara;

	static UINT playThread(PVOID para);

	static UINT threadLoseBlack(PVOID para);
	struct structLoseBlackPara{
		double gamma;
	}loseBlackPara;

public:
	//日志
	CString logFileName;
	bool useLog;
	void writeLog(const CString str);
	void writeLog(const CString operation, const CString remark);
	void writeLog(const CString operation, const str remark);
	void writeLog(const CString operation, int num);
	afx_msg void OnTool06();
	afx_msg void OnIMG0801();
	afx_msg void OnTool07();
};

UINT lazyThread(PVOID para);
UINT canvasThread(PVOID para);
UINT uncanvasThread(PVOID para);
UINT indexingThread(PVOID para);
UINT indexingExternThread(PVOID para);
UINT indexingProcessThread(PVOID para);