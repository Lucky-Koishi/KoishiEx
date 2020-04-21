#pragma once
class Profile
{
public:
	Profile(void);
	~Profile(void);

public:
	CString outputPath;
	CString NPKdictPath;
	CString avatarPath;
	DWORD mainColor;
	DWORD canvasColor0;
	DWORD canvasColor1;
	DWORD canvasColor2;
	DWORD avatarColor0;
	DWORD avatarColor1;
	DWORD avatarThumbSize;
	DWORD miniSecPerFrame;
	DWORD audioBackColor;
	DWORD channel1Color;
	DWORD channel2Color;
	DWORD volumeColor;
	DWORD MP3defaultColor;
	DWORD MP3quality;
	DWORD useDefaultRecorder;
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
	CString getThumbnailPath(int thumbSize, KoishiAvatar::avatarCareer ac);
	CString getIconPath(KoishiAvatar::avatarCareer ac);
	CString getSupportPath();
	CString getNPKdictPath();
	CString getAvatarPath();
	Koishi::color getMainColor();
	Koishi::color getCanvasColor(int n);
	Koishi::color getAvatarColor(int n);
	Koishi::color getAudioColor(int n);
};

