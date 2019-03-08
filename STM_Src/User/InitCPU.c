#include "InitCPU.h"



#include "stm32f10x.h"
#include "user_Config.h"                  //�û�����ͷ�ļ�����������Ӳ��������Դ,λ����Ŀ�ļ�����




/********************************************************************
				��LED����ص�GPIO��ʼ������
********************************************************************/
void GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;     												//����һ���ṹ�����GPIO_InitStructure�����ڳ�ʼ��GPIO����
	  /* ����LED��ʹ�õ�GPIO�ܽ�ģʽ�����ģʽ�����������*/
  	RCC_APB2PeriphClockCmd(RCC_GPIO_LED8, ENABLE); 					//ʹ��LED��ʹ�õ�GPIOʱ��
  	GPIO_InitStructure.GPIO_Pin = DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN; //ʹ��PC0~PC7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO���������ģʽ
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_LED8, &GPIO_InitStructure);  						//��ص�GPIO�ڳ�ʼ��
  	GPIO_SetBits(GPIO_LED8,DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN);//�ر����е�LEDָʾ��
}


/********************************************************************
				�����ж����������ַ
********************************************************************/

void NVIC_Config(void)
{

}






void InitCPU( ){
	GPIO_Config( );															//GPIO��ʼ�����ã�����LED��GPIO��
	
	NVIC_Config( );															//����USART2�ж�
	
	USART1_Config( );
	USART2_Config( );
	USART3_Config( );
}

