/*
*********************************************************************************************************
*
*	模块名称 : 图片资源模块。
*	文件名称 : image.H
*	版    本 : V2.0
*	说    明 : 头文件
*	修改记录 :
*		版本号  日期       作者    说明
*		v2.0    2011-10-16 armfly  创建
*
*	Copyright (C), 2010-2012, 安富莱电子
*
*********************************************************************************************************
*/

#ifndef __IMAGE_H
#define __IMAGE_H

#include "stm32f4xx.h"
#include "GUI.h"
extern const unsigned char acRecord[128 * 128 * 4];
extern const unsigned char acMaintaining[128 * 128 * 4];
extern const unsigned char acMeasureture[128 * 128 * 4];
extern const unsigned char acPrint[128 * 128 * 4];
extern const unsigned char acQC[128 * 128 * 4];
extern const unsigned char acPreferences[128 * 128 * 4];
extern const unsigned short _ac1[];
extern const GUI_BITMAP bm1;

#endif
