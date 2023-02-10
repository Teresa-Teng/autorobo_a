#include "tofsense.h"

uint8_t u_rx_buf_3[16];                  //usart3���ջ�������
uint8_t TOF_unpack_correct_flag=0;       //TOFSenseһ֡���ݽ����ȷ��־λ
uint8_t TOF_DMA_receive_flag=0;          //DMA����һ֡TOFSenseЭ��������ɱ�־λ
uint8_t TOF_data_length=0;               //DMA����һ֡TOFSenseЭ�����ݳ���
uint8_t u_tx_buf_3[8]={0x57,0x10,0xff,0xff,0x00,0xff,0xff,0x63}; //usart3���ͻ������飬���ڲ�ѯ������TOF
uint8_t TOF_inquire_cycle_count=0;       //TOFSenseģ�鴮�ڲ�ѯģʽ��ѯ���ڼ���������5ms��ѯһ�Σ�
uint8_t TOF_inquire_number=0;            //TOFSenseģ�鴮�ڲ�ѯģʽ��ǰ��ѯ��ģ����
float TOF_FR_dis0=0.0;                   //0�ţ�ǰ�ң�TOFSenseģ�����
float TOF_FM_dis1=0.0;                   //1�ţ�ǰ�У�TOFSenseģ�����
float TOF_FL_dis2=0.0;                   //2�ţ�ǰ��TOFSenseģ�����
float TOF_BL_dis3=0.0;                   //3�ţ�����TOFSenseģ�����
float TOF_BM_dis4=0.0;                   //4�ţ����У�TOFSenseģ�����
float TOF_BR_dis5=0.0;                   //5�ţ����ң�TOFSenseģ�����
uint8_t TOF_status0=0;                   //0��TOFSenseģ�����״ָ̬ʾ
uint8_t TOF_status1=0;                   //1��TOFSenseģ�����״ָ̬ʾ
uint8_t TOF_status2=0;                   //2��TOFSenseģ�����״ָ̬ʾ
uint8_t TOF_status3=0;                   //3��TOFSenseģ�����״ָ̬ʾ
uint8_t TOF_status4=0;                   //4��TOFSenseģ�����״ָ̬ʾ
uint8_t TOF_status5=0;                   //5��TOFSenseģ�����״ָ̬ʾ
uint16_t TOF_signal_strength0=0;         //0��TOFSenseģ������ź�ǿ��
uint16_t TOF_signal_strength1=0;         //1��TOFSenseģ������ź�ǿ��
uint16_t TOF_signal_strength2=0;         //2��TOFSenseģ������ź�ǿ��
uint16_t TOF_signal_strength3=0;         //3��TOFSenseģ������ź�ǿ��
uint16_t TOF_signal_strength4=0;         //4��TOFSenseģ������ź�ǿ��
uint16_t TOF_signal_strength5=0;         //5��TOFSenseģ������ź�ǿ��
uint16_t TOF_signal_strength=2;          //�ź�ǿ����ֵ�������ź�ǿ�ȴ��ڵ��������ֵ��ִ�б��ϲ���
	
uint8_t avoid_danger_switch=1;           //����ģʽ���أ�0��1��
uint8_t avoid_danger_status=0;           //����ģʽ״̬��1��ʾ���ڱ����㷨������
float danger_distance=0.37;              //���Ͼ�����ֵ,��λ����
float slow_down_distance=1.0;            //���ϼ��ٻ�����������ֵ,��λ����
uint8_t avoid_danger_slow_down_speed=35; //���ϼ��ٻ����������ٶȣ���Χ[0,127]
uint8_t avoid_danger_shift_speed=100;    //���Ͽ������ƺ����ٶȣ���Χ[0,127]
uint16_t avoid_danger_shift_time=0;      //���Ͽ������ƺ���ʱ�䣬��λ��ms
uint8_t avoid_danger_turn_flag=0;        //ǰ��3TOF���붼С�ڱ�����ֵ����¿�ʼתȦ��־λ
uint16_t avoid_danger_turn_count=0;      //ǰ��3TOF���붼С�ڱ�����ֵ����¿�ʼתȦ��������

/************************************************
�������� �� TOF_Application
�������� �� TOFSenseӦ�ú���
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void TOF_Application(void)
{
	TOF_unpack_correct_flag=g_nts_frame0.UnpackData(u_rx_buf_3,TOF_data_length);//���ú���ָ�����н��뺯�������ؽ�����ȷ/ʧ��ֵ
	if(TOF_unpack_correct_flag == 1)                                            //���������ȷ
	{
		if(g_nts_frame0.result.id == 0)                                           //�����֡�Ǳ��0��TOFSenseģ������
		{		
			TOF_signal_strength0=g_nts_frame0.result.signal_strength;               //ȡTOFSense�����ź�ǿ��
			TOF_status0=g_nts_frame0.result.dis_status;                             //ȡTOFSense����״ֵ̬
			TOF_FR_dis0=g_nts_frame0.result.dis;                                    //ȡTOFSense��������ֵ
		}
		else if(g_nts_frame0.result.id == 1)                                      //�����֡�Ǳ��1��TOFSenseģ������
		{				
			TOF_signal_strength1=g_nts_frame0.result.signal_strength;               //ȡTOFSense�����ź�ǿ��
			TOF_status1=g_nts_frame0.result.dis_status;                             //ȡTOFSense����״ֵ̬
			TOF_FM_dis1=g_nts_frame0.result.dis;                                  	//ȡTOFSense��������ֵ
		}
		else if(g_nts_frame0.result.id == 2)                                      //�����֡�Ǳ��2��TOFSenseģ������
		{	
			TOF_signal_strength2=g_nts_frame0.result.signal_strength;               //ȡTOFSense�����ź�ǿ��
			TOF_status2=g_nts_frame0.result.dis_status;                             //ȡTOFSense����״ֵ̬
			TOF_FL_dis2=g_nts_frame0.result.dis;                                   	//ȡTOFSense��������ֵ
		}
		else if(g_nts_frame0.result.id == 3)                                      //�����֡�Ǳ��3��TOFSenseģ������
		{		
			TOF_signal_strength3=g_nts_frame0.result.signal_strength;               //ȡTOFSense�����ź�ǿ��
			TOF_status3=g_nts_frame0.result.dis_status;                             //ȡTOFSense����״ֵ̬
			TOF_BL_dis3=g_nts_frame0.result.dis;                                 		//ȡTOFSense��������ֵ
		}		
		else if(g_nts_frame0.result.id == 4)                                      //�����֡�Ǳ��4��TOFSenseģ������
		{	
			TOF_signal_strength4=g_nts_frame0.result.signal_strength;               //ȡTOFSense�����ź�ǿ��
			TOF_status4=g_nts_frame0.result.dis_status;                             //ȡTOFSense����״ֵ̬
			TOF_BM_dis4=g_nts_frame0.result.dis;                                 		//ȡTOFSense��������ֵ
		}
		else if(g_nts_frame0.result.id == 5)                                      //�����֡�Ǳ��5��TOFSenseģ������
		{				
			TOF_signal_strength5=g_nts_frame0.result.signal_strength;               //ȡTOFSense�����ź�ǿ��
			TOF_status5=g_nts_frame0.result.dis_status;                             //ȡTOFSense����״ֵ̬
			TOF_BR_dis5=g_nts_frame0.result.dis;                                    //ȡTOFSense��������ֵ
		}				
	}
		
}

/************************************************
�������� �� Avoid_Danger
�������� �� TOFSense���Ϻ���
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Avoid_Danger(void)
{
	if((TOF_FR_dis0<danger_distance)&&(TOF_FM_dis1<danger_distance)&&(TOF_FL_dis2<danger_distance)
			&&(TOF_signal_strength0>TOF_signal_strength)&&(TOF_signal_strength1>TOF_signal_strength)
			&&(TOF_signal_strength2>TOF_signal_strength)&&(TOF_status0 != 255)&&(TOF_status1 != 255)&&(TOF_status2 != 255))//��V1.0.1���Ӿ���״ָ̬ʾ�жϣ����ǰ�ҡ�ǰ�С�ǰ��TOF����������С�ڱ�����ֵ�Ҷ�Ӧ�ź�ǿ�ȴ�����ֵ
	{
		if(avoid_danger_turn_flag == 0)                                                  //�����һ�γ���3TOF����С����ֵ���
		{
			Move_Control( 127, 127, 127-avoid_danger_shift_speed); 											   //�����˶����ƣ���ʱ��ת��
			avoid_danger_turn_flag=1;                                                      //��־λ��1���ڵδ�ʱ������ʱxms
		}
		else if(avoid_danger_turn_flag == 2)                                             //����δ�ʱ����ʱxms����3��TOF����С����ֵ��˵���������Ҳ��ǽ��
		{
			Move_Control( 127, 127, 127+avoid_danger_shift_speed); 											   //�����˶����ƣ�˳ʱ��ת��
		}
	}
	else if((TOF_FR_dis0<danger_distance)&&(TOF_FM_dis1<danger_distance)&&
			(TOF_signal_strength0>TOF_signal_strength)&&(TOF_signal_strength1>TOF_signal_strength)&&
			(TOF_status0 != 255)&&(TOF_status1 != 255)) //���ǰ�ҡ�ǰ��TOF����������С�ڱ�����ֵ�Ҷ�Ӧ�ź�ǿ�ȴ�����ֵ
	{
		Move_Control( 127-avoid_danger_shift_speed, 127, 127);                           //�����˶�����
	}
	else if((TOF_FM_dis1<danger_distance)&&(TOF_FL_dis2<danger_distance)&&
			(TOF_signal_strength1>TOF_signal_strength)&&(TOF_signal_strength2>TOF_signal_strength)&&
			(TOF_status1 != 255)&&(TOF_status2 != 255)) //���ǰ�С�ǰ��TOF����������С�ڱ�����ֵ�Ҷ�Ӧ�ź�ǿ�ȴ�����ֵ
	{
		Move_Control( 127+avoid_danger_shift_speed, 127, 127);                           //�����˶�����
	}
	else if((TOF_FR_dis0<danger_distance)&&(TOF_FL_dis2<danger_distance)&&
			(TOF_signal_strength0>TOF_signal_strength)&&(TOF_signal_strength2>TOF_signal_strength)&&
			(TOF_status0 != 255)&&(TOF_status2 != 255)) //���ǰ�ҡ�ǰ��TOF����������С�ڱ�����ֵ�Ҷ�Ӧ�ź�ǿ�ȴ�����ֵ
	{
		Move_Control( 127-avoid_danger_shift_speed, 127, 127); 												   //�����˶�����
	}
	else if((TOF_FR_dis0<danger_distance)&&(TOF_signal_strength0>TOF_signal_strength)&&(TOF_status0 != 255)) //���ǰ��TOF����������С�ڱ�����ֵ�Ҷ�Ӧ�ź�ǿ�ȴ�����ֵ
	{
		Move_Control( 127-avoid_danger_shift_speed, 127, 127);                           //�����˶�����
		avoid_danger_shift_time=AVOID_DANGER_SHIFT_SHORT_TIME;                           //���򿪻�����һ�ν϶�ʱ��
		if(avoid_danger_turn_flag == 2)                                                  //���3TOF���붼С����ֵ����ʼ˳ʱ����ת����һ����������ֵ
		{
			avoid_danger_turn_flag=0;                                                      //����ת���־λ�����պ��Ʊ����߼�����
		}
		else if(avoid_danger_turn_flag == 1)                                             //���3TOF���붼С����ֵ����ʼ��ʱ����ת����һ����������ֵ
		{
			avoid_danger_turn_flag=0;                                                      //����ת���־λ�����պ��Ʊ����߼�����
			avoid_danger_turn_count=0;                                                     //����ת��������������պ��Ʊ����߼�����
		}
	}
	else if((TOF_FM_dis1<danger_distance)&&(TOF_signal_strength1>TOF_signal_strength)&&(TOF_status1 != 255)) //���ǰ��TOF����������С�ڱ�����ֵ�Ҷ�Ӧ�ź�ǿ�ȴ�����ֵ
	{
		Move_Control( 127-avoid_danger_shift_speed, 127, 127); 												   //�����˶�����
	}
	else if((TOF_FL_dis2<danger_distance)&&(TOF_signal_strength2>TOF_signal_strength)&&(TOF_status2 != 255)) //���ǰ��TOF����������С�ڱ�����ֵ�Ҷ�Ӧ�ź�ǿ�ȴ�����ֵ
	{
		Move_Control( 127+avoid_danger_shift_speed, 127, 127);                           //�����˶�����
		avoid_danger_shift_time=AVOID_DANGER_SHIFT_SHORT_TIME;                           //���򿪻�����һ�ν϶�ʱ��
		if(avoid_danger_turn_flag == 2)                                                  //���3TOF���붼С����ֵ����ʼ˳ʱ����ת����һ����������ֵ
		{
			avoid_danger_turn_flag=0;                                                      //����ת���־λ�����պ��Ʊ����߼�����
		}
		else if(avoid_danger_turn_flag == 1)                                             //���3TOF���붼С����ֵ����ʼ��ʱ����ת����һ����������ֵ
		{
			avoid_danger_turn_flag=0;                                                      //����ת���־λ�����պ��Ʊ����߼�����
			avoid_danger_turn_count=0;                                                     //����ת��������������պ��Ʊ����߼�����
		}
	}										
	
}


