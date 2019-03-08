#ifndef _USART2FUNC_C_
#define _USART2FUNC_C_
#include "stm32f10x.h"
#include "stdbool.h"



#define USART2_TX_BUF_SIZE 0x10
extern uint8_t  g_USART2_tx_buf[USART2_TX_BUF_SIZE];
extern uint8_t g_USART2_tx_wishtrans;

extern uint8_t s_USART2_tx_index;
extern bool g_USART2_sending;



//void USART2_Send(uint16_t value);
void USART2SendBuf(void);

void USART2_LOOP( void );

void USART2_Config( void );
#endif




