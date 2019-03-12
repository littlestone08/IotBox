#include "stdio.h"
#include "rtl.h"
#include "ToolCase.h"
#include "bsp.h"






namespace TOOLCASE{
CToolCase::CToolCase(){
	m_status = tcsUnkown;		
};

CToolCase::~CToolCase(){
	printf("ToolBox destrucvtor\n");
};


void CToolCase::setBoxStatus(const ToolCaseStatusDef value){
	if (m_status != value){
		//os_tmr_create(1000, 1); //trigger the timer after 1 sec
		m_status = value;
//		os_evt_set(0x0001, id_task_tool_check);		
		
		if (value == tcsOpen)
			os_evt_set(0x0001, id_rfid_check);
		else if (value == tcsClose)
			os_evt_set(0x0002, id_rfid_check);
	}
};

ToolCaseStatusDef CToolCase::getStatus(void){
	return (m_status);
};
void CToolCase::print_version(void){
	printf("This is ToolBox version 0.1\n");
}


}
