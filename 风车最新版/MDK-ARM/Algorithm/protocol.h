#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "usart.h"
#include "String.h"



#define UP_REG_ID    0xA0  //up layer regional id
#define DN_REG_ID    0xA5  //down layer regional id
#define HEADER_LEN   sizeof(frame_header_t)
#define CMD_LEN      2    //cmdid bytes
#define CRC_LEN      2    //crc16 bytes

#define PROTOCAL_FRAME_MAX_SIZE  200

/** 
  * @brief  frame header structure definition
  */
//�ڲ���������
typedef __packed struct
{
  uint8_t  sof;
  uint16_t data_length;
  uint8_t  seq;
  uint8_t  crc8;
} frame_header_t;
//�ⲿ��������

typedef __packed struct
{
	uint8_t SOF;          //������ʼ�ֽڣ��̶�Ϊ0xA5          
	uint16_t DataLength;  //���ݳ���
	uint8_t Seq;          //�����
	uint8_t CRC8;         //֡ͷCRCУ��
}tFrameHeader;//֡ͷ

typedef enum                 //ö�����ͣ�����id_���
{
	GameInfo = 0x0001,      //����������״̬    ����Ƶ�� 10 Hz
	DamagedData = 0x0002,             //�˺����ݣ�ʵʱ����
	ShootData = 0x0003,                //������ݣ�ʵʱ����
	PowerANDHeat = 0x0004,							//���ʺ���������50hzƵ��
	RfidData = 0x0005,								//���ؽ������ݼ�⵽RFID��10hz���ڷ���
	GameData = 0x0006,								//�����������
	BuffChangeData = 0x0007,					//buff״̬����buff״̬�ı����һ��
	PositionData = 0x0008,						//������λ����Ϣ��ǹ�ڳ���λ��
	SelfDefinedData =0x0100, //ѧ���Զ�������      id��_���  
	Wrong = 0x1301       //ö����Ч��ֻ��Ϊ��ʹ��ö�ٴ�СΪ2�ֽ�
}tCmdID; 

typedef __packed struct
{
	uint16_t stageRemainTime;       //����ʣ��ʱ�䣨�ӵ���ʱ�����ӿ�ʼ���㣬��λ s��
	uint8_t gameProgress;     //��������
	uint8_t roboLevel;        //�����˵ȼ�
	uint16_t remainHp;        //ʣ��Ѫ��
	uint16_t maxHp;           //���Ѫ��
}tGameInfo; //����������״̬��0x0001��

typedef __packed struct
{

	uint8_t armorType :4;
	uint8_t hurtType : 4;
	
}tDamagedData;   //�˺�����(0x002)

typedef __packed struct
{
	uint8_t bulletType;
	uint8_t bulletFreq;
	float  bulletSpeed;
	
}tShootData;   //�������(0x003)

typedef __packed struct
{
	
 float chassisVolt;
 float chassisCurrent;
 float chassisPower;
 float chassisPowerBuffer;
	uint16_t shootHeat0;
	uint16_t shootHeat1;
	
}tPowerANDHeat;   //���ʺ���������50hzƵ��(0x004)


typedef __packed struct
{
	
	uint8_t cardType;
	uint8_t cardldx;

}tRfidData;							//���ؽ������ݼ�⵽RFID��10hz���ڷ���(0x005)

typedef __packed struct
{
	
	uint8_t winner;

}tGameData;								//�����������(0x006)

typedef __packed struct
{
	
	uint16_t buffMusk;

}tBuffChangeData;					//buff״̬����buff״̬�ı����һ��(0x007)

typedef __packed struct
{
	
  float x;
	float y;
	float z;
  float yaw;
	
}tPositionData;						//������λ����Ϣ��ǹ�ڳ���λ��(0x008)
typedef __packed struct
{
	float data1;
	float data2;
	float data3;
	uint8_t data4;
}tSelfDefine;                     //�Զ�������(0x100)


typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	__packed union 
	{
		tGameInfo    			GameInfo;  				  //����������״̬    ����Ƶ�� 10 Hz
		tDamagedData  		DamagedData;        //�˺����ݣ�ʵʱ����
		tShootData     		ShootData;          //������ݣ�ʵʱ����
		tPowerANDHeat			PowerANDHeat;				//���ʺ���������50hzƵ��
		tRfidData					RfidData;						//���ؽ������ݼ�⵽RFID��10hz���ڷ���
		tGameData					GameData;						//�����������
		tBuffChangeData		BuffChangeData;			//buff״̬����buff״̬�ı����һ��
		tPositionData			PositionData;				//������λ����Ϣ��ǹ�ڳ���λ��
		tSelfDefine       SelfDefinedData; 		//ѧ���Զ�������      
	}Data;
	uint16_t        CRC16;         //֮ǰ��������CRCУ��   ע������ݺ�֮ǰ�����ݿ��ܲ����������Բ�Ҫֱ��ʹ�ã�����Ҫֱ��ʹ�ã������ڴ˸�ֵ
}tFrame;  //����֡


//typedef __packed struct
//{
//	tFrameHeader    FrameHeader;
//	tCmdID          CmdID;
//  tSelfDefine     SelfDefine;
//	uint16_t        CRC16;         //֮ǰ��������CRCУ��   ע������ݺ�֮ǰ�����ݿ��ܲ����������Բ�Ҫֱ��ʹ�ã�����Ҫֱ��ʹ�ã������ڴ˸�ֵ
//}tFrame;  //����֡


typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tGameInfo       GameInfo;   
	uint16_t        CRC16;         //����CRCУ��
}tGameInfoFrame;  //����������״̬��0x0001��
typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tDamagedData    DamagedData;   
	uint16_t        CRC16;         //����CRCУ��
}tDamagedDataFrame; //ʵʱѪ���仯���ݣ�0x0002��
typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tShootData      ShootData;   
	uint16_t        CRC16;         //����CRCУ��
}tShootDataFrame;    //�������(0x003)  

typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tPowerANDHeat   PowerANDHeat;   
	uint16_t        CRC16;         //����CRCУ��
}tPowerANDHeatFrame;   //���ʺ���������50hzƵ��(0x004)    

typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tRfidData   		RfidData;   
	uint16_t        CRC16;         //����CRCУ��
}tRfidDataFrame;			//���ؽ������ݼ�⵽RFID��10hz���ڷ���(0x005)

typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tGameData   		GameData;   
	uint16_t        CRC16;         //����CRCУ��
}tGameDataFrame;								//�����������(0x006)

typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tBuffChangeData BuffChangeData;   
	uint16_t        CRC16;         //����CRCУ��
}tBuffChangeDataFrame;					//buff״̬����buff״̬�ı����һ��(0x007);	

typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tPositionData   PositionData;   
	uint16_t        CRC16;         //����CRCУ��
}tPositionDataFrame;					 	//������λ����Ϣ��ǹ�ڳ���λ��(0x008)

typedef __packed struct
{
	tFrameHeader    FrameHeader;
	tCmdID          CmdID;
	tSelfDefine     SelfDefine;   
	uint16_t        CRC16;         //����CRCУ��
}tSelfDefineFrame;               //�Զ�������(0x100);	


//�ڲ�����
uint8_t verify_crc8_check_sum(uint8_t* pchMessage, uint16_t dwLength);
uint8_t verify_crc16_check_sum(uint8_t* pchMessage, uint32_t dwLength);
uint8_t get_crc8_check_sum(uint8_t* pchMessage, uint16_t dwLength, uint8_t ucCRC8);
uint16_t get_crc16_check_sum(uint8_t* pchMessage, uint32_t dwLength, uint16_t wCRC);
uint8_t  append_crc8_check_sum(uint8_t* pchMessage, uint16_t dwLength);
uint16_t append_crc16_check_sum(uint8_t* pchMessage, uint32_t dwLength);

//�ӿں���
void Send_FrameData(tCmdID cmdid, uint8_t * pchMessage,uint8_t dwLength);
void sendata(void);

#endif
