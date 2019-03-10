#ifndef _KEY_MACRO_H_
#define _KEY_MACRO_H_
#include "rtl.h"

/*****************************************
*
*
*
*2013.10.28  1.���򰴼����꣬ȥ��Trap��
			 2.tick1_ms��tick2_ms��ȫ�ֺ�����Ϊ�ֲ�������������Ƕ�׵���
*******************************************/

#define delay_ms() os_dly_wait (1000)

//����û��ʾ��������DELAY��ʵ��ʱ�䣬���������DELAY_MS�ƺ��͵���ʱ�ľ��鲻����ʱ�䳤�˺þã���ĳЩ�ط�ȴ��һ�µ�
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










