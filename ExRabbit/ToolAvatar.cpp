// ToolAvatar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolAvatar.h"
#include "afxdialogex.h"
#include "ExRabbitdlg.h"

// CToolAvatar �Ի���

IMPLEMENT_DYNAMIC(CToolAvatar, CDialogEx)

CToolAvatar::CToolAvatar(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolAvatar::IDD, pParent)
{

}

CToolAvatar::~CToolAvatar()
{
}

CString CToolAvatar::LoadStringToOutput(__in UINT id) {
	CString output;
	output.LoadStringW(id);
	return output;
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


// CToolAvatar ��Ϣ�������
CString CToolAvatar::GetRequestNPK(KoishiTitle::charElem ch, KoishiTitle::mainPartElem pt){
	CString fix1 = L"sprite_character_";
	CString fix2[14] = {
		L"_",
		L"swordman_",
		L"swordman_at",
		L"fighter_",
		L"fighter_at",
		L"gunner_",
		L"gunner_at",
		L"mage_",
		L"mage_at",
		L"priest_",
		L"priest_at",
		L"thief_",
		L"knight_",
		L"demoniclancer_"
	};
	CString fix3 = L"equipment_avatar_";
	CString fix4[10] = {
		L"",
		L"cap",
		L"hair",
		L"face",
		L"neck",
		L"coat",
		L"pants",
		L"belt",
		L"shoes",
		L"skin"
	};
	CString fix5 = L".NPK";
	return fix1+fix2[ch]+fix3+fix4[pt]+fix5;
}
BOOL CToolAvatar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_cType.ResetContent();
	/*
	m_cType.AddString(L"δѡ��");
	m_cType.AddString(L"��ʿ");
	m_cType.AddString(L"��ʿ(Ů)");
	m_cType.AddString(L"�񶷼�");
	m_cType.AddString(L"�񶷼�(��)");
	m_cType.AddString(L"��ǹ��");
	m_cType.AddString(L"��ǹ��(Ů)");
	m_cType.AddString(L"ħ��ʦ");
	m_cType.AddString(L"ħ��ʦ(��)");
	m_cType.AddString(L"ʥְ��");
	m_cType.AddString(L"ʥְ��(Ů)");
	m_cType.AddString(L"��ҹʹ��");
	m_cType.AddString(L"�ػ���");
	m_cType.AddString(L"ħǹʿ");
	*/
	m_cType.AddString(LoadStringToOutput(IDS_STRING_NOTSELECTED));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_SWORDMANM));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_SWORDMANF));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_FIGHTERF));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_FIGHTERM));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_GUNNERM));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_GUNNERF));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_MAGEF));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_MAGEM));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_PRIESTM));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_PRIESTF));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_THIEF));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_KNIGHT));
	m_cType.AddString(LoadStringToOutput(IDS_STRING_DEMONICLANCER));
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
	m_e1.SetWindowText(L"K:\\ImagePacks2");
	m_p1.SetRange32(0,1000);
	
	canvas.allocate(220,220);
	drawing = 0;
	frmID = 0;
	imgCount = 0;

	m_cPart13.ResetContent();
	/*
	m_cPart13.AddString(L"ѡ����");
	m_cPart13.AddString(L"վ��(ƽ��)");
	m_cPart13.AddString(L"վ��(��ս)");
	m_cPart13.AddString(L"��·");
	m_cPart13.AddString(L"�ܶ�");
	m_cPart13.AddString(L"��Ծ");
	m_cPart13.AddString(L"��ͨ����");
	m_cPart13.AddString(L"Z������");
	m_cPart13.AddString(L"�ͷ�");
	m_cPart13.AddString(L"������");
	m_cPart13.AddString(L"����");
	*/
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_SELECTACTION));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_REST));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_FIGHT));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_WALK));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_RUN));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_JUMP));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_ATTACK));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_ZSKILL));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_CAST));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_DAMAGED));
	m_cPart13.AddString(LoadStringToOutput(IDS_STRING_FALLDOWN));
	m_cPart13.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CToolAvatar::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND hwnd= GetSafeHwnd();   //�õ����ھ��
	CString filePath= L"";	//�õ��ļ�·��
	CString tra, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){	//ȡ��IMalloc�������ӿ�
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		tra.LoadStringW(IDS_STRING_SELECTFOLDER);
		bi.lpszTitle = tra;
		//bi.lpszTitle = _T("ѡ���ļ���");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){//ȡ��IMalloc�������ӿ�   
			if(::SHGetPathFromIDList(pidl, pszBuffer)){ //���һ���ļ�ϵͳ·��
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);	//�ͷ��ڴ�
			if(filePath.GetLength()<=1){
				tra.LoadStringW(IDS_STRING_NOTAVAILABLEFOLDER);
				MessageBox(tra, title);
				//MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				m_e1.SetWindowText(filePath);
				m_cType.SetCurSel(0);
			}
		}
		pMalloc->Release();	//�ͷŽӿ�
	}
}


void CToolAvatar::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxBeginThread(loadNPKThread, (PVOID)this);

}
void CToolAvatar::draw(){
	AfxBeginThread(drawThread_av, (PVOID)this);
}
UINT CToolAvatar::loadNPKThread(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	KoishiTitle::charElem ch = (KoishiTitle::charElem)dlg->m_cType.GetCurSel();
	CString path;
	CString tra;
	str fn;
	dlg->m_e1.GetWindowText(path);
	dlg->m_p1.SetPos(0);
	int i,j;
	li32 idList;
	lb8 tnList;
	KoishiTitle::avatar av;
	CString charStr[14] = {L"",L"sm",L"sg",L"ft",L"fm",L"gn",L"gg",L"mg",L"mm",L"pr",L"pg",L"th",L"kn",L"dl"};
	CString partStr[10] = {L"cap",L"hair",L"face",L"neck",L"coat",L"pants",L"belt",L"shoes",L"body",L"weapon"};
	for(i=0;i<9;i++){
		CStrToStr(path+L"\\"+GetRequestNPK(ch,(KoishiTitle::mainPartElem)(i+1)),fn);
		dlg->noList[i].release();
		dlg->cbPart[i]->ResetContent();
		tra.LoadStringW(IDS_STRING_READING);
		dlg->cbPart[i]->AddString(tra);
		//dlg->cbPart[i]->AddString(L"��ȡ��");
		dlg->cbPart[i]->SetCurSel(0);
		if(!dlg->noList[i].loadFile(fn)){
			dlg->cbPart[i]->DeleteString(0);
			tra.LoadStringW(IDS_STRING_NULL);
			dlg->cbPart[i]->AddString(tra);
			//dlg->cbPart[i]->AddString(L"��");
			dlg->cbPart[i]->SetCurSel(0);
			continue;
		}
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
		for(j=0;j<idList.size();j++){
			dlg->cbPart[i]->AddString(((tnList[j]==1)?L"(tn)":L"")+charStr[ch]+L"_"+partStr[i]+StrToCStr(KoishiTitle::avaFmt(idList[j])));
		}
		dlg->cbPart[i]->DeleteString(0);
		tra.LoadStringW(IDS_STRING_NULL);
		dlg->cbPart[i]->InsertString(0,tra);
		//dlg->cbPart[i]->InsertString(0,L"��");
		dlg->cbPart[i]->SetCurSel(0);
		tra.LoadStringW(IDS_STRING_NULL);
		dlg->ioSuffix[i] = tra;
		//dlg->ioSuffix[i] = L"��";
		if(dlg->cbPart[i]->GetCount()>1){
			dlg->cbPart[i]->SetCurSel(1);
			dlg->cbPart[i]->GetLBText(1, dlg->ioSuffix[i]);	//����
		}
		dlg->m_p1.SetPos(i*1000/9);
	}
	dlg->m_p1.SetPos(1000);
	dlg->OnCbnSelchangeCombo11();
	return 0;
}
UINT CToolAvatar::drawThread_av(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	if(dlg->drawing){
		return 0;
	}
	dlg->drawing = 1;
	int i,j,k;
	int canw= 220;
	int canh = 220;
	dlg->imgCount = 0;
	b32 temp;
	str imgn;
	CString strSp[10] = {L"",L"a",L"b",L"c",L"d",L"e",L"f",L"g",L"h",L"x"};
	for(k=0;k<55;k++){
		//55ͼ��
		KoishiTitle::mixSeqElem mse = KoishiTitle::mixSeqList[k];
		KoishiTitle::mainPartElem mpe = mse.mainPart;//mpe=0Ϊδ����
		KoishiTitle::subPartElem spe = mse.subPart;//spe=0Ϊ""���޺�׺
		CStrToStr(dlg->ioSuffix[mpe-1]+strSp[spe%10], imgn);
		if(dlg->noList[mpe-1].IMGfind(imgn, temp)){
			TRACE(dlg->ioSuffix[mpe-1]+strSp[spe%10]+L"\n");
			dlg->ioList[dlg->imgCount].Release();
			dlg->noList[mpe-1].IMGextract(temp, dlg->ioList[dlg->imgCount]);
			dlg->pltID[dlg->imgCount] = dlg->cbPalette[mpe-1]->GetCurSel();
			dlg->ioName[dlg->imgCount] = dlg->noList[mpe-1].content[temp].get_imgname();
			dlg->imgCount ++ ;
		}
	}
	dlg->preLoaded = true;		//��ʼ״̬����һ�����ݵ�����״̬Ϊtrue����ʼִ�е������Ϊfalse
	for(k=0;k<dlg->imgCount+1;k++){
		dlg->preDrawed[k] = false;
	}
	AfxBeginThread(drawThread_bg, para);
	for(k=0;k<dlg->imgCount;k++){
		while(!dlg->preLoaded);			//��һ�׶θ�ֵʱ��һ�׶α���Ϊtrue������ȴ���
		dlg->imgDrawing = dlg->imgCount-k-1;		//�Ӻ���ǰ��
		dlg->preLoaded = false;
		AfxBeginThread(drawThread_fg, para);
	}
	while(!dlg->preDrawed[0]);
	CImage img;
	img.Create(canw, canh, 32);
	img.SetHasAlphaChannel(true);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	for(i=0;i<canw;i++){
		for(j=0;j<canh;j++){
			*(pst + pit*j + 4*i + 0) = dlg->canvas[j][i].get_B()*dlg->canvas[j][i].get_A()/0xff;
			*(pst + pit*j + 4*i + 1) = dlg->canvas[j][i].get_G()*dlg->canvas[j][i].get_A()/0xff;
			*(pst + pit*j + 4*i + 2) = dlg->canvas[j][i].get_R()*dlg->canvas[j][i].get_A()/0xff;
			*(pst + pit*j + 4*i + 3) = dlg->canvas[j][i].get_A();
		}
	}
	//TRACE(L"d_"+NumToCStr(drawID)+L"\n");
	img.Draw(dlg->GetDC()->m_hDC,235,41);
	dlg->drawing = 0;
	return 0;
}
UINT CToolAvatar::drawThread_bg(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	//����ǰ��
	dlg->canvas.fill(color(0xff,0x33,0x33,0x33));
	dlg->preDrawed[dlg->imgCount] = true;
	return 0;
}
UINT CToolAvatar::drawThread_fg(PVOID para){
	CToolAvatar *dlg = (CToolAvatar*)para;
	int drawID = dlg->imgDrawing;
	dlg->preLoaded = true;
	IMGobject io = dlg->ioList[drawID];
	int row = dlg->frmID;
	int cbpro = dlg->pltID[drawID];
	if(cbpro<0)
		cbpro = 0;
	if(row <0)
		row = 0;
	PICinfo po;
	int i,j,k,tx,ty;
	matrix mat;
	color clr;
	//����ǰ��
	int canw = 200;
	int canh = 200;
	//����ͼ
	io.GetPICInfo(row, po);
	if(po.get_format() == LINK)
		row = io.linkFind(row);
	io.GetPICInfo(row, po);
	if(io.version == V5 || io.version == V4)
		cbpro = 0;
	io.PICextract(row, mat, (i32)cbpro);
	while(!dlg->preDrawed[drawID+1]);
	for(i=0;i<canh;i++){
		for(j=0;j<canw;j++){
			tx = i-po.get_basePt().get_Y()-dlg->basePoint.get_Y();	//��ʵ����
			ty = j-po.get_basePt().get_X()-dlg->basePoint.get_X();	//��������
			if(tx<mat.getRowCount() && ty<mat.getColumnCount()){
				clr = mat.getElem(tx,ty);
				clr.mixWith(dlg->canvas.getElem(i,j),LAY);
				dlg->canvas.setElem(i, j, clr);
			}
		}
	}
	dlg->preDrawed[drawID] = true;
	mat.release();
	io.Release();
	return 0;
}

void CToolAvatar::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart1.GetLBText(m_cPart1.GetCurSel(), cs);
	ioSuffix[0] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_cap-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_cap-1].IMGextract(temp, io);
		m_cPalette1.ResetContent();
		if(io.version == V6){
			m_cPalette1.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette1.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette1.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette1.AddString(tra);
			//m_cPalette1.AddString(L"��V6");
		}
		m_cPalette1.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart2.GetLBText(m_cPart2.GetCurSel(), cs);
	ioSuffix[1] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_hair-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_hair-1].IMGextract(temp, io);
		m_cPalette2.ResetContent();
		if(io.version == V6){
			m_cPalette2.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette2.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette2.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette2.AddString(tra);
			//m_cPalette2.AddString(L"��V6");
		}
		m_cPalette2.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart3.GetLBText(m_cPart3.GetCurSel(), cs);
	ioSuffix[2] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_face-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_face-1].IMGextract(temp, io);
		m_cPalette3.ResetContent();
		if(io.version == V6){
			m_cPalette3.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette3.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette3.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette3.AddString(tra);
			//m_cPalette3.AddString(L"��V6");
		}
		m_cPalette3.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart4.GetLBText(m_cPart4.GetCurSel(), cs);
	ioSuffix[3] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_neck-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_neck-1].IMGextract(temp, io);
		m_cPalette4.ResetContent();
		if(io.version == V6){
			m_cPalette4.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette4.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette4.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette4.AddString(tra);
			//m_cPalette4.AddString(L"��V6");
		}
		m_cPalette4.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart5.GetLBText(m_cPart5.GetCurSel(), cs);
	ioSuffix[4] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_coat-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_coat-1].IMGextract(temp, io);
		m_cPalette5.ResetContent();
		if(io.version == V6){
			m_cPalette5.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette5.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette5.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette5.AddString(tra);
			//m_cPalette5.AddString(L"��V6");
		}
		m_cPalette5.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart6.GetLBText(m_cPart6.GetCurSel(), cs);
	ioSuffix[5] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_pants-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_pants-1].IMGextract(temp, io);
		m_cPalette6.ResetContent();
		if(io.version == V6){
			m_cPalette6.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette6.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette6.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette6.AddString(tra);
			//m_cPalette6.AddString(L"��V6");
		}
		m_cPalette6.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart7.GetLBText(m_cPart7.GetCurSel(), cs);
	ioSuffix[6] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_belt-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_belt-1].IMGextract(temp, io);
		m_cPalette7.ResetContent();
		if(io.version == V6){
			m_cPalette7.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette7.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette7.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette7.AddString(tra);
			//m_cPalette7.AddString(L"��V6");
		}
		m_cPalette7.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart8.GetLBText(m_cPart8.GetCurSel(), cs);
	ioSuffix[7] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_shoes-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_shoes-1].IMGextract(temp, io);
		m_cPalette8.ResetContent();
		if(io.version == V6){
			m_cPalette8.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette8.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette8.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette8.AddString(tra);
			//m_cPalette8.AddString(L"��V6");
		}
		m_cPalette8.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart9.GetLBText(m_cPart9.GetCurSel(), cs);
	ioSuffix[8] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_skin-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_skin-1].IMGextract(temp, io);
		basePoint.set_X(100-io.PICcontent[0].get_basePt().get_X()-io.PICcontent[0].get_picSize().get_W()/2);
		basePoint.set_Y(100-io.PICcontent[0].get_basePt().get_Y()-io.PICcontent[0].get_picSize().get_H()/2);
		m_cPalette9.ResetContent();
		if(io.version == V6){
			m_cPalette9.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette9.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette9.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette9.AddString(tra);
			//m_cPalette9.AddString(L"��V6");
		}
		m_cPalette9.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString cs;
	CString tra;
	str imgn;
	b32 temp;
	m_cPart10.GetLBText(m_cPart10.GetCurSel(), cs);
	ioSuffix[9] = cs;
	CStrToStr(cs, imgn);
	if(noList[KoishiTitle::mp_weapon-1].IMGfind(imgn, temp)){
		noList[KoishiTitle::mp_weapon-1].IMGextract(temp, io);
		m_cPalette10.ResetContent();
		if(io.version == V6){
			m_cPalette10.EnableWindow(true);
			for(int i = 0;i<io.paletteData.getCount();i++){
				m_cPalette10.AddString(L"P"+NumToCStr(i));
			}
		}else{
			m_cPalette10.EnableWindow(false);
			tra.LoadStringW(IDS_STRING_NOTV6);
			m_cPalette10.AddString(tra);
			//m_cPalette10.AddString(L"��V6");
		}
		m_cPalette10.SetCurSel(0);
	}
	draw();
}


void CToolAvatar::OnBnClickedButton15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	info.LoadStringW(IDS_STRING_DRESSINGROOMINTRODUCTION);
	MessageBox(info, title);
	//MessageBox(L"ֻҪָ���ļ��м�����ʹ�õ�ֽ����ϵͳ��\r\bn������ʱװID���ʱװЧ����Ҳ���Խ������ʱװ��ӵ�EX����б༭��\r\n --By kfu(colg)");
}


void CToolAvatar::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	frmID--;
	if(frmID<0)
		frmID = 0;
	draw();
}


void CToolAvatar::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMGobject io;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if(!noList[KoishiTitle::mp_skin-1].IMGextract(0,io)){
		info.LoadStringW(IDS_STRING_FRAMENOTRECOGNIZED);
		MessageBox(info, title);
		//MessageBox(L"��ǰƤ��NPK�ļ�δʶ������޷�ʶ��֡����",L"��ʾ��");
		return;
	}
	frmID++;
	if(frmID>io.indexCount-1)
		frmID = io.indexCount-1;
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo16()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo17()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo18()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo19()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo20()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo21()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo22()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnCbnSelchangeCombo23()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw();
}


void CToolAvatar::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg *dlg = (CExRabbitDlg*)GetParent();
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	dlg->no.release();
	dlg->no.create();
	dlg->fileNPKname = L"newNPK.npk";
	dlg->fileOpen = true;
	dlg->mixMode = false;
	dlg->saveAlert = false;
	dlg->dispModeShowAll = false;
	dlg->updateIMGlist();
	for(int i = 0;i<imgCount;i++)
		dlg->no.IMGinsert(0, ioList[i], ioName[i]);
	info.LoadStringW(IDS_STRING_ALLIMPORTED);
	MessageBox(info, title);
	//MessageBox(L"�Ѿ�����ЧIMG��Ū��EX��������",L"��ʾ��");
	dlg->updateIMGlist();
	dlg->updateNPKInfo();
}


void CToolAvatar::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}


void CToolAvatar::OnCbnSelchangeCombo13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	m_cPart13.AddString(L"ѡ����");
	m_cPart13.AddString(L"վ��(ƽ��)");
	m_cPart13.AddString(L"վ��(��ս)");
	m_cPart13.AddString(L"��·");
	m_cPart13.AddString(L"�ܶ�");
	m_cPart13.AddString(L"��Ծ");
	m_cPart13.AddString(L"��ͨ����");
	m_cPart13.AddString(L"Z������");
	m_cPart13.AddString(L"�ͷ�");
	m_cPart13.AddString(L"������");
	m_cPart13.AddString(L"����");
	*/
	int m[13][11] = {
		{0,176,125,180,105,127,13,50,82,96,102},
		{0,0,9,15,151,0,0,0,129,140,143},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}
	}; 
	frmID = m[(m_cType.GetCurSel()-1)%13][m_cPart13.GetCurSel()%11];
	IMGobject io;
	CString info, title;
	title.LoadStringW(IDS_MESSAGE_TITLE);
	if(!noList[KoishiTitle::mp_skin-1].IMGextract(0,io)){
		info.LoadStringW(IDS_STRING_ACTIONNOTRECOGNIZED);
		MessageBox(info, title);
		//MessageBox(L"��ǰƤ��NPK�ļ�δʶ������޷�������",L"��ʾ��");
		return;
	}
	if(frmID>io.indexCount-1)
		frmID = io.indexCount-1;
	draw();
}
