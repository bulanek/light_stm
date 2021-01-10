
#include "stdio.h"

#include "calendar_com.h"
#include "calendar_cfg.h"
#include "CMSIS/device/system_stm32f1xx.h"
#include "stm32f103xb.h"
#include "trace_out.h"

#include "time.h"

static void _rtcUnLock(void)
{
}

static void _rtcLock(void)
{
}

static void _calibrationInit(void)
{
}

static void _rtcInit(void)
{
    IRQn_Type type = RTC_IRQn;
    NVIC_EnableIRQ(type);
    NVIC_SetPriority(type, 15U);

    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
    RTC->CRL |= RTC_CRL_CNF;
    RTC->CRH |= RTC_CRH_SECIE; /* seconds interrupt enable*/
    RTC->PRLL = 0x9C3F;         /* to have 1 sec period (40kHz)*/
    RTC->CRL &= ~RTC_CRL_CNF;
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
}

void clockInit(void)
{
//    SystemInit();
    RCC->CR |= RCC_CR_HSION;
    RCC->CSR |= RCC_CSR_LSION;

    /* Backup registers and RTC enable*/
    RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;
    PWR->CR |= PWR_CR_DBP;

    RCC->BDCR |= RCC_BDCR_RTCEN;
    RCC->BDCR |= RCC_BDCR_RTCSEL_1; /* LSI oscilator*/

    while ((RCC->CSR & RCC_CSR_LSIRDY) == 0);

    _rtcInit();
}

extern uint32_t _timeSec;
/* Date in BinaryCodedDecimal*/
void setCalendar( const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime)
{
    struct tm time;
    time.tm_year = pDate->year + 100U;
    time.tm_mon = pDate->month;
    time.tm_mday = pDate->day;
    time.tm_wday = pDate->weekDay;

    time.tm_hour = pTime->hour;
    time.tm_min = pTime->minute;
    time.tm_sec = pTime->second;
    _timeSec = mktime(&time);
}

void getCalendar(CALENDAR_DATE_S* pDate, CALENDAR_TIME_S* pTime)
{
    clock_t	c = clock()/4;
    struct tm* timeCurrent;


    time_t unixtime = time(NULL);
    timeCurrent = localtime(&unixtime);
    if (pDate != NULL)
    {
        pDate->day = timeCurrent->tm_mday;
        pDate->month = timeCurrent->tm_mon;
        pDate->year = timeCurrent->tm_year - 100U;
        pDate->weekDay = timeCurrent->tm_wday;
    }

    if (pTime != NULL)
    {
        pTime->hour = timeCurrent->tm_hour;
        pTime->minute = timeCurrent->tm_min;
        pTime->second = timeCurrent->tm_sec;
    }
}
