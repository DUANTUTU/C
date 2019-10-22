
/*
	2019-9-6 @LiaoHelin 
*/ 

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#define u8	uint8_t


/**
  ����
*/
#define GO_BACK_MP 1000 //��������
#define TRACK_SPEED 40  //ѭ���ٶ�
#define DX_SPEED 30     //�����ε��ٶ�
#define GO_SPEED 50     // ǰ���ٶ�
#define GO_MP 300      //ǰ������    ���������̶�һ�㣬��ͨ������һ��
#define GW_SPEED 90     //ת���ٶ�
#define LEFT_MP 850     // ��ת����
#define RIGHT_MP 920    //��������
#define RIGHT45_MP 500  //������ת45������ֵ  ʶ����̵�320
#define LEFT45_MP 425   //������ת45������ֵ



/**
  ����ָ�
*/
#define GO 1
#define BACK 2     // ����
#define MPLEFT 3   // ��ת
#define MPRIGHT 4  // ��ת
#define TGO 5      // ѭ��
#define TGO_GO 100 // ѭ��
#define TGO_DX 6   // ѭ��+������
#define STOP 7     // ֹͣ
#define BACK_LUKOUSTOP 11   


/**
  ��־��
*/
#define QRCODE 8        // ��ά��ʶ��
#define ULTRASONIC 9    // ������
#define LITI 100         //�����ʾ�� ȫ��
#define LIGHT 14        // ·�Ƶ���
#define TOWER 15        // ����̨
#define BACK_TO_STM 17  // ������Ϣ������
#define AGV_FLAG 18     // �ӳ�ȫ�Զ���־λ
#define TSTOP 21
#define TLEFT 22
#define TRIGHT 23
#define CHEKU 24
#define DAOZHA 26
#define WIRELESS 29     //���߳���ʶ��
#define MARKER_LED 31   //LED��־��
#define TFT 34
#define YUYIN 41 //����
#define JTD_SHIBIE 42 //��ͨ��ʶ��
#define YANSHI 43     //��ת��ʱ

#define B_TFT_HEX 51         //TFT��ʾHEX
#define B_TFT_JULI 52        //TFT��ʾ����

#define B_GET_LOCATION 57 // ���B���⵱ǰ����

/** ����ͨѶ **/
#define SEND_TO_STM32 58
#define TEST 61

/* ��� */
#define BACK_TO_CHEKU 62
#define TUXING 64        //ͼ��
#define CHANGERUNFLAG 65 //�ı����б�־λrun_flag
//#define YUYINRENYI 66    //����������������
/* ���� */
#define DELAY 67 //����������������
#define TOWER 68



/**
  �߼�ָ�
*/

/*  ------------------ ���� ---------------------  */
//@param 3 :�������̵ľ���
#define CMD_GO{GO, GO_SPEED,800}
#define CMD_WORDAXIS_HALF{GO,GO_SPEED,900}//ʹ�����ڵ�����ÿ��Ԫ�е�һ��λ��
#define CMD_TGO{ TGO, TRACK_SPEED, GO_MP } //ѭ�� + ǰ��
#define CMD_TGO_GO{TGO_GO, TRACK_SPEED, GO_MP} //ѭ��+ ǰ��
#define CMD_TGO_DX{TGO_DX, DX_SPEED} //ѭ�� + ������
#define CMD_BACK{BACK, GO_SPEED, GO_BACK_MP} //���� +
#define CMD_MPLEFT{MPLEFT, GW_SPEED, LEFT_MP} //������ת
#define CMD_MPRIGHT{MPRIGHT, GW_SPEED, RIGHT_MP} //������ת
#define CMD_MPLEFT_45{MPLEFT, GW_SPEED, LEFT45_MP} //��ת 45 ��
#define CMD_MPRIGHT_45{MPRIGHT, GW_SPEED, RIGHT45_MP} //��ת 45��
#define CMD_TLEFT{TLEFT, GW_SPEED} //ѭ����ת
#define CMD_TRIGHT{TRIGHT, GW_SPEED} //ѭ����ת
#define CMD_TSTOP{TSTOP, TRACK_SPEED, GO_MP} //ѭ������ֹͣ
#define CMD_STOP{STOP}
// �˻ص�·��
#define CMD_BACK_LUKOUSTOP{BACK_LUKOUSTOP,GO_SPEED}
/* ʶ���ά�� */
#define CMD_QRCODE{QRCODE}
/* ͼ��ʶ�� */
#define CMD_TUXING{TUXING}

/* ʶ��ͨ�� */
#define CMD_JID_SHIBIE{JTD_SHIBIE}



/* ---------------�����ʾ�� ��ʾʶ�� ---------------*/
// ��ʾ�����ʾ�� ���� �� PublicVariable.dis ������ȡ������ñ�ָ����������ʶ����ʾ����
#define CMD_LITI_SHOW_DISTANCE{ LITI, 1}
// ��ʾ�����ʶ�� Ĭ����Ϣ�������������ʶ��
#define CMD_LITI_DEFAULT{LITI, 2}
// ��ʾ�����ʶ�� ͼ��;�� PublicVariable.liti_show_content ���� ��õ�����ñ�ָ�����ʾ��Ӧͼ��
#define CMD_LITI_GRAPH{LITI, 3}
// ��ʾ�����ʶ�� ��ɫ; �� PublicVariable.liti_show_content ���� ��õ�����ñ�ָ�����ʾ��Ӧ��ɫ
#define CMD_LITI_RGB{LITI, 4}
//��ʾ�����ʶ�� ·��; �� PublicVariable.liti_show_content ���� ��õ�����ñ�ָ�����ʾ��Ӧ·��
#define CMD_LITI_ROAD{LITI, 5}
//��ʾ�����ʾ�� ����; ��ʾ���� PublicVariable.platenumber �����ĳ���
#define CMD_LITI_CHEPAI{LITI, 6}


/* -------------------·��------------------- */
//Ѱ�ҵ�λ �޲���
#define CMD_LIGHT_FINDONE{LIGHT, 1}
#define CMD_LIGHT_FINDTWO{LIGHT, 2}
#define CMD_LIGHT_FINDTHREE{LIGHT, 3}
//��ȡ��λ ���õ� PublicVariable.gear ��������ĵ�λֵ
#define CMD_GET_LIGHT{LIGHT, 4}

/* ------------------���̨--------------------*/
#define CMD_TOWER_OPEN{TOWER, 1}
//�رշ��̨
#define CMD_TOWER_CLOSE{TOWER, 2}

/* ------------------��������� -----------------*/
//---------- �� δ֪-------------
// ��� �õ�������� PublicVariable.dis
#define CMD_ULTRASONIC_DIS{ULTRASONIC}

/* ---------   ZIGBEE��־�� -------------*/
/* ---------------����ʶ�� --------------*/
#define CMD_YUYIN{YUYIN}


/* ------------------���� A--------------- */
//�������峵�⵽��ָ������; @param 3 ��ʾָ�����
#define CMD_CHEKU_A{CHEKU, 1,2} 
//���󷵻س���λ�ڵڼ���
#define CMD_CHEKU_A_REQUEST{CHEKU,2} 
//�����Ƿ���ָ�����,��������ת��ָ�����;@param 3 ��ʾָ�����
#define CMD_CHEKU_A_CTL{CHEKU,3,2}
//��ȡ��ǰ����λ�� �õ���ǰ�ĳ���λ�� PublicVariable.current_garage ����
#define CMD_CHEKU_A_LOCATION{CHEKU,4}

/* ---------------------����b------------------- */
// ָ���������
//@param 3 ��ʾ����
#define CMD_CHEKU_B_ONE{CHEKU,11,1}
#define CMD_CHEKU_B_TWO{CHEKU,11,2}
#define CMD_CHEKU_B_THREE{CHEKU, 11,3} 
#define CMD_CHEKU_B_FOUR{CHEKU,11,4}
//���󷵻س���λ�ڵڼ���
#define CMD_CHEKU_B_REQUEST{CHEKU} 
// ��ǰ�����Ƿ���ָ��λ��,���û�а���@param 3 ��ת��ָ���㼶
#define CMD_CHEKU_B_CTL_ONE{CHEKU,13,1}
#define CMD_CHEKU_B_CTL_TWO{CHEKU,13,2}
#define CMD_CHEKU_B_CTL_THREE{CHEKU,13,3}
#define CMD_CHEKU_B_CTL_FOUR{CHEKU,13,4}
//��õ�ǰ����λ��
//�õ���ǰ�ĳ���λ�� PublicVariable.current_garage ����
#define CMD_CHEKU_B_GET_LOCATION {CHEKU,14}
/* -------------------��բ------------------ */
//�򿪻��߹رյ�բ 0x01 �򿪵�բ ,0x02�رյ�բ
#define CMD_DAOZHA_OPEN{DAOZHA, 1}
//��բ�ر�
#define CMD_DAOZHA_CLASE{DAOZHA, 2}
//��բ��������״̬; ��բ��ʱ����:@PublicVariable.daozha_count ��Ϊ 0 
#define CMD_DAOZHA_REQUEST{DAOZHA,3} 
//��բʶ����; 
#define CMD_DAOZHA_CHEPAI{DAOZHA,4} 

/* --------------------LED------------------------ */
//��LED�п�ʼ��ʱ;���� ��ʱ�ر�0x02,��ʱ��0x01
#define CMD_LED_TIME_OPEN{MARKER_LED, 1} 
#define CMD_LED_TIME_CLOSE{MARKER_LED, 2}
//����PublicVarabile.dis
#define CMD_LED_JULI{MARKER_LED,3}
//��LED����16������ʾ����(��ϧʹ��ȫ�ֱ���);@param3 ��ʾҪ�ڵڼ���д������,ΪONE ��ʾ�ڵ�һ�� 
#define CMD_LED_DATA{MARKER_LED, 4,1} 

/* --------------------���߳�� ---------------------------*/
//���߳�翪�� 
#define CMD_WIRELESS_OPEN{WIRELESS,1} 
//���޳��ر�
#define CMD_WIRELESS_CLOSE{WIRELESS,2} 

/* ------------------TFT A-------------------- */
// "TFT_A" ����; ��Ҫ����PublicVariable.platenumber�������
#define CMD_TFT_A_CHEPAI{TFT,1}
//��ʼ��ʱ; 
#define CMD_TFT_A_JISHI_START{TFT,2}
//�رռ�ʱ;
#define CMD_TFT_A_JISHI_CLOSE{TFT,3}
//��ռ�ʱ;
#define CMD_TFT_A_JISHI_CLEAR{TFT,4}
//"TFT_A"��ʶ���Զ���ת
#define CMD_TFT_A_PICTURE_AUTO{TFT,5}
//"TFT_A"ͼƬָ����ʾ; @param 3 :��ʾָ���ڼ���ͼƬ
#define CMD_TFT_A_PICTURE_ASSIGN{TFT,6,2}
//"TFT_A"��ʹ��HEXģʽ
#define CMD_TFT_A_HEX{TFT,7}
//"TFT_A"��ʶ������ʾ����
#define CMD_TFT_A_DISTANCE{TFT,8}

/* ----------------- TFT B ----------------*/
// ��ʾ����
#define CMD_TFT_B_CHEPAI{TFT,21}
//��ʱ��ʼ
#define CMD_TFT_B_JISHI_START{TFT,22}
//��ʱ�ر�
#define CMD_TFT_B_JISHI_CLOSE{TFT,23}
//��ʱ���
#define CMD_TFT_B_JISHI_CLEAR{TFT,24}
//TFTͼƬ�Զ���ת
#define CMD_TFT_B_PICTURE_AUTO{TFT,25}
//TFTͼƬָ����ʾ; @param 3 :��ʾָ���ڼ���ͼƬ
#define CMD_TFT_B_PICTURE_ASSIGN{TFT,26,2}
//ʹ��HEXģʽ,ʹ��ʹ��ȫ�ֱ���
#define CMD_TFT_B_HEX{TFT,27}
//��ʾΪʮ����25 ��Ӧʮ������19,�����ĵ�һ��������λ��ֻ��Ϊһλ��
#define CMD_TFT_B_DISTANCE{TFT,28}

/* ���� */
#define CMD_DELAY{DELAY, 10}
#define CMD_AGVFLAG{AGV_FLAG, 1}
#define CMD_END{0, 0, 0}
#define CMD_YANSHI{YANSHI,20}

#define MYCODE1   200
class _PublicVariable
{
  public:
  	int circlenum = 0;						//��¼Բ�ĸ��� 
  	int index = 0;   						//��������
  	int chekucengshu = 1;					// 
  	int openmv_zhuangtai = 0;				//OpenMV ͨѶ״̬ 
  	int run_flag = 0; // ������־��
  	uint8_t openmv_agvdata_flag = 0;		//
  	uint8_t openmv_return_data[40];			//openMVʶ�����ʱ�����ص����� 
	uint8_t current_garage = 0; 			// ���⵱ǰ�ĵ�λ  	
  	uint8_t sendflag;						//��Ϣ��� 
  	uint8_t dis;							//�����йؾ���Ҫ�õ��ı���; 
	uint8_t stop_flag; 						//stop_flag? 
	uint8_t data_length;					//���ݳ��� 
	uint8_t liti_show_content;        	  	//��Ҫ��ʾ�������ʶ���Ӧ����Ϣ,�ڻ�ȡ֮��ʹ��
	uint8_t gear;	
  	uint8_t zigbee_back[16] = {0x55, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	//ZigBee ���ص����� 
  	uint8_t trm_buf[8] = {0xAF, 0x06, 0x00, 0x02, 0x00, 0x00, 0x01, 0xBB}; //�����ն����õĵ�ͨѶЭ��, 
 	uint8_t qrdi_buf[8] = {0x55, 0x02, 0x92, 0x00, 0x00, 0x00, 0x00, 0xBB}; // ��OpenMV����ʶ���ά����߽�ͨ��
 
  	char *platenumber;						//�����ʶ�� ���Ʋ���;	
 	char jtd_type = 'B'; 					//��ͨ�Ƶ����� A��־�� ��B��־��	
	uint8_t daozha_count = 0;				//������� 
						//�Ƶĵ�λ 
	uint8_t infrare_com[6];
    boolean isstart = false;
    uint32_t yanshi_check_times = 0; 		//��ʱ����    
    
    
  private:

};
extern _PublicVariable PublicVariable;











//#endif
