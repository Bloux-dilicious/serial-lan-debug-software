#include "main.h"
#include <stm32f4xx.h> 
 

//初始化IO 串口6 
//bound:波特率
void USART6_Configuration(u32 bound){
		//GPIO端口设置
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE); //使能GPIOG时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART6时钟

		//串口6对应引脚复用映射
		GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_USART6); //GPIOA9复用为USART6
		GPIO_PinAFConfig(GPIOG,GPIO_PinSource14,GPIO_AF_USART6); //GPIOA10复用为USART6

		//USART6端口配置
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14; //GPIOG9与GPIOG14
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
		GPIO_Init(GPIOG,&GPIO_InitStructure); //初始化GPIOG9与GPIOG14

		//USART6 初始化设置
		USART_InitStructure.USART_BaudRate = bound;//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;        //收发模式
		USART_Init(USART6, &USART_InitStructure); //初始化串口6

		USART_Cmd(USART6, ENABLE);  //使能串口6 

		USART_ClearFlag(USART6, USART_FLAG_TC);

		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//开启相关中断

		//USART6 NVIC 配置
		NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//串口6中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;                //子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);        //根据指定的参数初始化VIC寄存器、
 
        
}

      

void USART6_SendChar(u8 ch)
{
  while((USART6->SR&0X40)==0);//循环发送,直到发送完毕   
			USART6->DR = (u8) ch;   
}

void usart6_printf(const char *fmt6,...)
{
    static uint8_t tx_buf6[256] = {0};
    static va_list ap6;
    static uint16_t len6;
    va_start(ap6, fmt6);

    //return length of string 
    //返回字符串长度
    len6 = vsprintf((char *)tx_buf6, fmt6, ap6);

    va_end(ap6);

		for(int i = 0; i < len6; i++)
		{
			USART6_SendChar(tx_buf6[i]);
		}
}

void Tick_TIM7_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  ///使能TIM7时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = 100; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=850 -1;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//初始化TIM7
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //允许定时器7更新中断
	TIM_Cmd(TIM7,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //定时器7中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
