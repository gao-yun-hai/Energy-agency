

#if BoardOld

旧板子：

-时钟          输入					PLLCK系数					输出					  
			   HSE   12MHz			M=12，N=336，P=2			SYSCLK					        168MHz
                                              APB1-peripheral clock	  42MHz
                                              APB1-timer clock		    84MHz
                                              APB2-peripheral clock 	84MHz
                                              APB2-timer clock		    168MHz

GPIO：
	引脚		功能/备注	
	PE3 		IST初始化
	PE2			IST重置
	PE1			外部上升中断  //官方自检程序中用于检查mpu的
	PG13		激光  
	PF6			SPI5NSS引脚   //SPI的剩余引脚SCK，MISO，MOSI引脚在spi初始化中定义的
	PF14		红灯
	PE7 		绿灯
	PD10		按键
    
	PH5			 ？？？？？
	PI0			定时器5通道4	

-串口：			-  引脚		  	功能/备注				         DMA_request        DMA-stream           波特率              	优先级

-USART1   -  PB9/PB7  UART1_TX/UART1_RX（遥控器）   USART1_RX        DMA2-Stream2          100000   				  (5，0)/dma对应相同
-USART2   -  PD5/PD6  UART2_TX/UART2_Rx(蓝牙) USART2_RX				 DMA1_Stream5					 115200
-USART3   -  PD9/PD8	UART3_TX/UART3_RX（串口）	    USART3_RX        DMA1-Stream1          115200					    NULL	
-UART4    -  PA0/PA1  UART4_TX/UART4_Rx（JY61）     UART4_RX         DMA1-Stream2          115200
-USART6   -  PG14/PG9	UART6_TX/UART6_RX（JY61）     USART6_RX				 DMA2-Stream1          115200				   	 (6,0) /
//-USRT8    -  PE1/PE0	UART8_TX/UART8_RX（JY61）	    UART8_RX				 DMA1_Stream6					 115200					    (6,0) /

-spi5：
	PF7     ------> SPI5_SCK
	PF9     ------> SPI5_MOSI
	PF8     ------> SPI5_MISO 


-定时器             引脚       		                 功能/备注  			  模式			         分频系数			   重载系数		  	   计数模式
  
  -TIM5	   	    -PH11/PH10		TIM5_CH2/TIM5_CH1  	摩擦轮电调         PWM输出模式             	83+1				1999+1			     UP
  
-CAN：
    PD0     ------> CAN1_RX																															(6,0)
    PD1     ------> CAN1_TX 																												
	
    PB12    ------> CAN2_RX																														  (6,0)
    PB13    ------> CAN2_TX 

  #endif
 /****************************************************************************************************************************************************************
 **************************************************************************line**********************************************************************************
 ****************************************************************************************************************************************************************/
#if BoardNew
新板子：  
  
  -时钟          输入					PLLCK系数					输出					                                         引脚
			   HSE 12MHz			M=12，N=336，P=2			SYSCLK					168MHz
																APB1-peripheral clock	42MHz
																APB1-timer clock		84MHz
																APB2-peripheral clock	84MHz
																APB2-timer clock		168MHz


-串口：			-	模块			            DMA_request       DMA-stream             波特率           RX/TX         

  -USART1       -   遥控器          USART1_RX         DMA2-Stream2             115200         PB7/PB6
  -USART3       -   串口            USART3_RX         DMA1-Stream1             115200         PD9/PD8
  -USART6       -   裁判系统        USART6_RX					DMA2-Stream1          	 115200         PG9/PG14
  -USRT8        -	JY61		          UART8_RX					DMA1_Stream6						 115200         PE0/PE1
  -USART2       -   与pc机通讯 		  USART2_RX					DMA1_Stream5						 115200					PD6/PD5
  
	         NSS/SCK/MISO/MOSI
-SPI       PF6/PF7/PF8/PF9                                                                                                                         


-定时器                             模式						  分频系数			    重载系数		    计数模式            CH1/CH2/CH3/CH4
  
  -TIM5	   	    -摩擦轮电调         PWM输出模式       839+1				    1999+1		           	UP              PH10/PH11/PH12/PI0
  
  
-CAN通讯                                            RX/TX            

-CAN1           -底盘电机           CAN正常模式     PD0/PD1
                                                                                                                     
-CAN2           -云台电机           CAN正常模式     PB12/PB13       


-LED
GREEN                   PF14          
RED                     PE11          
按键							    	PB2		
IST初始化					    	PE3 
IST重置						    	PE2																											
激光							    	PG13
定时器4通道2 //激光引脚	PD13

  #endif
  