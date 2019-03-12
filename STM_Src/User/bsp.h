#ifndef _BSP_H_
#define _BSP_H_

#include "rtl.h"
#include "stdio.h"
#include "stm32f10x.h"   
#include "USART3Func.h"


#ifdef __cplusplus
#define __EXTERN extern "C"
#else
#define __EXTERN extern
#endif

//using namespace TOOLCASE;

#define RFID_SendCmdFrame(ArrayX) USART3_send(ArrayX[4]+7, ArrayX)

__EXTERN OS_TID  id_dbg_coommand, id_uart_paser, id_key_detect, id_rfid_check;
__EXTERN void set_toolcase_status(uint8_t value);


#endif
