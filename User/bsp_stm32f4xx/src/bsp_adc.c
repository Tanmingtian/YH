/*
*********************************************************************************************************
*
*	模块名称 : ADC驱动模块
*	文件名称 : bsp_adc.c
*	版    本 : V1.0
*	说    明 : ADC3工作在注入模式
*	修改记录 :
*		版本号    日期        作者     说明
*		V1.0    2014-01-08  armfly   正式发布
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"


/* define ---------------------------------------------------------------------*/
#define ADC3_DR_ADDRESS    ((uint32_t)0x4001224C)

/* 供本文件使用 --------------------------------------------------------------*/
static void TIM1_Config(void);
/*
*********************************************************************************************************
*	函 数 名: bsp_InitADC
*	功能说明: ADC初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitADC(void)
{  
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    GPIO_InitTypeDef      GPIO_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 配置ADC中断，用于注入中断模式 */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* 使能 ADC3, DMA2 和 GPIO 时钟 --------------------------------------------*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

    /* 配置ADC引脚 -------------------------------------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* ADC 公共部分初始化 -------------------------------------------------------*/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* ADC3 初始化 --------------------------------------------------------------*/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigInjecConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC3;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    /* ADC3 注入通道配置 -----------------------------------------------------------*/
    ADC_InjectedChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime_3Cycles);
    /* 设置注入序列长度 */
    ADC_InjectedSequencerLengthConfig(ADC3, 1); 
    /* 注入通道外部触发配置 */
    ADC_ExternalTrigInjectedConvConfig(ADC3, ADC_ExternalTrigInjecConv_T1_CC4);
    ADC_ExternalTrigInjectedConvEdgeConfig(ADC3, ADC_ExternalTrigInjecConvEdge_Rising);
    
    /* 使能注入中断 */
    ADC_ITConfig(ADC3, ADC_IT_JEOC, ENABLE);
    
    /* 使能ADC3 */
    ADC_Cmd(ADC3, ENABLE);
    
    TIM1_Config();
}

/*
*********************************************************************************************************
*	函 数 名: TIM1_Config
*	功能说明: 配置定时器1，用于触发ADC，每秒更新一次
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void TIM1_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);			   			//使能定时器1时钟
    
    TIM_Cmd(TIM1, DISABLE);	
    
     /* --------------------------------------------------------
    system_stm32f4xx.c 文件中 void SetSysClock(void) 函数对时钟的配置如下：

    HCLK = SYSCLK / 1     (AHB1Periph)
    PCLK2 = HCLK / 2      (APB2Periph)
    PCLK1 = HCLK / 4      (APB1Periph)

    因为APB1 prescaler != 1, 所以 APB1上的TIMxCLK = PCLK1 x 2 = SystemCoreClock / 2;
    因为APB2 prescaler != 1, 所以 APB2上的TIMxCLK = PCLK2 x 2 = SystemCoreClock;

    APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
    APB2 定时器有 TIM1, TIM8 ,TIM9, TIM10, TIM11
          
    TIM6 更新周期是 = TIM1CLK / （TIM_Period + 1）/（TIM_Prescaler + 1）
    ----------------------------------------------------------- */
    
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 				   //初始化定时器1的寄存器为复位值
    TIM_TimeBaseStructure.TIM_Period = 168000000 / 10000-1;    //ARR自动重装载寄存器周期的值(定时时间）到设置频率后产生个更新或者中断(也是说定时时间到)
    TIM_TimeBaseStructure.TIM_Prescaler = 16800-1;   						   //PSC时钟预分频数 例如：时钟频率=TIM1CLK/(时钟预分频+1)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    				   //CR1->CKD时间分割值
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	   //CR1->CMS[1:0]和DIR定时器模式 向上计数
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				      //CCMR2在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为有效电平，否则为无效电平
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;         //CCER 输出使能          
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period / 2;//CCR3同计数器TIMx_CNT的比较，并在OC4端口上产生输出信号 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    	     //CCER输出极性设置	高电平有效     
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    //TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);					 //CMR2 设置预装载使能  更新事件产生时写入有效
    //TIM_ARRPreloadConfig(TIM1, ENABLE);		   		 				 //CR1  设置ARR自动重装 更新事件产生时写入有效
    TIM_Cmd(TIM1, ENABLE);	
    TIM_CtrlPWMOutputs(TIM1, ENABLE);  								   //使能PWM 输出
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
