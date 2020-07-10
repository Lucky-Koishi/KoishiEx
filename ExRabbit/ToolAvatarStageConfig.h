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

