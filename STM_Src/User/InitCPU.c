#include "InitCPU.h"



#include "stm32f10x.h"
#include "user_Config.h"                  //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下




/********************************************************************
				与LED灯相关的GPIO初始化函数
********************************************************************/
void GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;     												//定义一个结构体变量GPIO_InitStructure，用于初始化GPIO操作
	  /* 配置LED灯使用的GPIO管脚模式，输出模式，灌电流驱动*/
  	RCC_APB2PeriphClockCmd(RCC_GPIO_LED8, ENABLE); 					//使能LED灯使用的GPIO时钟
  	GPIO_InitStructure.GPIO_Pin = DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN; //使用PC0~PC7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO工作在输出模式
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_LED8, &GPIO_InitStructure);  						//相关的GPIO口初始化
  	GPIO_SetBits(GPIO_LED8,DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN);//关闭所有的LED指示灯
}


/********************************************************************
				配置中断向量表基地址
********************************************************************/

void NVIC_Config(void)
{

}






void InitCPU( ){
	GPIO_Config( );															//GPIO初始化配置，配置LED灯GPIO口
	
	NVIC_Config( );															//配置USART2中断
	
	USART1_Config( );
	USART2_Config( );
	USART3_Config( );
}

