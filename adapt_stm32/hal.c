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

//void*
//_sbrk(int nbytes)
//{
//
//    /* The statically held previous end of the heap, with its initialization. */
//    static void* heap_ptr = (void*)&_end;         /* Previous end */
//
//    if ((stack - (heap_ptr + nbytes)) > _Min_Stack_Size)
//    {
//        void* base = heap_ptr;
//        heap_ptr += nbytes;
//
//        return  base;
//    }
//    else
//    {
//        errno = ENOMEM;
//        return  (void*)-1;
//    }
//}       /* _sbrk () */


//
//int _fstat(int file, struct stat* st)
//{
//	return 0;
//}
//
//int _wait(int* status)
//{
//	//errno = ECHILD;
//	return -1;
//}
//
//
//int _stat(char* file, struct stat* st)
//{
//	return 0;
//}
//
//int _link(char* old, char* new)
//{
//	//errno = EMLINK;
//	return -1;
//}
//
//int _fork(void)
//{
//	//errno = EAGAIN;
//	return -1;
//}
//
//int _execve(char* name, char** argv, char** env)
//{
//	//errno = ENOMEM;
//	return -1;
//}

#ifdef HAVE_INITFINI_ARRAY

/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start[]) (void) ;
extern void (*__preinit_array_end[]) (void) ;
extern void (*__init_array_start[]) (void);
extern void (*__init_array_end[]) (void) ;

extern void _init(void) __attribute__((weak));

///* Iterate over all the init routines.  */
//void
//__libc_init_array(void)
//{
//	size_t count;
//	size_t i;
//	size_t init_start, init_end;
//
//	count = __preinit_array_end - __preinit_array_start;
//	for (i = 0; i < count; i++)
//	{
//		__preinit_array_start[i]();
//	}
//
//	_init();
//
//	init_start = __init_array_start;
//	init_end = __init_array_end;
//	count = __init_array_end - __init_array_start;
//	for (i = 0; i < count; i++)
//	{
//		__init_array_start[i]();
//	}
//}
#endif
