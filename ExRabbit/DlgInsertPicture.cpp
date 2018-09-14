// DlgInsert2.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsertPicture.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgInsertPicture 对话框

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


// CDlgInsertPicture 消息处理程序


void CDlgInsertPicture::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CString defExt;
	CString extFilter;
	int cb = m_cb2.GetCurSel();
	if(ver == V2 && cb == 1 || ver == V5 && cb == 1){
		defExt = L"DDS图像(*.dds)|*.dds";
		extFilter = L"DDS图像(*.dds)|*.dds||";
	}else if(ver == V4 && cb == 1 || ver == V5 && cb == 2 || ver == V6 && cb == 0){
		defExt = L"索引数据(*.pid)|*.pid";
		extFilter = L"索引数据(*.pid)|*.pid||";
	}else{
		defExt = L"PNG图像(*.png)|*.png";
		extFilter = L"PNG图像(*.png)|*.png||";
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
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
}


void CDlgInsertPicture::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
}


void CDlgInsertPicture::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
}

void CDlgInsertPicture::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//0-指向 1-PNG图片 2-索引图片 3-Tex图片 4-Tex引用
	switch(mode1){
	case 0:
		//空贴图帧
		dlg->io.PICempty(s, pi);
		if(iORr == CDlgInsertPicture::__INSERT){
			dlg->io.PICinsert(pos, pi, NULL);
		}else{
			dlg->io.PICreplace(pos, pi, NULL);
		}
		break;
	case 1:
		//贴图帧
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		//总计如下操作
		//200 201 202 210 211 212 213 400 410
		//500 501 502 503 504 505 506 507 508 509
		//510 511 512 513 514 515 516 517 600
		switch(mode2){
		case 200:
			//读取PNG转化为ARGB8888
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 201:
			//读取PNG转化为ARGB4444
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 202:
			//读取PNG转化为ARGB1555
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 210:
			//读取DDS转化为ARGB8888
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 211:
			//读取DDS转化为ARGB4444
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 212:
			//读取DDS转化为ARGB1555
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 213:
			//测试用：保留DDS格式，不确定在V2中是否能够生效
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
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
			//将PNG转化为索引贴图（需进行颜色量化操作）
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, INDEX_FMT_PALETTE)){
				MessageBox(L"颜色表溢出喵！",L"提示");
				return;
			}
			mat.release();
			break;
		case 410:
			//导入索引模式
			if(!s1.loadFile(fn)){
				MessageBox(L"无法读取文件喵！",L"提示");
				return;
			}
			s1.read(i1);
			if((b32)i1 != 0x73696F4B){
				MessageBox(L"该PID未能识别喵！",L"提示！");
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
			//读取PNG并转化为ARGB8888
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 501:
			//读取PNG并转化为ARGB4444
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 502:
			//读取PNG并转化为ARGB1555
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 503:
			//读取PNG并转化为索引颜色(需进行颜色量化)
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, INDEX_FMT_PALETTE)){
				MessageBox(L"颜色表溢出喵！",L"提示");
				return;
			}
			mat.release();
			break;
		case 504:
			//读取PNG并转化为DDS_DXT5格式（自写算法，效果极差）
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, DDS_DXT5)){
				MessageBox(L"转换失败喵！",L"提示");
				return;
			}
			mat.release();
			break;
		case 505:
			//读取PNG并转化为ARGB8888存入纹理集，然后图像帧对其全图引用
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
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
			//读取PNG并转化为ARGB4444存入纹理集，然后图像帧对其全图引用
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
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
			//读取PNG并转化为ARGB1555存入纹理集，然后图像帧对其全图引用
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
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
			//读取PNG并转化为索引颜色存入纹理集（测试），然后图像帧对其全图引用
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, INDEX_FMT_PALETTE)){
				MessageBox(L"颜色表溢出喵。",L"提示");
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
			//读取PNG并转化为DDS_DXT5格式（自写算法，效果极差）存入纹理集，然后图像帧对其全图引用
			//（兔子.4之前在V5插入帧时均采用此方法）
			if(!mat.loadPNG(fn)){
				MessageBox(L"读取PNG文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, DDS_DXT5)){
				MessageBox(L"转换失败喵。",L"提示");
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
			//读取DDS并转化为ARGB8888格式
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 511:
			//读取DDS并转化为ARGB4444格式
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 512:
			//读取DDS并转化为ARGB1555格式
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.PICpreprocess(mat, s, pi, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
			}
			mat.release();
			break;
		case 513:
			//保留DDS格式
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
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
			//读取DDS格式并创建ARGB8888格式纹理集，并引用
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB8888)){
				MessageBox(L"转换失败喵。",L"提示");
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
			//读取DDS格式并创建ARGB4444格式纹理集，并引用
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB4444)){
				MessageBox(L"转换失败喵。",L"提示");
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
			//读取DDS格式并创建ARGB1555格式纹理集，并引用
			if(!d.loadFile(fn)){
				MessageBox(L"读取DDS文件失败喵！",L"提示");
				return;
			}
			if(!d.uncompress(mat)){
				MessageBox(L"解析DDS文件失败喵！",L"提示");
				return;
			}
			if(!dlg->io.TEXpreprocess(mat, s1, di, ARGB1555)){
				MessageBox(L"转换失败喵。",L"提示");
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
			//读取DDS格式并将其作为纹理集，并引用
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
			//读取索引格式作为V6的索引数据
			if(!s1.loadFile(fn)){
				MessageBox(L"无法读取文件喵！",L"提示");
				return;
			}
			s1.read(i1);
			if((b32)i1 != 0x73696F4B){
				MessageBox(L"该PID未能识别喵！",L"提示！");
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
			MessageBox(L"不支持的操作喵！",L"提示");
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
		//指向帧
		pi.set_format(LINK);
		m_ed2.GetWindowText(cstr);
		i = _ttoi(cstr);
		if(iORr == CDlgInsertPicture::__INSERT){
			if(i>dlg->io.indexCount || i<0){
				MessageBox(L"添加该索引项后，不存在ID为"+cstr+L"的索引项喵！",L"提示喵");
				return;
			}
			if(i<pos && dlg->io.PICcontent[i].get_format() == LINK){
				MessageBox(L"添加该索引项后，ID为"+cstr+L"的索引项是指向型索引项喵！\r\n不能再由其他指向型索引项去指向它喵！",L"提示喵");
				return;
			}
			if(pos == -1 || i==pos || i > pos && dlg->io.PICcontent[i-1].get_format() == LINK){
				MessageBox(L"添加该索引项后，ID为"+cstr+L"的索引项是指向型索引项喵！\r\n不能再由其他指向型索引项去指向它喵！",L"提示喵");
				return;
			}
		}else{
			if(i>dlg->io.indexCount-1 || i<0){
				MessageBox(L"不存在ID为"+cstr+L"的索引项喵！",L"提示喵");
				return;
			}
			if(dlg->io.PICcontent[i].get_format() == LINK){
				MessageBox(L"ID为"+cstr+L"的索引项已经是指向型索引项喵！\r\n不能再由其他指向型索引项去指向它喵！",L"提示喵");
				return;
			}
			if(i==pos){
				MessageBox(L"指向型索引项不能指向自己喵！",L"提示喵");
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
		m_ed8.GetWindowText(cstr);//纹理集编号
		i = _ttoi(cstr);
		if(i>(i32)dlg->io.TEXcontent.size()-1){
			MessageBox(L"不存在编号为"+cstr+L"的纹理集喵！\r\n当前最大纹理集编号："+NumToCStr(dlg->io.TEXcontent.size()-1),L"提示喵");
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
			MessageBox(L"右下角的坐标两点必须都大于左上角的坐标喵！\r\n当前坐标左上点："
				+NumToCStr(x1)
				+L"，"
				+NumToCStr(y1)
				+L"\r\n当前坐标右下点："
				+NumToCStr(x2)
				+L"，"
				+NumToCStr(y2),L"提示喵");
			return;
		}
		if(x2>(i32)di.get_width() || y2>(i32)di.get_height() || x1<0 || y1<0){
			MessageBox(L"所有坐标点必须都小与纹理集的尺寸喵！\r\n当前纹理集尺寸："
				+NumToCStr(di.get_width())
				+L"×"
				+NumToCStr(di.get_height())
				+L"\r\n当前坐标左上点："
				+NumToCStr(x1)
				+L"，"
				+NumToCStr(y1)
				+L"\r\n当前坐标右下点："
				+NumToCStr(x2)
				+L"，"
				+NumToCStr(y2),L"提示喵");
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
		MessageBox(L"插入成功喵！",L"提示喵！");
		dlg->m_lPicture.InsertItem(pos, NumToCStr(pos));
	}else{
		MessageBox(L"替换成功喵！",L"提示喵！");
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
			dlg->m_lPicture.SetItemText(pos, 5, L"纹理集"+NumToCStr(dlg->io.PICcontent[pos].get_TEXusing())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_TEXpointRB()));
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
	// TODO: 在此添加控件通知处理程序代码
	//0-指向 1-PNG图片 2-索引图片 3-Tex图片
	ShowWindow(SW_HIDE);
}


void CDlgInsertPicture::OnCbnSelchangeCombo8()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(ver){
	case V2:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"转化为ARGB8888");
			m_cb3.AddString(L"转化为ARGB4444");
			m_cb3.AddString(L"转化为ARGB1555");
			m_cb3.SetCurSel(0);
			break;
		case 1:
			m_cb3.ResetContent();
			m_cb3.AddString(L"转化为ARGB8888");
			m_cb3.AddString(L"转化为ARGB4444");
			m_cb3.AddString(L"转化为ARGB1555");
			m_cb3.AddString(L"保留DXTn格式(测试)");
			m_cb3.SetCurSel(0);
			break;
		}
		break;
	case V4:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"转化为索引颜色(重新分配调色板)");
			m_cb3.SetCurSel(0);
			break;
		case 1:
			m_cb3.ResetContent();
			m_cb3.AddString(L"保留索引颜色");
			m_cb3.SetCurSel(0);
			break;
		}
		break;
	case V5:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"转化为ARGB8888");
			m_cb3.AddString(L"转化为ARGB4444");
			m_cb3.AddString(L"转化为ARGB1555");
			m_cb3.AddString(L"转化为索引颜色(重新分配调色板)");
			m_cb3.AddString(L"转化为DXT5格式");
			m_cb3.AddString(L"创建ARGB8888纹理集并引用");
			m_cb3.AddString(L"创建ARGB4444纹理集并引用");
			m_cb3.AddString(L"创建ARGB1555纹理集并引用");
			m_cb3.AddString(L"创建索引颜色纹理集并引用(测试)");
			m_cb3.AddString(L"创建DXT5纹理集并引用");
			m_cb3.SetCurSel(0);
			break;
		case 1:
			m_cb3.ResetContent();
			m_cb3.AddString(L"转化为ARGB8888");
			m_cb3.AddString(L"转化为ARGB4444");
			m_cb3.AddString(L"转化为ARGB1555");
			m_cb3.AddString(L"保留DXTn格式");
			m_cb3.AddString(L"创建ARGB8888纹理集并引用");
			m_cb3.AddString(L"创建ARGB4444纹理集并引用");
			m_cb3.AddString(L"创建ARGB1555纹理集并引用");
			m_cb3.AddString(L"创建DXTn纹理集并引用");
			m_cb3.SetCurSel(7);
			break;
		case 2:
			m_cb3.ResetContent();
			m_cb3.AddString(L"转化为索引颜色(重新分配调色板)");
			m_cb3.AddString(L"创建索引颜色纹理集并引用");
			m_cb3.SetCurSel(1);
			break;
		}
		break;
	case V6:
		switch(m_cb2.GetCurSel()){
		case 0:
			m_cb3.ResetContent();
			m_cb3.AddString(L"索引颜色(8位调色板·24位彩色·不支持半透明)");
			m_cb3.SetCurSel(0);
			break;
		}
		break;
	}
}
