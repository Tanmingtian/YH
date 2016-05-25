#include "bsp.h"
#include "measurement.h"
#include "motor.h"

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* SPI2 IRQ Channel configuration */
	NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//行程开关外部中断
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* TIM1 update Channel configuration */
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//timer2
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//timer3
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	 
 
}
/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化硬件设备。只需要调用一次。该函数配置CPU寄存器和外设的寄存器并初始化一些全局变量。
*			 全局变量。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOI, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_ADC1|RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5|RCC_APB1Periph_SPI2 ,ENABLE);
	NVIC_Configuration();
	bsp_InitTimer();	/* 初始化系统滴答定时器 (此函数会开中断) */
//	bsp_InitExtSRAM();	/* 配置FSMC总线, 用于SRAM访问 */
//	bsp_InitNorFlash();	/* 初始化FSMC NOR Flash */
	bsp_InitI2C();		/* 配置I2C总线 */
	bsp_InitSPIBus();	/* 配置SPI总线 */
	AK5385_Config();
	bsp_DelayMS(20);	/* 后面的设备需要延迟后初始化 */
	Speaker_Config();	
//	ADC_Config();
	bsp_InitADC();
	EXTI_Config();
  LightModulation_Config();
  Motor_Config();
//	Sys_100msClock_Config();
  
//SPI_FLASH_Init();	
//	PRINT_Init();	
}
/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer1s
*	功能说明: 该函数每隔1s被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
//extern __IO uint8_t s_ucRA8875BusyNow;
void bsp_RunPer1s(void)
{
		
}
/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer10ms
*	功能说明: 该函数每隔10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
//extern __IO uint8_t s_ucRA8875BusyNow;
void bsp_RunPer10ms(void)
{
	/* RA8875 触摸*/
	if (g_ChipID == IC_8875)
	{
	    /* 资源共享标志 */
		if(s_ucRA8875BusyNow == 0)
		{
			GUI_TOUCH_Exec();
		}
	}
	/* XPT2046 */
	else
	{
		GUI_TOUCH_Exec();	
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer1ms
*	功能说明: 该函数每隔1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
*			 可以放在此函数。比如：触摸坐标扫描。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_RunPer1ms(void)
{
	TOUCH_Scan();		/* 触摸扫描 */
	//PS2_Timer();		/* PS/2键盘和鼠标定时处理 */
	
	GT811_Timer10ms();	/* 电容触摸屏程序计数器 */
}

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
//extern void SaveScreenToBmp(uint16_t _index);
void bsp_Idle(void)
{
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
	GT811_Scan();
	bsp_KeyScan();
//	GT811_Scan();	/* 触摸扫描 */
//	if (bsp_GetKey2() == SYS_DOWN_K1K2)	/* K1 K2 组合键用于截屏 */
//	{
//		static uint16_t s_file_no = 0;

//		SaveScreenToBmp(s_file_no++);	/* 截图保存为bmp文件， SD卡根目录 */
//	}
}

/*****************************   END OF FILE   *********************************/
