#pragma once
#include "../KoishiEx/KoishiEx.h"
#include "../KoishiEx/avatar.h"
// ToolAvatarMark 对话框
using namespace Koishi;
using namespace KoishiAvatar;
class ToolAvatarMark : public CDialogEx
{
	DECLARE_DYNAMIC(ToolAvatarMark)

public:
	ToolAvatarMark(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolAvatarMark();

// 对话框数据
	enum { IDD = IDD_TOOL_AVATAR_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton2();

	void title();
	static unsigned go(void*context);
	afx_msg void OnBnClickedButton3();
	inline static str getSerialID(const str &imgStr){
		bool startScan = false;
		str result = "0";
		for(int i = 0;i<imgStr.size();i++){
			if(imgStr[i] >= '0' && imgStr[i]<='9'){
				result.push_back(imgStr[i]);
				startScan = true;
			}else{
				if(startScan)
					return result;
			}
		}
		return result;
	}
	inline static std::vector<str> getWeaponNPKlist(const AvatarCharacter &ac){
		std::vector<str> list;
		switch(ac){
		case ACHARACTER_SM:
			list.push_back("sprite_character_swordman_equipment_weapon_boneswd.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_lgswd.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_lkatana.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_mswd.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_beamswd.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_club.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_gemswd.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_lswd_teen.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_sswd.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_lswd.NPK");
			list.push_back("sprite_character_swordman_equipment_weapon_katana.NPK");
			break;
		case ACHARACTER_SG:
			list.push_back("sprite_character_swordman_atequipment_weapon_lgswd.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_beamswd.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_boneswd.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_gemswd.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_lkatana.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_lswd.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_mswd.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_sswd.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_club.NPK");
			list.push_back("sprite_character_swordman_atequipment_weapon_katana.NPK");
			break;
		case ACHARACTER_GN:
			list.push_back("sprite_character_gunner_equipment_weapon_auto.NPK");
			list.push_back("sprite_character_gunner_equipment_weapon_bowgun.NPK");
			list.push_back("sprite_character_gunner_equipment_weapon_musket.NPK");
			list.push_back("sprite_character_gunner_equipment_weapon_rev.NPK");
			list.push_back("sprite_character_gunner_equipment_weapon_hcan.NPK");
			break;
		case ACHARACTER_GG:
			list.push_back("sprite_character_gunner_atequipment_weapon_auto.NPK");
			list.push_back("sprite_character_gunner_atequipment_weapon_bowgun.NPK");
			list.push_back("sprite_character_gunner_atequipment_weapon_musket.NPK");
			list.push_back("sprite_character_gunner_atequipment_weapon_rev.NPK");
			list.push_back("sprite_character_gunner_atequipment_weapon_hcan.NPK");
			break;
		case ACHARACTER_FT:
			list.push_back("sprite_character_fighter_equipment_weapon_arm.NPK");
			list.push_back("sprite_character_fighter_equipment_weapon_boneclaw.NPK");
			list.push_back("sprite_character_fighter_equipment_weapon_boxglove.NPK");
			list.push_back("sprite_character_fighter_equipment_weapon_claw.NPK");
			list.push_back("sprite_character_fighter_equipment_weapon_glove.NPK");
			list.push_back("sprite_character_fighter_equipment_weapon_knuckle.NPK");
			list.push_back("sprite_character_fighter_equipment_weapon_tonfa.NPK");
			list.push_back("sprite_character_fighter_equipment_weapon_gauntlet.NPK");
			break;
		case ACHARACTER_FM:
			list.push_back("sprite_character_fighter_atequipment_weapon_arm.NPK");
			list.push_back("sprite_character_fighter_atequipment_weapon_boneclaw.NPK");
			list.push_back("sprite_character_fighter_atequipment_weapon_boxglove.NPK");
			list.push_back("sprite_character_fighter_atequipment_weapon_claw.NPK");
			list.push_back("sprite_character_fighter_atequipment_weapon_glove.NPK");
			list.push_back("sprite_character_fighter_atequipment_weapon_knuckle.NPK");
			list.push_back("sprite_character_fighter_atequipment_weapon_tonfa.NPK");
			list.push_back("sprite_character_fighter_atequipment_weapon_gauntlet.NPK");
			break;
		case ACHARACTER_MG:
			list.push_back("sprite_character_mage_equipment_weapon_rod.NPK");
			list.push_back("sprite_character_mage_equipment_weapon_broom.NPK");
			list.push_back("sprite_character_mage_equipment_weapon_pole.NPK");
			list.push_back("sprite_character_mage_equipment_weapon_spear.NPK");
			list.push_back("sprite_character_mage_equipment_weapon_staff.NPK");
			break;
		case ACHARACTER_MM:
			list.push_back("sprite_character_mage_atequipment_weapon_rod.NPK");
			list.push_back("sprite_character_mage_atequipment_weapon_broom.NPK");
			list.push_back("sprite_character_mage_atequipment_weapon_pole.NPK");
			list.push_back("sprite_character_mage_atequipment_weapon_spear.NPK");
			list.push_back("sprite_character_mage_atequipment_weapon_staff.NPK");
			break;
		case ACHARACTER_PR:
			list.push_back("sprite_character_priest_equipment_weapon_axe.NPK");
			list.push_back("sprite_character_priest_equipment_weapon_cross.NPK");
			list.push_back("sprite_character_priest_equipment_weapon_rosary.NPK");
			list.push_back("sprite_character_priest_equipment_weapon_totem.NPK");
			list.push_back("sprite_character_priest_equipment_weapon_scythe.NPK");
			break;
		case ACHARACTER_PG:
			list.push_back("sprite_character_priest_atequipment_weapon_axe.NPK");
			list.push_back("sprite_character_priest_atequipment_weapon_cross.NPK");
			list.push_back("sprite_character_priest_atequipment_weapon_rosary.NPK");
			list.push_back("sprite_character_priest_atequipment_weapon_totem.NPK");
			list.push_back("sprite_character_priest_atequipment_weapon_scythe.NPK");
			list.push_back("sprite_character_priest_atequipment_weapon_khakkhara.NPK");
			break;
		case ACHARACTER_TH:
			list.push_back("sprite_character_thief_equipment_weapon_chakraweapon.NPK");
			list.push_back("sprite_character_thief_equipment_weapon_dagger.NPK");
			list.push_back("sprite_character_thief_equipment_weapon_twinswd.NPK");
			list.push_back("sprite_character_thief_equipment_weapon_wand.NPK");
			break;
		case ACHARACTER_KN:
			list.push_back("sprite_character_knight_equipment_weapon_lgswd.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_lkatana.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_mswd.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_boneswd.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_gemswd.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_lswd.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_sswd.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_club.NPK");
			list.push_back("sprite_character_knight_equipment_weapon_katana.NPK");
			break;
		case ACHARACTER_DL:
			list.push_back("sprite_character_demoniclancer_equipment_weapon_beamspear.NPK");
			list.push_back("sprite_character_demoniclancer_equipment_weapon_javelin.NPK");
			list.push_back("sprite_character_demoniclancer_equipment_weapon_pike.NPK");
			list.push_back("sprite_character_demoniclancer_equipment_weapon_halberd.NPK");
			break;
		case ACHARACTER_GB:
			list.push_back("sprite_character_gunblader_equipment_weapon_coreswd.NPK");
			list.push_back("sprite_character_gunblader_equipment_weapon_lblade.NPK");
			list.push_back("sprite_character_gunblader_equipment_weapon_sblade.NPK");
			list.push_back("sprite_character_gunblader_equipment_weapon_mswd.NPK");
			break;
		}
		return list;
	}
};
