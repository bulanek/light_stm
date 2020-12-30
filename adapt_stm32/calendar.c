
#include "stdio.h"

#include "calendar_com.h"
#include "calendar_cfg.h"
#include "CMSIS/device/system_stm32f1xx.h"
#include "stm32f103xb.h"

static void _rtcUnLock(void)
{
}

static void _rtcLock(void)
{
}

static void _rtcInit(void)
{
    while ((RCC->CR | RTC_CRL_RTOFF) == 0);
//    RTC->CR |= RTC_CRL

}

void clockInit(void)
{
//    SystemInit();
    RCC->CR |= RCC_CR_HSION;
}

/* Date in BinaryCodedDecimal*/
void setCalendar( const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime)
{
}

void getCalendar(CALENDAR_DATE_S* pDate, CALENDAR_TIME_S* pTime)
{
}

