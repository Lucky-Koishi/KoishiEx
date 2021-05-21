#include "stdafx.h"
#include "Music.h"

//相邻半音频率比
double HALF_NOTE_GAP = 1.05946309436;
//频率比的幂
double rateTableUp[12] = {
	1,
	1.05946309436,
	1.12246204831,
	1.18920711501,
	1.25992104990,
	1.33483985417,
	1.41421356238,
	1.49830707688,
	1.58740105198,
	1.68179283052,
	1.78179743629,
	1.88774862538
};
//频率比的负数次幂
double rateTableDown[12] = {
	1,
	0.94387431268,
	0.89089871814,
	0.84089641525,
	0.79370052598,
	0.74915353844,
	0.70710678118,
	0.66741992708,
	0.62996052494,
	0.59460355750,
	0.56123102415,
	0.52973154718
};

Note::Note() {
	base = 0;
	sharp = 0;
	degree = 0;
}
Note::Note(CString rString) {
	parse(rString);
}
Note::Note(int nBase) {
	base = 0;
	if(nBase >= 0 && nBase <= 7)
		base = nBase;
	sharp = 0;
	degree = 0;
}
Note::Note(int nBase, int nSharp, int nDegree) {
	if(nBase >= 0 && nBase <= 7) {
		base = nBase;
		sharp = nSharp;
		degree = nDegree;
		standard();
	} else {
		base = 0;
		sharp = 0;
		degree = 0;
	}
}
void Note::parse(CString rString) {
	base = 0;
	sharp = 0;
	degree = 0;
	for(int i = 0; i < rString.GetLength(); i++) {
		char p = rString.GetAt(i);
		if(p == '0') {
			base = 0;
			sharp = 0;
			degree = 0;
			return;
		} else if(p >= '1' && p <= '7') {
			base = p - '0';
		} else if(p == '+') {
			degree++;
		} else if(p == '-') {
			degree--;
		} else if(p == '#') {
			sharp++;
		} else if(p == 'b') {
			sharp--;
		}
	}
	standard();
}
void Note::standard() {
	if(base == 0)
		return;
	int baseStep[7] = {0, 2, 4, 5, 7, 9, 11};
	int baseList[12] = {1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7};
	int sharpList[12] = {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0};
	int step = baseStep[base - 1] + sharp + 12 * degree;
	if(step >= 0) {
		degree = step / 12;
		int bs = step % 12;
		base = baseList[bs];
		sharp = sharpList[bs];
	} else {
		degree = -(-step - 1) / 12 - 1;
		int bs = 11 - ((-step - 1) % 12);
		base = baseList[bs];
		sharp = sharpList[bs];
	}
}
double Note::rate() const {
	if(base == 0)
		return 0.f;
	int baseStep[7] = {0, 2, 4, 5, 7, 9, 11};
	int step = baseStep[base - 1] + sharp + 12 * degree;
	if(step < 12 && step >= 0) {
		return rateTableUp[step];
	} else if(step >= 12) {
		double dRate = 1.f;
		while(step >= 12) {
			dRate *= 2;
			step -= 12;
		}
		return dRate * rateTableUp[step];
	} else if(step > -12 && step <= 0) {
		return rateTableDown[-step];
	} else {
		double dRate = 1.f;
		while(step <= -12) {
			dRate *= .5f;
			step += 12;
		}
		return dRate * rateTableDown[-step];
	}
	return 0.f;
}
CString Note::toString()const {
	CString baseStr;
	uchar baseChar = '0' + base;
	baseStr += baseChar;
	if(sharp > 0) {
		for(int i = 0; i < sharp; i++) {
			baseStr = L"#" + baseStr;
		}
	} else {
		for(int i = 0; i < -sharp; i++) {
			baseStr = L"b" + baseStr;
		}
	}
	if(degree > 0) {
		for(int i = 0; i < degree; i++) {
			baseStr = L"+" + baseStr;
		}
	} else {
		for(int i = 0; i < -degree; i++) {
			baseStr = L"-" + baseStr;
		}
	}
	return baseStr;
}
NoteBar::NoteBar() {
	subNode.clear();
	isLeaf = TRUE;
	leafNode = Note(0);
}
NoteBar::NoteBar(CString rString) {
	parse(rString);
}
NoteBar::NoteBar(const Note &n1) {
	subNode.clear();
	isLeaf = TRUE;
	leafNode = n1;
}
NoteBar::NoteBar(const std::vector<Note> &nList) {
	subNode.clear();
	isLeaf = FALSE;
	leafNode = Note(0);
	for(Note n : nList) {
		NoteBar nb(n);
		subNode.push_back(nb);
	}
}
NoteBar::NoteBar(int i) {
	subNode.clear();
	isLeaf = FALSE;
	leafNode = Note(0);
	while(i--) {
		subNode.push_back(NoteBar());
	}
}
NoteBar &NoteBar::operator [](int n) {
	if(isLeaf) {
		return NoteBar();
	}
	return subNode[n];
}

std::vector<NoteInfo> NoteBar::serial() const {
	std::vector<NoteInfo> niList;
	if(isLeaf) {
		NoteInfo ni = {leafNode, leafNode.rate(), 0.f};
		niList.push_back(ni);
		return niList;
	} else{
		int count = subNode.size();
		double interval = 1.f / count;
		for(int i = 0; i < subNode.size(); i++) {
			std::vector<NoteInfo> niSubList = subNode[i].serial();
			for(int j = 0; j < niSubList.size(); j++) {
				niSubList[j].pos /= count;
				niSubList[j].pos += interval * i;
				niList.push_back(niSubList[j]);
			}
		}
		return niList;
	}
}

void NoteBar::parse(CString rString) {
	subNode.clear();
	std::vector<int> splitPos;
	int levelOfBracket = 0;
	int haveBracket = 0;
	for(int i = 0; i < rString.GetLength(); i++) {
		if(rString.GetAt(i) == ',' && levelOfBracket == 0) {
			splitPos.push_back(i);
		}
		if(rString.GetAt(i) == '(') {
			levelOfBracket++;
			haveBracket++;
		}
		if(rString.GetAt(i) == ')') {
			levelOfBracket--;
		}
	}

	if(splitPos.size() == 0) {
		if(haveBracket) {
			CString rString1 = rString.Left(rString.GetLength() - 1);
			rString1 = rString.Right(rString.GetLength() - 1);
			parse(rString1);
		} else {
			Note nt;
			nt.parse(rString);
			isLeaf = true;
			leafNode = nt;
		}
	} else {
		isLeaf = false;
		leafNode = Note(0);
		std::vector<CString> subStringList;
		subStringList.push_back(rString.Left(splitPos[0]));
		for(int i = 0; i < splitPos.size() - 1; i++) {
			subStringList.push_back(rString.Mid(splitPos[i] + 1, splitPos[i + 1] - splitPos[i] - 1));
		}
		subStringList.push_back(rString.Right(rString.GetLength() - splitPos[splitPos.size() - 1] - 1));
		for(CString subString : subStringList) {
			NoteBar nb;
			nb.parse(subString);
			subNode.push_back(nb);
		}
	}
}
CString NoteBar::toString() const {
	if(isLeaf) 
		return leafNode.toString();
	if(subNode.size() == 0) 
		return L"0";
	CString ss;
	for(NoteBar nb : subNode) {
		if(!nb.isLeaf)
			ss += L"(";
		ss += nb.toString();
		if(!nb.isLeaf)
			ss += L")";
		ss += L",";
	}
	ss = ss.Left(ss.GetLength() - 1);
	return ss;
}

void NoteBar::makeImage(image &output, const size& sz) {
	image imSharp(5, 5);
	imSharp.fill(color(0));
	imSharp.line(point(0, 1), point(4, 1), color(0xFF, 0xFF, 0xFF));
	imSharp.line(point(0, 3), point(4, 3), color(0xFF, 0xFF, 0xFF));
	imSharp.line(point(1, 0), point(1, 4), color(0xFF, 0xFF, 0xFF));
	imSharp.line(point(3, 0), point(3, 4), color(0xFF, 0xFF, 0xFF));
	image imPoint(2, 2);
	imPoint.fill(color(0xFF, 0xFF, 0xFF));
	color noteColor[12] = {
		color(0xFF, 0x00, 0x00),
		color(0xFD, 0x53, 0x00),
		color(0xD5, 0x7B, 0x00),
		color(0xC6, 0x9E, 0x00),
		color(0xDF, 0xC9, 0x00),
		color(0x45, 0xF2, 0x00),
		color(0x00, 0xE8, 0x46),
		color(0x00, 0xD5, 0xD5),
		color(0x65, 0xB8, 0xFF),
		color(0x78, 0x93, 0xFF),
		color(0x99, 0x00, 0xFF),
		color(0xFF, 0x00, 0xFF),
	};
	output.create(sz);
	output.fill(color(0x77, 0x77, 0x77));
	std::vector<NoteInfo> niList = serial();
	int width = sz.W;
	int height = sz.H;
	int baseStep[7] = {0, 2, 4, 5, 7, 9, 11};
	for(int i = 0; i < niList.size(); i++) {
		if(niList[i].note.base == 0)
			continue;
		int leftBound = niList[i].pos * width;
		int rightBound = ((i == niList.size() - 1) ? width : niList[i + 1].pos * width) - 1;
		Note nt = niList[i].note;
		color noteColor1 = noteColor[baseStep[nt.base - 1] + (nt.sharp ? 1 : 0)];
		if(nt.degree > 0) {
			for(int j = 0; j < nt.degree; j++) 
				noteColor1 = color::getBrighten(noteColor1);
		}
		if(nt.degree < 0) {
			for(int j = 0; j > nt.degree; j--) {
				noteColor1.R *= 0.7;
				noteColor1.G *= 0.7;
				noteColor1.B *= 0.7;
			}
		}
		color noteColor2 = color::getBrighten(noteColor1);
		color noteColor3 = color::getDarken(noteColor1);
		//rightbound已经减1了
		output.filledRectangle(point(leftBound, 0), point(rightBound, height - 1), noteColor1);
		output.line(point(leftBound, 0), point(leftBound, height - 1), noteColor2);
		output.line(point(leftBound + 1, 1), point(leftBound + 1, height - 2), noteColor2);
		output.line(point(leftBound, 0), point(rightBound, 0), noteColor2);
		output.line(point(leftBound + 1, 1), point(rightBound - 1, 1), noteColor2);
		output.line(point(rightBound, 0), point(rightBound, height - 1), noteColor3);
		output.line(point(rightBound - 1, 1), point(rightBound - 1, height - 2), noteColor3);
		output.line(point(leftBound, height - 1), point(rightBound, height - 1), noteColor3);
		output.line(point(leftBound + 1, height - 2), point(rightBound - 1, height - 2), noteColor3);
		image imChar;
		KoishiExpand::KoishiMarkTool::CharMatLarge('0' + nt.base, imChar, color(0xFF, 0xFF, 0xFF));
		point charPoint((rightBound + leftBound) / 2 - imChar.width / 2, height / 2 - imChar.height / 2);
		output.putFore(imChar, LAY, charPoint);
		if(nt.degree > 0) {
			for(int j = 0; j < nt.degree; j++) {
				point ptPoint((rightBound + leftBound) / 2 - 1, height / 2 - imChar.height / 2 - 3 * (j + 1));
				output.putFore(imPoint, LAY, ptPoint);
			}
		}
		if(nt.degree < 0) {
			for(int j = 0; j > nt.degree; j--) {
				point ptPoint((rightBound + leftBound) / 2 - 1, height / 2 + imChar.height / 2 + 3 * j + 1);
				output.putFore(imPoint, LAY, ptPoint);
			}
		}
		if(nt.sharp) {
			point ptSharp((rightBound + leftBound) / 2 - imChar.width / 2 - 7, height / 2 - imChar.height / 2);
			output.putFore(imSharp, LAY, ptSharp);
		}
	}
}