#ifndef CALENDAR_CFG_H
#define CALENDAR_CFG_H

#define WAKEUP_TIME_SEC   60U

#define TIME_UPDATE_INTERVAL_SEC 36000U

#define LIGHT_STOP_AFTER_SUNRISE 3600U

#define LIGHT_START_BEFORE_SUNSET_SEC 3600U

// Light start, time in seconds after midnight; (6:40)
#define LIGHT_START_SEC 24000UL
// Light stop, time in seconds after midnight; (23:00)
#define LIGHT_STOP_SEC ((uint32_t)82800U )


#endif // !CALENDAR_CFG_H

