
/*******************************************************************************
                      ��Ȩ���� (C), 2017-,NCUROBOT
 *******************************************************************************
  �� �� ��   : pidwireless.c
  �� �� ��   : ���԰�
  ��    ��   : xubiao
  ��������   : 2018��10��
  ����޸�   :
  ��������   : pid���ߵ���
  �����б�   :
							 
*******************************************************************************/

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "pidwireless.h"

/* �ڲ��Զ����������� --------------------------------------------------------*/

/* �ڲ��궨�� ----------------------------------------------------------------*/
#define ABS(x)		((x>0)? (x): (-x)) 
#define QUERY_CMD_ID 0X10
#define SET_CMD_ID 0X01
#define UPLOAD_PARAMS_CMD_ID 0x10
#define DATA_LENGTH_UPLOAD_PID_PATAMS 30
/* ���������Ϣ����-----------------------------------------------------------*/

/* �ڲ���������---------------------------------------------------------------*/
enum UART_State USART_state = UART_Waiting;		//����״̬���	

/* �ⲿ�������� --------------------------------------------------------------*/
pid_t * Motor_PID[20]={ &pid_3508_spd[0],    //Motor_PID[0]
												&pid_3508_spd[1],    //Motor_PID[1]
												&pid_3508_spd[2],    //Motor_PID[2]
												&pid_3508_spd[3],    //Motor_PID[3]
												&pid_3508_pos,       //Motor_PID[4]
												&pid_dial_spd,       //Motor_PID[5]
												&pid_dial_pos,       //Motor_PID[6]
												&pid_pit_jy61_spd,  //Motor_PID[7]
												&pid_yaw_jy61_spd,  //Motor_PID[8]
												&pid_pit,            //Motor_PID[9]
												&pid_yaw_jy61,      //Motor_PID[10]
												&pid_yaw,            //Motor_PID[11]
	                      &pid_yaw_jy61_spd,0,0,0,0,0,0,0,  //Motor_PID[12]
                       };
													
/* �ⲿ����ԭ������ ----------------------------------------------------------*/

/* �ڲ����� ------------------------------------------------------------------*/
uint8_t  UsartRx_Info[SizeofPid];//���ߵ���
uint8_t  UsartTx_Info[SizeofPid];//���ߵ���
int8_t USART_Rx_index = 0;       //������λ
int8_t USART_Tx_index = 0;
uint16_t rxLength = 8;					 //�������ݳ���
			 
MsgsFrame_struct PID_Regulator_Msg; //pid���ߵ��νṹ��


static uint8_t upload_flag = 0;

/* ����ԭ������ ----------------------------------------------------------*/

/**
	**************************************************************
	** Descriptions: pid������ֵ����
	** Input:  MsgsFrame_struct ���յ����ݽṹ��	
	** Output: NULL
	** Note: ��MsgsFrame_struct�ṹ�����ݾֲ��ĸ�ֵ��pid_t�ṹ�壬
	**       ���ѽ��յ���Ϣ��ֵ�����pid���������ݽ��յ�֮��ı���������á�
	**
	**************************************************************
**/
void PID_ParamsSet(MsgsFrame_struct *pidSet)
{
  
  	unsigned char index = pidSet->PID.motor_ID;
    Motor_PID[index]->pid_mode = pidSet->PID.PID_Mode;
	
    Motor_PID[index]->p = pidSet->PID.Kp_value.tempFloat;
    Motor_PID[index]->i = pidSet->PID.Ki_value.tempFloat;
    Motor_PID[index]->d = pidSet->PID.Kd_value.tempFloat;
    
    Motor_PID[index]->pout_max = pidSet->PID.P_out_max.tempFloat;
    Motor_PID[index]->iout_max = pidSet->PID.I_out_max.tempFloat;
    Motor_PID[index]->dout_max = pidSet->PID.D_out_max.tempFloat;
	
    Motor_PID[index]->MaxOutput = pidSet->PID.PID_out_max.tempFloat;
		
}

/**
	**************************************************************
	** Descriptions: pid�����ϴ�����
	** Input:  ���id�ţ�ʵ���Ͽ������ⶨ��õ�pid����	
	** Output: NULL
	** Note: ������ID�ţ�pid��Ӧ�ı�ţ�֮����ϴ�һЩpid���������pid�ṹ������ݸ�ֵ��
	**			 MsgsFrame_struct������ṹ���ڸ�ֵ����������UsartTx_Info��
	**			 ����������ǰ��pid�����ϴ�����λ��
	**************************************************************
**/
void PID_ParamsUpload(unsigned char motor_ID)
{

    unsigned char i=0,j=0;
    static unsigned char seq = 0;
    uint8_t usart_tx[100];
    uint8_t crc8;
    uint16_t crc16;
    MsgsFrame_struct tempMsgs;
    
    tempMsgs.SOF = 0xA5;
    tempMsgs.Data_Length = DATA_LENGTH_UPLOAD_PID_PATAMS;
    tempMsgs.seq = seq;
    seq++;
    //tempMsgs.crc8 = 0;//
    tempMsgs.cmd_ID = UPLOAD_PARAMS_CMD_ID;
    tempMsgs.PID.motor_ID = motor_ID;
  	tempMsgs.PID.PID_Mode = Motor_PID[motor_ID]->pid_mode;
		
    tempMsgs.PID.Kp_value.tempFloat = Motor_PID[motor_ID]->p;
    tempMsgs.PID.Ki_value.tempFloat = Motor_PID[motor_ID]->i;
    tempMsgs.PID.Kd_value.tempFloat = Motor_PID[motor_ID]->d;
		
    tempMsgs.PID.P_out_max.tempFloat = Motor_PID[motor_ID]->pout_max;//TODO
    tempMsgs.PID.I_out_max.tempFloat = Motor_PID[motor_ID]->iout_max;//TODO
    tempMsgs.PID.D_out_max.tempFloat = Motor_PID[motor_ID]->dout_max;//TODO
		
    tempMsgs.PID.PID_out_max.tempFloat = Motor_PID[motor_ID]->MaxOutput;
		
    usart_tx[i++] = tempMsgs.SOF;
    usart_tx[i++] = tempMsgs.Data_Length;
    usart_tx[i++] = tempMsgs.seq;
    crc8 = get_crc8_check_sum(usart_tx,i,0xff);
    usart_tx[i++] = crc8;
    usart_tx[i++] = tempMsgs.cmd_ID;
    usart_tx[i++] = tempMsgs.PID.motor_ID;
	  usart_tx[i++] = tempMsgs.PID.PID_Mode;
		
    for(j=0;j<4;j++) usart_tx[i++] = tempMsgs.PID.Kp_value.tempChar[j];
    for(j=0;j<4;j++) usart_tx[i++] = tempMsgs.PID.Ki_value.tempChar[j];
    for(j=0;j<4;j++) usart_tx[i++] = tempMsgs.PID.Kd_value.tempChar[j];
    for(j=0;j<4;j++) usart_tx[i++] = tempMsgs.PID.P_out_max.tempChar[j];
    for(j=0;j<4;j++) usart_tx[i++] = tempMsgs.PID.I_out_max.tempChar[j];
    for(j=0;j<4;j++) usart_tx[i++] = tempMsgs.PID.D_out_max.tempChar[j];
    for(j=0;j<4;j++) usart_tx[i++] = tempMsgs.PID.PID_out_max.tempChar[j];
    //����crc16У��
    crc16 = get_crc16_check_sum(usart_tx,i,0xffff);
    usart_tx[i++] = crc16&0xff;
    usart_tx[i++] = (crc16>>8)&0xff;    
    //���ͺ���
    HAL_UART_Transmit(&huart3, usart_tx, 37, 10);
}

/**
	**************************************************************
	** Descriptions: PID�������ղ���ֵ
	** Input:  NULL
	** Output: NULL
	** Note: �����ǽ����ڻ�����������ݽ��е��pid�����á�
	**			 ���������ݸ�ֵ��MsgsFrame_struct�������ٴ�MsgsFrame_struct
	**		   ���ú���PID_ParamsSet������ֵ�����pid
	**************************************************************
**/
void PID_Regulator_Decode(void)
{
    int i = 0,j=0;    
    PID_Regulator_Msg.SOF = UsartRx_Info[i++];
    PID_Regulator_Msg.Data_Length = UsartRx_Info[i++];
    PID_Regulator_Msg.seq = UsartRx_Info[i++];
    PID_Regulator_Msg.crc8 = UsartRx_Info[i++];
    PID_Regulator_Msg.cmd_ID = UsartRx_Info[i++];
    if ( PID_Regulator_Msg.cmd_ID == 0x00)//��λ��->��λ������ѯ����PID����
    {
        PID_Regulator_Msg.PID.motor_ID = UsartRx_Info[i++];
        
        for(j=0;j<2;j++) PID_Regulator_Msg.crc16.tempChar[j] = UsartRx_Info[i++];        
    }
    else if ( PID_Regulator_Msg.cmd_ID == 0x01)//��λ��->��λ����PID��������
    {
        PID_Regulator_Msg.PID.motor_ID = UsartRx_Info[i++];
        PID_Regulator_Msg.PID.PID_Mode = UsartRx_Info[i++];
        for(j=0;j<4;j++) PID_Regulator_Msg.PID.Kp_value.tempChar[j] = UsartRx_Info[i++];
        for(j=0;j<4;j++) PID_Regulator_Msg.PID.Ki_value.tempChar[j] = UsartRx_Info[i++];
        for(j=0;j<4;j++) PID_Regulator_Msg.PID.Kd_value.tempChar[j] = UsartRx_Info[i++];
        for(j=0;j<4;j++) PID_Regulator_Msg.PID.P_out_max.tempChar[j] = UsartRx_Info[i++];
        for(j=0;j<4;j++) PID_Regulator_Msg.PID.I_out_max.tempChar[j] = UsartRx_Info[i++];
        for(j=0;j<4;j++) PID_Regulator_Msg.PID.D_out_max.tempChar[j] = UsartRx_Info[i++];
        for(j=0;j<4;j++) PID_Regulator_Msg.PID.PID_out_max.tempChar[j] = UsartRx_Info[i++];
        
        for(j=0;j<2;j++) PID_Regulator_Msg.crc16.tempChar[j] = UsartRx_Info[i++];
        
        //������ֵ���洢����
        PID_ParamsSet(&PID_Regulator_Msg);        
    }    
}

/**
	**************************************************************
	** Descriptions: PID���ߵ��ε��жϴ�����
	** Input:  NULL
	** Output: NULL
	** Note:	������ڻص������з���ͳһ����
	**************************************************************
**/
void PID_UART_IRQHandler(UART_HandleTypeDef * huart,uint8_t Res)
{
	 if( (USART_state == UART_Waiting)&&(Res == 0xA5) ) 
      {	
          USART_state = UART_Receiving;
          USART_Rx_index = 0;          //��������ļ�����
          UsartRx_Info[USART_Rx_index] = Res;
          USART_Rx_index++;
      }
      else if( USART_state == UART_Receiving )
      {
          if( USART_Rx_index == 1 )//Data Length
          {
              UsartRx_Info[USART_Rx_index] = Res;
              USART_Rx_index++;
              rxLength = Res+7;
          }
      else if( USART_Rx_index == 2 )//Seq
          {
              UsartRx_Info[USART_Rx_index] = Res;
              USART_Rx_index++;
          }
      else if( USART_Rx_index == 3 )
          {
              UsartRx_Info[USART_Rx_index] = Res;
              USART_Rx_index++;
              if (  verify_crc8_check_sum(UsartRx_Info,4)) 
              {
               //������һ��
              }                  
              else //CRCУ��������µȴ���ȡ
              {	
                   rxLength = 8 ;
                   USART_Rx_index = 0;
                   USART_state = UART_Waiting;	
              }
          }
       else if (USART_Rx_index < rxLength)
          { 				
              UsartRx_Info[USART_Rx_index] = Res ;
              USART_Rx_index++;
              if (USART_Rx_index == rxLength) //������� ��������
              {               
                  //���Ƚ���crcУ��Ӧ��                   
                  if (verify_crc16_check_sum(UsartRx_Info, rxLength ))  
                  {	
                      PID_Regulator_Decode();
                      upload_flag = 1;
									 }                
                  rxLength = 8 ;
                  USART_Rx_index = 0;
                  USART_state = UART_Waiting;	                		   
              }
          }          
      }
			
			if(upload_flag)
			{
				HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7); //Red
				PID_ParamsUpload(PID_Regulator_Msg.PID.motor_ID);
				upload_flag=0;
			}
	
}

