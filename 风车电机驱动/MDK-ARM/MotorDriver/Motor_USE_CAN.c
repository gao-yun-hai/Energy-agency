/*******************************************************************************
*                     ��Ȩ���� (C), 2017-,NCUROBOT
********************************************************************************
* �� �� ��   : Motor_USE_CAN.c
* �� �� ��   : ����
* ��    ��   : NCURM
* ��������   : 2018��7��
* ����޸�   :
* ��������   : �����ģ����ʹ��CAN���п��Ƶĵ��
* �����б�   :
*ʹ��CANͨѶ�ĵ������̨���   		 ���̵��	 	 	  �������
*				 	��Ӧ�ͺţ� c620						3508					 C2000
*�ӿں�����
*					Cloud_Platform_Motor(CAN_HandleTypeDef * hcan,int16_t yaw,int16_t	pitch)
*					Chassis_Motor( CAN_HandleTypeDef * hcan,
*								  int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
*******************************************************************************/
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "Motor_USE_CAN.h"
#include "communication.h "
/* �ڲ��Զ����������� --------------------------------------------------------*/

/* �ڲ��궨�� ----------------------------------------------------------------*/

/* ���������Ϣ����-----------------------------------------------------------*/

/* �ڲ���������---------------------------------------------------------------*/

/* �ⲿ�������� --------------------------------------------------------------*/
/*******************Ħ���ֵ���͵��̵���Ĳ�������***************************/
moto_measure_t   moto_chassis_get[4] = {0};//4 �� 3508
moto_measure_t   moto_stir_get = {0};  //3508
moto_measure_t   moto_dial_get = {0};  //c2006
moto_measure_t   pit_get;
moto_measure_t   yaw_get;
/* �ⲿ����ԭ������ ----------------------------------------------------------*/

/* �ڲ����� ------------------------------------------------------------------*/
//Ϊcan���ͷֱ𴴽����棬��ֹ���ڷ��͵�ʱ����ֻ��һ���ڴ���໥����
static CAN_TxHeaderTypeDef  Cloud_Platform_Data;
static CAN_TxHeaderTypeDef  Allocate_Motor_Data;
static CAN_TxHeaderTypeDef  CANSend_DP;

static CAN_TxHeaderTypeDef	 Chassis_Motor_Header;
static CAN_TxHeaderTypeDef	 Stir_Motor_Header;
static CAN_TxHeaderTypeDef	 Gimbal_Motor_Header;

extern uint8_t rx_date[8];
uint8_t tx_date[8];
/* ����ԭ������ ----------------------------------------------------------*/
extern RC_Ctl_t RC_Ctl;
extern uint8_t chassis_gimble_Mode_flg;
int16_t yaw_speed;
uint8_t flag1;
int16_t OutLine_Flag;
int16_t task_OutLine_Flag;
int16_t R_key_v;
int16_t R_rc_ch0;
int16_t R_rc_ch1;
uint8_t R_rc_s1;
uint8_t R_rc_s2;
/**
	**************************************************************
	** Descriptions: ��̨�����������
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN1
	**					yaw:yaw�����ֵ
	**				pitch:pitch����ֵ
	** Output: NULL
	**************************************************************
**/
void Cloud_Platform_Motor(CAN_HandleTypeDef * hcan,int16_t yaw,int16_t	pitch)
{
      Gimbal_Motor_Header.DLC = 0x08;
			Gimbal_Motor_Header.IDE = CAN_ID_STD;
			Gimbal_Motor_Header.RTR = CAN_RTR_DATA;
			Gimbal_Motor_Header.StdId =  0x1FF;;

			tx_date[0] = yaw >> 8;
	    tx_date[1] = yaw;
	    tx_date[2] = pitch >> 8;
      tx_date[3] = pitch;
	    tx_date[4] = 0x00;
	    tx_date[5] = 0x00;
	    tx_date[6] = 0x00;
	    tx_date[7] = 0x00;
	
	
			HAL_CAN_AddTxMessage(hcan, &Gimbal_Motor_Header, tx_date, (uint32_t *)CAN_TX_MAILBOX0 );
}

/**
	**************************************************************
	** Descriptions: ��̨���У׼����
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN1
	**					
	**				
	** Output: NULL
	**************************************************************
**/
void Cloud_Platform_Motor_Correct(CAN_HandleTypeDef * hcan)
{
	
//		Cloud_Platform_Data.StdId = 0x3F0;
//		Cloud_Platform_Data.IDE = CAN_ID_STD;
//		Cloud_Platform_Data.RTR = CAN_RTR_DATA;
//		Cloud_Platform_Data.DLC = 0X08;
//		
//		Cloud_Platform_Data.Data[0] = 'c' ;
//		Cloud_Platform_Data.Data[1] = 0x00;
//		Cloud_Platform_Data.Data[2] = 0x00;
//		Cloud_Platform_Data.Data[3] = 0x00;
//		Cloud_Platform_Data.Data[4] = 0x00;
//		Cloud_Platform_Data.Data[5] = 0x00;
//		Cloud_Platform_Data.Data[6] = 0x00;
//		Cloud_Platform_Data.Data[7] = 0x00;

//  	hcan->pTxMsg = &Cloud_Platform_Data;
//		HAL_CAN_Transmit(hcan,10);
}

/**
	**************************************************************
	** Descriptions: ��̨���ʧ�ܺ���
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN1
	**					
	**				
	** Output: NULL
	**************************************************************
**/
void Cloud_Platform_Motor_Disable(CAN_HandleTypeDef * hcan)
{
	
//		Cloud_Platform_Data.StdId = 0x1FF;
//		Cloud_Platform_Data.IDE = CAN_ID_STD;
//		Cloud_Platform_Data.RTR = CAN_RTR_DATA;
//		Cloud_Platform_Data.DLC = 0X08;
//		
//		Cloud_Platform_Data.Data[0] = 0x00;
//		Cloud_Platform_Data.Data[1] = 0x00;
//		Cloud_Platform_Data.Data[2] = 0x00;
//		Cloud_Platform_Data.Data[3] = 0x00;
//		Cloud_Platform_Data.Data[4] = 0x00;
//		Cloud_Platform_Data.Data[5] = 0x00;
//		Cloud_Platform_Data.Data[6] = 0x00;
//		Cloud_Platform_Data.Data[7] = 0x00;

//  	hcan->pTxMsg = &Cloud_Platform_Data;
//		HAL_CAN_Transmit(hcan,10);
}

/**
	**************************************************************
	** Descriptions: ���̵����������
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN2
	**					iqn:��n�����̵���ĵ���ֵ
	** Output: NULL
	**************************************************************
**/


void Chassis_Motor( CAN_HandleTypeDef * hcan,int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{
			Chassis_Motor_Header.DLC = 0x08;
			Chassis_Motor_Header.IDE = CAN_ID_STD;
			Chassis_Motor_Header.RTR = CAN_RTR_DATA;
			Chassis_Motor_Header.StdId = 0x200;

			tx_date[0] = iq1>>8;
	    tx_date[1] = iq1;
	    tx_date[2] = iq2>>8;
      tx_date[3] = iq2;
	    tx_date[4] = iq3>>8;
	    tx_date[5] = iq3;
	    tx_date[6] = iq4>>8;
	    tx_date[7] = iq4;
	
	
			HAL_CAN_AddTxMessage(hcan, &Chassis_Motor_Header, tx_date, (uint32_t *)CAN_TX_MAILBOX0 );
}	

/**
	**************************************************************
	** Descriptions: ���̵��ʧ�ܺ���
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN2
	**					iqn:��n�����̵���ĵ���ֵ
	** Output: NULL
	**************************************************************
**/
void Chassis_Motor_Disable( CAN_HandleTypeDef * hcan)
{
      Chassis_Motor_Header.DLC = 0x08;
			Chassis_Motor_Header.IDE = CAN_ID_STD;
			Chassis_Motor_Header.RTR = CAN_RTR_DATA;
			Chassis_Motor_Header.StdId = 0x200;

			tx_date[0] = 0x00;
	    tx_date[1] = 0x00;
	    tx_date[2] = 0x00;
      tx_date[3] = 0x00;
	    tx_date[4] = 0x00;
	    tx_date[5] = 0x00;
	    tx_date[6] = 0x00;
	    tx_date[7] = 0x00;
	
	
			HAL_CAN_AddTxMessage(hcan, &Chassis_Motor_Header, tx_date, (uint32_t *)CAN_TX_MAILBOX0 );
}	

/**
	**************************************************************
	** Descriptions: ���������������
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN1
	**				value:��������ĵ���ֵ
	** Output: NULL
	**************************************************************
**/
void Allocate_Motor(CAN_HandleTypeDef * hcan,int16_t value)
{

//			Allocate_Motor_Data.DLC = 0x08;
//			Allocate_Motor_Data.IDE = CAN_ID_STD;
//			Allocate_Motor_Data.RTR = CAN_RTR_DATA;
//			Allocate_Motor_Data.StdId = 0x200;

//			Allocate_Motor_Data.Data[0]=value>>8;
//			Allocate_Motor_Data.Data[1]=value;
//			Allocate_Motor_Data.Data[2]=0;
//			Allocate_Motor_Data.Data[3]=0;
//			Allocate_Motor_Data.Data[4]=0;
//			Allocate_Motor_Data.Data[5]=0;
//			Allocate_Motor_Data.Data[6]=0;
//			Allocate_Motor_Data.Data[7]=0;
//	
//			hcan->pTxMsg = &Allocate_Motor_Data;
//			HAL_CAN_Transmit(hcan,0);
}
/**
	**************************************************************
	** Descriptions: ��������������
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN1
	**				value:�������ĵ���ֵ
	** Output: NULL
	**************************************************************
**/
void Stir_Motor(CAN_HandleTypeDef * hcan,int16_t value)
{

      Stir_Motor_Header.DLC = 0x08;
			Stir_Motor_Header.IDE = CAN_ID_STD;
			Stir_Motor_Header.RTR = CAN_RTR_DATA;
			Stir_Motor_Header.StdId = 0x200;

      tx_date[0] = 0x00;
	    tx_date[1] = 0x00;
	    tx_date[2] = value>>8;
      tx_date[3] = value;
	    tx_date[4] = 0x00;
	    tx_date[5] = 0x00;
	    tx_date[6] = 0x00;
	    tx_date[7] = 0x00;
	
	
			HAL_CAN_AddTxMessage(hcan, &Stir_Motor_Header, tx_date, (uint32_t *)CAN_TX_MAILBOX0 );
}
/**
	**************************************************************
	** Descriptions: ��������������
	** Input: 	
	**			   hcan:Ҫʹ�õ�CAN1
	**				value:�������ĵ���ֵ
	** Output: NULL
	**************************************************************
**/
void Stir_Motor_Disable(CAN_HandleTypeDef * hcan)
{

      Stir_Motor_Header.DLC = 0x08;
			Stir_Motor_Header.IDE = CAN_ID_STD;
			Stir_Motor_Header.RTR = CAN_RTR_DATA;
			Stir_Motor_Header.StdId = 0x200;

			tx_date[0] = 0x00;
	    tx_date[1] = 0x00;
	    tx_date[2] = 0x00;
      tx_date[3] = 0x00;
	    tx_date[4] = 0x00;
	    tx_date[5] = 0x00;
	    tx_date[6] = 0x00;
	    tx_date[7] = 0x00;
	
	
			HAL_CAN_AddTxMessage(hcan, &Stir_Motor_Header, tx_date, (uint32_t *)CAN_TX_MAILBOX0 );
}
/**                                                           //����
	**************************************************************
	** Descriptions: ��ȡCANͨѶ��6623����ķ���ֵ
	** Input: 	
	**			  ptr:Ŀ�����ݵ��ڴ��ַ
	**				hcan->pRxMsg->Data:���������CAN�����ݵ�����
	** Output: NULL
	**************************************************************
**/
void get_moto_measure_6623(moto_measure_t *ptr,CAN_HandleTypeDef * hcan)
{
	/*BUG!!! dont use this para code*/

//	ptr->last_angle = ptr->angle;
//	ptr->angle = (uint16_t)(hcan->pRxMsg->Data[0]<<8 | hcan->pRxMsg->Data[1]) ;
//	ptr->real_current  = (int16_t)(hcan->pRxMsg->Data[2]<<8 | hcan->pRxMsg->Data[3]);
//	ptr->given_current = (int16_t)(hcan->pRxMsg->Data[4]<<8 | hcan->pRxMsg->Data[5]);
//	ptr->speed_rpm = ptr->real_current;
////	ptr->hall = hcan->pRxMsg->Data[6];
//	
//	if(ptr->angle - ptr->last_angle > 4096)
//		ptr->round_cnt --;
//	else if (ptr->angle - ptr->last_angle < -4096)
//		ptr->round_cnt ++;
//	ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}
/**                                                           //����
	**************************************************************
	** Descriptions: ��ȡCANͨѶ��3508����ķ���ֵ
	** Input: 	
	**			  ptr:Ŀ�����ݵ��ڴ��ַ
	**				hcan->pRxMsg->Data:���������CAN�����ݵ�����
	** Output: NULL
	**************************************************************
**/
void get_moto_measure_3508(moto_measure_t *ptr,CAN_HandleTypeDef * hcan)
{
	/*BUG!!! dont use this para code*/

	ptr->last_angle = ptr->angle;
	ptr->angle = (uint16_t)(rx_date[0]<<8 | rx_date[1]) ;
	ptr->speed_rpm  = (int16_t)(rx_date[2]<<8 | rx_date[3]);
	ptr->real_current = (int16_t)(rx_date[4]<<8 | rx_date[5]);
	ptr->hall = rx_date[6];
	
	if(ptr->angle - ptr->last_angle > 4096)
		ptr->round_cnt --;
	else if (ptr->angle - ptr->last_angle < -4096)
		ptr->round_cnt ++;
	ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}
/**
	**************************************************************
	** Descriptions:��ȡ�������ֵ��ƫ��ֵ
	** Input: 	
	**			  ptr:Ŀ�����ݵ��ڴ��ַ
	**				hcan->pRxMsg->Data:���������CAN�����ݵ�����
	** Output: NULL
	**************************************************************
**/
/*this function should be called after system+can init */
void get_moto_offset(moto_measure_t *ptr,CAN_HandleTypeDef * hcan)
{
	ptr->angle = (uint16_t)(rx_date[0]<<8 |rx_date[1]) ;
	ptr->offset_angle = ptr->angle;
}

#define ABS(x)	( (x>0) ? (x) : (-x) )
/**
	**************************************************************
	** Descriptions: ��ȡ������ܽǶ�ֵ
	** Input: 	
	**			   *P:��Ҫ��ȡ�ܽǶ�ֵ�ĵ�ַ
	**				
	** Output: NULL
	**************************************************************
**/
void get_total_angle(moto_measure_t *p){
	
	int res1, res2, delta;
	if(p->angle < p->last_angle){			//?????
		res1 = p->angle + 8192 - p->last_angle;	//??,delta=+
		res2 = p->angle - p->last_angle;				//??	delta=-
	}else{	//angle > last
		res1 = p->angle - 8192 - p->last_angle ;//??	delta -
		res2 = p->angle - p->last_angle;				//??	delta +
	}
	if(ABS(res1)<ABS(res2))
		delta = res1;
	else
		delta = res2;

	p->total_angle += delta;
	p->last_angle = p->angle;
}

void CAN_RX_YT(CAN_HandleTypeDef * hcan)
{
	yaw_get.total_angle = (int16_t)(rx_date[0]<<8 |rx_date[1]) ;
	yaw_speed = (int16_t) (rx_date[2]<<8 | rx_date[3]) ;
	chassis_gimble_Mode_flg = (int16_t)(rx_date[4]<<8);
	flag1 = (int16_t)(rx_date[5]<<8);
	
}
void CAN_RX_YK(CAN_HandleTypeDef * hcan)
{
 RC_Ctl.key.v=(int16_t)(rx_date[0]<<8 |rx_date[1]) ;
 RC_Ctl.rc.ch0=(int16_t) (rx_date[2]<<8 |rx_date[3]) ;
 RC_Ctl.rc.ch1=(int16_t) (rx_date[4]<<8 |rx_date[5]) ;
 RC_Ctl.rc.s1=rx_date[6];
 RC_Ctl.rc.s2=rx_date[7];
	
}
	

void CAN_RX_ERROR(CAN_HandleTypeDef * hcan)
{
	OutLine_Flag = (int16_t)(rx_date[0]<<8 |rx_date[1]);
	task_OutLine_Flag = (int16_t) (rx_date[2]<<8 |rx_date[3]);
}

void CAN_SEND_DP( CAN_HandleTypeDef * hcan,int16_t speed_rpm1, int16_t speed_rpm2, 
	int16_t speed_rpm3, uint8_t speed_rpm4)
{
//	    CANSend_DP.DLC = 0x08;
//			CANSend_DP.IDE = CAN_ID_STD;
//			CANSend_DP.RTR = CAN_RTR_DATA;
//			CANSend_DP.StdId = 0x119;

//			CANSend_DP.Data[0]=OutLine_Flag>>8;
//			CANSend_DP.Data[1]=OutLine_Flag;
//			CANSend_DP.Data[2]=task_OutLine_Flag>>8;
//			CANSend_DP.Data[3]=task_OutLine_Flag;
//			CANSend_DP.Data[4]=0;
//			CANSend_DP.Data[5]=0;
//			CANSend_DP.Data[6]=0;
//			CANSend_DP.Data[7]=0;
//	
//			hcan->pTxMsg = &CANSend_DP;
//			HAL_CAN_Transmit(hcan,30);
}
