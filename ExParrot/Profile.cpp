#include "StdAfx.h"
#include "Profile.h"


Profile::Profile(void){
	defaultProfile();
}
Profile::~Profile(void){
}
void Profile::defaultProfile(){
	outputPath = GetCurDir()+L"output";
	NPKdictPath = L"D:\\���³�����ʿ\\ImagePacks2";
	avatarPath = L"D:\\���³�����ʿ\\ImagePacks2";
	mainColor = 0xFFCCBB;
	canvasColor0 = 0xCCCCCC;
	canvasColor1 = 0xFFFFFF;
	canvasColor2 = 0xDDDDDD;
	avatarColor0 = 0xFFCCCC;
	avatarColor1 = 0xCCCCFF;
	avatarThumbSize = 1;
	miniSecPerFrame = 100;
	audioBackColor = 0;
	channel1Color = 0xFFFF00;
	channel1Color = 0x33FF00;
	volumeColor = 0xFFFF00;
	MP3defaultColor = 0xCCCCCC;
	MP3quality = 3;
	useDefaultRecorder = 1;
}
void Profile::loadProfile(){
	CStdioFile file;
	CString lineStr, termStr, valueStr;
	TRACE(L"LOAD\n");
	if(file.Open(L"profile.ini", CFile::modeRead)){
		TRACE(L"OKLOAD\n");
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
		TRACE(L"FAILLOAD\n");
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
	//���Ŀ¼û���򴴽�
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
Koishi::color Profile::getAudioColor(int n){
	DWORD audioColorList[5] = {audioBackColor, channel1Color, channel2Color, volumeColor, MP3defaultColor};
	return color(0xFF, audioColorList[n%5] & 0xFF, (audioColorList[n%5] & 0XFF00)>> 8, (audioColorList[n%5] & 0xFF0000)>> 16);
}