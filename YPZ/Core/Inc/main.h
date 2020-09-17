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

#define DEBUG 1
#define APP 2
#define IMP_ADC_CH 				3    			// ADC RES  1
#define VOL_ADC_CH 				2	   			// ADC VOLT 1
#define M_VOL_OUT_MAIN_2_ADC_CH 				12   			// ADC RES  2 
#define M_IMP_OUT_MAIN_2_ADC_CH 				13	 			// ADC VOLT 2
#define  IMP_LOW_SHORT 0
#define ON 1
#define OFF 2
#define TOGGLE 3
#define PROG 1
#define NORM 0
#define LOOP   1
#define SINGLE 2
#define SKU_CH 26

#define TRUE 1
#define FALSE 2

#define EXTERNAL 1
#define BATTERY  2

#define CH_9  9
#define CH_11 11
#define CH_12 12
#define CH_15 15
#define CH_17 17

#define CH_18 18
#define CH_19 19
#define CH_20 20
#define CH_21 21
#define CH_22 22
#define CH_23 23
#define CH_24 24
#define CH_25 25





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
#define M_0V8_ENABLE                    HAL_GPIO_WritePin(M_0V8_ENABLE_PORT,M_0V8_ENABLE_PIN,GPIO_PIN_SET)
#define M_0V8_DISABLE                   HAL_GPIO_WritePin(M_0V8_ENABLE_PORT,M_0V8_ENABLE_PIN,GPIO_PIN_RESET)



#define M_ENABLE_MAIN_VOL_RES_PORT      GPIOC       //ENABLE_MAIN_VOL_RES_2
#define M_ENABLE_MAIN_VOL_RES_PIN       GPIO_PIN_5  //ENABLE_MAIN_VOL_RES_2
#define M_ENABLE_MAIN_RES_HIGH          HAL_GPIO_WritePin(M_ENABLE_MAIN_VOL_RES_PORT,M_ENABLE_MAIN_VOL_RES_PIN,GPIO_PIN_SET)
#define M_ENABLE_MAIN_RES_LOW           HAL_GPIO_WritePin(M_ENABLE_MAIN_VOL_RES_PORT,M_ENABLE_MAIN_VOL_RES_PIN,GPIO_PIN_RESET)

#define M_ENABLE_MAIN_VOL_RES_2_PORT    GPIOC       //ENABLE_MAIN_VOL_RES_2
#define M_ENABLE_MAIN_VOL_RES_2_PIN     GPIO_PIN_8  //ENABLE_MAIN_VOL_RES_2
#define VOl_RES_2_HIGH                  HAL_GPIO_WritePin(M_ENABLE_MAIN_VOL_RES_2_PORT,M_ENABLE_MAIN_VOL_RES_2_PIN,GPIO_PIN_SET)
#define VOL_RES_2_LOW                   HAL_GPIO_WritePin(M_ENABLE_MAIN_VOL_RES_2_PORT,M_ENABLE_MAIN_VOL_RES_2_PIN,GPIO_PIN_RESET)
/*===================Nail Board Design==========================================================*/
#define N_MAIN_MUX_SELC_0_PORT					GPIOC     	//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_0_PIN					  GPIO_PIN_10	//MAIN_MUX_SELC_0 		OK    OK
#define N_MAIN_MUX_SELC_1_PORT 		      GPIOA      	//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_1_PIN		        GPIO_PIN_10	//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_2_PORT		      GPIOA				//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_2_PIN			      GPIO_PIN_9	//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_3_PORT 		      GPIOC				//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_3_PIN		        GPIO_PIN_11	//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_4_PORT 		      GPIOB				//MAIN_MUX_SELC_0			OK    OK
#define N_MAIN_MUX_SELC_4_PIN		        GPIO_PIN_14	//MAIN_MUX_SELC_0			OK    OK

#define N_MAIN_MUX_SELC_EN_PORT					GPIOB				//MAIN_MUX_SELC_EN    --    OK    
#define N_MAIN_MUX_SELC_EN_PIN					GPIO_PIN_9 	//MAIN_MUX_SELC_EN    --    OK
#define N_MAIN_MUX_ENABLE               HAL_GPIO_WritePin(N_MAIN_MUX_SELC_EN_PORT,N_MAIN_MUX_SELC_EN_PIN,GPIO_PIN_SET)
#define N_MAIN_MUX_DISABLE              HAL_GPIO_WritePin(N_MAIN_MUX_SELC_EN_PORT,N_MAIN_MUX_SELC_EN_PIN,GPIO_PIN_RESET)

 
#define DUT_MAIN_PWR_EN_PORT 					  GPIOB				//DUT_MAIN_PWR_EN			OK   OK
#define DUT_MAIN_PWR_EN_PIN  					  GPIO_PIN_8	//DUT_MAIN_PWR_EN  		OK   OK
#define DUT_MAIN_PWR_EN_HIGH            HAL_GPIO_WritePin(DUT_MAIN_PWR_EN_PORT,DUT_MAIN_PWR_EN_PIN,GPIO_PIN_SET)
#define DUT_MAIN_PWR_EN_LOW             HAL_GPIO_WritePin(DUT_MAIN_PWR_EN_PORT,DUT_MAIN_PWR_EN_PIN,GPIO_PIN_RESET)


#define QC_RS485_UART0_DE_PORT          GPIOB
#define QC_RS485_UART0_DE_PIN           GPIO_PIN_5
#define QC_RS485_UART0_DE_HIGH          HAL_GPIO_WritePin(QC_RS485_UART0_DE_PORT,QC_RS485_UART0_DE_PIN,GPIO_PIN_SET)
#define QC_RS485_UART0_DE_LOW           HAL_GPIO_WritePin(QC_RS485_UART0_DE_PORT,QC_RS485_UART0_DE_PIN,GPIO_PIN_RESET)
 
#define QC_RS485_UART0_RE_PORT          GPIOA
#define QC_RS485_UART0_RE_PIN           GPIO_PIN_9
#define QC_RS485_UART0_RE_HIGH          HAL_GPIO_WritePin(QC_RS485_UART0_RE_PORT,QC_RS485_UART0_RE_PIN,GPIO_PIN_SET)
#define QC_RS485_UART0_RE_LOW           HAL_GPIO_WritePin(QC_RS485_UART0_RE_PORT,QC_RS485_UART0_RE_PIN,GPIO_PIN_RESET)

#define VCC_BATT_PWR_EN_PORT            GPIOB
#define VCC_BATT_PWR_EN_PIN             GPIO_PIN_8
#define VCC_BATT_PWR_EN_HIGH            HAL_GPIO_WritePin(VCC_BATT_PWR_EN_PORT,VCC_BATT_PWR_EN_PIN,GPIO_PIN_SET)
#define VCC_BATT_PWR_EN_LOW             HAL_GPIO_WritePin(VCC_BATT_PWR_EN_PORT,VCC_BATT_PWR_EN_PIN,GPIO_PIN_RESET)

#define SAT_LEVEL_EN_PORT               GPIOC
#define SAT_LEVEL_EN_PIN                GPIO_PIN_6
#define SAT_LEVEL_EN_HIGH               HAL_GPIO_WritePin(SAT_LEVEL_EN_PORT,SAT_LEVEL_EN_PIN,GPIO_PIN_SET)   
#define SAT_LEVEL_EN_LOW                HAL_GPIO_WritePin(SAT_LEVEL_EN_PORT,SAT_LEVEL_EN_PIN,GPIO_PIN_RESET)

#define DUT_IMP_TEST_EN_PORT            GPIOB
#define DUT_IMP_TEST_EN_PIN             GPIO_PIN_7
#define DUT_IMP_TEST_EN_HIGH            HAL_GPIO_WritePin(DUT_IMP_TEST_EN_PORT,DUT_IMP_TEST_EN_PIN,GPIO_PIN_SET) 
#define DUT_IMP_TEST_EN_LOW             HAL_GPIO_WritePin(DUT_IMP_TEST_EN_PORT,DUT_IMP_TEST_EN_PIN,GPIO_PIN_RESET)

#define FTDI_RESET_CTRL_PORT              GPIOB
#define FTDI_RESET_CTRL_PIN               GPIO_PIN_6
#define FTDI_RESET_CTRL_HIGH              HAL_GPIO_WritePin(FTDI_RESET_CTRL_PORT,FTDI_RESET_CTRL_PIN,GPIO_PIN_SET)
#define FTDI_RESET_CTRL_LOW               HAL_GPIO_WritePin(FTDI_RESET_CTRL_PORT,FTDI_RESET_CTRL_PIN,GPIO_PIN_RESET)

#define DUT_USB_PWR_EN_PORT               GPIOB
#define DUT_USB_PWR_EN_PIN                GPIO_PIN_15 
#define DUT_USB_PWR_HIGH                  HAL_GPIO_WritePin(DUT_USB_PWR_EN_PORT,DUT_USB_PWR_EN_PIN,GPIO_PIN_SET)
#define DUT_USB_PWR_LOW                   HAL_GPIO_WritePin(DUT_USB_PWR_EN_PORT,DUT_USB_PWR_EN_PIN,GPIO_PIN_RESET)

#define VCC_3V3_EN_PORT                  GPIOB
#define VCC_3V3_EN_PIN                   GPIO_PIN_13 
#define VCC_3V3_EN_HIGH                  HAL_GPIO_WritePin(VCC_3V3_EN_PORT,VCC_3V3_EN_PIN,GPIO_PIN_SET)
#define VCC_3V3_EN_LOW                   HAL_GPIO_WritePin(VCC_3V3_EN_PORT,VCC_3V3_EN_PIN,GPIO_PIN_RESET)

#define VCC_5VOUT_EN_PORT              GPIOB
#define VCC_5VOUT_EN_PIN               GPIO_PIN_10
#define VCC_5VOUT_EN_HIGH              HAL_GPIO_WritePin(VCC_5VOUT_EN_PORT,VCC_5VOUT_EN_PIN,GPIO_PIN_SET)
#define VCC_5VOUT_EN_LOW               HAL_GPIO_WritePin(VCC_5VOUT_EN_PORT,VCC_5VOUT_EN_PIN,GPIO_PIN_RESET)

#define FORCE_BOOT_EN_PORT              GPIOB
#define FORCE_BOOT_EN_PIN               GPIO_PIN_12
#define FORCE_BOOT_EN_HIGH              HAL_GPIO_WritePin(FORCE_BOOT_EN_PORT,FORCE_BOOT_EN_PIN,GPIO_PIN_SET)
#define FORCE_BOOT_EN_LOW               HAL_GPIO_WritePin(FORCE_BOOT_EN_PORT,FORCE_BOOT_EN_PIN,GPIO_PIN_RESET)
 
#define QCA_GPIO_59_SAT_RESET_PORT      GPIOA
#define QCA_GPIO_59_SAT_RESET_PIN       GPIO_PIN_10
#define QCA_GPIO_59_HIGH                HAL_GPIO_WritePin(QCA_GPIO_59_SAT_RESET_PORT,QCA_GPIO_59_SAT_RESET_PIN,GPIO_PIN_SET)
#define QCA_GPIO_59_LOW                 HAL_GPIO_WritePin(QCA_GPIO_59_SAT_RESET_PORT,QCA_GPIO_59_SAT_RESET_PIN,GPIO_PIN_RESET)

#define POWER_ON_OFF_PORT              GPIOC
#define POWER_ON_OFF_PIN               GPIO_PIN_7
#define POWER_ON                       HAL_GPIO_WritePin(POWER_ON_OFF_PORT,POWER_ON_OFF_PIN,GPIO_PIN_SET) 
#define POWER_OFF                      HAL_GPIO_WritePin(POWER_ON_OFF_PORT,POWER_ON_OFF_PIN,GPIO_PIN_RESET)

#define QC_Pushbutton_1_PORT           GPIOA
#define QC_Pushbutton_1_PIN            GPIO_PIN_7
#define QC_Pushbutton_HIGH             HAL_GPIO_WritePin(QC_Pushbutton_1_PORT,QC_Pushbutton_1_PIN,GPIO_PIN_SET)
#define QC_Pushbutton_LOW              HAL_GPIO_WritePin(QC_Pushbutton_1_PORT,QC_Pushbutton_1_PIN,GPIO_PIN_RESET)  
 
#define QC_SW_RESET_PORT               GPIOA 
#define QC_SW_RESET_PIN                GPIO_PIN_5 
#define QC_SW_RESET_HIGH               HAL_GPIO_WritePin(QC_SW_RESET_PORT,QC_SW_RESET_PIN,GPIO_PIN_SET)
#define QC_SW_RESET_LOW                HAL_GPIO_WritePin(QC_SW_RESET_PORT,QC_SW_RESET_PIN,GPIO_PIN_RESET)

#define UART_MUX_EN_IN2_PORT           GPIOA 
#define UART_MUX_EN_IN2_PIN            GPIO_PIN_4 
#define UART_MUX_EN_2_HIGH             HAL_GPIO_WritePin(UART_MUX_EN_IN2_PORT,UART_MUX_EN_IN2_PIN,GPIO_PIN_SET)
#define UART_MUX_EN_2_LOW              HAL_GPIO_WritePin(UART_MUX_EN_IN2_PORT,UART_MUX_EN_IN2_PIN,GPIO_PIN_RESET)

#define UART_MUX_EN_IN1_PORT           GPIOC 
#define UART_MUX_EN_IN1_PIN            GPIO_PIN_10 
#define UART_MUX_EN_1_HIGH             HAL_GPIO_WritePin(UART_MUX_EN_IN1_PORT,UART_MUX_EN_IN1_PIN,GPIO_PIN_SET)
#define UART_MUX_EN_1_LOW              HAL_GPIO_WritePin(UART_MUX_EN_IN1_PORT,UART_MUX_EN_IN1_PIN,GPIO_PIN_RESET)

#define QC_GPIO54_LDO_EN_PORT           GPIOA 
#define QC_GPIO54_LDO_EN_PIN            GPIO_PIN_6 
#define QC_GPIO54_LDO_HIGH              HAL_GPIO_WritePin(QC_GPIO54_LDO_EN_PORT,QC_GPIO54_LDO_EN_PIN,GPIO_PIN_SET)
#define QC_GPIO54_LDO_LOW               HAL_GPIO_WritePin(QC_GPIO54_LDO_EN_PORT,QC_GPIO54_LDO_EN_PIN,GPIO_PIN_RESET)


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
	float sep_vol;
	float sep_imp;
}STR_PTS; 

	void 					SystemClock_Config	(void);
STR_PTS 		* select_test_routine	(STR_PTS * ob);
STR_PTS 		* init_str						(void	);//Will Create and initialize the Structure Object
void 					enable_rx_interrupt	(void	);
STR_PACKET 	* get_packet_form_pc	(STR_PACKET * ob); 



void 	transimit_str_to(uint8_t board,uint8_t * str,uint8_t strlen);
void uart_tx_data_to(uint8_t * data,uint8_t strlen); //funtion defination for UART4
STR_PACKET * reset_packet_object(STR_PACKET * ob);
STR_PTS * print3(STR_PTS * ob);  // Just to check, Not in actually used 
STR_PACKET 	* get_packet_form_pc	(STR_PACKET * ob );
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart); 

//sys_core.c
uint32_t Get_ADC2_value(uint8_t adc_channel); 
void	imp_read_all(STR_PTS * ob);
void vol_read_all(void);
void set_mux_ch(uint8_t channel); // To select the MUX  for Voltage and impedance test MUX
void set_mux_state(uint8_t choice); // To ON and OFF the MUX
void sep_imp_read(STR_PTS * ob,uint8_t i_test); //query.c
void sep_vol_read(STR_PTS * ob,uint8_t v_test); //query.c
void imp_setup_all(void);                      // query.c
void vol_setup_all(void);                      // query.c
void led_cnt(uint8_t led_no,uint8_t led_stat); //query.c
void defualt_state(void);    
uint8_t gpio_status_read(void);                 //query.c
void flash_QCA4020_Module(uint8_t mode);        //test.c    // test.c
void seprate_gpio_status_read(uint8_t channel);    //test.c
void dut_pwr_on_OFF(uint8_t state);            //query.c
void debug_flag(uint8_t mode);  //query.c
void BAT_pwr_on_OFF(uint8_t state);
void modem_RESET(void);
void mcu_reset(void);
STR_PTS * sw_test(STR_PTS *ob,uint8_t switch_choice);
void post_vol_read_all(void);
void Error_Handler(void);


//query.c
STR_PTS * system_state_query(STR_PTS * ob);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
