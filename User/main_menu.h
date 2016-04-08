/*
*********************************************************************************************************
*
*	模块名称 : 主界面
*	文件名称 : main_menu.h
*	版    本 : V1.0
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H


#define ICON_HEIGHT	128				/* 矩形图标高度 */
#define ICON_WIDTH	128				/* 矩形图标宽度 */

#define ICON_STEP_X 180		/* 图标之间的间隔 */
#define ICON_STEP_Y	170		/* 图标之间的间隔 */

extern uint8_t MainMenu(void);
extern void DispBackground(void);
extern void DispTopBar(void);
extern void DispBottomBar(void);

#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
