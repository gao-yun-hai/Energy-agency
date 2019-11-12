#ifndef __gimbal_task_H
#define __gimbal_task_H
/* ����ͷ�ļ�----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "pid.h"
#include "communication.h "
#include "Motor_USE_CAN.h"
#include "chassis_task.h"
#include "atom_imu.h"
#include "decode.h"

/* ��ģ�����ⲿ�ṩ���������Ͷ���--------------------------------------------*/

typedef struct{
		//int16_t expect;
		float expect;
    float expect_last;
    float ture_value;
		uint8_t	step;
		uint8_t mode;
		int16_t expect_pc;
} Pos_Set;



/* ��ģ�����ⲿ�ṩ�ĺ궨��--------------------------------------------------*/

/* ��ģ�����ⲿ�ṩ�Ľӿڳ�������--------------------------------------------*/

extern Pos_Set  yaw_set;
extern Pos_Set  yaw_set_follow;
extern Pos_Set  pit_set;
extern int8_t gimbal_disable_flg;

/* ��ģ�����ⲿ�ṩ�Ľӿں���ԭ������----------------------------------------*/
void Gimbal_Task(void const * argument);

/* ȫ��������----------------------------------------------------------------*/

#endif
