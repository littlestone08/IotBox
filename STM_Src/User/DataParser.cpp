#include "stdint.h"
#include "DataParser.h"
#include "CQ3.h"
#include "RF200_Drv.h"


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
  while ((CQ3_COUNT() >= 0x04) && (CQ3(0) != 0xBB))
  {    
      CQ3_D1();
  }
  
	if (CQ3_COUNT() >= 0x04){		
		
		#define RFID_TYPE 				(CQ3(1))								
		#define RFID_COMMAND 			(CQ3(2))
		#define RFID_FRAME_LEN  	(CQ3(3) + 7)	
		
		if (RFID_FRAME_LEN <= _CQ3_SIZE)
		{ 
			if (CQ3_COUNT() >= RFID_FRAME_LEN)
			{ //已经接收到了本帧的全部
				
				switch (RFID_TYPE)
				{
					case FRAME_CMD: //上位机给下位机			
						break;
					case FRAME_INFO://下位机给上位机的通知
						break;
					case FRAME_RES://下位机给上位机的响应
						break;
					case FRAME_ERROR://下位机给上位机的错误帧
						break;					
					default:;
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
	
  if ((CQ3(0) == 0xEB) && (CQ3_COUNT() >= 0x04))
  {
    uint8_t InfoType = CQ3(1);
    switch(InfoType)
    {
      case 0x90: //��Э����Ӧ
        {
          const uint8_t FrameLen = 0x07;
          
          if (CQ3_COUNT() >= FrameLen)
          {
            if (CQ3(FrameLen - 1) == 0xAA)
            {
              if ((CQ3(2) == 0x07) && (CQ3(3) == 0x01))
              {
                uint8_t Cmd = CQ3(4);
                if (Cmd == 0x41) //�ҽ��豸���صĲ����Ƿ�ɹ��Ľ������Ҫͨ��CAN�ϱ�
                {
								}
                
                CQ3_DN(FrameLen);
              }
            }
            else
            {
              CQ3_D1();
            }
          }
        }
        break;
 
      default:
      {
        CQ3_D1();
      }
    }
  }
}
