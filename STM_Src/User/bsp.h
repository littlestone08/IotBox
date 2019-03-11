#ifndef _BSP_H_
#define _BSP_H_

typedef enum {bsUnkown = 0, bsOpen, bsClose} BoxStatusDef;

typedef struct {
	BoxStatusDef status;
		
} BoxInfoDef;


BoxInfoDef g_BoxInfo;

#endif
