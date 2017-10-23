// DlgInsert2.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsert2.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgInsert2 对话框

IMPLEMENT_DYNAMIC(CDlgInsert2, CDialogEx)

CDlgInsert2::CDlgInsert2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInsert2::IDD, pParent)
{

}

CDlgInsert2::~CDlgInsert2()
{
}

void CDlgInsert2::DoDataExchange(CDataExchange* pDX)
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
}


BEGIN_MESSAGE_MAP(CDlgInsert2, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgInsert2::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInsert2::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgInsert2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgInsert2::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgInsert2::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgInsert2::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgInsert2::OnBnClickedCheck3)
END_MESSAGE_MAP()


// CDlgInsert2 消息处理程序


void CDlgInsert2::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	PICinfo pi;
	dlg->io.GetPICInfo(pos,pi);

	int cm = m_cb1.GetCurSel();
	mode = 0;//0-指向 1-PNG图片 2-索引图片 3-DDS引用
	if(ver == V2 && cm == 1)
		mode = 1;
	if(ver == V4 && cm == 1)
		mode = 2;
	if(ver == V4 && cm == 2)
		mode = 1;
	if(ver == V5 && cm == 1)
		mode = 3;
	if(ver == V5 && cm == 2)
		mode = 1;
	if(ver == V6 && cm == 1)
		mode = 2;
	m_ed1.EnableWindow(false);
	m_b1.EnableWindow(false);
	m_ed2.EnableWindow(false);
	m_ed4.EnableWindow(false);
	m_ed5.EnableWindow(false);
	m_ed6.EnableWindow(false);
	m_ed7.EnableWindow(false);
	m_ed8.EnableWindow(false);
	m_ed9.EnableWindow(false);
	m_ed10.EnableWindow(false);
	m_ed11.EnableWindow(false);
	m_ed12.EnableWindow(false);
	switch(mode){
	case 0:
		m_ed2.EnableWindow(true);
		m_ed2.SetWindowText(NumToCStr(pi.get_linkTo()));
		break;
	case 1:
		m_ed1.EnableWindow(true);
		m_b1.EnableWindow(true);
		m_ed4.EnableWindow(true);
		m_ed5.EnableWindow(true);
		m_ed6.EnableWindow(true);
		m_ed7.EnableWindow(true);
		m_ed4.SetWindowText(NumToCStr(pi.get_basePt().get_X()));
		m_ed5.SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
		m_ed6.SetWindowText(NumToCStr(pi.get_frmSize().get_W()));
		m_ed7.SetWindowText(NumToCStr(pi.get_frmSize().get_H()));
		break;
	case 2:
		m_ed1.EnableWindow(true);
		m_b1.EnableWindow(true);
		m_ed4.EnableWindow(true);
		m_ed5.EnableWindow(true);
		m_ed6.EnableWindow(true);
		m_ed7.EnableWindow(true);
		m_ed4.SetWindowText(NumToCStr(pi.get_basePt().get_X()));
		m_ed5.SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
		m_ed6.SetWindowText(NumToCStr(pi.get_frmSize().get_W()));
		m_ed7.SetWindowText(NumToCStr(pi.get_frmSize().get_H()));
		break;
	case 3:
		m_ed4.EnableWindow(true);
		m_ed5.EnableWindow(true);
		m_ed6.EnableWindow(true);
		m_ed7.EnableWindow(true);
		m_ed8.EnableWindow(true);
		m_ed9.EnableWindow(true);
		m_ed10.EnableWindow(true);
		m_ed11.EnableWindow(true);
		m_ed12.EnableWindow(true);
		m_ed4.SetWindowText(NumToCStr(pi.get_basePt().get_X()));
		m_ed5.SetWindowText(NumToCStr(pi.get_basePt().get_Y()));
		m_ed6.SetWindowText(NumToCStr(pi.get_frmSize().get_W()));
		m_ed7.SetWindowText(NumToCStr(pi.get_frmSize().get_H()));
		m_ed8.SetWindowText(NumToCStr(pi.get_DDSIDused()));
		m_ed9.SetWindowText(NumToCStr(pi.get_DDSpointLT().get_X()));
		m_ed10.SetWindowText(NumToCStr(pi.get_DDSpointLT().get_Y()));
		m_ed11.SetWindowText(NumToCStr(pi.get_DDSpointRB().get_X()));
		m_ed12.SetWindowText(NumToCStr(pi.get_DDSpointRB().get_Y()));
		break;
	}
}


void CDlgInsert2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString listExt[4] = {
		_T("png图像(*.png)|*.png"),
		_T("png图像(*.png)|*.png"),
		_T("索引数据(*.pid)|*.pid"),
		_T("dds图像(*.dds)|*.dds")
	}; 
	CString defExt = listExt[mode];
	CString extFilter = listExt[mode] + L"||";
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		m_ed1.SetWindowText(fileName);
	}
}


void CDlgInsert2::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
}


void CDlgInsert2::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
}


void CDlgInsert2::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
}

void CDlgInsert2::OnBnClickedOk()
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
	DDSinfo di;
	stream s,s1;
	CString cstr;
	CString cstr1,cstr2;
	str fn;
	matrix mat;
	i32 i;
	i32 i1,i2;
	i32 x1,y1,x2,y2;
	//0-指向 1-PNG图片 2-索引图片 3-DDS图片 4-DDS引用
	switch(mode){
	case 0:
		pi.set_format(LINK);
		m_ed2.GetWindowText(cstr);
		i = _ttoi(cstr);
		if(iORr == CDlgInsert2::__INSERT){
			if(i>dlg->io.indexCount || i<0){
				MessageBox(L"添加该索引项后，不存在ID为"+cstr+L"的索引项喵！",L"提示喵");
				return;
			}
			if(i<pos && dlg->io.PICcontent[i].get_format() == LINK){
				MessageBox(L"添加该索引项后，ID为"+cstr+L"的索引项是指向型索引项喵！\r\n不能再由其他指向型索引项去指向它喵！",L"提示喵");
				return;
			}
			if(i==pos || i > pos && dlg->io.PICcontent[i-1].get_format() == LINK){
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
		if(iORr == CDlgInsert2::__INSERT){
			dlg->io.PICinsert(pos, pi, NULL);
		}else{
			dlg->io.PICreplace(pos, pi, NULL);
		}
		break;
	case 1:
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		if(!mat.loadPNG(fn)){
			MessageBox(L"读取PNG文件失败喵！",L"提示喵");
			return;
		}
		if(!dlg->io.PICpreprocess(mat, s, pi)){
			MessageBox(L"颜色表溢出，确保插入的PNG所含颜色与该IMG调色板所含颜色总数小于256！",L"提示喵");
			return;
		}
		m_ed4.GetWindowText(cstr1);
		m_ed5.GetWindowText(cstr2);
		pi.set_basePt(point(_ttoi(cstr1),_ttoi(cstr2)));
		m_ed6.GetWindowText(cstr1);
		m_ed7.GetWindowText(cstr2);
		pi.set_frmSize(size(_ttoi(cstr1),_ttoi(cstr2)));
		if(iORr == CDlgInsert2::__INSERT){
			dlg->io.PICinsert(pos, pi, s);
		}else{
			dlg->io.PICreplace(pos, pi, s);
		}
		break;
	case 2:
		m_ed1.GetWindowText(cstr);
		CStrToStr(cstr, fn);
		if(!s.loadFile(fn)){
			MessageBox(L"无法读取文件喵！",L"提示喵");
			return;
		}
		s.read(i1);
		if((b32)i1 != 0x73696F4B){
			MessageBox(L"该PID未能识别喵！",L"提示喵！");
			return;
		}
		s.read(i1);
		s.read(i1);
		s.read(i2);
		s.ptMoveTo(0);
		s.deleteStream(0, 16);
		s.compressData(s1, COMP_ZLIB);
		pi.set_format(ARGB1555);
		pi.set_comp(COMP_ZLIB);
		pi.set_dataSize(s1.getLen());
		pi.set_picSize(size(i1,i2));
		m_ed4.GetWindowText(cstr1);
		m_ed5.GetWindowText(cstr2);
		pi.set_basePt(point(_ttoi(cstr1),_ttoi(cstr2)));
		m_ed6.GetWindowText(cstr1);
		m_ed7.GetWindowText(cstr2);
		pi.set_frmSize(size(_ttoi(cstr1),_ttoi(cstr2)));
		if(iORr == CDlgInsert2::__INSERT){
			dlg->io.PICinsert(pos, pi, s1);
		}else{
			dlg->io.PICreplace(pos, pi, s1);
		}
		break;
	case 3:
		m_ed8.GetWindowText(cstr);//DDSUSED
		i = _ttoi(cstr);
		if(i>(i32)dlg->io.DDScontent.size()-1){
			MessageBox(L"不存在ID为"+cstr+L"的DDS图像喵！\r\n最大的DDS图像ID为"+NumToCStr(dlg->io.DDScontent.size()-1)+L"喵！",L"提示喵");
			return;
		}
		dlg->io.GetDDSInfo(i, di);
		pi.set_format((colorFormat)di.get_fourCCID());
		pi.set_comp(COMP_ZLIB2);
		pi.set_DDSIDused((b32)i);
		m_ed9.GetWindowText(cstr1);
		m_ed10.GetWindowText(cstr2);
		x1 = _ttoi(cstr1);
		x2 = _ttoi(cstr2);
		m_ed11.GetWindowText(cstr1);
		m_ed12.GetWindowText(cstr2);
		y1 = _ttoi(cstr1);
		y2 = _ttoi(cstr2);
		if(x1>=x2 || y1>=y2){
			MessageBox(L"右下角的坐标两点必须都大于左上角的坐标喵！",L"提示喵");
			return;
		}
		if(x2>=(i32)di.get_width() || y2>=(i32)di.get_height() || x1<=0 || y1<=0){
			MessageBox(L"所有坐标点必须都位于DDS图像内喵！",L"提示喵");
			return;
		}
		pi.set_DDSpointLT(point(x1,y1));
		pi.set_DDSpointRB(point(x2,y2));
		pi.set_picSize(size(x2-x1,y2-y1));
		pi.set_dataSize(0);
		m_ed4.GetWindowText(cstr1);
		m_ed5.GetWindowText(cstr2);
		pi.set_basePt(point(_ttoi(cstr1),_ttoi(cstr2)));
		m_ed6.GetWindowText(cstr1);
		m_ed7.GetWindowText(cstr2);
		pi.set_frmSize(size(_ttoi(cstr1),_ttoi(cstr2)));
		if(iORr == CDlgInsert2::__INSERT){
			dlg->io.PICinsert(pos, pi, NULL);
		}else{
			dlg->io.PICreplace(pos, pi, NULL);
		}
		break;
	}
	if(iORr == CDlgInsert2::__INSERT){
		MessageBox(L"插入成功喵！",L"提示喵！");
	}else{
		MessageBox(L"替换成功喵！",L"提示喵！");
	}
	dlg->updatePIClist();
	dlg->updateNPKInfo();
	dlg->updateIMGInfo();
	dlg->updatePICInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsert2::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//0-指向 1-PNG图片 2-索引图片 3-DDS图片
	ShowWindow(SW_HIDE);
}