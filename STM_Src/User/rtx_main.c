/********************************************************************
//DMSTM-L����Сϵͳ����صĴ����Է����ղ��Գ��򣬲�����Ϊ9600
//�ó������ڲ��԰��ص�MAX232ģ���Ƿ���������DB9ͷ��2��3��������ñ��·�����γ��Է����ջ�·
//���Ƚ�����ͨ��USART2���ͳ�ȥ�����Խ��ջ�·������յ�������ȷ���ٷ�һ�����ݣ��ٽ��գ������ȷ��ʾ����
//����������������ص�LED�ƻ���˸����
//ע�Ⲩ����Ҫ��������Ϊһ��,�����ʸ����ڴ��ڳ�ʼ�����ú�����
//�������ST�ٷ�����̼�����ʽ���汾ΪV3.50���ⲿ����8.000MHZ
//���Ի�����Keil MDK V4.60
//���ߣ�www.avrgcc.com
//ʱ�䣺2013.04.19
********************************************************************/

/********************************************************************
				����ͷ�ļ�
********************************************************************/
#include "rtl.h"
#include "stm32f10x.h"                   //STM32�����Ĵ�������ͷ�ļ����������
#include "user_Config.h"                  //�û�����ͷ�ļ�����������Ӳ��������Դ,λ����Ŀ�ļ�����
#include "InitCPU.h"
#include "test.h"




/********************************************************************
                      ������
********************************************************************/


OS_TID  id_led_key, id_uart_echo, id_task_uart_redirect;

__task void tsk_blink_task( void ){
	while(1){
		os_dly_wait (1000);
		GPIO_SetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
		os_dly_wait (1000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	}
}


__task void tsk_uart_echo( void ){
		USART1_LOOP();
		USART2_LOOP();		
		USART3_LOOP();
}


__task void tsk_uart_redirect( void ){
		id_task_uart_redirect = os_tsk_self( );
		id_led_key = os_tsk_create(tsk_blink_task, 1);
		
	
		while( 1 ){
			USART3_REDIRECT_USART2( );
			USART2_REDIRECT_USART3( );
		}
}

__task void led_key( void ){
	KEY_Dec();		
}
//		USART1_LOOP();
//		USART2_LOOP();		
//		USART3_LOOP();
int main(void)
{
	InitCPU( );
	
//	g_USART3_tx_buf[0] = 0x01;
//	g_USART3_tx_buf[1] = 0x02;
//	g_USART3_tx_buf[2] = 0x03;
//	g_USART3_tx_buf[3] = 0x04;
//	g_USART3_tx_buf[4] = 0x05;
//	g_USART3_tx_buf[5] = 0x06;
//	g_USART3_tx_buf[6] = 0x07;
//	
//	g_USART3_tx_wishtrans = 5;
//	USART3SendBuf( );
//	while(g_USART1_sending == 1);
//	g_USART1_tx_wishtrans = 6;
//	USART1SendBuf( );
	LED_KEY_Init();
	SensorSWInit( );	
	
	
	os_sys_init (tsk_uart_redirect);
	
	while(1){		
		
	};
	
}



