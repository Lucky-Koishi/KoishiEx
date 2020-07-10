
// ExParrotDlg.h : 头文件
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx//KoishiNeoplePack.h"
#include "../KoishiEx//KoishiAudioTool.h"

#include "TinyBar(white).h"

#include "ModalRename(white).h"
#include "ModalPreference(white).h"

#pragma once

#define VERSION_STR "恋恋のEx白猫版.2.1"

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
	//播放器
	PCMplayer player;
	PCMdevice recorder;
	//信号量
	volatile int processing;
	volatile int sizing;
	bool recording;
	//布局量
	int width, height, barWidth;
	int barHeight, barPart1, barPart2;	
	//其他量
	bool NPKsaveAlert;
	bool SNDsaveAlert;
	int crtSNDid;
	int fndSNDid;
	image MP3image;
	//音标指针
	longex leftBound;				//当前选择左边界
	longex rightBound;				//当前选择右边界
	longex dispLeftBound;			//当前显示左边界
	longex dispRightBound;			//当前显示右边界
	longex zoomBound1;				//放大时选择范围的左边界
	longex zoomBound2;				//放大时选择范围的有边界
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
	void adjustWindow(int w, int h);
	int getIconSND(dword ext);
	enum enum_selectType{
		SINGLE_SELECT, 
		MULTI_SELECT, 
		ALL_SELECT
	};
	void getSelected(CGoodListCtrl *listCtrl, int highLine, int targetPara, std::vector<int> &selected);
	std::vector<int> CExParrotDlg::getSelected(UINT listCtrlID, INT selectType);
	void updateSNDlist();
	void updateSNDterm(int pos);
	void updateInfo();
	void updateMP3image();
	void updateModified();
	BOOL getMouseAxis(point &pt);
	BOOL getMousePos(longex &pos);
	CPoint getWinMouseAxis();
	void OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt);
public:
	DeclareThreadFunc(play, BOOL);			//播放线程，BOOL=TURE -> 只播放选定段 
	DeclareThreadFunc(RecordStart,	BOOL);	//录音线程，BOOL无意义
	DeclareThreadFunc(RecordFinish, BOOL);	//录音结束处理线程，BOOL无意义
	DeclareThreadFunc(ReplaceSound,	BOOL);	//音频段替换线程，BOOL无意义
	DeclareThreadFunc(Draw, BOOL);			//绘制时域图线程，BOOL无意义
	DeclareThreadFunc(DrawPower, BOOL);		//绘制频域图线程，BOOL无意义
	DeclareThreadFunc(DecodeAndPlay, BOOL);		//解码线程
	void draw();
	void makeGraph(image &graphMat, int w, int h);
	void decodeAndPlay();
public:
	//所需控件
	TinyBar bar;
	CBitmap m_logoPic;
	CBitmap m_buttonPic[25];
	CImageList i_lSND;
	CToolTipCtrl m_ttc;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnBnClickedButtonSNDsearch();
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
	
	afx_msg void OnBnClickedButtonControl1();
	afx_msg void OnBnClickedButtonControl2();
	afx_msg void OnBnClickedButtonControl3();
	afx_msg void OnBnClickedButtonControl4();
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

	afx_msg void OnToolDownload();
	//SND右键菜单
	DeclareThreadFunc(SoundInsertEmpty, DWORD);
	DeclareThreadFunc(SoundInsertSND, DWORD);
	DeclareThreadFunc(SoundInsertNPK, DWORD);
	DeclareThreadFunc(SoundInsertFolder, DWORD);
	DeclareThreadFunc(SoundInsertOther, DWORD);
	DeclareThreadFunc(SoundReplaceExtern, DWORD);
	DeclareThreadFunc(SoundReplaceLocal, DWORD);
	DeclareThreadFunc(SoundReplaceQuote, DWORD);
	DeclareThreadFunc(SoundRemove, DWORD);
	DeclareThreadFunc(SoundExtract, DWORD);
	DeclareThreadFunc(SoundSaveAsNPK, DWORD);
	DeclareThreadFunc(SoundDequote, DWORD);
	DeclareThreadFunc(SoundHide, DWORD);
	afx_msg void OnMenuSoundInertEmpty();
	afx_msg void OnMenuSoundInertSnd();
	afx_msg void OnMenuSoundInertNPK();
	afx_msg void OnMenuSoundInertFolder();
	afx_msg void OnMenuSoundInertOther();
	afx_msg void OnMenuSoundInertEmptyBlank();
	afx_msg void OnMenuSoundInertSNDBlank();
	afx_msg void OnMenuSoundInertNPKBlank();
	afx_msg void OnMenuSoundInertFolderBlank();
	afx_msg void OnMenuSoundInertOtherBlank();
	afx_msg void OnMenuSoundReplaceSND();
	afx_msg void OnMenuSoundReplaceCopy();
	afx_msg void OnMenuSoundReplaceQuote();
	afx_msg void OnMenuSoundInsertSndPatch();
	afx_msg void OnMenuSoundReplaceCopyPatch();
	afx_msg void OnMenuSoundReplaceQuotePatch();
	afx_msg void OnMenuSoundRemove();
	afx_msg void OnMenuSoundRemovePatch();
	afx_msg void OnMenuSoundExtract();
	afx_msg void OnMenuSoundExtractPatch();
	afx_msg void OnMenuSoundSave();
	afx_msg void OnMenuSoundSaveNPK();
	afx_msg void OnMenuSoundSaveNPKPatch();
	afx_msg void OnMenuSoundCopyResource();
	afx_msg void OnMenuSoundCopyQuote();
	afx_msg void OnMenuSoundRename();
	afx_msg void OnMenuSoundDequote();
	afx_msg void OnMenuSoundDequotePatch();
	afx_msg void OnMenuSoundHide();
	afx_msg void OnMenuSoundHidePatch();
	afx_msg void OnMenuSoundSelectAll();
	afx_msg void OnMenuSoundSelectReverse();
	afx_msg void OnMenuSoundSelectHighline();
	afx_msg void OnMenuSoundMoveUp();
	afx_msg void OnMenuSoundMoveDown();
	afx_msg void OnClose();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedToolButton14();
	afx_msg void OnBnClickedToolButton15();
	afx_msg void OnToolsPiano();
};
