#include "measurement.h"
#include "bsp.h"	
#include "motor.h"
#include "main_menu.h"
#include "math.h"
#include "typewriting.h"
/* 按钮的坐标 */
#define BUTTON_RET_H	45
#define BUTTON_RET_W	90
#define	BUTTON_RET_X	50
#define	BUTTON_RET_Y	360
#define RETURN_RET_H	45
#define RETURN_RET_W	90
#define	RETURN_RET_X	160
#define	RETURN_RET_Y	360
/* 进度条的坐标 */
#define BAR_RET_H	20
#define BAR_RET_W	23
#define	BAR1_RET_X	50
#define	BAR1_RET_Y	150+20
#define	BAR2_RET_X	50
#define	BAR2_RET_Y	250+40
/* 通道检测结果窗口的坐标 */
#define CH_RET_H	70
#define CH_RET_W	450
#define	CH1_RET_X	300
#define	CH1_RET_Y	100+20
#define	CH2_RET_X	300
#define	CH2_RET_Y	200+40
/*通道状态显示坐标*/
#define CHBUTTON_RET_H	30
#define CHBUTTON_RET_W	30
#define	CH1BUTTON_RET_X	50
#define	CH1BUTTON_RET_Y	100+20
#define	CH2BUTTON_RET_X	50
#define	CH2BUTTON_RET_Y	200+40
/* 姓名编辑标签坐标*/
#define NAME_RET_H	30
#define NAME_RET_W	130
#define	NAME1_RET_X	120
#define	NAME1_RET_Y	100+20
#define	NAME2_RET_X	120
#define	NAME2_RET_Y	200+40
#define ABS(A) (((A)>0)?(A):(-(A)))
#define T m_lCf[7]	  //可改变试压最大压力，T务必小于5400
unsigned int m=0;
u8 	m_bIgnoreConcentrationLow=0;
double m_lCfC12[6]={0.0391,4.3608,8.0441,-11.2015,13.7568};
double m_lCfC13[6]={1.0273,1287.1415,1972.6467,-2396.7769,3653.4883};
double C12BABS=0;
double C12SABS=0;
double m_lC12B=0;
double m_lC12S=0;
double	Percent=0.600;
double 	Per=0.600;
u32	Intensitys[18];
double xbc12,xbc13, xsc12,xsc13,c12[30],c13[30],delta1[30],cz1,cz2,Ints5[30],Ints6[30];
double cbc12,cbc13,csc12,csc13;
double ratebase,ratesample;
s16 dob=0,dob1;
u8	m_bChanged;
u8	checkChannel;
u8	m_mesureType;
u8	m_bDilution;
u8	F_name;
uint8_t ucTouch;		/* 触摸事件 */
int16_t tpX, tpY;
uint8_t fButton=0;
FONT_T  tFontBtn,tFontBtnCh1;	/* 定义一个字体结构体变量，用于设置字体参数 */
BUTTON_T tBtn,tBtn1,CH1Btn,CH2Btn;
char name1[8],name2[8];
char ch[10];
void ChannelMeas(u8 Pnum);
void bsp_KeyScan(void)
{
	if(fButton==0)
		return;
	GT811_Scan();
	ucTouch = TOUCH_GetKey(&tpX, &tpY);	/* 读取触摸事件 */
	if (ucTouch != TOUCH_NONE)
	{
		switch(ucTouch)
		{
				case TOUCH_DOWN:		/* 触笔按下事件 */
//					if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
//					{						
//						tBtn.Font = &tFontBtn;
//						tBtn.Left = BUTTON_RET_X;
//						tBtn.Top = BUTTON_RET_Y;
//						tBtn.Height = BUTTON_RET_H;
//						tBtn.Width = BUTTON_RET_W;
//						tBtn.Focus = 1;	/* 焦点 */
//						strcpy(ch,"停止");		
//						tBtn.pCaption = ch;
//						LCD_DrawButton(&tBtn);							
//					}
					break;
			case TOUCH_RELEASE:	
					if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
					{
						fButton=0;
						m_bMeasureBreak=1;
//						tBtn.Font = &tFontBtn;
//						tBtn.Left = BUTTON_RET_X;
//						tBtn.Top = BUTTON_RET_Y;
//						tBtn.Height = BUTTON_RET_H;
//						tBtn.Width = BUTTON_RET_W;
//						tBtn.Focus = 0;	/* 焦点 */
//						strcpy(ch,"测量");							
//						tBtn.pCaption = ch;
//						LCD_DrawButton(&tBtn);
					}
				break;
			default:break;
		}
	}
}
void  Air(void)
{
  u8 i;
	Valve(171);
	Valve(181);		//3180-->3500
	Motorun(0,3500,FORWARD,0,  30,65,8,20, 30,5,20,0,    81,150,160);      //抽气
	Motorun(0,3500,BACKWARD,0, 30,65,8,20, 30,5,20,200,  80,151,170);      //打气,清洗
	for(i=0;i<2;i++)
	{
		Motorun(0,3500,FORWARD,0,  30,65,8,20, 30,5,20,0,    81,150,171);      //抽气
		Motorun(0,3500,BACKWARD,0, 30,65,8,20, 30,5,20,200,  80,151,170);      //打气,清洗
		bsp_DelayMS(4);
	}

	Motorun(0,3500,FORWARD,0,      30,65,8,20,  30,5,20,0,   81,150,171);      //抽气
	bsp_DelayMS(514);
	Valve(170);
	Valve(180);
	Motorun(0,3500,BACKWARD,1,     27,27,0,1,  30,0,20,200, 80,151,170);      //打气，慢推1~3r/s，过程中测参比气体吸光度
	bsp_DelayMS(200);	
	Valve(150);
	bsp_DelayMS(23);

}
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
/*-----------------------------
初步样气测量程序
-----------------------------------*/
void	SampleFirst(u8 Pnum,u16 m)
{
    u8 OpenValve=0,CloseValve=0;
    switch(Pnum)
    {
    case 1:
        OpenValve=21,CloseValve=20;
        break;
    case 2:
        OpenValve=41,CloseValve=40;
        break;
    case 3:
        OpenValve=61,CloseValve=60;
        break;
    case 4:
        OpenValve=101,CloseValve=100;
        break;
    case 5:
        OpenValve=121,CloseValve=120;
        break;
    case 6:
        OpenValve=141,CloseValve=140;
        break;
    default:
        break;
    }

Valve(171);	
	Valve(181);		  //1570-->1800
	Motorun(0,1800,FORWARD,0,      30,60,8,20,      30,6,20,0, 	 OpenValve, 150, 160);   //抽气 4~8r/s	脉冲数:1500
	Valve(CloseValve); Valve(170);	
	bsp_DelayMS(22);
	Valve(151);
	bsp_DelayMS(2);
	Motorun(0,1800,BACKWARD,0,     30,60,8,20,      30,6,20,200,	 0, 0, 0);  //打气，底气清洗
	Valve(171);
	Valve(OpenValve);
	bsp_DelayMS(2);
	Valve(150);
	bsp_DelayMS(27);	
	
  	Motorun(0,T,FORWARD,0,      30,60,8,20,      30,6,20,0, 	 0, 0, 0);   //抽气，满行程
	
	bsp_DelayMS(1532);
	
	Valve(CloseValve);
	bsp_DelayMS(25);
	Valve(170);
	Valve(151);
	bsp_DelayMS(2);	
	Motorun(0, m,  BACKWARD,0,     30,30,0,0,      30,0,0,0,	 	 0, 0, 0);  //反推m个脉冲  ,速度4~5r/s
	bsp_DelayMS(1024);
	Valve(161);
	bsp_DelayMS(54);
	Motorun(1,T-m,BACKWARD,0,   20,30,1,20, 20,5,50,200	, 0, 0, 0);  //打气至底
	bsp_DelayMS(480);
	Valve(150);
	bsp_DelayMS(664);         
    //转换发送数据
	AK_Conv(); Valve(151);
	Valve(160);//排气  
	bsp_DelayMS(183);	
}
void	BaseFirst(u8 Pnum,u16 m)
{
    u8 OpenValve=0,CloseValve=0;
    switch(Pnum)
    {
    case 1:
        OpenValve=11,CloseValve=10;
        break;
    case 2:
        OpenValve=31,CloseValve=30;
        break;
    case 3:
        OpenValve=51,CloseValve=50;
        break;
    case 4:
        OpenValve=71,CloseValve=70;
        break;
    case 5:		
        OpenValve=111,CloseValve=110;
        break;
    case 6:
        OpenValve=131,CloseValve=130;
        break;
    default:
        break;
    }

Valve(171);	
	Valve(181);	//1570-->1800
	Motorun(0,1800,FORWARD,0,      30,60,8,20,      30,6,20,0, 	 OpenValve, 150, 160);   //抽气 4~8r/s	脉冲数:1500
	Valve(CloseValve);
	Valve(170);
	bsp_DelayMS(22);
	Valve(151);
	bsp_DelayMS(2);
	Motorun(0,1800,BACKWARD,0,     30,60,8,20,      30,6,20,200,	 0, 0, 0);  //打气，底气清洗
	Valve(171);
	Valve(OpenValve);
	bsp_DelayMS(2);
	Valve(150);
	bsp_DelayMS(27);	
	
  	Motorun(0,T,FORWARD,0,      30,60,8,20,      30,6,20,0, 	 0, 0, 0);   //抽气，满行程
	
	bsp_DelayMS(1532);
	
	Valve(CloseValve);
	bsp_DelayMS(25);
	Valve(170);
	Valve(151);
	bsp_DelayMS(2);	
	Motorun(0, m,  BACKWARD,0,     30,30,0,0,      30,0,0,0,	 	 0, 0, 0);  //反推m个脉冲  ,速度4~5r/s
	bsp_DelayMS(1024);
	Valve(161);
	bsp_DelayMS(54);
	Motorun(1,T-m,BACKWARD,0,   20,30,1,20, 20,5,50,200	, 0, 0, 0);  //打气至底
	bsp_DelayMS(480);
	Valve(150);

	bsp_DelayMS(1362);         
    //转换发送数据
	AK_Conv(); Valve(151);
	Valve(160);//排气  
	bsp_DelayMS(43);
}
void Sample(u8 Pnum,u16 pulse,double percent,u8 t)
{
    u8 	OpenValve=0,CloseValve=0;
    u8	TempValveOpen	= 91;
    u8	TempValveClose	= 90;
    u16	i;

    switch(Pnum)
    {
    case 11:
        OpenValve=11,CloseValve=10;
        break;
    case 12:
        OpenValve=31,CloseValve=30;
        break;
    case 13:
        OpenValve=51,CloseValve=50;
        break;
    case 14:
        OpenValve=71,CloseValve=70;
        break;
    case 15:
        OpenValve=111,CloseValve=110;
        break;
    case 16:
        OpenValve=131,CloseValve=130;
        break;
    case 21:
        OpenValve=21,CloseValve=20;
        break;
    case 22:
        OpenValve=41,CloseValve=40;
        break;
    case 23:
        OpenValve=61,CloseValve=60;
        break;
    case 24:
        OpenValve=101,CloseValve=100;
        break;
    case 25:
        OpenValve=121,CloseValve=120;
        break;
    case 26:
        OpenValve=141,CloseValve=140;
        break;
    default:
        break;
    }
    
	if(percent>0.95)
		t=0;
	Valve(171);
	Valve(181);
	if(t==0)
	{	
	    Motorun(0,2875,FORWARD,0,  30,60,8,20,  30,6,20,0, OpenValve, 150, 160);   //抽气 4~8r/s	脉冲数:1500
    	bsp_DelayMS(300);	 //200
		Motorun(0,2875,BACKWARD,0, 30,60,8,20,  30,6,20,200,CloseValve, 151, 160);  //打气，底气清洗 
		bsp_DelayMS(10);
  		Motorun(0,T,FORWARD,0,  30,60,8,20,  30,6,20,0,  OpenValve, 151, 161);   //抽气，满行程
		bsp_DelayMS(300);
	}
	else
	{				
		i	= (u16)(2875*percent);
		Motorun(0,    i,FORWARD,0, 30,60,4,20,  30,4,20,0,  OpenValve, 150, 160);   //抽气 4~8r/s	脉冲数:1500
		bsp_DelayMS(300);
		Valve(CloseValve);
		Motorun(0,2875-i,FORWARD,0,30,30,0,0, 30,0,0,0, 	 TempValveOpen, 150, 160);   //抽气 4~8r/s	脉冲数:1500
		bsp_DelayMS(300);
		Motorun(0,2875,BACKWARD,0, 30,30,8,20, 30,6,20,200, TempValveClose, 151, 160);  //打气，底气清洗
		bsp_DelayMS(10);

		i	= (u16)(T*percent);
  		Motorun(0, i,FORWARD,0,30,60,4,20,  30,4,20,0, OpenValve, 150, 160);   //抽气，
		bsp_DelayMS(300);
		Valve(CloseValve);
		Motorun(0,T-i,FORWARD,0,30,30,0,0, 30,0,0,0, 	 TempValveOpen, 150, 160);   //抽气 4~8r/s	脉冲数:1500
		bsp_DelayMS(300);
		Valve(170);
		Motorun(1,T,BACKWARD,0,  20,30,1,20, 20,5,50,200, TempValveClose, 151, 161);  //打气
		Motorun(0,T,FORWARD,0, 	 30,60,8,20, 30,6,20,0, 	 0, 0, 0);   //抽气 		
		Motorun(1,T,BACKWARD,0,  20,30,1,20, 20,5,50,200, 0, 0, 0);  //打气
		bsp_DelayMS(400);
		Motorun(0,T,FORWARD,0, 	 30,60,8,20, 30,6,20,0, 	 0, 0, 0);   //抽气 
	}
	Valve(CloseValve);
	Valve(170);
	Motorun(0, pulse,  BACKWARD,0,     30,30,0,0,  30,0,0,0,	 CloseValve, 151, 160);  //反推m个脉冲  ,速度4~5r/s
	bsp_DelayMS(300);	   //200
	Motorun(1,T-pulse,BACKWARD,0,   20,30,1,20,  20,5,50,200,0, 0, 161);  //打气至底

	bsp_DelayMS(480);
	Valve(150);
//	if(Pnum/10==2)
//		bsp_DelayMS(5700);         //共延时5s等气压稳定
//	else
	bsp_DelayMS(5000);
    //转换发送数据
//	for(t1=0;t1<10;t1++)
//	{
		AK_Conv();
//		Int1[t1+t2*10]=Intensity1;
//		Int2[t1+t2*10]=Intensity2;
//	}
//	t2+=1;
	Valve(151);
	Valve(160);//排气  
	bsp_DelayMS(200);
}
void Dis_Measurement(void)
{
	uint8_t i;	
	DispTopBar();		/* 显示顶部栏 */
	DispBottomBar();	/* 显示底部栏 */
	DispBackground();	/* 显示图标背景 */
	

	
	CH1Btn.Font = &tFontBtnCh1;
	CH1Btn.Left = CH1BUTTON_RET_X;
	CH1Btn.Top = CH1BUTTON_RET_Y;
	CH1Btn.Height = CHBUTTON_RET_H;
	CH1Btn.Width = CHBUTTON_RET_W;
	CH1Btn.Focus = 1;	/* 焦点 */
	strcpy(ch,"1");							
	CH1Btn.pCaption = ch;
	LCD_DrawButton(&CH1Btn);
	
	CH2Btn.Font = &tFontBtnCh1;
	CH2Btn.Left = CH2BUTTON_RET_X;
	CH2Btn.Top = CH2BUTTON_RET_Y;
	CH2Btn.Height = CHBUTTON_RET_H;
	CH2Btn.Width = CHBUTTON_RET_W;
	CH2Btn.Focus = 1;	/* 焦点 */
	strcpy(ch,"2");							
	CH2Btn.pCaption = ch;
	LCD_DrawButton(&CH2Btn);
	
	LCD_DrawRect(CH1_RET_X,CH1_RET_Y,CH_RET_H,CH_RET_W,CL_BLACK);
	LCD_DrawRect(CH2_RET_X,CH2_RET_Y,CH_RET_H,CH_RET_W,CL_BLACK);
	LCD_DrawRect(NAME1_RET_X,NAME1_RET_Y,NAME_RET_H,NAME_RET_W,CL_BLACK);
	LCD_DrawRect(NAME2_RET_X,NAME2_RET_Y,NAME_RET_H,NAME_RET_W,CL_BLACK);
	for(i=0;i<9;i++)
	{
		LCD_DrawRect(BAR1_RET_X+(BAR_RET_W-1)*i,BAR1_RET_Y,BAR_RET_H,BAR_RET_W,CL_BLACK);
		LCD_DrawRect(BAR2_RET_X+(BAR_RET_W-1)*i,BAR2_RET_Y,BAR_RET_H,BAR_RET_W,CL_BLACK);	
	}	
	LCD_DispStr(50, 60, "通道号", &tFontBtnCh1);//
	LCD_DispStr(160, 60, "姓名", &tFontBtnCh1);//
	LCD_DispStr(475, 60, "检测结果", &tFontBtnCh1);//
	
	tBtn.Font = &tFontBtn;
	tBtn.Left = BUTTON_RET_X;
	tBtn.Top = BUTTON_RET_Y;
	tBtn.Height = BUTTON_RET_H;
	tBtn.Width = BUTTON_RET_W;
	tBtn.Focus = 0;	/* 失去焦点 */
	strcpy(ch,"测量");
	tBtn.pCaption = ch;
	LCD_DrawButton(&tBtn);
	tBtn1.Font = &tFontBtn;
	tBtn1.Left = RETURN_RET_X;
	tBtn1.Top = RETURN_RET_Y;
	tBtn1.Height = RETURN_RET_H;
	tBtn1.Width = RETURN_RET_W;
	tBtn1.Focus = 0;	/* 失去焦点 */
	strcpy(ch,"返回");
	tBtn1.pCaption = ch;
	LCD_DrawButton(&tBtn1);
}
void MainTask(void)
{
	uint8_t i,j;		
	uint8_t fRefresh,fMeasurement=1;		/* 刷屏请求标志,1表示需要刷新 */
	uint16_t fProgess=0;
	{	/* 按钮字体 */
		tFontBtn.FontCode = FC_ST_24;
		tFontBtn.BackColor = CL_MASK;	/* 透明色 */
		tFontBtn.FrontColor = CL_BLACK;
		tFontBtn.Space = 1;
	}
	{	/* 按钮字体 */
		tFontBtnCh1.FontCode = FC_ST_24;
		tFontBtnCh1.BackColor = CL_MASK;	/* 透明色 */
		tFontBtnCh1.FrontColor = CL_BLACK;
		tFontBtnCh1.Space = 1;
	}
	Dis_Measurement();
	fRefresh = 1;	/* 1表示需要刷新LCD */
	while (fMeasurement)
	{
		bsp_Idle();	
		if(fButton)
		{		
			j=1;
			for(;j<10;j++)
			{			
				fProgess+=BAR_RET_W-1;
				checkChannel=1;
				LCD_Fill_Rect(BAR1_RET_X+1,BAR1_RET_Y+1,BAR_RET_H-2,fProgess-1,CL_GREEN);
				ChannelMeas(checkChannel*10+j);
				if(m_bMeasureBreak||fButton==0)
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
					LCD_Fill_Rect(BAR1_RET_X,BAR1_RET_Y,BAR_RET_H,200,CL_WHITE);
					for(i=0;i<9;i++)
					{
						LCD_DrawRect(BAR1_RET_X+(BAR_RET_W-1)*i,BAR1_RET_Y,BAR_RET_H,BAR_RET_W,CL_BLACK);
						LCD_DrawRect(BAR2_RET_X+(BAR_RET_W-1)*i,BAR2_RET_Y,BAR_RET_H,BAR_RET_W,CL_BLACK);	
					}
					fProgess=0;
					m_bMeasureBreak=0;
					fButton=0;
					break;
				}	
			}				
		}
		if(dis_keyboard)
		{
			LCD_ClrScr(CL_WHITE);  		/* 清屏，【背景白色 */
			LCD_Fill_Rect(0,0,450,800,M_BACKGROUND_COLOR);
			keyboard();
			while(dis_keyboard)
			{
				typewriting();
			}
			Dis_Measurement();
			if(F_name)
			{
				strcpy(name1,s_Textbuf);				
			}
			else
			{
				strcpy(name2,s_Textbuf);				
			}
			LCD_DispStr(NAME1_RET_X+10, NAME1_RET_Y+3, name1, &tFontBtnCh1);//显示选择的汉字	
			LCD_DispStr(NAME2_RET_X+10, NAME2_RET_Y+3, name2, &tFontBtnCh1);//显示选择的汉字	
		}
		ucTouch = TOUCH_GetKey(&tpX, &tpY);	/* 读取触摸事件 */
		if (ucTouch != TOUCH_NONE)
		{
			switch (ucTouch)
			{
				case TOUCH_DOWN:		/* 触笔按下事件 */
					if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
					{
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
					else if (TOUCH_InRect(tpX, tpY, RETURN_RET_X, RETURN_RET_Y, RETURN_RET_H, RETURN_RET_W))
					{
						tBtn1.Focus = 1;	/* 焦点 */
						strcpy(ch,"返回");
						tBtn1.pCaption = ch;
						LCD_DrawButton(&tBtn1);
									
					}			
					break;

				case TOUCH_RELEASE:		/* 触笔释放事件 */
					if (TOUCH_InRect(tpX, tpY, BUTTON_RET_X, BUTTON_RET_Y, BUTTON_RET_H, BUTTON_RET_W))
					{
						if(fButton==0)
						{
							fButton=1;
							tBtn.Focus = 0;	/* 焦点 */
							strcpy(ch,"停止");
							tBtn.pCaption = ch;
							LCD_DrawButton(&tBtn);
						}
						else 
						{
							fButton=0;
							tBtn.Focus = 0;	/* 焦点 */
							strcpy(ch,"测量");
							tBtn.pCaption = ch;
							LCD_DrawButton(&tBtn);
							LCD_Fill_Rect(BAR1_RET_X,BAR1_RET_Y,BAR_RET_H,200,CL_WHITE);
							for(i=0;i<9;i++)
							{
								LCD_DrawRect(BAR1_RET_X+(BAR_RET_W-1)*i,BAR1_RET_Y,BAR_RET_H,BAR_RET_W,CL_BLACK);
								LCD_DrawRect(BAR2_RET_X+(BAR_RET_W-1)*i,BAR2_RET_Y,BAR_RET_H,BAR_RET_W,CL_BLACK);	
							}
							fProgess=0;
							m_bMeasureBreak=0;
							fButton=0;
						}
					}
					else if (TOUCH_InRect(tpX, tpY, RETURN_RET_X, RETURN_RET_Y, RETURN_RET_H, RETURN_RET_W))
					{
						tBtn1.Focus = 0;	/* 焦点 */
						strcpy(ch,"返回");
						tBtn1.pCaption = ch;
						LCD_DrawButton(&tBtn1);	
						fMeasurement=0;										
					}
					else if(TOUCH_InRect(tpX, tpY, NAME1_RET_X, NAME1_RET_Y, NAME_RET_H, NAME_RET_W))
					{
						dis_keyboard=1;
						F_name=1;
					}
					else if(TOUCH_InRect(tpX, tpY, NAME2_RET_X, NAME2_RET_Y, NAME_RET_H, NAME_RET_W))
					{
						dis_keyboard=1;
						F_name=0;
					}
					else if(TOUCH_InRect(tpX, tpY, CH1BUTTON_RET_X, CH1BUTTON_RET_Y, CHBUTTON_RET_H, CHBUTTON_RET_W))
					{
						CH1Btn.Focus =~CH1Btn.Focus;	/* 焦点 */
						strcpy(ch,"1");
						tBtn.pCaption = ch;
						LCD_DrawButton(&CH1Btn);
					}
					else if(TOUCH_InRect(tpX, tpY, CH2BUTTON_RET_X, CH2BUTTON_RET_Y, CHBUTTON_RET_H, CHBUTTON_RET_W))
					{
						CH2Btn.Focus =~CH2Btn.Focus;	/* 焦点 */
						strcpy(ch,"2");
						tBtn.pCaption = ch;
						LCD_DrawButton(&CH2Btn);
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
void ChannelMeas(u8 Pnum)
{
    u8 Pno=Pnum%10;
    Pnum = (u8)(Pnum/10);
    switch(Pno)
    {
    case	1:
        AirFirst();
        Intensitys[0]=Intensity1;
        Intensitys[1]=Intensity2;
        break;
    case 	2:
        BaseFirst(Pnum,m);
        if(m_bMeasureBreak==1)
            break;
        Intensitys[2]=Intensity1;
        Intensitys[3]=Intensity2;
        C12BABS = -log10((float)Intensitys[2] / ((float)Intensitys[0]));
        m_lC12B = ((((m_lCfC12[5] * C12BABS + m_lCfC12[4]) * C12BABS + m_lCfC12[3]) * C12BABS + m_lCfC12[2]) * C12BABS + m_lCfC12[1]) * C12BABS + m_lCfC12[0];
        if(m_bIgnoreConcentrationLow==0)
        {
					if(m_lC12B<0.5)
					{
						m_bMeasureBreak=2;//底气浓度过低，中止测量
					}
        }
        break;
    case 	3:
        AirFirst();
        Intensitys[4]=Intensity1;
        Intensitys[5]=Intensity2;
        break;
    case 	4:
        SampleFirst(Pnum,m);
        if(m_bMeasureBreak==1)
            break;
        Intensitys[6]=Intensity1;
        Intensitys[7]=Intensity2;
        C12SABS = -log10((float)Intensitys[6] /( (float)Intensitys[4]));
        m_lC12S = ((((m_lCfC12[5] * C12SABS + m_lCfC12[4]) * C12SABS + m_lCfC12[3]) * C12SABS + m_lCfC12[2]) * C12SABS + m_lCfC12[1]) * C12SABS + m_lCfC12[0];
        if(m_bIgnoreConcentrationLow==0)
        {
					if(m_lC12S<0.5)
					{
						m_bMeasureBreak=3;//样气浓度过低，中止测量
						break;	 
					}
        }
        break;
    case 	5:
        Air();
        Intensitys[8]=Intensity1;
        Intensitys[9]=Intensity2;
				C12BABS = -log10((float)Intensitys[2] / ((float)(Intensitys[4]* 0.5+Intensitys[0]*0.5)));
				m_lC12B = ((((m_lCfC12[5] * C12BABS + m_lCfC12[4]) * C12BABS + m_lCfC12[3]) * C12BABS + m_lCfC12[2]) * C12BABS + m_lCfC12[1]) * C12BABS + m_lCfC12[0];

        C12SABS = -log10((float)Intensitys[6] /( (float)(Intensitys[4]*0.7+Intensitys[8]* 0.3)));
        m_lC12S = ((((m_lCfC12[5] * C12SABS + m_lCfC12[4]) * C12SABS + m_lCfC12[3]) * C12SABS + m_lCfC12[2]) * C12SABS + m_lCfC12[1]) * C12SABS + m_lCfC12[0];
   
        if ((ABS(m_lC12B - m_lC12S) > 0.05)&&(m_mesureType==1||m_mesureType==4))
        {
          m_bDilution = 1;
					if(m_lC12B <2.2|| m_lC12S<2.2)
					{
						Per = 0.900;
					}
					else if(m_lC12B>4.0&& m_lC12S>4.0)
					{
						Per = 0.750;
					}
					else
					{
						Per = 0.800;
					}
					if (m_lC12B > m_lC12S)
					{
							Percent =  m_lC12S / m_lC12B * Per ;
							m_bChanged = 1;
					}
					else   
					{
							Percent =  m_lC12B / m_lC12S * Per;
							m_bChanged = 0;
					}	             
				}
				else
				{
					m_bDilution = 0;
				}				
				break;
    case 	6:
        if(m_bDilution==1)
        {
					if(m_bChanged)
					{
							Sample(Pnum+10,m,Percent,1);//	Pno =8;
					}
					else
					{
							Sample(Pnum+10,m,Per,1);
					}
        }
        else
          Sample(Pnum+10,m,Per,1);
//			Sample(Pnum+10,m,Per,0);
        Intensitys[10]=Intensity1;
        Intensitys[11]=Intensity2;
        break;
    case 	7:
        Air();
        Intensitys[12]=Intensity1;
        Intensitys[13]=Intensity2;
        break;
    case 	8:
        if(m_bDilution==1)
        {
					if(m_bChanged)
						Sample(Pnum+20,m,Per,1);
					else
						Sample(Pnum+20,m,Percent,1);
        }
        else
				Sample(Pnum+20,m,Per,1);
//			Sample(Pnum+20,m,Per,0);
        Intensitys[14]=Intensity1;
        Intensitys[15]=Intensity2;
        break;
    case 	9:
        Air();
        Valve(161);
        Valve(150);
        Intensitys[16]=Intensity1;
        Intensitys[17]=Intensity2;
        GPIO_WriteBit(GPIO_M1MO,GPIO_Pin_M1MO,Bit_SET);
        Speaker(1);
        break;
    default:
        break;
    }
    if(m_bMeasureBreak==0)
    {
      if(Pno==9)
      {	 
				//1.吸光度
				xbc12=-log10((float)(Intensitys[10]<<1) / ((float)Intensitys[8]+(float)Intensitys[12]));
				xsc12=-log10((float)(Intensitys[14]<<1) / ((float)Intensitys[12]+(float)Intensitys[16]));

				xbc13=-log10((float)(Intensitys[11]<<1) / ((float)Intensitys[9]+(float)Intensitys[13]));
				xsc13=-log10((float)(Intensitys[15]<<1) / ((float)Intensitys[13]+(float)Intensitys[17]));

				
					//2.浓度				
					cbc12 = ((((m_lCfC12[5] * xbc12 + m_lCfC12[4]) * xbc12 + m_lCfC12[3]) * xbc12 + m_lCfC12[2]) * xbc12 + m_lCfC12[1]) * xbc12 + m_lCfC12[0];
					csc12 = ((((m_lCfC12[5] * xsc12 + m_lCfC12[4]) * xsc12 + m_lCfC12[3]) * xsc12 + m_lCfC12[2]) * xsc12 + m_lCfC12[1]) * xsc12 + m_lCfC12[0];
					cbc13 = ((((m_lCfC13[5] * xbc13 + m_lCfC13[4]) * xbc13 + m_lCfC13[3]) * xbc13 + m_lCfC13[2]) * xbc13 + m_lCfC13[1]) * xbc13 + m_lCfC13[0];
					csc13 = ((((m_lCfC13[5] * xsc13 + m_lCfC13[4]) * xsc13 + m_lCfC13[3]) * xsc13 + m_lCfC13[2]) * xsc13 + m_lCfC13[1]) * xsc13 + m_lCfC13[0];
					//3.浓度比
					ratebase	= cbc13*100.0/cbc12*10.0;	 //107.7-->1.077
					ratesample	= csc13*100.0/csc12*10.0;
					//4.dob	 *100
					dob=(s16)((ratesample-ratebase)*100.0/1.12372);     
//					Num++;
//					GetDate();
//					GetTime();
//					ID[0]= (dob&0xFF00)>>8;
//					ID[1]=  dob&0x00FF;					
//					ID[2]= (Num&0xFF00)>>8;
//					ID[3]=  Num&0x00FF;
//					ID[5]= ((u16)(cbc12*1000)&0xFF00)>>8;
//					ID[4]=  (u16)(cbc12*1000)&0x00FF;
//					ID[6]= checkChannel;
//					ID[18]= ((u16)(csc12*1000)&0xFF00)>>8;
//					ID[17]=  (u16)(csc12*1000)&0x00FF;
//					ID[7]=timer.w_year/10%10;
//					ID[8]=timer.w_year%10;
//					ID[9]=timer.w_month/10;
//					ID[10]=timer.w_month%10;
//					ID[11]=timer.w_date/10;
//					ID[12]=timer.w_date%10;
//					ID[13]=timer.hour/10;
//					ID[14]=timer.hour%10;
//					ID[15]=timer.min/10;
//					ID[16]=timer.min%10;
//					ID[20]=flag_dob;
//					SPI_FLASH_SectorErase(0x7E0000);
//					SPI_FLASH_BufferWrite(ID,0x7E0000,30);
//					SPI_FLASH_BufferWrite(ID,0x010000+Num*30,30);
//				print_result();
				fButton=0;
    }
			
  }
}
