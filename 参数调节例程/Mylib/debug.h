#ifndef DEBUG_H
#define DEBUG_H

#include "main.h"
#include "fifo.h"

#define FIFOBUF_MAX 512 //发送fifo队列长度
#define ProgramPeriod 1 //debug程序运行周期 单位：ms

#define SendByteMax 10 //单次发送最大字节数。由波特率决定（115200波特率下1ms最大11.5个）保险起见少一点
#define AddWavePrescaler 10 //波形添加分频系数 需保证 SendByteMax * AddWavePrescaler * ProgramPeriod 大于单帧最大字节数。 当回调数据个数为8个时，字节长度为3+4*8+1=36字节

#define FRAME_SOF 0x28 //帧头
#define FRAME_TAIL 0x29  //帧尾
#define FRAME_PARAM_ID 0x10 

//---虚拟示波器------//
//| id    |  功能  |
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
 *@breif 初始化
 *-------------------------------------
*/
void debug_init(void);

/*-------------------------------------
 *@breif 调参主函数
 *-------------------------------------
*/
void debug_run(fifo_s_t* fifo);

/*-------------------------------------
 *@breif 协议解包
 *-------------------------------------
*/
uint8_t UnPack(fifo_s_t* fifo);

/*-------------------------------------
 *@breif 添加参数数据到fifo
 *-------------------------------------
*/
void Add_ParamData(int row, fp32* num, int count);

/*-------------------------------------
 *@breif 添加浮点型波形数据到fifo
 *-------------------------------------
*/
void Add_FloatWaveData(fp32* num, int count);

/*-------------------------------------
 *@breif 从fifo中取出单次最大数据并发送
 *-------------------------------------
*/
void Send_FifoData(void);



#endif
