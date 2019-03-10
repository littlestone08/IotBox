#include "test.h"
#include "user_Config.h"

void USART3_REDIRECT_USART2( ){
	uint8_t n = 0;
	
	while(g_USART2_sending == 1);		
	
	while(CQ3_COUNT( ) > 0){
		if (n < USART2_TX_BUF_SIZE){
			g_USART2_tx_buf[n++] = CQ3(0);
			CQ3_D1();				
		}
		else{
			break;
		}		
	}
	
	if ( n > 0 ) {
		g_USART2_tx_wishtrans = n;	
		USART2SendBuf( );			
	}	
}


void USART2_REDIRECT_USART3( ){
	uint8_t n = 0;
	
	while(g_USART3_sending == 1);		
	
	while(CQ2_COUNT( ) > 0){
		if (n < USART3_TX_BUF_SIZE){
			g_USART3_tx_buf[n++] = CQ2(0);
			CQ2_D1();				
		}
		else{
			break;
		}		
	}
	
	if ( n > 0 ) {
		g_USART3_tx_wishtrans = n;	
		USART3SendBuf( );			
	}	
}
