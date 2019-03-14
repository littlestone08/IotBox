#include "stdio.h"
#include "rtl.h"
#include "ToolCase.h"
#include "bsp.h"






namespace TOOLCASE{
CToolCase::CToolCase(){
	uint8_t x = 0x15;
	m_status = tcsUnkown;		
	m_FrameGenToPC.Begin(g_USART2_tx_buf, USART2_TX_BUF_SIZE);
	m_FrameGenToPC.Push(&x, 1);
	m_FrameGenToPC.End(0x01, 0xFF);
	
	g_USART2_tx_wishtrans = m_FrameGenToPC.Size();	
	USART2SendBuf( );
	
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


//======================帧形成=======================
void CFrameGen::Begin(uint8_t *PtrBuf, const uint8_t MaxBufSize)
{
	m_PtrBufRef = PtrBuf;
	m_MaxBufSize = MaxBufSize;
	m_RearIndex = 0;
	
	m_PtrBufRef[m_RearIndex++] = 0xBB;
	m_PtrBufRef[m_RearIndex++] = 0x00; //type 域占位
	m_PtrBufRef[m_RearIndex++] = 0x00; //Cmd 域占位
	m_PtrBufRef[m_RearIndex++] = 0x00; //PARAMLen(H) 域占位
 	m_PtrBufRef[m_RearIndex++] = 0x00; //PARAMLen(L) 域占位
	m_Processing = true;
};

void CFrameGen::End(uint8_t Type_Value, uint8_t Command_Value)
{
	uint16_t Param_Len = m_RearIndex  + 2 - 7;
	
	if (m_Processing)
	{
		//补充TYPE、CMD域，校验域和帧尾
		m_PtrBufRef[1] = Type_Value;
		m_PtrBufRef[2] = Command_Value;
		m_PtrBufRef[3] = Param_Len >> 8;
		m_PtrBufRef[4] = Param_Len;
		
		{//补充校验域
		uint8_t check_sum = Type_Value;
		for(uint16_t i = 2; i <= m_RearIndex; i++)
		{
			check_sum += m_PtrBufRef[i];			
		}
		m_PtrBufRef[m_RearIndex++] = check_sum;
		}
		
		m_PtrBufRef[m_RearIndex++] = 0x7E;
		//处理完成
		m_Processing = false;
	}
};

bool CFrameGen::Push(uint8_t *PtrBuf, const uint8_t Count)
{
	bool Succ = false;
	if (m_Processing)
	{		
		if (m_RearIndex + Count < m_MaxBufSize - 2 )
		{//需要留出帧尾和校验字节两个位置
			uint8_t i = 0;
			while (i < Count)	m_PtrBufRef[m_RearIndex++] = PtrBuf[i++];
			Succ = true;
		}
	}
	return Succ;
};


}
