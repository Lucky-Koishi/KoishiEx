#include "stdafx.h"
#include "KoishiEx.h"
#include "KoishiNeoplePack.h"

#pragma once
//���ظ�ʽ
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
	//ÿ��ͼ�����Ϣ
	class AvatarLayer{
	public:
		AvatarLayerFlag layer;	//ͼ�������־λ
		long posInNPK;			//��ͼ����NPK�ĺ�λ��
		long paletteID;			//��ͼ��ʹ�õ��Ǽ��ŵ�ɫ��
	public:
		bool isGlowing() const;
	};
	//װ��
	class Avatar{
	public:
		//Avatar();
	public:
		int ID;										//װ��ID
		int layerCount;
		int layerCountTN;
	public:
		std::vector<AvatarLayer> info;					//ÿ����ʽ��װ����Ϣ
		std::vector<AvatarLayer> infoTN;				//ÿ����ʽTN��װ����Ϣ
	};
	class AvatarAlbum{
	//װ���
	public:
		AvatarAlbum();
	private:
		volatile uchar locked;						//����updateImage�õ���
	public:
		AvatarCharacter character;					//ְҵ����
		AvatarPart part;							//��װ�粿������
		std::vector<Avatar> content;				//װ��Ŀ¼
		NPKobject source;							//���������������ֻ�е�һ������
	public:
		//���Ʋ���
		long currentSelect;						//��ǰѡ��
		long currentFrame;						//��ǰ֡
		long TNenabled;							//TN�����͹ر�
		std::vector<AvatarLayer> layerList;		//��ǰѡ��װ���ͼ�㣨�洢��NPK�ڲ���λ�ú͵�ɫ�壩
		std::vector<IMGobject> layerIMGlist;	//��ǰѡ��װ���ͼ���IMG
		std::vector<str> layerNameList;			//��ǰѡ��װ���ͼ���·����
		std::vector<image> layerImageList;		//��ǰѡ��װ���ͼ�����ͼ����
		std::vector<point> layerBasePointList;	//��ǰѡ��װ���ͼ�����ͼ��׼������
	public:
		bool loadNPK(const str& NPKfileName);
		bool changeAvatar(const long &index);	//����content��index���Avatar
		long findAvatarID(const long &newID);
		bool changeAvatarByID(const long &newID);	//����Avatar��ID���Avatar
		bool changeTN(bool TN);
		bool changeFrame(const long &newFrame);
		bool updateIMG();						//����layerIMGlist��layerNameList�����Avatar��ʱ����ã�
		bool updateImage();						//������ͼ
	};
	class WeaponAlbum{
	//װ���
	public:
		WeaponAlbum();
	private:
		volatile uchar locked;						//����updateImage�õ���
	public:
		WeaponType type;							//��װ�粿������
		std::vector<Avatar> content;				//װ��Ŀ¼
		NPKobject source;							//���������������ֻ�е�һ������
	public:
		//���Ʋ���
		long currentSelect;						//��ǰѡ��
		long currentFrame;						//��ǰ֡
		long TNenabled;							//TN�����͹ر�
		std::vector<AvatarLayer> layerList;		//��ǰѡ��װ���ͼ�㣨�洢��NPK�ڲ���λ�ú͵�ɫ�壩
		std::vector<IMGobject> layerIMGlist;	//��ǰѡ��װ���ͼ���IMG
		std::vector<str> layerNameList;			//��ǰѡ��װ���ͼ���·����
		std::vector<image> layerImageList;		//��ǰѡ��װ���ͼ�����ͼ����
		std::vector<point> layerBasePointList;	//��ǰѡ��װ���ͼ�����ͼ��׼������
	public:
		bool loadNPK(const str& NPKfileName);
		bool changeWeapon(const long &index);	//����content��index���Avatar
		long findWeaponID(const long &newID);
		bool changeWeaponByID(const long &newID);	//����Avatar��ID���Avatar
		bool changeTN(bool TN);
		bool changeFrame(const long &newFrame);
		bool updateIMG();						//����layerIMGlist��layerNameList�����Avatar��ʱ����ã�
		bool updateImage();						//������ͼ
	};
	class AvatarFactory{
	public:
		AvatarFactory();
	private:
		volatile uchar locked;						//����updateImage�õ���
	public:
		str resourcePath;
		AvatarCharacter character;					//ְҵ����
		WeaponSet weapon;							//��������
		int currentWeapon;							//��ǰѡ�������
		std::vector<AvatarAlbum> album;
		std::vector<WeaponAlbum> weaponAlbum;// weaponAlbum[WEAPON_MAXCOUNT_PER_CHAR];
	public:
		void initial(const AvatarCharacter &newCharacter, const str &newPath);
	public:
		void loadAvatar(const AvatarPart &part);
		void changeAvatar(const AvatarPart &part, const long &index);
		void changeAvatarByID(const AvatarPart &part, const long &newID);
		void updateAvatarIMG(const AvatarPart &part);								//����layerIMGlist��layerNameList�����Avatar��ʱ����ã�
		void updateAvatarImage(const AvatarPart &part);								//������ͼ��changeFrame��ʱ����ã�
		void updateAvatarIMG();
		void updateAvatarImage();
		void releaseAvatar(const AvatarPart &part);
	public:
		void loadWeapon(const int &weaponSetID);
		void changeWeaponType(const int &newCurrentWeapon);
		void changeWeaponTypeByEnum(const WeaponType &newWeaponType);
		void changeWeapon(const long &index);
		void changeWeaponByID(const long &newID);
		void updateWeaponIMG();								//����layerIMGlist��layerNameList�����Avatar��ʱ����ã�
		void updateWeaponImage();								//������ͼ��changeFrame��ʱ����ã�
		void releaseWeapon(const int &weaponSetID);
	public:
		void changeTN(bool TN);														
		void changeFrame(const long &newFrame);										//ȫ������䶯
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
		void makeAvatarModel(image &outputImage, const AvatarPart &part, const long &index, bool isTN = false); //�����ȵ���initialModelMaker
		void makeWeaponModel(image &outputImage, const long &weaponSetID, const long &index, bool isTN = false);
		void makeButtonImage(image &outputImage, const size &sz, const long &buttonUse);	
	};
	//���ָ�������
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
		str avatarTitle;		//����
	public:
		AvatarMapEntry();
		str output() const;
		void input(const str &line);
	};
	class AvatarSuitEntry{
	public:
		long avatarID[9];
		str suitName;			//����
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
		//����
		bool checkAvatarEntry(const AvatarPart &part, const long &ID, const str &iconName, const str &avatarName);
		bool checkWeaponEntry(const WeaponType &type, const long &ID, const str &iconName, const str &avatarName);
		bool checkSuitEntry(const str &suitName, const long id[9]);
	public:
		//��ѯ
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