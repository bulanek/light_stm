#include "calendar_com.h"
#include "calendar_cfg.h"
#include "trace_out.h"
#include "sun_com.h"
#include "led_com.h"
#include "flash_com.h"

#include "time.h"

#include "CMSIS/device/stm32f1xx.h"


uint32_t _clock = 0;
uint32_t _timeSec = 0;

void RTC_IRQHandler(void)
{
    ++_clock;
    ++_timeSec;

    RTC->CRL &= ~RTC_CRL_SECF; /* ack*/
}

void TIM5_IRQHandler(void)
{

}
