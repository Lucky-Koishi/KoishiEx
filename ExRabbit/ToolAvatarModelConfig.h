#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"

using namespace Koishi;
using namespace KoishiAvatar;
class ToolAvatarModelConfig
{
public:
	ToolAvatarModelConfig(void);
public:
	color modelBackColor[ACHARACTER_MAXCOUNT];
	long modelAvatarFrame[ACHARACTER_MAXCOUNT][APART_MAXCOUNT];
	long modelWeaponFrame[ACHARACTER_MAXCOUNT];
	point modelAvatarOffset[ACHARACTER_MAXCOUNT][APART_MAXCOUNT];
	point modelWeaponOffset[ACHARACTER_MAXCOUNT];
	
public:
	void load(const CString &filePath);
	void save(const CString &filePath);
	void defaultConfig();
};

