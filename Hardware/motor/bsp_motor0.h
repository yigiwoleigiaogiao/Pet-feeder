#ifndef __MOTOR0_H
#define	__MOTOR0_H
#include "stm32f10x.h"
#include "sys.h"

#define L0A    PAout(4) 			//A 相
#define L0B    PAout(5) 			//B 相
#define L0C    PAout(6) 			//C 相
#define L0D    PAout(7) 			//D 相

/* 定义电机连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define L0A_GPIO_PORT    	GPIOA		                /* GPIO端口 */
#define L0A_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
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
