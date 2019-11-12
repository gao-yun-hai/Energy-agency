/*******************************************************************************
                      ��Ȩ���� (C), 2017-,NCUROBOT
 *******************************************************************************
  �� �� ��   : Power_restriction.c
  �� �� ��   : ����
  ��    ��   : NCUERM
  ��������   : 2018��7��
  ����޸�   :
  ��������   : ���̹�������
  �����б�   :void power_limit(float  Current_get[4])


*******************************************************************************/
/*
* ��ѹ������������Ĺ�ϵ:
*			VOUT = VOUT(Q) + Vsens*I;
*	VOUT(Q)Ϊ��̬�����ѹ����VCC/2��Ҳ����������ʱ������ĵ�ѹ��Vsens�Ǵ�����������
*��ʹ�õ��ͺŵ�ϵ����40MV/A��I�ķ����Ǵ�IP+����IP-�ĵ���
*	eg:
*			VCCΪ5V��I����Ϊ10A����ô�����Ϊ5V / 2 + 40MV/A * 10A = 2.9V
*			VCCΪ3.3V��I����Ϊ10A����ô�����Ϊ3.3V / 2 + 40MV/A*10A = 2.05V
* �����
*			I = (VOUT - VOUT(Q))/Vsens
*			I = (V_get - 2.5)/0.04; 	  //��5V��ѹ
*			I = (V_get - 1.65)/0.04;		//��3.3V��ѹ
*/
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "Power_restriction.h"
/* �ڲ��Զ����������� --------------------------------------------------------*/

/* �ڲ��궨�� ----------------------------------------------------------------*/
#define MyAbs(x) ((x > 0) ? (x) : (-x))
#define VAL_LIMIT(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\
/* ���������Ϣ����-----------------------------------------------------------*/

/* �ڲ���������---------------------------------------------------------------*/

/* �ⲿ�������� --------------------------------------------------------------*/

/* �ⲿ����ԭ������ ----------------------------------------------------------*/

/* �ڲ����� ------------------------------------------------------------------*/
/*
*
*	����˵��:ADC�������� , ����ϵ��0.8058608{3300/4095}
*  			  �õ�ʵ�ʵ�ѹֵ
*	����ʱ��:�ɼ�һ�����ݵ�ʱ����(ת������+��������)/ʱ��(12λ�ɼ���15������)
*				  �������õĲ���ʱ����(12+3)/(84/4)M = 0.7142us
*	   Note:ʵ�ʵ������ݵļ����С5ms�����Դ���һ������Ϊ10�����飬ÿ��ʹ�����ݵ�ʱ��
*		   		��10������ȡƽ��ֵ��Ȼ���ٴ���һ��10λ������洢��ʷ���ݣ����д��ڻ�����
*					�� (��Ϊ���ڻ�û��Ӳ����ƣ���ʱ�����ַ������˲�),������Чʱ���ӳ���0.7ms
*/
uint32_t  uhADCxConvertedValue[10] = {0};  
Limit  limit = {.PowerRemain_Calculat = 60};
Current_GET  current_get = {0};
MyTimeTick  time_for_limit = {0}; //����ʱ���ʱ
MyTimeTick  time_for_RP = {0};  //remain power �������������ʱ
//���Ա���

/* ����ԭ������ ----------------------------------------------------------*/


/*
** Descriptions: ����������ֵ
** Input: ��Ҫ��������������float��
** Output: NULL
*/
void swap(float *a,float *b)
{
 float c;
 c=*a;*a=*b;*b=c;
}
/*
** Descriptions: ������ֳ������֣�ǰһ���ֵ�ֵ���Ⱥ�һ����ֵС
** Input: Ҫ������ݵĿ�ͷ��ĩβ
** Output: ���طֽ��
*/
int Partition(float data[],int low,int high)
{
 float pivokey;
 pivokey=data[low];
 while(low<high)
 {
  while(low<high&&data[high]>=pivokey)
   high--;
  swap(&data[low],&data[high]);

  while(low<high&&data[low]<=pivokey)
   low++;
  swap(&data[low],&data[high]);
 }
 return low;
}
/*
** Descriptions: ���еĵݹ�ĵ��ã��ﵽ�����Ŀ��
** Input: ��Ҫ�������������ָ�룬�Լ���Ӧ�ķ�Χ
** Output: NULL
*/
void QSort(float data[],int low,int high)
{
 if(low<high)
 {
  int pivokey=Partition(data,low,high);
  QSort(data,low,pivokey-1);
  QSort(data,pivokey+1,high);
 }
}
/*
** Descriptions: ��û������ֵ
** Input:��Ӧ�Ļ���ָ�룬��������鳤����ҪΪ10
** Output:��ֵ
*/
float Median_value_fliter(uint32_t *buff,int length)
{	
	uint32_t mybuff[length];
	memcpy(mybuff,buff,length);
	QSort((float*)mybuff, 0, length-1);
	return buff[(int)((length-1)/2)];
}
/*
** Descriptions: ��ֵƽ���˲�
** Input:��Ӧ�Ļ���ָ�룬��������鳤����ҪΪ10
** Output:��ȥ�����Сֵ��ƽ��ֵ
*/
float Median_average_fliter(uint32_t *buff,int length)
{
	int16_t sum = 0;
	uint32_t mybuff[length];
	memcpy(mybuff,buff,length);
	QSort((float*)mybuff, 0, length-1);
	for(uint8_t i = 1;i < length-1;i++)
	{
		sum += mybuff[i];
	}
	sum = sum/(length-2);
	return sum;
}
/*
** Descriptions: ��ֵ�˲�
** Input: ��Ҫ�˲��Ļ����ָ��
** Output: �˲����
*/
float Average_value_fliter(uint32_t *buff)
{
	float sum = 0;
	uint32_t mybuff[10];
	memcpy(mybuff,buff,10);
	for(uint8_t i = 0;i < 10;i++ )
	{
		sum += mybuff[i];
	}
	sum *= 0.1f;
	return sum;
}
/*
** Descriptions: ���ڻ����˲�
** Input: ��Ҫ�˲��Ļ����ָ��
** Output: �˲����
*/
float Window_sliding_filter(float *buff)
{
	float sum = 0;
	for(uint8_t i = 0; i < 10; i++) {
	buff[i] = buff[i+1]; // �����������ƣ���λ�Ե�
	sum += buff[i];
  }
	
	return sum;
}

/*
** Descriptions: һ�׵�ͨ�˲�
** Input: 
** Output: �˲����
*/
float LPF_1st(float oldData, float newData, float lpf_factor)
{
	return oldData * (1 - lpf_factor) + newData * lpf_factor;
}

/*
** Descriptions: �޷��˲�
** Input:   ���ڵ���������
** Output: �˲����
*/
float Limit_filter(float oldData,float newData,float val)
{
	if(abs(newData-oldData)>val)
		{
			return oldData;
		}
	else
		{
			return newData;
		}
}

/*
** Descriptions: ���Բ�������ʱ��(s)
** Input: ʱ��ṹ���ָ��
** Output: NULL
*/
void	MyTime_statistics(MyTimeTick *time_tick)
{

	time_tick->time_now = HAL_GetTick();
	if(time_tick->time_last == 0)//�����һ�μ�����ʱ��lastΪ��
	{
		time_tick->time = time_tick->time_now - time_tick->time_now;
	}else
	{
		time_tick->time = time_tick->time_now - time_tick->time_last;		
	}
	time_tick->time_last = time_tick->time_now;
	//�м�������ʱ��
	time_tick->total_time_ms += time_tick->time;
	time_tick->total_time_s = time_tick->total_time_ms * 0.001f;
}
/*
** Descriptions: ���ʱ��ṹ��
** Input: 
**				MyTimeTick *: 		ʱ��ṹ���ָ��
**				flag:  ѡ����յ�����
**								flag = 1  ���ȫ��
**								flag = 2	�����ʱ��(��ֹ��������ʱ�ļ�ʱ�������)
** Output: NULL
*/
void MyTime_memset(MyTimeTick *time_tick ,char flag)
{
	if(flag == 1)
	{
		memset(time_tick,0,sizeof(MyTimeTick));
	}else if(flag == 2)
	{
		time_tick->total_time_ms = 0;
		time_tick->total_time_s = 0;
	}
	
}

/*
** Descriptions: ADC���ݲɼ����˲�
** Input: NULL
** Output: ���ݲɼ�ֵ
*/
void Get_ADC_Value(void)
{
		uint32_t *buff = uhADCxConvertedValue;
		//��һ���˲�Ҫ�ر�ADC��dma
		int getbuff = 0;
		for(uint8_t i = 0;i < 10;i++)
		{
			getbuff += buff[i];
		}
		/*current_get.CurrentBuff1_get =  Median_value_fliter(buff,10);
			current_get.CurrentBuff1_get =  Median_average_fliter(buff,10);*/
		current_get.CurrentBuff1_get =  getbuff * 0.1f;
		current_get.CurrentBuff2_fliter[10] = current_get.CurrentBuff1_get;
		current_get.CurrentBuff2_get = Window_sliding_filter(current_get.CurrentBuff2_fliter)*0.1f;
	
		if(current_get.Current_Offset_num > 200)
		{
			
			current_get.CurrentCalculat = (current_get.CurrentBuff2_get * (0.00080566f) - 2.50f) * 25.0f -
																		 current_get.Current_Offset;
		}
		else
		{
			current_get.Current_Offset_num++;
			current_get.CurrentCalculat = (current_get.CurrentBuff2_get * (0.00080566f) - 2.50f) * 25.0f;
			
			if(current_get.Current_Offset_num > 50)
			{		
				current_get.Current_Offset += current_get.CurrentCalculat - current_get.Current_Referee;
			}
			if(current_get.Current_Offset_num > 200)
			{				
				current_get.Current_Offset = current_get.Current_Offset/150.0f;
			}
		}

}

/*
** Descriptions: ������������
** Input: NULL
** Output: NULL
*/

void Remain_Power_Calculate(void)
{
		/*�ɼ�ʱ��*/
		MyTime_statistics(&time_for_RP);
	
		/*�����������*/
		if(limit.Power_Calculat >80)
		{
			limit.PowerRemain_Calculat -= (limit.Power_Calculat - 80) * time_for_RP.time * 0.01f;
		}
		if(limit.Power_Calculat <80)
		{
			limit.PowerRemain_Calculat = 60-(limit.Power_Calculat - 80) * time_for_RP.time * 0.01f;
		}
		
		/*�����ʱ��*/
		MyTime_memset(&time_for_RP,2);		
		
		/*�ָ���������*/
		VAL_LIMIT(limit.PowerRemain_Calculat, 0.0f, 60.0f);

}

/*
** Descriptions: ��������
** Input: NULL
** Output: ��������ֵ
*/

/*
*	��γ�����ò���ϵͳ���صĹ��ʺ���������
*
*/
void power_limit(float  Current_get[4])
{
		
		float total_current = 0;
		float T0 = 0;
		float P0 = 0;
		float RE = 0;
		float V0 = 0;
		total_current = MyAbs(Current_get[0]) + MyAbs(Current_get[1])+\
										MyAbs(Current_get[2]) + MyAbs(Current_get[3]);
		
		/*�����ɼ�*/
		Get_ADC_Value();

		/*���ʼ���*/
		if(limit.Volt_Referee != 0)//��ֹ����ϵͳʧЧ
		{
			limit.Power_Calculat = current_get.CurrentCalculat * limit.Volt_Referee;

		}else
		{
			limit.Power_Calculat = current_get.CurrentCalculat * 23.0f;		

		}
		
		/*�����������*/
		Remain_Power_Calculate();
		
		/*��������*/

	
//			printf("\n power:%4f .\n",limit.Power_Calculat);
}

