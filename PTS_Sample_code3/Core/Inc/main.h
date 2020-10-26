/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

 #include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "string.h"

#define SCAP_12V_SENSE_ADC 				4    			
#define SCAP_12V_OUT_ADC 				  5	   			
#define  IMP_LOW_SHORT 0
#define ON   1
#define OFF  2
#define TOGGLE 3

#define M_LED_1_PORT 										GPIOC
#define M_LED_1_PIN  										GPIO_PIN_0
#define M_LED_2_PORT 										GPIOC
#define M_LED_2_PIN  										GPIO_PIN_1
#define M_SW_1_PORT  										GPIOC
#define M_SW_1_PIN	 										GPIO_PIN_13                     --       OK IP
#define M_SW_2_PORT	 										GPIOC															--			OK
#define M_SW_2_PIN	 										GPIO_PIN_14
#define M_0V8_ENABLE_PORT								GPIOB				//0V8_ENABLE					OK      OK  
#define M_0V8_ENABLE_PIN								GPIO_PIN_1	//0V8_ENABLE					OK      OK

#define SCAP1_12V_IN_EN_PORT            GPIOB      
#define SCAP1_12V_IN_EN_PIN             GPIO_PIN_15  
#define SCAP1_12V_IN_ENABLE             HAL_GPIO_WritePin(SCAP1_12V_IN_EN_PORT,SCAP1_12V_IN_EN_PIN,GPIO_PIN_SET)
#define SCAP1_12V_IN_DISABLE            HAL_GPIO_WritePin(SCAP1_12V_IN_EN_PORT,SCAP1_12V_IN_EN_PIN,GPIO_PIN_RESET)

#define SCAP2_12V_IN_EN_PORT            GPIOB       
#define SCAP2_12V_IN_EN_PIN             GPIO_PIN_14  
#define SCAP2_12V_IN_ENABLE             HAL_GPIO_WritePin(SCAP2_12V_IN_EN_PORT,SCAP2_12V_IN_EN_PIN,GPIO_PIN_SET)
#define SCAP2_12V_IN_DISABLE            HAL_GPIO_WritePin(SCAP2_12V_IN_EN_PORT,SCAP2_12V_IN_EN_PIN,GPIO_PIN_RESET)

#define SCAP3_12V_IN_EN_PORT					  GPIOC     			
#define SCAP3_12V_IN_EN_PIN					    GPIO_PIN_6	
#define SCAP3_12V_IN_ENABLE             HAL_GPIO_WritePin(SCAP3_12V_IN_EN_PORT,SCAP3_12V_IN_EN_PIN,GPIO_PIN_SET)
#define SCAP3_12V_IN_DISABLE            HAL_GPIO_WritePin(SCAP3_12V_IN_EN_PORT,SCAP3_12V_IN_EN_PIN,GPIO_PIN_RESET)

#define SCAP4_12V_IN_EN_PORT 		        GPIOA      
#define SCAP4_12V_IN_EN_PIN		          GPIO_PIN_9	
#define SCAP4_12V_IN_ENABLE             HAL_GPIO_WritePin(SCAP4_12V_IN_EN_PORT,SCAP4_12V_IN_EN_PIN,GPIO_PIN_SET)
#define SCAP4_12V_IN_DISABLE            HAL_GPIO_WritePin(SCAP4_12V_IN_EN_PORT,SCAP4_12V_IN_EN_PIN,GPIO_PIN_RESET)

#define SCAP1_12V_SENSE_EN_PORT		       GPIOC				//MAIN_MUX_SELC_0			OK    OK
#define SCAP1_12V_SENSE_EN_PIN			     GPIO_PIN_10	//MAIN_MUX_SELC_0			OK    OK
#define SCAP1_12V_SENSE_ENABLE           HAL_GPIO_WritePin(SCAP1_12V_SENSE_EN_PORT,SCAP1_12V_SENSE_EN_PIN,GPIO_PIN_SET)
#define SCAP1_12V_SENSE_DISABLE          HAL_GPIO_WritePin(SCAP1_12V_SENSE_EN_PORT,SCAP1_12V_SENSE_EN_PIN,GPIO_PIN_RESET)

#define SCAP2_12V_SENSE_EN_PORT 		      GPIOB				//MAIN_MUX_SELC_0			OK    OK
#define SCAP2_12V_SENSE_EN_PIN		        GPIO_PIN_5	//MAIN_MUX_SELC_0			OK    OK
#define SCAP2_12V_SENSE_ENABLE            HAL_GPIO_WritePin(SCAP2_12V_SENSE_EN_PORT,SCAP2_12V_SENSE_EN_PIN,GPIO_PIN_SET)
#define SCAP2_12V_SENSE_DISABLE           HAL_GPIO_WritePin(SCAP2_12V_SENSE_EN_PORT,SCAP2_12V_SENSE_EN_PIN,GPIO_PIN_RESET)

#define SCAP3_12V_SENSE_EN_PORT		        GPIOB				//MAIN_MUX_SELC_0			OK    OK
#define SCAP3_12V_SENSE_EN_PIN			      GPIO_PIN_7	//MAIN_MUX_SELC_0			OK    OK
#define SCAP3_12V_SENSE_ENABLE            HAL_GPIO_WritePin(SCAP3_12V_SENSE_EN_PORT,SCAP3_12V_SENSE_EN_PIN,GPIO_PIN_SET)
#define SCAP3_12V_SENSE_DISABLE           HAL_GPIO_WritePin(SCAP3_12V_SENSE_EN_PORT,SCAP3_12V_SENSE_EN_PIN,GPIO_PIN_RESET)

#define SCAP4_12V_SENSE_EN_PORT					  GPIOB				//MAIN_MUX_SELC_EN    --    OK    
#define SCAP4_12V_SENSE_EN_PIN					  GPIO_PIN_9 	//MAIN_MUX_SELC_EN    --    OK
#define SCAP4_12V_SENSE_ENABLE            HAL_GPIO_WritePin(SCAP4_12V_SENSE_EN_PORT,SCAP4_12V_SENSE_EN_PIN,GPIO_PIN_SET)
#define SCAP4_12V_SENSE_DISABLE           HAL_GPIO_WritePin(SCAP4_12V_SENSE_EN_PORT,SCAP4_12V_SENSE_EN_PIN,GPIO_PIN_RESET)

#define ADC_SEL_1_PORT                    GPIOA
#define ADC_SEL_1_PIN                     GPIO_PIN_6

#define ADC_SEL_2_PORT                    GPIOB
#define ADC_SEL_2_PIN                     GPIO_PIN_0

#define MUX_SEL_1_PORT                    GPIOA      // this mux used for uart data pin selection
#define MUX_SEL_1_PIN                     GPIO_PIN_7

#define MUX_SEL_2_PORT                    GPIOB
#define MUX_SEL_2_PIN                     GPIO_PIN_10

#define RS485_EN_1_PORT                    GPIOB
#define RS485_EN_1_PIN                     GPIO_PIN_12         
#define RS485_EN_1_ENABLE                  HAL_GPIO_WritePin(RS485_EN_1_PORT,RS485_EN_1_PIN,GPIO_PIN_SET)
#define RS485_EN_1_DISABLE                 HAL_GPIO_WritePin(RS485_EN_1_PORT,RS485_EN_1_PIN,GPIO_PIN_RESET)


 
typedef struct STR_PACKET
{
	uint8_t current_rec_ch;
	uint8_t pc_rx_buffer[50];
	uint8_t keyword[20];
	uint8_t keyword_len;
	uint8_t arg_1[10];
	uint8_t arg_1_len;
	uint8_t arg_2[10];
	uint8_t arg_2_len;
}STR_PACKET;
 
typedef struct STR_PTS
{
	STR_PACKET * pkt;
	float imp_val; 
	float vol_val;
	float _0v8_value_mcu;
	uint8_t dut_connected[5];
}STR_PTS; 

	void 					SystemClock_Config	(void);
STR_PTS 		* select_test_routine	(STR_PTS * ob);
STR_PTS 		* init_str						(void	);//Will Create and initialize the Structure Object
void 					enable_rx_interrupt	(void	);
STR_PACKET 	* get_packet_form_pc	(STR_PACKET * ob); 



void 	transimit_str_to(uint8_t board,uint8_t * str,uint8_t strlen);// for uart5
void uart_tx_data_to(uint8_t * data,uint8_t strlen); //funtion defination for uart4
STR_PACKET * reset_packet_object(STR_PACKET * ob);
STR_PTS * print3(STR_PTS * ob);  // Just to check, Not in actually used 
STR_PACKET 	* get_packet_form_pc	(STR_PACKET * ob );
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart); 




//sys_core.c
uint32_t Get_ADC2_value(uint8_t adc_channel); 
//void	imp_read_all(STR_PTS * ob,uint8_t adc_ch);
void vol_read_all(void);
//void set_mux_ch(uint8_t channel); // To select the MUX  for Voltage and impedance test MUX
void set_mux_state(uint8_t choice); // To ON and OFF the MUX
uint32_t read_pps(STR_PTS *ob);
void Dual_mux_selection(uint8_t mux_channel);
void uart_pin_mux_selection(uint8_t pin_channel);// this mux selection fun used for uart4 data exchange from super cap
void Scap_EN_PIN_SEL(uint8_t state,uint8_t num);
void Sense_PIN_SEL(uint8_t mode,uint8_t num);
void super_cap_data_exchange_fun(void);
//void super_cap_dis_test(void);
void charge_enable_pin(void);
void disharge_pin(void);
void led_cnt(uint8_t led_no,uint8_t led_stat);
void hal_sec(void);
void hal_min(void);
void my_delay(uint8_t time);

void Error_Handler(void);


//query.c
STR_PTS * system_state_query(STR_PTS * ob);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
