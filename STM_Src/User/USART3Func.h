#ifndef _USART3FUNC_C_
#define _USART3FUNC_C_
#include "stm32f10x.h"
#include "stdbool.h"



#define USART3_TX_BUF_SIZE 0x10
extern uint8_t  g_USART3_tx_buf[USART3_TX_BUF_SIZE];
extern uint8_t g_USART3_tx_wishtrans;

extern uint8_t s_USART3_tx_index;
extern bool g_USART3_sending;



//void USART3_Send(uint16_t value);
void USART3SendBuf(void);

void USART3_LOOP( void );

void USART3_Config( void );
#endif




