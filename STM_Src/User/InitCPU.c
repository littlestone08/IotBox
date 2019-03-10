#include "InitCPU.h"



#include "stm32f10x.h"
#include "user_Config.h"                  //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下



/********************************************************************
				配置中断向量表基地址
********************************************************************/

void NVIC_Config(void)
{

}






void InitCPU( ){	
	
	NVIC_Config( );															//配置USART2中断
	
	USART1_Config( );
	USART2_Config( );
	USART3_Config( );
}

