
// ExParrotDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ExParrotDlg.h"
#include "afxdialogex.h"
#include "TinyAdjustVolume.h"
#include "TinyAdjustSpeed.h"
#include "TinyStretch.h"
#include "TinyEcho.h"
#include "TinySetName(white).h"
#include "TinySNDSelect.h"
#include "ModalConflictWarning(white).h"
#include "ModalSaveWarning(white).h"
#include "ToolDownload.h"
#include "ToolDownloadServerSelection.h"
#include <thread>
#include "ToolPiano.h"
#include "ToolAudioMark.h"
#include "Music.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef DEBUG
#define UGLY			0
#define trace(x)		TRACE(L##x)
#else
#define UGLY 1
#define trace(x)
#endif

// CExParrotDlg �Ի���




CExParrotDlg::CExParrotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExParrotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAIN);
	profile.loadProfile();
	width = 1210;
	height = 650;
	SNDsaveAlert = false;
	NPKsaveAlert = false;
	recording = false;
	crtSNDid = 0;
	fndSNDid = 0;
	leftBound = 0;
	rightBound = 0;
	dispLeftBound = 0;
	dispRightBound = 441000;		//��ʾ�ı߽��Ĭ��10�루Ĭ�ϲ���Ƶ��44100Hz)
	zoomBound1 = 0;
	zoomBound2 = 0;
	processing = 0;
	sizing = 0;
	canvasOperatePara.canvasOperating = false;
	canvasOperatePara.canvasOperation = CANVAS_SELECT;
	canvasOperatePara.firstPos = 0;
}

void CExParrotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExParrotDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MENU, &CExParrotDlg::OnBnClickedButtonMenu)
	ON_BN_CLICKED(IDC_BUTTON_MENU2, &CExParrotDlg::OnBnClickedButtonMenu2)
	ON_BN_CLICKED(IDC_BUTTON_MENU3, &CExParrotDlg::OnBnClickedButtonMenu3)
	ON_COMMAND(IDM_MAIN_01, &CExParrotDlg::OnMain01)
	ON_COMMAND(IDM_MAIN_02, &CExParrotDlg::OnMain02)
	ON_COMMAND(IDM_MAIN_03, &CExParrotDlg::OnMain03)
	ON_COMMAND(IDM_MAIN_04, &CExParrotDlg::OnMain04)
	ON_COMMAND(IDM_MAIN_05, &CExParrotDlg::OnMain05)
	ON_COMMAND(IDM_MAIN_06, &CExParrotDlg::OnMain06)
	ON_COMMAND(IDM_MAIN_07, &CExParrotDlg::OnMain07)
	ON_COMMAND(IDM_MAIN_08, &CExParrotDlg::OnMain08)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SND, &CExParrotDlg::OnNMClickListSnd)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SND, &CExParrotDlg::OnNMRClickListSnd)
	ON_COMMAND(ID_MENU_SOUND_INERT_EMPTY, &CExParrotDlg::OnMenuSoundInertEmpty)
	ON_COMMAND(ID_MENU_SOUND_INERT_SND, &CExParrotDlg::OnMenuSoundInertSnd)
	ON_COMMAND(ID_MENU_SOUND_INERT_NPK, &CExParrotDlg::OnMenuSoundInertNPK)
	ON_COMMAND(ID_MENU_SOUND_INERT_FOLDER, &CExParrotDlg::OnMenuSoundInertFolder)
	ON_COMMAND(ID_MENU_SOUND_INERT_OTHER, &CExParrotDlg::OnMenuSoundInertOther)
	ON_COMMAND(ID_MENU_SOUND_INERT_EMPTY_BLANK, &CExParrotDlg::OnMenuSoundInertEmptyBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_SND_BLANK, &CExParrotDlg::OnMenuSoundInertSNDBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_NPK_BLANK, &CExParrotDlg::OnMenuSoundInertNPKBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_FOLDER_BLANK, &CExParrotDlg::OnMenuSoundInertFolderBlank)
	ON_COMMAND(ID_MENU_SOUND_INERT_OTHER_BLANK, &CExParrotDlg::OnMenuSoundInertOtherBlank)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_SND, &CExParrotDlg::OnMenuSoundReplaceSND)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_COPY, &CExParrotDlg::OnMenuSoundReplaceCopy)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_QUOTE, &CExParrotDlg::OnMenuSoundReplaceQuote)
	ON_COMMAND(ID_MENU_SOUND_INSERT_SND_PATCH, &CExParrotDlg::OnMenuSoundInsertSndPatch)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_COPY_PATCH, &CExParrotDlg::OnMenuSoundReplaceCopyPatch)
	ON_COMMAND(ID_MENU_SOUND_REPLACE_QUOTE_PATCH, &CExParrotDlg::OnMenuSoundReplaceQuotePatch)
	ON_COMMAND(ID_MENU_SOUND_REMOVE, &CExParrotDlg::OnMenuSoundRemove)
	ON_COMMAND(ID_MENU_SOUND_REMOVE_PATCH, &CExParrotDlg::OnMenuSoundRemovePatch)
	ON_COMMAND(ID_MENU_SOUND_SAVE_NPK, &CExParrotDlg::OnMenuSoundSaveNPK)
	ON_COMMAND(ID_MENU_SOUND_SAVE_NPK_PATCH, &CExParrotDlg::OnMenuSoundSaveNPKPatch)
	ON_COMMAND(ID_MENU_SOUND_COPY_RESOURCE, &CExParrotDlg::OnMenuSoundCopyResource)
	ON_COMMAND(ID_MENU_SOUND_COPY_QUOTE, &CExParrotDlg::OnMenuSoundCopyQuote)
	ON_COMMAND(ID_MENU_SOUND_DEQUOTE, &CExParrotDlg::OnMenuSoundDequote)
	ON_COMMAND(ID_MENU_SOUND_DEQUOTE_PATCH, &CExParrotDlg::OnMenuSoundDequotePatch)
	ON_COMMAND(ID_MENU_SOUND_HIDE_PATCH, &CExParrotDlg::OnMenuSoundHidePatch)
	ON_COMMAND(ID_MENU_SOUND_SELECT_ALL, &CExParrotDlg::OnMenuSoundSelectAll)
	ON_COMMAND(ID_MENU_SOUND_SELECT_REVERSE, &CExParrotDlg::OnMenuSoundSelectReverse)
	ON_COMMAND(ID_MENU_SOUND_SELECT_HIGHLINE, &CExParrotDlg::OnMenuSoundSelectHighline)
	ON_COMMAND(ID_MENU_SOUND_EXTRACT, &CExParrotDlg::OnMenuSoundExtract)
	ON_COMMAND(ID_MENU_SOUND_EXTRACT_PATCH, &CExParrotDlg::OnMenuSoundExtractPatch)
	ON_COMMAND(ID_MENU_SOUND_RENAME, &CExParrotDlg::OnMenuSoundRename)
	ON_COMMAND(ID_MENU_SOUND_HIDE, &CExParrotDlg::OnMenuSoundHide)
	ON_COMMAND(ID_MENU_SOUND_MOVE_UP, &CExParrotDlg::OnMenuSoundMoveUp)
	ON_COMMAND(ID_MENU_SOUND_MOVE_DOWN, &CExParrotDlg::OnMenuSoundMoveDown)
	ON_COMMAND(ID_MENU_SOUND_SAVE, &CExParrotDlg::OnMenuSoundSave)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL1, &CExParrotDlg::OnBnClickedButtonControl1)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL2, &CExParrotDlg::OnBnClickedButtonControl2)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL3, &CExParrotDlg::OnBnClickedButtonControl3)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL4, &CExParrotDlg::OnBnClickedButtonControl4)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL5, &CExParrotDlg::OnBnClickedButtonControl5)
	ON_BN_CLICKED(IDC_TOOL_BUTTON1, &CExParrotDlg::OnBnClickedToolButton1)
	ON_BN_CLICKED(IDC_TOOL_BUTTON2, &CExParrotDlg::OnBnClickedToolButton2)
	ON_BN_CLICKED(IDC_TOOL_BUTTON3, &CExParrotDlg::OnBnClickedToolButton3)
	ON_BN_CLICKED(IDC_TOOL_BUTTON4, &CExParrotDlg::OnBnClickedToolButton4)
	ON_BN_CLICKED(IDC_TOOL_BUTTON5, &CExParrotDlg::OnBnClickedToolButton5)
	ON_BN_CLICKED(IDC_TOOL_BUTTON6, &CExParrotDlg::OnBnClickedToolButton6)
	ON_BN_CLICKED(IDC_TOOL_BUTTON7, &CExParrotDlg::OnBnClickedToolButton7)
	ON_BN_CLICKED(IDC_TOOL_BUTTON8, &CExParrotDlg::OnBnClickedToolButton8)
	ON_BN_CLICKED(IDC_TOOL_BUTTON9, &CExParrotDlg::OnBnClickedToolButton9)
	ON_BN_CLICKED(IDC_TOOL_BUTTON10, &CExParrotDlg::OnBnClickedToolButton10)
	ON_BN_CLICKED(IDC_TOOL_BUTTON11, &CExParrotDlg::OnBnClickedToolButton11)
	ON_BN_CLICKED(IDC_TOOL_BUTTON12, &CExParrotDlg::OnBnClickedToolButton12)
	ON_BN_CLICKED(IDC_TOOL_BUTTON13, &CExParrotDlg::OnBnClickedToolButton13)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_IMGSEARCH, &CExParrotDlg::OnBnClickedButtonSNDsearch)
	ON_COMMAND(IDM_TOOL_DOWNLOAD, &CExParrotDlg::OnToolDownload)
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_TOOL_BUTTON14, &CExParrotDlg::OnBnClickedToolButton14)
	ON_BN_CLICKED(IDC_TOOL_BUTTON15, &CExParrotDlg::OnBnClickedToolButton15)
	ON_COMMAND(ID_TOOLS_PIANO, &CExParrotDlg::OnToolsPiano)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_WAV, &CExParrotDlg::OnMenuSoundTransformToWAV)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_OGG, &CExParrotDlg::OnMenuSoundTransformToOGG)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_WAV_PATCH, &CExParrotDlg::OnMenuSoundTransformToWAVPatch)
	ON_COMMAND(ID_MENU_SOUND_TRANSFORM_TO_OGG_PATCH, &CExParrotDlg::OnMenuSoundTransformToOGGPatch)
	ON_COMMAND(ID_TOOLS_AUDIO_MARK, &CExParrotDlg::OnToolsAudioMark)
END_MESSAGE_MAP()


// CExParrotDlg ��Ϣ�������

BOOL CExParrotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText(_T(VERSION_STR));
	SetWindowPos(NULL,0,0,width,height,SWP_NOZORDER|SWP_NOMOVE);
	CRect rc;
	GetClientRect(rc);
	adjustWindow(rc.Width(), rc.Height());
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetExtendedStyle(GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->EasyInsertColumn(L"��Ч��,200");
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(L"������ʾNPK�ļ�����Ϣ");
	GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"������ʾ��Ƶ����Ϣ");
	GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(L"������ʾ��Ƶ�İ�Ȩ��Ϣ");

	i_lSND.Create(16,16, TRUE|ILC_COLOR24, 6, 1);
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_UNKNOWN));	//0����Դ����Ч
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_LINK));		//1����Դ��LINK
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_IMAGE));	//2����Դ
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_SOUND_WAVE));		//3����Դ
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_SOUND_VORBIS));
	i_lSND.Add(AfxGetApp()->LoadIconW(IDI_ICON_SOUND_MP3));
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetImageList(&i_lSND, LVSIL_SMALL);

	CREATEW(bar, IDD_TINY_PROGRESSBAR);
#if UGLY
	m_buttonPic[0].LoadBitmap(IDB_BITMAP_TOOL1);
	m_buttonPic[1].LoadBitmap(IDB_BITMAP_TOOL2);
	m_buttonPic[2].LoadBitmap(IDB_BITMAP_TOOL3);
	m_buttonPic[3].LoadBitmap(IDB_BITMAP_TOOL4);
	m_buttonPic[4].LoadBitmap(IDB_BITMAP_TOOL5);
	m_buttonPic[5].LoadBitmap(IDB_BITMAP_TOOL6);
	m_buttonPic[6].LoadBitmap(IDB_BITMAP_TOOL7);
	m_buttonPic[7].LoadBitmap(IDB_BITMAP_TOOL8);
	m_buttonPic[8].LoadBitmap(IDB_BITMAP_TOOL9);
	m_buttonPic[9].LoadBitmap(IDB_BITMAP_TOOL10);
	m_buttonPic[10].LoadBitmap(IDB_BITMAP_TOOL11);
	m_buttonPic[11].LoadBitmap(IDB_BITMAP_TOOL12);
	m_buttonPic[12].LoadBitmap(IDB_BITMAP_TOOL13);
	m_buttonPic[13].LoadBitmap(IDB_BITMAP_TOOL14);
	m_buttonPic[14].LoadBitmap(IDB_BITMAP_TOOL15);
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
			m_logoPic.LoadBitmapW(IDB_BITMAP_LOGO);
	}
	GET_CTRL(CStatic, IDC_LOGO)->SetBitmap(m_logoPic);
#endif
	no.create();
	fileNPKname = L"newNPK.npk";

	m_ttc.Create(this);
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON1), L"ѡ��");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON2), L"�Ŵ�");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON3), L"�϶�");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON4), L"ѡ�����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON5), L"ѡ���ұ�");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON6), L"ȫѡ");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON7), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON8), L"��������");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON9), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON10), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON11), L"��ת");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON12), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON13), L"����");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON14), L"�ٶȵ���");
	m_ttc.AddTool(GET_CTRL(CButton, IDC_TOOL_BUTTON15), L"��������");
	MP3image.create(1,1);
	MP3image.fill(profile.getAudioColor(4));

	StartThreadFunc(DrawPower, 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExParrotDlg::OnPaint()
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
		draw();
		updateMP3image();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExParrotDlg::OnQueryDragIcon(){
	return static_cast<HCURSOR>(m_hIcon);
}
void CExParrotDlg::decodeAndPlay() {
	StartThreadFunc(DecodeAndPlay, 0);
}
void CExParrotDlg::draw(){
	if(rightBound - leftBound > 0){
		GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowText(L"���:" + DoubleToCStr(0.001F*au.getTime(leftBound))+L"s");
		GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowText(L"�Ҷ�:" + DoubleToCStr(0.001F*au.getTime(rightBound))+L"s");
	}else{
		GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowText(L"���:" + DoubleToCStr(0.001F*au.getTime(0))+L"s");
		GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowText(L"�Ҷ�:" + DoubleToCStr(0.001F*au.getLastTime())+L"s");
	}
	StartThreadFunc(Draw, 0);
}
void CExParrotDlg::makeGraph(image &graphMat, int w, int h){
	color clrLeftChannel = profile.getAudioColor(1);//color(0xFF, 0xff, 0x66, 0x00);
	color clrRightChannel = profile.getAudioColor(2);//color(0xFF, 0xff, 0x00, 0xCC);
	color clrBack = profile.getAudioColor(0);//color(0xFF,0x66,0xCC,0xFF);
	color clrBound = color(0xFF,0,0,0);
	color clrZoom = color(0xFF,0xFF,0x22,0x22);
	graphMat.create(h, w);
	graphMat.fill(clrBack);
	int i, j;
	image content;
	if(KoishiImageTool::loadPNG(content, CStrToStr(profile.getSupportPath() + L"back.png"))){
		for(i = 0;i<content.getWidth();i++){
			for(j = 0;j<content.getHeight();j++){
				color clr = content.getElem(j, i);
				if(i<content.getWidth()*0.3 || j < content.getHeight()*0.3){
					clr.alpha = MIN(0xB0*j/(0.3*content.getHeight()), 0xB0*i/(0.3*content.getWidth()));
				}else{
					clr.alpha = 0xB0;
				}
				content.setElem(j,i,clr);
			}
		}
		graphMat.putFore(content, LAY, point(w - content.getWidth(), h - content.getHeight()));
	}
	content.destory();

	graphMat.rectangle(point(0,0),point(w-1,h-1),clrBound);
	graphMat.rectangle(point(1,1),point(w-2,h-2),clrBound);
	graphMat.line(point(0,(h-1)/2),point(w-1,(h-1)/2),clrBound);
	for(i = 0;i<h*w;i++){
		int x = i % w;
		int y = i / w;
		int xd = (dispRightBound - dispLeftBound) * x / w + dispLeftBound;
		int yd = 32768 - 65536 * y / (h / 2);
		if(xd<au.length && xd >= 0){
			//�Ѷ�������
			int yd0 = abs(au[xd][0]);
			int yd1 = abs(au[xd][1]);
			if( yd >= -abs(yd0) && yd <= abs(yd0)){
				graphMat.setElem(i, clrLeftChannel);
			}else if(yd + 65536 >= -abs(yd1) && yd + 65536 <= abs(yd1)){
				graphMat.setElem(i, clrRightChannel);
			}
			//��ѡ������
			if(leftBound < rightBound && xd >= leftBound && xd <rightBound){
				color T = graphMat.getElem(i);
				color T1 = color(0XFF, 0XFF-T.R, 0XFF-T.G, 0XFF-T.B);
				graphMat.setElem(i, T1);
			}
		}else{
			//δ��������
			color T = graphMat.getElem(i);
			color T1 = color(0XFF, T.R/2, T.G/2, T.B/2);
			graphMat.setElem(i, T1);
		}
	}
	if(zoomBound1 != 0 && zoomBound1 >= dispLeftBound && zoomBound1 < dispRightBound){
		int XX = (zoomBound1 - dispLeftBound) * w / (dispRightBound - dispLeftBound);
		graphMat.line(point(XX,1), point(XX,h-1), clrZoom);
	}
	if(zoomBound2 != 0 && zoomBound2 >= dispLeftBound && zoomBound2 < dispRightBound){
		int XX = (zoomBound2 - dispLeftBound) * w / (dispRightBound - dispLeftBound);
		graphMat.line(point(XX,1), point(XX,h-1), clrZoom);
	}
	return;
}
void CExParrotDlg::adjustWindow(int w, int h){
	//�������ڿؼ�
	CHECK_VALID(w>=700);
	CHECK_VALID(h>=500);
	width = w;
	height = h;
	barWidth = (w-540);
	barPart1 = barWidth*30/45;
	barPart2 = barWidth*15/45;
	barHeight = 30;
	GET_CTRL(CStatic, IDC_LOGO)->SetWindowPos(NULL,10,10,150,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU)->SetWindowPos(NULL,170,10,110,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU2)->SetWindowPos(NULL,290,10,110,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_MENU3)->SetWindowPos(NULL,410,10,110,40,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_SNDSEARCH)->SetWindowPos(NULL,10,60,100,25,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_IMGSEARCH)->SetWindowPos(NULL,120,60,40,25,SWP_NOZORDER);
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetWindowPos(NULL,10,95,150,h-115,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowPos(NULL,170,60,170,80,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowPos(NULL,350,60,170,80,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowPos(NULL,170,150,170,170,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL1)->SetWindowPos(NULL,170,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL2)->SetWindowPos(NULL,241,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL3)->SetWindowPos(NULL,312,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowPos(NULL,383,330,66,40,SWP_NOZORDER);
	GET_CTRL(CButton, IDC_BUTTON_CONTROL5)->SetWindowPos(NULL,454,330,66,40,SWP_NOZORDER);

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
	GET_CTRL(CButton, IDC_TOOL_BUTTON15)->SetWindowPos(NULL, 530 + delta * 14, h - 10 - barHeight, delta, barHeight, SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_RANGE1)->SetWindowPos(NULL,530+barPart1+barPart2*0/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_RANGE2)->SetWindowPos(NULL,530+barPart1+barPart2*1/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
	GET_CTRL(CEdit, IDC_EDIT_RANGE3)->SetWindowPos(NULL,530+barPart1+barPart2*2/3,h-10-barHeight,barPart2/3,barHeight,SWP_NOZORDER);
}
UINT CExParrotDlg::SNDiconID(SNDversion sv) {
	switch(sv) {
	case VWAVE:
		return 3;
	case VVORBIS:
		return 4;
	case VMP3:
		return 5;
	case VIMAGE:
		return 2;
	case VSNDQUOTE:
		return 1;
	default:
		return 0;
	}
	return 0;
}
void CExParrotDlg::SNDaddTerm(int pos, SNDversion sv, CString comment) {
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	if(pos == -1) {
		ctl->InsertItem(ctl->GetItemCount(), comment, SNDiconID(sv));
	} else {
		ctl->InsertItem(pos, comment, SNDiconID(sv));
	}
}
void CExParrotDlg::SNDdeleteTerm(int pos) {
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	ctl->DeleteItem(pos);
}
void CExParrotDlg::SNDmodifyTerm(int pos, SNDversion sv, CString comment) {
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	ctl->SetItemText(pos, 0, comment);
	ctl->SetItem(pos, 0, LVIF_IMAGE, NULL, SNDiconID(sv), 0, 0, 0);
}
void CExParrotDlg::SNDmodifyIcon(int pos, SNDversion sv) {
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	ctl->SetItem(pos, 0, LVIF_IMAGE, NULL, SNDiconID(sv), 0, 0, 0);
}
void CExParrotDlg::SNDsetHighLine(int pos) {
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	if(pos >= 0) {
		ctl->SetSelectionMark(pos);
		ctl->SetItemState(pos, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}
	if(crtSNDid >= 0) {
		ctl->SetItemState(crtSNDid, 0, LVIS_SELECTED | LVIS_FOCUSED);
	}
	crtSNDid = pos;
}
void CExParrotDlg::SNDloadList() {
	updateInfo();
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	ctl->DeleteAllItems();
	for(int i = 0; i < no.getCount(); i++) {
		long qti = no.checkQuote(i);
		if(i != qti) {
			SNDaddTerm(-1, VSNDQUOTE,
					   GetTail(StrToCStr(no.content[i].comment)) + L"->" +
					   GetTail(StrToCStr(no.content[qti].comment)));
		} else {
			SNDaddTerm(-1, no.SNDgetVersion(i),
					   GetTail(StrToCStr(no.content[i].comment)));
		}
	}
}
void CExParrotDlg::SNDupdateTerm(int pos) {
	long qtPos = no.checkQuote(pos);
	if(qtPos != pos) {
		SNDmodifyTerm(pos, VSNDQUOTE,
					  GetTail(StrToCStr(no.content[pos].comment)) + L"->" +
					  GetTail(StrToCStr(no.content[qtPos].comment)));
	} else {
		SNDmodifyTerm(pos, no.SNDgetVersion(pos),
					  GetTail(StrToCStr(no.content[pos].comment)));
	}
}
void CExParrotDlg::SNDupdateList() {
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	int nc = no.getCount();
	int ic = ctl->GetItemCount();
	for(int i = 0; i < max(nc, ic); i++) {
		if(i < ic && i < nc) {
			SNDupdateTerm(i);
		}
		if(i >= ic && i < nc) {
			//��ǰNPK��Ŀ��Ŀ�����б�
			long qti = no.checkQuote(i);
			if(i != qti) {
				SNDaddTerm(-1, VSNDQUOTE,
						   GetTail(StrToCStr(no.content[i].comment)) + L"->" +
						   GetTail(StrToCStr(no.content[qti].comment)));
			} else {
				SNDaddTerm(-1, no.SNDgetVersion(i),
						   GetTail(StrToCStr(no.content[i].comment)));
			}
		}
		if(i >= nc && i < ic) {
			//��ǰ�б���Ŀ��Ŀ����NPK
			SNDdeleteTerm(nc);
		}
	}
}
queue CExParrotDlg::SNDgetChecked(enumSelectType selectType) {
	queue selected;
	auto ctl = GET_CTRL(CGoodListCtrl, IDC_LIST_SND);
	switch(selectType) {
	case SINGLE_SELECT:
		selected.push_back(crtSNDid);
		return selected;
	case MULTI_SELECT:
		for(int k = 0; k<ctl->GetItemCount(); k++)
			if(ctl->GetCheck(k))
				selected.push_back(k);
		return selected;
	case ALL_SELECT:
		for(int k = 0; k<ctl->GetItemCount(); k++)
			selected.push_back(k);
		return selected;
	}
	return selected;
}
void CExParrotDlg::updateInfo(){
	CString cstr;
	cstr = L"�ļ�����"+GetTail(fileNPKname)+L"\r\n";
	cstr += L"��С��"+NumToCStr(no.getSize())+L"�ֽ�\r\n";
	cstr += L"��Ŀ����" + NumToCStr(no.getCount()) + L"\r\n";
	cstr += L"ʵ������" + NumToCStr(no.block.size()) + L"\r\n";
	cstr += (crtSNDid == -1) ? L"��ǰ��Ŀ��δѡ��" : (L"��ǰ��Ŀ��" + (NumToCStr(crtSNDid)) + L"\r\n");
	long qtCrtSNDid = no.checkQuote(crtSNDid);
	if(qtCrtSNDid != crtSNDid) {
		cstr += L"�����ԣ�" + GetTail(StrToCStr(no.content[qtCrtSNDid].comment));
	}
	GET_CTRL(CEdit, IDC_EDIT_NPK)->SetWindowText(cstr);

	cstr = SNDsaveAlert ? L"��Ч״̬���ѱ䶯\r\n" : L"��Ч״̬��δ�䶯\r\n";
	cstr += L"������:" + NumToCStr(au.channel) + L"\r\n";
	cstr += L"����Ƶ��:" + NumToCStr(au.sampleRate) + L"Hz\r\n";
	cstr += L"ʱ��:" + DoubleToCStr(au.getLastTime() * 0.001f) + L"s";
	GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(cstr);
}
void CExParrotDlg::updateCommentInfo(const SNDversion &ver) {
	CString tempStr;
	switch(ver) {
	case SNDversion::VWAVE:
		tempStr = L"���: WAV��Ƶ(PCM��)\r\n";
		break;
	case SNDversion::VVORBIS:
		tempStr = L"���: Ogg��Ƶ\r\n��������Ϣ: \r\n" + StrToCStr(OGGcopyRight.vendorInfo) + L"\r\n";
		tempStr += L"������Ϣ:" + NumToCStr(OGGcopyRight.userInfo.size()) + L"��\r\n";
		if(OGGcopyRight.vendorInfo.size() > 0) {
			for(int i = 0; i < OGGcopyRight.userInfo.size(); i++) {
				CString userInfoStr = StrToCStr(OGGcopyRight.userInfo[i]);
				userInfoStr.Replace(L"=", L": ");
				tempStr += userInfoStr + L"\r\n";
			}
		}
		break;
	case SNDversion::VMP3:
		tempStr = L"���: MP3\r\n";
		tempStr += L"MP3���뻹û��д������";
		break;
	case SNDversion::VIMAGE:
		tempStr = L"���: IMG����\r\n";
		tempStr += L"��ʹ��������Ex��è��������������";
		break;
	default:
		tempStr = L"���: δʶ��\r\n";
		break;
	}
	GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(tempStr);
}
void CExParrotDlg::updateMP3image(){
	int i, j;
	image mat;
	MP3image.zoom(mat, 170.0f/MP3image.width, 170.0f/MP3image.height);
	CImage img;
	img.Create(170, 170, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<170;i++){
		for(j=0;j<170;j++){
			*(pst + pit*j + 4*i + 0) = mat[j][i].B;
			*(pst + pit*j + 4*i + 1) = mat[j][i].G;
			*(pst + pit*j + 4*i + 2) = mat[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,350,150);
	img.Destroy();
	ReleaseDC(pDC);
	//dlg->drawing = 0;
	mat.destory();
}
void CExParrotDlg::resetBound() {
	dispLeftBound = 0;
	dispRightBound = MAX(1, au.length - 1);
	leftBound = 0;
	rightBound = 0;
}
/////////////////////
void CExParrotDlg::play(BOOL para) {
	if((!para) || rightBound - leftBound <= 0) {
		player.play(au);
	} else {
		audio ad = au;
		ad.clip(leftBound, rightBound);
		player.play(ad);
	}
}
void CExParrotDlg::RecordStart(BOOL para) {
	recorder.initFormat(2, 16, 44100, 88200, 4, 0);
	if(!recorder.record()) {
		MessageBox(L"û�ҵ�¼���豸�����޷�¼������", L"��ʾ��");
		return;
	}
	recording = true;
	GET_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowText(L"ֹͣ¼��");
}
void CExParrotDlg::RecordFinish(BOOL para) {
	stream s;
	audio newAd;
	if(processing)
		return;
	processing = 1;
	recorder.stop();
	recorder.getData(s);
	newAd.create(s, 2, 44100);
	if(1/*���¼����С���Զ��Ŵ�¼��*/) {
		long maxEnergy = 0;
		for(int i = 0; i<newAd.length; i++) {
			long a1 = abs((long)newAd[i].value[0]);
			long a2 = abs((long)newAd[i].value[1]);
			if(a1 > maxEnergy)
				maxEnergy = a1;
			if(a2 > maxEnergy)
				maxEnergy = a2;
		}
		if(maxEnergy < 16384) {
			double powerup = 16384.f / maxEnergy;
			newAd.mult(powerup);
		}
	}
	recording = false;
	if(au.length == 0/*�����ǰ��Ч����Ϊ0���������ڣ��½���Ч*/) {
		au.destory();
		au = newAd;
		stream sFile;
		setCopyRight(CRO_CREATE);
		encodeTo(sFile);
		no.push("new_record.ogg", sFile);
		SNDaddTerm(no.getCount(), checkAudioFormat(sFile), L"new_record.ogg");
	} else if(rightBound - leftBound <= 0 /*δѡ��߽磬Ĭ���滻������Ч*/) {
		au.destory();
		au = newAd;
		setCopyRight(CRO_CREATE);
	} else /*��ѡ��߽磬���滻ѡ��߽�����Ч*/{
		audio au1, au2, au3;
		au.clip(au1, 0, leftBound);
		au.clip(au3, rightBound, au.length - 1);
		au.destory();
		au = au1;
		au.cat(newAd);
		au.cat(au3);
		rightBound = leftBound + newAd.length;
	}
	draw();
	MessageBox(L"¼���������", L"��ʾ��");
	updateModified();
	updateInfo();
	GET_CTRL(CButton, IDC_BUTTON_CONTROL4)->SetWindowText(L"¼��");
	processing = 0;
}
void CExParrotDlg::ReplaceSound(BOOL para) {
	if(rightBound - leftBound <= 0 && IDNO == MessageBox(L"��ǰδ����Ƶ�ν���ѡ��������������Ļ��������滻������Ƶ����ȷ������", L"��ʾ��"))
		return;
	CFileDialog dlg(true, L"֧�ֵ���Ч�ļ�(*.WAV,*.OGG)|*.WAV;*.OGG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"֧�ֵ���Ч�ļ�(*.WAV,*.OGG)|*.WAV;*.OGG|vorbis��Ч(*.OGG)|*.OGG||", this);
	if(IDOK != dlg.DoModal())
		return;
	CString fileName = dlg.GetPathName();
	stream sFile;
	if(!sFile.loadFile(CStrToStr(fileName))) {
		MessageBox(L"��ȡʧ������", L"��ʾ��");
		return;
	}
	SNDversion sv = checkAudioFormat(sFile);
	audio newAd;
	OGGvorbis::OGGobject newOo;
	WAV::WAVobject newWo;
	switch(sv) {
	case VVORBIS:
		bar.show(4);
		bar.setInfo(L"���ڽ���������", 0);
		if(!newOo.decodeAndMake(sFile, newAd)) {
			bar.hide();
			MessageBox(L"����ʧ������", L"��ʾ��");
			return;
		}
		bar.hide();
		break;
	case VMP3:
		MessageBox(L"�ݲ�֧��MP3��������", L"��ʾ��");
		return;
	case VWAVE:
		bar.show(4);
		bar.setInfo(L"���ڽ���������", 0);
		if(!newWo.decodeAndMake(sFile, newAd)) {
			bar.hide();
			MessageBox(L"����ʧ������", L"��ʾ��");
			return;
		}
		bar.hide();
		break;
	default:
		MessageBox(L"δ��ʶ������ļ�����", L"��ʾ��");
		return;
	}
	//ʶ����ɿ�ʼ����
	if(rightBound - leftBound <= 0) {
		au.destory();
		au = newAd;
	} else {
		audio au1, au2, au3;
		au.clip(au1, 0, leftBound);
		au.clip(au3, rightBound, au.length - 1);
		au.destory();
		au = au1;
		au.cat(newAd);
		au.cat(au3);
		rightBound = leftBound + newAd.length;
	}
	draw();
	MessageBox(L"�����������", L"��ʾ��");
	updateModified();
	updateInfo();
}
void CExParrotDlg::Draw(BOOL para) {
	int canw = width - 540;
	int canh = height - 50;
	image canvas;
	makeGraph(canvas, canw, canh);
	int i, j;
	CImage img;
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
	ReleaseDC(pDC);
	canvas.destory();
}
void CExParrotDlg::DrawPower(BOOL para) {
	long power[16] = {0};	//������
	long cur[2] = {0};		//����������ǰ����
	while(1) {
		if(recording) {
			cur[0] = recorder.energyLeft * 100 / 32767;
			cur[1] = recorder.energyRight * 100 / 32767;
			for(int i = 0; i<16; i++) {
				power[i] = recorder.freq[i] * 100 / 10000;
				if(power[i] > 100)
					power[i] = 100;
			}
		} else if(player.idv != -1) {
			cur[0] = player.dv[player.idv].energyLeft * 100 / 32767;
			cur[1] = player.dv[player.idv].energyRight * 100 / 32767;
			for(int i = 0; i<16; i++) {
				power[i] = player.dv[player.idv].freq[i] * 100 / 10000;
				if(power[i] > 100)
					power[i] = 100;
			}
		}
		if(cur[0]>100)
			cur[0] = 100;
		if(cur[1]>100)
			cur[1] = 100;
		image mat;
		int canw = 520 - 170;
		int canh = height - 10 - 380;
		mat.create(canh, canw);
		mat.fill(color(0xFF, 0, 0, 0));
		for(int i = 0; i<16; i++) {
			colorHSV hsv = {i * 360 / 16, 1.0F, 1.0F};
			color clr;
			clr.useHSV(hsv);
			mat.filledRectangle(point(2 + 18 * i, canh - (canh - 5)*(power[i] + 2) / 100), point(17 + 18 * i, canh - 3), clr);
		}
		mat.filledRectangle(point(290, canh - (canh - 5)*(cur[0] + 2) / 100), point(290 + (canw - 296) / 2, canh - 3), profile.getAudioColor(3));
		mat.filledRectangle(point(293 + (canw - 296) / 2, canh - (canh - 5)*(cur[1] + 2) / 100), point(canw - 3, canh - 3), profile.getAudioColor(3));
		int i, j;
		CImage img;
		img.Create(canw, canh, 32);
		UCHAR* pst = (UCHAR*)img.GetBits();
		int pit = img.GetPitch();
		CDC *pDC = GetDC();
		for(i = 0; i<canw; i++) {
			for(j = 0; j<canh; j++) {
				*(pst + pit*j + 4 * i + 0) = mat[j][i].B;
				*(pst + pit*j + 4 * i + 1) = mat[j][i].G;
				*(pst + pit*j + 4 * i + 2) = mat[j][i].R;
			}
		}
		img.Draw(pDC->m_hDC, 170, 380);
		img.Destroy();
		ReleaseDC(pDC);
		//dlg->drawing = 0;
		mat.destory();
		Sleep(4);
	}
}
void CExParrotDlg::DecodeAndPlay(BOOL para) {
	int id = crtSNDid;
	stream s, sPCM;
	OGGvorbis::OGGobject oo;
	WAV::WAVobject wo;
	switch(no.SNDgetVersion(id)) {
	case VVORBIS:
		bar.show(4);
		bar.setInfo(L"���ڽ���������", 0);
		no.extract(crtSNDid, s);
		fileSNDname = StrToCStr(no.content[id].comment);
		if(!oo.decodeAndMake(s, au)) {
			bar.hide();
			GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"�ö����޷�����������");
			updateCommentInfo(VSNDUKNOWN);
			MessageBox(L"����ʧ������", L"��ʾ��");
			return;
		}
		OGGcopyRight = oo.comment;
		resetBound();
		updateInfo();
		updateCommentInfo(VVORBIS);
		bar.hide();
		draw();
		player.play(au);
		Sleep(10);
		return;
	case VMP3:
		GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"MP3���뻹ûд������");
		updateCommentInfo(VMP3);
		return;
	case VWAVE:
		bar.show(4);
		bar.setInfo(L"���ڽ���������", 0);
		no.extract(crtSNDid, s);
		fileSNDname = StrToCStr(no.content[id].comment);
		if(!wo.decodeAndMake(s, au)) {
			bar.hide();
			GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"�ö����޷�����������");
			updateCommentInfo(VSNDUKNOWN);
			MessageBox(L"����ʧ������", L"��ʾ��");
			return;
		}
		resetBound();
		updateInfo();
		updateCommentInfo(VWAVE);
		bar.hide();
		draw();
		player.play(au);
		Sleep(10);
		return;
	default:
		GET_CTRL(CEdit, IDC_EDIT_SNDINFO)->SetWindowText(L"δ��ʶ������ļ���");
		GET_CTRL(CEdit, IDC_EDIT_SNDCOMMENT)->SetWindowText(L"���:�����ļ�");
		return;
	}
}
/////////////////////
BOOL CExParrotDlg::setCopyRight(enumCopyRightOpera opera) {
	if(profile.artist.GetLength() == 0)
		return FALSE;
	if(profile.artist == L"noname")
		return FALSE;
	if(opera == CRO_NONE)
		return FALSE;
	if(opera == CRO_CLEAR) {
		OGGcopyRight.clearInfo();
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		OGGcopyRight.addInfo("created_date", localt);
	}
	if(opera == CRO_CREATE) {
		OGGcopyRight.clearInfo();
		str artist = CStrToStr(profile.artist);
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		OGGcopyRight.addInfo_author(artist, localt);
	}
	if(opera == CRO_MODIFIED) {
		str modifier = CStrToStr(profile.artist);
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		OGGcopyRight.addInfo_modifier(modifier, localt);
	}
	return TRUE;
}
BOOL CExParrotDlg::encodeTo(stream &dest) {
	return encodeTo(au, dest);
}
BOOL CExParrotDlg::encodeTo(const audio &newAd, stream &dest) {
	dest.release();
	if(profile.outputQuality == 0) {
		WAV::WAVobject wo;
		if(!wo.loadAndEncode(newAd, dest)) {
			MessageBox(L"�޷�����ת��ΪWAV����", L"��ʾ��");
			return FALSE;
		}
		return TRUE;
	} else if(profile.outputQuality <= 5) {
		OGGvorbis::OGGobject newOo;
		newOo.comment = OGGcopyRight;
		double dRate[5] = {-0.1, 0, 0.4, 0.7, 1};
		if(!newOo.loadAndEncode(newAd, dest,
			OGGvorbis::OGGencodeSetting('V', -1, dRate[profile.outputQuality - 1]))) {
			MessageBox(L"�����������\r\n" + StrToCStr(newOo.errorMessage), L"��ʾ��");
			return FALSE;
		}
		return TRUE;
	}
	MessageBox(L"�޷��������ļ�ʶ��Ҫת���ĸ�ʽ��Ʒ������", L"��ʾ��");
	return FALSE;
}
/////////////////////
void CExParrotDlg::OnBnClickedButtonMenu(){
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ��  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this); 
}

void CExParrotDlg::OnBnClickedButtonMenu2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU_TOOL);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //���λ��  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}

void CExParrotDlg::OnBnClickedButtonMenu3(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	stream s;
	setCopyRight(CRO_MODIFIED);
	encodeTo(s);
	if(no.replace(crtSNDid, s)){
		MessageBox(L"��Ч�޸��������",L"��ʾ����");
		SNDsaveAlert = false;
	}else{
		MessageBox(L"��Ч�޸�ʧ������",L"��ʾ����");
	}
	s.release();
}

void CExParrotDlg::OnMain01(){
	// TODO: �ڴ���������������
	no.release();
	no.create();
	au.destory();
	fileNPKname = L"newNPK.npk";
	fileSNDname = L"newSound.ogg";
	au.create(44100);
	au.channel = 1;
	au.sampleRate = 44100;
	stream s;
	setCopyRight(CRO_CREATE);
	encodeTo(s);
	no.push("newSound.ogg", s);
	updateInfo();
	SNDloadList();
	s.release();
	au.channel = 2;
	au.sampleRate = 44100;
	au.create(1);
}

void CExParrotDlg::OnMain02(){
	// TODO: �ڴ���������������
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("����֧�ֵ��ļ�(*.NPK,*.WAV,*.OGG,*.MP3)|*.NPK;*.WAV;*.OGG;*.MP3|��Ч�ļ�(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3|NPK�ļ�(*.NPK)|*.NPK|vorbis��Ч(*.OGG)|*.OGG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		fmt = fileName.Right(1);
		CStrToStr(fileName, fn);
		if(fmt == L"K" || fmt == L"k"){
			no.release();
			if(no.loadFile(fn)){
			}else{
				MessageBox(L"��ȡʧ������");
				return;
			}
			fileNPKname = fileName;
			SNDsaveAlert = false;
			SNDloadList();
			if(no.getCount()>0) {
				GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(0);
				crtSNDid = 0;
			}
		}else{
			no.release();
			no.create();
			fileNPKname = L"newNPK.npk";
			fileSNDname = fileName;
			SNDsaveAlert = false;
			stream s;
			s.loadFile(fn);
			fileName = GetTail(fileName);
			CStrToStr(Slashing(fileName), fn);
			no.push(fn, s);
			SNDloadList();
			updateInfo();
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(0);
			crtSNDid = 0;
		}
	}
}

void CExParrotDlg::OnMain03(){
	// TODO: �ڴ���������������
	if(SNDsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_SND;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			SNDsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	str fn;
	CString fileName;
	fileName = fileNPKname;
	CStrToStr(fileName, fn);
	if(no.saveFile(fn)){
		MessageBox(_T("NPK�����������"),L"��ʾ��");
	}else{
		MessageBox(_T("NPK����ʧ������"),L"��ʾ��");
	}
}

void CExParrotDlg::OnMain04(){
	// TODO: �ڴ���������������
	if(SNDsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_SND;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			SNDsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
	CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
	CFileDialog dlg(false, defExt, GetTail(fileNPKname), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
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

void CExParrotDlg::OnMain05(){
	// TODO: �ڴ���������������
	ModalPreference2 dlg;
	dlg.modifiedProfile = profile;
	if(IDOK == dlg.DoModal()){
		profile = dlg.modifiedProfile;
		MessageBox(L"������ñ��޸���������������Ч��",L"��ʾ��");
	}
}

void CExParrotDlg::OnMain06(){
	// TODO: �ڴ���������������
	MessageBox(L"ʩ����");
}

void CExParrotDlg::OnMain07(){
	ShellExecute(NULL, L"open",L"https://github.com/Lucky-Koishi/KoishiExAPI/wiki/%E6%81%8B%E6%81%8B%E3%81%AEEx%E5%85%94%E5%AD%90%E7%89%88", NULL, NULL, SW_MAXIMIZE); 
}

void CExParrotDlg::OnMain08(){
	CDialogEx::OnCancel();
}


void CExParrotDlg::OnNMClickListSnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	////////////////////////////
	//�л�OGGʱ��ʾ����
	if(SNDsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = ModalSaveWarning::MODIFIED_SND;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			if(crtSNDid != row) {
				GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(crtSNDid, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetItemState(row, 0, LVIS_SELECTED | LVIS_FOCUSED);
			}
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			SNDsaveAlert = FALSE;
			updateInfo();
			break;
		}
	}
	GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetSelectionMark(row);
	if(row>=0){
		crtSNDid = row;
		fndSNDid = row;
		au.destory();
		decodeAndPlay();
	}
	updateInfo();
	*pResult = 0;
}


void CExParrotDlg::OnNMRClickListSnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListSnd(pNMHDR, pResult);
	/////////////////////////////////
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //���λ��
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_SOUND);  
	pPopup = menu.GetSubMenu(pNMListView->iItem < 0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}

void CExParrotDlg::OnBnClickedButtonControl1(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	StartThreadFunc(play, TRUE);
}

void CExParrotDlg::OnBnClickedButtonControl2(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷�ֹͣ����",L"��ʾ��");
		return;
	}
	player.stop();
}


void CExParrotDlg::OnBnClickedButtonControl3(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	StartThreadFunc(play, FALSE);
}

void CExParrotDlg::OnBnClickedButtonControl4(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!recording){
		StartThreadFunc(RecordStart, 0);
	}else{
		StartThreadFunc(RecordFinish, 0);
	}
}

void CExParrotDlg::OnBnClickedButtonControl5(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	StartThreadFunc(ReplaceSound, 0);
}
//������
void CExParrotDlg::OnBnClickedToolButton1(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷�ѡ������",L"��ʾ��");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_SELECT;
}
void CExParrotDlg::OnBnClickedToolButton2(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_ZOOM;
}
void CExParrotDlg::OnBnClickedToolButton3(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷��϶�����",L"��ʾ��");
		return;
	}
	canvasOperatePara.canvasOperation = CANVAS_DRAG;
}
void CExParrotDlg::OnBnClickedToolButton4(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷�ѡ������",L"��ʾ��");
		return;
	}
	rightBound = leftBound;
	leftBound = 0;
	draw();
}
void CExParrotDlg::OnBnClickedToolButton5(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷�ѡ������",L"��ʾ��");
		return;
	}
	leftBound = rightBound;
	rightBound = au.length - 1;
	draw();
}
void CExParrotDlg::OnBnClickedToolButton6(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷�ѡ������",L"��ʾ��");
		return;
	}
	leftBound = 0;
	rightBound = au.length - 1;
	draw();
}
void CExParrotDlg::OnBnClickedToolButton7(){
	//ɾ��
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷�ɾ������",L"��ʾ��");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"��ѡ��һ����Ƶ����",L"��ʾ��");
		return;
	}
	audio au1,au2;
	au.clip(au1, 0, leftBound);
	au.clip(au2, rightBound, au.length-1);
	au.destory();
	au = au1;
	au.cat(au2);
	rightBound = leftBound;
	updateModified();
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton8(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"��ѡ��һ����Ƶ����",L"��ʾ��");
		return;
	}
	TinyAdjustVolume dlg;
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	if(true){
		TinyAdjustVolume dlg;
		long maxEnergy = 0;
		for(int i = 0;i<au2.length;i++){
			long a1 = abs((long)au2[i].value[0]);
			long a2 = abs((long)au2[i].value[1]);
			if(a1 > maxEnergy)
				maxEnergy = a1;
			if(a2 > maxEnergy)
				maxEnergy = a2;
		}
		dlg.maxEnergy = maxEnergy;
		if(dlg.DoModal() == IDOK){
			au2.mult(dlg.rate);
		}else{
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();

}
void CExParrotDlg::OnBnClickedToolButton9(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"��ѡ��һ����Ƶ����",L"��ʾ��");
		return;
	}
	audio au1,au2,au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	au2.applayFadeIn(au2.length);
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton10(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"��ѡ��һ����Ƶ����",L"��ʾ��");
		return;
	}
	audio au1,au2,au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	au2.applayFadeOut(au2.length);
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton11(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���ת����",L"��ʾ��");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"��ѡ��һ����Ƶ����",L"��ʾ��");
		return;
	}
	audio au1,au2,au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	au2.reverse();
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}
void CExParrotDlg::OnBnClickedToolButton12(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"��ѡ��һ����Ƶ����",L"��ʾ��");
		return;
	}
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	if(true){
		TinyStretch dlg;
		long len = au2.length;
		dlg.originLen = len;
		dlg.sampleRate = au2.sampleRate;
		if(dlg.DoModal() == IDOK){
			au2.zoom(dlg.rate);
			rightBound = leftBound + au2.length;
		}else{
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}


void CExParrotDlg::OnBnClickedToolButton13(){
	if(au.length == 0){
		MessageBox(L"��ǰû����Ƶ�����޷���������",L"��ʾ��");
		return;
	}
	if(rightBound-leftBound <= 0){
		MessageBox(L"��ѡ��һ����Ƶ����",L"��ʾ��");
		return;
	}
	TinyAdjustVolume dlg;
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length-1);
	if(true){
		TinyEcho dlg;
		long len = au2.length;
		if(dlg.DoModal() == IDOK){
			audio au21, au22;
			au2.echo(dlg.times, au.getPos(dlg.offset), dlg.attenu);
			au2.clip(au21, 0, len);
			au2.clip(au22, len, au2.length - 1);
			len = au2.length;
			au2.destory();
			au2 = au21;
			if(au3.length < au22.length){
				au3.expand(au22.length);
			}
			au3.mixWith(au22, 1.f, 0);
			rightBound = leftBound + len;
		}else{
			return;
		}
	}
	
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}


void CExParrotDlg::OnSize(UINT nType, int cx, int cy)
{
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
	// TODO: �ڴ˴������Ϣ����������
}


void CExParrotDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
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
	// TODO: �ڴ˴������Ϣ����������
}
void CExParrotDlg::updateModified() {
	SNDsaveAlert = TRUE;
	NPKsaveAlert = TRUE;
	updateInfo();
}
BOOL CExParrotDlg::getMouseAxis(point &pt){
	CPoint myPoint = getWinMouseAxis();
	point xy(myPoint.x-530, myPoint.y-10);
	pt = xy;
	
	return myPoint.x >= 530 && myPoint.y >= 10 && myPoint.x <= width - 10 && myPoint.y <= height - 40;
}
CPoint CExParrotDlg::getWinMouseAxis(){
	CPoint myPoint;
    GetCursorPos(&myPoint); //���λ��
	ScreenToClient(&myPoint);
	return myPoint;
}
BOOL CExParrotDlg::getMousePos(longex &pos){
	point pt;
	getMouseAxis(pt);
	pos = dispLeftBound + pt.X * (dispRightBound - dispLeftBound) / (width - 540);
	return pt.X >= 0;
}
void CExParrotDlg::OnLButtonDown(UINT nFlags, CPoint pt){
	CDialogEx::OnLButtonDown(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_LEFT_PRESS, mousePt);
	}
}
void CExParrotDlg::OnRButtonDown(UINT nFlags, CPoint pt){
	CDialogEx::OnRButtonDown(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_RIGHT_PRESS, mousePt);
	}
}
void CExParrotDlg::OnMouseMove(UINT nFlags, CPoint pt){
	CDialogEx::OnMouseMove(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		//TRACE(NumToCStr(mousePt.X)+L","+NumToCStr(mousePt.Y)+L"\r\n");
		longex pt;
		getMousePos(pt);
		GET_CTRL(CEdit, IDC_EDIT_RANGE2)->SetWindowText(L"����:"+DoubleToCStr(0.001F*au.getTime(pt))+L"s");
		OnMouseEventCanvas(canvasOperatePara.canvasOperating ? CANVAS_MOUSE_LEFT_DRAG : CANVAS_MOUSE_MOVE, mousePt);
	}else{
		OnMouseEventCanvas(canvasOperatePara.canvasOperating ? CANVAS_MOUSE_LEFT_RELEASE : CANVAS_MOUSE_MOVE, mousePt);
	}
}
void CExParrotDlg::OnLButtonUp(UINT nFlags, CPoint pt){
	CDialogEx::OnLButtonUp(nFlags, pt);
	point mousePt;
	if(getMouseAxis(mousePt)){
		OnMouseEventCanvas(CANVAS_MOUSE_LEFT_RELEASE, mousePt);
	}
}

void CExParrotDlg::OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt){
	CHECK_VALID(crtSNDid >= 0);
	switch(canvasOperatePara.canvasOperation){
	case CANVAS_SELECT:
		//ѡ��
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 1;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.firstPos = 0;
			{
				longex pos;
				getMousePos(pos);
				leftBound = pos;
				canvasOperatePara.firstPos = pos;
			}
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			{
				longex pos;
				getMousePos(pos);
				if(pos<canvasOperatePara.firstPos){
					rightBound = canvasOperatePara.firstPos;
					leftBound = pos;
				}else{
					leftBound =  canvasOperatePara.firstPos;
					rightBound = pos;
				}
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			dispLeftBound = 0;
			dispRightBound = au.length - 1;
			draw();
			break;
		}
		break;
	case CANVAS_DRAG:
		//�϶�����
		switch(mouseOperation){
		case CANVAS_MOUSE_MOVE:
			canvasOperatePara.currentCursor = 2;
			break;
		case CANVAS_MOUSE_LEFT_PRESS:
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.firstPos = 0;
			{
				point pt;
				getMouseAxis(pt);
				canvasOperatePara.firstPos = pt.X;
				canvasOperatePara.oldDispLeftBound = dispLeftBound;
				canvasOperatePara.oldDispRightBound = dispRightBound;
			}
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			{
				point pt;
				getMouseAxis(pt);
				long xDelta = pt.X - canvasOperatePara.firstPos;
				longex xxDelta = xDelta * (canvasOperatePara.oldDispRightBound - canvasOperatePara.oldDispLeftBound) / (width - 540);
				dispLeftBound = canvasOperatePara.oldDispLeftBound - xDelta * (canvasOperatePara.oldDispRightBound - canvasOperatePara.oldDispLeftBound) / (width - 540);
				dispRightBound = canvasOperatePara.oldDispRightBound - xDelta * (canvasOperatePara.oldDispRightBound - canvasOperatePara.oldDispLeftBound) / (width - 540);
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			dispLeftBound = 0;
			dispRightBound = au.length - 1;
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
			canvasOperatePara.canvasOperating = true;
			canvasOperatePara.firstPos = 0;
			{
				longex pos;
				getMousePos(pos);
				zoomBound1 = pos;
				zoomBound2 = pos;
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_DRAG:
			{
				longex pos;
				getMousePos(pos);
				zoomBound2 = pos;
				draw();
			}
			break;
		case CANVAS_MOUSE_LEFT_RELEASE:
			canvasOperatePara.canvasOperating = false;
			{
				longex pos;
				getMousePos(pos);
				zoomBound2 = pos;
				if(zoomBound1 != zoomBound2){
					dispLeftBound = MIN(zoomBound1, zoomBound2);
					dispRightBound = MAX(zoomBound1, zoomBound2);
				}
				zoomBound1 = 0;
				zoomBound2 = 0;
				draw();
			}
			break;
		case CANVAS_MOUSE_RIGHT_PRESS:
			dispLeftBound = 0;
			dispRightBound = au.length - 1;
			draw();
			break;
		}
		break;
	}
}



void CExParrotDlg::OnBnClickedButtonSNDsearch(){
	CString str1,str2;
	GET_CTRL(CEdit, IDC_EDIT_SNDSEARCH)->GetWindowText(str1);
	int i;
	for (i = fndSNDid;i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount();i++){
		str2 = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndSNDid = i;
			int nItem = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetTopIndex(); 
			CRect rc;
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndSNDid - nItem)*rc.Height());
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->Scroll(sz);
			return;
		}
	}
	for (i = 0;i<fndSNDid;i++){
		str2 = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemText(i,0);
		if(str2.Find(str1) != -1){
			fndSNDid = i;
			int nItem = GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetTopIndex(); 
			CRect rc;
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemRect(nItem, rc, LVIR_BOUNDS);
			CSize sz(0, (fndSNDid - nItem)*rc.Height());
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->Scroll(sz);
			return;
		}
	}
	MessageBox(L"û���ҵ�·����������"+str1+"������Ч����",L"��ʾ��");
}


void CExParrotDlg::OnToolDownload(){
	ToolDownloadServerSelection dlg;
	if(IDOK == dlg.DoModal()) {
		ToolDownload dlg1;
		dlg1.context = this;
		dlg1.serverInfo = dlg.serverInfo;
		dlg1.folderName = profile.getDownloadPath(dlg.serverInfo.region + L"-" + dlg.serverInfo.name);
		dlg1.DoModal();
	}
}


BOOL CExParrotDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_MOUSEMOVE){
		m_ttc.RelayEvent(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CExParrotDlg::SoundInsertEmpty(DWORD para) {
	processing = 1;
	int insertPos = (para) ? no.getCount() : crtSNDid;
	audio newAu(44100, 1, 44100);
	stream s;
	setCopyRight(CRO_CREATE);
	encodeTo(newAu, s);
	no.insert(insertPos, "new_sound.ogg", s);
	SNDaddTerm(insertPos, checkAudioFormat(s), L"new_sound.ogg");
	s.release();
	newAu.destory();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundInsertSND(DWORD para) {
	processing = 1;
	int insertPos = (para) ? no.getCount() : crtSNDid;
	CFileDialog dlg(true, L"��Ч�ļ�(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"��Ч�ļ�(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3||", this);
	TinySetName dlgTiny(this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	dlgTiny.name = Slashing(GetTail(fileName));
	if(IDOK != dlgTiny.DoModal()) {
		processing = 0;
		return;
	}
	stream newStream;
	if(!newStream.loadFile(CStrToStr(fileName))) {
		MessageBox(L"����ļ��޷�������", L"��ʾ��");
		processing = 0;
		return;
	}
	no.insert(insertPos, CStrToStr(dlgTiny.name), newStream);
	SNDaddTerm(insertPos, no.SNDgetVersion(insertPos), GetTail(dlgTiny.name));
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundInsertNPK(DWORD para) {
	processing = 1;
	int insertPos = (para) ? no.getCount() : crtSNDid;
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
	bar.show(newNO.getCount());
	int countFail = 0;
	int countSkip = 0;
	int countReplace = 0;
	int countSuccess = 0;
	int conflict = -1;		//���ҳ�ͻ��
	for(int i = 0; i < newNO.getCount(); i++) {
		bar.setInfo(L"��ǰ����" + GetTail(StrToCStr(newNO.content[i].comment)) + L"������(�ɹ�" + NumToCStr(countSuccess) + L"��,����" + NumToCStr(countSkip) + L"��,�滻" + NumToCStr(countReplace) + L"��,ʧ��" + NumToCStr(countFail) + L"��)", i);
		stream newStream;
		if(!newNO.extract(i, newStream)) {
			countFail++;
			continue;
		}
		//����ͻ��
		if(TRUE) {
			conflict = -1;
			for(int j = 0; j<no.getCount(); j++) {
				CString s1 = GetTail(StrToCStr(newNO.content[i].comment));
				CString s2 = GetTail(StrToCStr(no.content[j].comment));
				if(s1 == s2) {
					conflict = j;
					break;
				}
			}
		}
		if(!noAlarm && conflict > 0) {
			ModalConflictWarning dlgWarning(this);
			dlgWarning.conflictName = StrToCStr(newNO.content[i].comment);
			dlgWarning.DoModal();
			noAlarm = dlgWarning.noAlarm;
			conflictMethod = dlgWarning.method;
		}
		if(conflict < 0) {
			no.insert(insertPos + countSuccess, newNO.content[i].comment, newStream);
			countSuccess++;
		} else {
			switch(conflictMethod) {
			case 0:
				//�滻
				no.replace(conflict, newStream);
				countReplace++;
				break;
			case 1:
				//����
				countSkip++;
				break;
			case 2:
				//����
				no.insert(insertPos + countSuccess, newNO.content[i].comment, newStream);
				countSuccess++;
				break;
			case 3:
				//����������
				no.insert(insertPos + countSuccess, newNO.content[i].comment + "(new)", newStream);
				countSuccess++;
				break;
			}
		}
	}
	MessageBox(L"�������������" + NumToCStr(newNO.getCount()) + L"��,���" + NumToCStr(countSuccess) + L"��,����" + NumToCStr(countSkip) + L"��,�滻" + NumToCStr(countReplace) + L"��,ʧ��" + NumToCStr(countFail) + L"������", L"��ʾ��");
	bar.hide();
	SNDloadList();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundInsertFolder(DWORD para) {
	processing = 1;
	int insertPos = (para) ? no.getCount() : crtSNDid;
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
	stream newStream;
	int countNPK = 0;
	int countNPKSND = 0;
	int countSND = 0;
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
			bar.setMax(newNO.getCount());
			for(int i = 0; i<newNO.getCount(); i++) {
				bar.setInfo(L"��ǰ����" + fileList[fileID] +
							L"�е�" + GetTail(StrToCStr(newNO.content[i].comment)) +
							L"������(�ɹ�" + NumToCStr(countSuccess) +
							L"��,����" + NumToCStr(countSkip) +
							L"��,�滻" + NumToCStr(countReplace) +
							L"��,ʧ��" + NumToCStr(countFail) +
							L"��)", i);
				if(!newNO.extract(i, newStream)) {
					countFail++;
					continue;
				}
				if(TRUE) {
					conflict = -1;
					for(int j = 0; j<no.getCount(); j++) {
						CString s1 = GetTail(StrToCStr(newNO.content[i].comment));
						CString s2 = GetTail(StrToCStr(no.content[j].comment));
						if(s1 == s2) {
							conflict = j;
							break;
						}
					}
				}
				if(!noAlarm && conflict > 0) {
					ModalConflictWarning dlgWarning(this);
					dlgWarning.conflictName = StrToCStr(newNO.content[i].comment);
					dlgWarning.DoModal();
					noAlarm = dlgWarning.noAlarm;
					conflictMethod = dlgWarning.method;
				}
				if(conflict < 0) {
					no.insert(insertPos + totalSuccess, newNO.content[i].comment, newStream);
					countSuccess++;
					totalSuccess++;
				} else {
					switch(conflictMethod) {
					case 0:
						//�滻
						no.replace(conflict, newStream);
						countReplace++;
						break;
					case 1:
						//����
						countSkip++;
						break;
					case 2:
						//����
						no.insert(insertPos + countSuccess, newNO.content[i].comment, newStream);
						countSuccess++;
						totalSuccess++;
						break;
					case 3:
						//����������
						no.insert(insertPos + countSuccess, newNO.content[i].comment + "(new)", newStream);
						countSuccess++;
						totalSuccess++;
						break;
					}
				}
				newStream.release();
			}
			newNO.release();
			countNPK++;
			countNPKSND += countSuccess;
		}
		if(fileList[fileID].Right(4) == L".ogg" || fileList[fileID].Right(4) == L".OGG") {
			if(!newStream.loadFile(CStrToStr(pathList[fileID]))) {
				continue;
			}
			bar.setInfo(L"��ǰ����" + fileList[fileID] + L"������", 0);
			CString newPathName = Slashing(fileList[fileID]);
			no.insert(insertPos + totalSuccess, CStrToStr(newPathName), newStream);
			totalSuccess++;
			newStream.release();
			countSND++;
		}
	}
	MessageBox(L"������������ɹ�������" + NumToCStr(countSND) + L"���ⲿSND������������" + NumToCStr(countNPK) + L"��NPK�ļ��е�����" + NumToCStr(countNPKSND) + L"��SND��������", L"��ʾ��");
	bar.hide();
	SNDloadList();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundInsertOther(DWORD para) {
	processing = 1;
	int insertPos = (para) ? no.getCount() : crtSNDid;
	CFileDialog dlg(true, L"�����ļ�(*.*)|*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"�����ļ��ļ�(*.*)|*.*||", this);
	if(IDOK != dlg.DoModal()) {
		processing = 0;
		return;
	}
	CString fileName = dlg.GetPathName();
	no.insertFile(insertPos, CStrToStr(GetTail(fileName)), CStrToStr(fileName));
	SNDloadList();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundReplaceExtern(DWORD para) {
	processing = 1;
	CFileDialog dlg(TRUE, L"��Ч�ļ�(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"��Ч�ļ�(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3||", this);
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
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"�����滻" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		no.replace(id, s);
		SNDupdateTerm(id);
	}
	MessageBox(L"�滻�������");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundReplaceLocal(DWORD para) {
	processing = 1;
	TinySNDSelect dlg;
	dlg.listStr.clear();
	dlg.defaultSelected = 0;
	for(int i = 0; i < no.getCount(); i++)
		dlg.listStr.push_back(no.content[i].comment);
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
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"�����滻" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		no.subscribe(id, s);
		SNDupdateTerm(id);
	}
	MessageBox(L"�滻�������");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundReplaceQuote(DWORD para) {
	processing = 1;
	TinySNDSelect dlg;
	dlg.listStr.clear();
	dlg.defaultSelected = 0;
	for(int i = 0; i < no.getCount(); i++)
		dlg.listStr.push_back(no.content[i].comment);
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
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"�����滻" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		no.replaceQuote(id, dlg.selected);
		SNDupdateTerm(id);
	}
	MessageBox(L"�滻�������");
	bar.hide();
	updateInfo();
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundRemove(DWORD para) {
	processing = 1;
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[targetList.size() - i - 1];
		bar.setInfo(L"����ɾ��" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		no.remove(id);
		SNDdeleteTerm(id);
	}
	bar.hide();
	updateInfo();
	SNDupdateList();
	SNDsetHighLine(-1);
	draw();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundExtract(DWORD para) {
	processing = 1;
	CString filePath = profile.getOutputPath(fileNPKname);
	CString fileName;
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"������ȡ" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		fileName = filePath + Underlining(StrToCStr(no.content[id].comment));
		no.extractFile(id, CStrToStr(fileName));
	}
	MessageBox(L"ȫ����ȡ��������ѱ��浽" + profile.getOutputPath(fileNPKname) + L"������", L"��ʾ��");
	bar.hide();
	updateInfo();
	processing = 0;
}
void CExParrotDlg::SoundSaveAsNPK(DWORD para) {
	processing = 1;
	queue targetList = SNDgetChecked(enumSelectType(para));
	CFileDialog dlg(FALSE, L"NPK�ļ�(*.NPK)|*.NPK", L"newNPK.NPK", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"NPK�ļ�(*.NPK)|*.NPK||", this);
	if(IDOK == dlg.DoModal()) {
		NPKobject newNo;
		newNo.create();
		bar.show(targetList.size() - 1);
		for(int i = 0; i<targetList.size(); i++) {
			int id = targetList[i];
			bar.setInfo(L"������ȡ" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
			stream tempStr;
			no.extract(id, tempStr);
			newNo.push(no.content[id].comment, tempStr);
		}
		newNo.saveFile(CStrToStr(dlg.GetPathName()));
		bar.hide();
		MessageBox(L"�����������", L"��ʾ��");
	}
	processing = 0;
}
void CExParrotDlg::SoundTransToWAV(DWORD para) {
	processing = 1;
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	int count = 0;
	int skip = 0;
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"����ת��" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		stream sour, dest;
		if(no.SNDgetVersion(id) != VVORBIS) {
			skip++;
			continue;
		}
		no.extract(id, sour);
		audio aTemp;
		WAV::WAVobject wo;
		OGGvorbis::OGGobject oo;
		if(!oo.decodeAndMake(sour, aTemp))
			continue;
		if(!wo.loadAndEncode(aTemp, dest))
			continue;
		no.replace(id, dest);
		SNDmodifyIcon(id, VWAVE);
		count++;
	}
	bar.hide();
	NPKsaveAlert = true;
	processing = 0;
	MessageBox(L"����ת��" + NumToCStr(targetList.size()) + L"�����ɹ�" + NumToCStr(count) + L"��������" + NumToCStr(skip) + L"������", L"��ʾ��");
}
void CExParrotDlg::SoundTransToOGG(DWORD para) {
	processing = 1;
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	int count = 0;
	int skip = 0;
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"����ת��" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		stream sour,dest;
		if(no.SNDgetVersion(id) != VWAVE) {
			skip++;
			continue;
		}
		no.extract(id, sour);
		audio aTemp;
		WAV::WAVobject wo;
		OGGvorbis::OGGobject oo;
		if(!wo.decodeAndMake(sour, aTemp))
			continue;
		double dRate[6] = {0.4, -0.1, 0, 0.4, 0.7, 1};
		str localt = CStrToStr(CTime::GetTickCount().Format(L"%Y-%m-%d %H:%M:%S"));
		oo.comment.addInfo("created_date", localt);
		if(!oo.loadAndEncode(aTemp, dest,
			OGGvorbis::OGGencodeSetting('V', -1, dRate[profile.outputQuality])))
			continue;
		no.replace(id, dest);
		SNDmodifyIcon(id, VVORBIS); 
		count++;
	}
	bar.hide();
	NPKsaveAlert = true;
	processing = 0;
	MessageBox(L"����ת��" + NumToCStr(targetList.size()) + L"�����ɹ�" + NumToCStr(count) + L"��������" + NumToCStr(skip) + L"������", L"��ʾ��");
}
void CExParrotDlg::SoundDequote(DWORD para) {
	processing = 1;
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	for(int i = 0; i < targetList.size(); i++) {
		int id = targetList[i];
		bar.setInfo(L"��������Ϊ" + GetTail(StrToCStr(no.content[id].comment)) + L"��������������", i);
		if(no.dequote(id)) {
			SNDupdateTerm(id);
		}
	}
	bar.hide();
	NPKsaveAlert = true;
	processing = 0;
}
void CExParrotDlg::SoundHide(DWORD para) {
	processing = 1;
	queue targetList = SNDgetChecked(enumSelectType(para));
	bar.show(targetList.size() - 1);
	audio emptyAu(1, 1);
	stream s;
	setCopyRight(CRO_MODIFIED);
	encodeTo(emptyAu, s);
	for(int i = 0; i<targetList.size(); i++) {
		int id = targetList[targetList.size() - 1 - i];
		bar.setInfo(L"��������" + GetTail(StrToCStr(no.content[id].comment)) + L"������", i);
		no.replace(id, s);
		SNDupdateTerm(id);
	}
	bar.hide();
	updateInfo();
	NPKsaveAlert = true;
	processing = 0;
}

void CExParrotDlg::OnMenuSoundInertEmpty() {
	StartThreadFunc(SoundInsertEmpty, 0);
}


void CExParrotDlg::OnMenuSoundInertSnd() {
	StartThreadFunc(SoundInsertSND, 0);
}


void CExParrotDlg::OnMenuSoundInertNPK() {
	StartThreadFunc(SoundInsertNPK, 0);
}


void CExParrotDlg::OnMenuSoundInertFolder() {
	StartThreadFunc(SoundInsertFolder, 0);
}


void CExParrotDlg::OnMenuSoundInertOther() {
	StartThreadFunc(SoundInsertOther, 0);
}


void CExParrotDlg::OnMenuSoundInertEmptyBlank() {
	StartThreadFunc(SoundInsertEmpty, 1);
}


void CExParrotDlg::OnMenuSoundInertSNDBlank() {
	StartThreadFunc(SoundInsertSND, 1);
}


void CExParrotDlg::OnMenuSoundInertNPKBlank() {
	StartThreadFunc(SoundInsertNPK, 1);
}


void CExParrotDlg::OnMenuSoundInertFolderBlank() {
	StartThreadFunc(SoundInsertFolder, 1);
}


void CExParrotDlg::OnMenuSoundInertOtherBlank() {
	StartThreadFunc(SoundInsertOther, 1);
}


void CExParrotDlg::OnMenuSoundReplaceSND() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundReplaceExtern, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceCopy() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundReplaceLocal, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceQuote() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundReplaceQuote, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundInsertSndPatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundReplaceExtern, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceCopyPatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundReplaceLocal, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundReplaceQuotePatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundReplaceQuote, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundRemove() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundRemove, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundRemovePatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundRemove, MULTI_SELECT);
}

void CExParrotDlg::OnMenuSoundExtract() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundExtract, SINGLE_SELECT);
}

void CExParrotDlg::OnMenuSoundExtractPatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundExtract, MULTI_SELECT);
}

void CExParrotDlg::OnMenuSoundSave() {
	CHECK_VALID(crtSNDid >= 0);
	CString defExt = _T("�����ļ�(*.*)|*.*");
	CString extFilter = _T("�����ļ�(*.*)|*.*||");
	CFileDialog dlg(false, defExt, Underlining(StrToCStr(no.content[crtSNDid].comment)), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, extFilter, this);
	if(dlg.DoModal() == IDOK) {
		no.extractFile(crtSNDid, CStrToStr(dlg.GetPathName()));
		MessageBox(_T("�����������"));
	}
}

void CExParrotDlg::OnMenuSoundSaveNPK() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundSaveAsNPK, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundSaveNPKPatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundSaveAsNPK, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundCopyResource() {
	CHECK_VALID(crtSNDid >= 0);
	stream sTemp;
	no.extract(crtSNDid, sTemp);
	no.insert(crtSNDid + 1, no.content[crtSNDid].comment, sTemp);
	SNDaddTerm(crtSNDid + 1, no.SNDgetVersionEx(crtSNDid + 1), GetTail(StrToCStr(no.content[crtSNDid].comment)));
	NPKsaveAlert = true;
}


void CExParrotDlg::OnMenuSoundCopyQuote() {
	CHECK_VALID(crtSNDid >= 0);
	no.insertQuote(crtSNDid + 1, no.content[crtSNDid].comment, crtSNDid);
	SNDaddTerm(crtSNDid + 1, no.SNDgetVersionEx(crtSNDid + 1), GetTail(StrToCStr(no.content[crtSNDid].comment)) + GetTail(StrToCStr(no.content[crtSNDid].comment)));
	NPKsaveAlert = true;
}

void CExParrotDlg::OnMenuSoundRename() {
	CHECK_VALID(crtSNDid >= 0);
	ModalRename dlg;
	dlg.oldName = StrToCStr(no.content[crtSNDid].comment);
	if(IDOK == dlg.DoModal()) {
		no.rename(crtSNDid, CStrToStr(dlg.newName));
		updateInfo();
		SNDupdateTerm(crtSNDid);
		for(int i = 1 + crtSNDid; i < no.getCount(); i++) {
			if(no.checkQuote(i) == crtSNDid)
				SNDupdateTerm(i);
		}
		fileSNDname = dlg.newName;
		NPKsaveAlert = true;
		updateInfo();
	}
}


void CExParrotDlg::OnMenuSoundDequote() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundDequote, SINGLE_SELECT);
}


void CExParrotDlg::OnMenuSoundDequotePatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundDequote, MULTI_SELECT);
}

void CExParrotDlg::OnMenuSoundHide() {
	CHECK_VALID(crtSNDid >= 0);
	StartThreadFunc(SoundHide, SINGLE_SELECT);
}

void CExParrotDlg::OnMenuSoundHidePatch() {
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundHide, MULTI_SELECT);
}


void CExParrotDlg::OnMenuSoundSelectAll() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(); i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, TRUE);
}


void CExParrotDlg::OnMenuSoundSelectReverse() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(); i++)
		GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, 1 - GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetCheck(i));
}


void CExParrotDlg::OnMenuSoundSelectHighline() {
	for(int i = 0; i<GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemCount(); i++)
		if(GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			GET_CTRL(CGoodListCtrl, IDC_LIST_SND)->SetCheck(i, TRUE);

}


void CExParrotDlg::OnMenuSoundMoveUp() {
	int row = crtSNDid;
	CHECK_VALID(row >= 1);
	NPKentry ne = no.content[row];
	no.content[row] = no.content[row - 1];
	no.content[row - 1] = ne;
	SNDupdateTerm(row);
	SNDupdateTerm(row - 1);
	SNDsetHighLine(row - 1);
	updateInfo();
	NPKsaveAlert = true;
}


void CExParrotDlg::OnMenuSoundMoveDown() {
	int row = crtSNDid;
	CHECK_VALID(row >= 0);
	CHECK_VALID(row<no.getCount() - 1);
	NPKentry ne = no.content[row];
	no.content[row] = no.content[row + 1];
	no.content[row + 1] = ne;
	SNDupdateTerm(row);
	SNDupdateTerm(row + 1);
	SNDsetHighLine(row + 1);
	NPKsaveAlert = true;
	updateInfo();
}

void CExParrotDlg::OnClose() {
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(NPKsaveAlert) {
		ModalSaveWarning ms;
		ms.alertType = SNDsaveAlert ? ModalSaveWarning::MODIFIED_SND_NPK : ModalSaveWarning::MODIFIED_NPK;
		ms.DoModal();
		switch(ms.returnType) {
		case ModalSaveWarning::RETURN_CANCEL:
			return;
		case ModalSaveWarning::RETURN_NO_SAVE:
			SNDsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			break;
		case ModalSaveWarning::RETURN_SAVE:
			no.saveFile(CStrToStr(fileNPKname));
			SNDsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		case ModalSaveWarning::RETURN_ALL_SAVE:
			stream s;
			setCopyRight(CRO_MODIFIED);
			encodeTo(s);
			no.replace(crtSNDid, s);
			no.saveFile(CStrToStr(fileNPKname));
			SNDsaveAlert = FALSE;
			NPKsaveAlert = FALSE;
			updateInfo();
			break;
		}
	} else {

	}
	CDialogEx::OnClose();
}


void CExParrotDlg::OnDropFiles(HDROP hDropInfo) {
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		if(NPKsaveAlert) {
			ModalSaveWarning ms;
			ms.alertType = SNDsaveAlert ? ModalSaveWarning::MODIFIED_SND_NPK : ModalSaveWarning::MODIFIED_NPK;
			ms.DoModal();
			switch(ms.returnType) {
			case ModalSaveWarning::RETURN_CANCEL:
				return;
			case ModalSaveWarning::RETURN_NO_SAVE:
				SNDsaveAlert = FALSE;
				NPKsaveAlert = FALSE;
				break;
			case ModalSaveWarning::RETURN_SAVE:
				no.saveFile(CStrToStr(fileNPKname));
				SNDsaveAlert = FALSE;
				NPKsaveAlert = FALSE;
				updateInfo();
				break;
			case ModalSaveWarning::RETURN_ALL_SAVE:
				stream s;
				au.make(s);
				no.replace(crtSNDid, s);
				no.saveFile(CStrToStr(fileNPKname));
				SNDsaveAlert = FALSE;
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
		SNDloadList();
		if(no.getCount() > 0) {
			SNDsetHighLine(0);
		}
	} else if(fmt == L".OGG" || fmt == L".MP3" || fmt == L".WAV") {
		int success = 0;
		for(int i = 0; i<fileCount; i++) {
			if(i != 0) {
				memset(szPath, 0, MAX_PATH * sizeof(WCHAR));
				nChars = ::DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
				fileName = CString(szPath, nChars);
			}
			fmt = fileName.Right(4).MakeUpper();
			if(fmt == L".OGG" || fmt == L".MP3" || fmt == L".WAV") {
				stream sTemp;
				if(!sTemp.loadFile(CStrToStr(fileName)))
					continue;
				CString path = Slashing(GetTail(fileName));
				no.push(CStrToStr(path), sTemp);
				success++;
				SNDaddTerm(-1, checkAudioFormat(sTemp), GetTail(path));
				sTemp.release();
			}
			updateInfo();
		}
		MessageBox(L"�������" + NumToCStr(success) + L"����Ч��������", L"��ʾ��");
		NPKsaveAlert = TRUE;
	}
	CDialogEx::OnDropFiles(hDropInfo);
}


void CExParrotDlg::OnBnClickedToolButton14() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if(au.length == 0) {
		MessageBox(L"��ǰû����Ƶ�����޷���������", L"��ʾ��");
		return;
	}
	if(rightBound - leftBound <= 0) {
		MessageBox(L"��ѡ��һ����Ƶ����", L"��ʾ��");
		return;
	}
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length - 1);
	if(true) {
		TinyAdjustSpeed dlg;
		dlg.type = TinyAdjustSpeed::ADJUST_SPEED;
		long len = au2.length;
		if(dlg.DoModal() == IDOK) {
			au2.adjustSpeed(dlg.rate);
			rightBound = leftBound + au2.length;
		} else {
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}


void CExParrotDlg::OnBnClickedToolButton15() {
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if(au.length == 0) {
		MessageBox(L"��ǰû����Ƶ�����޷���������", L"��ʾ��");
		return;
	}
	if(rightBound - leftBound <= 0) {
		MessageBox(L"��ѡ��һ����Ƶ����", L"��ʾ��");
		return;
	}
	audio au1, au2, au3;
	au.clip(au1, 0, leftBound);
	au.clip(au2, leftBound, rightBound);
	au.clip(au3, rightBound, au.length - 1);
	if(true) {
		TinyAdjustSpeed dlg;
		dlg.type = TinyAdjustSpeed::ADJUST_PITCH;
		long len = au2.length;
		if(dlg.DoModal() == IDOK) {
			au2.adjustPitch(dlg.rate);
			rightBound = leftBound + au2.length;
		} else {
			return;
		}
	}
	au.destory();
	au = au1;
	au.cat(au2);
	au.cat(au3);
	updateModified();
	updateInfo();
	draw();
}


void CExParrotDlg::OnToolsPiano() {
	// TODO:  �ڴ���������������
	ToolPiano dlg;
	dlg.DoModal();
}

void CExParrotDlg::OnToolsAudioMark() {
	// TODO:  �ڴ���������������
	ToolAudioMark dlg;
	dlg.DoModal();
}


void CExParrotDlg::OnMenuSoundTransformToWAV() {
	// TODO:  �ڴ���������������
	StartThreadFunc(SoundTransToWAV, 0);
}


void CExParrotDlg::OnMenuSoundTransformToOGG() {
	// TODO:  �ڴ���������������
	StartThreadFunc(SoundTransToOGG, 0);
}


void CExParrotDlg::OnMenuSoundTransformToWAVPatch() {
	// TODO:  �ڴ���������������
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundTransToWAV, 1);
}


void CExParrotDlg::OnMenuSoundTransformToOGGPatch() {
	// TODO:  �ڴ���������������
	if(!SNDgetChecked(MULTI_SELECT).size()) {
		MessageBox(L"û�й�ѡ����Ч��������");
		return;
	}
	StartThreadFunc(SoundTransToOGG, 1);
}

