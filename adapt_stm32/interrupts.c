#include "calendar_com.h"
#include "calendar_cfg.h"
#include "trace_out.h"
#include "sun_com.h"
#include "led_com.h"

#include "CMSIS/device/stm32f103xb.h"


static uint8_t f_intensity = 0U;
void RTC_IRQHandler(void) 
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
    //RTC_ISR2->WUTF = 0; /* acknowledge*/
}

