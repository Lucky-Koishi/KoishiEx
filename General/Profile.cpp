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
	avatarModelSize = 1;
	miniSecPerFrame = 100;
	audioBackColor = 0;
	channel1Color = 0xFFFF00;
	channel1Color = 0x33FF00;
	volumeColor = 0xFFFF00;
	MP3defaultColor = 0xCCCC00;
	MP3quality = 3;
	useDefaultRecorder = 1;
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
				avatarModelSize = _ttoi(valueStr);
			}
			if(termStr == L"[GIF_MSPF]"){
				miniSecPerFrame = _ttoi(valueStr);
			}
			if(termStr == L"[AUDIOBACK_COLOR]"){
				audioBackColor = _ttoi(valueStr);
			}
			if(termStr == L"[CHANNEL1_COLOR]"){
				channel1Color = _ttoi(valueStr);
			}
			if(termStr == L"[CHANNEL2_COLOR]"){
				channel2Color = _ttoi(valueStr);
			}
			if(termStr == L"[VOLUME_COLOR]"){
				volumeColor = _ttoi(valueStr);
			}
			if(termStr == L"[MP3_DEFAULT_COLOR]"){
				MP3defaultColor = _ttoi(valueStr);
			}
			if(termStr == L"[MP3_QUALITY]"){
				MP3quality = _ttoi(valueStr);
			}
			if(termStr == L"[USE_DEFAULT_RECORDER]"){
				useDefaultRecorder = _ttoi(valueStr);
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
	file.WriteString(L"[AVATAR_THUMBSIZE]" + NumToCStr(avatarModelSize) + L"\n");
	file.WriteString(L"[GIF_MSPF]" + NumToCStr(miniSecPerFrame) + L"\n");
	file.WriteString(L"[AUDIOBACK_COLOR]" + NumToCStr(audioBackColor) + L"\n");
	file.WriteString(L"[CHANNEL1_COLOR]" + NumToCStr(channel1Color) + L"\n");
	file.WriteString(L"[CHANNEL2_COLOR]" + NumToCStr(channel2Color) + L"\n");
	file.WriteString(L"[VOLUME_COLOR]" + NumToCStr(volumeColor) + L"\n");
	file.WriteString(L"[MP3_DEFAULT_COLOR]" + NumToCStr(MP3defaultColor) + L"\n");
	file.WriteString(L"[MP3_QUALITY]" + NumToCStr(MP3quality) + L"\n");
	file.WriteString(L"[USE_DEFAULT_RECORDER]" + NumToCStr(useDefaultRecorder) + L"\n");
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
CString Profile::getDownloadPath(CString hostName) {
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Download";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\" + hostName;
	::CreateDirectory(savePathStr, NULL);
	return savePathStr + L"\\";
}
CString Profile::getModelPath(int modelSize, KoishiAvatar::AvatarCharacter ac){
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
CString Profile::getIconPath(KoishiAvatar::AvatarCharacter ac){
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
CString Profile::getAvatarStagePath(){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\舞台";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getAvatarDownloadPath(){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\NPK资源";
	::CreateDirectory(savePathStr, NULL);
	return savePathStr+L"\\";
}
CString Profile::getAvatarMapPath(){
	CString savePathStr = outputPath;
	::CreateDirectory(savePathStr, NULL);
	savePathStr += L"\\Avatar";
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
Koishi::color Profile::getAudioColor(int n){
	DWORD audioColorList[5] = {audioBackColor, channel1Color, channel2Color, volumeColor, MP3defaultColor};
	return color(0xFF, (audioColorList[n%5] & 0xFF0000)>> 16, (audioColorList[n%5] & 0XFF00)>> 8, audioColorList[n%5] & 0xFF);
}