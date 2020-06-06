
#ifndef TRACE_CFG_H
#define TRACE_CFG_H

#include "stdint.h"

#include "trace_com.h"


void trace_00(const TRACE_LEVEL level, const char pMsg[], const char pFile[], const int line);
void trace_01(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1, const char pFile[], const int line);
void trace_02(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1,const uint32_t par2, const char pFile[], const int line);
void trace_03(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1,const uint32_t par2,const uint32_t par3, const char pFile[], const int line);


#define TRACE_00(level,pMsg)  trace_00(level,pMsg, __FILE__,__LINE__)
#define TRACE_01(level,pMsg,par1) trace_01(level,pMsg,par1,__FILE__,__LINE__)
#define TRACE_02(level,pMsg,par1,par2) trace_02(level,pMsg,par1,par2,__FILE__,__LINE__)
#define TRACE_03(level,pMsg,par1,par2,par3) trace_03(level,pMsg,par1,par2,par3,__FILE__,__LINE__)


#endif // !TRACE_CFG_H

