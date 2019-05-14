#include "StdAfx.h"
#include "KoishiEx.h"

using namespace KoishiAvatar;


bool KoishiAvatar::isnum(Koishi::uchar chars){
	return chars >= '0' && chars <= '9';
}

str KoishiAvatar::shorten(const str &path){
	str path1,path2;
	str::size_type st;
	st = path.find_last_of('\\');
	if(st != str::npos){
		path1 = path.substr(st+1);
	}else{
		path1 = path;
	}
	st = path1.find_last_of('/');
	if(st != str::npos){
		path2 = path1.substr(st+1);
	}else{
		path2 = path1;
	}
	return path2;
}
str KoishiAvatar::imgAddV4Num(const str &imgName, long num){
	str newName = imgName;
	long i1 = num % 10;	//个位数
	long i2 = num / 10 % 10;	//十位数
	Koishi::uchar c1 = '0'+i1;
	Koishi::uchar c2 = '0'+i2;
	str::size_type pos = imgName.find_last_of('0');
	if(pos != str::npos){
		newName[pos] = c1;
		newName[pos-1] = c2;
	}
	return newName;
}


str KoishiAvatar::getAvatarIDString(int i){
	str s = "";
	if(i>9999){
		s.push_back('0'+i/10000);
	}
	s.push_back('0'+(i/1000)%10);
	s.push_back('0'+(i/100)%10);
	s.push_back('0'+(i/10)%10);
	s.push_back('0'+i%10);
	return s;
}
void KoishiAvatar::getMQData(int order, avatarPart &part, avatarLayer &layer){
	int mixSeqList[TOTAL_LAYER_COUNT][2] = {
		{APART_SHOES,	ALAYER_F},{APART_BELT,	ALAYER_F},{APART_PANTS,	ALAYER_F},{APART_COAT,	ALAYER_F},
		{APART_NECK,	ALAYER_F},{APART_FACE,	ALAYER_F},{APART_CAP,	ALAYER_F},{APART_FACE,	ALAYER_G},
		{APART_FACE,	ALAYER_A},{APART_WEAPON,ALAYER_C2},{APART_WEAPON,ALAYER_C1},{APART_WEAPON,	ALAYER_C},
		{APART_CAP,		ALAYER_C},{APART_HAIR,	ALAYER_C},{APART_NECK,	ALAYER_E},{APART_COAT,	ALAYER_C},
		{APART_NECK,	ALAYER_G},{APART_NECK,	ALAYER_C},{APART_WEAPON,ALAYER_A2},{APART_WEAPON,	ALAYER_A1},
		{APART_WEAPON,	ALAYER_A},{APART_CAP,	ALAYER_G},{APART_CAP,	ALAYER_A},{APART_HAIR,	ALAYER_A},
		{APART_NECK,	ALAYER_X},{APART_BELT,	ALAYER_G},{APART_BELT,	ALAYER_C},{APART_FACE,	ALAYER_C},
		{APART_NECK,	ALAYER_A},{APART_COAT,	ALAYER_G},{APART_COAT,	ALAYER_A},{APART_BELT,	ALAYER_A},
		{APART_SHOES,	ALAYER_C},{APART_PANTS,	ALAYER_G},{APART_PANTS,	ALAYER_A},{APART_SHOES,	ALAYER_G},
		{APART_SHOES,	ALAYER_A},{APART_PANTS,	ALAYER_B},{APART_SHOES,	ALAYER_H},{APART_SHOES,	ALAYER_B},
		{APART_PANTS,	ALAYER_H},{APART_PANTS,	ALAYER_D},{APART_BELT,	ALAYER_B},{APART_NECK,	ALAYER_B},
		{APART_COAT,	ALAYER_H},{APART_COAT,	ALAYER_B},{APART_BELT,	ALAYER_D},{APART_HAIR,	ALAYER_B},
		{APART_CAP,		ALAYER_H},{APART_CAP,	ALAYER_B},{APART_WEAPON,	ALAYER_B2},{APART_WEAPON,	ALAYER_B1},
		{APART_WEAPON,	ALAYER_B},{APART_NECK,	ALAYER_D},{APART_NECK,	ALAYER_H},{APART_COAT,	ALAYER_D},
		{APART_HAIR,	ALAYER_D},{APART_CAP,	ALAYER_D},{APART_WEAPON,	ALAYER_D2},{APART_WEAPON,	ALAYER_D1},
		{APART_WEAPON,	ALAYER_D},{APART_FACE,	ALAYER_B},{APART_NECK,	ALAYER_K},{APART_BODY,	ALAYER_UD}
	};
	if(order>TOTAL_LAYER_COUNT-1)
		order = TOTAL_LAYER_COUNT-1;
	part = (avatarPart)mixSeqList[order][0];
	layer = (avatarLayer)mixSeqList[order][1];
}
extern avatarPart KoishiAvatar::getMQPart(int order){
	avatarPart ap;
	avatarLayer al;
	getMQData(order, ap, al);
	return ap;
}
extern avatarLayer KoishiAvatar::getMQLayer(int order){
	avatarPart ap;
	avatarLayer al;
	getMQData(order, ap, al);
	return al;
}
extern str KoishiAvatar::getCareerNPKName(avatarCareer cr){
	str fix[15] = {"","swordman_","swordman_at","fighter_","fighter_at","gunner_","gunner_at","mage_","mage_at","priest_","priest_at","thief_","knight_","demoniclancer_","gunblader_"};
	return fix[cr];
}
extern str KoishiAvatar::getCareerIMGName(avatarCareer cr){
	str fix[15] = {"","sm_","sg_","ft_","fm_","gn_","gg_","mg_","mm_","pr_","pg_","th_","kn_","dl_","gb_"};
	return fix[cr];
}
extern str KoishiAvatar::getAvatarPartNPKName(avatarPart pt){
	str fix[10] = {"","cap","hair","face","neck","coat","pants","belt","shoes","skin"};
	return fix[pt];
}
extern str KoishiAvatar::getAvatarPartIMGName(avatarPart pt){
	str fix[10] = {"","cap","hair","face","neck","coat","pants","belt","shoes","body"};
	return fix[pt];
}
extern str KoishiAvatar::getAvatarLayerName(avatarLayer ly){
	str fix[28] = {"","a","a1","a2","b","b1","b2","c","c1","c2","d","d1","d2","e","e1","e2","f","f1","f2","g","g1","g2","h","h1","h2","x","x1","x2"};
	return fix[ly];
}
extern str KoishiAvatar::getAvatarNPKName(avatarCareer ch, avatarPart pt){
	str fix1 = "sprite_character_";
	str fix2 = "equipment_avatar_";
	str fix3 = ".NPK";
	return fix1 + getCareerNPKName(ch) + fix2 + getAvatarPartNPKName(pt) + fix3;
}
extern str KoishiAvatar::getAvatarIMGName(avatarCareer ch, avatarPart pt){
	return getCareerIMGName(ch) + getAvatarPartIMGName(pt);
}
extern str KoishiAvatar::getIconNPKName(avatarCareer cr){
	str fix[15] = {"","swordman","atswordman","fighter","atfighter","gunner","atgunner","mage","atmage","priest","atpriest","thief","knight","demoniclancer","gunblader"};
	return "sprite_item_avatar_"+fix[cr]+".NPK";
}
extern std::vector<str> KoishiAvatar::getIconIMGName(avatarCareer cr, avatarPart pt){
	std::vector<str> imgNameList;
	if(pt == APART_BODY){
		imgNameList.push_back(getCareerIMGName(cr) + "abody");
		imgNameList.push_back(getCareerIMGName(cr) + "atong");
	}else{
		imgNameList.push_back(getCareerIMGName(cr) + "a" + getAvatarPartIMGName(pt));
	}
	return imgNameList;
}
extern color KoishiAvatar::getCareerColor(avatarCareer cr){
	color clrList[15] = {
		color(0xFF, 0xFF, 0xFF, 0xFF),
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
	return clrList[cr];
}
extern point KoishiAvatar::getAvatarModelOffset(avatarCareer cr, avatarPart pt){
	point ptList[15][10] = {
		{point(0,0), point(0,0),point(0,0),point(0,0),point(0,0),point(0,0),point(0,0),point(0,0),point(0,0)},
		{point(0,0), point(0,-40),point(0,-30),point(0,-30),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,40),point(0,0)},
		{point(0,0), point(0,-40),point(0,-30),point(0,-30),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,40),point(0,0)},
		{point(0,0), point(0,-40),point(0,-30),point(0,-30),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,40),point(0,0)},
		{point(0,0), point(0,-40),point(0,-30),point(0,-30),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,40),point(0,0)},
		{point(0,0), point(0,-50),point(0,-40),point(0,-40),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,50),point(0,0)},
		{point(0,0), point(0,-40),point(0,-30),point(0,-30),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,40),point(0,0)},
		{point(0,0), point(0,-30),point(0,-30),point(0,-30),point(0,-10),point(0,-10),point(0,10),point(0,0),point(0,30),point(0,0)},
		{point(0,0), point(0,-30),point(0,-30),point(0,-30),point(0,-10),point(0,-10),point(0,10),point(0,0),point(0,30),point(0,0)},
		{point(0,0), point(-20,-50),point(-20,-40),point(-20,-40),point(-20,-20),point(-20,-10),point(-20,20),point(-20,0),point(-20,50),point(-20,0)},
		{point(0,0), point(0,-40),point(0,-30),point(0,-30),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,40),point(0,0)},
		{point(0,0), point(0,-40),point(0,-30),point(0,-30),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,40),point(0,0)},
		{point(0,0), point(5,-30),point(5,-30),point(5,-30),point(5,-10),point(5,-10),point(5,10),point(5,0),point(5,30),point(5,0)},
		{point(0,0), point(0,-50),point(0,-40),point(0,-40),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,50),point(0,0)},
		{point(0,0), point(0,-50),point(0,-40),point(0,-40),point(0,-20),point(0,-10),point(0,20),point(0,0),point(0,50),point(0,0)},
	};
	return ptList[cr][pt];
}
extern long KoishiAvatar::getCareerRepresentativeFrame(avatarCareer cr){
	long frameList[15] = {0, 176, 0, 113, 0, 0, 0, 12, 0, 150, 0, 0, 0, 0, 0};
	return frameList[cr];
}
extern bool KoishiAvatar::parseAvatarName(const str &avatarName, avatar &av, avatarLayer &al){
	str numstr = "";
	Koishi::uchar p, q;
	long i;
	av.isTN = !(avatarName.find("(tn)") == str::npos);
	if(avatarName.find("_mask1") != str::npos){
		return false;
	}
	if(avatarName.size() <= 5){
		return false;
	}
	i = avatarName.size()-5;
	p = avatarName[i-1];
	q = avatarName[i];
	al = ALAYER_UD;
	if(q == 'a'){
		al = ALAYER_A;
		i --;
	}
	if(q == 'b'){
		al = ALAYER_B;
		i --;
	}
	if(q == 'c'){
		al = ALAYER_C;
		i --;
	}
	if(q == 'd'){
		al = ALAYER_D;
		i --;
	}
	if(q == 'e'){
		al = ALAYER_E;
		i --;
	}
	if(q == 'f'){
		al = ALAYER_F;
		i --;
	}
	if(q == 'g'){
		al = ALAYER_G;
		i --;
	}
	if(q == 'h'){
		al = ALAYER_H;
		i --;
	}
	if(q == 'k'){
		al = ALAYER_K;
		i --;
	}
	if(q == 'x'){
		al = ALAYER_X;
		i --;
	}
	if(p == 'a' && q == '1'){
		al = ALAYER_A1;
		i -= 2;
	}
	if(p == 'b' && q == '1'){
		al = ALAYER_B1;
		i -= 2;
	}
	if(p == 'c' && q == '1'){
		al = ALAYER_C1;
		i -= 2;
	}
	if(p == 'd' && q == '1'){
		al = ALAYER_D1;
		i -= 2;
	}
	if(p == 'e' && q == '1'){
		al = ALAYER_E1;
		i -= 2;
	}
	if(p == 'f' && q == '1'){
		al = ALAYER_F1;
		i -= 2;
	}
	if(p == 'g' && q == '1'){
		al = ALAYER_G1;
		i -= 2;
	}
	if(p == 'h' && q == '1'){
		al = ALAYER_H1;
		i -= 2;
	}
	if(p == 'k' && q == '1'){
		al = ALAYER_K1;
		i -= 2;
	}
	if(p == 'x' && q == '1'){
		al = ALAYER_X2;
		i -= 2;
	}
	if(p == 'a' && q == '2'){
		al = ALAYER_A2;
		i -= 2;
	}
	if(p == 'b' && q == '2'){
		al = ALAYER_B2;
		i -= 2;
	}
	if(p == 'c' && q == '2'){
		al = ALAYER_C2;
		i -= 2;
	}
	if(p == 'd' && q == '2'){
		al = ALAYER_D2;
		i -= 2;
	}
	if(p == 'e' && q == '2'){
		al = ALAYER_E2;
		i -= 2;
	}
	if(p == 'f' && q == '2'){
		al = ALAYER_F2;
		i -= 2;
	}
	if(p == 'g' && q == '2'){
		al = ALAYER_G2;
		i -= 2;
	}
	if(p == 'h' && q == '2'){
		al = ALAYER_H2;
		i -= 2;
	}
	if(p == 'k' && q == '2'){
		al = ALAYER_K2;
		i -= 2;
	}
	if(p == 'x' && q == '2'){
		al = ALAYER_X2;
		i -= 2;
	}
	while(isnum(p = avatarName[i--])){
		numstr.push_back(p);
	}
	if(numstr.length() == 0)
		return false;
	std::reverse(numstr.begin(), numstr.end());
	av.ID = std::stoi(numstr);
	if(avatarName.find("coat") != str::npos){
		av.part = APART_COAT;
	}else if(avatarName.find("pants") != str::npos){
		av.part = APART_PANTS; 
	}else if(avatarName.find("cap") != str::npos){
		av.part = APART_CAP;
	}else if(avatarName.find("hair") != str::npos){
		av.part = APART_HAIR;
	}else if(avatarName.find("face") != str::npos){
		av.part = APART_FACE;
	}else if(avatarName.find("neck") != str::npos){
		av.part = APART_NECK;
	}else if(avatarName.find("shoes") != str::npos){
		av.part = APART_SHOES;
	}else if(avatarName.find("belt") != str::npos){
		av.part = APART_BELT;
	}else if(avatarName.find("body") != str::npos){
		av.part = APART_BODY;
	}else{
		return false;
	}
	if(avatarName.find("sm_") != str::npos){
		av.carrer = ACAREER_SM;
	}else if(avatarName.find("sg_") != str::npos){
		av.carrer = ACAREER_SG; 
	}else if(avatarName.find("ft_") != str::npos){
		av.carrer = ACAREER_FT;
	}else if(avatarName.find("fm_") != str::npos){
		av.carrer = ACAREER_FM;
	}else if(avatarName.find("gn_") != str::npos){
		av.carrer = ACAREER_GN;
	}else if(avatarName.find("gg_") != str::npos){
		av.carrer = ACAREER_GG;
	}else if(avatarName.find("mg_") != str::npos){
		av.carrer = ACAREER_MG;
	}else if(avatarName.find("mm_") != str::npos){
		av.carrer = ACAREER_MM;
	}else if(avatarName.find("pr_") != str::npos){
		av.carrer = ACAREER_PR;
	}else if(avatarName.find("pg_") != str::npos){
		av.carrer = ACAREER_PG;
	}else if(avatarName.find("th_") != str::npos){
		av.carrer = ACAREER_TH;
	}else if(avatarName.find("kn_") != str::npos){
		av.carrer = ACAREER_KN;
	}else if(avatarName.find("dl_") != str::npos){
		av.carrer = ACAREER_DL;
	}else if(avatarName.find("gb_") != str::npos){
		av.carrer = ACAREER_GB;
	}else{
		return false;
	}
	return true;
}
extern str KoishiAvatar::makeAvatarName(avatar av, avatarLayer al){
	str output = "";
	if(av.isTN){
		output += "(tn)";
	}
	output += getCareerIMGName(av.carrer);
	output += getAvatarPartIMGName(av.part);
	output += getAvatarIDString(av.ID);
	output += getAvatarLayerName(al);
	return output;
}
avatar::avatar(){
	carrer = ACAREER_UD;
	part = APART_UD;
	ID = -1;
	isTN = false;
	v6palette = 0;
	for(int i=0;i<ALAYER_MAXCOUNT;i++){
		layer[i] = false;
	}
}
avatarAlbum::avatarAlbum(){
	valid = false;
	selected = 0;
	selectedPalette = 0;
	selectedFrame = 0;
}
void avatarAlbum::clear(){
	avatarList.clear();
	avatarPos.clear();
	sourceNPK.release();
	avatarPosAtBigramList.clear();
	bigramList.clear();
	for(int i=0;i<ALAYER_MAXCOUNT;i++){
		layerIMG[i].release();
		layerIMGpath[i] = "";
		layerIMGpos[i] = -1;
		layerMatrix[i].destory();
		selected = 0;
		selectedPalette = 0;
		selectedFrame = 0;
	}
	valid = false;
}
bool avatarAlbum::loadNPK(){
	str fileName = resoucePath + ::getAvatarNPKName(career, part);
	sourceNPK.release();
	if(!sourceNPK.loadFile(fileName)){
		valid = false;
		return false;
	}
	//更新列表
	for(int i = 0;i<sourceNPK.count;i++){
		avatar av;
		avatarLayer layer;
		if(!::parseAvatarName(shorten(sourceNPK.content[i].imgname), av, layer))
			continue;
		bool isNew = true;
		for(int j = 0;j<avatarList.size();j++){
			if(avatarList[j].ID == av.ID && avatarList[j].isTN == av.isTN){
				avatarList[j].layer[layer] = true;
				avatarPos[j][layer] = i;
				isNew = false;
				break;
			}
		}
		if(isNew){
			av.layer[layer] = true;
			av.v6palette = sourceNPK.getPaletteCount(i);
			std::vector<long> newi;
			for(long j =0;j<ALAYER_MAXCOUNT;j++)
				newi.push_back(-1);
			newi[layer] = i;
			avatarPos.push_back(newi);
			avatarList.push_back(av);
			/////////////////////////////////////
			std::vector<long> newAvatarPosByBigram;
			avatarBigram bigram;
			bigram.ID = av.ID;
			bigram.isTN = av.isTN;
			bigram.originPos = avatarList.size() - 1;
			if(av.v6palette == 0){
				bigram.paletteID = 0;
				bigramList.push_back(bigram);
				newAvatarPosByBigram.push_back(bigramList.size() - 1);
			}else{
				for(int j = 0;j<av.v6palette;j++){
					bigram.paletteID = j;
					bigramList.push_back(bigram);
					newAvatarPosByBigram.push_back(bigramList.size() - 1);
				}
			}
			avatarPosAtBigramList.push_back(newAvatarPosByBigram);
		}
	}
	valid = true;
	if(part == APART_BODY || part == APART_COAT || part == APART_PANTS || part == APART_HAIR || part == APART_SHOES){
		changeIMGByID(0);
	}else{
		changeIMG(-1);
	}
	return true;
}
bool avatarAlbum::changeIMG(long newSelect){
	if(newSelect >= (long)avatarList.size() || newSelect < -1)
		return false;
	selected = newSelect;
	selectedPalette = 0;
	for(int i = 0;i<ALAYER_MAXCOUNT;i++){
		if(selected == -1){
			layerIMGpos[i] = -1;
			layerIMG[i].release();
			layerIMGpath[i] = "";
		}else{
			layerIMGpos[i] = avatarPos[selected][i];
			layerIMG[i].release();
			layerIMGpath[i] = "";
			if(avatarPos[selected][i] != -1){
				sourceNPK.IMGextract(avatarPos[selected][i], layerIMG[i]);
				layerIMGpath[i] = sourceNPK.content[avatarPos[selected][i]].imgname;
			}
		}
	}
	updateMatrix();
	return true;
}
bool avatarAlbum::changeIMGByID(long avatarID, bool isTN){
	for(int i = 0;i<avatarList.size();i++){
		if(avatarList[i].ID == avatarID && avatarList[i].isTN == isTN){
			changeIMG(i);
			updateMatrix();
			return true;
		}
		if(avatarList[i].ID == avatarID /100 * 100 && avatarList[i].v6palette > (avatarID % 100) && avatarList[i].isTN == isTN){
			changeIMG(i);
			selectedPalette = avatarID % 100;
			updateMatrix();
			return true;
		}
	}
	return false;
}
long avatarAlbum::findPosByID(long avatarID, bool isTN){
	for(int i = 0;i<avatarList.size();i++){
		if(avatarList[i].ID == avatarID && avatarList[i].isTN == isTN){
			return i;
		}
		if(avatarList[i].ID == avatarID /100 * 100 && avatarList[i].v6palette > (avatarID % 100) && avatarList[i].isTN == isTN){
			return i;
		}
	}
	return -1;
}
bool avatarAlbum::changePalette(long paletteID){
	if(selected == -1)
		return false;
	if(paletteID >= avatarList[selected].v6palette)
		return false;
	selectedPalette = paletteID;
	updateMatrix();
	return true;
}
bool avatarAlbum::changeFrame(long frame){
	selectedFrame = frame;
	updateMatrix();
	return true;
}
bool avatarAlbum::updateMatrix(){
	for(int i = 0;i<ALAYER_MAXCOUNT;i++){
		layerMatrix[i].destory();
		getMatrix((avatarLayer)i, layerMatrix[i]);
	}
	return true;
}
bool avatarAlbum::getBasePoint(avatarLayer al, point &pt){
	if(layerIMGpos[al] == -1)
		return false;
	if(selectedFrame >= layerIMG[al].indexCount)
		return false;
	PICinfo pi;
	layerIMG[al].PICgetInfo(layerIMG[al].linkFind(selectedFrame), pi);
	pt = pi.basePt;
	return true;
}
bool avatarAlbum::getMatrix(avatarLayer al, matrix &mat){
	if(layerIMGpos[al] == -1)
		return false;
	if(selectedFrame >= layerIMG[al].indexCount)
		return false;
	return layerIMG[al].PICextract(selectedFrame, mat, selectedPalette);
}
///////////////////////////////////////////////
void avatarFactory::clear(){
	for(int i = 0;i<APART_MAXCOUNT;i++){
		partAlbum[i].clear();
	}
}
void avatarFactory::setPath(str pathStr){
	resoucePath = pathStr;
	for(int i = 0;i<APART_MAXCOUNT;i++){
		partAlbum[i].resoucePath = pathStr;
	}
}
void avatarFactory::setCarrer(avatarCareer ac){
	career = ac;
	for(int i = 0;i<APART_MAXCOUNT;i++){
		partAlbum[i].career = ac;
	}
}
bool avatarFactory::loadNPK(avatarPart ap){
	partAlbum[ap].part = ap;
	return partAlbum[ap].loadNPK();
}
bool avatarFactory::changeFrame(int newFrame){
	for(int i = 0;i<APART_MAXCOUNT;i++){
		partAlbum[i].changeFrame(newFrame);
	}
	return true;
}
bool avatarFactory::changeIMG(avatarPart ap, long selected){
	return partAlbum[ap].changeIMG(selected);
}
long avatarFactory::changeIMGByID(avatarPart ap, long ID, bool isTN){
	return partAlbum[ap].changeIMGByID(ID, isTN);
}

void avatarFactory::makeNPK(NPKobject &no){
	no.release();
	no.create();
	for(int i = 0;i<TOTAL_LAYER_COUNT;i++){
		avatarPart ap;
		avatarLayer al;
		::getMQData(TOTAL_LAYER_COUNT - 1 - i, ap, al);
		if(ap == APART_WEAPON)
			continue;
		if(partAlbum[ap].layerIMGpos[al] == -1)
			continue;
		no.IMGpush(partAlbum[ap].layerIMG[al], partAlbum[ap].layerIMGpath[al]);
	}
}
void avatarFactory::updateMatrix(avatarPart ap){
	partAlbum[ap].updateMatrix();
}
void avatarFactory::makeMatrix(point leftTopPos, size displaySize, matrix &mat){
	mat.create(displaySize);
	for(int i = 0;i<TOTAL_LAYER_COUNT;i++){
		avatarPart ap;
		avatarLayer al;
		::getMQData(TOTAL_LAYER_COUNT - 1 -i, ap, al);
		if(ap == APART_WEAPON)
			continue;
		if(partAlbum[ap].layerIMGpos[al] == -1)
			continue;
		point basePt;
		partAlbum[ap].getBasePoint(al, basePt);
		mat.putFore(partAlbum[ap].layerMatrix[al], LAY, basePt - leftTopPos);
	}
}
void avatarFactory::makeModel(matrix &outputMat, color baseColor, size modelSize, avatarPart ap, int selected, int paletteID, point offsetPos, int frame, PICinfo *ptrModelPI, matrix *ptrModelMat){
	long w = MAX(10, modelSize.W);
	long h = MAX(30, modelSize.H);
	outputMat.create(h, w);
	uchar r = baseColor.R;
	uchar g = baseColor.G;
	uchar b = baseColor.B;
	color color1 = color(0xFF-((0xFF-r)>>1), 0xFF-((0xFF-g)>>1), 0xFF-((0xFF-b)>>1));
	color color2 = baseColor;
	color color3 = color(r>>1, g>>1, b>>1);
	outputMat.fill(baseColor);
	outputMat.line(point(0,0), point(0, h-1), color1);
	outputMat.line(point(0,0), point(w-1, 0), color1);
	outputMat.line(point(1,1), point(1, h-2), color1);
	outputMat.line(point(1,1), point(w-2, 1), color1);
	outputMat.line(point(w-1,h-1), point(0, h-1), color3);
	outputMat.line(point(w-1,h-1), point(w-1, 0), color3);
	outputMat.line(point(w-2,h-2), point(1, h-2), color3);
	outputMat.line(point(w-2,h-2), point(w-2, 1), color3);
	outputMat.line(point(3,3), point(3, h-24), color3);
	outputMat.line(point(3,3), point(w-4, 3), color3);
	outputMat.line(point(w-4,h-24), point(3, h-24), color1);
	outputMat.line(point(w-4,h-24), point(w-4, 3), color1);

	matrix strMat;
	if(selected >= 0){
		KoishiExpand::KoishiMarkTool::StrMatLarge(KoishiAvatar::getAvatarIDString(partAlbum[ap].avatarList[selected].ID + paletteID), strMat);
	}else{
		KoishiExpand::KoishiMarkTool::StrMatLarge("NA", strMat);
	}
	outputMat.putFore(strMat, LAY, point(w/2-strMat.getWidth()/2, h-12-strMat.getHeight()/2));

	matrix dispMat1;
	dispMat1.create(h-28,w-8);
	matrix dispMat;
	IMGobject dispIO;
	PICinfo dispPI;
	point bodyDeltaPoint, bodyBasePoint;

	bodyDeltaPoint = point((modelSize.W - ptrModelPI->picSize.W) / 2, (modelSize.H - ptrModelPI->picSize.H) / 2) - offsetPos;
	bodyBasePoint = ptrModelPI->basePt;
	dispMat1.putFore(*ptrModelMat, LAY, bodyDeltaPoint);
	if(selected < 0)
		return;
	for(int i = 0;i<partAlbum[ap].avatarPos[selected].size();i++){
		if(partAlbum[ap].avatarPos[selected][i] == -1)
			continue;
		if(!partAlbum[ap].sourceNPK.IMGextract(partAlbum[ap].avatarPos[selected][i], dispIO))
			continue;
		if(!dispIO.PICgetInfo(dispIO.linkFind(frame), dispPI))
			continue;
		if(!dispIO.PICextract(frame, dispMat, paletteID))
			continue;
		dispMat1.putFore(dispMat, LAY, bodyDeltaPoint-bodyBasePoint+dispPI.basePt);
		dispIO.release();
		dispMat.destory();
	}
	outputMat.putFore(dispMat1, LAY, point(4,4));
}
void avatarFactory::makeButton(matrix &outputMat, color baseColor, size modelSize, int iconCtrl){
	long w = MAX(10, modelSize.W);
	long h = MAX(30, modelSize.H);
	outputMat.create(h, w);
	uchar r = baseColor.R;
	uchar g = baseColor.G;
	uchar b = baseColor.B;
	color color1 = color(0xFF-((0xFF-r)>>1), 0xFF-((0xFF-g)>>1), 0xFF-((0xFF-b)>>1));
	color color2 = baseColor;
	color color3 = color(r>>1, g>>1, b>>1);
	outputMat.fill(baseColor);
	outputMat.line(point(0,0), point(0, h-1), color1);
	outputMat.line(point(0,0), point(w-1, 0), color1);
	outputMat.line(point(1,1), point(1, h-2), color1);
	outputMat.line(point(1,1), point(w-2, 1), color1);
	outputMat.line(point(w-1,h-1), point(0, h-1), color3);
	outputMat.line(point(w-1,h-1), point(w-1, 0), color3);
	outputMat.line(point(w-2,h-2), point(1, h-2), color3);
	outputMat.line(point(w-2,h-2), point(w-2, 1), color3);
	point centerPoint = point(w/2, h/2);
	switch(iconCtrl){
	case 0:
		outputMat.line(centerPoint + point(0, -6), centerPoint + point(0, 7), color3);
		outputMat.line(centerPoint + point(1, -5), centerPoint + point(1, 7), color3);
		outputMat.line(centerPoint + point(2, -4), centerPoint + point(2, 7), color3);
		outputMat.line(centerPoint + point(3, -3), centerPoint + point(3, 7), color3);
		outputMat.line(centerPoint + point(4, -2), centerPoint + point(4, 0), color3);
		outputMat.line(centerPoint + point(5, -1), centerPoint + point(5, 0), color3);
		outputMat.line(centerPoint + point(6, 0), centerPoint + point(6, 0), color3);
		outputMat.line(centerPoint + point(-1, -5), centerPoint + point(-1, 7), color3);
		outputMat.line(centerPoint + point(-2, -4), centerPoint + point(-2, 7), color3);
		outputMat.line(centerPoint + point(-3, -3), centerPoint + point(-3, 7), color3);
		outputMat.line(centerPoint + point(-4, -2), centerPoint + point(-4, 0), color3);
		outputMat.line(centerPoint + point(-5, -1), centerPoint + point(-5, 0), color3);
		outputMat.line(centerPoint + point(-6, 0), centerPoint + point(-6, 0), color3);
		break;
	case 1:
		outputMat.line(centerPoint + point(0, -7), centerPoint + point(0, 6), color3);
		outputMat.line(centerPoint + point(1, -7), centerPoint + point(1, 5), color3);
		outputMat.line(centerPoint + point(2, -7), centerPoint + point(2, 4), color3);
		outputMat.line(centerPoint + point(3, -7), centerPoint + point(3, 3), color3);
		outputMat.line(centerPoint + point(4, 0), centerPoint + point(4, 2), color3);
		outputMat.line(centerPoint + point(5, 0), centerPoint + point(5, 1), color3);
		outputMat.line(centerPoint + point(6, 0), centerPoint + point(6, 0), color3);
		outputMat.line(centerPoint + point(-1, -7), centerPoint + point(-1, 5), color3);
		outputMat.line(centerPoint + point(-2, -7), centerPoint + point(-2, 4), color3);
		outputMat.line(centerPoint + point(-3, -7), centerPoint + point(-3, 3), color3);
		outputMat.line(centerPoint + point(-4, 0), centerPoint + point(-4, 2), color3);
		outputMat.line(centerPoint + point(-5, 0), centerPoint + point(-5, 1), color3);
		outputMat.line(centerPoint + point(-6, 0), centerPoint + point(-6, 0), color3);
		break;
	case 2:
		outputMat.line(centerPoint + point(-7, -7), centerPoint + point(7, 7), color3);
		outputMat.line(centerPoint + point(-7, -6), centerPoint + point(6, 7), color3);
		outputMat.line(centerPoint + point(-7, -5), centerPoint + point(5, 7), color3);
		outputMat.line(centerPoint + point(-7, -4), centerPoint + point(4, 7), color3);
		outputMat.line(centerPoint + point(-6, -7), centerPoint + point(7, 6), color3);
		outputMat.line(centerPoint + point(-5, -7), centerPoint + point(7, 5), color3);
		outputMat.line(centerPoint + point(-4, -7), centerPoint + point(7, 4), color3);
		outputMat.line(centerPoint + point(-7, 7), centerPoint + point(7, -7), color3);
		outputMat.line(centerPoint + point(-7, 6), centerPoint + point(6, -7), color3);
		outputMat.line(centerPoint + point(-7, 5), centerPoint + point(5, -7), color3);
		outputMat.line(centerPoint + point(-7, 4), centerPoint + point(4, -7), color3);
		outputMat.line(centerPoint + point(-6, 7), centerPoint + point(7, -6), color3);
		outputMat.line(centerPoint + point(-5, 7), centerPoint + point(7, -5), color3);
		outputMat.line(centerPoint + point(-4, 7), centerPoint + point(7, -4), color3);
		break;
	case 3:
		outputMat.line(centerPoint + point(3, -4), centerPoint + point(3, -4), color3);
		outputMat.line(centerPoint + point(2, -3), centerPoint + point(2, -5), color3);
		outputMat.line(centerPoint + point(1, -2), centerPoint + point(1, -6), color3);
		outputMat.line(centerPoint + point(0, -1), centerPoint + point(0, -7), color3);
		outputMat.line(centerPoint + point(-1, 0), centerPoint + point(-1, -8), color3);
		outputMat.line(centerPoint + point(-2, -2), centerPoint + point(-2, -6), color3);
		outputMat.line(centerPoint + point(-7, 2), centerPoint + point(-7, -2), color3);
		outputMat.line(centerPoint + point(-6, 4), centerPoint + point(-6, -4), color3);
		outputMat.line(centerPoint + point(-5, 5), centerPoint + point(-5, -5), color3);
		outputMat.line(centerPoint + point(-4, 6), centerPoint + point(-4, -6), color3);
		outputMat.line(centerPoint + point(-3, 6), centerPoint + point(-3, -6), color3);
		outputMat.line(centerPoint + point(-2, 7), centerPoint + point(-2, 2), color3);
		outputMat.line(centerPoint + point(-1, 7), centerPoint + point(-1, 3), color3);
		outputMat.line(centerPoint + point(0, 7), centerPoint + point(0, 3), color3);
		outputMat.line(centerPoint + point(1, 7), centerPoint + point(1, 3), color3);
		outputMat.line(centerPoint + point(2, 7), centerPoint + point(2, 2), color3);
		outputMat.line(centerPoint + point(3, 6), centerPoint + point(3, -1), color3);
		outputMat.line(centerPoint + point(4, 6), centerPoint + point(4, -1), color3);
		outputMat.line(centerPoint + point(5, 5), centerPoint + point(5, -1), color3);
		outputMat.line(centerPoint + point(6, 4), centerPoint + point(6, -1), color3);
		outputMat.line(centerPoint + point(7, 2), centerPoint + point(7, -1), color3);
		break;
	}
}