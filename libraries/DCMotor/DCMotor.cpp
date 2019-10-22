#include "DCMotor.h"
#include <Command.h>
#include "wiring_private.h"
#include <ExtSRAMInterface.h>
#include <Metro.h>


_DCMotor DCMotor;
Metro DCMotorMetro(20);

_DCMotor::_DCMotor() {
	ExtSRAMInterface.Initialization();
}

_DCMotor::~_DCMotor() {
}


/************************************************************************************************************
【函 数 名】：	Initialization	直流电机初始化
【参数说明】：	fHz		：		初始化PWM输出频率，单位：Hz
【返 回 值】：	无
【简    例】：	Initialization(8000);
************************************************************************************************************/
void _DCMotor::Initialization(uint32_t fHz) {
	/*ExtSRAMInterface.Initialization();*/
	pinMode(L_CONTROL_PIN, OUTPUT);
	pinMode(R_CONTROL_PIN, OUTPUT);


	//RFSpeed = 0;
	//RBSpeed = 0;
	//LFSpeed = 0;
	//LBSpeed = 0;

	pinMode(R_F_M_PIN, OUTPUT);
	pinMode(R_B_M_PIN, OUTPUT);
	pinMode(L_F_M_PIN, OUTPUT);
	pinMode(L_B_M_PIN, OUTPUT);

	TCCR4A = 0x00;
	TCCR4B = 0x00;
	TCCR3A = 0x00;
	TCCR3B = 0x00;

	//选择工作模式,模式14--fast PWM
	TCCR4A |= _BV(WGM41);
	TCCR4B |= _BV(WGM42) | _BV(WGM43);
	TCCR3A |= _BV(WGM31);
	TCCR3B |= _BV(WGM32) | _BV(WGM33);

	//设置PWM波的频率
	MotorFrequency(fHz);

	//设置PWM波的占空比
	//SpeedCtr(0, 0);
	Stop();
	//MotorSpeed(MOVE_RUNMODE_STOP,_Fspeed, _Bspeed);
	//LeftMotorSpeed(_Fspeed, _Bspeed);

	//设置输出通道
	//TCCR4A |= _BV(COM4C1) | _BV(COM4B1) | _BV(COM4C0) | _BV(COM4B0);
	//TCCR3A |= _BV(COM3C1) | _BV(COM3B1) | _BV(COM3C0) | _BV(COM3B0);
	TCCR4A |= _BV(COM4C1) | _BV(COM4B1);
	TCCR3A |= _BV(COM3C1) | _BV(COM3B1);

	ParameterInit();
}

void _DCMotor::ParameterInit(void) {
	for (uint8_t i = 0; i < 101; i++) {	//占空比初始化
		speed[i] = fHz * i / 100;
	}
}

void _DCMotor::SpeedSetOne(int16_t s, uint8_t *c1, uint8_t *c2) {
	uint8_t t;
	t = (s >= 0) ? s : s*(-1);
	if (t > 100)
		t = 100;
	if (t < 5)
		t = 5;
	if (s == 0) {
		*c1 = speed[100];		//100;
		*c2 = speed[100];		//100;
	} else if (s > 0) {
		*c1 = speed[t];
		*c2 = speed[0];
	} else {
		*c1 = speed[0];
		*c2 = speed[t];
	}
}

void _DCMotor::SpeedCtr(int16_t L_speed, int16_t R_speed) {
	uint8_t ocr3b, ocr3c, ocr4b, ocr4c;

	SpeedSetOne(L_speed, &ocr4c, &ocr4b);
	SpeedSetOne(R_speed, &ocr3b, &ocr3c);

	(ocr3b == 0) ? (TCCR3A |= _BV(COM3B0), ocr3b = fHz) : (TCCR3A &= ~_BV(COM3B0));
	(ocr3c == 0) ? (TCCR3A |= _BV(COM3C0), ocr3c = fHz) : (TCCR3A &= ~_BV(COM3C0));
	(ocr4b == 0) ? (TCCR4A |= _BV(COM4B0), ocr4b = fHz) : (TCCR4A &= ~_BV(COM4B0));
	(ocr4c == 0) ? (TCCR4A |= _BV(COM4C0), ocr4c = fHz) : (TCCR4A &= ~_BV(COM4C0));

	OCR4C = ocr4c;
	OCR4B = ocr4b;
	OCR3C = ocr3c;
	OCR3B = ocr3b;
}

bool _DCMotor::ClearCodeDisc(void) {
	uint16_t distance;
	unsigned long t;
	Command.Judgment(Command.command01);
	for (size_t i = 0; i < 8; i++) {
		ExtSRAMInterface.ExMem_JudgeWrite(WRITEADDRESS + i, Command.command01[i]);
	}
//	t = millis();
	DCMotorMetro.interval(20);
	for (size_t i = 0; i < 5; i++) {
		if (DCMotorMetro.check() == 1) {
			distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
			if (distance == 0x0000) {
				return false;
			}
		}
	}
	return true;
}
/************************************************************************************************************
小车动作的相关函数
************************************************************************************************************/
/************************************************************************************************************
【函 数 名】：  Go		小车前进函数
【参数说明】：	speed	：设置速度
distance: 设置前进的距离
【返 回 值】：	无
【简    例】：	Go(70);	小车动作：前进，前进速度：70
************************************************************************************************************/
void _DCMotor::Go(uint8_t speed) {
	SpeedCtr(speed, speed);
	StartUp();
}
uint16_t _DCMotor::Go(uint8_t speed, uint16_t _distance) {
	unsigned long t;
	uint16_t distance;
	while (ClearCodeDisc()) {
		//DCMotor.SpeedCtr(80, 80);
		//DCMotor.StartUp();
		//delay(20);
		//DCMotor.Stop();
	}
	SpeedCtr(speed, speed);
	StartUp();

	t = millis();
	do {
		distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
		if ((65516 > distance) && (distance > 20)) {
			if ((distance >= _distance) || ((millis() - t) >= 30000))
				//if (((distance >= _distance) && ((millis() - t) < 10000)) || (ExtSRAMInterface.ExMem_Read(0x6100) == 0x55))
				//if ((65535 - distance >= _distance) || ((millis() - t) >= 10000))
			{
				Stop();
				//ShutDown();
				delay(50);
				distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
				break;
			}
		}
		delay(1);
	} while (true);
	return distance;
	//return (65535 - distance);
}

/************************************************************************************************************
【函 数 名】：  Back		小车后退函数
【参数说明】：	speed	:	设置速度
distance:	设置后退的距离
【返 回 值】：	无
【简    例】：	Back(70);	小车动作：后退，后退速度：70
************************************************************************************************************/
void _DCMotor::Back(uint8_t speed) {
	SpeedCtr(speed*(-1), speed*(-1));
	StartUp();
}
uint16_t _DCMotor::Back(uint8_t speed, uint16_t _distance) {
	unsigned long t;
	uint16_t distance;

	while (ClearCodeDisc()) {
		//DCMotor.SpeedCtr(-80, -80);
		//DCMotor.StartUp();
		//delay(20);
		//DCMotor.Stop();
	}
	Back(speed);
	t = millis();
	do {
		distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
		if ((65516 > distance) && (distance > 20)) {
			//if (((65535 - distance) >= _distance) || (ExtSRAMInterface.ExMem_Read(0x6100) == 0x55))
			if (((65536 - distance) >= _distance) || ((millis() - t) > 30000)) {
				Stop();
				//Serial.print(distance, 10);
				//Serial.print("   ");
				//Serial.println(ExtSRAMInterface.ExMem_Read(0x6100), 16);
				delay(50);
				distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
				break;
			}
		}
		delay(10);
	} while (true);
	return (65536 - distance);
}

/************************************************************************************************************
【函 数 名】：  TurnLeft	小车左转函数,Lspeed <= Rspeed
【参数说明】：	Lspeed	：	设置左轮速度
Rspeed	：	设置右轮速度
【返 回 值】：	无
【简    例】：	TurnLeft(70);	小车动作：左转，左转速度：70
************************************************************************************************************/
void _DCMotor::TurnLeft(int8_t Lspeed, int8_t Rspeed) {
	SpeedCtr(Lspeed*(-1), Rspeed);
	StartUp();
}
void _DCMotor::TurnLeft(int8_t speed) {
	uint8_t tgd, tp;
	unsigned long t;
	uint8_t  trackval;
	while (ClearCodeDisc()) {
		//DCMotor.SpeedCtr(-80, 80);
		//DCMotor.StartUp();
		//delay(20);
		//DCMotor.Stop();
	}
	SpeedCtr(speed*(-1), speed);
	StartUp();
	//TurnLeft(speed);
	do {
		tgd = ExtSRAMInterface.ExMem_Read(BASEADDRESS + TRACKOFFSET);
		tp = SearchBit(1,tgd);
		if ((tp <= 0x04) )	break;//|| (ExtSRAMInterface.ExMem_Read(0x6100) == 0x55)
	} while (true);

	t = millis();
	do {
		trackval = ExtSRAMInterface.ExMem_Read(BASEADDRESS + TRACKOFFSET);
		if (((!(trackval & 0x10)) || ((millis() - t) > 10000)) )//|| (ExtSRAMInterface.ExMem_Read(0x6100) == 0x55)
			//if ((SearchBit(1, tgd) <= 0x10) || ((millis() - t) > 10000))
		{
			Stop();
			//ShutDown();
			break;
		}
	} while (true);
}


/************************************************************************************************************
【函 数 名】：  TurnRight	小车右转函数,Rspeed <= Lspeed
【参数说明】：	Lspeed	：	设置左轮速度
Rspeed	：	设置右轮速度
【返 回 值】：	无
【简    例】：	TurnRight(70);	小车动作：右转，右转速度：70
************************************************************************************************************/
void _DCMotor::TurnRight(int8_t Lspeed, int8_t Rspeed) {
	SpeedCtr(Lspeed, Rspeed*(-1));
	StartUp();
}
void _DCMotor::TurnRight(int8_t speed) {
	uint8_t tgd, tp;
	unsigned long t;
	uint8_t  trackval;
	while (ClearCodeDisc()) {
		//DCMotor.SpeedCtr(80, -80);
		//DCMotor.StartUp();
		//delay(20);
		//DCMotor.Stop();
	}

	SpeedCtr(speed, speed*(-1));
	StartUp();
	//TurnRight(speed);
	do {
		tgd = ExtSRAMInterface.ExMem_Read(BASEADDRESS + TRACKOFFSET);
		tp = SearchBit(0,tgd);
		//Serial.println("start TurnRight!");
		//Serial.println(tp,16);
		if ((tp >= 0x20) )	break;// || (ExtSRAMInterface.ExMem_Read(0x6100) == 0x55)
	} while (true);

	t = millis();
	do {
		trackval = ExtSRAMInterface.ExMem_Read(BASEADDRESS + TRACKOFFSET);

		//if ((SearchBit(0, trackval) >= 0x08) || ((millis() - t) > 10000))
		if (((!(trackval & 0x08)) || ((millis() - t) > 10000)) ) {//|| (ExtSRAMInterface.ExMem_Read(0x6100) == 0x55)
			Stop();
			//ShutDown();
			break;
		}
		//Serial.println(trackval, 16);
	} while (true);
}

void _DCMotor::TurnLeftToRight(void) {

}
void _DCMotor::TurnRightToLeft(void) {

}
/************************************************************************************************************
【函 数 名】：  Stop	小车停止函数
【参数说明】：	无
【返 回 值】：	无
【简    例】：	Stop();	小车动作：停止
************************************************************************************************************/
void _DCMotor::Stop(void) {
	/*这两段代码都有电机停止功能，但停止的效果不一样*/

	/**********电机不锁死******************/
	//PORTE &= ~_BV(PE3);
	//PORTH &= ~_BV(PH3);
	//SpeedCtr(0, 0);
	/***********END**************************/

	//电机瞬间锁死
	SpeedCtr(0, 0);
	PORTE |= _BV(PE3);
	PORTH |= _BV(PH3);
	/**********END************/
}

/************************************************************************************************************
【函 数 名】：  StartUp		小车启动函数
【参数说明】：	无
【返 回 值】：	无
【简    例】：	StartUp();	小车动作：启动
************************************************************************************************************/
void _DCMotor::StartUp(void) {
	PORTE |= _BV(PE3);
	PORTH |= _BV(PH3);
	//digitalWrite(L_CONTROL_PIN, HIGH);
	//digitalWrite(R_CONTROL_PIN, HIGH);
}

/************************************************************************************************************
【函 数 名】：  ShutDown	小车关闭函数
【参数说明】：	无
【返 回 值】：	无
【简    例】：	ShutDown();	小车动作：关闭
************************************************************************************************************/
void _DCMotor::ShutDown(void) {
	SpeedCtr(100, 100);
	PORTE |= _BV(PE3);
	PORTH |= _BV(PH3);
}
/*************************************************************END***********************************************/

void _DCMotor::CarTrack(uint8_t Car_Spend) {
	unsigned long t;
	uint8_t mode, _mode = 10;
	uint8_t tp;
	uint8_t gd, ogd, tgd;
	uint8_t LSpeed, RSpeed;
	uint16_t count = 0;
	uint8_t  firstbit[8];
	ogd = 0xff;
	StartUp();
	while (true) {
		tp = 0;
		firstbit[0] = 0;
		//tgd = ExtSRAMInterface.ExMem_Read(TRACK_ADDR);
		//if (ogd != tgd)
		//	gd = ogd & tgd;
		//else
		//	gd = tgd;红外
		gd = ExtSRAMInterface.ExMem_Read(TRACK_ADDR); // 获取后八位 循迹灯的状态
//		for (size_t i = 0x01; i<0x100; i <<= 1) {
//			if ((gd & i) == 0) {
//				firstbit[tp++] = uint8_t(i);
//			}
//		}
		//(ExtSRAMInterface.ExMem_Read(0x6100) == 0x55)

		if (gd==0x00||(gd & 0x81) ==0 || (gd & 0x03) == 0||(gd & 0xC0) == 0) {	//(tp > 0x03) || 	/*循迹灯灭的个数≥5表示全灭*/
			//ShutDown();
			Stop();
			break;
		} else {
//#if 0
			weitiao(gd,Car_Spend);
//			switch (firstbit[0]) {
//				case 0x00:
//					SpeedCtr(Car_Spend, Car_Spend);
//					break;
//				case 0x01:
//					SpeedCtr(Car_Spend + 60, Car_Spend - 120);
//					break;
//				case 0x02:
//					SpeedCtr(Car_Spend + 40, Car_Spend - 70);
//					break;
//				case 0x04:
//					SpeedCtr(Car_Spend + 30, Car_Spend - 30);
//					break;
//				case 0x08:
//					SpeedCtr(Car_Spend, Car_Spend);
//					break;
//				case 0x10:
//					SpeedCtr(Car_Spend - 30, Car_Spend + 30);
//					break;
//				case 0x20:
//					SpeedCtr(Car_Spend - 70, Car_Spend + 40);
//					break;
//				case 0x40:
//					SpeedCtr(Car_Spend - 120, Car_Spend + 60);
//					break;
//				case 0x80:
//					SpeedCtr(Car_Spend - 120, Car_Spend + 60);
//					break;
//			}
			//if ((firstbit[0] == 0x00) || (firstbit[0] == 0x08))
			//{
			//	//DCMotor.Go(Car_Spend);
			//	SpeedCtr(Car_Spend, Car_Spend);
			//}
			//else if (mode < 4)
			//{
			//	LSpeed = (Car_Spend + 60) - (mode * 10);
			//	RSpeed = (Car_Spend - 120) + (mode * 30);
			//	DCMotor.SpeedCtr(LSpeed, RSpeed);
			//}
			//else
			//{
			//	RSpeed = Car_Spend + ((mode - 1) * 10);
			//	LSpeed = (Car_Spend - ((mode - 3) * 30));
			//	DCMotor.SpeedCtr(LSpeed, RSpeed);
			//}
//#else
//			DCMotor.Go(Car_Spend);
//#endif
		}
	}
}

//////////////迅即前进，到达一定的码盘值后停止///////////////// 

void _DCMotor::CarTrack_stop(uint8_t Car_Spend,uint16_t mp) {
	unsigned long t;
	uint8_t mode, _mode = 10;
	uint8_t tp;
	uint8_t gd, ogd, tgd;
	uint8_t LSpeed, RSpeed;
	uint16_t count = 0;
	uint8_t  firstbit[8];
	ogd = 0xff;
	while (ClearCodeDisc()) {
		//DCMotor.SpeedCtr(80, 80);
		//DCMotor.StartUp();
		//delay(20);
		//DCMotor.Stop();
	}
	StartUp();
	while (true) {
		tp = 0;
		firstbit[0] = 0;
		uint16_t distance;
		distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
		gd = ExtSRAMInterface.ExMem_Read(TRACK_ADDR); // 获取后八位 循迹灯的状态
//		for (size_t i = 0x01; i<0x100; i <<= 1) {
//			if ((gd & i) == 0) {
//				firstbit[tp++] = uint8_t(i);
//			}
//		}
		//(ExtSRAMInterface.ExMem_Read(0x6100) == 0x55)

		if (distance>=mp) {		/*循及到规定的吗盘值之后停止*/
			//ShutDown();
			Stop();
			distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
			break;
		} else {
			weitiao(gd,Car_Spend);
//			switch (firstbit[0]) {
//
//				case 0x00:
//					SpeedCtr(Car_Spend, Car_Spend);
//					break;
//				case 0x01:
//					SpeedCtr(Car_Spend + 60, Car_Spend - 120);
//					break;
//				case 0x02:
//					SpeedCtr(Car_Spend + 40, Car_Spend - 70);
//					break;
//				case 0x04:
//					SpeedCtr(Car_Spend + 30, Car_Spend - 30);
//					break;
//				case 0x08:
//					SpeedCtr(Car_Spend, Car_Spend);
//					break;
//				case 0x10:
//					SpeedCtr(Car_Spend - 30, Car_Spend + 30);
//					break;
//				case 0x20:
//					SpeedCtr(Car_Spend - 70, Car_Spend + 40);
//					break;
//				case 0x40:
//					SpeedCtr(Car_Spend - 120, Car_Spend + 60);
//					break;
//				case 0x80:
//					SpeedCtr(Car_Spend - 120, Car_Spend + 60);
//					break;
//			}

		}
	}
}




uint8_t Line_Flag=0;
void _DCMotor::CarTrack_2(uint8_t Car_Spend) {
	unsigned long t;
	uint8_t mode, _mode = 10;
	uint8_t tp;
	uint8_t gd, ogd, tgd;
	uint8_t LSpeed, RSpeed;
	uint16_t count = 0;
	uint8_t firstbit[8];
	ogd = 0xff;
	StartUp();
	while (true) {
		tp = 0;
		firstbit[0] = 0;

		gd = ExtSRAMInterface.ExMem_Read(TRACK_ADDR); // 获取后八位 循迹灯的状态

		if (gd==0x00 ||(gd & 0xC0) == 0||(gd & 0x03) == 0 ) { /*循迹灯灭全灭或最左侧2个灯灭 或最右侧2灯灭*/
			//ShutDown();
			Stop();
			break;
		} else {
			weitiao(gd,Car_Spend);
//			if (gd == 0XE7 ) { //1、中间3/4传感器检测到黑线，全速运行
//				SpeedCtr(Car_Spend, Car_Spend);
//			}
//
//			if (Line_Flag != 2) {
//
//             if (gd == 0XF7)
//               {
//               	   SpeedCtr(Car_Spend + 30, Car_Spend - 30);
//               		Line_Flag = 0;
//			   }
//				if (gd == 0XF3 || gd == 0XFB) { //2、中间4、3传感器检测到黑线，微右拐
//					SpeedCtr(Car_Spend + 60, Car_Spend - 60);
//					Line_Flag = 0;
//				} else if (gd == 0XF9 || gd == 0XFD) { //3、中间3、2传感器检测到黑线，再微右拐
//					SpeedCtr(Car_Spend + 70, Car_Spend - 70);
//					Line_Flag = 0;
//				} else if (gd == 0XFC) { //4、中间2、1传感器检测到黑线，强右拐
//					SpeedCtr(Car_Spend + 60, Car_Spend - 90);
//					Line_Flag = 0;
//				} else if (gd == 0XFE) { //5、最右边1传感器检测到黑线，再强右拐
//					SpeedCtr(Car_Spend + 60, Car_Spend - 120);
//					Line_Flag = 1;
//				}
//			}
//			if (Line_Flag != 1) {
//				if (gd == 0XEF)
//               {
//               	   SpeedCtr(Car_Spend - 30, Car_Spend + 30);
//               		Line_Flag = 0;
//			   }
//				if (gd == 0XCF) { //6、中间6、5传感器检测到黑线，微左拐
//					SpeedCtr(Car_Spend - 60, Car_Spend + 60);
//					Line_Flag = 0;
//				} else if (gd == 0X9F || gd == 0XDF) { //7、中间7、6传感器检测到黑线，再微左拐
//					SpeedCtr(Car_Spend - 70, Car_Spend + 70);
//					Line_Flag = 0;
//				} else if (gd == 0X3F || gd == 0XBF) { //8、中间8、7传感器检测到黑线，强左拐
//					SpeedCtr(Car_Spend - 60, Car_Spend + 90);
//					Line_Flag = 0;
//				} else if (gd == 0X7F) { //9、最左8传感器检测到黑线，再强左拐
//					SpeedCtr(Car_Spend - 60, Car_Spend + 120);
//					Line_Flag = 2;
//				}
//			}
		}
	}
}

void _DCMotor::weitiao(uint8_t gd,uint8_t Car_Spend) {
	int ischange=0;
	if (gd == 0XE7) { //1、中间3/4传感器检测到黑线，全速运行
		SpeedCtr(Car_Spend, Car_Spend);
		ischange=1;
	}

	if (Line_Flag != 2) {

		if (gd == 0XF7) {
			SpeedCtr(Car_Spend + 30, Car_Spend - 30);
			Line_Flag = 0;
		    ischange=1;
		}
		if (gd == 0XF3 || gd == 0XFB) { //2、中间4、3传感器检测到黑线，微右拐
			SpeedCtr(Car_Spend + 60, Car_Spend - 60);
			Line_Flag = 0;
		    ischange=1;
		} else if (gd == 0XF9 || gd == 0XFD) { //3、中间3、2传感器检测到黑线，再微右拐
			SpeedCtr(Car_Spend + 70, Car_Spend - 70);
			Line_Flag = 0;
		    ischange=1;
		} else if (gd == 0XFC) { //4、中间2、1传感器检测到黑线，强右拐
			SpeedCtr(Car_Spend + 60, Car_Spend - 90);
			Line_Flag = 0;
		    ischange=1;
		} else if (gd == 0XFE) { //5、最右边1传感器检测到黑线，再强右拐
			SpeedCtr(Car_Spend + 60, Car_Spend - 120);
			Line_Flag = 1;
			ischange=1;
		}
		
	
	}
	if (Line_Flag != 1) {
		if (gd == 0XEF) {
			SpeedCtr(Car_Spend - 30, Car_Spend + 30);
			Line_Flag = 0;
			ischange=1;
		}
		if (gd == 0XCF) { //6、中间6、5传感器检测到黑线，微左拐
			SpeedCtr(Car_Spend - 60, Car_Spend + 60);
			Line_Flag = 0;
			ischange=1;
		} else if (gd == 0X9F || gd == 0XDF) { //7、中间7、6传感器检测到黑线，再微左拐
			SpeedCtr(Car_Spend - 70, Car_Spend + 70);
			Line_Flag = 0;
			ischange=1;
		} else if (gd == 0X3F || gd == 0XBF) { //8、中间8、7传感器检测到黑线，强左拐
			SpeedCtr(Car_Spend - 60, Car_Spend + 90);
			Line_Flag = 0;
			ischange=1;
		} else if (gd == 0X7F) { //9、最左8传感器检测到黑线，再强左拐
			SpeedCtr(Car_Spend - 60, Car_Spend + 120);
			Line_Flag = 2;
			ischange=1;
		}
	}
	
	if(ischange==0)
		SpeedCtr(Car_Spend, Car_Spend);
}

//退到路口就停止
void _DCMotor::Back_lukoustop(uint8_t speed) {
	unsigned long t;
	uint8_t gd,tp;
	uint8_t  firstbit[8];
	while (ClearCodeDisc()) {}
	Back(speed);
	do {
		firstbit[0] = 0;
		gd = ExtSRAMInterface.ExMem_Read(TRACK_ADDR); // 获取后八位 循迹灯的状态
//		for (size_t i = 0x01; i<0x100; i <<= 1) {
//			if ((gd & i) == 0) {
//				firstbit[tp++] = uint8_t(i);
//			}
//		}
		if(gd==0x00 ||(gd & 0xC0) == 0||(gd & 0x03) == 0) {
			//	if ((tp >= 0x04) || (gd & 0x99) == 0x98 || (gd & 0x99) == 0x19) {		/*循迹灯灭的个数≥5表示全灭*/
			Stop();
			break;
		}
		delay(10);
	} while (true);
}

void _DCMotor::CarTrack_DX(uint8_t Car_Spend) {
	unsigned long t;
	uint8_t mode, _mode = 10;
	uint8_t tp;
	uint8_t gd, ogd, tgd;
	uint8_t LSpeed, RSpeed;
	uint16_t count = 0;
	uint8_t  firstbit[8];
	ogd = 0xff;
	StartUp();
	while (true) {
		tp = 0;
		firstbit[0] = 0;
		int ischange=0; 
		gd = ExtSRAMInterface.ExMem_Read(TRACK_ADDR); // 获取后八位 循迹灯的状态

		if((gd&0x81)==0||(gd&0x03)==0||(gd&0xC0)==0) { //90mp4>90     &&(Roadway_mp_Get()<2000)
			Stop();
//			delay(100);
//			Back(50, 150);
//			delay(100);
//			Back_lukoustop(50);
//			delay(100);
//			Go(50, 200);
//			delay(100);
//			CarTrack(30);
			delay(100);
			Go(50, 1400);
			delay(100);
			CarTrack(40);
			return;
		} else {
			if (gd == 0XE7||gd==0xFF) { //1、中间3/4传感器检测到黑线，全速运行
				SpeedCtr(Car_Spend, Car_Spend);
				ischange=1;
			}

			if (Line_Flag != 2) {
				if (gd == 0XF7) {
					SpeedCtr(Car_Spend + 30, Car_Spend - 30);
					Line_Flag = 0;
					ischange=1;
				}
				if (gd == 0XF3 || gd == 0XFB) { //2、中间4、3传感器检测到黑线，微右拐
					SpeedCtr(Car_Spend + 60, Car_Spend - 60);
					Line_Flag = 0;
					ischange=1;
				} else if (gd == 0XF9 || gd == 0XFD) { //3、中间3、2传感器检测到黑线，再微右拐
					SpeedCtr(Car_Spend + 70, Car_Spend - 70);
					Line_Flag = 0;
					ischange=1;
				} else if (gd == 0XFC) { //4、中间2、1传感器检测到黑线，强右拐
					SpeedCtr(Car_Spend + 60, Car_Spend - 90);
					Line_Flag = 1;
					ischange=1;
				}
			}
			if (Line_Flag != 1) {
				if (gd == 0XEF) {
					SpeedCtr(Car_Spend - 30, Car_Spend + 30);
					Line_Flag = 0;
					ischange=1;
				}
				if (gd == 0XCF) { //6、中间6、5传感器检测到黑线，微左拐
					SpeedCtr(Car_Spend - 60, Car_Spend + 60);
					Line_Flag = 0;
					ischange=1;
				} else if (gd == 0X9F || gd == 0XDF) { //7、中间7、6传感器检测到黑线，再微左拐
					SpeedCtr(Car_Spend - 70, Car_Spend + 70);
					Line_Flag = 0;
					ischange=1;
				} else if (gd == 0X3F || gd == 0XBF) { //8、中间8、7传感器检测到黑线，强左拐
					SpeedCtr(Car_Spend - 60, Car_Spend + 90);
					Line_Flag = 2;
					ischange=1;
				}
			}
			if(ischange==0)
			    SpeedCtr(Car_Spend, Car_Spend);
		}
	}
}
//mode=1 返回从左侧开始第一个灭掉的灯的位置  mode！=1  返回右侧第一个灭掉的灯位置
uint8_t _DCMotor::SearchBit(uint8_t mode,uint8_t s) {
	if (mode == 1) {
		for (size_t i = 0x80; i > 0x00; i >>= 1) {
			if ((s & i) == 0)	return i;
		}
		return 0;
	} else {
		for (size_t i = 0x01; i < 0x100; i <<= 1) {
			if ((s & i) == 0)	return i;
		}
		return 0xff;
	}
}



/************************************************************************************************************
【函 数 名】：  RightMotorSpeed	设置PWM波的占空比，频率保持最后一次设置值  通道A-----pin6，通道B-----pin7
【参数说明】：	_Fduty	：设置通道 A 输出PWM波的占空比
				_Bduty	：设置通道 B 输出PWM波的占空比
【返 回 值】：	无
【简    例】：	RightMotorSpeed(70,0);
************************************************************************************************************/
void _DCMotor::MotorSpeed(uint8_t runmode, int8_t l_speed, int8_t r_speed) {
	/*sbi(TCCR4A, COM4C1);
	sbi(TCCR4A, COM4B1);
	sbi(TCCR3A, COM3C1);
	sbi(TCCR3A, COM3B1);*/
	switch (runmode) {
		case MOVE_RUNMODE_STOP:
			PORTE &= ~(_BV(PE4) | _BV(PE5));
			PORTH &= ~(_BV(PH4) | _BV(PH5));
			OCR4C = 0x0000;
			OCR4B = 0x0000;
			OCR3C = 0x0000;
			OCR3B = 0x0000;
			break;
		case MOVE_RUNMODE_FF:
			OCR4C = 0;
			OCR4B = fHz * l_speed / 100;
			OCR3C = 0;
			OCR3B = fHz * r_speed / 100;
			break;
		case MOVE_RUNMODE_BB:
			OCR4B = 0;
			OCR4C = fHz * l_speed / 100;
			OCR3B = 0;
			OCR3C = fHz * r_speed / 100;
			break;
		case MOVE_RUNMODE_LIFT:
			OCR4C = 0;
			OCR4B = fHz * l_speed / 100;
			OCR3B = 0;
			OCR3C = fHz * r_speed / 100;
			break;
		case MOVE_RUNMODE_RIGHT:
			OCR4B = 0;
			OCR4C = fHz * l_speed / 100;
			OCR3C = 0;
			OCR3B = fHz * r_speed / 100;
			break;
		case MOVE_RUNMODE_TRACK:

			break;
	}
}

/************************************************************************************************************
【函 数 名】：  RightMotorFrequency	设置PWM波的频率，占空比保持最后一次设置值  通道A-----pin6，通道B-----pin7
【参数说明】：	_fHz	：设置通道 A/B 输出PWM波的频率
【返 回 值】：	无
【简    例】：	RightMotorFrequency(7000);	//频率范围为245Hz～8MHz
************************************************************************************************************/
void _DCMotor::MotorFrequency(uint32_t _fHz) {
	fHz = 16000000 / _fHz;
	TCCR4B &= ~(_BV(CS40) | _BV(CS41) | _BV(CS42));
	TCCR4B |= _BV(CS40);
	TCCR3B &= ~(_BV(CS30) | _BV(CS31) | _BV(CS32));
	TCCR3B |= _BV(CS30);

	ICR4 = fHz;
	ICR3 = fHz;
}
/***************************************************END*****************************************************/


/***************************Timer5设置Fast PWM工作模式，以下是一些设置函数**********************************/

/************************************************************************************************************
【函 数 名】：  LeftMotorSpeed	设置PWM波的占空比，频率保持最后一次设置值  通道A-----pin46，通道B-----pin45
【参数说明】：	_front_speed	：设置通道 A 输出PWM波的占空比
				_behind_speed	：设置通道 B 输出PWM波的占空比
【返 回 值】：	无
【简    例】：	LeftMotorSpeed(70,50);
************************************************************************************************************/
void _DCMotor::LeftMotorSpeed(uint8_t _front_speed, uint8_t _behind_speed) {
	//LfHz = TCNT3;
	LFSpeed = _front_speed;
	LBSpeed = _behind_speed;
	if ((_front_speed == 100) && (_behind_speed == 100)) {
		sbi(TCCR3A, COM3C1);
		sbi(TCCR3A, COM3B1);
		OCR3C = 0xffff;// LfHz;
		OCR3B = 0xffff;// LfHz;
	} else {
		if (_front_speed >= 100) {
			sbi(TCCR3A, COM3C1);
			OCR3C = 0xffff;
		} else if (_front_speed <= 0) {
			sbi(TCCR3A, COM3C1);
			OCR3C = 0;
		} else {
			sbi(TCCR3A, COM3C1);
			OCR3C = LfHz * _front_speed / 100;
		}

		if (_behind_speed >= 100) {
			sbi(TCCR3A, COM3B1);
			OCR3B = 0xffff;

		} else if(_behind_speed <= 0) {
			sbi(TCCR3A, COM3B1);
			OCR3B = 0;

		} else {
			sbi(TCCR3A, COM3B1);
			OCR3B = LfHz * _behind_speed / 100;
		}

	}


}

/************************************************************************************************************
【函 数 名】：  LeftMotorFrequency	设置PWM波的频率，占空比保持最后一次设置值  通道A-----pin46，通道B-----pin45
【参数说明】：	_fHz	：设置通道 A/B 输出PWM波的频率
【返 回 值】：	无
【简    例】：	LeftMotorFrequency(7000);
************************************************************************************************************/
void _DCMotor::LeftMotorFrequency(uint32_t _fHz) {
	LfHz = _fHz;

	if (_fHz > 1000000) {	//频率最大为1MHz
		TCCR3B &= ~(_BV(CS30) | _BV(CS31) | _BV(CS32));
		TCCR3B |= _BV(CS30);
		ICR3 = 16;
		LfHz = 16;
		LeftMotorSpeed(LFSpeed, LBSpeed);
	} else if (_fHz < 30) {	//频率最小为30Hz
		TCCR3B &= ~(_BV(CS30) | _BV(CS31) | _BV(CS32));
		TCCR3B |= _BV(CS31);
		ICR3 = 0xffff;
		LfHz = 0xffff;
		LeftMotorSpeed(LFSpeed, LBSpeed);
	} else {			//频率范围为30Hz~1MHz
		LfHz = 16000000 / _fHz;
		if (LfHz >= 0xffff) {
			TCCR3B &= ~(_BV(CS30) | _BV(CS31) | _BV(CS32));
			TCCR3B |= _BV(CS31);
			LfHz = 2000000 / _fHz;
			ICR3 = LfHz;
			LeftMotorSpeed(LFSpeed, LBSpeed);
		} else {
			TCCR3B &= ~(_BV(CS30) | _BV(CS31) | _BV(CS32));
			TCCR3B |= _BV(CS30);
			/*LfHz = 16000000 / _fHz;*/
			ICR3 = LfHz;
			LeftMotorSpeed(LFSpeed, LBSpeed);
		}
	}
}


uint8_t _DCMotor::ShiftBitAdd(uint8_t n) {
	uint8_t bit = 0;
	for (uint8_t i = 0; i < 8; i++) {
		/*if (((n >> i) & 0x01) == 0x01)	bit ++;*/
		bit += bitRead(n, i);
	}
	return bit;
}

uint8_t _DCMotor::JudgeAround(uint8_t n) {
	for (uint8_t i = 0; i < 4; i++) {
		if ((((n >> 3) & 0x01) == 0x00) && (((n >> 4) & 0x01) == 0x00)) {
			return 8;
		} else if (((n >> (3 - i)) & 0x01) == 0x00) {
			return (3 - i);
		} else if (((n >> (4 + i)) & 0x01) == 0x00) {
			return (4 + i);
		}
	}
	return 9;
}


/************************************************************************************************************
【函 数 名】：  MPLeft	小车码盘左转函数
【参数说明】：	speed	：设置速度
distance: 设置前进的距离
【返 回 值】：	无
************************************************************************************************************/
uint16_t _DCMotor::MPLeft(uint8_t speed, uint16_t _distance) {
	unsigned long t;
	uint16_t distance;
	while (ClearCodeDisc()) {
		//DCMotor.SpeedCtr(80, 80);
		//DCMotor.StartUp();
		//delay(20);
		//DCMotor.Stop();
	}
	SpeedCtr(-speed, speed);
	StartUp();

	t = millis();
	do {
		distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
		if ((65516 > distance) && (distance > 20)) {

			if ((distance+_distance >= _distance) ||((millis() - t) >= 30000))

			{
				Stop();
				//ShutDown();
				delay(50);
				distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
				break;
			}
		}
		delay(1);
	} while (true);
	return distance;
	//return (65535 - distance);
}


/************************************************************************************************************
【函 数 名】：  MPRight		小车码盘右转函数
【参数说明】：	speed	：设置速度
distance: 设置前进的距离
【返 回 值】：	无
************************************************************************************************************/
uint16_t _DCMotor::MPRight(uint8_t speed, uint16_t _distance) {
	unsigned long t;
	uint16_t distance;
	while (ClearCodeDisc()) {
		//DCMotor.SpeedCtr(80, 80);
		//DCMotor.StartUp();
		//delay(20);
		//DCMotor.Stop();
	}
	SpeedCtr(speed, -speed);
	StartUp();

	t = millis();
	do {
		distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
		if ((65516 > distance) && (distance > 20)) {
			if ((distance >= _distance) || ((millis() - t) >= 30000))

			{
				Stop();
				//ShutDown();
				delay(50);
				distance = uint16_t(ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET) + (ExtSRAMInterface.ExMem_Read(BASEADDRESS + CODEOFFSET + 1) << 8));
				break;
			}
		}
		delay(1);
	} while (true);
	return distance;
	//return (65535 - distance);
}

