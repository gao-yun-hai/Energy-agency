/*************************************************************************************
*	@file			SystemState.c
* @author	 	   by  donglin   
*	@version 	V1.0
*	@date			
* @brief		NONE
*************************************************************************************//* Includes ------------------------------------------------------------------------*/
#include "SystemState.h"
#include "tim.h"
/* External variables --------------------------------------------------------------*/
/* Internal variables --------------------------------------------------------------*/
SystemStateDef SystemState={0};
float g_TimePer[100]={0};
float g_Time_DeviceOutLine[DeviceTotal_No]={0};//�������һ��ͨ��ʱ������
float g_Time_TASKOutLine[TASKTotal_No]={0};//�������һ��ͨ��ʱ������
/* Private function prototypes ---------------------------------------------------*/
//���߼����
void OutLine_Check()
{
	short num=0;//��ʱ�����ۼ���
	float time=GetSystemTimer();//��ǰϵͳʱ��

	for(num=0;num<DeviceTotal_No;num++)
	{
		if(time-g_Time_DeviceOutLine[num]>OutLine_Time)
		{
			MyFlagSet(SystemState.OutLine_Flag,(num));//���ö��߱�־
		}
		else
		{
			MyFlagClear(SystemState.OutLine_Flag,(num));//������߱�־
		}
	}
}

//���߼����
void TASK_Check()
{
	short num=0;//��ʱ�����ۼ���
	float time=GetSystemTimer();//��ǰϵͳʱ��

	for(num=0;num<TASKTotal_No;num++)
	{
		if(time-g_Time_TASKOutLine[num]>OutLine_Time)
		{
			MyFlagSet(SystemState.task_OutLine_Flag,(num));//���ö��߱�־
		}
		else
		{
			MyFlagClear(SystemState.task_OutLine_Flag,(num));//������߱�־
		}
	}
}


//=====================================================
//							  �ڲ�����
//
//====================================================


//���߼��
void vOutLineCheck_Task(void const *argument)
{

	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		RefreshTaskOutLineTime(vOutLineCheckTask_ON);
		
		
		TASK_Check();//������
		OutLine_Check();//���߼��
		osDelayUntil(&xLastWakeTime,20/ portTICK_RATE_MS);
		
	}
}



int SystemState_Inite()
{
	int state;
	SystemState.Enable=0;
	SystemState.State=0;
	SystemState.Task=0;
	SystemState.Time=0;
	SystemState.htim=&htim6;//��ʱ�����趨 ÿ 10us ��һ����  ����ֵΪ 100-1 (1ms)  ���� Timer3 ��Ƶ168M Ԥ��Ƶ (840-1) ����ֵ (100-1)
//	state=HAL_TIM_Base_Start_IT(SystemState.htim);//����ʱ�������
  return state;
}

//�ж�ˢ���е��� ����ϵͳʱ�� ms
 void RefreshSysTime(void)
{
		SystemState.Time+=1;
}


//���ϵͳʱ��
uint32_t GetSystemTimer()
{
	return HAL_GetTick();
}


//ˢ������ͨ��ʱ��ʱ������
void RefreshDeviceOutLineTime(DeviceX_NoDEF DevX_No)
{
	
	g_Time_DeviceOutLine[DevX_No]=GetSystemTimer();
	
}



//ˢ������ʱ������
void RefreshTaskOutLineTime(TASK_NoDEF Task_No)
{
	
	g_Time_TASKOutLine[Task_No]=GetSystemTimer();
	
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/








