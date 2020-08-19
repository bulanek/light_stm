#ifndef SUN_COM_H
#define SUN_COM_H

#include "stdbool.h"
#include "calendar_com.h"

/** @return Intensity in 0-100. */
uint8_t getIntensity( const CALENDAR_DATE_S* const pDate,const CALENDAR_TIME_S* const pTime);

bool isSummerTime(const CALENDAR_DATE_S* const pDate);

#endif // !SUN_COM_H
