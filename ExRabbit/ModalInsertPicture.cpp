// ModalInsertPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalInsertPicture.h"
#include "ExRabbitDlg.h"
#include "afxdialogex.h"


// ModalInsertPicture 对话框

IMPLEMENT_DYNAMIC(ModalInsertPicture, CDialogEx)

ModalInsertPicture::ModalInsertPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalInsertPicture::IDD, pParent)
{

}

ModalInsertPicture::~ModalInsertPicture()
{
}

void ModalInsertPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalInsertPicture, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalInsertPicture::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalInsertPicture::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalInsertPicture::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_OPERATE4, &ModalInsertPicture::OnBnClickedRadioOperate4)
	ON_BN_CLICKED(IDC_RADIO_OPERATE5, &ModalInsertPicture::OnBnClickedRadioOperate5)
	ON_BN_CLICKED(IDC_RADIO_TYPE1, &ModalInsertPicture::OnBnClickedRadioType1)
	ON_BN_CLICKED(IDC_RADIO_TYPE2, &ModalInsertPicture::OnBnClickedRadioType2)
	ON_BN_CLICKED(IDC_RADIO_TYPE3, &ModalInsertPicture::OnBnClickedRadioType3)
	ON_BN_CLICKED(IDC_RADIO_FORMAT1, &ModalInsertPicture::OnBnClickedRadioFormat1)
	ON_BN_CLICKED(IDC_RADIO_FORMAT2, &ModalInsertPicture::OnBnClickedRadioFormat2)
	ON_BN_CLICKED(IDC_RADIO_FORMAT3, &ModalInsertPicture::OnBnClickedRadioFormat3)
	ON_BN_CLICKED(IDC_RADIO_FORMAT4, &ModalInsertPicture::OnBnClickedRadioFormat4)
	ON_BN_CLICKED(IDC_BUTTON_RESOURCE, &ModalInsertPicture::OnBnClickedButtonResource)
	ON_BN_CLICKED(IDOK, &ModalInsertPicture::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalInsertPicture 消息处理程序


BOOL ModalInsertPicture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	out.fileName = L"";
	out.inputFormat = 0;
	out.para[0] = 0;
	out.para[1] = in.pi.basePt.X;
	out.para[2] = in.pi.basePt.Y;
	out.para[3] = in.pi.frmSize.W;
	out.para[4] = in.pi.frmSize.H;
	out.para[5] = 0;
	out.para[6] = 0;
	out.para[7] = 0;
	out.para[8] = 0;
	out.para[9] = 0;
	if(in.firstInsert){
		GET_CTRL(CButton, IDC_RADIO_OPERATE1)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE2)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE3)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE4)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_OPERATE5)->SetCheck(1);
		out.operate = 5;
	}else{
		GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(1);
		out.operate = 3;
	}
	GET_CTRL(CButton, IDC_RADIO_TYPE1)->SetCheck(1);
	out.type = 1;
	if(in.version == V4 || in.version == V6){
		GET_CTRL(CButton, IDC_RADIO_FORMAT1)->SetCheck(1);
		out.outputFormat = 1;
	}else{
		GET_CTRL(CButton, IDC_RADIO_FORMAT2)->SetCheck(1);
		out.outputFormat = 2;
	}
	if(in.version != V5){
		GET_CTRL(CButton, IDC_RADIO_TYPE3)->EnableWindow(FALSE);
	}
	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(FALSE);

	GET_CTRL(CEdit, IDC_EDIT_RESOURCE)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_BUTTON_RESOURCE)->EnableWindow(FALSE);

	GET_CTRL(CButton, IDC_EDIT_PARA1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA4)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA5)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA6)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA7)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA8)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA9)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA10)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->SetWindowText(NumToCStr(in.pi.basePt.X));
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->SetWindowText(NumToCStr(in.pi.basePt.Y));
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->SetWindowText(NumToCStr(in.pi.frmSize.W));
	GET_CTRL(CEdit, IDC_EDIT_PARA5)->SetWindowText(NumToCStr(in.pi.frmSize.H));
	GET_CTRL(CEdit, IDC_EDIT_PARA6)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA7)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA8)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA9)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_PARA10)->SetWindowText(L"0");
	GET_CTRL(CEdit, IDC_EDIT_MAX_PARA1)->SetWindowText(in.maxPICcount == 0 ? L"不存在喵":(L"0-"+NumToCStr(in.maxPICcount-1)));
	GET_CTRL(CEdit, IDC_EDIT_MAX_PARA2)->SetWindowText(in.maxTEXcount == 0 ? L"不存在喵":(L"0-"+NumToCStr(in.maxTEXcount-1)));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ModalInsertPicture::OnBnClickedRadioOperate1(){
	out.operate = 1;
}
void ModalInsertPicture::OnBnClickedRadioOperate2(){
	out.operate = 2;
}
void ModalInsertPicture::OnBnClickedRadioOperate3(){
	out.operate = 3;
}
void ModalInsertPicture::OnBnClickedRadioOperate4(){
	out.operate = 4;
}
void ModalInsertPicture::OnBnClickedRadioOperate5(){
	out.operate = 5;
}
void ModalInsertPicture::OnBnClickedRadioType1(){
	out.type = 1;
	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT_RESOURCE)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_BUTTON_RESOURCE)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA1)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA4)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA5)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA6)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA7)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA8)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA9)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA10)->EnableWindow(FALSE);
}
void ModalInsertPicture::OnBnClickedRadioType2(){
	out.type = 2;

	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(in.version == V2 ? FALSE : TRUE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(in.version == V4 || in.version == V6 ? FALSE : TRUE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(in.version == V4 || in.version == V6 ? FALSE : TRUE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(in.version == V4 || in.version == V6 ? FALSE : TRUE);
	GET_CTRL(CEdit, IDC_EDIT_RESOURCE)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_BUTTON_RESOURCE)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA3)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA4)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA5)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA6)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA7)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA8)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA9)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA10)->EnableWindow(FALSE);
}
void ModalInsertPicture::OnBnClickedRadioType3(){
	out.type = 3;
	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(FALSE);
	GET_CTRL(CEdit, IDC_EDIT_RESOURCE)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_BUTTON_RESOURCE)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_EDIT_PARA2)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA3)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA4)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA5)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA6)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA7)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA8)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA9)->EnableWindow(TRUE);
	GET_CTRL(CButton, IDC_EDIT_PARA10)->EnableWindow(TRUE);
}
void ModalInsertPicture::OnBnClickedRadioFormat1(){
	out.outputFormat = 1;
}
void ModalInsertPicture::OnBnClickedRadioFormat2(){
	out.outputFormat = 2;
}
void ModalInsertPicture::OnBnClickedRadioFormat3(){
	out.outputFormat = 3;
}
void ModalInsertPicture::OnBnClickedRadioFormat4(){
	out.outputFormat = 4;
}
void ModalInsertPicture::OnBnClickedButtonResource(){
	// TODO: 在此添加控件通知处理程序代码
	CString defExt = L"PNG图像(*.png)|*.png";
	CString extFilter = L"PNG图像(*.png)|*.png|DDS图像(*.dds)|*.dds||";
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


void ModalInsertPicture::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CEdit, IDC_EDIT_RESOURCE)->GetWindowText(out.fileName);
	CString numStr;
	GET_CTRL(CEdit, IDC_EDIT_PARA1)->GetWindowText(numStr);
	out.para[0] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA2)->GetWindowText(numStr);
	out.para[1] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA3)->GetWindowText(numStr);
	out.para[2] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA4)->GetWindowText(numStr);
	out.para[3] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA5)->GetWindowText(numStr);
	out.para[4] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA6)->GetWindowText(numStr);
	out.para[5] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA7)->GetWindowText(numStr);
	out.para[6] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA8)->GetWindowText(numStr);
	out.para[7] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA9)->GetWindowText(numStr);
	out.para[8] = _ttoi(numStr);
	GET_CTRL(CEdit, IDC_EDIT_PARA10)->GetWindowText(numStr);
	out.para[9] = _ttoi(numStr);
	//判断禁止事项
	CExRabbitDlg* dlg = (CExRabbitDlg*)GetParent();
	std::vector<int> replacePos;
	dlg->getSelected(GET_DLG_CTRL(CGoodListCtrl, IDC_LIST_PIC), 0, dlg->MULTI_SELECT, replacePos);
	if(out.operate == 2 && replacePos.size() == 0){
		MessageBox(L"没有勾选任何帧喵。",L"错误喵");
		return;
	}
	if(out.type == 1){
		if(out.para[0]<0){
			MessageBox(L"指定帧不存在喵！",L"错误喵");
			return;
		}
		if(out.para[0] >= in.maxPICcount){
			MessageBox(L"指定帧不存在喵！",L"错误喵");
			return;
		}
	}
	if(out.type == 3){
		if(out.para[5]<0){
			MessageBox(L"指定纹理集不存在喵！",L"错误喵");
			return;
		}
		if(out.para[5] >= in.maxTEXcount){
			MessageBox(L"指定纹理集不存在喵！",L"错误喵");
			return;
		}
	}
	matrix mat;
	DDSobject dds;
	if(out.type == 2 && out.inputFormat == 1){
		if(!KoishiImageTool::loadPNG(mat, CStrToStr(out.fileName))){
			MessageBox(L"无法读取该PNG文件喵！",L"错误喵");
			return;
		}
	}
	if(out.type == 2 && out.inputFormat == 2){
		if(!dds.loadFile(CStrToStr(out.fileName))){
			MessageBox(L"无法识别该DDS文件。",L"错误");
			return;
		}
		if(!dds.uncompress(mat)){
			MessageBox(L"无法解析该文件的DXT格式。",L"错误");
			return;
		}
	}
	mat.destory();
	out.context = GetParent();
	CDialogEx::OnOK();
}

