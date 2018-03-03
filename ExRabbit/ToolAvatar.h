#pragma once


// CToolAvatar 对话框

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
	CComboBox m_cPart1;
	CComboBox m_cPart2;
	CComboBox m_cPart3;
	CComboBox m_cPart4;
	CComboBox m_cPart5;
	CComboBox m_cPart6;
	CComboBox m_cPart7;
	CComboBox m_cPart8;
	CComboBox m_cPart9;
	CComboBox m_cPart10;
	CComboBox m_cPalette1;
	CComboBox m_cPalette2;
	CComboBox m_cPalette3;
	CComboBox m_cPalette4;
	CComboBox m_cPalette5;
	CComboBox m_cPalette6;
	CComboBox m_cPalette7;
	CComboBox m_cPalette8;
	CComboBox m_cPalette9;
	CComboBox m_cPalette10;
	CEdit m_e1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	void draw();
	volatile bool drawing;			//正在绘制
	volatile int imgDrawing;		//正在绘制第几个
	volatile bool preLoaded;		//前一个IMGloading
	volatile bool preDrawed[64];	//前一个Drawing(0是背景),1才是第0号图层
	int frmID;		//帧数
	point basePoint;	//基准点
	NPKobject noList[10];
	CString ioSuffix[10];
	IMGobject ioList[64];
	str ioName[64];
	int pltID[64];
	int imgCount;
	CComboBox *cbPart[10];
	CComboBox *cbPalette[10];
	matrix canvas;
	static CString GetRequestNPK(KoishiTitle::charElem ch, KoishiTitle::mainPartElem pt);//不适用于WEAPON
	static UINT loadNPKThread(PVOID para);
	static UINT drawThread_av(PVOID para);
	static UINT drawThread_bg(PVOID para);
	static UINT drawThread_fg(PVOID para);
	CString LoadStringToOutput(__in UINT id);
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