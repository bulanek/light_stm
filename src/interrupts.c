#include "stm8l.h"
#include "calendar_com.h"
#include "calendar_cfg.h"
#include "trace_out.h"
#include "sun_com.h"
#include "led_com.h"

void SPI_IRQHandler(void) __interrupt(SPI_IRQ_NO) 
{
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
}

static uint8_t f_intensity = 0U;
void _wakeupInterrupt(void) __interrupt(RTC_ALARM_IRQ_NO)
{
    CALENDAR_DATE_S date;
    CALENDAR_TIME_S time;

    TRACE_00(TRACE_LEVEL_LOG,"Wakeup interrupt");
    getCalendar(&date, &time);
    uint8_t intensity = getIntensity(&date, &time);
    if (f_intensity != intensity)
    {
        TRACE_02(TRACE_LEVEL_LOG,"New intensity: %i -> %i",f_intensity, intensity);
        f_intensity = intensity;
        sendIntensity(intensity);
    }
    RTC_ISR2->WUTF = 0; /* acknowledge*/
}

static uint8_t timer_overflow = 0;
void _overflowInterrupt(void) __interrupt(TIM1_UPDATE_OVERFLOW_TRIGER_IRQ)
{
    ++timer_overflow;
}

static uint8_t timer_capture = 0;
void _captureInterrupt(void) __interrupt(TIM1_CAPTURE_IRQ)
{
    ++timer_capture;
}

