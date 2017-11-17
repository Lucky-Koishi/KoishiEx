#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//ÏñËØ¸ñÊ½

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
		bool useName(str imgName);
		i32 getWeight() const;
	};
	typedef struct{
		mainPartElem mainPart;
		subPartElem subPart;
	}mixSeqElem;
	extern mixSeqElem mixSeqList[55];
	extern bool isnum(b8 chars);
	extern str replaceAll(const str &oldStr, const str &oldChar, const str &newChar);
	extern str shorten(const str &path);
	extern str fileUnslash(const str &filePath);
	extern str imgUnslash(const str &imgPath);
	extern str imgSlash(const str &imgPath);
	extern str imgAddV4Num(const str &imgName, i32 num);
	extern str avaFmt(int i);
}