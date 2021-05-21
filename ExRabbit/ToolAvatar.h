#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"
#include "TinyBar.h"
#include "ToolAvatarModelConfig.h"
#include "ToolAvatarStageConfig.h"

// ToolAvatar �Ի���
using namespace Koishi;
using namespace KoishiAvatar;
//��ֹ����ʱ��װ�ı���
#define PLAYING_PAUSE {\
	bool alreadyPlaying = playing;\
	playing = false;
#define PLAYING_CONTINUE \
	if(!alreadyPlaying){\
	factory.updateImage();\
	drawAvatar();\
	}\
	playing = alreadyPlaying;\
}

class ToolAvatar : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatar)

public:
	ToolAvatar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ToolAvatar();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	TinyBar bar;
public:
	//��������
	ProfileBlack profile;
	AvatarFactory factory;
	AvatarMap map;
	AvatarCharacter character;
	AvatarPart currentPart;
	int currentWeaponIndex;
	long maxFrame;
	long currentFrame;
	point basePoint;
	bool loading;
	bool TNmode;		//TNģʽ
	bool playing;		//�ڲ��Ŷ���
	/*struct _ani{
		long frameLength;
		long frame[255];
		_ani();
		_ani &operator>(long);
		_ani &operator>=(long);
		long &operator[](long);
		long operator~() const;
	}animation;
	enum{
		ANI_STATIC,
		ANI_NORMAL,
		ANI_PREPARE,
		ANI_WALK,
		ANI_DASH,
		ANI_ATTACK,
		ANI_ZATTACK,
		ANI_CAST,
		ANI_HIT,
		ANI_FALL,
		ANI_FULLPLAY,
		ANI_MAXCOUNT
	};*/
	void setAnimation(const long &aniID);
	ToolAvatarStageConfig stage;
	ToolAvatarAnimation animationList;
	ToolAvatarAnimation::animation animation;
public:
	//չʾͼ�����Ϣ
	struct{
		int sizeMode;		//0.С 1.�� 2.�� 3.�޴�
		long width;			//���
		long height;		//�߶�
		long countPerRow;	//ÿ�и���
		long row;			//����
		long countPerPage;	//ÿҳ������ÿ�и���*����-2��
	}modelInfo;
	int oldSizeMode;
	long maxPage;
	long currentPage;
public:
	bool isIconic;
	bool iconEnabled[1296];
	long currentIconSelect;
public:
	long lastSelected;
protected:
	CBitmap m_buttonPic[25];
	CBitmap m_buttonPicX[25];
	CBitmap m_partPic[10];
	CToolTipCtrl m_ttc;
public:
	void chooseCharacter(const AvatarCharacter &newCharacter);
	void loadResource();
	void initalModel(const int &newSizeMode);
	void updateList();
	void showAvatarInfo();
	void updateSuitInfo();
	void updatePageInfo();
	void drawModel(int indexInPage);		//����չʾͼ, -1��ʾȫ��
	void drawAvatar();
	static unsigned p(void*para);
	void playAvatar();
	void buildModel(const int &index);
	void buildModelPatch();
	void buildIconPatch();
	void buildPatch();
	//ͼ��ģʽ
	//����ʾ�޴�ͼ����Դ
	//��ɫ̾�ű�ʾӳ�����û��ʵ��װ�������Ӧ
	//��ɫ̾�ű�ʾӳ���������NPK��װ�������Ӧ�����������װ��
	void buildMixedIMG(IMGobject &io);
	void buildMixedIMG4(IMGobject &io);	//��Ȼ����V2�˵���GIF������V4
public:
	void *context;
	CListBox *lbContent;
	CComboBox *cbWeaponType;
	CEdit *eAvatarInfo, *eAvatarSuit;
	CButton *bTool[12];
	CButton *bPFrame, *bNFrame;
	CEdit *ePageInfo;
	CComboBox *cbAction;
	CBitmap charImg[ACHARACTER_MAXCOUNT+1];
	CStatic *charButton;
	CStatic *partButton[10];
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	BOOL getMouseClicked(int &type, long &checkSelected); //type:0 ���ְҵ��ť 1:���������ť��0-9��2�����������ͼ��ť
	void drawImage(const image &img, const point &leftTop);
	
	afx_msg void OnCbnSelchangeComboWeapon();
	afx_msg void OnLbnSelchangeListContent();
	afx_msg void OnBnClickedButtonPframe();
	afx_msg void OnBnClickedButtonNframe();
	afx_msg void OnBnClickedButtonTool1();
	afx_msg void OnBnClickedButtonTool2();
	afx_msg void OnBnClickedButtonTool3();
	afx_msg void OnBnClickedButtonTool4();
	afx_msg void OnBnClickedButtonTool5();
	afx_msg void OnBnClickedButtonTool6();
	afx_msg void OnBnClickedButtonTool7();
	afx_msg void OnBnClickedButtonTool8();
	afx_msg void OnBnClickedButtonTool9();
	afx_msg void OnBnClickedButtonTool10();
	afx_msg void OnBnClickedButtonTool11();
	afx_msg void OnMenuAvatarsize1();
	afx_msg void OnMenuAvatarsize2();
	afx_msg void OnMenuAvatarsize3();
	afx_msg void OnMenuAvatarsize4();
	afx_msg void OnMenuLocalizeOne();
	afx_msg void OnMenuLocalizeAll();
	afx_msg void OnMenuLocalizeSet();
	afx_msg void OnMenuAvatarFunToEX();
	afx_msg void OnMenuAvatarFunMakeNPK();
	afx_msg void OnMenuAvatarFunMakeAntiNPK();
	afx_msg void OnMenuAvatarFunMakeAllIn1NPK();
	afx_msg void OnCbnSelchangeComboAction();
	afx_msg void OnMenuLocalizeMapEdit();
	afx_msg void OnMenuSuitList();
	afx_msg void OnMenuSuitRegister();
	afx_msg void OnMenuSuitImport();
	afx_msg void OnMenuSuitExport();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuAvatarmodelRefresh();
	afx_msg void OnMenuAvatarmodelRegister();
	afx_msg void OnBnClickedButtonTool12();
	virtual void OnOK();
	afx_msg void OnMenuLocalizeMapCombine();
	afx_msg void OnMenuLocalizeMapResort();
	afx_msg void OnMenuLocalizeSetResource();
	afx_msg void OnMenuLocalizeOpenResource();
	afx_msg void OnMenuLocalizeDownloadResource();
	afx_msg void OnMenuSuitAnimation();
	afx_msg void OnBnClickedButtonAframe();
	afx_msg void OnBnClickedButtonTool13();
};
