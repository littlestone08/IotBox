
#include "Usart1Func.h"
#include "CQ1.h"


//������ʹ��RS485��D/Rʹ��GPIO�����ƣ�����ʹ��TC�жϣ������ݷ�����ɺ�ŷ�����һ������,
//������ʹ��RXE



uint8_t  g_USART1_tx_buf[USART1_TX_BUF_SIZE] = {0x76};
  
uint8_t g_USART1_tx_wishtrans = 0;

uint8_t s_USART1_tx_index = 0;

bool g_USART1_sending = 0; 


/*
void USART1_Send(uint16_t value){
  RS485CTR_SET();														//����״̬��CTRΪ��
  USART_SendData(USART1, value); 			//����ֵ���͵��ӻ�
  
  //while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //�ȴ��������		
  //delay_ms(1); //���ʹ��TXE����ձ�־�� ��Ҫ��ʱ��ȷʵ�շ���ɺ�ſ���ת����ģʽ
  
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC ) == RESET); //�ȴ��������		
  USART_ClearFlag(USART1, USART_FLAG_TC);   
  RS485CTR_CLR();																	//����״̬��CTRΪ��
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�  
}
*/




/*******************************************************************************
** ������: USART1_Config()
** ����:   ��������Ϊ˫���շ�ģʽ�����ղ�����Ϊ9600
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
		
		GPIO_InitTypeDef GPIO_InitStructure;			//����GPIO��ʼ���ṹ��
	  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;					//����TX���ڵ�PA2�ܽ�
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //���ﲻ�ܴ�
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
                      ��ʼ��
********************************************************************/
     
void USART1SendBuf(){
  //RS485CTR_SET();
	if (( g_USART1_sending == 0 ) && ( s_USART1_tx_index < g_USART1_tx_wishtrans )){
		USART_ITConfig(USART1, USART_IT_TC,  ENABLE);
		g_USART1_sending = 1;		
	}	
}



/********************************************************************
                      USART�ж�
********************************************************************/
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
  {   
    if (s_USART1_tx_index < g_USART1_tx_wishtrans)
    {      
      //RS485CTR_SET();                                       //����״̬��CTRΪ��      
      USART_SendData(USART1, g_USART1_tx_buf[s_USART1_tx_index++]); 			//����ֵ���͵��ӻ�  
    }
    else
    {
      USART_ITConfig(USART1, USART_IT_TC,  DISABLE);
      //RS485CTR_CLR();																	      //����״̬��CTRΪ��            
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
                      ����1 ECHO DEMO
********************************************************************/

//�յ�����ԭ������
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

//����nCount���ֽ�
void USART1_send( uint8_t nCount){
	g_USART1_tx_wishtrans = nCount;
	USART1SendBuf( );
}
