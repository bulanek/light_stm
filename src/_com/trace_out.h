#ifndef TRACE_OUT_H
#define TRACE_OUT_H

#include "trace_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus*/

    /*! @brief  Trace with no parameters. */
#ifndef TRACE_00
    void TRACE_00(const TRACE_LEVEL level, const char pMsg[], const  std::experimental::source_location& location = std::experimental::source_location::current());
#endif

#ifndef TRACE_01
    void TRACE_01(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1, const  std::experimental::source_location& location = std::experimental::source_location::current());
#endif

#ifndef TRACE_02
    void TRACE_02(const TRACE_LEVEL level, const char pMsg[], const uint32_t par1, const uint32_t par2, const  std::experimental::source_location& location = std::experimental::source_location::current());
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus*/

#endif // !TRACE_OUT_H
