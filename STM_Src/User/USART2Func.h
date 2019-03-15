#ifndef _USART2FUNC_C_
#define _USART2FUNC_C_
#include "stm32f10x.h"
#include "stdbool.h"


#ifdef __cplusplus
#define __EXTERN extern "C"
#else
#define __EXTERN extern
#endif

#define USART2_TX_BUF_SIZE 0xFF
__EXTERN uint8_t  g_USART2_tx_buf[USART2_TX_BUF_SIZE];
__EXTERN uint8_t g_USART2_tx_wishtrans;

__EXTERN uint8_t s_USART2_tx_index;
__EXTERN bool g_USART2_sending;



//void USART2_Send(uint16_t value);
__EXTERN void USART2SendBuf(void);

__EXTERN void USART2_LOOP( void );

__EXTERN void USART2_Config( void );
#endif




