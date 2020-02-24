#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "Profile.h"
#include "DictAvatar.h"
#include "ModalAvatarMap1.h"
#include "ModalAvatarMap2.h"
#include "ModalAvatarUpdate.h"
// CToolAvatar �Ի���

using namespace Koishi;
using namespace KoishiAvatar;
class CToolAvatar : public CDialogEx
{
	DECLARE_DYNAMIC(CToolAvatar)

public:
	CToolAvatar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolAvatar();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR };

protected:
	DECLARE_MESSAGE_MAP()
public:
	CComboBox *cbPart		[APART_MAXCOUNT];		//10��ID��Ͽ��ָ��
	CComboBox *cbPalette	[APART_MAXCOUNT];		//10����ɫ����Ͽ��ָ��
	void *context;
	bool loading;					//��ȡNPK
	bool moving;					//���Ŷ���
	long animation[16];				//����֡
	long animationLength;
	void setAnimation(int f1 = 0, int f2 = -1, int f3 = -1, int f4 = -1, int f5 = -1, int f6 = -1, int f7 = -1, int f8 = -1, int f9 = -1, int f10 = -1, int f11 = -1, int f12 = -1, int f13 = -1, int f14 = -1, int f15 = -1, int f16 = -1);

	matrix canvas;
	
	void draw();
	volatile bool drawing;			//���ڻ���
	avatarFactory factory;
	DictAvatar dict;
	point basePoint;
	int frame, maxFrame;

	int displayStyle;									//0.չʾͼģʽ 1.ͼ��ģʽ(����װ��ID˳��) 2.ͼ��ģʽ(����ͼ��ID˳��)
	void changeDisplayStyle(int newDisplayStyle);
	void selectionTransform(
		avatarPart ap, int oldDisplayStyle, int newDisplayStyle, 
		long oldSelected, long oldSelectedPalette,
		long &newSelected, long &newSelectedPalette);		//�����л�ģʽ���µ�
	Profile profile;									//preference�趨
	avatarPart displayPart;								//��ǰѡ�񲿼�
	long page;											//��ǰҳ
	long selected;										//��ǰѡ�񲿼���ѡ����
	//չʾͼ�������
	int thumbnailSize;									//0.С 1.�� 2.�� 3.�޴� 4.ͼ��
	long thumbnailWidth;								//ÿ��չʾͼ�Ŀ��
	long thumbnailHeight;								//ÿ��չʾͼ�ĸ߶�
	long thumbnailCountPerRow;							//ÿ�а���չʾͼ�ĸ�������������
	long thumbnailCountRow;								//������
	long thumbnailCountPerPage;							//ÿҳ����
	void changeThumbnailSize(int tSize);				//����չʾͼ��С
	void loadThumbnail(avatarCareer ac, avatarPart ap);	//����չʾͼ
	void drawThumbnail(int page);						//����չʾͼ
	//ͼ���������
	std::vector<long> iconCount;						//ͼ����
	bool loadImage(str fileNameWithoutExp, matrix &mat);//����ͼ��������չ��
	void loadIconCount(avatarCareer ac);				//����ͼ����
	void drawIconByAvatar(int page);					//����װ����˳�����ͼ��
	void drawIconByIcon(int page);						//����ͼ����˳�����ͼ�꣨��װ��˳��

	static UINT loadNPKThread(PVOID para);				//����NPK�߳�
	static UINT drawThread(PVOID para);					//����Ԥ��ͼ
	static UINT animationThread(void*para);
	void makeThumbnailBySingle(int newSelected);
	void makeThumbnailByPart();
	void makeThumbnailByAll();//�������ͼ�ļ�
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
	afx_msg void OnCbnSelchangeComboMultcolor();
	afx_msg void OnMenuOneKeyHide();
	afx_msg void OnCbnSelchangeComboSuit();
};