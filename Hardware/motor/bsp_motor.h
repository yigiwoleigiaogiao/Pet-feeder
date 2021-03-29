#ifndef __MOTOR_H
#define	__MOTOR_H
#include "stm32f10x.h"
#include "sys.h"

#define LA    PBout(6) 			//A ��
#define LB    PBout(7) 			//B ��
#define LC    PBout(8) 			//C ��
#define LD    PBout(9) 			//D ��

/* ���������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define LA_GPIO_PORT    	GPIOB		                /* GPIO�˿� */
#define LA_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LA_GPIO_PIN			  GPIO_Pin_6

#define LB_GPIO_PORT    	GPIOB
#define LB_GPIO_CLK 	    RCC_APB2Periph_GPIOB
#define LB_GPIO_PIN		    GPIO_Pin_7

#define LC_GPIO_PORT    	GPIOB
#define LC_GPIO_CLK 	    RCC_APB2Periph_GPIOB
#define LC_GPIO_PIN		    GPIO_Pin_8

#define LD_GPIO_PORT    	GPIOB
#define LD_GPIO_CLK 	    RCC_APB2Periph_GPIOB
#define LD_GPIO_PIN		    GPIO_Pin_9

void Motor_GPIO_Config( void );
void MotorCW( void );
void MotorCCW( void );
void MotorStop( void );
void WarehouseGate( void );
void QuickFeed( void );

#endif /* __LED_H */
