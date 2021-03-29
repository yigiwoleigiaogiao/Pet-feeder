
#include "bsp_motor.h"
#include "bsp_motor0.h"
#include "bsp_SysTick.h"

/**
 * @brief  初始化控制电机的IO
 * @param  无
 * @retval 无
 */
void Motor_GPIO_Config( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( LA_GPIO_CLK | LB_GPIO_CLK | LC_GPIO_CLK | LD_GPIO_CLK, ENABLE );

    GPIO_InitStructure.GPIO_Pin = LA_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( LA_GPIO_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = LB_GPIO_PIN;
    GPIO_Init( LB_GPIO_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = LC_GPIO_PIN;
    GPIO_Init( LC_GPIO_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = LD_GPIO_PIN;
    GPIO_Init( LD_GPIO_PORT, &GPIO_InitStructure );
}


/*
步距角：5.625 / 64 = 0.087度 （也就是说理论上，你给一个脉冲，电机外部轴转动0.087度）
也就是说一个脉冲内部转子转5.625度，但是由于减速64倍，所以外部轴只转了0.087度
那么外部轴要转一圈的话，需要360/0.087=4096个脉冲。
采用4相8拍驱动的话，8个脉冲是一个周期，那么就需要4096/8=512个周期，外部轴刚好转一圈
*/
/*
 1相励磁法：每一瞬间只有一个线圈相通，其它休息。（优点）简单，耗电低，精确性良好。
（缺点）力矩小，振动大，每次励磁信号走的角度都是标称角度。
 1相励磁法  A->B->C->D
*/
//u8 phasecw[4] = {0x08, 0x04, 0x02, 0x01}; //正转 电机导通相序  D-C-B-A
//u8 phaseccw[4] = {0x01, 0x02, 0x04, 0x08}; //反转 电机导通相序   A-B-C-D
/*
 2相励磁法：每一瞬间有两个线圈导通。
（优点）力矩大，震动小。（缺点）每励磁信号走的角度都是标称角度。
 2相励磁法  AB->BC->CD->DA
*/
u8 phasecw[4] = {0x0c, 0x06, 0x03,0x09}; //正转 电机导通相序  DC-CB-BA-AD
u8 phaseccw[4] = {0x03, 0x06, 0x0c, 0x09}; //反转 电机导通相序  AB-BC-CD-DA

/*
 1-2相励磁法：1相和2相交替导通。
 优点）精度较高，运转平滑，每送一个励磁信号转动1/2标称角度，称为半步驱动。
（前两种称为4相4拍，这一种称为4相8拍）
 1-2相励磁法  A-->AB-->B->BC->C-->CD->D-->DA
*/
//u8 phasecw[8] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09}; //正转 电机导通相序  D-DC-C-CB-B-BA-A-AD
//u8 phaseccw[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x89}; //反转 电机导通相序  A-AB-B-BC-C-CD-D-DA


//将 A、B、C、D 四项组成一个字节低四位，A为biit0，D为bit1。这样通过数组比较容易给端口赋值。

//顺时针转动
void MotorCW( void )
{
    u8 i;
    u8 temp = 0;
    for( i = 0; i < 4; i++ )
    {
        temp = phasecw[i];

        LD = ( temp >> 3 ) & 0x01;							//取bit4的值
        LC = ( temp >> 2 ) & 0x01;
        LB = ( temp >> 1 ) & 0x01;
        LA = ( temp >> 0 ) & 0x01;							//取bit0的值
        delay_us( 256 ); 													//转速调节    延时小于2ms电机不转
    }
    MotorStop();																//一个周期转动结束后需要复位所有相，否则最后一项如果被设置为高电平后会持续维持高电平。
}
//逆时针转动
void MotorCCW( void )
{
    u8 i;
    u8 temp;
    for( i = 0; i < 4; i++ )
    {
        temp = phaseccw[i];

        LD = ( temp >> 3 ) & 0x01;							//取bit4的值
        LC = ( temp >> 2 ) & 0x01;
        LB = ( temp >> 1 ) & 0x01;
        LA = ( temp >> 0 ) & 0x01;							//取bit0的值

        delay_us( 256 ); //转速调节    延时小于2ms电机不转
    }
    MotorStop();																//一个周期转动结束后需要复位所有相，否则最后一项如果被设置为高电平后会持续维持高电平。
}
//停止转动
void MotorStop( void )
{
    LA = 0;
    LB = 0;
    LC = 0;
    LD = 0;
}
void WarehouseGate( void )
{
			u16 cntC = 0;
			u16 cntCC = 0;
			MotorStop();
			for(cntC=0;cntC<=140;cntC++)
			{
						MotorCW();
			}
			delay_ms( 1000 );
			for(cntCC=0;cntCC<=140;cntCC++)
			{
						MotorCCW();
			}
			MotorStop();
}
void QuickFeed( void )
{
			u16 cntC;
			u16 cntCC;
			MotorStop();
			for(cntC=0;cntC<=140;cntC++)
			{
						MotorCW();
			}
			FanBlade();
			delay_ms( 10 );
			for(cntCC=0;cntCC<=140;cntCC++)
			{
						MotorCCW();
			}
			MotorStop();
}




/*********************************************END OF FILE**********************/
