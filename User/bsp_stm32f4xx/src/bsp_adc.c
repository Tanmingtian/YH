/*
*********************************************************************************************************
*
*	ģ������ : ADC����ģ��
*	�ļ����� : bsp_adc.c
*	��    �� : V1.0
*	˵    �� : ADC3������ע��ģʽ
*	�޸ļ�¼ :
*		�汾��    ����        ����     ˵��
*		V1.0    2014-01-08  armfly   ��ʽ����
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"


/* define ---------------------------------------------------------------------*/
#define ADC3_DR_ADDRESS    ((uint32_t)0x4001224C)

/* �����ļ�ʹ�� --------------------------------------------------------------*/
static void TIM1_Config(void);
/*
*********************************************************************************************************
*	�� �� ��: bsp_InitADC
*	����˵��: ADC��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitADC(void)
{  
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    GPIO_InitTypeDef      GPIO_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;

    /* ����ADC�жϣ�����ע���ж�ģʽ */
    NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* ʹ�� ADC3, DMA2 �� GPIO ʱ�� --------------------------------------------*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

    /* ����ADC���� -------------------------------------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* ADC �������ֳ�ʼ�� -------------------------------------------------------*/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* ADC3 ��ʼ�� --------------------------------------------------------------*/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigInjecConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC3;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    /* ADC3 ע��ͨ������ -----------------------------------------------------------*/
    ADC_InjectedChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime_3Cycles);
    /* ����ע�����г��� */
    ADC_InjectedSequencerLengthConfig(ADC3, 1); 
    /* ע��ͨ���ⲿ�������� */
    ADC_ExternalTrigInjectedConvConfig(ADC3, ADC_ExternalTrigInjecConv_T1_CC4);
    ADC_ExternalTrigInjectedConvEdgeConfig(ADC3, ADC_ExternalTrigInjecConvEdge_Rising);
    
    /* ʹ��ע���ж� */
    ADC_ITConfig(ADC3, ADC_IT_JEOC, ENABLE);
    
    /* ʹ��ADC3 */
    ADC_Cmd(ADC3, ENABLE);
    
    TIM1_Config();
}

/*
*********************************************************************************************************
*	�� �� ��: TIM1_Config
*	����˵��: ���ö�ʱ��1�����ڴ���ADC��ÿ�����һ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void TIM1_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);			   			//ʹ�ܶ�ʱ��1ʱ��
    
    TIM_Cmd(TIM1, DISABLE);	
    
     /* --------------------------------------------------------
    system_stm32f4xx.c �ļ��� void SetSysClock(void) ������ʱ�ӵ��������£�

    HCLK = SYSCLK / 1     (AHB1Periph)
    PCLK2 = HCLK / 2      (APB2Periph)
    PCLK1 = HCLK / 4      (APB1Periph)

    ��ΪAPB1 prescaler != 1, ���� APB1�ϵ�TIMxCLK = PCLK1 x 2 = SystemCoreClock / 2;
    ��ΪAPB2 prescaler != 1, ���� APB2�ϵ�TIMxCLK = PCLK2 x 2 = SystemCoreClock;

    APB1 ��ʱ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13, TIM14
    APB2 ��ʱ���� TIM1, TIM8 ,TIM9, TIM10, TIM11
          
    TIM6 ���������� = TIM1CLK / ��TIM_Period + 1��/��TIM_Prescaler + 1��
    ----------------------------------------------------------- */
    
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 				   //��ʼ����ʱ��1�ļĴ���Ϊ��λֵ
    TIM_TimeBaseStructure.TIM_Period = 168000000 / 10000-1;    //ARR�Զ���װ�ؼĴ������ڵ�ֵ(��ʱʱ�䣩������Ƶ�ʺ���������»����ж�(Ҳ��˵��ʱʱ�䵽)
    TIM_TimeBaseStructure.TIM_Prescaler = 16800-1;   						   //PSCʱ��Ԥ��Ƶ�� ���磺ʱ��Ƶ��=TIM1CLK/(ʱ��Ԥ��Ƶ+1)
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    				   //CR1->CKDʱ��ָ�ֵ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	   //CR1->CMS[1:0]��DIR��ʱ��ģʽ ���ϼ���
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				      //CCMR2�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;         //CCER ���ʹ��          
    TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period / 2;//CCR3ͬ������TIMx_CNT�ıȽϣ�����OC4�˿��ϲ�������ź� 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    	     //CCER�����������	�ߵ�ƽ��Ч     
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    //TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);					 //CMR2 ����Ԥװ��ʹ��  �����¼�����ʱд����Ч
    //TIM_ARRPreloadConfig(TIM1, ENABLE);		   		 				 //CR1  ����ARR�Զ���װ �����¼�����ʱд����Ч
    TIM_Cmd(TIM1, ENABLE);	
    TIM_CtrlPWMOutputs(TIM1, ENABLE);  								   //ʹ��PWM ���
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
