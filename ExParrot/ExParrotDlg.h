
// ExParrotDlg.h : ͷ�ļ�
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx//KoishiNeoplePack.h"
#include "../KoishiEx//KoishiAudioTool.h"

#include "TinyBar(white).h"

#include "ModalRename(white).h"
#include "ModalPreference(white).h"

#pragma once

#define VERSION_STR "������Ex��è��.2.1"

using namespace Koishi;
using namespace KoishiNeoplePack;
using namespace KoishiAudioTool;
// CExParrotDlg �Ի���
class CExParrotDlg : public CDialogEx
{
// ����
public:
	CExParrotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXPARROT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Profile profile;
public:
	//��������
	NPKobject no;
	audio au;
	CString fileNPKname;
	CString fileSNDname;
	//������
	PCMplayer player;
	PCMdevice recorder;
	//�ź���
	volatile int processing;
	volatile int sizing;
	bool recording;
	//������
	int width, height, barWidth;
	int barHeight, barPart1, barPart2;	
	//������
	bool NPKsaveAlert;
	bool SNDsaveAlert;
	int crtSNDid;
	int fndSNDid;
	image MP3image;
	//����ָ��
	longex leftBound;				//��ǰѡ����߽�
	longex rightBound;				//��ǰѡ���ұ߽�
	longex dispLeftBound;			//��ǰ��ʾ��߽�
	longex dispRightBound;			//��ǰ��ʾ�ұ߽�
	longex zoomBound1;				//�Ŵ�ʱѡ��Χ����߽�
	longex zoomBound2;				//�Ŵ�ʱѡ��Χ���б߽�
public:
	enum enumCanvasOperation{
		CANVAS_SELECT,		//������ʾ
		CANVAS_ZOOM,		//�϶�
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
		int currentCursor;						//��ǰ���
		bool canvasOperating;					//���ڲ���
		enumCanvasOperation canvasOperation;    //��������
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
	DeclareThreadFunc(play, BOOL);			//�����̣߳�BOOL=TURE -> ֻ����ѡ���� 
	DeclareThreadFunc(RecordStart,	BOOL);	//¼���̣߳�BOOL������
	DeclareThreadFunc(RecordFinish, BOOL);	//¼�����������̣߳�BOOL������
	DeclareThreadFunc(ReplaceSound,	BOOL);	//��Ƶ���滻�̣߳�BOOL������
	DeclareThreadFunc(Draw, BOOL);			//����ʱ��ͼ�̣߳�BOOL������
	DeclareThreadFunc(DrawPower, BOOL);		//����Ƶ��ͼ�̣߳�BOOL������
	DeclareThreadFunc(DecodeAndPlay, BOOL);		//�����߳�
	void draw();
	void makeGraph(image &graphMat, int w, int h);
	void decodeAndPlay();
public:
	//����ؼ�
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
	//SND�Ҽ��˵�
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
