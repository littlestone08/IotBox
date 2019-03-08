
#include "Usart2Func.h"
#include "CQ2.h"


//������ʹ��RS485��D/Rʹ��GPIO�����ƣ�����ʹ��TC�жϣ������ݷ�����ɺ�ŷ�����һ������,
//������ʹ��RXE



uint8_t  g_USART2_tx_buf[USART2_TX_BUF_SIZE] = {0xA6};
  
uint8_t g_USART2_tx_wishtrans = 0;

uint8_t s_USART2_tx_index = 0;

bool g_USART2_sending = 0; 


/*
void USART2_Send(uint16_t value){
  RS485CTR_SET();														//����״̬��CTRΪ��
  USART_SendData(USART2, value); 			//����ֵ���͵��ӻ�
  
  //while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //�ȴ��������		
  //delay_ms(1); //���ʹ��TXE����ձ�־�� ��Ҫ��ʱ��ȷʵ�շ���ɺ�ſ���ת����ģʽ
  
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC ) == RESET); //�ȴ��������		
  USART_ClearFlag(USART2, USART_FLAG_TC);   
  RS485CTR_CLR();																	//����״̬��CTRΪ��
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�  
}
*/




/*******************************************************************************
** ������: USART2_Config()
** ����:   ��������Ϊ˫���շ�ģʽ�����ղ�����Ϊ9600
*******************************************************************************/
void USART2_Config(void)
{
		#define BAUD					115200
		
		//************************RCC**************************************	
		{
	  /*GPIOA Periph clock enable*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /*USART2 Periph clock enable*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_USART2, ENABLE);
		}

		//************************GPIO**************************************	
		{
		GPIO_InitTypeDef GPIO_InitStructure;			//����GPIO��ʼ���ṹ��
			
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
			
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;					
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
  	GPIO_Init(GPIOA, &GPIO_InitStructure);			
		}
		
		//************************NVIC**************************************
		{
		NVIC_InitTypeDef NVIC_InitStructure;

		/* Configure the NVIC Preemption Priority Bits */  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		
		/* Enable the USART1 Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
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
  
  	USART_Init(USART2, &USART_InitStructure);
		}

		//***********************INTERRUPT FLAGS*******************************
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  	//USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
  	USART_Cmd(USART2, ENABLE);
		#undef BAUD
}



/********************************************************************
                      ��ʼ��
********************************************************************/
     
void USART2SendBuf(){
  //RS485CTR_SET();
	if (( g_USART2_sending == 0 ) && ( s_USART2_tx_index < g_USART2_tx_wishtrans )){
		USART_ITConfig(USART2, USART_IT_TC,  ENABLE);
		g_USART2_sending = 1;		
	}	
}



/********************************************************************
                      ����2�ж�
********************************************************************/
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
  {   
    if (s_USART2_tx_index < g_USART2_tx_wishtrans)
    {      
      //RS485CTR_SET();                                       //����״̬��CTRΪ��      
      USART_SendData(USART2, g_USART2_tx_buf[s_USART2_tx_index++]); 			//����ֵ���͵��ӻ�  
    }
    else
    {
      USART_ITConfig(USART2, USART_IT_TC,  DISABLE);
      //RS485CTR_CLR();																	      //����״̬��CTRΪ��            
      g_USART2_tx_wishtrans = s_USART2_tx_index = 0;
			g_USART2_sending = 0;
    }
  }
  
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    uint16_t RecvChar = USART_ReceiveData(USART2);
    if (!CQ2_FULL())
      CQ2_EN(RecvChar);
  }
}


/********************************************************************
                      USART2 ECHO DEMO
********************************************************************/

//�յ�����ԭ������
void USART2_LOOP(){
	uint8_t n = 0;
	
	while(g_USART2_sending == 1);		
	
	while(CQ2_COUNT( ) > 0){
		if (n < USART2_TX_BUF_SIZE){
			g_USART2_tx_buf[n++] = CQ2(0);
			CQ2_D1();				
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

//����nCount���ֽ�
void usart2_send( uint8_t nCount){
	g_USART2_tx_wishtrans = nCount;
	USART2SendBuf( );
}
