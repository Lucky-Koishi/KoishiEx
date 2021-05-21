// ModalInsertPicturePatch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalInsertPicturePatch.h"
#include "afxdialogex.h"


// ModalInsertPicturePatch �Ի���

IMPLEMENT_DYNAMIC(ModalInsertPicturePatch, CDialogEx)

ModalInsertPicturePatch::ModalInsertPicturePatch(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalInsertPicturePatch::IDD, pParent){

}

ModalInsertPicturePatch::~ModalInsertPicturePatch(){
}

void ModalInsertPicturePatch::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalInsertPicturePatch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ModalInsertPicturePatch::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalInsertPicturePatch::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalInsertPicturePatch::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_FORMAT1, &ModalInsertPicturePatch::OnBnClickedRadioFormat1)
	ON_BN_CLICKED(IDC_RADIO_FORMAT2, &ModalInsertPicturePatch::OnBnClickedRadioFormat2)
	ON_BN_CLICKED(IDC_RADIO_FORMAT3, &ModalInsertPicturePatch::OnBnClickedRadioFormat3)
	ON_BN_CLICKED(IDC_RADIO_FORMAT4, &ModalInsertPicturePatch::OnBnClickedRadioFormat4)
	ON_BN_CLICKED(IDC_RADIO_METHOD1, &ModalInsertPicturePatch::OnBnClickedRadioMethod1)
	ON_BN_CLICKED(IDC_RADIO_METHOD2, &ModalInsertPicturePatch::OnBnClickedRadioMethod2)
	ON_BN_CLICKED(IDOK, &ModalInsertPicturePatch::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalInsertPicturePatch ��Ϣ�������


BOOL ModalInsertPicturePatch::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(1);
	out.operate = 1;
	GET_CTRL(CButton, IDC_CHECK1)->EnableWindow(FALSE);
	if(in.version == V4 || in.version == V6){
		GET_CTRL(CButton, IDC_RADIO_FORMAT1)->SetCheck(1);
		GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(FALSE);
		out.outputFormat = 1;
	}else{
		GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT2)->SetCheck(1);
		out.outputFormat = 2;
	}
	GET_CTRL(CButton, IDC_RADIO_METHOD1)->SetCheck(1);
	out.inputFormat = 1;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ModalInsertPicturePatch::OnBnClickedButton1(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString defExt = L"PNGͼ��(*.png)|*.png";
	CString extFilter = L"PNGͼ��(*.png)|*.png||";
	if(out.inputFormat == 2){
		defExt = L"IMG�ļ�(*.IMG)|*.img";
		extFilter = L"IMG�ļ�(*.IMG)|*.img||";
	}
	CString fileName;
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(fileName);
	}
}


void ModalInsertPicturePatch::OnBnClickedRadioOperate1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 1;
	GET_CTRL(CButton, IDC_CHECK1)->EnableWindow(FALSE);
}


void ModalInsertPicturePatch::OnBnClickedRadioOperate2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.operate = 2;
	GET_CTRL(CButton, IDC_CHECK1)->EnableWindow(TRUE);
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 1;
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 2;
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 3;
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.outputFormat = 4;
}


void ModalInsertPicturePatch::OnBnClickedRadioMethod1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.inputFormat = 1;
	GET_CTRL(CStatic, IDC_STATIC_HINT)->SetWindowText(L"��ѡ�����֡�Ŷ�Ӧ���ļ�");
}


void ModalInsertPicturePatch::OnBnClickedRadioMethod2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	out.inputFormat = 2;
	GET_CTRL(CStatic, IDC_STATIC_HINT)->SetWindowText(L"��ѡ���ⲿIMG�ļ�");
}


void ModalInsertPicturePatch::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString fileName;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(fileName);
	if(fileName.GetLength() <= 4){
		MessageBox(L"��������д�ļ�������");
		return;
	}
	out.PNGcount = 0;
	if(out.inputFormat == 1){
		int pathSpl = fileName.ReverseFind('\\');
		out.filePath = fileName.Left(pathSpl+1);
		CString shortName = fileName.Right(fileName.GetLength()-pathSpl-1);
		if(shortName.GetLength() > 4){
			CString countCStr = shortName.Left(shortName.GetLength()-4);
			out.PNGcount = _ttoi(countCStr) + 1;
		}else{
			out.PNGcount = _ttoi(shortName) + 1;
		}
	}else{
		out.filePath = fileName;
	}
	CDialogEx::OnOK();
}
