#include "StdAfx.h"
#include "ToolAvatarStageConfig.h"
#include <locale.h>

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
		int readContent = -1; //0.���� 1.����ͼƬ 2.ǰ��ͼƬ
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
	file.Close();
}
void ToolAvatarStageConfig::createEmpty(const CString &stageConfigFolderPath){
	CStdioFile file;
	file.Open(stageConfigFolderPath + L"location.txt", CFile::modeCreate | CFile::modeReadWrite);
	file.WriteString(L"[background]\n");
	file.WriteString(L"[back_layer]\n");
	file.WriteString(L"[front_layer]\n");
	file.Close();
}
ToolAvatarAnimation::ToolAvatarAnimation() {
	ann.clear();
}
long ToolAvatarAnimation::animation::operator[](int frameID) const {
	int size1 = aniFrame.size();
	return size1 ? aniFrame[frameID % size1] : 0;
}
ToolAvatarAnimation::animation ToolAvatarAnimation::operator[](int aniID) const {
	return ann[aniID];
}
void ToolAvatarAnimation::load(const CString &stageConfigFolderPath, KoishiAvatar::AvatarCharacter ac) {
	CStdioFile file;
	if(!file.Open(stageConfigFolderPath + L"animation.txt", CFile::modeRead)) {
		createEmpty(stageConfigFolderPath);
		file.Open(stageConfigFolderPath + L"animation.txt", CFile::modeRead);
	}
	CString careerNameList[KoishiAvatar::ACHARACTER_MAXCOUNT] = {
		L"��ʿ(��)", L"��ʿ(Ů)", L"�񶷼�(Ů)", L"�񶷼�(��)",
		L"��ǹ��(��)", L"��ǹ��(Ů)", L"ħ��ʦ(Ů)", L"ħ��ʦ(��)",
		L"ʥְ��(��)", L"ʥְ��(Ů)",
		L"��ҹʹ��", L"�ػ���", L"ħǹʿ", L"ǹ��ʿ"
	};
	CString carrerName = L"[" + careerNameList[ac] + L"]";
	CString lineStr;
	BOOL finishLoad = FALSE;
	ann.clear();
	CHS_LOCALE_START;
	while(file.ReadString(lineStr)) {
		if(finishLoad)
			break;
		if(lineStr != carrerName)
			continue;
		while(file.ReadString(lineStr)) {
			CString aniName;
			CString frameListStr;
			AfxExtractSubString(aniName, lineStr, 0, '|');
			if(AfxExtractSubString(frameListStr, lineStr, 1, '|')) {
				ToolAvatarAnimation::animation ani;
				ani.aniName = aniName;
				ani.aniFrame.clear();
				CString frameStr;
				int i = 0;
				while(AfxExtractSubString(frameStr, frameListStr, i++, '-')) {
					ani.aniFrame.push_back(_ttoi(frameStr));
				}
				ann.push_back(ani);
			} else {
				//�鲻������|������
				finishLoad = TRUE;
				break;
			}
		}
	}
	CHS_LOCALE_END;
	file.Close();
}
void ToolAvatarAnimation::createEmpty(const CString &stageConfigFolderPath) {
	CStdioFile file;
	file.Open(stageConfigFolderPath + L"animation.txt", CFile::modeCreate | CFile::modeReadWrite);
	CHS_LOCALE_START;
	file.WriteString(L"[��ʿ(��)]\n");
	file.WriteString(L"ͨ��|176-176-176-177-178\n");
	file.WriteString(L"��ս|90-91-92-93-94-95\n");
	file.WriteString(L"�ƶ�|180-181-182-183-184-185-186-187\n");
	file.WriteString(L"ǰ��|105-106-107-108-109-110-111-112\n");
	file.WriteString(L"����|0-2-3-4-5-6-7-8-8-8-8\n");
	file.WriteString(L"Z��|33-34-35-36-37-38-39-39-39-39\n");
	file.WriteString(L"�ͷ�|75-76-77-78-79-80-81-82-82-82\n");
	file.WriteString(L"����|96-96-96-99-99-99\n");
	file.WriteString(L"����|101-102-102-102-102-102-102-102\n");
	file.WriteString(L"\n");
	file.WriteString(L"[��ʿ(Ů)]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5-6-7-8\n");
	file.WriteString(L"��ս|9-10-11-12\n");
	file.WriteString(L"�ƶ�|13-14-15-16-17-18-19-20-21-22\n");
	file.WriteString(L"ǰ��|151-152-153-154-155-156-157-158\n");
	file.WriteString(L"����|48-49-50-51-52\n");
	file.WriteString(L"Z��|48-49-50-51-52\n");
	file.WriteString(L"�ͷ�|121-122-123-124-125-126-127-128-129-130-131-132-133-134-135-136\n");
	file.WriteString(L"����|139-140\n");
	file.WriteString(L"����|141-142-143\n");
	file.WriteString(L"\n");
	file.WriteString(L"[��ǹ��(��)]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5-6-7-8-9-10-11-12\n");
	file.WriteString(L"��ս|13-14-15-16-17-18-19-20-21-22\n");
	file.WriteString(L"�ƶ�|55-56-57-58-59-60-61-62\n");
	file.WriteString(L"ǰ��|103-104-105-106-107-108-109-110\n");
	file.WriteString(L"����|25-26-27-28-29-30-31-32-33-34-35-36-37-38\n");
	file.WriteString(L"Z��|155-156-157-158\n");
	file.WriteString(L"�ͷ�|193-194-195-196-197\n");
	file.WriteString(L"����|121-122-123-124\n");
	file.WriteString(L"����|125-126-127\n");
	file.WriteString(L"\n");
	file.WriteString(L"[��ǹ��(Ů)]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5-6-7-8-9\n");
	file.WriteString(L"��ս|14-15-16-17-18-19-20\n");
	file.WriteString(L"�ƶ�|68-69-70-71-72-73-74-75\n");
	file.WriteString(L"ǰ��|76-77-78-79-80-71\n");
	file.WriteString(L"����|22-23-24-25-26-27-28-29-30-31-32-33-34-35\n");
	file.WriteString(L"Z��|111-112-113-114-115\n");
	file.WriteString(L"�ͷ�|10-11-12-13\n");
	file.WriteString(L"����|89-90\n");
	file.WriteString(L"����|91\n");
	file.WriteString(L"\n");
	file.WriteString(L"[�񶷼�(Ů)]\n");
	file.WriteString(L"��ս|132-133-134-135\n");
	file.WriteString(L"�ƶ�|136-137-138-139-140-141-142-143\n");
	file.WriteString(L"ǰ��|39-40-41-42-43-44-45-46\n");
	file.WriteString(L"����|5-6-7-8-9\n");
	file.WriteString(L"Z��|30-31-32-33-34-35\n");
	file.WriteString(L"�ͷ�|92-93-94-95\n");
	file.WriteString(L"����|77-78-84-85\n");
	file.WriteString(L"����|79-80-81-82-83\n");
	file.WriteString(L"\n");
	file.WriteString(L"[�񶷼�(��)]\n");
	file.WriteString(L"ͨ��|0-1-2-3\n");
	file.WriteString(L"��ս|12-13-14-15\n");
	file.WriteString(L"�ƶ�|4-5-6-7-8-9-10-11\n");
	file.WriteString(L"ǰ��|136-137-138-139-140-141-142-143\n");
	file.WriteString(L"����|28-29-30-31-32\n");
	file.WriteString(L"Z��|64-65-66-67-68\n");
	file.WriteString(L"�ͷ�|79-80-81-82-83-84-85\n");
	file.WriteString(L"����|74-75\n");
	file.WriteString(L"����|76-77-78\n");
	file.WriteString(L"\n");
	file.WriteString(L"[ħ��ʦ(Ů)]\n");
	file.WriteString(L"ͨ��|10-11-12-13\n");
	file.WriteString(L"��ս|14-15-16-17\n");
	file.WriteString(L"�ƶ�|0-1-2-3-4-5-6-7-8-9\n");
	file.WriteString(L"ǰ��|18-19-20-21\n");
	file.WriteString(L"����|109-110-111-112-113-113-113\n");
	file.WriteString(L"Z��|114-115-116-117-118-118-118\n");
	file.WriteString(L"�ͷ�|144-145-146-146-146-147\n");
	file.WriteString(L"����|128-128-129-129\n");
	file.WriteString(L"����|133-134-134-134-134-134\n");
	file.WriteString(L"\n");
	file.WriteString(L"[ħ��ʦ(��)]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5-6-7\n");
	file.WriteString(L"��ս|8-9-10-11-12-13-14-15-16-17\n");
	file.WriteString(L"�ƶ�|18-19-20-21-22-23-24-25-26-27\n");
	file.WriteString(L"ǰ��|28-29-30-31-32-33-34-35\n");
	file.WriteString(L"����|60-61-62-63-64\n");
	file.WriteString(L"Z��|60-61-62-63-64\n");
	file.WriteString(L"�ͷ�|142-143-144-145-146-147-148-149-150-151-152-153\n");
	file.WriteString(L"����|175-176\n");
	file.WriteString(L"����|177-178-179\n");
	file.WriteString(L"\n");
	file.WriteString(L"[ʥְ��(��)]\n");
	file.WriteString(L"ͨ��|0-1-2-3\n");
	file.WriteString(L"��ս|4-5-6-7\n");
	file.WriteString(L"�ƶ�|65-66-67-68-69-70-71-72\n");
	file.WriteString(L"ǰ��|73-74-75-76-77-78\n");
	file.WriteString(L"����|8-9-10-11-12-13-14-15\n");
	file.WriteString(L"Z��|31-32-33-34-35-36-37-38-39\n");
	file.WriteString(L"�ͷ�|146-147-148-149-150-151-152-153\n");
	file.WriteString(L"����|122-123\n");
	file.WriteString(L"����|124-126-126-126\n");
	file.WriteString(L"\n");
	file.WriteString(L"[ʥְ��(Ů)]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5-6-7-8\n");
	file.WriteString(L"��ս|9-10-11-12\n");
	file.WriteString(L"�ƶ�|13-14-15-16-17-18-19-20\n");
	file.WriteString(L"ǰ��|21-22-23-24-25-26-27-28\n");
	file.WriteString(L"����|23-30-31-32\n");
	file.WriteString(L"Z��|70-71-72-73\n");
	file.WriteString(L"�ͷ�|108-109-110-111-112\n");
	file.WriteString(L"����|51-52\n");
	file.WriteString(L"����|53-54-55\n");
	file.WriteString(L"\n");
	file.WriteString(L"[��ҹʹ��]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5-6-7-8-9-10-11\n");
	file.WriteString(L"��ս|12-13-14-15-16-17\n");
	file.WriteString(L"�ƶ�|18-19-20-21-22-23-24-25-26\n");
	file.WriteString(L"ǰ��|61-62-63-64-65-66\n");
	file.WriteString(L"����|67-68-69-70-71-72\n");
	file.WriteString(L"Z��|96-97-98-99-100\n");
	file.WriteString(L"�ͷ�|32-33-34-35-36-37-38-39-40-41-42-43-44-45\n");
	file.WriteString(L"����|91-92\n");
	file.WriteString(L"����|93-94-95\n");
	file.WriteString(L"\n");
	file.WriteString(L"[�ػ���]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5\n");
	file.WriteString(L"��ս|6-7-8-9-10-11\n");
	file.WriteString(L"�ƶ�|12-13-14-15-16-17-18-19-20-21\n");
	file.WriteString(L"ǰ��|22-23-24-25-26-27-28-29\n");
	file.WriteString(L"����|51-52-53-54-55-56-57-58-59\n");
	file.WriteString(L"Z��|182-183-184-185-186\n");
	file.WriteString(L"�ͷ�|170-171-172-173-174-175-176-177-178-179-180-171\n");
	file.WriteString(L"����|195-196\n");
	file.WriteString(L"����|197-198-199\n");
	file.WriteString(L"\n");
	file.WriteString(L"[ħǹʿ]\n");
	file.WriteString(L"ͨ��|0-1-2-3\n");
	file.WriteString(L"��ս|4-5-6-7\n");
	file.WriteString(L"�ƶ�|8-9-10-11-12-13-14-15-16\n");
	file.WriteString(L"ǰ��|17-18-19-20-21-22-23-24\n");
	file.WriteString(L"����|62-63-64-65-66\n");
	file.WriteString(L"Z��|143-144-145-146-147-148-149\n");
	file.WriteString(L"�ͷ�|158-159-160\n");
	file.WriteString(L"����|175-176\n");
	file.WriteString(L"����|177-178-179\n");
	file.WriteString(L"\n");
	file.WriteString(L"[ǹ��ʿ]\n");
	file.WriteString(L"ͨ��|0-1-2-3-4-5-6-7-8-9\n");
	file.WriteString(L"��ս|10-11-12-13-14\n");
	file.WriteString(L"�ƶ�|15-16-17-18-19-20-21-22\n");
	file.WriteString(L"ǰ��|23-24-25-26-27-28-29-30\n");
	file.WriteString(L"����|76-77-78-79\n");
	file.WriteString(L"Z��|56-57-58-59-60-61-62\n");
	file.WriteString(L"�ͷ�|141-142-143-144\n");
	file.WriteString(L"����|145-146\n");
	file.WriteString(L"����|147-148-149\n");
	CHS_LOCALE_END;
	file.Close();
}