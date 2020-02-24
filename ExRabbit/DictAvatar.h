#pragma once
#include "../KoishiEx/KoishiEx.h"

using namespace Koishi;
using namespace KoishiAvatar;
typedef struct DictAvatarTerm{
	long ID;
	bool isTN;
	long paletteID;
	long iconID;
	CString avatarName;
}DictAvatarTerm;

typedef struct DictAvatarSuitTerm{
	long ID[KoishiAvatar::APART_MAXCOUNT];
	CString suitName;
}DictAvatarSuitTerm;
typedef std::vector<DictAvatarTerm> DictAvatarContent;

class DictAvatar{
public:
	DictAvatar(void);
	~DictAvatar(void);
public:
	CString dictFileName;
	std::vector<std::vector<DictAvatarContent>> term;
	//DictAvatarContent term[ACAREER_MAXCOUNT][APART_MAXCOUNT];
public:
	void setFile(CString usingFileName);
	void loadDict();
	void saveDict();
	void insertTerm(avatarCareer ac, avatarPart ap, const DictAvatarTerm &newTerm);
	void deleteTerm(avatarCareer ac, avatarPart ap, int pos);
	void modifiedTerm(avatarCareer ac, avatarPart ap, int pos, const DictAvatarTerm &newTerm);
public:
	//≤È—Ø
	std::vector<long> findPos(avatarCareer ac, avatarPart ap, long iconID);
	std::vector<long> findPos(avatarCareer ac, avatarPart ap, long ID, bool isTN, long paletteID);
	std::vector<long> findPos(avatarCareer ac, avatarPart ap, CString avatarName);
	DictAvatarContent findTerm(avatarCareer ac, avatarPart ap, long iconID);
	DictAvatarContent findTerm(avatarCareer ac, avatarPart ap, long ID, bool isTN, long paletteID);
	DictAvatarContent findTerm(avatarCareer ac, avatarPart ap, CString avatarName);
};
