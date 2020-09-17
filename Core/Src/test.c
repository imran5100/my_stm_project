/**
  ******************************************************************************
  * File Name          : test.c
  * Description        :  
  ******************************************************************************
	*/
	#include "main.h" 
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart4;
extern uint8_t response[150];
extern uint32_t step;
extern ADC_HandleTypeDef hadc2;	 //ADC Handler
extern uint8_t my_flag;
extern uint8_t my_data[10];     // this variable use to recieve the data from uart recieved data uart4
extern uint8_t arri_buffer[30]; // this variable use to extract the data from uart recieved data uart4
extern uint8_t orignal_data[12]; // this is variable to recieve the data from uart4
extern uint8_t num_index;    //this is the variable for count for uart4
extern uint8_t byte_cmplt;
const char *test_name[30] =       {"DUT_IMP_IN_VBUS_5V(TP188)","DUT_IMP_IN(TP185)","DUT_VOLT_IN_VBUS_5V(TP51)","DUT_VOLT_IN(TP51)","VPH_PWR(TP174)","VREG_L2_1P8(TP149)",\
															   "VREG_L4_3P1(TP55)","VREG_L8_1P8(TP118)","VREG_L9_1P225(TP121)","VREG_L11_1P8(TP60)","VREG_L12_1P15(TP74)","VREG_S1_1P125(TP57)","VREG_S2_1P275(TP147)","VREG_S3_1P125(TP152)",\
                                 "VREG_S4_1P95(TP70)","VREF_LPDDR2(TP157)","VDD_3V3(TP59)","VDD_1V8","VREG_L5_3P0","VREG_L6_UIM1","VREG_L7_1P8","VREG_L10_1P0","VREG_L14_2P7","VREG_WLAN_3P3","VREG_L13_2P85","VBATT",\
                                  "VREG_L1_1P25","VREG_L3_1P8","DVDD11","AVDD11"};
 
																 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


/** @fun    01
  * @brief  Impedance test through the diffrent input signal
  * @param  structure type pointer 
  * @retval None
  */
void	imp_read_all(STR_PTS * ob)
{
	imp_setup_all(); // here all the condition are execute one by one according to impedance setup
  uint8_t i=0;
	uint32_t AdcVal;
	float vcc=3.3;
	float oldVolt=0.8;
	float newVolt=0; 
	float impLow=0;
	float impUp=10;
	float volt_diff=0;
  sprintf((char *)response,"\r\n");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));
  HAL_Delay(100);
  sprintf((char *)response,"Y_I@");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));
  for(i=1;i<=30;i++)
{            
	if(i==2|| i==4 ||i==5 ||i==16)  //skip these test channels
	 {    
	continue;//will continue loop of j only    
	 } 
	set_mux_ch(i);
	AdcVal=Get_ADC2_value(IMP_ADC_CH);
	newVolt=(float)AdcVal*vcc;
	newVolt/=4096;			      
	volt_diff=oldVolt-newVolt;
	if(volt_diff>0)
  impLow=newVolt*impUp/volt_diff;
	else
  impLow=IMP_LOW_SHORT;
  sprintf((char *)response," %.2f,",impLow);
  transimit_str_to(1,response,strlen((char *)response));
	if(my_flag==DEBUG)
	{								
	sprintf((char *)response,"%s-|AdcVal-%d |newVolt-%f |volt_diff-%f|impLow-%.2f KOHM\n\r",test_name[i-1],AdcVal,newVolt,volt_diff,impLow);     //ob->imp_val
	transimit_str_to(1,response,strlen((char *)response));
	}
	impLow=0;
	}
  // POWER_ON;
	// QC_SW_RESET_HIGH;
	// QC_Pushbutton_HIGH;
	// QCA_GPIO_59_HIGH;
	sprintf((char *)response,"IMP READ DONE\r\n");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));
}

/** @fun    2.0
  * @brief   pre voltage test through the diffrent input signal before the flash the board
  * @param  None 
  * @retval None
  */
void vol_read_all(void)
{     
	vol_setup_all(); 
	uint8_t j=0;
	uint32_t AdcVal=0x00;
	float volt=0; 
//	float raw_vol=0; 
	sprintf((char *)response,"\r\n");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));
	HAL_Delay(100);
	sprintf((char *)response,"Y_V_B@");     //ob->imp_val
	transimit_str_to(1,response,strlen((char *)response));  
  for(j=1;j<=30;j++)
	 {   
   if(j==1|| j==2 ||j==19||j==20||j==21||j==22||j==23||j==24||j==25||j==27\
		 ||j==28||j==29||j==30||j==31||j==32)  //skip these test channels
		 {    
    continue;//will continue loop of j only    
     }    			 
	 set_mux_ch(j);                      // Here Mux channel are select by this funtion from 1 to 8
	 AdcVal=Get_ADC2_value(VOL_ADC_CH);  // To read the adc value from relevant channel of ADC module
	volt=(float)AdcVal*3.3f;
	volt/=4096;
	volt*=2;
	sprintf((char *)response,"%.2f,",volt);
	transimit_str_to(1,response,strlen((char *)response));
	if(my_flag==DEBUG)
	{
	sprintf((char *)response,"s[%d]-%s-|AdcVal-%d|%.2fvolt\n\r",j,test_name[j-1],AdcVal,volt);     //ob->imp_val
	transimit_str_to(1,response,strlen((char *)response));
	}
	volt=0;
	//raw_vol=0;
	 }
	sprintf((char *)response,"VOL READ DONE\r\n");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));
}

/** @fun    2.0
  * @brief   post voltage test through the diffrent input signal before the flash the board
  * @param  None 
  * @retval None
  */
void post_vol_read_all(void)
{     
	vol_setup_all(); 
	uint8_t j=0;
	uint32_t AdcVal=0x00;
	float volt=0; 
//	float raw_vol=0; 
	sprintf((char *)response,"\r\n");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));
	HAL_Delay(100);
	sprintf((char *)response,"Y_V_A@");     //ob->imp_val
	transimit_str_to(1,response,strlen((char *)response));  
  for(j=1;j<=30;j++)
	 {   
   if(j==1|| j==2 ||j==19||j==20||j==21||j==22||j==23||j==24||j==25||j==27\
		 ||j==28||j==29||j==30||j==31||j==32)  //skip these test channels
		 {    
    continue;//will continue loop of j only    
     }    			 
	 set_mux_ch(j);                      // Here Mux channel are select by this funtion from 1 to 8
	 AdcVal=Get_ADC2_value(VOL_ADC_CH);  // To read the adc value from relevant channel of ADC module
	volt=(float)AdcVal*3.3f;
	volt/=4096;
	volt*=2;
	sprintf((char *)response,"%.2f,",volt);
	transimit_str_to(1,response,strlen((char *)response));
	if(my_flag==DEBUG)
	{
	sprintf((char *)response,"s[%d]-%s-|AdcVal-%d|%.2fvolt\n\r",j,test_name[j-1],AdcVal,volt);     //ob->imp_val
	transimit_str_to(1,response,strlen((char *)response));
	}
	volt=0;
	//raw_vol=0;
	 }
	sprintf((char *)response,"VOL READ DONE\r\n");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));
}
void flash_QCA4020_Module(uint8_t mode)
{
if(mode==PROG)
{
	FORCE_BOOT_EN_HIGH;
	led_cnt(2,ON);
}
else if(mode==NORM)
{
FORCE_BOOT_EN_LOW;
led_cnt(2,OFF);	
}
}
