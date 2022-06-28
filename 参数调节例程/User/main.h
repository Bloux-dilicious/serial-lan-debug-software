#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"

#include "delay.h"
#include "usart6.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define abs(x) ((x)>0? (x):(-(x)))

typedef float fp32;

typedef struct
{
	 fp32 Kp;
   fp32 Ki;
   fp32 Kd;
   fp32 max_out;
   fp32 max_iout; 
}PID_t;

//返回单参数value地址
float* value_point(void);
//返回单环pid首地址
PID_t* pid_point(void);
//返回角度环pid首地址
PID_t* angle_pid_point(void);
//返回速度环pid首地址
PID_t* gyro_pid_point(void);
//返回滑动调参首地址
float* trackBarValue_point(void);
#endif 
