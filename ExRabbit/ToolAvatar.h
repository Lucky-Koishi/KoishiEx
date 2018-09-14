#pragma once


// CToolAvatar �Ի���
#define AVATAR_MAX_NPK_COUNT				10			//ʱװNPK�ļ��������ֵ
#define AVATAR_MAX_LAYER_COUNT				64			//ʱװͼ�㣨��IMG���������ֵ


class CToolAvatar : public CDialogEx
{
	DECLARE_DYNAMIC(CToolAvatar)

public:
	CToolAvatar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolAvatar();

// �Ի�������
	enum { IDD = IDD_TOOL_AVATAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cType;
	CComboBox m_cPart1,m_cPart2,m_cPart3,m_cPart4,m_cPart5;
	CComboBox m_cPart6,m_cPart7,m_cPart8,m_cPart9,m_cPart10;
	CComboBox m_cPalette1,m_cPalette2,m_cPalette3,m_cPalette4,m_cPalette5;
	CComboBox m_cPalette6,m_cPalette7,m_cPalette8,m_cPalette9,m_cPalette10;
	CComboBox *cbPart		[AVATAR_MAX_NPK_COUNT];		//10��ʱװID��Ͽ��ָ��
	CComboBox *cbPalette	[AVATAR_MAX_NPK_COUNT];	//10��ʱװ��ɫ����Ͽ��ָ��
	CEdit m_e1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();

	void draw();
	volatile bool drawing;			//���ڻ���
	int frmID;					//��ǰ֡
	point basePoint;			//��׼��
	NPKobject	noList		[AVATAR_MAX_NPK_COUNT];		//NPK����ѡ���ɫ��ȷ��
	CString		ioSuffix	[AVATAR_MAX_NPK_COUNT];		//AvatarID�����֣���Ͽ�����ʾ�����֣���ѡ���ɫ��ȷ��
	
	IMGobject	ioList		[AVATAR_MAX_LAYER_COUNT];	//IMG����ѡ�񲿼������
	int			pltID		[AVATAR_MAX_LAYER_COUNT];	//��ɫ�塤ѡ���ɫ������
	matrix		layer		[AVATAR_MAX_LAYER_COUNT];	//ͼ�����ѡ�񲿼���ѡ��֡�����
	str			ioName		[AVATAR_MAX_LAYER_COUNT];	//IMG·����������ʱʹ��
	void updateIMG(int cb);								//������Ͽ��ڵ����ݸı�IMG���������󲢻��ƣ�
	void updateByPalette(int cb);						//���ݵ�ɫ�����ݸı����
	void updateByFrame(int frame);						//����֡���ı�ı����о��󣨻���ƣ�
	void updateMatrix(int cb);							//���ݲ��� ���¾���
	void getCanvas(matrix &mat);						//����ͼ��ȷ����������
	static UINT loadNPKThread(PVOID para);
	static UINT drawThread_av(PVOID para);		//�ܻ����߳�

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