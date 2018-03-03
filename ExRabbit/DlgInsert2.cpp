// DlgInsert2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "DlgInsert2.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"

// CDlgInsert2 �Ի���

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


// CDlgInsert2 ��Ϣ�������


void CDlgInsert2::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	int pos = dlg->m_lPicture.GetSelectionMark();
	PICinfo pi;
	dlg->io.GetPICInfo(pos,pi);

	int cm = m_cb1.GetCurSel();
	mode = 0;//0-ָ�� 1-PNGͼƬ 2-����ͼƬ 3-DDS����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString listExt[4] = {
		_T("pngͼ��(*.png)|*.png"),
		_T("pngͼ��(*.png)|*.png"),
		_T("��������(*.pid)|*.pid"),
		_T("ddsͼ��(*.dds)|*.dds")
	}; 
	listExt[0].LoadStringW(IDS_STRING_PNGTYPE);
	listExt[1].LoadStringW(IDS_STRING_PNGTYPE);
	listExt[2].LoadStringW(IDS_STRING_INDEXTYPE);
	listExt[3].LoadStringW(IDS_STRING_DDSTYPE);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(1);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(0);
}


void CDlgInsert2::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(1);
	m_ch3.SetCheck(0);
}


void CDlgInsert2::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ch1.SetCheck(0);
	m_ch2.SetCheck(0);
	m_ch3.SetCheck(1);
}

void CDlgInsert2::OnBnClickedOk()
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
	DDSinfo di;
	stream s,s1;
	CString cstr;
	CString cstr1,cstr2;
	CString info, title;
	str fn;
	matrix mat;
	i32 i;
	i32 i1,i2;
	i32 x1,y1,x2,y2;
	//0-ָ�� 1-PNGͼƬ 2-����ͼƬ 3-DDSͼƬ 4-DDS����
	switch(mode){
	case 0:
		pi.set_format(LINK);
		m_ed2.GetWindowText(cstr);
		i = _ttoi(cstr);
		if(iORr == CDlgInsert2::__INSERT){
			if(i>dlg->io.indexCount || i<0){
				info.LoadStringW(IDS_INDEXNOTEXiST);
				info.Format(info, cstr);
				title.LoadStringW(IDS_MESSAGE_TITLE);
				MessageBox(info, title);
				//MessageBox(L"��Ӹ�������󣬲�����IDΪ"+cstr+L"������������",L"��ʾ��");
				return;
			}
			if(i<pos && dlg->io.PICcontent[i].get_format() == LINK){
				info.LoadStringW(IDS_STRING_INDEXLINK);
				info.Format(info, cstr);
				title.LoadStringW(IDS_MESSAGE_TITLE);
				MessageBox(info, title);
				//MessageBox(L"��Ӹ��������IDΪ"+cstr+L"����������ָ��������������\r\n������������ָ����������ȥָ��������",L"��ʾ��");
				return;
			}
			if(pos == -1 || i==pos || i > pos && dlg->io.PICcontent[i-1].get_format() == LINK){
				info.LoadStringW(IDS_STRING_INDEXLINK);
				info.Format(info, cstr);
				title.LoadStringW(IDS_MESSAGE_TITLE);
				MessageBox(info, title);
				//MessageBox(L"��Ӹ��������IDΪ"+cstr+L"����������ָ��������������\r\n������������ָ����������ȥָ��������",L"��ʾ��");
				return;
			}
		}else{
			if(i>dlg->io.indexCount-1 || i<0){
				info.LoadStringW(IDS_INDEXNOTEXiST);
				info.Format(info, cstr);
				title.LoadStringW(IDS_MESSAGE_TITLE);
				MessageBox(info, title);
				//MessageBox(L"������IDΪ"+cstr+L"������������",L"��ʾ��");
				return;
			}
			if(dlg->io.PICcontent[i].get_format() == LINK){
				info.LoadStringW(IDS_STRING_ALREADYINDEXLINK);
				info.Format(info, cstr);
				title.LoadStringW(IDS_MESSAGE_TITLE);
				MessageBox(info, title);
				//MessageBox(L"IDΪ"+cstr+L"���������Ѿ���ָ��������������\r\n������������ָ����������ȥָ��������",L"��ʾ��");
				return;
			}
			if(i==pos){
				info.LoadStringW(IDS_STRING_UNABLETOLINKTOITSELF);
				title.LoadStringW(IDS_MESSAGE_TITLE);
				MessageBox(info, title);
				//MessageBox(L"ָ�����������ָ���Լ�����",L"��ʾ��");
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
			info.LoadStringW(IDS_STRING_FAILEDTOREADPNGFILE);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"��ȡPNG�ļ�ʧ������",L"��ʾ��");
			return;
		}
		if(!dlg->io.PICpreprocess(mat, s, pi)){
			info.LoadStringW(IDS_COLORSHEETOVERFLOW);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"��ɫ�������ȷ�������PNG������ɫ���IMG��ɫ��������ɫ����С��256��",L"��ʾ��");
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
			info.LoadStringW(IDS_STRING_FAILEDTOREADFILE);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"�޷���ȡ�ļ�����",L"��ʾ��");
			return;
		}
		s.read(i1);
		if((b32)i1 != 0x73696F4B){
			info.LoadStringW(IDS_STRING_PIDNOTRECOGNIZED);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"��PIDδ��ʶ������",L"��ʾ����");
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
			info.LoadStringW(IDS_DDSIMAGENOTEXIST);
			info.Format(info, cstr, NumToCStr(dlg->io.DDScontent.size() - 1));
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"������IDΪ"+cstr+L"��DDSͼ������\r\n����DDSͼ��IDΪ"+NumToCStr(dlg->io.DDScontent.size()-1)+L"����",L"��ʾ��");
			return;
		}
		dlg->io.GetDDSInfo(i, di);
		pi.set_format((colorFormat)di.get_fourCCID());
		pi.set_comp(COMP_ZLIB2);
		pi.set_DDSIDused((b32)i);
		m_ed9.GetWindowText(cstr1);
		m_ed10.GetWindowText(cstr2);
		x1 = _ttoi(cstr1);
		y1 = _ttoi(cstr2);
		m_ed11.GetWindowText(cstr1);
		m_ed12.GetWindowText(cstr2);
		x2 = _ttoi(cstr1);
		y2 = _ttoi(cstr2);
		if(x1>=x2 || y1>=y2){
			info.LoadStringW(IDS_STRING_LOWERTWOPOINTSREQUIRY);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"���½ǵ�����������붼�������Ͻǵ���������",L"��ʾ��");
			return;
		}
		if(x2>=(i32)di.get_width() || y2>=(i32)di.get_height() || x1<=0 || y1<=0){
			info.LoadStringW(IDS_STRING_POINTSINDDSREQUIRY);
			title.LoadStringW(IDS_MESSAGE_TITLE);
			MessageBox(info, title);
			//MessageBox(L"�����������붼λ��DDSͼ��������",L"��ʾ��");
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
		info.LoadStringW(IDS_STRING_INSERTFINISHED);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		MessageBox(info, title);
		//MessageBox(L"����ɹ�����",L"��ʾ����");
		dlg->m_lPicture.InsertItem(pos, NumToCStr(pos));
	}else{
		info.LoadStringW(IDS_STRING_REPLACEFINISHED);
		title.LoadStringW(IDS_MESSAGE_TITLE);
		MessageBox(info, title);
		//MessageBox(L"�滻�ɹ�����",L"��ʾ����");
	}
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
			dlg->m_lPicture.SetItemText(pos, 5, L"DDS"+NumToCStr(dlg->io.PICcontent[pos].get_DDSIDused())+L":"+PtToCStr(dlg->io.PICcontent[pos].get_DDSpointLT())+L"-"+PtToCStr(dlg->io.PICcontent[pos].get_DDSpointRB()));
		}
	}
	//dlg->updatePIClist();
	dlg->updateDDSlist();
	dlg->updateNPKInfo();
	dlg->updateIMGInfo();
	dlg->updatePICInfo();
	ShowWindow(SW_HIDE);
}


void CDlgInsert2::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//0-ָ�� 1-PNGͼƬ 2-����ͼƬ 3-DDSͼƬ
	ShowWindow(SW_HIDE);
}