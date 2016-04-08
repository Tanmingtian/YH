/*
*********************************************************************************************************
*	                                  
*	模块名称 : emWin的入口文件
*	文件名称 : MainTask.c
*	版    本 : V1.0
*	说    明 : 用于声明众多头文件和变量
*	修改记录 :
*		版本号    日期          作者              说明
*		v1.0    2012-12-07    Eric2013       ST固件库版本 V1.0.2版本。
*       v1.1    2014-02-24    Eric2013       升级到STemWin5.22d
*
*********************************************************************************************************
*/

#ifndef __MainTask_H
#define __MainTask_H

#include "stm32f4xx.h"
#include "GUI.h"
#include "DIALOG.h"
#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"
#include "GRAPH.h"
#include "MENU.h"
#include "MULTIPAGE.h"
#include "ICONVIEW.h"
#include "TREEVIEW.h"


/* 提供给其他C文件调用的函数 */
void MainTask(void);
	
#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/

