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
extern uint8_t my_data[100];
extern uint8_t arri_buffer[10];
extern uint8_t byte_cmplt;

extern uint32_t step;
extern ADC_HandleTypeDef hadc2;	 //ADC Handler 
//static void imp_setup_all(void);
//static void vol_setup_all(void);
const char *test_name[8] =      {"DUT_VCC_12V","DUT_PWR_SENSE_12V","DUT_USB_5V","DUT_VCC_3V7","DUT_VCC_3V3",\
															   "DUT_GPS1_3V3","DUT_VCC_1V8","DUT_VCC_1V1"};
uint32_t AdcVal=0x00;
float volt=0;
uint32_t adc_charge_value(void);															 
 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/*================= fun for read the charge 12 volt output coming from super cap n cable=================*/
void vol_read_all(void)
{  
	float my_value=0;
	sprintf((char *)response,"\n\r");     //ob->imp_val
  transimit_str_to(1,response,strlen((char *)response));  
	uint8_t a=0;
	float sense_value=0,sen_out=7000;		
	  uint8_t j=0;
//  uint32_t AdcVal=0x00;
//	float volt=0;
	  uint32_t new_value=0x00;
	uint8_t i=0;
charge_enable_pin();
	//disharge_pin();                // here all 4 charging pin will be enable with some delay
for(i=1;i<=4;i++)
{ 
 Dual_mux_selection(i);              // Here Mux channel are select by this funtion from 1 to 4
     volt=0;
	   AdcVal=0;
	   AdcVal=Get_ADC2_value(SCAP_12V_OUT_ADC);  // To read the adc value from relevant channel of 5 ADC module SCAP_12V_OUT_ADC
	   volt=(float)AdcVal*3.3f;
	   volt/=4096; 
	    volt*=5.64;
 sprintf((char *)response,"SCAP[%d]_12V DETECTED-:%f\n\r",i,volt);
 transimit_str_to(1,response,strlen((char *)response)); //for debug purpose
 volt=0; 
 HAL_Delay(100);                                 
}	
	for(a=1;a<=4;a++)
	{
	Scap_EN_PIN_SEL(1,a);
		HAL_Delay(200);
	Sense_PIN_SEL(1,a);
		HAL_Delay(500);
	Dual_mux_selection(a);
  new_value=Get_ADC2_value(SCAP_12V_SENSE_ADC);  // To read the adc value from relevant channel of 4 ADC module
 sense_value=(float)new_value*3.3f;
 sense_value/=4096;
		sense_value*=5.64;
 sprintf((char *)response,"SENSE VALUE [%d]:%f\n\r",a,sense_value);  //2.3f
 transimit_str_to(1,response,strlen((char *)response));
 Sense_PIN_SEL(2,a);     // here Scap sense selected pin will be *disable
 HAL_Delay(100);		
	}

my_value=0;
led_cnt(1,ON);
 my_delay(15);  
 led_cnt(2,ON);      // this is min taken funtion
i=0;
for(i=1;i<=4;i++)
{  
Scap_EN_PIN_SEL(2,i);
Dual_mux_selection(i);             // Here Mux channel are select by this funtion from 1 to 4
volt=0;
	   AdcVal=0;
	   AdcVal=Get_ADC2_value(SCAP_12V_OUT_ADC);  // To read the adc value from relevant channel of 5 ADC module SCAP_12V_OUT_ADC
	   volt=(float)AdcVal*3.3f;
	   volt/=4096;
	    volt*=5.64;
sprintf((char *)response,"volt before 7 second delay[%d]-:%f\n\r",i,volt);
transimit_str_to(1,response,strlen((char *)response)); //for debug purpose
HAL_Delay(7000);                   //delay for 7 second
volt=0;
	   AdcVal=0;
	   AdcVal=Get_ADC2_value(SCAP_12V_OUT_ADC);  // To read the adc value from relevant channel of 5 ADC module SCAP_12V_OUT_ADC
	   volt=(float)AdcVal*3.3f;
	   volt/=4096;
	    volt*=5.64;
sprintf((char *)response,"volt after delay[%d]-:%f\n\r",i,volt);
transimit_str_to(1,response,strlen((char *)response)); //for debug purpose
}	
uint8_t k=0;
my_value=0;
for(k=1;k<=4;k++)
{
Dual_mux_selection(k);             // Here Mux channel are select by this funtion from 1 to 4
do
{
    volt=0;
	   AdcVal=0;
	   AdcVal=Get_ADC2_value(SCAP_12V_OUT_ADC);  // To read the adc value from relevant channel of 5 ADC module SCAP_12V_OUT_ADC
	   volt=(float)AdcVal*3.3f;
	   volt/=4096;
	    volt*=5.64;
}
while(volt>0.5);
sprintf((char *)response,"final value[%d]-:%f\n\r",k,volt);
transimit_str_to(1,response,strlen((char *)response)); //for debug purpose}
 }  
 }	

 
/*==========fun to sense the discharge volt of super cap cable n==================*/					 
/*   void super_cap_dis_test(void)
{		uint32_t  t_sense=0,sen_out=7000;		
	  uint8_t j=0;
//  uint32_t AdcVal=0x00;
//	float volt=0;
	  uint32_t new_value=0x00;
	  float sense_value=0;	
		sprintf((char *)response,"\n\r");     //ob->imp_val
		transimit_str_to(1,response,strlen((char *)response)); 
     led_cnt(1,ON);
	  // led_cnt(2,ON);	
	  for(j=1;j<=4;j++)
		{					
		// Scap_EN_PIN_SEL(2,j);	 // here scap selected pin will be *disable
		 Sense_PIN_SEL(1,j);     // here Scap sense selected pin will be *enable
		 Dual_mux_selection(j);
		//	HAL_Delay(300);					
		 new_value=Get_ADC2_value(SCAP_12V_SENSE_ADC);  // To read the adc value from relevant channel of 4 ADC module
		 sense_value=(float)new_value*3.3f;
		 sense_value/=4096;
		 sprintf((char *)response,"SCAP[%d]:%f :t_sense-%d;",j,sense_value,t_sense);  //2.3f
		 transimit_str_to(1,response,strlen((char *)response));
		 Sense_PIN_SEL(2,j);     // here Scap sense selected pin will be *disable
		 }
	 }
*/
/* funtion defination for uart data exchange from NTDI Cable*/
void super_cap_data_exchange_fun(void)
{
  uint8_t k,m=0;
	RS485_EN_1_ENABLE;
	for(k=1;k<=4;k++)
	{ 
		uart_pin_mux_selection(k);
		sprintf((char *)my_data,"super_cap_test\r");  //2.3f
		uart_tx_data_to(my_data,strlen((char *)my_data)); //funtion defination
		HAL_Delay(1000);
		led_cnt(1,ON);	 
	}
	led_cnt(1,OFF);
	HAL_Delay(500);
	RS485_EN_1_DISABLE; // location may be change from here and may be uart recive interrupt has to put
	for(m=1;m<=4;m++)
	{
		led_cnt(2,OFF);  // led 2 off when it goes under single iteration
	uart_pin_mux_selection(m);
		HAL_Delay(500);
		if(byte_cmplt)  //if uart4 rcv pkt of one byte will cmplte this flag will be set
		{
			byte_cmplt=0;
	if(strncmp((char *)arri_buffer,"super_cap_test",5)==0)   //here the string will be compare
	{
			sprintf((char *)response,"UART[%d]:PASS;",m);     // the result will be sent to PC Application through the UART5
			transimit_str_to(1,response,strlen((char *)response));
      led_cnt(2,ON);	 // led2 on when uart recieve string successfully	
	}
	else
			sprintf((char *)response,"UART[%d]:FAIL;",m);  //2.3f
			transimit_str_to(1,response,strlen((char *)response));	    
  } 
   else
		 sprintf((char *)response,"UART_NOT_RCV_PKT");  //2.3f
		 transimit_str_to(1,response,strlen((char *)response));	
	             
}
	HAL_Delay(200);
}
void Dual_mux_selection(uint8_t mux_channel)
{
switch(mux_channel)
{
	case 1:
  HAL_GPIO_WritePin(ADC_SEL_1_PORT,ADC_SEL_1_PIN,GPIO_PIN_RESET);//0  PA6  LOW
  HAL_GPIO_WritePin(ADC_SEL_2_PORT,ADC_SEL_2_PIN,GPIO_PIN_RESET);//0  PB0  LOW
  break;
	case 2:
  HAL_GPIO_WritePin(ADC_SEL_1_PORT,ADC_SEL_1_PIN,GPIO_PIN_SET); //1    HIGH
  HAL_GPIO_WritePin(ADC_SEL_2_PORT,ADC_SEL_2_PIN,GPIO_PIN_RESET);//0    LOW
  break;

	case 3:
  HAL_GPIO_WritePin(ADC_SEL_1_PORT,ADC_SEL_1_PIN,GPIO_PIN_RESET); //0   LOW
  HAL_GPIO_WritePin(ADC_SEL_2_PORT,ADC_SEL_2_PIN,GPIO_PIN_SET); //1     HIGH
  break;

	case 4:
  HAL_GPIO_WritePin(ADC_SEL_1_PORT,ADC_SEL_1_PIN,GPIO_PIN_SET); //1    HIGH
  HAL_GPIO_WritePin(ADC_SEL_2_PORT,ADC_SEL_2_PIN,GPIO_PIN_SET);  //1   HIGH
  break;

default:
break;

}

}

void uart_pin_mux_selection(uint8_t pin_channel)
{
switch(pin_channel)
{
	case 1:
  HAL_GPIO_WritePin(MUX_SEL_1_PORT ,MUX_SEL_1_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MUX_SEL_2_PORT,MUX_SEL_2_PIN,GPIO_PIN_RESET);
	HAL_Delay(100);
  break;
	case 2:
  HAL_GPIO_WritePin(MUX_SEL_1_PORT,MUX_SEL_1_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(MUX_SEL_2_PORT,MUX_SEL_2_PIN,GPIO_PIN_RESET);
	HAL_Delay(100);
  break;

	case 3:
  HAL_GPIO_WritePin(MUX_SEL_1_PORT,MUX_SEL_1_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MUX_SEL_2_PORT,MUX_SEL_2_PIN,GPIO_PIN_SET);
	HAL_Delay(100);
  break;

	case 4:
  HAL_GPIO_WritePin(MUX_SEL_1_PORT,MUX_SEL_1_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(MUX_SEL_2_PORT,MUX_SEL_2_PIN,GPIO_PIN_SET);
	HAL_Delay(100);
  break;

default:
break;

}

}
void Scap_EN_PIN_SEL(uint8_t state,uint8_t num)
{
	if(state==1)
	{
switch(num)
{
	case 1:
		SCAP1_12V_IN_ENABLE;
	  break;
	
	 case 2:
		SCAP2_12V_IN_ENABLE;
	  break;
	 
	 case 3:
		SCAP3_12V_IN_ENABLE;
	  break;
	 
	 case 4:
		SCAP4_12V_IN_ENABLE;
	  break;
	 default:
		 break;
	
}
}
else if(state==2)
{
switch(num)
{
	case 1:
		SCAP1_12V_IN_DISABLE;
	  break;
	
	 case 2:
		SCAP2_12V_IN_DISABLE;
	  break;
	 
	 case 3:
		SCAP3_12V_IN_DISABLE;
	  break;
	 
	 case 4:
		SCAP4_12V_IN_DISABLE;
	  break;
	 default:
		 break;
	
}
}
}

void Sense_PIN_SEL(uint8_t mode,uint8_t num)
{
	if(mode==1)
	{
switch(num)
{
	case 1:
		SCAP1_12V_SENSE_ENABLE;
	  break;
	
	 case 2:
		SCAP2_12V_SENSE_ENABLE;
	  break;
	 
	 case 3:
		SCAP3_12V_SENSE_ENABLE;
	  break;
	 
	 case 4:
		SCAP4_12V_SENSE_ENABLE;
	  break;
	 default:
		 break;
	
}
}
else if(mode==2)
{
switch(num)
{
	case 1:
		SCAP1_12V_SENSE_DISABLE;
	  break;
	
	 case 2:
		SCAP2_12V_SENSE_DISABLE;
	  break;
	 
	 case 3:
		SCAP3_12V_SENSE_DISABLE;
	  break;
	 
	 case 4:
		SCAP4_12V_SENSE_DISABLE;
	  break;
	 default:
		 break;
	
}
}
}
void charge_enable_pin(void)
{
SCAP1_12V_IN_ENABLE;
	HAL_Delay(10000);
SCAP2_12V_IN_ENABLE;
	HAL_Delay(10000);
SCAP3_12V_IN_ENABLE;
	HAL_Delay(10000);
SCAP4_12V_IN_ENABLE;
  HAL_Delay(200);
}
void disharge_pin(void)
{
SCAP1_12V_IN_DISABLE;
SCAP2_12V_IN_DISABLE;
SCAP3_12V_IN_DISABLE;
SCAP4_12V_IN_DISABLE;
}


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

void hal_sec(void) // this will get one second elapse
{
uint32_t i=0;
for(i=0;i<=1000;i++)
	{
HAL_Delay(1);
	}
}

void hal_min(void)  // this will get one min elapse
{
uint8_t j=0;
for(j=1;j<=29;j++)
{
hal_sec();
}
}
void my_delay(uint8_t time)  // this is min taken funtion
{
 uint8_t k=0;
 for(k=1;k<=time;k++)
{
hal_min();
}

}

/*===========================================*/
uint32_t adc_charge_value(void)
{    volt=0;
	   AdcVal=0;
	   AdcVal=Get_ADC2_value(5);  // To read the adc value from relevant channel of 5 ADC module SCAP_12V_OUT_ADC
	   volt=(float)AdcVal*3.3f;
	   volt/=4096;
	   return volt;
}
