#include "trace_cfg.h"
#include "stdio.h"




void trace_00(const TRACE_LEVEL level, const char pMsg[], const char pFile[], const int line)
{
    printf("Trace(%i)  in %s(%i): %s\n",level, pFile, line, pMsg);
}

void trace_01(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1, const char pFile[], const int line)
{
    printf("Trace(%i) in %s(%i): ",level, pFile, line);
    printf(pMsg, par1);
    printf("\n");
}

void trace_02(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1, const uint32_t par2, const char pFile[], const int line)
{
    printf("Trace(%i) in %s(%i): ",level, pFile, line);
    printf(pMsg, par1, par2);
    printf("\n");
}
void trace_03(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1, const uint32_t par2, const uint32_t par3, const char pFile[], const int line)
{
    printf("Trace(%i) in %s(%i): ",level, pFile, line);
    printf(pMsg, par1, par2, par3);
    printf("\n");
}
