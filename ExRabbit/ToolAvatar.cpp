// ToolAvatar.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatar.h"
#include "afxdialogex.h"
#include "ExRabbitdlg.h"

// CToolAvatar 对话框

IMPLEMENT_DYNAMIC(CToolAvatar, CDialogEx)

CToolAvatar::CToolAvatar(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolAvatar::IDD, pParent)
{

}

CToolAvatar::~CToolAvatar()
{
}

void CToolAvatar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cType);
	DDX_Control(pDX, IDC_COMBO3, m_cPart1);
	DDX_Control(pDX, IDC_COMBO4, m_cPart2);
	DDX_Control(pDX, IDC_COMBO5, m_cPart3);
	DDX_Control(pDX, IDC_COMBO6, m_cPart4);
	//  DDX_Control(pDX, IDC_COMBO7, m_cPart6);
	DDX_Control(pDX, IDC_COMBO7, m_cPart5);
	DDX_Control(pDX, IDC_COMBO8, m_cPart6);
	DDX_Control(pDX, IDC_COMBO9, m_cPart7);
	DDX_Control(pDX, IDC_COMBO10, m_cPart8);
	DDX_Control(pDX, IDC_COMBO11, m_cPart9);
	DDX_Control(pDX, IDC_COMBO12, m_cPart10);
	DDX_Control(pDX, IDC_COMBO14, m_cPalette1);
	DDX_Control(pDX, IDC_COMBO15, m_cPalette2);
	DDX_Control(pDX, IDC_COMBO16, m_cPalette3);
	DDX_Control(pDX, IDC_COMBO17, m_cPalette4);
	DDX_Control(pDX, IDC_COMBO18, m_cPalette5);
	DDX_Control(pDX, IDC_COMBO19, m_cPalette6);
	DDX_Control(pDX, IDC_COMBO20, m_cPalette7);
	DDX_Control(pDX, IDC_COMBO21, m_cPalette8);
	DDX_Control(pDX, IDC_COMBO22, m_cPalette9);
	DDX_Control(pDX, IDC_COMBO23, m_cPalette10);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_PROGRESS1, m_p1);
	DDX_Control(pDX, IDC_COMBO13, m_cPart13);
}


BEGIN_MESSAGE_MAP(CToolAvatar, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolAvatar::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CToolAvatar::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CToolAvatar::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CToolAvatar::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CToolAvatar::OnCbnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CToolAvatar::OnCbnSelchangeCombo6)
	ON_CBN_SELCHANGE(IDC_COMBO7, &CToolAvatar::OnCbnSelchangeCombo7)
	ON_CBN_SELCHANGE(IDC_COMBO8, &CToolAvatar::OnCbnSelchangeCombo8)
	ON_CBN_SELCHANGE(IDC_COMBO9, &CToolAvatar::OnCbnSelchangeCombo9)
	ON_CBN_SELCHANGE(IDC_COMBO10, &CToolAvatar::OnCbnSelchangeCombo10)
	ON_CBN_SELCHANGE(IDC_COMBO11, &CToolAvatar::OnCbnSelchangeCombo11)
	ON_CBN_SELCHANGE(IDC_COMBO12, &CToolAvatar::OnCbnSelchangeCombo12)
	ON_BN_CLICKED(IDC_BUTTON15, &CToolAvatar::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolAvatar::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CToolAvatar::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO14, &CToolAvatar::OnCbnSelchangeCombo14)
	ON_CBN_SELCHANGE(IDC_COMBO15, &CToolAvatar::OnCbnSelchangeCombo15)
	ON_CBN_SELCHANGE(IDC_COMBO16, &CToolAvatar::OnCbnSelchangeCombo16)
	ON_CBN_SELCHANGE(IDC_COMBO17, &CToolAvatar::OnCbnSelchangeCombo17)
	ON_CBN_SELCHANGE(IDC_COMBO18, &CToolAvatar::OnCbnSelchangeCombo18)
	ON_CBN_SELCHANGE(IDC_COMBO19, &CToolAvatar::OnCbnSelchangeCombo19)
	ON_CBN_SELCHANGE(IDC_COMBO20, &CToolAvatar::OnCbnSelchangeCombo20)
	ON_CBN_SELCHANGE(IDC_COMBO21, &CToolAvatar::OnCbnSelchangeCombo21)
	ON_CBN_SELCHANGE(IDC_COMBO22, &CToolAvatar::OnCbnSelchangeCombo22)
	ON_CBN_SELCHANGE(IDC_COMBO23, &CToolAvatar::OnCbnSelchangeCombo23)
	ON_BN_CLICKED(IDC_BUTTON14, &CToolAvatar::OnBnClickedButton14)
	ON_BN_CLICKED(IDCANCEL, &CToolAvatar::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO13, &CToolAvatar::OnCbnSelchangeCombo13)
END_MESSAGE_MAP()


// CToolAvatar 消息处理程序
BOOL CToolAvatar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cType.ResetContent();
	m_cType.AddString(L"未选择");
	m_cType.AddString(L"鬼剑士");
	m_cType.AddString(L"鬼剑士(女)");
	m_cType.AddString(L"格斗家");
	m_cType.AddString(L"格斗家(男)");
	m_cType.AddString(L"神枪手");
	m_cType.AddString(L"神枪手(女)");
	m_cType.AddString(L"魔法师");
	m_cType.AddString(L"魔法师(男)");
	m_cType.AddString(L"圣职者");
	m_cType.AddString(L"圣职者(女)");
	m_cType.AddString(L"暗夜使者");
	m_cType.AddString(L"守护者");
	m_cType.AddString(L"魔枪士");
	m_cType.AddString(L"枪剑士");
	m_cType.SetCurSel(0);
	cbPart[0] = &m_cPart1;
	cbPart[1] = &m_cPart2;
	cbPart[2] = &m_cPart3;
	cbPart[3] = &m_cPart4;
	cbPart[4] = &m_cPart5;
	cbPart[5] = &m_cPart6;
	cbPart[6] = &m_cPart7;
	cbPart[7] = &m_cPart8;
	cbPart[8] = &m_cPart9;
	cbPart[9] = &m_cPart10;
	cbPalette[0] = &m_cPalette1;
	cbPalette[1] = &m_cPalette2;
	cbPalette[2] = &m_cPalette3;
	cbPalette[3] = &m_cPalette4;
	cbPalette[4] = &m_cPalette5;
	cbPalette[5] = &m_cPalette6;
	cbPalette[6] = &m_cPalette7;
	cbPalette[7] = &m_cPalette8;
	cbPalette[8] = &m_cPalette9;
	cbPalette[9] = &m_cPalette10;
	m_p1.SetRange32(0,1000);
	
	drawing = 0;
	frmID = 0;

	m_cPart13.ResetContent();
	m_cPart13.AddString(L"选择动作");
	m_cPart13.AddString(L"站立(平常)");
	m_cPart13.AddString(L"站立(备战)");
	m_cPart13.AddString(L"走路");
	m_cPart13.AddString(L"跑动");
	m_cPart13.AddString(L"跳跃");
	m_cPart13.AddString(L"普通攻击");
	m_cPart13.AddString(L"Z键攻击");
	m_cPart13.AddString(L"释放");
	m_cPart13.AddString(L"被攻击");
	m_cPart13.AddString(L"倒地");
	m_cPart13.SetCurSel(0);

	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	m_e1.SetWindowText(dlg->imPack2Dir);

	for(int i = 0;i<AVATAR_MAX_LAYER_COUNT;i++){
		layer[i].allocate(200,200);
		layer[i].fill(0);
		pltID[i] = 0;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CToolAvatar::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND hwnd= GetSafeHwnd();   //得到窗口句柄
	CString filePath= L"";	//得到文件路径
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//取得IMalloc分配器接口
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("选择文件夹");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//取得IMalloc分配器接口   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //获得一个文件系统路径
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//释放内存
			if(filePath.GetLength()<=1){
				MessageBox(L"并不是有效的文件夹喵！",L"提示喵");
			}else{
				m_e1.SetWindowText(filePath);
				m_cType.SetCurSel(0);
			}
		}
		pMalloc->Release();	//释放接口
	}
}


void CToolAvatar::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(loadNPKThread, (PVOID)this);

}
void CToolAvatar::draw(){
	AfxBeginThread(drawThread_av, (PVOID)this);
}
void CToolAvatar::updateIMG(int cb){
	//修改ioList
	int i;
	str sufStr;
	for(i=0;i<AVATAR_MAX_LAYER_COUNT;i++){
		//如果该部件的大部件对应
		KoishiTitle::mainPartElem mp = KoishiTitle::mixSeqList[i].mainPart;
		KoishiTitle::subPartElem sp = KoishiTitle::mixSeqList[i].subPart;
		int si = KoishiTitle::mixSeqList[i].subPartID;
		if(1 + cb == (int)mp){
			//如果这个图层属于这个部件·更新IMG
			cbPart[cb]->GetLBText(cbPart[cb]->GetCurSel(), ioSuffix[cb]);
			CStrToStr(ioSuffix[cb], sufStr);
			//TRACE(ioSuffix[cb]);
			bool findResult;
			unsigned long pos;
			if(ioSuffix[cb].Left(4) != L"(tn)"){
				//如果组合框里不带有(tn)字样
				findResult = noList[cb].IMGfind(sufStr+KoishiTitle::GetAvatarSubPartString(sp), "(tn)", pos);
			}else{
				//如果组合框里带有(tn)字样
				findResult = noList[cb].IMGfind(sufStr+KoishiTitle::GetAvatarSubPartString(sp), pos);
			}
			//TRACE(NumToCStr(i)+L":"+StrToCStr(sufStr+KoishiTitle::GetAvatarSubPartString(sp))+(findResult?L":Y\n":L":N\n"));
			if(findResult){
				//若找到了这个图层对应的IMG
				ioList[i].release();
				noList[cb].IMGextract(pos, ioList[i]);
				ioName[i] = noList[cb].content[pos].get_imgname();
				//更新调色板组合框
				cbPalette[cb]->ResetContent();
				if(ioList[i].version == V6){
					cbPalette[cb]->EnableWindow(true);
					for(int j = 0;j<ioList[i].paletteData.getCount();j++){
						cbPalette[cb]->AddString(L"P"+NumToCStr(j));
					}
				}else{
					cbPalette[cb]->EnableWindow(false);
					cbPalette[cb]->AddString(L"非V6");
				}
				//调色板默认置零
				cbPalette[cb]->SetCurSel(0);
				pltID[i] = 0;
			}else{
				//若找不到
				ioList[i].release();
			}
		}
	}
}
void CToolAvatar::updateByPalette(int cb){
	int i;
	for(i=0;i<AVATAR_MAX_LAYER_COUNT;i++){
		//取每个图层应属于的部件和子部件
		KoishiTitle::mainPartElem mp = KoishiTitle::mixSeqList[i].mainPart;
		if(1 + cb == (int)mp){
			pltID[i] = cbPalette[cb]->GetCurSel();
		}
		//TRACE(NumToCStr(pltID[i]));

	}
	//TRACE(L"\n");
}
void CToolAvatar::updateByFrame(int frame){
	for(int i=0;i<9;i++){
		updateMatrix(i);
	}
}
void CToolAvatar::updateMatrix(int cb){
	int i;
	//TRACE(NumToCStr(cb)+L"=====\n");
	for(i=0;i<AVATAR_MAX_LAYER_COUNT;i++){
		//取每个图层应属于的部件和子部件
		KoishiTitle::mainPartElem mp = KoishiTitle::mixSeqList[i].mainPart;
		if(1 + cb == (int)mp){
			//如果这个图层属于这个部件
			layer[i].fill(0);
			//TRACE(NumToCStr(i)+L":V"+NumToCStr((int)ioList[i].version)+L"\n");
			if(ioList[i].version == VUDEF){
				//如果不存在（例如这个图层对应的部件或子部件不存在导致的IMG对象未被分配）则空建矩阵
				continue;
			}
			//存在则计算矩阵
			PICinfo pi;
			matrix matTemp;
			color clr;
			int plt = pltID[i];			//取调色板
			int frmID2, tx, ty, m, n;		//帧号
			ioList[i].PICgetInfo(frmID, pi);
			if(pi.get_format() == LINK){
				frmID2 = ioList[i].linkFind(frmID);	//指向帧修正
			}else{
				frmID2 = frmID;
			}
			ioList[i].PICgetInfo(frmID2, pi);		//取帧信息
			if(ioList[i].version == V5 || ioList[i].version == V4 || plt<0){
				plt = 0;
			}
			ioList[i].PICextract(frmID2, matTemp, plt);		//提取矩阵
			//平移
			for(m=0;m<200;m++){
				for(n=0;n<200;n++){
					tx = m-pi.get_basePt().get_Y()-basePoint.get_Y();	//真实坐标
					ty = n-pi.get_basePt().get_X()-basePoint.get_X();	//真是坐标
					if(tx>=0 && ty>=0 && tx<matTemp.getRowCount() && ty<matTemp.getColumnCount()){
						clr = matTemp.getElem(tx,ty);
						clr.mixWith(layer[i].getElem(m,n),LAY);
						layer[i].setElem(m, n, clr);
					}
				}
			}
			//layer[i].makePNG("test.png");
			//matTemp.makePNG("test2.png");
			//TRACE(NumToCStr(i)+L":"+NumToCStr(plt)+L"\n");
			matTemp.release();
		}
	}
}
void CToolAvatar::getCanvas(matrix &mat){
	mat.release();
	mat.allocate(200,200);
	mat.fill(color(0xff,0x33,0x33,0x33));
	int i,m,n;
	color clr;
	for(m=0;m<200;m++){
		for(n=0;n<200;n++){
			clr = mat.getElem(m,n);
			for(i=63;i>=0;i--){
				if(layer[i].valid()){
					if(layer[i].getElem(m,n).get_A() != 0){
						clr = layer[i].getElem(m,n);
					//TRACE(NumToCStr(i)+L":"+ClrToCStr(clr)+L"\n");
					}
				}
			}
			mat.setElem(m,n,clr);
		}
	}
}
UINT CToolAvatar::loadNPKThread(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	KoishiTitle::charElem ch = (KoishiTitle::charElem)dlg->m_cType.GetCurSel();
	CString path;
	str pathStr, fileStr, imgNameStr;
	dlg->m_e1.GetWindowText(path);
	dlg->m_p1.SetPos(0);
	int i,j;
	li32 idList;		//每个NPK所含的ID值列表
	lb8 tnList;			//每个NPK所含的ID值列表对应是否含有(tn)
	KoishiTitle::avatar av;
	CStrToStr(path+L"\\", pathStr);
	for(i=0;i<9;i++){
		fileStr = KoishiTitle::GetAvatarNPKFileName(ch, (KoishiTitle::mainPartElem)(i+1));
		dlg->noList[i].release();
		dlg->cbPart[i]->ResetContent();
		dlg->cbPart[i]->AddString(L"读取中");
		dlg->cbPart[i]->SetCurSel(0);
		if(!dlg->noList[i].loadFile(pathStr + fileStr)){
			dlg->cbPart[i]->DeleteString(0);
			dlg->cbPart[i]->AddString(L"无");
			dlg->cbPart[i]->SetCurSel(0);
			continue;
		}
		//读取ID列表
		idList.clear();
		tnList.clear();
		for(j=0;j<dlg->noList[i].count;j++){
			if(!av.useName(KoishiTitle::shorten(dlg->noList[i].content[j].get_imgname())))
				continue;
			if(idList.size() == 0 || idList[idList.size()-1] != av.mainPartID){
				idList.push_back(av.mainPartID);
				tnList.push_back(av.isTN?1:0);
			}
		}
		//给组合框添加ID列表
		for(j=0;j<idList.size();j++){
			imgNameStr = (tnList[j]==1)?"(tn)":"";
			imgNameStr += KoishiTitle::GetAvatarIMG_Fmt_CH_XXXX(ch, (KoishiTitle::mainPartElem)(i+1));
			imgNameStr += KoishiTitle::avaFmt(idList[j]);
			//小部件之后的内容不加，便于查找即可
			dlg->cbPart[i]->AddString(StrToCStr(imgNameStr));
		}
		//将第一个设置为“无”
		dlg->cbPart[i]->DeleteString(0);
		dlg->cbPart[i]->InsertString(0,L"无");
		dlg->cbPart[i]->SetCurSel(0);
		dlg->ioSuffix[i] = L"无";
		if(dlg->cbPart[i]->GetCount()>1){
			if(i == 8){
				//如果是skin，设置基准点
				IMGobject io;
				if(dlg->noList[i].IMGextract(0, io)){
					dlg->basePoint.set_X(100-io.PICcontent[0].get_basePt().get_X()-io.PICcontent[0].get_picSize().get_W()/2);
					dlg->basePoint.set_Y(100-io.PICcontent[0].get_basePt().get_Y()-io.PICcontent[0].get_picSize().get_H()/2);
					io.release();
				}else{
					dlg->basePoint = point(0,0);
				}
			}
			dlg->cbPart[i]->SetCurSel(1);
			dlg->cbPart[i]->GetLBText(1, dlg->ioSuffix[i]);
			dlg->cbPalette[i]->SetCurSel(0);
			dlg->updateIMG(i);
		}
		dlg->m_p1.SetPos(i*1000/9);
	}
	dlg->m_p1.SetPos(1000);
	for(i=0;i<9;i++){
		dlg->updateMatrix(i);
	}
	dlg->draw();
	return 0;
}

UINT CToolAvatar::drawThread_av(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	if(dlg->drawing){
		return 0;
	}
	dlg->drawing = 1;
	int i,j,k;
	int canw= 200;
	int canh = 200;

	matrix mat;
	dlg->getCanvas(mat);
	CImage img;
	img.Create(canw, canh, 32);
	img.SetHasAlphaChannel(true);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = dlg->GetDC();
	for(i=0;i<canw;i++){
		for(j=0;j<canh;j++){
			*(pst + pit*j + 4*i + 0) = mat[j][i].get_B()*mat[j][i].get_A()/0xff;
			*(pst + pit*j + 4*i + 1) = mat[j][i].get_G()*mat[j][i].get_A()/0xff;
			*(pst + pit*j + 4*i + 2) = mat[j][i].get_R()*mat[j][i].get_A()/0xff;
			*(pst + pit*j + 4*i + 3) = mat[j][i].get_A();
		}
	}
	//TRACE(L"d_"+NumToCStr(drawID)+L"\n");
	img.Draw(pDC->m_hDC,235,41);
	dlg->ReleaseDC(pDC);
	dlg->drawing = 0;
	return 0;
}

void CToolAvatar::OnCbnSelchangeCombo3()
{
	// TODO: 第一部件
	updateIMG(0);
	updateMatrix(0);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(1);
	updateMatrix(1);
	draw();
}
	



void CToolAvatar::OnCbnSelchangeCombo5()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(2);
	updateMatrix(2);
	draw();
	
}


void CToolAvatar::OnCbnSelchangeCombo6()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(3);
	updateMatrix(3);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo7()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(4);
	updateMatrix(4);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo8()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(5);
	updateMatrix(5);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo9()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(6);
	updateMatrix(6);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo10()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(7);
	updateMatrix(7);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo11()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(8);
	updateMatrix(8);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo12()
{
	// TODO: 在此添加控件通知处理程序代码
	updateIMG(9);
	updateMatrix(9);
	draw();
}


void CToolAvatar::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"只要指定文件夹即可以使用的纸娃娃系统。\r\bn允许按照时装ID浏览时装效果，也可以将浏览的时装添加到EX里进行编辑。\r\n --By kfu(colg)");
}


void CToolAvatar::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	frmID--;
	if(frmID<0)
		frmID = 0;
	updateByFrame(frmID);
	draw();
}


void CToolAvatar::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	IMGobject io;
	if(!noList[KoishiTitle::mp_skin-1].IMGextract(0,io)){
		MessageBox(L"当前皮肤NPK文件未识别，因而无法识别帧数。",L"提示喵");
		return;
	}
	frmID++;
	if(frmID>io.indexCount-1)
		frmID = io.indexCount-1;
	updateByFrame(frmID);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo14()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(0);
	updateMatrix(0);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo15()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(1);
	updateMatrix(1);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo16()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(2);
	updateMatrix(2);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo17()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(3);
	updateMatrix(3);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo18()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(4);
	updateMatrix(4);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo19()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(5);
	updateMatrix(5);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo20()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(6);
	updateMatrix(6);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo21()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(7);
	updateMatrix(7);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo22()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(8);
	updateMatrix(8);
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo23()
{
	// TODO: 在此添加控件通知处理程序代码
	updateByPalette(9);
	updateMatrix(9);
	draw();
}


void CToolAvatar::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	dlg->no.release();
	dlg->no.create();
	dlg->fileNPKname = L"newNPK.npk";
	dlg->saveAlert = false;
	for(int i = 0;i<64;i++){
		if(ioList[i].version != VUDEF)
		dlg->no.IMGinsert(0, ioList[i], ioName[i]);
	}
	MessageBox(L"已经将有效IMG都弄到EX里了喵！",L"提示喵");
	dlg->updateIMGlist();
	dlg->updateNPKInfo();
}


void CToolAvatar::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}


void CToolAvatar::OnCbnSelchangeCombo13()
{
	// TODO: 在此添加控件通知处理程序代码
	int m[14][11] = {
		{0,176,125,180,105,127,13,50,82,96,102},
		{0,1,9,15,151,38,205,78,136,140,143},
		{0,113,132,136,40,48,6,14,92,78,81},
		{0,1,12,7,137,25,17,66,84,75,78},
		{0,1,20,55,108,64,27,36,197,122,127},
		{0,1,20,70,76,94,23,29,12,90,91},
		{0,11,14,0,18,78,110,118,146,129,134},
		{0,1,14,22,30,46,90,63,145,176,179},
		{0,1,4,70,76,90,8,36,150,123,126},
		{0,1,9,16,23,49,161,44,117,52,55},
		{0,1,12,20,61,48,71,109,38,92,95},
		{0,1,6,15,24,32,56,190,178,196,199},
		{0,1,4,12,20,44,148,126,159,176,179},
		{0,0,0,0,0,0,0,0,0,0,0}
	}; 
	frmID = m[(m_cType.GetCurSel()-1)%14][m_cPart13.GetCurSel()%11];
	IMGobject io;
	if(!noList[KoishiTitle::mp_skin-1].IMGextract(0,io)){
		MessageBox(L"当前皮肤NPK文件未识别，因而无法动作。",L"提示喵");
		return;
	}
	if(frmID>io.indexCount-1)
		frmID = io.indexCount-1;
	updateByFrame(frmID);
	draw();
}
