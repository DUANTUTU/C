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
		void daozha_open(void);			    //打开道闸函数声明
		void gateSendPlateOpen(char *chepai);   //向道闸发送车牌函数说明

		void litiGarageF1(void);					//立体车库到达第一层函数声明
		void litiGarageF2(void);					//立体车库到达第二层函数声明
		void litiGarageF3(void);					//立体车库到达第三层函数声明
		void litiGarageF4(void);					//立体车库到达第四层函数声明
		void requestLocation(void);			        //请求返回车库位于第几层函数声明
		void Request_Infrared(void);			    //请求返回前后侧红外状态函数声明

		void Wireless_charging_open(void);		//打开无线充电标志物的函数说明
		void Wireless_charging_close(void);		//打开无线充电标志物的函数说明

		void gateOpenAClose(u8 kaiguan);
		void litiGarage(u8 cengshu);
		void requestDaoZha(void);				//获取道闸状态 
		void LED_Data(u8 paishu,u8 one,u8 two,u8 three);
		void LED_Timer_open(void);		    	  //LED显示标志物计时开始函数声明
		void LED_Timer_close(void);			 	  //LED显示标志物计时结束函数声明
		void LED_Timer_clear(void);			 	  //LED显示标志物计时清零函数声明
		void LED_secondline_clear(void);		  //LED数码管第二行清零函数说明
		void LED_xianshi_juli(void);			  //LED数码管第二行显示距离函数说明
		void LED_secondline_appear(u16 juli);
		void LED_Time(u8 func);
		void TFT_send_chepai(char* chepai);   //向TFT显示车牌信息
		void TFT_jishi_open(void);		   	//TFT标志物计时开始函数声明
		void TFT_jishi_close(void);		    //TFT标志物计时结束函数声明
		void TFT_jishi_clear(void);			//TFT标志物计时清零函数声明

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
		void B_Request_Location(void);			    //请求返回车库位于第几层函数声明
		void B_Request_Infrared(void);			    //请求返回前后侧红外状态函数声明
		void B_TFT_send_chepai(char* chepai);   //向TFT显示车牌信息
		void B_TFT_jishi_open(void);		   	//TFT标志物计时开始函数声明
		void B_TFT_jishi_close(void);		    //TFT标志物计时结束函数声明
		void B_TFT_jishi_clear(void);			//TFT标志物计时清零函数声明

		void B_TFT_picture(u8 fu1,u8 fu2);
		void B_TFT_hex(u8 one,u8 two,u8 three);
		void B_TFT_juli(u8 juli);	
			
			
		/*----------------- 车库 ---------------------*/ 
		void chekuCtl(int param, char type); 	 
		void getGarageLocation(int type);
		
		/*----------------车库内聚--------------------*/ 
		void cheKu(uint8_t type,uint8_t functionPara);		
		
		/*------------------LED内聚-------------------*/ 
		void ledAgregate(uint8_t type,uint8_t functionPara);
		
		/*-------------------TFT内聚------------------*/ 
		void tftAgregate(uint8_t type,uint8_t functionPara);
		
		/*---------------------道闸-------------------*/ 
		void gateAgregate(uint8_t type,uint8_t functionPara);
		void gateRequst();
		
		/*---------------------无线充电-----------------*/ 
		void wirelessAgregate(uint8_t type,uint8_t functionPara);
		
		void speechDisc();
		
		void ultrasonic();
		
		void sendToSTM32(uint8_t protocol);
		
		void yanshi(int a); 
	private:
	

};
extern _ZigbeeBiaozhiwu ZigbeeBiaozhiwu;
//#endif
