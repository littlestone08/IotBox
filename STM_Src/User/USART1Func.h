#ifndef _USART1FUNC_C_
#define _USART1FUNC_C_
#include "stm32f10x.h"
#include "stdbool.h"

#ifdef __cplusplus
#define __EXTERN extern "C"
#else
#define __EXTERN extern
#endif
	
#define USART1_TX_BUF_SIZE 0x10
__EXTERN uint8_t  g_USART1_tx_buf[USART1_TX_BUF_SIZE];
__EXTERN uint8_t g_USART1_tx_wishtrans;

__EXTERN uint8_t s_USART1_tx_index;
__EXTERN bool g_USART1_sending;



//void USART1_Send(uint16_t value);

	
__EXTERN void USART1SendBuf(void);

__EXTERN void USART1_LOOP( void );

__EXTERN void USART1_Config( void );
	
 

#endif




