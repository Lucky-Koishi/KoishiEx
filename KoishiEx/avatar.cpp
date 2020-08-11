#include "StdAfx.h"
#include "KoishiEx.h"
#include "KoishiNeoplePack.h"
#include "avatar.h"

using namespace Koishi;
using namespace KoishiNeoplePack;
using namespace KoishiAvatar;

dword layerSequence[100][2] = {
	{APART_SHOES,	'f'},
	{APART_BELT,	'f'},
	{APART_PANTS,	'f'},
	{APART_COAT,	'f'},
	{APART_NECK,	'f'},
	{APART_FACE,	'f'},
	{APART_CAP,		'f'},
	{APART_BELT,	'e'},
	{APART_NECK,	'e'|'f'<<8},
	{APART_FACE,	'g'},
	{APART_FACE,	'a'},
	{APART_WEAPON,	'c'|'2'<<8},
	{APART_WEAPON,	'c'|'1'<<8},
	{APART_WEAPON,	'c'},
	{APART_CAP,		'c'},
	{APART_HAIR,	'c'},
	{APART_NECK,	'e'},
	{APART_COAT,	'c'}, 
	{APART_NECK,	'g'},
	{APART_NECK,	'c'|'f'<<8},
	{APART_NECK,	'c'},
	{APART_WEAPON,	'a'|'2'<<8},
	{APART_WEAPON,	'a'|'1'<<8},
	{APART_WEAPON,	'a'},
	{APART_CAP,		'g'},
	{APART_CAP,		'a'},
	{APART_HAIR,	'a'},
	{APART_WEAPON,	'e'|'2'<<8},
	{APART_WEAPON,	'e'|'1'<<8},
	{APART_WEAPON,	'e'},
	{APART_NECK,	'x'|'f'<<8},
	{APART_NECK,	'x'},
	{APART_NECK,	'z'},
	{APART_COAT,	'x'},
	{APART_BELT,	'g'},
	{APART_BELT,	'c'},
	{APART_FACE,	'c'},
	{APART_NECK,	'a'},
	{APART_COAT,	'g'},
	{APART_COAT,	'a'},
	{APART_BELT,	'a'},
	{APART_PANTS,	'c'},
	{APART_SHOES,	'c'},
	{APART_PANTS,	'g'},
	{APART_PANTS,	'a'},
	{APART_SHOES,	'g'},
	{APART_SHOES,	'a'},
	{APART_WEAPON,	'x'|'2'<<8},
	{APART_WEAPON,	'x'|'1'<<8},
	{APART_WEAPON,	'x'},
	{APART_PANTS,	'b'},
	{APART_SHOES,	'h'},
	{APART_SHOES,	'b'},
	{APART_PANTS,	'h'},
	{APART_PANTS,	'd'},
	{APART_BELT,	'b'},
	{APART_NECK,	'b'|'f'<<8},
	{APART_NECK,	'b'},
	{APART_COAT,	'h'},
	{APART_COAT,	'b'},
	{APART_BELT,	'h'},
	{APART_BELT,	'd'},
	{APART_HAIR,	'b'},
	{APART_CAP,		'h'},
	{APART_CAP,		'b'},
	{APART_WEAPON,	'b'|'2'<<8},
	{APART_WEAPON,	'b'|'1'<<8},
	{APART_WEAPON,	'b'},
	{APART_NECK,	'd'|'f'<<8},
	{APART_NECK,	'd'},
	{APART_NECK,	'h'},
	{APART_COAT,	'd'},
	{APART_HAIR,	'd'},
	{APART_CAP,		'd'},
	{APART_NECK,	'k'|'f'<<8},
	{APART_NECK,	'k'},
	{APART_FACE,	'h'},
	{APART_WEAPON,	'd'|'2'<<8},
	{APART_WEAPON,	'd'|'1'<<8},
	{APART_WEAPON,	'd'},
	{APART_FACE,	'b'},
	{APART_HAIR,	'f'|'1'<<8},
	{APART_BODY,	0}
};
color modelColor[ACHARACTER_MAXCOUNT] = {
	color(0xFF, 0x00, 0xCC, 0xFF),
	color(0xFF, 0xCC, 0x55, 0x88),
	color(0xFF, 0xFF, 0x99, 0x66),
	color(0xFF, 0xFF, 0xEE, 0x99),
	color(0xFF, 0xCC, 0x99, 0xEE),
	color(0xFF, 0x99, 0xFF, 0xFF),
	color(0xFF, 0xFF, 0xCC, 0xFF),
	color(0xFF, 0xCC, 0xCC, 0xFF),
	color(0xFF, 0xCC, 0xCC, 0xCC),
	color(0xFF, 0xFF, 0xFF, 0xCC),
	color(0xFF, 0xDD, 0x99, 0xEE),
	color(0xFF, 0x99, 0xFF, 0x66),
	color(0xFF, 0x77, 0x77, 0xFF),
	color(0xFF, 0xDD, 0xCC, 0x88)
};
long modelFrame[ACHARACTER_MAXCOUNT] = {
	176, 0, 113, 0, 0, 0, 12, 0, 150, 0, 0, 0, 0, 0
};

str avatarString[APART_MAXCOUNT] = {
	"cap","hair","face","neck","coat","pants","belt","shoes","body"
};
str weaponString[AWEAPON_MAXCOUNT] = {
	"lgswd","lswd","mswd","sswd","boneswd","gemswd","beamswd","club","katana","lkatana","lblade","sblade","coreswd",
	"arm","tonfa","gauntlet","boneclaw","claw","boxglove","glove","knuckle",
	"auto","bowgun","hcan","musket","rev",
	"pole", "rod", "spear", "staff", "broom", "dagger", "twinswd", "wand", "chakraweapon", "halberd", "pike", "javelin", "beamspear",
	"khakkhara", "rosary", "scythe", "totem", "axe", "cross"
};
WeaponType characterWeaponTable[ACHARACTER_MAXCOUNT][WEAPON_MAXCOUNT_PER_CHAR] = {
	{AWEAPON_LSWD, AWEAPON_MSWD, AWEAPON_SSWD, AWEAPON_LGSWD, AWEAPON_BONESWD, AWEAPON_GEMSWD, AWEAPON_KATANA, AWEAPON_LKATANA, AWEAPON_CLUB, AWEAPON_BEAMSWD, AWEAPON_UD},
	{AWEAPON_LSWD, AWEAPON_MSWD, AWEAPON_SSWD, AWEAPON_LGSWD, AWEAPON_BONESWD, AWEAPON_GEMSWD, AWEAPON_KATANA, AWEAPON_LKATANA, AWEAPON_CLUB, AWEAPON_BEAMSWD, AWEAPON_UD},
	{AWEAPON_GAUNTLET, AWEAPON_ARM, AWEAPON_GLOVE, AWEAPON_KNUCKLE, AWEAPON_BOXGLOVE, AWEAPON_CLAW, AWEAPON_BONECLAW, AWEAPON_TONFA, AWEAPON_UD},
	{AWEAPON_GAUNTLET, AWEAPON_ARM, AWEAPON_GLOVE, AWEAPON_KNUCKLE, AWEAPON_BOXGLOVE, AWEAPON_CLAW, AWEAPON_BONECLAW, AWEAPON_TONFA, AWEAPON_UD},
	{AWEAPON_AUTO, AWEAPON_REV, AWEAPON_MUSKET, AWEAPON_BOWGUN, AWEAPON_HCAN,AWEAPON_UD},
	{AWEAPON_AUTO, AWEAPON_REV, AWEAPON_MUSKET, AWEAPON_BOWGUN, AWEAPON_HCAN,AWEAPON_UD},
	{AWEAPON_ROD, AWEAPON_STAFF, AWEAPON_POLE, AWEAPON_SPEAR, AWEAPON_BROOM, AWEAPON_UD},
	{AWEAPON_ROD, AWEAPON_STAFF, AWEAPON_POLE, AWEAPON_SPEAR, AWEAPON_BROOM, AWEAPON_UD},
	{AWEAPON_CROSS, AWEAPON_AXE, AWEAPON_SCYTHE, AWEAPON_TOTEM, AWEAPON_ROSARY, AWEAPON_UD},
	{AWEAPON_CROSS, AWEAPON_AXE, AWEAPON_SCYTHE, AWEAPON_TOTEM, AWEAPON_ROSARY, AWEAPON_KHAKKHARA, AWEAPON_UD},
	{AWEAPON_DAGGER, AWEAPON_TWINSWD, AWEAPON_WAND, AWEAPON_CHAKRAWEAPON, AWEAPON_UD},
	{AWEAPON_LSWD, AWEAPON_MSWD, AWEAPON_SSWD, AWEAPON_LGSWD, AWEAPON_BONESWD, AWEAPON_GEMSWD, AWEAPON_KATANA, AWEAPON_LKATANA, AWEAPON_CLUB, AWEAPON_UD},
	{AWEAPON_PIKE, AWEAPON_HALBERD, AWEAPON_JAVELIN, AWEAPON_BEAMSPEAR, AWEAPON_UD},
	{AWEAPON_MSWD, AWEAPON_SBLADE, AWEAPON_LBLADE, AWEAPON_CORESWD, AWEAPON_UD}
};
WeaponSet characterWeaponList(const AvatarCharacter &character){
	WeaponSet result;
	for(int i = 0;i<WEAPON_MAXCOUNT_PER_CHAR;i++){
		if(characterWeaponTable[character][i] == AWEAPON_UD)
			return result;
		result.push_back(characterWeaponTable[character][i]);
	}
	return result;
}
long characterWeaponListID(const AvatarCharacter &character, const WeaponType &type){
	WeaponSet list = characterWeaponList(character);
	for(int i = 0;i<list.size();i++){
		if(list[i] == type)
			return i;
	}
	return -1;
}
///////////////////////////////////////////////////////////////////////
str formatID(int i){
	if(i == 0){
		return "0";
	}
	str result = "";
	bool p = i < 0;
	if(p)
		i = -i;
	while(i){
		char d = '0' + i % 10;
		result = d + result;
		i /= 10;
	}
	if(p)
		result = '-' + result;
	return result;
}
str KoishiAvatar::formatAvatarID(int i){
	str result = "";
	if(i > 9999){
		result.push_back('0' + i /10000);
	}
	result.push_back('0' + (i /1000)%10);
	result.push_back('0' + (i /100)%10);
	result.push_back('0' + (i /10)%10);
	result.push_back('0' + i %10);
	return result;
}
str KoishiAvatar::formatAvatarIDplusBy(const str &imgName, int num){
	str result = imgName;
	long i1 = num % 10;	//个位数
	long i2 = num / 10 % 10;	//十位数
	Koishi::uchar c1 = '0'+i1;
	Koishi::uchar c2 = '0'+i2;
	str::size_type pos = imgName.find_last_of('0');
	if(pos != str::npos){
		result[pos] = c1;
		result[pos-1] = c2;
	}
	return result;
}
str KoishiAvatar::NPK_avatar(AvatarCharacter ac, AvatarPart ap){
	str fix1 = "sprite_character_";
	str fix2 = "equipment_avatar_";
	str fix3 = ".NPK";
	str fixn1[ACHARACTER_MAXCOUNT] = {"swordman_","swordman_at","fighter_","fighter_at","gunner_","gunner_at","mage_","mage_at","priest_","priest_at","thief_","knight_","demoniclancer_","gunblader_"};
	str fixn2[APART_MAXCOUNT] = {"cap","hair","face","neck","coat","pants","belt","shoes","skin"};
	if(ap < APART_MAXCOUNT){
		if(ac < ACHARACTER_MAXCOUNT)
			return (fix1 + fixn1[ac] + fix2 + fixn2[ap] + fix3);
	}
	return "unexceptable";
}

str KoishiAvatar::IMG_avatar(AvatarCharacter ac, AvatarPart ap){
	str fixn1[ACHARACTER_MAXCOUNT] = {"sm_","sg_","ft_","fm_","gn_","gg_","mg_","mm_","pr_","pg_","th_","kn_","dl_","gb_"};
	str fixn2[APART_MAXCOUNT] = {"cap","hair","face","neck","coat","pants","belt","shoes","body"};
	if(ap < APART_MAXCOUNT){
		if(ac < ACHARACTER_MAXCOUNT)
			return (fixn1[ac] + fixn2[ap]);
	}
	return "unexceptable";
}
str KoishiAvatar::NPK_weapon(AvatarCharacter ac, WeaponType wt){
	str fix1 = "sprite_character_";
	str fix2 = "equipment_weapon_";
	str fix3 = ".NPK";
	str fixn1[ACHARACTER_MAXCOUNT] = {"swordman_","swordman_at","fighter_","fighter_at","gunner_","gunner_at","mage_","mage_at","priest_","priest_at","thief_","knight_","demoniclancer_","gunblader_"};
	str fixn2[AWEAPON_MAXCOUNT] = {"lgswd","lswd","mswd","sswd","boneswd","gemswd","beamswd","club","katana","lkatana","lblade","sblade","coreswd",
		"arm","tonfa","gauntlet","boneclaw","claw","boxglove","glove","knuckle",
		"auto","bowgun","hcan","musket","rev",
		"pole", "rod", "spear", "staff", "broom", "dagger", "twinswd", "wand", "chakraweapon", "halberd", "pike", "javelin", "beamspear",
		"khakkhara", "rosary", "scythe", "totem", "axe", "cross"
	};
	if(wt < AWEAPON_MAXCOUNT){
		if(ac < ACHARACTER_MAXCOUNT)
			return (fix1 + fixn1[ac] + fix2 + fixn2[wt] + fix3);
	}
	return "unexceptable";
}
str KoishiAvatar::NPK_avatarIcon(AvatarCharacter ac){
	str fix1 = "sprite_item_avatar_";
	str fix2 = ".NPK";
	str fixn1[ACHARACTER_MAXCOUNT] = {"swordman","atswordman","fighter","atfighter","gunner","atgunner","mage","atmage","priest","atpriest","thief","knight","demoniclancer","gunblader"};
	if(ac < ACHARACTER_MAXCOUNT)
		return (fix1 + fixn1[ac] + fix2 );
	return "unexceptable";
}
str KoishiAvatar::IMG_avatarIcon(AvatarCharacter ac, AvatarPart ap){
	str fix1 = "_a";
	str fix2 = ".img";
	str fixn1[ACHARACTER_MAXCOUNT] = {"sm","sg","ft","fm","gn","gg","mg","mm","pr","pg","th","kn","dl","gb"};
	str fixn2[APART_MAXCOUNT] = {"cap","hair","face","neck","coat","pants","belt","shoes","body"};
	if(ap < APART_MAXCOUNT){
		if(ac < ACHARACTER_MAXCOUNT){
			return fixn1[ac] + fix1 + fixn2[ap] + fix2;
		}
	}
	return "unexceptable";
}
str KoishiAvatar::IMG_avatarIcon(AvatarCharacter ac, str s){
	str fix1 = "_a";
	str fix2 = ".img";
	str fixn1[ACHARACTER_MAXCOUNT] = {"sm","sg","ft","fm","gn","gg","mg","mm","pr","pg","th","kn","dl","gb"};
	if(ac < ACHARACTER_MAXCOUNT){
		return fixn1[ac] + fix1 + s + fix2;
	}
	return "unexceptable";
}
std::vector<str> KoishiAvatar::NPK_weaponIcon(AvatarCharacter ac){
	str fix1 = "sprite_item_new_equipment_01_weapon_";
	str fix2 = "_";
	str fix3 = ".NPK";
	str fixn1[ACHARACTER_MAXCOUNT] = {"swordman","swordman","fighter","fighter","gunner","gunner","mage","mage","priest","priest","thief","swordman","demoniclancer","gunblader"};
	std::vector<str> fileList;
	switch(ac){
	case ACHARACTER_SM:
	case ACHARACTER_SG:
	case ACHARACTER_KN:
		fileList.push_back(fix1 + "swordman" + fix2 + "lswd" + fix3);
		fileList.push_back(fix1 + "swordman" + fix2 + "sswd" + fix3);
		fileList.push_back(fix1 + "swordman" + fix2 + "club" + fix3);
		fileList.push_back(fix1 + "swordman" + fix2 + "katana" + fix3);	
		fileList.push_back(fix1 + "swordman" + fix2 + "beamswd" + fix3);
		break;
	case ACHARACTER_FT:
	case ACHARACTER_FM:
		fileList.push_back(fix1 + "fighter" + fix2 + "bglove" + fix3);
		fileList.push_back(fix1 + "fighter" + fix2 + "claw" + fix3);
		fileList.push_back(fix1 + "fighter" + fix2 + "gauntlet" + fix3);
		fileList.push_back(fix1 + "fighter" + fix2 + "knuckle" + fix3);
		fileList.push_back(fix1 + "fighter" + fix2 + "tonfa" + fix3);
		break;
	case ACHARACTER_GN:
	case ACHARACTER_GG:
		fileList.push_back(fix1 + "gunner" + fix2 + "automatic" + fix3);
		fileList.push_back(fix1 + "gunner" + fix2 + "bowgun" + fix3);
		fileList.push_back(fix1 + "gunner" + fix2 + "hcannon" + fix3);
		fileList.push_back(fix1 + "gunner" + fix2 + "musket" + fix3);
		fileList.push_back(fix1 + "gunner" + fix2 + "revolver" + fix3);
		break;
	case ACHARACTER_MG:
	case ACHARACTER_MM:
		fileList.push_back(fix1 + "mage" + fix2 + "broom" + fix3);
		fileList.push_back(fix1 + "mage" + fix2 + "pole" + fix3);
		fileList.push_back(fix1 + "mage" + fix2 + "rod" + fix3);
		fileList.push_back(fix1 + "mage" + fix2 + "spear" + fix3);
		fileList.push_back(fix1 + "mage" + fix2 + "staff" + fix3);
		break;

	case ACHARACTER_PR:
	case ACHARACTER_PG:
		fileList.push_back(fix1 + "priest" + fix2 + "axe" + fix3);
		fileList.push_back(fix1 + "priest" + fix2 + "cross" + fix3);
		fileList.push_back(fix1 + "priest" + fix2 + "rosary" + fix3);
		fileList.push_back(fix1 + "priest" + fix2 + "scythe" + fix3);
		fileList.push_back(fix1 + "priest" + fix2 + "totem" + fix3);
		break;	
	case ACHARACTER_TH:
		fileList.push_back(fix1 + "thief" + fix2 + "chakraweapon" + fix3);
		fileList.push_back(fix1 + "thief" + fix2 + "dagger" + fix3);
		fileList.push_back(fix1 + "thief" + fix2 + "twinswd" + fix3);
		fileList.push_back(fix1 + "thief" + fix2 + "wand" + fix3);
		break;
	case ACHARACTER_DL:
		fileList.push_back(fix1 + "demoniclancer" + fix2 + "beamspear" + fix3);
		fileList.push_back(fix1 + "demoniclancer" + fix2 + "halberd" + fix3);
		fileList.push_back(fix1 + "demoniclancer" + fix2 + "javelin" + fix3);
		fileList.push_back(fix1 + "demoniclancer" + fix2 + "pike" + fix3);
		break;
	case ACHARACTER_GB:
		fileList.push_back(fix1 + "gunblader" + fix2 + "coreswd" + fix3);
		fileList.push_back(fix1 + "gunblader" + fix2 + "sblade" + fix3);
		fileList.push_back(fix1 + "gunblader" + fix2 + "lblade" + fix3);
		fileList.push_back(fix1 + "gunblader" + fix2 + "mswd" + fix3);
		break;
	}
	return fileList;
}
bool AvatarLayer::isGlowing() const{
	return layer[0] == 'f' || layer[1] == 'f' || layer[2] == 'f' || layer[3] == 'f';
}
AvatarAlbum::AvatarAlbum(){
	character = ACHARACTER_UD;
	part = APART_UD;
	currentSelect = -1;
	currentFrame = 0;
	TNenabled = false;
	layerList.reserve(16);		//当前选择装扮各图层（存储在NPK内部的位置和调色板）
	layerIMGlist.reserve(16);;	//当前选择装扮各图层的IMG
	layerNameList.reserve(16);;			//当前选择装扮各图层的路径名
	layerImageList.reserve(16);;		//当前选择装扮各图层的贴图数据
	layerBasePointList.reserve(16);;	//当前选择装扮各图层的贴图基准点坐标
	locked = 0;
}
bool AvatarAlbum::loadNPK(const str& NPKfileName){
	if(!source.loadFile(NPKfileName))
		return AERROR_NO_SUCH_FILE;
	//开始解析IMG路径名
	int IMGindex = 0;
	content.clear();
	for(IMGindex = 0; IMGindex < source.count; IMGindex++){
		IMGversion IMGver = (IMGversion)source.IMGgetVersion(IMGindex);
		if(IMGver <= 0 || IMGver > V6)
			continue;
		str IMGpath = source.entry[IMGindex].comment;
		str::size_type st = IMGpath.find_last_of('/');
		str IMGname = (st == str::npos) ? IMGpath:IMGpath.substr(st+1);
		if(IMGname.size() < 6)
			continue;
		if(IMGname.find("awake") != str::npos)
			continue;
		if(IMGname.find("mask") != str::npos)
			continue;
		if(IMGname.find(".img") == str::npos)
			continue;
		//名称解析
		long ID = 0;
		bool isTN = false;
		bool isFlow = false;
		str mainStr;
		str IDstr;
		str layStr;
		str::size_type is = 0;
		if(IMGname.substr(0, 4) == "(tn)"){
			isTN = true;
			is += 4;
		}
		while(is < IMGname.size() && (IMGname[is] < '0' || IMGname[is] > '9')){
			mainStr.push_back(IMGname[is]);
			is ++;
		}
		while(is < IMGname.size() && IMGname[is] >= '0' && IMGname[is] <= '9'){
			IDstr.push_back(IMGname[is]);
			is ++;
		}
		while(is < IMGname.size() && IMGname[is] != '.'){
			layStr.push_back(IMGname[is]);
			is ++;
		}
		//主域解析
		//blablabla..记得写武器解析.
		if(IDstr.size() < 4)
			continue;
		//还要通过mainStr过滤掉本不属于该NPK的部件
		///if(mainStr != IMG_avatar(character, part)[0]);
		//	continue;
		//图层信息不可能使用超过4个字符表示，mask除外
		if(layStr.size() > 4)
			continue;
		//ID解析//图层解析
		int paletteCount = source.IMGgetPaletteCount(IMGindex);
		if(IMGver != V6)
			paletteCount = 1;
		long IDbase = std::stoi(IDstr);
		for(int palette = 0;palette < paletteCount;palette++){
			ID = IDbase + palette;
			int searchID = 0;
			bool IDexist = false;
			for(; searchID < content.size(); searchID ++){
				if(content[searchID].ID == ID){
					IDexist = true;
					break;
				}else if(content[searchID].ID > ID){
					break;
				}
			}
			AvatarLayer newLayer;
			newLayer.paletteID = IMGver == V6 ? palette :-1;
			newLayer.posInNPK = IMGindex;
			memset(newLayer.layer, 0, sizeof(AvatarLayerFlag));
			memcpy(newLayer.layer, layStr.data(), layStr.size());
			if(IDexist){
				if(isTN){
					content[searchID].infoTN.push_back(newLayer);
					content[searchID].layerCountTN ++;
				}else{
					content[searchID].info.push_back(newLayer);
					content[searchID].layerCount ++;
				}
			}else{
				Avatar newAvatar;
				newAvatar.ID = ID;
				newAvatar.layerCount = 0;
				newAvatar.layerCountTN = 0;
				if(isTN){
					newAvatar.infoTN.push_back(newLayer);
					newAvatar.layerCountTN ++;
				}else{
					newAvatar.info.push_back(newLayer);
					newAvatar.layerCount ++;
				}
				content.insert(content.begin()+searchID, newAvatar);
			}
		}
	}
	return true;
}

bool AvatarAlbum::changeAvatar(const long &index){
	if(index < 0){
		currentSelect = -1;
		layerList.clear();
		return true;
	}
	if(index >= content.size())
		return false;
	currentSelect = index;
	layerList = (TNenabled && content[index].layerCountTN > 0) ? content[index].infoTN : content[index].info;
	updateIMG();
	return true;
}
long AvatarAlbum::findAvatarID(const long &newID){
	if(newID < 0){
		return -1;
	}
	long index = -1;
	for(int i = 0;i<content.size();i++){
		if(content[i].ID == newID){
			return i;
		}
	}
	return -1;
}
bool AvatarAlbum::changeAvatarByID(const long &newID){
	if(newID < 0){
		currentSelect = -1;
		layerList.clear();
		return true;
	}
	long index = -1;
	for(int i = 0;i<content.size();i++){
		if(content[i].ID == newID){
			index = i;
			break;
		}
	}
	if(index >= 0){
		changeAvatar(index);
		return true;
	}
	return false;
}

bool AvatarAlbum::changeTN(bool TN){
	TNenabled = TN;
	if(currentSelect >= 0 && currentSelect<content.size()){
		layerList = (TNenabled && content[currentSelect].layerCountTN > 0) ? content[currentSelect].infoTN : content[currentSelect].info;
		updateIMG();
	}
	return true;
}

bool AvatarAlbum::changeFrame(const long &newFrame){
	currentFrame = newFrame;
	return true;
}

bool AvatarAlbum::updateIMG(){
	layerIMGlist.clear();
	layerNameList.clear();
	for(int i = 0;i<layerList.size();i++){
		IMGobject io;
		source.IMGextract(layerList[i].posInNPK, io);
		layerIMGlist.push_back(io);
		layerNameList.push_back(source.entry[layerList[i].posInNPK].comment);
	}
	return true;
}

bool AvatarAlbum::updateImage(){
	while(locked == 1);
	locked = 1;
	layerImageList.clear();
	layerBasePointList.clear();
	for(int i = 0;i<layerList.size();i++){
		image im;
		PICinfo pi;
		if(currentFrame >= 0 && currentFrame < layerIMGlist[i].indexCount){
			layerIMGlist[i].PICextract(currentFrame, im, layerList[i].paletteID);
			layerIMGlist[i].PICgetInfo(layerIMGlist[i].linkFind(currentFrame), pi);
			if(layerList[i].isGlowing())
				im.loseBlack(3);
		}else{
			im.create(1,1);
			pi.basePt = point(0,0);
		}
		if(im.getElemCount() == 0){
			im.create(1,1);
			pi.basePt = point(0,0);
		}
		layerBasePointList.push_back(pi.basePt);
		layerImageList.push_back(im);
	}
	locked = 0;
	return true;
}
WeaponAlbum::WeaponAlbum(){
	//character = ACHARACTER_UD;
	type = AWEAPON_UD;
	currentSelect = -1;
	currentFrame = 0;
	TNenabled = false;
	layerList.reserve(16);		//当前选择装扮各图层（存储在NPK内部的位置和调色板）
	layerIMGlist.reserve(16);;	//当前选择装扮各图层的IMG
	layerNameList.reserve(16);;			//当前选择装扮各图层的路径名
	layerImageList.reserve(16);;		//当前选择装扮各图层的贴图数据
	layerBasePointList.reserve(16);;	//当前选择装扮各图层的贴图基准点坐标
	locked = 0;
}
bool WeaponAlbum::loadNPK(const str& NPKfileName){
	if(!source.loadFile(NPKfileName))
		return AERROR_NO_SUCH_FILE;
	//开始解析IMG路径名
	int IMGindex = 0;
	content.clear();
	for(IMGindex = 0; IMGindex < source.count; IMGindex++){
		IMGversion IMGver = (IMGversion)source.IMGgetVersion(IMGindex);
		if(IMGver <= 0 || IMGver > V6)
			continue;
		str IMGpath = source.entry[IMGindex].comment;
		str::size_type st = IMGpath.find_last_of('/');
		str IMGname = (st == str::npos) ? IMGpath:IMGpath.substr(st+1);
		if(IMGname.size() < 6)
			continue;
		if(IMGname.find("mask") != str::npos)
			continue;
		if(IMGname.find("awake") != str::npos)
			continue;
		if(IMGname.find(".img") == str::npos)
			continue;
		//名称解析
		long ID = 0;
		bool isTN = false;
		bool isFlow = false;
		str mainStr;
		str IDstr;
		str layStr;
		str::size_type is = 0;
		if(IMGname.substr(0, 4) == "(tn)"){
			isTN = true;
			is += 4;
		}
		while(is < IMGname.size() && (IMGname[is] < '0' || IMGname[is] > '9')){
			mainStr.push_back(IMGname[is]);
			is ++;
		}
		while(is < IMGname.size() && IMGname[is] >= '0' && IMGname[is] <= '9'){
			IDstr.push_back(IMGname[is]);
			is ++;
		}
		while(is < IMGname.size() && IMGname[is] != '.'){
			layStr.push_back(IMGname[is]);
			is ++;
		}
		//主域解析
		//blablabla..记得写武器解析.
		if(IDstr.size() < 4)
			continue;
		//还要通过mainStr过滤掉本不属于该NPK的部件
		///if(mainStr != IMG_avatar(character, part)[0]);
		//	continue;
		//图层信息不可能使用超过4个字符表示，mask除外
		if(layStr.size() > 4)
			continue;
		//ID解析//图层解析
		int paletteCount = source.IMGgetPaletteCount(IMGindex);
		if(IMGver != V6)
			paletteCount = 1;
		long IDbase = std::stoi(IDstr);
		for(int palette = 0;palette < paletteCount;palette++){
			ID = IDbase + palette;
			int searchID = 0;
			bool IDexist = false;
			for(; searchID < content.size(); searchID ++){
				if(content[searchID].ID == ID){
					IDexist = true;
					break;
				}else if(content[searchID].ID > ID){
					break;
				}
			}
			AvatarLayer newLayer;
			newLayer.paletteID = IMGver == V6 ? palette :-1;
			newLayer.posInNPK = IMGindex;
			memset(newLayer.layer, 0, sizeof(AvatarLayerFlag));
			memcpy(newLayer.layer, layStr.data(), layStr.size());
			if(IDexist){
				if(isTN){
					content[searchID].infoTN.push_back(newLayer);
					content[searchID].layerCountTN ++;
				}else{
					content[searchID].info.push_back(newLayer);
					content[searchID].layerCount ++;
				}
			}else{
				Avatar newAvatar;
				newAvatar.ID = ID;
				newAvatar.layerCount = 0;
				newAvatar.layerCountTN = 0;
				if(isTN){
					newAvatar.infoTN.push_back(newLayer);
					newAvatar.layerCountTN ++;
				}else{
					newAvatar.info.push_back(newLayer);
					newAvatar.layerCount ++;
				}
				content.insert(content.begin()+searchID, newAvatar);
			}
		}
	}
	return true;
}

bool WeaponAlbum::changeWeapon(const long &index){
	if(index < 0){
		currentSelect = -1;
		layerList.clear();
		return true;
	}
	if(index >= content.size())
		return false;
	currentSelect = index;
	layerList = (TNenabled && content[index].layerCountTN > 0) ? content[index].infoTN : content[index].info;
	updateIMG();
	return true;
}
long WeaponAlbum::findWeaponID(const long &newID){
	if(newID < 0){
		return -1;
	}
	long index = -1;
	for(int i = 0;i<content.size();i++){
		if(content[i].ID == newID){
			return i;
		}
	}
	return -1;
}
bool WeaponAlbum::changeWeaponByID(const long &newID){
	if(newID < 0){
		currentSelect = -1;
		layerList.clear();
		return true;
	}
	long index = -1;
	for(int i = 0;i<content.size();i++){
		if(content[i].ID == newID){
			index = i;
			break;
		}
	}
	if(index >= 0){
		changeWeapon(index);
		return true;
	}
	return false;
}

bool WeaponAlbum::changeTN(bool TN){
	if(currentSelect == -1)
		return false;
	TNenabled = TN;
	layerList = (TNenabled && content[currentSelect].layerCountTN > 0) ? content[currentSelect].infoTN : content[currentSelect].info;
	updateIMG();
	return true;
}

bool WeaponAlbum::changeFrame(const long &newFrame){
	currentFrame = newFrame;
	return true;
}

bool WeaponAlbum::updateIMG(){
	layerIMGlist.clear();
	layerNameList.clear();
	for(int i = 0;i<layerList.size();i++){
		IMGobject io;
		source.IMGextract(layerList[i].posInNPK, io);
		layerIMGlist.push_back(io);
		layerNameList.push_back(source.entry[layerList[i].posInNPK].comment);
	}
	return true;
}

bool WeaponAlbum::updateImage(){
	while(locked == 1);
	locked = 1;
	layerImageList.clear();
	layerBasePointList.clear();
	for(int i = 0;i<layerList.size();i++){
		image im;
		PICinfo pi;
		if(currentFrame >= 0 && currentFrame < layerIMGlist[i].indexCount){
			layerIMGlist[i].PICextract(currentFrame, im, layerList[i].paletteID);
			layerIMGlist[i].PICgetInfo(layerIMGlist[i].linkFind(currentFrame), pi);
			if(layerList[i].isGlowing())
				im.loseBlack(3);
		}
		if(im.getElemCount() == 0)
			im.create(1,1);
		layerBasePointList.push_back(pi.basePt);
		layerImageList.push_back(im);
	}
	locked = 0;
	return true;
}
AvatarFactory::AvatarFactory(){
	album.clear();
	weapon.clear();
	weaponAlbum.clear();
	currentWeapon = -1;
	character = ACHARACTER_UD;

	locked = false;
}
void AvatarFactory::initial(const AvatarCharacter &newCharacter, const str &newPath){
	character = newCharacter;
	resourcePath = newPath;
	album.clear();
	for(int i = 0;i<APART_MAXCOUNT;i++)
		album.push_back(AvatarAlbum());
	weapon.clear();
	weapon = characterWeaponList(character);
	weaponAlbum.clear();
	for(int i = 0;i<weapon.size();i++)
		weaponAlbum.push_back(WeaponAlbum());
}
void AvatarFactory::loadAvatar(const AvatarPart &part){
	album[part].character = character;
	album[part].part = part;
	album[part].loadNPK(resourcePath + NPK_avatar(character, part));
	album[part].changeAvatar(0);
	album[part].changeFrame(modelFrame[character]);
}
void AvatarFactory::changeAvatar(const AvatarPart &part, const long &index){
	album[part].changeAvatar(index);
}
void AvatarFactory::changeAvatarByID(const AvatarPart &part, const long &newID){
	album[part].changeAvatarByID(newID);
}
void AvatarFactory::updateAvatarIMG(const AvatarPart &part){
	album[part].updateIMG();
}
void AvatarFactory::updateAvatarImage(const AvatarPart &part){
	album[part].updateImage();
}
void AvatarFactory::updateAvatarIMG(){
	for(int p = 0;p<APART_MAXCOUNT;p++){
		album[p].updateIMG();
	}
}
void AvatarFactory::updateAvatarImage(){
	for(int p = 0;p<APART_MAXCOUNT;p++){
		album[p].updateImage();
	}
}
void AvatarFactory::releaseAvatar(const AvatarPart &part){
	album[part].source.release();
}
void AvatarFactory::loadWeapon(const int &weaponSetID){
	weaponAlbum[weaponSetID].type = weapon[weaponSetID];
	weaponAlbum[weaponSetID].loadNPK(resourcePath + NPK_weapon(character, weapon[weaponSetID]));
	weaponAlbum[weaponSetID].changeWeapon(0);
	weaponAlbum[weaponSetID].changeFrame(modelFrame[character]);
}
void AvatarFactory::changeWeaponType(const int &newCurrentWeapon){
	if(newCurrentWeapon >= weapon.size())
		return;
	int oldFrame = currentWeapon == -1 ? 0 : weaponAlbum[currentWeapon].currentFrame;
	currentWeapon = newCurrentWeapon;
	weaponAlbum[currentWeapon].changeWeaponByID(0);
	weaponAlbum[currentWeapon].changeFrame(oldFrame);
}
void AvatarFactory::changeWeaponTypeByEnum(const WeaponType &newWeaponType){
	for(int i = 0;i<weapon.size();i++){
		if(newWeaponType == weapon[i]){
			changeWeaponType(i);
			break;
		}
	}
}
void AvatarFactory::changeWeapon(const long &index){
	weaponAlbum[currentWeapon].changeWeapon(index);
}
void AvatarFactory::changeWeaponByID(const long &newID){
	weaponAlbum[currentWeapon].changeWeaponByID(newID);
}
void AvatarFactory::updateWeaponIMG(){
	weaponAlbum[currentWeapon].updateIMG();
}
void AvatarFactory::updateWeaponImage(){
	weaponAlbum[currentWeapon].updateImage();
}
void AvatarFactory::releaseWeapon(const int &weaponSetID){
	weaponAlbum[weaponSetID].source.release();
}
void AvatarFactory::changeTN(bool TN){
	for(int i = 0;i<APART_MAXCOUNT;i++){
		album[i].changeTN(TN);
	}
	weaponAlbum[currentWeapon].changeTN(TN);
}
void AvatarFactory::changeFrame(const long &newFrame){
	for(int i = 0;i<APART_MAXCOUNT;i++)
		album[i].changeFrame(newFrame);
	weaponAlbum[currentWeapon].changeFrame(newFrame);
}
void AvatarFactory::updateIMG(){
	updateAvatarIMG();
	updateWeaponIMG();
}
void AvatarFactory::updateImage(){
	while(locked == 1);
	locked = 1;
	updateAvatarImage();
	updateWeaponImage();
	locked = 0;
}
void AvatarFactory::makeNPK(NPKobject &no){
	no.release();
	std::vector<queue> layerUsed;
	queue weaponLayerUsed;
	for(int p = 0;p<APART_MAXCOUNT;p++){
		queue q;
		for(int l = 0;l<album[p].layerList.size();l++){
			q.push_back(0);
		}
		layerUsed.push_back(q);
	}
	for(int l = 0;l<weaponAlbum[currentWeapon].layerList.size();l++){
		weaponLayerUsed.push_back(0);
	}
	int seq = 0;
	while(true){
		AvatarPart p = (AvatarPart)layerSequence[seq][0];
		if(p == APART_WEAPON){
			for(int l = 0;l<weaponAlbum[currentWeapon].layerList.size();l++){
				if(*(dword*)weaponAlbum[currentWeapon].layerList[l].layer == layerSequence[seq][1]){
					weaponLayerUsed[l] = 1;
					if(weaponAlbum[currentWeapon].layerList[l].paletteID <= 0){
						no.IMGpush(weaponAlbum[currentWeapon].layerIMGlist[l], weaponAlbum[currentWeapon].layerNameList[l]);
					}else{
						std::vector<IMGobject> ioList;
						weaponAlbum[currentWeapon].layerIMGlist[l].convertToV4(ioList, colorList());
						if(weaponAlbum[currentWeapon].layerList[l].paletteID < ioList.size()){
							no.IMGpush(ioList[weaponAlbum[currentWeapon].layerList[l].paletteID], formatAvatarIDplusBy(weaponAlbum[currentWeapon].layerNameList[l], weaponAlbum[currentWeapon].layerList[l].paletteID));
						}else{
							no.IMGpush(weaponAlbum[currentWeapon].layerIMGlist[l], weaponAlbum[currentWeapon].layerNameList[l]);
						}
					}
				}
			}
		}else{
			for(int l = 0;l<album[p].layerList.size();l++){
				if(*(dword*)album[p].layerList[l].layer == layerSequence[seq][1]){
					layerUsed[p][l] = 1;
					if(album[p].layerList[l].paletteID <= 0){
						no.IMGpush(album[p].layerIMGlist[l], album[p].layerNameList[l]);
					}else{
						std::vector<IMGobject> ioList;
						album[p].layerIMGlist[l].convertToV4(ioList, colorList());
						if(album[p].layerList[l].paletteID < ioList.size()){
							no.IMGpush(ioList[album[p].layerList[l].paletteID], formatAvatarIDplusBy(album[p].layerNameList[l], album[p].layerList[l].paletteID));
						}else{
							no.IMGpush(album[p].layerIMGlist[l], album[p].layerNameList[l]);
						}
					}
				}
			}
		}
		if(layerSequence[seq][0] == APART_BODY)
			break;
		seq ++;
	}
	//不在拼合表中的图层
	for(int p = 0;p<APART_MAXCOUNT;p++){
		for(int l = 0;l<album[p].layerList.size();l++){
			if(!layerUsed[p][l]){
				no.IMGpush(album[p].layerIMGlist[l], album[p].layerNameList[l]);
			}
		}
	}
	for(int l = 0;l<weaponAlbum[currentWeapon].layerList.size();l++){
		if(!weaponLayerUsed[l]){
			no.IMGpush(weaponAlbum[currentWeapon].layerIMGlist[l], weaponAlbum[currentWeapon].layerNameList[l]);
		}
	}
}
void AvatarFactory::makeImage(point leftTopPos, size displaySize, image &mat){
	mat.create(displaySize);
	int seq = 0;
	while(true){
		AvatarPart p = (AvatarPart)layerSequence[seq][0];
		if(p == APART_WEAPON){
			for(int l = 0;l<weaponAlbum[currentWeapon].layerList.size();l++){
				dword sol = 0;
				memcpy(&sol, weaponAlbum[currentWeapon].layerList[l].layer, 4);
				if(*(dword*)weaponAlbum[currentWeapon].layerList[l].layer == layerSequence[seq][1]){
					mat.putBack(weaponAlbum[currentWeapon].layerImageList[l], LAY, weaponAlbum[currentWeapon].layerBasePointList[l] - leftTopPos);
				}
			}
		}else{
			for(int l = 0;l<album[p].layerList.size();l++){
				dword sol = 0;
				memcpy(&sol, album[p].layerList[l].layer, 4);
				if(*(dword*)album[p].layerList[l].layer == layerSequence[seq][1]){
					mat.putBack(album[p].layerImageList[l], LAY, album[p].layerBasePointList[l] - leftTopPos);
				}
			}
		}
		if(layerSequence[seq][0] == APART_BODY)
			break;
		seq ++;
	}
}
void AvatarFactory::initialModelMaker(const size &outputSize, const point &ofPt, const long &fm, int bodyMode){
	modelMaker.modelSize = outputSize;
	long w = MAX(10, outputSize.W);
	long h = MAX(30, outputSize.H);
	uchar r = modelColor[character].R;
	uchar g = modelColor[character].G;
	uchar b = modelColor[character].B;
	color color1 = color(0xFF-((0xFF-r)>>1), 0xFF-((0xFF-g)>>1), 0xFF-((0xFF-b)>>1));
	color color2 = color(r, g, b);
	color color3 = color(r>>1, g>>1, b>>1);
	modelMaker.backImage.destory();
	modelMaker.backImage.create(h, w);
	modelMaker.backImage.fill(color2);
	modelMaker.backImage.line(point(0,0), point(0, h-1), color1);
	modelMaker.backImage.line(point(0,0), point(w-1, 0), color1);
	modelMaker.backImage.line(point(1,1), point(1, h-2), color1);
	modelMaker.backImage.line(point(1,1), point(w-2, 1), color1);
	modelMaker.backImage.line(point(w-1,h-1), point(0, h-1), color3);
	modelMaker.backImage.line(point(w-1,h-1), point(w-1, 0), color3);
	modelMaker.backImage.line(point(w-2,h-2), point(1, h-2), color3);
	modelMaker.backImage.line(point(w-2,h-2), point(w-2, 1), color3);
	modelMaker.backImage.line(point(3,3), point(3, h-24), color3);
	modelMaker.backImage.line(point(3,3), point(w-4, 3), color3);
	modelMaker.backImage.line(point(w-4,h-24), point(3, h-24), color1);
	modelMaker.backImage.line(point(w-4,h-24), point(w-4, 3), color1);
	modelMaker.frame = fm;
	modelMaker.offset = ofPt;
	//绘制BodyImage
	modelMaker.bodyImage.destory();
	if(album[APART_BODY].content.size() > 0){
		IMGobject io;
		PICinfo pi;
		album[APART_BODY].source.IMGextract(album[APART_BODY].content[0].info[0].posInNPK, io);
		if(modelMaker.frame  >= io.indexCount)
			modelMaker.frame = 0;
		io.PICgetInfo(io.linkFind(modelMaker.frame ), pi);
		io.PICextract(modelMaker.frame, modelMaker.bodyImage);
		modelMaker.bodyImage.turnShield();
		modelMaker.bodyBasePt = pi.basePt;
	}
}
void AvatarFactory::makeAvatarModel(image &outputImage, const AvatarPart &part, const long &index, bool isTN){
	if(index < 0 || index >= album[part].content.size())
		return;
	outputImage.create(modelMaker.modelSize);
	outputImage.putFore(modelMaker.backImage);

	image strImage;
	KoishiExpand::KoishiMarkTool::StrMatLarge(formatAvatarID(album[part].content[index].ID), strImage);
	outputImage.putFore(strImage, LAY, point(outputImage.getWidth() / 2 - strImage.getWidth() / 2, outputImage.getHeight() - 12 - strImage.getHeight() / 2));
	
	image modelImage;
	modelImage.create(size(modelMaker.modelSize.W - 8, modelMaker.modelSize.H - 28));
	int seq = 0;
	while(true){
		AvatarPart p = (AvatarPart)layerSequence[seq][0];
		if(p == part){
			const std::vector<AvatarLayer> &info = (isTN && album[p].content[index].infoTN.size() > 0) ? album[p].content[index].infoTN : album[p].content[index].info;
			for(int l = 0;l<info.size();l++){
				dword sol = 0;
				memcpy(&sol, info[l].layer, 4);
				if(*(dword*)info[l].layer == layerSequence[seq][1]){
					IMGobject io;
					PICinfo pi;
					image im;
					album[p].source.IMGextract(info[l].posInNPK, io);
					io.PICgetInfo(io.linkFind(modelMaker.frame), pi);
					io.PICextract(modelMaker.frame, im, info[l].paletteID);
					modelImage.putBack(im, LAY, point(
						modelImage.getWidth() / 2 - modelMaker.bodyImage.getWidth() / 2 - modelMaker.bodyBasePt.X + pi.basePt.X,
						modelImage.getHeight() / 2 - modelMaker.bodyImage.getHeight() / 2 - modelMaker.bodyBasePt.Y + pi.basePt.Y
						) - modelMaker.offset);
				}
			}
		}
		if(layerSequence[seq][0] == APART_BODY)
			break;
		seq ++;
	}
	modelImage.putBack(modelMaker.bodyImage, LAY, point(
		modelImage.getWidth() / 2 - modelMaker.bodyImage.getWidth() / 2,
		modelImage.getHeight() / 2 - modelMaker.bodyImage.getHeight() / 2) - modelMaker.offset);
	outputImage.putFore(modelImage, LAY, point(4,4));
}
void AvatarFactory::makeWeaponModel(image &outputImage, const long &weaponSetID, const long &index, bool isTN){
	if(index < 0 || index >= weaponAlbum[weaponSetID].content.size())
		return;
	outputImage.create(modelMaker.modelSize);
	outputImage.putFore(modelMaker.backImage);

	image strImage;
	KoishiExpand::KoishiMarkTool::StrMatLarge(formatAvatarID(weaponAlbum[weaponSetID].content[index].ID), strImage);
	outputImage.putFore(strImage, LAY, point(outputImage.getWidth() / 2 - strImage.getWidth() / 2, outputImage.getHeight() - 12 - strImage.getHeight() / 2));
	
	image modelImage;
	modelImage.create(size(modelMaker.modelSize.W - 8, modelMaker.modelSize.H - 28));
	int seq = 0;
	while(true){
		AvatarPart p = (AvatarPart)layerSequence[seq][0];
		if(p == APART_WEAPON){
			const std::vector<AvatarLayer> &info = (isTN && weaponAlbum[weaponSetID].content[index].infoTN.size() > 0) ?
				weaponAlbum[weaponSetID].content[index].infoTN : weaponAlbum[weaponSetID].content[index].info;
			for(int l = 0;l<info.size();l++){
				dword sol = 0;
				memcpy(&sol, info[l].layer, 4);
				if(*(dword*)info[l].layer == layerSequence[seq][1]){
					IMGobject io;
					PICinfo pi;
					image im;
					weaponAlbum[weaponSetID].source.IMGextract(info[l].posInNPK, io);
					if(l == 1 && index == 42) {
						int aa = 0;
						aa++;
						aa = aa + 1;
					}
					io.PICgetInfo(io.linkFind(modelMaker.frame), pi);
					io.PICextract(modelMaker.frame, im, info[l].paletteID);
					modelImage.putBack(im, LAY, point(
						modelImage.getWidth() / 2 - modelMaker.bodyImage.getWidth() / 2 - modelMaker.bodyBasePt.X + pi.basePt.X,
						modelImage.getHeight() / 2 - modelMaker.bodyImage.getHeight() / 2 - modelMaker.bodyBasePt.Y + pi.basePt.Y
						) - modelMaker.offset);
				}
			}
		}
		if(layerSequence[seq][0] == APART_BODY)
			break;
		seq ++;
	}
	modelImage.putBack(modelMaker.bodyImage, LAY, point(
		modelImage.getWidth() / 2 - modelMaker.bodyImage.getWidth() / 2,
		modelImage.getHeight() / 2 - modelMaker.bodyImage.getHeight() / 2) - modelMaker.offset);
	outputImage.putFore(modelImage, LAY, point(4,4));
}
void AvatarFactory::makeButtonImage(image &outputImage, const size &sz, const long &buttonUse){
	// buttonUse:0 empty 1 refresh
	outputImage.create(sz);
	color bColor = modelColor[character];
	uchar r = bColor.R;
	uchar g = bColor.G;
	uchar b = bColor.B;
	color color1 = color(0xFF-((0xFF-r)>>1), 0xFF-((0xFF-g)>>1), 0xFF-((0xFF-b)>>1));
	color color2 = bColor;
	color color3 = color(r>>1, g>>1, b>>1);
	long h = outputImage.getHeight();
	long w = outputImage.getWidth();
	point centerPoint = point(w/2, h/2);
	outputImage.fill(color2);
	outputImage.line(point(0,0), point(0, h-1), color1);
	outputImage.line(point(0,0), point(w-1, 0), color1);
	outputImage.line(point(1,1), point(1, h-2), color1);
	outputImage.line(point(1,1), point(w-2, 1), color1);
	outputImage.line(point(w-1,h-1), point(0, h-1), color3);
	outputImage.line(point(w-1,h-1), point(w-1, 0), color3);
	outputImage.line(point(w-2,h-2), point(1, h-2), color3);
	outputImage.line(point(w-2,h-2), point(w-2, 1), color3);
	if(1 == buttonUse){
		outputImage.line(centerPoint + point(3, -4), centerPoint + point(3, -4), color3);
		outputImage.line(centerPoint + point(2, -3), centerPoint + point(2, -5), color3);
		outputImage.line(centerPoint + point(1, -2), centerPoint + point(1, -6), color3);
		outputImage.line(centerPoint + point(0, -1), centerPoint + point(0, -7), color3);
		outputImage.line(centerPoint + point(-1, 0), centerPoint + point(-1, -8), color3);
		outputImage.line(centerPoint + point(-2, -2), centerPoint + point(-2, -6), color3);
		outputImage.line(centerPoint + point(-7, 2), centerPoint + point(-7, -2), color3);
		outputImage.line(centerPoint + point(-6, 4), centerPoint + point(-6, -4), color3);
		outputImage.line(centerPoint + point(-5, 5), centerPoint + point(-5, -5), color3);
		outputImage.line(centerPoint + point(-4, 6), centerPoint + point(-4, -6), color3);
		outputImage.line(centerPoint + point(-3, 6), centerPoint + point(-3, -6), color3);
		outputImage.line(centerPoint + point(-2, 7), centerPoint + point(-2, 2), color3);
		outputImage.line(centerPoint + point(-1, 7), centerPoint + point(-1, 3), color3);
		outputImage.line(centerPoint + point(0, 7), centerPoint + point(0, 3), color3);
		outputImage.line(centerPoint + point(1, 7), centerPoint + point(1, 3), color3);
		outputImage.line(centerPoint + point(2, 7), centerPoint + point(2, 2), color3);
		outputImage.line(centerPoint + point(3, 6), centerPoint + point(3, -1), color3);
		outputImage.line(centerPoint + point(4, 6), centerPoint + point(4, -1), color3);
		outputImage.line(centerPoint + point(5, 5), centerPoint + point(5, -1), color3);
		outputImage.line(centerPoint + point(6, 4), centerPoint + point(6, -1), color3);
		outputImage.line(centerPoint + point(7, 2), centerPoint + point(7, -1), color3);;
	}
}
///////////////////////////////////////////////////////////////////////////
//装扮辞典
///////////////////////////////////////////////////////////////////////////
AvatarMapEntry::AvatarMapEntry(){
	avatarID = -1;
	iconName = "reserved";
	avatarTitle = "untitled";
}
str AvatarMapEntry::output() const{
	str outStr = "";
	outStr += formatID(avatarID);
	outStr += ",";
	outStr += iconName;
	outStr += ",";
	outStr += avatarTitle;
	return outStr;
}
void AvatarMapEntry::input(const str &line){
	std::vector<str> strArray;
	str::size_type st1 = 0, st2;
	while(true){
		st2 = line.find(",", st1);
		if(st2 == str::npos){
			strArray.push_back(line.substr(st1));
			break;
		}else{
			strArray.push_back(line.substr(st1, st2 - st1));
			st1 = st2 + 1;
		}
	}
	avatarID = strArray.size() > 0 ? std::stoi(strArray[0]) : -1;
	iconName = strArray.size() > 1 ? strArray[1] : "reserved";
	avatarTitle = strArray.size() > 2 ? strArray[2] : "untitled";
}
AvatarSuitEntry::AvatarSuitEntry(){
	suitName = "untitled";
	for(int i = 0;i<APART_MAXCOUNT;i++)
		avatarID[i] = -1;
}
str AvatarSuitEntry::output() const{
	str outStr = "";
	outStr += suitName;
	outStr += ",";
	for(int i = 0;i<APART_MAXCOUNT;i++){
		outStr += formatID(avatarID[i]);
		if(i<APART_MAXCOUNT-1)
			outStr += ",";
	}
	return outStr;
}
void AvatarSuitEntry::input(const str &line){
	std::vector<str> strArray;
	str::size_type st1 = 0, st2;
	while(true){
		st2 = line.find(",", st1);
		if(st2 == str::npos){
			strArray.push_back(line.substr(st1));
			break;
		}else{
			strArray.push_back(line.substr(st1, st2 - st1));
			st1 = st2 + 1;
		}
	}
	suitName = strArray.size() > 0 ? strArray[0] : "untitled";
	for(int i = 0;i<APART_MAXCOUNT;i++){
		avatarID[i] = (strArray.size() > 1 + i) ? std::stoi(strArray[1+i]):-1;
	}
}
void AvatarMap::initial(const AvatarCharacter &newAvatarCharacter){
	character = newAvatarCharacter;
	avatarContent.clear();
	for(int i = 0;i<APART_MAXCOUNT;i++)
		avatarContent.push_back(std::vector<AvatarMapEntry>());
	weapon = characterWeaponList(character);
	weaponContent.clear();
	for(int i = 0;i<weapon.size();i++)
		weaponContent.push_back(std::vector<AvatarMapEntry>());
	suitContent.clear();
}
void AvatarMap::load(str fileName){
	stream sFile;
	if(!sFile.loadFile(fileName))
		return;
	str myStr((const char*)sFile.begin());
	str::size_type st1 = 0, st2;
	int parsing = 0;	//解码suit/avatar/weapon
	AvatarPart parsingPart = APART_UD;
	WeaponType parsingType = AWEAPON_UD;
	while(true){
		st2 = myStr.find("\r\n", st1);
		str lineStr;
		if(st2 == str::npos){
			lineStr = myStr.substr(st1);
		}else{
			lineStr = myStr.substr(st1, st2-st1);
			st1 = st2 + 2;
		}
		if(lineStr.size() == 0){
			if(st2 == str::npos){
				break;
			}
			continue;
		}
		if(lineStr.size() > 0 && lineStr[0] == '['){
			parsing = 0;
			if(lineStr == "[suit]"){
				parsing = 1;
			}
			if(lineStr.substr(0,7) == "[avatar"){
				parsingPart = APART_UD;
				for(int p = 0; p<APART_MAXCOUNT;p++){
					if(lineStr.substr(8) == avatarString[p] + "]"){
						parsingPart = (AvatarPart)p;
					}
				}
				if(parsingPart != APART_UD){
					parsing = 2;
				}else{
					parsing = 0;
				}
			}
			if(lineStr.substr(0,7) == "[weapon"){
				parsingType = AWEAPON_UD;
				for(int p = 0; p<AWEAPON_MAXCOUNT;p++){
					if(lineStr.substr(8) == weaponString[p] + "]"){
						parsingType = (WeaponType)p;
					}
				}
				if(parsingType != AWEAPON_UD){
					parsing = 3;
				}else{
					parsing = 0;
				}
			}
		}else{
			switch(parsing){
			case 1:
				{
					AvatarSuitEntry ase;
					ase.input(lineStr);
					if(ase.suitName.size() > 0){
						suitContent.push_back(ase);
					}
				}
				break;
			case 2:
				{
					AvatarMapEntry ame;
					ame.input(lineStr);
					if(ame.avatarID >= 0){
						avatarContent[parsingPart].push_back(ame);
					}
				}
				break;
			case 3:
				{
					AvatarMapEntry ame;
					ame.input(lineStr);
					if(ame.avatarID >= 0){
						long weaponID = characterWeaponListID(character, parsingType);
						if(weaponID >= 0)
							weaponContent[weaponID].push_back(ame);
					}
				}
			}
		}
		if(st2 == str::npos){
			break;
		}
	}
}
void AvatarMap::save(str fileName){
	stream sFile;
	//计算分配空间
	int allocateLen = 512 + 96 * suitContent.size();
	for(int i = 0;i<avatarContent.size();i++)
		allocateLen += 32 * avatarContent[i].size();
	for(int i = 0;i<weaponContent.size();i++)
		allocateLen += 32 * weaponContent[i].size();
	sFile.allocate(allocateLen);
	sFile.pushString("[suit]\r\n");
	for(int i = 0;i<suitContent.size();i++){
		sFile.pushString(suitContent[i].output());
		sFile.pushString("\r\n");
	}
	for(int i = 0;i<avatarContent.size();i++){
		sFile.pushString("[avatar,"+avatarString[i]+"]\r\n");
		for(int j = 0;j<avatarContent[i].size();j++){
			sFile.pushString(avatarContent[i][j].output());
			sFile.pushString("\r\n");
		}
	}
	for(int i = 0;i<weaponContent.size();i++){
		sFile.pushString("[weapon,"+weaponString[weapon[i]]+"]\r\n");
		for(int j = 0;j<weaponContent[i].size();j++){
			sFile.pushString(weaponContent[i][j].output());
			sFile.pushString("\r\n");
		}
	}
	sFile.makeFile(fileName);
}
void AvatarMap::addAvatarEntry(const AvatarPart &part, const long &ID, const str &iconIMGname, const str &avatarName){
	AvatarMapEntry ame;
	ame.avatarID = ID;
	ame.avatarTitle = avatarName;
	ame.iconName = iconIMGname;
	for(int i = 0 ;i<avatarContent[part].size();i++){
		if(avatarContent[part][i].avatarID>ID){
			avatarContent[part].insert(avatarContent[part].begin()+i, ame);
			return;
		}
	}
	avatarContent[part].push_back(ame);
	return;
}
void AvatarMap::addWeaponEntry(const WeaponType &type, const long &ID, const str &iconIMGname, const str &avatarName){
	long weaponTypeIndex = characterWeaponListID(character, type);
	if(weaponTypeIndex == -1)
		return;
	AvatarMapEntry ame;
	ame.avatarID = ID;
	ame.avatarTitle = avatarName;
	ame.iconName = iconIMGname;
	for(int i = 0 ;i<weaponContent[weaponTypeIndex].size();i++){
		if(weaponContent[weaponTypeIndex][i].avatarID>ID){
			weaponContent[weaponTypeIndex].insert(weaponContent[weaponTypeIndex].begin()+i, ame);
			return;
		}
	}
	weaponContent[weaponTypeIndex].push_back(ame);
	return;
}
void AvatarMap::addSuitEntry(const str &suitName, const long id[9]){
	AvatarSuitEntry ase;
	ase.suitName = suitName;
	memcpy(ase.avatarID, id, sizeof(long)*9);
	suitContent.push_back(ase);
	return;
}
bool AvatarMap::checkAvatarEntry(const AvatarPart &part, const long &ID, const str &iconName, const str &avatarName){
	queue q = findAvatarPos(part, ID);
	for(int i = 0;i<q.size();i++){
		if(iconName.find(avatarContent[part][q[i]].iconName) != str::npos && 
			avatarName.find(avatarContent[part][q[i]].avatarTitle) != str::npos){
				return true;
		}
	}
	return false;
}
bool AvatarMap::checkWeaponEntry(const WeaponType &type, const long &ID, const str &iconName, const str &avatarName){
	queue q = findWeaponPos(type, ID);
	long weaponTypeIndex = characterWeaponListID(character, type);
	for(int i = 0;i<q.size();i++){
		if(iconName.find(weaponContent[weaponTypeIndex][q[i]].iconName) != str::npos && 
			avatarName.find(weaponContent[weaponTypeIndex][q[i]].avatarTitle) != str::npos){
				return true;
		}
	}
	return false;
}
bool AvatarMap::checkSuitEntry(const str &suitName, const long id[9]){
	queue q = findSuitPos(suitName);
	for(int i = 0;i<q.size();i++){
		bool allSame = true;
		for(int j = 0;j<9;j++){
			if(id[j] != suitContent[q[i]].avatarID[j]){
				allSame = false;
				break;
			}
		}
		if(allSame)
			return true;
	}
	return false;
}
void AvatarMap::deleteAvatarEntry(const AvatarPart &part, const long &pos){
	avatarContent[part].erase(avatarContent[part].begin() + pos);
}
void AvatarMap::deleteWeaponEntry(const WeaponType &type, const long &pos){
	long weaponTypeIndex = characterWeaponListID(character, type);
	if(weaponTypeIndex == -1)
		return;
	weaponContent[weaponTypeIndex].erase(weaponContent[weaponTypeIndex].begin() + pos);
}
void AvatarMap::deleteSuitEntry(const long &pos){
	suitContent.erase(suitContent.begin() + pos);
}
queue AvatarMap::findAvatarPosByIcon(const AvatarPart &part, const str &iconName){
	queue q;
	for(int i = 0;i<avatarContent[part].size();i++){
		if(avatarContent[part][i].iconName.find(iconName) != str::npos)
			q.push_back(i);
	}
	return q;
}
queue AvatarMap::findAvatarPos(const AvatarPart &part, const long &ID){
	queue q;
	for(int i = 0;i<avatarContent[part].size();i++){
		if(avatarContent[part][i].avatarID == ID)
			q.push_back(i);
	}
	return q;
}
queue AvatarMap::findAvatarPosByName(const AvatarPart &part, const str &avatarName){
	queue q;
	for(int i = 0;i<avatarContent[part].size();i++){
		if(avatarContent[part][i].avatarTitle.find(avatarName) != str::npos)
			q.push_back(i);
	}
	return q;
}
queue AvatarMap::findWeaponPosByIcon(const WeaponType &type, const str &iconName){
	long weaponTypeIndex = characterWeaponListID(character, type);
	if(weaponTypeIndex == -1)
		return queue();
	queue q;
	for(int i = 0;i<weaponContent[weaponTypeIndex].size();i++){
		if(weaponContent[weaponTypeIndex][i].iconName.find(iconName) != str::npos)
			q.push_back(i);
	}
	return q;
}
queue AvatarMap::findWeaponPos(const WeaponType &type, const long &ID){
	long weaponTypeIndex = characterWeaponListID(character, type);
	if(weaponTypeIndex == -1)
		return queue();
	queue q;
	for(int i = 0;i<weaponContent[weaponTypeIndex].size();i++){
		if(weaponContent[weaponTypeIndex][i].avatarID == ID)
			q.push_back(i);
	}
	return q;
}
queue AvatarMap::findWeaponPosByName(const WeaponType &type, const str &avatarName){
	long weaponTypeIndex = characterWeaponListID(character, type);
	if(weaponTypeIndex == -1)
		return queue();
	queue q;
	for(int i = 0;i<weaponContent[weaponTypeIndex].size();i++){
		if(weaponContent[weaponTypeIndex][i].avatarTitle.find(avatarName) != str::npos)
			q.push_back(i);
	}
	return q;
}

queue AvatarMap::findSuitPos(const AvatarPart &part, const int &avatarID){
	queue q;
	for(int i = 0;i<suitContent.size();i++){
		if(suitContent[i].avatarID[part] == avatarID){
			q.push_back(i);
		}
	}
	return q;
}

queue AvatarMap::findSuitPos(const str &suitName){
	queue q;
	for(int i = 0;i<suitContent.size();i++){
		if(suitContent[i].suitName == suitName){
			q.push_back(i);
		}
	}
	return q;
}