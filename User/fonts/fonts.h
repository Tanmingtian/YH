#ifndef __FONTS_H_
#define __FONTS_H_

extern unsigned char const g_Ascii12[];
extern unsigned char const g_Ascii16[];
extern unsigned char const g_Ascii24[];
extern unsigned char const g_Ascii48[];

extern unsigned char const g_Hz12[];
extern unsigned char const g_Hz16[];
extern unsigned char const g_Hz24[];
extern unsigned char const g_Hz48[];
extern unsigned char const g_Hz64[];
extern unsigned char const g_Hz96[];
extern unsigned char const g_HZK16[];
extern unsigned char const g_HZK24[];

#define USE_SMALL_FONT	/* 定义此行表示使用小字库， 这个宏只在bsp_tft+lcd.c中使用 */

#define HZK16_ADDR 0x803EA00		/* 汉字库地址， 这个地址在CPU内部Flash，位于主程序区的后面一部分 */

#endif
