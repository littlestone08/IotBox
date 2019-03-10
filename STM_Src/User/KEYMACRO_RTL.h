#ifndef _KEY_MACRO_H_
#define _KEY_MACRO_H_
#include <stdbool.h>
#include <rtl.h>
	
#define KEY_UP(KEY)  (!(KEY)?(os_dly_wait(10), !(KEY) ? true : false) : (false))	
#define KEY_DOWN(KEY) ((KEY)?(os_dly_wait(10), (KEY) ? true : false) : (false))

#define  SCAN_KEY(KEY, KEY_DOWN_ACTION, KEY_UP_ACTION, TIMER_ROUTE ) 				\
do{																	\
	unsigned char tick1_10ms = 0;			\
	unsigned char tick2_10ms = 0;			\
	bool  pressed = false;						\
	while ( KEY_DOWN(KEY)){						\
		TIMER_ROUTE;										\
		if (pressed == 0 ){							\
			KEY_DOWN_ACTION;							\
			pressed = 1;									\
		}																\
		tick1_10ms++;										\
		if (tick1_10ms > 50){						\
			do{														\
				TIMER_ROUTE;								\
				if (++tick2_10ms > 20){			\
					KEY_DOWN_ACTION;					\
					tick2_10ms = 0;						\
				}														\
			}while (KEY_DOWN(KEY));				\
		}																\
	}																	\
	if (tick1_10ms > 0){							\
		KEY_UP_ACTION;									\
	}																	\
}while(0)


#endif










