
#include <Handler.h>
#include <DCMotor.h>
#include <CoreLED.h>
#include <CoreKEY.h>
#include <CoreBeep.h>
#include <ExtSRAMInterface.h>
#include <LED.h>
#include <BH1750.h>
#include <Command.h>
#include <BEEP.h>
#include <Infrare.h>
#include <Ultrasonic.h>
#include <SYN7318.h>
#include <Chinese.h>
#include <ZigbeeBiaozhiwu.h>
#include <math.h>
#include <Infrared.h>
#include <PublicVariable.h>
#define TSendCycle 200
uint8_t ZigBee_command[8];
uint8_t ZigBee_judge;
uint8_t infrare_com[6];
unsigned long frisrtime;
unsigned long Tcount;
uint8_t Data_Type;
uint8_t Data_Flag;

void KEY_Handler(uint8_t k_value);
String DecIntToHexStr(long long num);

//自定义算法



//命令列表
int cmdlist1[160][3] = {
  CMD_TGO_GO,
  CMD_TGO_GO,
  CMD_TLEFT,
  CMD_TGO_GO,
  CMD_TRIGHT,
  CMD_JID_SHIBIE,
  CMD_TGO_GO,
  CMD_TRIGHT,
  CMD_TGO_GO,
  {BACK, 50, 2200},
  CMD_END
};

int cmdlist2[50][3] = {
  CMD_TGO_GO,
  CMD_TGO_GO,
  CMD_TLEFT,
  CMD_TGO_GO,
  CMD_TRIGHT,
  CMD_TGO_GO,
  CMD_TRIGHT,
  CMD_TGO_GO,
  {BACK, 50, 2200},
  CMD_END
};
int cmdlist3[30][3] = {
  /*CMD_GO,
  CMD_MPRIGHT_45,
  CMD_MPRIGHT_45,
  //二维码
  CMD_YANSHI,
  CMD_TRIGHT,
  CMD_TGO_GO,
  CMD_TLEFT,
  CMD_TGO_GO,
  CMD_TLEFT,
  CMD_MPLEFT_45,
  CMD_YANSHI,
  CMD_MPRIGHT_45,
  CMD_BACK_LUKOUSTOP,
  CMD_GO,
  CMD_WORDAXIS_HALF,
  CMD_MPLEFT_45,
  CMD_MPLEFT_45,
  CMD_YANSHI,
  CMD_TRIGHT,

  //语音识别交互
  CMD_TGO_GO,
  CMD_YUYIN,
  CMD_YANSHI,
  //通过ETC
  CMD_TLEFT,
  CMD_TGO_GO,
  //RFID 数据获取
  CMD_TGO_GO,
  CMD_TRIGHT,
  CMD_TGO_GO,
  CMD_TRIGHT,
  //经过特殊地形
  CMD_TGO_DX,
  CMD_YANSHI,
  CMD_TRIGHT,
  CMD_MPRIGHT_45,
  //立体显示 任务 11
  CMD_LITI_SHOW_DISTANCE,
  CMD_YANSHI,
  CMD_TRIGHT,
  CMD_MPRIGHT_45,
  CMD_MPRIGHT_45,
  CMD_GET_LIGHT,
  CMD_TRIGHT,
  CMD_TGO_GO,
  CMD_TGO_GO,
  CMD_TRIGHT,
  CMD_MPRIGHT_45,
  //开启报警台12
  CMD_END*/
};
int cmdlist4[30][3] = {
  CMD_QRCODE,
  //  CMD_TGO_GO,
  //  CMD_MPRIGHT,
  //  CMD_TGO,
  //
  //  //识别红绿灯
  //  {MPRIGHT, GW_SPEED, 300},
  //  CMD_YANSHI,
  //  CMD_JID_SHIBIE,
  //  {MPLEFT, GW_SPEED, 300},
  //  //过地形
  //  CMD_TGO_DX,
  //
  //  CMD_TLEFT,
  //  CMD_TGO_GO,
  //
  //  //获取静态标识物b垂直平面到b4 的中心距离
  //  CMD_MPRIGHT,
  //  CMD_YANSHI,
  //  CMD_ULTRASONIC_DIS,
  //  {MYCODE1, 0, 0},
  //  CMD_MPLEFT_
  //  CMD_MPLEFT_45,
  //  CMD_TGO_GO,
  //  CMD_MPRIGHT,
  //  CMD_MPRIGHT,
  //  CMD_BACK,
  //
  //  {1000, 0, 0},
  //  CMD_GO,
  //  CMD_TGO_GO,
  // CMD_TRIGHT
  //
  //  //{MYCODE1, 0, 0},
  CMD_END
};
//解码器
void Arduino_Der(int cmd[][3])
{
  if (getGetSub(PublicVariable.yanshi_check_times) != 0)  return;
  switch (cmd[PublicVariable.index][0])
  {
    case GO: // 前进
      DCMotor.Go(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case BACK: // 后退
      DCMotor.Back(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case TGO: // 循迹
      DCMotor.CarTrack(cmd[PublicVariable.index][1]);
      break;
    case TGO_GO: // 循迹+过地形
      DCMotor.CarTrack(cmd[PublicVariable.index][1]);
      //delay(300);
      DCMotor.Go(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case TGO_DX: // 循迹+过地形
      DCMotor.CarTrack_DX(cmd[PublicVariable.index][1]);
      DCMotor.Go(TRACK_SPEED, GO_MP);
      break;
    case MPLEFT: // 码盘左转
      DCMotor.MPLeft(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case MPRIGHT: // 码盘右转
      DCMotor.MPRight(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case TLEFT: // 循迹左转
      DCMotor.TurnLeft(cmd[PublicVariable.index][1]);
      break;
    case TRIGHT: // 循迹右转
      DCMotor.TurnRight(cmd[PublicVariable.index][1]);
      break;
    case STOP: // 停止
      DCMotor.Stop();
      break;
    case TSTOP: //循迹停止
      DCMotor.CarTrack_stop(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case BACK_LUKOUSTOP:
      DCMotor.Back_lukoustop(cmd[PublicVariable.index][1]);
      break;
    case QRCODE: // 二维码识别
      Handler.ShiBieQRcode();
      break;
    case JTD_SHIBIE: //交通灯识别
      Handler.ShiBieJiaoTongDeng();
      break;
    case TUXING: // 图形
      Handler.ShiBiePicture();
      break;
    case ULTRASONIC: // 超声波测距
      ZigbeeBiaozhiwu.ultrasonic();
      break;
    case LITI:    //立体标志物 A B
      Infrared.liti(cmd[PublicVariable.index][1]);
      break;
    case YUYIN://语音播报物
      ZigbeeBiaozhiwu.speechDisc();
      break;
    case LIGHT: // 路灯
      Infrared.light(cmd[PublicVariable.index][1]);
      break;
    case TOWER: // 烽火台
      Infrared.HW_tower(cmd[PublicVariable.index][1]);
      break;
    case CHEKU: //车库
      ZigbeeBiaozhiwu.cheKu(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case DAOZHA: // 道闸
      ZigbeeBiaozhiwu.gateAgregate(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case WIRELESS://无线电冲
      ZigbeeBiaozhiwu.wirelessAgregate(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case MARKER_LED://LED标志物
      ZigbeeBiaozhiwu.ledAgregate(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case TFT:// TFT
      ZigbeeBiaozhiwu.tftAgregate(cmd[PublicVariable.index][1], cmd[PublicVariable.index][2]);
      break;
    case SEND_TO_STM32://与主车通讯
      ZigbeeBiaozhiwu.sendToSTM32(cmd[PublicVariable.index][1]);
      break;
    case YANSHI:
      ZigbeeBiaozhiwu.yanshi(cmd[PublicVariable.index][1]);
      break;
    case MYCODE1:
      PublicVariable.zigbee_back[2] = 0x96;
      PublicVariable.zigbee_back[3] = PublicVariable.dis / 10;
      PublicVariable.zigbee_back[4] = PublicVariable.dis % 10;
      PublicVariable.sendflag = 0x01;
      ZigbeeBiaozhiwu.yanshi(20);
      break;
    case 1000:
      PublicVariable.run_flag = 0;
      break;
    case 1001:
      ZigbeeBiaozhiwu.yanshi(5);
      PublicVariable.zigbee_back[2] = 0x97;
      PublicVariable.sendflag = 0x01;
      break;
    case CHANGERUNFLAG:
      PublicVariable.run_flag = cmd[PublicVariable.index][1];
      PublicVariable.index = 0;
      return;

    default:
      PublicVariable.run_flag = 0;
      PublicVariable.index = 0;
      return;
  }
  PublicVariable.index++;

  // Serial.print("PublicVariable.index=");
  // Serial.print(PublicVariable.index);
  // Serial.print(", cmd=");
  // Serial.println(cmd[PublicVariable.index][0]);
}

void mucode1()
{
  PublicVariable.chekucengshu = (((PublicVariable.openmv_return_data[0] - 48) + (PublicVariable.openmv_return_data[2] - 48) * (PublicVariable.openmv_return_data[4] - 48) - (PublicVariable.openmv_return_data[6] - 48)) % 4) + 1;

}
void setup()
{
  CoreLED.Initialization();
  CoreKEY.Initialization();
  CoreBeep.Initialization();
  ExtSRAMInterface.Initialization();
  LED.Initialization();
  BH1750.Initialization();
  BEEP.Initialization();
  Infrare.Initialization();
  Ultrasonic.Initialization();
  DCMotor.Initialization();
  SYN7318.Initialization();

  Serial.begin(115200);
  while (!Serial)  ;

  PublicVariable.sendflag = 0;
  frisrtime = 0;
  Tcount = 0;
  PublicVariable.run_flag = 0;

  //TEST TEST TEST
  PublicVariable.dis = 18;
  PublicVariable.platenumber = "ABC123";
}

void loop()
{
  uint8_t si = 0;
  frisrtime = millis();
  CoreKEY.Kwhile(KEY_Handler);                     //按键检测
  if (ExtSRAMInterface.ExMem_Read(0x6100) != 0x00) //从车接收ZigBee数据
  {

    ExtSRAMInterface.ExMem_Read_Bytes(ZigBee_command, 8);
    ZigBee_judge = ZigBee_command[6]; //获取校验和
    Command.Judgment(ZigBee_command); //计算校验和
    if ((ZigBee_judge == ZigBee_command[6]) && (ZigBee_command[0] == 0x55) && (ZigBee_command[7] == 0xBB))
    {
      Handler.ZigBeeRx_Handler(ZigBee_command); //ZigBee接收数据处理
    }
  }

  if (ExtSRAMInterface.ExMem_Read(0x6038) != 0x00) //检测OpenMV识别结果
  {
    Data_Type = ExtSRAMInterface.ExMem_Read(0x603A);
    Data_Flag = ExtSRAMInterface.ExMem_Read(0x603B);
    PublicVariable.data_length = ExtSRAMInterface.ExMem_Read(0x603C);
    PublicVariable.data_length = PublicVariable.data_length + 6;
    ExtSRAMInterface.ExMem_Read_Bytes(0x6038, PublicVariable.openmv_return_data, PublicVariable.data_length);
    if ((PublicVariable.openmv_return_data[0] == 0x55) && (PublicVariable.openmv_return_data[1] == 0x02))
    {
      ExtSRAMInterface.ExMem_Write_Bytes(0x6180, PublicVariable.openmv_return_data, PublicVariable.data_length); //使用自定义数据区上传OpenMV识别结果
      Handler.OpenMVRx_Handler(PublicVariable.openmv_return_data);                                        //接收OpenMV，数据处理函数
    }
  }

  if (((millis() - frisrtime >= TSendCycle) || (Tcount >= TSendCycle)) && (PublicVariable.sendflag > 0)) //获取、上传任务版数据
  {
    ExtSRAMInterface.ExMem_Write_Bytes(0x6080, PublicVariable.zigbee_back, 16);
    Tcount = 0x00;
    PublicVariable.sendflag--;
  }
  else if (PublicVariable.sendflag > 0)
  {
    Tcount += (millis() - frisrtime);
  }

  if (PublicVariable.run_flag != 0)
  {
    switch (PublicVariable.run_flag)
    {
      case 1:
        Arduino_Der(cmdlist1);
        break;
      case 2:
        Arduino_Der(cmdlist2);
        break;
      case 3:
        Arduino_Der(cmdlist3);
        break;
      case 4:
        Arduino_Der(cmdlist4);
        break;
      default:
        return;
    }
  }
}

// uint8_t qrdi_buf[8] = {0x55, 0x02, 0x92, 0x00, 0x00, 0x00, 0x00, 0xBB}; // 给OpenMV发送识别二维码或者交通灯

/**
  功   能: 按键处理函数
  参   数: K_value 按键值
  返回值:无
*/
int key = 1;
void KEY_Handler(uint8_t k_value)
{
  switch (k_value)
  {
    case 1:
      BEEP.TurnOn();
      delay(50);
      PublicVariable.run_flag = 1;
      BEEP.TurnOff();
      break;
    case 2:
      BEEP.TurnOn();
      delay(50);
      PublicVariable.run_flag = 2;
      BEEP.TurnOff();
      break;
    case 3:
      BEEP.TurnOn();
      delay(50);
      PublicVariable.run_flag = 3;
      BEEP.TurnOff();
      break;
    case 4:
      BEEP.TurnOn();
      delay(50);
      PublicVariable.run_flag = 4;
      BEEP.TurnOff();
      break;
  }
}



//空转延时
uint32_t getGetSub(uint32_t c)
{
  if (c > millis())
    c -= millis();
  else
    c = 0;
  return c;
}
