#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//���ظ�ʽ

namespace KoishiTitle{
	using namespace Koishi;
	enum charElem{ch_udef, ch_sm, ch_sg, ch_ft, ch_fm, ch_gn, ch_gg, ch_mg, ch_mm, ch_pr, ch_pg, ch_th, ch_kn, ch_dl};
	enum mainPartElem{mp_udef, mp_cap, mp_hair, mp_face, mp_neck, mp_coat, mp_pants, mp_belt, mp_shoes, mp_skin, mp_weapon};
	enum subPartElem{sp_udef, sp_a, sp_b, sp_c, sp_d, sp_e, sp_f, sp_g, sp_h, sp_x};
	class avatar
	{
	public:
		avatar(void);
		~avatar(void);
	public:
		bool isTN;
		charElem chars;
		mainPartElem mainPart;
		i32 mainPartID;
		subPartElem subPart;
		i32 subPartID;
		bool isMask1;
	public:
		bool useName(str imgName);		//����IMG·����
		i32 getWeight() const;			//���Ȩ��
		i32 getWeight2() const;			//���Ȩ��2����1��ͬ����˳��ѹ����1-N��
	};
	typedef struct mixSeqElemW{
		mainPartElem mainPart;
		subPartElem subPart;
		i32 subPartID;
	}mixSeqElem;
	//����·�����õĸ�������
	extern mixSeqElem mixSeqList[64];
	extern bool isnum(b8 chars);			//����һ���ֽ��Ƿ��������ַ�Χ�ڼ�'0'-'9'֮��
	extern str shorten(const str &path);	//����·���������һ���ڵ�
	extern str imgAddV4Num(const str &imgName, i32 num);	//V6���V4ʱʹ��
	extern str avaFmt(int i);			//���ʱװ��ID��Ӧ���ַ�������4λ���㣩
	//������������
	extern str GetAvatarNPKFileName(charElem ch, mainPartElem pt);	//���ݽ�ɫ�Ͳ����������NPK�ļ������ݲ�֧������
	extern str GetAvatarIMG_Fmt_CH_XXXX(charElem ch, mainPartElem pt);	//���ݽ�ɫ�Ͳ�������������sg_body�Ķ�·����
	extern str GetAvatarSubPartString(subPartElem sp);
}