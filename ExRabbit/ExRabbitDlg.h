
// ExRabbitDlg.h : ͷ�ļ�
//
#include "stdafx.h"
#include "../KoishiEx/koishiex.h"
#include "../KoishiEx/KoishiNeoplePack.h"

#include "DialogNew.h"
#include "DialogAbout.h"
#include "TinyBar.h"
#include "ToolAvatar.h"
#include "ToolForceEx.h"
#include "AdjustColorDlg.h"

#include "ModalInsertPicture.h"
#include "ModalInsertPicturePatch.h"
#include "ModalAdjustCanvas.h"
#include "ModalPictureStretch.h"
#include "ModalPictureParameter.h"
#include "ModalClearPicture.h"
#include "ModalLoseBlackPicture.h"
#include "ModalAdjustColor.h"
#include "ModalAddMark.h"
#include "ModalGradient.h"
#include "ModalInsertTexture.h"
#include "ModalTransform.h"
#include "ModalRename.h"
#include "ModalPreference.h"
#include "ModalAdvancedMix.h"
#include "ToolPatch.h"
#include "ToolNPKsource.h"

#pragma once

#define VERSION_STR "������Ex��è��.5.2"

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
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	ProfileBlack profile;
public:
	//��������
	IMGobject io;			//���༭IMG
	NPKobject no;			//���༭NPK
	colorList cl;			//��ɫ��
	NPKobject noClip;		//������NPK
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
	int width;			//���
	int height;			//�߶�
	int barWidth;		//״̬���ܿ�
	int barHeight;		//״̬���߶�(30)
	int barPart1;		//״̬������1���
	int barPart2;		//״̬������2���
	//������
	BOOL NPKsaveAlert;			//������NPK
	BOOL IMGsaveAlert;			//������IMG
	int crtIMGid;				//IMG�б�ǰ����
	int fndIMGid;				//IMG�б�ǰѰ��λ��
	int crtPICid;				//֡�б�ǰ����
	int crtTEXid;				//�����б�ǰ����
	//���Ʋ���
	struct structDrawPara {
		BOOL texture;			//��������б����������ͼʱΪtrue
		point basePoint;		//��ʵ������ʾʱ��0,0�����ʾλ��
		int zoom;				//���ű��� (0-ԭ�ߴ磬����Ϊn+1��������Ϊn+1��֮һ��-8��+8)
		double zoomRate;		//���ű���
		double oldZoomRate;		//�����ű���
		BOOL showPalette;		//�Ƿ���ʾɫ��
		BOOL showAxis;			//�Ƿ���ʾ�������
		BOOL showCanvas;		//�Ƿ���ʾ������Χ
		BOOL showBound;			//�Ƿ���ʾIMG�����ܷ�Χ
		BOOL indexMode;			//����ģʽ
		BOOL entireTextureMode;	//��������ģʽ
		BOOL compareMode;		//IMG�Ƚ�ģʽ
		colorMethod mixMode;	//�����ʾģʽ
	}drawPara;
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
	struct structCanvasOperatePara{
		int currentCursor;						//��ǰ���
		BOOL canvasOperating;					//��������ʱ
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
		BOOL oldMatrixEnable;					//�����ˢ�����ʱ���Ϊtrue���л�����/֡��ʱ���Ϊfalse
	}canvasOperatePara;
	struct structColorOperatePara{
		int current;							//��ǰ��ɫID
		BOOL isChosen[256];						//��ǰ����ѡɫ���
		int tolerance;							//����ѡɫ�ݲ�
		int layout;								//��ɫ����
		//���֣�0 - ����ɫ��<48ʱ��ÿ�����25���أ��ֳ�4�У�ÿ��12��
		//���֣�1 - ����ɫ��<75ʱ��ÿ�����20���أ��ֳ�5�У�ÿ��15��
		//���֣�2 - ����ɫ��<120ʱ��ÿ�����15���أ��ֳ�6�У�ÿ��20��
		//���֣�3 - ����ɫ��<200ʱ��ÿ�����12���أ��ֳ�8�У�ÿ��25��
		//���֣�4 - ����ɫ��>=200ʱ��ÿ�����10���أ��ֳ�10�У�ʵ��ֻ����9�У���ÿ��30��
		colorList v2Color;						//V2ʱ�õĵ�ɫ��
	}colorOperatePara;
	void OnMouseEventCanvas(enumCanvasMouseOperation mouseOperation, point mousePt);
	void OnMouseEventColor(enumCanvasMouseOperation mouseOperation, int selectColorID);
	void setDefaultColor();						//����Ĭ����ɫ��
	void updateColorTable();					//������ɫ��
	BOOL getIDofCurrentPos(int &cid);			//�������ɫ��ʱ����ȡ��ǰ����ɫID
public:
	//���¿ؼ�
	void adjustWindow(int w, int h);
	void switchIMGver(IMGversion ver);
public:
	//IMG�б���
	void IMGloadList();				//��ȡIMG�б�
	void IMGupdateList();			//��������IMG��
	void IMGupdateTerm(int pos);	//����ĳһ��IMG��
	void IMGaddTerm(int pos, IMGversion iv, CString comment);
	void IMGdeleteTerm(int pos);
	void IMGmodifyTerm(int pos, IMGversion iv, CString comment);
	void IMGmodifyIcon(int pos, IMGversion iv);
	void IMGsetHighLine(int pos);	//ǿ�Ƹ��ĸ����У��Լ���ǰѡ���־��
	queue IMGgetChecked(enumSelectType selectType);
	UINT IMGiconID(IMGversion iv);
	//֡�б���
	void PICloadList();				//��ȡ֡�б�
	void PICupdateList();			//�������е�֡��Ϣ
	void PICupdateTerm(int pos);	//����ĳһ��֡��Ϣ
	void PICrenumber();				//����Ϊ֡���
	void PICaddTerm(int pos, PICinfo pi);
	void PICdeleteTerm(int pos);
	void PICmodifyTerm(int pos, PICinfo pi);
	void PICmodifyBasePoint(int pos);//����ĳһ֡�Ļ�׼������Ϣ
	void PICsetHighLine(int pos);
	queue PICgetChecked(enumSelectType selectType);
	UINT PICiconID(IMGversion iv, PICinfo pi);

	//void updateTEXlist();
	void TEXloadList();
	void TEXaddTerm(int pos, TEXinfo ti);
	void TEXmodifyTerm(int pos, TEXinfo ti);
	void TEXsetHighLine(int pos);
	queue TEXgetChecked(enumSelectType selectType);
	UINT TEXiconID(TEXinfo pi);
	//��������
	void updateInfo();
	void updateCursorInfo();
	void updateModified();
	BOOL getMouseTrueAxis(point &pt);		//�������ڻ����ڻ�����ʵ������
	BOOL getMouseAxis(point &pt);			//��������ڻ���������
	CPoint getWinMouseAxis();				//������Ĵ���������
public:
	//�����̺߳���
	DeclareThreadFunc(CExRabbitDlg, Draw, BOOL);				//�����߳�
	DeclareThreadFunc(CExRabbitDlg, DrawColor, PVOID);		//����ɫ����߳�
	DeclareThreadFunc(CExRabbitDlg, Play, PVOID);
	DeclareThreadFunc(CExRabbitDlg, Lazy, PVOID);
	void draw(BOOL isTex = false);
public:
	//��Ҫ�Ŀؼ����Ի����
	CDialogNew dNewFile;
	TinyBar bar;
	CBitmap m_logoPic;
	CBitmap m_buttonPic[25];
	CBitmap m_buttonPicX[25];
	CImageList i_lIMG,i_lPIC,i_lTEX;
	CToolTipCtrl m_ttc;
public:
	ToolAvatar toolAvatar;
	CToolForceEx toolForceEx;
public:
	//��ť�¼�
	virtual void OnOK();
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButtonMenu2();
	afx_msg void OnBnClickedButtonMenu3();
	afx_msg void OnBnClickedButtonPalette();
	afx_msg void OnBnClickedButtonImgsearch();
	afx_msg void OnStnClickedLogo();
	afx_msg void OnClose();
	//�б��Ҽ��˵�
	afx_msg void OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListTex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboPro();
	//�б�����¼�
	afx_msg void OnLvnKeydownListImg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListTex(NMHDR *pNMHDR, LRESULT *pResult);
	//�϶��ļ��¼�
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//�ƶ������¼�
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//���ơ����ͼ����ɫ������
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//���˵���
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
	//��������ť
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void updateToolButtonStatus();
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
	afx_msg void OnBnClickedToolButton14();
	afx_msg void OnBnClickedToolButton15();
	//��ɫ����Ų˵�
	DeclareThreadFunc(CExRabbitDlg, PickColorFromFrame, PVOID);
	DeclareThreadFunc(CExRabbitDlg, PickColorFromImage, PVOID);
	afx_msg void OnMenuColorTableChooseAll();
	afx_msg void OnMenuColorTableChooseNone();
	afx_msg void OnMenuColorTableInverseChoose();
	afx_msg void OnMenuColorTableChooseFamiliar();
	afx_msg void OnMenuColorTableDeleteOne();
	afx_msg void OnMenuColorTableDeleteAll();
	afx_msg void OnMenuColorTableImport();
	afx_msg void OnMenuColorTableExport();
	afx_msg void OnMenuColorPaletteNew();
	afx_msg void OnMenuColorPaletteCopy();
	afx_msg void OnMenuColorPaletteImport();
	afx_msg void OnMenuColorPaletteDelete();
	afx_msg void OnMenuColorTableClassical();
	afx_msg void OnMenuColorTable16();
	afx_msg void OnMenuColorTable256();
	afx_msg void OnMenuColorTableExtractCurrent();
	afx_msg void OnMenuColorTableExtractAllFrame();
	//֡�б��Ҽ��˵�
	DeclareThreadFunc(CExRabbitDlg, PictureInsert, ModalInsertPicture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureInsertPatch, ModalInsertPicturePatch::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureAxisModify, ModalPictureParameter::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureCanvas, ModalAdjustCanvas::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureStretch, ModalPictureStretch::__output);
	DeclareThreadFunc(CExRabbitDlg, PictureClear, ModalClearPicture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureLoseBlack, ModalLoseBlackPicture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureGradient, ModalGradient::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureColor, ModalAdjustColor::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureMark, ModalAddMark::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, PictureGetPNG, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, PictureGetGIF, PVOID);
	afx_msg void OnMenuPictureChooseAll();
	afx_msg void OnMenuPictureChooseInverse();
	afx_msg void OnMenuPictureChooseHighline();
	afx_msg void OnMenuPictureInsert();
	afx_msg void OnMenuPictureInsert2();
	afx_msg void OnMenuPictureInsertPatch();
	afx_msg void OnMenuPictureInsertPatch2();
	afx_msg void OnMenuPictureDelete();
	afx_msg void OnMenuPictureDeletePatch();
	afx_msg void OnMenuPictureAxisModify();
	afx_msg void OnMenuPictureCanvas();
	afx_msg void OnMenuPictureStretch();
	afx_msg void OnMenuPictureClear();
	afx_msg void OnMenuPictureLoseblack();
	afx_msg void OnMenuPictureGradient();
	afx_msg void OnMenuPictureColor();
	afx_msg void OnMenuPictureMark();
	afx_msg void OnMenuPictureGetPng();
	afx_msg void OnMenuPictureGetPngPatch();
	afx_msg void OnMenuPictureGetGIF();
	//�����б��Ҽ��˵�
	DeclareThreadFunc(CExRabbitDlg, TextureInsert, ModalInsertTexture::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, TextureGetPNG, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, TextureGetOrigin, enumSelectType);
	afx_msg void OnMenuTextureChooseAll();
	afx_msg void OnMenuTextureChooseInverse();
	afx_msg void OnMenuTextureChooseHighline();
	afx_msg void OnMenuTextureInsert();
	afx_msg void OnMenuTextureDelete();
	afx_msg void OnMenuTextureDeletePatch();
	afx_msg void OnMenuTextureGetPng();
	afx_msg void OnMenuTextureGetPngPatch();
	afx_msg void OnMenuTextureGetOrigin();
	afx_msg void OnMenuTextureGetOriginPatch();
	afx_msg void OnMenuTextureInsert2();
	//���⹤�߲˵�
	afx_msg void OnToolAvatar();
	afx_msg void OnToolNpkDict();
	afx_msg void OnToolDownload();
	afx_msg void OnToolForceExtract();
	afx_msg void OnToolOpenOutputFolder();
	afx_msg void OnToolsNpkLock();
	afx_msg void OnToolsPatchOperate();
	afx_msg void OnToolsAvatarMark();
	//�������Ҽ��˵�
	afx_msg void OnDrawColorTable();
	afx_msg void OnDrawCanvas();
	afx_msg void OnDrawAxis();
	afx_msg void OnDrawBound();
	afx_msg void OnDrawSetCompare1();
	afx_msg void OnDrawSetCompare2();
	afx_msg void OnDrawCompareEnabled();
	afx_msg void OnDrawCompareDisabled();
	//IMG�б��Ҽ��˵�
	DeclareThreadFunc(CExRabbitDlg, ImageInsertEmpty, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertIMG, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertNPK, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertFolder, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageInsertOther, DWORD);
	DeclareThreadFunc(CExRabbitDlg, ImageReplaceExtern, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageReplaceLocal, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageReplaceQuote, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageRemove, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageExtract, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageMakeNPKandSavePatch, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageDequote, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageHide, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageTransToV2, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageV6TransToV4, enumSelectType);
	DeclareThreadFunc(CExRabbitDlg, ImageTransform, ModalTransform::OUTPUT);
	DeclareThreadFunc(CExRabbitDlg, ImageAutoSort, PVOID);
	DeclareThreadFunc(CExRabbitDlg, ImageMix, ModalAdvancedMix::OUTPUT);
	afx_msg void OnMenuImageInertEmpty();
	afx_msg void OnMenuImageInertIMG();
	afx_msg void OnMenuImageInertNPK();
	afx_msg void OnMenuImageInertFolder();
	afx_msg void OnMenuImageInertOther();
	afx_msg void OnMenuImageReplaceIMG();
	afx_msg void OnMenuImageReplaceCopy();
	afx_msg void OnMenuImageReplaceQuote();
	afx_msg void OnMenuImageReplaceImgPatch();
	afx_msg void OnMenuImageReplaceCopyPatch();
	afx_msg void OnMenuImageReplaceQuotePatch();
	afx_msg void OnMenuImageRemove();
	afx_msg void OnMenuImageRemovePatch();
	afx_msg void OnMenuImageExtract();
	afx_msg void OnMenuImageExtractPatch();
	afx_msg void OnMenuImageSave();
	afx_msg void OnMenuImageSaveNPK();
	afx_msg void OnMenuImageSaveNPKPatch();
	afx_msg void OnMenuImageCopyResource();
	afx_msg void OnMenuImageCopyQuote();
	afx_msg void OnMenuImageRename();
	afx_msg void OnMenuImageDequote();
	afx_msg void OnMenuImageDequotePatch();
	afx_msg void OnMenuImageTransformTo2();
	afx_msg void OnMenuImageTransformTo4();
	afx_msg void OnMenuImageTransformTo2Patch();
	afx_msg void OnMenuImageTransformTo4Patch();
	afx_msg void OnMenuImageTransformAdvanced();
	afx_msg void OnMenuImageHide();
	afx_msg void OnMenuImageHideContent();
	afx_msg void OnMenuImageHidePatch();
	afx_msg void OnMenuImageHideContentPatch();
	afx_msg void OnMenuImageClipboardCopy();
	afx_msg void OnMenuImageClipboardInsert();
	afx_msg void OnMenuImageClipboardReplace();
	afx_msg void OnMenuImageSetCompare();
	afx_msg void OnMenuImageSelectAll();
	afx_msg void OnMenuImageSelectReverse();
	afx_msg void OnMenuImageSelectHighline();
	afx_msg void OnMenuImageMoveUp();
	afx_msg void OnMenuImageMoveDown();
	afx_msg void OnMenuImageMix();
	afx_msg void OnMenuImageMixAdvanced();
	afx_msg void OnMenuImageAutoSort();
	afx_msg void OnMenuImageInertEmptyBlank();
	afx_msg void OnMenuImageInertIMGBlank();
	afx_msg void OnMenuImageInertNPKBlank();
	afx_msg void OnMenuImageInertFolderBlank();
	afx_msg void OnMenuImageInertOtherBlank();
	afx_msg void OnToolsStat();
	afx_msg void OnToolsTeenSwitch();
};
