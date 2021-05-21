// ToolPatch.cpp : 实现文件
//

#include "stdafx.h"
#include "ExRabbit.h"
#include "ToolPatch.h"
#include "afxdialogex.h"


// ToolPatch 对话框

IMPLEMENT_DYNAMIC(ToolPatch, CDialogEx)

ToolPatch::ToolPatch(CWnd* pParent /*=NULL*/)
	: CDialogEx(ToolPatch::IDD, pParent)
{

}

ToolPatch::~ToolPatch()
{
}

void ToolPatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolPatch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ToolPatch::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &ToolPatch::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &ToolPatch::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &ToolPatch::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &ToolPatch::OnBnClickedCheck4)
	ON_BN_CLICKED(IDOK, &ToolPatch::OnBnClickedOk)
	ON_BN_CLICKED(IDSTOP, &ToolPatch::OnBnClickedStop)
END_MESSAGE_MAP()


// ToolPatch 消息处理程序


BOOL ToolPatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(L"请设置文件夹。");
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"总体进度在这里显示。");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"单体进度在这里显示。");

	GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetRange32(0, 1000);
	GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetRange32(0, 1000);
	
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ToolPatch::OnBnClickedButton1(){
	// TODO: 在此添加控件通知处理程序代码
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
				GET_CTRL(CEdit, IDC_EDIT1)->SetWindowText(filePath);
			}
		}
		pMalloc->Release();	//释放接口
	}
}

void ToolPatch::OnBnClickedCheck1(){
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK4)->SetCheck(0);
}

void ToolPatch::OnBnClickedCheck2(){
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK4)->SetCheck(0);
}


void ToolPatch::OnBnClickedCheck3(){
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(1);
	GET_CTRL(CButton, IDC_CHECK4)->SetCheck(0);
}


void ToolPatch::OnBnClickedCheck4(){
	// TODO: 在此添加控件通知处理程序代码
	GET_CTRL(CButton, IDC_CHECK1)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK2)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK3)->SetCheck(0);
	GET_CTRL(CButton, IDC_CHECK4)->SetCheck(1);
}


void ToolPatch::OnBnClickedOk(){
	AfxBeginThread(go, this);
}
void ToolPatch::OnBnClickedStop(){
}
unsigned ToolPatch::go(void*context){
	ToolPatch* dlg = (ToolPatch*)context;
	GET_DLG_CTRL(CButton, IDOK)->EnableWindow(FALSE);
	GET_DLG_CTRL(CButton, IDCANCEL)->EnableWindow(FALSE);
	if(GET_DLG_CTRL(CButton, IDC_CHECK1)->GetCheck() == 1){
		dlg->getPNG();
	}else if(GET_DLG_CTRL(CButton, IDC_CHECK2)->GetCheck() == 1){
		dlg->getGIF();
	}else if(GET_DLG_CTRL(CButton, IDC_CHECK3)->GetCheck() == 1){
		dlg->transToV2();
	}else if(GET_DLG_CTRL(CButton, IDC_CHECK4)->GetCheck() == 1){
	}
	GET_DLG_CTRL(CButton, IDOK)->EnableWindow(TRUE);
	GET_DLG_CTRL(CButton, IDCANCEL)->EnableWindow(TRUE);
	return 0;
}
void ToolPatch::getPNG(){
	int fileID, imgID, clrID, frameID;
	CString folderPath;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderPath);
	CString folderName = folderPath + L"\\*.*";
	CFileFind fileFind;
	std::vector<CString> fileList;
	std::vector<CString> pathList;
	BOOL ret = fileFind.FindFile(folderName);
	while(ret){
		ret = fileFind.FindNextFile();
		fileList.push_back(fileFind.GetFileName());
		pathList.push_back(fileFind.GetFilePath());
	}
	for(fileID = 0;fileID < pathList.size(); fileID ++){
		if(fileList[fileID].Right(4).MakeLower() == L".npk"){
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在提取"+GetTail(fileList[fileID])+L"中的贴图。");
			NPKobject no;
			if(no.loadFile(CStrToStr(pathList[fileID]))){
				for(imgID = 0;imgID<no.getCount();imgID++){
					GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在提取"+GetTail(StrToCStr(no.content[imgID].comment))+L"中的贴图。");
					IMGobject io;
					if(no.IMGextract(imgID, io)){
						for(frameID = 0;frameID<io.indexCount;frameID++){
							if(io.version != V6){
								CString fileName = p->getOutputPath(GetTail(fileList[fileID]),GetTail(StrToCStr(no.content[imgID].comment)));
								image mPic;
								if(io.PICextract(frameID, mPic)){
									KoishiImageTool::makePNG(mPic, CStrToStr(fileName+NumToCStr(frameID)+L".PNG"));
								}
							}else{
								for(clrID = 0;clrID<io.paletteData.getCount();clrID++){
									CString fileName = p->getOutputPath(GetTail(fileList[fileID]),GetTail(StrToCStr(no.content[imgID].comment)), clrID);
									image mPic;
									if(io.PICextract(frameID, mPic, clrID)){
										KoishiImageTool::makePNG(mPic, CStrToStr(fileName+NumToCStr(frameID)+L".PNG"));
									}
								}
							}
						}
					}
					GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos((imgID+1)*1000/no.getCount());
				}
			}
		}
		if(fileList[fileID].Right(4).MakeLower() == L".img"){
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在提取"+fileList[fileID]+L"中的贴图。");
			GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在提取"+fileList[fileID]+L"中的贴图。");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(0);
			IMGobject io;
			if(io.loadFile(CStrToStr(pathList[fileID]))){
				for(frameID = 0;frameID<io.indexCount;frameID++){
					if(io.version != V6){
						CString fileName = p->getOutputPath(GetTail(fileList[fileID]));
						image mPic;
						if(io.PICextract(frameID, mPic)){
							KoishiImageTool::makePNG(mPic, CStrToStr(fileName+NumToCStr(frameID)+L".PNG"));
						}
					}else{
						for(clrID = 0;clrID<io.paletteData.getCount();clrID++){
							CString fileName = p->getOutputPath(GetTail(fileList[fileID]),NumToCStr(clrID));
							image mPic;
							if(io.PICextract(frameID, mPic, clrID)){
								KoishiImageTool::makePNG(mPic, CStrToStr(fileName+NumToCStr(frameID)+L".PNG"));
							}
						}
					}
				}
			}
		}
		GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos((fileID+1)*1000/pathList.size());
	}
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"结束提取。");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"结束提取。");
}
void ToolPatch::getGIF(){
	int fileID, imgID, clrID, frameID;
	CString folderPath;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderPath);
	CString folderName = folderPath + L"\\*.*";
	CFileFind fileFind;
	std::vector<CString> fileList;
	std::vector<CString> pathList;
	BOOL ret = fileFind.FindFile(folderName);
	while(ret){
		ret = fileFind.FindNextFile();
		fileList.push_back(fileFind.GetFileName());
		pathList.push_back(fileFind.GetFilePath());
	}
	for(fileID = 0;fileID < pathList.size(); fileID ++){
		if(fileList[fileID].Right(4).MakeLower() == L".npk"){
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在提取"+GetTail(fileList[fileID])+L"中的贴图。");
			NPKobject no;
			if(no.loadFile(CStrToStr(pathList[fileID]))){
				for(imgID = 0;imgID<no.getCount();imgID++){
					GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在提取"+GetTail(StrToCStr(no.content[imgID].comment))+L"中的贴图。");
					IMGobject io;
					if(no.IMGextract(imgID, io)){
						if(io.version != V6){
							std::vector<image> matList;
							long imgX1, imgX2, imgY1, imgY2;
							io.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
							for(frameID = 0;frameID<io.indexCount;frameID++){
								image mOrigin, mExpanded;
								PICinfo pInfo;
								io.PICgetInfo(io.linkFind(frameID), pInfo); 
								io.PICextract(io.linkFind(frameID), mOrigin);
								int x1old = pInfo.basePt.X;
								int y1old = pInfo.basePt.Y;
								int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
								int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
								int x1new = imgX1;
								int y1new = imgY1;
								int x2new = imgX2;
								int y2new = imgY2;
								int x1 = min(x1old,x1new);
								int x2 = max(x2old,x2new);
								int y1 = min(y1old,y1new);
								int y2 = max(y2old,y2new);
								mExpanded.create(y2-y1+1,x2-x1+1);
								mExpanded.putFore(mOrigin, LAY, point(x1old-x1, y1old-y1));
								mExpanded.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
								matList.push_back(mExpanded);
								mOrigin.destory();
								mExpanded.destory();
							}
							KoishiImageTool::GIF::GIFobject gf;
							gf.input(matList, p->miniSecPerFrame);
							CString fileName = p->getOutputPath(fileList[fileID]) + GetTail(StrToCStr(no.content[imgID].comment)) + ".GIF";
							gf.makeFile(CStrToStr(fileName));
						}else{
							for(clrID = 0;clrID<io.paletteData.getCount();clrID++){
								std::vector<image> matList;
								long imgX1, imgX2, imgY1, imgY2;
								io.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
								for(frameID = 0;frameID<io.indexCount;frameID++){
									image mOrigin, mExpanded;
									PICinfo pInfo;
									io.PICgetInfo(io.linkFind(frameID), pInfo); 
									io.PICextract(io.linkFind(frameID), mOrigin, clrID);
									int x1old = pInfo.basePt.X;
									int y1old = pInfo.basePt.Y;
									int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
									int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
									int x1new = imgX1;
									int y1new = imgY1;
									int x2new = imgX2;
									int y2new = imgY2;
									int x1 = min(x1old,x1new);
									int x2 = max(x2old,x2new);
									int y1 = min(y1old,y1new);
									int y2 = max(y2old,y2new);
									mExpanded.create(y2-y1+1,x2-x1+1);
									mExpanded.putFore(mOrigin, LAY, point(x1old-x1, y1old-y1));
									mExpanded.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
									matList.push_back(mExpanded);
									mOrigin.destory();
									mExpanded.destory();
								}
								KoishiImageTool::GIF::GIFobject gf;
								gf.input(matList, p->miniSecPerFrame);
								CString fileName = p->getOutputPath(fileList[fileID]) + GetTail(StrToCStr(no.content[imgID].comment)) + "_P"+ NumToCStr(clrID) + ".GIF";
								gf.makeFile(CStrToStr(fileName));
							}
						}
					}
					GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos((imgID+1)*1000/no.getCount());
				}
			}
		}
		if(fileList[fileID].Right(4).MakeLower() == L".img"){
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在提取"+GetTail(fileList[fileID])+L"中的贴图。");
			GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在提取"+GetTail(fileList[fileID])+L"中的贴图。");
			GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos(0);
			IMGobject io;
			if(io.loadFile(CStrToStr(pathList[fileID]))){
				if(io.version != V6){
					std::vector<image> matList;
					long imgX1, imgX2, imgY1, imgY2;
					io.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
					for(frameID = 0;frameID<io.indexCount;frameID++){
						image mOrigin, mExpanded;
						PICinfo pInfo;
						io.PICgetInfo(io.linkFind(frameID), pInfo); 
						io.PICextract(io.linkFind(frameID), mOrigin);
						int x1old = pInfo.basePt.X;
						int y1old = pInfo.basePt.Y;
						int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
						int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
						int x1new = imgX1;
						int y1new = imgY1;
						int x2new = imgX2;
						int y2new = imgY2;
						int x1 = min(x1old,x1new);
						int x2 = max(x2old,x2new);
						int y1 = min(y1old,y1new);
						int y2 = max(y2old,y2new);
						mExpanded.create(y2-y1+1,x2-x1+1);
						mExpanded.putFore(mOrigin, LAY, point(x1old-x1, y1old-y1));
						mExpanded.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
						matList.push_back(mExpanded);
						mOrigin.destory();
						mExpanded.destory();
					}
					KoishiImageTool::GIF::GIFobject gf;
					gf.input(matList, p->miniSecPerFrame);
					CString fileName = p->getOutputPath() + fileList[fileID] + ".GIF";
					gf.makeFile(CStrToStr(fileName));
				}else{
					for(clrID = 0;clrID<io.paletteData.getCount();clrID++){
						std::vector<image> matList;
						long imgX1, imgX2, imgY1, imgY2;
						io.PICgetTotalBound(imgX1, imgX2, imgY1, imgY2);
						for(frameID = 0;frameID<io.indexCount;frameID++){
							image mOrigin, mExpanded;
							PICinfo pInfo;
							io.PICgetInfo(io.linkFind(frameID), pInfo); 
							io.PICextract(io.linkFind(frameID), mOrigin, clrID);
							int x1old = pInfo.basePt.X;
							int y1old = pInfo.basePt.Y;
							int x2old = pInfo.basePt.X+pInfo.picSize.W-1;
							int y2old = pInfo.basePt.Y+pInfo.picSize.H-1;
							int x1new = imgX1;
							int y1new = imgY1;
							int x2new = imgX2;
							int y2new = imgY2;
							int x1 = min(x1old,x1new);
							int x2 = max(x2old,x2new);
							int y1 = min(y1old,y1new);
							int y2 = max(y2old,y2new);
							mExpanded.create(y2-y1+1,x2-x1+1);
							mExpanded.putFore(mOrigin, LAY, point(x1old-x1, y1old-y1));
							mExpanded.clip(y1new-y1, y2new-y1+1, x1new-x1, x2new-x1+1);
							matList.push_back(mExpanded);
							mOrigin.destory();
							mExpanded.destory();
						}
						KoishiImageTool::GIF::GIFobject gf;
						gf.input(matList, p->miniSecPerFrame);
						CString fileName = p->getOutputPath() + fileList[fileID] + "_P"+ NumToCStr(clrID) + ".GIF";
						gf.makeFile(CStrToStr(fileName));
					}
				}
			}
		}
		GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos((fileID+1)*1000/pathList.size());
	}
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"结束提取。");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"结束提取。");
}
void ToolPatch::transToV2(){
	int fileID, imgID, clrID;
	CString folderPath;
	GET_CTRL(CEdit, IDC_EDIT1)->GetWindowText(folderPath);
	CString folderName = folderPath + L"\\*.*";
	CFileFind fileFind;
	std::vector<CString> fileList;
	std::vector<CString> pathList;
	BOOL ret = fileFind.FindFile(folderName);
	while(ret){
		ret = fileFind.FindNextFile();
		fileList.push_back(fileFind.GetFileName());
		pathList.push_back(fileFind.GetFilePath());
	}
	for(fileID = 0;fileID < pathList.size(); fileID ++){
		if(fileList[fileID].Right(4).MakeLower() == L".npk"){
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在转换"+GetTail(fileList[fileID])+L"中的IMG文件。");
			NPKobject no;
			if(no.loadFile(CStrToStr(pathList[fileID]))){
				for(imgID = no.getCount() - 1;imgID>=0;imgID--){
					GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在转换"+GetTail(StrToCStr(no.content[imgID].comment))+L"。");
					IMGobject io;
					if(no.IMGextract(imgID, io)){
						std::vector<IMGobject> ioList;
						io.convertToV2(ioList);
						for(clrID = 0;clrID<ioList.size();clrID++){
							if(clrID == 0){
								no.IMGreplace(imgID, ioList[0]);
							}else{
								str newName = KoishiAvatar::formatAvatarIDplusBy(no.content[imgID].comment, clrID);
								no.IMGinsert(imgID + clrID, newName, ioList[clrID]);
							}
						}
					}
					GET_CTRL(CProgressCtrl, IDC_PROGRESS2)->SetPos((imgID+1)*1000/no.getCount());
				}
				CString newNPKFilePath = pathList[fileID].Left(pathList[fileID].GetLength()-4);
				newNPKFilePath += L"(Transformed).npk";
				no.saveFile(CStrToStr(newNPKFilePath));
			}
		}
		if(fileList[fileID].Right(4).MakeLower() == L".img"){
			GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"正在转换"+GetTail(fileList[fileID])+L"中的IMG文件。");
			GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"正在转换"+GetTail(fileList[fileID])+L"中的IMG文件。");
			IMGobject io;
			if(io.loadFile(CStrToStr(pathList[fileID]))){
				std::vector<IMGobject> ioList;
				io.convertToV2(ioList);
				for(clrID = 0;clrID<ioList.size();clrID++){
					CString newIMGFilePath = pathList[fileID].Left(pathList[fileID].GetLength()-4);
					if(clrID == 0){
						newIMGFilePath += L"(Transformed).img";
						ioList[0].saveFile(CStrToStr(newIMGFilePath));
					}else{
						newIMGFilePath += L"(Transformed "+NumToCStr(clrID)+L").img";
						ioList[clrID].saveFile(CStrToStr(newIMGFilePath));
					}
				}
			}
		}
		GET_CTRL(CProgressCtrl, IDC_PROGRESS1)->SetPos((fileID+1)*1000/pathList.size());
	}
	GET_CTRL(CEdit, IDC_EDIT2)->SetWindowText(L"结束提取。");
	GET_CTRL(CEdit, IDC_EDIT3)->SetWindowText(L"结束提取。");
}