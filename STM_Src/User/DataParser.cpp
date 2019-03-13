#include "stdint.h"
#include "DataParser.h"
#include "CQ3.h"
#include "RF200_Drv.h"
#include "ToolCase.h"

using namespace TOOLCASE;

__EXTERN CToolCase *pToolCase;
void Parser_RFID_Respond(){
	
//要注意CQ3可不可以容得下RFID可能的最大数据长度
/*
Header Type Command PL(MSB) PL(LSB) Parameter Checksum End
BB 		  00 			07 		00 			01 			  01 				09 	 7E
	
帧头 					Header: 			0xBB
帧类型 				Type: 				0x00
指令代码 			Command: 			0x07
指令参数长度 	PL: 					0x0001
指令参数 			Parameter: 		0x01
校验位 				Checksum: 		0x09
帧尾 					End: 					0x7E
*/
	if (pToolCase == NULL) return;

  while ((CQ3_COUNT() >= 0x04) && (CQ3(0) != 0xBB))
  {    
      CQ3_D1();
  }
  
	if (CQ3_COUNT() >= 0x04){		
		
		#define RFID_TYPE 				(CQ3(1))								
		#define RFID_COMMAND 			(CQ3(2))
		#define RFID_PARA_LEN     (((uint16_t)CQ3(3) << 8) | CQ3(4))
		#define RFID_FRAME_LEN  	(RFID_PARA_LEN + 7)	
		
		if (RFID_FRAME_LEN <= _CQ3_SIZE)
		{ 
			if (CQ3_COUNT() >= RFID_FRAME_LEN)
			{ //已经接收到了本帧的全部
				uint16_t param_len = RFID_PARA_LEN;
				uint8_t rfid_type = RFID_TYPE;
				uint8_t check_sum = CQ3(1);
				
				for(uint8_t i = 2; i < RFID_FRAME_LEN - 2; i++) 
					check_sum += CQ3(i);
				
				if (check_sum == CQ3(RFID_FRAME_LEN - 2)){
					
					switch (rfid_type)
					{
						case FRAME_CMD: //上位机给下位机
							break;
						case FRAME_INFO://下位机给上位机的通知
							if (((RFID_COMMAND == CMD_SINGLE_ID) || (RFID_COMMAND == CMD_MULTI_ID)) && 
								(param_len == 0x0011))
							{
								static uint8_t epc_value[12];
								for(uint8_t i = 0; i < 12; i++) epc_value[i] = CQ3(i + 8);
								pToolCase->get_tools().push(CQ3(5), (uint16_t)CQ3(6) | CQ3(7),	epc_value);
							}
							break;
						case FRAME_RES://下位机给上位机的响应
							break;
						case FRAME_ERROR://下位机给上位机的错误 帧
							if (param_len == 0x0001)
							{
								#ifdef _PROCESS_ERROR_CODE
								fail_code error_code = (fail_code)CQ3(5);
								#endif
								pToolCase->get_tools().push_error();
							}
							break;					
						default:;
					}					
				}
				CQ3_DN(RFID_FRAME_LEN);
			}
			else
			{
				//等待
			}
		}
		else
		{ //将要接收的帧已经要超出了接收缓冲的最大长度
			//不接收此帧，清除掉已经接收的数据
			CQ3_DN(CQ3_COUNT( ));
		}
		


		#undef RFID_TYPE
		#undef RFID_COMMAND
		#undef RFID_FRAME_LEN

	}
}
