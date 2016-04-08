/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "measurement.h"
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
#include "bsp.h"	
#include "motor.h"
#include "main_menu.h"
/* 按钮的坐标 */
#define BUTTON_RET_H	60
#define BUTTON_RET_W	150
#define	BUTTON_RET_X	(g_LcdWidth - BUTTON_RET_W - 50)
#define	BUTTON_RET_Y	(g_LcdHeight - BUTTON_RET_H - 200)
/* 进度条的坐标 */
#define BAR_RET_H	60
#define BAR_RET_W	500
#define	BAR_RET_X	(g_LcdWidth - BAR_RET_W - 250)
#define	BAR_RET_Y	(g_LcdHeight - BAR_RET_H - 200)

void  AirFirst(void)
{
//	u8 i;
	Valve(171);
	Valve(181);	   //1270-->1500
//	for(i=0;i<2;i++)
//	{
		Motorun(0,1500,FORWARD,0,  30,60,8,20,  30,2,20,0,     81,150,160);      //抽气
		Motorun(0,1500,BACKWARD,0, 30,60,8,20,  30,2,20,200,  80,151,170);      //打气,清洗
		bsp_DelayMS(4);
//	}
	Valve(150);	 //2540-->3000
	Motorun(0,3000,FORWARD,0,      30,60,8,20,  30,2,20,0,     81,0,171);      //抽气
	bsp_DelayMS(444);
	Valve(80);	
	Valve(151);
	Valve(170);
	Valve(180);
	bsp_DelayMS(52);															
	Motorun(0,3000,BACKWARD,1,     27,27,0,0,  30,0,0,0,  0,0,0); 
	bsp_DelayMS(75);
}
void MainTask(void)
{
	uint8_t fButton=0;
	uint8_t ucTouch,j;		/* 触摸事件 */
	uint8_t fRefresh;		/* 刷屏请求标志,1表示需要刷新 */
	FONT_T  tFontBtn;	/* 定义一个字体结构体变量，用于设置字体参数 */
	int16_t tpX, tpY;
	BUTTON_T tBtn;
	uint16_t fProgess=0,fProgess1=0;
	char ch[10];
//	LCD_ClrScr(CL_BLUE);  	/* 清屏，背景蓝色 */
	DispTopBar();		/* 显示顶部栏 */
	DispBottomBar();	/* 显示底部栏 */
	DispBackground();	/* 显示图标背景 */
	
	{	/* 按钮字体 */
		tFontBtn.FontCode = FC_ST_48;
		tFontBtn.BackColor = CL_MASK;	/* 透明色 */
		tFontBtn.FrontColor = CL_BLACK;
		tFontBtn.Space = 1;
	}
	fRefresh = 1;	/* 1表示需要刷新LCD */
	LCD_DrawRect(BAR_RET_X,BAR_RET_Y,BAR_RET_H,BAR_RET_W,CL_WHITE);
//	LCD_Fill_Rect(BAR_RET_X,BAR_RET_Y,BAR_RET_H,BAR_RET_W,CL_GREEN);
	while (1)
	{
		bsp_Idle();
		
		if(fButton&&fProgess<BAR_RET_W)
		{
			for(;j<10;j++)
			{
				fProgess+=55;
				LCD_Fill_Rect(BAR_RET_X,BAR_RET_Y,BAR_RET_H,fProgess,CL_GREEN);
//				AirFirst();
			}
		}
		if (fRefresh)
		{
			fRefresh = 0;

			/* 显示按钮 */
			{
				tBtn.Font = &tFontBtn;

				tBtn.Left = BUTTON_RET_X;
				tBtn.Top = BUTTON_RET_Y;
				tBtn.Height = BUTTON_RET_H;
				tBtn.Width = BUTTON_RET_W;
				tBtn.Focus = 0;	/* 失去焦点 */
				strcpy(ch,"测量");
				tBtn.pCaption = ch;
				LCD_DrawButton(&tBtn);
			}
		}
		ucTouch = TOUCH_GetKey(&tpX, &tpY);	/* 读取触摸事件 */
		if (ucTouch != TOUCH_NONE)
		{
			switch (ucTouch)
			{
				case TOUCH_DOWN:		/* 触笔按下事件 */
					if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
					{
						
						tBtn.Font = &tFontBtn;

						tBtn.Left = BUTTON_RET_X;
						tBtn.Top = BUTTON_RET_Y;
						tBtn.Height = BUTTON_RET_H;
						tBtn.Width = BUTTON_RET_W;
						tBtn.Focus = 1;	/* 焦点 */
						if(fButton==0)
						{
							strcpy(ch,"测量");
						}
						else
						{
							strcpy(ch,"停止");
						}
						tBtn.pCaption = ch;
						LCD_DrawButton(&tBtn);
							
					}
					break;

				case TOUCH_RELEASE:		/* 触笔释放事件 */
					if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
					{
						if(fButton==0)
						{
							fButton=1;
							tBtn.Font = &tFontBtn;

							tBtn.Left = BUTTON_RET_X;
							tBtn.Top = BUTTON_RET_Y;
							tBtn.Height = BUTTON_RET_H;
							tBtn.Width = BUTTON_RET_W;
							tBtn.Focus = 0;	/* 焦点 */
							strcpy(ch,"停止");
							tBtn.pCaption = ch;
							LCD_DrawButton(&tBtn);
						}
						else return;

					}
					else	/* 按钮失去焦点 */
					{
						tBtn.Font = &tFontBtn;

						tBtn.Left = BUTTON_RET_X;
						tBtn.Top = BUTTON_RET_Y;
						tBtn.Height = BUTTON_RET_H;
						tBtn.Width = BUTTON_RET_W;
						tBtn.Focus = 0;	/* 焦点 */
						strcpy(ch,"测量");
						tBtn.pCaption = ch;
						LCD_DrawButton(&tBtn);

					}
			}
		}
	}
	
}

