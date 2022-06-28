#ifndef __DELAY_H__
#define __DELAY_H__

void delay_init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_xms(u16 nms);
void delay_ms(u16 nms);

#endif 
