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
	
	
	void OpenMVDiscStartUp(u8 zhu, u8 fu);//OpenMVʶ��XX��������
	void ShiBieJiaoTongDeng();//ʶ��ͨ��
	void ShiBieQRcode();//ʶ���ά��
	void ShiBiePicture();//ʶ��ͼ��

	boolean judgecmd(uint8_t com);
  private:

};
extern _Handler Handler;
//#endif
