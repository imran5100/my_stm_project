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
 
extern uint8_t Rx_Buffer[50];
extern uint8_t curr_Rx_index; 


 STR_PTS * select_test_routine(STR_PTS * ob)

{
	if(ob->pkt->keyword_len>0)
	{
	if(strncmp((char *)ob->pkt->keyword,"IMP",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"READ",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{ }
															
													 
							}
	}
	else if(strncmp((char *)ob->pkt->keyword,"VOLT",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"READ",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{vol_read_all();}
																}
							}
	
							else if(strncmp((char *)ob->pkt->keyword,"CH",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"PIN",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{ charge_enable_pin();}
																}
							}
	
							else if(strncmp((char *)ob->pkt->keyword,"DIS",ob->pkt->keyword_len)==0)
	{
							if(strncmp((char *)ob->pkt->arg_1,"PIN",ob->pkt->arg_1_len)==0)
							{
																if(strncmp((char *)ob->pkt->arg_2,"ALL"  ,ob->pkt->arg_2_len)==0)
																{disharge_pin();}
																}
							}
	
}
	return ob;
	}

	/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

