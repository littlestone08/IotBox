#include "bsp.h"
#include "ToolCase.h"

OS_TID  id_led_blink, id_key_detect, id_task_uart_redirect, id_task_tool_check;

TOOLCASE::CToolCase *pToolCase = NULL;

extern "C"{	
	void set_toolcase_status(uint8_t value ){
		pToolCase->setBoxStatus((TOOLCASE::ToolCaseStatusDef)value);
	}
}
