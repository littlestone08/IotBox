#ifndef _USART1FUNC_C_
#define _USART1FUNC_C_
#include "stm32f10x.h"
#include "stdbool.h"



#define USART1_TX_BUF_SIZE 0x10
extern uint8_t  g_USART1_tx_buf[USART1_TX_BUF_SIZE];
extern uint8_t g_USART1_tx_wishtrans;

extern uint8_t s_USART1_tx_index;
extern bool g_USART1_sending;



//void USART1_Send(uint16_t value);
void USART1SendBuf(void);

void USART1_LOOP( void );

void USART1_Config( void );
#endif




