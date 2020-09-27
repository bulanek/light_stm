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
#if (WAKEUP_TIME_SEC <= 0)
#error("WAKEUP_TIME == 0")
#endif

    RTC_CR2->WUTE = 0U; /* disable wakeup timer*/
    RTC_CR2->WUTIE = 0U;
    while (RTC_ISR1->WUTWF == 0U); /* access to autoreload counter*/
    RTC_WUTRL->WUT = (WAKEUP_TIME_SEC - 1) & 0xFF;
    RTC_WUTRH->WUT = ((WAKEUP_TIME_SEC - 1) >> 8) & 0xFF;
    RTC_CR1->WUCKSEL = 0b100; /* ck_spre used (1 Hz counter)*/
    RTC_CR2->WUTIE = 1U;  /* Allow wakeup interrupt*/
    RTC_CR2->WUTE = 1U;
}

void clockInit(void)
{

	CLK_DIVR = 0x00; // Set the frequency to 16 MHz
    CLK_PCKENR2->RTC = 1;
    while (CLK_CRTCR->RTCSWBSY);
    CLK_CRTCR->RTCSEL = CLOCK_LSE;
    CLK_ECKR->LSEON = 1;
    while (CLK_ECKR->LSERDY == 0);
    _rtcUnLock();
    RTC_ISR1->INIT = 1U;
    while (RTC_ISR1->INITF == 0U);

    RTC_APRER->PREDIV_A  = 0x7F;
    RTC_SPRERH->PREDIV_S = 0x00;
    RTC_SPRERL->PREDIV_S = 0xFF;

    RTC_ISR1->INIT = 0U;
    _autoWakeUpInit();

    _rtcLock();
}

/* Date in BinaryCodedDecimal*/
void setCalendar( const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime)
{
    _rtcUnLock();
    RTC_ISR1->INIT = 1U;
    while (RTC_ISR1->INITF == 0U);

    if (pDate != NULL)
    {
        RTC_DR1->DU = pDate->day % 10;
        RTC_DR1->DT = pDate->day / 10;

        RTC_DR2->MU = pDate->month % 10;
        RTC_DR2->MT = pDate->month / 10;

        RTC_DR3->YU = pDate->year % 10;
        RTC_DR3->YT = pDate->year / 10;

        RTC_DR2->WDU = pDate->weekDay;
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
    RTC_ISR1->INIT = 0U;
    _rtcLock();
}

void getCalendar(CALENDAR_DATE_S* pDate, CALENDAR_TIME_S* pTime)
{
    if (pDate != NULL)
    {
        pDate->day = RTC_DR1->DT * 10U + RTC_DR1->DU;
        pDate->month = RTC_DR2->MT * 10U + RTC_DR2->MU;
        pDate->year = RTC_DR3->YT * 10U + RTC_DR3->YU;
        pDate->weekDay = (uint8_t)(RTC_DR2->WDU*1);
    }

    if (pTime != NULL)
    {
        pTime->second = RTC_TR1->ST * 10U + RTC_TR1->SU;
        pTime->minute = RTC_TR2->MNT * 10U + RTC_TR2->MNU;
        pTime->hour = RTC_TR3->HT * 10U + RTC_TR3->HU;
    }
}


