#include "StdAfx.h"
#include "Profile.h"

ProfileBlack::ProfileBlack(void) {
	defaultProfile();
}
ProfileBlack::~ProfileBlack(void) {
}
void ProfileBlack::defaultProfile() {
	outputPath = GetCurDir()+L"output";
	sourcePath = L"D:\\地下城与勇士\\ImagePacks2";
	avatarPath = L"D:\\地下城与勇士\\ImagePacks2";
	mainColor = 0xFFCCBB;
	canvasColor0 = 0xCCCCCC;
	canvasColor1 = 0xFFFFFF;
	canvasColor2 = 0xDDDDDD;
	avatarModelSize = 1;
	miniSecPerFrame = 100;
}
void ProfileBlack::loadProfile() {
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
				sourcePath = valueStr;
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
			if(termStr == L"[AVATAR_THUMBSIZE]"){
				avatarModelSize = _ttoi(valueStr);
			}
			if(termStr == L"[GIF_MSPF]"){
				miniSecPerFrame = _ttoi(valueStr);
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
void ProfileBlack::saveProfile() {
	CStdioFile file;
	CString lineStr, termStr, valueStr;
	file.Open(L"profile.ini", CFile::modeCreate|CFile::modeReadWrite);
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	file.WriteString(L"[OUTPUT_PATH]" + outputPath + L"\n");
	file.WriteString(L"[NPKDICT_PATH]" + sourcePath + L"\n");
	file.WriteString(L"[AVATAR_PATH]" + avatarPath + L"\n");
	file.WriteString(L"[MAIN_COLOR]" + NumToCStr(mainColor) + L"\n");
	file.WriteString(L"[CANVAS_COLOR0]" + NumToCStr(canvasColor0) + L"\n");
	file.WriteString(L"[CANVAS_COLOR1]" + NumToCStr(canvasColor1) + L"\n");
	file.WriteString(L"[CANVAS_COLOR2]" + NumToCStr(canvasColor2) + L"\n");
	file.WriteString(L"[AVATAR_THUMBSIZE]" + NumToCStr(avatarModelSize) + L"\n");
	file.WriteString(L"[GIF_MSPF]" + NumToCStr(miniSecPerFrame) + L"\n");
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
	//如果目录没有则创建
	generateFolder();
}
void ProfileBlack::generateFolder() {
	getOutputPath();
	getDownloadPath();
	getSupportPath();
}
CString ProfileBlack::getOutputPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getOutputPath(CString npkName) {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(npkName);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getOutputPath(CString npkName, CString imgName) {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(npkName);
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\"+GetTail(imgName);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getOutputPath(CString npkName, CString imgName, int clPro) {
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
CString ProfileBlack::getDownloadPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Download";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getDownloadPath(CString hostName) {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Download";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + hostName;
	::CreateDirectory(savePathStr, NULL);
	return savePathStr + L"\\";
}
CString ProfileBlack::getModelPath(int modelSize, KoishiAvatar::AvatarCharacter ac) {
	CString careerName[KoishiAvatar::ACHARACTER_MAXCOUNT] = {L"鬼剑士(男)",L"鬼剑士(女)",L"格斗家(女)",L"格斗家(男)",L"神枪手(男)",L"神枪手(女)",L"魔法师(女)",L"魔法师(男)",L"圣职者(男)",L"圣职者(女)",L"暗夜使者",L"守护者",L"魔枪士",L"枪剑士"};
	CString s[4] = {L"小", L"中", L"大", L"巨大"};
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + s[modelSize % 4];
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + careerName[ac];
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getIconPath(KoishiAvatar::AvatarCharacter ac) {
	CString careerName[KoishiAvatar::ACHARACTER_MAXCOUNT] = {L"鬼剑士(男)",L"鬼剑士(女)",L"格斗家(女)",L"格斗家(男)",L"神枪手(男)",L"神枪手(女)",L"魔法师(女)",L"魔法师(男)",L"圣职者(男)",L"圣职者(女)",L"暗夜使者",L"守护者",L"魔枪士",L"枪剑士"};
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\图标";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + careerName[ac];
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getAvatarStagePath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\舞台";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getAvatarDownloadPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\NPK资源";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getAvatarMapPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getSupportPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Support";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString ProfileBlack::getSourcePath() {
	return sourcePath + L"\\";
}
CString ProfileBlack::getAvatarPath() {
	return avatarPath + L"\\";
}
Koishi::color ProfileBlack::getMainColor() {
	return color(0xFF, (mainColor & 0xFF0000)>> 16, (mainColor & 0XFF00)>> 8, mainColor & 0xFF);
}
Koishi::color ProfileBlack::getCanvasColor(int n) {
	DWORD canvasColorList[3] = {canvasColor0, canvasColor1, canvasColor2};
	return color(0xFF, (canvasColorList[n%3] & 0xFF0000)>> 16, (canvasColorList[n%3] & 0XFF00)>> 8, canvasColorList[n%3] & 0xFF);
}
///////////////////////////

ProfileWhite::ProfileWhite(void) {
	defaultProfile();
}
ProfileWhite::~ProfileWhite(void) {}
void ProfileWhite::defaultProfile() {
	outputPath = GetCurDir() + L"output";
	sourcePath = L"D:\\地下城与勇士\\SoundPacks";
	videoPath = L"D:\\地下城与勇士\\SoundPacks";
	mainColor = 0xFFCCBB;
	audioBackColor = 0;
	channel1Color = 0xFFFF00;
	channel2Color = 0x33FF00;
	volumeColor = 0xFFFF00;
	MP3defaultColor = 0xCCCC00;
	outputQuality = 3;
	artist = L"noname";
}
void ProfileWhite::loadProfile() {
	CStdioFile file;
	CString lineStr, termStr, valueStr;
	if(file.Open(L"profile_w.ini", CFile::modeRead)) {
		char *old_locale = _strdup(setlocale(LC_CTYPE, NULL));
		setlocale(LC_CTYPE, "chs");
		while(file.ReadString(lineStr)) {
			AfxExtractSubString(termStr, lineStr, 0, ']');
			AfxExtractSubString(valueStr, lineStr, 1, ']');
			if(valueStr.GetLength() == 0)
				continue;
			termStr += L"]";
			if(termStr == L"[OUTPUT_PATH]") {
				outputPath = valueStr;
			}
			if(termStr == L"[NPKDICT_PATH]") {
				sourcePath = valueStr;
			}
			if(termStr == L"[VIDEO_PATH]") {
				videoPath = valueStr;
			}
			if(termStr == L"[MAIN_COLOR]") {
				mainColor = _ttoi(valueStr);
			}
			if(termStr == L"[AUDIOBACK_COLOR]") {
				audioBackColor = _ttoi(valueStr);
			}
			if(termStr == L"[CHANNEL1_COLOR]") {
				channel1Color = _ttoi(valueStr);
			}
			if(termStr == L"[CHANNEL2_COLOR]") {
				channel2Color = _ttoi(valueStr);
			}
			if(termStr == L"[VOLUME_COLOR]") {
				volumeColor = _ttoi(valueStr);
			}
			if(termStr == L"[MP3_DEFAULT_COLOR]") {
				MP3defaultColor = _ttoi(valueStr);
			}
			if(termStr == L"[OUTPUT_QUALITY]") {
				outputQuality = _ttoi(valueStr);
			}
			if(termStr == L"[ARTIST]") {
				artist = valueStr;
			}
		}
		setlocale(LC_CTYPE, old_locale);
		free(old_locale);
		file.Close();
	} else {
		saveProfile();
	}
	generateFolder();
}
void ProfileWhite::saveProfile() {
	CStdioFile file;
	CString lineStr, termStr, valueStr;
	file.Open(L"profile_w.ini", CFile::modeCreate | CFile::modeReadWrite);
	char *old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");
	file.WriteString(L"[OUTPUT_PATH]" + outputPath + L"\n");
	file.WriteString(L"[NPKDICT_PATH]" + sourcePath + L"\n");
	file.WriteString(L"[VIDEO_PATH]" + videoPath + L"\n");
	file.WriteString(L"[MAIN_COLOR]" + NumToCStr(mainColor) + L"\n");
	file.WriteString(L"[AUDIOBACK_COLOR]" + NumToCStr(audioBackColor) + L"\n");
	file.WriteString(L"[CHANNEL1_COLOR]" + NumToCStr(channel1Color) + L"\n");
	file.WriteString(L"[CHANNEL2_COLOR]" + NumToCStr(channel2Color) + L"\n");
	file.WriteString(L"[VOLUME_COLOR]" + NumToCStr(volumeColor) + L"\n");
	file.WriteString(L"[MP3_DEFAULT_COLOR]" + NumToCStr(MP3defaultColor) + L"\n");
	file.WriteString(L"[OUTPUT_QUALITY]" + NumToCStr(outputQuality) + L"\n");
	file.WriteString(L"[ARTIST]" + artist + L"\n");
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
	//如果目录没有则创建
	generateFolder();
}
void ProfileWhite::generateFolder() {
	getOutputPath();
	getDownloadPath();
	getSupportPath();
}
CString ProfileWhite::getOutputPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	return savePathStr + L"\\";
}
CString ProfileWhite::getOutputPath(CString npkName) {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + GetTail(npkName);
	::CreateDirectory(savePathStr, NULL);
	return savePathStr + L"\\";
}
CString ProfileWhite::getDownloadPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Download";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr + L"\\";
}
CString ProfileWhite::getDownloadPath(CString hostName) {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Download";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + hostName;
	::CreateDirectory(savePathStr, NULL);
	return savePathStr + L"\\";
}
CString ProfileWhite::getSupportPath() {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Support";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr + L"\\";
}
CString ProfileWhite::getSourcePath() {
	return sourcePath + L"\\";
}
CString ProfileWhite::getVideoPath() {
	return videoPath + L"\\";
}
Koishi::color ProfileWhite::getMainColor() {
	return color(0xFF, (mainColor & 0xFF0000) >> 16, (mainColor & 0XFF00) >> 8, mainColor & 0xFF);
}
Koishi::color ProfileWhite::getAudioColor(int n) {
	DWORD audioColorList[5] = {audioBackColor, channel1Color, channel2Color, volumeColor, MP3defaultColor};
	return color(0xFF, (audioColorList[n % 5] & 0xFF0000) >> 16, (audioColorList[n % 5] & 0XFF00) >> 8, audioColorList[n % 5] & 0xFF);
}