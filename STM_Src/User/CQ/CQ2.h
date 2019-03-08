
#ifndef _CQ2_H_
#define _CQ2_H_


//_CQ2_SIZE大小必须为POWER(2,N)，以便进行快速取模

#define _CQ2_SIZE 0x20

#define CQ2_MOD_MASK (_CQ2_SIZE - 1)
//#define CQ2_MOD_MASK 15

#ifdef  __C51__

#define DAT_SEG idata

#else
#define DAT_SEG 
#endif



extern unsigned char DAT_SEG _CQ2_items[_CQ2_SIZE];
extern unsigned char  _CQ2_front;
extern unsigned char  _CQ2_rear;
extern unsigned char  _CQ2_count;



#define CQ2_COUNT()         (_CQ2_count)
#define CQ2(index)          (_CQ2_items[(_CQ2_front + index) & CQ2_MOD_MASK])

#define CQ2_RST()           (_CQ2_front = _CQ2_rear = _CQ2_count = 0)
#define CQ2_EMPTY()         (_CQ2_count == 0)
#define CQ2_FULL()          (_CQ2_count == (_CQ2_SIZE))                        
#define CQ2_D1()            CQ2_DN(1)

#define CQ2_EN(x)  do{if (!CQ2_FULL()){                         \
                        _CQ2_count++;                           \
                        _CQ2_items[_CQ2_rear] = x;              \
                        _CQ2_rear = (_CQ2_rear + 1) & CQ2_MOD_MASK; \
                      }}while(0)

#define CQ2_DN(N)  do{                                              \
                      if (N >= _CQ2_count)                          \
                        CQ2_RST();	                            \
                      else{                                         \
                        _CQ2_count -= N;                            \
                        _CQ2_front = (_CQ2_front + N) & CQ2_MOD_MASK;   \
                      }                                             \
                   }while(0)
                    
#endif
