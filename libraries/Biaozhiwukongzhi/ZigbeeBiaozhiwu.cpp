/**
*	从车通过zigbee控制的标志物所有的函数
*	2019.05.12	胡记龙
*/
#include "ZigbeeBiaozhiwu.h"
#include <Command.h>
#include <Chinese.h>
#include <ExtSRAMInterface.h>
#include <Infrare.h>
#include <math.h>
#include <PublicVariable.h>
#include <SYN7318.h> 
#include <Ultrasonic.h>

_ZigbeeBiaozhiwu ZigbeeBiaozhiwu;

uint8_t send_zigbee[8];
int i=1;
void _ZigbeeBiaozhiwu:: delayMs(uint16_t shijian){
    unsigned long t;
	t=millis();
	while(millis()-t<shijian);
}

/**
*从车控制智能交通灯
*参数zhu,0x01为进入识别模式，0x02为请求确认识别结果
*参数fu,如zhu为0x01保留不用，如zhu为0x02,fu0x01为红灯，0x02为绿灯，0x03为黄灯
*/
void _ZigbeeBiaozhiwu:: jiaoTongDeng(uint8_t zhu,uint8_t fu){
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0E;
	send_zigbee[2]=zhu;
	send_zigbee[3]=fu;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;
	send_zigbee[7]=0xBB;
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
}

/***************************************************************
** 功能：   立体车库到达第一层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu::litiGarageF1() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0d;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x01;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/***************************************************************
** 功能：   立体车库到达第二层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: litiGarageF2() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0d;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x02;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/***************************************************************
** 功能：   立体车库到达第三层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: litiGarageF3() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0d;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x03;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/***************************************************************
** 功能：   立体车库到达第四层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: litiGarageF4() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0d;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x04;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/**
*控制立体车库到达某一层，参数cengshu为控制车库需要到达的层数
*/
void _ZigbeeBiaozhiwu:: litiGarage(u8 cengshu) {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0d;
	send_zigbee[2]=0x01;
	send_zigbee[3]=cengshu;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);

}
/***************************************************************
** 功能：   请求返回车库位于第几层
** 参数：	 head  0x0d为标志物A    0x05为标志位B 
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: requestLocation() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0d;
	send_zigbee[2]=0x02;
	send_zigbee[3]=0x01;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(100);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}


/***************************************************************
** 功能：   请求返回前后侧红外状态
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: Request_Infrared() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0d;
	send_zigbee[2]=0x02;
	send_zigbee[3]=0x02;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}



/***************************************************************
** 功能：    无线充电标志物开启
** 参数：	 无
** 返回值：  无
** 说明：    主车通过zigbee控制无线充电标志物开启
****************************************************************/
void _ZigbeeBiaozhiwu:: Wireless_charging_open() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0a;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x01;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/***************************************************************
** 功能：    无线充电标志物关闭
** 参数：	 无
** 返回值：  无
** 说明：    主车通过zigbee控制无线充电标志物关闭
****************************************************************/
void _ZigbeeBiaozhiwu:: Wireless_charging_close() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0a;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x00;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}




/***************************************************************
** 功能：     LED显示标志物开始计时
** 参数：	  无
** 返回值：   无
** 说明：     主车通过zigbee控制LED显示标志物的计时功能开启
****************************************************************/
void _ZigbeeBiaozhiwu::LED_Timer_open()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x04;
    send_zigbee[2]=0x03;
    send_zigbee[3]=0x01;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/***************************************************************
** 功能：     LED显示标志物计时结束
** 参数：	  无
** 返回值：   无
** 说明：     主车通过zigbee控制LED显示标志物的计时功能关闭
****************************************************************/
void _ZigbeeBiaozhiwu:: LED_Timer_close()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x04;
    send_zigbee[2]=0x03;
    send_zigbee[3]=0x00;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/***************************************************************
** 功能：     LED显示标志物计时清零
** 参数：	  无
** 返回值：   无
** 说明：     主车通过zigbee控制LED显示标志物的计时清零
****************************************************************/
void _ZigbeeBiaozhiwu:: LED_Timer_clear()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x04;
    send_zigbee[2]=0x03;
    send_zigbee[3]=0x02;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*LED进入计时模式，参数function为指定计时模式的功能，0x00关闭，0x01打开，0x02清零
*/
void _ZigbeeBiaozhiwu:: LED_Time(u8 func)
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x04;
    send_zigbee[2]=0x03;
    send_zigbee[3]=func;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(300);
}
/***************************************************************
** 功能：     LED显示标志物第二行清零
** 参数：	  无
** 返回值：   无
** 说明：     主车通过zigbee控制LED显示标志物的第二行清零
****************************************************************/
void _ZigbeeBiaozhiwu:: LED_secondline_clear()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x04;
    send_zigbee[2]=0x02;
    send_zigbee[3]=0x00;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}

/***************************************************************
** 功能：     LED显示标志物第二行显示距离
** 参数：	  需要显示的值
** 返回值：   无
** 说明：     主车通过zigbee控制LED显示标志物的第二行显示距离
****************************************************************/

void _ZigbeeBiaozhiwu:: LED_secondline_appear(uint16_t juli)
{
	
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x04;
    send_zigbee[2]=0x04;
    send_zigbee[3]=0x00;
    int ge,shi,bai;
    //bai=juli/100;
    shi=(juli%100)/10;
    send_zigbee[4]=0x00;
    send_zigbee[5]=(shi<<4)+(juli%10);
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*LED第一排和第二排写入数据
*参数paishu为要在第几排写入数据，1为1排，2为2排
*参数one，two，three为要写入的数据
*/
void _ZigbeeBiaozhiwu:: LED_Data(u8 paishu,u8 one,u8 two,u8 three)
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x04;
    send_zigbee[2]=paishu;
    send_zigbee[3]=one;
    send_zigbee[4]=two;
    send_zigbee[5]=three;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/***************************************************************
** 功能：     向TFT标志物发送车牌
** 参数：	    车牌6位的ASCll值
** 返回值：   无
** 说明：     主车通过zigbee向TFT发送车牌信息
****************************************************************/
void _ZigbeeBiaozhiwu:: TFT_send_chepai(char* chepai)
{
		delayMs(500);
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x20;
    send_zigbee[3]=chepai[0];
    send_zigbee[4]=chepai[1];
    send_zigbee[5]=chepai[2];
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(500);
	  delayMs(500);

    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x21;
    send_zigbee[3]=chepai[3];
    send_zigbee[4]=chepai[4];
    send_zigbee[5]=chepai[5];
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}

/***************************************************************
** 功能：     TFT标志物计时功能开始
** 参数：	    无
** 返回值：   无
** 说明：     主车通过zigbee控制TFT标志物的计时功能开启
****************************************************************/
void _ZigbeeBiaozhiwu:: TFT_jishi_open()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x30;
    send_zigbee[3]=0x01;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}

/***************************************************************
** 功能：     TFT标志物计时功能结束
** 参数：	    无
** 返回值：   无
** 说明：     主车通过zigbee控制TFT标志物的计时功能结束
****************************************************************/
void _ZigbeeBiaozhiwu:: TFT_jishi_close()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x30;
    send_zigbee[3]=0x00;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}

/***************************************************************
** 功能：     TFT标志物计时功能清零
** 参数：	    无
** 返回值：   无
** 说明：     主车通过zigbee控制TFT标志物的计时功能清零
****************************************************************/
void _ZigbeeBiaozhiwu:: TFT_jishi_clear()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x30;
    send_zigbee[3]=0x02;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*TFT图片显示模式，参数为副指令1和副指令2
*/
void _ZigbeeBiaozhiwu:: TFT_picture(u8 fu1,u8 fu2)
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x10;
    send_zigbee[3]=fu1;
    send_zigbee[4]=fu2;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*TFTHEX显示模式,参数为要显示的3为数据
*/
void _ZigbeeBiaozhiwu:: TFT_hex(u8 one,u8 two,u8 three)
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x40;
    send_zigbee[3]=one;
    send_zigbee[4]=two;
    send_zigbee[5]=three;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*TFTHEX显示距离模式,参数为要显示的距离的百位和十位个位
*/
void _ZigbeeBiaozhiwu:: TFT_juli(u8 juli)
{
	juli *= 10;
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x0b;
    send_zigbee[2]=0x50;
    send_zigbee[3]=0x00;
    int ge,shi,bai;
    bai=juli/100;
    shi=(juli%100)/10;
    send_zigbee[4]=bai;
    send_zigbee[5]=(shi<<4)+(juli%10);
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}


/********************** 标志物B *************************/ 

/**
*从车控制智能交通灯
*参数zhu,0x01为进入识别模式，0x02为请求确认识别结果
*参数fu,如zhu为0x01保留不用，如zhu为0x02,fu0x01为红灯，0x02为绿灯，0x03为黄灯
*/
void _ZigbeeBiaozhiwu:: B_jiaotongdeng(uint8_t zhu,uint8_t fu) {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x0F;
	send_zigbee[2]=zhu;
	send_zigbee[3]=fu;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xBB;
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
}

/***************************************************************
** 功能：   立体车库到达第一层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu::B_litiGarageF1() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x05;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x01;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);

}
/***************************************************************
** 功能：   立体车库到达第二层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: B_litiGarageF2() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x05;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x02;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/***************************************************************
** 功能：   立体车库到达第三层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: B_litiGarageF3() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x05;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x03;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/***************************************************************
** 功能：   立体车库到达第四层
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: B_litiGarageF4() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x05;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x04;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/**
*控制立体车库到达某一层，参数cengshu为控制车库需要到达的层数
*/
void _ZigbeeBiaozhiwu:: B_litiGarage(u8 cengshu) {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x05;
	send_zigbee[2]=0x01;
	send_zigbee[3]=cengshu;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);

}
/***************************************************************
** 功能：   请求返回车库位于第几层
** 参数：	 head  0x0d为标志物A    0x05为标志位B 
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: B_Request_Location() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x05;
	send_zigbee[2]=0x02;
	send_zigbee[3]=0x01;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(100);

	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}


/***************************************************************
** 功能：   请求返回前后侧红外状态
** 参数：	  无参数
** 返回值： 无
****************************************************************/
void _ZigbeeBiaozhiwu:: B_Request_Infrared() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x05;
	send_zigbee[2]=0x02;
	send_zigbee[3]=0x02;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}

/***************************************************************
** 功能：     向TFT标志物发送车牌
** 参数：	    车牌6位的ASCll值
** 返回值：   无
** 说明：     主车通过zigbee向TFT发送车牌信息
****************************************************************/
void _ZigbeeBiaozhiwu:: B_TFT_send_chepai(char* chepai)
{
	delayMs(500);
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x20;
    send_zigbee[3]=chepai[0];
    send_zigbee[4]=chepai[1];
    send_zigbee[5]=chepai[2];
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(500);
	delayMs(500);

    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x21;
    send_zigbee[3]=chepai[3];
    send_zigbee[4]=chepai[4];
    send_zigbee[5]=chepai[5];
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}

/***************************************************************
** 功能：     TFT标志物计时功能开始
** 参数：	    无
** 返回值：   无
** 说明：     主车通过zigbee控制TFT标志物的计时功能开启
****************************************************************/
void _ZigbeeBiaozhiwu:: B_TFT_jishi_open()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x30;
    send_zigbee[3]=0x01;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}

/***************************************************************
** 功能：     TFT标志物计时功能结束
** 参数：	    无
** 返回值：   无
** 说明：     主车通过zigbee控制TFT标志物的计时功能结束
****************************************************************/
void _ZigbeeBiaozhiwu:: B_TFT_jishi_close()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x30;
    send_zigbee[3]=0x00;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}

/***************************************************************
** 功能：     TFT标志物计时功能清零
** 参数：	    无
** 返回值：   无
** 说明：     主车通过zigbee控制TFT标志物的计时功能清零
****************************************************************/
void _ZigbeeBiaozhiwu:: B_TFT_jishi_clear()
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x30;
    send_zigbee[3]=0x02;
    send_zigbee[4]=0x00;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*TFT图片显示模式，参数为副指令1和副指令2
*/
void _ZigbeeBiaozhiwu:: B_TFT_picture(u8 fu1,u8 fu2)
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x10;
    send_zigbee[3]=fu1;
    send_zigbee[4]=fu2;
    send_zigbee[5]=0x00;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*TFTHEX显示模式,参数为要显示的3为数据
*/
void _ZigbeeBiaozhiwu:: B_TFT_hex(u8 one,u8 two,u8 three)
{
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x40;
    send_zigbee[3]=one;
    send_zigbee[4]=two;
    send_zigbee[5]=three;
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*TFTHEX显示距离模式,参数为要显示的距离的百位和十位个位
*/
void _ZigbeeBiaozhiwu:: B_TFT_juli(u8 juli)
{
	juli *= 10;
    send_zigbee[0]=0x55;
    send_zigbee[1]=0x08;
    send_zigbee[2]=0x50;
    send_zigbee[3]=0x00;
    int ge,shi,bai;
    bai=juli/100;
    shi=(juli%100)/10;
    send_zigbee[4]=bai;
    send_zigbee[5]=(shi<<4)+(juli%10);
    send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
    send_zigbee[7]=0xbb;
    delayMs(1);
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
    delayMs(100);
}
/**
*语音识别的编号发送给评分终端 
*/
void _ZigbeeBiaozhiwu:: SendBianhao(int bh)
{
    uint8_t array[] = {0xAF,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
    array[2] = bh;
    array[3] = 0x02;
    array[4] = 0x00;
    array[5] = 0x00;
    array[6] = 0x01;
    array[7] = 0xBB;
    ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
}


/*---------------------有关车库------------------*/ 
//控制车库到达目标层
void _ZigbeeBiaozhiwu::chekuCtl(int param, char type)
{
  if (PublicVariable.stop_flag == 0 && PublicVariable.daozha_count < 5)
  {
    if (type == 'A')
      ZigbeeBiaozhiwu.requestLocation();
    if (type == 'B')
      ZigbeeBiaozhiwu.B_Request_Location();
 	PublicVariable.daozha_count++;
    PublicVariable.index--;
    yanshi(6);
  }
  else if (PublicVariable.stop_flag != 0)
  {
    Serial.println(222);
    for (int i = 1; i < 3; i++)
    {
      delay(100);
      if (type == 'A')
        ZigbeeBiaozhiwu.litiGarage(param);
      if (type == 'B')
        ZigbeeBiaozhiwu.B_litiGarage(param);
    }

    yanshi(120 * (abs(param - (PublicVariable.stop_flag - 8))));
    PublicVariable.stop_flag = 0;
    PublicVariable.daozha_count = 0;
  }
  else if (PublicVariable.daozha_count = 5)
  {
    Serial.println(333);

    for (int i = 1; i < 3; i++)
    {
      delay(100);
      ZigbeeBiaozhiwu.litiGarage(param);
    }
    yanshi(300);
    PublicVariable.stop_flag = 0;
    PublicVariable.daozha_count = 0;
  }
}
/**
   获取AB车库当前层数
**/
void _ZigbeeBiaozhiwu::getGarageLocation(int type)
{
  if (PublicVariable.stop_flag == 0 && PublicVariable.daozha_count < 5)
  {
    Serial.println(111);
    if (type == 'A')
      ZigbeeBiaozhiwu.requestLocation();
    if (type == 'B')
      ZigbeeBiaozhiwu.B_Request_Location();
    PublicVariable.daozha_count++;
    PublicVariable.index--;
    yanshi(6);
  }
  else if (PublicVariable.stop_flag != 0)
  {
    Serial.println(PublicVariable.stop_flag);

    switch (PublicVariable.stop_flag)
    {
    case 0x09:
      PublicVariable.current_garage = 1; //第一层
      break;
    case 0x0A:
      PublicVariable.current_garage = 2; //第二层
      break;
    case 0x0B:
      PublicVariable.current_garage = 3; //第三层
      break;
    case 0x0C:
      PublicVariable.current_garage = 4; //第四层
      break;
    }
    PublicVariable.stop_flag = 0;
    PublicVariable.daozha_count = 0;
  }
}

/*----------------车库内聚---------------*/
//@type 参数在1-10之间表示"A"车库,大于10表示"B"车库 
void _ZigbeeBiaozhiwu::cheKu(uint8_t type,uint8_t functionPara){
		switch(type){
			case 1:
				litiGarage(functionPara);
				break;
			case 2:
				requestLocation();		//获得当前车库位置 
				break;
			case 3:
				chekuCtl(functionPara, 'A');//判断当前车库是否在指定层，不在的话就到达指定层
				break;
			case 4:
				getGarageLocation('A');	//获得A车库当前位置 
				break;
			case 11:
				B_litiGarage(functionPara);
				break;
			case 12:
				requestLocation();
				break;
			case 13:
				chekuCtl(functionPara, 'B');	//判断当前车库是否在指定层，不在的话就到达指定层
				break;
			case 14:
				getGarageLocation('B');
				break;
				
		
				
		}
};

/*-------------------Led 内聚--------------------*/
void _ZigbeeBiaozhiwu::ledAgregate(uint8_t type,uint8_t functionPara){
	switch(type){
		case 1:
			LED_Time(1);
			break;
		case 2:
			LED_Time(2);
			break;
		case 3:
			LED_secondline_appear(PublicVariable.dis);
			break;
		case 4:
			LED_Data(functionPara, ('A' - 0x37) * 16 + 11, ('B' - 0x37) * 16 + 12, ('C' - 0x37) * 16 + 13);
			
	}	
}


/*-------------------TFT内聚------------------*/ 
//@param type 在范围1-20时表示"A"TFT标识物,在大于 20 时表示"B"TFT标识物 
void _ZigbeeBiaozhiwu::tftAgregate(uint8_t type,uint8_t functionPara){
	switch(type){
		case 1://显示车牌;
			TFT_send_chepai(PublicVariable.platenumber);
			break; 
		case 2: // TFT计时开始
			TFT_jishi_open();
			break;
		case 3:// TFT计时结束
			TFT_jishi_close();
			break;
		case 4:// TFT计时清零
			TFT_jishi_clear();
			break;
		case 5://图片自动跳转;不指定图片"TFT_A"标识物自动翻转 
			TFT_picture(0x01,functionPara);
			break;
		case 6://指定跳转到那张图片;@functionPara :指定跳转那张图片,指定显示图片在 0x01 - 0x20 之间
			TFT_picture(0x00,functionPara);
			break;
		case 7:// TFT的HEX模式显示
			TFT_hex(('A' - 0x37) * 16 + 1, ('B' - 0x37) * 16 + 2, ('C' - 0x37) * 16 + 3);
			break;
		case 8://25显示为十进制25对应的十六进制，即显示19
			TFT_juli(PublicVariable.dis);
			break;
		
		case 21://显示车牌; 
			B_TFT_send_chepai(PublicVariable.platenumber);			
			break;
		case 22:
			B_TFT_jishi_open();
			break;
		case 23:
			B_TFT_jishi_close();
			break;
		case 24:
			B_TFT_jishi_clear();
			break;
		case 25://图片自动跳转;不指定图片"TFT_B"标识物自动翻转 
			B_TFT_picture(0x01,functionPara);
			break;
		case 26://定跳转到那张图片;@functionPara :指定跳转那张图片,指定显示图片在 0x01 - 0x20 之间
			B_TFT_picture(0x00,functionPara);
			break;
		case 27://使用HEX模式 
			B_TFT_hex(('A' - 0x37) * 16 + 1, ('B' - 0x37) * 16 + 2, ('C' - 0x37) * 16 + 3);
			break;
		case 28://使用PublicVariable.dis,在TFT中显示距离 
			B_TFT_juli(PublicVariable.dis);
		
			
	}
}
/*-------------------------道闸内聚--------------------------*/
/***************************************************************
** 功能：     打开道闸
** 参数：	    无
** 返回值：   无
** 说明：     主车通过zigbee控制道闸开启
****************************************************************/
void _ZigbeeBiaozhiwu:: daozha_open() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x03;
	send_zigbee[2]=0x01;
	send_zigbee[3]=0x01;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}
/**
*请求返回道闸是否打开
*/
void _ZigbeeBiaozhiwu:: requestDaoZha() {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x03;
	send_zigbee[2]=0x20;
	send_zigbee[3]=0x01;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
}


/***************************************************************
** 功能：     向道闸标志物发送车牌
** 参数：	    车牌6位的ASCll值
** 返回值：   无
** 说明：     主车通过zigbee向道闸发送车牌信息
****************************************************************/
void _ZigbeeBiaozhiwu:: gateSendPlateOpen(char *chepai) {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x03;
	send_zigbee[2]=0x10;
	send_zigbee[3]=chepai[0];
	send_zigbee[4]=chepai[1];
	send_zigbee[5]=chepai[2];
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(500);

	send_zigbee[0]=0x55;
	send_zigbee[1]=0x03;
	send_zigbee[2]=0x11;
	send_zigbee[3]=chepai[3];
	send_zigbee[4]=chepai[4];
	send_zigbee[5]=chepai[5];
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;
	send_zigbee[7]=0xbb;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
//	gateRequst();
}
/**
  请求返回道闸是否打开, 可跳出
  打开:@PublicVariable.daozha_count 不为 0 
*/

void _ZigbeeBiaozhiwu:: gateRequst()
{
	//识别成功 0x05 就不再执行if内 
  if (PublicVariable.stop_flag != 0x05)
  {
    if (PublicVariable.daozha_count < 5)
    {
      ZigbeeBiaozhiwu.daozha_open();
      delay(100);
      ZigbeeBiaozhiwu.requestDaoZha();
      PublicVariable.daozha_count++;
      yanshi(6);
      PublicVariable.index--;
    }
    else
    {
      PublicVariable.daozha_count = 0;
      PublicVariable.stop_flag = 0;
    }
  }
  else
  {
    PublicVariable.daozha_count = 0;
    PublicVariable.stop_flag = 0;
  }
  
}
/**
*主车控制道闸
*参数kaiguan,0x01为打开道闸，0x02为关闭道闸
*/
void _ZigbeeBiaozhiwu:: gateOpenAClose(u8 kaiguan) {
	send_zigbee[0]=0x55;
	send_zigbee[1]=0x03;
	send_zigbee[2]=0x01;
	send_zigbee[3]=kaiguan;
	send_zigbee[4]=0x00;
	send_zigbee[5]=0x00;
	send_zigbee[6]=(send_zigbee[2]+send_zigbee[3]+send_zigbee[4]+send_zigbee[5])%256;;
	send_zigbee[7]=0xBB;
	delayMs(1);
	ExtSRAMInterface.ExMem_Write_Bytes(0x6008, send_zigbee, 8);
	delayMs(100);
	gateRequst();
}
//道闸内聚
void _ZigbeeBiaozhiwu::gateAgregate(uint8_t type,uint8_t functionPara){
	switch(type){
		case 1://开启道闸 
			gateOpenAClose(0x01);
			break;
		case 2://关闭道闸 
			gateOpenAClose(0x02);
			break;
		case 3://获得道闸状态 
			gateRequst(); 
			break;
		case 4://打开道闸; 通过 PublicVariable.platenumber 变量 
			gateSendPlateOpen(PublicVariable.platenumber);
			break;
	}
}


/*---------------------无线充电-----------------*/ 
void _ZigbeeBiaozhiwu:: wirelessAgregate(uint8_t type,uint8_t functionPara){
	switch(type){
		case 1://无线充电开启 
			Wireless_charging_open();
			break;
		case 2://关闭充电 
			Wireless_charging_close();
			break;
	
	}
}

/*-------------识别语音---------------*/
//识别并复读 
void _ZigbeeBiaozhiwu:: speechDisc()
{
  uint8_t sph_id = 0;
  SYN7318.Start_ASR_send(4);
  delay(200);
  ExtSRAMInterface.ExMem_Write_Bytes(0x6008, Command.command33, 8);
  sph_id = SYN7318.Start_ASR_rec(true);
  switch (sph_id)
  {
    Serial.print(SYN7318.Start_ASR_rec(true));
  case 0x02:
    SYN7318.VSPTest(str[0], 1);
    break;
  case 0x03:
    SYN7318.VSPTest(str[1], 1);
    break;
  case 0x04:
    SYN7318.VSPTest(str[2], 1);
    break;
  case 0x05:
    SYN7318.VSPTest(str[3], 1);
    break;
  case 0x06:
    SYN7318.VSPTest(str[4], 1);
    break;
  default:
    SYN7318.VSPTest(str[10], 1);
    break;
  }
  PublicVariable.trm_buf[2] = sph_id;
  ExtSRAMInterface.ExMem_Write_Bytes(0x6008, PublicVariable.trm_buf, 8);
}

/*-------------------超声波------------------------*/
void _ZigbeeBiaozhiwu:: ultrasonic()
{
  PublicVariable.dis = (uint8_t)Ultrasonic.Ranging(1);
}

/*----------------给主车发送命令------------------*/
void _ZigbeeBiaozhiwu:: sendToSTM32(uint8_t protocol)
{
  PublicVariable.sendflag = 10;
  PublicVariable.zigbee_back[2] = protocol;
  ExtSRAMInterface.ExMem_Write_Bytes(0x6180, PublicVariable.zigbee_back, 16);
}
//延时 参数10为1秒
void _ZigbeeBiaozhiwu::yanshi(int a)
{
   PublicVariable.yanshi_check_times = millis() + a * 100;
}
