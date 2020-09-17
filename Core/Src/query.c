/**
  ******************************************************************************
  * File Name          : test.c                                                *
  * Description        :                                                       *
  ******************************************************************************
	*/
	#include "main.h" 
extern UART_HandleTypeDef huart5;
extern uint8_t response[150];
extern uint32_t step;
extern uint8_t my_flag;
const char *sep_signal_name[30] =       {"DUT_IMP_IN_VBUS_5V(TP188)","DUT_IMP_IN(TP185)","DUT_VOLT_IN_VBUS_5V(TP51)","DUT_VOLT_IN(TP51)","VPH_PWR(TP174)","VREG_L2_1P8(TP149)",\
															        "VREG_L4_3P1(TP55)","VREG_L8_1P8(TP118)","VREG_L9_1P225(TP121)","VREG_L11_1P8(TP60)","VREG_L12_1P15(TP74)","VREG_S1_1P125(TP57)","VREG_S2_1P275(TP147)","VREG_S3_1P125(TP152)",\
                                      "VREG_S4_1P95(TP70)","VREF_LPDDR2(TP157)","VDD_3V3(TP59)","VDD_1V8","VREG_L5_3P0","VREG_L6_UIM1","VREG_L7_1P8","VREG_L10_1P0","VREG_L14_2P7","VREG_WLAN_3P3","VREG_L13_2P85","VBATT",\
                                      "VREG_L1_1P25","VREG_L3_1P8","DVDD11","AVDD11"};
													 

	/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
* @brief  voltage test through the diffrent input signal for Debug 
* @param  structure type pointer 
* @retval None
*/
	void sep_vol_read(STR_PTS * ob,uint8_t v_test)
	{
	vol_setup_all(); 
	uint32_t v_Adc=0x00;
	float my_value=0; 
	sprintf((char *)response,"\n\r");     //ob->imp_val
	transimit_str_to(1,response,strlen((char *)response)); 
  set_mux_ch(v_test);   // Here Mux channel are select by this funtion from 1 to 8
	v_Adc=Get_ADC2_value(4);  // To read the adc value from relevant channel of ADC module
	my_value=(float)v_Adc*3.3f;
	my_value/=4096;
	my_value*=2;
	ob->sep_vol=my_value;
	sprintf((char *)response," %s|v_Adc-%d|my_value-%.2f volt\n\r ",sep_signal_name[v_test],v_Adc,ob->sep_vol);
	transimit_str_to(1,response,strlen((char *)response));		
	}
		
/**
* @brief  Impedance test through the diffrent input signal for Debug 
* @param  structure type pointer 
* @retval None
*/
	void sep_imp_read(STR_PTS * ob,uint8_t i_test)
	{
	imp_setup_all();
	uint32_t raw_value=0x00;
  float supply=3.3;
	float old=0.8;
	float i_new=0; 
	float i_resLow=0;
	float i_resUp=10;
	float res_diff=0;	
sprintf((char *)response,"\n\r");     //ob->imp_val
transimit_str_to(1,response,strlen((char *)response));
set_mux_ch(i_test);
raw_value=Get_ADC2_value(IMP_ADC_CH);
 i_new=(float)raw_value*supply;
 i_new/=4096;
// newVolt=0.6;
res_diff=old-i_new;
if(res_diff>0)
 i_resLow=i_new*i_resUp/res_diff;
else
 i_resLow=IMP_LOW_SHORT;
 ob->sep_imp=i_resLow;
sprintf((char *)response,"%s-|raw_value-%d |i_new-%f |res_diff-%f|i_resLow-%.2f KOHM\n\r",sep_signal_name[i_test],raw_value,i_new,res_diff,ob->sep_imp);     //ob->imp_val
transimit_str_to(1,response,strlen((char *)response));
		  
	}
/**
* @brief  Led funtion for indicate the signal 
* @param  Led Number(1/2),State of the led (ON/OFF) 
* @retval None
*/
void led_cnt(uint8_t led_no,uint8_t led_stat)
{
if(led_no==1)
{
if(led_stat==ON		)HAL_GPIO_WritePin(M_LED_1_PORT,M_LED_1_PIN,GPIO_PIN_RESET);
else if(led_stat==OFF		)HAL_GPIO_WritePin(M_LED_1_PORT,M_LED_1_PIN,GPIO_PIN_SET  );
else if(led_stat==TOGGLE)HAL_GPIO_TogglePin(M_LED_1_PORT,M_LED_1_PIN              );
}  
else if(led_no==2)
{
if(led_stat==ON		)HAL_GPIO_WritePin(M_LED_2_PORT,M_LED_2_PIN,GPIO_PIN_RESET);
else if(led_stat==OFF		)HAL_GPIO_WritePin(M_LED_2_PORT,M_LED_2_PIN,GPIO_PIN_SET  );
else if(led_stat==TOGGLE)HAL_GPIO_TogglePin(M_LED_2_PORT,M_LED_2_PIN              );
} 
}
/**
* @brief  funtion for Setup the condition for run the impedance test 
* @param  None
* @retval None
*/
 void imp_setup_all(void)
{
 FTDI_RESET_CTRL_LOW;
 M_ENABLE_MAIN_RES_LOW;
 DUT_IMP_TEST_EN_HIGH;
 VCC_5VOUT_EN_LOW;  // dut pwr on/off
 M_0V8_ENABLE;
 N_MAIN_MUX_ENABLE; 
if(my_flag==DEBUG)
{
sprintf((char *)response," imp setup done\r\n ");
transimit_str_to(1,response,strlen((char *)response));	
}	
}
/**
* @brief  funtion for Setup the condition for run the Voltage test 
* @param  None
* @retval None
*/
 void vol_setup_all(void)
{ 
FTDI_RESET_CTRL_HIGH;	
M_0V8_DISABLE;
led_cnt(1,ON);
M_ENABLE_MAIN_RES_HIGH;
DUT_IMP_TEST_EN_LOW;
N_MAIN_MUX_ENABLE;
VCC_5VOUT_EN_HIGH;
// VCC_BATT_PWR_EN_HIGH;
if(my_flag==DEBUG) 
{
sprintf((char *)response," vol setup done\r\n ");
transimit_str_to(1,response,strlen((char *)response));
}     	     
}

/**
* @brief  funtion for Setup the condition for Turn back  the all condition in By default state 
* @param  None
* @retval None
*/
void defualt_state(void)
{
FTDI_RESET_CTRL_LOW;	
M_0V8_DISABLE;
led_cnt(1,OFF);
N_MAIN_MUX_ENABLE;
led_cnt(2,OFF);
if(my_flag==DEBUG)
{
sprintf((char *)response," reset setup done\r\n ");
transimit_str_to(1,response,strlen((char *)response));
}
}
/**
* @brief  funtion for Read the State of the signal through the ADC  
* @param  None
* @retval state of the signal
*/
uint8_t gpio_status_read(void)
{    
 uint32_t raw_value=0;
 float volt_value=0;
 raw_value=Get_ADC2_value(VOL_ADC_CH);  // To read the adc value from relevant channel of ADC module
 volt_value=(float)raw_value*3.3f;
 volt_value/=4096;
// volt_value*=2;	    
if(my_flag==DEBUG)
{
sprintf((char *)response," vol value-%f",volt_value);
transimit_str_to(1,response,strlen((char *)response));
}
if(volt_value>=3)
 return 1;
else 
 return 0; 
 }
/**
* @brief  funtion for Turn on/off the Dut power   
* @param  Sttae(ON/OFF)
* @retval None
*/
void dut_pwr_on_OFF(uint8_t state)
{
if(state==ON)
{VCC_5VOUT_EN_HIGH;
VCC_3V3_EN_HIGH;
 led_cnt(1,ON);
if(my_flag==DEBUG)
{
sprintf((char *)response,"DUR POWER ON\r\n");
transimit_str_to(1,response,strlen((char *)response));
}	
}
else
{
VCC_5VOUT_EN_LOW;
led_cnt(1,OFF);
if(my_flag==DEBUG)
{
sprintf((char *)response,"DUR POWER OFF\r\n");
transimit_str_to(1,response,strlen((char *)response));
}	
	}
}
/*
* @brief  funtion for Turn on/off the Battery power   
* @param  Sttae(ON/OFF)
* @retval None
*/
void BAT_pwr_on_OFF(uint8_t state)
{
if(state==ON)
{VCC_BATT_PWR_EN_HIGH;		
}
else
{
VCC_BATT_PWR_EN_LOW;
	}
}

/**
* @brief  funtion for Reboot the MCU through the Software  
* @param  Channel Number
* @retval state of the signal
*/
void mcu_reset(void)
{       
 NVIC_SystemReset();   
 led_cnt(1,OFF);
 led_cnt(2,OFF);
}

