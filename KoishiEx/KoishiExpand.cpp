#include "StdAfx.h"
#include "KoishiEx.h"
#include "avatar.h"
#include "KoishiNeoplePack.h"
#include "KoishiImageTool.h"
#include <fstream> 

using namespace Koishi;
using namespace KoishiAvatar;
using namespace KoishiNeoplePack;
using namespace KoishiExpand::KoishiMarkTool;
using namespace KoishiExpand::KoishiDownloadTool;

char tinyChar[54][100] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1,
		0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},//COAT !
		{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},//PANTS @
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
		0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},//shoes #
		{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
		0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//hair $
		{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},//cap ^
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//neck +
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
		0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},//face |
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0,
		0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//belt :
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0},//skin ;
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1}//weapon ,
};
void KoishiExpand::KoishiMarkTool::CharMatLarge(char p, Koishi::image &mat, Koishi::color clr){
	if(p>='a'&& p <= 'z'){
		p = p-'a'+'A';
	}
	int situ = 0;
	if(p >= 'A' && p <= 'Z'){situ = p - 'A' + 10;}
	else if(p >= '0' && p<= '9'){situ = p - '0';}
	else if(p == '.'){situ = 36;}
	else if(p == '_'){situ = 37;}
	else if(p == '('){situ = 38;}
	else if(p == ')'){situ = 39;}
	else if(p == '&'){situ = 41;}
	else if(p == '*'){situ = 42;}
	else if(p == '?'){situ = 43;}
	else if(p == '!'){situ = 44;}
	else if(p == '@'){situ = 45;}
	else if(p == '#'){situ = 46;}
	else if(p == '$'){situ = 47;}
	else if(p == '^'){situ = 48;}
	else if(p == '+'){situ = 49;}
	else if(p == '|'){situ = 50;}
	else if(p == ':'){situ = 51;}
	else if(p == ';'){situ = 52;}
	else if(p == ','){situ = 53;}
	else{situ = 40;}
	mat.create(10,10);
	int i;
	for(i=0;i<100;i++){
		mat.push(tinyChar[situ][i] ? clr : color(0, 0, 0, 0));
	}
}
void KoishiExpand::KoishiMarkTool::StrMatLarge(str s, Koishi::image &mat, Koishi::color clr){
	char p;
	if(s.size() == 0){
		s = " ";
	}
	image subMat;
	mat.create(10,11*s.size()-1);
	mat.fill(0);
	for(int i = 0;i<s.size();i++){
		p = s[s.size()-i-1];
		CharMatLarge(p, subMat, clr);
		mat.putFore(subMat);
		if(i != s.size()-1){
			mat.moveHonz(11);
		}
		subMat.destory();
	}
}
bool KoishiExpand::KoishiMarkTool::ImageMarking(const image &sourceMatrix, image &destMatrix, str codeString, point deltaPoint, color textColor){
	image strMatrix;
	StrMatLarge(codeString, strMatrix, textColor);
	long topEx = 0;
	long leftEx = 0;
	long rightEx = 0;
	long bottomEx = 0;
	if(deltaPoint.Y < 0){
		topEx = -deltaPoint.Y;
	}
	if(deltaPoint.X < 0){
		leftEx = -deltaPoint.X;
	}
	if(deltaPoint.X + strMatrix.getWidth() > sourceMatrix.getWidth()){
		rightEx = deltaPoint.X + strMatrix.getWidth() - sourceMatrix.getWidth();
	}
	if(deltaPoint.Y + strMatrix.getHeight() > sourceMatrix.getHeight()){
		bottomEx = deltaPoint.Y + strMatrix.getHeight() - sourceMatrix.getHeight();
	}
	sourceMatrix.expand(destMatrix, topEx, bottomEx, leftEx, rightEx);
	strMatrix.expand(deltaPoint.Y > 0 ? deltaPoint.Y:0, 0, deltaPoint.X > 0 ? deltaPoint.X:0, 0); 
	destMatrix.putBack(strMatrix);
	return true;
}
bool KoishiExpand::KoishiMarkTool::ImagePSstyle(const image &sourceMatrix, image &destMatrix, color clrBound, color clrBG1, color clrBG2){
	long i, j;
	destMatrix.create(sourceMatrix.getHeight(), sourceMatrix.getWidth());
	for(i = 0;i<destMatrix.getWidth();i++){
		for(j = 0;j<destMatrix.getHeight();j++){
			destMatrix.setElem(j, i, (i%10<5&&j%10<5||i%10>=5&&j%10>=5)?clrBG1:clrBG2);
			if(i==0||j==0||i==destMatrix.getWidth()-1||j==destMatrix.getHeight()-1){
				destMatrix.setElem(j,i,clrBound);
			}
		}
	}
	destMatrix.putFore(sourceMatrix);
	return true;
}

/////////////////////////////////////////////////////////////
bool SPKobject::load(str fileName){
	int i,j;
	unsigned long dw;
	if(!data.loadFile(fileName)){
		return false;
	}
	data.readDWord(magic);
	if(magic != 0x1B111){
		data.release();
		return false;
	}
	for(i=0;i<260;i++){
		data.readByte(name[i]);
	}
	data.readDWord(reserve1);
	data.readDWord(decompressed_len);
	for(i=0;i<32;i++){
		data.readByte(hash[i]);
	}
	data.readDWord(maxBlockSize);
	data.readDWord(indexCount);
	listLen.clear();
	for(i=0;i<indexCount;i++){
		data.readDWord(dw);
		listLen.push_back(dw);
	}
	for(i=0;i<indexCount;i++){
		SPKblock sb;
		sb.startPos = data.getPosition();
		data.readDWord(sb.bzlib);
		data.readDWord(sb.len);
		data.readDWord(sb.bzlib_r);
		data.readDWord(sb.len_r);
		for(j=0;j<32;j++){
			data.readByte(sb.hash[j]);
		}
		sb.mainStartPos = data.getPosition();
		data.movePosition(sb.len);
		list.push_back(sb);
	}
	return true;
}

void SPKobject::release(){
	data.release();
}

void SPKobject::extract(int pos, stream &s){
	data.setPosition(list[pos].mainStartPos);
	data.readStream(s, list[pos].len);
}

void SPKobject::extractTrueStream(stream &s){
	s.allocate(decompressed_len*2);
	s.clear();
	stream s1,s2;
	for(int i = 0;i<indexCount;i++){
		extract(i, s1);
		if(list[i].bzlib){
			s1.BZuncompress(s2);
			s.pushStream(s2,s2.length);
		}else{
			s.pushStream(s1,s1.length);
		}
	}
}

void SPKobject::makeNPK(str NPKfileName){
	stream s;
	extractTrueStream(s);
	s.makeFile(NPKfileName);
}

LSTfile::LSTfile(){
	int i = 0;
	nameLen = 0;
	for(i=0;i<256;i++){
		name[i] = 0;
	}
	fileLen = 0;
	compLen = 0;
	hashLen = 0;
	for(i=0;i<32;i++){
		hash[i] = 0;
	}
}

LSTfolder::LSTfolder(){
	int i = 0;
	nameLen = 0;
	for(i=0;i<256;i++){
		name[i] = 0;
	}
	fileCount = 0;
	subFolderCount = 0;
	list.clear();
}
void LSTobject::load(Koishi::stream &s){
	int i,j;
	for(i=0;i<32;i++){
		s.readByte(hash[i]);
	}
	s.readDWord(magic);
	s.readDWord(reserve);
	s.readDWord(reserve2);
	list.clear();
	while(true){
		LSTfolder lf;
		if(!s.readDWord(lf.nameLen)){
			break;
		}
		for(i=0;i<lf.nameLen;i++){
			s.readByte(lf.name[i]);
		}
		s.readDWord(lf.fileCount);
		lf.list.clear();
		for(j=0;j<lf.fileCount;j++){
			LSTfile lfl;
			s.readDWord(lfl.nameLen);
			for(i=0;i<lfl.nameLen;i++){
				s.readByte(lfl.name[i]);
			}
			s.readDWord(lfl.compLen);
			s.readDWord(lfl.fileLen);
			s.readDWord(lfl.hashLen);
			for(i=0;i<lfl.hashLen;i++){
				s.readByte(lfl.hash[i]);
			}
			lf.list.push_back(lfl);
		}
		s.readDWord(lf.subFolderCount);
		list.push_back(lf);
	}
}
bool LSTobject::load(const str &fileName){
	int i,j;
	stream s;
	if(!s.loadFile(fileName))
		return false;
	for(i=0;i<32;i++){
		s.readByte(hash[i]);
	}
	s.readDWord(magic);
	if(magic != 0x54534C){
		return false;
	}
	s.readDWord(reserve);
	s.readDWord(reserve2);
	list.clear();
	while(true){
		LSTfolder lf;
		if(!s.readDWord(lf.nameLen)){
			break;
		}
		for(i=0;i<lf.nameLen;i++){
			s.readByte(lf.name[i]);
		}
		s.readDWord(lf.fileCount);
		lf.list.clear();
		for(j=0;j<lf.fileCount;j++){
			LSTfile lfl;
			s.readDWord(lfl.nameLen);
			for(i=0;i<lfl.nameLen;i++){
				s.readByte(lfl.name[i]);
			}
			s.readDWord(lfl.compLen);
			s.readDWord(lfl.fileLen);
			s.readDWord(lfl.hashLen);
			for(i=0;i<lfl.hashLen;i++){
				s.readByte(lfl.hash[i]);
			}
			lf.list.push_back(lfl);
		}
		s.readDWord(lf.subFolderCount);
		list.push_back(lf);
	}
	return true;
}

bool LSTobject::getImagePack2(LSTfolder &lf){
	int i;
	for(i=0;i<list.size();i++){
		str s1((char*)list[i].name);
		str s2 = "ImagePacks2";
		if(s1 == s2){
			lf = list[i];
			return true;
		}
	}
	return false;
}

bool LSTobject::getSoundPack(LSTfolder &lf){
	int i;
	for(i=0;i<list.size();i++){
		str s1((char*)list[i].name);
		str s2 = "SoundPacks";
		if(s1 == s2){
			lf = list[i];
			return true;
		}
	}
	return false;
}


bool TCTobject::load(Koishi::str fileName){
	int i;
	if(!data.loadFile(fileName)){
		return false;
	}
	data.readDWord(magic);
	if(magic != 0x04034b50){
		return false;
	}
	data.readWord(minVersion);
	data.readWord(GTBF);
	data.readWord(compMethod);
	data.readWord(lastTime);
	data.readWord(lastDate);
	data.readDWord(CRC32);
	data.readDWord(comSize);
	data.readDWord(uncomSize);
	data.readWord(nmSize);
	data.readWord(exSize);
	for(i=0;i<256;i++){
		 name[i] = 0;
		 if(i<nmSize){
			 data.readByte(name[i]);
		 }
	}
	for(i=0;i<256;i++){
		 ex[i] = 0;
		 if(i<exSize){
			 data.readByte(ex[i]);
		 }
	}
	dtStartPos = data.getPosition();
	return true;
}
bool TCTobject::release(){
	data.release();
	return true;
}
bool TCTobject::makeNPK(Koishi::str NPKfileName){
	stream s, s1, sHead,sOut;
	data.setPosition(dtStartPos);
	data.readStream(s, comSize);
	sHead.allocate(2);
	sHead.pushWord(0x9C78);
	s.insertStream(sHead, 2, 0);
	s.ZLIBuncompress(s1, uncomSize);
	s1.readStream(sOut, uncomSize);
	sOut.makeFile(NPKfileName);
	s.release();
	s1.release();
	sOut.release();
	sHead.release();
	return true;
}
LSTfileGF::LSTfileGF(){
	int i;
	for(i=0;i<256;i++){
		name[i] = 0;		
	}
	for(i=0;i<32;i++){
		lenStr[i] = 0;
		hash[i] = 0;	
	}
}
bool LSTobjectGF::load(const Koishi::str &fileName){
	int i,j;
	unsigned char n;
	stream s,sSplit;
	queueex pos, len;
	s.loadFile(fileName);
	sSplit.allocate(20);
	sSplit.pushString("ImagePacks2\\");
	s.splitStream(sSplit, pos, len);
	sSplit.release();
	list.clear();
	for(i=1;i<pos.size();i++){
		s.setPosition(pos[i]);
		LSTfileGF lf;
		j = 0;
		while(true){
			s.readByte(n);
			if(n == 0x22){
				break;
			}else{
				lf.name[j++] = n;
			}
		}
		s.readByte(n);
		j = 0;
		while(true){
			s.readByte(n);
			if(n == 0x20){
				break;
			}else{
				lf.hash[j++] = n;
			}
		}
		j = 0;
		while(true){
			s.readByte(n);
			if(n == 0x0D){
				break;
			}else{
				lf.lenStr[j++] = n;
			}
		}
		list.push_back(lf);
	}
	return true;
}
bool LSTobjectGF::load2(const Koishi::str &fileName){
	int i,j;
	unsigned char n;
	stream s,sSplit;
	queueex pos, len;
	s.loadFile(fileName);
	sSplit.allocate(20);
	sSplit.pushString("SoundPacks\\");
	s.splitStream(sSplit, pos, len);
	sSplit.release();
	list.clear();
	for(i=1;i<pos.size();i++){
		s.setPosition(pos[i]);
		LSTfileGF lf;
		j = 0;
		while(true){
			s.readByte(n);
			if(n == 0x22){
				break;
			}else{
				lf.name[j++] = n;
			}
		}
		s.readByte(n);
		j = 0;
		while(true){
			s.readByte(n);
			if(n == 0x20){
				break;
			}else{
				lf.hash[j++] = n;
			}
		}
		j = 0;
		while(true){
			s.readByte(n);
			if(n == 0x0D){
				break;
			}else{
				lf.lenStr[j++] = n;
			}
		}
		list.push_back(lf);
	}
	return true;
}
/////////////旧版本IMG///////////////////
bool KoishiExpand::IMGobjectV1::load(const Koishi::str &fileName){
	stream s;
	if(!s.loadFile(fileName))
		return false;
	return load(s);
}

bool KoishiExpand::IMGobjectV1::load(Koishi::stream &s){
	data = s;
	//开始读取
	int i;
	unsigned long dwTemp;
	unsigned long dwVersion;
	unsigned long dwIndexCount;
	s.resetPosition();
	if(s.readString(20) != "Neople Image File")
		return false;
	s.readDWord(dwTemp);	//保留位
	s.readDWord(dwVersion); //版本
	if(dwVersion != (unsigned long)V1){
		return false;
	}
	s.readDWord(dwIndexCount);	//INDEX数
	PICcontent.clear();
	posList.clear();

	for(i=0;i<dwIndexCount;i++){
		PICinfo pi;
		s.read(&pi.format, 4);
		s.read(&pi.comp, 4);
		s.readInt(pi.picSize.W);
		s.readInt(pi.picSize.H);
		s.readDWord(pi.dataSize);
		s.readInt(pi.basePt.X);
		pi.basePt.X = (long)dwTemp;
		s.readInt(pi.basePt.Y);
		pi.basePt.Y = (long)dwTemp;
		s.readInt(pi.frmSize.W);
		s.readInt(pi.frmSize.H);
		PICcontent.push_back(pi);
		posList.push_back(s.getPosition());
		lenList.push_back(pi.dataSize);
		s.movePosition(pi.dataSize);
	}
	return true;
}
bool KoishiExpand::IMGobjectV1::make(IMGobject &io){
	io.create(V2);
	stream s;
	int i;
	for(i=0;i<PICcontent.size();i++){
		data.setPosition(posList[i]);
		data.readStream(s, lenList[i]);
		io.PICpush(PICcontent[i], s);
		s.release();
	}
	return true;
}
bool KoishiExpand::IMGobjectV1::release(){
	data.release();
	posList.clear();
	lenList.clear();
	return true;
}

///////////全帧展示////////////////////////

KoishiExpand::exhibit::exhibit(){
	clear();
}
void KoishiExpand::exhibit::clear(){
	hMaxPerRow = 0;
	hList.clear();
	rList.clear();
	hList.push_back(0);
	queue zero;
	zero.push_back(0);
	rList.push_back(zero);
	canvas.destory();
}
void KoishiExpand::exhibit::create(int width, int height){
	canvas.create(height, width);
}
//全帧显示
//1.首先计算新放置缩略图的位置的顶部坐标和左边坐标
//2.根据左边坐标到画布右侧的距离与缩略图宽度做比较，如果不够放，则另起一行（转至3）；否则转至4。
//3.另起一行时，若上一行的最大高度超过了画布下册，则返回失败0；否则转至4。
//4.放置图像，坐标以及最大高度更新，返回成功1。

bool KoishiExpand::exhibit::putImage(const image &newMat, bool expanded){
	int currentRow = hList.size()-1;	//当前已经达成的行
	int top = hList[currentRow];		//顶部坐标
	int current = rList[currentRow].size()-1;	//当前行中已插入的个数
	int left = rList[currentRow][current];		//左边坐标

	bool needNewLine = false;
	if(newMat.getWidth() + left > canvas.getWidth()){
		needNewLine = true;
	}
	if(needNewLine){
		//计算上一栏的最低层
		currentRow ++;
		top += hMaxPerRow;
		current = 0;
		left = 0;
		if(top >= canvas.getHeight() && !expanded){
			return false;
		}
		hMaxPerRow = 0;
		queue zero;
		zero.push_back(0);
		rList.push_back(zero);
		hList.push_back(top);
	}
	image offset;
	newMat.expand(offset, top, 0, left, 0);
	if(expanded){
		if(canvas.getHeight()<offset.getHeight()){
			int hDelta = offset.getHeight() - canvas.getHeight();
			image tempCanvas(canvas);
			canvas.destory();
			tempCanvas.expand(canvas, 0, hDelta, 0, 0);
			tempCanvas.destory();
		}
	}
	canvas.putFore(offset);
	if(newMat.getHeight()>hMaxPerRow){
		hMaxPerRow = newMat.getHeight();
	}
	rList[currentRow].push_back(left + newMat.getWidth());
	return true;
}

/////////////////////////////////////////////////////
int KoishiExpand::authorLock::checkLock(str fileName, str password){
	stream s, sStr, sSHA1, sSHA2;
	sStr.allocate(password.size());
	sStr.pushString(password);
	sStr.SHA256code(sSHA1);
	//没能打开文件
	if(!s.loadFile(fileName))
		return 3;
	//长度不够，不可能含有锁
	if(s.length < 38)
		return 3;
	s.setPosition(s.length - 6);
	//未加锁
	if("XYZZY" != s.readString(6))
		return 2;
	//已经加锁
	s.setPosition(s.length - 38);
	s.readStream(sSHA2, 32);
	for(int i = 0;i<32;i++){
		if(sSHA1[i] != sSHA2[i])
			return 0;
	}	
	return 1;

}
bool KoishiExpand::authorLock::addLock(str fileName, str password){
	stream s, sStr, sSHA1;
	sStr.allocate(password.size());
	sStr.pushString(password);
	sStr.SHA256code(sSHA1);
	if(checkLock(fileName, password) < 2)
		return false;	//已经有锁所以不能加锁
	if(!s.loadFile(fileName))
		return false;	//无法读取文件
	s.pushStream(sSHA1, 32);
	s.pushString("XYZZY");
	s.pushByte(uchar(0));
	s.makeFile(fileName);
	return true;
}
//////////////////////////////////////////////////////////////////////////////
void KoishiExpand::textDisplay::binary(const stream &in, stream &out){
	out.release();
	out.allocate(in.length*10);
	for(longex i = 0;i<in.length;i++){
		if(i % 16 == 0){
			char s[10];
			itoa(i, s, 16);
			out.pushString(str(s));
			out.pushByte(' ');
		}
		uchar mask = 1;
		for(uchar j = 0;j<8;j++){
			if(in[i] & mask){
				out.pushByte((uchar)'1');
			}else{
				out.pushByte((uchar)'0');
			}
			mask <<= 1;
		}
		
		out.pushByte((uchar)' ');
		if(i % 16 == 15){
			out.pushByte((uchar)'\r');
			out.pushByte((uchar)'\n');
		}
	}
}
void KoishiExpand::textDisplay::binaryFile(const stream &in, str fileName){
	stream out;
	binary(in, out);
	out.makeFile(fileName);
}
void KoishiExpand::textDisplay::binaryCompareFile(const stream &in1, const stream &in2, str fileName){
	stream out;
	longex maxLen =MAX(in1.length, in2.length);
	out.allocate(maxLen*40);
	for(longex i = 0;i<maxLen;i+=16){
		//head:
		char s[10];
		itoa(i, s, 16);
		out.pushString(str(s));
		out.pushByte((uchar)':');
		out.pushByte((uchar)' ');
		for(uchar j = 0;j<16;j++){
			uchar mask = 1;
			for(uchar k = 0;k<8;k++){
				if(i+j>=in1.length){
					out.pushByte((uchar)' ');
				}else if(in1[i+j] & mask){
					out.pushByte((uchar)'1');
				}else{
					out.pushByte((uchar)'0');
				}
				mask <<= 1;
			}
			out.pushByte((uchar)' ');
		}
		out.pushByte((uchar)'\r');
		out.pushByte((uchar)'\n');
		out.pushString(str(s));
		out.pushByte((uchar)':');
		out.pushByte((uchar)' ');
		for(uchar j = 0;j<16;j++){
			uchar mask = 1;
			for(uchar k = 0;k<8;k++){
				if(i+j>=in2.length){
					out.pushByte((uchar)' ');
				}else if(in2[i+j] & mask){
					out.pushByte((uchar)'1');
				}else{
					out.pushByte((uchar)'0');
				}
				mask <<= 1;
			}
			out.pushByte((uchar)' ');
		}
		out.pushByte((uchar)'\r');
		out.pushByte((uchar)'\n');
		out.pushByte((uchar)'\r');
		out.pushByte((uchar)'\n');
	}
	out.makeFile(fileName);
}