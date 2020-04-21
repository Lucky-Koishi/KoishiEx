// ModalInsertTexture.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalInsertTexture.h"
#include "afxdialogex.h"


// ModalInsertTexture �Ի���

IMPLEMENT_DYNAMIC(ModalInsertTexture, CDialogEx)

ModalInsertTexture::ModalInsertTexture(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalInsertTexture::IDD, pParent)
{

}

ModalInsertTexture::~ModalInsertTexture()
{
}

void ModalInsertTexture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalInsertTexture, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalInsertTexture::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalInsertTexture::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalInsertTexture::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE4, &ModalInsertTexture::OnBnClickedRadioOperate4)
	ON_BN_CLICKED(IDC_RADIO_FORMAT1, &ModalInsertTexture::OnBnClickedRadioFormat1)
	ON_BN_CLICKED(IDC_RADIO_FORMAT2, &ModalInsertTexture::OnBnClickedRadioFormat2)
	ON_BN_CLICKED(IDC_RADIO_FORMAT3, &ModalInsertTexture::OnBnClickedRadioFormat3)
	ON_BN_CLICKED(IDC_RADIO_FORMAT4, &ModalInsertTexture::OnBnClickedRadioFormat4)
	ON_BN_CLICKED(IDC_BUTTON_RESOURCE, &ModalInsertTexture::OnBnClickedButtonResource)
	ON_BN_CLICKED(IDOK, &ModalInsertTexture::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalInsertTexture ��Ϣ�������


BOOL ModalInsertTexture::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	out.fileName = L"";
	out.inputFormat = 0;
	
	if(in.firstInsert){
		GET_CTRL(CButton, IDC_RADIO_OPERATE1)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE2)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE3)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE4)->SetCheck(1);
		out.operate = 4;
	}else{
		GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(1);
		out.operate = 2;
	}
	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->SetCheck(1);
	out.outputFormat = 1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ModalInsertTexture::updateRadio(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(out.operate == 1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(out.operate == 2);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(out.operate == 3);
	GET_CTRL(CButton, IDC_RADIO_OPERATE4)->SetCheck(out.operate == 4);
	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->SetCheck(out.outputFormat == 1);
	GET_CTRL(CButton, IDC_RADIO_FORMAT2)->SetCheck(out.outputFormat == 2);
	GET_CTRL(CButton, IDC_RADIO_FORMAT3)->SetCheck(out.outputFormat == 3);
	GET_CTRL(CButton, IDC_RADIO_FORMAT4)->SetCheck(out.outputFormat == 4);
}

void ModalInsertTexture::OnBnClickedRadioOperate1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 1;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedRadioOperate2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 2;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedRadioOperate3(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 3;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedRadioOperate4(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 4;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedRadioFormat1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 1;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedRadioFormat2(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 2;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedRadioFormat3(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 3;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedRadioFormat4(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 4;
	updateRadio();
}


void ModalInsertTexture::OnBnClickedButtonResource()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defExt = L"PNGͼ��(*.png)|*.png";
	CString extFilter = L"PNGͼ��(*.png)|*.png|DDSͼ��(*.dds)|*.dds||";
	CString filePath, extName;
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		filePath = dlg.GetPathName();
		if(filePath.GetLength() >= 4){
			extName = filePath.Right(4);
			if(extName == L".PNG" || extName == L".png"){
				out.inputFormat = 1;
			}
			if(extName == L".DDS" || extName == L".dds"){
				out.inputFormat = 2;
			}
		}
		GET_CTRL(CEdit, IDC_EDIT_RESOURCE)->SetWindowText(filePath);
	}
}


void ModalInsertTexture::OnBnClickedOk(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GET_CTRL(CEdit, IDC_EDIT_RESOURCE)->GetWindowText(out.fileName);
	//�жϽ�ֹ����
	image mat;
	DDSobject dds;
	if(out.inputFormat == 1){
		if(!KoishiImageTool::loadPNG(mat, CStrToStr(out.fileName))){
			MessageBox(L"�޷���ȡ��PNG�ļ�����",L"������");
			return;
		}
	}
	if(out.inputFormat == 2){
		if(!dds.loadFile(CStrToStr(out.fileName))){
			MessageBox(L"�޷�ʶ���DDS�ļ���",L"����");
			return;
		}
		if(!dds.uncompress(mat)){
			MessageBox(L"�޷��������ļ���DXT��ʽ��",L"����");
			return;
		}
	}
	mat.destory();
	out.context = GetParent();
	CDialogEx::OnOK();
}
