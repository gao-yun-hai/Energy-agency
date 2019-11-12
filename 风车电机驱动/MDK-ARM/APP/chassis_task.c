/* ����ͷ�ļ�----------------------------------------------------------------*/
#include "chassis_task.h"
#include "SystemState.h"
/* �ڲ��궨��----------------------------------------------------------------*/

/* �ڲ��Զ�����������--------------------------------------------------------*/

/* ���������Ϣ����----------------------------------------------------------*/
//extern osMessageQId Chassis_QueueHandle;

/* �ڲ���������--------------------------------------------------------------
void Chassis_Motor( CAN_HandleTypeDef * hcan,
									  int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
float pid_calc(pid_t* pid, float get, float set);
void motor_move_setvmmps(float  wheel[4],float dstVmmps_X,
													float dstVmmps_Y,float dstVmmps_W);
----------------------------------------------------------------------------
*/
/* �ⲿ��������--------------------------------------------------------------*/
moto3508_type  moto_3508_set = {.flag = 0}; 
extern float power;		//����  	_���Ա���
int8_t chassis_disable_flg;
/* ���õ��ⲿ����ԭ������----------------------------------------------------------*/

/* �ڲ�����------------------------------------------------------------------*/
pid_t pid_3508_pos;     		 //���̵��λ�û�
pid_t pid_3508_spd[4];			 //���̵���ٶȻ�
pid_t pid_3508_current[4];	 //���̵����������	
pid_t pid_chassis_follow = {0};//���̸���λ�û�
pid_t pid_chassis_follow_spd = {0};//���̸����ٶȻ�

//int chiss_count;

static float Current_set[4] = {0};  //���ݸ��������ƵĻ���

//���Ա���
int16_t angle[2];

extern int16_t yaw_speed;
#define CHASSIS_PERIOD 5

/* �ڲ�����ԭ������----------------------------------------------------------*/
void Chassis_pid_init(void)
{
	
	 PID_struct_init(&pid_3508_pos, POSITION_PID, 10000, 1000,
									1.5f,	0.0f,	20.0f);  // motos angular rate closeloop.pid:1.5,0.0,20.0
	 pid_3508_pos.deadband=150;
	
	 PID_struct_init(&pid_chassis_follow, POSITION_PID,10000,1000,
	                4.0f, 0.01f , 20.0f  );
//	  pid_chassis_follow.deadband=10;
	 PID_struct_init(&pid_chassis_follow_spd, POSITION_PID,4000,1000,
	                0.8f, 0.0f , 0.0f  );
	
		for(int i=0; i<4; i++)
		{ 
			PID_struct_init(&pid_3508_spd[i], POSITION_PID, 10000, 2000,
										1.5f,	0.1f,	0.1f	);  //4 motos angular rate closeloop.
		}
}
/* �������岿�� -------------------------------------------------------------*/

/***************************************************************************************
**
	*	@brief	Chassis_Contrl_Task(void const * argument)
	*	@param
	*	@supplement	���̿�������
	*	@retval	
****************************************************************************************/
void Chassis_Contrl_Task(void const * argument)
{
  /*���ݳ�ʼ��*/
	static float  wheel[4]={0,0,0,0};
	osDelay(200);//��ʱ200ms
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  chassis_disable_flg=0;
  
  /*���ܳ�ʼ��*/
	Chassis_pid_init();
  
	for(;;)
	{

    RefreshTaskOutLineTime(ChassisContrlTask_ON);
    /*����ģʽ*/
//		switch(chassis_gimble_Mode_flg)
//		{	
//			case 0:	{	//����	
//        /*���ֽ���ó�wheel[4]*/
//			motor_move_setvmmps(wheel,moto_3508_set.dstVmmps_X,moto_3508_set.dstVmmps_Y,moto_3508_set.dstVmmps_W);
//			}break;
//      
//			case 1:	{	//���̸�����̨
//	  	/*��������ϣ�
//			*						 1. get:yaw_get.totalangle 
//			* 							set:0     			��Ϊһ��������̨������λ��������������totalangle����0��
//			*			  		 2. get:yaw_get.angle
//			*								set:ǹ����������ʱ�����̨����ֵ 
//			*/	
//        /*����λ�û�*/
//			pid_calc(&pid_chassis_follow,yaw_get.total_angle,0);
//        /*�����ٶȻ�*/ 
//			pid_calc(&pid_chassis_follow_spd,-yaw_speed,pid_chassis_follow.pos_out);
//		
//        /*���ֽ���ó�wheel[4]*/
//			motor_move_setvmmps(wheel,moto_3508_set.dstVmmps_X,moto_3508_set.dstVmmps_Y,pid_chassis_follow_spd.pos_out); 																																												
//			}break;
//		}
    /*�ٶȻ�����*/
//		for(int i=0; i<4; i++)
//			{		
//				//pid_calc(&pid_3508_spd[i], moto_chassis_get[i].speed_rpm, wheel[i]);
//        pid_calc(&pid_3508_spd[i], moto_chassis_get[i].speed_rpm, 600);
//			}
		
		/**********��������*********/

//			Current_set[0] = pid_3508_spd[0].pos_out;
//			Current_set[1] = pid_3508_spd[1].pos_out;
//			Current_set[2] = pid_3508_spd[2].pos_out;
//			Current_set[3] = pid_3508_spd[3].pos_out;			
			
//			printf("befeor:%f   ",Current_set[0]);
//		  power_limit(Current_set);
//			printf("after:%f\n\r",Current_set[0]);
			
//			pid_3508_spd[0].pos_out = Current_set[0];			
//			pid_3508_spd[1].pos_out = Current_set[1];
//			pid_3508_spd[2].pos_out = Current_set[2];
//			pid_3508_spd[3].pos_out = Current_set[3];

							
	  /************end***********/	
			
      /*�������*/
//      if(chassis_disable_flg==1)//ʧ��
//			{
//				  Chassis_Motor_Disable(&hcan2);
//			}
//			else
//			{
//					Chassis_Motor(&hcan2,
//												pid_3508_spd[0].pos_out,
//												pid_3508_spd[1].pos_out, 
//												pid_3508_spd[2].pos_out, 
//												pid_3508_spd[3].pos_out);

//      }        
//				
//			if(0){  //���ݷ��ͺ�������   _����
			//	if(HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_0) == 1)            //���ּ��  �͵�ƽ��������0Ϊ�ӵ���
																															 //                    ����1Ϊ������
			//	{
			//		data1 = 1;
			//	}
			//	else if(HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_0) == 0)
			//	{	
			//	data1 = 0;
			//	}
			//	sendata();
			//		
			//	
			//	
			//		if(data_pro_task_flag==1) { data_pro_task_flag=0;flag_counter=0;}				//������
			//		else flag_counter++;
			//		if(flag_counter>100)  { NVIC_SystemReset();}
			//		if(flag_counter>200)
			//			flag_counter = 0;
//				}
			
			
			Cloud_Platform_Motor(&hcan2,minipc_rx.yaw_out,minipc_rx.yaw_out);
//			Cloud_Platform_Motor(&hcan2,500,500);//������
//			chiss_count++;
			osDelay(5); 
  }
}


