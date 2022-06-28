#ifndef __USART6_H__
#define __USART6_H__ 
#include "main.h"
#define USART_REC_LEN  			8  	//�����������ֽ��� 200
#define EN_USART6_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����  
#define UART6_Waiting 0
#define UART6_Receiving 1
#define UART6_Success 2 
#define UART6_Failed  3

void USART6_Configuration(u32 bound);
void USART6_SendChar(u8 ch);
void usart6_printf(const char *fmt6,...);

void Tick_TIM7_Init (void);
#endif
