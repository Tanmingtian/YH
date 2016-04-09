#include "motor.h"
#include "math.h"
#include "stm32f4xx.h"
#include "bsp.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#define ABS(A) (((A)>0)?(A):(-(A)))
#define ADC1_DR_ADDRESS          ((uint32_t)0x4001204C)
#define NPT 256            /* NPT = No of FFT point*/
long lBUFIN[NPT];         /* Complex input vector */
long lBUFOUT[NPT];        /* Complex output vector */
long lBUFMAG[NPT + NPT/2];/* Magnitude vector */
u16 temp1=3620;
u16 temp2=3500;
u8  	reTest;
s16 	m=0;
//²ÉÑùÉè¶¨
u8		ADCIndex;
u16		ADCResult[36];
u16		ADCConv[ADCNUM]; 
__IO uint16_t uhADCConvertedValue[5];
u32 Intensity,Intensitys1,Intensitys2,C12[60],C13[60];
//const unsigned int Speedup[200]={
//	62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766, 62766,56978,51962,47586,43746,40357,37351,34673,32278,30125,28185,26429,24835,23384,22059,20846,19733,18709,17765,16893,16085,15335,14639,13991,13386,12821,12293,11798,11334,10898,10488,10102,9738,9394,9070,8763,8472,8197,7936,7688,7452,7228,7015,6811,6618,6433,6257,6088,5927,5773,5626,5485,5349,5220,5095,4976,4861,4751,4645,4543,4445,4351,4260,4173,4088,4007,3929,3853,3780,3709,3641,3575,3512,3450,3391,3333,3277,3223,3171,3121,3072,3024,2978,2933,2890,2848,2807,2768,2729,2692,2656,2621,2587,2554,2521,2490,2460,2430,2401,2373,2346,2320,2294,2269,2245,2221,2198,2176,2154,2133,2112,2092,2073,2054,2035,2017,2000,1983,1966,1950,1934,1919,1904,1890,1876,1862,1849,1836,1823,1811,1799,1787,1776,1765,1755,1745,1735,1725,1716,1706,1698,1689,1681,1673,1665,1658,1650,1643,1637,1630,1624,1618,1612,1607,1601,1596,1591,1587,1582,1578,1574,1570,1567,1563,1560,1557,1554,1552,1549,1547,1545,1543,1542,1540,1539,1538,1537,1536,1536,1536,1536,
//};
const unsigned int Speedup[200]={
	57641,8106,3603,2027,1297,901,662,507,400,324,268,225,192,166,144,127,112,100,90,81,74,67,61,56,52,48,45,42,39,36,34,32,30,28,27,25,24,23,21,20,19,19,18,17,16,16,15,14,14,13,13,12,12,11,11,11,10,10,10,9,9,9,8,8,8,8,7,7,7,7,7,6,6,6,6,6,6,6,5,5,5,5,5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
};
	volatile unsigned int Step_LM=0;
u8 m_bChopper;	
double 	m_lCf[9]={0} ;
double temp;
u8 Go=0 ;
//AK5351 ±äÁ¿//AK5351 ±äÁ¿
	u8 STATUS;
u16 Pressure0=0,Pressure1=0,Pressure2=0;
volatile unsigned int RxLeftIdx = 0;
volatile unsigned int RxRightIdx = 0;
volatile u16 AK_Left_Data[DataLength*2]={0};
volatile u16 AK_Right_Data[DataLength*2]={0};
//Æû¸×µç»ú±äÁ¿
volatile uint8_t flagPress;
volatile uint16_t PulseNum=0;
volatile uint16_t PulseCount=0;
volatile uint8_t StartSpeed=0;
volatile uint8_t TargeSpeed=0;
volatile uint8_t StepTimes_1=0;
volatile uint16_t StepCount_1=0;
volatile uint8_t EndSpeed=0;
volatile uint8_t StepTimes_2=0;
volatile uint16_t StepCount_2=0;
volatile uint16_t AddedNum=0;
u8  flag_moto=0;
volatile u8 cw_status=FORWARD;
u8	m_bMeasureBreak=0;
u32	Intensity1,Intensity2;
u8 prnerr=0;
u8  TripSwitchStatus=0;
void LightModulation_Config()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//CL
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_M2CL;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIO_M2CL, &GPIO_InitStructure);
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_Init(GPIOA,&GPIO_InitStructure);
	//Reset
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_M2RESET;
	GPIO_Init(GPIO_M2RESET, &GPIO_InitStructure);
	//En
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_M2EN;
	GPIO_Init(GPIO_M2EN, &GPIO_InitStructure); 

	GPIO_WriteBit(GPIO_M2EN,GPIO_Pin_M2EN,Bit_RESET);	  //
	bsp_DelayMS(50);
	GPIO_WriteBit(GPIO_M2RESET,GPIO_Pin_M2RESET,Bit_SET);//
		//set up timer2
	TIM_TimeBaseStructure.TIM_Period	= 1125; 
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//¼ÆÊýÆ÷ÉÏÒçÖÐ¶ÏÉè¶¨
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);/*Çå³ý¸üÐÂ±êÖ¾Î»*/
	TIM_ARRPreloadConfig(TIM3, DISABLE);/*Ô¤×°ÔØ¼Ä´æÆ÷µÄÄÚÈÝ±»Á¢¼´´«ËÍµ½Ó°×Ó¼Ä´æÆ÷ */
	//¹Ø±Õ¶¨Ê±Æ÷
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
}

void LightModulation(u8 status)
{
//	u32 ccr1,TimerPeriod;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
//RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1);
	if(status==ON)
	{
		Step_LM=0;
		
		TIM_Cmd(TIM3, ENABLE);   
		m_bChopper=1;
	}
	if(status==OFF)
	{		
		TIM_Cmd(TIM3, DISABLE);	
		//¹Ø±Õ CL=0 EN=0 RESET=0
		GPIO_WriteBit(GPIO_M2CL,GPIO_Pin_M2CL,Bit_RESET);
		GPIO_WriteBit(GPIO_M2EN,GPIO_Pin_M2EN,Bit_RESET);
		GPIO_WriteBit(GPIO_M2RESET,GPIO_Pin_M2RESET,Bit_SET);		
		m_bChopper=0;
	}
}

/*--------------------
ÏÞ·ùÆ½¾ùÂË²¨
----------------------*/
u16 weedavg(u16 a[ADCNUM],u8 num)  
{ 
	u8	i, j;
	u16	p;
	u32	sum = 0;
	u8	exchange; //½»»»±êÖ¾
	for( i=0;i<ADCNUM;i++)
	{ //×î¶à×ön-1ÌËÅÅÐò
		exchange = 0; //±¾ÌËÅÅÐò¿ªÊ¼Ç°£¬½»»»±êÖ¾Ó¦Îª¼Ù
		for( j = ADCNUM-1;j>i;j--) //¶Ôµ±Ç°ÎÞÐòÇøa[i..n]×ÔÏÂÏòÉÏÉ¨Ãè
			if(a[j]<a[j-1])
			{//½»»»¼ÇÂ¼
				p		= a[j]; //p×öÔÝ´æµ¥Ôª
				a[j]	= a[j-1];
				a[j-1]	= p;
				exchange= 1; //·¢ÉúÁË½»»»£¬¹Ê½«½»»»±êÖ¾ÖÃÎªÕæ
			}
			if(!exchange) //±¾ÌËÅÅÐòÎ´·¢Éú½»»»£¬ÌáÇ°ÖÕÖ¹Ëã·¨
				break;
	} //endfor(ÍâÑ­»·)
	for (i=num;i<ADCNUM-num;i++)         //³ýÈ¥×î´óa0,×îÐ¡anºóÈ¡Æ½¾ùÖµ
		sum += a[i];

	return (sum/(ADCNUM-num*2));
}//BubbleSort


unsigned int ADC_1(unsigned char ch)
{
	u32 res=0;
	u8 i=0;
	u16  ADCConvPress[ADCNUM];
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles);
	// Start ADC1 Software Conversion 
	ADC_Cmd(ADC1, ENABLE);
  ADC_SoftwareStartConv(ADC1);
	for(i=0;i<ADCNUM;i++)
	{
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
		ADCConvPress[i]=ADC_GetConversionValue(ADC1);
	}
	res	= weedavg(ADCConvPress,5);
	return res;		
}
void AK_Conv(void)	  
{
	u16	i;
	unsigned long long temp5=0;
	unsigned long long temp6=0;
	RxLeftIdx	= 0;
	RxRightIdx	= 0;	 
	SPI_I2S_ClearITPendingBit(SPI2,SPI_I2S_IT_RXNE); 
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
	//µÈ´ý¶ÁÈ¡ÖÐ¶Ï½áÊø
	while (RxLeftIdx<DataLength*2 ||RxRightIdx<DataLength*2);
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, DISABLE);
	temp5=0;
	temp6=0;
	for(i=0;i<DataLength;i++)
	{ 
		temp5 += ABS((s16)AK_Left_Data [i*2])*ABS((s16)AK_Left_Data [i*2]);
		temp6 += ABS((s16)AK_Right_Data[i*2])*ABS((s16)AK_Right_Data[i*2]);
	}
	temp5>>=6;
	temp6>>=6;
	Intensity1=sqrt(temp5);
	Intensity2=sqrt(temp6);

	AK_Left_Data[0]	= (temp5>>48)&0xFFFF;
	AK_Left_Data[1]	= (temp5>>32)&0xFFFF;
	AK_Left_Data[2]	= (temp5>>16)&0xFFFF;
	AK_Left_Data[3]	= temp5&0xFFFF;

	AK_Left_Data[4]	= (temp6>>48)&0xFFFF;
	AK_Left_Data[5]	= (temp6>>32)&0xFFFF;
	AK_Left_Data[6]	= (temp6>>16)&0xFFFF;
	AK_Left_Data[7]	= temp6&0xFFFF; 
//u16	i;
//	unsigned long long temp5=0;
//	unsigned long long temp6=0;
// 	unsigned long long leftdata=0;
//	unsigned long long rightdata=0;
//	RxLeftIdx	= 0;
//	RxRightIdx	= 0;

//	SPI_I2S_ClearITPendingBit(SPI2,SPI_I2S_IT_RXNE); 
//	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
//   	//µÈ´ý¶ÁÈ¡ÖÐ¶Ï½áÊø
//	while (RxLeftIdx<DataLength*2 ||RxRightIdx<DataLength*2);
//	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, DISABLE);
//	for(i=0;i<DataLength;i++)
//	{
//		leftdata	= (ABS((s32)(AK_Left_Data [i*2]<<16	+ AK_Left_Data [i*2+1])))/0x1000; 
//		rightdata	= (ABS((s32)(AK_Right_Data[i*2]<<16+ AK_Right_Data [i*2+1])))/0x1000;
//		temp5 += leftdata*leftdata;
//		temp6 += rightdata*rightdata;
//	}
//	temp5>>=1;
//	temp6>>=1;
//	Intensity=sqrt(temp5);
//	Intensitys1=sqrt(temp5);
//	Intensitys2=sqrt(temp6);
//	AK_Left_Data[0]	= (temp5>>48)&0xFFFF;
//	AK_Left_Data[1]	= (temp5>>32)&0xFFFF;
//	AK_Left_Data[2]	= (temp5>>16)&0xFFFF;
//	AK_Left_Data[3]	= temp5&0xFFFF;

//	AK_Left_Data[4]	= (temp6>>48)&0xFFFF;
//	AK_Left_Data[5]	= (temp6>>32)&0xFFFF;
//	AK_Left_Data[6]	= (temp6>>16)&0xFFFF;
//	AK_Left_Data[7]	= temp6&0xFFFF; 
}
void Valve(unsigned char Vnum)
{
	switch(Vnum)
	{
	case 0:		
		break;
	case 10:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve1, Bit_RESET);
		break;
	case 11:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve1, Bit_SET);
		break;
	case 20:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve2, Bit_RESET);
		break;
	case 21:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve2, Bit_SET);
		break;
	case 30:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve3, Bit_RESET);
		break;
	case 31:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve3, Bit_SET);
		break;
	case 40:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve4, Bit_RESET);
		break;
	case 41:
		GPIO_WriteBit(GPIO_Valve1_4, GPIO_Pin_Valve4,  Bit_SET);
		break;
	case 50:
		GPIO_WriteBit(GPIO_Valve5_6, GPIO_Pin_Valve5, Bit_RESET);
		break;
	case 51:
		GPIO_WriteBit(GPIO_Valve5_6, GPIO_Pin_Valve5,  Bit_SET);
		break;
	case 60:
		GPIO_WriteBit(GPIO_Valve5_6, GPIO_Pin_Valve6, Bit_RESET);
		break;
	case 61:
		GPIO_WriteBit(GPIO_Valve5_6, GPIO_Pin_Valve6, Bit_SET);
		break;
	case 70:
		GPIO_WriteBit(GPIO_Valve7_8, GPIO_Pin_Valve7, Bit_RESET);
		break;
	case 71:
		GPIO_WriteBit(GPIO_Valve7_8, GPIO_Pin_Valve7, Bit_SET);
		break;
	case 80:
		GPIO_WriteBit(GPIO_Valve7_8, GPIO_Pin_Valve8, Bit_RESET);
		break;
	case 81:
		GPIO_WriteBit(GPIO_Valve7_8, GPIO_Pin_Valve8, Bit_SET);
		break;
	case 90:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve9, Bit_RESET);
		break;
	case 91:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve9, Bit_SET);
		break;
	case 100:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve10, Bit_RESET);
		break;
	case 101:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve10, Bit_SET);
		break;
	case 110:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve11, Bit_RESET);
		break;
	case 111:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve11, Bit_SET);
		break;
	case 120:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve12,  Bit_RESET);
		break;
	case 121:
		GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve12,  Bit_SET);
		break;
	default:
		break;
	}
}
u8 IsTripSwitchClosed(void)
{
	return GPIO_ReadInputDataBit(GPIO_TripSwitch,GPIO_Pin_TripSwitch);
}

/*
MotorunÆû¸×µç»úÇý¶¯º¯Êý
En=1/0 1ÎªÆô¶¯Àø´Å
FPulseNumÎªÂö³å¸öÊý
Cw=FORWARD/BACKWORD
IfConv=0/1 ÊÇ·ñÔÚ¹ý³ÌÖÐ½øÐÐ²É¼¯
FStartSpeed Æô¶¯ËÙ¶È£¬µ¥Î»r/s
FTargeSpeed Ä¿±êËÙ¶È£¬µ¥Î»r/s
FStepTimes_1 ¼ÓËÙ¹ý³ÌµÄ¹ý³ÌÊý
FStepCount_1 Ã¿¸ö¼ÓËÙ¹ý³Ì³ÖÐøÂö³åÊý
FEndSpeed ½áÊøËÙ¶È£¬µ¥Î»r/s
FStepTimes_2¼õËÙ¹ý³ÌµÄ¹ý³ÌÊý
FStepCount_2 Ã¿¸ö¼õËÙ¹ý³Ì³ÖÐøÂö³åÊý
u8 vnum1,u8 vnum2,u8 vnum3 Èý¸öµç´Å·§×´Ì¬
*/
void Motorun(u8 En,u16 FPulseNum,u8 Cw,u8 IfConv,
			u8 FStartSpeed,u8 FTargeSpeed,u8 FStepTimes_1,u16 FStepCount_1,
			u8 FEndSpeed,u8 FStepTimes_2,u16 FStepCount_2,u16 FAddedNum,
			u8 vnum1,u8 vnum2,u8 vnum3)//(  0,800,FORWARD,0,      20,50,5,20,      30,3,20,0,        91,150,161)
{
	GPIO_WriteBit(GPIO_M1MO,GPIO_Pin_M1MO,Bit_RESET); 	
	//µç´Å·§¶¯×÷
 	Valve(vnum1);
  Valve(vnum2);
  Valve(vnum3); 
	flagPress=En;
	GPIO_WriteBit(GPIO_M1EN, GPIO_Pin_M1EN, (BitAction)(1));
	GPIO_WriteBit(GPIO_M1CW, GPIO_Pin_M1CW, (BitAction)(Cw));//Cw;
	//ÑÓÊ±30ms
	bsp_DelayMS(30);
		   
	//Í£Ö¹reset
	GPIO_WriteBit(GPIO_M1RESET, GPIO_Pin_M1RESET, Bit_RESET);
	//Âö³å¼ÆÊý¹éÁã
	PulseCount	= 0;
	//ÅäÖÃÈ«¾Ö±äÁ¿
	PulseNum	= (u16)((FPulseNum<<2));
	StartSpeed	= FStartSpeed<<1;
	TargeSpeed	= FTargeSpeed<<1;
	StepTimes_1	= FStepTimes_1;
	StepCount_1	= FStepCount_1;
	EndSpeed	= FEndSpeed<<1;
	StepTimes_2	= FStepTimes_2;
	StepCount_2	= FStepCount_2;
	AddedNum	= FAddedNum;

	cw_status	= Cw;
	if(Cw==BACKWARD)
		EXTI->IMR|=0x2000;
	//Éè¶¨timer2
	TIM2->ARR	= 2671;//122880/StartSpeed;
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	//Èç¹ûÐèÒªÔÚ´òÆø¹ý³ÌÖÐ½øÐÐÊý¾Ý²É¼¯
	if(IfConv)
	{
		bsp_DelayMS(300);
		AK_Conv();
		while(PulseCount<=FStepTimes_1*FStepCount_1+200) ;
	}
	//µÈ´ýÔË¶¯½áÊø
	while(PulseCount<PulseNum+AddedNum)
	{
		if(IsTripSwitchClosed() && cw_status==BACKWARD)
			break;
	}
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIM2,DISABLE);
	cw_status=255;
	PulseCount=0; 
} 


void Motor_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//set up motor gpio
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_M1RESET;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIO_M1RESET, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_M1CL|GPIO_Pin_M1EN|GPIO_Pin_M1CW;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIO_M1CL, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_M1MO;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIO_M1MO, &GPIO_InitStructure);

	GPIO_WriteBit(GPIO_M1CL,GPIO_Pin_M1CL,Bit_RESET);

	GPIO_WriteBit(GPIO_M1EN, GPIO_Pin_M1EN, (BitAction)(0))	;	 	//Ê¹ÄÜ0
	bsp_DelayMS(200);
	GPIO_WriteBit(GPIO_M1RESET, GPIO_Pin_M1RESET, (BitAction)(1));	//¸´Î»1
	GPIO_WriteBit(GPIO_M1MO,GPIO_Pin_M1MO,Bit_RESET); 
		
	//set up timer2
	TIM_TimeBaseStructure.TIM_Period	= 1000; 
	TIM_TimeBaseStructure.TIM_Prescaler = 9;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//¼ÆÊýÆ÷ÉÏÒçÖÐ¶ÏÉè¶¨
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);/*Çå³ý¸üÐÂ±êÖ¾Î»*/
	TIM_ARRPreloadConfig(TIM2, DISABLE);/*Ô¤×°ÔØ¼Ä´æÆ÷µÄÄÚÈÝ±»Á¢¼´´«ËÍµ½Ó°×Ó¼Ä´æÆ÷ */
	//¹Ø±Õ¶¨Ê±Æ÷
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
}

void ADC_Config(void)
{
		ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
//	DMA_InitTypeDef       DMA_InitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;
	
	/* Ê¹ÄÜÍâÉèÊ±ÖÓ */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* DMA2 Stream0 channel0 ÅäÖÃ-------------------------------------------------- */
//	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&uhADCConvertedValue;;
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
//	DMA_InitStructure.DMA_BufferSize = 4;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//    
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//    
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

//	/* DMA2_Stream0 enable */
//	DMA_Cmd(DMA2_Stream0, ENABLE);
//    
    /****************************************************************************   
	  PCLK2 = HCLK / 2 
	  ÏÂÃæÑ¡ÔñµÄÊÇ2·ÖÆµ
	  ADCCLK = PCLK2 /8 = HCLK / 8 = 168 / 8 = 21M
      ADC²ÉÑùÆµÂÊ£º Sampling Time + Conversion Time = 480 + 12 cycles = 492cyc
                    Conversion Time = 21MHz / 492cyc = 42.6ksps. 
	*****************************************************************************/
    ADC_DeInit();
	/* ADC Common ÅäÖÃ ----------------------------------------------------------*/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

	/* ADC1 regular channel 12 configuration ************************************/
	 ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);        
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
    
     /* Enable ADC1 DMA */
//    ADC_DMACmd(ADC1, ENABLE);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 5, ADC_SampleTime_480Cycles);
    /* ADC1 regular channel18 (VBAT) configuration ******************************/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_480Cycles);
    /* ADC1 regular channel18 (VBAT) configuration *****************************/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_480Cycles);
    
    /* ADC1 regular channels 10, 11 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 3, ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 4, ADC_SampleTime_480Cycles);   

    /* Enable VBAT channel */
//    ADC_VBATCmd(ENABLE); 
//    
//    ADC_TempSensorVrefintCmd(ENABLE); 

//    /* Enable DMA request after last transfer (Single-ADC mode) */
//    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

//    /* Enable ADC1 **************************************************************/
    ADC_Cmd(ADC1, ENABLE);
    
        /* Start ADC1 Software Conversion */
    ADC_SoftwareStartConv(ADC1);
}

void Speaker_Config(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SPEAKER;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* ÉèÎªÍÆÍìÄ£Ê½ */
	GPIO_Init(GPIO_SPEAKER, &GPIO_InitStructure);
	GPIO_WriteBit(GPIO_SPEAKER, GPIO_Pin_SPEAKER, Bit_RESET);
}

void AK5385_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2S_InitTypeDef I2S_InitStructure;	
		/* 使能SPI2时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	/* Enable GPIOI, GPIOB, GPIOC clock */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOH| RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Connect pins to I2S peripheral  */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_SPI2);
	
	GPIO_InitStructure.GPIO_Pin   = Pin_AK5385_PDN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_AK5385_PDN, &GPIO_InitStructure);
	//		
	GPIO_InitStructure.GPIO_Pin =Pin_AK5385_DIF;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_AK5385_DIF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =Pin_AK5385_MS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_AK5385_MS, &GPIO_InitStructure);
	
	
		//   
//	GPIO_InitStructure.GPIO_Pin =Pin_AK5385_CKS0 ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIO_AK5385_CKS0, &GPIO_InitStructure);

//		//  
//	GPIO_InitStructure.GPIO_Pin =Pin_AK5385_CKS1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIO_AK5385_CKS1, &GPIO_InitStructure);
	
	RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
	RCC_PLLI2SCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY)==RESET){} 
	/*打开I2S2 APB1 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		/* 复位 SPI2 外设到缺省状态 */
	SPI_I2S_DeInit(SPI2);
	/* I2S2 外设配置 */
//	I2S_StructInit(&I2S_InitStructure);
	I2S_InitStructure.I2S_Mode = I2S_Mode_MasterRx;			/* 配置I2S工作模式 */
	I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;			/* 接口标准*/
	I2S_InitStructure.I2S_DataFormat =  I2S_DataFormat_32b;			/* 数据格式32bit */
	I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Enable;	/* 主时钟模式 */
	I2S_InitStructure.I2S_AudioFreq =    (u32)4800;			/* 音频采样频率 */
	I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
	I2S_Init(SPI2, &I2S_InitStructure);
		/* 使能 SPI2/I2S2 外设 */
	I2S_Cmd(SPI2, ENABLE);
	GPIO_ResetBits(GPIO_AK5385_SCLK, Pin_AK5385_SCLK);
	GPIO_ResetBits(GPIO_AK5385_LRCK, Pin_AK5385_LRCK);
	GPIO_SetBits(GPIO_AK5385_DIF, Pin_AK5385_DIF);
	GPIO_SetBits(GPIO_AK5385_MS,Pin_AK5385_MS);	
	GPIO_ResetBits(GPIO_AK5385_PDN, Pin_AK5385_PDN);

	GPIO_ResetBits(GPIO_AK5385_CKS0,Pin_AK5385_CKS0);	
	GPIO_ResetBits(GPIO_AK5385_CKS1,Pin_AK5385_CKS1);
	bsp_DelayMS(5);
	GPIO_SetBits(GPIO_AK5385_PDN, Pin_AK5385_PDN);
	GPIO_SetBits(GPIO_AK5385_LRCK, Pin_AK5385_LRCK);	
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);		/* 使能发送中断 */
	while (RxLeftIdx<DataLength*2 ||RxRightIdx<DataLength*2);
	RxLeftIdx=0;
	RxRightIdx=0;
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, DISABLE);
}

void AK5351_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2S_InitTypeDef I2S_InitStructure;	
		/* Ê¹ÄÜSPI2Ê±ÖÓ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	/* Enable GPIOI, GPIOB, GPIOC clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOI, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Connect pins to I2S peripheral  */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
//	GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_SPI3);	/* ×¢Òâ£º PI2Á¬½ÓÉèÖÃÐèÒªÊÇ SPI3 */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_SPI2);
	GPIO_InitStructure.GPIO_Pin   = Pin_AK5351_PD;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_AK5351_PD, &GPIO_InitStructure);
	//		
	GPIO_InitStructure.GPIO_Pin =Pin_AK5351_FSYNC;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_AK5351_FSYNC, &GPIO_InitStructure);
	RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
	RCC_PLLI2SCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY)==RESET){} 
	/* ´ò¿ª I2S2 APB1 Ê±ÖÓ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	/* ¸´Î» SPI2 ÍâÉèµ½È±Ê¡×´Ì¬ */
	SPI_I2S_DeInit(SPI2);
	/* I2S2 ÍâÉèÅäÖÃ */
//	I2S_StructInit(&I2S_InitStructure);
	I2S_InitStructure.I2S_Mode = I2S_Mode_MasterRx;			/* ÅäÖÃI2S¹¤×÷Ä£Ê½ */
	I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;			/* ½Ó¿Ú±ê×¼ */
	I2S_InitStructure.I2S_DataFormat =  I2S_DataFormat_32b;			/* Êý¾Ý¸ñÊ½£¬16bit */
	I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Enable;	/* Ö÷Ê±ÖÓÄ£Ê½ */
	I2S_InitStructure.I2S_AudioFreq =    (u32)4800;			/* ÒôÆµ²ÉÑùÆµÂÊ */
	I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
	I2S_Init(SPI2, &I2S_InitStructure);
		/* Ê¹ÄÜ SPI2/I2S2 ÍâÉè */
	I2S_Cmd(SPI2, ENABLE);
	GPIO_ResetBits(GPIO_AK5351_PD, Pin_AK5351_PD);
	GPIO_ResetBits(GPIO_AK5351_FSYNC,Pin_AK5351_FSYNC);
	bsp_DelayMS(5);
	GPIO_SetBits(GPIO_AK5351_PD, Pin_AK5351_PD);	
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);		/* Ê¹ÄÜ·¢ËÍÖÐ¶Ï */
	while (RxLeftIdx<DataLength*2 ||RxRightIdx<DataLength*2);
	RxLeftIdx=0;
	RxRightIdx=0;
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, DISABLE);
}

void EXTI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/* Ê¹ÄÜSYSCFGÊ±ÖÓ */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_TripSwitch;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* ÉèÎªÍÆÍìÄ£Ê½ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ÎÞÐèÉÏÏÂÀ­µç×è */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* IO¿Ú×î´óËÙ¶È */
	GPIO_Init(GPIO_TripSwitch, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource12);

	EXTI_InitStructure.EXTI_Line = EXTI_LINE_TripSwitch;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	

}

void pprint(unsigned char ch)                             
{ 	  
	u16 i=3000;
//	unsigned char  tValue; 
	while(BUSY) 
	{
	 	i--;
		if(i<10)return;			
	}; 
//	tValue=~ch; 
	GPIOD->BSRRL=(unsigned int)ch; 
//	GPIOD->BRR=(unsigned int)tValue;          
	STB=0;                                              
	bsp_DelayMS(5);
	STB=1;                                               
}
void PRINT_Init (void)
{
   u16 i=500;
	while(BUSY)
	{
		i--;
		if(i==0)
		{			
			prnerr=1;
			break;
		}	
	}
	if(!prnerr)
	{
		BUSY = 1;		 
		STB  = 1; 
		pprint(0x1b);
		pprint(0x40);     
	}
//	pprint(0x1c);pprint(0x26);  
}
u8 Trip2;
void Motor_Init(void)
{
		FONT_T aFont;
		aFont.FontCode = FC_ST_48;		/* ×ÖÌå´úÂë 16µãÕó */
		aFont.FrontColor = CL_WHITE;	/* ×ÖÌåÑÕÉ« */
		aFont.BackColor = CL_MASK;		/* ÎÄ×Ö±³¾°ÑÕÉ« */
		aFont.Space = 0;
    LCD_DispStr(304, 100, "ÒÇÆ÷×Ô¼ì", &aFont);
		LCD_DispStr(304, 200, "´óµç»ú³õÊ¼»¯", &aFont);
    Trip2= IsTripSwitchClosed() ;
    if(Trip2)
    {
        Motorun(  0,800,FORWARD,0,      20,50,5,20,      30,3,20,0,        91,100,41);

        Trip2= IsTripSwitchClosed() ;
        if(Trip2)
        {        
					while(1)
					{
						LCD_DispStr(304, 100, "¹âµç¿ª¹ØÒì³£", &aFont);
					}//
        }
        else
        {  
						Motorun(  0,800,BACKWARD,0,     20,50,5,20,      30,3,20,200,      90,101,40);
        }
    }
    else
    {
        TripSwitchStatus=0;
        Motorun(  0,6000,BACKWARD,0,     20,30,0,0,      30,0,0,200,      90,101,40);
        if(!TripSwitchStatus)
        {
            LCD_DispStr(304, 100, "¹âµç¿ª¹ØÒì³£", &aFont);/*ÏÔÊ¾¹âµç¿ª¹Ø³ö´í*/	
				}
		}
}
void onesided(long nfill)
{
    u32 i;

    lBUFMAG[0] = lBUFMAG[0];
    lBUFMAG[nfill/2] = lBUFMAG[nfill/2];
    for (i=1; i < nfill/2; i++)
    {
        lBUFMAG[i] = lBUFMAG[i] + lBUFMAG[nfill-i];
        lBUFMAG[nfill-i] = 0x0;
    }
}
/**
* @brief  Compute power magnitude of the FFT transform
* @param ill: length of the array holding power mag
*   : strPara: if set to "1SIDED", removes aliases part of spectrum (not tested)
* @retval : None
*/
void powerMag(long nfill, char* strPara)
{
    s32 lX,lY;
    u32 i;

    for (i=0; i < nfill; i++)
    {
        lX= (lBUFOUT[i]<<16)>>16; /* sine_cosine --> cos */
        lY= (lBUFOUT[i] >> 16);   /* sine_cosine --> sin */
        {
            float X=  64*((float)lX)/32768;
            float Y = 64*((float)lY)/32768;
            float Mag = sqrt(X*X+ Y*Y)/nfill;
            lBUFMAG[i] = (u32)(Mag*65536);
        }
    }
    if (strPara == "1SIDED")
        onesided(nfill);
}
void ChopperCheck1(u8 run)
{
    u8	m_bRestart= 1;
    u16  i;
    u8	times=0;

    while(m_bRestart)
    {
        LightModulation(ON);
        bsp_DelayMS(5000);
        AK_Conv();
        for(i=0; i<256; i++)
        {
            lBUFIN[i] = AK_Left_Data[1200+i*2]<<16;
        }
        cr4_fft_256_stm32(lBUFOUT,lBUFIN,NPT);
        powerMag(NPT,"1SIDED");
        for(i=0; i<32; i++)
        {
            if(lBUFMAG[i]>(60*(6+times)))
            {
                m_bRestart	= 1;
                times++;
								break;
            }
            else
                m_bRestart	= 0;
        }
        if(lBUFMAG[32]<1280)
        {
            m_bRestart	= 1;
            times++;
        }
        if(times>4)
        {
            LightModulation(OFF);
            return;
        }
    }
    if(run!=1)
    {
        LightModulation(OFF);
    }
}

void ChopperCheck(u8 run)
{
 	u8 i;
	if(m_bChopper==1)
        return;
	ChopperCheck1(run);	 
	if(m_bChopper==0)
  {
		while(1)
		{}
  }
}
void Sys_100msClock_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//ÖÜÆÚ100ms
	TIM_TimeBaseStructure.TIM_Period	= 6143; 
	TIM_TimeBaseStructure.TIM_Prescaler = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//¼ÆÊýÆ÷ÉÏÒçÖÐ¶ÏÉè¶¨
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);/*Çå³ý¸üÐÂ±êÖ¾Î»*/
	TIM_ARRPreloadConfig(TIM3, DISABLE);/*Ô¤×°ÔØ¼Ä´æÆ÷µÄÄÚÈÝ±»Á¢¼´´«ËÍµ½Ó°×Ó¼Ä´æÆ÷ */
	//Æô¶¯¶¨Ê±Æ÷
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   
	TIM_Cmd(TIM3, ENABLE);
}
void Speaker(u8 Num)
{
	while(Num-->0)
	{
		GPIO_WriteBit(GPIO_SPEAKER, GPIO_Pin_SPEAKER, Bit_SET);
		//500ms
		bsp_DelayMS(500);
		GPIO_WriteBit(GPIO_SPEAKER, GPIO_Pin_SPEAKER, Bit_RESET);
		bsp_DelayMS(500);
	}
}

void Valve_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_Valve1|GPIO_Pin_Valve2 |GPIO_Pin_Valve3|GPIO_Pin_Valve4 ;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ÉÏÏÂÀ­µç×è²»Ê¹ÄÜ */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_Init(GPIO_Valve1_4, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_Valve5 |GPIO_Pin_Valve6 ;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ÉÏÏÂÀ­µç×è²»Ê¹ÄÜ */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_Init(GPIO_Valve5_6, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_Valve7 | GPIO_Pin_Valve8 ;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ÉÏÏÂÀ­µç×è²»Ê¹ÄÜ */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_Init(GPIO_Valve7_8, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_Valve9 | GPIO_Pin_Valve10 |GPIO_Pin_Valve11 |GPIO_Pin_Valve12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ÉÏÏÂÀ­µç×è²»Ê¹ÄÜ */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_Init(GPIO_Valve9_12, &GPIO_InitStructure);

	//ËùÓÐ·§ÃÅµÍµçÆ½
	GPIO_WriteBit(GPIO_Valve1_4,	GPIO_Pin_Valve1,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve1_4,	GPIO_Pin_Valve2,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve1_4,  GPIO_Pin_Valve3,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve1_4, 	GPIO_Pin_Valve4,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve5_6, 	GPIO_Pin_Valve5,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve5_6, 	GPIO_Pin_Valve6,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve7_8, 	GPIO_Pin_Valve7,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve7_8, 	GPIO_Pin_Valve8,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve9,  Bit_RESET);
	GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve10, Bit_RESET);
	GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve11, Bit_RESET);
	GPIO_WriteBit(GPIO_Valve9_12, GPIO_Pin_Valve12, Bit_RESET);

}
void PowerCheck(void)
{
	  u8	i,j;
	  ChopperCheck(1);
    Valve(171);
    Valve(181);
    for(i=0; i<2; i++)
    {
        Motorun(0,3000,FORWARD,0,  20,60,8,20, 30,5,20,0,    81,150,0);      //³éÆø
        Motorun(0,3000,BACKWARD,0, 20,60,8,20, 20,4,50,200,  81,151,161);      //´òÆø,ÇåÏ´

        Valve(160);
    }
    Motorun(0,4000,FORWARD,0,      20,60,8,20,  30,5,20,0,   81,150,0);      //³éÆø
    bsp_DelayMS(20);
    Motorun(0,4000,BACKWARD,0,     30,60,8,20,  30,1,20,1200,81,151,160);      //´òÆø£¬ÂýÍÆ1~3r/s£¬
    Valve(150);
    Valve(161);
    for(i=0; i<60; i++)
    {
      AK_Conv();	
			C12[i]=Intensity1;
			C13[i]=Intensity2;       
//		print_power(i+1,1);		
   
			if(m_bMeasureBreak==0)
			{
					bsp_DelayMS(350);
			}
			else
			{		
					m_bMeasureBreak=0;
						break;
			}
    }
    Valve(151);
    Valve(160);					   
}	


void LeakageCheck(u8 Go)
{	
  u8 i,j; 	
	u16 Press[10]={0},Y;
	if(Go==0)
	{
		bsp_DelayMS(50);
		for(i=0;i<10;i++)
		{
			bsp_DelayMS(1000);         //ÑÓÊ±
			Press[i] =ADC_1(ADC_FS);
			Y=(u16)(((((float)(Press[i] + 28) * 3 / 4096) - 1) / 4)*1000);
		}
		bsp_DelayMS(50);	
		if((Press[0]-Press[9])>100)
		{	
	//		print_pressure(Y,2);
		} 
		else
		{	
	//		print_pressure(Y,1);
		}
	}
}

  u16 n	= 0;
/*-----------------------------------
ÊÔ´òÆøÌåÈ·¶¨Âö³åÊý£¨Ó¦ÔÚ¿ª»ú×Ô¼ì¹ý³ÌÖ´ÐÐ,²âÁ¿4~6´Î£¿£©
ADC»ù×¼µçÑ¹3.0V£»
Ñ¹Á¦±íÊä³öµçÑ¹Óë±íÏÔÑ¹Á¦Âú×ã¹ØÏµÊ½ y=4x+1£»
ADÖµÓëÑ¹Á¦µÄ¹ØÏµ AD=£¨4x+1£©*4096/3.0£»
´òµ½Ä¿±êÑ¹Á¦£¨0.4Mpa£©µÄÂö³åÊýn=£¨Ä¿±êÑ¹Á¦/ÊÔ²âÑ¹Á¦£©*ÊÔ²âÂö³å£»
¿ÉµÃn=8738133/(AD-1365);
ÆäÖÐADÎªÊÔ²âÊ±¶ÁÈ¡µÄADÖµ£»
1365¼´Îª±ê×¼´óÆøÑ¹Ê±µÄADÖµ£¨pressure0£©£¬¿É¶à´Î²âÁ¿È¡Æ½¾ù£»
-------------------------------------*/
s16 Test(void)
{ 
	FONT_T aFont;
	int	i;
	n	= 0;
//m_lCf[6]=2190;
	Go=0;
  if(m_lCf[7]<3000||m_lCf[7]>4500)  
  m_lCf[7]=4000;
  T= m_lCf[7];
	
	aFont.FontCode = FC_ST_48;		/* ×ÖÌå´úÂë 16µãÕó */
	aFont.FrontColor = CL_WHITE;	/* ×ÖÌåÑÕÉ« */
	aFont.BackColor = CL_MASK;		/* ÎÄ×Ö±³¾°ÑÕÉ« */
	aFont.Space = 0;
	LCD_DispStr(304, 100, "¹âµç¿ª¹ØÒì³£", &aFont);
	while(Go<=3)
	{
		//·ÅÆø
		Valve(101);
		Valve(40);//ÅÅÆø
		Valve(170);
		Valve(180);
		bsp_DelayMS(1000);
		Pressure0=ADC_1(ADC_FS);				//¶ÁÈ¡Ñ¹Á¦±í³õÊ¼ADÖµ
		Motorun(0,2000,FORWARD,0,     30,60,5,20,     30,6,20,0,        91,100,40);
		bsp_DelayMS(50);
		Motorun(0,2000,BACKWARD,0,    30,60,5,20,     30,6,20,200,      90,101,40);
		bsp_DelayMS(100);
		//´Ó·§ÃÅ11ÎüÆø
		Motorun(0,2000,FORWARD,0,     30,60,5,20,     30,6,20,0,        91,100,40);
		bsp_DelayMS(50);
		Motorun(0,2000,BACKWARD,0,    30,60,5,20,     30,6,20,200,      90,101,40);
		bsp_DelayMS(100);
		Motorun(0,T,FORWARD,0,     30,60,5,20,     30,7,20,0,        91,100,41);
		bsp_DelayMS(1500);
		Motorun(1,T,BACKWARD,0,    20,30,1,20,     20,4,50,200,      90,101,41);
	//	bsp_DelayMS(400);
		//¹Ø±Õ·§ÃÅ9±£³ÖÑùÆ·³ØÆøÑ¹
		Valve(100);
		LeakageCheck(Go);
		Pressure1=ADC_1(ADC_FS);         //¶ÁÈ¡Ñ¹Á¦±íÊÔ²âADÖµ
		Pressure1=Pressure1-Pressure0;
		if(m_lCf[8]==400)
		{
		// 	if(m_lCf[6]<1700||m_lCf[6]>2200)  m_lCf[6]=1900;
	   	if(m_lCf[6]<2000||m_lCf[6]>2400)
			{
			 	m_lCf[6]=2190;
				temp1=3620;
				temp2=3500;
			}
		}
		else if(m_lCf[8]==300)
		{
			if(m_lCf[6]<1300||m_lCf[6]>1800)
			{
			  m_lCf[6]=1580;
				temp1=3250;
				temp2=2850;
			}
		}
		else if(m_lCf[8]==200)
		{
			if(m_lCf[6]<800||m_lCf[6]>1400)
			{
				m_lCf[6]=1100;
				temp1=2520;
				temp2=2400;
			}
		}
		else
		{
			m_lCf[6]=2190;
				temp1=3620;
				temp2=3500;
		}
		n=(unsigned int)(m_lCf[6]*T/Pressure1);   // Ðè¸ù¾ÝÊµÑé½á¹ûÐ£Õý	1084 3800   1110 0000
		Valve(101);
		Valve(40);
		bsp_DelayMS(1000);
 		Motorun(0,T,FORWARD,0,      30,60,8,20,  30,6,20,0,     91,101,40);      //³éÆø
		bsp_DelayMS(1500);	
		Motorun(0,T-n,BACKWARD,0,   30,30,0,0,  30,0,0,0,      90,101,40);
		bsp_DelayMS(1000);				  
		Motorun(1,n,BACKWARD,0,     20,30,1,20,     20,4,50,200,   90,101,41);
		Valve(100);
	//	LeakageCheck(Go);  
	  bsp_DelayMS(5000);
		Pressure2=ADC_1(ADC_FS);
	//  if(Pressure2<3380&&Pressure2>3200)
 	  if(Pressure2<temp1&&Pressure2>temp2)
    { Go=6; }
		else 
		{ Go++; }
	}
	m=T-n;  //¿Û³ým¸öÂö³åºó·´ÍÆ¼´¿ÉµÃµ½0.4MPaÆøÑ¹//568
	//·ÅÆø
	Valve(11);
	Valve(40);//ÅÅÆø
	Valve(170);
	Valve(180);
	bsp_DelayMS(1000);
	//È«²¿¹Ø±Õ
	Valve(100);
	bsp_DelayMS(100);
	reTest = 0;
	return m;
}
void  	Cartridge(u8 wash)
{
    u8 i;
    u8 OpenValve=0,CloseValve=0;
    switch(wash)
    {
    case 8:
        Valve(171);
        Valve(181);
        OpenValve=81,CloseValve=80;
        break;
    case 9:
        OpenValve=91,CloseValve=90;
        break;
    default:
        break;
    }

    for(i=0; i<2; i++)
    {
        Motorun(1,3250,FORWARD,0,      30,60,8,20,      20,6,20,0, 	 OpenValve, 150, 40);   //³éÆø 4~8r/s	Âö³åÊý:1500
        Motorun(1,3250,BACKWARD,0,     30,60,8,20,      20,6,20,200,	 CloseValve, 151, 40);  //´òÆø£¬µ×ÆøÇåÏ´
    }
    Motorun(1,T,FORWARD,0,      30,50,8,20,      20,6,20,0, 	 OpenValve, 150, 40);   //³éÆø£¬ÂúÐÐ³Ì
    bsp_DelayMS(1500);
    Valve(170);
    Valve(180);
    Motorun(1, m,  BACKWARD,0,   30,30,0,0,      30,0,0,0,	CloseValve, 151, 40);  //·´ÍÆm¸öÂö³å  ,ËÙ¶È4~5r/s
    bsp_DelayMS(1000);
    Motorun(1,T-m,BACKWARD,0,   20,30,1,20, 20,5,50,200,	 0, 0, 41);  //´òÆøÖÁµ×
    Valve(150);
    bsp_DelayMS(5000);         //¹²ÑÓÊ±5sµÈÆøÑ¹ÎÈ¶¨
    //×ª»»·¢ËÍÊý¾Ý
    AK_Conv();
    Valve(151);
    Valve(40);//ÅÅÆø
    bsp_DelayMS(100);
    Valve(150);
}
void PerkCheck(void)
{
    u8 i;
    u32 Intensityair;
    u32 Intensityref;
    s16 ratioc12 ;
    Cartridge(9);
    Intensityair=Intensity1;
    bsp_DelayMS(10);
    Cartridge(8);
    Intensityref=Intensity1;
    ratioc12 = (s16)((double)Intensityair / (double)Intensityref * 2000.0 - 1000.0);
//	print_filter(ratioc12);
}

