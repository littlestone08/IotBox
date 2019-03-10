/********************************************************************
//DMSTM-L型最小系统板板载的串口自发自收测试程序，波特率为9600
//该程序用于测试板载的MAX232模块是否正常，将DB9头的2和3脚用跳线帽短路即可形成自发自收回路
//首先将数据通过USART2发送出去，再自接收回路，如果收到数据正确，再发一个数据，再接收，如果正确表示正常
//如果测试正常，板载的LED灯会闪烁三次
//注意波特率要两端设置为一致,波特率更改在串口初始化配置函数中
//程序采用ST官方外设固件库形式，版本为V3.50，外部晶振8.000MHZ
//调试环境：Keil MDK V4.60
//作者：www.avrgcc.com
//时间：2013.04.19
********************************************************************/

/********************************************************************
				包含头文件
********************************************************************/
#include "rtl.h"
#include "stm32f10x.h"                   //STM32器件寄存器定义头文件，必须包含
#include "user_Config.h"                  //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "InitCPU.h"
#include "test.h"




/********************************************************************
                      主函数
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



