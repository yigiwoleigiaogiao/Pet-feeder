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
//		SystemInit();	//����ϵͳʱ��Ϊ72M 
//		delay_init();//��ʱ��ʼ��
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//    LED_GPIO_Config();
	
		uart1_init();                       //����1����PCͨѶ����ʼ��
		uart2_init();                       //����2����wifiģ��ͨѶ����ʼ��
		Motor_GPIO_Config();
		Motor0_GPIO_Config();
		wifi_protocol_init();								//wifi��ʼ��
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

