#ifndef DEBUG_H
#define DEBUG_H

#include "main.h"
#include "fifo.h"

#define FIFOBUF_MAX 512 //����fifo���г���
#define ProgramPeriod 1 //debug������������ ��λ��ms

#define SendByteMax 10 //���η�������ֽ������ɲ����ʾ�����115200��������1ms���11.5�������������һ��
#define AddWavePrescaler 10 //������ӷ�Ƶϵ�� �豣֤ SendByteMax * AddWavePrescaler * ProgramPeriod ���ڵ�֡����ֽ����� ���ص����ݸ���Ϊ8��ʱ���ֽڳ���Ϊ3+4*8+1=36�ֽ�

#define FRAME_SOF 0x28 //֡ͷ
#define FRAME_TAIL 0x29  //֡β
#define FRAME_PARAM_ID 0x10 

//---����ʾ����------//
//| id    |  ����  |
//| :---: | :----: |
//| 0x01  | uint8  |
//| 0x09  |  int8  |
//| 0x02  | uint16 |
//| 0x0a  | int16  |
//| 0x04  | uint32 |
//| 0x0c  | int32  |
//| 0x0f  | float  |

typedef struct 
{
    uint8_t sof;
    uint8_t id;
    uint8_t data_count;
}Wave_header_t;


typedef struct 
{
	uint8_t sof;
	uint8_t id;
	uint8_t name_lenth;
	uint8_t data_count;
}Param_header_t;



typedef struct Debug_t
{
	Param_header_t param_header;
	Wave_header_t wave_header;

	int check_lenth;
	int name_lenth;
	int data_lenth;
}Debug_t;


/*-------------------------------------
 *@breif ��ʼ��
 *-------------------------------------
*/
void debug_init(void);

/*-------------------------------------
 *@breif ����������
 *-------------------------------------
*/
void debug_run(fifo_s_t* fifo);

/*-------------------------------------
 *@breif Э����
 *-------------------------------------
*/
uint8_t UnPack(fifo_s_t* fifo);

/*-------------------------------------
 *@breif ��Ӳ������ݵ�fifo
 *-------------------------------------
*/
void Add_ParamData(int row, fp32* num, int count);

/*-------------------------------------
 *@breif ��Ӹ����Ͳ������ݵ�fifo
 *-------------------------------------
*/
void Add_FloatWaveData(fp32* num, int count);

/*-------------------------------------
 *@breif ��fifo��ȡ������������ݲ�����
 *-------------------------------------
*/
void Send_FifoData(void);



#endif
