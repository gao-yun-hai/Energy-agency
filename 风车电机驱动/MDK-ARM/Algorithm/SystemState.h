/*************************************************************************************
*	@file			SystemState.h
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		NONE
*************************************************************************************/
#ifndef __SysState_H__
#define __SysState_H__

/* Includes ------------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
/* Exported macro ------------------------------------------------------------*/
#define OutLine_Time 100 //���߼��ʱ��
#define Motor_Stall_Time 200
#define Motor_Stall_Spd 5

#define MyFlagSet(x,y) x=x|(0x00000001<<y) //���ñ�־λ  y�ڼ�λ
#define MyFlagClear(x,y) x=x&~(0x00000001<<y)
#define MyFlagGet(x,y) (x&(0x00000001<<y))
/* Exported types ------------------------------------------------------------*/
typedef struct{
	short Mode;//����ģʽ
	short Enable;//״̬
	short State;//״̬
	short Task;//����
//	BEEPMode Beep;//������
	int Time;//System run time mm
	TIM_HandleTypeDef *htim;//ʱ����������
	uint16_t OutLine_Flag;//���߱�־
	uint16_t task_OutLine_Flag;//���߱�־	
//	RobotDistDef RobotDist;//�����˲���
}SystemStateDef;

typedef enum
{
		Motor1_NO,
	  Motor2_NO,
		Motor3_NO,
		Motor4_NO,
    Remote_NO,
    MotorS_NO,
    
	
		DeviceTotal_No	
}DeviceX_NoDEF;

typedef enum
{
	testTask_ON,
	ChassisContrlTask_ON,
	RemoteDataTask_ON,
	GunTask_ON,
	vOutLineCheckTask_ON,
  RefereeTask_ON,
	
	TASKTotal_No	
}TASK_NoDEF;

/* Exported constants --------------------------------------------------------*/
extern SystemStateDef SystemState;
/* Internal functions ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
int SystemState_Inite(void);//SystemState��ʼ��
void RefreshSysTime(void);//ˢ��ϵͳʱ�䣨mm��
uint32_t GetSystemTimer(void);//��ȡϵͳ��ǰ׼ȷʱ��


void OutLine_Check(void);//���߼����
void TASK_Check(void);//������
void RefreshDeviceOutLineTime(DeviceX_NoDEF DevX_No);//ˢ������ͨ��ʱ��ʱ������
void RefreshTaskOutLineTime(TASK_NoDEF Task_No);


void vOutLineCheck_Task(void const *argument);

#endif
/************************ (H) COPYRIGHT STMicroelectronics *****END OF FILE****/

















