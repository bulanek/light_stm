#include "stm32f1xx.h"
//#include "errno.h"
#include "sys/types.h"
#include "strings.h"

/* Symbol defined by linker map */
extern int  _end;              /* start of free memory (as symbol) */

/* Value set by crt0.S */
extern void* stack;           /* end of free memory */

extern int _Min_Stack_Size;
extern char end __asm("end");


void enableInterrupt(void)
{
	__enable_irq();
}

void waitForInterrupt(void)
{
	__WFI();
}

int _read(int file, char* pData, int len)
{
    int bytes_read;

    for (bytes_read = 0; bytes_read < len; ++bytes_read)
    {
        while ((USART2->SR & USART_SR_RXNE) == 0U);
        *pData = (char)USART2->DR;
        ++pData;
        bytes_read = 1;
        break;
    }
    return bytes_read;
}

int _write(int file, char* pData, int len)
{
    char* pTmpData = pData;
    int bytes_written;
    for (bytes_written = 0; bytes_written < len; ++bytes_written)
    {
        while ((USART2->SR & USART_SR_TXE) == 0U);
        volatile uint8_t data = pTmpData[bytes_written];
        USART2->DR = data;
        if (pTmpData[bytes_written] == '\n')
        {
            while ((USART2->SR & USART_SR_TXE) == 0U);
            USART2->DR = '\r';
        }
    }
    return len;
}

#ifdef HAVE_INITFINI_ARRAY

/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start[]) (void) ;
extern void (*__preinit_array_end[]) (void) ;
extern void (*__init_array_start[]) (void);
extern void (*__init_array_end[]) (void) ;

extern void _init(void) __attribute__((weak));

#endif
