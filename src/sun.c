#include "stdint.h"
#include "calendar_cfg.h"
#include "calendar_com.h"


// Sunset in UTC time
const uint32_t SUNSET_MONTHS_IN_MIN[12] = {
        15 * 60 + 49,
        16 * 60 + 31,
        17 * 60 + 16,
        18 * 60 + 7,
        18 * 60 * 58,
        19 * 60 + 46,
        19 * 60 + 59,
        19 * 60 + 23,
        18 * 60 + 19,
        17 * 60 + 12,
        16 * 60 + 12,
        15 * 60 + 40
};

// Sunrise in UTC time
const uint32_t SUNRISE_MONTHS_IN_MIN[12] = {
        7 * 60 + 01,
        6 * 60 + 35,
        5 * 60 + 45,
        4 * 60 + 38,
        3 * 60 * 38,
        2 * 60 + 57,
        2 * 60 + 56,
        3 * 60 + 31,
        4 * 60 + 17,
        5 * 60 + 02,
        5 * 60 + 52,
        6 * 60 + 39
};

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

static uint32_t _getSunsetRiseInSec(const CALENDAR_DATE_S* pDate, const uint32_t* const pSunsetRiseInMin)
{
    if ((pSunsetRiseInMin != SUNSET_MONTHS_IN_MIN) && (pSunsetRiseInMin != SUNRISE_MONTHS_IN_MIN)) return 0;
    uint32_t sunsetRiseInSec = pSunsetRiseInMin[pDate->month - 1] * 60U;
    return sunsetRiseInSec;
}

uint8_t _getIntensitySunset(const CALENDAR_TIME_S* const pTime, const CALENDAR_DATE_S* const pDate)
{
    uint32_t timeSec = pTime->hour * 3600U + pTime->minute * 60U + pTime->second;
    uint32_t sunsetInSec = _getSunsetRiseInSec(pDate, SUNSET_MONTHS_IN_MIN);

    uint32_t startTimeSec = sunsetInSec - LIGHT_START_BEFORE_SUNSET_SEC;
    uint32_t endTimeSec = LIGHT_STOP_SEC;

    return endTimeSec > startTimeSec ? _computeTriangleRatioU32(timeSec, startTimeSec, endTimeSec) : 0U;
}

uint8_t _getIntensitySunrise(const CALENDAR_TIME_S* const pTime, const CALENDAR_DATE_S* const pDate) {
    uint32_t timeSec = pTime->hour * 3600U + pTime->minute * 60U + pTime->second;

    uint32_t sunRiseInSec = _getSunsetRiseInSec(pDate, SUNRISE_MONTHS_IN_MIN);

    uint32_t startTimeSec = LIGHT_START_SEC;
    uint32_t endTimeSec = LIGHT_STOP_AFTER_SUNRISE + sunRiseInSec;

    return endTimeSec > startTimeSec ? _computeTriangleRatioU32(timeSec, startTimeSec, endTimeSec) : 0U;
}

uint8_t getIntensity( const CALENDAR_DATE_S* const pDate,const CALENDAR_TIME_S* const pTime) {
    uint8_t intensity = 0U;
    intensity = _getIntensitySunset(pTime, pDate);
    if (intensity == 0U)
    {
        intensity = _getIntensitySunrise(pTime, pDate);
    }
    return intensity;
}

