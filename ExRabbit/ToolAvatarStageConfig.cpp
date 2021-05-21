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
		int readContent = -1; //0.背景 1.背景图片 2.前景图片
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
		L"鬼剑士(男)", L"鬼剑士(女)", L"格斗家(女)", L"格斗家(男)",
		L"神枪手(男)", L"神枪手(女)", L"魔法师(女)", L"魔法师(男)",
		L"圣职者(男)", L"圣职者(女)",
		L"暗夜使者", L"守护者", L"魔枪士", L"枪剑士"
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
				//查不到带“|”的了
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
	file.WriteString(L"[鬼剑士(男)]\n");
	file.WriteString(L"通常|176-176-176-177-178\n");
	file.WriteString(L"备战|90-91-92-93-94-95\n");
	file.WriteString(L"移动|180-181-182-183-184-185-186-187\n");
	file.WriteString(L"前冲|105-106-107-108-109-110-111-112\n");
	file.WriteString(L"攻击|0-2-3-4-5-6-7-8-8-8-8\n");
	file.WriteString(L"Z键|33-34-35-36-37-38-39-39-39-39\n");
	file.WriteString(L"释放|75-76-77-78-79-80-81-82-82-82\n");
	file.WriteString(L"被击|96-96-96-99-99-99\n");
	file.WriteString(L"倒地|101-102-102-102-102-102-102-102\n");
	file.WriteString(L"\n");
	file.WriteString(L"[鬼剑士(女)]\n");
	file.WriteString(L"通常|0-1-2-3-4-5-6-7-8\n");
	file.WriteString(L"备战|9-10-11-12\n");
	file.WriteString(L"移动|13-14-15-16-17-18-19-20-21-22\n");
	file.WriteString(L"前冲|151-152-153-154-155-156-157-158\n");
	file.WriteString(L"攻击|48-49-50-51-52\n");
	file.WriteString(L"Z键|48-49-50-51-52\n");
	file.WriteString(L"释放|121-122-123-124-125-126-127-128-129-130-131-132-133-134-135-136\n");
	file.WriteString(L"被击|139-140\n");
	file.WriteString(L"倒地|141-142-143\n");
	file.WriteString(L"\n");
	file.WriteString(L"[神枪手(男)]\n");
	file.WriteString(L"通常|0-1-2-3-4-5-6-7-8-9-10-11-12\n");
	file.WriteString(L"备战|13-14-15-16-17-18-19-20-21-22\n");
	file.WriteString(L"移动|55-56-57-58-59-60-61-62\n");
	file.WriteString(L"前冲|103-104-105-106-107-108-109-110\n");
	file.WriteString(L"攻击|25-26-27-28-29-30-31-32-33-34-35-36-37-38\n");
	file.WriteString(L"Z键|155-156-157-158\n");
	file.WriteString(L"释放|193-194-195-196-197\n");
	file.WriteString(L"被击|121-122-123-124\n");
	file.WriteString(L"倒地|125-126-127\n");
	file.WriteString(L"\n");
	file.WriteString(L"[神枪手(女)]\n");
	file.WriteString(L"通常|0-1-2-3-4-5-6-7-8-9\n");
	file.WriteString(L"备战|14-15-16-17-18-19-20\n");
	file.WriteString(L"移动|68-69-70-71-72-73-74-75\n");
	file.WriteString(L"前冲|76-77-78-79-80-71\n");
	file.WriteString(L"攻击|22-23-24-25-26-27-28-29-30-31-32-33-34-35\n");
	file.WriteString(L"Z键|111-112-113-114-115\n");
	file.WriteString(L"释放|10-11-12-13\n");
	file.WriteString(L"被击|89-90\n");
	file.WriteString(L"倒地|91\n");
	file.WriteString(L"\n");
	file.WriteString(L"[格斗家(女)]\n");
	file.WriteString(L"备战|132-133-134-135\n");
	file.WriteString(L"移动|136-137-138-139-140-141-142-143\n");
	file.WriteString(L"前冲|39-40-41-42-43-44-45-46\n");
	file.WriteString(L"攻击|5-6-7-8-9\n");
	file.WriteString(L"Z键|30-31-32-33-34-35\n");
	file.WriteString(L"释放|92-93-94-95\n");
	file.WriteString(L"被击|77-78-84-85\n");
	file.WriteString(L"倒地|79-80-81-82-83\n");
	file.WriteString(L"\n");
	file.WriteString(L"[格斗家(男)]\n");
	file.WriteString(L"通常|0-1-2-3\n");
	file.WriteString(L"备战|12-13-14-15\n");
	file.WriteString(L"移动|4-5-6-7-8-9-10-11\n");
	file.WriteString(L"前冲|136-137-138-139-140-141-142-143\n");
	file.WriteString(L"攻击|28-29-30-31-32\n");
	file.WriteString(L"Z键|64-65-66-67-68\n");
	file.WriteString(L"释放|79-80-81-82-83-84-85\n");
	file.WriteString(L"被击|74-75\n");
	file.WriteString(L"倒地|76-77-78\n");
	file.WriteString(L"\n");
	file.WriteString(L"[魔法师(女)]\n");
	file.WriteString(L"通常|10-11-12-13\n");
	file.WriteString(L"备战|14-15-16-17\n");
	file.WriteString(L"移动|0-1-2-3-4-5-6-7-8-9\n");
	file.WriteString(L"前冲|18-19-20-21\n");
	file.WriteString(L"攻击|109-110-111-112-113-113-113\n");
	file.WriteString(L"Z键|114-115-116-117-118-118-118\n");
	file.WriteString(L"释放|144-145-146-146-146-147\n");
	file.WriteString(L"被击|128-128-129-129\n");
	file.WriteString(L"倒地|133-134-134-134-134-134\n");
	file.WriteString(L"\n");
	file.WriteString(L"[魔法师(男)]\n");
	file.WriteString(L"通常|0-1-2-3-4-5-6-7\n");
	file.WriteString(L"备战|8-9-10-11-12-13-14-15-16-17\n");
	file.WriteString(L"移动|18-19-20-21-22-23-24-25-26-27\n");
	file.WriteString(L"前冲|28-29-30-31-32-33-34-35\n");
	file.WriteString(L"攻击|60-61-62-63-64\n");
	file.WriteString(L"Z键|60-61-62-63-64\n");
	file.WriteString(L"释放|142-143-144-145-146-147-148-149-150-151-152-153\n");
	file.WriteString(L"被击|175-176\n");
	file.WriteString(L"倒地|177-178-179\n");
	file.WriteString(L"\n");
	file.WriteString(L"[圣职者(男)]\n");
	file.WriteString(L"通常|0-1-2-3\n");
	file.WriteString(L"备战|4-5-6-7\n");
	file.WriteString(L"移动|65-66-67-68-69-70-71-72\n");
	file.WriteString(L"前冲|73-74-75-76-77-78\n");
	file.WriteString(L"攻击|8-9-10-11-12-13-14-15\n");
	file.WriteString(L"Z键|31-32-33-34-35-36-37-38-39\n");
	file.WriteString(L"释放|146-147-148-149-150-151-152-153\n");
	file.WriteString(L"被击|122-123\n");
	file.WriteString(L"倒地|124-126-126-126\n");
	file.WriteString(L"\n");
	file.WriteString(L"[圣职者(女)]\n");
	file.WriteString(L"通常|0-1-2-3-4-5-6-7-8\n");
	file.WriteString(L"备战|9-10-11-12\n");
	file.WriteString(L"移动|13-14-15-16-17-18-19-20\n");
	file.WriteString(L"前冲|21-22-23-24-25-26-27-28\n");
	file.WriteString(L"攻击|23-30-31-32\n");
	file.WriteString(L"Z键|70-71-72-73\n");
	file.WriteString(L"释放|108-109-110-111-112\n");
	file.WriteString(L"被击|51-52\n");
	file.WriteString(L"倒地|53-54-55\n");
	file.WriteString(L"\n");
	file.WriteString(L"[暗夜使者]\n");
	file.WriteString(L"通常|0-1-2-3-4-5-6-7-8-9-10-11\n");
	file.WriteString(L"备战|12-13-14-15-16-17\n");
	file.WriteString(L"移动|18-19-20-21-22-23-24-25-26\n");
	file.WriteString(L"前冲|61-62-63-64-65-66\n");
	file.WriteString(L"攻击|67-68-69-70-71-72\n");
	file.WriteString(L"Z键|96-97-98-99-100\n");
	file.WriteString(L"释放|32-33-34-35-36-37-38-39-40-41-42-43-44-45\n");
	file.WriteString(L"被击|91-92\n");
	file.WriteString(L"倒地|93-94-95\n");
	file.WriteString(L"\n");
	file.WriteString(L"[守护者]\n");
	file.WriteString(L"通常|0-1-2-3-4-5\n");
	file.WriteString(L"备战|6-7-8-9-10-11\n");
	file.WriteString(L"移动|12-13-14-15-16-17-18-19-20-21\n");
	file.WriteString(L"前冲|22-23-24-25-26-27-28-29\n");
	file.WriteString(L"攻击|51-52-53-54-55-56-57-58-59\n");
	file.WriteString(L"Z键|182-183-184-185-186\n");
	file.WriteString(L"释放|170-171-172-173-174-175-176-177-178-179-180-171\n");
	file.WriteString(L"被击|195-196\n");
	file.WriteString(L"倒地|197-198-199\n");
	file.WriteString(L"\n");
	file.WriteString(L"[魔枪士]\n");
	file.WriteString(L"通常|0-1-2-3\n");
	file.WriteString(L"备战|4-5-6-7\n");
	file.WriteString(L"移动|8-9-10-11-12-13-14-15-16\n");
	file.WriteString(L"前冲|17-18-19-20-21-22-23-24\n");
	file.WriteString(L"攻击|62-63-64-65-66\n");
	file.WriteString(L"Z键|143-144-145-146-147-148-149\n");
	file.WriteString(L"释放|158-159-160\n");
	file.WriteString(L"被击|175-176\n");
	file.WriteString(L"倒地|177-178-179\n");
	file.WriteString(L"\n");
	file.WriteString(L"[枪剑士]\n");
	file.WriteString(L"通常|0-1-2-3-4-5-6-7-8-9\n");
	file.WriteString(L"备战|10-11-12-13-14\n");
	file.WriteString(L"移动|15-16-17-18-19-20-21-22\n");
	file.WriteString(L"前冲|23-24-25-26-27-28-29-30\n");
	file.WriteString(L"攻击|76-77-78-79\n");
	file.WriteString(L"Z键|56-57-58-59-60-61-62\n");
	file.WriteString(L"释放|141-142-143-144\n");
	file.WriteString(L"被击|145-146\n");
	file.WriteString(L"倒地|147-148-149\n");
	CHS_LOCALE_END;
	file.Close();
}