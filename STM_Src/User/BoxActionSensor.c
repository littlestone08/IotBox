#include "stm32f10x.h"
#include "BoxActionSensor.h"
#include "KEYMACRO_RTL.h"
#include "stdbool.h"

#include "bsp.h"

//GPIOD.1��Ϊ���ؼ��
#define RCC_GPIO_SENSOR RCC_APB2Periph_GPIOD
#define GPIO_SENSOR GPIOD
#define GPIO_SENDSOR_PIN GPIO_Pin_1

void SensorSWInit(){
		GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_SENSOR, &GPIO_InitStructure);  						//��ص�GPIO�ڳ�ʼ��
	
		GPIO_SetBits(GPIO_SENSOR, GPIO_SENDSOR_PIN);
}


void LED_KEY_Init(){
		/*8��LED�ӿڶ���*/
		#define RCC_GPIO_LED8                   RCC_APB2Periph_GPIOC    //LEDʹ�õ�GPIOʱ��
		#define LEDn                            8                       //LED����Ϊ8
		#define GPIO_LED8                       GPIOC                   //LEDʹ�õ�GPIOΪPC

		#define DS1_PIN                         GPIO_Pin_0             	//DS1ʹ�õ�GPIO�ܽ�
		#define DS2_PIN                         GPIO_Pin_1							//DS2ʹ�õ�GPIO�ܽ�
		#define DS3_PIN                         GPIO_Pin_2  						//DS3ʹ�õ�GPIO�ܽ�
		#define DS4_PIN                         GPIO_Pin_3							//DS4ʹ�õ�GPIO�ܽ�
		#define DS5_PIN                         GPIO_Pin_4             	//DS5ʹ�õ�GPIO�ܽ�
		#define DS6_PIN                         GPIO_Pin_5							//DS6ʹ�õ�GPIO�ܽ�
		#define DS7_PIN                         GPIO_Pin_6  						//DS7ʹ�õ�GPIO�ܽ�
		#define DS8_PIN                         GPIO_Pin_7							//DS8ʹ�õ�GPIO�ܽ�

		/*4��KEY�����ӿڶ���*/
		#define RCC_GPIO_KEY4                   RCC_APB2Periph_GPIOB    //KEY����ʹ�õ�GPIOʱ��
		#define Sn                              4                       //KEY��������Ϊ8
		#define GPIO_KEY4                       GPIOB                   //KEY����ʹ�õ�GPIOΪPB

		#define S1_PIN                         GPIO_Pin_12             	//S1ʹ�õ�GPIO�ܽ�
		#define S2_PIN                         GPIO_Pin_13							//S2ʹ�õ�GPIO�ܽ�
		#define S3_PIN                         GPIO_Pin_14  						//S3ʹ�õ�GPIO�ܽ�
		#define S4_PIN                         GPIO_Pin_15							//S4ʹ�õ�GPIO�ܽ�	
		
		GPIO_InitTypeDef GPIO_InitStructure;
		
  	RCC_APB2PeriphClockCmd(RCC_GPIO_LED8, ENABLE); 					
  	GPIO_InitStructure.GPIO_Pin = DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN; //ʹ��PC0~PC7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_LED8, &GPIO_InitStructure);  						
  	GPIO_SetBits(GPIO_LED8,DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN);
	
	 
  	RCC_APB2PeriphClockCmd(RCC_GPIO_KEY4, ENABLE); 					
  	GPIO_InitStructure.GPIO_Pin = S1_PIN|S2_PIN|S3_PIN|S4_PIN; //ʹ��PB12~PB15
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				    //GPIO��������������ģʽ
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_KEY4, &GPIO_InitStructure);  						
  	GPIO_SetBits(GPIO_LED8,S1_PIN|S2_PIN|S3_PIN|S4_PIN);    
		
}


void KEY_Dec(void)
{
//	if(GPIO_ReadInputDataBit(GPIO_KEY4, S1_PIN)==0) GPIO_ResetBits(GPIO_LED8,DS1_PIN); 	//����S1ʱDS1Ϩ��
//	else  GPIO_SetBits(GPIO_LED8,DS1_PIN);
//	
//	if(GPIO_ReadInputDataBit(GPIO_KEY4, S2_PIN)==0) GPIO_ResetBits(GPIO_LED8,DS2_PIN);	//����S2ʱDS2Ϩ��
//	else  GPIO_SetBits(GPIO_LED8,DS2_PIN);
//	
//	if(GPIO_ReadInputDataBit(GPIO_KEY4, S3_PIN)==0) GPIO_ResetBits(GPIO_LED8,DS3_PIN);	//����S3ʱDS3Ϩ��
//	else  GPIO_SetBits(GPIO_LED8,DS3_PIN);
//	
//	if(GPIO_ReadInputDataBit(GPIO_KEY4, S4_PIN)==0) GPIO_ResetBits(GPIO_LED8,DS4_PIN);	//����S4ʱDS4Ϩ��
//	else  GPIO_SetBits(GPIO_LED8,DS4_PIN);
//	


#define KEY_S2_DETERMINE_EXP() (GPIO_ReadInputDataBit(GPIO_KEY4, S2_PIN) == 0)



#define TIMER_ROUTE()
#define KEY_DOWN_ACTION() 	(printf("S2 DOWN\n"), os_evt_set(0x0001, id_rfid_check), set_toolcase_status(1))

#define KEY_UP_ACTION()			(printf("S2   UP\n"), os_evt_set(0x0001, id_rfid_check), set_toolcase_status(2))

	
SCAN_KEY(KEY_S2_DETERMINE_EXP(), KEY_DOWN_ACTION(),KEY_UP_ACTION(), TIMER_ROUTE());

}
