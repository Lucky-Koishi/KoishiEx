
// ExRabbitDlg.h : ͷ�ļ�
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiNeoplePack.h"

#include "DialogNew.h"
#include "DialogAbout.h"
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
#include "ModalPreference.h"
#include "modalcopyinsert.h"
#include "ModalCopyReplace.h"
#include "ToolPatch.h"

#pragma once

#define DISC(x)

#define VERSION_STR "������Ex��è��.4.5"

// CExRabbitDlg �Ի���
using namespace Koishi;
using namespace KoishiNeoplePack;
using KoishiImageTool::DDS::DDSobject;
class CExRabbitDlg : public CDialogEx
{
// ����
public:
	CExRabbitDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXRABBIT_DIALOG };

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Profile profile;
public:
	//��������
	IMGobject io;			//���༭IMG
	NPKobject no;			//���༭NPK
	colorList cl;			//��ɫ��

	NPKobject noClip;		//������IMG
	IMGobject ioComp;		//�Ա���IMG
	CString fileNPKname;	//NPK���֣�ȫ�ƣ�
	CString fileIMGname;	//IMG���֣�ȫ�ƣ�
	//�ź���
	volatile int drawing;		//������
	volatile int drawingColor;	//������
	volatile int processing;	//��ȡ��ת�������䡤����
	volatile int playing;		//������
	volatile int lazyTime;		//��Ӧ��ʱ�������
	volatile int sizing;		//���ڵ�����С
	//������
	int width, height, barWidth;
	int barHeight, barPart1, barPart2;		//״̬���ߣ�״̬������1��ȣ�����2���
	
	//������
	//bool NPKsaveAlert;
	bool saveAlert;				//������IMG
	int crtIMGid;				//IMG�б�ǰ����
	int fndIMGid;				//IMG�б�ǰѰ��λ��
	int crtPICid;				//֡�б�ǰ����
	int crtTEXid;				//�����б�ǰ����
	//������
	enum enumCanvasOperation{
		CANVAS_SHOW,		//������ʾ
		CANVAS_DRAG,		//�϶�
		CANVAS_ZOOM,		//����
		CANVAS_MOVE,		//�ƶ�����
		CANVAS_CUT,			//�������
		CANVAS_BRUSH,		//��ˢ
		CANVAS_DRAWLINE,	//��ֱ��
		CANVAS_DRAWRECT,	//������
		CANVAS_ERASE,		//����
		CANVAS_PICK,		//ȡɫ
		CANVAS_MARK			//���ϱ�־
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
		int currentCursor;						//��ǰ���
		bool canvasOperating;					//��������ʱ
		enumCanvasOperation canvasOperation;    //��������
		enumCanvasPara canvasPara;				//��������
		int brushShape;							//��ˢ��״
		int brushSize;							//��ˢ��С
		point oldBasePoint;						//�϶�ʱ��¼�ɻ�׼������
		point startPoint;						//��¼��갴סʱ�����꣨��һ����������꣩
		point movePoint;						//��¼����ƶ�ʱ������
		point endPoint;							//��¼����ƶ��������
		std::vector<point> drawnPoint;			//��¼��ˢ/������ס�����Ĺ켣
		image oldMatrix;						//Ӧ�û�ˢʱ����һ���ɵľ������Գ���
		bool oldMatrixEnable;					//�����ˢ�����ʱ���Ϊtrue���л�����/֡��ʱ���Ϊfalse
	}canvasOperatePara;
	//��ɫ����
	struct structColorOperatePara{
		int current;							//��ǰ��ɫID
		bool isChosen[256];						//��ǰ����ѡɫ���
		int tolerance;							//����ѡɫ�ݲ�
		int layout;								//��ɫ����
		//���֣�0 - ����ɫ��<48ʱ��ÿ�����25���أ��ֳ�4�У�ÿ��12��
		//���֣�1 - ����ɫ��<75ʱ��ÿ�����20���أ��ֳ�5�У�ÿ��15��
		//���֣�2 - ����ɫ��<120ʱ��ÿ�����15���أ��ֳ�6�У�ÿ��20��
		//���֣�3 - ����ɫ��<200ʱ��ÿ�����12���أ��ֳ�8�У�ÿ��25��
		//���֣�4 - ����ɫ��>=200ʱ��ÿ�����10���أ��ֳ�10�У�ʵ��ֻ����9�У���ÿ��30��
		colorList v2Color;						//V2ʱ�õĵ�ɫ��
	}colorOperatePara;
	void setDefaultColor();						//����Ĭ����ɫ��
	void updateColorTable();					//������ɫ��
	BOOL getIDofCurrentPos(int &cid);			//�������ɫ��ʱ����ȡ��ǰ����ɫID
	static UINT threadDrawColor(PVOID para);	//����ɫ����߳�
public:
	//��������
	int getIconIMG(IMGversion iv);
	int getIconPIC(Koishi::colorFormat cf);
	int getIconPIC(const PICinfo &pi);
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
	BOOL getMouseTrueAxis(point &pt);		//�������ڻ����ڻ�����ʵ������
	BOOL getMouseAxis(point &pt);			//��������ڻ���������
	CPoint getWinMouseAxis();				//������Ĵ���������
public:
	CDialogNew dNewFile;
	TinyBar bar;

	CBitmap m_logoPic;
	CBitmap m_buttonPic[25];
	CBitmap m_buttonPicX[25];
	CImageList i_lIMG,i_lPIC,i_lTEX;
	void draw(bool isTex = false);
public:
	//�¼�
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
	ToolAvatar toolAvatar;
	CToolDict toolDict;
	CToolSPK toolSPK;
	CToolForceEx toolForceEx;

	//CButton m_btnPalette;
	//�˵�
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
		bool texture;			//��������б����������ͼʱΪtrue
		point basePoint;		//��ʵ������ʾʱ��0,0�����ʾλ��
		int zoom;				//���ű��� (0-ԭ�ߴ磬����Ϊn+1��������Ϊn+1��֮һ��-8��+8)
		double zoomRate;		//���ű���
		double oldZoomRate;		//�����ű���
		bool showPalette;		//�Ƿ���ʾɫ��
		bool showAxis;			
		bool showCanvas;
		bool showBound;
		bool indexMode;			//����ģʽ
		bool entireTextureMode;	//��������ģʽ
		bool compareMode;		//IMG�Ƚ�ģʽ
		colorMethod mixMode;//�����ʾģʽ
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
	void changeToolButtonStatus();
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
	static UINT ThreadPictureGetGIF(void*context);
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
	afx_msg void OnToolsNpkLock();
	afx_msg void OnMenuPictureGetGIF();
	afx_msg void OnMenuColorTableClassical();
	afx_msg void OnMenuColorTable16();
	afx_msg void OnMenuColorTable256();
	afx_msg void OnMenuColorTableExtractCurrent();
	afx_msg void OnMenuColorTableExtractAllFrame();
	static UINT pickColorFrame(void*context);
	static UINT pickColorImage(void*context);
	
	CToolTipCtrl m_ttc;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuImageInsertOther();
	afx_msg void OnMenuImageInsertCopy();
	afx_msg void OnMenuImageDelink();
	afx_msg void OnMenuImagePutIntoClip();
	afx_msg void OnMenuImageInsertClip();
	afx_msg void OnMenuImageReplaceClip();
	afx_msg void OnMenuImageReplaceCopy();
	afx_msg void OnToolsPatchOperate();
	afx_msg void OnToolsAvatarMark();
	afx_msg void OnMenuImageMakeNPKandSave();
	static UINT ThreadImageMakeNPKandSavePatch(void*context);
	CString paraMakeNPKandSavePatch;
	afx_msg void OnMenuImageMakeNPKandSavePatch();
	afx_msg void OnClose();
};
