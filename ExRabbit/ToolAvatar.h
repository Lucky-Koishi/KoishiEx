#pragma once


// CToolAvatar 对话框
#define AVATAR_MAX_NPK_COUNT				10			//时装NPK文件数的最大值
#define AVATAR_MAX_LAYER_COUNT				64			//时装图层（即IMG数）的最大值


class CToolAvatar : public CDialogEx
{
	DECLARE_DYNAMIC(CToolAvatar)

public:
	CToolAvatar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CToolAvatar();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cType;
	CComboBox m_cPart1,m_cPart2,m_cPart3,m_cPart4,m_cPart5;
	CComboBox m_cPart6,m_cPart7,m_cPart8,m_cPart9,m_cPart10;
	CComboBox m_cPalette1,m_cPalette2,m_cPalette3,m_cPalette4,m_cPalette5;
	CComboBox m_cPalette6,m_cPalette7,m_cPalette8,m_cPalette9,m_cPalette10;
	CComboBox *cbPart		[AVATAR_MAX_NPK_COUNT];		//10个时装ID组合框的指针
	CComboBox *cbPalette	[AVATAR_MAX_NPK_COUNT];	//10个时装调色板组合框的指针
	CEdit m_e1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();

	void draw();
	volatile bool drawing;			//正在绘制
	int frmID;					//当前帧
	point basePoint;			//基准点
	NPKobject	noList		[AVATAR_MAX_NPK_COUNT];		//NPK对象·选择角色后确认
	CString		ioSuffix	[AVATAR_MAX_NPK_COUNT];		//AvatarID的名字（组合框里显示的名字）·选择角色后确认
	
	IMGobject	ioList		[AVATAR_MAX_LAYER_COUNT];	//IMG对象·选择部件后更新
	int			pltID		[AVATAR_MAX_LAYER_COUNT];	//调色板·选择调色板后更新
	matrix		layer		[AVATAR_MAX_LAYER_COUNT];	//图层矩阵·选择部件和选择帧后更新
	str			ioName		[AVATAR_MAX_LAYER_COUNT];	//IMG路径名·导出时使用
	void updateIMG(int cb);								//根据组合框内的内容改变IMG（会变更矩阵并绘制）
	void updateByPalette(int cb);						//根据调色板内容改变矩阵
	void updateByFrame(int frame);						//根据帧数改变改变所有矩阵（会绘制）
	void updateMatrix(int cb);							//根据部件 更新矩阵
	void getCanvas(matrix &mat);						//根据图层确定画布矩阵
	static UINT loadNPKThread(PVOID para);
	static UINT drawThread_av(PVOID para);		//总绘制线程

	CProgressCtrl m_p1;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnCbnSelchangeCombo6();
	afx_msg void OnCbnSelchangeCombo7();
	afx_msg void OnCbnSelchangeCombo8();
	afx_msg void OnCbnSelchangeCombo9();
	afx_msg void OnCbnSelchangeCombo10();
	afx_msg void OnCbnSelchangeCombo11();
	afx_msg void OnCbnSelchangeCombo12();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo14();
	afx_msg void OnCbnSelchangeCombo15();
	afx_msg void OnCbnSelchangeCombo16();
	afx_msg void OnCbnSelchangeCombo17();
	afx_msg void OnCbnSelchangeCombo18();
	afx_msg void OnCbnSelchangeCombo19();
	afx_msg void OnCbnSelchangeCombo20();
	afx_msg void OnCbnSelchangeCombo21();
	afx_msg void OnCbnSelchangeCombo22();
	afx_msg void OnCbnSelchangeCombo23();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedCancel();
	CComboBox m_cPart13;
	afx_msg void OnCbnSelchangeCombo13();
};