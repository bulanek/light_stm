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
volatile uint16_t value = 0;
volatile uint16_t lastValue = 0;
volatile uint16_t difference;
volatile uint32_t diff256= 0;
volatile uint32_t diff256Tmp = 0;
volatile uint32_t meanDifference = 0;
volatile uint32_t value_ccif;
void TIM5_IRQHandler(void)
{
    value_ccif = TIM5->SR & TIM_SR_CC4IF;
    value = TIM5->CCR4;
    difference = (value - lastValue);
    value_ccif = TIM5->SR & TIM_SR_CC4IF;
    ++counterTimer;
    diff256Tmp += difference;
    if ((counterTimer % 0x10000 ) == 0)
    {
        diff256 = diff256Tmp;
        diff256Tmp = 0;
    }
    lastValue = value;

    
    //TIM5->SR &= ~TIM_SR_CC4IF;

}
