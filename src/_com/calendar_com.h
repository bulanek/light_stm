#ifndef CALENDAR_COM_H
#define CALENDAR_COM_H

#include "stdint.h"
#include "calendar_cfg.h"

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} CALENDAR_TIME_S;

typedef struct {
    uint8_t day;
    uint8_t month;
    uint8_t year;
} CALENDAR_DATE_S;


void getCalendar(CALENDAR_DATE_S* pDate, CALENDAR_TIME_S* pTime);
void setCalendar(const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime);
void rtcInit(void);

void uartDebugInit(void);

uint8_t getIntensity( const CALENDAR_DATE_S* const pDate,const CALENDAR_TIME_S* const pTime);

void sendIntensity(const uint8_t intensity);


#endif // !CALENDAR_COM_H
