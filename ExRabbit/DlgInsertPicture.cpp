// DlgInsert2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsertPicture.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgInsertPicture �Ի���

IMPLEMENT_DYNAMIC(CDlgInsertPicture, CDialogEx)

CDlgInsertPicture::CDlgInsertPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInsertPicture::IDD, pParent)
{

}

CDlgInsertPicture::~CDlgInsertPicture()
{
}

void CDlgInsertPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
	DDX_Control(pDX, IDC_CHECK2, m_ch2);
	DDX_Control(pDX, IDC_CHECK3, m_ch3);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	DDX_Control(pDX, IDC_EDIT1, m_ed1);
	DDX_Control(pDX, IDC_EDIT2, m_ed2);
	DDX_Control(pDX, IDC_EDIT4, m_ed4);
	DDX_Control(pDX, IDC_EDIT5, m_ed5);
	DDX_Control(pDX, IDC_EDIT6, m_ed6);
	DDX_Control(pDX, IDC_EDIT7, m_ed7);
	DDX_Control(pDX, IDC_EDIT8, m_ed8);
	DDX_Control(pDX, IDC_EDIT9, m_ed9);
	DDX_Control(pDX, IDC_EDIT10, m_ed10);
	DDX_Control(pDX, IDC_EDIT11, m_ed11);
	DDX_Control(pDX, IDC_EDIT12, m_ed12);
	DDX_Control(pDX, IDC_BUTTON1, m_b1);
	DDX_Control(pDX, IDC_COMBO8, m_cb2);
	DDX_Control(pDX, IDC_EDIT14, m_e14);
	DDX_Control(pDX, IDC_EDIT15, m_e15);
	DDX_Control(pDX, IDC_EDIT16, m_e16);
	DDX_Control(pDX, IDC_EDIT17, m_e17);
	DDX_Control(pDX, IDC_COMBO24, m_cb3);
}


BEGIN_MESSAGE_MAP(CDlgInsertPicture, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgInsertPicture::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInsertPicture::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgInsertPicture::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgInsertPicture::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgInsertPicture::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgInsertPicture::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgInsertPicture::OnBnClickedCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO8, &CDlgInsertPicture::OnCbnSelchangeCombo8)
END_MESSAGE_MAP()


// CDlgInsertPicture ��Ϣ�������


void CDlgInsertPicture::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	PICinfo pi;
	dlg->io.PICgetInfo(pos,pi);
	int cm = m_cb1.GetCurSel();
	GetDlgItem(IDC_STATIC_F1)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F2)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F3)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F4)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F5)->EnableWindow(false);
	GetDlgItem(IDC_COMBO8)->EnableWindow(false);
	GetDlgItem(IDC_COMBO24)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	GetDlgItem(IDC_EDIT4)->EnableWindow(false);
	GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	GetDlgItem(IDC_EDIT6)->EnableWindow(false);
	GetDlgItem(IDC_EDIT7)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F6)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F7)->EnableWindow(false);
	GetDlgItem(IDC_EDIT2)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F8)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F9)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F10)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F11)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F12)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_F13)->EnableWindow(false);
	GetDlgItem(IDC_EDIT8)->EnableWindow(false);
	GetDlgItem(IDC_EDIT9)->EnableWindow(false);
	GetDlgItem(IDC_EDIT10)->EnableWindow(false);
	GetDlgItem(IDC_EDIT11)->EnableWindow(false);
	GetDlgItem(IDC_EDIT12)->EnableWindow(false);
	GetDlgItem(IDC_EDIT14)->EnableWindow(false);
	GetDlgItem(IDC_EDIT15)->EnableWindow(false);
	GetDlgItem(IDC_EDIT16)->EnableWindow(false);
	GetDlgItem(IDC_EDIT17)->EnableWindow(false);
	switch(cm){
	case 1:
		GetDlgItem(IDC_STATIC_F1)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F2)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F3)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F4)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F5)->EnableWindow(true);
		GetDlgItem(IDC_COMBO8)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
		GetDlgItem(IDC_COMBO24)->EnableWindow(true);
		GetDlgItem(IDC_EDIT1)->EnableWindow(true);
		GetDlgItem(IDC_EDIT4)->EnableWindow(true);
		GetDlgItem(IDC_EDIT5)->EnableWindow(true);
		GetDlgItem(IDC_EDIT6)->EnableWindow(true);
		GetDlgItem(IDC_EDIT7)->EnableWindow(true);
		GetDlgItem(IDC_EDIT4)->SetWindowText(NumToCStr(pi.get_basePt().get_X()));
		GetDlgItem(IDC_EDIT5)->SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
		GetDlgItem(IDC_EDIT6)->SetWindowText(NumToCStr(pi.get_frmSize().get_W()));
		GetDlgItem(IDC_EDIT7)->SetWindowText(NumToCStr(pi.get_frmSize().get_H()));
		break;
	case 2:
		GetDlgItem(IDC_STATIC_F6)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F7)->EnableWindow(true);
		GetDlgItem(IDC_EDIT2)->EnableWindow(true);
		GetDlgItem(IDC_EDIT2)->SetWindowText(NumToCStr(pi.get_linkTo()));
		break;
	case 3:
		GetDlgItem(IDC_STATIC_F8)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F9)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F10)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F11)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F12)->EnableWindow(true);
		GetDlgItem(IDC_STATIC_F13)->EnableWindow(true);
		GetDlgItem(IDC_EDIT8)->EnableWindow(true);
		GetDlgItem(IDC_EDIT9)->EnableWindow(true);
		GetDlgItem(IDC_EDIT10)->EnableWindow(true);
		GetDlgItem(IDC_EDIT11)->EnableWindow(true);
		GetDlgItem(IDC_EDIT12)->EnableWindow(true);
		GetDlgItem(IDC_EDIT14)->EnableWindow(true);
		GetDlgItem(IDC_EDIT15)->EnableWindow(true);
		GetDlgItem(IDC_EDIT16)->EnableWindow(true);
		GetDlgItem(IDC_EDIT17)->EnableWindow(true);
		GetDlgItem(IDC_EDIT14)->SetWindowText(NumToCStr(pi.get_basePt().get_X()));
		GetDlgItem(IDC_EDIT15)->SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
		GetDlgItem(IDC_EDIT16)->SetWindowText(NumToCStr(pi.get_frmSize().get_W()));
		GetDlgItem(IDC_EDIT17)->SetWindowText(NumToCStr(pi.get_frmSize().get_H()));
		GetDlgItem(IDC_EDIT8)->SetWindowText(NumToCStr(pi.get_TEXusing()));
		GetDlgItem(IDC_EDIT9)->SetWindowText(NumToCStr(pi.get_TEXpointLT().get_X()));
		GetDlgItem(IDC_EDIT10)->SetWindowText(NumToCStr(pi.get_TEXpointLT().get_Y()));
		GetDlgItem(IDC_EDIT11)->SetWindowText(NumToCStr(pi.get_TEXpointRB().get_X()));
		GetDlgItem(IDC_EDIT12)->SetWindowText(NumToCStr(pi.get_TEXpointRB().get_Y()));
		break;
	}
}


void CDlgInsertPicture::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defExt;
	CString extFilter;
	int cb = m_cb2.GetCurSel();
	if(ver == V2 && cb == 1 || ver == V5 && cb == 1){
		defExt = L"DDSͼ��(*.dds)|*.dds";
		extFilter = L"DDSͼ��(*.dds)|*.dds||";
	}else if(ver == V4 && cb == 1 || ver == V5 && cb == 2 || ver == V6 && cb == 0){
		defExt = L"��������(*.pid)|*.pid";
		extFilter = L"��������(*.pid)|*.pid||";
	}else{
		defExt = L"PNGͼ��(*.png)|*.png";
		extFilter = L"PNGͼ��(*.png)|*.png||";
	}
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_ed1.SetWindowText(fileName);
	}
}


void CDlgInsertPicture::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
}


void CDlgInsertPicture::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
}


void CDlgInsertPicture::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
}

void CDlgInsertPicture::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos = 0;
	if(m_ch1.GetCheck()){
		pos = dlg->m_lPicture.GetSelectionMark();
	}else if(m_ch2.GetCheck()){
		pos = dlg->m_lPicture.GetSelectionMark()+1;
	}else if(m_ch3.GetCheck()){
		pos = dlg->io.indexCount;
	}
	PICinfo pi;
	TEXinfo di;
	KoishiDDS::DDS d;
	stream s,s1;
	CString cstr;
	CString cstr1,cstr2;
	str fn;
	matrix mat;
	i32 i;
	i32 i1,i2;
	i32 x1,y1,x2,y2;
	int mode1 = m_cb1.GetCurSel();
	int inSel = m_cb2.GetCurSel();
	int outSel = m_cb3.GetCurSel();
	int mode2 = 100*ver+10*inSel+outSel;
	//0-ָ�� 1-PNGͼƬ 2-����ͼƬ 3-TexͼƬ 4-Tex����
	switch(mode1){
	case 0:
		//����ͼ֡
		dlg->io.PICempty(s, pi);
		if(iORr == CDlgInsertPicture::__INSERT){
			dlg->io.PICinsert(pos, pi, NULL);
		}else{
			dlg->io.PICreplace(pos, pi, NULL);
		}
		break;
	case 1:
		//��ͼ֡
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		//�ܼ����²���
		//200 201 202 210 211 212 213 400 410
		//500 501 502 503 504 505 506 507 508 509
		//510 511 512 513 514 515 516 517 600
		switch(mode2){
		case 200:
			//��ȡPNGת��ΪARGB8888
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 201:
			//��ȡPNGת��ΪARGB4444
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 202:
			//��ȡPNGת��ΪARGB1555
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 210:
			//��ȡDDSת��ΪARGB8888
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 211:
			//��ȡDDSת��ΪARGB4444
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 212:
			//��ȡDDSת��ΪARGB1555
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 213:
			//�����ã�����DDS��ʽ����ȷ����V2���Ƿ��ܹ���Ч
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			s1.loadFile(fn);
			s1.compressData(s,COMP_ZLIB);
			s1.release();
			switch(d.getHeader()->pixelFormat.fourCC){
			case 0x31545844:
				pi.set_format(DDS_DXT1);
				break;
			case 0x33545844:
				pi.set_format(DDS_DXT3);
				break;
			case 0x35545844:
				pi.set_format(DDS_DXT5);
				break;
			}
			pi.set_comp(COMP_ZLIB);
			pi.set_picSize(size(d.getHeader()->width, d.getHeader()->height));
			pi.set_dataSize(s.getLen());
			break;
		case 400:
			//��PNGת��Ϊ������ͼ���������ɫ����������
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, INDEX_FMT_PALETTE)){
				MessageBox(L"��ɫ���������",L"��ʾ");
				return;
			}
			mat.release();
			break;
		case 410:
			//��������ģʽ
			if(!s1.loadFile(fn)){
				MessageBox(L"�޷���ȡ�ļ�����",L"��ʾ");
				return;
			}
			s1.read(i1);
			if((b32)i1 != 0x73696F4B){
				MessageBox(L"��PIDδ��ʶ������",L"��ʾ��");
				return;
			}
			s1.read(i1);
			s1.read(i1);
			s1.read(i2);
			s1.ptMoveTo(0);
			s1.deleteStream(0, 16);
			s1.compressData(s, COMP_ZLIB);
			s1.release();
			pi.set_format(ARGB1555);
			pi.set_comp(COMP_ZLIB);
			pi.set_picSize(size(i1,i2));
			pi.set_dataSize(s.getLen());
			break;
		case 500:
			//��ȡPNG��ת��ΪARGB8888
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 501:
			//��ȡPNG��ת��ΪARGB4444
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 502:
			//��ȡPNG��ת��ΪARGB1555
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 503:
			//��ȡPNG��ת��Ϊ������ɫ(�������ɫ����)
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, INDEX_FMT_PALETTE)){
				MessageBox(L"��ɫ���������",L"��ʾ");
				return;
			}
			mat.release();
			break;
		case 504:
			//��ȡPNG��ת��ΪDDS_DXT5��ʽ����д�㷨��Ч�����
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, DDS_DXT5)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
				return;
			}
			mat.release();
			break;
		case 505:
			//��ȡPNG��ת��ΪARGB8888����������Ȼ��ͼ��֡����ȫͼ����
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB8888);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 506:
			//��ȡPNG��ת��ΪARGB4444����������Ȼ��ͼ��֡����ȫͼ����
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB4444);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 507:
			//��ȡPNG��ת��ΪARGB1555����������Ȼ��ͼ��֡����ȫͼ����
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB1555);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 508:
			//��ȡPNG��ת��Ϊ������ɫ�������������ԣ���Ȼ��ͼ��֡����ȫͼ����
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, INDEX_FMT_PALETTE)){
				MessageBox(L"��ɫ���������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB1555);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 509:
			//��ȡPNG��ת��ΪDDS_DXT5��ʽ����д�㷨��Ч���������������Ȼ��ͼ��֡����ȫͼ����
			//������.4֮ǰ��V5����֡ʱ�����ô˷�����
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, DDS_DXT5)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB1555);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 510:
			//��ȡDDS��ת��ΪARGB8888��ʽ
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 511:
			//��ȡDDS��ת��ΪARGB4444��ʽ
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 512:
			//��ȡDDS��ת��ΪARGB1555��ʽ
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 513:
			//����DDS��ʽ
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			s1.loadFile(fn);
			s1.compressData(s,COMP_ZLIB);
			s1.release();
			switch(d.getHeader()->pixelFormat.fourCC){
			case 0x31545844:
				pi.set_format(DDS_DXT1);
				break;
			case 0x33545844:
				pi.set_format(DDS_DXT3);
				break;
			case 0x35545844:
				pi.set_format(DDS_DXT5);
				break;
			}
			pi.set_comp(COMP_ZLIB);
			pi.set_picSize(size(d.getHeader()->width, d.getHeader()->height));
			pi.set_dataSize(s.getLen());
			break;
		case 514:
			//��ȡDDS��ʽ������ARGB8888��ʽ������������
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB8888);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 515:
			//��ȡDDS��ʽ������ARGB4444��ʽ������������
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB4444);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 516:
			//��ȡDDS��ʽ������ARGB1555��ʽ������������
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			dlg->io.TEXpush(di, s1);
			pi.set_format(ARGB1555);
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 517:
			//��ȡDDS��ʽ��������Ϊ������������
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			s1.loadFile(fn);
			s1.compressData(s,COMP_ZLIB);
			switch(d.getHeader()->pixelFormat.fourCC){
			case 0x31545844:
				di.set_format(DDS_DXT1);
				break;
			case 0x33545844:
				di.set_format(DDS_DXT3);
				break;
			case 0x35545844:
				di.set_format(DDS_DXT5);
				break;
			default:
				MessageBox(L"��֧�ֵ�DXTn��ʽ����",L"��ʾ");
				return;
			}
			di.set_compressedLength(s.getLen());
			di.set_dataLength(s1.getLen());
			di.set_height(d.getHeader()->height);
			di.set_width(d.getHeader()->width);
			di.set_ID(dlg->io.V5_TEXCount);
			di.set_reserved(1);
			s1.release();
			dlg->io.TEXpush(di, s);
			s.release();
			s = NULL;
			pi.set_format(di.get_format());
			pi.set_comp(COMP_ZLIB2);
			pi.set_dataSize(0);
			pi.set_picSize(size(di.get_width(),di.get_height()));
			pi.set_TEXusing(dlg->io.V5_TEXCount-1);
			pi.set_TEXpointLT(point(0,0));
			pi.set_TEXpointRB(point(di.get_width(),di.get_height()));
			s = NULL;
			break;
		case 600:
			//��ȡ������ʽ��ΪV6����������
			if(!s1.loadFile(fn)){
				MessageBox(L"�޷���ȡ�ļ�����",L"��ʾ");
				return;
			}
			s1.read(i1);
			if((b32)i1 != 0x73696F4B){
				MessageBox(L"��PIDδ��ʶ������",L"��ʾ��");
				return;
			}
			s1.read(i1);
			s1.read(i1);
			s1.read(i2);
			s1.ptMoveTo(0);
			s1.deleteStream(0, 16);
			s1.compressData(s, COMP_ZLIB);
			s1.release();
			pi.set_format(ARGB1555);
			pi.set_comp(COMP_ZLIB);
			pi.set_picSize(size(i1,i2));
			pi.set_dataSize(s.getLen());
			break;
		default:
			MessageBox(L"��֧�ֵĲ�������",L"��ʾ");
			break;
		}
		m_ed4.GetWindowText(cstr1);
		m_ed5.GetWindowText(cstr2);
		pi.set_basePt(point(_ttoi(cstr1),_ttoi(cstr2)));
		m_ed6.GetWindowText(cstr1);
		m_ed7.GetWindowText(cstr2);
		pi.set_frmSize(size(_ttoi(cstr1),_ttoi(cstr2)));
		if(iORr == CDlgInsertPicture::__INSERT){
			dlg->io.PICinsert(pos, pi, s);
		}else{
			dlg->io.PICreplace(pos, pi, s);
		}
		break;
	case 2:
		//ָ��֡
		pi.set_format(LINK);
		m_ed2.GetWindowText(cstr);
		i = _ttoi(cstr);
		if(iORr == CDlgInsertPicture::__INSERT){
			if(i>dlg->io.indexCount || i<0){
				MessageBox(L"��Ӹ�������󣬲�����IDΪ"+cstr+L"������������",L"��ʾ��");
				return;
			}
			if(i<pos && dlg->io.PICcontent[i].get_format() == LINK){
				MessageBox(L"��Ӹ��������IDΪ"+cstr+L"����������ָ��������������\r\n������������ָ����������ȥָ��������",L"��ʾ��");
				return;
			}
			if(pos == -1 || i==pos || i > pos && dlg->io.PICcontent[i-1].get_format() == LINK){
				MessageBox(L"��Ӹ��������IDΪ"+cstr+L"����������ָ��������������\r\n������������ָ����������ȥָ��������",L"��ʾ��");
				return;
			}
		}else{
			if(i>dlg->io.indexCount-1 || i<0){
				MessageBox(L"������IDΪ"+cstr+L"������������",L"��ʾ��");
				return;
			}
			if(dlg->io.PICcontent[i].get_format() == LINK){
				MessageBox(L"IDΪ"+cstr+L"���������Ѿ���ָ��������������\r\n������������ָ����������ȥָ��������",L"��ʾ��");
				return;
			}
			if(i==pos){
				MessageBox(L"ָ�����������ָ���Լ�����",L"��ʾ��");
				return;
			}
		}
		pi.set_linkTo(_ttoi(cstr));
		if(iORr == CDlgInsertPicture::__INSERT){
			dlg->io.PICinsert(pos, pi, NULL);
		}else{
			dlg->io.PICreplace(pos, pi, NULL);
		}
		break;
	case 3:
		m_ed8.GetWindowText(cstr);//�������
		i = _ttoi(cstr);
		if(i>(i32)dlg->io.TEXcontent.size()-1){
			MessageBox(L"�����ڱ��Ϊ"+cstr+L"����������\r\n��ǰ���������ţ�"+NumToCStr(dlg->io.TEXcontent.size()-1),L"��ʾ��");
			return;
		}
		dlg->io.TEXgetInfo(i, di);
		pi.set_format((colorFormat)di.get_format());
		pi.set_comp(COMP_ZLIB2);
		pi.set_TEXusing((b32)i);
		m_ed9.GetWindowText(cstr1);
		m_ed10.GetWindowText(cstr2);
		x1 = _ttoi(cstr1);
		y1 = _ttoi(cstr2);
		m_ed11.GetWindowText(cstr1);
		m_ed12.GetWindowText(cstr2);
		x2 = _ttoi(cstr1);
		y2 = _ttoi(cstr2);
		if(x1>=x2 || y1>=y2){
			MessageBox(L"���½ǵ�����������붼�������Ͻǵ���������\r\n��ǰ�������ϵ㣺"
				+NumToCStr(x1)
				+L"��"
				+NumToCStr(y1)
				+L"\r\n��ǰ�������µ㣺"
				+NumToCStr(x2)
				+L"��"
				+NumToCStr(y2),L"��ʾ��");
			return;
		}
		if(x2>(i32)di.get_width() || y2>(i32)di.get_height() || x1<0 || y1<0){
			MessageBox(L"�����������붼С�������ĳߴ�����\r\n��ǰ�����ߴ磺"
				+NumToCStr(di.get_width())
				+L"��"
				+NumToCStr(di.get_height())
				+L"\r\n��ǰ�������ϵ㣺"
				+NumToCStr(x1)
				+L"��"
				+NumToCStr(y1)
				+L"\r\n��ǰ�������µ㣺"
				+NumToCStr(x2)
				+L"��"
				+NumToCStr(y2),L"��ʾ��");
			return;
		}
		pi.set_TEXpointLT(point(x1,y1));
		pi.set_TEXpointRB(point(x2,y2));
		pi.set_picSize(size(x2-x1,y2-y1));
		pi.set_dataSize(0);
		m_ed4.GetWindowText(cstr1);
		m_ed5.GetWindowText(cstr2);
		pi.set_basePt(point(_ttoi(cstr1),_ttoi(cstr2)));
		m_ed6.GetWindowText(cstr1);
		m_ed7.GetWindowText(cstr2);
		pi.set_frmSize(size(_ttoi(cstr1),_ttoi(cstr2)));
		if(iORr == CDlgInsertPicture::__INSERT){
			dlg->io.PICinsert(pos, pi, NULL);
		}else{
			dlg->io.PICreplace(pos, pi, NULL);
		}
		break;
	}
	if(iORr == CDlgInsertPicture::__INSERT){
		MessageBox(L"����ɹ�����",L"��ʾ����");
		dlg->m_lPicture.InsertItem(pos, NumToCStr(pos));
	}else{
		MessageBox(L"�滻�ɹ�����",L"��ʾ����");
	}
	dlg->m_lPicture.SetItem(pos,0,LVIF_IMAGE,NULL,dlg->getIconPIC(dlg->io.PICcontent[pos].get_format()),0,0,0);
	if(dlg->io.PICcontent[pos].get_format() == LINK){
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version) + NumToCStr(dlg->io.PICcontent[pos].get_linkTo()));
		dlg->m_lPicture.SetItemText(pos, 2, L"");
		dlg->m_lPicture.SetItemText(pos, 3, L"");
		dlg->m_lPicture.SetItemText(pos, 4, L"");
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"");
		}
	}else{
		dlg->m_lPicture.SetItemText(pos, 1, FmtToCStr(dlg->io.PICcontent[pos].get_format(), dlg->io.version));
		dlg->m_lPicture.SetItemText(pos, 2, PtToCStr(dlg->io.PICcontent[pos].get_basePt()));
		dlg->m_lPicture.SetItemText(pos, 3, SzToCStr(dlg->io.PICcontent[pos].get_picSize()));
		dlg->m_lPicture.SetItemText(pos, 4, SzToCStr(dlg->io.PICcontent[pos].get_frmSize()));
		if(dlg->io.version == V5){
			dlg->m_lPicture.SetItemText(pos, 5, L"����"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
		}
	}
	//dlg->updatePIClist();
	dlg->updateTEXlist();
	dlg->updateNPKInfo();
	dlg->updatePICInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsertPicture::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//0-ָ�� 1-PNGͼƬ 2-����ͼƬ 3-TexͼƬ
	ShowWindow(SW_HIDE);
}


void CDlgInsertPicture::OnCbnSelchangeCombo8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(ver){
	case V2:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"ת��ΪARGB8888");
			m_cb3.AddString(L"ת��ΪARGB4444");
			m_cb3.AddString(L"ת��ΪARGB1555");
			m_cb3.SetCurSel(0);
			break;
		case 1:
			m_cb3.ResetContent();
			m_cb3.AddString(L"ת��ΪARGB8888");
			m_cb3.AddString(L"ת��ΪARGB4444");
			m_cb3.AddString(L"ת��ΪARGB1555");
			m_cb3.AddString(L"����DXTn��ʽ(����)");
			m_cb3.SetCurSel(0);
			break;
		}
		break;
	case V4:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"ת��Ϊ������ɫ(���·����ɫ��)");
			m_cb3.SetCurSel(0);
			break;
		case 1:
			m_cb3.ResetContent();
			m_cb3.AddString(L"����������ɫ");
			m_cb3.SetCurSel(0);
			break;
		}
		break;
	case V5:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"ת��ΪARGB8888");
			m_cb3.AddString(L"ת��ΪARGB4444");
			m_cb3.AddString(L"ת��ΪARGB1555");
			m_cb3.AddString(L"ת��Ϊ������ɫ(���·����ɫ��)");
			m_cb3.AddString(L"ת��ΪDXT5��ʽ");
			m_cb3.AddString(L"����ARGB8888����������");
			m_cb3.AddString(L"����ARGB4444����������");
			m_cb3.AddString(L"����ARGB1555����������");
			m_cb3.AddString(L"����������ɫ����������(����)");
			m_cb3.AddString(L"����DXT5����������");
			m_cb3.SetCurSel(0);
			break;
		case 1:
			m_cb3.ResetContent();
			m_cb3.AddString(L"ת��ΪARGB8888");
			m_cb3.AddString(L"ת��ΪARGB4444");
			m_cb3.AddString(L"ת��ΪARGB1555");
			m_cb3.AddString(L"����DXTn��ʽ");
			m_cb3.AddString(L"����ARGB8888����������");
			m_cb3.AddString(L"����ARGB4444����������");
			m_cb3.AddString(L"����ARGB1555����������");
			m_cb3.AddString(L"����DXTn����������");
			m_cb3.SetCurSel(7);
			break;
		case 2:
			m_cb3.ResetContent();
			m_cb3.AddString(L"ת��Ϊ������ɫ(���·����ɫ��)");
			m_cb3.AddString(L"����������ɫ����������");
			m_cb3.SetCurSel(1);
			break;
		}
		break;
	case V6:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"������ɫ(8λ��ɫ�塤24λ��ɫ����֧�ְ�͸��)");
			m_cb3.SetCurSel(0);
			break;
		}
		break;
	}
}
