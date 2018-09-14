
// ExKittyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExKitty.h"
#include "ExKittyDlg.h"
#include "afxdialogex.h"
#include "Func.h"
#include "GoodListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExKittyDlg �Ի���

CExKittyDlg::CExKittyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExKittyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExKittyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExKittyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MENU1, &CExKittyDlg::OnBnClickedButtonMenu1)
	ON_BN_CLICKED(IDC_BUTTON_MENU2, &CExKittyDlg::OnBnClickedButtonMenu2)
	ON_BN_CLICKED(IDC_BUTTON_MENU3, &CExKittyDlg::OnBnClickedButtonMenu3)
	ON_BN_CLICKED(IDC_BUTTON_MENU4, &CExKittyDlg::OnBnClickedButtonMenu4)
	ON_BN_CLICKED(IDC_BUTTON_MENU5, &CExKittyDlg::OnBnClickedButtonMenu5)
END_MESSAGE_MAP()


// CExKittyDlg ��Ϣ�������

BOOL CExKittyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Initial();
	DrawUI();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExKittyDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExKittyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CExKittyDlg::Initial(){
	for(int i = 0;i<10;i++){
		avatarEnableDisplay[i] = true;
		avatarIconEnable[i].LoadBitmap(IDB_AVATAR_ICON_NULL_ENABLE);
		avatarIconDisable[i].LoadBitmap(IDB_AVATAR_ICON_NULL_DISABLE);
	}
}
void CExKittyDlg::DrawUI(){
	SetWindowPos(NULL,200,100,800,480,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU1)->SetWindowPos(NULL,200,0,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU2)->SetWindowPos(NULL,240,0,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU3)->SetWindowPos(NULL,280,0,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU4)->SetWindowPos(NULL,320,0,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_BUTTON_MENU5)->SetWindowPos(NULL,360,0,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_EDIT_INFO)->SetWindowPos(NULL,0,40,200,80,SWP_NOZORDER);
	GetDlgItem(IDC_IMG_LIST)->SetWindowPos(NULL,200,40,200,400,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON1)->SetWindowPos(NULL, 0,120,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON2)->SetWindowPos(NULL, 40,120,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON3)->SetWindowPos(NULL, 80,120,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON4)->SetWindowPos(NULL, 120,120,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON5)->SetWindowPos(NULL, 160,120,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON6)->SetWindowPos(NULL, 0,160,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON7)->SetWindowPos(NULL, 40,160,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON8)->SetWindowPos(NULL, 80,160,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON9)->SetWindowPos(NULL, 120,160,40,40,SWP_NOZORDER);
	GetDlgItem(IDC_IMAGE_AVATAR_ICON10)->SetWindowPos(NULL, 160,160,40,40,SWP_NOZORDER);
	((CGoodListCtrl*)GetDlgItem(IDC_IMG_LIST))->EasyInsertColumn(L"��λ,60,���,40,����,40");
	DrawIconButton();
	DrawPalette();
}

void CExKittyDlg::DrawIconButton(){
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON1))->SetBitmap(avatarEnableDisplay[0]?avatarIconEnable[0]:avatarIconDisable[0]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON2))->SetBitmap(avatarEnableDisplay[1]?avatarIconEnable[1]:avatarIconDisable[1]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON3))->SetBitmap(avatarEnableDisplay[2]?avatarIconEnable[2]:avatarIconDisable[2]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON4))->SetBitmap(avatarEnableDisplay[3]?avatarIconEnable[3]:avatarIconDisable[3]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON5))->SetBitmap(avatarEnableDisplay[4]?avatarIconEnable[4]:avatarIconDisable[4]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON6))->SetBitmap(avatarEnableDisplay[5]?avatarIconEnable[5]:avatarIconDisable[5]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON7))->SetBitmap(avatarEnableDisplay[6]?avatarIconEnable[6]:avatarIconDisable[6]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON8))->SetBitmap(avatarEnableDisplay[7]?avatarIconEnable[7]:avatarIconDisable[7]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON9))->SetBitmap(avatarEnableDisplay[8]?avatarIconEnable[8]:avatarIconDisable[8]);
	((CStatic*)GetDlgItem(IDC_IMAGE_AVATAR_ICON10))->SetBitmap(avatarEnableDisplay[9]?avatarIconEnable[9]:avatarIconDisable[9]);
}

void CExKittyDlg::DrawPalette(){
	matrix paletteCanvas;
	int i,j;
	paletteCanvas.allocate(40, 400);
	for(i=0;i<400;i++){
		for(j=0;j<40;j++){
			if(i % 20 == 0 || i % 20 == 19 || j % 20 == 0 || j % 20 == 19){
				paletteCanvas[j][i] = Koishi::color(0xFF,0,0,0);
			}
		}
	}

	CImage img;
	int width = 40;
	int height = 400;
	img.Create(width, height, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(j=0;j<width;j++){
		for(i=0;i<height;i++){
			*(pst + pit*j + 4*i + 0) = paletteCanvas[j][i].get_B();
			*(pst + pit*j + 4*i + 1) = paletteCanvas[j][i].get_G();
			*(pst + pit*j + 4*i + 2) = paletteCanvas[j][i].get_R();
		}
	}
	img.Draw(pDC->m_hDC,0,0);
	img.Destroy();
	paletteCanvas.release();
	ReleaseDC(pDC);
}

void CExKittyDlg::OnBnClickedButtonMenu1(){
	// TODO: �½���ť
}


void CExKittyDlg::OnBnClickedButtonMenu2(){
	// TODO: �򿪰�ť
}


void CExKittyDlg::OnBnClickedButtonMenu3(){
	// TODO: ���밴ť
}


void CExKittyDlg::OnBnClickedButtonMenu4(){
	// TODO: ���ð�ť
}


void CExKittyDlg::OnBnClickedButtonMenu5(){
	// TODO: ������ť
}
