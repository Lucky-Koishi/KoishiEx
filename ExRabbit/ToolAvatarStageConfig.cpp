#include "StdAfx.h"
#include "ToolAvatarStageConfig.h"


ToolAvatarStageConfig::ToolAvatarStageConfig(void)
{
	loaded = FALSE;
}
void ToolAvatarStageConfig::load(const CString &stageConfigFolderPath){
	CStdioFile file;
	if(loaded){
		loaded = FALSE;
		backLayer.destory();
		foreLayer.destory();
	}
	backLayer.create(210, 210);
	foreLayer.create(210, 210);
	if(!file.Open(stageConfigFolderPath + L"location.txt", CFile::modeRead)){
		createEmpty(stageConfigFolderPath);
	}else{
		CString lineStr;
		CString subStr;
		int readContent = -1; //0.±³¾° 1.±³¾°Í¼Æ¬ 2.Ç°¾°Í¼Æ¬
		while(file.ReadString(lineStr)){
			if(L"[background]" == lineStr){
				readContent = 0;
				continue;
			}
			if(L"[back_layer]" == lineStr){
				readContent = 1;
				continue;
			}
			if(L"[front_layer]" == lineStr){
				readContent = 2;
				continue;
			}
			switch(readContent){
			case 0:
				if(true){
					image imgBG;
					if(::loadPNG(imgBG, CStrToStr(stageConfigFolderPath + lineStr + L".PNG"))){
						imgBG.clip(0, 210, 0, 210);
						backLayer.putFore(imgBG);
						readContent = -1;
						loaded = TRUE;
					}
				}
				break;
			case 1:
				if(AfxExtractSubString(subStr, lineStr, 2, ',')){
					point pt(0, _ttoi(subStr));
					AfxExtractSubString(subStr, lineStr, 1, ',');
					pt.X = _ttoi(subStr);
					image img;
					AfxExtractSubString(subStr, lineStr, 0, ',');
					if(::loadPNG(img, CStrToStr(stageConfigFolderPath + subStr + L".PNG"))){
						img.clip(0, 210, 0, 210);
						backLayer.putFore(img, LAY, pt);
						loaded = TRUE;
					}
				}
				break;
			case 2:
				if(AfxExtractSubString(subStr, lineStr, 2, ',')){
					point pt(0, _ttoi(subStr));
					AfxExtractSubString(subStr, lineStr, 1, ',');
					pt.X = _ttoi(subStr);
					image img;
					AfxExtractSubString(subStr, lineStr, 0, ',');
					if(::loadPNG(img, CStrToStr(stageConfigFolderPath + subStr + L".PNG"))){
						img.clip(0, 210, 0, 210);
						foreLayer.putFore(img, LAY, pt);
						loaded = TRUE;
					}
				}
				break;
			}
		}
	}
}
void ToolAvatarStageConfig::createEmpty(const CString &stageConfigFolderPath){
	CStdioFile file;
	file.Open(stageConfigFolderPath + L"location.txt", CFile::modeCreate | CFile::modeReadWrite);
	file.WriteString(L"[background]\n");
	file.WriteString(L"[back_layer]\n");
	file.WriteString(L"[front_layer]\n");
	file.Close();
}