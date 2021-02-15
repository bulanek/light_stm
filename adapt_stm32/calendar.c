
#include "stdio.h"

#include "calendar_com.h"
#include "calendar_cfg.h"
#include "CMSIS/device/system_stm32f1xx.h"
#include "stm32f1xx.h"
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
    IRQn_Type type = TIM5_IRQn;
    NVIC_EnableIRQ(type);
    NVIC_SetPriority(type, 15U);

    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    TIM5->CCMR2 |= TIM_CCMR2_CC4S_0; /* CC4 channel is configured as input, IC4 is mapped on TI4 */
    TIM5->DIER |= TIM_DIER_CC4IE;
    TIM5->CCER |= TIM_CCER_CC4E;

    //TIM5->SR &= ~TIM_SR_CC4IF;
    TIM5->CR1 |= TIM_CR1_CEN;
    AFIO->MAPR |= AFIO_MAPR_TIM5CH4_IREMAP;
}

static void _rtcInit(void)
{
    IRQn_Type type = RTC_IRQn;
    NVIC_EnableIRQ(type);
    NVIC_SetPriority(type, 15U);

    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
    RTC->CRL |= RTC_CRL_CNF;
    RTC->CRH |= RTC_CRH_SECIE; /* seconds interrupt enable*/
//    RTC->PRLL = 0x9C3F;         /* to have 1 sec period (40kHz)*/
    RTC->PRLL = 0x9A6F;         /* to have 1 sec period (40kHz) -> 9A70 - 1*/

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


    _calibrationInit();
    _rtcInit();
    
}

extern uint32_t _timeSec;
/* Date in BinaryCodedDecimal*/
void setCalendar( const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime)
{
    struct tm timeS;
    timeS.tm_year = pDate->year + 100U;
    timeS.tm_mon = pDate->month;
    timeS.tm_mday = pDate->day;
    timeS.tm_wday = pDate->weekDay;

    timeS.tm_hour = pTime->hour;
    timeS.tm_min = pTime->minute;
    timeS.tm_sec = pTime->second;
    __disable_irq();
    _timeSec = mktime(&timeS);
    __enable_irq();
    time_t unixTime = time(NULL);
    struct tm* timeCurrent =localtime(&unixTime);

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
