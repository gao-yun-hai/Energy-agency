/*************************************************************************************
*	@file			bsp.h
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		NONE
*************************************************************************************/
#ifndef test_task_h
#define test_task_h

/* Includes ------------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "BSP.h"
/* Exported macro ------------------------------------------------------------*/
#define printf_sendware 1   //ʾ������ӡ
#define printf_speed    1   //�����ٶȴ�ӡ 
#define printf_power    0   //�����ٶȴ�ӡ 
/* Exported types --------------------------------------------------------*/
typedef struct 
{
	
 uint8_t ID;
 uint8_t state;
 uint8_t flag;       //�ж��Ƿ�������
 uint8_t on_off;     //�жϴ�ʱ������״̬
}LED;
/* Exported constants------------------------------------------------------------*/

/* Internal functions ------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/