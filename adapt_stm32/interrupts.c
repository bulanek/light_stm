#include "calendar_com.h"
#include "calendar_cfg.h"
#include "trace_out.h"
#include "sun_com.h"
#include "led_com.h"
#include "flash_com.h"

#include "time.h"

#include "CMSIS/device/stm32f1xx.h"

#include "stdio.h"

uint32_t _clock = 0;
uint32_t _timeSec = 0;

void RTC_IRQHandler(void)
{
    ++_clock;
    ++_timeSec;

    RTC->CRL &= ~RTC_CRL_SECF; /* ack*/
}

static int counterTimer = 0;
volatile uint32_t value = 0;
volatile uint32_t lastValue = 0;
volatile uint32_t difference;
volatile uint32_t diff128= 0;
volatile uint32_t diff128Tmp = 0;
volatile uint32_t meanDifference = 0;
volatile uint32_t value_ccif;
void TIM5_IRQHandler(void)
{
    value_ccif = TIM5->SR & TIM_SR_CC4IF;
    value = TIM5->CCR4;
    difference = (value - lastValue);
    lastValue = value;
    value_ccif = TIM5->SR & TIM_SR_CC4IF;
    ++counterTimer;
    diff128Tmp += difference;
    if ((counterTimer % 128 ) == 0)
    {
        diff128 = diff128Tmp;
        diff128Tmp = 0;
    }
    
    //TIM5->SR &= ~TIM_SR_CC4IF;

}
