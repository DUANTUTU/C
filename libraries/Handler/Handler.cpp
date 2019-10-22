/*-----------------------------
		?????? 
2019-9-20  @LiaoHelin 
*/

#include "Handler.h"
#include "DCMotor.h"
#include "LED.h"
#include "BEEP.h"
#include "Command.h"
#include "ExtSRAMInterface.h"
#include "Infrare.h"- 
#include "PublicVariable.h"
#include "ZigbeeBiaozhiwu.h" 
_Handler Handler;


uint8_t oldcmd = 0;
boolean _Handler::judgecmd(uint8_t com)
{
  if (com != oldcmd)
  {
    oldcmd = com;
    return 1;
  }
  return 0;
}
/**
  ??    ????????????????
  ??    ????com ?????
  ?? ?? ?????
*/
void _Handler::Analyze_Handler(uint8_t *com)
{

  switch (com[2])
  {
  case 0x01: //??
    DCMotor.Stop();
    break;
  case 0x02: //???
    DCMotor.Go(com[3], (com[4] + (com[5] << 8)));
    PublicVariable.zigbee_back[2] = 0x03;
    break;
  case 0x03: //????
    DCMotor.Back(com[3], (com[4] + (com[5] << 8)));
    PublicVariable.zigbee_back[2] = 0x03;
    break;
  case 0x04: //???
    DCMotor.TurnLeft(com[3]);
    PublicVariable.zigbee_back[2] = 0x02;
    break;
  case 0x05: //???
    DCMotor.TurnRight(com[3]);
    PublicVariable.zigbee_back[2] = 0x02;
    break;
  case 0x06: //???
    DCMotor.CarTrack(com[3]);
    PublicVariable.zigbee_back[2] = 0x00;
    break;
  case 0x07:                                                  //????????
    Command.Judgment(Command.command01);                      //????У???
    ExtSRAMInterface.ExMem_Write_Bytes(Command.command01, 8); //????????
    break;
  case 0x10: //???????????
    PublicVariable.infrare_com[0] = com[3];
    PublicVariable.infrare_com[1] = com[4];
    PublicVariable.infrare_com[2] = com[5];
    break;
  case 0x11: //???????????
    PublicVariable.infrare_com[3] = com[3];
    PublicVariable.infrare_com[4] = com[4];
    PublicVariable.infrare_com[5] = com[5];
    break;
  case 0x12: //???????????
    Infrare.Transmition(PublicVariable.infrare_com, 6);
    break;
  case 0x20: //????????
    if (com[3] == 0x01)
      LED.LeftTurnOn();
    else
      LED.LeftTurnOff();
    if (com[4] == 0x01)
      LED.RightTurnOn();
    else
      LED.RightTurnOff();
    break;
	case 0x90:
		PublicVariable.run_flag = 0x01;	
  case 0x30: //??????
    if (com[3] == 0x01)
      BEEP.TurnOn();
    else
      BEEP.TurnOff();
    break;
  case 0x40: //????
    break;
  case 0x50: //LCD??????
    Command.Judgment(Command.command13);
    ExtSRAMInterface.ExMem_Write_Bytes(Command.command13, 8);
    break;
  case 0x51: //LCD???·??
    Command.Judgment(Command.command14);
    ExtSRAMInterface.ExMem_Write_Bytes(Command.command14, 8);
    break;
  case 0x61: //????????
    Infrare.Transmition(Command.HW_Dimming1, 4);
    break;
  case 0x62: //????????
    Infrare.Transmition(Command.HW_Dimming2, 4);
    break;
  case 0x63: //?????????
    Infrare.Transmition(Command.HW_Dimming3, 4);
    break;
  case 0x80: //????????????л?
  
  
    if (com[3] == 0x01)
    {
      PublicVariable.sendflag = 0x01; //??????????
    }
    else
    {
      PublicVariable.sendflag = 0x00; //???????????
      oldcmd=0;
    }
    break;
     case 0x81: //????????????л?
     PublicVariable.run_flag = 0x01;
     break; 
  case 0x94: //??????????
    
    break;
  case 0x95: //???????????  
    PublicVariable.zigbee_back[2]=com[2];
    PublicVariable.sendflag=0x01;
    if (!judgecmd(com[2]))    break;//???е???ν?????????
	PublicVariable.run_flag=4;
	break;	 

  case 0x97:

    break;
  case 0x98:
    PublicVariable.zigbee_back[2]=com[2];
    PublicVariable.sendflag=0x01;
    if (!judgecmd(com[2]))    break;//???е???ν?????????
    PublicVariable.run_flag=4;
    break;    
  default:
    break;
  }
}



/*
  ??    ??????ZigBee?????????????
  ??    ????*mar ???????????
  ?? ?? ?????
*/
void _Handler::ZigBeeRx_Handler(uint8_t *Zigb_Rx_Buf)
{
  switch (Zigb_Rx_Buf[1])
  {
  case 0x02:                      //????
     Analyze_Handler(Zigb_Rx_Buf); //???????????????
    break;
  case 0x03: //????????
    if (Zigb_Rx_Buf[2] == 0x01)
    {
      PublicVariable.stop_flag = Zigb_Rx_Buf[4];
    }
    break;
  case 0x04: //LED????????????????
    break;
  case 0x05: //???峵??????B
    if ((Zigb_Rx_Buf[2] == 0x03) && (Zigb_Rx_Buf[3] == 0x01))
    {
      switch (Zigb_Rx_Buf[4])
      {
      case 1:
        PublicVariable.stop_flag = 0x09; //?????
        break;
      case 2:
        PublicVariable.stop_flag = 0x0A; //?????
        break;
      case 3:
        PublicVariable.stop_flag = 0x0B; //??????
        break;
      case 4:
        PublicVariable.stop_flag = 0x0C; //?????
        break;
      }
    }
    break;
  case 0x06: //?????????????
    break;
  case 0x07: //???????????
    break;
  case 0x08: //TFT????????B
    break;
  case 0x09: //????????
    break;
  case 0x0A: //????????????????
    break;
  case 0x0B: //TFT????????A
    break;
  case 0x0C: //ETC???????
    break;
  case 0x0D: //???峵??????A
    if ((Zigb_Rx_Buf[2] == 0x03) && (Zigb_Rx_Buf[3] == 0x01))
    {
      switch (Zigb_Rx_Buf[4])
      {
      case 1:
        PublicVariable.stop_flag = 0x09; //?????
        break;
      case 2:
        PublicVariable.stop_flag = 0x0A; //?????
        break;
      case 3:
        PublicVariable.stop_flag = 0x0B; //??????
        break;
      case 4:
        PublicVariable.stop_flag = 0x0C; //?????
        break;
      }
    }
    break;
  case 0x0E: //?????????A
    if (Zigb_Rx_Buf[2] == 0x01)
    {
      PublicVariable.stop_flag = Zigb_Rx_Buf[4];
    }
    break;
  case 0x0F: //?????????B
    if (Zigb_Rx_Buf[2] == 0x01)
    {
      PublicVariable.stop_flag = Zigb_Rx_Buf[4];
    }
    break;
  default:
    break;
  }
}



void _Handler::OpenMVRx_Handler(uint8_t *mac)
{
  Serial.print("OpenMV ");
  Serial.println("");
  switch (mac[2])
  {
  case 0x91: //?????
    Serial.print("OpenMV ");
    Serial.println("");
    PublicVariable.data_length = PublicVariable.data_length + 6;
    ExtSRAMInterface.ExMem_Read_Bytes(0x6038, PublicVariable.openmv_return_data, PublicVariable.data_length); // ???????????
    PublicVariable.openmv_agvdata_flag = 1;
    if (PublicVariable.isstart == true)
      PublicVariable.openmv_zhuangtai = 1;
    break;
  case 0x92: //????????
    PublicVariable.data_length = PublicVariable.data_length + 6;
    ExtSRAMInterface.ExMem_Read_Bytes(0x6038, PublicVariable.openmv_return_data, PublicVariable.data_length);  // ???????????
    ExtSRAMInterface.ExMem_Write_Bytes(0x6180, PublicVariable.openmv_return_data, PublicVariable.data_length); // ?????????????
    for (int i = 0; i < PublicVariable.data_length; i++)
    {
    	Serial.println(PublicVariable.openmv_return_data[i]);
    }
    PublicVariable.openmv_agvdata_flag = 1;
    if (PublicVariable.isstart == true)
      PublicVariable.openmv_zhuangtai = 2;

    break;
  case 0x93: //
    PublicVariable.data_length = PublicVariable.data_length + 6;
    ExtSRAMInterface.ExMem_Read_Bytes(0x6038, PublicVariable.openmv_return_data, PublicVariable.data_length); // ???????????
    PublicVariable.openmv_agvdata_flag = 1;
    PublicVariable.openmv_zhuangtai = 3;
    if (PublicVariable.circlenum < PublicVariable.openmv_return_data[3])
    {
      PublicVariable.circlenum = PublicVariable.openmv_return_data[3];
    }
    break;
  default:
    break;
  }
}

///////////////////////////openmv????????/////////////////////////////////////

/*
  ??    ?????????? ???????Camera????????
  ??    ????*mac ???????????
  ?? ?? ?????
*/

int count = 0; 




//??????
void _Handler::ShiBiePicture()
{
  if (PublicVariable.openmv_zhuangtai != 3 && count < 6)
  {
    PublicVariable.isstart = true;
    OpenMVDiscStartUp(0x91, 0x01);
    ZigbeeBiaozhiwu.yanshi(20);
    PublicVariable.index--;
    count++;
  }
  else
  {
    PublicVariable.isstart = false;
    PublicVariable.openmv_zhuangtai = 0;
    count = 0;
  }
}

//???????
void _Handler::ShiBieQRcode()
{
  if (PublicVariable.openmv_zhuangtai != 2 && count < 6)
  {
    PublicVariable.isstart = true;
    OpenMVDiscStartUp(0x92, 0x01);
    ZigbeeBiaozhiwu.yanshi(20);
    PublicVariable.index--;
    count++;
  }
  else
  {
    PublicVariable.isstart = false;
    if (PublicVariable.openmv_zhuangtai == 2)
    {
         }
    PublicVariable.openmv_zhuangtai = 0;
    count = 0;
  }
}



//??????
void _Handler::ShiBieJiaoTongDeng()
{
  if (PublicVariable.stop_flag != 7 && PublicVariable.daozha_count < 3)
  {
    if (PublicVariable.jtd_type == 'A')
      ZigbeeBiaozhiwu.jiaoTongDeng(0x01, 0x00); //?????????
    if (PublicVariable.jtd_type == 'B')
      ZigbeeBiaozhiwu.B_jiaotongdeng(0x01, 0x00); //?????????
    ZigbeeBiaozhiwu.yanshi(5);
    PublicVariable.daozha_count++;
    PublicVariable.index--;
    Serial.println(111);
  }
  else
  {
    if (PublicVariable.openmv_zhuangtai != 1 && count < 4)
    {
      PublicVariable.isstart = true;
      OpenMVDiscStartUp(0x91, 0x00);
      ZigbeeBiaozhiwu.yanshi(10);
      PublicVariable.index--;
      count++;
    }
    else
    {
      if (PublicVariable.openmv_zhuangtai == 1)
      {
        PublicVariable.isstart = false;
        if (PublicVariable.openmv_return_data[3] == 1)
        {
          Serial.println("red");
          Serial.println(PublicVariable.openmv_return_data[3]);
          if (PublicVariable.jtd_type == 'A')
          {
            ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x01);
            delay(300);
            ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x01);
          }
          if (PublicVariable.jtd_type == 'B')
          {
            ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x01);
            delay(300);
            ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x01);
          }
        }
        else if (PublicVariable.openmv_return_data[3] == 2)
        {
          Serial.println("green");
          if (PublicVariable.jtd_type == 'A')
          {
            ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x02);
            delay(300);
            ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x02);
          }
          if (PublicVariable.jtd_type == 'B')
          {
            ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x02);
            delay(300);
            ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x02);
          }
        }
        else if (PublicVariable.openmv_return_data[3] == 4)
        {
          Serial.println("yellow");
          if (PublicVariable.jtd_type == 'A')
          {
            ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x03);
            delay(300);
            ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x03);
          }
          if (PublicVariable.jtd_type == 'B')
          {
            ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x03);
            delay(300);
            ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x03);
          }
        }
      }
      else
      { //?????

        if (PublicVariable.jtd_type == 'A')
        {
          ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x03);
          delay(300);
          ZigbeeBiaozhiwu.jiaoTongDeng(0x02, 0x03);
        }
        if (PublicVariable.jtd_type == 'B')
        {
          ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x03);
          delay(300);
          ZigbeeBiaozhiwu.B_jiaotongdeng(0x02, 0x03);
        }
      }
      count = 0;
      PublicVariable.openmv_zhuangtai = 0;
      PublicVariable.stop_flag = 0;
      PublicVariable.daozha_count = 0;
    }
  }
}

/*????
  ??    ???OpenMV???XX????????
  ??    ??
  ?? ?? ?????
*/
void _Handler::OpenMVDiscStartUp(u8 zhu, u8 fu)
{
  PublicVariable.qrdi_buf[2] = zhu;
  PublicVariable.qrdi_buf[3] = fu;           //??????
  Command.Judgment(PublicVariable.qrdi_buf); //????У???
  ExtSRAMInterface.ExMem_Write_Bytes(0x6008, PublicVariable.qrdi_buf, 8);
}


