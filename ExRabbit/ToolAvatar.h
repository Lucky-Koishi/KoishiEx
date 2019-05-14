#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "Profile.h"
#include "DictAvatar.h"
#include "ModalAvatarMap1.h"
#include "ModalAvatarMap2.h"
#include "ModalAvatarUpdate.h"
// CToolAvatar 对话框

using namespace Koishi;
using namespace KoishiAvatar;
class CToolAvatar : public CDialogEx
{
	DECLARE_DYNAMIC(CToolAvatar)

public:
	CToolAvatar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CToolAvatar();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR };

protected:
	DECLARE_MESSAGE_MAP()
public:
	CComboBox *cbPart		[APART_MAXCOUNT];		//10个ID组合框的指针
	CComboBox *cbPalette	[APART_MAXCOUNT];		//10个调色板组合框的指针
	void *context;
	bool loading;					//读取NPK
	bool moving;					//播放动画
	long animation[16];				//动画帧
	long animationLength;
	void setAnimation(int f1 = 0, int f2 = -1, int f3 = -1, int f4 = -1, int f5 = -1, int f6 = -1, int f7 = -1, int f8 = -1, int f9 = -1, int f10 = -1, int f11 = -1, int f12 = -1, int f13 = -1, int f14 = -1, int f15 = -1, int f16 = -1);

	matrix canvas;
	
	void draw();
	volatile bool drawing;			//正在绘制
	avatarFactory factory;
	DictAvatar dict;
	point basePoint;
	int frame, maxFrame;

	int displayStyle;									//0.展示图模式 1.图标模式(根据装扮ID顺序) 2.图标模式(根据图标ID顺序)
	void changeDisplayStyle(int newDisplayStyle);
	void selectionTransform(
		avatarPart ap, int oldDisplayStyle, int newDisplayStyle, 
		long oldSelected, long oldSelectedPalette,
		long &newSelected, long &newSelectedPalette);		//计算切换模式后新的
	Profile profile;									//preference设定
	avatarPart displayPart;								//当前选择部件
	long page;											//当前页
	long selected;										//当前选择部件的选择项
	//展示图相关数据
	int thumbnailSize;									//0.小 1.中 2.大 3.巨大 4.图标
	long thumbnailWidth;								//每个展示图的宽度
	long thumbnailHeight;								//每个展示图的高度
	long thumbnailCountPerRow;							//每行包含展示图的个数（总列数）
	long thumbnailCountRow;								//总行数
	long thumbnailCountPerPage;							//每页总数
	void changeThumbnailSize(int tSize);				//更改展示图大小
	void loadThumbnail(avatarCareer ac, avatarPart ap);	//导入展示图
	void drawThumbnail(int page);						//绘制展示图
	//图标相关数据
	std::vector<long> iconCount;						//图标数
	bool loadImage(str fileNameWithoutExp, matrix &mat);//导入图像，无视扩展名
	void loadIconCount(avatarCareer ac);				//导入图标数
	void drawIconByAvatar(int page);					//根据装扮编号顺序绘制图标
	void drawIconByIcon(int page);						//根据图标编号顺序绘制图标（按装扮顺序）

	static UINT loadNPKThread(PVOID para);				//导入NPK线程
	static UINT drawThread(PVOID para);					//绘制预览图
	static UINT animationThread(void*para);
	void makeThumbnailBySingle(int newSelected);
	void makeThumbnailByPart();
	void makeThumbnailByAll();//生成浏览图文件
	static UINT makeThumbnailThread(void*para);
	static UINT makeAllThumbnailThread(void*para);
	static UINT makeIconThread(void*para);

	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboCareer();
	afx_msg void OnCbnSelchangeComboPart1();
	afx_msg void OnCbnSelchangeComboPart2();
	afx_msg void OnCbnSelchangeComboPart3();
	afx_msg void OnCbnSelchangeComboPart4();
	afx_msg void OnCbnSelchangeComboPart5();
	afx_msg void OnCbnSelchangeComboPart6();
	afx_msg void OnCbnSelchangeComboPart7();
	afx_msg void OnCbnSelchangeComboPart8();
	afx_msg void OnCbnSelchangeComboPart9();
	afx_msg void OnCbnSelchangeComboPalette1();
	afx_msg void OnCbnSelchangeComboPalette2();
	afx_msg void OnCbnSelchangeComboPalette3();
	afx_msg void OnCbnSelchangeComboPalette4();
	afx_msg void OnCbnSelchangeComboPalette5();
	afx_msg void OnCbnSelchangeComboPalette6();
	afx_msg void OnCbnSelchangeComboPalette7();
	afx_msg void OnCbnSelchangeComboPalette8();
	afx_msg void OnCbnSelchangeComboPalette9();

	void OnComboPartChange(avatarPart ap);
	void OnComboPaletteChange(avatarPart ap);
	void OnButtonSelectThumbnail(avatarPart ap);
	void InvokeMappingDialog1(long getSelected);
	void InvokeMappingDialog2(long getSelected);

	afx_msg void OnBnClickedButtonResource();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboAction();
	afx_msg void OnBnClickedButtonPart1();
	afx_msg void OnBnClickedButtonPart2();
	afx_msg void OnBnClickedButtonPart3();
	afx_msg void OnBnClickedButtonPart4();
	afx_msg void OnBnClickedButtonPart5();
	afx_msg void OnBnClickedButtonPart6();
	afx_msg void OnBnClickedButtonPart7();
	afx_msg void OnBnClickedButtonPart8();
	afx_msg void OnBnClickedButtonPart9();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	BOOL getMouseClicked(int &checkSelected);
	CPoint getWinMouseAxis();
	afx_msg void OnMenuAvatarSetName();
	afx_msg void OnMenuAvatarSetIcon();
	afx_msg void OnMenuAvatarSizeSmall();
	afx_msg void OnMenuAvatarSizeMedium();
	afx_msg void OnMenuAvatarSizeLarge();
	afx_msg void OnMenuAvatarSizeHuge();
	afx_msg void OnMenuAvatarRefresh();
	afx_msg void OnMenuAvatarRefreshAll();
	afx_msg void OnBnClickedRadioDisplay1();
	afx_msg void OnBnClickedRadioDisplay2();
	afx_msg void OnBnClickedRadioDisplay3();
	afx_msg void OnMenuAvatarRefreshIcon();
	afx_msg void OnMenuAvatarSetavatar();
	afx_msg void OnMenuAvatarSetAvatar2();
	afx_msg void OnBnClickedButtonOneKey();

	afx_msg void OnMenuOneKeyLocalize();
	afx_msg void OnMenuOneKeyPatch();

	void makeOneKeyPatch();
	static UINT makeOneKeyPatchThread(void*para);
	afx_msg void OnMenuOneKeyNPK();
};