#ifndef _TOOLCASE_H_
#define _TOOLCASE_H_



namespace TOOLCASE{
	
typedef enum {tcsUnkown = 0, tcsOpen, tcsClose} ToolCaseStatusDef;

//======================工具箱类=======================
class CToolCase {
public:
	CToolCase();
	~CToolCase();
	ToolCaseStatusDef getStatus(void);
	void setBoxStatus(const ToolCaseStatusDef value);
	void print_version();
private:
	ToolCaseStatusDef m_status;	
};

}
#endif
