// ModalTransform.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ModalTransform.h"
#include "afxdialogex.h"


// ModalTransform �Ի���

IMPLEMENT_DYNAMIC(ModalTransform, CDialogEx)

ModalTransform::ModalTransform(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalTransform::IDD, pParent)
{

}

ModalTransform::~ModalTransform()
{
}

void ModalTransform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModalTransform, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_OPERATE1, &ModalTransform::OnBnClickedRadioOperate1)
	ON_BN_CLICKED(IDC_RADIO_OPERATE2, &ModalTransform::OnBnClickedRadioOperate2)
	ON_BN_CLICKED(IDC_RADIO_OPERATE3, &ModalTransform::OnBnClickedRadioOperate3)
	ON_BN_CLICKED(IDC_RADIO_TYPE1, &ModalTransform::OnBnClickedRadioType1)
	ON_BN_CLICKED(IDC_RADIO_TYPE2, &ModalTransform::OnBnClickedRadioType2)
	ON_BN_CLICKED(IDC_RADIO_TYPE3, &ModalTransform::OnBnClickedRadioType3)
	ON_BN_CLICKED(IDC_RADIO_TYPE4, &ModalTransform::OnBnClickedRadioType4)
	ON_BN_CLICKED(IDC_RADIO_FORMAT1, &ModalTransform::OnBnClickedRadioFormat1)
	ON_BN_CLICKED(IDC_RADIO_FORMAT2, &ModalTransform::OnBnClickedRadioFormat2)
	ON_BN_CLICKED(IDC_RADIO_FORMAT3, &ModalTransform::OnBnClickedRadioFormat3)
	ON_BN_CLICKED(IDC_RADIO_FORMAT4, &ModalTransform::OnBnClickedRadioFormat4)
	ON_BN_CLICKED(IDC_RADIO_FORMAT5, &ModalTransform::OnBnClickedRadioFormat5)
	ON_BN_CLICKED(IDC_BUTTON_GET_PALETTE, &ModalTransform::OnBnClickedButtonGetPalette)
	ON_LBN_SELCHANGE(IDC_LIST_PALETTE, &ModalTransform::OnLbnSelchangeListPalette)
	ON_BN_CLICKED(IDOK, &ModalTransform::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_USE_NEW_PALETTE, &ModalTransform::OnBnClickedRadioUseNewPalette)
	ON_BN_CLICKED(IDC_RADIO_USE_NEW_PALETTE2, &ModalTransform::OnBnClickedRadioUseOldPalette)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_USE_TEXTURE, &ModalTransform::OnBnClickedCheckUseTexture)
	ON_COMMAND(ID_MENU_INDEXING_CURRENT, &ModalTransform::OnMenuIndexingCurrent)
	ON_COMMAND(ID_MENU_INDEXING_BASE, &ModalTransform::OnMenuIndexingBase)
	ON_COMMAND(ID_MENU_INDEXING_16, &ModalTransform::OnMenuIndexing16)
	ON_COMMAND(ID_MENU_INDEXING_64, &ModalTransform::OnMenuIndexing64)
	ON_COMMAND(ID_MENU_INDEXING_256, &ModalTransform::OnMenuIndexing256)
	ON_COMMAND(ID_MENU_INDEXING_BASE_ON_FRAME, &ModalTransform::OnMenuIndexingBaseOnFrame)
	ON_COMMAND(ID_MENU_INDEXING_BASE_ON_IMAGE, &ModalTransform::OnMenuIndexingBaseOnImage)
	ON_COMMAND(ID_MENU_INDEXING_IMPORT_PHOTOSHOP, &ModalTransform::OnMenuIndexingImportPhotoshop)
	ON_COMMAND(ID_MENU_INDEXING_IMPORT_RABBIT, &ModalTransform::OnMenuIndexingImportRabbit)
END_MESSAGE_MAP()


// ModalTransform ��Ϣ�������

BOOL ModalTransform::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CREATEW(bar, IDD_TINY_PROGRESSBAR);

	out.target = 1;
	out.version = V2;
	out.outputFormat = ARGB8888;
	if(in.contextIO->version == V4 || in.contextIO->version == V6){
		out.useNewPalette = false;
	}else{
		out.useNewPalette = true;
	}
	out.useColorPalette.clear();
	out.useColorPalette.push_back(in.contextColorList);
	currentPaletteID = 0;
	//
	CString vStr[7] = {L"?", L"V1", L"V2", L"V3", L"V4", L"V5", L"V6"};
	GET_CTRL(CButton, IDC_RADIO_TYPE1)->SetWindowText(vStr[in.contextIO->version]+L"-V2");
	GET_CTRL(CButton, IDC_RADIO_TYPE2)->SetWindowText(vStr[in.contextIO->version]+L"-V4");
	GET_CTRL(CButton, IDC_RADIO_TYPE3)->SetWindowText(vStr[in.contextIO->version]+L"-V5");
	GET_CTRL(CButton, IDC_RADIO_TYPE4)->SetWindowText(vStr[in.contextIO->version]+L"-V6");
	//
	updateRadio();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ModalTransform::updateRadio(){
	GET_CTRL(CButton, IDC_RADIO_OPERATE1)->SetCheck(out.target == 1);
	GET_CTRL(CButton, IDC_RADIO_OPERATE2)->SetCheck(out.target == 2);
	GET_CTRL(CButton, IDC_RADIO_OPERATE3)->SetCheck(out.target == 3);
	GET_CTRL(CButton, IDC_RADIO_TYPE1)->SetCheck(out.version == V2);
	GET_CTRL(CButton, IDC_RADIO_TYPE2)->SetCheck(out.version == V4);
	GET_CTRL(CButton, IDC_RADIO_TYPE3)->SetCheck(out.version == V5);
	GET_CTRL(CButton, IDC_RADIO_TYPE4)->SetCheck(out.version == V6);
	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->SetCheck(out.outputFormat == INDEX_FMT_PALETTE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT2)->SetCheck(out.outputFormat == ARGB8888);
	GET_CTRL(CButton, IDC_RADIO_FORMAT3)->SetCheck(out.outputFormat == ARGB4444);
	GET_CTRL(CButton, IDC_RADIO_FORMAT4)->SetCheck(out.outputFormat == ARGB1555);
	GET_CTRL(CButton, IDC_RADIO_FORMAT5)->SetCheck(out.outputFormat == DDS_DXT5);
	GET_CTRL(CButton, IDC_RADIO_USE_NEW_PALETTE)->SetCheck(out.useNewPalette);
	GET_CTRL(CButton, IDC_RADIO_USE_NEW_PALETTE2)->SetCheck(!out.useNewPalette);
	GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_RADIO_FORMAT5)->EnableWindow(FALSE);
	GET_CTRL(CButton, IDC_CHECK_USE_TEXTURE)->EnableWindow(FALSE);
	switch(out.version){
	case V2:
		GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(TRUE);
		break;
	case V4:
	case V6:
		GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(TRUE);
		break;
	case V5:
		GET_CTRL(CButton, IDC_RADIO_FORMAT1)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT2)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT3)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT4)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_RADIO_FORMAT5)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_CHECK_USE_TEXTURE)->EnableWindow(TRUE);
		break;
	}
	if((out.target != 1 || in.contextIO->version == V4 || in.contextIO->version == V6) && (out.version == V4 || out.version == V6)){
		GET_CTRL(CButton, IDC_RADIO_USE_NEW_PALETTE)->EnableWindow(TRUE);
		GET_CTRL(CButton, IDC_RADIO_USE_NEW_PALETTE2)->EnableWindow(TRUE);
	}else{
		GET_CTRL(CButton, IDC_RADIO_USE_NEW_PALETTE)->EnableWindow(FALSE);
		GET_CTRL(CButton, IDC_RADIO_USE_NEW_PALETTE2)->EnableWindow(FALSE);
	}
	if((out.version == V4 || out.version == V6) && out.useNewPalette){
		GET_CTRL(CButton, IDC_BUTTON_GET_PALETTE)->EnableWindow(TRUE);
		GET_CTRL(CListBox, IDC_LIST_PALETTE)->EnableWindow(TRUE);
	}else{
		GET_CTRL(CButton, IDC_BUTTON_GET_PALETTE)->EnableWindow(FALSE);
		GET_CTRL(CListBox, IDC_LIST_PALETTE)->EnableWindow(FALSE);
	}
	updatePalette();
	updatePaletteList();
}

void ModalTransform::updatePaletteList(){
	GET_CTRL(CListBox, IDC_LIST_PALETTE)->ResetContent();
	for(long i = 0;i<out.useColorPalette.size();i++){
		GET_CTRL(CListBox, IDC_LIST_PALETTE)->AddString(L"#" + NumToCStr(i)+L"("+NumToCStr(out.useColorPalette[i].size())+L"����ɫ)");
	}
	GET_CTRL(CListBox, IDC_LIST_PALETTE)->AddString(L"�½���ɫ��");
}
void ModalTransform::updatePalette(){
	int xdelta = 320;
	int ydelta = 30;
	int i,j;
	color clr;
	color clrBack(0xFF, 0xFF, 0xFF, 0xFF);
	color clrLine(0xFF, 0, 0, 0);
	image canvas(160, 160);
	image block(10, 10);
	image alphaBlock(10, 10);
	alphaBlock.filledLattice(point(0,0),point(9,9),color(0xff, 0xff, 0xff, 0xff),color(0xff,0xcc,0xcc,0xcc),3);
	int index = 0;
	for(j=0;j<16;j++){
		for(i=0;i<16;i++){
			if(i+16*j >= out.useColorPalette[currentPaletteID].size()){
				block.fill(color(0XFF, 0XFF, 0XFF, 0XFF));
				block.line(point(1,1), point(8,8), color(0xFF, 0, 0, 0));
				block.line(point(1,8), point(8,1), color(0xFF, 0, 0, 0));
			}else{
				block.fill(out.useColorPalette[currentPaletteID][i+16*j]);
				block.putBack(alphaBlock);
			}
			canvas.putFore(block, LAY, point(10*i, 10*j));
		}
	}
	CImage img;
	img.Create(160,160,32);
	UCHAR* pst = (UCHAR*)img.GetBits();
	int pit = img.GetPitch();
	CDC *pDC = GetDC();
	for(i=0;i<160;i++){
		for(j=0;j<160;j++){
			*(pst + pit*j + 4*i + 0) = canvas[j][i].B;
			*(pst + pit*j + 4*i + 1) = canvas[j][i].G;
			*(pst + pit*j + 4*i + 2) = canvas[j][i].R;
		}
	}
	img.Draw(pDC->m_hDC,xdelta,ydelta);
	img.Destroy();
	ReleaseDC(pDC);
}

void ModalTransform::OnBnClickedRadioOperate1(){
	out.target = 1;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioOperate2(){
	out.target = 2;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioOperate3(){
	out.target = 3;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioType1(){
	out.version = V2;
	out.useNewPalette = true;
	if(out.outputFormat == INDEX_FMT_PALETTE ||out.outputFormat == DDS_DXT5){
		out.outputFormat = ARGB8888;
	}
	updateRadio();
}
void ModalTransform::OnBnClickedRadioType2(){
	out.version = V4;
	out.outputFormat = INDEX_FMT_PALETTE;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioType3(){
	out.version = V5;
	out.useNewPalette = true;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioType4(){
	out.version = V6;
	out.outputFormat = INDEX_FMT_PALETTE;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioFormat1(){
	out.outputFormat = INDEX_FMT_PALETTE;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioFormat2(){
	out.outputFormat = ARGB8888;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioFormat3(){
	out.outputFormat = ARGB4444;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioFormat4(){
	out.outputFormat = ARGB1555;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioFormat5(){
	out.outputFormat = DDS_DXT5;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioUseNewPalette(){
	out.useNewPalette = true;
	updateRadio();
}
void ModalTransform::OnBnClickedRadioUseOldPalette(){
	out.useNewPalette = false;
	updateRadio();
}
void ModalTransform::OnBnClickedButtonGetPalette(){
	CMenu menu, *pPopup;  
	menu.LoadMenu(IDR_MENU_COLOR);  
	pPopup = menu.GetSubMenu(2);  
	CPoint myPoint; 
	ClientToScreen(&myPoint);  
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}
void ModalTransform::OnLbnSelchangeListPalette(){
	if(GET_CTRL(CListBox, IDC_LIST_PALETTE)->GetCurSel() == out.useColorPalette.size()){
		//�½�
		colorList newCl;
		newCl.push_back(color(0, 0, 0, 0));
		newCl.push_back(color(0xFF, 0xFF, 0xFF, 0xFF));
		newCl.push_back(color(0xFF, 0, 0, 0));
		out.useColorPalette.push_back(newCl);
		updatePaletteList();
		GET_CTRL(CListBox, IDC_LIST_PALETTE)->SetCurSel(out.useColorPalette.size() - 1);
	}
	currentPaletteID = GET_CTRL(CListBox, IDC_LIST_PALETTE)->GetCurSel();
	updatePalette();
}
void ModalTransform::OnBnClickedOk(){
	out.makeTexture = GET_CTRL(CButton, IDC_CHECK_USE_TEXTURE)->GetCheck() == 1;
	if(out.version == V4){
		//V4���õ�ǰѡ���ɫ��
		colorList cl = out.useColorPalette[currentPaletteID];
		out.useColorPalette.clear();
		out.useColorPalette.push_back(cl);
	}
	CDialogEx::OnOK();
}

void ModalTransform::OnPaint(){
	CPaintDC dc(this);
	updatePalette();
}

void ModalTransform::OnBnClickedCheckUseTexture(){
}

void ModalTransform::OnMenuIndexingCurrent(){
	out.useColorPalette[currentPaletteID] = in.contextColorList;
	updatePaletteList();
	updatePalette();
}

void ModalTransform::OnMenuIndexingBase(){
	out.useColorPalette[currentPaletteID] = Koishi::palette::palette2();
	updatePaletteList();
	updatePalette();
}

void ModalTransform::OnMenuIndexing16(){
	out.useColorPalette[currentPaletteID] = Koishi::palette::palette16();
	updatePaletteList();
	updatePalette();
}

void ModalTransform::OnMenuIndexing64(){
	out.useColorPalette[currentPaletteID] = Koishi::palette::palette64();
	updatePaletteList();
	updatePalette();
}

void ModalTransform::OnMenuIndexing256(){
	out.useColorPalette[currentPaletteID] = Koishi::palette::palette256();
	updatePaletteList();
	updatePalette();
}


void ModalTransform::OnMenuIndexingBaseOnFrame(){
	// TODO: �ڴ���������������
	if(in.currentFrame < 0){
		MessageBox(L"��û��ѡ���κ�֡����",L"��ʾ��");
		return;
	}
	AfxBeginThread(pickColorFrame, this);
}


void ModalTransform::OnMenuIndexingBaseOnImage(){
	AfxBeginThread(pickColorImage, this);
}

UINT ModalTransform::pickColorFrame(void*context){
	ModalTransform*dlg = (ModalTransform*)context;
	IMGobject *ptrIO = dlg->in.contextIO;
	image mat;
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	if(!ptrIO->PICextract(dlg->in.currentFrame, mat, dlg->in.currentPalette)){
		dlg->MessageBox(L"������ǰͼƬʧ������",L"��ʾ��");
		return 0U;
	}
	dlg->bar.show(100);
	dlg->bar.setInfo(L"������ȡ��ɫ������", 0);
	for(int i = 0;i<mat.getElemCount();i++){
		color clr = mat.getElem(i);
		long clrPos = pal.findColor(clr,0);
		if(clrPos == -1){
			pal[0].push_back(clr);
			clrCount.push_back(1);
		}else{
			clrCount[clrPos] ++;
		}
	}
	clrList = pal[0];
	long finalColorCount = MIN(0xFE, pal.getColorCount(0));
	colorList finalColorList;
	dlg->bar.show(finalColorCount);
	for(int i = 0;i<finalColorCount; i++){
		dlg->bar.setInfo(L"���ڷ�����ɫ������", i);
		long maxCount = 0;
		long maxID = -1;
		for(int j = 0;j<clrCount.size();j++){
			if(clrCount[j] > maxCount){
				maxCount =clrCount[j];
				maxID = j;
			}
		}
		finalColorList.push_back(clrList[maxID]);
		clrList.erase(clrList.begin() + maxID);
		clrCount.erase(clrCount.begin() + maxID);
	}
	dlg->bar.setInfo(L"�������ɵ�ɫ��������", finalColorCount);
	dlg->out.useColorPalette[dlg->currentPaletteID] = KoishiImageTool::nearbySort(finalColorList);
	dlg->out.useColorPalette[dlg->currentPaletteID].insert(dlg->out.useColorPalette[dlg->currentPaletteID].begin(), color(0,0,0,0));
	dlg->bar.hide();
	dlg->updatePaletteList();
	dlg->updatePalette();
	return 0U;
}
UINT ModalTransform::pickColorImage(void*context){
	ModalTransform*dlg = (ModalTransform*)context;
	IMGobject *ptrIO = dlg->in.contextIO;
	palette pal;
	colorList clrList;
	queue clrCount;
	pal.push(clrList);
	dlg->bar.show(ptrIO->indexCount);
	for(long getFrame = 0;getFrame<ptrIO->indexCount;getFrame ++){
		dlg->bar.setInfo(L"������ȡ��"+NumToCStr(getFrame+1)+L"֡����ɫ������", getFrame);
		image mat;
		if(!ptrIO->PICextract(getFrame, mat, dlg->in.currentPalette)){
			continue;
		}
		for(int i = 0;i<mat.getElemCount();i++){
			color clr = mat.getElem(i);
			long clrPos = pal.findColor(clr,0);
			if(clrPos == -1){
				pal[0].push_back(clr);
				clrCount.push_back(1);
			}else{
				clrCount[clrPos] ++;
			}
		}
		mat.destory();
	}
	clrList = pal[0];
	long finalColorCount = MIN(0xFE, pal.getColorCount(0));
	colorList finalColorList;
	dlg->bar.show(finalColorCount);
	for(int i = 0;i<finalColorCount; i++){
		dlg->bar.setInfo(L"���ڷ�����ɫ������", i);
		long maxCount = 0;
		long maxID = -1;
		for(int j = 0;j<clrCount.size();j++){
			if(clrCount[j] > maxCount){
				maxCount =clrCount[j];
				maxID = j;
			}
		}
		finalColorList.push_back(clrList[maxID]);
		clrList.erase(clrList.begin() + maxID);
		clrCount.erase(clrCount.begin() + maxID);
	}
	dlg->bar.setInfo(L"�������ɵ�ɫ��������", finalColorCount);
	dlg->out.useColorPalette[dlg->currentPaletteID] = KoishiImageTool::nearbySort(finalColorList);
	dlg->out.useColorPalette[dlg->currentPaletteID].insert(dlg->out.useColorPalette[dlg->currentPaletteID].begin(), color(0,0,0,0));
	dlg->bar.hide();
	dlg->updatePaletteList();
	dlg->updatePalette();
	return 0U;
}
void ModalTransform::OnMenuIndexingImportPhotoshop(){
	// TODO: �ڴ���������������
	colorList cl;
	CString defExt = _T("Photoshop��ɫ��(*.act)|*.act");
	CString extFilter = _T("Photoshop��ɫ��(*.act)|*.act||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(!palette::loadACT(CStrToStr(fileName), cl)){
			MessageBox(L"δʶ��ĵ�ɫ���ļ�����",L"��ʾ��");
			return;
		}
		out.useColorPalette[currentPaletteID] = cl;
		updatePaletteList();
		updatePalette();
	}
}


void ModalTransform::OnMenuIndexingImportRabbit(){
	// TODO: �ڴ���������������
	colorList cl;
	CString defExt = _T("CID��ɫ��(*.cid)|*.cid");
	CString extFilter = _T("CID��ɫ��(*.cid)|*.cid||");
	CFileDialog dlg(true, defExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,extFilter, this);
	CString fileName;
	if(dlg.DoModal() == IDOK){
		fileName = dlg.GetPathName();
		if(!palette::loadCID(CStrToStr(fileName), cl)){
			MessageBox(L"δʶ��ĵ�ɫ���ļ�����",L"��ʾ��");
			return;
		}
		out.useColorPalette[currentPaletteID] = cl;
		updatePaletteList();
		updatePalette();
	}
}
