#ifndef CALENDAR_COM_H
#define CALENDAR_COM_H

#include "stdint.h"
#include "calendar_cfg.h"

typedef struct {
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
} CALENDAR_TIME_S;

typedef struct {
    uint16_t day;
    uint16_t month;
    uint16_t year;
    uint16_t weekDay;
} CALENDAR_DATE_S;

typedef enum {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
}WEEK_DAY_E;


void getCalendar(CALENDAR_DATE_S* pDate, CALENDAR_TIME_S* pTime);
void setCalendar(const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime);
void clockInit(void);

#endif // !CALENDAR_COM_H
