
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

static void _autoWakeUpInit(void)
{

}

void clockInit(void)
{
//    SystemInit();
}

/* Date in BinaryCodedDecimal*/
void setCalendar( const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime)
{
}

void getCalendar(CALENDAR_DATE_S* pDate, CALENDAR_TIME_S* pTime)
{
}


