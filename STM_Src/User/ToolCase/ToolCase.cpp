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




CTools::CTools(){};

CTools::~CTools(){};

void CTools::push(const uint8_t RSSI, uint16_t PC, uint8_t* EPC){	
	//if found in vector, add RSSI and Count for average statistics, or push a 
	//new one to the vector;	
	for (ToolVectorItr itr = m_Tools.begin(); itr != m_Tools.end(); itr++){
		if ((itr->PC == PC) && (itr->Same(PC, EPC))) {
			itr->RSSI_Sigma += RSSI;
			itr->RSSI_SigmaCount++;
			return;			
		}
  }

	{
	ToolInfoEx_t new_item;
	new_item.SetValue(PC, EPC);
	m_Tools.push_back(new_item);
	}
};


TOOL_t CTools::operator[](const uint8_t index){
	TOOL_t item;
	ToolInfoEx_t tool_ex = this->m_Tools.at(index);
	
	item.PC = tool_ex.PC;
	for(uint8_t i = 0; i < 12; i++){
		item.EPC[i] = tool_ex.EPC[i];
	}
	
	item.RSSI = tool_ex.RSSI_Sigma / tool_ex.RSSI_SigmaCount;
	
	return item;
};

}
