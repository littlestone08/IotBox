#include "InitCPU.h"



#include "stm32f10x.h"
#include "user_Config.h"                  //�û�����ͷ�ļ�����������Ӳ��������Դ,λ����Ŀ�ļ�����



/********************************************************************
				�����ж����������ַ
********************************************************************/

void NVIC_Config(void)
{

}






void InitCPU( ){	
	
	NVIC_Config( );															//����USART2�ж�
	
	USART1_Config( );
	USART2_Config( );
	USART3_Config( );
}

