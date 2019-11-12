/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stm32f4xx.h"
#include "chassis_task.h"
#include "data_pro_task.h"
#include "gimbal_task.h"
#include "gun_task.h"
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
 osThreadId defaultTaskHandle;		  //= 0;
 osThreadId testTaskHandle; 				//= 0;
 osThreadId ChassisTaskHandle;		  //= 0;
 osThreadId RemoteDataTaskHandle;  //= 0;
 osThreadId RefereeDataTaskHandle; //= 0;
 osThreadId GimbalTaskHandle;		 	//= 0;
 osThreadId GunTaskHandle; 				//= 0;
 osThreadId MiniPCDataTaskHandle;
 osThreadId LedTaskHandle;
 osThreadId vOutLineCheckTaskHandle;
 osThreadId CheckTaskHandle;
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void  StartDefaultTask(void const * argument);
extern void testTask(void const * argument);
extern void Chassis_Contrl_Task(void const * argument);
extern void Remote_Data_Task(void const * argument);
extern void Referee_Data_Task(void const * argument);
extern void Gimbal_Contrl_Task(void const * argument);
extern void Gun_Task(void const * argument);
extern void MiniPC_Data_task(void const * argument);
extern void Led_Task(void const * argument);
//extern void vOutLineCheck_Task(void const *argument);
extern void Check_Task(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	osThreadDef(Task1, testTask, osPriorityNormal, 0, 256); //����ʾ������ʾ
	testTaskHandle = osThreadCreate(osThread(Task1), NULL);
	
	osThreadDef(RemoteDataTask, Remote_Data_Task, osPriorityHigh, 0, 256);
	RemoteDataTaskHandle = osThreadCreate(osThread(RemoteDataTask), NULL);
	
//	osThreadDef(RefereeDataTask, Referee_Data_Task, osPriorityAboveNormal, 0, 128);
//	RefereeDataTaskHandle = osThreadCreate(osThread(RefereeDataTask), NULL);

//	osThreadDef(MiniPCDataTask, MiniPC_Data_task, osPriorityAboveNormal, 0, 128);
//	MiniPCDataTaskHandle = osThreadCreate(osThread(MiniPCDataTask), NULL);

	osThreadDef(GimbalTask, Gimbal_Contrl_Task, osPriorityHigh, 0, 256);
	GimbalTaskHandle = osThreadCreate(osThread(GimbalTask), NULL);
	
//	osThreadDef(GunTask, Gun_Task, osPriorityNormal, 0, 128);
//	GunTaskHandle = osThreadCreate(osThread(GunTask), NULL);

//	osThreadDef(CheckTask, Check_Task, osPriorityNormal, 0, 128);
//	CheckTaskHandle = osThreadCreate(osThread(CheckTask), NULL);
	
//	osThreadDef(vOutLineCheckTask, vOutLineCheck_Task, osPriorityNormal, 0, 64);
//	vOutLineCheckTaskHandle = osThreadCreate(osThread(vOutLineCheckTask), NULL);

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
