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

#define USE_SMALL_FONT	/* ������б�ʾʹ��С�ֿ⣬ �����ֻ��bsp_tft+lcd.c��ʹ�� */

#define HZK16_ADDR 0x803EA00		/* ���ֿ��ַ�� �����ַ��CPU�ڲ�Flash��λ�����������ĺ���һ���� */

#endif
