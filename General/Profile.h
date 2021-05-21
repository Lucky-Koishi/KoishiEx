#pragma once
#include "../KoishiEx/avatar.h"
class ProfileBlack
{
public:
	ProfileBlack(void);
	~ProfileBlack(void);

public:
	CString outputPath;		//输出目录
	CString sourcePath;		//资源目录
	CString avatarPath;		//试衣间资源目录
	DWORD mainColor;		//主界面颜色
	DWORD canvasColor0;		//绘制区域颜色
	DWORD canvasColor1;		//画布颜色1
	DWORD canvasColor2;		//画布颜色2
	DWORD avatarModelSize;
	DWORD miniSecPerFrame;
public:
	void defaultProfile();
	void loadProfile();
	void saveProfile();
	void generateFolder();
public:
	CString getOutputPath();
	CString getOutputPath(CString npkName);
	CString getOutputPath(CString npkName, CString imgName);
	CString getOutputPath(CString npkName, CString imgName, int clPro);
	CString getDownloadPath();
	CString getDownloadPath(CString hostName);
	CString getModelPath(int modelSize, KoishiAvatar::AvatarCharacter ac);
	CString getIconPath(KoishiAvatar::AvatarCharacter ac);
	CString getAvatarStagePath();
	CString getAvatarDownloadPath();
	CString getAvatarMapPath();
	CString getSupportPath();
	CString getSourcePath();
	CString getAvatarPath();
	Koishi::color getMainColor();
	Koishi::color getCanvasColor(int n);
	Koishi::color getAvatarColor(int n);
};

class ProfileWhite {
public:
	ProfileWhite(void);
	~ProfileWhite(void);

public:
	CString outputPath;
	CString sourcePath;
	CString videoPath;
	DWORD mainColor;
	DWORD audioBackColor;
	DWORD channel1Color;
	DWORD channel2Color;
	DWORD volumeColor;
	DWORD MP3defaultColor;
	DWORD outputQuality;
	CString artist;
public:
	void defaultProfile();
	void loadProfile();
	void saveProfile();
	void generateFolder();
public:
	CString getOutputPath();
	CString getOutputPath(CString npkName);
	CString getDownloadPath();
	CString getDownloadPath(CString hostName);
	CString getSupportPath();
	CString getSourcePath();
	CString getVideoPath();
	Koishi::color getMainColor();
	Koishi::color getAudioColor(int n);
};

