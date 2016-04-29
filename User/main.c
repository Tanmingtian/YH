
/*单片机由407IG更换为427IG:option->C/C++ ->define ->USE_STDPERIPH_DRIVER,STM32F427_437xx;将FSMC改为FMC*/

#include "bsp.h"			/* 底层硬件驱动 */
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
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/	uint16_t ucStatus;
u8 test=1;
int main(void)
{
	bsp_Init();	/* 为了是main函数看起来更简洁些，我们将硬件初始化的代码封装到这个函数 */
	LoadParam();	/* 读取应用程序参数, 该函数在param.c */

	LCD_InitHard();	/* 初始化显示器硬件(配置GPIO和FSMC,给LCD发送初始化指令) */
	TOUCH_InitHard();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
//LCD_ClrScr(CL_BLUE);  		/* 清屏，【背景蓝色 */

//LCD_SetBackLight(g_tParam.ucBackLight);		/* 设置背光亮度。 */
	ucStatus = MS_MAIN_MENU;	/* 初始状态 = 图标界面 */
	
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
//			 	TOUCH_Calibration();		/* 校准触摸, 该界面实现在bsp_touch.c */
//			 	ucStatus = MS_MAIN_MENU; 	/* 校准完毕后，返回到主界面 */
//			 	break;
			 case MS_MAIN_MENU:
					
					ucStatus = MainMenu();		/* 主界面状态 */
					break;
			 case MS_MEASURETURE:			/* 样品检测 */

					MainTask();
					ucStatus = MS_MAIN_MENU;     		 
					break;
			 case MS_QC:			/* 质量控制 */
			 
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_PREFERENCES:			/* 参数设置 */
			
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_RECORD:			/* 检测记录 */
			 
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_PRINT:			/* 打印 */
			 
					ucStatus = MS_MAIN_MENU;
					break;
			 case MS_MAINTAINING:			/* 维护 */
					
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

