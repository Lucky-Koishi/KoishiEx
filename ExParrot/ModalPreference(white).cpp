// ModalPreference2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ModalPreference(white).h"
#include "afxdialogex.h"


// ModalPreference2 �Ի���

IMPLEMENT_DYNAMIC(ModalPreference2, CDialogEx)

ModalPreference2::ModalPreference2(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalPreference2::IDD, pParent)
{

}

ModalPreference2::~ModalPreference2()
{
}

void ModalPreference2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalPreference2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE1, &ModalPreference2::OnBnClickedButtonPreference1)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE2, &ModalPreference2::OnBnClickedButtonPreference2)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE3, &ModalPreference2::OnBnClickedButtonPreference3)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE4, &ModalPreference2::OnBnClickedButtonPreference4)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE5, &ModalPreference2::OnBnClickedButtonPreference5)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE6, &ModalPreference2::OnBnClickedButtonPreference6)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE7, &ModalPreference2::OnBnClickedButtonPreference7)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE8, &ModalPreference2::OnBnClickedButtonPreference8)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE9, &ModalPreference2::OnBnClickedButtonPreference9)
	ON_BN_CLICKED(IDC_BUTTON_SETPIC1, &ModalPreference2::OnBnClickedButtonSetpic1)
	ON_BN_CLICKED(IDC_BUTTON_SETPIC2, &ModalPreference2::OnBnClickedButtonSetpic2)
	ON_BN_CLICKED(IDOK, &ModalPreference2::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE10, &ModalPreference2::OnBnClickedButtonPreference10)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE11, &ModalPreference2::OnBnClickedButtonPreference11)
END_MESSAGE_MAP()


// ModalPreference2 ��Ϣ�������


void ModalPreference2::OnBnClickedButtonPreference1(){
	HWND hwnd= GetSafeHwnd();
	CString filePath= L"";
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("ѡ������ļ���");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){  
			if(::SHGetPathFromIDList(pidl, pszBuffer)){
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);
			if(filePath.GetLength()<=1){
				MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				GET_CTRL(CEdit, IDC_EDIT_PREFERENCE1)->SetWindowText(filePath);
				modifiedProfile.outputPath = filePath;
			}
		}
		pMalloc->Release();
	}
}


void ModalPreference2::OnBnClickedButtonPreference2(){
	HWND hwnd= GetSafeHwnd();
	CString filePath= L"";
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("ѡ����Դ�ļ���");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){  
			if(::SHGetPathFromIDList(pidl, pszBuffer)){
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);
			if(filePath.GetLength()<=1){
				MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				GET_CTRL(CEdit, IDC_EDIT_PREFERENCE2)->SetWindowText(filePath);
				modifiedProfile.sourcePath = filePath;
			}
		}
		pMalloc->Release();
	}
}


void ModalPreference2::OnBnClickedButtonPreference3(){
	HWND hwnd= GetSafeHwnd();
	CString filePath= L"";
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR){
		BROWSEINFO bi;
		TCHAR pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;   
		bi.hwndOwner = hwnd;
		bi.pidlRoot	= NULL;
		bi.pszDisplayName = pszBuffer;
		bi.lpszTitle = _T("ѡ����Դ�ļ���");
		bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		if((pidl =::SHBrowseForFolder(&bi)) != NULL){  
			if(::SHGetPathFromIDList(pidl, pszBuffer)){
				filePath = pszBuffer;
			}
			pMalloc->Free(pidl);
			if(filePath.GetLength()<=1){
				MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
			}else{
				GET_CTRL(CEdit, IDC_EDIT_PREFERENCE3)->SetWindowText(filePath);
				modifiedProfile.videoPath = filePath;
			}
		}
		pMalloc->Release();
	}
}


void ModalPreference2::OnBnClickedButtonPreference4(){
	CString s;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE4)->GetWindowText(s);
	DWORD clr = _ttoi(s);
	CColorDialog dlg(clr, CC_FULLOPEN | CC_RGBINIT, this);
	if(IDOK == dlg.DoModal()){
		clr = dlg.GetColor();
	}else{
		return;
	}
	s.Format(L"%d", clr);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE4)->SetWindowText(s);
	modifiedProfile.mainColor = clr;
}


void ModalPreference2::OnBnClickedButtonPreference5(){
	CString s;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE5)->GetWindowText(s);
	DWORD clr = _ttoi(s);
	CColorDialog dlg(clr, CC_FULLOPEN | CC_RGBINIT, this);
	if(IDOK == dlg.DoModal()){
		clr = dlg.GetColor();
	}else{
		return;
	}
	s.Format(L"%d", clr);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE5)->SetWindowText(s);
	modifiedProfile.audioBackColor = clr;
}


void ModalPreference2::OnBnClickedButtonPreference6()
{
	CString s;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE6)->GetWindowText(s);
	DWORD clr = _ttoi(s);
	CColorDialog dlg(clr, CC_FULLOPEN | CC_RGBINIT, this);
	if(IDOK == dlg.DoModal()){
		clr = dlg.GetColor();
	}else{
		return;
	}
	s.Format(L"%d", clr);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE6)->SetWindowText(s);
	modifiedProfile.channel1Color = clr;
}


void ModalPreference2::OnBnClickedButtonPreference7()
{
	CString s;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE7)->GetWindowText(s);
	DWORD clr = _ttoi(s);
	CColorDialog dlg(clr, CC_FULLOPEN | CC_RGBINIT, this);
	if(IDOK == dlg.DoModal()){
		clr = dlg.GetColor();
	}else{
		return;
	}
	s.Format(L"%d", clr);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE7)->SetWindowText(s);
	modifiedProfile.channel2Color = clr;
}


void ModalPreference2::OnBnClickedButtonPreference8()
{
	CString s;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE8)->GetWindowText(s);
	DWORD clr = _ttoi(s);
	CColorDialog dlg(clr, CC_FULLOPEN | CC_RGBINIT, this);
	if(IDOK == dlg.DoModal()){
		clr = dlg.GetColor();
	}else{
		return;
	}
	s.Format(L"%d", clr);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE8)->SetWindowText(s);
	modifiedProfile.volumeColor = clr;
}


void ModalPreference2::OnBnClickedButtonPreference9()
{
	CString s;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE9)->GetWindowText(s);
	DWORD clr = _ttoi(s);
	CColorDialog dlg(clr, CC_FULLOPEN | CC_RGBINIT, this);
	if(IDOK == dlg.DoModal()){
		clr = dlg.GetColor();
	}else{
		return;
	}
	s.Format(L"%d", clr);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE9)->SetWindowText(s);
	modifiedProfile.MP3defaultColor = clr;
}


void ModalPreference2::OnBnClickedButtonSetpic1()
{
	CString defExt = L"PNGͼ��(*.png)|*.png";
	CString extFilter = L"PNGͼ��(*.png)|*.png||";
	CString filePath, extName;
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		filePath = dlg.GetPathName();
		image mPic;
		loadPNG(mPic, CStrToStr(filePath));
		mPic.clip(0, 39, 0, 149);
		makeBMP(mPic, CStrToStr(modifiedProfile.getSupportPath() + L"LOGO.bmp"));
		MessageBox(L"����LOGO���������ע�⣺�ߴ��ü���150��40��",L"��ʾ��");
	}
}


void ModalPreference2::OnBnClickedButtonSetpic2()
{
	CString defExt = L"PNGͼ��(*.png)|*.png";
	CString extFilter = L"PNGͼ��(*.png)|*.png||";
	CString filePath, extName;
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		filePath = dlg.GetPathName();
		image mPic;
		loadPNG(mPic, CStrToStr(filePath));
		makePNG(mPic, CStrToStr(modifiedProfile.getSupportPath() + L"back.png"));
		MessageBox(L"���ñ����������",L"��ʾ��");
	}
}


void ModalPreference2::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sTemp;
	int iTemp;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE10)->GetWindowText(sTemp);
	iTemp = _ttoi(sTemp);
	if(iTemp < 0)
		iTemp = 0;
	if(iTemp > 3)
		iTemp = 3;
	modifiedProfile.outputQuality = iTemp;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE11)->GetWindowText(sTemp);
	modifiedProfile.artist = sTemp;
	modifiedProfile.outputQuality = GET_CTRL(CComboBox, IDC_COMBO_PREFERENCE10)->GetCurSel();
	modifiedProfile.saveProfile();
	CDialogEx::OnOK();
}


void ModalPreference2::OnBnClickedButtonPreference10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void ModalPreference2::OnBnClickedButtonPreference11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL ModalPreference2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE1)->SetWindowText(modifiedProfile.outputPath);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE2)->SetWindowText(modifiedProfile.sourcePath);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE3)->SetWindowText(modifiedProfile.videoPath);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE4)->SetWindowText(NumToCStr(modifiedProfile.mainColor));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE5)->SetWindowText(NumToCStr(modifiedProfile.audioBackColor));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE6)->SetWindowText(NumToCStr(modifiedProfile.channel1Color));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE7)->SetWindowText(NumToCStr(modifiedProfile.channel2Color));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE8)->SetWindowText(NumToCStr(modifiedProfile.volumeColor));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE9)->SetWindowText(NumToCStr(modifiedProfile.MP3defaultColor));
	//GET_CTRL(CEdit, IDC_EDIT_PREFERENCE10)->SetWindowText(NumToCStr(modifiedProfile.outputQuality));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE11)->SetWindowText(modifiedProfile.artist);
	CComboBox *cb = GET_CTRL(CComboBox, IDC_COMBO_PREFERENCE10);
	cb->ResetContent();
	cb->AddString(L"WAV �������ʣ�������");
	cb->AddString(L"OGG Ʒ�ʽϲ�����С");
	cb->AddString(L"OGG Ʒ��һ�㣬��Լ�ռ�");
	cb->AddString(L"OGG Ʒ����ռ���");
	cb->AddString(L"OGG Ʒ�ʳ�ɫ����ռ�ռ�");
	cb->AddString(L"OGG Ʒ����������ռ�ռ�");
	cb->SetCurSel(MIN(5, modifiedProfile.outputQuality));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
