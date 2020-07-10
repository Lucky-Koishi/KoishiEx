#pragma once
class Note {
public:
	Note();
	Note(CString);
	Note(int);
	Note(int, int, int);
public:
	uchar base;
	char sharp;
	char degree;
public:
	void parse(CString);	//解析
	void standard();		//标准化·不带降号·最多只带1个升号
	double rate() const;	//转化为频率
	CString toString()const;//转化为字符串
};

class NoteInfo {
public:
	Note note;
	double rate;
	double pos; //取值范围[0, 1)
};
class NoteBar {
public:
	NoteBar();
	NoteBar(CString);
	NoteBar(const Note &);
	NoteBar(const std::vector<Note> &);
	NoteBar(int);		//平均分多少份
public:
	BOOL isLeaf;
	Note leafNode;					//isLeaf = TRUE 有效
	std::vector<NoteBar> subNode;	//isLeaf = FALSE 有效
public:
	NoteBar &operator [](int);		//isLeaf = FALSE 有效
	std::vector<NoteInfo> serial() const;
	void parse(CString);
	CString toString() const;
	void makeImage(image &output, const size& sz);
};