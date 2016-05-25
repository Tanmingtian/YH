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

	//�г̿����ⲿ�ж�
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
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ��Ӳ���豸��ֻ��Ҫ����һ�Ρ��ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����
*			 ȫ�ֱ�����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOI, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_ADC1|RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5|RCC_APB1Periph_SPI2 ,ENABLE);
	NVIC_Configuration();
	bsp_InitTimer();	/* ��ʼ��ϵͳ�δ�ʱ�� (�˺����Ὺ�ж�) */
//	bsp_InitExtSRAM();	/* ����FSMC����, ����SRAM���� */
//	bsp_InitNorFlash();	/* ��ʼ��FSMC NOR Flash */
	bsp_InitI2C();		/* ����I2C���� */
	bsp_InitSPIBus();	/* ����SPI���� */
	AK5385_Config();
	bsp_DelayMS(20);	/* ������豸��Ҫ�ӳٺ��ʼ�� */
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
*	�� �� ��: bsp_RunPer1s
*	����˵��: �ú���ÿ��1s��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//extern __IO uint8_t s_ucRA8875BusyNow;
void bsp_RunPer1s(void)
{
		
}
/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//extern __IO uint8_t s_ucRA8875BusyNow;
void bsp_RunPer10ms(void)
{
	/* RA8875 ����*/
	if (g_ChipID == IC_8875)
	{
	    /* ��Դ�����־ */
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
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
*			 ���Է��ڴ˺��������磺��������ɨ�衣
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer1ms(void)
{
	TOUCH_Scan();		/* ����ɨ�� */
	//PS2_Timer();		/* PS/2���̺���궨ʱ���� */
	
	GT811_Timer10ms();	/* ���ݴ�������������� */
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//extern void SaveScreenToBmp(uint16_t _index);
void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
	GT811_Scan();
	bsp_KeyScan();
//	GT811_Scan();	/* ����ɨ�� */
//	if (bsp_GetKey2() == SYS_DOWN_K1K2)	/* K1 K2 ��ϼ����ڽ��� */
//	{
//		static uint16_t s_file_no = 0;

//		SaveScreenToBmp(s_file_no++);	/* ��ͼ����Ϊbmp�ļ��� SD����Ŀ¼ */
//	}
}

/*****************************   END OF FILE   *********************************/
