/*
*********************************************************************************************************
*
*	ģ������ : ADC����ģ��
*	�ļ����� : bsp_adc.c
*	��    �� : V1.0
*	˵    �� : ADC��ͨ��ɨ��
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
#define ADC1_DR_ADDRESS          ((uint32_t)0x4001204C)

/* ���� ----------------------------------------------------------------------*/
__IO uint16_t uhADCConvertedValue[5];

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
	DMA_InitTypeDef       DMA_InitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;
	
	/* ʹ������ʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA  | RCC_AHB1Periph_GPIOB| RCC_AHB1Periph_GPIOC, ENABLE);
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

	/* DMA2 Stream0 channel0 ����-------------------------------------------------- */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&uhADCConvertedValue;;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 4;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

	/* DMA2_Stream0 enable */
	DMA_Cmd(DMA2_Stream0, ENABLE);
    
    /****************************************************************************   
	  PCLK2 = HCLK / 2 
	  ����ѡ�����2��Ƶ
	  ADCCLK = PCLK2 /8 = HCLK / 8 = 168 / 8 = 21M
      ADC����Ƶ�ʣ� Sampling Time + Conversion Time = 480 + 12 cycles = 492cyc
                    Conversion Time = 21MHz / 492cyc = 42.6ksps. 
	*****************************************************************************/
    
	/* ADC Common ���� ----------------------------------------------------------*/
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
	ADC_InitStructure.ADC_NbrOfConversion = 4;
    ADC_Init(ADC1, &ADC_InitStructure);
    
     /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

  	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 5, ADC_SampleTime_15Cycles);
    /* ADC1 regular channel18 (VBAT) configuration ******************************/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_15Cycles);
    /* ADC1 regular channel18 (VBAT) configuration *****************************/
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_15Cycles);
    
    /* ADC1 regular channels 10, 11 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 3, ADC_SampleTime_15Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 4, ADC_SampleTime_15Cycles);   

//    /* Enable VBAT channel */
//    ADC_VBATCmd(ENABLE); 
//    
//    ADC_TempSensorVrefintCmd(ENABLE); 

    /* Enable DMA request after last transfer (Single-ADC mode) */
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

    /* Enable ADC1 **************************************************************/
    ADC_Cmd(ADC1, ENABLE);
    
        /* Start ADC1 Software Conversion */
    ADC_SoftwareStartConv(ADC1);
}


/*
*************************************************************************************************
  VSENSE���¶ȴ������ĵ�ǰ�����ѹ����ADC_DR �Ĵ����еĽ��ADC_ConvertedValue֮���ת����ϵΪ�� 
            ADC_ConvertedValue * Vdd
  VSENSE = --------------------------
            Vdd_convert_value(0xFFF)  
    ADCת�������Ժ󣬶�ȡADC_DR�Ĵ����еĽ����ת���¶�ֵ���㹫ʽ���£�
          V25 - VSENSE
  T(��) = ------------  + 25
           Avg_Slope
  V25��  �¶ȴ�������25��ʱ �������ѹ������ֵ0.76 V��
  Avg_Slope���¶ȴ����������ѹ���¶ȵĹ�������������ֵ2.5 mV/�档
************************************************************************************************
*/
//float GetTemp(uint16_t advalue)
//{
//    float Vtemp_sensor;
//    float  Current_Temp;
//    
//    Vtemp_sensor = advalue * 3.3/ 4095;  				           
//    Current_Temp = (Vtemp_sensor - 0.76)/0.0025 + 25;  
//    
//    return Current_Temp;
//}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
