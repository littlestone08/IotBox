#ifndef _USART3FUNC_C_
#define _USART3FUNC_C_
#include "stm32f10x.h"
#include "stdbool.h"

#ifdef __cplusplus
#define __EXTERN extern "C"
#else
#define __EXTERN extern
#endif

#define USART3_TX_BUF_SIZE 0x10
__EXTERN uint8_t  g_USART3_tx_buf[USART3_TX_BUF_SIZE];
__EXTERN uint8_t g_USART3_tx_wishtrans;

__EXTERN uint8_t s_USART3_tx_index;
__EXTERN bool g_USART3_sending;



//void USART3_Send(uint16_t value);
__EXTERN void USART3SendBuf(void);

__EXTERN void USART3_LOOP( void );

__EXTERN void USART3_Config( void );
#endif




