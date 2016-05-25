/*
*********************************************************************************************************
*	                                  
*	ģ������ : ȫ����ƴ�����뷨
*	�ļ����� : MainTask.c
*	��    �� : V1.0
*	˵    �� : �����̿�������Ӧ������������4.3�磬5���7������
*              1. ����emWin���ֹ������ɵ��ֿ�洢����NorFlash���棬ʹ��ǰ����ؽ��ֿ�洢��NorFlash
*                 ��8MB��ʼ�Ŀռ��У�Ҳ����0x64800000��Ϊ��ʼ��ַ��Ҫ��ϵͳ����������������
*                 ����д�������û��ֲ�V2.0: 1.9.3  ����STM32-V5_NOR.jflash �Ĳ��裩
*              2. ����һ��Ҫע�����ֻ�й��ܼ�Caps���õ���Сд��ʱ���֧����Ӣ���л���
*              3. ֧����Ӣ�ĵ��л���֧�ִ�Сд�л���֧�ֲ��������ַ���֧���������롣
*              4. ֧�ֺ�������ָ��λ�õĲ�����ı��༭ʱ�Ļظ�ͻس���
*              5. ��ǰ��֧��ÿ������һ�����֣�Ȼ���ûظ��ɾ����Ӧƴ����
*              6. ����˵����
*                (1) ������Ĭ�����ַ����빦�ܡ�
*                (2) ���ܼ�C/e��ʾ��ǰ�Ǻ������룬c/E��ʾӢ�����롣
*                (3) ���ܼ�Enter��ʾ�س���
*                (4) ���ܼ�Capsʵ�ִ�Сд���л���
*                (5) ���ܼ�Back��ʾ�ظ��ı��༭ʱ�ַ���ɾ���ͣ�ƴ������ʱƴ����ɾ������Ҫʹ���������
*                                   
*	�޸ļ�¼ :
*		�汾��    ����          ����          ˵��
*		v1.0    2014-07-08    Eric2013        �׷�
*	
*	Copyright (C), 2014-2015, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"			/* �ײ�Ӳ������ */
#include "main.h"
#include "bsp_tft_lcd.h"
#include "typewriting.h"
#include "pysearch.h"
#include "measurement.h"
/*
*********************************************************************************************************
*	                         ��̬����
*********************************************************************************************************
*/
static uint8_t s_SelectLangue = 0;	/* 0��ʾ���ģ�1��ʾӢ�� */
static uint8_t s_LeftFlag = 0;	    /* 1��ʾ��ǰ��Ŀ�����δ��ʾ����, ����֮ */
static uint8_t s_RightFlag = 0;	    /* 1��ʾ��ǰ��Ŀ�Ҳ���δ��ʾ����, ����֮ */
static uint8_t s_CapsLock = 0;      /* 0��ʾСд��1��ʾ��д */
static uint8_t BUTTON_Num=0;
static uint8_t s_Key;
static uint8_t s_Text;
unsigned char s_tempbuf[256]={0};
char s_Textbuf[8]={0};
char s_Hzbuf[512]={0};
char s_Bufview[128]={0};
char dis_keyboard=0;
static uint16_t  s_Offset = 0;
static uint16_t  s_Hznum;          
static uint16_t  s_Hzoff;

/*
*********************************************************************************************************
*	                         �궨��ͽṹ��
*********************************************************************************************************
*/
#define COLOR_BACK0            0xFF3333 
#define COLOR_BACK1            0x550000
#define COLOR_BORDER           0x444444
#define COLOR_KEYPAD0          0xAAAAAA
#define COLOR_KEYPAD1          0x555555
#define BUTTON_COLOR0          0xEEEEEE
#define BUTTON_COLOR1          0xCCCCCC
#define BUTTON_COLOR2          0xCCCCCC
#define BUTTON_COLOR3          0xAAAAAA
#define BUTTON_SKINFLEX_RADIUS 4
#define APP_INIT_LOWERCASE     (WM_USER + 0)
FONT_T	FontB;
BUTTON_T BtnCount;
typedef struct {
  int          xPos;
  int          yPos;
  int          xSize;
  int          ySize;
  char * acLabel;   /* ��ť��Ӧ��Сд�ַ� */
  char * acLabel1;  /* ��ť��Ӧ�Ĵ�д�ַ� */
  char         Control;   /* ��ť��Ӧ�Ŀ���λ��1��ʾ���ܰ�ť��0��ʾ��ͨ��ť */
} BUTTON_DATA;


/*
*********************************************************************************************************
*	                         �궨��ͽṹ��
*********************************************************************************************************
*/
#define BUTTON_WHITH  70
#define BUTTON_HIGHT  50
#define BUTTON_StartX  46
#define BUTTON_HIGHTX  60
	
static const BUTTON_DATA _aButtonData[] = 
{

	/* ��1�Ű�ť */
	{   5,                   6,  BUTTON_WHITH, BUTTON_HIGHT, "1" ,   "1",  0},
	{  31+BUTTON_StartX,     6,  BUTTON_WHITH, BUTTON_HIGHT, "2",    "2",  0},
	{  57+BUTTON_StartX*2,   6,  BUTTON_WHITH, BUTTON_HIGHT, "3",    "3",  0},
	{  83+BUTTON_StartX*3,   6,  BUTTON_WHITH, BUTTON_HIGHT, "4",    "4",  0},
	{ 109+BUTTON_StartX*4,   6,  BUTTON_WHITH, BUTTON_HIGHT, "5",    "5",  0},
	{ 135+BUTTON_StartX*5,   6,  BUTTON_WHITH, BUTTON_HIGHT, "6",    "6",  0},
	{ 161+BUTTON_StartX*6,   6,  BUTTON_WHITH, BUTTON_HIGHT, "7",    "7",  0},
	{ 187+BUTTON_StartX*7,   6,  BUTTON_WHITH, BUTTON_HIGHT, "8",    "8",  0},
	{ 213+BUTTON_StartX*8,   6,  BUTTON_WHITH, BUTTON_HIGHT, "9",    "9",  0},
	{ 239+BUTTON_StartX*9,   6,  BUTTON_WHITH, BUTTON_HIGHT, "0",    "0",  0},
	{ 265+BUTTON_StartX*10,  6,  BUTTON_WHITH, BUTTON_HIGHT, "Back", "Back", 1 },

	/* ��2�Ű�ť */
	{   5,                   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "Tab", "Tab", 1 },
	{  31+BUTTON_StartX,     BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "q", "Q", 0 },
	{  57+BUTTON_StartX*2,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "w", "W", 0 },
	{  83+BUTTON_StartX*3,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "e", "E", 0 },
	{ 109+BUTTON_StartX*4,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "r", "R", 0 },
	{ 135+BUTTON_StartX*5,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "t", "T", 0 },
	{ 161+BUTTON_StartX*6,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "y", "Y", 0 },
	{ 187+BUTTON_StartX*7,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "u", "U", 0 },
	{ 213+BUTTON_StartX*8,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "i", "I", 0 },
	{ 239+BUTTON_StartX*9,   BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "o", "O", 0 },
	{ 265+BUTTON_StartX*10,  BUTTON_HIGHTX,  BUTTON_WHITH, BUTTON_HIGHT, "p", "P", 0 },

	/* ��3�Ű�ť */
	{  16,                  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "a", "A", 0 },
	{  42+BUTTON_StartX,    33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "s", "S", 0 },
	{  68+BUTTON_StartX*2,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "d", "D", 0 },
	{  94+BUTTON_StartX*3,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "f", "F", 0 },
	{ 120+BUTTON_StartX*4,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "g", "G", 0 },
	{ 146+BUTTON_StartX*5,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "h", "H", 0 },
	{ 172+BUTTON_StartX*6,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "j", "J", 0 },
	{ 198+BUTTON_StartX*7,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "k", "K", 0 },
	{ 224+BUTTON_StartX*8,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH, BUTTON_HIGHT, "l", "L", 0 },
	{ 250+BUTTON_StartX*9,  33+BUTTON_HIGHTX+20,  BUTTON_WHITH+20,  BUTTON_HIGHT, "Enter","Enter", 1},

	/* ��4�Ű�ť */
	{   6,                   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "Caps", "Caps", 1},
	{  32+BUTTON_StartX*1,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "z", "Z", 0 },
	{  58+BUTTON_StartX*2,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "x", "X", 0 },
	{  84+BUTTON_StartX*3,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "c", "C", 0 },
	{ 110+BUTTON_StartX*4,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "v", "V", 0 },
	{ 136+BUTTON_StartX*5,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "b", "B", 0 },
	{ 162+BUTTON_StartX*6,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "n", "N", 0 },
	{ 188+BUTTON_StartX*7,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "m", "M", 0 },
	{ 214+BUTTON_StartX*8,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, ",", ",", 1 },
	{ 240+BUTTON_StartX*9,   67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, ".", ".", 1 },
	{ 266+BUTTON_StartX*10,  67+BUTTON_HIGHTX+20*2,  BUTTON_WHITH, BUTTON_HIGHT, "?", "?", 1 },

	/* ��5�Ű�ť */
	{   6,                   101+BUTTON_HIGHTX+20*3,  BUTTON_WHITH+10,  BUTTON_HIGHT, "Shift", "Shift", 1},
	{  32+BUTTON_StartX*1,   101+BUTTON_HIGHTX+20*3,  BUTTON_WHITH,  BUTTON_HIGHT, "123",   "123",   1},
	{  58+BUTTON_StartX*2,   101+BUTTON_HIGHTX+20*3,  BUTTON_WHITH,  BUTTON_HIGHT, "��",   "��",   1},
	{  84+BUTTON_StartX*3,   101+BUTTON_HIGHTX+20*3,  430,           BUTTON_HIGHT, " ",     " ",     1},
	{ 240+BUTTON_StartX*9,   101+BUTTON_HIGHTX+20*3,  BUTTON_WHITH,  BUTTON_HIGHT, "-",     "",      1},
	{ 266+BUTTON_StartX*10,  101+BUTTON_HIGHTX+20*3,  BUTTON_WHITH,  BUTTON_HIGHT, "_",     "",      1},
};
void keyboard(void)
{
	u8 i;
	s_Text=0;
	for(i=0;i<49;i++)
	{	
		FontB.FontCode = FC_ST_24;
		FontB.BackColor = CL_MASK;	/* ͸��ɫ */
		FontB.FrontColor = CL_RED;
		FontB.Space = 0;
		BtnCount.Font = &FontB;
		BtnCount.Left = _aButtonData[i].xPos;
		BtnCount.Top = _aButtonData[i].yPos+200;
		BtnCount.Height = _aButtonData[i].ySize;
		BtnCount.Width = _aButtonData[i].xSize;
		BtnCount.Focus = 0;	/* ʧȥ���� */
		BtnCount.acLabel =  _aButtonData[i].acLabel;
		BtnCount.acLabel1 =  _aButtonData[i].acLabel1;
		BtnCount.Control =  _aButtonData[i].Control;
		BtnCount.pCaption = _aButtonData[i].acLabel;
		dis_keyboard=1;
		LCD_DrawButton(&BtnCount);
	}
}
void typewriting(void)
{	
	u8 i;
//	char ch[10];
	bsp_Idle();
	ucTouch = TOUCH_GetKey(&tpX, &tpY);	/* ��ȡ�����¼� */
	if(ucTouch != TOUCH_NONE)
	{
		switch (ucTouch)
		{
			case TOUCH_DOWN:		/* ���ʰ����¼� */
				for(i=0;i<49;i++)
				{
					if(TOUCH_InRect(tpX, tpY, _aButtonData[i].xPos, _aButtonData[i].yPos+200, _aButtonData[i].ySize, _aButtonData[i].xSize))
					{
						BUTTON_Num=i;
						BtnCount.Left = _aButtonData[BUTTON_Num].xPos;
						BtnCount.Top = _aButtonData[BUTTON_Num].yPos+200;
						BtnCount.Height = _aButtonData[BUTTON_Num].ySize;
						BtnCount.Width = _aButtonData[BUTTON_Num].xSize;
						BtnCount.Focus = 1;	/* ʧȥ���� */
						BtnCount.acLabel =  _aButtonData[BUTTON_Num].acLabel;
						BtnCount.acLabel1 =  _aButtonData[BUTTON_Num].acLabel1;
						BtnCount.Control =  _aButtonData[BUTTON_Num].Control;
						BtnCount.pCaption = _aButtonData[BUTTON_Num].acLabel;
						LCD_DrawButton(&BtnCount);
						break;
					}
				}	
				
				break;
			case TOUCH_RELEASE:		/* �����ͷ��¼� */	

				BtnCount.Left = _aButtonData[BUTTON_Num].xPos;
				BtnCount.Top = _aButtonData[BUTTON_Num].yPos+200;
				BtnCount.Height = _aButtonData[BUTTON_Num].ySize;
				BtnCount.Width = _aButtonData[BUTTON_Num].xSize;
				BtnCount.Focus = 0;	/* ʧȥ���� */
				BtnCount.acLabel =  _aButtonData[BUTTON_Num].acLabel;
				BtnCount.acLabel1 =  _aButtonData[BUTTON_Num].acLabel1;
				BtnCount.Control =  _aButtonData[BUTTON_Num].Control;
				BtnCount.pCaption = _aButtonData[BUTTON_Num].acLabel;
				LCD_DrawButton(&BtnCount);
//				switch(BUTTON_Num)
//				{
//					case 43:
//						if(s_SelectLangue)//ֻ����Ӣ������ʱ���ܴ�Сд�л�
//						{
//							for(i=0;i<49;i++)
//							{									
//								BtnCount.Left = _aButtonData[i].xPos;
//								BtnCount.Top = _aButtonData[i].yPos+200;
//								BtnCount.Height = _aButtonData[i].ySize;
//								BtnCount.Width = _aButtonData[i].xSize;
//								BtnCount.Focus = 0;	/* ʧȥ���� */
//								BtnCount.acLabel =  _aButtonData[i].acLabel;
//								BtnCount.acLabel1 =  _aButtonData[i].acLabel1;
//								BtnCount.Control =  _aButtonData[i].Control;
//								if(s_CapsLock)
//								{
//									BtnCount.pCaption = _aButtonData[i].acLabel;
//								}
//								else
//								{
//									BtnCount.pCaption = _aButtonData[i].acLabel1;
//								}
//								LCD_DrawButton(&BtnCount);
//							}
//							s_CapsLock=~s_CapsLock;		
//						}
//						break;
//					case 45://��Ӣ���л�
//						/* ��ǰ��Ӣ�ģ�������Сд��ĸ��ʱ��ſ����л�  */
//						if((s_SelectLangue == 1)&&(s_CapsLock == 0))
//						{
//							s_SelectLangue = 0;
//							BtnCount.Left = _aButtonData[BUTTON_Num].xPos;
//							BtnCount.Top = _aButtonData[BUTTON_Num].yPos+200;
//							BtnCount.Height = _aButtonData[BUTTON_Num].ySize;
//							BtnCount.Width = _aButtonData[BUTTON_Num].xSize;
//							BtnCount.Focus = 0;	/* ʧȥ���� */
//							BtnCount.acLabel =  _aButtonData[BUTTON_Num].acLabel;
//							BtnCount.acLabel1 =  _aButtonData[BUTTON_Num].acLabel1;
//							BtnCount.Control =  _aButtonData[BUTTON_Num].Control;
//							strcpy(ch,"��");
//							BtnCount.pCaption = ch;
//							LCD_DrawButton(&BtnCount);
//						}
//						else if((s_SelectLangue == 0)&&(s_CapsLock == 0))
//						{
//							s_SelectLangue = 1;
//							BtnCount.Left = _aButtonData[BUTTON_Num].xPos;
//							BtnCount.Top = _aButtonData[BUTTON_Num].yPos+200;
//							BtnCount.Height = _aButtonData[BUTTON_Num].ySize;
//							BtnCount.Width = _aButtonData[BUTTON_Num].xSize;
//							BtnCount.Focus = 0;	/* ʧȥ���� */
//							BtnCount.acLabel =  _aButtonData[BUTTON_Num].acLabel;
//							BtnCount.acLabel1 =  _aButtonData[BUTTON_Num].acLabel1;
//							BtnCount.Control =  _aButtonData[BUTTON_Num].Control;
//							strcpy(ch,"Ӣ");
//							BtnCount.pCaption = ch;
//							LCD_DrawButton(&BtnCount);
//						}
//						break;
//					default: break;
//				}
				/* ����������ĸ��Сд��ʶ�� ********************************************/
				if(s_CapsLock == 0)
				{
					s_Key = _aButtonData[BUTTON_Num].acLabel[0];
				}
				/* ��д��ĸ */
				else
				{
					s_Key = _aButtonData[BUTTON_Num].acLabel1[0];
				}

				/* ���Ĳ������Ĵ��� **************************************************/
				if(s_SelectLangue == 0)
				{		
					int j;
					char *ptr;

					/* ����1����***********************************************************/
					if(s_Key == '1')
					{
						/* ��������δ��ʾ�ĺ��� */
						if(s_LeftFlag == 1)
						{
							/* ��Ϊÿ����������ʾ7�����֣����Գ�������7�ĵط��ܶ� */
							if(s_Hzoff%7 == 0)
							{
								s_Hzoff -= 7;	
							}
							else
							{
								s_Hzoff = s_Hzoff - (s_Hzoff % 7);	
							}
							
							s_Hzoff -= 7;

							s_RightFlag = 1;

							/* ���ƫ�Ƶ�ַ֮ǰ����7�����ϵĺ��� */
							if(s_Hzoff >= 7)
							{
								s_Bufview[0] = '1';
								s_Bufview[1] = '<';
								s_Bufview[2] = ' ';
								
								for (j = 0; j < 7;j++)
								{
									s_Bufview[j*4+3] = j+'2';
									s_Bufview[j*4+4] = s_Hzbuf[(s_Hzoff)*2];
									s_Bufview[j*4+5] = s_Hzbuf[(s_Hzoff)*2+1];
//											s_Bufview[j*4+6] = s_Hzbuf[(s_Hzoff)*2+2];
									s_Bufview[j*4+6] = ' ';
									s_Hzoff++;
								}

								s_Bufview[31] = '9';
								s_Bufview[32] = '>';
								s_Bufview[33] = 0;
								s_LeftFlag = 1;
							}
							/* ���ƫ�Ƶ�ַ֮ǰ������С��7 */
							else
							{	
								s_LeftFlag = 0;
								for (j = 0; j < 7;j++)
								{
									s_Bufview[j*4+0] = j+'1';
									s_Bufview[j*4+1] = s_Hzbuf[(s_Hzoff)*2];
									s_Bufview[j*4+2] = s_Hzbuf[(s_Hzoff)*2+1];
//											s_Bufview[j*4+3] = s_Hzbuf[(s_Hzoff)*2+2];
									s_Bufview[j*4+3] = ' ';
									s_Hzoff++;//
								}

								s_Bufview[28] = '8';
								s_Bufview[29] = '>';
								s_Bufview[30] = '\0';
							}
						}
						/* ���û�к��֣�ֱ����ʾ��һ������ */
						else
						{
							s_Textbuf[0+2*s_Text] = s_Hzbuf[0];
							s_Textbuf[1+2*s_Text] = s_Hzbuf[1];
//									s_Textbuf[2] = s_Hzbuf[2];
							s_Textbuf[2+2*s_Text] = '\0';
//								MULTIEDIT_AddText(hMulti, s_Textbuf);
							LCD_Fill_Rect(5,10,25,800,CL_WHITE);	
							LCD_DispStr(5, 10, s_Textbuf, &FontB);//��ʾѡ��ĺ���	
							if(s_Hzbuf[0]!=0)s_Text++;	
							for(i=0;i<34;i++)
							{
								s_tempbuf[i]= '\0';	
								s_Bufview[i]= '\0';
								s_Hzbuf[i]='\0';
							}
							s_Offset=0;
							LCD_Fill_Rect(5,155,25,500,CL_WHITE);	
							LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);		
						}							
//							TEXT_SetText(ahText[1],s_Bufview);
						LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);
						LCD_DispStr(5, 180, s_Bufview, &FontB);//��ʾԤѡ����
					}
					/* ����8����***********************************************************/
					else if(s_Key == '8')
					{
						if(s_LeftFlag == 1)
						{
							if(s_Hzoff%7 == 0)
							{							
								s_Textbuf[0+2*s_Text] = s_Hzbuf[(s_Hzoff-1)*2];
								s_Textbuf[1+2*s_Text] = s_Hzbuf[(s_Hzoff-1)*2+1];
//									s_Textbuf[2] = s_Hzbuf[2];
								s_Textbuf[2+2*s_Text] = '\0';
//								MULTIEDIT_AddText(hMulti, s_Textbuf);
								LCD_Fill_Rect(5,10,25,800,CL_WHITE);	
								LCD_DispStr(5, 10, s_Textbuf, &FontB);//��ʾѡ��ĺ���	
								if(s_Hzbuf[0]!=0)s_Text++;	
								for(i=0;i<34;i++)
								{
									s_tempbuf[i]= '\0';	
									s_Bufview[i]= '\0';
									s_Hzbuf[i]='\0';
								}
								s_Offset=0;
								LCD_Fill_Rect(5,155,25,500,CL_WHITE);	
								LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);												
							}
						}
						else
						{
							if(s_RightFlag == 1)	//1��ʾ��ǰ��Ŀ�Ҳ���δ��ʾ����
							{
								s_LeftFlag = 1;
								s_Bufview[0] = '1';
								s_Bufview[1] = '<';
								s_Bufview[2] = ' ';		
								if (s_Hznum <= (s_Hzoff + 7))
								{
									int k = s_Hznum - s_Hzoff;
									for (j = 0; j < k;j++)
									{
										s_Bufview[j*4+3] = j+'2';
										s_Bufview[j*4+4] = s_Hzbuf[(s_Hzoff)*2];
										s_Bufview[j*4+5] = s_Hzbuf[(s_Hzoff)*2+1];
//											s_Bufview[j*4+6] = s_Hzbuf[(s_Hzoff)*2+2];
										s_Bufview[j*4+6] = ' ';
										s_Hzoff++;
									}
									s_Bufview[k*4+3] = '\0';	
									s_RightFlag = 0;
								}
								else
								{
									for (j = 0; j < 7;j++)
									{
										s_Bufview[j*4+3] = j + '2';
										s_Bufview[j*4+4] = s_Hzbuf[s_Hzoff*2];
										s_Bufview[j*4+5] = s_Hzbuf[s_Hzoff*2+1];
//												s_Bufview[j*4+6] = s_Hzbuf[s_Hzoff*2+2];
										s_Bufview[j*4+6] = ' ';
										s_Hzoff++;
									}

									s_Bufview[31] = '9';
									s_Bufview[32] = '>';
									s_Bufview[33] = 0;

									s_RightFlag = 1;
								}
							}
						}
//							TEXT_SetText(ahText[1],s_Bufview);	
						LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);								
						LCD_DispStr(5, 180, s_Bufview, &FontB);//��ʾԤѡ����								
					}
					/* ����9����***********************************************************/
					else if(s_Key == '9')
					{
						if((s_LeftFlag == 1)&&(s_RightFlag == 1))
						{
							s_LeftFlag = 1;
							s_Bufview[0] = '1';
							s_Bufview[1] = '<';
							s_Bufview[2] = ' ';		
							if (s_Hznum <= (s_Hzoff + 7))
							{
								int k = s_Hznum - s_Hzoff;
								for (j = 0; j < k;j++)
								{
									s_Bufview[j*4+3] = j+'2';
									s_Bufview[j*4+4] = s_Hzbuf[(s_Hzoff)*2];
									s_Bufview[j*4+5] = s_Hzbuf[(s_Hzoff)*2+1];
//											s_Bufview[j*4+6] = s_Hzbuf[(s_Hzoff)*2+2];
									s_Bufview[j*4+6] = ' ';
									s_Hzoff++;
								}
								s_Bufview[k*4+3] = 0;	
								s_RightFlag = 0;
							}
							else
							{
								for (j = 0; j < 7;j++)
								{
									s_Bufview[j*4+3] = j + '2';
									s_Bufview[j*4+4] = s_Hzbuf[s_Hzoff*2];
									s_Bufview[j*4+5] = s_Hzbuf[s_Hzoff*2+1];
//											s_Bufview[j*4+6] = s_Hzbuf[s_Hzoff*2+2];
									s_Bufview[j*4+6] = ' ';
									s_Hzoff++;
								}

								s_Bufview[31] = '9';
								s_Bufview[32] = '>';
								s_Bufview[33] = 0;

								s_RightFlag = 1;
							}
						}						
//								TEXT_SetText(ahText[1],s_Bufview);
						LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);
						LCD_DispStr(5, 180, s_Bufview, &FontB);//��ʾԤѡ����
					}
					/* ����2-7����***********************************************************/
					else if((s_Key>='2')&&(s_Key<='7'))
					{
						if(s_LeftFlag == 1)
						{
							if(s_Hzoff%7 == 0)
							{
								s_Textbuf[0+2*s_Text]=s_Hzbuf[(s_Key-'2' + s_Hzoff - 7)*2];
								s_Textbuf[1+2*s_Text]=s_Hzbuf[(s_Key-'2' + s_Hzoff - 7)*2+1];
//										s_Textbuf[2]=s_Hzbuf[(s_Key-'2' + s_Hzoff - 7)*3+2];
							}
							else
							{
								s_Textbuf[0+2*s_Text]=s_Hzbuf[(s_Key-'2' + (s_Hzoff/7)*7)*2];
								s_Textbuf[1+2*s_Text]=s_Hzbuf[(s_Key-'2' + (s_Hzoff/7)*7)*2+1];
//										s_Textbuf[2]=s_Hzbuf[(s_Key-'2' + (s_Hzoff/7)*7)*3+2];
							}
							
							s_Textbuf[2+2*s_Text] = '\0';
							LCD_Fill_Rect(5,10,25,800,CL_WHITE);	
							LCD_DispStr(5, 10, s_Textbuf, &FontB);//��ʾѡ��ĺ���	
							if(s_Hzbuf[0]!=0)s_Text++;	
							for(i=0;i<34;i++)
							{
								s_tempbuf[i]= '\0';	
								s_Bufview[i]= '\0';
								s_Hzbuf[i]='\0';
							}
							s_Offset=0;
							LCD_Fill_Rect(5,155,25,500,CL_WHITE);	
							LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);									
						}
						else
						{							
							s_Textbuf[0+2*s_Text] = s_Hzbuf[(s_Key-'1')*2];
							s_Textbuf[1+2*s_Text] = s_Hzbuf[(s_Key-'1')*2+1];
//									s_Textbuf[2] = s_Hzbuf[2];
							s_Textbuf[2+2*s_Text] = '\0';
							LCD_Fill_Rect(5,10,25,800,CL_WHITE);	
							LCD_DispStr(5, 10, s_Textbuf, &FontB);//��ʾѡ��ĺ���	
							if(s_Hzbuf[0]!=0)s_Text++;	
							for(i=0;i<34;i++)
							{
								s_tempbuf[i]= '\0';	
								s_Bufview[i]= '\0';
								s_Hzbuf[i]='\0';
							}
							s_Offset=0;
							LCD_Fill_Rect(5,155,25,500,CL_WHITE);	
							LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);										
						}
					}
					/* ������������ ***************************************************/
					else
					{			
						/* �ڻ�û�����뺺�ֵ�����£����ڹ��ܼ��Ĵ��� */
//								if(s_Offset == 0)
//								{
//									/* ���»س��� */
//									if(strncmp((const char *)_aButtonData[BUTTON_Num].acLabel, "Enter", sizeof(_aButtonData[BUTTON_Num].acLabel)) == 0)
//									{
////										MULTIEDIT_AddKey(hMulti, GUI_KEY_ENTER);
//										break;
//									}
//									/* ���»ظ�� */
//									if(strncmp((const char *)_aButtonData[BUTTON_Num].acLabel, "Back", sizeof(_aButtonData[BUTTON_Num].acLabel)) == 0)
//									{
////										MULTIEDIT_AddKey(hMulti, GUI_KEY_BACKSPACE);
////										LCD_DispStr(5, 10, s_Textbuf, &FontB);//��ʾԤѡ����		
//										break;
//									}
//								}					
//							TEXT_SetBkColor(ahText[0],GUI_LIGHTGRAY);
						/* ����ظ��*/
						if(strncmp((const char *)_aButtonData[BUTTON_Num].acLabel, "Back", sizeof(_aButtonData[BUTTON_Num].acLabel)) == 0)
						{
							/* ʵ�ֺ���ƴ�������ɾ�� */
							if(s_Offset > 0)
							{
								s_Offset--;
							}								
							/* ƴ��ɾ����ϣ��˳����ֺ�ƴ������ʾ */
							else 
							{															
								if(s_Text>0)s_Text--;
								s_Textbuf[2*s_Text] = '\0';
								LCD_Fill_Rect(5,10,25,500,CL_WHITE);
								LCD_DispStr(5, 10, s_Textbuf, &FontB);//��ʾѡ��ĺ���										
							}
							s_tempbuf[s_Offset]= '\0';
						}
						else if(strncmp((const char *)_aButtonData[BUTTON_Num].acLabel, "Enter", sizeof(_aButtonData[BUTTON_Num].acLabel)) == 0)
						{
							dis_keyboard=0;
						}
						else
						{
							/* ����������������Ƽ������������Ŀ��Ƽ��˳���ʾ */
							if(_aButtonData[BUTTON_Num].Control == 1)
							{
								break;
							}									
							/* ���������ƴ����װ�뻺�� */
							s_tempbuf[s_Offset++]= s_Key;									
						}
//					TEXT_SetText(ahText[0], (const char *)s_tempbuf);
						LCD_Fill_Rect(5,155,25,500,CL_WHITE);
						LCD_DispStr(5, 155,   (char *)s_tempbuf, &FontB);
						ptr = PYSearch(s_tempbuf, (int *)&s_Hznum);
						if (ptr != '\0')
						{
							for (j = 0; j < s_Hznum*2; j++)
							{
								s_Hzbuf[j] = *ptr++;
							}
							s_Hzbuf[s_Hznum*2] = '\0';						
//								TEXT_SetBkColor(ahText[1],GUI_LIGHTGRAY);
							if (s_Hznum > 0)
							{	
//								printf("s_Hznum = %d\r\n", s_Hznum);
								s_Hzoff = 0;
								s_LeftFlag = 0;	//1��ʾ��ǰ��Ŀ�����δ��ʾ����

								if ((s_Hzoff +7) >= s_Hznum )
								{
									int k = s_Hznum - s_Hzoff;									
									for (j = 0; j < k;j++)
									{
										s_Bufview[j*4+0] = j+'1';
										s_Bufview[j*4+1] = s_Hzbuf[s_Hzoff*2];
										s_Bufview[j*4+2] = s_Hzbuf[s_Hzoff*2+1];
//											s_Bufview[j*5+3] = s_Hzbuf[s_Hzoff*2+2];
										s_Bufview[j*4+3] = ' ';
										s_Hzoff++;
									}
									s_Bufview[k*4] = '\0';
								}
								else
								{
									for (j = 0; j < 7;j++)
									{
										s_Bufview[j*4+0] = j + '1';
										s_Bufview[j*4+1] = s_Hzbuf[s_Hzoff*2];
										s_Bufview[j*4+2] = s_Hzbuf[s_Hzoff*2+1];
//											s_Bufview[j*5+3] = s_Hzbuf[s_Hzoff*3+2];
										s_Bufview[j*4+3] = ' ';
										s_Hzoff++;
									}
									s_Bufview[28] = '8';
									s_Bufview[29] = '>';
									s_Bufview[30] = '\0';
									s_RightFlag = 1;	//1��ʾ��ǰ��Ŀ�Ҳ���δ��ʾ����
								}
							}
//								TEXT_SetText(ahText[1],s_Bufview);
							LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);
							LCD_DispStr(5, 180, s_Bufview, &FontB);//��ʾԤѡ����
						}
						else
						{
							LCD_Fill_Rect(5,180,25,700,M_BACKGROUND_COLOR);
//								LCD_DispStr(5, 180," ", &FontB);//��ʾԤѡ����
						}
					}
				}/* �ַ���ʾ*******************************************************************/
//				else
//				{
////					/* ����س��� */
////					if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "Enter", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
////					{
////						MULTIEDIT_AddKey(hMulti, GUI_KEY_ENTER);
////						break;
////					}					
//					/* ����ظ�� */
//					if(strncmp((const char *)_aButtonData[BUTTON_Num].acLabel, "Back", sizeof(_aButtonData[BUTTON_Num].acLabel)) == 0)
//					{
//						if((s_Textbuf[2*s_Text+s_Char]-3)<0x80)
//						{
//							if((s_Textbuf[2*s_Text+s_Char]-2)<0x80)
//							{
//								
//							}
//							else 
//							{
//								
//							}
//						}
//						break;
//					}
//					/* �����������������ǹ��ܼ� */
//					if(_aButtonData[Id - BUTTON_Num].Control == 0)
//					{
//						s_Textbuf[2*s_Text+s_Char] = s_Key;
//						s_Textbuf[1+2*s_Text+s_Char] = '\0';
//						s_Char++;
//						LCD_DispStr(5, 10, s_Textbuf, &FontB);//��ʾѡ��ĺ���	
//					}
//				}
			default: break;
		}
	}
}
/*
*********************************************************************************************************
*	�� �� ��: _cbKeyPad
*	����˵��: �ص�����
*	��    �Σ�pMsg  ָ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//static void _cbKeyPad(WM_MESSAGE * pMsg) 
//{
//	WM_HWIN    hWin;
//	WM_HWIN    hButton;
//	int        Id;
//	int        NCode;
//	int        xSize;
//	int        ySize;
//	unsigned   i;

//	hWin = pMsg->hWin;
//	switch (pMsg->MsgId) 
//	{
//		/* ��������İ�ť */
//		case WM_CREATE:
//			for (i = 0; i < GUI_COUNTOF(_aButtonData); i++) 
//			{
//				hButton = BUTTON_CreateEx(_aButtonData[i].xPos, _aButtonData[i].yPos, _aButtonData[i].xSize, _aButtonData[i].ySize, 
//				hWin, WM_CF_SHOW, 0, BUTTON_Num + i);
//				BUTTON_SetFont(hButton, &GUI_Font16B_ASCII);
//				BUTTON_SetText(hButton, _aButtonData[i].acLabel);
//				BUTTON_SetFocussable(hButton, 0);
//			}
//			break;
//		
//		/* ���Ʊ��� */	
//		case WM_PAINT:	
//			xSize = WM_GetWindowSizeX(hWin);
//			ySize = WM_GetWindowSizeY(hWin);
//			GUI_SetColor(COLOR_BORDER);
//			GUI_DrawRect(0, 0, xSize - 1, ySize - 1);
//			GUI_DrawGradientV(1, 1, xSize - 2, ySize - 2, COLOR_KEYPAD0, COLOR_KEYPAD1);
//			break;
//		
//		/* ���ڴ���ť����Ϣ */
//		case WM_NOTIFY_PARENT:
//			Id    = WM_GetId(pMsg->hWinSrc);
//			NCode = pMsg->Data.v;
//			switch (NCode) 
//			{
//				case WM_NOTIFICATION_RELEASED:
//					if (_aButtonData[Id - BUTTON_Num].acLabel) 
//					{
//						/* ��һ����ʵ����ĸ��Сд���л� *******************************************/
//						if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "Caps", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
//						{
//							/* ��ǰ��Сд���л�����д��������Ӣ��ģʽ��ʵ�ִ�Сд�л�*/
//							if((s_CapsLock == 0)&&(s_SelectLangue == 1))
//							{
//								for (i = 0; i < GUI_COUNTOF(_aButtonData); i++) 
//								{
//									BUTTON_SetText(WM_GetDialogItem(hWin, BUTTON_Num + i), _aButtonData[i].acLabel1);
//								}
//								s_CapsLock = 1;
//							}
//							else if((s_CapsLock == 1)&&(s_SelectLangue == 1))
//							{
//								for (i = 0; i < GUI_COUNTOF(_aButtonData); i++) 
//								{
//									BUTTON_SetText(WM_GetDialogItem(hWin, BUTTON_Num + i), _aButtonData[i].acLabel);
//								}
//								s_CapsLock = 0;
//							}

//							/* ���ܼ�������Ҫ�˳� */
//							break;
//						}

//						/* �ڶ����� ʵ����Ӣ�ĵ��л� ********************************************/
//						if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "C/e", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0
//						|strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "c/E", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
//						{
//							/* ��ǰ��Ӣ�ģ�������Сд��ĸ��ʱ��ſ����л�  */
//							if((s_SelectLangue == 1)&&(s_CapsLock == 0))
//							{
//								s_SelectLangue = 0;
//								BUTTON_SetText(WM_GetDialogItem(hWin, Id), "C/e");
//							}
//							else if((s_SelectLangue == 0)&&(s_CapsLock == 0))
//							{
//								s_SelectLangue = 1;
//								BUTTON_SetText(WM_GetDialogItem(hWin, Id), "c/E");
//							}

//							/* ���ܼ�������Ҫ�˳� */
//							break;
//						}

//						/* ����������ĸ��Сд��ʶ�� ********************************************/
//						if(s_CapsLock == 0)
//						{
//							s_Key = _aButtonData[Id - BUTTON_Num].acLabel[0];
//						}
//						/* ��д��ĸ */
//						else
//						{
//							s_Key = _aButtonData[Id - BUTTON_Num].acLabel1[0];
//						}

//						/* ���Ĳ������Ĵ��� **************************************************/
//						if(s_SelectLangue == 0)
//						{		
//							int j;
//							char *ptr;

//							/* ����1����***********************************************************/
//							if(s_Key == '1')
//							{
//								/* ��������δ��ʾ�ĺ��� */
//								if(s_LeftFlag == 1)
//								{
//									/* ��Ϊÿ����������ʾ7�����֣����Գ�������7�ĵط��ܶ� */
//									if(s_Hzoff%7 == 0)
//									{
//										s_Hzoff -= 7;	
//									}
//									else
//									{
//										s_Hzoff = s_Hzoff - (s_Hzoff % 7);	
//									}
//									
//									s_Hzoff -= 7;

//									s_RightFlag = 1;

//									/* ���ƫ�Ƶ�ַ֮ǰ����7�����ϵĺ��� */
//									if(s_Hzoff >= 7)
//									{
//										s_Bufview[0] = '1';
//										s_Bufview[1] = '<';
//										s_Bufview[2] = ' ';
//										
//										for (j = 0; j < 7;j++)
//										{
//											s_Bufview[j*5+3] = j+'2';
//											s_Bufview[j*5+4] = s_Hzbuf[(s_Hzoff)*3];
//											s_Bufview[j*5+5] = s_Hzbuf[(s_Hzoff)*3+1];
//											s_Bufview[j*5+6] = s_Hzbuf[(s_Hzoff)*3+2];
//											s_Bufview[j*5+7] = ' ';
//											s_Hzoff++;
//										}

//										s_Bufview[38] = '9';
//										s_Bufview[39] = '>';
//										s_Bufview[40] = 0;
//										s_LeftFlag = 1;
//									}
//									/* ���ƫ�Ƶ�ַ֮ǰ������С��7 */
//									else
//									{	
//										s_LeftFlag = 0;
//										for (j = 0; j < 7;j++)
//										{
//											s_Bufview[j*5+0] = j+'1';
//											s_Bufview[j*5+1] = s_Hzbuf[(s_Hzoff)*3];
//											s_Bufview[j*5+2] = s_Hzbuf[(s_Hzoff)*3+1];
//											s_Bufview[j*5+3] = s_Hzbuf[(s_Hzoff)*3+2];
//											s_Bufview[j*5+4] = ' ';
//											s_Hzoff++;
//										}

//										s_Bufview[35] = '8';
//										s_Bufview[36] = '>';
//										s_Bufview[37] = '\0';
//									}
//								}
//								/* ���û�к��֣�ֱ����ʾ��һ������ */
//								else
//								{
//									s_Textbuf[0] = s_Hzbuf[0];
//									s_Textbuf[1] = s_Hzbuf[1];
//									s_Textbuf[2] = s_Hzbuf[2];
//									s_Textbuf[3] = '\0';
//									MULTIEDIT_AddText(hMulti, s_Textbuf);
//								}
//								
//								TEXT_SetText(ahText[1],s_Bufview);
//							}
//							/* ����8����***********************************************************/
//							else if(s_Key == '8')
//							{
//								if(s_LeftFlag == 1)
//								{
//									if(s_Hzoff%7 == 0)
//									{							
//										s_Textbuf[0] = s_Hzbuf[(s_Hzoff - 1)*3];
//										s_Textbuf[1] = s_Hzbuf[(s_Hzoff - 1)*3+1];
//										s_Textbuf[2] = s_Hzbuf[(s_Hzoff - 1)*3+2];
//										s_Textbuf[3] = '\0';
//										MULTIEDIT_AddText(hMulti, s_Textbuf);
//									}
//								}
//								else
//								{
//									if(s_RightFlag == 1)	//1��ʾ��ǰ��Ŀ�Ҳ���δ��ʾ����
//									{
//										s_LeftFlag = 1;
//										s_Bufview[0] = '1';
//										s_Bufview[1] = '<';
//										s_Bufview[2] = ' ';		
//										if (s_Hznum <= (s_Hzoff + 7))
//										{
//											int k = s_Hznum - s_Hzoff;
//											for (j = 0; j < k;j++)
//											{
//												s_Bufview[j*5+3] = j+'2';
//												s_Bufview[j*5+4] = s_Hzbuf[(s_Hzoff)*3];
//												s_Bufview[j*5+5] = s_Hzbuf[(s_Hzoff)*3+1];
//												s_Bufview[j*5+6] = s_Hzbuf[(s_Hzoff)*3+2];
//												s_Bufview[j*5+7] = ' ';
//												s_Hzoff++;
//											}
//											s_Bufview[k*5+3] = '\0';	
//											s_RightFlag = 0;
//										}
//										else
//										{
//											for (j = 0; j < 7;j++)
//											{
//												s_Bufview[j*5+3] = j + '2';
//												s_Bufview[j*5+4] = s_Hzbuf[s_Hzoff*3];
//												s_Bufview[j*5+5] = s_Hzbuf[s_Hzoff*3+1];
//												s_Bufview[j*5+6] = s_Hzbuf[s_Hzoff*3+2];
//												s_Bufview[j*5+7] = ' ';
//												s_Hzoff++;
//											}

//											s_Bufview[38] = '9';
//											s_Bufview[39] = '>';
//											s_Bufview[40] = 0;

//											s_RightFlag = 1;
//										}
//									}
//								}

//								TEXT_SetText(ahText[1],s_Bufview);						
//							}
//							/* ����9����***********************************************************/
//							else if(s_Key == '9')
//							{
//								if((s_LeftFlag == 1)&&(s_RightFlag == 1))
//								{
//									s_LeftFlag = 1;
//									s_Bufview[0] = '1';
//									s_Bufview[1] = '<';
//									s_Bufview[2] = ' ';		
//									if (s_Hznum <= (s_Hzoff + 7))
//									{
//										int k = s_Hznum - s_Hzoff;
//										for (j = 0; j < k;j++)
//										{
//											s_Bufview[j*5+3] = j+'2';
//											s_Bufview[j*5+4] = s_Hzbuf[(s_Hzoff)*3];
//											s_Bufview[j*5+5] = s_Hzbuf[(s_Hzoff)*3+1];
//											s_Bufview[j*5+6] = s_Hzbuf[(s_Hzoff)*3+2];
//											s_Bufview[j*5+7] = ' ';
//											s_Hzoff++;
//										}
//										s_Bufview[k*5+3] = 0;	
//										s_RightFlag = 0;
//									}
//									else
//									{
//										for (j = 0; j < 7;j++)
//										{
//											s_Bufview[j*5+3] = j + '2';
//											s_Bufview[j*5+4] = s_Hzbuf[s_Hzoff*3];
//											s_Bufview[j*5+5] = s_Hzbuf[s_Hzoff*3+1];
//											s_Bufview[j*5+6] = s_Hzbuf[s_Hzoff*3+2];
//											s_Bufview[j*5+7] = ' ';
//											s_Hzoff++;
//										}

//										s_Bufview[38] = '9';
//										s_Bufview[39] = '>';
//										s_Bufview[40] = 0;

//										s_RightFlag = 1;
//									}
//								}						
//								TEXT_SetText(ahText[1],s_Bufview);
//							}
//							/* ����2-7����***********************************************************/
//							else if((s_Key>='2')&&(s_Key<='7'))
//							{
//								if(s_LeftFlag == 1)
//								{
//									if(s_Hzoff%7 == 0)
//									{
//										s_Textbuf[0]=s_Hzbuf[(s_Key-'2' + s_Hzoff - 7)*3];
//										s_Textbuf[1]=s_Hzbuf[(s_Key-'2' + s_Hzoff - 7)*3+1];
//										s_Textbuf[2]=s_Hzbuf[(s_Key-'2' + s_Hzoff - 7)*3+2];
//									}
//									else
//									{
//										s_Textbuf[0]=s_Hzbuf[(s_Key-'2' + (s_Hzoff/7)*7)*3];
//										s_Textbuf[1]=s_Hzbuf[(s_Key-'2' + (s_Hzoff/7)*7)*3+1];
//										s_Textbuf[2]=s_Hzbuf[(s_Key-'2' + (s_Hzoff/7)*7)*3+2];
//									}
//									
//									s_Textbuf[3] = '\0';
//									MULTIEDIT_AddText(hMulti, s_Textbuf);					
//								}
//								else
//								{
//									s_Textbuf[0] = s_Hzbuf[(s_Key-'1')*3];
//									s_Textbuf[1] = s_Hzbuf[(s_Key-'1')*3+1];
//									s_Textbuf[2] = s_Hzbuf[(s_Key-'1')*3+2];
//									s_Textbuf[3] = '\0';
//									MULTIEDIT_AddText(hMulti, s_Textbuf);
//								}
//							}
//							/* ������������ ***************************************************/
//							else
//							{			
//								/* �ڻ�û�����뺺�ֵ�����£����ڹ��ܼ��Ĵ��� */
//								if(s_Offset == 0)
//								{
//									/* ���»س��� */
//									if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "Enter", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
//									{
//										MULTIEDIT_AddKey(hMulti, GUI_KEY_ENTER);
//										break;
//									}
//									/* ���»ظ�� */
//									if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "Back", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
//									{
//										MULTIEDIT_AddKey(hMulti, GUI_KEY_BACKSPACE);
//										break;
//									}
//								}
//								
//								TEXT_SetBkColor(ahText[0],GUI_LIGHTGRAY);
//								/* ����ظ��*/
//								if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "Back", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
//								{
//									/* ʵ�ֺ���ƴ�������ɾ�� */
//									if(s_Offset > 0)
//									{
//										s_Offset--;
//										s_tempbuf[s_Offset]= '\0';
//									}
//									
//									/* ƴ��ɾ����ϣ��˳����ֺ�ƴ������ʾ */
//									if(s_Offset == 0)
//									{
//										WM_HideWindow(ahText[0]);
//										WM_HideWindow(ahText[1]);
//										WM_InvalidateWindow(ahText[0]);
//										WM_InvalidateWindow(ahText[1]);
//										break;
//									}

//								}
//								else
//								{
//									/* ����������������Ƽ������������Ŀ��Ƽ��˳���ʾ */
//									if(_aButtonData[Id - BUTTON_Num].Control == 1)
//									{
//										break;
//									}
//									
//									/* ���������ƴ����װ�뻺�� */
//									s_tempbuf[s_Offset++]= s_Key;
//									
//									WM_ShowWindow(ahText[0]);
//									WM_ShowWindow(ahText[1]);
//								}

//								TEXT_SetText(ahText[0], (const char *)s_tempbuf);
//								ptr = PYSearch(s_tempbuf, (int *)&s_Hznum);

//								if (ptr != '\0')
//								{
//									for (j = 0; j < s_Hznum*3; j++)
//									{
//										s_Hzbuf[j] = *ptr++;
//									}
//									s_Hzbuf[s_Hznum*3] = '\0';						
//									TEXT_SetBkColor(ahText[1],GUI_LIGHTGRAY);

//									if (s_Hznum > 0)
//									{	
//										printf("s_Hznum = %d\r\n", s_Hznum);
//										s_Hzoff = 0;
//										s_LeftFlag = 0;	//1��ʾ��ǰ��Ŀ�����δ��ʾ����

//										if ((s_Hzoff +7) >= s_Hznum )
//										{
//											int k = s_Hznum - s_Hzoff;									
//											for (j = 0; j < k;j++)
//											{
//												s_Bufview[j*5+0] = j+'1';
//												s_Bufview[j*5+1] = s_Hzbuf[s_Hzoff*3];
//												s_Bufview[j*5+2] = s_Hzbuf[s_Hzoff*3+1];
//												s_Bufview[j*5+3] = s_Hzbuf[s_Hzoff*3+2];
//												s_Bufview[j*5+4] = ' ';
//												s_Hzoff++;
//											}
//											s_Bufview[k*5] = '\0';
//										}
//										else
//										{
//											for (j = 0; j < 7;j++)
//											{
//												s_Bufview[j*5+0] = j + '1';
//												s_Bufview[j*5+1] = s_Hzbuf[s_Hzoff*3];
//												s_Bufview[j*5+2] = s_Hzbuf[s_Hzoff*3+1];
//												s_Bufview[j*5+3] = s_Hzbuf[s_Hzoff*3+2];
//												s_Bufview[j*5+4] = ' ';
//												s_Hzoff++;
//											}

//											s_Bufview[35] = '8';
//											s_Bufview[36] = '>';
//											s_Bufview[37] = '\0';

//											s_RightFlag = 1;	//1��ʾ��ǰ��Ŀ�Ҳ���δ��ʾ����
//										}
//									}
//									TEXT_SetText(ahText[1],s_Bufview);
//								}
//								else
//								{
//									TEXT_SetBkColor(ahText[1],GUI_WHITE);
//									TEXT_SetText(ahText[1],"");
//								}
//							}
//						}
//					/* �ַ���ʾ*******************************************************************/
//					else
//					{
//						/* ����س��� */
//						if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "Enter", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
//						{
//							MULTIEDIT_AddKey(hMulti, GUI_KEY_ENTER);
//							break;
//						}
//						
//						/* ����ظ�� */
//						if(strncmp((const char *)_aButtonData[Id - BUTTON_Num].acLabel, "Back", sizeof(_aButtonData[Id - BUTTON_Num].acLabel)) == 0)
//						{
//							MULTIEDIT_AddKey(hMulti, GUI_KEY_BACKSPACE);
//							break;
//						}

//						/* �����������������ǹ��ܼ� */
//						if(_aButtonData[Id - BUTTON_Num].Control == 0)
//						{
//							s_Textbuf[0] = s_Key;
//							s_Textbuf[1] = '\0';
//							MULTIEDIT_AddText(hMulti, s_Textbuf);	
//						}
//					}
//				}
//				break;
//			}
//	}
//}

///*
//*********************************************************************************************************
//*	�� �� ��: MainTask
//*	����˵��: ����ƴ���ĺ���,ʹ�úܼ򵥣�ֻ������ƴ�����з������ƴ����Ӧ�ĺ��ָ�����
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/	
//void MainTask(void) 
//{

//	/* ��ʼ������ */
//	s_Offset=0;
//	s_SelectLangue = 1;
//	s_CapsLock = 0;
//	tBtnCount.Font = &tFontBtn;
//	tBtnCount.Left = M_BUTTON_X;
//	tBtnCount.Top = M_BUTTON_Y;
//	tBtnCount.Height = M_BUTTON_H;
//	tBtnCount.Width = M_BUTTON_W;
//	tBtnCount.Focus = 1;	/* ʧȥ���� */					
//	strcpy(chCount,"����");
//	tBtnCount.pCaption = chCount;
//	LCD_DrawButton(&tBtnCount);	
//	for (i = 0; i < GUI_COUNTOF(_aButtonData); i++) 
//	{
//		hButton = BUTTON_CreateEx(_aButtonData[i].xPos, _aButtonData[i].yPos, _aButtonData[i].xSize, _aButtonData[i].ySize, 
//		hWin, WM_CF_SHOW, 0, BUTTON_Num + i);
//		BUTTON_SetFont(hButton, &GUI_Font16B_ASCII);
//		BUTTON_SetText(hButton, _aButtonData[i].acLabel);
//		BUTTON_SetFocussable(hButton, 0);
//	}

//}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
