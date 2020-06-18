#include "stm8l.h"
#include "calendar_com.h"
#include "calendar_cfg.h"
#include "trace_out.h"


void SPI_IRQHandler(void) __interrupt(SPI_IRQ_NO) 
{
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
}
void _wakeupInterrupt(void) __interrupt(RTC_ALARM_IRQ_NO)
{
    CALENDAR_DATE_S date;
    CALENDAR_TIME_S time;
    //TRACE_00(TRACE_LEVEL_LOG, "Trace in wakeupInterrupt");

    getCalendar(&date, &time);
    uint8_t intensity = getIntensity(&date, &time);
    //sendIntensity(intensity);
    RTC_ISR2->WUTF = 0;
}


