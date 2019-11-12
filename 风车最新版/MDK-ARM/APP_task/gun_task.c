/* ����ͷ�ļ�----------------------------------------------------------------*/
#include "gun_task.h"
#include "math.h"
#include "SystemState.h"
#include "user_lib.h"
/* �ڲ��궨��----------------------------------------------------------------*/

/* �ڲ��Զ�����������--------------------------------------------------------*/

/* ���������Ϣ����----------------------------------------------------------*/
//extern osMessageQId JSYS_QueueHandle;
/* �ڲ���������--------------------------------------------------------------*/
#define GUN_PERIOD  10
#define Mocha_PERIOD  1
#define BLOCK_TIME 5000
#define REVERSE_TIME 2000
#define prepare_flag HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_0)
#define READY    1
#define NO_READY 0
/* �ⲿ��������--------------------------------------------------------------*/
Heat_Gun_t  ptr_heat_gun_t;
extern uint8_t shot_frequency;
extern float Golf_speed;
//Power_Heat * power_heat;
/* �ⲿ����ԭ������-----------------------------------------------------------
float pid_calc(pid_t* pid, float get, float set);
void Friction_Wheel_Motor(uint32_t wheelone,uint32_t wheeltwo);
void Allocate_Motor(CAN_HandleTypeDef * hcan,int16_t value);
-----------------------------------------------------------------------------
-*/
/* �ڲ�����------------------------------------------------------------------*/

pid_t pid_dial_pos  = {0};  //���̵��λ�û�
pid_t pid_dial_spd  = {0};	//���̵���ٶȻ�
pid_t pid_shot_spd[2]  = {0};	//Ħ�����ٶȻ�
/* �ڲ�����ԭ������----------------------------------------------------------*/
void Gun_Pid_Init()
{
  /*�������*/
		PID_struct_init(&pid_dial_pos, POSITION_PID, 6000, 5000,
									0.7f,	0.0f,	1.8f);  
		//pid_dial_pos.deadband = 10;
		PID_struct_init(&pid_dial_spd, POSITION_PID, 6000, 5000,
									1.5f,	0.0f,	0.15f	);  
   /*Ħ����*/
  for(uint8_t i = 0;i<2;i++)
  {
    PID_struct_init(&pid_shot_spd[i], POSITION_PID, 6000, 5000,
									1.8f,	0.0f,	0.0f	); 
  }
}
/* �������岿�� -------------------------------------------------------------*/

/***************************************************************************************
**
	*	@brief	Gun_Task(void const * argument)
	*	@param
	*	@supplement	ǹ��������������
	*	@retval	
****************************************************************************************/
void Gun_Task(void const * argument)
{ 

	osDelay(100);
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	Gun_Pid_Init();
  /*�趨����*/
  uint8_t motor_stop_flag=0;
	static int32_t set_angle = 0;
	int32_t set_speed = 0;
  int32_t set_M_speed = 0;
	static uint8_t set_cnt = 0;
  static uint8_t block_flag;

  static uint8_t contiue_flag = 0;
	for(;;)
	{
		RefreshTaskOutLineTime(GunTask_ON);

 /*�жϷ���ģʽ*/
    switch(ptr_heat_gun_t.sht_flg)
    {
			case 0://ֹͣ58982
			{
        
        switch(contiue_flag)
        {
          case 0:
          {
            /*�趨�Ƕ�*/
            set_angle=moto_dial_get.total_angle;	
            contiue_flag = 1;
            /*Ħ�����ٶ�*/
            set_M_speed = 3000;
          }break;
          case 1:
          {
            goto position;
          }break;
        }
        
			}break;
      case 1://����ģʽ
      {
        /*�趨�Ƕ�*/
				moto_dial_get.cmd_time=GetSystemTimer();
				set_cnt=1;
				set_angle=58982*set_cnt;
        /*����*/
				moto_dial_get.round_cnt=0;
				moto_dial_get.offset_angle=moto_dial_get.angle;
				moto_dial_get.total_angle=0;	
        /*����λ�û�*/
        ptr_heat_gun_t.sht_flg = 11;
        contiue_flag = 0;
        /*Ħ�����ٶ�*/
        set_M_speed = 7000;
      }break;
      case 2://3����ģʽ
      {
				moto_dial_get.cmd_time=GetSystemTimer();
				set_cnt=3;
				set_angle=58982*set_cnt;
        /*����*/
				moto_dial_get.round_cnt=0;
				moto_dial_get.offset_angle=moto_dial_get.angle;
				moto_dial_get.total_angle=0;
        /*����λ�û�*/
        ptr_heat_gun_t.sht_flg = 11;
        /*������*/
        contiue_flag = 0;
      }break;
      case 11:
      {
        /*pidλ�û�*/
       position: pid_calc(&pid_dial_pos, moto_dial_get.total_angle,set_angle);	
				set_speed=pid_dial_pos.pos_out;
      }break;
      

			default :break;
    }
     /*�ٶȻ�*/
     pid_calc(&pid_dial_spd,moto_dial_get.speed_rpm ,set_speed);
     pid_calc(&pid_shot_spd[0],moto_M_get[0].speed_rpm ,set_M_speed);
     pid_calc(&pid_shot_spd[1],moto_M_get[1].speed_rpm ,-set_M_speed);
     /*�����������,Ħ����*/
		 Shot_Motor(&hcan2,pid_dial_spd.pos_out,pid_shot_spd[0].pos_out,pid_shot_spd[1].pos_out);
		 minipc_rx.state_flag=0;
		 set_speed=0;	   
    
        osDelayUntil(&xLastWakeTime,GUN_PERIOD);
	}
}


