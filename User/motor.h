#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "bsp.h"
#define u8BAND(addr, u8num) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(u8num<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define u8_ADDR(addr, u8num)   MEM_ADDR(u8BAND(addr, u8num)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口
//确保n的值小于16！
#define PAout(n)   u8_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    u8_ADDR(GPIOA_IDR_Addr,n)  //输入

#define PBout(n)   u8_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    u8_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   u8_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    u8_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   u8_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    u8_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   u8_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    u8_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   u8_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    u8_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   u8_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    u8_ADDR(GPIOG_IDR_Addr,n)  //输入
//定义ADC变换通道
#ifndef ADCCH
	#define ADCCH
	#define ADC_T42 	14
	#define ADC_T18 	15
	#define ADC_FS 		1
	#define ADC_T_10A 	8
	#define ADC_T_10B   9
//	#define ADC_ROOM 	1
//	#define ADC_Humidity 	3
#endif
//定义切光片电机端口
#ifndef GPIO_M2
	#define GPIO_M2
	#define GPIO_M2CL 		GPIOA
	#define GPIO_Pin_M2CL 	GPIO_Pin_0
	#define GPIO_M2RESET 	GPIOH
	#define GPIO_Pin_M2RESET GPIO_Pin_8
	#define GPIO_M2EN		GPIOG
	#define GPIO_Pin_M2EN	GPIO_Pin_6	
#endif
//定义气缸电机端口
#ifndef GPIO_M1
	#define FORWARD	 0
	#define BACKWARD 1
	
	#define GPIO_M1
	#define GPIO_M1CL 		GPIOH
	#define GPIO_Pin_M1CL	GPIO_Pin_11
	#define GPIO_M1RESET 	GPIOH
	#define GPIO_Pin_M1RESET GPIO_Pin_7
	#define GPIO_M1EN		GPIOH
	#define GPIO_Pin_M1EN	GPIO_Pin_9
	#define GPIO_M1CW		GPIOH
	#define GPIO_Pin_M1CW	GPIO_Pin_12
	#define GPIO_M1MO		GPIOH
	#define GPIO_Pin_M1MO	GPIO_Pin_10
#endif
//定义电磁阀端口
#ifndef Valve_GPIO
	#define Valve_GPIO
	#define GPIO_Valve1_4 		GPIOG
	#define GPIO_Valve5_6 		GPIOB
	#define GPIO_Valve7_8 		GPIOE
	#define GPIO_Valve9_12		GPIOI
	#define GPIO_Pin_Valve1 	GPIO_Pin_11	
	#define GPIO_Pin_Valve2 	GPIO_Pin_13	
	#define GPIO_Pin_Valve3 	GPIO_Pin_14
	#define GPIO_Pin_Valve4 	GPIO_Pin_15
	#define GPIO_Pin_Valve5 	GPIO_Pin_5	
	#define GPIO_Pin_Valve6 	GPIO_Pin_8
	#define GPIO_Pin_Valve7 	GPIO_Pin_0	
	#define GPIO_Pin_Valve8 	GPIO_Pin_1
	#define GPIO_Pin_Valve9 	GPIO_Pin_4	
	#define GPIO_Pin_Valve10 	GPIO_Pin_5				 
 	#define GPIO_Pin_Valve11 	GPIO_Pin_6
	#define GPIO_Pin_Valve12 	GPIO_Pin_7
#endif
#ifndef GPIO_AK5351
	#define GPIO_AK5351
	#define GPIO_AK5351_SCLK GPIOB
	#define Pin_AK5351_SCLK	GPIO_Pin_13
	#define GPIO_AK5351_LRCK GPIOB
	#define Pin_AK5351_LRCK GPIO_Pin_12
	#define GPIO_AK5351_SDATA GPIOC
	#define Pin_AK5351_SDATA GPIO_Pin_3
	
	#define GPIO_AK5351_PD 	GPIOB
	#define Pin_AK5351_PD 	GPIO_Pin_14
	#define GPIO_AK5351_FSYNC GPIOD
	#define Pin_AK5351_FSYNC GPIO_Pin_8

	#define GPIO_AK5351_MCLK GPIOC
	#define Pin_AK5351_MCLK GPIO_Pin_6
#endif
#ifndef GPIO_AK5385
	#define GPIO_AK5385
	#define GPIO_AK5385_SCLK GPIOB
	#define Pin_AK5385_SCLK	GPIO_Pin_13
	#define GPIO_AK5385_LRCK GPIOB
	#define Pin_AK5385_LRCK GPIO_Pin_12
	#define GPIO_AK5385_SDATA GPIOB
	#define Pin_AK5385_SDATA GPIO_Pin_15
	#define GPIO_AK5385_DIF GPIOH
	#define Pin_AK5385_DIF GPIO_Pin_14	
	#define GPIO_AK5385_PDN 	GPIOB
	#define Pin_AK5385_PDN 	GPIO_Pin_14
	#define GPIO_AK5385_MS GPIOG
	#define Pin_AK5385_MS GPIO_Pin_8

//	#define GPIO_AK5385_DFS1 GPIOB
//	#define Pin_AK5385_DFS1 GPIO_Pin_10
//	#define GPIO_AK5385_DFS0 GPIOB
//	#define Pin_AK5385_DFS0 GPIO_Pin_11
	#define GPIO_AK5385_MCLK GPIOC
	#define Pin_AK5385_MCLK GPIO_Pin_6
	#define GPIO_AK5385_CKS0 GPIOC
	#define Pin_AK5385_CKS0 GPIO_Pin_7	
	#define GPIO_AK5385_CKS1 GPIOH
	#define Pin_AK5385_CKS1 GPIO_Pin_13
#endif
#ifndef GPIO_SPEAKER
	#define GPIO_SPEAKER GPIOG
	#define GPIO_Pin_SPEAKER GPIO_Pin_10
#endif
#ifndef GPIO_ERROR
	#define GPIO_ERROR 	GPIOB
	#define ERROR_Pin 	GPIO_Pin_9
#endif
#ifndef GPIO_TripSwitch
	#define GPIO_TripSwitch GPIOD
	#define GPIO_Pin_TripSwitch GPIO_Pin_7
	#define GPIO_PORT_SOURCE_TripSwitch GPIO_PortSourceGPIOD
	#define GPIO_PIN_SOURCE_TripSwitch GPIO_PinSource7
	#define EXTI_LINE_TripSwitch EXTI_Line7
#endif
//?¨ò??a1?
#ifndef ON_OFF
	#define ON_OFF
	#define ON 1
	#define OFF 0
#endif
//定义样品在位端口
#define SWITCH1  PFin(7)
#define SWITCH2  PIin(11)
#define SWITCH3  PIin(10)
#define SWITCH4  PIin(9)
#define SWITCH5  PCin(13)
#define SWITCH6  PIin(8)
//定义打印机端口
//#define STB  PBout(8)
//#define SEL  PEin(0)  
//#define BUSY  PBin(9)
extern uint16_t uhADCConvertedValue[5];
extern uint8_t ButtonStatus;
//小电机加速和记脉冲变量
extern volatile unsigned int Step_LM;
extern const unsigned int Speedup[200];
//ADC采样参数
#define  ADCNUM 25	  //延时2s后进行
extern u16	ADCConv[ADCNUM];
extern u8	ADCIndex;
extern u16	ADCResult[36];
//???×μ??ú±?á?
extern volatile uint16_t PulseNum;
extern volatile uint16_t PulseCount;
extern volatile uint8_t 	StartSpeed;
extern volatile uint8_t 	TargeSpeed;
extern volatile uint8_t 	StepTimes_1;
extern volatile uint16_t StepCount_1;
extern volatile uint8_t 	EndSpeed;
extern volatile uint8_t 	StepTimes_2;
extern volatile uint16_t StepCount_2;
extern volatile uint16_t AddedNum;	 
extern volatile uint8_t 	cw_status;
extern volatile u8 flagPress;
extern unsigned int 	m;
extern double 	m_lCf[9];
#define T m_lCf[7]	  //试压最大压力，小于5400
//AK5351 ±?á?
#define DataLength 3600
extern 	double m_lCfC13[6];
extern  u16  Pressure0,Pressure1,Pressure2; 
extern volatile unsigned int RxLeftIdx;
extern volatile unsigned int RxRightIdx;
extern volatile u16 AK_Left_Data[DataLength*2];
extern volatile u16 AK_Right_Data[DataLength*2];
extern u8 m_bChopper;
extern u8	m_bMeasureBreak;
extern 	u32	Intensity1,Intensity2;
extern 	u8  TripSwitchStatus;
void Speaker_Config(void);
void ADC_Config(void);
void EXTI_Config(void);
void PRINT_Init (void);
//ó?ò?D???3?ê??ˉ
void AK5385_Config(void);
void AK5351_Config(void);
//ó?ò?D???×a??
void AK_Conv(void);
//?D1a??μ??ú3?ê??ˉ
void LightModulation_Config(void);
//?D1a??μ??ú????status=1?a??status=0í￡?1
void LightModulation(u8 status);
//μ?′?·§GPIOéè?¨
void Valve_GPIO_Config(void);
//???×?y?ˉoˉêy3?ê??ˉ
void Motor_Config(void);
void Motor_Init(void);
unsigned int ADC_1(unsigned char ch);
void Sys_100msClock_Config(void);
void Speaker(u8 Num);
void PowerCheck(void);
s16 Test(void);
void AK_Test(void);
void PerkCheck(void);
void Valve(unsigned char Vnum);
void Motorun(u8 En,u16 FPulseNum,u8 Cw,u8 IfConv,
			u8 FStartSpeed,u8 FTargeSpeed,u8 FStepTimes_1,u16 FStepCount_1,
			u8 FEndSpeed,u8 FStepTimes_2,u16 FStepCount_2,u16 FAddedNum,
			u8 vnum1,u8 vnum2,u8 vnum3);
#endif

/***************************** END OF FILE *********************************/
