// ModalSoundInsert.cpp : 实现文件
//

#include "stdafx.h"
#include "ExParrot.h"
#include "ModalSoundInsert.h"
#include "afxdialogex.h"


// ModalSoundInsert 对话框

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


// ModalSoundInsert 消息处理程序
BOOL ModalSoundInsert::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
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
	//浏览
	if(out.type == 2){
		CString defExt = _T("音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3");
		CString extFilter = _T("音效文件(*.WAV,*.OGG,*.MP3)|*.WAV;*.OGG;*.MP3|波形音效(*.WAV)|*.WAV|vorbis音效(*.OGG)|*.OGG|MP3音效(*.MP3)|*.MP3||");
		CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
		CString fileName;
		if(dlg.DoModal() == IDOK){
			fileName = dlg.GetPathName();
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(fileName);
			GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(Slashing(GetTail(fileName)));
		}
	}else if(out.type == 3){
		CString defExt = _T("NPK文件(*.NPK)|*.NPK");
		CString extFilter = _T("NPK文件(*.NPK)|*.NPK||");
		CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
		CString fileName;
		if(dlg.DoModal() == IDOK){
			fileName = dlg.GetPathName();
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(fileName);
		}
	}else if(out.type == 4){
		HWND hwnd= GetSafeHwnd();   //得到窗口句柄
		CString filePath= L"";	//得到文件路径
		LPMALLOC pMalloc;
		if(::SHGetMalloc(&pMalloc) == NOERROR){	//取得IMalloc分配器接口
			BROWSEINFO bi;
			TCHAR pszBuffer[MAX_PATH];
			LPITEMIDLIST pidl;   
			bi.hwndOwner = hwnd;
			bi.pidlRoot	= NULL;
			bi.pszDisplayName = pszBuffer;
			bi.lpszTitle = _T("选择文件夹");
			bi.ulFlags =  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
			bi.lpfn = NULL;
			bi.lParam = 0;
			bi.iImage = 0;
			if((pidl =::SHBrowseForFolder(&bi)) != NULL){//取得IMalloc分配器接口   
				if(::SHGetPathFromIDList(pidl, pszBuffer)){ //获得一个文件系统路径
					filePath = pszBuffer;
				}
				pMalloc->Free(pidl);	//释放内存
				if(filePath.GetLength()<=1){
					MessageBox(L"并不是有效的文件夹喵！",L"提示喵");
				}else{
					GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(filePath);
				}
			}
			pMalloc->Release();	//释放接口
		}
	}
}

void ModalSoundInsert::OnBnClickedOk(){
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CEdit, IDC_EDIT2)->GetWindowText(out.fileName);
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(out.pathName);
	if(out.type == 2){
		stream s;
		if(!s.loadFile(CStrToStr(out.fileName))){
			MessageBox(L"未识别的文件喵！",L"提示喵");
			return;
		}
	}else if(out.type == 3){
		NPKobject no;
		if(!no.loadFile(CStrToStr(out.fileName))){
			MessageBox(L"未识别的NPK文件喵！",L"提示喵");
			return;
		}
	}
	CDialogEx::OnOK();
}
