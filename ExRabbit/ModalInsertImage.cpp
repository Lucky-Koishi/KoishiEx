// ModalInsertImage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalInsertImage.h"
#include "afxdialogex.h"


// ModalInsertImage �Ի���

IMPLEMENT_DYNAMIC(ModalInsertImage, CDialogEx)

ModalInsertImage::ModalInsertImage(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalInsertImage::IDD, pParent)
{

}

ModalInsertImage::~ModalInsertImage()
{
}

void ModalInsertImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalInsertImage, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalInsertImage::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalInsertImage::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalInsertImage::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_INPUT1, &ModalInsertImage::OnBnClickedRadioInput1)
	ON_BN_CLICKED(IDC_RADIO_INPUT2, &ModalInsertImage::OnBnClickedRadioInput2)
	ON_BN_CLICKED(IDC_RADIO_INPUT3, &ModalInsertImage::OnBnClickedRadioInput3)
	ON_BN_CLICKED(IDC_RADIO_INPUT4, &ModalInsertImage::OnBnClickedRadioInput4)
	ON_BN_CLICKED(IDC_RADIO_VERSION1, &ModalInsertImage::OnBnClickedRadioVersion1)
	ON_BN_CLICKED(IDC_RADIO_VERSION2, &ModalInsertImage::OnBnClickedRadioVersion2)
	ON_BN_CLICKED(IDC_RADIO_VERSION3, &ModalInsertImage::OnBnClickedRadioVersion3)
	ON_BN_CLICKED(IDC_RADIO_VERSION4, &ModalInsertImage::OnBnClickedRadioVersion4)
	ON_BN_CLICKED(IDC_RADIO_CONFLICK1, &ModalInsertImage::OnBnClickedRadioConflick1)
	ON_BN_CLICKED(IDC_RADIO_CONFLICK2, &ModalInsertImage::OnBnClickedRadioConflick2)
	ON_BN_CLICKED(IDC_RADIO_CONFLICK3, &ModalInsertImage::OnBnClickedRadioConflick3)
	ON_BN_CLICKED(IDC_BUTTON1, &ModalInsertImage::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &ModalInsertImage::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalInsertImage ��Ϣ�������
BOOL ModalInsertImage::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"new.img");
	out.operate = 1;
	out.type = 1;
	out.newVersion = V2;
	out.conflict = 1;
	out.pathName = L"new.img";
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_VERSION1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->SetCheck(1);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(FALSE);
	if(in.firstInsert){
		out.operate = 3;
		GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(0);
		GET_CTRL(CButton, IDC_RADIO_OPERATE1)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE2)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(1);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ModalInsertImage::OnBnClickedRadioOperate1(){
	out.operate = 1;
}

void ModalInsertImage::OnBnClickedRadioOperate2(){
	out.operate = 2;
}

void ModalInsertImage::OnBnClickedRadioOperate3(){
	out.operate = 3;
}

void ModalInsertImage::OnBnClickedRadioInput1(){
	out.type = 1;
	GET_CTRL(CButton, IDC_RADIO_VERSION1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_VERSION2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_VERSION3)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_VERSION4)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(FALSE);
}

void ModalInsertImage::OnBnClickedRadioInput2(){
	out.type = 2;
	GET_CTRL(CButton, IDC_RADIO_VERSION1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION4)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(FALSE);
}

void ModalInsertImage::OnBnClickedRadioInput3(){
	out.type = 3;
	GET_CTRL(CButton, IDC_RADIO_VERSION1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION4)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(TRUE);
}

void ModalInsertImage::OnBnClickedRadioInput4(){
	out.type = 4;
	GET_CTRL(CButton, IDC_RADIO_VERSION1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_VERSION4)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(TRUE);
}

void ModalInsertImage::OnBnClickedRadioVersion1(){
	out.newVersion = V2;
}

void ModalInsertImage::OnBnClickedRadioVersion2(){
	out.newVersion = V4;
}

void ModalInsertImage::OnBnClickedRadioVersion3(){
	out.newVersion = V5;
}

void ModalInsertImage::OnBnClickedRadioVersion4(){
	out.newVersion = V6;
}

void ModalInsertImage::OnBnClickedRadioConflick1(){
	out.conflict = 1;
}

void ModalInsertImage::OnBnClickedRadioConflick2(){
	out.conflict = 2;
}

void ModalInsertImage::OnBnClickedRadioConflick3(){
	out.conflict = 3;
}

void ModalInsertImage::OnBnClickedButton1(){
	//���
	if(out.type == 2){
		CString defExt = _T("IMG�ļ�(*.IMG)|*.IMG");
		CString extFilter = _T("IMG�ļ�(*.IMG)|*.IMG||");
		CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
		CString fileName;
		if(dlg.DoModal() == IDOK){
			fileName = dlg.GetPathName();
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(fileName);
			GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(Slashing(GetTail(fileName)));
		}
	}else if(out.type == 3){
		CString defExt = _T("NPK�ļ�(*.NPK)|*.NPK");
		CString extFilter = _T("NPK�ļ�(*.NPK)|*.NPK||");
		CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
		CString fileName;
		if(dlg.DoModal() == IDOK){
			fileName = dlg.GetPathName();
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(fileName);
		}
	}else if(out.type == 4){
		HWND hwnd= GetSafeHwnd();   //�õ����ھ��
		CString filePath= L"";	//�õ��ļ�·��
		LPMALLOC pMalloc;
		if(::SHGetMalloc(&pMalloc) == NOERROR){	//ȡ��IMalloc�������ӿ�
			BROWSEINFO bi;
			TCHAR pszBuffer[MAX_PATH];
			LPITEMIDLIST pidl;   
			bi.hwndOwner = hwnd;
			bi.pidlRoot	= NULL;
			bi.pszDisplayName = pszBuffer;
			bi.lpszTitle = _T("ѡ���ļ���");
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
					MessageBox(L"��������Ч���ļ�������",L"��ʾ��");
				}else{
					GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(filePath);
				}
			}
			pMalloc->Release();	//�ͷŽӿ�
		}
	}
}

void ModalInsertImage::OnBnClickedOk(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(out.fileName);
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(out.pathName);
	if(out.type == 2){
		IMGobject io;
		if(!io.loadFile(CStrToStr(out.fileName))){
			MessageBox(L"δʶ���IMG�ļ�����",L"��ʾ��");
			return;
		}
	}else if(out.type == 3){
		NPKobject no;
		if(!no.loadFile(CStrToStr(out.fileName))){
			MessageBox(L"δʶ���NPK�ļ�����",L"��ʾ��");
			return;
		}
	}
	CDialogEx::OnOK();
}
