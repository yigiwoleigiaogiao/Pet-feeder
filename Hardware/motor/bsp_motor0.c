
#include "bsp_motor0.h"
#include "bsp_SysTick.h"

/**
 * @brief  ��ʼ��������Ҷ�����IO
 * @param  ��
 * @retval ��
 */
void Motor0_GPIO_Config( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( L0A_GPIO_CLK | L0B_GPIO_CLK | L0C_GPIO_CLK | L0D_GPIO_CLK, ENABLE );

    GPIO_InitStructure.GPIO_Pin = L0A_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( L0A_GPIO_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = L0B_GPIO_PIN;
    GPIO_Init( L0B_GPIO_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = L0C_GPIO_PIN;
    GPIO_Init( L0C_GPIO_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = L0D_GPIO_PIN;
    GPIO_Init( L0D_GPIO_PORT, &GPIO_InitStructure );
}


/*
����ǣ�5.625 / 64 = 0.087�� ��Ҳ����˵�����ϣ����һ�����壬����ⲿ��ת��0.087�ȣ�
Ҳ����˵һ�������ڲ�ת��ת5.625�ȣ��������ڼ���64���������ⲿ��ֻת��0.087��
��ô�ⲿ��ҪתһȦ�Ļ�����Ҫ360/0.087=4096�����塣
����4��8�������Ļ���8��������һ�����ڣ���ô����Ҫ4096/8=512�����ڣ��ⲿ��պ�תһȦ
*/
/*
 1�����ŷ���ÿһ˲��ֻ��һ����Ȧ��ͨ��������Ϣ�����ŵ㣩�򵥣��ĵ�ͣ���ȷ�����á�
��ȱ�㣩����С���񶯴�ÿ�������ź��ߵĽǶȶ��Ǳ�ƽǶȡ�
 1�����ŷ�  A->B->C->D
*/
//u8 phase0cw[4] = {0x08, 0x04, 0x02, 0x01}; //��ת �����ͨ����  D-C-B-A
//u8 phase0ccw[4] = {0x01, 0x02, 0x04, 0x08}; //��ת �����ͨ����   A-B-C-D
/*
 2�����ŷ���ÿһ˲����������Ȧ��ͨ��
���ŵ㣩���ش���С����ȱ�㣩ÿ�����ź��ߵĽǶȶ��Ǳ�ƽǶȡ�
 2�����ŷ�  AB->BC->CD->DA
*/
u8 phase0cw[4] = {0x0c, 0x06, 0x03,0x09}; //��ת �����ͨ����  DC-CB-BA-AD
u8 phase0ccw[4] = {0x03, 0x06, 0x0c, 0x09}; //��ת �����ͨ����  AB-BC-CD-DA

/*
 1-2�����ŷ���1���2�ཻ�浼ͨ��
 �ŵ㣩���Ƚϸߣ���תƽ����ÿ��һ�������ź�ת��1/2��ƽǶȣ���Ϊ�벽������
��ǰ���ֳ�Ϊ4��4�ģ���һ�ֳ�Ϊ4��8�ģ�
 1-2�����ŷ�  A-->AB-->B->BC->C-->CD->D-->DA
*/
//u8 phase0cw[8] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09}; //��ת �����ͨ����  D-DC-C-CB-B-BA-A-AD
//u8 phase0ccw[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x89}; //��ת �����ͨ����  A-AB-B-BC-C-CD-D-DA


//�� A��B��C��D �������һ���ֽڵ���λ��AΪbiit0��DΪbit1������ͨ������Ƚ����׸��˿ڸ�ֵ��

//˳ʱ��ת��
void Motor0CW( void )
{
    u8 i;
    u8 temp = 0;
    for( i = 0; i < 4; i++ )
    {
        temp = phase0cw[i];

        L0D = ( temp >> 3 ) & 0x01;							//ȡbit4��ֵ
        L0C = ( temp >> 2 ) & 0x01;
        L0B = ( temp >> 1 ) & 0x01;
        L0A = ( temp >> 0 ) & 0x01;							//ȡbit0��ֵ
        delay_us( 256 ); 													//ת�ٵ���    ��ʱС��2ms�����ת
    }
    Motor0Stop();																//һ������ת����������Ҫ��λ�����࣬�������һ�����������Ϊ�ߵ�ƽ������ά�ָߵ�ƽ��
}
//��ʱ��ת��
void Motor0CCW( void )
{
    u8 i;
    u8 temp;
    for( i = 0; i < 4; i++ )
    {
        temp = phase0ccw[i];

        L0D = ( temp >> 3 ) & 0x01;							//ȡbit4��ֵ
        L0C = ( temp >> 2 ) & 0x01;
        L0B = ( temp >> 1 ) & 0x01;
        L0A = ( temp >> 0 ) & 0x01;							//ȡbit0��ֵ

        delay_us( 256 ); //ת�ٵ���    ��ʱС��2ms�����ת
    }
    Motor0Stop();																//һ������ת����������Ҫ��λ�����࣬�������һ�����������Ϊ�ߵ�ƽ������ά�ָߵ�ƽ��
}
//ֹͣת��
void Motor0Stop( void )
{
    L0A = 0;
    L0B = 0;
    L0C = 0;
    L0D = 0;
}
void FanBlade( void )
{
			u16 cntC = 0;
			Motor0Stop();
			for(cntC=0;cntC<=101;cntC++)
			{
						Motor0CW();
			}
			Motor0Stop();
}
/*********************************************END OF FILE**********************/
