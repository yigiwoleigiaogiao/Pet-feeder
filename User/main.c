#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
//#include "bsp_led.h"
#include "bsp_SysTick.h"
#include "bsp_motor.h"
#include "bsp_motor0.h"
#include "wifi.h"
#include "usart.h"
#include "misc.h"

int main( void )
{
//    u16 cntC;
//    u16 cntCC;
//		SystemInit();	//配置系统时钟为72M 
//		delay_init();//延时初始化
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//    LED_GPIO_Config();
	
		uart1_init();                       //串口1（与PC通讯）初始化
		uart2_init();                       //串口2（与wifi模块通讯）初始化
		Motor_GPIO_Config();
		Motor0_GPIO_Config();
		wifi_protocol_init();								//wifi初始化
		while(1)
		{	
//			USART_SendData(USART2,0x77);
//			UART2Test();
			wifi_uart_service();
//			MotorStop();
//			for(cntC=0;cntC<=140;cntC++)
//			{
//						MotorCW();
//			}
//			delay_ms( 1000 );
//			for(cntCC=0;cntCC<=140;cntCC++)
//			{
//						MotorCCW();
//			}
//			MotorStop();
//			delay_ms( 1000 );
		}
}

