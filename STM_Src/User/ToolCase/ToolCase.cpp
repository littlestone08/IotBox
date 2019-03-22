#include "stdio.h"
#include "rtl.h"
#include "ToolCase.h"
#include "bsp.h"
#include "RF200_Drv.h"



namespace TOOLCASE{
	
CToolCase::CToolCase(){

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

void CToolCase::dbg_commu_test()
{
	uint8_t x = 0x15;
	m_status = tcsUnkown;		
	m_FrameGenToPC.Begin(g_USART2_tx_buf, USART2_TX_BUF_SIZE);
	m_FrameGenToPC.Push(&x, 1);
	m_FrameGenToPC.End(ccInfo, itTest);	
	
	g_USART2_tx_wishtrans = m_FrameGenToPC.Size();	
	USART2SendBuf( );
}

void CToolCase::report_tool_list()
{
	printf("CToolCase::report_tool_list called\n");
	if (m_FrameGenToPC.Begin(g_USART2_tx_buf, USART2_TX_BUF_SIZE))
	{
		TOOL_t tool;
		uint8_t temp;
		
		temp = (uint8_t)m_status;		
		m_FrameGenToPC.Push(&temp, 1);
		
		temp = m_tools.count();
		m_FrameGenToPC.Push(&temp, 1);
		for(uint8_t i = 0; i < m_tools.count(); i++)
		{
			tool = m_tools[i];
			m_FrameGenToPC.Push((uint8_t*)&tool, sizeof(tool));
		}
		
		m_FrameGenToPC.End(ccInfo, itToolList);	
		
		g_USART2_tx_wishtrans = m_FrameGenToPC.Size();	
		USART2SendBuf( );		
	}
}

void CToolCase::refresh_tools()
{
	//uint8_t InventCMD[]=	{0xBB,0x00,0x27,0x00,0x03,0x22,0x00,0x10,0x5C,0x7E};	 //10次
		uint8_t InventCMD[] = {0xBB,0x00,0x27,0x00,0x03,0x22,0xFF,0xFF,0x4A,0x7E};   //65535次
		uint8_t StopMultiInventCMD[]=	{0xBB,0x00,0x28,0x00,0x00,0x28,0x7E };
	m_tools.clear();
	RFID_SendCmdFrame(InventCMD);
	//RFID_SendCmdFrame(SingleInventCMD);
	os_dly_wait(1000);
	RFID_SendCmdFrame(StopMultiInventCMD);

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
	new_item.SetValue(RSSI, PC, EPC);
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
bool CFrameGen::Begin(uint8_t *PtrBuf, const uint8_t MaxBufSize)
{
	if (m_Processing) return false;
	
	m_PtrBufRef = PtrBuf;
	m_MaxBufSize = MaxBufSize;
	m_RearIndex = 0;
	
	m_PtrBufRef[m_RearIndex++] = 0xBB;
	m_PtrBufRef[m_RearIndex++] = 0x00; //type 域占位
	m_PtrBufRef[m_RearIndex++] = 0x00; //Cmd 域占位
	m_PtrBufRef[m_RearIndex++] = 0x00; //PARAMLen(H) 域占位
 	m_PtrBufRef[m_RearIndex++] = 0x00; //PARAMLen(L) 域占位
	m_Processing = true;
	return true;
};

void CFrameGen::End(CmdCode cmd_code, uint8_t info_type)
{
	uint16_t Param_Len = m_RearIndex  + 2 - 7;
	
	if (m_Processing)
	{
		//补充TYPE、CMD域，校验域和帧尾
		m_PtrBufRef[1] = uint8_t(cmd_code);
		m_PtrBufRef[2] = uint8_t(info_type);
		m_PtrBufRef[3] = Param_Len >> 8;
		m_PtrBufRef[4] = Param_Len;
		
		{//补充校验域
		uint8_t check_sum = m_PtrBufRef[1];
		for(uint16_t i = 2; i <= m_RearIndex - 1; i++)
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
