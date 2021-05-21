// ModalInsertPicturePatch.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalInsertPicturePatch.h"
#include "afxdialogex.h"


// ModalInsertPicturePatch 对话框

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


// ModalInsertPicturePatch 消息处理程序


BOOL ModalInsertPicturePatch::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常: OCX 属性页应返回 FALSE
}


void ModalInsertPicturePatch::OnBnClickedButton1(){
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = L"PNG图像(*.png)|*.png";
	CString extFilter = L"PNG图像(*.png)|*.png||";
	if(out.inputFormat == 2){
		defExt = L"IMG文件(*.IMG)|*.img";
		extFilter = L"IMG文件(*.IMG)|*.img||";
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
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 1;
	GET_CTRL(CButton, IDC_CHECK1)->EnableWindow(FALSE);
}


void ModalInsertPicturePatch::OnBnClickedRadioOperate2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.operate = 2;
	GET_CTRL(CButton, IDC_CHECK1)->EnableWindow(TRUE);
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.outputFormat = 1;
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.outputFormat = 2;
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat3()
{
	// TODO: 在此添加控件通知处理程序代码
	out.outputFormat = 3;
}


void ModalInsertPicturePatch::OnBnClickedRadioFormat4()
{
	// TODO: 在此添加控件通知处理程序代码
	out.outputFormat = 4;
}


void ModalInsertPicturePatch::OnBnClickedRadioMethod1()
{
	// TODO: 在此添加控件通知处理程序代码
	out.inputFormat = 1;
	GET_CTRL(CStatic, IDC_STATIC_HINT)->SetWindowText(L"请选择最大帧号对应的文件");
}


void ModalInsertPicturePatch::OnBnClickedRadioMethod2()
{
	// TODO: 在此添加控件通知处理程序代码
	out.inputFormat = 2;
	GET_CTRL(CStatic, IDC_STATIC_HINT)->SetWindowText(L"请选择外部IMG文件");
}


void ModalInsertPicturePatch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(fileName);
	if(fileName.GetLength() <= 4){
		MessageBox(L"请认真填写文件名喵！");
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
