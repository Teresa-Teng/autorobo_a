/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

	/*PS2��ȡ��ʱ����1 ��ʼ*/
	if(PS2_delay_count1 >= 1)              				//��ʼ10ms��ʱ��ʱ
	{
		PS2_delay_count1++;
	}
	if(PS2_delay_count1 == 11)
	{
		PS2_delay_flag1=1;                   				//10ms��ʱ��������־λ��1
		PS2_delay_count1=0;                  				//���ü�������

	}
	/*PS2��ȡ��ʱ����1 ����*/

	/*PS2��ȡ��ʱ����2 ��ʼ*/
	if(PS2_delay_count2 >= 1)              				//��ʼ50ms��ʱ��ʱ
	{
		PS2_delay_count2++;
	}
	if(PS2_delay_count2 == 51)
	{
		PS2_delay_flag2=1;                   				//50ms��ʱ��������־λ��1
		PS2_delay_count2=0;                  				//���ü�������

	}
	/*PS2��ȡ��ʱ����2 ����*/

	/*TOFSense��ѯ���ڼ��� ��ʼ*/
	if(TOF_series_switch == 0)                      //�����ǰ���ӵ���TOFSenseϵ��
	{
		if(TOF_inquire_cycle_count >= 0)              //ÿ1ms���������Լ�һ��
		{
			TOF_inquire_cycle_count++;
		}
		if(TOF_inquire_cycle_count == 5)              //����ﵽ��5ms�Ĳ�ѯ���ڣ���ѯһ�ֵ�ʱ��Ϊx*5ms
		{
			if(TOF_inquire_number == 6)                 //�����ǰ��ѯ��ģ���ű�Ϊ6�������һ�ֲ�ѯ��
			{
				TOF_inquire_number=0;
			}
			u_tx_buf_3[4]=TOF_inquire_number;           //�����ͻ��������еĲ�ѯģ��ID��Ϊ��ǰ��Ҫ��ѯ�ı��
			u_tx_buf_3[7]=TOF_inquire_number+0x63;      //����У���
			HAL_UART_Transmit_DMA(&huart3,u_tx_buf_3,sizeof(u_tx_buf_3));//����usart3����DMA����
			TOF_inquire_number++;                       //��ǰ��ѯ��ģ����+1
			TOF_inquire_cycle_count=0;                  //���ü�������
		}
	}
	/*TOFSense��ѯ���ڼ��� ����*/

	/*TOFSense-M��ѯ���ڼ��� ��ʼ*/
	if(TOF_series_switch == 2)                      //�����ǰ���ӵ���TOFSense-Mϵ��
	{
		if(TOF_inquire_cycle_count >= 0)              //ÿ1ms���������Լ�һ��
		{
			TOF_inquire_cycle_count++;
		}
		if(TOF_inquire_cycle_count == 70)             //����ﵽ��70ms�Ĳ�ѯ����
		{
			u_tx_buf_3[4]=0;                            //�����ͻ��������еĲ�ѯģ��ID��Ϊ��ǰ��Ҫ��ѯ�ı��
			u_tx_buf_3[7]=0x63;                         //����У���
			HAL_UART_Transmit_DMA(&huart3,u_tx_buf_3,sizeof(u_tx_buf_3));//����usart3����DMA����
			TOF_inquire_cycle_count=0;                  //���ü�������
		}
	}
	/*TOFSense-M��ѯ���ڼ��� ����*/

	/*TOF���Ͽ���������ʱ ��ʼ*/
	if(avoid_danger_shift_time != 0)              //������Ͽ������ƺ�����ʱ������0
	{
		avoid_danger_shift_time--;
	}
	else
	{
		avoid_danger_status=0;                    	//����״̬��־λ��0
	}

	/*TOF���Ͽ���������ʱ ����*/

	/*TOF����ת�俪��������ʱ ��ʼ*/
	if(avoid_danger_turn_flag == 1)               //���3TOF��С����ֵ��ʼ��ʱ��תȦ
	{
		avoid_danger_turn_count++;
		if(avoid_danger_turn_count == 500)          //���ת��xms�Ժ�
		{
			avoid_danger_turn_count=0;							  //��ռ�������
			avoid_danger_turn_flag=2;								  //׼����ʼ˳ʱ��תȦ
		}
	}

	/*TOF����ת�俪��������ʱ ����*/

	/*RGB����������ʱ ��ʼ*/

	if(RGB_delay != 0)                            //���RGB��ʱ������0
	{
		RGB_delay--;                                //��ʱ�Լ�
	}

	/*RGB����������ʱ ����*/

	/*AD��ѹת����ʱ ��ʼ*/

	if(ADC_converted_count >= 0)                  //���ADת����ʱ�������ڵ���0
	{
		ADC_converted_count++;                      //��ʱ�Լ�
	}
	if(ADC_converted_count == 1000)               //���ADת����ʱ��������1000��1000msת��һ�Σ�
	{
		HAL_ADC_Start(&hadc1);                      //����ADת��
		if(battery_voltage<LOW_VOLTAGE)             //�����ص�ѹС�ڱ�����ѹ
		{
			battery_low_voltage_count++;              //��ص͵�ѹ����������1
			if(battery_low_voltage_count == 5)        //�������x�β�����ص�ѹ��С�ڱ�����ѹ
			{
				battery_low_voltage_flag=1;             //��ص͵�ѹ��־λ��1
				battery_low_voltage_count=0;            //�����ص͵�ѹ��������
			}

		}
		else
		{
			battery_low_voltage_count=0;              //�����ص͵�ѹ��������
		}
		ADC_converted_count=0;                      //�����ʱ����
	}

	/*AD��ѹת����ʱ ����*/

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */

  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */

  /* USER CODE END DMA1_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_rx);
  /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */

  /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart4_rx);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream3 global interrupt.
  */
void DMA1_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream3_IRQn 0 */

  /* USER CODE END DMA1_Stream3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_tx);
  /* USER CODE BEGIN DMA1_Stream3_IRQn 1 */

  /* USER CODE END DMA1_Stream3_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles ADC1 and ADC2 global interrupts.
  */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */

	if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC ) != RESET)                     //ȷ�Ϸ������ж�
	{
		ADC_converted_value=HAL_ADC_GetValue(&hadc1);                            //ȡADת��ֵ
		battery_voltage=(float)(((double)ADC_converted_value*3.3/65536)*63/24);  //�����ص�ѹֵ
	}

  /* USER CODE END ADC_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

	//ȷ���Ƿ������EXTI Line�ж�
	if(__HAL_GPIO_EXTI_GET_IT(KEY1_Pin) != RESET)
	{
		LED2_TOGGLE;                       				   //LED״̬��ת
		mode_selection++;                  				   //�л�ң��/�Ƕȸ���/�ǶȾ���ȫ����ģʽ/��λĿ����ƶ�ģʽ
		Reinit_XYZ_Output();                         //���³�ʼ���������ֹģʽ�л���С��ʧ��
		RGB_delay=0;                       				   //����RGB��ʱ��������ֹģʽ�л���RGB�ƹ�ʧ��
		RGB_delay_count=0;                 				   //����RGB��ʱ������������ֹģʽ�л���RGB�ƹ�ʧ��
		if(mode_selection == 4)            				   //���һ��ģʽʱ���°����л�����һ��ģʽ
		{
			mode_selection=0;
		}

		__HAL_GPIO_EXTI_CLEAR_IT(KEY1_Pin);          //����жϱ�־λ
	}

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

	// DMA�Ӵ��ڿ����жϽ������ ��ʼ
	if(__HAL_UART_GET_IT( &huart1, UART_IT_IDLE ) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);       	//������ڿ����жϱ�־λ
		HAL_UART_AbortReceive(&huart1);           	//�ر�DMA����
		LT_DMA_receive_flag=1;		                	//DMA���һ֡���ݽ���
		LT_data_length  = sizeof(u_rx_buf_1) - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   //������յ������ݳ���
		HAL_UART_Receive_DMA(&huart1,u_rx_buf_1,sizeof(u_rx_buf_1));//����DMA����

	}
	//DMA�Ӵ��ڿ����жϽ������ ����

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

	// DMA�Ӵ��ڿ����жϽ������ ��ʼ
	if(__HAL_UART_GET_IT( &huart2, UART_IT_IDLE ) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);       	//������ڿ����жϱ�־λ
		HAL_UART_AbortReceive(&huart2);           	//�ر�DMA����
		AOA_DMA_receive_flag=1;		                	//DMA���һ֡���ݽ���
		AOA_data_length  = sizeof(u_rx_buf_2) - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);   //������յ������ݳ���
		HAL_UART_Receive_DMA(&huart2,u_rx_buf_2,sizeof(u_rx_buf_2));//����DMA����

	}
	//DMA�Ӵ��ڿ����жϽ������ ����

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

	// DMA�Ӵ��ڿ����жϽ������ ��ʼ
	if(__HAL_UART_GET_IT( &huart3, UART_IT_IDLE ) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart3);       	//������ڿ����жϱ�־λ
		HAL_UART_AbortReceive(&huart3);           	//�ر�DMA����
		TOF_DMA_receive_flag=1;		                	//DMA���һ֡���ݽ���
		TOF_data_length  = sizeof(u_rx_buf_3) - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);   //������յ������ݳ���
		HAL_UART_Receive_DMA(&huart3,u_rx_buf_3,sizeof(u_rx_buf_3));//����DMA����

	}

	//DMA�Ӵ��ڿ����жϽ������ ����

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles UART4 global interrupt.
  */
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */

	// DMA�Ӵ��ڿ����жϽ������ ��ʼ
	if(__HAL_UART_GET_IT( &huart4, UART_IT_IDLE ) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart4);       	//������ڿ����жϱ�־λ
		HAL_UART_AbortReceive(&huart4);           	//�ر�DMA����
		WTIMU_DMA_receive_flag=1;		              	//DMA���һ֡���ݽ���
		WTIMU_data_length  = sizeof(u_rx_buf_4) - __HAL_DMA_GET_COUNTER(&hdma_uart4_rx);   //������յ������ݳ���
		HAL_UART_Receive_DMA(&huart4,u_rx_buf_4,sizeof(u_rx_buf_4));//����DMA����

	}
	//DMA�Ӵ��ڿ����жϽ������ ����

  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream5 global interrupt.
  */
void DMA2_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream5_IRQn 0 */

  /* USER CODE END DMA2_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream5_IRQn 1 */

  /* USER CODE END DMA2_Stream5_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
