#ifndef _KEY_MACRO_H_
#define _KEY_MACRO_H_
#include "rtl.h"

/*****************************************
*
*
*
*2013.10.28  1.精简按键检测宏，去掉Trap宏
			 2.tick1_ms和tick2_ms由全局函数改为局部函数，以运行嵌套调用
*******************************************/

#define delay_ms() os_dly_wait (1000)

//由于没有示波器测试DELAY的实际时间，经过计算的DELAY_MS似乎和调试时的经验不符，时间长了好久，但某些地方却是一致的
#define DELAY_RATIO 1 
#define key_down(KEY) 						\
	(										\
	!(KEY)?(delay_ms(10), !(KEY)?1:0):(0)	\
	)


#define DOWN_ACTION

#define  scan_key(KEY, PRESSED_ACTION, TIMER_ROUTE ) 				\
do{																	\
	unsigned char tick1_10ms = 0;									\
	unsigned char tick2_10ms = 0;									\
	bit pressed = 0;											   	\
	while (key_down(KEY)){											\
		TIMER_ROUTE;												\
		if (pressed == 0 ){											\
			PRESSED_ACTION;											\
			pressed = 1;										 	\
		}														 	\
		tick1_10ms++;												\
		if (tick1_10ms > 50){										\
			do{														\
				TIMER_ROUTE;										\
				if (++tick2_10ms > 20){								\
					PRESSED_ACTION;									\
					tick2_10ms = 0;									\
				}													\
			}while (key_down(KEY));									\
		}else{														\
			DOWN_ACTION;											\
		}															\
	}																\
}while(0)

#define  scan_key_ex(KEY, KEY_DOWN_ACTION, KEY_UP_ACTION, TIMER_ROUTE ) 				\
do{																	\
	unsigned char tick1_10ms = 0;									\
	unsigned char tick2_10ms = 0;									\
	bit pressed = 0;											   	\
	while (key_down(KEY)){											\
		TIMER_ROUTE;												\
		if (pressed == 0 ){											\
			KEY_DOWN_ACTION;										\
			pressed = 1;										 	\
		}														 	\
		tick1_10ms++;												\
		if (tick1_10ms > 50){										\
			do{														\
				TIMER_ROUTE;										\
				if (++tick2_10ms > 20){								\
					KEY_DOWN_ACTION;								\
					tick2_10ms = 0;									\
				}													\
			}while (key_down(KEY));									\
		}															\
	}																\
	if (tick1_10ms > 0){											\
		KEY_UP_ACTION;												\
	}																\
}while(0)

#endif










