/*************************************************************************************
*	@file			status_task.c
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		NONE
*************************************************************************************//* Includes ------------------------------------------------------------------------*/
#include "status_task.h"
/* External variables --------------------------------------------------------------*/
#define Check_PERIOD  100
#define BLINK_PERIOD  100
#define OFF_PERIOD    200
#define BLINK(); {LED8(1);osDelayUntil(&xLastWakeTime,BLINK_PERIOD);LED8(0);osDelayUntil(&xLastWakeTime,OFF_PERIOD);}
/* Internal variables --------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/**
	**************************************************************
	** Descriptions:Status_Task
	** Input: ����ģ������������������˸������������	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void Status_Task(void const * argument)
{
  osDelay(100);
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    if(!(SystemState.OutLine_Flag&0x01))//MOTOR1
      LED1_Blink();
    else LED1(0);
    
    if(!(SystemState.OutLine_Flag&0x02))//MOTOR2
      LED2_Blink();
    else LED2(0);
    
    if(!(SystemState.OutLine_Flag&0x04))//MOTOR3
      LED3_Blink();
    else LED3(0);
    
    if(!(SystemState.OutLine_Flag&0x08))//MOTOR4
      LED4_Blink();
    else LED4(0);
    
    if(!(SystemState.OutLine_Flag&0x10))//REMOTE
      LED5_Blink();
    else LED5(0);
    
    if(!(SystemState.OutLine_Flag&0x20))//MOTORS
      LED5_Blink();
    else LED6(0);
    
    osDelayUntil(&xLastWakeTime,300);
  }
}
/**
	**************************************************************
	** Descriptions:�Լ���������������������������˸����˸����Ϊ����������ID
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void Check_Task(void const * argument)
{
	osDelay(100);
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
    while(0)
    {
      OFF:LED8(0);
      osDelayUntil(&xLastWakeTime,2000);
    }
    if((SystemState.task_OutLine_Flag&0x01))//��������
    {
      BLINK();
      goto OFF;
    }
    else if((SystemState.task_OutLine_Flag&0x02))//��������
    {
      BLINK();
      BLINK();
      goto OFF;
    }
    else if((SystemState.task_OutLine_Flag&0x04))//ͨ������
    {
      BLINK();
      BLINK();
      BLINK();
      goto OFF;
    }
    else if((SystemState.task_OutLine_Flag&0x08))//��������
    {
      BLINK();
      BLINK();
      BLINK();
      BLINK();
      goto OFF;
    }
    else if((SystemState.task_OutLine_Flag&0x10))//��������
    {
      BLINK();
      BLINK();
      BLINK();
      BLINK();
      BLINK();
      goto OFF;
    }
    else if((SystemState.task_OutLine_Flag&0x20))//��������
    {
      BLINK();
      BLINK();
      BLINK();
      BLINK();
      BLINK();
      BLINK();
      goto OFF;
    }
    else 
    {
      LED8(1);
      osDelayUntil(&xLastWakeTime,20);
    }
    
  }
	
	
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/