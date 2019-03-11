#include "stdio.h"
#include "rtl.h"
#include "ToolCase.h"
#include "bsp.h"






namespace TOOLCASE{
CToolCase::CToolCase(){
	m_status = tcsUnkown;		
};

CToolCase::~CToolCase(){
	printf("This is ToolBox version 0.1\n");
};


void CToolCase::setBoxStatus(const ToolCaseStatusDef value){
	if (m_status != value){
		//os_tmr_create(1000, 1); //trigger the timer after 1 sec
		os_evt_set(0x0003, id_task_tool_check);
	}
};

ToolCaseStatusDef CToolCase::getStatus(void){
	return (m_status);
};
void CToolCase::print_version(void){
	printf("This is ToolBox version 0.1\n");
}


}
