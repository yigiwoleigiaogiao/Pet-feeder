#ifndef __MOTOR_H
#define	__MOTOR_H
#include "stm32f10x.h"
#include "sys.h"

#define LA    PBout(6) 			//A 相
#define LB    PBout(7) 			//B 相
#define LC    PBout(8) 			//C 相
#define LD    PBout(9) 			//D 相

/* 定义电机连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define LA_GPIO_PORT    	GPIOB		                /* GPIO端口 */
#define LA_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
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
