#include "bsp.h"
#include "ToolCase.h"

OS_TID  id_dbg_coommand, id_key_detect, id_uart_paser, id_rfid_check;

TOOLCASE::CToolCase *pToolCase = NULL;

extern "C"{	
	void set_toolcase_status(uint8_t value ){
		pToolCase->setBoxStatus((TOOLCASE::ToolCaseStatusDef)value);
	}
}
