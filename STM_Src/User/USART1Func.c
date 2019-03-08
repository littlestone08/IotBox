
#include "Usart1Func.h"
#include "CQ1.h"


//由于是使用RS485，D/R使用GPIO来控制，所以使用TC中断，即数据发送完成后才发送下一个数据,
//而不是使用RXE



uint8_t  g_USART1_tx_buf[USART1_TX_BUF_SIZE] = {0x76};
  
uint8_t g_USART1_tx_wishtrans = 0;

uint8_t s_USART1_tx_index = 0;

bool g_USART1_sending = 0; 


/*
void USART1_Send(uint16_t value){
  RS485CTR_SET();														//发送状态，CTR为高
  USART_SendData(USART1, value); 			//将键值发送到从机
  
  //while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //等待发送完成		
  //delay_ms(1); //如何使用TXE缓冲空标志， 需要延时，确实收发完成后才可以转成收模式
  
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC ) == RESET); //等待发送完成		
  USART_ClearFlag(USART1, USART_FLAG_TC);   
  RS485CTR_CLR();																	//接收状态，CTR为低
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能接收中断  
}
*/




/*******************************************************************************
** 函数名: USART1_Config()
** 功能:   串口配置为双工收发模式，接收波特率为9600
*******************************************************************************/
void USART1_Config(void)
{
		#define BAUD					115200
		
		//************************RCC**************************************	
		{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE) ;
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE) ;
		}

		//************************GPIO**************************************	
		{
		
		GPIO_InitTypeDef GPIO_InitStructure;			//声明GPIO初始化结构体
	  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;					//配置TX所在的PA2管脚
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //这里不能错
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
			
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
  	GPIO_Init(GPIOA, &GPIO_InitStructure);			
		}
		
		//************************NVIC**************************************
		{
		NVIC_InitTypeDef NVIC_InitStructure;

		/* Configure the NVIC Preemption Priority Bits */  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		
		/* Enable the USART1 Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
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
  
  	USART_Init(USART1, &USART_InitStructure);
		}

		//***********************INTERRUPT FLAGS*******************************
	  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  	//USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
  	USART_Cmd(USART1, ENABLE);
		#undef BAUD
}



/********************************************************************
                      初始化
********************************************************************/
     
void USART1SendBuf(){
  //RS485CTR_SET();
	if (( g_USART1_sending == 0 ) && ( s_USART1_tx_index < g_USART1_tx_wishtrans )){
		USART_ITConfig(USART1, USART_IT_TC,  ENABLE);
		g_USART1_sending = 1;		
	}	
}



/********************************************************************
                      USART中断
********************************************************************/
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
  {   
    if (s_USART1_tx_index < g_USART1_tx_wishtrans)
    {      
      //RS485CTR_SET();                                       //发送状态，CTR为高      
      USART_SendData(USART1, g_USART1_tx_buf[s_USART1_tx_index++]); 			//将键值发送到从机  
    }
    else
    {
      USART_ITConfig(USART1, USART_IT_TC,  DISABLE);
      //RS485CTR_CLR();																	      //接收状态，CTR为低            
      g_USART1_tx_wishtrans = s_USART1_tx_index = 0;
			g_USART1_sending = 0;
    }
  }
  
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    uint16_t RecvChar = USART_ReceiveData(USART1);
    if (!CQ1_FULL())
      CQ1_EN(RecvChar);
  }
}


/********************************************************************
                      串口1 ECHO DEMO
********************************************************************/

//收到的数原样返回
void USART1_LOOP(){
	uint8_t n = 0;
	
	while(g_USART1_sending == 1);		
	
	while(CQ1_COUNT( ) > 0){
		if (n < USART1_TX_BUF_SIZE){
			g_USART1_tx_buf[n++] = CQ1(0);
			CQ1_D1();				
		}
		else{
			break;
		}		
	}
	
	if ( n > 0 ) {
		g_USART1_tx_wishtrans = n;	
		USART1SendBuf( );			
	}
}

//发送nCount个字节
void USART1_send( uint8_t nCount){
	g_USART1_tx_wishtrans = nCount;
	USART1SendBuf( );
}
