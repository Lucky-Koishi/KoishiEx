
// ExParrotDlg.h : ͷ�ļ�
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx//KoishiNeoplePack.h"
#include "../KoishiEx//KoishiAudioTool.h"

#include "TinyBar.h"

#include "ModalRename(white).h"
#include "ModalPreference(white).h"

#pragma once

#define VERSION_STR "������Ex��è��.3.2"

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
	ProfileWhite profile;
public:
	//��������
	NPKobject no;
	OGGvorbis::OGGcomment OGGcopyRight;
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

	//SND�б���
	void SNDloadList();				//��ȡIMG�б�
	void SNDupdateList();			//��������IMG��
	void SNDupdateTerm(int pos);	//����ĳһ��IMG��
	void SNDaddTerm(int pos, SNDversion sv, CString comment);
	void SNDdeleteTerm(int pos);
	void SNDmodifyTerm(int pos, SNDversion sv, CString comment);
	void SNDmodifyIcon(int pos, SNDversion sv);
	void SNDsetHighLine(int pos);	//ǿ�Ƹ��ĸ����У��Լ���ǰѡ���־��
	queue SNDgetChecked(enumSelectType selectType);
	UINT SNDiconID(SNDversion sv);

	//void updateSNDlist();
	//void updateSNDterm(int pos);
	void updateInfo();
	void updateCommentInfo(const SNDversion &ver);
	void updateMP3image();
	void updateModified();
	void resetBound();
	BOOL getMouseAxis(point &pt);
	BOOL getMousePos(longex &pos);
	CPoint getWinMouseAxis();
	void OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt);
public:
	DeclareThreadFunc(CExParrotDlg, play, BOOL);			//�����̣߳�BOOL=TURE -> ֻ����ѡ���� 
	DeclareThreadFunc(CExParrotDlg, RecordStart, BOOL);	//¼���̣߳�BOOL������
	DeclareThreadFunc(CExParrotDlg, RecordFinish, BOOL);	//¼�����������̣߳�BOOL������
	DeclareThreadFunc(CExParrotDlg, ReplaceSound, BOOL);	//��Ƶ���滻�̣߳�BOOL������
	DeclareThreadFunc(CExParrotDlg, Draw, BOOL);			//����ʱ��ͼ�̣߳�BOOL������
	DeclareThreadFunc(CExParrotDlg, DrawPower, BOOL);		//����Ƶ��ͼ�̣߳�BOOL������
	DeclareThreadFunc(CExParrotDlg, DecodeAndPlay, BOOL);	//�����߳�
	void draw();
	void makeGraph(image &graphMat, int w, int h);
	void decodeAndPlay();
	enum enumCopyRightOpera {
		CRO_NONE,
		CRO_CREATE,
		CRO_MODIFIED,
		CRO_CLEAR		//��WAV���ް�Ȩ��ʽ����Ƶת�����а�Ȩ��ʽ����Ƶʱ����ã���Ϊ������û���κΰ�Ȩ
	};
	//���룬����Profile���outputQuality�������PCM����OGG
	BOOL setCopyRight(enumCopyRightOpera opera);
	BOOL encodeTo(stream &dest);		
	BOOL encodeTo(const audio &newAd, stream &dest);
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
	DeclareThreadFunc(CExParrotDlg, SoundInsertEmpty, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundInsertSND, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundInsertNPK, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundInsertFolder, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundInsertOther, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundReplaceExtern, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundReplaceLocal, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundReplaceQuote, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundTransToWAV, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundTransToOGG, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundRemove, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundExtract, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundSaveAsNPK, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundDequote, DWORD);
	DeclareThreadFunc(CExParrotDlg, SoundHide, DWORD);
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
	afx_msg void OnMenuSoundTransformToWAV();
	afx_msg void OnMenuSoundTransformToOGG();
	afx_msg void OnMenuSoundTransformToWAVPatch();
	afx_msg void OnMenuSoundTransformToOGGPatch();
	afx_msg void OnToolsAudioMark();
};
