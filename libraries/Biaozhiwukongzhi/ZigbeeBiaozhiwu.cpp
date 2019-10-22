/**
*	�ӳ�ͨ��zigbee���Ƶı�־�����еĺ���
*	2019.05.12	������
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
*�ӳ��������ܽ�ͨ��
*����zhu,0x01Ϊ����ʶ��ģʽ��0x02Ϊ����ȷ��ʶ����
*����fu,��zhuΪ0x01�������ã���zhuΪ0x02,fu0x01Ϊ��ƣ�0x02Ϊ�̵ƣ�0x03Ϊ�Ƶ�
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
** ���ܣ�   ���峵�⵽���һ��
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�   ���峵�⵽��ڶ���
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�   ���峵�⵽�������
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�   ���峵�⵽����Ĳ�
** ������	  �޲���
** ����ֵ�� ��
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
*�������峵�⵽��ĳһ�㣬����cengshuΪ���Ƴ�����Ҫ����Ĳ���
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
** ���ܣ�   ���󷵻س���λ�ڵڼ���
** ������	 head  0x0dΪ��־��A    0x05Ϊ��־λB 
** ����ֵ�� ��
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
** ���ܣ�   ���󷵻�ǰ������״̬
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�    ���߳���־�￪��
** ������	 ��
** ����ֵ��  ��
** ˵����    ����ͨ��zigbee�������߳���־�￪��
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
** ���ܣ�    ���߳���־��ر�
** ������	 ��
** ����ֵ��  ��
** ˵����    ����ͨ��zigbee�������߳���־��ر�
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
** ���ܣ�     LED��ʾ��־�￪ʼ��ʱ
** ������	  ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����LED��ʾ��־��ļ�ʱ���ܿ���
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
** ���ܣ�     LED��ʾ��־���ʱ����
** ������	  ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����LED��ʾ��־��ļ�ʱ���ܹر�
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
** ���ܣ�     LED��ʾ��־���ʱ����
** ������	  ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����LED��ʾ��־��ļ�ʱ����
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
*LED�����ʱģʽ������functionΪָ����ʱģʽ�Ĺ��ܣ�0x00�رգ�0x01�򿪣�0x02����
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
** ���ܣ�     LED��ʾ��־��ڶ�������
** ������	  ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����LED��ʾ��־��ĵڶ�������
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
** ���ܣ�     LED��ʾ��־��ڶ�����ʾ����
** ������	  ��Ҫ��ʾ��ֵ
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����LED��ʾ��־��ĵڶ�����ʾ����
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
*LED��һ�ź͵ڶ���д������
*����paishuΪҪ�ڵڼ���д�����ݣ�1Ϊ1�ţ�2Ϊ2��
*����one��two��threeΪҪд�������
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
** ���ܣ�     ��TFT��־�﷢�ͳ���
** ������	    ����6λ��ASCllֵ
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee��TFT���ͳ�����Ϣ
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
** ���ܣ�     TFT��־���ʱ���ܿ�ʼ
** ������	    ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����TFT��־��ļ�ʱ���ܿ���
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
** ���ܣ�     TFT��־���ʱ���ܽ���
** ������	    ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����TFT��־��ļ�ʱ���ܽ���
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
** ���ܣ�     TFT��־���ʱ��������
** ������	    ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����TFT��־��ļ�ʱ��������
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
*TFTͼƬ��ʾģʽ������Ϊ��ָ��1�͸�ָ��2
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
*TFTHEX��ʾģʽ,����ΪҪ��ʾ��3Ϊ����
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
*TFTHEX��ʾ����ģʽ,����ΪҪ��ʾ�ľ���İ�λ��ʮλ��λ
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


/********************** ��־��B *************************/ 

/**
*�ӳ��������ܽ�ͨ��
*����zhu,0x01Ϊ����ʶ��ģʽ��0x02Ϊ����ȷ��ʶ����
*����fu,��zhuΪ0x01�������ã���zhuΪ0x02,fu0x01Ϊ��ƣ�0x02Ϊ�̵ƣ�0x03Ϊ�Ƶ�
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
** ���ܣ�   ���峵�⵽���һ��
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�   ���峵�⵽��ڶ���
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�   ���峵�⵽�������
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�   ���峵�⵽����Ĳ�
** ������	  �޲���
** ����ֵ�� ��
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
*�������峵�⵽��ĳһ�㣬����cengshuΪ���Ƴ�����Ҫ����Ĳ���
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
** ���ܣ�   ���󷵻س���λ�ڵڼ���
** ������	 head  0x0dΪ��־��A    0x05Ϊ��־λB 
** ����ֵ�� ��
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
** ���ܣ�   ���󷵻�ǰ������״̬
** ������	  �޲���
** ����ֵ�� ��
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
** ���ܣ�     ��TFT��־�﷢�ͳ���
** ������	    ����6λ��ASCllֵ
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee��TFT���ͳ�����Ϣ
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
** ���ܣ�     TFT��־���ʱ���ܿ�ʼ
** ������	    ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����TFT��־��ļ�ʱ���ܿ���
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
** ���ܣ�     TFT��־���ʱ���ܽ���
** ������	    ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����TFT��־��ļ�ʱ���ܽ���
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
** ���ܣ�     TFT��־���ʱ��������
** ������	    ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee����TFT��־��ļ�ʱ��������
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
*TFTͼƬ��ʾģʽ������Ϊ��ָ��1�͸�ָ��2
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
*TFTHEX��ʾģʽ,����ΪҪ��ʾ��3Ϊ����
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
*TFTHEX��ʾ����ģʽ,����ΪҪ��ʾ�ľ���İ�λ��ʮλ��λ
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
*����ʶ��ı�ŷ��͸������ն� 
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


/*---------------------�йس���------------------*/ 
//���Ƴ��⵽��Ŀ���
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
   ��ȡAB���⵱ǰ����
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
      PublicVariable.current_garage = 1; //��һ��
      break;
    case 0x0A:
      PublicVariable.current_garage = 2; //�ڶ���
      break;
    case 0x0B:
      PublicVariable.current_garage = 3; //������
      break;
    case 0x0C:
      PublicVariable.current_garage = 4; //���Ĳ�
      break;
    }
    PublicVariable.stop_flag = 0;
    PublicVariable.daozha_count = 0;
  }
}

/*----------------�����ھ�---------------*/
//@type ������1-10֮���ʾ"A"����,����10��ʾ"B"���� 
void _ZigbeeBiaozhiwu::cheKu(uint8_t type,uint8_t functionPara){
		switch(type){
			case 1:
				litiGarage(functionPara);
				break;
			case 2:
				requestLocation();		//��õ�ǰ����λ�� 
				break;
			case 3:
				chekuCtl(functionPara, 'A');//�жϵ�ǰ�����Ƿ���ָ���㣬���ڵĻ��͵���ָ����
				break;
			case 4:
				getGarageLocation('A');	//���A���⵱ǰλ�� 
				break;
			case 11:
				B_litiGarage(functionPara);
				break;
			case 12:
				requestLocation();
				break;
			case 13:
				chekuCtl(functionPara, 'B');	//�жϵ�ǰ�����Ƿ���ָ���㣬���ڵĻ��͵���ָ����
				break;
			case 14:
				getGarageLocation('B');
				break;
				
		
				
		}
};

/*-------------------Led �ھ�--------------------*/
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


/*-------------------TFT�ھ�------------------*/ 
//@param type �ڷ�Χ1-20ʱ��ʾ"A"TFT��ʶ��,�ڴ��� 20 ʱ��ʾ"B"TFT��ʶ�� 
void _ZigbeeBiaozhiwu::tftAgregate(uint8_t type,uint8_t functionPara){
	switch(type){
		case 1://��ʾ����;
			TFT_send_chepai(PublicVariable.platenumber);
			break; 
		case 2: // TFT��ʱ��ʼ
			TFT_jishi_open();
			break;
		case 3:// TFT��ʱ����
			TFT_jishi_close();
			break;
		case 4:// TFT��ʱ����
			TFT_jishi_clear();
			break;
		case 5://ͼƬ�Զ���ת;��ָ��ͼƬ"TFT_A"��ʶ���Զ���ת 
			TFT_picture(0x01,functionPara);
			break;
		case 6://ָ����ת������ͼƬ;@functionPara :ָ����ת����ͼƬ,ָ����ʾͼƬ�� 0x01 - 0x20 ֮��
			TFT_picture(0x00,functionPara);
			break;
		case 7:// TFT��HEXģʽ��ʾ
			TFT_hex(('A' - 0x37) * 16 + 1, ('B' - 0x37) * 16 + 2, ('C' - 0x37) * 16 + 3);
			break;
		case 8://25��ʾΪʮ����25��Ӧ��ʮ�����ƣ�����ʾ19
			TFT_juli(PublicVariable.dis);
			break;
		
		case 21://��ʾ����; 
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
		case 25://ͼƬ�Զ���ת;��ָ��ͼƬ"TFT_B"��ʶ���Զ���ת 
			B_TFT_picture(0x01,functionPara);
			break;
		case 26://����ת������ͼƬ;@functionPara :ָ����ת����ͼƬ,ָ����ʾͼƬ�� 0x01 - 0x20 ֮��
			B_TFT_picture(0x00,functionPara);
			break;
		case 27://ʹ��HEXģʽ 
			B_TFT_hex(('A' - 0x37) * 16 + 1, ('B' - 0x37) * 16 + 2, ('C' - 0x37) * 16 + 3);
			break;
		case 28://ʹ��PublicVariable.dis,��TFT����ʾ���� 
			B_TFT_juli(PublicVariable.dis);
		
			
	}
}
/*-------------------------��բ�ھ�--------------------------*/
/***************************************************************
** ���ܣ�     �򿪵�բ
** ������	    ��
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee���Ƶ�բ����
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
*���󷵻ص�բ�Ƿ��
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
** ���ܣ�     ���բ��־�﷢�ͳ���
** ������	    ����6λ��ASCllֵ
** ����ֵ��   ��
** ˵����     ����ͨ��zigbee���բ���ͳ�����Ϣ
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
  ���󷵻ص�բ�Ƿ��, ������
  ��:@PublicVariable.daozha_count ��Ϊ 0 
*/

void _ZigbeeBiaozhiwu:: gateRequst()
{
	//ʶ��ɹ� 0x05 �Ͳ���ִ��if�� 
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
*�������Ƶ�բ
*����kaiguan,0x01Ϊ�򿪵�բ��0x02Ϊ�رյ�բ
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
//��բ�ھ�
void _ZigbeeBiaozhiwu::gateAgregate(uint8_t type,uint8_t functionPara){
	switch(type){
		case 1://������բ 
			gateOpenAClose(0x01);
			break;
		case 2://�رյ�բ 
			gateOpenAClose(0x02);
			break;
		case 3://��õ�բ״̬ 
			gateRequst(); 
			break;
		case 4://�򿪵�բ; ͨ�� PublicVariable.platenumber ���� 
			gateSendPlateOpen(PublicVariable.platenumber);
			break;
	}
}


/*---------------------���߳��-----------------*/ 
void _ZigbeeBiaozhiwu:: wirelessAgregate(uint8_t type,uint8_t functionPara){
	switch(type){
		case 1://���߳�翪�� 
			Wireless_charging_open();
			break;
		case 2://�رճ�� 
			Wireless_charging_close();
			break;
	
	}
}

/*-------------ʶ������---------------*/
//ʶ�𲢸��� 
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

/*-------------------������------------------------*/
void _ZigbeeBiaozhiwu:: ultrasonic()
{
  PublicVariable.dis = (uint8_t)Ultrasonic.Ranging(1);
}

/*----------------��������������------------------*/
void _ZigbeeBiaozhiwu:: sendToSTM32(uint8_t protocol)
{
  PublicVariable.sendflag = 10;
  PublicVariable.zigbee_back[2] = protocol;
  ExtSRAMInterface.ExMem_Write_Bytes(0x6180, PublicVariable.zigbee_back, 16);
}
//��ʱ ����10Ϊ1��
void _ZigbeeBiaozhiwu::yanshi(int a)
{
   PublicVariable.yanshi_check_times = millis() + a * 100;
}
