
#ifndef _CQ3_H_
#define _CQ3_H_


//_CQ3_SIZE大小必须为POWER(2,N)，以便进行快速取模

#define _CQ3_SIZE 0x40

#define CQ3_MOD_MASK (_CQ3_SIZE - 1)
//#define CQ3_MOD_MASK 15

#ifdef  __C51__

#define DAT_SEG idata

#else
#define DAT_SEG 
#endif



extern unsigned char DAT_SEG _CQ3_items[_CQ3_SIZE];
extern unsigned char  _CQ3_front;
extern unsigned char  _CQ3_rear;
extern unsigned char  _CQ3_count;



#define CQ3_COUNT()         (_CQ3_count)
#define CQ3(index)          (_CQ3_items[(_CQ3_front + index) & CQ3_MOD_MASK])

#define CQ3_RST()           (_CQ3_front = _CQ3_rear = _CQ3_count = 0)
#define CQ3_EMPTY()         (_CQ3_count == 0)
#define CQ3_FULL()          (_CQ3_count == (_CQ3_SIZE))                        
#define CQ3_D1()            CQ3_DN(1)

#define CQ3_EN(x)  do{if (!CQ3_FULL()){                         \
                        _CQ3_count++;                           \
                        _CQ3_items[_CQ3_rear] = x;              \
                        _CQ3_rear = (_CQ3_rear + 1) & CQ3_MOD_MASK; \
                      }}while(0)

#define CQ3_DN(N)  do{                                              \
                      if (N >= _CQ3_count)                          \
                        CQ3_RST();	                            \
                      else{                                         \
                        _CQ3_count -= N;                            \
                        _CQ3_front = (_CQ3_front + N) & CQ3_MOD_MASK;   \
                      }                                             \
                   }while(0)
                    
#endif
