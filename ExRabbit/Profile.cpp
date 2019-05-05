#include "StdAfx.h"
#include "Profile.h"


Profile::Profile(void){
	defaultProfile();
}
Profile::~Profile(void){
}
void Profile::defaultProfile(){
	outputPath = GetCurDir()+L"output";
	NPKdictPath = L"D:\\地下城与勇士\\ImagePacks2";
	avatarPath = L"D:\\地下城与勇士\\ImagePacks2";
	mainColor = 0xFFCCBB;
	canvasColor0 = 0xCCCCCC;
	canvasColor1 = 0xFFFFFF;
	canvasColor2 = 0xDDDDDD;
	avatarColor0 = 0xFFCCCC;
	avatarColor1 = 0xCCCCFF;
	avatarThumbSize = 1;
}
void Profile::loadProfile(){
	CStdioFile file;
	CString lineStr, termStr, valueStr;
	if(file.Open(L"profile.ini", CFile::modeRead)){
		char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
		setlocale(LC_CTYPE, "chs");
		while(file.ReadString(lineStr)){
			AfxExtractSubString(termStr, lineStr, 0, ']');
			AfxExtractSubString(valueStr, lineStr, 1, ']');
			if(valueStr.GetLength() == 0)
				continue;
			termStr += L"]";
			if(termStr == L"[OUTPUT_PATH]"){
				outputPath = valueStr;
			}
			if(termStr == L"[NPKDICT_PATH]"){
				NPKdictPath = valueStr;
			}
			if(termStr == L"[AVATAR_PATH]"){
				avatarPath = valueStr;
			}
			if(termStr == L"[MAIN_COLOR]"){
				mainColor = _ttoi(valueStr);
			}
			if(termStr == L"[CANVAS_COLOR0]"){
				canvasColor0 = _ttoi(valueStr);
			}
			if(termStr == L"[CANVAS_COLOR1]"){
				canvasColor1 = _ttoi(valueStr);
			}
			if(termStr == L"[CANVAS_COLOR2]"){
				canvasColor2 = _ttoi(valueStr);
			}
			if(termStr == L"[AVATAR_COLOR0]"){
				avatarColor0 = _ttoi(valueStr);
			}
			if(termStr == L"[AVATAR_COLOR1]"){
				avatarColor1 = _ttoi(valueStr);
			}
			if(termStr == L"[AVATAR_THUMBSIZE]"){
				avatarThumbSize = _ttoi(valueStr);
			}
		}
		setlocale(LC_CTYPE, old_locale);
		free(old_locale);
		file.Close();
	}else{
		saveProfile();
	}
	generateFolder();
}
void Profile::saveProfile(){
	CStdioFile file;
	CString lineStr, termStr, valueStr;
	file.Open(L"profile.ini", CFile::modeCreate|CFile::modeReadWrite);
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	file.WriteString(L"[OUTPUT_PATH]" + outputPath + L"\n");
	file.WriteString(L"[NPKDICT_PATH]" + NPKdictPath + L"\n");
	file.WriteString(L"[AVATAR_PATH]" + avatarPath + L"\n");
	file.WriteString(L"[MAIN_COLOR]" + NumToCStr(mainColor) + L"\n");
	file.WriteString(L"[CANVAS_COLOR0]" + NumToCStr(canvasColor0) + L"\n");
	file.WriteString(L"[CANVAS_COLOR1]" + NumToCStr(canvasColor1) + L"\n");
	file.WriteString(L"[CANVAS_COLOR2]" + NumToCStr(canvasColor2) + L"\n");
	file.WriteString(L"[AVATAR_COLOR0]" + NumToCStr(avatarColor0) + L"\n");
	file.WriteString(L"[AVATAR_COLOR1]" + NumToCStr(avatarColor1) + L"\n");
	file.WriteString(L"[AVATAR_THUMBSIZE]" + NumToCStr(avatarThumbSize) + L"\n");
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
	//如果目录没有则创建
	generateFolder();
}
void Profile::generateFolder(){
	getOutputPath();
	getDownloadPath();
	getSupportPath();
}
CString Profile::getOutputPath(){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getOutputPath(CString npkName){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(npkName);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getOutputPath(CString npkName, CString imgName){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(npkName);
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(imgName);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getOutputPath(CString npkName, CString imgName, int clPro){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(npkName);
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(imgName);
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Palette"+NumToCStr(clPro);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getDownloadPath(){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Download";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getThumbnailPath(int thumbSize, KoishiAvatar::avatarCareer ac){
	CString careerName[15] = {L"default",L"swordman",L"atswordman",L"fighter",L"atfighter",L"gunner",L"atgunner",L"mage",L"atmage",L"priest",L"atpriest",L"thief",L"knight",L"demoniclancer",L"gunblader"};
	CString s[4] = {L"Small", L"Medium", L"Large", L"Huge"};
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Thumbnail";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + s[thumbSize % 4];
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + careerName[ac];
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getIconPath(KoishiAvatar::avatarCareer ac){
	CString careerName[15] = {L"default",L"swordman",L"atswordman",L"fighter",L"atfighter",L"gunner",L"atgunner",L"mage",L"atmage",L"priest",L"atpriest",L"thief",L"knight",L"demoniclancer",L"gunblader"};
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Thumbnail";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\AvatarIcon";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + careerName[ac];
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getSupportPath(){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Support";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getNPKdictPath(){
	return NPKdictPath + L"\\";
}
CString Profile::getAvatarPath(){
	return avatarPath + L"\\";
}
Koishi::color Profile::getMainColor(){
	return color(0xFF, (mainColor & 0xFF0000)>> 16, (mainColor & 0XFF00)>> 8, mainColor & 0xFF);
}
Koishi::color Profile::getCanvasColor(int n){
	DWORD canvasColorList[3] = {canvasColor0, canvasColor1, canvasColor2};
	return color(0xFF, (canvasColorList[n%3] & 0xFF0000)>> 16, (canvasColorList[n%3] & 0XFF00)>> 8, canvasColorList[n%3] & 0xFF);
}
Koishi::color Profile::getAvatarColor(int n){
	DWORD avatarColorList[3] = {avatarColor0, avatarColor1};
	return color(0xFF, (avatarColorList[n%2] & 0xFF0000)>> 16, (avatarColorList[n%2] & 0XFF00)>> 8, avatarColorList[n%2] & 0xFF);
}