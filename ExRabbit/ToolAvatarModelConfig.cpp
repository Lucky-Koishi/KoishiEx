#include "StdAfx.h"
#include "ToolAvatarModelConfig.h"

extern CString avatarCString[APART_MAXCOUNT];
extern CString weaponCString[AWEAPON_MAXCOUNT];
extern CString careerName[ACHARACTER_MAXCOUNT];
extern CString weaponIconClassified[ACHARACTER_MAXCOUNT][WEAPON_MAXCOUNT_PER_CHAR];

ToolAvatarModelConfig::ToolAvatarModelConfig(void){
	defaultConfig();
}


void ToolAvatarModelConfig::load(const CString &filePath){
	CStdioFile file;
	if(!file.Open(filePath + L"模型生成设置.txt", CFile::modeRead)){
		defaultConfig();
		save(filePath);
	}else{
		char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
		setlocale(LC_CTYPE, "chs");
		CString lineStr;
		for(int a = 0;a < ACHARACTER_MAXCOUNT; a++){
			file.ReadString(lineStr);
			CString clrStr, rStr, gStr, bStr;
			AfxExtractSubString(clrStr, lineStr, 1, ':');
			modelBackColor[a].R = B16CStrToNum(clrStr.Left(2));
			modelBackColor[a].G = B16CStrToNum(clrStr.Mid(2, 2));
			modelBackColor[a].B = B16CStrToNum(clrStr.Right(2));
			for(int b = 0;b<APART_MAXCOUNT;b++){
				file.ReadString(lineStr);
				CString mString, subString;
				AfxExtractSubString(mString, lineStr, 1, ':');
				AfxExtractSubString(subString, mString, 0, ',');
				subString = subString.Right(subString.GetLength()-1);
				modelAvatarOffset[a][b].X = _ttoi(subString);
				AfxExtractSubString(subString, mString, 1, ',');
				subString = subString.Left(subString.GetLength()-1);
				modelAvatarOffset[a][b].Y = _ttoi(subString);
				AfxExtractSubString(subString, mString, 2, ',');
				modelAvatarFrame[a][b] = _ttoi(subString);
			}
			file.ReadString(lineStr);
			CString mString, subString;
			AfxExtractSubString(mString, lineStr, 1, ':');
			AfxExtractSubString(subString, mString, 0, ',');
			subString = subString.Right(subString.GetLength()-1);
			modelWeaponOffset[a].X = _ttoi(subString);
			AfxExtractSubString(subString, mString, 1, ',');
			subString = subString.Left(subString.GetLength()-1);
			modelWeaponOffset[a].Y = _ttoi(subString);
			AfxExtractSubString(subString, mString, 2, ',');
			modelWeaponFrame[a] = _ttoi(subString);
			file.WriteString(L"武器:");
		}
		setlocale(LC_CTYPE, old_locale);
		free(old_locale);
		file.Close();
	}
}
void ToolAvatarModelConfig::save(const CString &filePath){
	CStdioFile file;
	file.Open(filePath + L"模型生成设置.txt", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	for(int a = 0;a < ACHARACTER_MAXCOUNT; a++){
		file.WriteString(careerName[a] + L":" + ClrToCStr(modelBackColor[a]).Left(6) +L"\n");
		for(int b = 0;b<APART_MAXCOUNT;b++){
			file.WriteString(avatarCString[b]+L":");
			file.WriteString(L"(" + NumToCStr(modelAvatarOffset[a][b].X) + L"," + NumToCStr(modelAvatarOffset[a][b].Y)  +L")");
			file.WriteString(L"," + NumToCStr(modelAvatarFrame[a][b]) + L"\n");
		}
		file.WriteString(L"武器:");
		file.WriteString(L"(" + NumToCStr(modelWeaponOffset[a].X) + L"," + NumToCStr(modelWeaponOffset[a].Y)  +L")");
		file.WriteString(L"," + NumToCStr(modelWeaponFrame[a]) + L"\n");
	}
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
}

void ToolAvatarModelConfig::defaultConfig(){
	memset(this, 0, sizeof(*this));
	long FL[ACHARACTER_MAXCOUNT] = {
		176, 0, 113, 0, 0, 0, 12, 0, 150, 0, 0, 0, 0, 0
	};
	long XL[ACHARACTER_MAXCOUNT] = {
		0, 0, 0, 0, 0, 0, 0, 0, -15, 0, 0, 5, 0, 5
	};
	long WFL[ACHARACTER_MAXCOUNT] = {
		75, 96, 0, 0, 25, 23, 12, 12, 182, 136, 6, 137, 43, 0
	};
	long WXL[ACHARACTER_MAXCOUNT] = {
		-10, -50, 15, -20, 55, 55, -20, -20, -10, -25, 25, 40, 40, 5
	};
	long WYL[ACHARACTER_MAXCOUNT] = {
		-5, 10, 15, 0, -50, -50, -45, -55, -10, 0, -60, -15, 20, 25
	};
	long YL[ACHARACTER_MAXCOUNT][APART_MAXCOUNT] = {
		{
			-55, -45, -45, -25, -25, 5, 0, 40, 0
		},{
			-50, -30, -40, -25, -20, 5, 0, 40, 0
		},{
			-40, -35, -35, -20, -15, 5, 0, 35, 0
		},{
			-50, -45, -40, -25, -25, 5, 0, 40, 0
		},{
			-50, -50, -50, -40, -30, 5, -10, 55, 0
		},{
			-50, -50, -50, -35, -25, -5, 0, 45, 0
		},{
			-45, -30, -30, -25, -20, 5, 0, 30, 0
		},{
			-45, -35, -30, -25, -20, 5, 0, 30, 0
		},{
			-60, -50, -50, -35, -30, 10, 0, 50, 0
		},{
			-55, -50, -50, -35, -15, 5, -10, 35, 0
		},{
			-50, -50, -45, -25, -25, 5, 0, 40, 0
		},{
			-50, -40, -35, -15, -15, 5, 0, 30, 0
		},{
			-55, -45, -45, -30, -25, 5, 0, 40, 0
		},{
			-50, -50, -50, -20, -30, 10, -5, 50, 0
		}
	};
	for(int ac = 0;ac<ACHARACTER_MAXCOUNT;ac++){
		for(int ap = 0;ap<APART_MAXCOUNT;ap++){
			modelAvatarOffset[ac][ap] = point(XL[ac], YL[ac][ap]);
			modelAvatarFrame[ac][ap] = FL[ac];
		}
		modelWeaponOffset[ac] = point(WXL[ac], WYL[ac]);
		modelWeaponFrame[ac] = WFL[ac];
	}
	//////////////
	modelBackColor[0] = color(0xFF, 0x00, 0xCC, 0xFF);
	modelBackColor[1] = color(0xFF, 0xCC, 0x55, 0x88);
	modelBackColor[2] = color(0xFF, 0xFF, 0x99, 0x66);
	modelBackColor[3] = color(0xFF, 0xFF, 0xEE, 0x99);
	modelBackColor[4] = color(0xFF, 0xCC, 0x99, 0xEE);
	modelBackColor[5] = color(0xFF, 0x99, 0xFF, 0xFF);
	modelBackColor[6] = color(0xFF, 0xFF, 0xCC, 0xFF);
	modelBackColor[7] = color(0xFF, 0xCC, 0xCC, 0xFF);
	modelBackColor[8] = color(0xFF, 0xCC, 0xCC, 0xCC);
	modelBackColor[9] = color(0xFF, 0xFF, 0xFF, 0xCC);
	modelBackColor[10] = color(0xFF, 0xDD, 0x99, 0xEE);
	modelBackColor[11] = color(0xFF, 0x99, 0xFF, 0x66);
	modelBackColor[12] = color(0xFF, 0x77, 0x77, 0xFF);
	modelBackColor[13] = color(0xFF, 0xDD, 0xCC, 0x88);
};
