
#include "bsp.h"
#include "user_Config.h" 
#include "InitCPU.h"
#include "stdio.h"
#include "test.h"
#include "ToolCase.h"




using namespace TOOLCASE;


__EXTERN CToolCase *pToolCase;



__task void tsk_blink_task( void ){
	while(1){
		static U32 nSecTick = 0;
		os_dly_wait (1000);
		//printf("sec : %d\n", nSecTick++);
		GPIO_SetBits(GPIOC, GPIO_Pin_7);
		os_dly_wait (1000);
		//printf("sec : %d\n", nSecTick++);
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);
		
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



__task void tool_check( void ){
	while(1){
		if (os_evt_wait_or(0x0001, 1000) == OS_R_EVT){
			//case triggered(open or closed)
			if (pToolCase != NULL){
				if (pToolCase->getStatus( ) ==  tcsOpen){
					printf("ToolCase Opened, I will Check The ToolList 5 times Per 10 Sec\n");
				}
				else if (pToolCase->getStatus( ) ==  tcsClose){
					printf("ToolCase Closed, I will Check The ToolList 1 Time immediately\n");
				}
			}
		}
	}	
}
__task void tsk_uart_redirect( void ){
		id_task_uart_redirect = os_tsk_self( );
		id_led_blink = os_tsk_create(tsk_blink_task, 1);
		id_key_detect = os_tsk_create(led_key, 1);		
		id_task_tool_check = os_tsk_create(tool_check, 1);
	
		while( 1 ){
			USART3_REDIRECT_USART2( );
			USART2_REDIRECT_USART3( );
			
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

extern int test (void);

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
	
	CToolCase ToolCase;	
	pToolCase = &ToolCase;
	ToolCase.print_version();

	
	LED_KEY_Init();
	SensorSWInit( );	
	printf("Hello, this is Info From C++\n");
	
	test();
	os_sys_init(tsk_uart_redirect);

}



