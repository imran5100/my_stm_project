/**
  ******************************************************************************
  * File Name          : test.c
  * Description        :  
  ******************************************************************************
	*/
	#include "main.h" 
extern UART_HandleTypeDef huart5;
extern uint8_t response[150];
 
extern uint8_t Rx_Buffer[50];
extern uint8_t curr_Rx_index; 
extern uint8_t my_flag;


 STR_PTS * select_test_routine(STR_PTS * ob)

{
	if(ob->pkt->keyword_len>0)
	{
	if(strncmp((char *)ob->pkt->keyword,"IMP",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"SETUP",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{ imp_setup_all(); }						 
							}
							else if(strncmp((char *)ob->pkt->arg_1,"READ",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{ imp_read_all(ob); }						 
							}
							
	}
	else if(strncmp((char *)ob->pkt->keyword,"VOLT",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"SETUP",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{  vol_setup_all();}
							}
						}
							else if(strncmp((char *)ob->pkt->keyword,"PRE",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"VOL",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{  vol_read_all();}
							}
		}		
	
		else if(strncmp((char *)ob->pkt->keyword,"POS",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"VOL",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{ post_vol_read_all();}
							}
		}		
	else if(strncmp((char *)ob->pkt->keyword,"DUT",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"POWER",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ON"  ,ob->pkt->arg_2_len)==0)
																{ dut_pwr_on_OFF(ON);}
							                  else if(strncmp((char *)ob->pkt->arg_2,"OFF"  ,ob->pkt->arg_2_len)==0)
																{dut_pwr_on_OFF(OFF);}
							}
	}
	else if(strncmp((char *)ob->pkt->keyword,"BAT",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"POWER",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ON"  ,ob->pkt->arg_2_len)==0)
																{BAT_pwr_on_OFF(ON);}
							                  else if(strncmp((char *)ob->pkt->arg_2,"OFF"  ,ob->pkt->arg_2_len)==0)
																{BAT_pwr_on_OFF(OFF);}
							}
	}
	else if(strncmp((char *)ob->pkt->keyword,"DEBUG",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"FLAG",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ON"  ,ob->pkt->arg_2_len)==0)
																{my_flag=DEBUG;
																 sprintf((char *)response, "DEBUG MODE ON\n\r");
		                             transimit_str_to(1,response,strlen((char *)response));
														     }					
								                
							}
	}
	else if(strncmp((char *)ob->pkt->keyword,"APP",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"FLAG",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ON"  ,ob->pkt->arg_2_len)==0)
																{my_flag=APP;
																 sprintf((char *)response, "APP MODE ON\n\r");
		                             transimit_str_to(1,response,strlen((char *)response));
												        	}						                
							}
	}
	else if(strncmp((char *)ob->pkt->keyword,"RESET",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"ALL",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"STATE"  ,ob->pkt->arg_2_len)==0)
																{  defualt_state();}                 
							}
	}
	else if(strncmp((char *)ob->pkt->keyword,"EDL",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"MODE",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ON"  ,ob->pkt->arg_2_len)==0)
																{  flash_QCA4020_Module(PROG);}
																else if(strncmp((char *)ob->pkt->arg_2,"OFF"  ,ob->pkt->arg_2_len)==0)
														   { flash_QCA4020_Module(NORM);}                 
							}
	}
	else if(strncmp((char *)ob->pkt->keyword,"SOFT",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"RST",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"MCU"  ,ob->pkt->arg_2_len)==0)
																{   mcu_reset();}                
							}
	}

}	
	return ob;
	}
	/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
void set_mux_ch(uint8_t channel) // To select the MUX  for Voltage and impedance test MUX
 { 
	switch(channel)
	{
		case 1:   
		//	HAL_Delay(100);
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(500);
			break;
		case 2:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);   //1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);  //0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);  //0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);  //0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);  //0
		          HAL_Delay(1000);
			break;
		case 3:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(2000);
			break;
		case 4:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(500);
			break;
		case 5:	
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(500);
			break;
		case 6:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(1000);
			break;
		case 7:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(1000);
			break;
		case 8:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(700);
			break;
		case 9:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(500);
			break;
		case 10:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(500);
			break;
	case 11:   //-------1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
	            HAL_Delay(1000);
			break;
		case 12:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(5000);
			break;
		case 13:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(1000);
			break;
		case 14:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(500);
			break;
		case 15:	
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(1000);
			break;
		case 16:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_RESET);//0
		          HAL_Delay(500);
			break;
		case 17:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(500);
			break;
		case 18:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 19:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 20:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
		          break;
		case 21:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200); 
			break;
		case 22:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 23:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
	case 24:   //-------1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_RESET);//0
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
	            HAL_Delay(200);
			break;
		case 25:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 26:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 27:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 28:	
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_RESET);//0 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 29:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 30:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		case 31:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_RESET);//0
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
		
		case 32:
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_0_PORT,N_MAIN_MUX_SELC_0_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_1_PORT,N_MAIN_MUX_SELC_1_PIN,GPIO_PIN_SET);//1
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_2_PORT,N_MAIN_MUX_SELC_2_PIN,GPIO_PIN_SET);//1 
							HAL_GPIO_WritePin(N_MAIN_MUX_SELC_3_PORT,N_MAIN_MUX_SELC_3_PIN,GPIO_PIN_SET);//1
		          HAL_GPIO_WritePin(N_MAIN_MUX_SELC_4_PORT,N_MAIN_MUX_SELC_4_PIN,GPIO_PIN_SET);//1
		          HAL_Delay(200);
			break;
		
		default:
						 
			break;
	}
	            //sprintf((char *)response,"mux channel[%d]\n\r",channel);     //for debug purpose
						 // transimit_str_to(1,response,strlen((char *)response));
}
	
	
