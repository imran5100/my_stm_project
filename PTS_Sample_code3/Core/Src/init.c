/**
  ******************************************************************************
  * File Name          : init.c
  * Description        :  
  ******************************************************************************
	*/
	#include "main.h" 
extern UART_HandleTypeDef huart5;
extern uint8_t response[150];
extern uint32_t step;
extern uint8_t pack_received_cmplt;
extern uint8_t current_rx_ch;
extern uint8_t Rx_Buffer[50];
extern uint8_t curr_Rx_index; 
 

STR_PTS * init_str(void)//Will Create and initialize the Structure Object
{
	//------------Create  and Assigning memory to pointer
	STR_PTS * ob;
	ob 			=(STR_PTS 	 *)malloc(sizeof(STR_PTS		));
	ob->pkt	=(STR_PACKET *)malloc(sizeof(STR_PACKET	)); 
 
	//-------------Initialize the structure member by a initial value-------------------
  //memset(ob			,0,sizeof(STR_PTS		));
	//memset(ob->pkt,0,sizeof(STR_PACKET));
	//memset(ob->flg,0,sizeof(STR_FLAG	));

	
	
	return ob;
}

	/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
