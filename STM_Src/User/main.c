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
#include "stm32f10x.h"                   //STM32器件寄存器定义头文件，必须包含
#include "user_Config.h"                  //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "InitCPU.h"
#include "test.h"






/********************************************************************
				普通延时函数
********************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}



/********************************************************************
				LED灯闪烁三次
********************************************************************/
void Runing_LED8(void)
{
	u8 i=0;
	for(i=0;i<3;i++)
	{
		GPIO_Write(GPIO_LED8,0x00);
		Delay(0x3fffff);
		GPIO_Write(GPIO_LED8,0xFF);
		Delay(0x3fffff);
	}
}



/********************************************************************
                      主函数
********************************************************************/
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
	while(1){	
//		USART1_LOOP();
//		USART2_LOOP();		
//		USART3_LOOP();
		
		USART3_REDIRECT_USART2( );
		USART2_REDIRECT_USART3( );		
	};
	
}



