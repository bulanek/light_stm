#include "stdint.h"
#include "stdbool.h"
#include "calendar_cfg.h"
#include "calendar_com.h"

#include "sun_com.h"


// Sunset in UTC time
static const uint32_t SUNSET_MONTHS_UTC_IN_MIN[] = {
        15 * 60 + 29, /* 1*/
        16 * 60 + 21, /* 2*/
        17 * 60 +  9, /* 3*/
        18 * 60 +  7, /* 4*/
        18 * 60 * 43, /* 5*/
        19 * 60 + 14, /* 6*/
        19 * 60 + 05, /* 7*/
        18 * 60 + 18, /* 8*/
        17 * 60 + 12, /* 9*/
        16 * 60 +  6, /* 10*/
        15 * 60 + 16, /* 11*/
        15 * 60 +  0  /* 12*/
};

// Sunrise in UTC time
static const uint32_t SUNRISE_MONTHS_UTC_IN_MIN[] = {
        5 * 60 + 54, /* 1*/
        6 * 60 + 12, /* 2*/
        5 * 60 + 13, /* 3*/
        4 * 60 +  6, /* 4*/
        3 * 60 * 14, /* 5*/
        2 * 60 + 52, /* 6*/
        3 * 60 + 11, /* 7*/
        3 * 60 + 53, /* 8*/
        4 * 60 + 40, /* 9*/
        5 * 60 + 26, /* 10*/
        6 * 60 + 17, /* 11*/
        6 * 60 + 55  /* 12*/
};

static bool _isSummerTimeMarch(const CALENDAR_DATE_S* const pDate)
{
    // week with april
    if (((7 - pDate->weekDay) + pDate->day) > 31) return true;
    // week without april
    if (pDate->weekDay < 7) return false;
    // sunday
    if ((pDate->day + 7) > 31) return true;
    return false;
}

static bool _isSummerTimeOctober(const CALENDAR_DATE_S* const pDate)
{
    // week with november
    if (((7 - pDate->weekDay) + pDate->day) > 31) return false;
    // week without november
    if (pDate->weekDay < 7) return true;
    // sunday
    if ((pDate->day + 7) > 31) return false;
    return true;
}


bool isSummerTime(const CALENDAR_DATE_S* const pDate)
{
    bool retVal = false;
    do
    {
        if ((pDate->month < 3) || (pDate->month > 10))
        {
            break;
        }

        if ((pDate->month > 3) && (pDate->month < 10))
        {
            retVal = true;
            break;
        }

        if (pDate->month == 3) { /* march or october*/
            retVal = _isSummerTimeMarch(pDate);
        }
        else {
            retVal = _isSummerTimeOctober(pDate);
        }
    } while (0);
    return retVal;
}

/* 0-100 value*/
static uint8_t _computeTriangleRatioU32(const uint32_t timeSec, const uint32_t startTimeSec, const uint32_t endTimeSec)
{
    uint32_t middleTimeSec = (endTimeSec >> 1) + (startTimeSec >> 1);
    uint8_t intensity = 0U;
    if ((timeSec > startTimeSec) && (timeSec < middleTimeSec)) {
        // note may be uint32_t, pay attention on order of arg. eval.
        intensity = (uint8_t)((100U * (timeSec - startTimeSec)) / (middleTimeSec - startTimeSec));
    }
    else if ((timeSec > middleTimeSec) && (timeSec < endTimeSec)) {
        intensity = (uint8_t)((100U * (endTimeSec - timeSec)) / (middleTimeSec - startTimeSec));
    }
    else {
    }
    return intensity;
}

static uint32_t _getSunsetRiseUTCInSec(const CALENDAR_DATE_S* pDate, const uint32_t* const pSunsetRiseInMin)
{
    if ((pSunsetRiseInMin != SUNSET_MONTHS_UTC_IN_MIN) && (pSunsetRiseInMin != SUNRISE_MONTHS_UTC_IN_MIN)) return 0;
    uint32_t sunsetRiseInSec = pSunsetRiseInMin[pDate->month - 1] * 60U;
    return sunsetRiseInSec;
}

static uint8_t _getIntensitySunset(const CALENDAR_TIME_S* const pTime, const CALENDAR_DATE_S* const pDate)
{
    uint32_t timeSec = (uint32_t)pTime->hour * 3600U + (uint32_t)pTime->minute * 60U + pTime->second;
    uint32_t sunsetInSec = _getSunsetRiseUTCInSec(pDate, SUNSET_MONTHS_UTC_IN_MIN);
    sunsetInSec += 3600; /* UTC+1*/
    if (isSummerTime(pDate) == true)
    {
        sunsetInSec += 3600U;
    }

    uint32_t startTimeSec = sunsetInSec - LIGHT_START_BEFORE_SUNSET_SEC;
    uint32_t endTimeSec = LIGHT_STOP_SEC;

    return endTimeSec > startTimeSec ? _computeTriangleRatioU32(timeSec, startTimeSec, endTimeSec) : 0U;
}

static uint8_t _getIntensitySunrise(const CALENDAR_TIME_S* const pTime, const CALENDAR_DATE_S* const pDate) {
    uint32_t timeSec = pTime->hour * 3600U + pTime->minute * 60U + pTime->second;

    uint32_t sunRiseInSec = _getSunsetRiseUTCInSec(pDate, SUNRISE_MONTHS_UTC_IN_MIN);
    sunRiseInSec += 3600; /* UTC+1*/
    if (isSummerTime(pDate) == true)
    {
        sunRiseInSec += 3600U;
    }

    uint32_t startTimeSec = LIGHT_START_SEC;
    uint32_t endTimeSec = LIGHT_STOP_AFTER_SUNRISE + sunRiseInSec;

    return endTimeSec > startTimeSec ? _computeTriangleRatioU32(timeSec, startTimeSec, endTimeSec) : 0U;
}

uint8_t getIntensity(const CALENDAR_DATE_S* const pDate, const CALENDAR_TIME_S* const pTime) {
    uint8_t intensity = 0U;
    intensity = _getIntensitySunset(pTime, pDate);
    if (intensity == 0U)
    {
        intensity = _getIntensitySunrise(pTime, pDate);
    }
    return intensity;
}

