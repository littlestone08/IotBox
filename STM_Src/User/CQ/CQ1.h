
#ifndef _CQ1_H_
#define _CQ1_H_


//_CQ1_SIZE大小必须为POWER(2,N)，以便进行快速取模

#define _CQ1_SIZE 0x20

#define CQ1_MOD_MASK (_CQ1_SIZE - 1)
//#define CQ1_MOD_MASK 15

#ifdef  __C51__

#define DAT_SEG idata

#else
#define DAT_SEG 
#endif



extern unsigned char DAT_SEG _CQ1_items[_CQ1_SIZE];
extern unsigned char  _CQ1_front;
extern unsigned char  _CQ1_rear;
extern unsigned char  _CQ1_count;



#define CQ1_COUNT()         (_CQ1_count)
#define CQ1(index)          (_CQ1_items[(_CQ1_front + index) & CQ1_MOD_MASK])

#define CQ1_RST()           (_CQ1_front = _CQ1_rear = _CQ1_count = 0)
#define CQ1_EMPTY()         (_CQ1_count == 0)
#define CQ1_FULL()          (_CQ1_count == (_CQ1_SIZE))                        
#define CQ1_D1()            CQ1_DN(1)

#define CQ1_EN(x)  do{if (!CQ1_FULL()){                         \
                        _CQ1_count++;                           \
                        _CQ1_items[_CQ1_rear] = x;              \
                        _CQ1_rear = (_CQ1_rear + 1) & CQ1_MOD_MASK; \
                      }}while(0)

#define CQ1_DN(N)  do{                                              \
                      if (N >= _CQ1_count)                          \
                        CQ1_RST();	                            \
                      else{                                         \
                        _CQ1_count -= N;                            \
                        _CQ1_front = (_CQ1_front + N) & CQ1_MOD_MASK;   \
                      }                                             \
                   }while(0)
                    
#endif
