/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


//#include "init.h"   //Api Deriver writen here
//#include "cmd_h.h"  //Command Line Mechanisum Handle Here
//#include "test_h.h" //Test Handle File
uint8_t response[150];
uint32_t step=0;
uint8_t pack_received_cmplt=0;
 uint8_t long_press_no=0;	
uint8_t current_rx_ch=0;
uint8_t Rx_Buffer[50];
uint8_t curr_Rx_index=0;
uint8_t arri_buffer[30]; // this variable use to extract the data from uart recieved data
uint8_t orignal_data[12]; // this is variable to recieve the data from uart4
uint8_t num_index=0;
uint8_t my_flag;
uint8_t byte_cmplt;
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{ 
  HAL_Init(); 
  SystemClock_Config(); 
  MX_GPIO_Init();
  MX_UART5_Init();
//	HAL_UART_Receive_IT(&huart4, orignal_data, sizeof(orignal_data)-1);	
  MX_UART4_Init();
  MX_ADC2_Init();
//  MX_TIM2_Init(); 
	STR_PTS * obj=NULL;    //Create Structure Ptr Object 
	obj=init_str();        //Provide Memory and initialize the Structure Object
	
	sprintf((char *)response,"\n\rStep: %5d |==========YPZ_PTS_V1.0 ==========|\n\r",++step);  // Make Signature of Fimware
	transimit_str_to(1,response,strlen((char *)response));
		 led_cnt(1,OFF);
      led_cnt(2,OFF);	// Tranmit Signature on Uart  
	while (1)
	{
		if(pack_received_cmplt==1)        //If Command Received Completed
		{  																//If Yes
			obj->pkt=reset_packet_object(obj->pkt);  //Packet consist Keyword, Arg1 and Arg2 make it reset
			obj->pkt=get_packet_form_pc(obj->pkt);   //Extract Received String into Packet (Keyword, Arg1 and Arg2)
       	pack_received_cmplt	= 0;
	                //approch to the respective routine as per comman
			curr_Rx_index				= 0;  
			obj=select_test_routine(obj); 
			obj->pkt=reset_packet_object(obj->pkt);  //
		//	pack_received_cmplt	= 0;                 //RESET flag for next round
			sprintf((char *)response,"\n\r");
			transimit_str_to(1,response,strlen((char *)response));
		}
	  obj=sw_test(obj,1);
		enable_rx_interrupt(); 
 } 
	  return 0;
 }
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
/*
STR_PTS * sw_test(STR_PTS *ob,uint8_t switch_choice) //To Test Switch SW2  and SW3  
{
if(!(M_SW_1_PORT -> IDR & GPIO_PIN_13))          //Checking SW3 on MCU PTS BOARD
{
				long_press_no=0;
	while(!(M_SW_1_PORT -> IDR & GPIO_PIN_13)){
		
		HAL_Delay(1000);
		long_press_no++;
	}
	if(long_press_no>2 && long_press_no<4)
		 board_on(ON);
	else if(long_press_no>5 && long_press_no<9)
		 board_on(OFF);
}
if(!(GPIOC -> IDR & GPIO_PIN_14))					//Checking SW2 on MCU PTS BOARD
{
				//ob=flash_dut_out(ob);
long_press_no=0;
while(!(GPIOC -> IDR & GPIO_PIN_14))
	{
		HAL_Delay(1000);
	long_press_no++;}
	if(long_press_no>2 && long_press_no<4)
	{
	QCA_FLASH_HIGH;
	led_cnt(2,ON);
	}
else if(long_press_no>5 && long_press_no<9)
	QCA_FLASH_LOW;
	led_cnt(2,OFF);
}
			
			return ob;
}
*/
STR_PTS * sw_test(STR_PTS *ob,uint8_t switch_choice) //To Test Switch SW2  and SW3  
{
if(!(M_SW_1_PORT -> IDR & GPIO_PIN_13))          //Checking SW2 on MCU PTS BOARD
{        
long_press_no=0;
while(!(M_SW_1_PORT -> IDR & GPIO_PIN_13))
	{				
	HAL_Delay(1000);
	long_press_no++;
	}
	if(long_press_no>1 && long_press_no<4)  //Checking SW2 on MCU PTS BOARD for pwr on  
	{
//board_on(OFF);
sprintf((char *)response,"SW2 button  pressed for pwr oFF\n\r");
transimit_str_to(1,response,strlen((char *)response));
	}
	else if(long_press_no>2 && long_press_no<15)  //Checking SW2 on MCU PTS BOARD for pwr on  
	{
//board_on(ON);
sprintf((char *)response,"SW2 button  pressed for pwr ON\n\r");
transimit_str_to(1,response,strlen((char *)response));
	}
	else
	{		
sprintf((char *)response,"  No action perform \n\r");
transimit_str_to(1,response,strlen((char *)response));	
  }
}
			if(!(GPIOC -> IDR & GPIO_PIN_14))					//Checking SW3 on MCU PTS BOARD for pwr off 
			{
				long_press_no=0;
 				while(!(GPIOC -> IDR & GPIO_PIN_14))
        {  HAL_Delay(1000);
					long_press_no++;
				}		
				if(long_press_no>2 && long_press_no<4)  //Checking SW3 on MCU PTS BOARD for pwr on  
				{
			sprintf((char *)response,"  SW3 button  pressed for Prog Mode on\n\r");
			transimit_str_to(1,response,strlen((char *)response));
				//	QCA_FLASH_HIGH;
	        led_cnt(2,ON);
					//board_on(ON);
				}
				else if(long_press_no>5 && long_press_no<18)
				{
		//	QCA_FLASH_LOW;
			led_cnt(2,OFF);
			sprintf((char *)response," SW3 button  pressed for Normal Mode on\n\r");
			transimit_str_to(1,response,strlen((char *)response));
			}
			}
			
			return ob;
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
