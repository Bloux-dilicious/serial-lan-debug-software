/*!
 *     COPYRIGHT NOTICE
 *
 *     除注明出处外，以下所有内容版权均属肖时有个人所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留肖时有的版权声明。
 *     Except where indicated, the copyright of all the contents below is owned by Xiao Shiyou
 *     and can not be used for commercial purposes without permission. 
 *     The copyright notice of  Xiao Shiyou must be preserved when modifying the content.
 *
 * @brief  用户添加参数时，共有3步：
 *         1.按固定格式编写并添加功能函数
 *         2.将功能函数名添加至函数指针数组中(line43)
 *         3.按参数名添加至参数名数组中（line35），添加时需注意PARA_NUM 和 PARA_LEN 两个参数需符合要求
 *
 * @file      main.c
 * @author    肖时有
 * @version   v1.2.3
 * @date      2022-05-01
 */
#include "debug.h"
#include "usart6.h"
#include <stdlib.h>

//-----------------------功能函数初始化--------------------------//
void Load_Func(int name_index, float* data, int data_count, int waveshow);
void OneParam_Func(int name_index, float* data, int data_count, int waveshow);
void PID_Func(int name_index, float* data, int data_count, int waveshow);
void CascadePID_Func(int name_index, float* data, int data_count, int waveshow);
void TrackBar_Func(int name_index, float* data, int data_count, int waveshow);

//-----------------------具体参数--------------------------//
#define PARA_NUM 5 
#define PARA_LEN 12 //需比最长的参数名长度至少长 1 个字节

//参数名数组
const char Para_Name[PARA_NUM][PARA_LEN] = {
{"LOAD_START"},
{"OneParam"},
{"PID"},
{"CascadePID"},
{"TrackBar"}};

//函数指针数组
static void (*Para_Func[PARA_NUM])(int, float*, int, int) = 
{
	Load_Func,
	OneParam_Func,
	PID_Func,
	CascadePID_Func,
	TrackBar_Func
};



//-----------------------功能函数定义--------------------------//
/*-------------------------------------
 *@breif 参数加载函数
 *-------------------------------------
*/
uint8_t LOAD_START_ENABLE = 0;
uint8_t WAVE_SHOW_ENABLE = 0;
void Load_Func(int name_index, float* data, int data_count, int waveshow)
{
	LOAD_START_ENABLE = 1;
	WAVE_SHOW_ENABLE = 0;
}

/*-------------------------------------
 *@breif 单参数
 *-------------------------------------
*/
void OneParam_Func(int name_index, float* data, int data_count, int waveshow)
{
	//获取指针
	fp32* value = value_point();
	if(data != NULL && data_count == 1)
	{
		//if内可修改本地参数
		*value = data[0];
	}
	
	if(waveshow)
	{
		//添加波形显示数据 
		fp32 wave[1] = { *value }; 
		Add_FloatWaveData(wave, 1);
	}
	else
	{
		//添加回调参数
		fp32 param[1] = { *value };
		Add_ParamData(name_index, param, 1);
	}
}

/*-------------------------------------
 *@breif 单环PID
 *-------------------------------------
*/
void PID_Func(int name_index, float* data, int data_count, int waveshow)
{
	//获取指针
	PID_t* pid = pid_point();
	
	if(data != NULL && data_count == 5)
	{
		//if内可修改本地参数
		pid->Kp = data[0];
		pid->Ki = data[1];
		pid->Kd = data[2];
		pid->max_iout = data[3];
		pid->max_out = data[4];
	}
	
	if(waveshow)
	{
		//添加波形显示数据
		fp32 wave[3] = { pid->Kp, pid->Ki, pid->Kd };
		Add_FloatWaveData(wave, 3);
	}
	else
	{
		//添加回调参数
		fp32 param[5] = {pid->Kp , pid->Ki, pid->Kd, pid->max_iout, pid->max_out };
		Add_ParamData(name_index, param, 5);
	}
}

/*-------------------------------------
 *@breif 串级PID
 *-------------------------------------
*/
void CascadePID_Func(int name_index, float* data, int data_count, int waveshow)
{		
	//获取指针
	PID_t* gyro_pid = gyro_pid_point();
	PID_t* angle_pid = angle_pid_point();
	
	if(data != NULL && data_count == 10)
	{
		//if内可修改本地参数
		gyro_pid->Kp = data[0];
		gyro_pid->Ki = data[1];
		gyro_pid->Kd = data[2];
		gyro_pid->max_iout = data[3];
		gyro_pid->max_out = data[4];
		angle_pid->Kp = data[5];
		angle_pid->Ki = data[6];
		angle_pid->Kd = data[7];
		angle_pid->max_iout = data[8];
		angle_pid->max_out = data[9];
	}
	
	if(waveshow) 
	{
		//添加波形显示数据
		fp32 wave[2] = { gyro_pid->Kp, angle_pid->Kp };
		Add_FloatWaveData(wave, 2);
	}
	else 	
	{
		//添加参数回调数据
		fp32 param[10] = { gyro_pid->Kp , gyro_pid->Ki, gyro_pid->Kd, gyro_pid->max_iout, gyro_pid->max_out,
											 angle_pid->Kp , angle_pid->Ki, angle_pid->Kd, angle_pid->max_iout, angle_pid->max_out};
		Add_ParamData(name_index, param, 10);
	}
}

/*-------------------------------------
 *@breif 滑动调参
 *-------------------------------------
*/
void TrackBar_Func(int name_index, float* data, int data_count, int waveshow)
{
	float* barvalue = trackBarValue_point();
	if(data != NULL && data_count == 3)
	{
		//if内可修改本地参数
		barvalue[0] = data[0];
		barvalue[1] = data[1];
		barvalue[2] = data[2];
	}
	
	if(waveshow)
	{
		//添加波形显示数据
		Add_FloatWaveData(barvalue, 3);
	}
	else
	{
		Add_ParamData(name_index, barvalue, 3);
	}
}


//-----------------------------------------------------------//
//------------------------主体逻辑---------------------------//
//-----------------------------------------------------------//

//-----------------------参数初始化--------------------------//
fifo_s_t send_fifo; //发送队列
uint8_t send_buf[FIFOBUF_MAX]; //发送队列buff
Debug_t debug; //调试结构体

/*-------------------------------------
 *@breif 初始化
 *-------------------------------------
*/
void debug_init(void)
{
	fifo_s_init(&send_fifo, send_buf, FIFOBUF_MAX);
	debug.check_lenth = debug.data_lenth = debug.name_lenth = 0;
}

/*-------------------------------------
 *@breif 调参主函数
 *-------------------------------------
*/
void debug_run(fifo_s_t* fifo)
{
	//初始化加载参数
	if(LOAD_START_ENABLE)
	{
		 //10个线程周期添加一个参数
		static uint16_t load_time = 0;
		if(load_time++ % 10 == 0)
		{
			uint8_t index = load_time / 10 + 1;
			if(strlen(Para_Name[index]) != 0 && index < PARA_NUM)
			{
					(Para_Func[index])(index, NULL, 0, 0);
			}
			else
			{
				load_time = 0;
				LOAD_START_ENABLE = 0;
				Add_ParamData(0, NULL, 0); //发送标志位，结束参数导入
			}
		}
	}
	
	static uint16_t time = 0;
	if(time % AddWavePrescaler == 0 && WAVE_SHOW_ENABLE) //添加波形数据
			(Para_Func[WAVE_SHOW_ENABLE])(WAVE_SHOW_ENABLE, NULL, 0, 1); 
	
	if(time % 20 == 0) //20个周期解一次包	 
		UnPack(fifo);
	Send_FifoData(); //每个周期都发送数据
	time++;
}


/*-------------------------------------
 *@breif 协议解包
 *-------------------------------------
*/
uint8_t UnPack(fifo_s_t* fifo)
{
	uint8_t errorflag = 0; //错误标记位
	
	start:
	//帧头固定字节校验
	if(debug.check_lenth == 0)
	{
		uint8_t Byte;
		int lenth = fifo_s_used(fifo);
		while(lenth--)
		{
			Byte = fifo_s_get(fifo);
			if(Byte == FRAME_SOF)
			{
				debug.check_lenth ++;
				break;
			}
		}
	}
	//标识符检验
	if(debug.check_lenth == 1 && fifo_s_used(fifo) > 0)
	{
		if(fifo_s_get(fifo) == FRAME_PARAM_ID)
		{
			debug.check_lenth++;
		}
		else 
		{
			errorflag = 1;
			goto error;
		}
	}
	if(debug.check_lenth == 2 && fifo_s_used(fifo) >= 2)
	{
		debug.name_lenth = fifo_s_get(fifo);
		debug.data_lenth = fifo_s_get(fifo) * 4;
		debug.check_lenth += 2;
	}
	if(debug.check_lenth == 4 && fifo_s_used(fifo) > debug.name_lenth + debug.data_lenth)
	{
		char* name = (char*)calloc(debug.name_lenth + 1, 1); //+1使字符串末为0，保证stcmp功能正常
		fp32* data = (fp32*)malloc(debug.data_lenth);
		//内存分配失败
		if(name == NULL || data == NULL)
		{
			errorflag = 2;
			goto error;
		}
		fifo_s_gets(fifo, (char*)name, debug.name_lenth);
		fifo_s_gets(fifo, (char*)data, debug.data_lenth);
		//帧尾校验成功
		if(fifo_s_get(fifo) == FRAME_TAIL)
		{
			for(int i = 0; i < PARA_NUM; i++)
			{
				if(strcmp(name, Para_Name[i]) == 0)
				{
					//数据长度为0则显示波形
					if(debug.data_lenth == 0 && i != 0)
					{
						if(WAVE_SHOW_ENABLE == i)WAVE_SHOW_ENABLE = 0;
						else WAVE_SHOW_ENABLE = i;
					}
					else
					{
						//调参
						Para_Func[i](i, data, debug.data_lenth / 4, 0);
					}

					free(name);
					free(data);
					goto clear;
				}
			}
			free(name);
			free(data);
			errorflag = 3;
			goto error;
		}
		else 
		{
			free(name);
			free(data);
			errorflag = 4;
			goto error;
		}
	}
	
	error:
		if(errorflag)
		{
			//usart_printf("error %d \r\n", errorflag);
		}

	clear:
		debug.check_lenth = debug.data_lenth = debug.name_lenth = 0;	
		if(fifo_s_used(fifo) > 0)
			goto start;
		
		return errorflag;
}

/*-------------------------------------
 *@breif 添加参数数据到fifo
 *-------------------------------------
*/
void Add_ParamData(int row, fp32* num, int count)
{
	debug.param_header.sof = FRAME_SOF;
	debug.param_header.id = FRAME_PARAM_ID;
	debug.param_header.name_lenth = strlen(Para_Name[row]);
	debug.param_header.data_count = count;
	
	int Lenth = sizeof(Param_header_t) + debug.param_header.name_lenth + sizeof(fp32) * count + 1;
	uint8_t* data = (uint8_t*)malloc(Lenth);
	if(data == NULL) 
	{
		free(data);
		return;
	}
	memcpy(data, &(debug.param_header), sizeof(Param_header_t));
	memcpy(data + sizeof(Param_header_t), Para_Name[row], debug.param_header.name_lenth);
	memcpy(data + sizeof(Param_header_t) + debug.param_header.name_lenth, num, sizeof(fp32) * count);
	data[Lenth - 1] = FRAME_TAIL;
	
	fifo_s_puts(&send_fifo, (char*)data, Lenth);
	free(data);
}

/*-------------------------------------
 *@breif 添加浮点型波形数据到fifo
 *-------------------------------------
*/
void Add_FloatWaveData(fp32* num, int count)
{
	debug.wave_header.sof = FRAME_SOF;
	debug.wave_header.id = 0x0f;
	debug.wave_header.data_count = count;
	
	int Lenth = sizeof(Wave_header_t) + sizeof(fp32) * count + 1;
	uint8_t* data = (uint8_t*)malloc(Lenth);
	if(data == NULL) 
	{
		free(data);
		return;
	}
	memcpy(data, &(debug.wave_header), sizeof(Wave_header_t));
	memcpy(data + sizeof(Wave_header_t), num, sizeof(fp32) * count);
	data[Lenth - 1] = FRAME_TAIL;
	
	fifo_s_puts(&send_fifo, (char*)data, Lenth);
	free(data);
}


/*-------------------------------------
 *@breif 从fifo中取出单次最大数据并发送
 *-------------------------------------
*/
uint8_t SendBuff[SendByteMax];
void Send_FifoData(void)
{
	int remains = fifo_s_used(&send_fifo);
	if(remains >= SendByteMax) 
	{
		fifo_s_gets(&send_fifo, (char*)SendBuff, SendByteMax);
		//串口发送
		for(int i = 0; i < SendByteMax; i++)
		{
			USART6_SendChar(SendBuff[i]);
		}
	}
	else
	{
		fifo_s_gets(&send_fifo, (char*)SendBuff, remains);
		//串口发送
		for(int i = 0; i < remains; i++)
		{
			USART6_SendChar(SendBuff[i]);
		}
	}
}


