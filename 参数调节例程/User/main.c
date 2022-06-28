/*!
 *     COPYRIGHT NOTICE
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Фʱ�и������У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Фʱ�еİ�Ȩ������
 *     Except where indicated, the copyright of all the contents below is owned by Xiao Shiyou
 *     and can not be used for commercial purposes without permission. 
 *     The copyright notice of  Xiao Shiyou must be preserved when modifying the content.
 *
 * @brief �������ڹ���������fifo�ĵ���debug�ĵ���ɣ�fifo�ĵ����������ݴ棬debug�������ݴ���
 *        ������ͨ�ŷ�ʽΪ���ڣ���������Ϊͨ�����ڽ����жϻ�ȡ���ݲ������ݴ�����ջ������У�ͬʱ
 *        ��ʱ�жϷ���������ÿ�ν����ж�ʱ��ȡ���ջ��������������ݲ����������ͻ������д�������
 *        ���͡�
 *
 * @file      main.c
 * @author    Фʱ��
 * @version   v1.2.3
 * @date      2022-05-01
 */

#include "main.h"
#include "debug.h"

//-----------------------�����Բ���--------------------------//
float value = 100; //������

PID_t pid; //����PID

PID_t angle_pid; //�⻷�Ƕ�PID
PID_t gyro_pid; //�ڻ����ٶ�PID

fp32 TrackBarValue[3] = {8192.0f, 4000.0f, 0.0f}; //���ֵ����Сֵ����ʼֵ


//-----------------------fifo����--------------------------//
fifo_s_t fifo; //����fifo������
uint8_t fifo_buf[256];

int main( void )
{
	delay_init( 180 ); //��ʱ������ʼ��
	
	USART6_Configuration( 115200 ); //���ڳ�ʼ��
	Tick_TIM7_Init(); //��ʱ�жϳ�ʼ��
	
	fifo_s_init(&fifo, fifo_buf, sizeof(fifo_buf)); //fifo���ն��г�ʼ��
	debug_init(); //���γ�ʼ��

	while (1)
	{	
		
	}
}


void TIM7_IRQHandler(void) //1ms�ж�
{
	if (TIM_GetITStatus( TIM7, TIM_IT_Update) == SET)
	{
		//��ʱ���õ��δ�����
		debug_run(&fifo);
	}
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}


void USART6_IRQHandler(void)                        //����6�жϷ������
{
		if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //�����ж�
		{
			u8 Res =USART_ReceiveData(USART6);//(USART6->DR);        //��ȡ���յ�������
			
			//����������������fifo����
			fifo_s_put(&fifo, Res);			 
		} 
} 

//���ص�����value��ַ
float* value_point(void)
{
	return &value;
}

//���ص���pid�׵�ַ
PID_t* pid_point(void)
{
	return& pid;
}

//���ؽǶȻ�pid�׵�ַ
PID_t* angle_pid_point(void)
{
	return& angle_pid;
}

//�����ٶȻ�pid�׵�ַ
PID_t* gyro_pid_point(void)
{
	return& gyro_pid;
}

//���ػ��������׵�ַ
float* trackBarValue_point(void)
{
	return TrackBarValue;
}
