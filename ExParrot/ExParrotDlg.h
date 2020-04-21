
// ExParrotDlg.h : 头文件
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx//KoishiNeoplePack.h"
#include "../KoishiEx//KoishiAudioTool.h"

#include "TinyBar.h"
#include "GoodListCtrl.h"
#include "Profile.h"
#include "ToolSPK2.h"

#include "ModalRename.h"
#include "ModalSoundHide.h"
#include "ModalSoundInsert.h"
#include "ModalPreference2.h"

#pragma once

#define VERSION_STR "恋恋のEx白猫版.1.1"

using namespace Koishi;
using namespace KoishiNeoplePack;
using namespace KoishiAudioTool;
// CExParrotDlg 对话框
class CExParrotDlg : public CDialogEx
{
// 构造
public:
	CExParrotDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXPARROT_DIALOG };

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
	Profile profile;
public:
	//基础变量
	NPKobject no;
	audio au;
	CString fileNPKname;
	CString fileSNDname;
public:
	//布局变量和函数
	int width, height, barWidth;
	int barHeight, barPart1, barPart2;	
	//其他变量和函数
	bool saveAlert;
	int crtSNDid;
	int fndSNDid;
	TinyBar bar;
	volatile int processing;
	volatile int sizing;
public:
	enum enumCanvasOperation{
		CANVAS_SELECT,		//单纯显示
		CANVAS_ZOOM,		//拖动
		CANVAS_DRAG
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
		bool canvasOperating;					//正在操作
		enumCanvasOperation canvasOperation;    //操作种类
		longex firstPos;
		longex oldDispLeftBound;
		longex oldDispRightBound;
	}canvasOperatePara;
public:
	CBitmap m_logoPic;
	CBitmap m_buttonPic[25];
	CImageList i_lSND;
	void adjustWindow(int w, int h);
	int getIconSND(dword ext);
	enum enum_selectType{SINGLE_SELECT, MULTI_SELECT, ALL_SELECT};
	void getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected);
	void updateSNDlist();
	void updateInfo();
	image MP3image;
	void updateMP3image();
public:
	//播放器
	PCMplayer player;
	PCMdevice recorder;
	bool recording;
	static UINT playThread(void *para);
	static UINT xThread(void *para);
	//音标指针
	longex leftBound, rightBound;				//选择的边界
	longex dispLeftBound, dispRightBound;		//显示的边界
	longex zoomBound1, zoomBound2;
	void draw();
	void makeGraph(image &graphMat, int w, int h);
	static UINT drawThread(void *para);
	long power[16];								//功率谱
	long cur[2];								//获得当前
	void drawPower();
public:
	//解码器
	void decode();
	static UINT decodeThread(void *para);
public:
	afx_msg void OnEnChangeEditSndsearch();
	
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnMain01();
	afx_msg void OnMain02();
	afx_msg void OnMain03();
	afx_msg void OnMain04();
	afx_msg void OnMain05();
	afx_msg void OnMain06();
	afx_msg void OnMain07();
	afx_msg void OnMain08();
	afx_msg void OnNMClickListSnd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListSnd(NMHDR *pNMHDR, LRESULT *pResult);

	//SND菜单
	afx_msg void OnMenuSoundExtract();
	afx_msg void OnMenuSoundExtractPatch();
	static UINT ThreadSoundExtract(void*context);
	int ParaSoundExtract;

	afx_msg void OnMenuSoundInsert();
	static UINT ThreadSoundInsert(void*context);
	ModalSoundInsert::OUTPUT ParaSoundInsert;

	afx_msg void OnMenuSoundReplace();
	afx_msg void OnMenuSoundDelete();
	afx_msg void OnMenuSoundDeletePatch();
	static UINT ThreadSoundDelete(void*context);
	int ParaSoundDelete;

	afx_msg void OnMenuSoundRename();
	afx_msg void OnMenuSoundInsertCopy();
	afx_msg void OnMenuSoundInsertRef();
	afx_msg void OnMenuSoundDelink();
	afx_msg void OnMenuSoundHide();
	static UINT ThreadSoundHide(void*context);
	ModalSoundHide::OUTPUT ParaSoundHide;

	afx_msg void OnMenuSoundChooseAll();
	afx_msg void OnMenuSoundChooseHighline();
	afx_msg void OnMenuSoundChooseReverse();
	afx_msg void OnMenuSoundMoveUp();
	afx_msg void OnMenuSoundMoveDown();
	afx_msg void OnMenuSoundInsertOther();
	afx_msg void OnMenuSoundSave();
	afx_msg void OnMenuSoundInsert2();
	
	afx_msg void OnBnClickedButtonControl1();
	afx_msg void OnBnClickedButtonControl2();

	static UINT ThreadControlPlay(void*context);
	afx_msg void OnBnClickedButtonControl3();
	afx_msg void OnBnClickedButtonControl4();

	static UINT ThreadControlLoad(void*context);
	static UINT ThreadControlRecord(void*context);
	CString loadPara;
	bool newRecord;				//录音时是否有音频文件
	bool loadReplace;			//当存在音频时，是替换选定部分还是替换所有部分
	afx_msg void OnBnClickedButtonControl5();

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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	

	BOOL getMouseAxis(point &pt);
	CPoint getWinMouseAxis();
	BOOL getMousePos(longex &pos);
	void OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonSNDsearch();

	CToolTipCtrl m_ttc;

	afx_msg void OnToolDownload();
	CToolSPK toolSPK;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
