// ModalPreference.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalPreference.h"
#include "afxdialogex.h"
#include "ExRabbitDlg.h"


// ModalPreference �Ի���

IMPLEMENT_DYNAMIC(ModalPreference, CDialogEx)

ModalPreference::ModalPreference(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalPreference::IDD, pParent)
{

}

ModalPreference::~ModalPreference()
{
}

void ModalPreference::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalPreference, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE1, &ModalPreference::OnBnClickedButtonPreference1)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE2, &ModalPreference::OnBnClickedButtonPreference2)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE3, &ModalPreference::OnBnClickedButtonPreference3)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE4, &ModalPreference::OnBnClickedButtonPreference4)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE5, &ModalPreference::OnBnClickedButtonPreference5)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE6, &ModalPreference::OnBnClickedButtonPreference6)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE7, &ModalPreference::OnBnClickedButtonPreference7)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE8, &ModalPreference::OnBnClickedButtonPreference8)
	ON_BN_CLICKED(IDC_BUTTON_PREFERENCE9, &ModalPreference::OnBnClickedButtonPreference9)
	ON_BN_CLICKED(IDOK, &ModalPreference::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SETPIC1, &ModalPreference::OnBnClickedButtonSetpic1)
	ON_BN_CLICKED(IDC_BUTTON_SETPIC2, &ModalPreference::OnBnClickedButtonSetpic2)
END_MESSAGE_MAP()


// ModalPreference ��Ϣ�������


void ModalPreference::OnBnClickedButtonPreference1(){
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


void ModalPreference::OnBnClickedButtonPreference2(){
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
				modifiedProfile.NPKdictPath = filePath;
			}
		}
		pMalloc->Release();
	}
}


void ModalPreference::OnBnClickedButtonPreference3(){
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
				modifiedProfile.avatarPath = filePath;
			}
		}
		pMalloc->Release();
	}
}


void ModalPreference::OnBnClickedButtonPreference4(){
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


void ModalPreference::OnBnClickedButtonPreference5(){
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
	modifiedProfile.canvasColor0 = clr;
}


void ModalPreference::OnBnClickedButtonPreference6(){
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
	modifiedProfile.canvasColor1 = clr;
}


void ModalPreference::OnBnClickedButtonPreference7(){
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
	modifiedProfile.canvasColor2 = clr;
}


void ModalPreference::OnBnClickedButtonPreference8(){
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
	modifiedProfile.avatarColor0 = clr;
}


void ModalPreference::OnBnClickedButtonPreference9(){
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
	modifiedProfile.avatarColor1 = clr;
}


BOOL ModalPreference::OnInitDialog(){
	CDialogEx::OnInitDialog();

	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE1)->SetWindowText(modifiedProfile.outputPath);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE2)->SetWindowText(modifiedProfile.NPKdictPath);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE3)->SetWindowText(modifiedProfile.avatarPath);
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE4)->SetWindowText(NumToCStr(modifiedProfile.mainColor));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE5)->SetWindowText(NumToCStr(modifiedProfile.canvasColor0));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE6)->SetWindowText(NumToCStr(modifiedProfile.canvasColor1));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE7)->SetWindowText(NumToCStr(modifiedProfile.canvasColor2));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE8)->SetWindowText(NumToCStr(modifiedProfile.avatarColor0));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE9)->SetWindowText(NumToCStr(modifiedProfile.avatarColor1));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE10)->SetWindowText(NumToCStr(modifiedProfile.avatarModelSize));
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE11)->SetWindowText(NumToCStr(modifiedProfile.miniSecPerFrame));
	return TRUE;
}


void ModalPreference::OnBnClickedOk(){
	CString sTemp;
	int iTemp;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE10)->GetWindowText(sTemp);
	iTemp = _ttoi(sTemp);
	if(iTemp < 0)
		iTemp = 0;
	if(iTemp > 3)
		iTemp = 3;
	modifiedProfile.avatarModelSize = iTemp;
	GET_CTRL(CEdit, IDC_EDIT_PREFERENCE11)->GetWindowText(sTemp);
	iTemp = _ttoi(sTemp);
	if(iTemp < 10)
		iTemp = 10;
	if(iTemp > 3000)
		iTemp = 3000;
	modifiedProfile.miniSecPerFrame = iTemp;
	modifiedProfile.saveProfile();
	CDialogEx::OnOK();
}


void ModalPreference::OnBnClickedButtonSetpic1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void ModalPreference::OnBnClickedButtonSetpic2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
