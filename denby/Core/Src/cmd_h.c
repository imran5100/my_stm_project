/**
  ******************************************************************************
  * File Name          : cmd_h.c
  * Description        :  
  ******************************************************************************
	*/
	#include "main.h" 
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart4;
extern uint8_t response[150];
extern uint32_t step;
extern uint8_t pack_received_cmplt;
extern uint8_t current_rx_ch;
extern uint8_t Rx_Buffer[50];
extern uint8_t curr_Rx_index; 
extern uint8_t my_data[100];     // this variable use to recieve the data from uart recieved data uart4
extern uint8_t arri_buffer[30]; // this variable use to extract the data from uart recieved data uart4
extern uint8_t orignal_data[12]; // this is variable to recieve the data from uart4
extern uint8_t num_index;    //this is the variable for count for uart4
extern uint8_t byte_cmplt;

STR_PACKET * get_packet_form_pc(STR_PACKET * ob)
{
			int i=0;
			int j=0; 
			ob=reset_packet_object(ob);
			strcpy((char *)ob->pc_rx_buffer,(char *)Rx_Buffer); 
			j=0;
			while(Rx_Buffer[i]!=' ' && Rx_Buffer[i]!=13 && Rx_Buffer[i]!=13 && Rx_Buffer[i]!=NULL )
			{			
				ob->keyword[j++] =Rx_Buffer[i++];
				ob->keyword_len=j;
				if(j==(sizeof(ob->keyword)))break;
			}
		
			i++;
			j=0;
			while(Rx_Buffer[i]!=' ' && Rx_Buffer[i]!=13 && Rx_Buffer[i]!=NULL )
			{
				ob->arg_1[j++]=Rx_Buffer[i++];
				ob->arg_1_len=j;
				if(j==(sizeof(ob->arg_1)))break;
			}
		
			i++;
			j=0;
			while(Rx_Buffer[i]!=' ' && Rx_Buffer[i]!=13 && Rx_Buffer[i]!=NULL )
			{		
				ob->arg_2[j++] =Rx_Buffer[i++];
				ob->arg_2_len=j;
				if(j==(sizeof(ob->arg_2)))break;
			}
			
		memset(Rx_Buffer,0,sizeof(Rx_Buffer));
		 
	return ob;
}
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  
{
	//	uint8_t i=0;
    if (huart->Instance == UART5)  //current UART
		{
				if (current_rx_ch!=13 &&  current_rx_ch!='$'  && current_rx_ch!=0) //if received data different from ascii 13 (enter)
        {
							
						 if(current_rx_ch!=91)
						 {
							if( current_rx_ch==8   )
							{
								
								Rx_Buffer[--curr_Rx_index]=0; 
								HAL_UART_Transmit(&huart5,(uint8_t *)' ', 2,4);
							}
							else if(current_rx_ch==27 && curr_Rx_index>0){//37(left arrow)
									--curr_Rx_index;
							}
							else if(current_rx_ch==26 &&  curr_Rx_index < 50){//39(right arrow)
							 curr_Rx_index++;
							}
							else 
 							{
								if(current_rx_ch>='a' && current_rx_ch<='z')
									Rx_Buffer[curr_Rx_index++]=current_rx_ch-32;    //add data to Rx_Buffer
								else
									Rx_Buffer[curr_Rx_index++]=current_rx_ch;       // here the data coming from uart are recieve
								 
							}
					}
			 
        }
        else            //if received data = 13
        {							  
           pack_received_cmplt=1;//transfer complete, data is ready to read 
					 
        }  	 	
			enable_rx_interrupt(); 
		//	HAL_UART_Transmit(&huart5,(uint8_t *)&current_rx_ch, 1,10);
				//enable_rx_interrupt(); 
		}
		
		else if (huart->Instance == UART4)  //current UART)
		{
//			if(orignal_data=='\n')
//	{
//		arri_buffer[num_index++]='\n';
//		byte_cmplt=TRUE;
//		num_index =0;
//		HAL_UART_Transmit(&huart5, (uint8_t*)arri_buffer,num_index, HAL_MAX_DELAY);	
//	}
//	else
//	{
//  arri_buffer[num_index++]=orignal_data;
//	HAL_UART_Receive_IT(&huart4, (uint8_t *)&orignal_data, 1);	
//	}
			
			memcpy(arri_buffer, orignal_data, sizeof(orignal_data));
			sprintf((char *)response," >>[%s]\n\r ",arri_buffer);
      transimit_str_to(1,response,strlen((char *)response));
		//	HAL_UART_Transmit(&huart5, (uint8_t*)arri_buffer,num_index, HAL_MAX_DELAY);	
			byte_cmplt=TRUE;
			HAL_UART_Receive_IT(&huart4, orignal_data, sizeof(orignal_data)-1);	
			//memset(orignal_data,0x00,sizeof(orignal_data));
			
	}
		
}
		
void transimit_str_to(uint8_t board,uint8_t * str,uint8_t strlen)
{
			HAL_UART_Transmit(&huart5,(uint8_t *)str, strlen,strlen+5);
}

void uart_tx_data_to(uint8_t * data,uint8_t strlen) //funtion defination for UART4
{
HAL_UART_Transmit(&huart4,(uint8_t *)data, strlen,strlen+5);
}

STR_PACKET * reset_packet_object(STR_PACKET * ob)
{
	//memset(ob,0,sizeof(STR_PTS));
	memset(ob,0,sizeof(STR_PACKET));
	return ob;
}
void enable_rx_interrupt(void)
{
	if(HAL_UART_GetState(&huart5) == HAL_UART_STATE_READY)
	{// Put UART peripheral in reception process. Any data received will be stored "APQ_Buffer" buffer.
			if(HAL_UART_Receive_IT(&huart5,(uint8_t *)&current_rx_ch, 1) != HAL_OK)
			{
				//_Error_Handler(__FILE__, __LINE__);
			}
	}
} 



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


