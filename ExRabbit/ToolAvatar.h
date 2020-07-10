#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"
#include "TinyBar.h"
#include "ToolAvatarModelConfig.h"
#include "ToolAvatarStageConfig.h"
// ToolAvatar 对话框
using namespace Koishi;
using namespace KoishiAvatar;
//防止播放时换装的崩溃
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
	ToolAvatar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatar();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	TinyBar bar;
public:
	//基本内容
	Profile profile;
	AvatarFactory factory;
	AvatarMap map;
	AvatarCharacter character;
	AvatarPart currentPart;
	int currentWeaponIndex;
	long maxFrame;
	long currentFrame;
	point basePoint;
	bool loading;
	bool TNmode;		//TN模式
	bool playing;		//在播放动作
	struct _ani{
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
	};
	void setAnimation(const long &aniID);
	ToolAvatarStageConfig stage;
public:
	//展示图相关信息
	struct{
		int sizeMode;		//0.小 1.中 2.大 3.巨大
		long width;			//宽度
		long height;		//高度
		long countPerRow;	//每行个数
		long row;			//行数
		long countPerPage;	//每页个数（每行个数*行数-2）
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
	void drawModel(int indexInPage);		//绘制展示图, -1表示全部
	void drawAvatar();
	static unsigned p(void*para);
	void playAvatar();
	void buildModel(const int &index);
	void buildModelPatch();
	void buildIconPatch();
	void buildPatch();
	//图标模式
	//红叉表示无此图标资源
	//红色叹号表示映射表中没有实际装扮与其对应
	//蓝色叹号表示映射表中其他NPK有装扮与其对应，多见于武器装扮
	void buildMixedIMG(IMGobject &io);
public:
	void *context;
	CListBox *lbContent;
	CComboBox *cbWeaponType;
	CEdit *eAvatarInfo, *eAvatarSuit;
	CButton *bTool[11];
	CButton *bPFrame, *bNFrame;
	CEdit *ePageInfo;
	CComboBox *cbAction;
	CBitmap charImg[ACHARACTER_MAXCOUNT+1];
	CStatic *charButton;
	CStatic *partButton[10];
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	BOOL getMouseClicked(int &type, long &checkSelected); //type:0 点击职业按钮 1:点击部件按钮（0-9）2：点击了缩略图按钮
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
};
