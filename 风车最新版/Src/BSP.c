/*************************************************************************************
*	@file			BSP.c
* @author	 	
*	@version 	V1.0
*	@date			
* @brief		NONE
*************************************************************************************//* Includes ------------------------------------------------------------------------*/
#include "BSP.h"
/* External variables --------------------------------------------------------------*/
volatile unsigned long long FreeRTOSRunTimeTicks;
/* Internal variables --------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/**
	**************************************************************
	** Descriptions:	�°��ӵ�Դ��ʼ��
	** Input:	huart  
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void Power_Init(void)
{
  #if BoardNew

  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, GPIO_PIN_SET);   //power1
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);   //power2
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, GPIO_PIN_SET);   //power3
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, GPIO_PIN_SET);   //power4

  #endif
	HAL_Delay(50);
}

/**
	**************************************************************
	** Descriptions:	JY61����/������
	** Input:	huart  ����ָ��Ĵ��ڣ�������Ҫ��Ϊ115200
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void JY61_SLEEPorUNSLEEP(UART_HandleTypeDef *huart)
{
	uint8_t buff[3] = {0xff,0xaa,0x60};
	//����,������
	HAL_UART_Transmit(huart,buff,3,10);
}

/**
	**************************************************************
	** Descriptions: JY61֡���뺯��
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
#if BoardNew
void JY61_Frame(void)
{
	static uint8_t JY61_Frame_flag = 0;
	static	uint8_t JY61_Frame_Num = 0;
	
while( UART8_RX_DATA[0] != 0x55 ||  JY61_Frame_flag == 1)
{
	
	if(UART8_RX_DATA[0] != 0x55 && JY61_Frame_flag == 0)
	{
				
				HAL_UART_DMAPause(&huart8);
				*UART8_RX_DATA = 0;
				JY61_Frame_flag = 1;
				
	}
	if(JY61_Frame_flag == 1)//����һ�Σ����������
	{
			JY61_Frame_Num++;
			
					if(JY61_Frame_Num == 25)
					 {
						 
//								JY61_SLEEPorUNSLEEP(&huart8);
//								JY61_Frame_flag = 0;
//								JY61_Frame_Num = 0;
							
								HAL_UART_Receive_DMA(&huart8,UART8_RX_DATA,SizeofJY61);	//�����ǽ���

				   } else if(JY61_Frame_Num == 50)
							 {
								   HAL_UART_DMAResume(&huart8);
							 } else if(JY61_Frame_Num > 100  )
									 {
										 JY61_Frame_flag = 0;
							       JY61_Frame_Num = 0;
									 }

	 }
}
	
}



/**
	**************************************************************
	** Descriptions:JY61��ʼ������
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void JY61_Init(void)
{
	uint8_t JY61[6][5] = {
													{0xff,0xaa,0x24,0x01,0x00},//�����㷨
													{0xff,0xaa,0x02,0x00,0x00},//�����Զ�У׼
													{0xff,0xaa,0x02,0x0c,0x00},//�ش�����:0x0c������ٶȺͽǶ�//0x08��ֻ����Ƕ�
													{0xff,0xaa,0x03,0x0b,0x00},//�ش�����:200hz
													{0xff,0xaa,0x00,0x00,0x00},//���浱ǰ����
													{0xff,0xaa,0x04,0x06,0x00}//���ô��ڲ�����:115200
												};
		
	HAL_UART_Transmit_DMA(&huart8,JY61[2],5);
	HAL_Delay(100);
	HAL_UART_Transmit_DMA(&huart8,JY61[3],5);
	HAL_Delay(100);
	HAL_UART_Transmit_DMA(&huart8,JY61[4],5);	
	HAL_Delay(100);
	if(HAL_UART_Transmit_DMA(&huart8,JY61[2],5) == HAL_OK )	
	{
		printf("JY61 Init \n\r");
	}
		if(HAL_UART_Transmit_DMA(&huart8,JY61[4],5) == HAL_OK)	
	{
		printf("JY61 Init save\n\r");
	}
}
#endif
void JY61_Frame(void)
{
	static uint8_t JY61_Frame_flag = 0;
	static	uint8_t JY61_Frame_Num = 0;
	
while( UART4_RX_DATA[0] != 0x55 ||  JY61_Frame_flag == 1)
{
	
	if(UART4_RX_DATA[0] != 0x55 && JY61_Frame_flag == 0)
	{
				
				HAL_UART_DMAPause(&huart4);
				*UART4_RX_DATA = 0;
				JY61_Frame_flag = 1;
				
	}
	if(JY61_Frame_flag == 1)//����һ�Σ����������
	{
			JY61_Frame_Num++;
			
					if(JY61_Frame_Num == 25)
					 {
						 
//								JY61_SLEEPorUNSLEEP(&huart4);
//								JY61_Frame_flag = 0;
//								JY61_Frame_Num = 0;
							
								HAL_UART_Receive_DMA(&huart4,UART4_RX_DATA,SizeofJY61);	//�����ǽ���

				   } else if(JY61_Frame_Num == 50)
							 {
								   HAL_UART_DMAResume(&huart4);
							 } else if(JY61_Frame_Num > 100  )
									 {
										 JY61_Frame_flag = 0;
							       JY61_Frame_Num = 0;
									 }

	 }
}
	
}



/**
	**************************************************************
	** Descriptions:JY61��ʼ������
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void JY61_Init(void)
{
	uint8_t JY61[6][5] = {
													{0xff,0xaa,0x24,0x01,0x00},//�����㷨
													{0xff,0xaa,0x02,0x00,0x00},//�����Զ�У׼
													{0xff,0xaa,0x02,0x0c,0x00},//�ش�����:0x0c������ٶȺͽǶ�//0x08��ֻ����Ƕ�
													{0xff,0xaa,0x03,0x0b,0x00},//�ش�����:200hz
													{0xff,0xaa,0x00,0x00,0x00},//���浱ǰ����
													{0xff,0xaa,0x04,0x06,0x00}//���ô��ڲ�����:115200
												};
		
	HAL_UART_Transmit_DMA(&huart4,JY61[2],5);
	HAL_Delay(100);
	HAL_UART_Transmit_DMA(&huart4,JY61[3],5);
	HAL_Delay(100);
	HAL_UART_Transmit_DMA(&huart4,JY61[4],5);	
	HAL_Delay(100);
	if(HAL_UART_Transmit_DMA(&huart4,JY61[2],5) == HAL_OK )	
	{
		printf("JY61 Init \n\r");
	}
		if(HAL_UART_Transmit_DMA(&huart4,JY61[4],5) == HAL_OK)	
	{
		printf("JY61 Init save\n\r");
	}
}
/**
	**************************************************************
	** Descriptions:ʱ��ͳ��
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void ConfigureTimerForRunTimeStats(void)  
{
	FreeRTOSRunTimeTicks = 0;
	MX_TIM3_Init(); //����50us��Ƶ��20K
}

/**
	**************************************************************
	** Descriptions:��ʼ��
	** Input: 	
  **						
	**					
	**					
	** Output: NULL
	**************************************************************
**/
void BSP_Init(void)
{
	
	/*���ź�����ʱ��*/
  MX_GPIO_Init();
	HAL_Delay(1000);
	Power_Init();
	/*dma*/
  MX_DMA_Init();
	/*can*/
	MX_CAN1_Init();
	MX_CAN2_Init();	
	CanFilter_Init(&hcan1);
	CanFilter_Init(&hcan2);
	/*��ʱ��*/
  MX_TIM5_Init();//Ħ����PWM��
  MX_TIM12_Init();//����ģ�鶨ʱ��
	MX_TIM6_Init();
	SystemState_Inite();
  /*ADC*/
	MX_ADC1_Init();
	/*����*/
  MX_USART1_UART_Init();
	MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();
  MX_USART6_UART_Init();
  MX_UART8_Init();
	/*SPI*/
	MX_SPI5_Init();

	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
//	__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
  __HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
  __HAL_UART_ENABLE_IT(&huart8, UART_IT_IDLE);
	
	/*ʹ��DMA�ж�*/
	HAL_UART_Receive_DMA(&huart1,USART1_RX_DATA,SizeofRemote); //��һ����Ŀ���Ǵ���һ�ν����ڴ棬��CAN��һ��
	HAL_UART_Receive_DMA(&huart2,USART2_RX_DATA,SizeofMinipc);
  HAL_UART_Receive_DMA(&huart4,UART4_RX_DATA,SizeofJY61);

/*����ADC��DMA���գ�ע�⻺�治��С��2����������Ϊ_IO�ͼ��ױ���*/
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)uhADCxConvertedValue, 10); 
	/*������*/
	 MPU6500_Init();
	/*Ħ����*/
//	GUN_Init();
	/*ʹ��can�ж�*/
  HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0); 
  HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);
	#if jy61
//	JY61_Frame();  
  #endif
	HAL_Delay(1000);

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/




