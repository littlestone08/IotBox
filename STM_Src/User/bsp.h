#ifndef _BSP_H_
#define _BSP_H_
#include "rtl.h"
#include "stm32f10x.h"   

#ifdef __cplusplus
#define __EXTERN extern "C"
#else
#define __EXTERN extern
#endif

//using namespace TOOLCASE;

__EXTERN OS_TID  id_led_blink, id_key_detect, id_task_uart_redirect, id_task_tool_check;
__EXTERN void set_toolcase_status(uint8_t value);


#endif
