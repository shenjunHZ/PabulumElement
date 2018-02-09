/*
* Copyright (c) 
* All rights reserved.
*
* 文件名称：XMLOsdTxt.h
* 文件标识：
* 摘　　要：
*

* 当前版本：1.0
* 原作者　：
* 完成日期：
* 修订记录：创建
*/
#ifndef _XML_OSD_TXT_H_
#define _XML_OSD_TXT_H_
#include "Common/CommonGlobal.h"
#include "AX_API/platform.h"

class COMMON_EXPORT XMLOsdTxt
{
public:
	XMLOsdTxt(void);
	~XMLOsdTxt(void);

	XMLOsdTxt* clone(void);
	int copy(XMLOsdTxt* src);

public:
	int		 _enable; //使能
	uint16	 _posX;   //叠加的坐标
	uint16   _posY;
	uint32   _color; //字体颜色
	int      _fontSize; //字体大小
	int		 _fontType; //字体
	int		 _isBold;
	int		 _isTransparent;
	uint32   _bkColor; //背景色
};

#endif
