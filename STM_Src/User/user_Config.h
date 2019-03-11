

#include "USART1Func.h"
#include "USART2Func.h"
#include "USART3Func.h"
#include "CQ1.h"
#include "CQ2.h"
#include "CQ3.h"




#include "BoxActionSensor.h"

///*8个LED接口定义*/
//#define RCC_GPIO_LED8                   RCC_APB2Periph_GPIOC    //LED使用的GPIO时钟
//#define LEDn                            8                       //LED数量为8
//#define GPIO_LED8                       GPIOC                   //LED使用的GPIO为PC

//#define DS1_PIN                         GPIO_Pin_0             	//DS1使用的GPIO管脚
//#define DS2_PIN                         GPIO_Pin_1							//DS2使用的GPIO管脚
//#define DS3_PIN                         GPIO_Pin_2  						//DS3使用的GPIO管脚
//#define DS4_PIN                         GPIO_Pin_3							//DS4使用的GPIO管脚
//#define DS5_PIN                         GPIO_Pin_4             	//DS5使用的GPIO管脚
//#define DS6_PIN                         GPIO_Pin_5							//DS6使用的GPIO管脚
//#define DS7_PIN                         GPIO_Pin_6  						//DS7使用的GPIO管脚
//#define DS8_PIN                         GPIO_Pin_7							//DS8使用的GPIO管脚

///*4个KEY按键接口定义*/
//#define RCC_GPIO_KEY4                   RCC_APB2Periph_GPIOB    //KEY按键使用的GPIO时钟
//#define Sn                              4                       //KEY按键数量为8
//#define GPIO_KEY4                       GPIOB                   //KEY按键使用的GPIO为PB

//#define S1_PIN                         GPIO_Pin_12             	//S1使用的GPIO管脚
//#define S2_PIN                         GPIO_Pin_13							//S2使用的GPIO管脚
//#define S3_PIN                         GPIO_Pin_14  						//S3使用的GPIO管脚
//#define S4_PIN                         GPIO_Pin_15							//S4使用的GPIO管脚


/*变量定义区*/

//GPIO_InitTypeDef GPIO_InitStructure;     												//定义一个结构体变量GPIO_InitStructure，用于初始化GPIO操作
//ErrorStatus HSEStartUpStatus;
//u8 count=0;

/*函数声明区*/

void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void LED_Runing(u8 LED_NUM);
void USART_Config(void);
void SEND_Data(u8 TXBUFFER);

