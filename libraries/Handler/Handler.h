/*
	Handler
	
	2019 - 9 - 20 @LiaoHelin 
*/ 
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class _Handler 
{
  public:
	void Analyze_Handler(uint8_t *com);
	void ZigBeeRx_Handler(uint8_t *Zigb_Rx_Buf); 
	void OpenMVRx_Handler(uint8_t *mac); 
	
	
	void OpenMVDiscStartUp(u8 zhu, u8 fu);//OpenMV识别XX启动函数
	void ShiBieJiaoTongDeng();//识别交通灯
	void ShiBieQRcode();//识别二维码
	void ShiBiePicture();//识别图形

	boolean judgecmd(uint8_t com);
  private:

};
extern _Handler Handler;
//#endif
