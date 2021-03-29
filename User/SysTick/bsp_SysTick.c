#include "bsp_SysTick.h"

// ��� SysTick_Config()�⺯�� �� core_cm3.h��

//����������ʱ���������Գɹ����� TM1637��Ψһ���������ʱ���ȵĲ���


#if 1					//����һ  ʹ�����ַ�����ʱ�����������в���1us��ʱ����ʾ��������ʵ����ʱΪ2.44us

// couter ��1��ʱ�� ���� 1/systick_clk
// ��counter �� reload ��ֵ��С��0��ʱ��Ϊһ��ѭ��������������ж���ִ���жϷ������
// ͬʱ CTRL �� countflag λ����1
// ��һ��ѭ����ʱ��Ϊ reload * (1/systick_clk)

/*
 * t : ��ʱʱ��
 * Ticks : ���ٸ�ʱ�����ڲ���һ���ж�
 * f : ʱ��Ƶ�� 72000000
 * t = Ticks * 1/f = (72000000/1000000) * (1/72000000) = 1us
 */

void SysTick_Delay_Us( __IO uint32_t us )
{
    uint32_t i;
    SysTick_Config( SystemCoreClock / 1000000 );

    for( i = 0; i < us; i++ )
    {
        // ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
        while( !( ( SysTick->CTRL ) & ( 1 << 16 ) ) );
    }
    // �ر�SysTick��ʱ��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_Ms( __IO uint32_t ms )
{
    uint32_t i;
    SysTick_Config( SystemCoreClock / 1000 );

    for( i = 0; i < ms; i++ )
    {
        // ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
        // ����1ʱ����ȡ��λ����0
        while( !( ( SysTick->CTRL ) & ( 1 << 16 ) ) );
    }
    // �ر�SysTick��ʱ��
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

#else         //������  ʹ�����ַ�����ʱ�����������в���1us��ʱ����ʾ��������ʵ����ʱΪ1.12us


void delay_config( void )
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;     //ʱ��ԴΪϵͳʱ�� 72MHz
    //��ʾ�������� ������ֵ����Ϊ 71ʱ 1us����ʱ��ʾ��������Ϊ1.67us
    //����ʵ�ʲ��� ������ֵ����Ϊ 50ʱ��1us��ʱʵ�ʲ���Ϊ 1.12us
    SysTick->LOAD = 51 - 1;                          //����ֵΪ72-1��ÿ1us���һ��
}

void delay_ms( vu32 nTime )
{
    nTime *= 1000;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;        //ʹ��SysTick����ʼ����
    while( nTime-- )
    {
        while( ( SysTick->CTRL & 0X010000 ) == 0 );  //�ȴ�COUNTFLAG��־λ��1
    }
    SysTick->CTRL &= ( ~SysTick_CTRL_ENABLE_Msk );   //ʧ��SysTick��ֹͣ����
}

void delay_us( vu32 nTime )
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    while( nTime-- )
    {
        while( ( SysTick->CTRL & 0X010000 ) == 0 );
    }
    SysTick->CTRL &= ( ~SysTick_CTRL_ENABLE_Msk );
}


#endif 

/*********************************************END OF FILE**********************/
