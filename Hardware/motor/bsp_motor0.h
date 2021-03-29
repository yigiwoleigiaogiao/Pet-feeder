#ifndef __MOTOR0_H
#define	__MOTOR0_H
#include "stm32f10x.h"
#include "sys.h"

#define L0A    PAout(4) 			//A ��
#define L0B    PAout(5) 			//B ��
#define L0C    PAout(6) 			//C ��
#define L0D    PAout(7) 			//D ��

/* ���������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define L0A_GPIO_PORT    	GPIOA		                /* GPIO�˿� */
#define L0A_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define L0A_GPIO_PIN			  GPIO_Pin_4

#define L0B_GPIO_PORT    	GPIOA
#define L0B_GPIO_CLK 	    RCC_APB2Periph_GPIOA
#define L0B_GPIO_PIN		    GPIO_Pin_5

#define L0C_GPIO_PORT    	GPIOA
#define L0C_GPIO_CLK 	    RCC_APB2Periph_GPIOA
#define L0C_GPIO_PIN		    GPIO_Pin_6

#define L0D_GPIO_PORT    	GPIOA
#define L0D_GPIO_CLK 	    RCC_APB2Periph_GPIOA
#define L0D_GPIO_PIN		    GPIO_Pin_7
void Motor0_GPIO_Config( void );
void Motor0CW( void );
void Motor0CCW( void );
void Motor0Stop( void );
void FanBlade( void );

#endif /* __LED_H */
