#include "stdafx.h"
#include "KoishiEx.h"
#include "KoishiNeoplePack.h"

#pragma once
//像素格式
using namespace Koishi;
using namespace KoishiNeoplePack;

namespace KoishiAvatar{
	typedef char AvatarLayerFlag[4];
	enum AvatarPart:uchar{
		APART_CAP, APART_HAIR, APART_FACE, APART_NECK, 
		APART_COAT,	APART_PANTS, APART_BELT, APART_SHOES, APART_BODY,
		APART_MAXCOUNT, APART_UD = 0XFF, APART_WEAPON = 0xFE 
	};
	enum AvatarCharacter:uchar{
		ACHARACTER_SM, ACHARACTER_SG, ACHARACTER_FT, ACHARACTER_FM, 
		ACHARACTER_GN, ACHARACTER_GG, ACHARACTER_MG, ACHARACTER_MM, ACHARACTER_PR, 
		ACHARACTER_PG, ACHARACTER_TH, ACHARACTER_KN, ACHARACTER_DL, ACHARACTER_GB, 
		ACHARACTER_MAXCOUNT, ACHARACTER_UD = 0xFF
	};
	enum WeaponType:uchar{
		AWEAPON_LGSWD, AWEAPON_LSWD, AWEAPON_MSWD, AWEAPON_SSWD, 
		AWEAPON_BONESWD, AWEAPON_GEMSWD, AWEAPON_BEAMSWD, 
		AWEAPON_CLUB, AWEAPON_KATANA, AWEAPON_LKATANA,
		AWEAPON_LBLADE, AWEAPON_SBLADE, AWEAPON_CORESWD,
		AWEAPON_ARM, AWEAPON_TONFA, AWEAPON_GAUNTLET,
		AWEAPON_BONECLAW, AWEAPON_CLAW, 
		AWEAPON_BOXGLOVE, AWEAPON_GLOVE, AWEAPON_KNUCKLE,
		AWEAPON_AUTO, AWEAPON_BOWGUN, AWEAPON_HCAN, AWEAPON_MUSKET, AWEAPON_REV,
		AWEAPON_POLE, AWEAPON_ROD, AWEAPON_SPEAR, AWEAPON_STAFF, AWEAPON_BROOM,
		AWEAPON_DAGGER, AWEAPON_TWINSWD, AWEAPON_WAND, AWEAPON_CHAKRAWEAPON,
		AWEAPON_HALBERD, AWEAPON_PIKE, AWEAPON_JAVELIN, AWEAPON_BEAMSPEAR,
		AWEAPON_KHAKKHARA, AWEAPON_ROSARY, AWEAPON_SCYTHE, AWEAPON_TOTEM, AWEAPON_AXE, AWEAPON_CROSS,
		AWEAPON_MAXCOUNT, AWEAPON_UD = 0XFF
	};
	typedef std::vector<WeaponType> WeaponSet;
	enum {
		WEAPON_MAXCOUNT_PER_CHAR = 12
	};
	enum AvatarErrorCode:uchar{
		AERROR_OK,
		AERROR_NO_SUCH_FILE,
		AERROR_INDEX_EXCEEDED,
		AERROR_IMAGE_ERROR,
		AERROR_DATA_ERROR,
		AERROR_DATA_OVERFLOW
	};
	//每个图层的信息
	class AvatarLayer{
	public:
		AvatarLayerFlag layer;	//图层的主标志位
		long posInNPK;			//该图层在NPK的何位置
		long paletteID;			//该图层使用的是几号调色板
	public:
		bool isGlowing() const;
	};
	//装扮
	class Avatar{
	public:
		//Avatar();
	public:
		int ID;										//装扮ID
		int layerCount;
		int layerCountTN;
	public:
		std::vector<AvatarLayer> info;					//每种样式的装扮信息
		std::vector<AvatarLayer> infoTN;				//每种样式TN的装扮信息
	};
	class AvatarAlbum{
	//装扮库
	public:
		AvatarAlbum();
	private:
		volatile uchar locked;						//调用updateImage用的锁
	public:
		AvatarCharacter character;					//职业类型
		AvatarPart part;							//该装扮部件类型
		std::vector<Avatar> content;				//装扮目录
		NPKobject source;							//如果不是武器，则只有第一个可用
	public:
		//控制参数
		long currentSelect;						//当前选择
		long currentFrame;						//当前帧
		long TNenabled;							//TN开启和关闭
		std::vector<AvatarLayer> layerList;		//当前选择装扮各图层（存储在NPK内部的位置和调色板）
		std::vector<IMGobject> layerIMGlist;	//当前选择装扮各图层的IMG
		std::vector<str> layerNameList;			//当前选择装扮各图层的路径名
		std::vector<image> layerImageList;		//当前选择装扮各图层的贴图数据
		std::vector<point> layerBasePointList;	//当前选择装扮各图层的贴图基准点坐标
	public:
		bool loadNPK(const str& NPKfileName);
		bool changeAvatar(const long &index);	//根据content的index变更Avatar
		long findAvatarID(const long &newID);
		bool changeAvatarByID(const long &newID);	//根据Avatar的ID变更Avatar
		bool changeTN(bool TN);
		bool changeFrame(const long &newFrame);
		bool updateIMG();						//更新layerIMGlist，layerNameList（变更Avatar的时候调用）
		bool updateImage();						//更新贴图
	};
	class WeaponAlbum{
	//装扮库
	public:
		WeaponAlbum();
	private:
		volatile uchar locked;						//调用updateImage用的锁
	public:
		WeaponType type;							//该装扮部件类型
		std::vector<Avatar> content;				//装扮目录
		NPKobject source;							//如果不是武器，则只有第一个可用
	public:
		//控制参数
		long currentSelect;						//当前选择
		long currentFrame;						//当前帧
		long TNenabled;							//TN开启和关闭
		std::vector<AvatarLayer> layerList;		//当前选择装扮各图层（存储在NPK内部的位置和调色板）
		std::vector<IMGobject> layerIMGlist;	//当前选择装扮各图层的IMG
		std::vector<str> layerNameList;			//当前选择装扮各图层的路径名
		std::vector<image> layerImageList;		//当前选择装扮各图层的贴图数据
		std::vector<point> layerBasePointList;	//当前选择装扮各图层的贴图基准点坐标
	public:
		bool loadNPK(const str& NPKfileName);
		bool changeWeapon(const long &index);	//根据content的index变更Avatar
		long findWeaponID(const long &newID);
		bool changeWeaponByID(const long &newID);	//根据Avatar的ID变更Avatar
		bool changeTN(bool TN);
		bool changeFrame(const long &newFrame);
		bool updateIMG();						//更新layerIMGlist，layerNameList（变更Avatar的时候调用）
		bool updateImage();						//更新贴图
	};
	class AvatarFactory{
	public:
		AvatarFactory();
	private:
		volatile uchar locked;						//调用updateImage用的锁
	public:
		str resourcePath;
		AvatarCharacter character;					//职业类型
		WeaponSet weapon;							//武器种类
		int currentWeapon;							//当前选择的武器
		std::vector<AvatarAlbum> album;
		std::vector<WeaponAlbum> weaponAlbum;// weaponAlbum[WEAPON_MAXCOUNT_PER_CHAR];
	public:
		void initial(const AvatarCharacter &newCharacter, const str &newPath);
	public:
		void loadAvatar(const AvatarPart &part);
		void changeAvatar(const AvatarPart &part, const long &index);
		void changeAvatarByID(const AvatarPart &part, const long &newID);
		void updateAvatarIMG(const AvatarPart &part);								//更新layerIMGlist，layerNameList（变更Avatar的时候调用）
		void updateAvatarImage(const AvatarPart &part);								//更新贴图（changeFrame的时候调用）
		void updateAvatarIMG();
		void updateAvatarImage();
		void releaseAvatar(const AvatarPart &part);
	public:
		void loadWeapon(const int &weaponSetID);
		void changeWeaponType(const int &newCurrentWeapon);
		void changeWeaponTypeByEnum(const WeaponType &newWeaponType);
		void changeWeapon(const long &index);
		void changeWeaponByID(const long &newID);
		void updateWeaponIMG();								//更新layerIMGlist，layerNameList（变更Avatar的时候调用）
		void updateWeaponImage();								//更新贴图（changeFrame的时候调用）
		void releaseWeapon(const int &weaponSetID);
	public:
		void changeTN(bool TN);														
		void changeFrame(const long &newFrame);										//全部都会变动
		void updateIMG();
		void updateImage();
	public:
		void makeNPK(NPKobject &no);
		void makeImage(point leftTopPos, size displaySize, image &mat);
	public:
		struct{
			image backImage;
			image bodyImage;
			point bodyBasePt;
			size modelSize;
			long frame;
			point offset;
		}modelMaker;
		void initialModelMaker(const size &outputSize, const point &ofPt, const long &fm, int bodyMode = 1);
		void makeAvatarModel(image &outputImage, const AvatarPart &part, const long &index, bool isTN = false); //必须先调用initialModelMaker
		void makeWeaponModel(image &outputImage, const long &weaponSetID, const long &index, bool isTN = false);
		void makeButtonImage(image &outputImage, const size &sz, const long &buttonUse);	
	};
	//部分辅助函数
	str formatAvatarID(int);
	str formatAvatarIDplusBy(const str &, int);
	str NPK_avatar(AvatarCharacter, AvatarPart);
	str IMG_avatar(AvatarCharacter, AvatarPart);
	str NPK_weapon(AvatarCharacter, WeaponType);
	str NPK_avatarIcon(AvatarCharacter);
	str IMG_avatarIcon(AvatarCharacter, AvatarPart);
	str IMG_avatarIcon(AvatarCharacter, str);
	std::vector<str> NPK_weaponIcon(AvatarCharacter);
	class AvatarMapEntry{
	public:
		long avatarID;
		str iconName;
		str avatarTitle;		//名称
	public:
		AvatarMapEntry();
		str output() const;
		void input(const str &line);
	};
	class AvatarSuitEntry{
	public:
		long avatarID[9];
		str suitName;			//名称
	public:
		AvatarSuitEntry();
		str output() const;
		void input(const str &line);
	};
	class AvatarMap{
	public:
		AvatarCharacter character;
		WeaponSet weapon;
		std::vector<std::vector<AvatarMapEntry>> avatarContent;
		std::vector<std::vector<AvatarMapEntry>> weaponContent;
		std::vector<AvatarSuitEntry> suitContent;
	public:
		void initial(const AvatarCharacter &newAvatarCharacter);
		void load(str fileName);
		void save(str fileName);
		void addAvatarEntry(const AvatarPart &part, const long &ID, const str &iconName, const str &avatarName);
		void addWeaponEntry(const WeaponType &type, const long &ID, const str &iconName, const str &avatarName);
		void addSuitEntry(const str &suitName, const long id[9]);
		void deleteAvatarEntry(const AvatarPart &part, const long &pos);
		void deleteWeaponEntry(const WeaponType &type, const long &pos);
		void deleteSuitEntry(const long &pos);
	public:
		//查重
		bool checkAvatarEntry(const AvatarPart &part, const long &ID, const str &iconName, const str &avatarName);
		bool checkWeaponEntry(const WeaponType &type, const long &ID, const str &iconName, const str &avatarName);
		bool checkSuitEntry(const str &suitName, const long id[9]);
	public:
		//查询
		queue findAvatarPosByIcon(const AvatarPart &part, const str &iconName);
		queue findAvatarPos(const AvatarPart &part, const long &ID);
		queue findAvatarPosByName(const AvatarPart &part, const str &avatarName);
		queue findWeaponPosByIcon(const WeaponType &type, const str &iconName);
		queue findWeaponPos(const WeaponType &type, const long &ID);
		queue findWeaponPosByName(const WeaponType &type, const str &avatarName);
		queue findSuitPos(const AvatarPart &part, const int &avatarID);
		queue findSuitPos(const str &suitName);
	};
}