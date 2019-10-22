/*-----------------------------
所有有关红外线IO的使用 
2019-9-6  @LiaoHelin 
*/

#include "Infrared.h"
#include <Infrare.h>
#include <PublicVariable.h>
#include <Command.h> 
#include <BH1750.h>
_Infrared Infrared;


/*----------------------- 立体标识物 ------------------------------*/ 
/*
  立体显示图形/颜色
  参数mode表示选择哪个模式   0x12显示图形    0x13显示颜色
  参数param表示对应的形状或颜色
*/
void _Infrared::liti_show(uint8_t mode, uint8_t param)
{
  uint8_t HW_3D6[6] = {0xff, mode, param, 0x00, 0x00, 0x00};
  delay(10);
  Infrare.Transmition(HW_3D6, 6);
  delay(100);
}

/*
  立体显示路况信息
*/
void _Infrared::liti_traffic(uint8_t param)
{
  uint8_t HW_3D7[6] = {0xff, 0x14, param, 0x00, 0x00, 0x00};
  Infrare.Transmition(HW_3D7, 6);
}

/*
  立体显示车牌
  @data 参数1: 车牌信息 
*/
void _Infrared::liti_platenumber(char *dataParam)
{
  uint8_t HW_3D1[6] = {0xff, 0x20, dataParam[0], dataParam[1], dataParam[2], dataParam[3]};
  Serial.println(dataParam);
  delay(100);
  Infrare.Transmition(HW_3D1, 6);
  delay(100);
  uint8_t HW_3D2[6] = {0xff, 0x10, dataParam[4], dataParam[5], dataParam[6], dataParam[7]};
  delay(100);
  Infrare.Transmition(HW_3D2, 6);
}

/*
立体显示距离
*/
void _Infrared::liti_distance(){
   uint8_t shi = PublicVariable.dis / 10 + 48;
   uint8_t ge = PublicVariable.dis % 10 + 48;
   uint8_t command[6] = {0xff, 0x11, shi, ge, 0x00, 0x00};
   Infrare.Transmition(command, 6);
}

/*
  立体显示默认信息
*/
void _Infrared::liti_default()
{
  uint8_t HW_3D8[6] = {0xff, 0x15, 0x01, 0x00, 0x00, 0x00};
  delay(100);
  Infrare.Transmition(HW_3D8, 6);
}

/*
  立体表示物聚合函数
*/
void _Infrared::liti(int type)
{
  switch (type)
  {
  case 1: //显示距离
    liti_distance();
    break;
  case 2: //显示默认信息 并且归零
    liti_default();
    break;
  case 3: //显示 形状 全局变量 liti_show_content 根据@param liti_show_content 参数显示对应模式的语句 
    liti_show(0x12, PublicVariable.liti_show_content);
    break;
  case 4: //显示 颜色 全局变量 liti_show_content 根据@param liti_show_content 参数显示对应模式的语句 
    liti_show(0x13, PublicVariable.liti_show_content);
    break;
  case 5: //显示路况 根据@param liti_show_content 参数显示对应模式的语句 
    liti_traffic(PublicVariable.liti_show_content);
    break;
  case 6: //显示车牌    
    liti_platenumber(PublicVariable.platenumber);
    break;
  default:
    break;
  }
}

/*------------------------ 路灯 -------------------*/
/*
  路灯自动调节到指定档位
  参数 End_Goal是要调到的最终档位
*/
void _Infrared::adjust_light(int End_Goal){
	long array[4];
	long nowLight = 0;
  	if (End_Goal != 0 && End_Goal < 5)
	  {
    	for (int i = 0; i < 4; i++)
   		 {
    	  Infrare.Transmition(Command.HW_Dimming1, 4);
    	  delay(1500);
    	  array[i] = BH1750.ReadLightLevel();
   		 }
   		nowLight = array[3];
 	 }

  for (int i = 0; i < 4 - 1; i++)
  {
    for (int j = 0; j < 3 - i; j++)
    {
      if (array[j] > array[j + 1])
      {
        long temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }

  for (int n = 0; n < 4; n++)
  {
    if (nowLight == array[n])
    {
      int size = (End_Goal + 3 - n) % 4;
      if (size == 1)
      {
        Infrare.Transmition(Command.HW_Dimming1, 4);
      }
      else if (size == 2)
      {
        Infrare.Transmition(Command.HW_Dimming2, 4);
      }
      else if (size == 3)
      {
        Infrare.Transmition(Command.HW_Dimming3, 4);
      }
    }
  }
  }
  
  // 智能路灯光源档位加1档
void _Infrared::light_one()
{
  Infrare.Transmition(Command.HW_Dimming1, 4);
  delay(100);
}

// 智能路灯光源档位加2档
void _Infrared::light_two()
{
  Infrare.Transmition(Command.HW_Dimming2, 4);
  delay(100);
}

// 智能路灯光源档位加3档
void _Infrared::light_three()
{
  Infrare.Transmition(Command.HW_Dimming3, 4);
  delay(100);
}

/*
  获取路灯当前档位
*/
uint8_t _Infrared::get_light()
{
  long array[4];
  long nowLight = 0;
  for (int i = 0; i < 4; i++)
  {
    Infrare.Transmition(Command.HW_Dimming1, 4);
    delay(1500);
    array[i] = BH1750.ReadLightLevel();
    ;
  }
  nowLight = array[3];
  for (int i = 0; i < 4 - 1; i++)
  {
    for (int j = 0; j < 3 - i; j++)
    {
      if (array[j] > array[j + 1])
      {
        long temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }

  for (int n = 0; n < 4; n++)
  {
    if (nowLight == array[n])
    {
      return n + 1;
    }
  }
}

/*LIGHT 聚合*/
void _Infrared::light(int type){
	switch(type){
		case 1:
			adjust_light(type);
			break;
		case 2:
			adjust_light(type);
			break;
		case 3:
			adjust_light(type);
			break;
		case 4:
			break;
		case 5:
			PublicVariable.gear = get_light();
			break;
	}
} 


/* --------------- Totwer ---------- */ 
void _Infrared::HW_tower(int type) {
	switch(type){
		case 1:
			Infrare.Transmition(HW_K, 6);
  			delay(100);
  		case 2:
  			Infrare.Transmition(HW_G, 6);
  			delay(100);
	}
} 

