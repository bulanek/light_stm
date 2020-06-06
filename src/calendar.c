#include "stm8l.h"
#include "stdio.h"

#include "calendar_com.h"
#include "calendar_cfg.h"

static void _rtcUnLock(void)
{
    RTC_WPR->KEY = 0xCA;
    RTC_WPR->KEY = 0x53;
}

static void _rtcLock(void)
{
    RTC_WPR->KEY = 0xFF;
}    

static void _autoWakeUpInit(void)
{
    RTC_CR2->WUTE = 0U; /* disable wakeup timer*/
    while (RTC_ISR1->WUTWF != 1U); /* access to autoreload counter*/
    RTC_WUTRL->WUT = WAKEUP_TIME_S & 0xFF;
    RTC_WUTRH->WUT = WAKEUP_TIME_S >> 8;
    RTC_CR1->WUCKSEL = 0b100; /* ck_spre used*/
    RTC_CR2->WUTIE = 1U;  /* Allow wakeup interrupt*/
    RTC_CR2->WUTE = 1U;
}

void rtcInit(void)
{
    _rtcUnLock();
    RTC_ISR1->INIT = 1U;
    while (RTC_ISR1->INITF == 0U);
    RTC_ISR1->INIT = 0U;
    _rtcLock();
}

/* Date in BinaryCodedDecimal*/
void setCalendar( const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime)
{
    _rtcUnLock();

    if (pDate != NULL)
    {
        RTC_DR1->DU = pDate->day % 10;
        RTC_DR1->DT = pDate->day / 10;

        RTC_DR2->MU = pDate->month % 10;
        RTC_DR2->MT = pDate->month / 10;

        RTC_DR3->YU = pDate->year % 10;
        RTC_DR3->YT = pDate->year / 10;
    }

    if (pTime != NULL)
    {
        RTC_TR1->SU = pTime->second % 10U;
        RTC_TR1->ST = pTime->second / 10U;

        RTC_TR2->MNU = pTime->minute % 10U;
        RTC_TR2->MNT = pTime->minute / 10U;

        RTC_TR3->HU = pTime->hour % 10U;
        RTC_TR3->HT = pTime->hour / 10U;
    }
    _rtcLock();
}

void getCalendar(CALENDAR_DATE_S* pDate, CALENDAR_TIME_S* pTime)
{
    if (pDate != NULL)
    {
        pDate->day = RTC_DR1->DT * 10U + RTC_DR1->DU;
        pDate->month = RTC_DR2->MT * 10U + RTC_DR2->MU;
        pDate->year = RTC_DR3->YT * 10U + RTC_DR3->YU;
    }

    if (pTime != NULL)
    {
        pTime->second = RTC_TR1->ST * 10U + RTC_TR1->SU;
        pTime->minute = RTC_TR2->MNT * 10U + RTC_TR2->MNU;
        pTime->hour = RTC_TR3->HT * 10U + RTC_TR3->HU;
    }
}

void _wakeupInterrupt(void) __interrupt(RTC_ALARM_IRQ_NO) {

    CALENDAR_DATE_S date;
    CALENDAR_TIME_S time;
    getCalendar(&date, &time);
    uint8_t intensity = getIntensity(&date, &time);
    sendIntensity(intensity);
}

