#include "stm32f1xx.h"
//#include "errno.h"
#include "sys/types.h"
#include "strings.h"
#include "errno.h"
#include "sys/_timeval.h"

/* Symbol defined by linker map */
extern int  _end;              /* start of free memory (as symbol) */

/* Value set by crt0.S */
extern void* stack;           /* end of free memory */

extern int _Min_Stack_Size  __asm("_Min_Stack_Size");
extern int _Min_Heap_Size __asm("_Min_Heap_Size");

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

void* _sbrk(int  incr) {

    int min_heap_size =(int) &_Min_Heap_Size;
    static char* heap_end;		/* Previous end of heap or 0 if none */
    char* prev_heap_end;

    if (0 == heap_end) {
        heap_end = &_end;			/* Initialize first time round */
    }

    prev_heap_end = heap_end;
    heap_end += incr;
    //check
    if (heap_end < (&_end + min_heap_size)) {

    }
    else {
        errno = ENOMEM;
        return (char*)-1;
    }
    return (void*)prev_heap_end;
}	/* _sbrk () */

int _close(int fd) {
    return -1;
}

int _lseek(int fd, int ptr, int dir) {
    (void)fd;
    (void)ptr;
    (void)dir;

    errno = EBADF;
    return -1;
}

int _fstat(int fd, struct stat* st) {
    errno = EBADF;
    return 0;
}

int _isatty(int fd) {
    errno = EBADF;
    return 0;
}

#include "sys/times.h"
extern uint32_t _clock;
int _times(struct tms* buf)
{
    buf->tms_utime = _clock;
    buf->tms_stime = _clock;
    buf->tms_cutime = _clock;
    buf->tms_cstime = _clock;

    return (int)buf->tms_utime;
}

extern uint32_t _timeSec;
int _gettimeofday(struct timeval* tv, void* tzvp)
{

    tv->tv_sec = _timeSec;
    tv->tv_usec = _timeSec;
    tv->tv_usec *= 1000000ULL;
    return 0;  // return non-zero for error
} // end _gettimeofday()

#ifdef HAVE_INITFINI_ARRAY

/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start[]) (void) ;
extern void (*__preinit_array_end[]) (void) ;
extern void (*__init_array_start[]) (void);
extern void (*__init_array_end[]) (void) ;

extern void _init(void) __attribute__((weak));

#endif
