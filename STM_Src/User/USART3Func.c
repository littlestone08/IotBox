
#include "USART3Func.h"
#include "CQ3.h"



uint8_t	*g_USART3_tx_buf_ptr = 0;

uint8_t  g_USART3_tx_buf[USART3_TX_BUF_SIZE] = {0xA6};
  
uint8_t g_USART3_tx_wishtrans = 0;

uint8_t s_USART3_tx_index = 0;

bool g_USART3_sending = 0; 






/*******************************************************************************
** 函数名: USART3_Config()
** 功能:   串口配置为双工收发模式，接收波特率为9600
*******************************************************************************/
void USART3_Config(void)
{
		#define BAUD					115200
		
		//************************RCC**************************************	
		{
	  /*GPIOA Periph clock enable*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /*USART3 Periph clock enable*/		
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
		}

		//************************GPIO**************************************	
		{
		GPIO_InitTypeDef GPIO_InitStructure;			//声明GPIO初始化结构体
			
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
			
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
  	GPIO_Init(GPIOB, &GPIO_InitStructure);			
		}
		
		//************************NVIC**************************************
		{
		NVIC_InitTypeDef NVIC_InitStructure;

		/* Configure the NVIC Preemption Priority Bits */  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		
		/* Enable the USART3 Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);		
		}
		
		
		//************************USART**************************************
		{
		USART_InitTypeDef USART_InitStructure; 
	  USART_InitStructure.USART_BaudRate = BAUD;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  	USART_Init(USART3, &USART_InitStructure);
		}

		//***********************INTERRUPT FLAGS*******************************
	  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  	//USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
  	USART_Cmd(USART3, ENABLE);
		#undef BAUD
}



/********************************************************************
                      初始化
********************************************************************/
     
void USART3SendBuf(){
  //RS485CTR_SET();
	if (( g_USART3_sending == 0 ) && ( s_USART3_tx_index < g_USART3_tx_wishtrans )){
		USART_ITConfig(USART3, USART_IT_TC,  ENABLE);
		g_USART3_sending = 1;		
	}	
}



/********************************************************************
                      USART3中断
********************************************************************/
void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
  {   
    if ((s_USART3_tx_index < g_USART3_tx_wishtrans) && (g_USART3_tx_buf_ptr != 0))
    {
      //RS485CTR_SET();                                       //发送状态，CTR为高      
      USART_SendData(USART3, g_USART3_tx_buf_ptr[s_USART3_tx_index++]); 			//将键值发送到从机  
    }
    else
    {
      USART_ITConfig(USART3, USART_IT_TC,  DISABLE);
      //RS485CTR_CLR();																	      //接收状态，CTR为低            
      g_USART3_tx_wishtrans = s_USART3_tx_index = 0;
			g_USART3_sending = 0;
			g_USART3_tx_buf_ptr = 0;
    }
  }
  
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    uint16_t RecvChar = USART_ReceiveData(USART3);
    if (!CQ3_FULL())
      CQ3_EN(RecvChar);
  }
}


/********************************************************************
                      USART3 ECHO DEMO
********************************************************************/

//收到的数原样返回
void USART3_LOOP(){
	uint8_t n = 0;
	
	while(g_USART3_sending == 1);		
	
	while(CQ3_COUNT( ) > 0){
		if (n < USART3_TX_BUF_SIZE){
			g_USART3_tx_buf[n++] = CQ3(0);
			CQ3_D1();				
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

//发送nCount个字节
void USART3_send( uint8_t nCount, uint8_t *ptr){
	if ( g_USART3_sending == 0 ){
		g_USART3_tx_buf_ptr = ptr;
		s_USART3_tx_index = 0;
		g_USART3_tx_wishtrans = nCount;
		
		USART3SendBuf( );
	}
}

