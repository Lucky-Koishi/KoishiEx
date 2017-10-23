
// ExRabbitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ExRabbitDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExRabbitDlg 对话框


CExRabbitDlg::CExRabbitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExRabbitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExRabbitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnMenu);
	DDX_Control(pDX, IDC_EDIT_INFO, m_edInfo);
	DDX_Control(pDX, IDC_EDIT_NPK, m_edNPK);
	DDX_Control(pDX, IDC_LIST_IMG, m_lIMG);
	DDX_Control(pDX, IDC_PROGRESS1, m_pgInfo);
	DDX_Control(pDX, IDC_COMBO_PRO, m_cbPro);
	DDX_Control(pDX, IDC_EDIT_BASEX, m_edX);
	DDX_Control(pDX, IDC_EDIT_BASEY, m_edY);
	DDX_Control(pDX, IDC_EDIT_IMGINFO, m_edIMGinfo);
	DDX_Control(pDX, IDC_EDIT_IMGNAME, m_edIMGname);
	DDX_Control(pDX, IDC_LIST_CLR, m_lColor);
	DDX_Control(pDX, IDC_LIST_PIC, m_lPicture);
	DDX_Control(pDX, IDC_SPIN_X, m_spX);
	DDX_Control(pDX, IDC_SPIN_Y, m_spY);
	DDX_Control(pDX, IDC_LIST_DDS, m_lDDS);
}

BEGIN_MESSAGE_MAP(CExRabbitDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MENU, &CExRabbitDlg::OnBnClickedButtonMenu)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMClickListImg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_IMG, &CExRabbitDlg::OnNMRClickListImg)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CLR, &CExRabbitDlg::OnNMClickListClr)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CLR, &CExRabbitDlg::OnNMRClickListClr)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMClickListDds)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DDS, &CExRabbitDlg::OnNMRClickListDds)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMClickListPic)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PIC, &CExRabbitDlg::OnNMRClickListPic)
	ON_CBN_SELCHANGE(IDC_COMBO_PRO, &CExRabbitDlg::OnCbnSelchangeComboPro)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_X, &CExRabbitDlg::OnDeltaposSpinX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_Y, &CExRabbitDlg::OnDeltaposSpinY)
	ON_COMMAND(ID_MAINMENU_NEW, &CExRabbitDlg::OnMainMenuNew)
	ON_COMMAND(ID_MAINMENU_OPEN, &CExRabbitDlg::OnMainMenuOpen)
	ON_COMMAND(ID_MAINMENU_SAVE, &CExRabbitDlg::OnMainMenuSave)
	ON_COMMAND(ID_MAINMENU_ABOUT, &CExRabbitDlg::OnMainMenuAbout)
	ON_COMMAND(ID_MAINMENU_QUIT, &CExRabbitDlg::OnMainmenuQuit)
	ON_COMMAND(ID_IMGMENU_EXTRACT, &CExRabbitDlg::OnImgMenuExtract)
	ON_COMMAND(ID_IMGMENU_INSERT, &CExRabbitDlg::OnImgMenuInsert)
	ON_COMMAND(ID_IMGMENU_REMOVE, &CExRabbitDlg::OnImgMenuRemove)
	ON_COMMAND(ID_IMGMENU_REPLACE, &CExRabbitDlg::OnImgMenuReplace)
	ON_COMMAND(ID_IMGMENU_RENAME, &CExRabbitDlg::OnImgMenuRename)
	ON_COMMAND(ID_IMGMENU_MOVEUP, &CExRabbitDlg::OnImgMenuMoveUp)
	ON_COMMAND(ID_IMGMENU_MOVEDOWN, &CExRabbitDlg::OnImgMenuMoveDown)
	ON_COMMAND(ID_IMGMENU_HIDE, &CExRabbitDlg::OnImgMenuHide)
	ON_COMMAND(ID_IMGMENU_CONVERT, &CExRabbitDlg::OnImgMenuConvert)
	ON_COMMAND(ID_IMGMENU2_INSERT, &CExRabbitDlg::OnImgMenu2Insert)
	ON_COMMAND(ID_PICMENU_EXTRACTPNG, &CExRabbitDlg::OnPicMenuExtractPng)
	ON_COMMAND(ID_PICMENU_EXTRACTALLPNG, &CExRabbitDlg::OnPicMenuExtractAllPng)
	ON_COMMAND(ID_PICMENU_EXTRACTINDEX, &CExRabbitDlg::OnPicMenuExtractIndex)
	ON_COMMAND(ID_PICMENU_EXTRACTALLINDEX, &CExRabbitDlg::OnPicMenuExtractAllIndex)
	ON_COMMAND(ID_PICMENU_INSERT, &CExRabbitDlg::OnPicMenuInsert)
	ON_COMMAND(ID_PICMENU_REMOVE, &CExRabbitDlg::OnPicMenuRemove)
	ON_COMMAND(ID_PICMENU_REPLACE, &CExRabbitDlg::OnPicMenuReplace)
	ON_COMMAND(ID_PICMENU_SETPARA, &CExRabbitDlg::OnPicMenuSetPara)
	ON_COMMAND(ID_PICMENU_LINKTO, &CExRabbitDlg::OnPicMenuLinkTo)
	ON_COMMAND(ID_PICMENU_HIDE, &CExRabbitDlg::OnPicMenuHide)
	ON_COMMAND(ID_PICMENU2_EXTRACTALLPNG, &CExRabbitDlg::OnPicMenu2ExtractAllPng)
	ON_COMMAND(ID_PICMENU2_EXTRACTALLINDEX, &CExRabbitDlg::OnPicMenu2ExtractAllIndex)
	ON_COMMAND(ID_PICMENU2_INSERT, &CExRabbitDlg::OnPicMenu2Insert)
	ON_COMMAND(ID_DDSMENU_EXTRACTPNG, &CExRabbitDlg::OnDdsMenuExtractPng)
	ON_COMMAND(ID_DDSMENU_EXTRACTALLPNG, &CExRabbitDlg::OnDdsMenuExtractAllPng)
	ON_COMMAND(ID_DDSMENU_EXTRACTDDS, &CExRabbitDlg::OnDdsMenuExtractDds)
	ON_COMMAND(ID_DDSMENU_EXTRACTALLDDS, &CExRabbitDlg::OnDdsMenuExtractAllDds)
	ON_COMMAND(ID_DDSMENU_INSERT, &CExRabbitDlg::OnDdsMenuInsert)
	ON_COMMAND(ID_DDSMENU_REMOVE, &CExRabbitDlg::OnDdsMenuRemove)
	ON_COMMAND(ID_DDSMENU_REPLACE, &CExRabbitDlg::OnDdsMenuReplace)
	ON_COMMAND(ID_DDSMENU2_EXTRACTALLPNG, &CExRabbitDlg::OnDdsMenu2ExtractAllPng)
	ON_COMMAND(ID_DDSMENU2_EXTRACTALLDDS, &CExRabbitDlg::OnDdsMenu2ExtractAllDds)
	ON_COMMAND(ID_DDSMENU2_INSERT, &CExRabbitDlg::OnDdsMenu2Insert)
	ON_COMMAND(ID_CLRMENU_INSERT, &CExRabbitDlg::OnClrMenuInsert)
	ON_COMMAND(ID_CLRMENU_REMOVE, &CExRabbitDlg::OnClrmenuRemove)
	ON_COMMAND(ID_CLRMENU_REPLACE, &CExRabbitDlg::OnClrMenuReplace)
	ON_COMMAND(ID_CLRMENU_EXTRACTPALETTE, &CExRabbitDlg::OnClrMenuExtractPalette)
	ON_COMMAND(ID_CLRMENU_EXTRACTALLPALETTE, &CExRabbitDlg::OnClrMenuExtractAllPalette)
	ON_COMMAND(ID_CLRMENU2_INSERT, &CExRabbitDlg::OnClrMenu2Insert)
	ON_COMMAND(ID_CLRMENU2_EXTRACTPALETTE, &CExRabbitDlg::OnClrMenu2ExtractPalette)
	ON_COMMAND(ID_CLRMENU2_EXTRACTALLPALETTE, &CExRabbitDlg::OnClrMenu2ExtractAllPalette)
	ON_COMMAND(ID_DISPLAYMENU_SWITCH_ABS, &CExRabbitDlg::OnDisplayMenuSwitchAbs)
	ON_COMMAND(ID_DISPLAYMENU_AUTOFIND, &CExRabbitDlg::OnDisplayMenuAutoFind)
	ON_COMMAND(ID_DISPLAYMENU_SWITCHINDEX, &CExRabbitDlg::OnDisplayMenuSwitchIndex)
	ON_COMMAND(ID_DISPLAYMENU_SWITCHDDS, &CExRabbitDlg::OnDisplayMenuSwitchDds)
	ON_COMMAND(ID_DISPLAYMENU_COLORTAB, &CExRabbitDlg::OnDisplayMenuColorTab)
	ON_COMMAND(ID_DISPLAYMENU_PICBOUND, &CExRabbitDlg::OnDisplayMenuPicBound)
	ON_COMMAND(ID_DISPLAYMENU_FRMBOUND, &CExRabbitDlg::OnDisplayMenuFrmBound)
	ON_COMMAND(ID_DISPLAYMENU_BASEAXIS, &CExRabbitDlg::OnDisplayMenuBaseAxis)
	ON_COMMAND(ID_DISPLAYMENU_GRID, &CExRabbitDlg::OnDisplayMenuGrid)
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_MENU2, &CExRabbitDlg::OnBnClickedButtonMenu2)
END_MESSAGE_MAP()
/////////

// CExRabbitDlg 消息处理程序

BOOL CExRabbitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_lPicture.SetExtendedStyle(m_lPicture.GetExtendedStyle()|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT);
	m_lColor.SetExtendedStyle(m_lColor.GetExtendedStyle()|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT);
	m_lDDS.SetExtendedStyle(m_lDDS.GetExtendedStyle()|LVS_EX_ONECLICKACTIVATE|LVS_EX_FULLROWSELECT);
	m_lIMG.EasyInsertColumn(L"IMG名,145");
	m_pgInfo.SetRange32(0,1000);
	m_edNPK.SetWindowText(L"这里显示NPK文件的信息");
	m_edIMGinfo.SetWindowText(L"这里显示IMG文件的信息");
	m_edX.SetWindowText(L"0");
	m_edY.SetWindowText(L"0");
	switchIMGver(V2);
	fileOpen =false;
	dispModeAbs = false;
	dispModeIndex = false;
	dispModeDds = false;
	dispSwColorTab = false;
	dispSwPicBound = false;
	dispSwFrmBound = false;
	dispSwAxis = false;
	dispSwGrid = false;
	fileNPKname = L"";
	fileIMGname = L"";
	drawing = 0;
	to_ver = V2;
	drawDDS = 0;
	extracting = 0;	//提取中
	converting = 0;	//转换中
	crtIMGid = -1;

	dlgInsert.Create(IDD_INSERT_DIALOG, this);
	dlgInsert.ShowWindow(SW_HIDE);
	dlgRename.Create(IDD_RENAME_DIALOG, this);
	dlgRename.ShowWindow(SW_HIDE);
	dlgTrasform.Create(IDD_TRASFORM_DIALOG, this);
	dlgTrasform.ShowWindow(SW_HIDE);
	dlgNew.Create(IDD_NEW_DIALOG, this);
	dlgNew.ShowWindow(SW_HIDE);
	dlgInsert2.Create(IDD_INSERT2_DIALOG, this);
	dlgInsert2.ShowWindow(SW_HIDE);
	dlgSetpara.Create(IDD_SERPARA_DIALOG, this);
	dlgSetpara.ShowWindow(SW_HIDE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExRabbitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExRabbitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CExRabbitDlg::switchIMGver(IMGversion ver){
	int i;
	switch(ver){
	case V2:
		m_lPicture.SetWindowPos(NULL,0,0,455,175,SWP_NOZORDER|SWP_NOMOVE);
		m_lColor.ShowWindow(SW_HIDE);
		m_lDDS.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_HIDE);
		m_lPicture.EasyInsertColumn(L"帧号,40,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
		break;
	case V4:
		m_lPicture.SetWindowPos(NULL,0,0,321,175,SWP_NOZORDER|SWP_NOMOVE);
		m_lColor.SetWindowPos(NULL,0,0,129,175,SWP_NOZORDER|SWP_NOMOVE);
		m_lColor.ShowWindow(SW_SHOW);
		m_lDDS.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_HIDE);
		m_lPicture.EasyInsertColumn(L"帧号,40,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
		m_lColor.EasyInsertColumn(L"色号,40,RGBA数据,70");
		break;
	case V5:
		m_lPicture.SetWindowPos(NULL,0,0,321,175,SWP_NOZORDER|SWP_NOMOVE);
		m_lDDS.SetWindowPos(NULL,0,0,129,175,SWP_NOZORDER|SWP_NOMOVE);
		m_lColor.ShowWindow(SW_HIDE);
		m_lDDS.ShowWindow(SW_SHOW);
		m_cbPro.ShowWindow(SW_HIDE);
		m_lPicture.EasyInsertColumn(L"帧号,40,颜色格式,90,使用DDS状态,200,基准坐标,80,尺寸,80,帧域尺寸,80");
		m_lDDS.EasyInsertColumn(L"编号,40,颜色格式,90,尺寸,80");
		break;
	case V6:
		m_lPicture.SetWindowPos(NULL,0,0,321,175,SWP_NOZORDER|SWP_NOMOVE);
		m_lColor.SetWindowPos(NULL,0,0,129,175,SWP_NOZORDER|SWP_NOMOVE);
		m_lColor.ShowWindow(SW_SHOW);
		m_lDDS.ShowWindow(SW_HIDE);
		m_cbPro.ShowWindow(SW_SHOW);
		m_lPicture.EasyInsertColumn(L"帧号,40,颜色格式,90,基准坐标,80,尺寸,80,帧域尺寸,80");
		m_lColor.EasyInsertColumn(L"色号,40,RGBA数据,70");
		m_cbPro.ResetContent();
		for(i = 0;i<io.paletteData.getCount();i++)
			m_cbPro.AddString(L"调色板方案"+NumToCStr(i));
		if(io.paletteData.getCount()>0){
			m_cbPro.SetCurSel(0);
		}
		break;
	}
	return 0;
}

BOOL CExRabbitDlg::updateIMGlist(){
	// 更新IMG列表
	updateNPKInfo();
	m_lIMG.DeleteAllItems();
	for(int i = 0;i<no.count;i++){
		m_lIMG.EasyInsertItem(shorten(StrToCStr(no.content[i].get_imgname()),'/'));
	}
	return 0;
}

BOOL CExRabbitDlg::updatePIClist(){
	// 更新IMG列表
	CString cstr;
	m_lPicture.DeleteAllItems();
	for(int i=0;i<io.indexCount;i++){
		cstr = NumToCStr(i) + L",";
		cstr += FmtToCStr(io.PICcontent[i].get_format(), io.version);
		if(io.PICcontent[i].get_format() == LINK){
			cstr += NumToCStr(io.PICcontent[i].get_linkTo());
		}
		cstr += L",";
		if(io.version == V5){
			cstr += L"DDS"+NumToCStr(io.PICcontent[i].get_DDSIDused())+L":"+PtToCStr(io.PICcontent[i].get_DDSpointLT())+L"-"+PtToCStr(io.PICcontent[i].get_DDSpointRB())+L",";
		}
		cstr += PtToCStr(io.PICcontent[i].get_basePt()) + L",";
		cstr += SzToCStr(io.PICcontent[i].get_picSize())+L",";
		cstr += SzToCStr(io.PICcontent[i].get_frmSize());
		m_lPicture.EasyInsertItem(cstr);
	}
	return 0;
}

BOOL CExRabbitDlg::updateCLRlist(){
	//更新颜色列表
	CString cstr;
	m_lColor.DeleteAllItems();
	int pro = m_cbPro.GetCurSel();
	if(io.version == V4){
		pro = 0;
	}
	if(pro<0 || pro>io.paletteData.getCount()-1)
		return 1;
	for(int i=0;i<io.paletteData[pro].size();i++){
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += ClrToCStr(io.paletteData[pro][i]);
		m_lColor.EasyInsertItem(cstr);
	}
	return 0;
}

BOOL CExRabbitDlg::updateDDSlist(){
	//更新颜色列表
	CString cstr;
	m_lDDS.DeleteAllItems();
	for(int i=0;i<io.DDScontent.size();i++){
		cstr = L"#" + NumToCStr(i) + L",";
		cstr += FmtToCStr((colorFormat)(int)io.DDScontent[i].get_fourCCID(),V5)+L",";
		cstr += NumToCStr(io.DDScontent[i].get_width())+L"×";
		cstr += NumToCStr(io.DDScontent[i].get_height());
		m_lDDS.EasyInsertItem(cstr);
	}
	return 0;
}
BOOL CExRabbitDlg::updateNPKInfo(){
	CString cstr;
	cstr = L"文件名："+shorten(fileNPKname,'\\')+L"\r\n";
	cstr += L"大小："+NumToCStr(no.getSize())+L"\r\n";
	cstr += L"IMG数："+NumToCStr(no.count);
	m_edNPK.SetWindowText(cstr);
	return 0;
}
BOOL CExRabbitDlg::updateIMGInfo(){
	CString cstr;
	cstr = shorten(fileIMGname,'\\');
	cstr += L" 于"+shorten(fileNPKname, '\\');
	cstr += L"中";
	m_edIMGname.SetWindowText(cstr);
	return 0;
}
BOOL CExRabbitDlg::updatePICInfo(){
	CString cstr;
	int i;
	cstr = L"版本:"+NumToCStr(io.version)+L"\r\n";
	cstr += L"帧数:"+NumToCStr(io.indexCount)+L"\r\n";
	switch(io.version){
	case V4:
		cstr += L"调色板颜色项:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V5:
		cstr += L"DDS大图个数:"+NumToCStr(io.DDScontent.size())+L"\r\n";
		cstr += L"调色板颜色项:"+NumToCStr(io.paletteData[0].size())+L"\r\n";
		break;
	case V6:
		cstr += L"调色板方案数:"+NumToCStr(io.paletteData.getCount())+L"\r\n";
		if((i = m_cbPro.GetCurSel()) >= 0){
			cstr += L"当前方案颜色项:"+NumToCStr(io.paletteData[i].size())+L"\r\n";
		}
		break;
	}
	m_edIMGinfo.SetWindowText(cstr);
	return 0;
}
//点击菜单按钮
void CExRabbitDlg::OnBnClickedButtonMenu()
{
	// TODO: 点击菜单按钮
	CMenu menu, *pPopup;  
    menu.LoadMenu(IDR_MENU);  
    pPopup = menu.GetSubMenu(0);  
    CPoint myPoint;  
    ClientToScreen(&myPoint);  
    GetCursorPos(&myPoint); //鼠标位置  
    pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
}
void CExRabbitDlg::OnBnClickedButtonMenu2()
{
	// TODO: 在此添加控件通知处理程序代码
	int row;
	if((row = crtIMGid) >= 0){
		no.IMGreplace(row, io);
		MessageBox(L"已保存完毕喵！");
		updateIMGlist();
		updatePIClist();
		updateCLRlist();
		updateDDSlist();
		updateNPKInfo();
		updateIMGInfo();
		updatePICInfo();
		m_lIMG.SetSelectionMark(row);
	}
}

//////////////////////////////////////////////////
/////////////////表头事件/////////////////////////
//////////////////////////////////////////////////
void CExRabbitDlg::OnNMClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int row = pNMListView->iItem;
	if(row>=0){
		io.Release();
		no.IMGextract(row, io);
		fileIMGname = shorten(StrToCStr(no.content[row].get_imgname()),'/');
		switchIMGver(io.version);
		updatePIClist();
		updateCLRlist();
		updateDDSlist();
		updateIMGInfo();
		updatePICInfo();
		crtIMGid = row;
	}
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListImg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListImg(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?1:2);  
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}


void CExRabbitDlg::OnNMClickListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListClr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 右键点击颜色菜单
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListClr(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?7:8);    
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}


void CExRabbitDlg::OnNMClickListDds(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	draw(true);
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListDds(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListDds(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?5:6);  
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}


void CExRabbitDlg::OnNMClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	OnNMClickListPic(pNMHDR, pResult);
	int row = pNMListView->iItem;
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU);  
	pPopup = menu.GetSubMenu(row>=0?3:4);  
	//v4v6不能提取索引表
	if(row>=0 && !(io.version == V4 || io.version == V6)){
		pPopup->EnableMenuItem(ID_PICMENU_EXTRACTALLINDEX, MF_DISABLED|MF_GRAYED);
		pPopup->EnableMenuItem(ID_PICMENU_EXTRACTINDEX, MF_DISABLED|MF_GRAYED);
	}
	if(row>=0 && io.PICcontent[row].get_format() == LINK){
		pPopup->EnableMenuItem(ID_PICMENU_EXTRACTINDEX, MF_DISABLED|MF_GRAYED);
		pPopup->EnableMenuItem(ID_PICMENU_SETPARA, MF_DISABLED|MF_GRAYED);
	}
	CPoint myPoint;  
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	*pResult = 0;
}


void CExRabbitDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(point.x>164 && point.y>226){
		CMenu menu, *pPopup;  
		menu.LoadMenu(IDR_MENU);  
		pPopup = menu.GetSubMenu(9);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCH_ABS, dispModeAbs?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCHINDEX, dispModeIndex?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_SWITCHDDS, dispModeDds?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_COLORTAB, dispSwColorTab?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_PICBOUND, dispSwPicBound?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_FRMBOUND, dispSwFrmBound?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_BASEAXIS, dispSwAxis?MF_CHECKED:MF_UNCHECKED);
		menu.CheckMenuItem(ID_DISPLAYMENU_GRID, dispSwGrid?MF_CHECKED:MF_UNCHECKED);
		CPoint myPoint;  
		ClientToScreen(&myPoint);  
		GetCursorPos(&myPoint); //鼠标位置  
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);  
	}
	CDialogEx::OnRButtonUp(nFlags, point);
}


void CExRabbitDlg::OnDeltaposSpinX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	basePoint.set_X(basePoint.get_X()+pNMUpDown->iDelta);
	m_edX.SetWindowText(NumToCStr(basePoint.get_X()));
	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnDeltaposSpinY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	basePoint.set_Y(basePoint.get_Y()+pNMUpDown->iDelta);
	m_edY.SetWindowText(NumToCStr(basePoint.get_Y()));
	draw();
	*pResult = 0;
}


void CExRabbitDlg::OnCbnSelchangeComboPro()
{
	// TODO: 在此添加控件通知处理程序代码
	draw();
}

void CExRabbitDlg::draw(bool isDDS){
	drawDDS = isDDS;
	AfxBeginThread(drawThread, (LPVOID)this);
}
void CExRabbitDlg::transform(IMGversion vers){
	to_ver = vers;
	AfxBeginThread(transformThread, (LPVOID)this);
}
UINT drawThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	int row = dlg->m_lPicture.GetSelectionMark();
	int clrRow = dlg->m_lColor.GetSelectionMark();
	int ddsRow = dlg->m_lDDS.GetSelectionMark();
	int cbpro = dlg->m_cbPro.GetCurSel();
	bool chaxis = dlg->dispModeAbs;
	if(dlg->drawing)
		return 0;
	dlg->m_edInfo.SetWindowText(L"绘制中……");
	dlg->drawing = 1;
	IMGobject *io = &(dlg->io);
	int i,j,tx,ty;
	CImage img;

	matrix mat, canvas;
	color clr;
	canvas.allocate(300,600);
	canvas.fill(color(0xff,0x33,0x33,0x33));

	if(dlg->drawDDS){
		if(ddsRow == -1){
			dlg->drawing = 0;
			dlg->m_edInfo.SetWindowText(L"绘制终止。");
			return 0;
		}
		DDSinfo di;
		stream s,s1;
		io->GetDDSInfo(ddsRow, di);
		io->DDSextract(ddsRow, mat);
		if(chaxis){
			for(i=0;i<300;i++){
				for(j=0;j<600;j++){
					tx = i-dlg->basePoint.get_Y();	//真实坐标
					ty = j-dlg->basePoint.get_X();	//真是坐标
					if(tx<mat.getRowCount() && ty<mat.getColumnCount()){
						clr = mat.getElem(tx,ty);
						clr.mixWith(canvas.getElem(i,j),LAY);
						canvas.setElem(i, j, clr);
					}
				}
			}
		}else{
			for(i=0;i<300;i++){
				for(j=0;j<600;j++){
					if(i<mat.getRowCount() && j<mat.getColumnCount()){
						clr = mat.getElem(i,j);
						clr.mixWith(canvas.getElem(i,j),LAY);
						canvas.setElem(i, j, clr);
					}
				}
			}
		}
	}else{
		if(row == -1){
			dlg->drawing = 0;
			dlg->m_edInfo.SetWindowText(L"绘制终止。");
			return 0;
		}
		PICinfo po;
		io->GetPICInfo(row, po);
		if(po.get_format() == LINK)
			row = io->linkFind(row);
		io->GetPICInfo(row, po);
		if(io->version == V5)
			cbpro = 0;
		io->PICextract(row, mat, (i32)cbpro);
		if(chaxis){
			for(i=0;i<300;i++){
				for(j=0;j<600;j++){
					tx = i-po.get_basePt().get_Y()-dlg->basePoint.get_Y();	//真实坐标
					ty = j-po.get_basePt().get_X()-dlg->basePoint.get_X();	//真是坐标
					if(tx<mat.getRowCount() && ty<mat.getColumnCount()){
						clr = mat.getElem(tx,ty);
						clr.mixWith(canvas.getElem(i,j),LAY);
						canvas.setElem(i, j, clr);
					}
				}
			}
		}else{
			for(i=0;i<300;i++){
				for(j=0;j<600;j++){
					if(i<mat.getRowCount() && j<mat.getColumnCount()){
						clr = mat.getElem(i,j);
						clr.mixWith(canvas.getElem(i,j),LAY);
						canvas.setElem(i, j, clr);
					}
				}
			}
		}
		int clrBlockSize = 10;
		int clct,cp;
		int m,n;
		if(io->version == V4){
			clct = io->paletteData[0].size();
			for(i=300-clrBlockSize;i<300;i++){
				for(j=0;j<clct;j++){
					for(m = 0;m<clrBlockSize;m++){
						canvas.setElem(i, 600-clrBlockSize*clct+clrBlockSize*j+m, io->paletteData[0][j]);
					}
				}
			}
			tx = 600-clrBlockSize*clct+clrBlockSize*clrRow;
			ty = 300-clrBlockSize;
		
			for(m=0;m<clrBlockSize;m++){
				canvas.setElem(ty+m,tx,color(0xff,0xff,0xff,0xff));
				canvas.setElem(ty,tx+m,color(0xff,0xff,0xff,0xff));
				canvas.setElem(ty+clrBlockSize-1,tx+m,color(0xff,0xff,0xff,0xff));
				canvas.setElem(ty+m,tx+clrBlockSize-1,color(0xff,0xff,0xff,0xff));
				//canvas.setElem(tx+m,	600-clrBlockSize*clct+clrBlockSize*clrRow, color(0xff,0xff,0xff,0xff));
				//canvas.setElem(299-clrBlockSize+m,	600-clrBlockSize*clct+clrBlockSize*(clrRow+1)-1, color(0xff,0xff,0xff,0xff));
			}
		}
		if(io->version == V6){
			cp = io->paletteData.getCount();
			for(i=0;i<cp;i++){
				clct = io->paletteData[cbpro].size();
				for(j=0;j<clct;j++){
					for(m = 0;m<clrBlockSize;m++){
						for(n=0;n<clrBlockSize;n++){
							canvas.setElem(300-clrBlockSize*cp+clrBlockSize*i+m, 600-clrBlockSize*clct+clrBlockSize*j+n, io->paletteData[i][j]);
						}
					}
				}
			}
			tx = 600-clrBlockSize*clct+clrBlockSize*clrRow;
			ty = 300-clrBlockSize*cp+clrBlockSize*cbpro;
		
			for(m=0;m<clrBlockSize;m++){
				canvas.setElem(ty+m,tx,color(0xff,0xff,0xff,0xff));
				canvas.setElem(ty,tx+m,color(0xff,0xff,0xff,0xff));
				canvas.setElem(ty+clrBlockSize-1,tx+m,color(0xff,0xff,0xff,0xff));
				canvas.setElem(ty+m,tx+clrBlockSize-1,color(0xff,0xff,0xff,0xff));
			}
		}
	}
	img.Create(600, 300, 32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();

	for(i=0;i<600;i++){
		for(j=0;j<300;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].get_B();
			*(pst + pit*j + 4*i + 1) = canvas[j][i].get_G();
			*(pst + pit*j + 4*i + 2) = canvas[j][i].get_R();
		}
	}
	img.Draw(dlg->GetDC()->m_hDC,164,226);
	img.Destroy();
	mat.release();
	dlg->drawing = 0;
	dlg->m_edInfo.SetWindowText(L"绘制完毕。");
	canvas.release();
	return 0;
}

UINT transformThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if(dlg->converting){
		dlg->MessageBox(L"上一个转换操作进行中。",L"提示喵");
		return 0;
	}
	dlg->converting = 1;
	int row = dlg->crtIMGid;
	int p;
	str fn, ser;
	IMGobject io, _io;
	dlg->m_edInfo.SetWindowText(L"转换中……");
	dlg->no.IMGextract(row, io);
	if(io.version == V6){
		if(io.paletteData.getCount() <= 0){
			dlg->MessageBox(L"转换失败，没有调色板数据！",L"提示");
			dlg->m_edInfo.SetWindowText(L"转换终止。");
			return 0;
		}
		fn = dlg->no.content[row].get_imgname();
		dlg->no.IMGremove(row);
		for(p=0;p<io.paletteData.getCount();p++){
			dlg->m_pgInfo.SetPos((p+1)*1000/io.paletteData.getCount());
			io.ConvertTo(_io,dlg->to_ver, p);
			ser = 'a' + p;
			dlg->no.IMGinsert(row+p, _io, fn+ser);
			_io.Release();
		}
	}else{
		if(io.ConvertTo(_io,dlg->to_ver)){
			dlg->no.IMGreplace(row, _io);
		}else{
			dlg->MessageBox(L"转换失败，颜色表溢出！",L"提示");
			dlg->m_edInfo.SetWindowText(L"转换终止。");
			return 0;
		}
	}
	dlg->MessageBox(L"转换完毕！",L"提示喵");
	dlg->switchIMGver(dlg->to_ver);
	dlg->updatePIClist();
	dlg->updateIMGInfo();
	dlg->updateDDSlist();
	dlg->updateNPKInfo();
	dlg->updateIMGlist();
	dlg->updateCLRlist();
	dlg->m_edInfo.SetWindowText(L"转换完毕。");
	dlg->converting = 0;
	return 0;
}

UINT extractThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if(dlg->extracting){
		dlg->MessageBox(L"上一个提取操作进行中。",L"提示喵");
		return 0;
	}
	dlg->extracting = 1;
	dlg->m_edInfo.SetWindowText(L"提取中……");
	for(int i = 0;i<dlg->io.indexCount;i++){
		str fn;
		CString filePath;
		CString fileName;
		matrix mat;
		dlg->m_pgInfo.SetPos((i+1)*1000/dlg->io.indexCount);
		if(dlg->io.version == V6){
			fileName = getOutPutDir(dlg->fileIMGname+L"(调色方案"+NumToCStr(dlg->m_cbPro.GetCurSel())+L")")+L"帧号"+NumToCStr(i)+L".PNG";
		}else{
			fileName = getOutPutDir(dlg->fileIMGname)+L"帧号"+NumToCStr(i)+L".PNG";
		}
		CStrToStr(fileName, fn);
		dlg->io.PICextract(i, mat, dlg->m_cbPro.GetCurSel());
		mat.makePNG(fn);
		mat.release();
	}
	dlg->MessageBox(L"已保存到文件夹"+getOutPutDir(dlg->fileIMGname)+L"里了。",L"提示喵");
	dlg->m_edInfo.SetWindowText(L"提取完毕。");
	dlg->extracting = 0;
	return 0;
}

UINT extractDDSPNGThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if(dlg->extracting){
		dlg->MessageBox(L"上一个提取操作进行中。",L"提示喵");
		return 0;
	}
	dlg->extracting = 1;
	dlg->m_edInfo.SetWindowText(L"提取中……");
	for(int i = 0;i<dlg->io.V5_DDSCount;i++){
		str fn;
		CString filePath;
		CString fileName;
		matrix mat;
		dlg->m_pgInfo.SetPos((i+1)*1000/dlg->io.V5_DDSCount);
		fileName = getOutPutDir(dlg->fileIMGname)+L"DDS贴图"+NumToCStr(i)+L".PNG";
		CStrToStr(fileName, fn);
		dlg->io.DDSextract(i, mat);
		mat.makePNG(fn);
		mat.release();
	}
	dlg->MessageBox(L"已保存到文件夹"+getOutPutDir(dlg->fileIMGname)+L"里了。",L"提示喵");
	dlg->m_edInfo.SetWindowText(L"提取完毕。");
	dlg->extracting = 0;
	return 0;
}
UINT extractPIDThread(PVOID para){
	CExRabbitDlg* dlg = (CExRabbitDlg*)para;
	if(dlg->extracting){
		dlg->MessageBox(L"上一个提取操作进行中。",L"提示喵");
		return 0;
	}
	dlg->extracting = 1;
	dlg->m_edInfo.SetWindowText(L"提取中……");
	for(int i = 0;i<dlg->io.indexCount;i++){
		str fn;
		CString fileName =  getOutPutDir(dlg->fileIMGname) + L"帧号"+NumToCStr(i)+L".PID";
		CStrToStr(fileName, fn);
		stream s,s1,sHead;
		PICinfo pi;
		dlg->m_pgInfo.SetPos((i+1)*1000/dlg->io.indexCount);
		dlg->io.GetPICInfo(i, pi);
		dlg->io.GetPICData(i, s);
		if(pi.get_format() == ARGB1555){
			s.uncompressData(s1, pi.get_comp());
			sHead.allocate(16);
			sHead.push((b32)0x73696F4B);
			sHead.push((b32)0x78456968);
			sHead.push(pi.get_picSize().get_W());
			sHead.push(pi.get_picSize().get_H());
			s1.insertStream(sHead, 16, 0);
			s1.makeFile(fn);
		}
		s.release();
		s1.release();
		sHead.release();
	}
	dlg->MessageBox(L"已保存到文件夹"+getOutPutDir(dlg->fileIMGname)+L"里了。",L"提示喵");
	dlg->m_edInfo.SetWindowText(L"提取完毕。");
	dlg->extracting = 0;
	return 0;
}
//////////////////////////////////////////////
/*************菜单处理事件*******************/
//////////////////////////////////////////////
void CExRabbitDlg::OnMainMenuNew()
{
	// TODO: 在此添加命令处理程序代码
	dlgNew.OnBnClickedCheck1();
	dlgNew.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnMainMenuOpen()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 打开文件
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK|IMG文件(*.IMG)|*.IMG|拼合方案(*.MPL)|*.MPL||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName,fmt;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		fmt = fileName.Right(1);
		CStrToStr(fileName, fn);
		if(fmt == L"K" || fmt == L"k"){
			no.release();
			if(no.loadFile(fn)){
				MessageBox(L"读取完毕！");
			}else{
				MessageBox(L"读取失败！");
				return;
			}
			fileNPKname = fileName;
			fileOpen = true;
			updateIMGlist();
			if(no.count>0){
				m_lIMG.SetSelectionMark(0);
				crtIMGid = 0;
			}
		}
		if(fmt == L"G" || fmt == L"g"){
			io.Release();
			if(io.LoadFile(fn)){
				MessageBox(L"读取完毕！");
			}else{
				MessageBox(L"读取失败！");
				return;
			}
			no.release();
			no.create();
			fileIMGname = fileName;
			fileNPKname = L"临时NPK";
			fileOpen = true;
			fileName = shorten(fileName, '\\');
			CStrToStr(fileName, fn);
			no.IMGpush(io, fn);
			switchIMGver(io.version);
			updateIMGlist();
			updatePIClist();
			updateCLRlist();
			updateDDSlist();
			updateNPKInfo();
			updateIMGInfo();
			updatePICInfo();
			m_lIMG.SetSelectionMark(0);
			crtIMGid = 0;
		}
	}
}


void CExRabbitDlg::OnMainMenuSave()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 保存NPK
	CString defExt = _T("NPK文件(*.NPK)|*.NPK");
	CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
	CFileDialog dlg(false, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	str fn;
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		if(no.saveFile(fn)){
			MessageBox(_T("保存完毕！"));
		}else{
			MessageBox(_T("保存失败！"));
		}
	}
}


void CExRabbitDlg::OnMainMenuAbout()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(L"Ex兔子版  --by乘着歌声的翅膀(EXNPK & COLG)");
}


void CExRabbitDlg::OnMainmenuQuit()
{
	// TODO: 在此添加命令处理程序代码
	CDialogEx::OnCancel();
}


void CExRabbitDlg::OnImgMenuExtract()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0)
		return;
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(false, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName1;
	str fn;
	if(dlg.DoModal() == IDOK){
		fileName1 = dlg.GetPathName();
		CStrToStr(fileName1, fn);
		if(no.extractIMGFile(row, fn)){
			MessageBox(_T("保存完毕！"));
		}else{
			MessageBox(_T("保存失败！"));
		}
	}
}


void CExRabbitDlg::OnImgMenuInsert()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0){
		dlgInsert.m_ch1.EnableWindow(false);
		dlgInsert.m_ch2.EnableWindow(false);
	}else{
		dlgInsert.m_ch1.EnableWindow(true);
		dlgInsert.m_ch2.EnableWindow(true);
	}
	dlgInsert.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnImgMenuRemove()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0){
		return;
	}
	if(no.IMGremove(row)){
		MessageBox(L"删除完毕！");
	}else{
		MessageBox(L"删除失败！");
	}
	updateIMGlist();
	m_lIMG.SetSelectionMark(row-1);
}


void CExRabbitDlg::OnImgMenuReplace()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0){
		return;
	}
	CString defExt = _T("IMG文件(*.IMG)|*.IMG");
	CString extFilter = _T("IMG文件(*.IMG)|*.IMG||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	str fn;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		CStrToStr(fileName, fn);
		IMGobject _io;
		_io.LoadFile(fn);
		if(no.IMGreplace(row,_io)){
			MessageBox(L"替换完毕！");
		}else{
			MessageBox(L"替换失败！");
		}
		_io.Release();
		updateIMGlist();
		m_lIMG.SetSelectionMark(row);
	}
}


void CExRabbitDlg::OnImgMenuRename()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0){
		return;
	}
	dlgRename.m_ed1.SetWindowText(StrToCStr(no.content[row].get_imgname()));
	dlgRename.m_ed2.SetWindowText(StrToCStr(no.content[row].get_imgname()));
	dlgRename.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnImgMenuMoveUp()
{
	// TODO: 在此添加命令处理程序代码
	// TODO：上移
	int row = crtIMGid;
	if(row<1){
		return;
	}
	IMGobject _io;
	no.IMGextract(row, _io);
	str fn = no.content[row].get_imgname();
	no.IMGremove(row);
	no.IMGinsert(row-1, _io, fn);
	_io.Release();
	updateNPKInfo();
	updateIMGlist();
}


void CExRabbitDlg::OnImgMenuMoveDown()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0){
		return;
	}
	if(row == no.count - 1){
		return;
	}
	IMGobject _io;
	no.IMGextract(row, _io);
	str fn = no.content[row].get_imgname();
	no.IMGremove(row);
	no.IMGinsert(row+1, _io, fn);
	_io.Release();
	updateNPKInfo();
	updateIMGlist();
}


void CExRabbitDlg::OnImgMenuHide()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0){
		return;
	}
	IMGobject _io;
	PICinfo _pi;
	stream _s;
	no.IMGextract(row, _io);
	for(int i = 0;i<_io.indexCount;i++){
		_io.GetPICInfo(i,_pi);
		_io.PICempty(_s, _pi);
		_io.PICreplace(i, _pi, _s);
		_s.release();
	}
	no.IMGreplace(row, _io);
	MessageBox(L"已隐藏该IMG内所有贴图！",L"提示喵");
	updatePIClist();
}


void CExRabbitDlg::OnImgMenuConvert()
{
	// TODO: 在此添加命令处理程序代码
	int row = crtIMGid;
	if(row<0){
		return;
	}
	IMGobject _io;
	no.IMGextract(row, _io);
	dlgTrasform.m_ch1.EnableWindow(true);
	dlgTrasform.m_ch2.EnableWindow(true);
	dlgTrasform.m_ch3.EnableWindow(true);
	dlgTrasform.m_ch4.EnableWindow(true);
	dlgTrasform.m_ch1.SetCheck(false);
	dlgTrasform.m_ch2.SetCheck(false);
	dlgTrasform.m_ch3.SetCheck(false);
	dlgTrasform.m_ch4.SetCheck(false);
	switch(_io.version){
	case V2:
		dlgTrasform.m_ch1.EnableWindow(false);
		dlgTrasform.m_ch2.SetCheck(1);
		break;
	case V4:
		dlgTrasform.m_ch2.EnableWindow(false);
		dlgTrasform.m_ch1.SetCheck(1);
		break;
	case V5:
		dlgTrasform.m_ch3.EnableWindow(false);
		dlgTrasform.m_ch1.SetCheck(1);
		break;
	case V6:
		dlgTrasform.m_ch4.EnableWindow(false);
		dlgTrasform.m_ch1.SetCheck(1);
		break;
	default:
		MessageBox(L"未识别的版本啊！",L"提示");
		break;
	}

	dlgTrasform.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnImgMenu2Insert()
{
	// TODO: 在此添加命令处理程序代码
	OnImgMenuInsert();
}


void CExRabbitDlg::OnPicMenuExtractPng()
{
	// TODO: 在此添加命令处理程序代码
	int row = m_lPicture.GetSelectionMark();
	if(row == -1){
		return;
	}
	str fn;
	CString fileName;
	if(io.version == V6){
		fileName = getOutPutDir(fileIMGname+L"(调色方案"+NumToCStr(m_cbPro.GetCurSel())+L")")+L"帧号"+NumToCStr(row)+L".PNG";
	}else{
		fileName = getOutPutDir(fileIMGname)+L"帧号"+NumToCStr(row)+L".PNG";
	}
	CStrToStr(fileName, fn);
	matrix mat;
	io.PICextract(row, mat, m_cbPro.GetCurSel());
	mat.makePNG(fn);
	mat.release();
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}


void CExRabbitDlg::OnPicMenuExtractAllPng()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(extractThread, (LPVOID)this);
}


void CExRabbitDlg::OnPicMenuExtractIndex()
{
	// TODO: 在此添加命令处理程序代码
	int row = m_lPicture.GetSelectionMark();
	if(row == -1){
		return;
	}
	str fn;
	CString fileName =  getOutPutDir(fileIMGname) + L"帧号"+NumToCStr(row)+L".PID";
	CStrToStr(fileName, fn);
	stream s,s1,sHead;
	PICinfo pi;
	io.GetPICInfo(row, pi);
	io.GetPICData(row, s);
	s.uncompressData(s1, pi.get_comp());
	sHead.allocate(16);
	sHead.push((b32)0x73696F4B);
	sHead.push((b32)0x78456968);
	sHead.push(pi.get_picSize().get_W());
	sHead.push(pi.get_picSize().get_H());
	s1.insertStream(sHead, 16, 0);
	s1.makeFile(fn);
	s.release();
	s1.release();
	sHead.release();
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}


void CExRabbitDlg::OnPicMenuExtractAllIndex()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(extractPIDThread, (LPVOID)this);
}


void CExRabbitDlg::OnPicMenuInsert()
{
	// TODO: 在此添加命令处理程序代码
	dlgInsert2.SetWindowText(L"插入贴图");
	dlgInsert2.iORr = CDlgInsert2::__INSERT;
	dlgInsert2.ver = io.version;
	switch(io.version){
	case V2:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"插入指向型索引项");
		dlgInsert2.m_cb1.AddString(L"插入图片型索引项(基于PNG文件)");
		break;
	case V4:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"插入指向型索引项");
		dlgInsert2.m_cb1.AddString(L"插入图片型索引项(基于索引)");
		dlgInsert2.m_cb1.AddString(L"插入图片型索引项(基于PNG文件)");
		break;
	case V5:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"插入指向型索引项");
		dlgInsert2.m_cb1.AddString(L"插入DDS图片型索引项(基于已知DDS引用)");
		dlgInsert2.m_cb1.AddString(L"插入DDS图片型索引项(基于PNG文件)");
		break;
	case V6:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"插入指向型索引项");
		dlgInsert2.m_cb1.AddString(L"插入图片型索引项(基于索引)");
		break;
	}
	dlgInsert2.m_ch1.SetCheck(1);
	dlgInsert2.m_ch2.SetCheck(0);
	dlgInsert2.m_ch3.SetCheck(0);
	dlgInsert2.m_ch1.EnableWindow(true);
	dlgInsert2.m_ch2.EnableWindow(true);
	dlgInsert2.m_ch3.EnableWindow(true);
	/////////////////
	dlgInsert2.m_cb1.SetCurSel(1);
	dlgInsert2.OnCbnSelchangeCombo1();
	/////////////////
	dlgInsert2.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnPicMenuRemove()
{
	// TODO: 在此添加命令处理程序代码
	int row = m_lPicture.GetSelectionMark();
	io.PICremove(row);
	m_lPicture.SetSelectionMark(row-1);
	MessageBox(L"已将这个贴图删掉了喵！",L"提示喵！");
}


void CExRabbitDlg::OnPicMenuReplace()
{
	// TODO: 在此添加命令处理程序代码
	dlgInsert2.SetWindowText(L"替换贴图");
	dlgInsert2.iORr = CDlgInsert2::__REPLACE;
	dlgInsert2.ver = io.version;
	switch(io.version){
	case V2:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"替换为指向型索引项");
		dlgInsert2.m_cb1.AddString(L"替换为图片型索引项(基于PNG文件)");
		break;
	case V4:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"替换为指向型索引项");
		dlgInsert2.m_cb1.AddString(L"替换为图片型索引项(基于索引)");
		dlgInsert2.m_cb1.AddString(L"替换为图片型索引项(基于PNG文件)");
		break;
	case V5:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"替换为指向型索引项");
		dlgInsert2.m_cb1.AddString(L"替换为DDS图片型索引项(基于已知DDS引用)");
		dlgInsert2.m_cb1.AddString(L"替换为DDS图片型索引项(基于PNG文件)");
		break;
	case V6:
		dlgInsert2.m_cb1.ResetContent();
		dlgInsert2.m_cb1.AddString(L"替换为指向型索引项");
		dlgInsert2.m_cb1.AddString(L"替换为图片型索引项(基于索引)");
		break;
	}
	dlgInsert2.m_ch1.SetCheck(1);
	dlgInsert2.m_ch2.SetCheck(0);
	dlgInsert2.m_ch3.SetCheck(0);
	dlgInsert2.m_ch1.EnableWindow(false);
	dlgInsert2.m_ch2.EnableWindow(false);
	dlgInsert2.m_ch3.EnableWindow(false);
	///////////////////////////
	int pos = m_lPicture.GetSelectionMark();
	PICinfo pi;
	io.GetPICInfo(pos,pi);
	if(pi.get_format() == LINK){
		dlgInsert2.m_cb1.SetCurSel(0);
	}else{
		dlgInsert2.m_cb1.SetCurSel(1);
	}
	dlgInsert2.OnCbnSelchangeCombo1();
	///////////////////////////
	dlgInsert2.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnPicMenuSetPara()
{
	// TODO: 在此添加命令处理程序代码
	int pos = m_lPicture.GetSelectionMark();
	PICinfo pi;
	io.GetPICInfo(pos,pi);
	dlgSetpara.m_c1.SetCheck(1);
	dlgSetpara.m_c2.SetCheck(0);
	dlgSetpara.m_c3.SetCheck(0);
	dlgSetpara.m_e1.SetWindowText(NumToCStr(pi.get_basePt().get_X()));
	dlgSetpara.m_e2.SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
	dlgSetpara.m_e3.SetWindowText(NumToCStr(pi.get_frmSize().get_W()));
	dlgSetpara.m_e4.SetWindowText(NumToCStr(pi.get_frmSize().get_H()));
	dlgSetpara.ShowWindow(SW_SHOW);
}


void CExRabbitDlg::OnPicMenuLinkTo()
{
	// TODO: 此项作废
}


void CExRabbitDlg::OnPicMenuHide()
{
	// TODO: 在此添加命令处理程序代码
	int pos = m_lPicture.GetSelectionMark();
	PICinfo pi;
	stream s;
	io.PICempty(s, pi);
	io.PICreplace(pos, pi, s);
	MessageBox(L"已将选定贴图隐藏！",L"提示喵");
}


void CExRabbitDlg::OnPicMenu2ExtractAllPng()
{
	// TODO: 此项作废
}


void CExRabbitDlg::OnPicMenu2ExtractAllIndex()
{
	// TODO: 此项作废
}


void CExRabbitDlg::OnPicMenu2Insert()
{
	// TODO: 在此添加命令处理程序代码
	OnPicMenuInsert();
}


void CExRabbitDlg::OnDdsMenuExtractPng()
{
	// TODO: 在此添加命令处理程序代码
	int row = m_lDDS.GetSelectionMark();
	if(row == -1){
		return;
	}
	str fn;
	CString fileName;
	fileName = getOutPutDir(fileIMGname)+L"DDS贴图"+NumToCStr(row)+L".PNG";
	CStrToStr(fileName, fn);
	matrix mat;
	io.DDSextract(row, mat);
	mat.makePNG(fn);
	mat.release();
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}


void CExRabbitDlg::OnDdsMenuExtractAllPng()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(extractDDSPNGThread, (PVOID)this);
}


void CExRabbitDlg::OnDdsMenuExtractDds()
{
	// TODO: 在此添加命令处理程序代码
	int row = m_lDDS.GetSelectionMark();
	if(row == -1){
		return;
	}
	str fn;
	CString fileName;
	fileName = getOutPutDir(fileIMGname)+L"DDS贴图"+NumToCStr(row)+L".dds";
	CStrToStr(fileName, fn);
	matrix mat;
	io.DDSextract(row, mat);
	mat.makePNG(fn);
	mat.release();
	MessageBox(L"已保存为"+fileName+L"。",L"提示喵");
}


void CExRabbitDlg::OnDdsMenuExtractAllDds()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnDdsMenuInsert()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnDdsMenuRemove()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnDdsMenuReplace()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnDdsMenu2ExtractAllPng()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnDdsMenu2ExtractAllDds()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnDdsMenu2Insert()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrMenuInsert()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrmenuRemove()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrMenuReplace()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrMenuExtractPalette()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrMenuExtractAllPalette()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrMenu2Insert()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrMenu2ExtractPalette()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnClrMenu2ExtractAllPalette()
{
	// TODO: 在此添加命令处理程序代码
}


void CExRabbitDlg::OnDisplayMenuSwitchAbs()
{
	// TODO: 在此添加命令处理程序代码
	dispModeAbs = !dispModeAbs;
	draw();
}


void CExRabbitDlg::OnDisplayMenuAutoFind()
{
	// TODO: 在此添加命令处理程序代码
	int row = m_lPicture.GetSelectionMark();
	if(row<0)
		return;
	switch(dispModeAbs){
	case true:
		basePoint.set_X(-io.PICcontent[row].get_basePt().get_X());
		basePoint.set_Y(-io.PICcontent[row].get_basePt().get_Y());
		m_edX.SetWindowText(NumToCStr(basePoint.get_X()));
		m_edY.SetWindowText(NumToCStr(basePoint.get_Y()));
		break;
	default:
		break;
	}
	draw();
}


void CExRabbitDlg::OnDisplayMenuSwitchIndex()
{
	// TODO: 在此添加命令处理程序代码
	dispModeIndex = !dispModeIndex;
	draw();
}


void CExRabbitDlg::OnDisplayMenuSwitchDds()
{
	// TODO: 在此添加命令处理程序代码
	dispModeDds = !dispModeDds;
	draw();
}


void CExRabbitDlg::OnDisplayMenuColorTab()
{
	// TODO: 在此添加命令处理程序代码
	dispSwColorTab = !dispSwColorTab;
	draw();
}


void CExRabbitDlg::OnDisplayMenuPicBound()
{
	// TODO: 在此添加命令处理程序代码
	dispSwPicBound = !dispSwPicBound;
	draw();
}


void CExRabbitDlg::OnDisplayMenuFrmBound()
{
	// TODO: 在此添加命令处理程序代码
	dispSwFrmBound = !dispSwFrmBound;
	draw();
}


void CExRabbitDlg::OnDisplayMenuBaseAxis()
{
	// TODO: 在此添加命令处理程序代码
	dispSwAxis = !dispSwAxis;
	draw();
}


void CExRabbitDlg::OnDisplayMenuGrid()
{
	// TODO: 在此添加命令处理程序代码
	dispSwGrid = !dispSwGrid;
	draw();
}


void CExRabbitDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	MessageBox(L"不许按回车喵！",L"提示喵");
}
