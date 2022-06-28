/*!
 *     COPYRIGHT NOTICE
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Фʱ�и������У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Фʱ�еİ�Ȩ������
 *     Except where indicated, the copyright of all the contents below is owned by Xiao Shiyou
 *     and can not be used for commercial purposes without permission. 
 *     The copyright notice of  Xiao Shiyou must be preserved when modifying the content.
 *
 * @brief  �û���Ӳ���ʱ������3����
 *         1.���̶���ʽ��д����ӹ��ܺ���
 *         2.�����ܺ��������������ָ��������(line43)
 *         3.������������������������У�line35�������ʱ��ע��PARA_NUM �� PARA_LEN �������������Ҫ��
 *
 * @file      main.c
 * @author    Фʱ��
 * @version   v1.2.3
 * @date      2022-05-01
 */
#include "debug.h"
#include "usart6.h"
#include <stdlib.h>

//-----------------------���ܺ�����ʼ��--------------------------//
void Load_Func(int name_index, float* data, int data_count, int waveshow);
void OneParam_Func(int name_index, float* data, int data_count, int waveshow);
void PID_Func(int name_index, float* data, int data_count, int waveshow);
void CascadePID_Func(int name_index, float* data, int data_count, int waveshow);
void TrackBar_Func(int name_index, float* data, int data_count, int waveshow);

//-----------------------�������--------------------------//
#define PARA_NUM 5 
#define PARA_LEN 12 //�����Ĳ������������ٳ� 1 ���ֽ�

//����������
const char Para_Name[PARA_NUM][PARA_LEN] = {
{"LOAD_START"},
{"OneParam"},
{"PID"},
{"CascadePID"},
{"TrackBar"}};

//����ָ������
static void (*Para_Func[PARA_NUM])(int, float*, int, int) = 
{
	Load_Func,
	OneParam_Func,
	PID_Func,
	CascadePID_Func,
	TrackBar_Func
};



//-----------------------���ܺ�������--------------------------//
/*-------------------------------------
 *@breif �������غ���
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
 *@breif ������
 *-------------------------------------
*/
void OneParam_Func(int name_index, float* data, int data_count, int waveshow)
{
	//��ȡָ��
	fp32* value = value_point();
	if(data != NULL && data_count == 1)
	{
		//if�ڿ��޸ı��ز���
		*value = data[0];
	}
	
	if(waveshow)
	{
		//��Ӳ�����ʾ���� 
		fp32 wave[1] = { *value }; 
		Add_FloatWaveData(wave, 1);
	}
	else
	{
		//��ӻص�����
		fp32 param[1] = { *value };
		Add_ParamData(name_index, param, 1);
	}
}

/*-------------------------------------
 *@breif ����PID
 *-------------------------------------
*/
void PID_Func(int name_index, float* data, int data_count, int waveshow)
{
	//��ȡָ��
	PID_t* pid = pid_point();
	
	if(data != NULL && data_count == 5)
	{
		//if�ڿ��޸ı��ز���
		pid->Kp = data[0];
		pid->Ki = data[1];
		pid->Kd = data[2];
		pid->max_iout = data[3];
		pid->max_out = data[4];
	}
	
	if(waveshow)
	{
		//��Ӳ�����ʾ����
		fp32 wave[3] = { pid->Kp, pid->Ki, pid->Kd };
		Add_FloatWaveData(wave, 3);
	}
	else
	{
		//��ӻص�����
		fp32 param[5] = {pid->Kp , pid->Ki, pid->Kd, pid->max_iout, pid->max_out };
		Add_ParamData(name_index, param, 5);
	}
}

/*-------------------------------------
 *@breif ����PID
 *-------------------------------------
*/
void CascadePID_Func(int name_index, float* data, int data_count, int waveshow)
{		
	//��ȡָ��
	PID_t* gyro_pid = gyro_pid_point();
	PID_t* angle_pid = angle_pid_point();
	
	if(data != NULL && data_count == 10)
	{
		//if�ڿ��޸ı��ز���
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
		//��Ӳ�����ʾ����
		fp32 wave[2] = { gyro_pid->Kp, angle_pid->Kp };
		Add_FloatWaveData(wave, 2);
	}
	else 	
	{
		//��Ӳ����ص�����
		fp32 param[10] = { gyro_pid->Kp , gyro_pid->Ki, gyro_pid->Kd, gyro_pid->max_iout, gyro_pid->max_out,
											 angle_pid->Kp , angle_pid->Ki, angle_pid->Kd, angle_pid->max_iout, angle_pid->max_out};
		Add_ParamData(name_index, param, 10);
	}
}

/*-------------------------------------
 *@breif ��������
 *-------------------------------------
*/
void TrackBar_Func(int name_index, float* data, int data_count, int waveshow)
{
	float* barvalue = trackBarValue_point();
	if(data != NULL && data_count == 3)
	{
		//if�ڿ��޸ı��ز���
		barvalue[0] = data[0];
		barvalue[1] = data[1];
		barvalue[2] = data[2];
	}
	
	if(waveshow)
	{
		//��Ӳ�����ʾ����
		Add_FloatWaveData(barvalue, 3);
	}
	else
	{
		Add_ParamData(name_index, barvalue, 3);
	}
}


//-----------------------------------------------------------//
//------------------------�����߼�---------------------------//
//-----------------------------------------------------------//

//-----------------------������ʼ��--------------------------//
fifo_s_t send_fifo; //���Ͷ���
uint8_t send_buf[FIFOBUF_MAX]; //���Ͷ���buff
Debug_t debug; //���Խṹ��

/*-------------------------------------
 *@breif ��ʼ��
 *-------------------------------------
*/
void debug_init(void)
{
	fifo_s_init(&send_fifo, send_buf, FIFOBUF_MAX);
	debug.check_lenth = debug.data_lenth = debug.name_lenth = 0;
}

/*-------------------------------------
 *@breif ����������
 *-------------------------------------
*/
void debug_run(fifo_s_t* fifo)
{
	//��ʼ�����ز���
	if(LOAD_START_ENABLE)
	{
		 //10���߳��������һ������
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
				Add_ParamData(0, NULL, 0); //���ͱ�־λ��������������
			}
		}
	}
	
	static uint16_t time = 0;
	if(time % AddWavePrescaler == 0 && WAVE_SHOW_ENABLE) //��Ӳ�������
			(Para_Func[WAVE_SHOW_ENABLE])(WAVE_SHOW_ENABLE, NULL, 0, 1); 
	
	if(time % 20 == 0) //20�����ڽ�һ�ΰ�	 
		UnPack(fifo);
	Send_FifoData(); //ÿ�����ڶ���������
	time++;
}


/*-------------------------------------
 *@breif Э����
 *-------------------------------------
*/
uint8_t UnPack(fifo_s_t* fifo)
{
	uint8_t errorflag = 0; //������λ
	
	start:
	//֡ͷ�̶��ֽ�У��
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
	//��ʶ������
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
		char* name = (char*)calloc(debug.name_lenth + 1, 1); //+1ʹ�ַ���ĩΪ0����֤stcmp��������
		fp32* data = (fp32*)malloc(debug.data_lenth);
		//�ڴ����ʧ��
		if(name == NULL || data == NULL)
		{
			errorflag = 2;
			goto error;
		}
		fifo_s_gets(fifo, (char*)name, debug.name_lenth);
		fifo_s_gets(fifo, (char*)data, debug.data_lenth);
		//֡βУ��ɹ�
		if(fifo_s_get(fifo) == FRAME_TAIL)
		{
			for(int i = 0; i < PARA_NUM; i++)
			{
				if(strcmp(name, Para_Name[i]) == 0)
				{
					//���ݳ���Ϊ0����ʾ����
					if(debug.data_lenth == 0 && i != 0)
					{
						if(WAVE_SHOW_ENABLE == i)WAVE_SHOW_ENABLE = 0;
						else WAVE_SHOW_ENABLE = i;
					}
					else
					{
						//����
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
 *@breif ��Ӳ������ݵ�fifo
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
 *@breif ��Ӹ����Ͳ������ݵ�fifo
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
 *@breif ��fifo��ȡ������������ݲ�����
 *-------------------------------------
*/
uint8_t SendBuff[SendByteMax];
void Send_FifoData(void)
{
	int remains = fifo_s_used(&send_fifo);
	if(remains >= SendByteMax) 
	{
		fifo_s_gets(&send_fifo, (char*)SendBuff, SendByteMax);
		//���ڷ���
		for(int i = 0; i < SendByteMax; i++)
		{
			USART6_SendChar(SendBuff[i]);
		}
	}
	else
	{
		fifo_s_gets(&send_fifo, (char*)SendBuff, remains);
		//���ڷ���
		for(int i = 0; i < remains; i++)
		{
			USART6_SendChar(SendBuff[i]);
		}
	}
}


