#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/KoishiImageTool.h"
#include <vector>
using namespace Koishi;
using namespace KoishiImageTool;
class ToolAvatarStageConfig
{
public:
	ToolAvatarStageConfig(void);
public:
	bool loaded;
	image backLayer;
	image foreLayer;
public:
	void load(const CString &stageConfigFolderPath);
	void createEmpty(const CString &stageConfigFolderPath);
};

class ToolAvatarAnimation {
public:
	ToolAvatarAnimation();
public:
	typedef struct {
		CString aniName;
		queue aniFrame;
		long operator[](int frameID) const;
	}animation;
	std::vector<animation> ann;
	animation operator[](int aniID) const;
	void load(const CString &stageConfigFolderPath, KoishiAvatar::AvatarCharacter ac);
	void createEmpty(const CString &stageConfigFolderPath);
};