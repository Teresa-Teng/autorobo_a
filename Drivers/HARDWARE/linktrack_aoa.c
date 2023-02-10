#include "linktrack_aoa.h"

uint8_t u_rx_buf_2[256];                 //usart2���ջ�������
uint8_t AOA_unpack_correct_flag=0;       //AOAһ֡���ݽ����ȷ��־λ
uint8_t AOA_DMA_receive_flag=0;          //DMA����һ֡AOAЭ��������ɱ�־λ
uint16_t AOA_data_length=0;              //DMA����һ֡AOAЭ�����ݳ���
uint8_t AOA_valid_node_count=0;          //AOA���ýڵ����������жϱ�ǩͻȻ�ϵ����
float angle_target_range=2.0;            //˫�����������Ŀ�껷��Χ���ǶȾ���ֵС��Ŀ�껷ʱ�����������ж�
float angle_dead_zone_range=9.0;         //˫�������������������Χ���ǶȾ���ֵС��������ʱ���Ϊ0
uint8_t angle_dead_zone_range_flag=0;    //������������־λ

float angle_measure=0.0;                 //�ǶȲ���ֵ
float angle_expect=0.0;                  //��ƫֵ���Ƕȸ�������ֵ

float dis_measure=0.0;                   //�������ֵ
float dis_expect=0.7;                    //������������ʱ������PID����ֵΪ�������ģ���λ��m
float dis_range=0.4;                     //����������������С����λ��m

uint8_t follow_me_speed=90;              //��ʼ�����ٶȣ���Χ[0,127]

/************************************************
�������� �� AOA_Application
�������� �� AOA����Ӧ�ú���
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void AOA_Application(void)
{
	AOA_unpack_correct_flag=g_nltaoa_nodeframe0.UnpackData(u_rx_buf_2,AOA_data_length); //���ú���ָ�����н��뺯�������ؽ�����ȷ/ʧ��ֵ
	if((g_nltaoa_nodeframe0.result.nodes[0] != 0)&&(AOA_unpack_correct_flag == 1)) //���nodes[0]������Ч�ҽ�����ȷ
	{
		angle_measure=g_nltaoa_nodeframe0.result.nodes[0]->angle;                 //ȡAOA�����Ƕ�ֵ
		dis_measure=g_nltaoa_nodeframe0.result.nodes[0]->dis;                     //ȡAOA��������ֵ
		AOA_valid_node_count=g_nltaoa_nodeframe0.result.valid_node_count;         //ȡAOA���ýڵ���
	}					
	if((mode_selection == 1)||(mode_selection == 2))                            //������ڽǶȸ����ǶȾ���ȫ����ģʽ
	{
		/*����ģʽ������� ��ʼ*/
		z1_increase = (int)PID_Loc(angle_expect, angle_measure, &AOA_PID);        //PID��������
		if(fabsf(angle_measure)<angle_target_range)                               //�жϽǶȲ���ֵ�Ƿ�ﵽ��Ŀ�껷��
		{
			angle_dead_zone_range_flag=1;                                           //����ﵽĿ�껷�������������жϲ���λ��־λ
		}
		if(angle_dead_zone_range_flag == 1)                                       //�����������־λΪ1
		{
			if(fabsf(angle_measure)<angle_dead_zone_range)                          //����ǶȲ�����ΧС����������Χ
			{
				z1_increase=0;                                                        //�����Ϊ0
			}
			else
			{
				angle_dead_zone_range_flag=0;                                         //����ǶȲ�����Χ������������Χ����־λ����
			}
		}
		if(z1_increase>127)                                                       //����޷�
		{
			z1_increase=127;
		}
		else if(z1_increase<-127)
		{
			z1_increase=-127;
		}
		z1_output = z1_increase+127;                                              //�����������Χ
				
		if(AOA_valid_node_count>0)                                                //������ýڵ�������0�ٿ��ƣ���ֹ��ǩͻȻ�ϵ�С��ʧ��
		{
			if(mode_selection == 1)                                                 //������ڽǶȸ���ģʽ
			{
				Move_Control( 127, 127, z1_output);                                   //�Ƕȸ���ģʽ�¸���PID���ֵ����ת���˶�����
			}
			else if(mode_selection == 2)                                            //������ڽǶȾ���ȫ����ģʽ
			{
				y1_increase=follow_me_speed;                                          //��ʼ�����ٶ�
				if(avoid_danger_switch == 1)                                          //��������˱���ģʽ
				{
					if((dis_measure>=(dis_expect+dis_range))||(dis_measure<=(dis_expect-dis_range))) //�ھ�������ʱ��Ž��б���
					{ 
						if(((TOF_FR_dis0<danger_distance)&&(TOF_signal_strength0>TOF_signal_strength)&&(TOF_status0 != 255))||
								((TOF_FM_dis1<danger_distance)&&(TOF_signal_strength1>TOF_signal_strength)&&(TOF_status1 != 255))||
								((TOF_FL_dis2<danger_distance)&&(TOF_signal_strength2>TOF_signal_strength)&&(TOF_status2 != 255)))//V1.0.1���Ӿ���״ָ̬ʾ�ж�
						{
							avoid_danger_status=1;                                          //������ϱ��ϵ����������Ͽ��Ʊ�־λ��1
						}
					}
							
					if(avoid_danger_status == 1)                                        //������Ͽ��Ʊ�־λΪ1����ʼ���Ͽ���
					{
						Avoid_Danger();                                                   //���ñ��Ϻ���
					}
					else                                                                //������Ͽ��Ʊ�־λΪ0����ʼ����������
					{
						if(((TOF_FR_dis0<slow_down_distance)&&(TOF_signal_strength0>TOF_signal_strength)&&(TOF_status0 != 255))||
								((TOF_FM_dis1<slow_down_distance)&&(TOF_signal_strength1>TOF_signal_strength)&&(TOF_status1 != 255))||
								((TOF_FL_dis2<slow_down_distance)&&(TOF_signal_strength2>TOF_signal_strength)&&(TOF_status2 != 255)))
						{
							y1_increase=avoid_danger_slow_down_speed;                       //�����һ������������С�ڼ��ٻ�������ֵ����Ӧ���ź�ǿ�ȴ�����ֵ������
						}
						else
						{
							y1_increase=follow_me_speed;                                    //�ָ���ʼ�����ٶ�
						}
						if(dis_measure>=(dis_expect+dis_range)) 													//�����������ֵ���ڵ��ڷ�Χֵ����
						{
							Move_Control( 127, y1_output-y1_increase, z1_output);           //�ǶȾ���ȫ����ģʽ���˶�����
						}
						else if(dis_measure<=(dis_expect-dis_range)) 										  //�����������ֵС�ڵ��ڷ�Χֵ����
						{
							Move_Control( 127, y1_output+y1_increase, z1_output);           //�ǶȾ���ȫ����ģʽ���˶�����
						}
						else
						{
							Move_Control( 127, y1_output, z1_output);                       //������淶Χ��ֻ���нǶȸ���
						}
					}
				}
				else                                                                  //����ر��˱���ģʽ
				{
					if(dis_measure>=(dis_expect+dis_range)) 														//�����������ֵ���ڵ��ڷ�Χֵ����
					{
						Move_Control( 127, y1_output-y1_increase, z1_output);             //�ǶȾ���ȫ����ģʽ���˶�����
					}
					else if(dis_measure<=(dis_expect-dis_range)) 												//�����������ֵС�ڵ��ڷ�Χֵ����
					{
						Move_Control( 127, y1_output+y1_increase, z1_output);             //�ǶȾ���ȫ����ģʽ���˶�����
					}
					else
					{
						Move_Control( 127, y1_output, z1_output);                         //������淶Χ��ֻ���нǶȸ���
					}
				}
						
			}
		}
		else
		{
			Move_Control( 127, 127, 127);                        							      //������ýڵ���=0��С�����ֲ���
		}
				
		/*����ģʽ������� ����*/
	}
}
