//#ifndef _ZIGBEEBIAOZHIWU_h
//#define _ZIGBEEBIAOZHIWU_h
//
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#define u8	uint8_t
#define u16	uint16_t
class _ZigbeeBiaozhiwu {
	public:
		void delayMs(uint16_t shijian);
		void jiaoTongDeng(uint8_t zhu,uint8_t fu);
		void daozha_open(void);			    //�򿪵�բ��������
		void gateSendPlateOpen(char *chepai);   //���բ���ͳ��ƺ���˵��

		void litiGarageF1(void);					//���峵�⵽���һ�㺯������
		void litiGarageF2(void);					//���峵�⵽��ڶ��㺯������
		void litiGarageF3(void);					//���峵�⵽������㺯������
		void litiGarageF4(void);					//���峵�⵽����Ĳ㺯������
		void requestLocation(void);			        //���󷵻س���λ�ڵڼ��㺯������
		void Request_Infrared(void);			    //���󷵻�ǰ������״̬��������

		void Wireless_charging_open(void);		//�����߳���־��ĺ���˵��
		void Wireless_charging_close(void);		//�����߳���־��ĺ���˵��

		void gateOpenAClose(u8 kaiguan);
		void litiGarage(u8 cengshu);
		void requestDaoZha(void);				//��ȡ��բ״̬ 
		void LED_Data(u8 paishu,u8 one,u8 two,u8 three);
		void LED_Timer_open(void);		    	  //LED��ʾ��־���ʱ��ʼ��������
		void LED_Timer_close(void);			 	  //LED��ʾ��־���ʱ������������
		void LED_Timer_clear(void);			 	  //LED��ʾ��־���ʱ���㺯������
		void LED_secondline_clear(void);		  //LED����ܵڶ������㺯��˵��
		void LED_xianshi_juli(void);			  //LED����ܵڶ�����ʾ���뺯��˵��
		void LED_secondline_appear(u16 juli);
		void LED_Time(u8 func);
		void TFT_send_chepai(char* chepai);   //��TFT��ʾ������Ϣ
		void TFT_jishi_open(void);		   	//TFT��־���ʱ��ʼ��������
		void TFT_jishi_close(void);		    //TFT��־���ʱ������������
		void TFT_jishi_clear(void);			//TFT��־���ʱ���㺯������

		void TFT_picture(u8 fu1,u8 fu2);
		void TFT_hex(u8 one,u8 two,u8 three);
		void TFT_juli(u8 juli);
		void SendBianhao(int bh); 
	
		
		/*** B ***/
		void B_jiaotongdeng(uint8_t zhu,uint8_t fu);
		void B_litiGarageF1(); 
		void B_litiGarageF2(); 
		void B_litiGarageF3(); 
		void B_litiGarageF4(); 
		void B_litiGarage(u8 cengshu);
		void B_Request_Location(void);			    //���󷵻س���λ�ڵڼ��㺯������
		void B_Request_Infrared(void);			    //���󷵻�ǰ������״̬��������
		void B_TFT_send_chepai(char* chepai);   //��TFT��ʾ������Ϣ
		void B_TFT_jishi_open(void);		   	//TFT��־���ʱ��ʼ��������
		void B_TFT_jishi_close(void);		    //TFT��־���ʱ������������
		void B_TFT_jishi_clear(void);			//TFT��־���ʱ���㺯������

		void B_TFT_picture(u8 fu1,u8 fu2);
		void B_TFT_hex(u8 one,u8 two,u8 three);
		void B_TFT_juli(u8 juli);	
			
			
		/*----------------- ���� ---------------------*/ 
		void chekuCtl(int param, char type); 	 
		void getGarageLocation(int type);
		
		/*----------------�����ھ�--------------------*/ 
		void cheKu(uint8_t type,uint8_t functionPara);		
		
		/*------------------LED�ھ�-------------------*/ 
		void ledAgregate(uint8_t type,uint8_t functionPara);
		
		/*-------------------TFT�ھ�------------------*/ 
		void tftAgregate(uint8_t type,uint8_t functionPara);
		
		/*---------------------��բ-------------------*/ 
		void gateAgregate(uint8_t type,uint8_t functionPara);
		void gateRequst();
		
		/*---------------------���߳��-----------------*/ 
		void wirelessAgregate(uint8_t type,uint8_t functionPara);
		
		void speechDisc();
		
		void ultrasonic();
		
		void sendToSTM32(uint8_t protocol);
		
		void yanshi(int a); 
	private:
	

};
extern _ZigbeeBiaozhiwu ZigbeeBiaozhiwu;
//#endif
