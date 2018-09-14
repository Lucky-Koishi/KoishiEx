// DlgInsert3.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsertTexture.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgInsertTexTexture 对话框

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


// CDlgInsertTexTexture 消息处理程序


void CDlgInsertTexture::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(1);
	m_c2.SetCheck(0);
	m_c3.SetCheck(0);
}


void CDlgInsertTexture::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(0);
	m_c2.SetCheck(1);
	m_c3.SetCheck(0);
}


void CDlgInsertTexture::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_c1.SetCheck(0);
	m_c2.SetCheck(0);
	m_c3.SetCheck(1);
}

void CDlgInsertTexture::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(ver){
	case V5:
		switch(m_cb1.GetCurSel()){
		case 0:
			m_cb2.ResetContent();
			m_cb2.AddString(L"保留DXTn格式");
			m_cb2.AddString(L"转化为ARGB8888");
			m_cb2.AddString(L"转化为ARGB4444");
			m_cb2.AddString(L"转化为ARGB1555");
			m_cb2.SetCurSel(0);
			break;
		case 1:
			m_cb2.ResetContent();
			m_cb2.AddString(L"转化为DXT5格式");
			m_cb2.AddString(L"转化为ARGB8888");
			m_cb2.AddString(L"转化为ARGB4444");
			m_cb2.AddString(L"转化为ARGB1555");
			m_cb2.SetCurSel(1);
			break;
		}
		break;
	default:
		m_cb2.ResetContent();
		m_cb2.AddString(L"不支持的IMG版本");
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
		defExt = L"DDS图像(*.dds)|*.dds";
		extFilter = L"DDS图像(*.dds)|*.dds||";
	}else if(ver == V5 && cb == 1){
		defExt = L"PNG图像(*.png)|*.png";
		extFilter = L"PNG图像(*.png)|*.png||";
	}else{
		defExt = L"所有文件(*.*)|*.*";
		extFilter = L"所有文件(*.*)|*.*||";
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
	// TODO: 在此添加控件通知处理程序代码
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
		//纹理集
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		//总计如下操作
		//500 501 502 503 510 511 512 513
		switch(mode2){
		case 500:
			//读取DDS并保留DXTn格式作为纹理集
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
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
				MessageBox(L"不支持的DXTn格式喵！",L"提示");
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
			//读取DDS并转换为ARGB8888格式作为纹理集
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			break;
		case 502:
			//读取DDS并转换为ARGB8888格式作为纹理集
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			break;
		case 503:
			//读取DDS并转换为ARGB8888格式作为纹理集
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			break;
		case 510:
			//读取PNG并转换为DXT5格式作为纹理集（效果极差）
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, DDS_DXT5)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 511:
			//读取PNH并转换为ARGB8888格式
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 512:
			//读取PNH并转换为ARGB4444格式
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 513:
			//读取PNH并转换为ARGB1555格式
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s, di, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
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
		MessageBox(L"不支持的操作喵！",L"提示");
		break;
	}
	if(iORr == __INSERT){
		MessageBox(L"插入成功喵！",L"提示");
	}else{
		MessageBox(L"替换成功喵！",L"提示");
	}
	dlg->updateTEXlist();
	dlg->updateNPKInfo();
	dlg->updatePICInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsertTexture::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
