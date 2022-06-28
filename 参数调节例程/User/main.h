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

//���ص�����value��ַ
float* value_point(void);
//���ص���pid�׵�ַ
PID_t* pid_point(void);
//���ؽǶȻ�pid�׵�ַ
PID_t* angle_pid_point(void);
//�����ٶȻ�pid�׵�ַ
PID_t* gyro_pid_point(void);
//���ػ��������׵�ַ
float* trackBarValue_point(void);
#endif 
