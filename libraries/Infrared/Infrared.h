/*
	所有有关红外IO
	2019 - 9 - 6 @LiaoHelin 
*/ 


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class _Infrared
{
  public:
  	// 立体标识物所有方法 
  	void liti_traffic(uint8_t param);
  	void liti_show(uint8_t mode,uint8_t param);
  	void liti_platenumber(char *data);	
	void liti_distance(); 
	void liti_default();
	void liti(int type);
	
	//路灯所有方法
	void adjust_light(int End_Goal); 
	void light_one();
	void light_two();
	void light_three();
	uint8_t get_light();
	void light(int type);
	
	//Tower
	void HW_tower(int type); 
	
  private:
	uint8_t HW_K[6] = {1, 2, 3, 4, 5, 6};                    /*报警器打开命令       不修改*/
	uint8_t HW_G[6] = {0x67, 0x34, 0x78, 0xA2, 0xFD, 0x27};  /*报警器关闭命令       不修改*/	
};
extern _Infrared Infrared;
//#endif
