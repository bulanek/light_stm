#include "calendar_com.h"
#include "calendar_cfg.h"
#include "trace_out.h"
#include "sun_com.h"
#include "led_com.h"

#include "CMSIS/device/stm32f103xb.h"


static uint8_t f_intensity = 0U;
uint32_t _clock = 0;
uint32_t _timeSec = 0;

void RTC_IRQHandler(void)
{
    __disable_irq();
    ++_clock;
    ++_timeSec;
    __enable_irq();
    CALENDAR_DATE_S date;
    CALENDAR_TIME_S time;

    //TRACE_00(TRACE_LEVEL_LOG,"Second interrupt");
    getCalendar(&date, &time);
    uint8_t intensity = getIntensity(&date, &time);
    if (f_intensity != intensity)
    {
        TRACE_02(TRACE_LEVEL_LOG,"New intensity: %i -> %i",f_intensity, intensity);
        f_intensity = intensity;
        sendIntensity(intensity);
    }

    RTC->CRL &= ~RTC_CRL_SECF; /* ack*/
}
