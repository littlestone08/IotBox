

#include "USART1Func.h"
#include "USART2Func.h"
#include "USART3Func.h"
#include "CQ1.h"
#include "CQ2.h"
#include "CQ3.h"




#include "BoxActionSensor.h"

///*8��LED�ӿڶ���*/
//#define RCC_GPIO_LED8                   RCC_APB2Periph_GPIOC    //LEDʹ�õ�GPIOʱ��
//#define LEDn                            8                       //LED����Ϊ8
//#define GPIO_LED8                       GPIOC                   //LEDʹ�õ�GPIOΪPC

//#define DS1_PIN                         GPIO_Pin_0             	//DS1ʹ�õ�GPIO�ܽ�
//#define DS2_PIN                         GPIO_Pin_1							//DS2ʹ�õ�GPIO�ܽ�
//#define DS3_PIN                         GPIO_Pin_2  						//DS3ʹ�õ�GPIO�ܽ�
//#define DS4_PIN                         GPIO_Pin_3							//DS4ʹ�õ�GPIO�ܽ�
//#define DS5_PIN                         GPIO_Pin_4             	//DS5ʹ�õ�GPIO�ܽ�
//#define DS6_PIN                         GPIO_Pin_5							//DS6ʹ�õ�GPIO�ܽ�
//#define DS7_PIN                         GPIO_Pin_6  						//DS7ʹ�õ�GPIO�ܽ�
//#define DS8_PIN                         GPIO_Pin_7							//DS8ʹ�õ�GPIO�ܽ�

///*4��KEY�����ӿڶ���*/
//#define RCC_GPIO_KEY4                   RCC_APB2Periph_GPIOB    //KEY����ʹ�õ�GPIOʱ��
//#define Sn                              4                       //KEY��������Ϊ8
//#define GPIO_KEY4                       GPIOB                   //KEY����ʹ�õ�GPIOΪPB

//#define S1_PIN                         GPIO_Pin_12             	//S1ʹ�õ�GPIO�ܽ�
//#define S2_PIN                         GPIO_Pin_13							//S2ʹ�õ�GPIO�ܽ�
//#define S3_PIN                         GPIO_Pin_14  						//S3ʹ�õ�GPIO�ܽ�
//#define S4_PIN                         GPIO_Pin_15							//S4ʹ�õ�GPIO�ܽ�


/*����������*/

//GPIO_InitTypeDef GPIO_InitStructure;     												//����һ���ṹ�����GPIO_InitStructure�����ڳ�ʼ��GPIO����
//ErrorStatus HSEStartUpStatus;
//u8 count=0;

/*����������*/

void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void LED_Runing(u8 LED_NUM);
void USART_Config(void);
void SEND_Data(u8 TXBUFFER);

