#ifndef __PIDWIRELESS_H
#define __PIDWIRELESS_H
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "pid.h"
#include "protocol.h"
#include "communication.h "



enum UART_State
{
	UART_Waiting = 0,
	UART_Receiving,
	UART_Success,
	UART_Failed,
};

/*
���ļ��ж����������ṹ�壬�ֱ�ΪPID_struct��MsgsFrame_struct��pid_t��
���е�һ���ṹ���������ڵڶ����ṹ���У���������ʱ�����ݴ���ֻ���ڵڶ����͵������ṹ���У�
���Զ���ṹ�����ʱֻ�ᶨ��ڶ������ṹ���������һ���ṹ���ڵڶ����ṹ���ж��塣



������ֻ�а�pid�ṹ�����ݴ��ݽ��������������֣�
��һ��������pid�ṹ��֮����и�ֵ�Ļ���
�ڶ��ǽ�Դ����Ľṹ��ĳɴ˵��εĽṹ��
�����ǽ��˵���pid�ṹ�廻��Դ�����pid�ṹ��
*/
#define SizeofPid  100
extern uint8_t  UsartRx_Info[SizeofPid];//���ߵ���
extern uint8_t  UsartTx_Info[SizeofPid];//���ߵ���



//pid�ṹ�壬һ���������ݣ���ȫ��Ϊ��MsgsFrame_struct�ṹ�����
typedef struct{
    unsigned char motor_ID;
    unsigned char PID_Mode;//����ʽ��1��λ��ʽ��0
    union{
        unsigned char tempChar[4];
        float tempFloat;
    }Kp_value;
    union{
        unsigned char tempChar[4];
        float tempFloat;
    }Ki_value;
    union{
        unsigned char tempChar[4];
        float tempFloat;
    }Kd_value;
    union{
        unsigned char tempChar[4];
        float tempFloat;
    }P_out_max;
    union{
        unsigned char tempChar[4];
        float tempFloat;
    }I_out_max;
    union{
        unsigned char tempChar[4];
        float tempFloat;  
    }D_out_max;
    union{
        unsigned char tempChar[4];
        float tempFloat;
    }PID_out_max;
} PID_struct;
//����������Ҫ���͵��������ݣ�����pid���ݺ�����ͨ��Э�顣
typedef struct{
    unsigned char SOF;
    unsigned char Data_Length;
    unsigned char seq;
    unsigned char crc8;
    unsigned char cmd_ID;
    PID_struct PID;
    union{
        unsigned char tempChar[2];
        int tempInt;
    }crc16;
}MsgsFrame_struct;


void PID_ParamsSet(MsgsFrame_struct *pidSet);
void PID_ParamsUpload(unsigned char motor_ID);
void PID_Regulator_Decode(void);
void PID_UART_IRQHandler(UART_HandleTypeDef * huart,uint8_t Res);

#endif
