
#include "InitCPU.h"
#include "stdio.h"
#include "ToolCase.h"
#include "bsp.h"
#include "user_Config.h" 
#include "test.h"
#include "RF200_Drv.h"
#include "DataParser.h"




using namespace TOOLCASE;


__EXTERN CToolCase *pToolCase;



__task void tsk_dbg_command( void ){
	while(1){
		static U32 nSecTick = 0;
		static bool led_value = false;
		os_dly_wait (500);
		if (led_value){
			GPIO_SetBits(GPIOC, GPIO_Pin_7);	
		}
		else{
			GPIO_ResetBits(GPIOC, GPIO_Pin_7);	
		}
		led_value = !led_value;
		
		//printf("sec : %d\n", nSecTick++);
						
		while(CQ1_COUNT( ) > 0){				
			switch(CQ1(0)){
				case 'o':
				case 'O':
					printf("Open\n");
					set_toolcase_status(1);
					break;
				case 'c':
				case 'C':
					printf("Close\n");
					set_toolcase_status(2);
					break;		
				default:
					printf("Unkown Command\n");						
			}
			
			CQ1_D1();				
		}			
	}
}


__task void tsk_uart_echo( void ){
		USART1_LOOP();
		USART2_LOOP();		
		USART3_LOOP();
}




__task void led_key( void ){
	while(1)	KEY_Dec();		
}
//		USART1_LOOP();
//		USART2_LOOP();		
//		USART3_LOOP();



__task void rfid_check( void ){
	while(1){
		if (os_evt_wait_or(0x0003, 1000) == OS_R_EVT){
			//case triggered(open or closed)
			if (pToolCase != NULL){
				if (pToolCase->getStatus( ) ==  tcsOpen){
					bool closed = false;
					printf("ToolCase Opened, I will Check The ToolList 5 times Per 10 Sec\n");
					{						
						for(uint8_t i = 0; i < 5; i++){
							printf("CheckTool List: %d, status: %d\n", i, os_evt_get());
							pToolCase->refresh_tools( );							
							pToolCase->report_tool_list( );
							for(uint8_t j = 0; j < 10; j++){
								os_dly_wait(1000);								
								if (pToolCase->getStatus( ) !=  tcsOpen) {
									closed = true;
									break;
								}
							}
							if (closed){
								printf("ToolCase Closed during OPENCHECKING\n");
								break;
							}
						}
					}
				}
				else if (pToolCase->getStatus( ) ==  tcsClose){
					printf("ToolCase Closed, I will Check The ToolList 1 Time immediately, , status: %d\n",  os_evt_get());
				}
			}
		}
	}	
}

__task void tsk_uart_parser( void ){
		id_uart_paser = os_tsk_self( );
		id_dbg_coommand = os_tsk_create(tsk_dbg_command, 1);
		id_key_detect = os_tsk_create(led_key, 1);		
		id_rfid_check = os_tsk_create(rfid_check, 1);
	
		while( 1 ){
			//USART3_REDIRECT_USART2( );
			//USART2_REDIRECT_USART3( );
			Parser_RFID_Respond();
		}
}




CToolCase ToolCase;	
int main(void)
{
	InitCPU( );
	
//	g_USART3_tx_buf[0] = 0x01;
//	g_USART3_tx_buf[1] = 0x02;
//	g_USART3_tx_buf[2] = 0x03;
//	g_USART3_tx_buf[3] = 0x04;
//	g_USART3_tx_buf[4] = 0x05;
//	g_USART3_tx_buf[5] = 0x06;
//	g_USART3_tx_buf[6] = 0x07;
//	
//	g_USART3_tx_wishtrans = 5;
//	USART3SendBuf( );
//	while(g_USART1_sending == 1);
//	g_USART1_tx_wishtrans = 6;
//	USART1SendBuf( );

		
	pToolCase = &ToolCase;
	ToolCase.print_version();


	LED_KEY_Init();
	SensorSWInit( );	
	printf("-----------Hello from  IotToolCase, good luck...-----------\n");
	
	pToolCase->dbg_commu_test();
	os_sys_init(tsk_uart_parser);

}



