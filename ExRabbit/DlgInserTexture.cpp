// DlgInsert3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsertTexture.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgInsertTexTexture �Ի���

IMPLEMENT_DYNAMIC(CDlgInsertTexture, CDialogEx)

CDlgInsertTexture::CDlgInsertTexture(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInsertTexture::IDD, pParent)
{

}

CDlgInsertTexture::~CDlgInsertTexture()
{
}

void CDlgInsertTexture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_c1);
	DDX_Control(pDX, IDC_CHECK2, m_c2);
	DDX_Control(pDX, IDC_CHECK3, m_c3);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	DDX_Control(pDX, IDC_EDIT1, m_ed1);
	DDX_Control(pDX, IDC_COMBO3, m_cb2);
}


BEGIN_MESSAGE_MAP(CDlgInsertTexture, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgInsertTexture::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgInsertTexture::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgInsertTexture::OnBnClickedCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgInsertTexture::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInsertTexture::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgInsertTexture::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgInsertTexture::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgInsertTexTexture ��Ϣ�������


void CDlgInsertTexture::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_c1.SetCheck(1);
	m_c2.SetCheck(0);
	m_c3.SetCheck(0);
}


void CDlgInsertTexture::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_c1.SetCheck(0);
	m_c2.SetCheck(1);
	m_c3.SetCheck(0);
}


void CDlgInsertTexture::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_c1.SetCheck(0);
	m_c2.SetCheck(0);
	m_c3.SetCheck(1);
}

void CDlgInsertTexture::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(ver){
	case V5:
		switch(m_cb1.GetCurSel()){
		case 0:
			m_cb2.ResetContent();
			m_cb2.AddString(L"����DXTn��ʽ");
			m_cb2.AddString(L"ת��ΪARGB8888");
			m_cb2.AddString(L"ת��ΪARGB4444");
			m_cb2.AddString(L"ת��ΪARGB1555");
			m_cb2.SetCurSel(0);
			break;
		case 1:
			m_cb2.ResetContent();
			m_cb2.AddString(L"ת��ΪDXT5��ʽ");
			m_cb2.AddString(L"ת��ΪARGB8888");
			m_cb2.AddString(L"ת��ΪARGB4444");
			m_cb2.AddString(L"ת��ΪARGB1555");
			m_cb2.SetCurSel(1);
			break;
		}
		break;
	default:
		m_cb2.ResetContent();
		m_cb2.AddString(L"��֧�ֵ�IMG�汾");
		m_cb2.SetCurSel(0);
		break;
	}
}

void CDlgInsertTexture::OnBnClickedButton1()
{
	CString defExt;
	CString extFilter;
	int cb = m_cb1.GetCurSel();
	if(ver == V5 && cb == 0){
		defExt = L"DDSͼ��(*.dds)|*.dds";
		extFilter = L"DDSͼ��(*.dds)|*.dds||";
	}else if(ver == V5 && cb == 1){
		defExt = L"PNGͼ��(*.png)|*.png";
		extFilter = L"PNGͼ��(*.png)|*.png||";
	}else{
		defExt = L"�����ļ�(*.*)|*.*";
		extFilter = L"�����ļ�(*.*)|*.*||";
	}
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_ed1.SetWindowText(fileName);
	}
}


void CDlgInsertTexture::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos = 0;
	if(m_c1.GetCheck()){
		pos = dlg->m_lTexture.GetSelectionMark();
	}else if(m_c2.GetCheck()){
		pos = dlg->m_lTexture.GetSelectionMark()+1;
	}else if(m_c3.GetCheck()){
		pos = dlg->io.V5_TEXCount;
	}
	if(pos<0)
		pos = 0;
	TEXinfo di;
	KoishiDDS::DDS d;
	stream s,s1;
	CString cstr;
	str fn;
	matrix mat;
	int mode1 = 0;
	int inSel = m_cb1.GetCurSel();
	int outSel = m_cb2.GetCurSel();
	int mode2 = 100*ver+10*inSel+outSel;
	switch(mode1){
	case 0:
		//����
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		//�ܼ����²���
		//500 501 502 503 510 511 512 513
		switch(mode2){
		case 500:
			//��ȡDDS������DXTn��ʽ��Ϊ����
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
			break;
		case 501:
			//��ȡDDS��ת��ΪARGB8888��ʽ��Ϊ����
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			break;
		case 502:
			//��ȡDDS��ת��ΪARGB8888��ʽ��Ϊ����
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			break;
		case 503:
			//��ȡDDS��ת��ΪARGB8888��ʽ��Ϊ����
			if(!d.loadFile(fn)){
				MessageBox(L"��ȡDDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"����DDS�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			break;
		case 510:
			//��ȡPNG��ת��ΪDXT5��ʽ��Ϊ������Ч�����
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, DDS_DXT5)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 511:
			//��ȡPNH��ת��ΪARGB8888��ʽ
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB8888)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 512:
			//��ȡPNH��ת��ΪARGB4444��ʽ
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB4444)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		case 513:
			//��ȡPNH��ת��ΪARGB1555��ʽ
			if(!mat.loadPNG(fn)){
				MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB1555)){
				MessageBox(L"ת��ʧ������",L"��ʾ");
			}
			mat.release();
			break;
		}
		if(iORr == __INSERT){
			dlg->io.TEXinsert(pos, di, s);
		}else{
			dlg->io.TEXreplace(pos, di, s);
		}
		break;
	default:
		MessageBox(L"��֧�ֵĲ�������",L"��ʾ");
		break;
	}
	if(iORr == __INSERT){
		MessageBox(L"����ɹ�����",L"��ʾ");
	}else{
		MessageBox(L"�滻�ɹ�����",L"��ʾ");
	}
	dlg->updateTEXlist();
	dlg->updateNPKInfo();
	dlg->updatePICInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsertTexture::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}
