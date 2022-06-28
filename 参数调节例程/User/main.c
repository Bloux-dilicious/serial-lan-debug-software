/*!
 *     COPYRIGHT NOTICE
 *
 *     除注明出处外，以下所有内容版权均属肖时有个人所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留肖时有的版权声明。
 *     Except where indicated, the copyright of all the contents below is owned by Xiao Shiyou
 *     and can not be used for commercial purposes without permission. 
 *     The copyright notice of  Xiao Shiyou must be preserved when modifying the content.
 *
 * @brief 参数调节功能主体由fifo文档与debug文档组成，fifo文档负责将数据暂存，debug负责数据处理。
 *        本例程通信方式为串口，基础流程为通过串口接收中断获取数据并将数据存入接收缓存区中，同时
 *        定时中断服务函数会在每次进入中断时读取接收缓存区中所有数据并处理，若发送缓存区中存在数据
 *        则发送。
 *
 * @file      main.c
 * @author    肖时有
 * @version   v1.2.3
 * @date      2022-05-01
 */

#include "main.h"
#include "debug.h"

//-----------------------待调试参数--------------------------//
float value = 100; //单参数

PID_t pid; //单环PID

PID_t angle_pid; //外环角度PID
PID_t gyro_pid; //内环角速度PID

fp32 TrackBarValue[3] = {8192.0f, 4000.0f, 0.0f}; //最大值，最小值，初始值


//-----------------------fifo队列--------------------------//
fifo_s_t fifo; //接收fifo缓存区
uint8_t fifo_buf[256];

int main( void )
{
	delay_init( 180 ); //延时函数初始化
	
	USART6_Configuration( 115200 ); //串口初始化
	Tick_TIM7_Init(); //定时中断初始化
	
	fifo_s_init(&fifo, fifo_buf, sizeof(fifo_buf)); //fifo接收队列初始化
	debug_init(); //调参初始化

	while (1)
	{	
		
	}
}


void TIM7_IRQHandler(void) //1ms中断
{
	if (TIM_GetITStatus( TIM7, TIM_IT_Update) == SET)
	{
		//定时调用调参处理函数
		debug_run(&fifo);
	}
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}


void USART6_IRQHandler(void)                        //串口6中断服务程序
{
		if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //接收中断
		{
			u8 Res =USART_ReceiveData(USART6);//(USART6->DR);        //读取接收到的数据
			
			//将待处理数据推入fifo队列
			fifo_s_put(&fifo, Res);			 
		} 
} 

//返回单参数value地址
float* value_point(void)
{
	return &value;
}

//返回单环pid首地址
PID_t* pid_point(void)
{
	return& pid;
}

//返回角度环pid首地址
PID_t* angle_pid_point(void)
{
	return& angle_pid;
}

//返回速度环pid首地址
PID_t* gyro_pid_point(void)
{
	return& gyro_pid;
}

//返回滑动调参首地址
float* trackBarValue_point(void)
{
	return TrackBarValue;
}
