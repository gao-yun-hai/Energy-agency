/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/
//���жԿ��ļ��ĸ���ȫ������ͳһ�Ĺؼ���: _�Ŀ�
/* USER CODE BEGIN Includes */
#define BoardOld 				1	//1Ϊ�ɰ��ӣ�0Ϊ�°���
#define BoardNew				0

#define infantry 				0 	//������
#define engineer				0 	//���̳�
#define hero						1		//Ӣ�۳�

#define imu             1  //��̨���ݷ���
#define jy61            0

#define pritnf_JY61  	  0		//JY61�Ƿ�������
#define pritnf_Gimbal 	0		//��̨����Can�Ƿ�������
#define pritnf_Imu    	0   //imu�Ƿ�������
#define printf_Referee 	0		//����ϵͳ�Ƿ�������
#define printf_Chassis  0   //���̸���pid����


#define USE_FULL_ASSERT 		//���ԣ�������
#undef  USE_FULL_ASSERT

#undef configGENERATE_RUN_TIME_STATS			//ʱ��ͳ��  ������ص����ݹؼ��ʡ�ʱ��ͳ�ơ�

/* USER CODE END Includes */
#if infantry

#endif
#if engineer

#endif
#if	hero

#endif	
/* Private define ------------------------------------------------------------*/

extern void Error_Handler(void);

#define TIM5_CH2_Pin GPIO_PIN_11
#define TIM5_CH2_GPIO_Port GPIOH
#define TIM5_CH1_Pin GPIO_PIN_10
#define TIM5_CH1_GPIO_Port GPIOH
/* USER CODE BEGIN Private defines */
#define TIM12_CH2_Pin GPIO_PIN_9
#define TIM12_CH2_GPIO_Port GPIOH
#define TIM12_CH1_Pin GPIO_PIN_6
#define TIM12_CH1_GPIO_Port GPIOH
/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
