
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
    IRQn_Type type = RTC_IRQn;
    NVIC_EnableIRQ(type);
    NVIC_SetPriority(type, 15U);

    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
    RTC->CRL |= RTC_CRL_CNF;
    RTC->CRH |= RTC_CRH_SECIE; /* seconds interrupt enable*/
    RTC->PRLL = 0x7FFF;         /* to have 1 sec period*/
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

/* Date in BinaryCodedDecimal*/
void setCalendar( const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime)
{
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
