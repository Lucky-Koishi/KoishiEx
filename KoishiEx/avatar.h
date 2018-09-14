#include "stdafx.h"
#include "KoishiEx.h"

#pragma once
//像素格式

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
		bool useName(str imgName);		//解析IMG路径名
		i32 getWeight() const;			//获得权重
		i32 getWeight2() const;			//获得权重2（跟1不同，将顺序压缩到1-N）
	};
	typedef struct mixSeqElemW{
		mainPartElem mainPart;
		subPartElem subPart;
		i32 subPartID;
	}mixSeqElem;
	//解析路径名用的辅助函数
	extern mixSeqElem mixSeqList[64];
	extern bool isnum(b8 chars);			//返回一个字节是否属于数字范围内即'0'-'9'之间
	extern str shorten(const str &path);	//缩短路径名至最后一个节点
	extern str imgAddV4Num(const str &imgName, i32 num);	//V6变成V4时使用
	extern str avaFmt(int i);			//获得时装用ID对应的字符串（≤4位补零）
	//其他辅助函数
	extern str GetAvatarNPKFileName(charElem ch, mainPartElem pt);	//根据角色和部件获得所在NPK文件名·暂不支持武器
	extern str GetAvatarIMG_Fmt_CH_XXXX(charElem ch, mainPartElem pt);	//根据角色和部件返回类似于sg_body的短路径名
	extern str GetAvatarSubPartString(subPartElem sp);
}