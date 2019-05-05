#include "StdAfx.h"
#include "DictAvatar.h"


DictAvatar::DictAvatar(void){
}
DictAvatar::~DictAvatar(void){
}
void DictAvatar::setFile(CString usingFileName){
	dictFileName = usingFileName;
}
void DictAvatar::loadDict(){
	for(int i = 0;i<ACAREER_MAXCOUNT;i++){
		std::vector<DictAvatarContent> t1;
		for(int j = 0;j<APART_MAXCOUNT;j++){
			DictAvatarContent d;
			d.clear();
			t1.push_back(d);
		}
		term.push_back(t1);
	}
	CString lineStr, tempStr[10];
	CStdioFile file;
	if(!file.Open(dictFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead))
		return;
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");

	while(file.ReadString(lineStr)){
		if(lineStr.Left(1) == L"["){
			if(!AfxExtractSubString(tempStr[1], lineStr, 1, ','))
				continue;
			AfxExtractSubString(tempStr[0], lineStr, 0, ',');
			avatarCareer ac = ACAREER_UD;
			avatarPart ap = APART_UD;
			if(tempStr[0] == L"[swordman"){
				ac = ACAREER_SM;
			}else if(tempStr[0] == L"[atswordman"){
				ac = ACAREER_SG;
			}else if(tempStr[0] == L"[fighter"){
				ac = ACAREER_FT;
			}else if(tempStr[0] == L"[atfighter"){
				ac = ACAREER_FM;
			}else if(tempStr[0] == L"[gunner"){
				ac = ACAREER_GN;
			}else if(tempStr[0] == L"[atgunner"){
				ac = ACAREER_GG;
			}else if(tempStr[0] == L"[mage"){
				ac = ACAREER_MG;
			}else if(tempStr[0] == L"[atmage"){
				ac = ACAREER_MM;
			}else if(tempStr[0] == L"[priest"){
				ac = ACAREER_PR;
			}else if(tempStr[0] == L"[atpriest"){
				ac = ACAREER_PG;
			}else if(tempStr[0] == L"[thief"){
				ac = ACAREER_TH;
			}else if(tempStr[0] == L"[knight"){
				ac = ACAREER_KN;
			}else if(tempStr[0] == L"[demoniclancer"){
				ac = ACAREER_DL;
			}else if(tempStr[0] == L"[gunblader"){
				ac = ACAREER_GB;
			}else{
				continue;
			}
			if(tempStr[1] == L"cap]"){
				ap = APART_CAP;
			}else if(tempStr[1] == L"hair]"){
				ap = APART_HAIR;
			}else if(tempStr[1] == L"face]"){
				ap = APART_FACE;
			}else if(tempStr[1] == L"neck]"){
				ap = APART_NECK;
			}else if(tempStr[1] == L"coat]"){
				ap = APART_COAT;
			}else if(tempStr[1] == L"pants]"){
				ap = APART_PANTS;
			}else if(tempStr[1] == L"belt]"){
				ap = APART_BELT;
			}else if(tempStr[1] == L"shoes]"){
				ap = APART_SHOES;
			}else if(tempStr[1] == L"body]"){
				ap = APART_BODY;
			}else{
				continue;
			}
			//导入内容
			while(file.ReadString(lineStr)){
				if(lineStr == L"[end]"){
					break;
				}
				if(!AfxExtractSubString(tempStr[3], lineStr, 3, ','))
					continue;
				AfxExtractSubString(tempStr[0], lineStr, 0, ',');
				AfxExtractSubString(tempStr[1], lineStr, 1, ',');
				AfxExtractSubString(tempStr[2], lineStr, 2, ',');

				DictAvatarTerm newTerm;
				//装扮名字
				newTerm.avatarName = tempStr[3];
				//装扮编号
				if(tempStr[1].Left(1) == L"T"){
					newTerm.isTN = true;
					tempStr[1] = tempStr[1].Right(tempStr[1].GetLength() - 1);
					newTerm.ID = _ttoi(tempStr[1]);
				}else{
					newTerm.isTN = false;
					newTerm.ID = _ttoi(tempStr[1]);
				}
				//装扮调色板编号
				newTerm.paletteID = _ttoi(tempStr[2]);
				//图标编号
				newTerm.iconID = _ttoi(tempStr[0]);
				term[ac][ap].push_back(newTerm);
			}
		}else{
			continue;
		}
	}
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();
}
void DictAvatar::saveDict(){
	CString careerName[15] = {L"",L"swordman",L"atswordman",L"fighter",L"atfighter",L"gunner",L"atgunner",L"mage",L"atmage",L"priest",L"atpriest",L"thief",L"knight",L"demoniclancer",L"gunblader"};
	CString partName[10] = {L"",L"cap",L"hair",L"face",L"neck",L"coat",L"pants",L"belt",L"shoes",L"body"};
	CStdioFile file;
	if(!file.Open(dictFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite))
		return;
	char *old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale(LC_CTYPE, "chs");
	for(int i = 1;i<ACAREER_MAXCOUNT;i++){
		for(int j = 1;j<APART_MAXCOUNT;j++){
			file.WriteString(L"["+careerName[i]+L","+partName[j]+L"]\n");
			for(int k = 0;k<term[i][j].size();k++){
				DictAvatarTerm newTerm = term[i][j][k];
				CString lineStr, tempStr;
				tempStr.Format(L"%d,", newTerm.iconID);
				lineStr = tempStr;
				lineStr += newTerm.isTN ? L"T" : L"";
				tempStr.Format(L"%d,", newTerm.ID);
				lineStr += tempStr;
				tempStr.Format(L"%d,", newTerm.paletteID);
				lineStr += tempStr;
				lineStr += newTerm.avatarName;
				file.WriteString(lineStr + L"\n");
			}
			file.WriteString(L"[end]\n");
		}
	}
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);
	file.Close();

}
void DictAvatar::insertTerm(avatarCareer ac, avatarPart ap, const DictAvatarTerm &newTerm){
	term[ac][ap].push_back(newTerm);
	saveDict();
}
void DictAvatar::deleteTerm(avatarCareer ac, avatarPart ap, int pos){
	term[ac][ap].erase(term[ac][ap].begin() + pos);
	saveDict();
}
void DictAvatar::modifiedTerm(avatarCareer ac, avatarPart ap, int pos, const DictAvatarTerm &newTerm){
	term[ac][ap][pos] = newTerm;
	saveDict();
}
std::vector<long> DictAvatar::findPos(avatarCareer ac, avatarPart ap, long iconID){
	std::vector<long> result;
	for(int i = 0;i<term[ac][ap].size();i++){
		if(term[ac][ap][i].iconID == iconID){
			result.push_back(i);
		}
	}
	return result;
}
std::vector<long> DictAvatar::findPos(avatarCareer ac, avatarPart ap, long ID, bool isTN, long paletteID){
	std::vector<long> result;
	for(int i = 0;i<term[ac][ap].size();i++){
		if(term[ac][ap][i].isTN == isTN && term[ac][ap][i].paletteID == paletteID && term[ac][ap][i].ID == ID){
			result.push_back(i);
		}
	}
	return result;
}
std::vector<long> DictAvatar::findPos(avatarCareer ac, avatarPart ap, CString avatarName){
	std::vector<long> result;
	for(int i = 0;i<term[ac][ap].size();i++){
		if(term[ac][ap][i].avatarName == avatarName){
			result.push_back(i);
		}
	}
	return result;
}
DictAvatarContent DictAvatar::findTerm(avatarCareer ac, avatarPart ap, long iconID){
	std::vector<long> result = findPos(ac, ap, iconID);
	DictAvatarContent list;
	for(int i = 0;i<result.size();i++){
		list.push_back(term[ac][ap][result[i]]);
	}
	return list;
}
DictAvatarContent DictAvatar::findTerm(avatarCareer ac, avatarPart ap, long ID, bool isTN, long paletteID){
	std::vector<long> result = findPos(ac, ap, ID, isTN, paletteID);
	DictAvatarContent list;
	for(int i = 0;i<result.size();i++){
		list.push_back(term[ac][ap][result[i]]);
	}
	return list;
}
DictAvatarContent DictAvatar::findTerm(avatarCareer ac, avatarPart ap, CString avatarName){
	std::vector<long> result = findPos(ac, ap, avatarName);
	DictAvatarContent list;
	for(int i = 0;i<result.size();i++){
		list.push_back(term[ac][ap][result[i]]);
	}
	return list;
}