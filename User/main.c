
/*��Ƭ����407IG����Ϊ427IG:option->C/C++ ->define ->USE_STDPERIPH_DRIVER,STM32F427_437xx;��FSMC��ΪFMC*/

#include "bsp.h"			/* �ײ�Ӳ������ */
#include "MainTask.h"
#include "main_menu.h"
#include "main.h"
#include "measurement.h"
#include "param.h"
#include "PROGBAR.h"
#include "motor.h"
#include "math.h"
extern volatile unsigned int m;
		u16	A1,A2,A3,A4;
		float	tempA,tempB,tempC,tempD ;
void SystemCheck(void)
{
	Valve_GPIO_Config();
	while(1)
	{
		
		tempA = ADC_1(ADC_T_10A);	
		tempA = 3.0 * tempA / 4096.0 / 2.0;
		tempA = -(-232.6 * log(log10(37.4 * 1000.0 * tempA / (1.2 - tempA))) + 343.82);
		A1=tempA*10;
		tempB = ADC_1(ADC_T_10B);
		tempB = 3.0 * tempB / 4096.0 / 2.0;
		tempB = -(-232.6 * log(log10(37.4 * 1000.0 * tempB / (1.2 - tempB))) + 343.82);
		A2=tempB*10;
		tempC = ADC_1(ADC_T18);
		tempC = 3.0 * tempC / 4096.0;
		tempC = (((2500.0*4.0*tempC)/(2.5*490.0))+(2500.0*100.0)/2600.0)/(1-((4.0*tempC)/(490.0*2.5))-(100.0/2600.0));
		tempC = 0.001 * tempC * tempC + 2.3589 * tempC - 245.87;
		A3=tempC*10;
		tempD = ADC_1(ADC_T42);
		tempD = 3.0 * tempD / 4096.0;
		tempD = (((2500.0*4.0*tempD)/(490.0*2.5))+(2500.0*100.0)/2600.0)/(1-((4.0*tempD)/(490.0*2.5))-(100.0/2600.0));
		tempD = (tempD - 100.0) / 0.385 - 1;
		A4=tempD*10;
		bsp_DelayMS(5);
		if(A1>85&&A1<110&&A2>85&&A2<110&&A3>150&&A3<250&&A4>360&&A4<505)
		{
			break;
		}
	}
	Motor_Init();	
	PowerCheck();
	m=Test();
	PerkCheck();
}
/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/	uint16_t ucStatus;
u8 test=1;
int main(void)
{
	bsp_Init();	/* Ϊ����main���������������Щ�����ǽ�Ӳ����ʼ���Ĵ����װ��������� */
	LoadParam();	/* ��ȡӦ�ó������, �ú�����param.c */

	LCD_InitHard();	/* ��ʼ����ʾ��Ӳ��(����GPIO��FSMC,��LCD���ͳ�ʼ��ָ��) */
	TOUCH_InitHard();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
//LCD_ClrScr(CL_BLUE);  		/* ��������������ɫ */

//LCD_SetBackLight(g_tParam.ucBackLight);		/* ���ñ������ȡ� */
	ucStatus = MS_MAIN_MENU;	/* ��ʼ״̬ = ͼ����� */
	
//	LightModulation(ON);
//	while(test)
//	{
//		bsp_DelayMS(10000);
//		AK_Test();
//	}

	SystemCheck();
	while (1)
	{
		switch (ucStatus)
		{
//		case MS_CALIBRATION:
//			 	TOUCH_Calibration();		/* У׼����, �ý���ʵ����bsp_touch.c */
//			 	ucStatus = MS_MAIN_MENU; 	/* У׼��Ϻ󣬷��ص������� */
//			 	break;
			 case MS_MAIN_MENU:
					
					ucStatus = MainMenu();		/* ������״̬ */
					break;
			 case MS_MEASURETURE:			/* ��Ʒ��� */

					MainTask();
					ucStatus = MS_MAIN_MENU;     		 
					break;
			 case MS_QC:			/* �������� */
			 
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_PREFERENCES:			/* �������� */
			
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_RECORD:			/* ����¼ */
			 
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_PRINT:			/* ��ӡ */
			 
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_MAINTAINING:			/* ά�� */
					
					TOUCH_Calibration();
					ucStatus = MS_MAIN_MENU;
					break;
			default:
				
					ucStatus = MS_MAIN_MENU;
					break;
		}
	}
    
	
}

/***************************** END OF FILE*********************************/

