#ifndef _TOOLCASE_H_
#define _TOOLCASE_H_

#include <stdint.h>
#include <vector>

namespace TOOLCASE{
	

typedef enum {tcsUnkown = 0, tcsOpen, tcsClose} ToolCaseStatusDef;




typedef struct {	
	uint8_t RSSI;
	uint16_t 	PC;
	uint8_t 	EPC[12];	
} TOOL_t;
//======================工具列表=======================
class CTools{
private:
	typedef struct {	
		uint32_t RSSI_Sigma;
		uint16_t RSSI_SigmaCount;	
		uint16_t 	PC;
		uint8_t 	EPC[12];	
				
		void SetValue(const uint16_t PC_value, const uint8_t *EPC_value){
			for(uint8_t i = 0; i < 12; i++)	EPC[i] = EPC_value[i];
			PC = PC_value;
			RSSI_SigmaCount = RSSI_Sigma = 0;
		}
		
		bool Same(const uint16_t PC_value, const uint8_t *EPC_value){
			if (PC != PC_value) 
				return false;
			
			for( uint8_t i = 0; i < 12; i++){
				if (EPC[i] != EPC_value[i]){
					return false;
				}
			}
			return true;
		}
	} ToolInfoEx_t;
	
	typedef std::vector<ToolInfoEx_t>       ToolVector_t;
	typedef ToolVector_t::iterator 					ToolVectorItr;
private:	
	ToolVector_t m_Tools; 
	uint8_t 			m_invalid_respond_cnt;
public:
	CTools();
	~CTools();
	void push(const uint8_t RSSI, uint16_t PC, uint8_t* EPC);
	void clear(){ m_Tools.clear(); m_invalid_respond_cnt = 0;}
	uint8_t count(){return m_Tools.size();}
  TOOL_t operator[](const uint8_t index);
};



//======================工具箱=======================

class CToolCase {
public:
	CToolCase();
	~CToolCase();
	ToolCaseStatusDef getStatus(void);
	void setBoxStatus(const ToolCaseStatusDef value);

	uint8_t tool_count();
	
public:
	void print_version();
private:
	ToolCaseStatusDef m_status;
	
};

}
#endif
