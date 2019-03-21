#include "stm32f10x.h"
#include "BoxActionSensor.h"
#include "KEYMACRO_RTL.h"
#include "stdbool.h"

#include "bsp.h"

//GPIOD.1作为开关检测
#define RCC_GPIO_SENSOR RCC_APB2Periph_GPIOD
#define GPIO_SENSOR GPIOD
#define GPIO_SENDSOR_PIN GPIO_Pin_1

void SensorSWInit(){
		GPIO_InitTypeDef GPIO_InitStructure;
		#ifdef DMSTM_BOARD		
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_SENSOR, &GPIO_InitStructure);  						//相关的GPIO口初始化
	
		GPIO_SetBits(GPIO_SENSOR, GPIO_SENDSOR_PIN);
	
		#else
	 
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 					
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				    //GPIO伽胤諝摔色鸭亍模式
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIOC, &GPIO_InitStructure);  	
		
  	GPIO_SetBits(GPIOC, GPIO_Pin_14); 	
		#endif
}


void LED_KEY_Init(){
		/*8个LED接口定义*/
		#ifdef DMSTM_BOARD
		#define RCC_GPIO_LED8                   RCC_APB2Periph_GPIOC    //LED使用的GPIO时钟
		#define LEDn                            8                       //LED数量为8
		#define GPIO_LED8                       GPIOC                   //LED使用的GPIO为PC

		#define DS1_PIN                         GPIO_Pin_0             	//DS1使用的GPIO管脚
		#define DS2_PIN                         GPIO_Pin_1							//DS2使用的GPIO管脚
		#define DS3_PIN                         GPIO_Pin_2  						//DS3使用的GPIO管脚
		#define DS4_PIN                         GPIO_Pin_3							//DS4使用的GPIO管脚
		#define DS5_PIN                         GPIO_Pin_4             	//DS5使用的GPIO管脚
		#define DS6_PIN                         GPIO_Pin_5							//DS6使用的GPIO管脚
		#define DS7_PIN                         GPIO_Pin_6  						//DS7使用的GPIO管脚
		#define DS8_PIN                         GPIO_Pin_7							//DS8使用的GPIO管脚

		/*4个KEY按键接口定义*/
		#define RCC_GPIO_KEY4                   RCC_APB2Periph_GPIOB    //KEY按键使用的GPIO时钟
		#define Sn                              4                       //KEY按键数量为8
		#define GPIO_KEY4                       GPIOB                   //KEY按键使用的GPIO为PB

		#define S1_PIN                         GPIO_Pin_12             	//S1使用的GPIO管脚
		#define S2_PIN                         GPIO_Pin_13							//S2使用的GPIO管脚
		#define S3_PIN                         GPIO_Pin_14  						//S3使用的GPIO管脚
		#define S4_PIN                         GPIO_Pin_15							//S4使用的GPIO管脚	
		
		GPIO_InitTypeDef GPIO_InitStructure;
		
  	RCC_APB2PeriphClockCmd(RCC_GPIO_LED8, ENABLE); 					
  	GPIO_InitStructure.GPIO_Pin = DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN; //使用PC0~PC7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_LED8, &GPIO_InitStructure);  						
  	GPIO_SetBits(GPIO_LED8,DS1_PIN|DS2_PIN|DS3_PIN|DS4_PIN|DS5_PIN|DS6_PIN|DS7_PIN|DS8_PIN);
	
	 
  	RCC_APB2PeriphClockCmd(RCC_GPIO_KEY4, ENABLE); 					
  	GPIO_InitStructure.GPIO_Pin = S1_PIN|S2_PIN|S3_PIN|S4_PIN; //使用PB12~PB15
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				    //GPIO工作在输入悬浮模式
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIO_KEY4, &GPIO_InitStructure);  						
  	GPIO_SetBits(GPIO_LED8,S1_PIN|S2_PIN|S3_PIN|S4_PIN);    
		#else
		///led init
		GPIO_InitTypeDef GPIO_InitStructure;
		
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 					
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //使詢PC0~PC7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  	GPIO_Init(GPIOC, &GPIO_InitStructure);  						
  	GPIO_SetBits(GPIOC, GPIO_Pin_13);
 		
		#endif
}


void KEY_Dec(void)
{

#define KEY_S2_DETERMINE_EXP() (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) == 0)

#define TIMER_ROUTE()
#define KEY_DOWN_ACTION() 	(printf("SW DOWN\n"), set_toolcase_status(1))

#define KEY_UP_ACTION()			(printf("SW   UP\n"), set_toolcase_status(2))

	
SCAN_KEY(KEY_S2_DETERMINE_EXP(), KEY_DOWN_ACTION(),KEY_UP_ACTION(), TIMER_ROUTE());

}
