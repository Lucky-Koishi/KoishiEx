// ModalSoundInsert.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ModalSoundInsert.h"
#include "afxdialogex.h"


// ModalSoundInsert �Ի���

IMPLEMENT_DYNAMIC(ModalSoundInsert, CDialogEx)

ModalSoundInsert::ModalSoundInsert(CWnd* pParent /*=NULL*/)	: CDialogEx(ModalSoundInsert::IDD, pParent){
}

ModalSoundInsert::~ModalSoundInsert(){
}

void ModalSoundInsert::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalSoundInsert, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalSoundInsert::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalSoundInsert::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalSoundInsert::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_INPUT1, &ModalSoundInsert::OnBnClickedRadioInput1)
	ON_BN_CLICKED(IDC_RADIO_INPUT2, &ModalSoundInsert::OnBnClickedRadioInput2)
	ON_BN_CLICKED(IDC_RADIO_INPUT3, &ModalSoundInsert::OnBnClickedRadioInput3)
	ON_BN_CLICKED(IDC_RADIO_INPUT4, &ModalSoundInsert::OnBnClickedRadioInput4)
	ON_BN_CLICKED(IDC_RADIO_CONFLICK1, &ModalSoundInsert::OnBnClickedRadioConflick1)
	ON_BN_CLICKED(IDC_RADIO_CONFLICK2, &ModalSoundInsert::OnBnClickedRadioConflick2)
	ON_BN_CLICKED(IDC_RADIO_CONFLICK3, &ModalSoundInsert::OnBnClickedRadioConflick3)
	ON_BN_CLICKED(IDC_BUTTON1, &ModalSoundInsert::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &ModalSoundInsert::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalSoundInsert ��Ϣ�������
BOOL ModalSoundInsert::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"new.wav");
	out.operate = 1;
	out.type = 1;
	out.conflict = 1;
	out.pathName = L"new.img";
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	GET_CTRL(CButton, IDC_RADIO_INPUT1)->SetCheck(1);
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

void ModalSoundInsert::OnBnClickedRadioOperate1(){
	out.operate = 1;
}

void ModalSoundInsert::OnBnClickedRadioOperate2(){
	out.operate = 2;
}

void ModalSoundInsert::OnBnClickedRadioOperate3(){
	out.operate = 3;
}

void ModalSoundInsert::OnBnClickedRadioInput1(){
	out.type = 1;
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(FALSE);
}

void ModalSoundInsert::OnBnClickedRadioInput2(){
	out.type = 2;
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(TRUE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(FALSE);
}

void ModalSoundInsert::OnBnClickedRadioInput3(){
	out.type = 3;
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(TRUE);
}

void ModalSoundInsert::OnBnClickedRadioInput4(){
	out.type = 4;
	GET_CTRL(CEdit, IDC_EDIT1)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_RADIO_CONFLICK3)->EnableWindow(TRUE);
}

void ModalSoundInsert::OnBnClickedRadioConflick1(){
	out.conflict = 1;
}

void ModalSoundInsert::OnBnClickedRadioConflick2(){
	out.conflict = 2;
}

void ModalSoundInsert::OnBnClickedRadioConflick3(){
	out.conflict = 3;
}

void ModalSoundInsert::OnBnClickedButton1(){
	//���
	if(out.type == 2){
		CString defExt = _T("��Ч�ļ�(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3");
		CString extFilter = _T("��Ч�ļ�(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3|������Ч(*.WAV)|*.WAV|vorbis��Ч(*.OGG)|*.OGG|MP3��Ч(*.MP3)|*.MP3||");
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

void ModalSoundInsert::OnBnClickedOk(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(out.fileName);
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(out.pathName);
	if(out.type == 2){
		stream s;
		if(!s.loadFile(CStrToStr(out.fileName))){
			MessageBox(L"δʶ����ļ�����",L"��ʾ��");
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
