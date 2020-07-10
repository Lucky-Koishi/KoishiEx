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
	void parse(CString);	//����
	void standard();		//��׼�����������š����ֻ��1������
	double rate() const;	//ת��ΪƵ��
	CString toString()const;//ת��Ϊ�ַ���
};

class NoteInfo {
public:
	Note note;
	double rate;
	double pos; //ȡֵ��Χ[0, 1)
};
class NoteBar {
public:
	NoteBar();
	NoteBar(CString);
	NoteBar(const Note &);
	NoteBar(const std::vector<Note> &);
	NoteBar(int);		//ƽ���ֶ��ٷ�
public:
	BOOL isLeaf;
	Note leafNode;					//isLeaf = TRUE ��Ч
	std::vector<NoteBar> subNode;	//isLeaf = FALSE ��Ч
public:
	NoteBar &operator [](int);		//isLeaf = FALSE ��Ч
	std::vector<NoteInfo> serial() const;
	void parse(CString);
	CString toString() const;
	void makeImage(image &output, const size& sz);
};